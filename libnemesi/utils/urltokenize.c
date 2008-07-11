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

#include "utils.h"

typedef struct
{
    char * protocol;
    char * hostname;
    char * port;
    char * path;
} RTSP_Url;

int RTSP_Url_init(RTSP_Url * url, char * urlname)
{
    char * protocol_begin, * hostname_begin, * port_begin, * path_begin;
    size_t protocol_len, hostname_len, port_len, path_len;

    memset(url, 0, sizeof(RTSP_Url));

    hostname_begin = strstr(urlname, "://");
    if (hostname_begin == NULL) {
        hostname_begin = urlname;
        protocol_begin = NULL;
        protocol_len = 0;
    }
    else {
        protocol_len = (size_t)(hostname_begin - urlname);
        hostname_begin = hostname_begin + 3;
        protocol_begin = urlname;
    }

    hostname_len = strlen(urlname) - ((size_t)(hostname_begin - urlname));

    path_begin = strstr(hostname_begin, "/");
    if (path_begin == NULL) {
        path_len = 0;
    }
    else {
        hostname_len = (size_t)(path_begin - hostname_begin);
        path_len = strlen(urlname) - ((size_t)(path_begin - urlname));
    }

    port_begin = strstr(hostname_begin, ":");
    if ((port_begin == NULL) || ((port_begin >= path_begin) && (path_begin != NULL))) {
        port_len = 0;
        port_begin = NULL;
    }
    else {
        ++port_begin;
        if (path_len)
            port_len = (size_t)(path_begin - port_begin);
        else
            port_len = strlen(urlname) - ((size_t)(port_begin - urlname));
        hostname_len = (size_t)(port_begin - hostname_begin - 1);
    }

    if (protocol_len) {
        url->protocol = (char*)malloc(protocol_len+1);
        strncpy(url->protocol, protocol_begin, protocol_len);
        url->protocol[protocol_len] = '\0';
    }

    if (port_len) {
        url->port = (char*)malloc(port_len+1);
        strncpy(url->port, port_begin, port_len);
        url->port[port_len] = '\0';
    }

    if (path_len) {
        url->path = (char*)malloc(path_len+1);
        strncpy(url->path, path_begin, path_len);
        url->path[path_len] = '\0';
    }

    url->hostname = (char*)malloc(hostname_len+1);
    strncpy(url->hostname, hostname_begin, hostname_len);
    url->hostname[hostname_len] = '\0';

    return 0;
}

void RTSP_Url_destroy(RTSP_Url * url)
{
    free(url->protocol);
    free(url->hostname);
    free(url->port);
    free(url->path);
}

int urltokenize(char *urlname, char **host, char **port, char **path)
{
    RTSP_Url url;

    RTSP_Url_init(&url, urlname);

    if (host != NULL) 
        *host = url.hostname;
    else
        free(url.hostname);

    if (port != NULL) 
        *port = url.port;
    else
        free(url.port);

    if (path != NULL) 
        *path = url.path;
    else
        free(url.path);

    free(url.protocol);

    return 0;
}
