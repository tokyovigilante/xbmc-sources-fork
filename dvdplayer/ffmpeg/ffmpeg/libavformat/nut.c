/*
 * nut
 * Copyright (c) 2004-2007 Michael Niedermayer
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

#include "nut.h"
#include "tree.h"

unsigned long av_crc04C11DB7_update(unsigned long checksum, const uint8_t *buf, unsigned int len){
    return av_crc(av_crc04C11DB7, checksum, buf, len);
}

void ff_nut_reset_ts(NUTContext *nut, AVRational time_base, int64_t val){
    int i;
    for(i=0; i<nut->avf->nb_streams; i++){
        nut->stream[i].last_pts= av_rescale_rnd(
            val / nut->time_base_count,
            time_base.num * (int64_t)nut->stream[i].time_base->den,
            time_base.den * (int64_t)nut->stream[i].time_base->num,
            AV_ROUND_DOWN);
    }
}

int64_t ff_lsb2full(StreamContext *stream, int64_t lsb){
    int64_t mask = (1<<stream->msb_pts_shift)-1;
    int64_t delta= stream->last_pts - mask/2;
    return  ((lsb - delta)&mask) + delta;
}

int ff_nut_sp_pos_cmp(syncpoint_t *a, syncpoint_t *b){
    return (a->pos - b->pos>>32) - (b->pos - a->pos>>32);
}

int ff_nut_sp_pts_cmp(syncpoint_t *a, syncpoint_t *b){
    return (a->ts - b->ts>>32) - (b->ts - a->ts>>32);
}

void ff_nut_add_sp(NUTContext *nut, int64_t pos, int64_t back_ptr, int64_t ts){
    syncpoint_t *sp2, *sp= av_mallocz(sizeof(syncpoint_t));

    sp->pos= pos;
    sp->back_ptr= back_ptr;
    sp->ts= ts;
    sp2= av_tree_insert(&nut->syncpoints, sp, ff_nut_sp_pos_cmp);
    if(sp2 && sp2 != sp)
        av_free(sp);
}
