/*   -*- c -*-
 * 
 *  ----------------------------------------------------------------------
 *  Misc includes.
 *  ----------------------------------------------------------------------
 *
 *  Copyright (c) 2002-2003 by PuhPuh
 *  
 *  This code is copyrighted property of the author.  It can still
 *  be used for any non-commercial purpose following conditions:
 *  
 *      1) This copyright notice is not removed.
 *      2) Source code follows any distribution of the software
 *         if possible.
 *      3) Copyright notice above is found in the documentation
 *         of the distributed software.
 *  
 *  Any express or implied warranties are disclaimed.  Author is
 *  not liable for any direct or indirect damages caused by the use
 *  of this software.
 *
 *  ----------------------------------------------------------------------
 *
 *  This code has been integrated into Xbox Media Player.  
 *  As such it can me copied, redistributed and modified under
 *  the same conditions as the XBMP itself.
 *
 */


#ifndef CCINCLUDES_H_INCLUDED
#define CCINCLUDES_H_INCLUDED 1
#ifdef __APPLE__
#include <sys/select.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#if defined(__linux__) || defined(__APPLE__)
#include <inttypes.h>
#else
#include "inttypes.h"
#endif

#include "ccutil.h"

#ifdef _XBOX
#include <xtl.h>
#elif defined(__linux__) || defined(__APPLE__)
#include <sys/socket.h>
#include <inttypes.h>
#include <netdb.h>
#else
#include <windows.h>
#endif /* _XBOX */

extern int errno;

#ifndef PATH_MAX
#define PATH_MAX 1024
#endif /* ! PATH_MAX */

#if defined(__linux__) || defined(__APPLE__)
#define CC_UINT_64_TYPE_NAME      uint64_t
#else
#define CC_UINT_64_TYPE_NAME	  UINT64
#endif
#define CC_UINT_64_PRINTF_FORMAT  "%lu"

#endif /* CCINCLUDES_H_INCLUDED */
/* eof (ccincludes.h) */
