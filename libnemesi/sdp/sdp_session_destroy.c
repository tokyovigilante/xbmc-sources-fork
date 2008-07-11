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

#include "sdp.h"

void sdp_session_destroy(sdp_session_info * session)
{
    sdp_attr *sdp_attr, *sdp_attr_prev;

    if (session) {
        sdp_media_destroy(session->media_info_queue);
        // destroy session attributes
        for (sdp_attr = session->attr_list; sdp_attr;
             sdp_attr_prev = sdp_attr, sdp_attr =
             sdp_attr->next, free(sdp_attr_prev));

        free(session);
    }
}
