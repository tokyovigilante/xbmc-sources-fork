/*
 * NuppelVideo demuxer.
 * Copyright (c) 2006 Reimar Doeffinger.
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
#include "avformat.h"
#include "riff.h"

typedef struct {
    int v_id;
    int a_id;
    int rtjpg_video;
} NUVContext;

typedef enum {
    NUV_VIDEO = 'V',
    NUV_EXTRADATA = 'D',
    NUV_AUDIO = 'A',
    NUV_SEEKP = 'R',
    NUV_MYTHEXT = 'X'
} frametype_t;

static int nuv_probe(AVProbeData *p) {
    if (!memcmp(p->buf, "NuppelVideo", 12))
        return AVPROBE_SCORE_MAX;
    if (!memcmp(p->buf, "MythTVVideo", 12))
        return AVPROBE_SCORE_MAX;
    return 0;
}

//! little macro to sanitize packet size
#define PKTSIZE(s) (s &  0xffffff)

/**
 * \brief read until we found all data needed for decoding
 * \param vst video stream of which to change parameters
 * \param ast video stream of which to change parameters
 * \param myth set if this is a MythTVVideo format file
 * \return 1 if all required codec data was found
 */
static int get_codec_data(ByteIOContext *pb, AVStream *vst,
                          AVStream *ast, int myth) {
    frametype_t frametype;
    if (!vst && !myth)
        return 1; // no codec data needed
    while (!url_feof(pb)) {
        int size, subtype;
        frametype = get_byte(pb);
        switch (frametype) {
            case NUV_EXTRADATA:
                subtype = get_byte(pb);
                url_fskip(pb, 6);
                size = PKTSIZE(get_le32(pb));
                if (vst && subtype == 'R') {
                    vst->codec->extradata_size = size;
                    vst->codec->extradata = av_malloc(size);
                    get_buffer(pb, vst->codec->extradata, size);
                    size = 0;
                    if (!myth)
                        return 1;
                }
                break;
            case NUV_MYTHEXT:
                url_fskip(pb, 7);
                size = PKTSIZE(get_le32(pb));
                if (size != 128 * 4)
                    break;
                get_le32(pb); // version
                if (vst) {
                    vst->codec->codec_tag = get_le32(pb);
                    vst->codec->codec_id =
                        codec_get_id(codec_bmp_tags, vst->codec->codec_tag);
                    if (vst->codec->codec_tag == MKTAG('R', 'J', 'P', 'G'))
                        vst->codec->codec_id = CODEC_ID_NUV;
                } else
                    url_fskip(pb, 4);

                if (ast) {
                    ast->codec->codec_tag = get_le32(pb);
                    ast->codec->sample_rate = get_le32(pb);
                    ast->codec->bits_per_sample = get_le32(pb);
                    ast->codec->channels = get_le32(pb);
                    ast->codec->codec_id =
                        wav_codec_get_id(ast->codec->codec_tag,
                                         ast->codec->bits_per_sample);
                    ast->need_parsing = AVSTREAM_PARSE_FULL;
                } else
                    url_fskip(pb, 4 * 4);

                size -= 6 * 4;
                url_fskip(pb, size);
                return 1;
            case NUV_SEEKP:
                size = 11;
                break;
            default:
                url_fskip(pb, 7);
                size = PKTSIZE(get_le32(pb));
                break;
        }
        url_fskip(pb, size);
    }
    return 0;
}

static int nuv_header(AVFormatContext *s, AVFormatParameters *ap) {
    NUVContext *ctx = s->priv_data;
    ByteIOContext *pb = s->pb;
    char id_string[12], version_string[5];
    double aspect, fps;
    int is_mythtv, width, height, v_packs, a_packs;
    int stream_nr = 0;
    AVStream *vst = NULL, *ast = NULL;
    get_buffer(pb, id_string, 12);
    is_mythtv = !memcmp(id_string, "MythTVVideo", 12);
    get_buffer(pb, version_string, 5);
    url_fskip(pb, 3); // padding
    width = get_le32(pb);
    height = get_le32(pb);
    get_le32(pb); // unused, "desiredwidth"
    get_le32(pb); // unused, "desiredheight"
    get_byte(pb); // 'P' == progressive, 'I' == interlaced
    url_fskip(pb, 3); // padding
    aspect = av_int2dbl(get_le64(pb));
    fps = av_int2dbl(get_le64(pb));

    // number of packets per stream type, -1 means unknown, e.g. streaming
    v_packs = get_le32(pb);
    a_packs = get_le32(pb);
    get_le32(pb); // text

    get_le32(pb); // keyframe distance (?)

    if (v_packs) {
        ctx->v_id = stream_nr++;
        vst = av_new_stream(s, ctx->v_id);
        vst->codec->codec_type = CODEC_TYPE_VIDEO;
        vst->codec->codec_id = CODEC_ID_NUV;
        vst->codec->width = width;
        vst->codec->height = height;
        vst->codec->bits_per_sample = 10;
        vst->codec->sample_aspect_ratio = av_d2q(aspect, 10000);
        vst->r_frame_rate = av_d2q(fps, 60000);
        av_set_pts_info(vst, 32, 1, 1000);
    } else
        ctx->v_id = -1;

    if (a_packs) {
        ctx->a_id = stream_nr++;
        ast = av_new_stream(s, ctx->a_id);
        ast->codec->codec_type = CODEC_TYPE_AUDIO;
        ast->codec->codec_id = CODEC_ID_PCM_S16LE;
        ast->codec->channels = 2;
        ast->codec->sample_rate = 44100;
        ast->codec->bit_rate = 2 * 2 * 44100 * 8;
        ast->codec->block_align = 2 * 2;
        ast->codec->bits_per_sample = 16;
        av_set_pts_info(ast, 32, 1, 1000);
    } else
        ctx->a_id = -1;

    get_codec_data(pb, vst, ast, is_mythtv);
    ctx->rtjpg_video = vst->codec->codec_id == CODEC_ID_NUV;
    return 0;
}

