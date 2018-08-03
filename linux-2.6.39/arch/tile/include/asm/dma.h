#include "linux/generated/autoconf.h"
/*
 * Copyright 2010 Tilera Corporation. All Rights Reserved.
 *
 *   This program is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU General Public License
 *   as published by the Free Software Foundation, version 2.
 *
 *   This program is distributed in the hope that it will be useful, but
 *   WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 *   NON INFRINGEMENT.  See the GNU General Public License for
 *   more details.
 */

#ifndef _ASM_TILE_DMA_H
#define _ASM_TILE_DMA_H

#include <asm-generic/dma.h>

/* Needed by drivers/pci/quirks.c */
#ifdef CONFIG_PCI
extern int isa_dma_bridge_buggy;
#endif

#endif /* _ASM_TILE_DMA_H */
