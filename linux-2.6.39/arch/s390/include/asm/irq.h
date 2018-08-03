#include "linux/generated/autoconf.h"
#ifndef _ASM_IRQ_H
#define _ASM_IRQ_H

#include <linux/hardirq.h>

enum interruption_class {
	EXTERNAL_INTERRUPT,
	IO_INTERRUPT,
	EXTINT_CLK,
	EXTINT_IPI,
	EXTINT_TMR,
	EXTINT_TLA,
	EXTINT_PFL,
	EXTINT_DSD,
	EXTINT_VRT,
	EXTINT_SCP,
	EXTINT_IUC,
	IOINT_QAI,
	IOINT_QDI,
	IOINT_DAS,
	IOINT_C15,
	IOINT_C70,
	IOINT_TAP,
	IOINT_VMR,
	IOINT_LCS,
	IOINT_CLW,
	IOINT_CTC,
	IOINT_APB,
	NMI_NMI,
	NR_IRQS,
};

#endif /* _ASM_IRQ_H */
