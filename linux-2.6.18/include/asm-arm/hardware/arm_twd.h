#include "linux/autoconf.h"
#ifndef __ASM_HARDWARE_TWD_H
#define __ASM_HARDWARE_TWD_H

#define TWD_TIMER_LOAD 		0x00
#define TWD_TIMER_COUNTER		0x04
#define TWD_TIMER_CONTROL		0x08
#define TWD_TIMER_INTSTAT		0x0C

#define TWD_WDOG_LOAD			0x20
#define TWD_WDOG_COUNTER		0x24
#define TWD_WDOG_CONTROL		0x28
#define TWD_WDOG_INTSTAT		0x2C
#define TWD_WDOG_RESETSTAT		0x30
#define TWD_WDOG_DISABLE		0x34

#endif
