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

/**
 * @file ssl.c
 * SSL support
 */

#include "ssl.h"
#include "wsocket.h"

/**
 * It initializes the global context ssl
 * @param : path of the server certificate
 * @param : cert verification mode @see SSL_CTX_set_verify
 * @return: 0 on success;
 */
SSL_CTX * Sock_init_ctx(char *key, char * cafile, char * capath) 
{
    SSL_CTX *global_ctx = NULL;
    char cipher[] = "ALL:eNULL";
    int s_server_session_id_context = 1;
    SSL_METHOD *method;

    SSL_load_error_strings();
    SSL_library_init();

    method = SSLv23_method();
    global_ctx = SSL_CTX_new(method);
    if(!global_ctx) {
        net_log(NET_LOG_ERR,"Creation of a new SSL_CTX object failed");
        return NULL;
    }

    /* Loads a certificate chain from file into ctx */
    if(!(SSL_CTX_use_certificate_chain_file(global_ctx,key))) {
        net_log(NET_LOG_ERR,"Failure in reading certificate file");
        return NULL;
    }

    /* Adds the first private key found in file to ctx */
    if(!(SSL_CTX_use_PrivateKey_file(global_ctx,key,SSL_FILETYPE_PEM))) {
        net_log(NET_LOG_ERR,"Failure in reading key file");
        return NULL;
    }

    /* Set default locations for trusted CA certificates */
    if(!(SSL_CTX_load_verify_locations(global_ctx, cafile, capath))) {
        net_log(NET_LOG_ERR,"Failure in reading CA list");
        return NULL;
    }

    /* Set context within which session can be reused */
    SSL_CTX_set_session_id_context(global_ctx,
                                   (void*)&s_server_session_id_context,
        sizeof(s_server_session_id_context));

    /* Choose list of available SSL_CIPHER */
    SSL_CTX_set_cipher_list(global_ctx,cipher);

    /* Manipulate SSL engine options */
    //SSL_CTX_set_options(ctx,SSL_OP_ALL);

    SSL_CTX_set_verify(global_ctx,SSL_VERIFY_PEER,0);

    return global_ctx;
}


/**
 * The Function establishes a new ssl connection
 * @param : the socket descriptor
 * @return: pointer to new structure ssl
 */

SSL *SSL_sock_accept(int sockfd, SSL_CTX * global_ctx) {

    int exit;
    SSL *ssl;

    ssl = SSL_new(global_ctx);
    if(!ssl) {
        net_log(NET_LOG_ERR, "Sock SSL_connect: SSL_new() failed.\n");
        return 0;
    }

    if((SSL_set_fd(ssl,sockfd))==0) {
        net_log(NET_LOG_ERR,"Operation failed\n");
        return 0;
    }

    if((SSL_accept(ssl)<=0)) {
        net_log(NET_LOG_ERR,"SSL accept error");
        return 0;
    }

    return(ssl);
}


/**
 * It closes a ssl connection
 * @param : pointer to structure ssl
 * @param : the socket descriptor
 * @return: '1' success operation, otherwise '0'
 */

int SSL_close_connection(SSL *ssl, int sockfd) {

    int exit;

    exit = SSL_shutdown(ssl);
    if(!exit) {
        shutdown(sockfd,SHUT_WR);
        SSL_shutdown(ssl);
    } else {
        net_log(NET_LOG_ERR,"Shutdown failed");
        return 0;
    }
    SSL_free(ssl);
    return 1;
}


/**
 * This function reads at most nbyte from the connection ssl
 * @param : pointer to structure ssl
 * @param : buffer to store bytes that are read.
 * @param : maximum number of bytes to write to the buffer
 * @return: 'number of bytes read' success operation, otherwise '0'
 */

int SSL_sock_read(SSL *ssl, void *buffer, int nbyte) {

    if(ssl)
        return(SSL_read(ssl,buffer,nbyte));
    else
        return 0;
}


/**
 * This function writes up to nbyte from buffer to socket ssl
 * @param : pointer to structure ssl
 * @param : buffer to store bytes that are read.
 * @param : maximum number of bytes to write to the buffer
 * @return: Number of bytes written
 */

int SSL_sock_write(SSL *ssl, void *buffer, int nbyte) {
    return(SSL_write(ssl,buffer,nbyte));
}

int sock_SSL_connect(SSL **ssl_con, int sockfd, SSL_CTX * ssl_ctx)
{
    int ssl_err;

    if(!ssl_ctx) {
        net_log(NET_LOG_ERR, "sock_SSL_connect: !ssl_ctx\n");
        return WSOCK_ERROR;
    }

    *ssl_con = SSL_new(ssl_ctx);

    if(!(*ssl_con)) {
        net_log(NET_LOG_ERR, "sock_SSL_connect: SSL_new() failed.\n");
        SSL_CTX_free(ssl_ctx);
        return WSOCK_ERROR;
    }

    SSL_set_fd (*ssl_con, sockfd);
    SSL_set_connect_state(*ssl_con);
    ssl_err = SSL_connect(*ssl_con);

    if(ssl_err < 0)
        SSL_set_shutdown(*ssl_con, SSL_SENT_SHUTDOWN);
    if(ssl_err <= 0) {
        net_log(NET_LOG_ERR, "sock_SSL_connect: SSL_connect() failed.\n");
        SSL_free(*ssl_con);
        SSL_CTX_free(ssl_ctx);
        return WSOCK_ERROR;
    }

    return WSOCK_OK;
}
