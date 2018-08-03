#include "linux/generated/autoconf.h"
/* linux/arch/arm/mach-s5p6442/include/mach/gpio.h
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * S5P6442 - GPIO lib support
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef __ASM_ARCH_GPIO_H
#define __ASM_ARCH_GPIO_H __FILE__

#define gpio_get_value	__gpio_get_value
#define gpio_set_value	__gpio_set_value
#define gpio_cansleep	__gpio_cansleep
#define gpio_to_irq	__gpio_to_irq

/* GPIO bank sizes */
#define S5P6442_GPIO_A0_NR	(8)
#define S5P6442_GPIO_A1_NR	(2)
#define S5P6442_GPIO_B_NR	(4)
#define S5P6442_GPIO_C0_NR	(5)
#define S5P6442_GPIO_C1_NR	(5)
#define S5P6442_GPIO_D0_NR	(2)
#define S5P6442_GPIO_D1_NR	(6)
#define S5P6442_GPIO_E0_NR	(8)
#define S5P6442_GPIO_E1_NR	(5)
#define S5P6442_GPIO_F0_NR	(8)
#define S5P6442_GPIO_F1_NR	(8)
#define S5P6442_GPIO_F2_NR	(8)
#define S5P6442_GPIO_F3_NR	(6)
#define S5P6442_GPIO_G0_NR	(7)
#define S5P6442_GPIO_G1_NR	(7)
#define S5P6442_GPIO_G2_NR	(7)
#define S5P6442_GPIO_H0_NR	(8)
#define S5P6442_GPIO_H1_NR	(8)
#define S5P6442_GPIO_H2_NR	(8)
#define S5P6442_GPIO_H3_NR	(8)
#define S5P6442_GPIO_J0_NR	(8)
#define S5P6442_GPIO_J1_NR	(6)
#define S5P6442_GPIO_J2_NR	(8)
#define S5P6442_GPIO_J3_NR	(8)
#define S5P6442_GPIO_J4_NR	(5)

/* GPIO bank numbers */

/* CONFIG_S3C_GPIO_SPACE allows the user to select extra
 * space for debugging purposes so that any accidental
 * change from one gpio bank to another can be caught.
*/

