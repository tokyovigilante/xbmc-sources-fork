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
 * @file wsocket.h
 * socket wrapper
 */

#ifndef WSOCKET_H
#define WSOCKET_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>

#ifndef WIN32
#   include <unistd.h>
#   include <netinet/in.h>
#   include <arpa/inet.h>
#   include <sys/types.h>
#   include <sys/socket.h>
#   include <arpa/inet.h>
#   include <netdb.h>
#else
#   include <winsock2.h>
#   include <ws2tcpip.h>
#   include <stdint.h>
#endif

#ifdef WIN32
typedef unsigned short sa_family_t;
typedef unsigned short in_port_t;
typedef unsigned int in_addr_t;

const char *inet_ntop(int af, const void *src, char *dst, unsigned cnt);
int inet_pton(int af, const char *src, void *dst);
#endif

/** flags definition*/
typedef enum {
/** ssl flags */
    IS_SSL = 0x1,
    IS_TLS = 0x3, /**< setting this will also set IS_SSL */
/** multicast flags */
    IS_MULTICAST = 0x4
} sock_flags;

/** socket type definition */
typedef enum {
/** socket fd not valid */
    SOCK_NONE,
/** IP based protcols */
    TCP,
    UDP,
    SCTP,
/** Local socket (Unix) */
    LOCAL
} sock_type;

/** 
 * Socket abstraction structure
 */
typedef struct {
    sock_type socktype; ///< socket type
    int fd;    ///< low level socket file descriptor
    struct sockaddr_storage local_stg;    ///< low level address storage from getsockname
    struct sockaddr_storage remote_stg;    ///< low level address storage from getpeername
    struct sockaddr_storage multicast_stg; ///< multicast address storage
    /** flags */
    sock_flags flags;
    /** human readable data */
    char *remote_host; ///< remote host stored as dinamic string
    char *local_host; ///< local host stored as dinamic string
    in_port_t remote_port;    ///< remote port stored in host order
    in_port_t local_port;    ///< local port stored in host order
    void *ssl; ///< stores ssl context information
} Sock;

#define WSOCK_ERRORPROTONOSUPPORT -5    
#define WSOCK_ERRORIOCTL    -4    
#define WSOCK_ERRORINTERFACE    -3    
#define WSOCK_ERROR    -2    
#define WSOCK_ERRFAMILYUNKNOWN    -1
#define WSOCK_OK 0
#define WSOCK_ERRSIZE    1
#define WSOCK_ERRFAMILY    2
#define WSOCK_ERRADDR    3
#define WSOCK_ERRPORT    4

/** log facilities */
/* Outputs the messages using the default logger or a custom one passed to
 * Sock_init() */
void net_log(int, const char*, ...);
/* levels to be implemented by log function */
#define NET_LOG_FATAL 0 
#define NET_LOG_ERR 1
#define NET_LOG_WARN 2 
#define NET_LOG_INFO 3 
#define NET_LOG_DEBUG 4 
#define NET_LOG_VERBOSE 5 

/** @defgroup NetEmbryo_Socket Sockets Access Interface
 *
 * @brief simple socket abstraction.
 *
 * @{ 
 */

Sock * Sock_connect(char *host, char *port, Sock *binded, sock_type socktype, void * ctx);

Sock * Sock_bind(char *host, char *port, Sock *sock, sock_type socktype, void * ctx);

Sock * Sock_accept(Sock *main, void * ctx);

int Sock_listen(Sock *s, int backlog);

int Sock_read(Sock *s, void *buffer, int nbytes, void *protodata, int flags);

int Sock_write(Sock *s, void *buffer, int nbytes, void *protodata, int flags);

int Sock_close(Sock *s);

void Sock_init(void (*log_function)(int level, const char *fmt, va_list list));

int Sock_compare(Sock *p, Sock *q);

int Sock_socketpair(Sock *pair[]);

int Sock_set_dest(Sock *s, struct sockaddr *dst);

/** low level access macros */
#define Sock_fd(A) ((A)->fd)
#define Sock_type(A) ((A)->socktype)
#define Sock_flags(A) ((A)->flags)

int Sock_set_props(Sock *s, int request, int *on);

/*get_info.c*/
char * get_remote_host(Sock *);
char * get_local_host(Sock *);
inline int get_local_hostname(char *localhostname, size_t len); // return 0 if ok
in_port_t get_remote_port(Sock *);
in_port_t get_local_port(Sock *);

/**
 * @}
 */
 
#endif // WSOCKET_H
