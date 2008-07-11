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

#ifndef NEMESI_RTCP_H
#define NEMESI_RTCP_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifndef WIN32
#include <unistd.h>
#endif

#include "comm.h"
#include "rtp.h"
#include "transport.h"


#define MAX_PKT_SIZE 548    /* 576 - 20 - 8 = Minimum Reassembly Buffer Size - IP datagram header -  UDP hedaer: in octects */
#define MAX_SDES_LEN 255    /* in octects */

typedef enum {
    RTCP_SR = 200,
    RTCP_RR = 201,
    RTCP_SDES = 202,
    RTCP_BYE = 203,
    RTCP_APP = 204
} rtcp_type_t;

typedef enum {
    RTCP_SDES_END = 0,
    RTCP_SDES_CNAME = 1,
    RTCP_SDES_NAME = 2,
    RTCP_SDES_EMAIL = 3,
    RTCP_SDES_PHONE = 4,
    RTCP_SDES_LOC = 5,
    RTCP_SDES_TOOL = 6,
    RTCP_SDES_NOTE = 7,
    RTCP_SDES_PRIV = 8
} rtcp_sdes_type_t;

typedef struct {
#ifdef WORDS_BIGENDIAN
    uint32_t ver:2;
    uint32_t pad:1;
    uint32_t count:5;
#else
    uint32_t count:5;
    uint32_t pad:1;
    uint32_t ver:2;
#endif
    uint32_t pt:8;
    uint32_t len:16;

} rtcp_common_t;

#ifdef WORDS_BIGENDIAN

#define RTCP_VALID_MASK ( 0xc000 | 0x2000 | 0xfe )    /* ver | pad | pt */
#define RTCP_VALID_VALUE ( (RTP_VERSION << 14) | RTCP_SR )

#else

#define RTCP_VALID_MASK ( 0xfe00 | 0x20 | 0xc0 )    /* pad | ver | pt */
#define RTCP_VALID_VALUE ( ( RTCP_SR << 8 ) | (RTP_VERSION << 6) )

#endif

typedef struct {
    uint32_t ssrc;
    uint32_t fraction:8;
    int32_t lost:24;
    uint32_t last_seq;
    uint32_t jitter;
    uint32_t last_sr;
    uint32_t dlsr;
} rtcp_rr_t;

typedef struct {
    uint32_t ntp_seq;
    uint32_t ntp_frac;
    uint32_t ntp_ts;
    uint32_t psent;
    uint32_t osent;
} rtcp_si_t;

typedef struct {
    uint8_t type;
    uint8_t len;
    uint8_t data[1];
} rtcp_sdes_item_t;

typedef struct {
    rtcp_common_t common;
    union {
        struct {
            uint32_t ssrc;
            rtcp_si_t si;
            rtcp_rr_t rr[1];
        } sr;

        struct {
            uint32_t ssrc;
            rtcp_rr_t rr[1];
        } rr;

        struct rtcp_sdes {
            uint32_t src;
            rtcp_sdes_item_t item[1];
        } sdes;

        struct {
            uint32_t src[1];
        } bye;

        struct {
            uint32_t src;
            char name[4];
            uint8_t data[1];
        } app;
    } r;
} rtcp_pkt;

struct rtcp_event {
    rtp_session *rtp_sess;
    struct timeval tv;
    rtcp_type_t type;
    struct rtcp_event *next;
};

typedef struct rtcp_sdes rtcp_sdes_t;

/**
 * RTCP Layer
 * @defgroup rtcp_layer RTCP Layer
 * @{
 */

int rtcp_thread_create(rtp_thread *th);
int rtcp_recv(rtp_session *sess);

/**
 * RTCP Packets Handling
 * @defgroup rtcp_packets RTCP Packets Handling
 * @{
 */
int rtcp_parse_pkt(rtp_ssrc *ssrc, rtcp_pkt *pkt, int len);
int rtcp_parse_sr(rtp_ssrc *ssrc, rtcp_pkt *pkt);
int rtcp_parse_sdes(rtp_ssrc *ssrc, rtcp_pkt *pkt);
int rtcp_parse_rr(rtcp_pkt *pkt);
int rtcp_parse_bye(rtp_ssrc *ssrc, rtcp_pkt *pkt);
int rtcp_parse_app(rtcp_pkt *pkt);

int rtcp_send_rr(rtp_session *sess);
int rtcp_build_rr(rtp_session *sess, rtcp_pkt *pkt);
int rtcp_build_sdes(rtp_session *sess, rtcp_pkt *pkt, int left);
int rtcp_send_bye(rtp_session *sess);
/**
 * @}
 */


/**
 * RTCP Events
 * @defgroup rtcp_events RTCP Events Loop
 * @{
 */
void rtcp_clean_events(void *events);

struct rtcp_event *rtcp_schedule(struct rtcp_event *head,
                                 rtp_session *sess,
                                 struct timeval tv, rtcp_type_t type);

struct rtcp_event *rtcp_deschedule(struct rtcp_event *event);

struct rtcp_event *rtcp_handle_event(struct rtcp_event *event);
/**
 * @}
 */

/**
 * @}
 */

#endif /* NEMESI_RTCP_H */
