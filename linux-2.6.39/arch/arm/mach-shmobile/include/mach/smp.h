#include "linux/generated/autoconf.h"
#ifndef __MACH_SMP_H
#define __MACH_SMP_H

#include <asm/hardware/gic.h>

/*
 * We use IRQ1 as the IPI
 */
static inline void smp_cross_call(const struct cpumask *mask, int ipi)
{
#if defined(CONFIG_ARM_GIC)
	gic_raise_softirq(mask, ipi);
#endif
}

#endif
