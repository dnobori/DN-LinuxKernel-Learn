#include "linux/generated/autoconf.h"
#ifndef __iop_version_defs_asm_h
#define __iop_version_defs_asm_h

/*
 * This file is autogenerated from
 *   file:           ../../inst/io_proc/rtl/guinness/iop_version.r
 *     id:           iop_version.r,v 1.3 2004/04/22 12:37:54 jonaso Exp
 *     last modfied: Mon Apr 11 16:08:44 2005
 *
 *   by /n/asic/design/tools/rdesc/src/rdes2c -asm --outfile asm/iop_version_defs_asm.h ../../inst/io_proc/rtl/guinness/iop_version.r
 *      id: $Id: iop_version_defs_asm.h,v 1.5 2005/04/24 18:31:07 starvik Exp $
 * Any changes here will be lost.
 *
 * -*- buffer-read-only: t -*-
 */

#ifndef REG_FIELD
#define REG_FIELD( scope, reg, field, value ) \
  REG_FIELD_X_( value, reg_##scope##_##reg##___##field##___lsb )
#define REG_FIELD_X_( value, shift ) ((value) << shift)
#endif

#ifndef REG_STATE
#define REG_STATE( scope, reg, field, symbolic_value ) \
  REG_STATE_X_( regk_##scope##_##symbolic_value, reg_##scope##_##reg##___##field##___lsb )
#define REG_STATE_X_( k, shift ) (k << shift)
#endif

#ifndef REG_MASK
#define REG_MASK( scope, reg, field ) \
  REG_MASK_X_( reg_##scope##_##reg##___##field##___width, reg_##scope##_##reg##___##field##___lsb )
#define REG_MASK_X_( width, lsb ) (((1 << width)-1) << lsb)
#endif

#ifndef REG_LSB
#define REG_LSB( scope, reg, field ) reg_##scope##_##reg##___##field##___lsb
#endif

#ifndef REG_BIT
#define REG_BIT( scope, reg, field ) reg_##scope##_##reg##___##field##___bit
#endif

#ifndef REG_ADDR
#define REG_ADDR( scope, inst, reg ) REG_ADDR_X_(inst, reg_##scope##_##reg##_offset)
#define REG_ADDR_X_( inst, offs ) ((inst) + offs)
#endif

#ifndef REG_ADDR_VECT
#define REG_ADDR_VECT( scope, inst, reg, index ) \
         REG_ADDR_VECT_X_(inst, reg_##scope##_##reg##_offset, index, \
			 STRIDE_##scope##_##reg )
#define REG_ADDR_VECT_X_( inst, offs, index, stride ) \
                          ((inst) + offs + (index) * stride)
#endif

/* Register r_version, scope iop_version, type r */
#define reg_iop_version_r_version___nr___lsb 0
#define reg_iop_version_r_version___nr___width 8
#define reg_iop_version_r_version_offset 0


/* Constants */
#define regk_iop_version_v1_0                     0x00000001
#endif /* __iop_version_defs_asm_h */
