#include "linux/generated/autoconf.h"
#undef IRQ_DISABLE
#undef IRQ_ENABLE
#undef IRQ_ENTER
#undef IRQ_EXIT

#define IRQ_ENABLE		HARDIRQ_ENABLE
#define IRQ_DISABLE		HARDIRQ_DISABLE
#define IRQ_ENTER		HARDIRQ_ENTER
#define IRQ_EXIT		HARDIRQ_EXIT
