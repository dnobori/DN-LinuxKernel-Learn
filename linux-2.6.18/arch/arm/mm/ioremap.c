#include "linux/autoconf.h"
/*
 *  linux/arch/arm/mm/ioremap.c
 *
 * Re-map IO memory to kernel address space so that we can access it.
 *
 * (C) Copyright 1995 1996 Linus Torvalds
 *
 * Hacked for ARM by Phil Blundell <philb@gnu.org>
 * Hacked to allow all architectures to build, and various cleanups
 * by Russell King
 *
 * This allows a driver to remap an arbitrary region of bus memory into
 * virtual space.  One should *only* use readl, writel, memcpy_toio and
 * so on with such remapped areas.
 *
 * Because the ARM only has a 32-bit address space we can't address the
 * whole of the (physical) PCI space at once.  PCI huge-mode addressing
 * allows us to circumvent this restriction by splitting PCI space into
 * two 2GB chunks and mapping only one at a time into processor memory.
 * We use MMU protection domains to trap any attempt to access the bank
 * that is not currently mapped.  (This isn't fully implemented yet.)
 */
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/vmalloc.h>

#include <asm/cacheflush.h>
#include <asm/io.h>
#include <asm/mmu_context.h>
#include <asm/pgalloc.h>
#include <asm/tlbflush.h>
#include <asm/sizes.h>

/*
 * Used by ioremap() and iounmap() code to mark (super)section-mapped
 * I/O regions in vm_struct->flags field.
 */
#define VM_ARM_SECTION_MAPPING	0x80000000

static inline void
remap_area_pte(pte_t * pte, unsigned long address, unsigned long size,
	       unsigned long phys_addr, pgprot_t pgprot)
{
	unsigned long end;

	address &= ~PMD_MASK;
	end = address + size;
	if (end > PMD_SIZE)
		end = PMD_SIZE;
	BUG_ON(address >= end);
	do {
		if (!pte_none(*pte))
			goto bad;

		set_pte(pte, pfn_pte(phys_addr >> PAGE_SHIFT, pgprot));
		address += PAGE_SIZE;
		phys_addr += PAGE_SIZE;
		pte++;
	} while (address && (address < end));
	return;

 bad:
	printk("remap_area_pte: page already exists\n");
	BUG();
}

static inline int
remap_area_pmd(pmd_t * pmd, unsigned long address, unsigned long size,
	       unsigned long phys_addr, unsigned long flags)
{
	unsigned long end;
	pgprot_t pgprot;

	address &= ~PGDIR_MASK;
	end = address + size;

	if (end > PGDIR_SIZE)
		end = PGDIR_SIZE;

	phys_addr -= address;
	BUG_ON(address >= end);

	pgprot = __pgprot(L_PTE_PRESENT | L_PTE_YOUNG | L_PTE_DIRTY | L_PTE_WRITE | flags);
	do {
		pte_t * pte = pte_alloc_kernel(pmd, address);
		if (!pte)
			return -ENOMEM;
		remap_area_pte(pte, address, end - address, address + phys_addr, pgprot);
		address = (address + PMD_SIZE) & PMD_MASK;
		pmd++;
	} while (address && (address < end));
	return 0;
}

static int
remap_area_pages(unsigned long start, unsigned long pfn,
		 unsigned long size, unsigned long flags)
{
	unsigned long address = start;
	unsigned long end = start + size;
	unsigned long phys_addr = __pfn_to_phys(pfn);
	int err = 0;
	pgd_t * dir;

	phys_addr -= address;
	dir = pgd_offset(&init_mm, address);
	BUG_ON(address >= end);
	do {
		pmd_t *pmd = pmd_alloc(&init_mm, dir, address);
		if (!pmd) {
			err = -ENOMEM;
			break;
		}
		if (remap_area_pmd(pmd, address, end - address,
					 phys_addr + address, flags)) {
			err = -ENOMEM;
			break;
		}

		address = (address + PGDIR_SIZE) & PGDIR_MASK;
		dir++;
	} while (address && (address < end));

	return err;
}


void __check_kvm_seq(struct mm_struct *mm)
{
	unsigned int seq;

	do {
		seq = init_mm.context.kvm_seq;
		memcpy(pgd_offset(mm, VMALLOC_START),
		       pgd_offset_k(VMALLOC_START),
		       sizeof(pgd_t) * (pgd_index(VMALLOC_END) -
					pgd_index(VMALLOC_START)));
		mm->context.kvm_seq = seq;
	} while (seq != init_mm.context.kvm_seq);
}