#define HDRSIZE 12

static int nuv_packet(AVFormatContext *s, AVPacket *pkt) {
    NUVContext *ctx = s->priv_data;
    ByteIOContext *pb = s->pb;
    uint8_t hdr[HDRSIZE];
    frametype_t frametype;
    int ret, size;
    while (!url_feof(pb)) {
        int copyhdrsize = ctx->rtjpg_video ? HDRSIZE : 0;
        ret = get_buffer(pb, hdr, HDRSIZE);
        if (ret <= 0)
            return ret ? ret : -1;
        frametype = hdr[0];
        size = PKTSIZE(AV_RL32(&hdr[8]));
        switch (frametype) {
            case NUV_EXTRADATA:
                if (!ctx->rtjpg_video) {
                    url_fskip(pb, size);
                    break;
                }
            case NUV_VIDEO:
                if (ctx->v_id < 0) {
                    av_log(s, AV_LOG_ERROR, "Video packet in file without video stream!\n");
                    url_fskip(pb, size);
                    break;
                }
                ret = av_new_packet(pkt, copyhdrsize + size);
                if (ret < 0)
                    return ret;
                pkt->pos = url_ftell(pb) - HDRSIZE;
                pkt->pts = AV_RL32(&hdr[4]);
                pkt->stream_index = ctx->v_id;
                if(hdr[2] == 0) {
                    AVStream *st = s->streams[pkt->stream_index];
                    pkt->flags |= PKT_FLAG_KEY;
                    av_add_index_entry(st, pkt->pos, pkt->pts, size + HDRSIZE, 0, AVINDEX_KEYFRAME);
                }
                memcpy(pkt->data, hdr, copyhdrsize);
                ret = get_buffer(pb, pkt->data + copyhdrsize, size);
                return ret;
            case NUV_AUDIO:
                if (ctx->a_id < 0) {
                    av_log(s, AV_LOG_ERROR, "Audio packet in file without audio stream!\n");
                    url_fskip(pb, size);
                    break;
                }
                ret = av_get_packet(pb, pkt, size);
                pkt->pts = AV_RL32(&hdr[4]);
                pkt->stream_index = ctx->a_id;
                return ret;
            case NUV_SEEKP:
                // contains no data, size value is invalid
                break;
            default:
                url_fskip(pb, size);
                break;
        }
    }
    return AVERROR(EIO);
}

/**
 * \brief looks for the string RTjjjjjjjjjj in the stream too resync reading
 * \return TRUE if the syncword is found.
 */
static int nuv_resync(AVFormatContext *s, int64_t pos_limit) {
    ByteIOContext *pb = s->pb;
    uint32_t tag;

    tag = get_be32(pb);
    while(!url_feof(pb) && url_ftell(pb) < pos_limit) {
        if(tag != MKBETAG('R','T','j','j')) {
            tag = (tag << 8) | get_byte(pb);
            continue;
        }
        tag = get_be32(pb);
        if(tag != MKBETAG('j','j','j','j'))
          continue;

        tag = get_be32(pb);
        if(tag != MKBETAG('j','j','j','j'))
          continue;

        return 1;
    }
    return 0;
}

/**
 * \brief attempts to read a timestamp from stream at the given stream position
 * \return timestamp if successfull and AV_NOPTS_VALUE if failure
 */
static int64_t nuv_read_dts(AVFormatContext *s, int stream_index,
                               int64_t *ppos, int64_t pos_limit)
{
    NUVContext *ctx = s->priv_data;
    ByteIOContext *pb = s->pb;
    uint8_t hdr[HDRSIZE];
    frametype_t frametype;
    int size;
    int64_t pos, dts;

    if (url_fseek(pb, *ppos, SEEK_SET) < 0)
        return AV_NOPTS_VALUE;

    if (!nuv_resync(s, pos_limit))
        return AV_NOPTS_VALUE;

    while (!url_feof(pb) && url_ftell(pb) < pos_limit) {
        if (get_buffer(pb, hdr, HDRSIZE) <= 0)
            return AV_NOPTS_VALUE;
        frametype = hdr[0];
        size = PKTSIZE(AV_RL32(&hdr[8]));
        switch (frametype) {
            case NUV_SEEKP:
                break;
            case NUV_AUDIO:
            case NUV_VIDEO:
                pos = url_ftell(s->pb) - HDRSIZE;
                dts = AV_RL32(&hdr[4]);
                // TODO - add general support in av_gen_search, so it adds positions after reading timestamps
                av_add_index_entry(s->streams[frametype == NUV_VIDEO ? ctx->v_id : ctx->a_id]
                                 , pos, dts, size + HDRSIZE, 0, hdr[2] == 0 ? AVINDEX_KEYFRAME : 0);

                if ((frametype == NUV_VIDEO && stream_index == ctx->v_id) ||
                    (frametype == NUV_AUDIO && stream_index == ctx->a_id)) {
                    *ppos = pos;
                    return dts;
                }
            default:
                url_fskip(pb, size);
                break;
        }
    }
    return AV_NOPTS_VALUE;
}


AVInputFormat nuv_demuxer = {
    "nuv",
    NULL_IF_CONFIG_SMALL("NuppelVideo format"),
    sizeof(NUVContext),
    nuv_probe,
    nuv_header,
    nuv_packet,
    NULL,
    NULL,
    nuv_read_dts,
};
