/* * 
 * This file is part of libnemesi
 *
 * Copyright (C) 2007 by LScube team <team@streaming.polito.it>
 * See AUTHORS for more details
 * 
 * libnemesi is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * libnemesi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with libnemesi; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *  
 * */

#include <stdlib.h>
#include <string.h>

#include "cc.h"
#include "utils.h"

// inspired by id3lib
#define MASK(bits) ((1 << (bits)) - 1)

#define ID3v2_MAJOR 0x03    // for now we use 3 for compliance with other software
#define ID3v2_REV 0x00

#define ID3v2_HDRLEN 10        // basic header lenght for id3 tag
#define ID3v2_FRAMEHDRLEN 11    // 10 for header + 1 for text encoding (redundant)

#define CC_URILIC "This work is licenced under the "
#define CC_URIMETA " verify at "

#define FRAME_ID { \
            "TIT2", \
            "TPE1", \
            "TCOP", \
         }
/*
            "COMM", \
            "TALB", \
            "TCOM", \
            "TENC", \
            "TOPE", \
            "TRAK", \
            "TYER", \
            "WXXX"  \
         }
*/

struct id3frm {
    uint8_t id[4];
    // uint32_t size;
    // uint8_t size[sizeof(uint32)];
    uint8_t size[4];
    uint16_t flags;
    uint8_t charenc;
    uint8_t data[1];
};

struct id3tag {
    uint8_t id[3];
    uint8_t major;
    uint8_t rev;
    uint8_t flags;
    // uint8_t size[sizeof(uint32)];
    uint8_t size[4];
    // not using extended header
    struct id3frm frames[1];    // the tag MUST contain at least one frame
};

static uint8_t enc_synchsafe_int(uint8_t * enc_chr, uint32_t num)
{
    uint32_t encoded = 0;
    // uint8_t *enc_chr=(uint8_t *)(&encoded);
    const unsigned char bitsused = 7;
    const uint32_t maxval = MASK(bitsused * sizeof(uint32_t));
    int i;

    num = min(num, maxval);

    for (i = sizeof(uint32_t) - 1; i >= 0; i--) {
        enc_chr[i] = (uint8_t) (num & MASK(bitsused));
        num >>= bitsused;
    }

    return encoded;
}

int cc_id3v2(cc_license * license, cc_tag * tag)
{
    uint32_t id3len = 0;
    struct id3tag *id3;
    struct id3frm *frame;
    // frama lens
    int tit2 = 0, tpe1 = 0, tcop = 0;
    uint8_t *pos;

    // id3 length computation
    // first we calculate len of each tag

    if (license->title) {
        // there's the creator info => put TIT2 frame
        tit2 = strlen(license->title) + 1;    // '\0' added
        id3len += ID3v2_FRAMEHDRLEN + tit2;
    }
    if (license->creator) {
        // there's the title info => put TPE1 frame
        tpe1 = strlen(license->creator) + 1;    // '\0' added
        id3len += ID3v2_FRAMEHDRLEN + tpe1;
    }
    if ((license->uriLicense) || (license->uriMetadata)) {
        // there's CC info => put TCOP frame
        if (license->uriLicense)
            tcop += strlen(CC_URILIC) + strlen(license->uriLicense) + 1;    // '\0' added
        if (license->uriMetadata)
            tcop += strlen(CC_URIMETA) + strlen(license->uriMetadata) + 1;    // '\0' added
        id3len += ID3v2_FRAMEHDRLEN + tcop;
    }

    if (!id3len)        // no frame to put in => error
        return 1;

    // add id3 header len to total dimension of buffer
    id3len += ID3v2_HDRLEN;

    // alloc buffer for tag
    if (!(id3 = malloc(id3len)))
        return 1;

    // ID3v2 header creation
    // string "ID3"
    strncpy((char *) id3->id, "ID3", 3);
    // ID3v2 version
    id3->major = ID3v2_MAJOR;
    id3->rev = ID3v2_REV;
    // flags
    id3->flags = 0x00;
    // synchsafe integer for size
    enc_synchsafe_int(id3->size, id3len - ID3v2_HDRLEN);

    frame = id3->frames;

    // put frames
    if (license->title) {
        // there's the creator info => put TIT2 frame
        strncpy((char *) frame->id, "TIT2", 4);
        /*frame->size = */ enc_synchsafe_int(frame->size, tit2 + 1);
        // char enc byte added
        frame->flags = 0;
        frame->charenc = 0;    // ISO-8858-1
        strcpy((char *) frame->data, license->title);
        frame = (struct id3frm *) (frame->data + tit2);
    }
    if (license->creator) {
        // there's the title info => put TPE1 frame
        strncpy((char *) frame->id, "TPE1", 4);
        /*frame->size = */ enc_synchsafe_int(frame->size, tpe1 + 1);
        // char enc byte added
        frame->flags = 0;
        frame->charenc = 0;    // ISO-8858-1
        strcpy((char *) frame->data, license->creator);
        frame = (struct id3frm *) (frame->data + tpe1);
    }
    if ((license->uriLicense) || (license->uriMetadata)) {
        // there's CC info => put TCOP frame
        strncpy((char *) frame->id, "TCOP", 4);
        /*frame->size = */ enc_synchsafe_int(frame->size, tcop + 1);
        // char enc byte added
        frame->flags = 0;
        frame->charenc = 0;    // ISO-8858-1
        pos = frame->data;
        if (license->uriLicense) {
            sprintf((char *) pos, "%s%s", CC_URILIC,
                license->uriLicense);
            pos += strlen((char *) pos);
        }
        if (license->uriMetadata) {
            sprintf((char *) pos, "%s%s", CC_URIMETA,
                license->uriMetadata);
        }
        frame = (struct id3frm *) (frame->data + tcop);
    }

    tag->header = (int8_t *) id3;
    tag->hdim = id3len;

    return 0;
}
