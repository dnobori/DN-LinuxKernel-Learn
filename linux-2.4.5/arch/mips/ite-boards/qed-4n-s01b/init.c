#include "linux/autoconf.h"
/*
 *
 * BRIEF MODULE DESCRIPTION
 *	IT8172/QED5231 board setup.
 *
 * Copyright 2000 MontaVista Software Inc.
 * Author: MontaVista Software, Inc.
 *         	ppopov@mvista.com or support@mvista.com
 *
 *  This program is free software; you can redistribute  it and/or modify it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS'' AND   ANY  EXPRESS OR IMPLIED
 *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
 *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License along
 *  with this program; if not, write  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <linux/init.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/bootmem.h>
#include <asm/addrspace.h>
#include <asm/bootinfo.h>
#include <linux/string.h>
#include <linux/kernel.h>
#include <asm/it8172/it8172.h>
#include <asm/it8172/it8172_dbg.h>

int prom_argc;
char **prom_argv, **prom_envp;

extern char _end;
extern void  __init prom_init_cmdline(void);
extern unsigned long __init prom_get_memsize(void);
extern void __init it8172_init_ram_resource(unsigned long memsize);

#define PFN_UP(x)	(((x) + PAGE_SIZE-1) >> PAGE_SHIFT)
#define PFN_ALIGN(x)	(((unsigned long)(x) + (PAGE_SIZE - 1)) & PAGE_MASK)


int __init prom_init(int argc, char **argv, char **envp, int *prom_vec)
{
	unsigned long mem_size, free_start, free_end, bootmap_size;
	unsigned long pcicr;

	prom_argc = argc;
	prom_argv = argv;
	prom_envp = envp;

	puts("ITE board running...");

	mips_machgroup = MACH_GROUP_ITE;
	mips_machtype = MACH_QED_4N_S01B;  /* ITE board name/number */

	prom_init_cmdline();
	mem_size = prom_get_memsize();

	printk("Memory size: %dMB\n", (unsigned)mem_size);

	mem_size <<= 20; /* MB */

	/*
	 * make the entire physical memory visible to pci bus masters
	 */
	IT_READ(IT_MC_PCICR, pcicr);
	pcicr &= ~0x1f; 
	pcicr |= (mem_size - 1) >> 22;
	IT_WRITE(IT_MC_PCICR, pcicr);

	it8172_init_ram_resource(mem_size);
	add_memory_region(0, 20 << 20, BOOT_MEM_RAM);

	return 0;
}
