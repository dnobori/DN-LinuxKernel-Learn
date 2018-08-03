#include "linux/generated/autoconf.h"
#undef IRQ_DISABLE
#undef IRQ_ENABLE
#undef IRQ_ENTER
#undef IRQ_EXIT

#define IRQ_DISABLE		SOFTIRQ_DISABLE
#define IRQ_ENABLE		SOFTIRQ_ENABLE
#define IRQ_ENTER		SOFTIRQ_ENTER
#define IRQ_EXIT		SOFTIRQ_EXIT
