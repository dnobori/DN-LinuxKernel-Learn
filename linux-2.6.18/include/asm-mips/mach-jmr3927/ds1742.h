#include "linux/autoconf.h"
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2003, 06 by Ralf Baechle
 */
#ifndef __ASM_MACH_JMR3927_DS1742_H
#define __ASM_MACH_JMR3927_DS1742_H

#include <asm/jmr3927/jmr3927.h>

#define rtc_read(reg)		(jmr3927_nvram_in(reg))
#define rtc_write(data, reg)	(jmr3927_nvram_out((data),(reg)))

#endif /* __ASM_MACH_JMR3927_DS1742_H */
