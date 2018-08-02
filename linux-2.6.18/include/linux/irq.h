#include "linux/autoconf.h"
#ifndef _LINUX_IRQ_H
#define _LINUX_IRQ_H

/*
 * Please do not include this file in generic code.  There is currently
 * no requirement for any architecture to implement anything held
 * within this file.
 *
 * Thanks. --rmk
 */

#include <linux/smp.h>

#ifndef CONFIG_S390

#include <linux/linkage.h>
#include <linux/cache.h>
#include <linux/spinlock.h>
#include <linux/cpumask.h>
#include <linux/irqreturn.h>

#include <asm/irq.h>
#include <asm/ptrace.h>

/*
 * IRQ line status.
 *
 * Bits 0-16 are reserved for the IRQF_* bits in linux/interrupt.h
 *
 * IRQ types
 */
#define IRQ_TYPE_NONE		0x00000000	/* Default, unspecified type */
#define IRQ_TYPE_EDGE_RISING	0x00000001	/* Edge rising type */
#define IRQ_TYPE_EDGE_FALLING	0x00000002	/* Edge falling type */
#define IRQ_TYPE_EDGE_BOTH (IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_EDGE_RISING)
#define IRQ_TYPE_LEVEL_HIGH	0x00000004	/* Level high type */
#define IRQ_TYPE_LEVEL_LOW	0x00000008	/* Level low type */
#define IRQ_TYPE_SENSE_MASK	0x0000000f	/* Mask of the above */
#define IRQ_TYPE_PROBE		0x00000010	/* Probing in progress */

/* Internal flags */
#define IRQ_INPROGRESS		0x00010000	/* IRQ handler active - do not enter! */
#define IRQ_DISABLED		0x00020000	/* IRQ disabled - do not enter! */
#define IRQ_PENDING		0x00040000	/* IRQ pending - replay on enable */
#define IRQ_REPLAY		0x00080000	/* IRQ has been replayed but not acked yet */
#define IRQ_AUTODETECT		0x00100000	/* IRQ is being autodetected */
#define IRQ_WAITING		0x00200000	/* IRQ not yet seen - for autodetection */
#define IRQ_LEVEL		0x00400000	/* IRQ level triggered */
#define IRQ_MASKED		0x00800000	/* IRQ masked - shouldn't be seen again */
#define IRQ_PER_CPU		0x01000000	/* IRQ is per CPU */
#ifdef CONFIG_IRQ_PER_CPU
# define CHECK_IRQ_PER_CPU(var) ((var) & IRQ_PER_CPU)
#else
# define CHECK_IRQ_PER_CPU(var) 0
#endif

#define IRQ_NOPROBE		0x02000000	/* IRQ is not valid for probing */
#define IRQ_NOREQUEST		0x04000000	/* IRQ cannot be requested */
#define IRQ_NOAUTOEN		0x08000000	/* IRQ will not be enabled on request irq */
#define IRQ_DELAYED_DISABLE	0x10000000	/* IRQ disable (masking) happens delayed. */
#define IRQ_WAKEUP		0x20000000	/* IRQ triggers system wakeup */

struct proc_dir_entry;

/**
 * struct irq_chip - hardware interrupt chip descriptor
 *
 * @name:		name for /proc/interrupts
 * @startup:		start up the interrupt (defaults to ->enable if NULL)
 * @shutdown:		shut down the interrupt (defaults to ->disable if NULL)
 * @enable:		enable the interrupt (defaults to chip->unmask if NULL)
 * @disable:		disable the interrupt (defaults to chip->mask if NULL)
 * @ack:		start of a new interrupt
 * @mask:		mask an interrupt source
 * @mask_ack:		ack and mask an interrupt source
 * @unmask:		unmask an interrupt source
 * @eoi:		end of interrupt - chip level
 * @end:		end of interrupt - flow level
 * @set_affinity:	set the CPU affinity on SMP machines
 * @retrigger:		resend an IRQ to the CPU
 * @set_type:		set the flow type (IRQ_TYPE_LEVEL/etc.) of an IRQ
 * @set_wake:		enable/disable power-management wake-on of an IRQ
 *
 * @release:		release function solely used by UML
 * @typename:		obsoleted by name, kept as migration helper
 */
struct irq_chip {
	const char	*name;
	unsigned int	(*startup)(unsigned int irq);
	void		(*shutdown)(unsigned int irq);
	void		(*enable)(unsigned int irq);
	void		(*disable)(unsigned int irq);

	void		(*ack)(unsigned int irq);
	void		(*mask)(unsigned int irq);
	void		(*mask_ack)(unsigned int irq);
	void		(*unmask)(unsigned int irq);
	void		(*eoi)(unsigned int irq);

	void		(*end)(unsigned int irq);
	void		(*set_affinity)(unsigned int irq, cpumask_t dest);
	int		(*retrigger)(unsigned int irq);
	int		(*set_type)(unsigned int irq, unsigned int flow_type);
	int		(*set_wake)(unsigned int irq, unsigned int on);

