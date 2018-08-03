#include "linux/generated/autoconf.h"
/*
 * stmp37xx: LCDIF register definitions
 *
 * Copyright (c) 2008 Freescale Semiconductor
 * Copyright 2008 Embedded Alley Solutions, Inc All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */
#define REGS_LCDIF_BASE	(STMP3XXX_REGS_BASE + 0x30000)
#define REGS_LCDIF_PHYS	0x80030000
#define REGS_LCDIF_SIZE	0x2000

#define HW_LCDIF_CTRL		0x0
#define BM_LCDIF_CTRL_COUNT	0x0000FFFF
#define BP_LCDIF_CTRL_COUNT	0
#define BM_LCDIF_CTRL_RUN	0x00010000
#define BM_LCDIF_CTRL_WORD_LENGTH	0x00020000
#define BM_LCDIF_CTRL_DATA_SELECT	0x00040000
#define BM_LCDIF_CTRL_DOTCLK_MODE	0x00080000
#define BM_LCDIF_CTRL_VSYNC_MODE	0x00100000
#define BM_LCDIF_CTRL_DATA_SWIZZLE	0x00600000
#define BP_LCDIF_CTRL_DATA_SWIZZLE	21
#define BM_LCDIF_CTRL_BYPASS_COUNT	0x00800000
#define BM_LCDIF_CTRL_SHIFT_NUM_BITS	0x06000000
#define BP_LCDIF_CTRL_SHIFT_NUM_BITS	25
#define BM_LCDIF_CTRL_DATA_SHIFT_DIR	0x08000000
#define BM_LCDIF_CTRL_WAIT_FOR_VSYNC_EDGE	0x10000000
#define BM_LCDIF_CTRL_CLKGATE	0x40000000
#define BM_LCDIF_CTRL_SFTRST	0x80000000

#define HW_LCDIF_CTRL1		0x10
#define BM_LCDIF_CTRL1_RESET	0x00000001
#define BP_LCDIF_CTRL1_RESET	0
#define BM_LCDIF_CTRL1_MODE86	0x00000002
#define BM_LCDIF_CTRL1_BUSY_ENABLE	0x00000004
#define BM_LCDIF_CTRL1_VSYNC_EDGE_IRQ	0x00000100
#define BM_LCDIF_CTRL1_CUR_FRAME_DONE_IRQ	0x00000200
#define BM_LCDIF_CTRL1_UNDERFLOW_IRQ	0x00000400
#define BM_LCDIF_CTRL1_OVERFLOW_IRQ	0x00000800
#define BM_LCDIF_CTRL1_VSYNC_EDGE_IRQ_EN	0x00001000
#define BM_LCDIF_CTRL1_BYTE_PACKING_FORMAT	0x000F0000
#define BP_LCDIF_CTRL1_BYTE_PACKING_FORMAT	16

#define HW_LCDIF_TIMING		0x20

#define HW_LCDIF_VDCTRL0	0x30
#define BM_LCDIF_VDCTRL0_VALID_DATA_CNT	0x000003FF
#define BP_LCDIF_VDCTRL0_VALID_DATA_CNT	0
#define BM_LCDIF_VDCTRL0_VSYNC_PULSE_WIDTH_UNIT	0x00100000
#define BM_LCDIF_VDCTRL0_VSYNC_PERIOD_UNIT	0x00200000
#define BM_LCDIF_VDCTRL0_ENABLE_POL	0x01000000
#define BM_LCDIF_VDCTRL0_DOTCLK_POL	0x02000000
#define BM_LCDIF_VDCTRL0_HSYNC_POL	0x04000000
#define BM_LCDIF_VDCTRL0_VSYNC_POL	0x08000000
#define BM_LCDIF_VDCTRL0_ENABLE_PRESENT	0x10000000
#define BM_LCDIF_VDCTRL0_VSYNC_OEB	0x20000000

#define HW_LCDIF_VDCTRL1	0x40
#define BM_LCDIF_VDCTRL1_VSYNC_PERIOD	0x000FFFFF
#define BP_LCDIF_VDCTRL1_VSYNC_PERIOD	0
#define BM_LCDIF_VDCTRL1_VSYNC_PULSE_WIDTH	0xFFF00000
#define BP_LCDIF_VDCTRL1_VSYNC_PULSE_WIDTH	20

#define HW_LCDIF_VDCTRL2	0x50
#define BM_LCDIF_VDCTRL2_VALID_DATA_CNT	0x000007FF
#define BP_LCDIF_VDCTRL2_VALID_DATA_CNT	0
#define BM_LCDIF_VDCTRL2_HSYNC_PERIOD	0x007FF800
#define BP_LCDIF_VDCTRL2_HSYNC_PERIOD	11
#define BM_LCDIF_VDCTRL2_HSYNC_PULSE_WIDTH	0xFF800000
#define BP_LCDIF_VDCTRL2_HSYNC_PULSE_WIDTH	23

#define HW_LCDIF_VDCTRL3	0x60
#define BM_LCDIF_VDCTRL3_VERTICAL_WAIT_CNT	0x000001FF
#define BP_LCDIF_VDCTRL3_VERTICAL_WAIT_CNT	0
#define BM_LCDIF_VDCTRL3_HORIZONTAL_WAIT_CNT	0x00FFF000
#define BP_LCDIF_VDCTRL3_HORIZONTAL_WAIT_CNT	12
#define BM_LCDIF_VDCTRL3_SYNC_SIGNALS_ON	0x01000000