#ifndef CONFIG_SMP
/*
 * Section support is unsafe on SMP - If you iounmap and ioremap a region,
 * the other CPUs will not see this change until their next context switch.
 * Meanwhile, (eg) if an interrupt comes in on one of those other CPUs
 * which requires the new ioremap'd region to be referenced, the CPU will
 * reference the _old_ region.
 *
 * Note that get_vm_area() allocates a guard 4K page, so we need to mask
 * the size back to 1MB aligned or we will overflow in the loop below.
 */
static void unmap_area_sections(unsigned long virt, unsigned long size)
{
	unsigned long addr = virt, end = virt + (size & ~SZ_1M);
	pgd_t *pgd;

	flush_cache_vunmap(addr, end);
	pgd = pgd_offset_k(addr);
	do {
		pmd_t pmd, *pmdp = pmd_offset(pgd, addr);

		pmd = *pmdp;
		if (!pmd_none(pmd)) {
			/*
			 * Clear the PMD from the page table, and
			 * increment the kvm sequence so others
			 * notice this change.
			 *
			 * Note: this is still racy on SMP machines.
			 */
			pmd_clear(pmdp);
			init_mm.context.kvm_seq++;

			/*
			 * Free the page table, if there was one.
			 */
			if ((pmd_val(pmd) & PMD_TYPE_MASK) == PMD_TYPE_TABLE)
				pte_free_kernel(pmd_page_kernel(pmd));
		}

		addr += PGDIR_SIZE;
		pgd++;
	} while (addr < end);

	/*
	 * Ensure that the active_mm is up to date - we want to
	 * catch any use-after-iounmap cases.
	 */
	if (current->active_mm->context.kvm_seq != init_mm.context.kvm_seq)
		__check_kvm_seq(current->active_mm);

	flush_tlb_kernel_range(virt, end);
}

static int
remap_area_sections(unsigned long virt, unsigned long pfn,
		    unsigned long size, unsigned long flags)
{
	unsigned long prot, addr = virt, end = virt + size;
	pgd_t *pgd;

	/*
	 * Remove and free any PTE-based mapping, and
	 * sync the current kernel mapping.
	 */
	unmap_area_sections(virt, size);

	prot = PMD_TYPE_SECT | PMD_SECT_AP_WRITE | PMD_DOMAIN(DOMAIN_IO) |
	       (flags & (L_PTE_CACHEABLE | L_PTE_BUFFERABLE));

	/*
	 * ARMv6 and above need XN set to prevent speculative prefetches
	 * hitting IO.
	 */
	if (cpu_architecture() >= CPU_ARCH_ARMv6)
		prot |= PMD_SECT_XN;

	pgd = pgd_offset_k(addr);
	do {
		pmd_t *pmd = pmd_offset(pgd, addr);

		pmd[0] = __pmd(__pfn_to_phys(pfn) | prot);
		pfn += SZ_1M >> PAGE_SHIFT;
		pmd[1] = __pmd(__pfn_to_phys(pfn) | prot);
		pfn += SZ_1M >> PAGE_SHIFT;
		flush_pmd_entry(pmd);

		addr += PGDIR_SIZE;
		pgd++;
	} while (addr < end);

	return 0;
}

static int
remap_area_supersections(unsigned long virt, unsigned long pfn,
			 unsigned long size, unsigned long flags)
{
	unsigned long prot, addr = virt, end = virt + size;
	pgd_t *pgd;

	/*
	 * Remove and free any PTE-based mapping, and
	 * sync the current kernel mapping.
	 */
	unmap_area_sections(virt, size);

	prot = PMD_TYPE_SECT | PMD_SECT_SUPER | PMD_SECT_AP_WRITE |
			PMD_DOMAIN(DOMAIN_IO) |
			(flags & (L_PTE_CACHEABLE | L_PTE_BUFFERABLE));

	/*
	 * ARMv6 and above need XN set to prevent speculative prefetches
	 * hitting IO.
	 */
	if (cpu_architecture() >= CPU_ARCH_ARMv6)
		prot |= PMD_SECT_XN;

	pgd = pgd_offset_k(virt);
	do {
		unsigned long super_pmd_val, i;

		super_pmd_val = __pfn_to_phys(pfn) | prot;
		super_pmd_val |= ((pfn >> (32 - PAGE_SHIFT)) & 0xf) << 20;

		for (i = 0; i < 8; i++) {
			pmd_t *pmd = pmd_offset(pgd, addr);

			pmd[0] = __pmd(super_pmd_val);
			pmd[1] = __pmd(super_pmd_val);
			flush_pmd_entry(pmd);

			addr += PGDIR_SIZE;
			pgd++;
		}

		pfn += SUPERSECTION_SIZE >> PAGE_SHIFT;
	} while (addr < end);

	return 0;
}
#endif


