#include "linux/autoconf.h"
/*
 * Carsten Langgaard, carstenl@mips.com
 * Copyright (C) 1999,2000 MIPS Technologies, Inc.  All rights reserved.
 *
 * ########################################################################
 *
 *  This program is free software; you can distribute it and/or modify it
 *  under the terms of the GNU General Public License (Version 2) as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.
 *
 * ########################################################################
 *
 * Reset the MIPS boards.
 *
 */
#include <linux/config.h>

#include <asm/reboot.h>
#include <asm/mips-boards/generic.h>
#if defined(CONFIG_MIPS_ATLAS)
#include <asm/mips-boards/atlas.h>
#endif

static void mips_machine_restart(char *command);
static void mips_machine_halt(void);
#if defined(CONFIG_MIPS_ATLAS)
static void atlas_machine_power_off(void);
#endif

static void mips_machine_restart(char *command)
{
        volatile unsigned int *softres_reg = (void *)SOFTRES_REG;

	*softres_reg = GORESET;
}

static void mips_machine_halt(void)
{
        volatile unsigned int *softres_reg = (void *)SOFTRES_REG;

	*softres_reg = GORESET;
}

#if defined(CONFIG_MIPS_ATLAS)
static void atlas_machine_power_off(void)
{
        volatile unsigned int *psustby_reg = (void *)ATLAS_PSUSTBY_REG;

	*psustby_reg = ATLAS_GOSTBY;
}
#endif

void mips_reboot_setup(void)
{
	_machine_restart = mips_machine_restart;
	_machine_halt = mips_machine_halt;
#if defined(CONFIG_MIPS_ATLAS)
	_machine_power_off = atlas_machine_power_off;
#endif
#if defined(CONFIG_MIPS_MALTA)
	_machine_power_off = mips_machine_halt;
#endif
}
