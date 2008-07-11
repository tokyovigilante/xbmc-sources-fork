/* * 
 * This file is part of NetEmbryo
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
 * @file wsocket-internal.h
 * Internal definitions
 */

#ifndef WSOCKET_INTERNAL_H
#define WSOCKET_INTERNAL_H

#ifdef HAVE_LIBSCTP
#include <netinet/sctp.h>
#define MAX_SCTP_STREAMS 15
#endif

#ifndef IN_IS_ADDR_MULTICAST
#define IN_IS_ADDR_MULTICAST(a)    ((((in_addr_t)(a)) & 0xf0000000) == 0xe0000000)
#endif

#if IPV6
#ifndef IN6_IS_ADDR_MULTICAST
#define IN6_IS_ADDR_MULTICAST(a) ((a)->s6_addr[0] == 0xff)
#endif
#endif //IPV6

/** 
 * @defgroup NetEmbryo_Internals Low level wrappers
 * @brief Low level internal implementations, private
 * @{ 
 */

int sock_connect(char *host, char *port, int *sock, sock_type socktype);
int sock_bind(char *host, char *port, int *sock, sock_type socktype);
int sock_accept(int sock);
int sock_listen(int s, int backlog);
int sock_close(int s);

/**
 * @return the address in human readable string format
 */
const char *sock_ntop_host(const struct sockaddr *sa, char *str, size_t len);

/**
 * @return the port in network byte order (use ntohs to change it)
 */
int sock_get_port(const struct sockaddr *sa);

/**
 * @defgroup multicast Multicast related functions
 * @brief join and leave facilities
 * @{
 */

int mcast_join (int sockfd, const struct sockaddr *sa);

int mcast_leave(int sockfd, const struct sockaddr *sa);

/**
 * @}
 * @}
 */

#endif // WSOCKET_INTERNAL_H
