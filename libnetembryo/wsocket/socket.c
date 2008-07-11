/* * 
 * * This file is part of NetEmbryo
 *
 * Copyright (C) 2007 by LScube team <team@streaming.polito.it>
 * See AUTHORS for more details
 * 
 * NetEmbryo is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * NetEmbryo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with NetEmbryo; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *  
 * */

/**
 * @file socket.c
 * low level socket management
 */

#include "wsocket.h"
#include "wsocket-internal.h"
#include <string.h>
/**
 * wraps accept
 * @return -1 on error 
 * @return the socket descriptor
 * @note doesn't shutdown the listened one
 **/

int sock_accept(int sock)
{
    int new_fd;      
    struct sockaddr_in their_addr; /* connector's address information */
    socklen_t sin_size;
    
    memset(&their_addr, 0, sizeof(struct sockaddr_in));

    sin_size = sizeof(struct sockaddr_in);
    new_fd = accept(sock,(struct sockaddr *)&their_addr, &sin_size);

    return new_fd;
}

/**
 * bind wrapper
 */

int sock_bind(char *host, char *port, int *sock, sock_type socktype)
{
    int n, param = 1;
    int bind_new;
    struct addrinfo *res, *ressave;
    struct addrinfo hints;
#ifdef HAVE_LIBSCTP
    struct sctp_initmsg initparams;
    struct sctp_event_subscribe subscribe;
#endif

    memset(&hints, 0, sizeof(struct addrinfo));

    if (host == NULL)
        hints.ai_flags = AI_PASSIVE;
    else
        hints.ai_flags = AI_CANONNAME;
#ifdef IPV6
    hints.ai_family = AF_UNSPEC;
#else
    hints.ai_family = AF_INET;
#endif

    switch (socktype) {
    case SCTP:
#ifndef HAVE_LIBSCTP
        net_log(NET_LOG_ERR, "SCTP protocol not compiled in\n");
        return WSOCK_ERROR;
        break;
#endif    // else go down to TCP case (SCTP and TCP are both SOCK_STREAM type)
    case TCP:
        hints.ai_socktype = SOCK_STREAM;
        break;
    case UDP:
        hints.ai_socktype = SOCK_DGRAM;
        break;
    default:
        net_log(NET_LOG_ERR, "Unknown socket type specified\n");
        return WSOCK_ERROR;
        break;
    }

    if ((n = getaddrinfo(host, port, &hints, &res)) != 0) {
        net_log(NET_LOG_ERR, "%s\n", gai_strerror(n));    
        return WSOCK_ERRADDR;
    }
    
    ressave = res;
    bind_new = (*sock < 0);

    do {
#ifdef HAVE_LIBSCTP
        if (socktype == SCTP)
            res->ai_protocol = IPPROTO_SCTP;
#endif // TODO: remove this code when SCTP will be supported from getaddrinfo()
        if (bind_new && (*sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0)
            continue;

#ifdef HAVE_LIBSCTP
        if (socktype == SCTP) {
            // Enable the propagation of packets headers
            memset(&subscribe, 0, sizeof(subscribe));
            subscribe.sctp_data_io_event = 1;
            if (setsockopt(*sock, SOL_SCTP, SCTP_EVENTS, &subscribe,
                    sizeof(subscribe)) < 0) {
                net_log(NET_LOG_ERR, "setsockopts(SCTP_EVENTS) error in sctp_open.\n");
                return WSOCK_ERROR;
                }

            // Setup number of streams to be used for SCTP connection
            memset(&initparams, 0, sizeof(initparams));
            initparams.sinit_max_instreams = MAX_SCTP_STREAMS;
            initparams.sinit_num_ostreams = MAX_SCTP_STREAMS;
            if (setsockopt(*sock, SOL_SCTP, SCTP_INITMSG, &initparams,
                    sizeof(initparams)) < 0) {
                net_log(NET_LOG_ERR, "setsockopts(SCTP_INITMSG) error in sctp_open.\n");
                return WSOCK_ERROR;
                }
        }
#endif
                if (setsockopt(*sock, SOL_SOCKET, SO_REUSEADDR, &param,
                    sizeof(int))) 
                        net_log(NET_LOG_ERR,
                                "setsockopts(SO_REUSEADDR) failed");

                if (bind(*sock, res->ai_addr, res->ai_addrlen) == 0)
            break;

        if (bind_new) {
            if (close(*sock) < 0)
                return WSOCK_ERROR;
            else
                *sock = -1;
        }

    } while ((res = res->ai_next) != NULL);

    freeaddrinfo(ressave);

    if ( !res )
        return WSOCK_ERROR;

    return 0;
}

/**
 * wraps close
 * @bug remove it or extend it!
 */

int sock_close(int s)
{
    return close(s);
}

/**
 * wraps connect
 */

int sock_connect(char *host, char *port, int *sock, sock_type socktype)
{
    int n, connect_new;
    struct addrinfo *res, *ressave;
    struct addrinfo hints;
#ifdef HAVE_LIBSCTP
    struct sctp_initmsg initparams;
    struct sctp_event_subscribe subscribe;
#endif

    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_flags = AI_CANONNAME;
#ifdef IPV6
    hints.ai_family = AF_UNSPEC;
#else
    hints.ai_family = AF_INET;
#endif
    switch (socktype) {
    case SCTP:
#ifndef HAVE_LIBSCTP
        net_log(NET_LOG_FATAL, "SCTP protocol not compiled in\n");
        return WSOCK_ERROR;
        break;
#endif    // else go down to TCP case (SCTP and TCP are both SOCK_STREAM type)
    case TCP:
        hints.ai_socktype = SOCK_STREAM;
        break;
    case UDP:
        hints.ai_socktype = SOCK_DGRAM;
        break;
    default:
        net_log(NET_LOG_ERR, "Unknown socket type specified\n");
        return WSOCK_ERROR;
        break;
    }

    if ((n = getaddrinfo(host, port, &hints, &res)) != 0) {
        net_log(NET_LOG_ERR, "%s\n", gai_strerror(n));    
        return WSOCK_ERRADDR;
    }
    
    ressave = res;

    connect_new = (*sock < 0);

    do {
#ifdef HAVE_LIBSCTP
        if (socktype == SCTP)
            res->ai_protocol = IPPROTO_SCTP;
#endif // TODO: remove this code when SCTP will be supported from getaddrinfo()
        if (connect_new && (*sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0)
            continue;

#ifdef HAVE_LIBSCTP
        if (socktype == SCTP) {
            // Enable the propagation of packets headers
            memset(&subscribe, 0, sizeof(subscribe));
            subscribe.sctp_data_io_event = 1;
            if (setsockopt(*sock, SOL_SCTP, SCTP_EVENTS, &subscribe,
                    sizeof(subscribe)) < 0) {
                net_log(NET_LOG_ERR, "setsockopts(SCTP_EVENTS) error in sock_connect.\n");
                return WSOCK_ERROR;
                }


            // Setup number of streams to be used for SCTP connection
            memset(&initparams, 0, sizeof(initparams));
            initparams.sinit_max_instreams = MAX_SCTP_STREAMS;
            initparams.sinit_num_ostreams = MAX_SCTP_STREAMS;
            if (setsockopt(*sock, SOL_SCTP, SCTP_INITMSG, &initparams,
                    sizeof(initparams)) < 0) {
                net_log(NET_LOG_ERR, "setsockopts(SCTP_INITMSG) error in sock_connect.\n");
                return WSOCK_ERROR;
                }
        }
#endif

        if (connect(*sock, res->ai_addr, res->ai_addrlen) == 0)
            break;

        if (connect_new) {
            if (close(*sock) < 0)
                return WSOCK_ERROR;
            else
                *sock = -1;
        }

    } while ((res = res->ai_next) != NULL);

    freeaddrinfo(ressave);

    if ( !res )
        return WSOCK_ERROR;

    return WSOCK_OK;
}

/**
 * get the port from a sockaddr
 * @return the port or -1 on error
 */

int sock_get_port(const struct sockaddr *sa)
{
    switch (sa->sa_family) {
        case AF_INET: {
            struct sockaddr_in    *sin = (struct sockaddr_in *) sa;
    
            return(sin->sin_port);
        }

#ifdef    IPV6
        case AF_INET6: {
            struct sockaddr_in6    *sin6 = (struct sockaddr_in6 *) sa;
    
            return(sin6->sin6_port);
        }
#endif
    }

    return -1;
}

/**
 * wraps listen
 * @bug extend or remove!
 */

int sock_listen(int s, int backlog)
{
    return listen(s, backlog);
}

