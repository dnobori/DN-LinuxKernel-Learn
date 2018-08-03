#include "linux/autoconf.h"
/*
 *  include/asm-s390/setup.h
 *
 *  S390 version
 *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation
 */

#ifndef _ASM_S390_SETUP_H
#define _ASM_S390_SETUP_H

#define PARMAREA		0x10400
#define COMMAND_LINE_SIZE 	896
#define RAMDISK_ORIGIN		0x800000
#define RAMDISK_SIZE		0x800000

#ifndef __ASSEMBLER__

#define IPL_DEVICE        (*(unsigned long *)  (0x10404))
#define INITRD_START      (*(unsigned long *)  (0x1040C))
#define INITRD_SIZE       (*(unsigned long *)  (0x10414))
#define COMMAND_LINE      ((char *)            (0x10480))

/*
 * Machine features detected in head.S
 */
extern unsigned long machine_flags;

#define MACHINE_IS_VM    (machine_flags & 1)
#define MACHINE_HAS_IEEE (machine_flags & 2)
#define MACHINE_IS_P390  (machine_flags & 4)
#define MACHINE_HAS_CSP  (machine_flags & 8)
#define MACHINE_HAS_MVPG (machine_flags & 16)

#else 

#define IPL_DEVICE        0x10404
#define INITRD_START      0x1040C
#define INITRD_SIZE       0x10414
#define COMMAND_LINE      0x10480

#endif

#endif