	/* Currently used only by UML, might disappear one day.*/
#ifdef CONFIG_IRQ_RELEASE_METHOD
	void		(*release)(unsigned int irq, void *dev_id);
#endif
	/*
	 * For compatibility, ->typename is copied into ->name.
	 * Will disappear.
	 */
	const char	*typename;
};

/**
 * struct irq_desc - interrupt descriptor
 *
 * @handle_irq:		highlevel irq-events handler [if NULL, __do_IRQ()]
 * @chip:		low level interrupt hardware access
 * @handler_data:	per-IRQ data for the irq_chip methods
 * @chip_data:		platform-specific per-chip private data for the chip
 *			methods, to allow shared chip implementations
 * @action:		the irq action chain
 * @status:		status information
 * @depth:		disable-depth, for nested irq_disable() calls
 * @wake_depth:		enable depth, for multiple set_irq_wake() callers
 * @irq_count:		stats field to detect stalled irqs
 * @irqs_unhandled:	stats field for spurious unhandled interrupts
 * @lock:		locking for SMP
 * @affinity:		IRQ affinity on SMP
 * @cpu:		cpu index useful for balancing
 * @pending_mask:	pending rebalanced interrupts
 * @move_irq:		need to re-target IRQ destination
 * @dir:		/proc/irq/ procfs entry
 * @affinity_entry:	/proc/irq/smp_affinity procfs entry on SMP
 *
 * Pad this out to 32 bytes for cache and indexing reasons.
 */
struct irq_desc {
	void fastcall		(*handle_irq)(unsigned int irq,
					      struct irq_desc *desc,
					      struct pt_regs *regs);
	struct irq_chip		*chip;
	void			*handler_data;
	void			*chip_data;
	struct irqaction	*action;	/* IRQ action list */
	unsigned int		status;		/* IRQ status */

	unsigned int		depth;		/* nested irq disables */
	unsigned int		wake_depth;	/* nested wake enables */
	unsigned int		irq_count;	/* For detecting broken IRQs */
	unsigned int		irqs_unhandled;
	spinlock_t		lock;
#ifdef CONFIG_SMP
	cpumask_t		affinity;
	unsigned int		cpu;
#endif
#if defined(CONFIG_GENERIC_PENDING_IRQ) || defined(CONFIG_IRQBALANCE)
	cpumask_t		pending_mask;
	unsigned int		move_irq;	/* need to re-target IRQ dest */
#endif
#ifdef CONFIG_PROC_FS
	struct proc_dir_entry *dir;
#endif
} ____cacheline_aligned;

extern struct irq_desc irq_desc[NR_IRQS];

/*
 * Migration helpers for obsolete names, they will go away:
 */
#define hw_interrupt_type	irq_chip
typedef struct irq_chip		hw_irq_controller;
#define no_irq_type		no_irq_chip
typedef struct irq_desc		irq_desc_t;

/*
 * Pick up the arch-dependent methods:
 */
#include <asm/hw_irq.h>

extern int setup_irq(unsigned int irq, struct irqaction *new);

#ifdef CONFIG_GENERIC_HARDIRQS

#ifndef handle_dynamic_tick
# define handle_dynamic_tick(a)		do { } while (0)
#endif

#ifdef CONFIG_SMP
static inline void set_native_irq_info(int irq, cpumask_t mask)
{
	irq_desc[irq].affinity = mask;
}
#else
static inline void set_native_irq_info(int irq, cpumask_t mask)
{
}
#endif

#ifdef CONFIG_SMP

#if defined(CONFIG_GENERIC_PENDING_IRQ) || defined(CONFIG_IRQBALANCE)

void set_pending_irq(unsigned int irq, cpumask_t mask);
void move_native_irq(int irq);

#ifdef CONFIG_PCI_MSI
/*
 * Wonder why these are dummies?
 * For e.g the set_ioapic_affinity_vector() calls the set_ioapic_affinity_irq()
 * counter part after translating the vector to irq info. We need to perform
 * this operation on the real irq, when we dont use vector, i.e when
 * pci_use_vector() is false.
 */
static inline void move_irq(int irq)
{
}

static inline void set_irq_info(int irq, cpumask_t mask)
{
}

#else /* CONFIG_PCI_MSI */

static inline void move_irq(int irq)
{
	move_native_irq(irq);
}

static inline void set_irq_info(int irq, cpumask_t mask)
{
	set_native_irq_info(irq, mask);
}

#endif /* CONFIG_PCI_MSI */

#else /* CONFIG_GENERIC_PENDING_IRQ || CONFIG_IRQBALANCE */

static inline void move_irq(int irq)
{
}

static inline void move_native_irq(int irq)
{
}

static inline void set_pending_irq(unsigned int irq, cpumask_t mask)
{
}

static inline void set_irq_info(int irq, cpumask_t mask)
{
	set_native_irq_info(irq, mask);
}

#endif /* CONFIG_GENERIC_PENDING_IRQ */

#else /* CONFIG_SMP */

#define move_irq(x)
#define move_native_irq(x)

#endif /* CONFIG_SMP */

