/* *
 *  This file is part of Feng
 *
 * Copyright (C) 2007 by LScube team <team@streaming.polito.it>
 * See AUTHORS for more details
 *
 * Feng is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * Feng is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Feng; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <openssl/ssl.h>


SSL_CTX * init_ctx(char *key, char * cafile, char * capath);
int sock_SSL_connect(SSL **ssl_con, int sockfd, SSL_CTX * ssl_ctx);
SSL *SSL_sock_accept(int sockfd, SSL_CTX * global_ctx);
int SSL_close_connection(SSL *ssl,int sockfd);
int SSL_sock_read(SSL *ssl,void *buffer,int nbyte);
int SSL_sock_write(SSL *ssl,void *buffer,int nbyte);
