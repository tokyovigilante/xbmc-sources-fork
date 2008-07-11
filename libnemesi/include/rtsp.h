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

/** @file rtsp.h
 * rtsp library public interface definitions.
 */

#ifndef NEMESI_RTSP_H
#define NEMESI_RTSP_H

#include <pthread.h>
#include "cc.h"
#include "transport.h"
#include "rtp.h"
#include "sdp.h"
#include <netembryo/rtsp_errors.h>

/*! Default RTSP port (default setting from rfc) if not explicitly specified. */
#define RTSP_DEFAULT_PORT 554

/*! Version of implemented protocol. */
#define RTSP_VER "RTSP/1.0"

/*! RTSP End of Line. */
#define RTSP_EL "\r\n"

/*! Lower bound for first RTP port if specified by user. */
#define RTSP_MIN_RTP_PORT 1024

#define RTSP_READY    0
#define RTSP_BUSY    1

#define RTSP_SESSION_ID_LEN 256

typedef struct {
    int first_rtp_port;
    int prebuffer_size;
    sock_type pref_rtsp_proto;
    sock_type pref_rtp_proto;
} nms_rtsp_hints;

/*!
 * @brief RTSP medium description.
 *
 * This struct is an item in a single-linked list that identifies all the media
 * that belong to a RTSP session. Through the \c rtp_sess pointer is possible
 * to get the RTP session of the described medium.
 
 * @note The methods SETUP e TEARDOWN are defined on a ``per medium'' scope,
 * they have to be sent for each medium and you must wait for a reply from 
 * the server for each of them.
 *
 * @see Medium_info
 * @see rtsp_session
 * */
typedef struct rtsp_medium_s {
    sdp_medium_info *medium_info;    /*!< Medium informations. */
    rtp_session *rtp_sess;    /*!< RTP session whom
                   the medium belongs */
    struct rtsp_medium_s *next;    /*!< Next medium. */
    char *filename;        /*!< Medium identifier. Used for the
                   ``per medium'' methods
                   (SETUP, TEARDOWN). */
} rtsp_medium;

/*!
 * @brief RTSP session description.
 *
 * Item of the RTSP sessions list.
 *
 * In this struct are present all the information used in a RTSP session.
 * For each session there is a queue of media that belongs to the same
 * ``presentation''
 *
 * @note The methods PLAY, PAUSE, RECORD are defined on a``per session'' scope,
 * they have to be sent for each active session. Aggregated media belongs to
 * the same session, so a session method will have effect to every of them.
 * E.g a PLAY method on an Audio Video session will start both audio and video
 * streams at the same time
 *
 * @see rtsp_session_info
 * @see rtsp_medium
 * */
typedef struct rtsp_session_s {
    char Session_ID[RTSP_SESSION_ID_LEN];    /*!< RTSP identifier. */
    int CSeq;        /*!< Last sent RTSP packet 
                   sequence number */
    char *pathname;        /*!< RTSP session identifier.
                   Used for the ``per session''
                   methods (PLAY, PAUSE, RECORD) */
    char *content_base;    /*!< Not \c NULL if a Content-Base field
                   is found in the response to the DESCRIBE 
                   method. In this case the field
                   <tt>\ref pathname</tt> and all the
                   <tt>\ref rtsp_medium</tt> of the session
                   are relative to \c content_base path. */
    sdp_session_info *info;    /*!< Session informations */

    rtsp_medium *media_queue;    /*!< Media queue */
    struct rtsp_session_s *next;    /*!< Next session */

    /********************************************/
    /* Do NOT USE IT! JUST FOR INTERNAL USAGE!  */
    /********************************************/
    char *body;        /*!< Contains the raw describe response.
                   It should be NEVER accessed directly.
                   All the data is available through
                   <tt>\ref rtsp_session_info</tt>. */
} rtsp_session;

/*! @enum Definition for possible states in RTSP state-machine
 * The last ("STATES_NUM") is used to know how many states are present in the machine.
 */
enum states { INIT, READY, PLAYING, RECORDING, STATES_NUM };

/*!
 * @brief Definition of the common part for rtsp_thread and rtsp_ctrl structs
 */
#define RTSP_COMMON_IF \
            pthread_mutex_t comm_mutex; \
            struct command *comm; \
            enum states status;    /*!< Current RTSP state-machine status */ \
            unsigned char busy; /*!< Boolean value identifing if \
                        the rtsp module is busy waiting reply from server*/ \
            pthread_t rtsp_tid; \
            char descr_fmt; /* Description format inside RTSP body */ \
            rtsp_session *rtsp_queue;/*!< List of active sessions. */ \
            cc_perm_mask accepted_CC;    /* accepted CC licenses */ \
            int response_id; /*!< Last received response from the server */

typedef struct rtsp_ctrl_t {
RTSP_COMMON_IF
} rtsp_ctrl;

extern RTSP_Error const RTSP_Ready;
extern RTSP_Error const RTSP_Reinitialized;

/**
 * RTSP Layer
 * @defgroup RTSP_layer RTSP Layer
 * @{
 */


/** @defgroup RTSP RTSP Public Interface
 *
 * @brief RTSP controller and management public interface
 *
 * The RTSP module requests the media streams and handles the service 
 * handshake. Once this phase is complete it behaves like a <em>remote 
 * controller</em> for the requested multimedia stream.
 *
 * @{ */

rtsp_ctrl *rtsp_init(nms_rtsp_hints *);
int rtsp_is_busy(rtsp_ctrl *);

RTSP_Error rtsp_wait(rtsp_ctrl *);
int rtsp_close(rtsp_ctrl *);
int rtsp_open(rtsp_ctrl *, char *);
int rtsp_pause(rtsp_ctrl *);
int rtsp_stop(rtsp_ctrl *);

int rtsp_play(rtsp_ctrl *, double, double);
int rtsp_seek(rtsp_ctrl *, double, double);

int rtsp_uninit(rtsp_ctrl *);

#define rtsp_status(ctrl) ctrl->status
void rtsp_info_print(rtsp_ctrl *);

rtp_thread *rtsp_get_rtp_th(rtsp_ctrl * rtsp_ctl);
rtp_session *rtsp_get_rtp_queue(rtsp_ctrl * rtsp_ctl);

/**
 * @}
 */

#endif /* NEMESI_RTSP_H */
