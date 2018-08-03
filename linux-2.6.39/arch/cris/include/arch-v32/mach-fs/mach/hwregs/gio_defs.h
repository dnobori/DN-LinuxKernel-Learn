#include "linux/generated/autoconf.h"
#ifndef __gio_defs_h
#define __gio_defs_h

/*
 * This file is autogenerated from
 *   file:           ../../inst/gio/rtl/gio_regs.r
 *     id:           gio_regs.r,v 1.5 2005/02/04 09:43:21 perz Exp 
 *     last modfied: Mon Apr 11 16:07:47 2005
 * 
 *   by /n/asic/design/tools/rdesc/src/rdes2c --outfile gio_defs.h ../../inst/gio/rtl/gio_regs.r
 *      id: $Id: gio_defs.h,v 1.1 2007/02/13 11:55:30 starvik Exp $
 * Any changes here will be lost.
 *
 * -*- buffer-read-only: t -*-
 */
/* Main access macros */
#ifndef REG_RD
#define REG_RD( scope, inst, reg ) \
  REG_READ( reg_##scope##_##reg, \
            (inst) + REG_RD_ADDR_##scope##_##reg )
#endif

#ifndef REG_WR
#define REG_WR( scope, inst, reg, val ) \
  REG_WRITE( reg_##scope##_##reg, \
             (inst) + REG_WR_ADDR_##scope##_##reg, (val) )
#endif

#ifndef REG_RD_VECT
#define REG_RD_VECT( scope, inst, reg, index ) \
  REG_READ( reg_##scope##_##reg, \
            (inst) + REG_RD_ADDR_##scope##_##reg + \
	    (index) * STRIDE_##scope##_##reg )
#endif

#ifndef REG_WR_VECT
#define REG_WR_VECT( scope, inst, reg, index, val ) \
  REG_WRITE( reg_##scope##_##reg, \
             (inst) + REG_WR_ADDR_##scope##_##reg + \
	     (index) * STRIDE_##scope##_##reg, (val) )
#endif

#ifndef REG_RD_INT
#define REG_RD_INT( scope, inst, reg ) \
  REG_READ( int, (inst) + REG_RD_ADDR_##scope##_##reg )
#endif

#ifndef REG_WR_INT
#define REG_WR_INT( scope, inst, reg, val ) \
  REG_WRITE( int, (inst) + REG_WR_ADDR_##scope##_##reg, (val) )
#endif

#ifndef REG_RD_INT_VECT
#define REG_RD_INT_VECT( scope, inst, reg, index ) \
  REG_READ( int, (inst) + REG_RD_ADDR_##scope##_##reg + \
	    (index) * STRIDE_##scope##_##reg )
#endif

#ifndef REG_WR_INT_VECT
#define REG_WR_INT_VECT( scope, inst, reg, index, val ) \
  REG_WRITE( int, (inst) + REG_WR_ADDR_##scope##_##reg + \
	     (index) * STRIDE_##scope##_##reg, (val) )
#endif

#ifndef REG_TYPE_CONV
#define REG_TYPE_CONV( type, orgtype, val ) \
  ( { union { orgtype o; type n; } r; r.o = val; r.n; } )
#endif

#ifndef reg_page_size
#define reg_page_size 8192
#endif

#ifndef REG_ADDR
#define REG_ADDR( scope, inst, reg ) \
  ( (inst) + REG_RD_ADDR_##scope##_##reg )
#endif

#ifndef REG_ADDR_VECT
#define REG_ADDR_VECT( scope, inst, reg, index ) \
  ( (inst) + REG_RD_ADDR_##scope##_##reg + \
    (index) * STRIDE_##scope##_##reg )
#endif

/* C-code for register scope gio */

/* Register rw_pa_dout, scope gio, type rw */
typedef struct {
  unsigned int data : 8;
  unsigned int dummy1 : 24;
} reg_gio_rw_pa_dout;
#define REG_RD_ADDR_gio_rw_pa_dout 0
#define REG_WR_ADDR_gio_rw_pa_dout 0

/* Register r_pa_din, scope gio, type r */
typedef struct {
  unsigned int data : 8;
  unsigned int dummy1 : 24;
} reg_gio_r_pa_din;
#define REG_RD_ADDR_gio_r_pa_din 4

/* Register rw_pa_oe, scope gio, type rw */
typedef struct {
  unsigned int oe : 8;
  unsigned int dummy1 : 24;
} reg_gio_rw_pa_oe;
#define REG_RD_ADDR_gio_rw_pa_oe 8
#define REG_WR_ADDR_gio_rw_pa_oe 8

/* Register rw_intr_cfg, scope gio, type rw */
typedef struct {
  unsigned int pa0 : 3;
  unsigned int pa1 : 3;
  unsigned int pa2 : 3;
  unsigned int pa3 : 3;
  unsigned int pa4 : 3;
  unsigned int pa5 : 3;
  unsigned int pa6 : 3;
  unsigned int pa7 : 3;
  unsigned int dummy1 : 8;
} reg_gio_rw_intr_cfg;
#define REG_RD_ADDR_gio_rw_intr_cfg 12
#define REG_WR_ADDR_gio_rw_intr_cfg 12

/* Register rw_intr_mask, scope gio, type rw */
typedef struct {
  unsigned int pa0 : 1;
  unsigned int pa1 : 1;
  unsigned int pa2 : 1;
  unsigned int pa3 : 1;
  unsigned int pa4 : 1;
  unsigned int pa5 : 1;
  unsigned int pa6 : 1;
  unsigned int pa7 : 1;
  unsigned int dummy1 : 24;
} reg_gio_rw_intr_mask;
#define REG_RD_ADDR_gio_rw_intr_mask 16
#define REG_WR_ADDR_gio_rw_intr_mask 16

/* Register rw_ack_intr, scope gio, type rw */
typedef struct {
  unsigned int pa0 : 1;
  unsigned int pa1 : 1;
  unsigned int pa2 : 1;
  unsigned int pa3 : 1;
  unsigned int pa4 : 1;
  unsigned int pa5 : 1;
  unsigned int pa6 : 1;
  unsigned int pa7 : 1;
  unsigned int dummy1 : 24;
} reg_gio_rw_ack_intr;
#define REG_RD_ADDR_gio_rw_ack_intr 20
#define REG_WR_ADDR_gio_rw_ack_intr 20

/* Register r_intr, scope gio, type r */
typedef struct {
  unsigned int pa0 : 1;
  unsigned int pa1 : 1;
  unsigned int pa2 : 1;
  unsigned int pa3 : 1;
  unsigned int pa4 : 1;
  unsigned int pa5 : 1;
  unsigned int pa6 : 1;
  unsigned int pa7 : 1;
  unsigned int dummy1 : 24;
} reg_gio_r_intr;
#define REG_RD_ADDR_gio_r_intr 24

/* Register r_masked_intr, scope gio, type r */
typedef struct {
  unsigned int pa0 : 1;
  unsigned int pa1 : 1;
  unsigned int pa2 : 1;
  unsigned int pa3 : 1;
  unsigned int pa4 : 1;
  unsigned int pa5 : 1;
  unsigned int pa6 : 1;
  unsigned int pa7 : 1;
  unsigned int dummy1 : 24;
} reg_gio_r_masked_intr;
#define REG_RD_ADDR_gio_r_masked_intr 28

/* Register rw_pb_dout, scope gio, type rw */
typedef struct {
  unsigned int data : 18;
  unsigned int dummy1 : 14;
} reg_gio_rw_pb_dout;
#define REG_RD_ADDR_gio_rw_pb_dout 32
#define REG_WR_ADDR_gio_rw_pb_dout 32

/* Register r_pb_din, scope gio, type r */
typedef struct {
  unsigned int data : 18;
  unsigned int dummy1 : 14;
} reg_gio_r_pb_din;
#define REG_RD_ADDR_gio_r_pb_din 36

/* Register rw_pb_oe, scope gio, type rw */
typedef struct {
  unsigned int oe : 18;
  unsigned int dummy1 : 14;
} reg_gio_rw_pb_oe;
#define REG_RD_ADDR_gio_rw_pb_oe 40
#define REG_WR_ADDR_gio_rw_pb_oe 40

/* Register rw_pc_dout, scope gio, type rw */
typedef struct {
  unsigned int data : 18;
  unsigned int dummy1 : 14;
} reg_gio_rw_pc_dout;
#define REG_RD_ADDR_gio_rw_pc_dout 48
#define REG_WR_ADDR_gio_rw_pc_dout 48

/* Register r_pc_din, scope gio, type r */
typedef struct {
  unsigned int data : 18;
  unsigned int dummy1 : 14;
} reg_gio_r_pc_din;
#define REG_RD_ADDR_gio_r_pc_din 52

/* Register rw_pc_oe, scope gio, type rw */
typedef struct {
  unsigned int oe : 18;
  unsigned int dummy1 : 14;
} reg_gio_rw_pc_oe;
#define REG_RD_ADDR_gio_rw_pc_oe 56
#define REG_WR_ADDR_gio_rw_pc_oe 56

/* Register rw_pd_dout, scope gio, type rw */
typedef struct {
  unsigned int data : 18;
  unsigned int dummy1 : 14;
} reg_gio_rw_pd_dout;
#define REG_RD_ADDR_gio_rw_pd_dout 64
#define REG_WR_ADDR_gio_rw_pd_dout 64

/* Register r_pd_din, scope gio, type r */
typedef struct {
  unsigned int data : 18;
  unsigned int dummy1 : 14;
} reg_gio_r_pd_din;
#define REG_RD_ADDR_gio_r_pd_din 68

/* Register rw_pd_oe, scope gio, type rw */
typedef struct {
  unsigned int oe : 18;
  unsigned int dummy1 : 14;
} reg_gio_rw_pd_oe;
#define REG_RD_ADDR_gio_rw_pd_oe 72
#define REG_WR_ADDR_gio_rw_pd_oe 72

/* Register rw_pe_dout, scope gio, type rw */
typedef struct {
  unsigned int data : 18;
  unsigned int dummy1 : 14;
} reg_gio_rw_pe_dout;
#define REG_RD_ADDR_gio_rw_pe_dout 80
#define REG_WR_ADDR_gio_rw_pe_dout 80

/* Register r_pe_din, scope gio, type r */
typedef struct {
  unsigned int data : 18;
  unsigned int dummy1 : 14;
} reg_gio_r_pe_din;
#define REG_RD_ADDR_gio_r_pe_din 84

/* Register rw_pe_oe, scope gio, type rw */
typedef struct {
  unsigned int oe : 18;
  unsigned int dummy1 : 14;
} reg_gio_rw_pe_oe;
#define REG_RD_ADDR_gio_rw_pe_oe 88
#define REG_WR_ADDR_gio_rw_pe_oe 88


/* Constants */
enum {
  regk_gio_anyedge                         = 0x00000007,
  regk_gio_hi                              = 0x00000001,
  regk_gio_lo                              = 0x00000002,
  regk_gio_negedge                         = 0x00000006,
  regk_gio_no                              = 0x00000000,
  regk_gio_off                             = 0x00000000,
  regk_gio_posedge                         = 0x00000005,
  regk_gio_rw_intr_cfg_default             = 0x00000000,
  regk_gio_rw_intr_mask_default            = 0x00000000,
  regk_gio_rw_pa_oe_default                = 0x00000000,
  regk_gio_rw_pb_oe_default                = 0x00000000,
  regk_gio_rw_pc_oe_default                = 0x00000000,
  regk_gio_rw_pd_oe_default                = 0x00000000,
  regk_gio_rw_pe_oe_default                = 0x00000000,
  regk_gio_set                             = 0x00000003,
  regk_gio_yes                             = 0x00000001
};
#endif /* __gio_defs_h */
