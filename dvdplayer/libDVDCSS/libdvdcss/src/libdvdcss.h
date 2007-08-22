/*****************************************************************************
 * libdvdcss.h: private DVD reading library data
 *****************************************************************************
 * Copyright (C) 1998-2001 VideoLAN
 * $Id: libdvdcss.h 152 2004-02-24 15:47:00Z sam $
 *
 * Authors: St�phane Borel <stef@via.ecp.fr>
 *          Samuel Hocevar <sam@zoy.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111, USA.
 *****************************************************************************/

struct iovec;

/*****************************************************************************
 * The libdvdcss structure
 *****************************************************************************/
struct dvdcss_s
{
    /* File descriptor */
    char * psz_device;
    int    i_fd;
    int    i_read_fd;
    int    i_pos;

    /* File handling */
    int ( * pf_seek )  ( dvdcss_t, int );
    int ( * pf_read )  ( dvdcss_t, void *, int );
    int ( * pf_readv ) ( dvdcss_t, struct iovec *, int );

    /* Decryption stuff */
    int          i_method;
    css_t        css;
    int          b_ioctls;
    int          b_scrambled;
    dvd_title_t *p_titles;

    /* Key cache directory and pointer to the filename */
    char   psz_cachefile[PATH_MAX];
    char * psz_block;

    /* Error management */
    char * psz_error;
    int    b_errors;
    int    b_debug;

#ifdef WIN32
    int    b_file;
    char * p_readv_buffer;
    int    i_readv_buf_size;
#endif

#ifndef WIN32
    int    i_raw_fd;
#endif
};

/*****************************************************************************
 * libdvdcss method: used like init flags
 *****************************************************************************/
#define DVDCSS_METHOD_KEY        0
#define DVDCSS_METHOD_DISC       1
#define DVDCSS_METHOD_TITLE      2

/*****************************************************************************
 * Functions used across the library
 *****************************************************************************/
#define print_error(dvdcss,msg) _print_error(dvdcss,msg)
#define print_debug(dvdcss,msg,args...) \
    if( dvdcss->b_debug ) \
    { \
        fprintf( stderr, "libdvdcss debug: " ); \
        fprintf( stderr, msg, ##args ); \
        fprintf( stderr, "\n" ); \
    }

void _print_error ( dvdcss_t, char * );

