#include "linux/autoconf.h"
/*
 * BK Id: SCCS/s.ppc8xx_pic.h 1.7 05/17/01 18:14:21 cort
 */
#ifndef _PPC_KERNEL_PPC8xx_H
#define _PPC_KERNEL_PPC8xx_H

#include <linux/config.h>
#include "local_irq.h"

extern struct hw_interrupt_type ppc8xx_pic;

void m8xx_pic_init(void);
void m8xx_do_IRQ(struct pt_regs *regs,
                 int            cpu);
int m8xx_get_irq(struct pt_regs *regs);

#ifdef CONFIG_MBX
#include "i8259.h"
#include <asm/io.h>
void mbx_i8259_action(int cpl, void *dev_id, struct pt_regs *regs);
#endif

#endif /* _PPC_KERNEL_PPC8xx_H */
