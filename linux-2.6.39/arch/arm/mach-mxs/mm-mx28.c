#include "linux/generated/autoconf.h"
/*
 * Copyright 2008-2010 Freescale Semiconductor, Inc. All Rights Reserved.
 *
 * The code contained herein is licensed under the GNU General Public
 * License.  You may obtain a copy of the GNU General Public License
 * Version 2 or later at the following locations:
 *
 * http://www.opensource.org/licenses/gpl-license.html
 * http://www.gnu.org/copyleft/gpl.html
 *
 * Create static mapping between physical to virtual memory.
 */

#include <linux/mm.h>
#include <linux/init.h>

#include <asm/mach/map.h>

#include <mach/mx28.h>
#include <mach/common.h>
#include <mach/iomux.h>

/*
 * Define the MX28 memory map.
 */
static struct map_desc mx28_io_desc[] __initdata = {
	mxs_map_entry(MX28, OCRAM, MT_DEVICE),
	mxs_map_entry(MX28, IO, MT_DEVICE),
};

/*
 * This function initializes the memory map. It is called during the
 * system startup to create static physical to virtual memory mappings
 * for the IO modules.
 */
void __init mx28_map_io(void)
{
	iotable_init(mx28_io_desc, ARRAY_SIZE(mx28_io_desc));
}

void __init mx28_init_irq(void)
{
	icoll_init_irq();
	mx28_register_gpios();
}