/*
 * Remap an arbitrary physical address space into the kernel virtual
 * address space. Needed when the kernel wants to access high addresses
 * directly.
 *
 * NOTE! We need to allow non-page-aligned mappings too: we will obviously
 * have to convert them into an offset in a page-aligned mapping, but the
 * caller shouldn't need to know that small detail.
 *
 * 'flags' are the extra L_PTE_ flags that you want to specify for this
 * mapping.  See include/asm-arm/proc-armv/pgtable.h for more information.
 */
void __iomem *
__ioremap_pfn(unsigned long pfn, unsigned long offset, size_t size,
	      unsigned long flags)
{
	int err;
	unsigned long addr;
 	struct vm_struct * area;

	/*
	 * High mappings must be supersection aligned
	 */
	if (pfn >= 0x100000 && (__pfn_to_phys(pfn) & ~SUPERSECTION_MASK))
		return NULL;

 	area = get_vm_area(size, VM_IOREMAP);
 	if (!area)
 		return NULL;
 	addr = (unsigned long)area->addr;

#ifndef CONFIG_SMP
	if ((((cpu_architecture() >= CPU_ARCH_ARMv6) && (get_cr() & CR_XP)) ||
	       cpu_is_xsc3()) &&
	       !((__pfn_to_phys(pfn) | size | addr) & ~SUPERSECTION_MASK)) {
		area->flags |= VM_ARM_SECTION_MAPPING;
		err = remap_area_supersections(addr, pfn, size, flags);
	} else if (!((__pfn_to_phys(pfn) | size | addr) & ~PMD_MASK)) {
		area->flags |= VM_ARM_SECTION_MAPPING;
		err = remap_area_sections(addr, pfn, size, flags);
	} else
#endif
		err = remap_area_pages(addr, pfn, size, flags);

	if (err) {
 		vunmap((void *)addr);
 		return NULL;
 	}

	flush_cache_vmap(addr, addr + size);
	return (void __iomem *) (offset + addr);
}
EXPORT_SYMBOL(__ioremap_pfn);

void __iomem *
__ioremap(unsigned long phys_addr, size_t size, unsigned long flags)
{
	unsigned long last_addr;
 	unsigned long offset = phys_addr & ~PAGE_MASK;
 	unsigned long pfn = __phys_to_pfn(phys_addr);

 	/*
 	 * Don't allow wraparound or zero size
	 */
	last_addr = phys_addr + size - 1;
	if (!size || last_addr < phys_addr)
		return NULL;

	/*
 	 * Page align the mapping size
	 */
	size = PAGE_ALIGN(last_addr + 1) - phys_addr;

 	return __ioremap_pfn(pfn, offset, size, flags);
}
EXPORT_SYMBOL(__ioremap);

void __iounmap(void __iomem *addr)
{
#ifndef CONFIG_SMP
	struct vm_struct **p, *tmp;
#endif
	unsigned int section_mapping = 0;

	addr = (void __iomem *)(PAGE_MASK & (unsigned long)addr);

#ifndef CONFIG_SMP
	/*
	 * If this is a section based mapping we need to handle it
	 * specially as the VM subysystem does not know how to handle
	 * such a beast. We need the lock here b/c we need to clear
	 * all the mappings before the area can be reclaimed
	 * by someone else.
	 */
	write_lock(&vmlist_lock);
	for (p = &vmlist ; (tmp = *p) ; p = &tmp->next) {
		if((tmp->flags & VM_IOREMAP) && (tmp->addr == addr)) {
			if (tmp->flags & VM_ARM_SECTION_MAPPING) {
				*p = tmp->next;
				unmap_area_sections((unsigned long)tmp->addr,
						    tmp->size);
				kfree(tmp);
				section_mapping = 1;
			}
			break;
		}
	}
	write_unlock(&vmlist_lock);
#endif

	if (!section_mapping)
		vunmap(addr);
}
EXPORT_SYMBOL(__iounmap);