#ifdef CONFIG_IRQBALANCE
extern void set_balance_irq_affinity(unsigned int irq, cpumask_t mask);
#else
static inline void set_balance_irq_affinity(unsigned int irq, cpumask_t mask)
{
}
#endif

#ifdef CONFIG_AUTO_IRQ_AFFINITY
extern int select_smp_affinity(unsigned int irq);
#else
static inline int select_smp_affinity(unsigned int irq)
{
	return 1;
}
#endif

extern int no_irq_affinity;

/* Handle irq action chains: */
extern int handle_IRQ_event(unsigned int irq, struct pt_regs *regs,
			    struct irqaction *action);

/*
 * Built-in IRQ handlers for various IRQ types,
 * callable via desc->chip->handle_irq()
 */
extern void fastcall
handle_level_irq(unsigned int irq, struct irq_desc *desc, struct pt_regs *regs);
extern void fastcall
handle_fasteoi_irq(unsigned int irq, struct irq_desc *desc,
			 struct pt_regs *regs);
extern void fastcall
handle_edge_irq(unsigned int irq, struct irq_desc *desc, struct pt_regs *regs);
extern void fastcall
handle_simple_irq(unsigned int irq, struct irq_desc *desc,
		  struct pt_regs *regs);
extern void fastcall
handle_percpu_irq(unsigned int irq, struct irq_desc *desc,
		  struct pt_regs *regs);
extern void fastcall
handle_bad_irq(unsigned int irq, struct irq_desc *desc, struct pt_regs *regs);

/*
 * Get a descriptive string for the highlevel handler, for
 * /proc/interrupts output:
 */
extern const char *
handle_irq_name(void fastcall (*handle)(unsigned int, struct irq_desc *,
					struct pt_regs *));

/*
 * Monolithic do_IRQ implementation.
 * (is an explicit fastcall, because i386 4KSTACKS calls it from assembly)
 */
extern fastcall unsigned int __do_IRQ(unsigned int irq, struct pt_regs *regs);

/*
 * Architectures call this to let the generic IRQ layer
 * handle an interrupt. If the descriptor is attached to an
 * irqchip-style controller then we call the ->handle_irq() handler,
 * and it calls __do_IRQ() if it's attached to an irqtype-style controller.
 */
static inline void generic_handle_irq(unsigned int irq, struct pt_regs *regs)
{
	struct irq_desc *desc = irq_desc + irq;

	if (likely(desc->handle_irq))
		desc->handle_irq(irq, desc, regs);
	else
		__do_IRQ(irq, regs);
}

/* Handling of unhandled and spurious interrupts: */
extern void note_interrupt(unsigned int irq, struct irq_desc *desc,
			   int action_ret, struct pt_regs *regs);

/* Resending of interrupts :*/
void check_irq_resend(struct irq_desc *desc, unsigned int irq);

/* Initialize /proc/irq/ */
extern void init_irq_proc(void);

/* Enable/disable irq debugging output: */
extern int noirqdebug_setup(char *str);

/* Checks whether the interrupt can be requested by request_irq(): */
extern int can_request_irq(unsigned int irq, unsigned long irqflags);

/* Dummy irq-chip implementations: */
extern struct irq_chip no_irq_chip;
extern struct irq_chip dummy_irq_chip;

extern void
set_irq_chip_and_handler(unsigned int irq, struct irq_chip *chip,
			 void fastcall (*handle)(unsigned int,
						 struct irq_desc *,
						 struct pt_regs *));
extern void
__set_irq_handler(unsigned int irq,
		  void fastcall (*handle)(unsigned int, struct irq_desc *,
					  struct pt_regs *),
		  int is_chained);

/*
 * Set a highlevel flow handler for a given IRQ:
 */
static inline void
set_irq_handler(unsigned int irq,
		void fastcall (*handle)(unsigned int, struct irq_desc *,
					struct pt_regs *))
{
	__set_irq_handler(irq, handle, 0);
}

/*
 * Set a highlevel chained flow handler for a given IRQ.
 * (a chained handler is automatically enabled and set to
 *  IRQ_NOREQUEST and IRQ_NOPROBE)
 */
static inline void
set_irq_chained_handler(unsigned int irq,
			void fastcall (*handle)(unsigned int, struct irq_desc *,
						struct pt_regs *))
{
	__set_irq_handler(irq, handle, 1);
}

/* Set/get chip/data for an IRQ: */

extern int set_irq_chip(unsigned int irq, struct irq_chip *chip);
extern int set_irq_data(unsigned int irq, void *data);
extern int set_irq_chip_data(unsigned int irq, void *data);
extern int set_irq_type(unsigned int irq, unsigned int type);

#define get_irq_chip(irq)	(irq_desc[irq].chip)
#define get_irq_chip_data(irq)	(irq_desc[irq].chip_data)
#define get_irq_data(irq)	(irq_desc[irq].handler_data)

#endif /* CONFIG_GENERIC_HARDIRQS */

#endif /* !CONFIG_S390 */

#endif /* _LINUX_IRQ_H */