#define S5P6442_GPIO_NEXT(__gpio) \
	((__gpio##_START) + (__gpio##_NR) + CONFIG_S3C_GPIO_SPACE + 1)

enum s5p_gpio_number {
	S5P6442_GPIO_A0_START	= 0,
	S5P6442_GPIO_A1_START	= S5P6442_GPIO_NEXT(S5P6442_GPIO_A0),
	S5P6442_GPIO_B_START	= S5P6442_GPIO_NEXT(S5P6442_GPIO_A1),
	S5P6442_GPIO_C0_START	= S5P6442_GPIO_NEXT(S5P6442_GPIO_B),
	S5P6442_GPIO_C1_START	= S5P6442_GPIO_NEXT(S5P6442_GPIO_C0),
	S5P6442_GPIO_D0_START	= S5P6442_GPIO_NEXT(S5P6442_GPIO_C1),
	S5P6442_GPIO_D1_START	= S5P6442_GPIO_NEXT(S5P6442_GPIO_D0),
	S5P6442_GPIO_E0_START	= S5P6442_GPIO_NEXT(S5P6442_GPIO_D1),
	S5P6442_GPIO_E1_START	= S5P6442_GPIO_NEXT(S5P6442_GPIO_E0),
	S5P6442_GPIO_F0_START	= S5P6442_GPIO_NEXT(S5P6442_GPIO_E1),
	S5P6442_GPIO_F1_START	= S5P6442_GPIO_NEXT(S5P6442_GPIO_F0),
	S5P6442_GPIO_F2_START	= S5P6442_GPIO_NEXT(S5P6442_GPIO_F1),
	S5P6442_GPIO_F3_START	= S5P6442_GPIO_NEXT(S5P6442_GPIO_F2),
	S5P6442_GPIO_G0_START	= S5P6442_GPIO_NEXT(S5P6442_GPIO_F3),
	S5P6442_GPIO_G1_START	= S5P6442_GPIO_NEXT(S5P6442_GPIO_G0),
	S5P6442_GPIO_G2_START	= S5P6442_GPIO_NEXT(S5P6442_GPIO_G1),
	S5P6442_GPIO_H0_START	= S5P6442_GPIO_NEXT(S5P6442_GPIO_G2),
	S5P6442_GPIO_H1_START	= S5P6442_GPIO_NEXT(S5P6442_GPIO_H0),
	S5P6442_GPIO_H2_START	= S5P6442_GPIO_NEXT(S5P6442_GPIO_H1),
	S5P6442_GPIO_H3_START	= S5P6442_GPIO_NEXT(S5P6442_GPIO_H2),
	S5P6442_GPIO_J0_START	= S5P6442_GPIO_NEXT(S5P6442_GPIO_H3),
	S5P6442_GPIO_J1_START	= S5P6442_GPIO_NEXT(S5P6442_GPIO_J0),
	S5P6442_GPIO_J2_START	= S5P6442_GPIO_NEXT(S5P6442_GPIO_J1),
	S5P6442_GPIO_J3_START	= S5P6442_GPIO_NEXT(S5P6442_GPIO_J2),
	S5P6442_GPIO_J4_START	= S5P6442_GPIO_NEXT(S5P6442_GPIO_J3),
};

/* S5P6442 GPIO number definitions. */
#define S5P6442_GPA0(_nr)	(S5P6442_GPIO_A0_START + (_nr))
#define S5P6442_GPA1(_nr)	(S5P6442_GPIO_A1_START + (_nr))
#define S5P6442_GPB(_nr)	(S5P6442_GPIO_B_START + (_nr))
#define S5P6442_GPC0(_nr)	(S5P6442_GPIO_C0_START + (_nr))
#define S5P6442_GPC1(_nr)	(S5P6442_GPIO_C1_START + (_nr))
#define S5P6442_GPD0(_nr)	(S5P6442_GPIO_D0_START + (_nr))
#define S5P6442_GPD1(_nr)	(S5P6442_GPIO_D1_START + (_nr))
#define S5P6442_GPE0(_nr)	(S5P6442_GPIO_E0_START + (_nr))
#define S5P6442_GPE1(_nr)	(S5P6442_GPIO_E1_START + (_nr))
#define S5P6442_GPF0(_nr)	(S5P6442_GPIO_F0_START + (_nr))
#define S5P6442_GPF1(_nr)	(S5P6442_GPIO_F1_START + (_nr))
#define S5P6442_GPF2(_nr)	(S5P6442_GPIO_F2_START + (_nr))
#define S5P6442_GPF3(_nr)	(S5P6442_GPIO_F3_START + (_nr))
#define S5P6442_GPG0(_nr)	(S5P6442_GPIO_G0_START + (_nr))
#define S5P6442_GPG1(_nr)	(S5P6442_GPIO_G1_START + (_nr))
#define S5P6442_GPG2(_nr)	(S5P6442_GPIO_G2_START + (_nr))
#define S5P6442_GPH0(_nr)	(S5P6442_GPIO_H0_START + (_nr))
#define S5P6442_GPH1(_nr)	(S5P6442_GPIO_H1_START + (_nr))
#define S5P6442_GPH2(_nr)	(S5P6442_GPIO_H2_START + (_nr))
#define S5P6442_GPH3(_nr)	(S5P6442_GPIO_H3_START + (_nr))
#define S5P6442_GPJ0(_nr)	(S5P6442_GPIO_J0_START + (_nr))
#define S5P6442_GPJ1(_nr)	(S5P6442_GPIO_J1_START + (_nr))
#define S5P6442_GPJ2(_nr)	(S5P6442_GPIO_J2_START + (_nr))
#define S5P6442_GPJ3(_nr)	(S5P6442_GPIO_J3_START + (_nr))
#define S5P6442_GPJ4(_nr)	(S5P6442_GPIO_J4_START + (_nr))

/* the end of the S5P6442 specific gpios */
#define S5P6442_GPIO_END	(S5P6442_GPJ4(S5P6442_GPIO_J4_NR) + 1)
#define S3C_GPIO_END		S5P6442_GPIO_END

/* define the number of gpios we need to the one after the GPJ4() range */
#define ARCH_NR_GPIOS		(S5P6442_GPJ4(S5P6442_GPIO_J4_NR) +	\
				 CONFIG_SAMSUNG_GPIO_EXTRA + 1)

#include <asm-generic/gpio.h>

#endif /* __ASM_ARCH_GPIO_H */
