/*
 * config_bfin.h
 *
 * Copyright (C) 2007 Marc Hoffman <marc.hoffman@analog.com>
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */
/*
   low level assembler interface wrapper

DEFUN(put_pixels_clamped,mL1,
        (DCTELEM *block, uint8_t *dest, int line_size)):

      body

      rts;
*/
#ifndef DEFUN

#ifndef mL1
#define mL1 .l1.text
#endif
#define mL3 .text

#define DEFUN(fname,where,interface) \
        .section where;              \
        .global _ff_bfin_ ## fname ; \
        .type _ff_bfin_ ## fname, STT_FUNC; \
        .align 8;                    \
        _ff_bfin_ ## fname

#define DEFUN_END(fname) \
        .size _ff_bfin_ ## fname, . - _ff_bfin_ ## fname


#endif

