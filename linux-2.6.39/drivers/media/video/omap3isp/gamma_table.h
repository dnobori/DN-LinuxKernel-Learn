#include "linux/generated/autoconf.h"
/*
 * gamma_table.h
 *
 * TI OMAP3 ISP - Default gamma table for all components
 *
 * Copyright (C) 2010 Nokia Corporation
 * Copyright (C) 2009 Texas Instruments, Inc.
 *
 * Contacts: Laurent Pinchart <laurent.pinchart@ideasonboard.com>
 *	     Sakari Ailus <sakari.ailus@iki.fi>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 */

  0,   0,   1,   2,   3,   3,   4,   5,   6,   8,  10,  12,  14,  16,  18,  20,
 22,  23,  25,  26,  28,  29,  31,  32,  34,  35,  36,  37,  39,  40,  41,  42,
 43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  52,  53,  54,  55,  56,  57,
 58,  59,  60,  61,  62,  63,  63,  64,  65,  66,  66,  67,  68,  69,  69,  70,
 71,  72,  72,  73,  74,  75,  75,  76,  77,  78,  78,  79,  80,  81,  81,  82,
 83,  84,  84,  85,  86,  87,  88,  88,  89,  90,  91,  91,  92,  93,  94,  94,
 95,  96,  97,  97,  98,  98,  99,  99, 100, 100, 101, 101, 102, 103, 104, 104,
105, 106, 107, 108, 108, 109, 110, 111, 111, 112, 113, 114, 114, 115, 116, 117,
117, 118, 119, 119, 120, 120, 121, 121, 122, 122, 123, 123, 124, 124, 125, 125,
126, 126, 127, 127, 128, 128, 129, 129, 130, 130, 131, 131, 132, 132, 133, 133,
134, 134, 135, 135, 136, 136, 137, 137, 138, 138, 139, 139, 140, 140, 141, 141,
142, 142, 143, 143, 144, 144, 145, 145, 146, 146, 147, 147, 148, 148, 149, 149,
150, 150, 151, 151, 152, 152, 153, 153, 153, 153, 154, 154, 154, 154, 155, 155,
156, 156, 157, 157, 158, 158, 158, 159, 159, 159, 160, 160, 160, 161, 161, 162,
162, 163, 163, 164, 164, 164, 164, 165, 165, 165, 165, 166, 166, 167, 167, 168,
168, 169, 169, 170, 170, 170, 170, 171, 171, 171, 171, 172, 172, 173, 173, 174,
174, 175, 175, 176, 176, 176, 176, 177, 177, 177, 177, 178, 178, 178, 178, 179,
179, 179, 179, 180, 180, 180, 180, 181, 181, 181, 181, 182, 182, 182, 182, 183,
183, 183, 183, 184, 184, 184, 184, 185, 185, 185, 185, 186, 186, 186, 186, 187,
187, 187, 187, 188, 188, 188, 188, 189, 189, 189, 189, 190, 190, 190, 190, 191,
191, 191, 191, 192, 192, 192, 192, 193, 193, 193, 193, 194, 194, 194, 194, 195,
195, 195, 195, 196, 196, 196, 196, 197, 197, 197, 197, 198, 198, 198, 198, 199,
199, 199, 199, 200, 200, 200, 200, 201, 201, 201, 201, 202, 202, 202, 203, 203,
203, 203, 204, 204, 204, 204, 205, 205, 205, 205, 206, 206, 206, 206, 207, 207,
207, 207, 208, 208, 208, 208, 209, 209, 209, 209, 210, 210, 210, 210, 210, 210,
210, 210, 210, 210, 210, 210, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211,
211, 212, 212, 212, 212, 213, 213, 213, 213, 213, 213, 213, 213, 213, 213, 213,
213, 214, 214, 214, 214, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215,
216, 216, 216, 216, 217, 217, 217, 217, 218, 218, 218, 218, 219, 219, 219, 219,
219, 219, 219, 219, 219, 219, 219, 219, 220, 220, 220, 220, 221, 221, 221, 221,
221, 221, 221, 221, 221, 221, 221, 222, 222, 222, 222, 223, 223, 223, 223, 223,
223, 223, 223, 223, 223, 223, 223, 224, 224, 224, 224, 225, 225, 225, 225, 225,
225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 226, 226,
226, 226, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 228, 228,
228, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 230, 230, 230,
230, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 232, 232, 232,
232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232,
233, 233, 233, 233, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 235,
235, 235, 235, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236,
236, 236, 236, 236, 236, 236, 237, 237, 237, 237, 238, 238, 238, 238, 238, 238,
238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238,
238, 238, 238, 238, 238, 239, 239, 239, 239, 240, 240, 240, 240, 240, 240, 240,
240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240,
240, 240, 240, 240, 241, 241, 241, 241, 242, 242, 242, 242, 242, 242, 242, 242,
242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242,
242, 242, 243, 243, 243, 243, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244,
244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244,
244, 245, 245, 245, 245, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246,
246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246,
246, 246, 246, 246, 246, 246, 246, 247, 247, 247, 247, 248, 248, 248, 248, 248,
248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248,
248, 248, 248, 248, 248, 248, 249, 249, 249, 249, 250, 250, 250, 250, 250, 250,
250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250,
250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250,
250, 250, 250, 250, 251, 251, 251, 251, 252, 252, 252, 252, 252, 252, 252, 252,
252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252,
252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252,
252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252,
252, 252, 252, 252, 252, 252, 252, 252, 253, 253, 253, 253, 253, 253, 253, 253,
253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253,
253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253,
253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253,
253, 254, 254, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
