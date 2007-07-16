/* png.h - header file for PNG reference library
 *
 * libpng version 1.2.5 - October 3, 2002
 * Copyright (c) 1998-2002 Glenn Randers-Pehrson
 * (Version 0.96 Copyright (c) 1996, 1997 Andreas Dilger)
 * (Version 0.88 Copyright (c) 1995, 1996 Guy Eric Schalnat, Group 42, Inc.)
 *
 * Authors and maintainers:
 *  libpng versions 0.71, May 1995, through 0.88, January 1996: Guy Schalnat
 *  libpng versions 0.89c, June 1996, through 0.96, May 1997: Andreas Dilger
 *  libpng versions 0.97, January 1998, through 1.2.5 - October 3, 2002: Glenn
 *  See also "Contributing Authors", below.
 *
 * Note about libpng version numbers:
 *
 *    Due to various miscommunications, unforeseen code incompatibilities
 *    and occasional factors outside the authors' control, version numbering
 *    on the library has not always been consistent and straightforward.
 *    The following table summarizes matters since version 0.89c, which was
 *    the first widely used release:
 *
 *    source                 png.h  png.h  shared-lib
 *    version                string   int  version
 *    -------                ------ -----  ----------
 *    0.89c "1.0 beta 3"     0.89      89  1.0.89
 *    0.90  "1.0 beta 4"     0.90      90  0.90  [should have been 2.0.90]
 *    0.95  "1.0 beta 5"     0.95      95  0.95  [should have been 2.0.95]
 *    0.96  "1.0 beta 6"     0.96      96  0.96  [should have been 2.0.96]
 *    0.97b "1.00.97 beta 7" 1.00.97   97  1.0.1 [should have been 2.0.97]
 *    0.97c                  0.97      97  2.0.97
 *    0.98                   0.98      98  2.0.98
 *    0.99                   0.99      98  2.0.99
 *    0.99a-m                0.99      99  2.0.99
 *    1.00                   1.00     100  2.1.0 [100 should be 10000]
 *    1.0.0      (from here on, the   100  2.1.0 [100 should be 10000]
 *    1.0.1       png.h string is   10001  2.1.0
 *    1.0.1a-e    identical to the  10002  from here on, the shared library
 *    1.0.2       source version)   10002  is 2.V where V is the source code
 *    1.0.2a-b                      10003  version, except as noted.
 *    1.0.3                         10003
 *    1.0.3a-d                      10004
 *    1.0.4                         10004
 *    1.0.4a-f                      10005
 *    1.0.5 (+ 2 patches)           10005
 *    1.0.5a-d                      10006
 *    1.0.5e-r                      10100 (not source compatible)
 *    1.0.5s-v                      10006 (not binary compatible)
 *    1.0.6 (+ 3 patches)           10006 (still binary incompatible)
 *    1.0.6d-f                      10007 (still binary incompatible)
 *    1.0.6g                        10007
 *    1.0.6h                        10007  10.6h (testing xy.z so-numbering)
 *    1.0.6i                        10007  10.6i
 *    1.0.6j                        10007  2.1.0.6j (incompatible with 1.0.0)
 *    1.0.7beta11-14        DLLNUM  10007  2.1.0.7beta11-14 (binary compatible)
 *    1.0.7beta15-18           1    10007  2.1.0.7beta15-18 (binary compatible)
 *    1.0.7rc1-2               1    10007  2.1.0.7rc1-2 (binary compatible)
 *    1.0.7                    1    10007  (still compatible)
 *    1.0.8beta1-4             1    10008  2.1.0.8beta1-4
 *    1.0.8rc1                 1    10008  2.1.0.8rc1
 *    1.0.8                    1    10008  2.1.0.8
 *    1.0.9beta1-6             1    10009  2.1.0.9beta1-6
 *    1.0.9rc1                 1    10009  2.1.0.9rc1
 *    1.0.9beta7-10            1    10009  2.1.0.9beta7-10
 *    1.0.9rc2                 1    10009  2.1.0.9rc2
 *    1.0.9                    1    10009  2.1.0.9
 *    1.0.10beta1              1    10010  2.1.0.10beta1
 *    1.0.10rc1                1    10010  2.1.0.10rc1
 *    1.0.10                   1    10010  2.1.0.10
 *    1.0.11beta1-3            1    10011  2.1.0.11beta1-3
 *    1.0.11rc1                1    10011  2.1.0.11rc1
 *    1.0.11                   1    10011  2.1.0.11
 *    1.0.12beta1-2            2    10012  2.1.0.12beta1-2
 *    1.0.12rc1                2    10012  2.1.0.12rc1
 *    1.0.12                   2    10012  2.1.0.12
 *    1.1.0a-f                 -    10100  2.1.1.0a-f (branch abandoned)
 *    1.2.0beta1-2             2    10200  2.1.2.0beta1-2
 *    1.2.0beta3-5             3    10200  3.1.2.0beta3-5
 *    1.2.0rc1                 3    10200  3.1.2.0rc1
 *    1.2.0                    3    10200  3.1.2.0
 *    1.2.1beta1-4             3    10201  3.1.2.1beta1-4
 *    1.2.1rc1-2               3    10201  3.1.2.1rc1-2
 *    1.2.1                    3    10201  3.1.2.1
 *    1.2.2beta1-6            12    10202  12.so.0.1.2.2beta1-6
 *    1.0.13beta1             10    10013  10.so.0.1.0.13beta1
 *    1.0.13rc1               10    10013  10.so.0.1.0.13rc1
 *    1.2.2rc1                12    10202  12.so.0.1.2.2rc1
 *    1.0.13                  10    10013  10.so.0.1.0.13
 *    1.2.2                   12    10202  12.so.0.1.2.2
 *    1.2.3rc1-6              12    10203  12.so.0.1.2.3rc1-6
 *    1.2.3                   12    10203  12.so.0.1.2.3
 *    1.2.4beta1-3            13    10204  12.so.0.1.2.4beta1-3
 *    1.0.14rc1               13    10014  10.so.0.1.0.14rc1
 *    1.2.4rc1                13    10204  12.so.0.1.2.4rc1
 *    1.0.14                  10    10014  10.so.0.1.0.14
 *    1.2.4                   13    10204  12.so.0.1.2.4
 *    1.2.5beta1-2            13    10205  12.so.0.1.2.5beta1-2
 *    1.0.15rc1-3             10    10015  10.so.0.1.0.15rc1-3
 *    1.2.5rc1-3              13    10205  12.so.0.1.2.5rc1-3
 *    1.0.15                  10    10015  10.so.0.1.0.15
 *    1.2.5                   13    10205  12.so.0.1.2.5
 *
 *    Henceforth the source version will match the shared-library major
 *    and minor numbers; the shared-library major version number will be
 *    used for changes in backward compatibility, as it is intended.  The
 *    PNG_LIBPNG_VER macro, which is not used within libpng but is available
 *    for applications, is an unsigned integer of the form xyyzz corresponding
 *    to the source version x.y.z (leading zeros in y and z).  Beta versions
 *    were given the previous public release number plus a letter, until
 *    version 1.0.6j; from then on they were given the upcoming public
 *    release number plus "betaNN" or "rcN".
 *
 *    Binary incompatibility exists only when applications make direct access
 *    to the info_ptr or xpng_ptr members through png.h, and the compiled
 *    application is loaded with a different version of the library.
 *
 *    DLLNUM will change each time there are forward or backward changes
 *    in binary compatibility (e.g., when a new feature is added).
 *
 * See libpng.txt or libpng.3 for more information.  The PNG specification
 * is available as RFC 2083 <ftp://ftp.uu.net/graphics/png/documents/>
 * and as a W3C Recommendation <http://www.w3.org/TR/REC.png.html>
 */

/*
 * COPYRIGHT NOTICE, DISCLAIMER, and LICENSE:
 *
 * If you modify libpng you may insert additional notices immediately following
 * this sentence.
 *
 * libpng versions 1.0.7, July 1, 2000, through 1.2.5, October 3, 2002, are
 * Copyright (c) 2000-2002 Glenn Randers-Pehrson, and are
 * distributed according to the same disclaimer and license as libpng-1.0.6
 * with the following individuals added to the list of Contributing Authors
 *
 *    Simon-Pierre Cadieux
 *    Eric S. Raymond
 *    Gilles Vollant
 *
 * and with the following additions to the disclaimer:
 *
 *    There is no warranty against interference with your enjoyment of the
 *    library or against infringement.  There is no warranty that our
 *    efforts or the library will fulfill any of your particular purposes
 *    or needs.  This library is provided with all faults, and the entire
 *    risk of satisfactory quality, performance, accuracy, and effort is with
 *    the user.
 *
 * libpng versions 0.97, January 1998, through 1.0.6, March 20, 2000, are
 * Copyright (c) 1998, 1999, 2000 Glenn Randers-Pehrson
 * Distributed according to the same disclaimer and license as libpng-0.96,
 * with the following individuals added to the list of Contributing Authors:
 *
 *    Tom Lane
 *    Glenn Randers-Pehrson
 *    Willem van Schaik
 *
 * libpng versions 0.89, June 1996, through 0.96, May 1997, are
 * Copyright (c) 1996, 1997 Andreas Dilger
 * Distributed according to the same disclaimer and license as libpng-0.88,
 * with the following individuals added to the list of Contributing Authors:
 *
 *    John Bowler
 *    Kevin Bracey
 *    Sam Bushell
 *    Magnus Holmgren
 *    Greg Roelofs
 *    Tom Tanner
 *
 * libpng versions 0.5, May 1995, through 0.88, January 1996, are
 * Copyright (c) 1995, 1996 Guy Eric Schalnat, Group 42, Inc.
 *
 * For the purposes of this copyright and license, "Contributing Authors"
 * is defined as the following set of individuals:
 *
 *    Andreas Dilger
 *    Dave Martindale
 *    Guy Eric Schalnat
 *    Paul Schmidt
 *    Tim Wegner
 *
 * The PNG Reference Library is supplied "AS IS".  The Contributing Authors
 * and Group 42, Inc. disclaim all warranties, expressed or implied,
 * including, without limitation, the warranties of merchantability and of
 * fitness for any purpose.  The Contributing Authors and Group 42, Inc.
 * assume no liability for direct, indirect, incidental, special, exemplary,
 * or consequential damages, which may result from the use of the PNG
 * Reference Library, even if advised of the possibility of such damage.
 *
 * Permission is hereby granted to use, copy, modify, and distribute this
 * source code, or portions hereof, for any purpose, without fee, subject
 * to the following restrictions:
 *
 * 1. The origin of this source code must not be misrepresented.
 *
 * 2. Altered versions must be plainly marked as such and
 * must not be misrepresented as being the original source.
 *
 * 3. This Copyright notice may not be removed or altered from
 *    any source or altered source distribution.
 *
 * The Contributing Authors and Group 42, Inc. specifically permit, without
 * fee, and encourage the use of this source code as a component to
 * supporting the PNG file format in commercial products.  If you use this
 * source code in a product, acknowledgment is not required but would be
 * appreciated.
 */

/*
 * A "xpng_get_copyright" function is available, for convenient use in "about"
 * boxes and the like:
 *
 * printf("%s",xpng_get_copyright(NULL));
 *
 * Also, the PNG logo (in PNG format, of course) is supplied in the
 * files "pngbar.png" and "pngbar.jpg (88x31) and "pngnow.png" (98x31).
 */

/*
 * Libpng is OSI Certified Open Source Software.  OSI Certified is a
 * certification mark of the Open Source Initiative.
 */

/*
 * The contributing authors would like to thank all those who helped
 * with testing, bug fixes, and patience.  This wouldn't have been
 * possible without all of you.
 *
 * Thanks to Frank J. T. Wojcik for helping with the documentation.
 */

/*
 * Y2K compliance in libpng:
 * =========================
 *
 *    October 3, 2002
 *
 *    Since the PNG Development group is an ad-hoc body, we can't make
 *    an official declaration.
 *
 *    This is your unofficial assurance that libpng from version 0.71 and
 *    upward through 1.2.5 are Y2K compliant.  It is my belief that earlier
 *    versions were also Y2K compliant.
 *
 *    Libpng only has three year fields.  One is a 2-byte unsigned integer
 *    that will hold years up to 65535.  The other two hold the date in text
 *    format, and will hold years up to 9999.
 *
 *    The integer is
 *        "xpng_uint_16 year" in xpng_time_struct.
 *
 *    The strings are
 *        "xpng_charp time_buffer" in xpng_struct and
 *        "near_time_buffer", which is a local character string in png.c.
 *
 *    There are seven time-related functions:
 *        png.c: xpng_convert_to_rfc_1123() in png.c
 *          (formerly xpng_convert_to_rfc_1152() in error)
 *        xpng_convert_from_struct_tm() in pngwrite.c, called in pngwrite.c
 *        xpng_convert_from_time_t() in pngwrite.c
 *        xpng_get_tIME() in pngget.c
 *        xpng_handle_tIME() in pngrutil.c, called in pngread.c
 *        xpng_set_tIME() in pngset.c
 *        xpng_write_tIME() in pngwutil.c, called in pngwrite.c
 *
 *    All handle dates properly in a Y2K environment.  The
 *    xpng_convert_from_time_t() function calls gmtime() to convert from system
 *    clock time, which returns (year - 1900), which we properly convert to
 *    the full 4-digit year.  There is a possibility that applications using
 *    libpng are not passing 4-digit years into the xpng_convert_to_rfc_1123()
 *    function, or that they are incorrectly passing only a 2-digit year
 *    instead of "year - 1900" into the xpng_convert_from_struct_tm() function,
 *    but this is not under our control.  The libpng documentation has always
 *    stated that it works with 4-digit years, and the APIs have been
 *    documented as such.
 *
 *    The tIME chunk itself is also Y2K compliant.  It uses a 2-byte unsigned
 *    integer to hold the year, and can hold years as large as 65535.
 *
 *    zlib, upon which libpng depends, is also Y2K compliant.  It contains
 *    no date-related code.
 *
 *       Glenn Randers-Pehrson
 *       libpng maintainer
 *       PNG Development Group
 */

#ifndef PNG_H
#define PNG_H

/* This is not the place to learn how to use libpng.  The file libpng.txt
 * describes how to use libpng, and the file example.c summarizes it
 * with some code on which to build.  This file is useful for looking
 * at the actual function definitions and structure components.
 */

/* Version information for png.h - this should match the version in png.c */
#define PNG_LIBPNG_VER_STRING "1.2.5"

#define PNG_LIBPNG_VER_SONUM   0
#define PNG_LIBPNG_VER_DLLNUM  %DLLNUM%

/* These should match the first 3 components of PNG_LIBPNG_VER_STRING: */
#define PNG_LIBPNG_VER_MAJOR   1
#define PNG_LIBPNG_VER_MINOR   2
#define PNG_LIBPNG_VER_RELEASE 5
/* This should match the numeric part of the final component of
 * PNG_LIBPNG_VER_STRING, omitting any leading zero: */

#define PNG_LIBPNG_VER_BUILD  0

#define PNG_LIBPNG_BUILD_ALPHA    1
#define PNG_LIBPNG_BUILD_BETA     2
#define PNG_LIBPNG_BUILD_RC       3
#define PNG_LIBPNG_BUILD_STABLE   4
#define PNG_LIBPNG_BUILD_TYPEMASK 7
#define PNG_LIBPNG_BUILD_PATCH    8 /* Can be OR'ed with STABLE only */
#define PNG_LIBPNG_BUILD_TYPE 4

/* Careful here.  At one time, Guy wanted to use 082, but that would be octal.
 * We must not include leading zeros.
 * Versions 0.7 through 1.0.0 were in the range 0 to 100 here (only
 * version 1.0.0 was mis-numbered 100 instead of 10000).  From
 * version 1.0.1 it's    xxyyzz, where x=major, y=minor, z=release */
#define PNG_LIBPNG_VER 10205 /* 1.2.5 */

#ifndef PNG_VERSION_INFO_ONLY

/* include the compression library's header */
#include "zlib.h"

/* include all user configurable info, including optional assembler routines */
#include "pngconf.h"

/* Inhibit C++ name-mangling for libpng functions but not for system calls. */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* This file is arranged in several sections.  The first section contains
 * structure and type definitions.  The second section contains the external
 * library functions, while the third has the internal library functions,
 * which applications aren't expected to use directly.
 */

#ifndef PNG_NO_TYPECAST_NULL
#define int_p_NULL                (int *)NULL
#define xpng_bytep_NULL            (xpng_bytep)NULL
#define xpng_bytepp_NULL           (xpng_bytepp)NULL
#define xpng_doublep_NULL          (xpng_doublep)NULL
#define xpng_error_ptr_NULL        (xpng_error_ptr)NULL
#define xpng_flush_ptr_NULL        (xpng_flush_ptr)NULL
#define xpng_free_ptr_NULL         (xpng_free_ptr)NULL
#define xpng_infopp_NULL           (xpng_infopp)NULL
#define xpng_malloc_ptr_NULL       (xpng_malloc_ptr)NULL
#define xpng_read_status_ptr_NULL  (xpng_read_status_ptr)NULL
#define xpng_rw_ptr_NULL           (xpng_rw_ptr)NULL
#define xpng_structp_NULL          (xpng_structp)NULL
#define xpng_uint_16p_NULL         (xpng_uint_16p)NULL
#define xpng_voidp_NULL            (xpng_voidp)NULL
#define xpng_write_status_ptr_NULL (xpng_write_status_ptr)NULL
#else
#define int_p_NULL                NULL
#define xpng_bytep_NULL            NULL
#define xpng_bytepp_NULL           NULL
#define xpng_doublep_NULL          NULL
#define xpng_error_ptr_NULL        NULL
#define xpng_flush_ptr_NULL        NULL
#define xpng_free_ptr_NULL         NULL
#define xpng_infopp_NULL           NULL
#define xpng_malloc_ptr_NULL       NULL
#define xpng_read_status_ptr_NULL  NULL
#define xpng_rw_ptr_NULL           NULL
#define xpng_structp_NULL          NULL
#define xpng_uint_16p_NULL         NULL
#define xpng_voidp_NULL            NULL
#define xpng_write_status_ptr_NULL NULL
#endif

/* variables declared in png.c - only it needs to define PNG_NO_EXTERN */
#if !defined(PNG_NO_EXTERN) || defined(PNG_ALWAYS_EXTERN)
/* Version information for C files, stored in png.c.  This had better match
 * the version above.
 */
#ifdef PNG_USE_GLOBAL_ARRAYS
PNG_EXPORT_VAR (const char) xpng_libxpng_ver[18];
  /* need room for 99.99.99beta99z */
#else
#define xpng_libxpng_ver xpng_get_header_ver(NULL)
#endif

#ifdef PNG_USE_GLOBAL_ARRAYS
/* This was removed in version 1.0.5c */
/* Structures to facilitate easy interlacing.  See png.c for more details */
PNG_EXPORT_VAR (const int FARDATA) xpng_pass_start[7];
PNG_EXPORT_VAR (const int FARDATA) xpng_pass_inc[7];
PNG_EXPORT_VAR (const int FARDATA) xpng_pass_ystart[7];
PNG_EXPORT_VAR (const int FARDATA) xpng_pass_yinc[7];
PNG_EXPORT_VAR (const int FARDATA) xpng_pass_mask[7];
PNG_EXPORT_VAR (const int FARDATA) xpng_pass_dsp_mask[7];
#ifdef PNG_HAVE_ASSEMBLER_COMBINE_ROW
PNG_EXPORT_VAR (const int FARDATA) xpng_pass_width[7];
#endif
/* This isn't currently used.  If you need it, see png.c for more details.
PNG_EXPORT_VAR (const int FARDATA) xpng_pass_height[7];
*/
#endif

#endif /* PNG_NO_EXTERN */

/* Three color definitions.  The order of the red, green, and blue, (and the
 * exact size) is not important, although the size of the fields need to
 * be xpng_byte or xpng_uint_16 (as defined below).
 */
typedef struct xpng_color_struct
{
   xpng_byte red;
   xpng_byte green;
   xpng_byte blue;
} xpng_color;
typedef xpng_color FAR * xpng_colorp;
typedef xpng_color FAR * FAR * xpng_colorpp;

typedef struct xpng_color_16_struct
{
   xpng_byte index;    /* used for palette files */
   xpng_uint_16 red;   /* for use in red green blue files */
   xpng_uint_16 green;
   xpng_uint_16 blue;
   xpng_uint_16 gray;  /* for use in grayscale files */
} xpng_color_16;
typedef xpng_color_16 FAR * xpng_color_16p;
typedef xpng_color_16 FAR * FAR * xpng_color_16pp;

typedef struct xpng_color_8_struct
{
   xpng_byte red;   /* for use in red green blue files */
   xpng_byte green;
   xpng_byte blue;
   xpng_byte gray;  /* for use in grayscale files */
   xpng_byte alpha; /* for alpha channel files */
} xpng_color_8;
typedef xpng_color_8 FAR * xpng_color_8p;
typedef xpng_color_8 FAR * FAR * xpng_color_8pp;

/*
 * The following two structures are used for the in-core representation
 * of sPLT chunks.
 */
typedef struct xpng_sPLT_entry_struct
{
   xpng_uint_16 red;
   xpng_uint_16 green;
   xpng_uint_16 blue;
   xpng_uint_16 alpha;
   xpng_uint_16 frequency;
} xpng_sPLT_entry;
typedef xpng_sPLT_entry FAR * xpng_sPLT_entryp;
typedef xpng_sPLT_entry FAR * FAR * xpng_sPLT_entrypp;

/*  When the depth of the sPLT palette is 8 bits, the color and alpha samples
 *  occupy the LSB of their respective members, and the MSB of each member
 *  is zero-filled.  The frequency member always occupies the full 16 bits.
 */

typedef struct xpng_sPLT_struct
{
   xpng_charp name;           /* palette name */
   xpng_byte depth;           /* depth of palette samples */
   xpng_sPLT_entryp entries;  /* palette entries */
   xpng_int_32 nentries;      /* number of palette entries */
} xpng_sPLT_t;
typedef xpng_sPLT_t FAR * xpng_sPLT_tp;
typedef xpng_sPLT_t FAR * FAR * xpng_sPLT_tpp;

#ifdef PNG_TEXT_SUPPORTED
/* xpng_text holds the contents of a text/ztxt/itxt chunk in a PNG file,
 * and whether that contents is compressed or not.  The "key" field
 * points to a regular zero-terminated C string.  The "text", "lang", and
 * "lang_key" fields can be regular C strings, empty strings, or NULL pointers.
 * However, the * structure returned by xpng_get_text() will always contain
 * regular zero-terminated C strings (possibly empty), never NULL pointers,
 * so they can be safely used in printf() and other string-handling functions.
 */
typedef struct xpng_text_struct
{
   int  compression;       /* compression value:
                             -1: tEXt, none
                              0: zTXt, deflate
                              1: iTXt, none
                              2: iTXt, deflate  */
   xpng_charp key;          /* keyword, 1-79 character description of "text" */
   xpng_charp text;         /* comment, may be an empty string (ie "")
                              or a NULL pointer */
   xpng_size_t text_length; /* length of the text string */
#ifdef PNG_iTXt_SUPPORTED
   xpng_size_t itxt_length; /* length of the itxt string */
   xpng_charp lang;         /* language code, 0-79 characters
                              or a NULL pointer */
   xpng_charp lang_key;     /* keyword translated UTF-8 string, 0 or more
                              chars or a NULL pointer */
#endif
} xpng_text;
typedef xpng_text FAR * xpng_textp;
typedef xpng_text FAR * FAR * xpng_textpp;
#endif

/* Supported compression types for text in PNG files (tEXt, and zTXt).
 * The values of the PNG_TEXT_COMPRESSION_ defines should NOT be changed. */
#define PNG_TEXT_COMPRESSION_NONE_WR -3
#define PNG_TEXT_COMPRESSION_zTXt_WR -2
#define PNG_TEXT_COMPRESSION_NONE    -1
#define PNG_TEXT_COMPRESSION_zTXt     0
#define PNG_ITXT_COMPRESSION_NONE     1
#define PNG_ITXT_COMPRESSION_zTXt     2
#define PNG_TEXT_COMPRESSION_LAST     3  /* Not a valid value */

/* xpng_time is a way to hold the time in an machine independent way.
 * Two conversions are provided, both from time_t and struct tm.  There
 * is no portable way to convert to either of these structures, as far
 * as I know.  If you know of a portable way, send it to me.  As a side
 * note - PNG has always been Year 2000 compliant!
 */
typedef struct xpng_time_struct
{
   xpng_uint_16 year; /* full year, as in, 1995 */
   xpng_byte month;   /* month of year, 1 - 12 */
   xpng_byte day;     /* day of month, 1 - 31 */
   xpng_byte hour;    /* hour of day, 0 - 23 */
   xpng_byte minute;  /* minute of hour, 0 - 59 */
   xpng_byte second;  /* second of minute, 0 - 60 (for leap seconds) */
} xpng_time;
typedef xpng_time FAR * xpng_timep;
typedef xpng_time FAR * FAR * xpng_timepp;

#if defined(PNG_UNKNOWN_CHUNKS_SUPPORTED)
/* xpng_unknown_chunk is a structure to hold queued chunks for which there is
 * no specific support.  The idea is that we can use this to queue
 * up private chunks for output even though the library doesn't actually
 * know about their semantics.
 */
typedef struct xpng_unknown_chunk_t
{
    xpng_byte name[5];
    xpng_byte *data;
    xpng_size_t size;

    /* libpng-using applications should NOT directly modify this byte. */
    xpng_byte location; /* mode of operation at read time */
}
xpng_unknown_chunk;
typedef xpng_unknown_chunk FAR * xpng_unknown_chunkp;
typedef xpng_unknown_chunk FAR * FAR * xpng_unknown_chunkpp;
#endif

/* xpng_info is a structure that holds the information in a PNG file so
 * that the application can find out the characteristics of the image.
 * If you are reading the file, this structure will tell you what is
 * in the PNG file.  If you are writing the file, fill in the information
 * you want to put into the PNG file, then call xpng_write_info().
 * The names chosen should be very close to the PNG specification, so
 * consult that document for information about the meaning of each field.
 *
 * With libpng < 0.95, it was only possible to directly set and read the
 * the values in the xpng_info_struct, which meant that the contents and
 * order of the values had to remain fixed.  With libpng 0.95 and later,
 * however, there are now functions that abstract the contents of
 * xpng_info_struct from the application, so this makes it easier to use
 * libpng with dynamic libraries, and even makes it possible to use
 * libraries that don't have all of the libpng ancillary chunk-handing
 * functionality.
 *
 * In any case, the order of the parameters in xpng_info_struct should NOT
 * be changed for as long as possible to keep compatibility with applications
 * that use the old direct-access method with xpng_info_struct.
 *
 * The following members may have allocated storage attached that should be
 * cleaned up before the structure is discarded: palette, trans, text,
 * pcal_purpose, pcal_units, pcal_params, hist, iccp_name, iccp_profile,
 * splt_palettes, scal_unit, row_pointers, and unknowns.   By default, these
 * are automatically freed when the info structure is deallocated, if they were
 * allocated internally by libpng.  This behavior can be changed by means
 * of the xpng_data_freer() function.
 *
 * More allocation details: all the chunk-reading functions that
 * change these members go through the corresponding xpng_set_*
 * functions.  A function to clear these members is available: see
 * xpng_free_data().  The xpng_set_* functions do not depend on being
 * able to point info structure members to any of the storage they are
 * passed (they make their own copies), EXCEPT that the xpng_set_text
 * functions use the same storage passed to them in the text_ptr or
 * itxt_ptr structure argument, and the xpng_set_rows and xpng_set_unknowns
 * functions do not make their own copies.
 */
typedef struct xpng_info_struct
{
   /* the following are necessary for every PNG file */
   xpng_uint_32 width;       /* width of image in pixels (from IHDR) */
   xpng_uint_32 height;      /* height of image in pixels (from IHDR) */
   xpng_uint_32 valid;       /* valid chunk data (see PNG_INFO_ below) */
   xpng_uint_32 rowbytes;    /* bytes needed to hold an untransformed row */
   xpng_colorp palette;      /* array of color values (valid & PNG_INFO_PLTE) */
   xpng_uint_16 num_palette; /* number of color entries in "palette" (PLTE) */
   xpng_uint_16 num_trans;   /* number of transparent palette color (tRNS) */
   xpng_byte bit_depth;      /* 1, 2, 4, 8, or 16 bits/channel (from IHDR) */
   xpng_byte color_type;     /* see PNG_COLOR_TYPE_ below (from IHDR) */
   /* The following three should have been named *_method not *_type */
   xpng_byte compression_type; /* must be PNG_COMPRESSION_TYPE_BASE (IHDR) */
   xpng_byte filter_type;    /* must be PNG_FILTER_TYPE_BASE (from IHDR) */
   xpng_byte interlace_type; /* One of PNG_INTERLACE_NONE, PNG_INTERLACE_ADAM7 */

   /* The following is informational only on read, and not used on writes. */
   xpng_byte channels;       /* number of data channels per pixel (1, 2, 3, 4) */
   xpng_byte pixel_depth;    /* number of bits per pixel */
   xpng_byte spare_byte;     /* to align the data, and for future use */
   xpng_byte signature[8];   /* magic bytes read by libpng from start of file */

   /* The rest of the data is optional.  If you are reading, check the
    * valid field to see if the information in these are valid.  If you
    * are writing, set the valid field to those chunks you want written,
    * and initialize the appropriate fields below.
    */

#if defined(PNG_gAMA_SUPPORTED) && defined(PNG_FLOATING_POINT_SUPPORTED)
   /* The gAMA chunk describes the gamma characteristics of the system
    * on which the image was created, normally in the range [1.0, 2.5].
    * Data is valid if (valid & PNG_INFO_gAMA) is non-zero.
    */
   float gamma; /* gamma value of image, if (valid & PNG_INFO_gAMA) */
#endif

#if defined(PNG_sRGB_SUPPORTED)
    /* GR-P, 0.96a */
    /* Data valid if (valid & PNG_INFO_sRGB) non-zero. */
   xpng_byte srgb_intent; /* sRGB rendering intent [0, 1, 2, or 3] */
#endif

#if defined(PNG_TEXT_SUPPORTED)
   /* The tEXt, and zTXt chunks contain human-readable textual data in
    * uncompressed, compressed, and optionally compressed forms, respectively.
    * The data in "text" is an array of pointers to uncompressed,
    * null-terminated C strings. Each chunk has a keyword that describes the
    * textual data contained in that chunk.  Keywords are not required to be
    * unique, and the text string may be empty.  Any number of text chunks may
    * be in an image.
    */
   int num_text; /* number of comments read/to write */
   int max_text; /* current size of text array */
   xpng_textp text; /* array of comments read/to write */
#endif /* PNG_TEXT_SUPPORTED */

#if defined(PNG_tIME_SUPPORTED)
   /* The tIME chunk holds the last time the displayed image data was
    * modified.  See the xpng_time struct for the contents of this struct.
    */
   xpng_time mod_time;
#endif

#if defined(PNG_sBIT_SUPPORTED)
   /* The sBIT chunk specifies the number of significant high-order bits
    * in the pixel data.  Values are in the range [1, bit_depth], and are
    * only specified for the channels in the pixel data.  The contents of
    * the low-order bits is not specified.  Data is valid if
    * (valid & PNG_INFO_sBIT) is non-zero.
    */
   xpng_color_8 sig_bit; /* significant bits in color channels */
#endif

#if defined(PNG_tRNS_SUPPORTED) || defined(PNG_READ_EXPAND_SUPPORTED) || \
defined(PNG_READ_BACKGROUND_SUPPORTED)
   /* The tRNS chunk supplies transparency data for paletted images and
    * other image types that don't need a full alpha channel.  There are
    * "num_trans" transparency values for a paletted image, stored in the
    * same order as the palette colors, starting from index 0.  Values
    * for the data are in the range [0, 255], ranging from fully transparent
    * to fully opaque, respectively.  For non-paletted images, there is a
    * single color specified that should be treated as fully transparent.
    * Data is valid if (valid & PNG_INFO_tRNS) is non-zero.
    */
   xpng_bytep trans; /* transparent values for paletted image */
   xpng_color_16 trans_values; /* transparent color for non-palette image */
#endif

#if defined(PNG_bKGD_SUPPORTED) || defined(PNG_READ_BACKGROUND_SUPPORTED)
   /* The bKGD chunk gives the suggested image background color if the
    * display program does not have its own background color and the image
    * is needs to composited onto a background before display.  The colors
    * in "background" are normally in the same color space/depth as the
    * pixel data.  Data is valid if (valid & PNG_INFO_bKGD) is non-zero.
    */
   xpng_color_16 background;
#endif

#if defined(PNG_oFFs_SUPPORTED)
   /* The oFFs chunk gives the offset in "offset_unit_type" units rightwards
    * and downwards from the top-left corner of the display, page, or other
    * application-specific co-ordinate space.  See the PNG_OFFSET_ defines
    * below for the unit types.  Valid if (valid & PNG_INFO_oFFs) non-zero.
    */
   xpng_int_32 x_offset; /* x offset on page */
   xpng_int_32 y_offset; /* y offset on page */
   xpng_byte offset_unit_type; /* offset units type */
#endif

#if defined(PNG_pHYs_SUPPORTED)
   /* The pHYs chunk gives the physical pixel density of the image for
    * display or printing in "phys_unit_type" units (see PNG_RESOLUTION_
    * defines below).  Data is valid if (valid & PNG_INFO_pHYs) is non-zero.
    */
   xpng_uint_32 x_pixels_per_unit; /* horizontal pixel density */
   xpng_uint_32 y_pixels_per_unit; /* vertical pixel density */
   xpng_byte phys_unit_type; /* resolution type (see PNG_RESOLUTION_ below) */
#endif

#if defined(PNG_hIST_SUPPORTED)
   /* The hIST chunk contains the relative frequency or importance of the
    * various palette entries, so that a viewer can intelligently select a
    * reduced-color palette, if required.  Data is an array of "num_palette"
    * values in the range [0,65535]. Data valid if (valid & PNG_INFO_hIST)
    * is non-zero.
    */
   xpng_uint_16p hist;
#endif

#ifdef PNG_cHRM_SUPPORTED
   /* The cHRM chunk describes the CIE color characteristics of the monitor
    * on which the PNG was created.  This data allows the viewer to do gamut
    * mapping of the input image to ensure that the viewer sees the same
    * colors in the image as the creator.  Values are in the range
    * [0.0, 0.8].  Data valid if (valid & PNG_INFO_cHRM) non-zero.
    */
#ifdef PNG_FLOATING_POINT_SUPPORTED
   float x_white;
   float y_white;
   float x_red;
   float y_red;
   float x_green;
   float y_green;
   float x_blue;
   float y_blue;
#endif
#endif

#if defined(PNG_pCAL_SUPPORTED)
   /* The pCAL chunk describes a transformation between the stored pixel
    * values and original physical data values used to create the image.
    * The integer range [0, 2^bit_depth - 1] maps to the floating-point
    * range given by [pcal_X0, pcal_X1], and are further transformed by a
    * (possibly non-linear) transformation function given by "pcal_type"
    * and "pcal_params" into "pcal_units".  Please see the PNG_EQUATION_
    * defines below, and the PNG-Group's PNG extensions document for a
    * complete description of the transformations and how they should be
    * implemented, and for a description of the ASCII parameter strings.
    * Data values are valid if (valid & PNG_INFO_pCAL) non-zero.
    */
   xpng_charp pcal_purpose;  /* pCAL chunk description string */
   xpng_int_32 pcal_X0;      /* minimum value */
   xpng_int_32 pcal_X1;      /* maximum value */
   xpng_charp pcal_units;    /* Latin-1 string giving physical units */
   xpng_charpp pcal_params;  /* ASCII strings containing parameter values */
   xpng_byte pcal_type;      /* equation type (see PNG_EQUATION_ below) */
   xpng_byte pcal_nparams;   /* number of parameters given in pcal_params */
#endif

/* New members added in libpng-1.0.6 */
#ifdef PNG_FREE_ME_SUPPORTED
   xpng_uint_32 free_me;     /* flags items libpng is responsible for freeing */
#endif

#if defined(PNG_UNKNOWN_CHUNKS_SUPPORTED)
   /* storage for unknown chunks that the library doesn't recognize. */
   xpng_unknown_chunkp unknown_chunks;
   xpng_size_t unknown_chunks_num;
#endif

#if defined(PNG_iCCP_SUPPORTED)
   /* iCCP chunk data. */
   xpng_charp iccp_name;     /* profile name */
   xpng_charp iccp_profile;  /* International Color Consortium profile data */
                            /* Note to maintainer: should be xpng_bytep */
   xpng_uint_32 iccp_proflen;  /* ICC profile data length */
   xpng_byte iccp_compression; /* Always zero */
#endif

#if defined(PNG_sPLT_SUPPORTED)
   /* data on sPLT chunks (there may be more than one). */
   xpng_sPLT_tp splt_palettes;
   xpng_uint_32 splt_palettes_num;
#endif

#if defined(PNG_sCAL_SUPPORTED)
   /* The sCAL chunk describes the actual physical dimensions of the
    * subject matter of the graphic.  The chunk contains a unit specification
    * a byte value, and two ASCII strings representing floating-point
    * values.  The values are width and height corresponsing to one pixel
    * in the image.  This external representation is converted to double
    * here.  Data values are valid if (valid & PNG_INFO_sCAL) is non-zero.
    */
   xpng_byte scal_unit;         /* unit of physical scale */
#ifdef PNG_FLOATING_POINT_SUPPORTED
   double scal_pixel_width;    /* width of one pixel */
   double scal_pixel_height;   /* height of one pixel */
#endif
#ifdef PNG_FIXED_POINT_SUPPORTED
   xpng_charp scal_s_width;     /* string containing height */
   xpng_charp scal_s_height;    /* string containing width */
#endif
#endif

#if defined(PNG_INFO_IMAGE_SUPPORTED)
   /* Memory has been allocated if (valid & PNG_ALLOCATED_INFO_ROWS) non-zero */
   /* Data valid if (valid & PNG_INFO_IDAT) non-zero */
   xpng_bytepp row_pointers;        /* the image bits */
#endif

#if defined(PNG_FIXED_POINT_SUPPORTED) && defined(PNG_gAMA_SUPPORTED)
   xpng_fixed_point int_gamma; /* gamma of image, if (valid & PNG_INFO_gAMA) */
#endif

#if defined(PNG_cHRM_SUPPORTED) && defined(PNG_FIXED_POINT_SUPPORTED)
   xpng_fixed_point int_x_white;
   xpng_fixed_point int_y_white;
   xpng_fixed_point int_x_red;
   xpng_fixed_point int_y_red;
   xpng_fixed_point int_x_green;
   xpng_fixed_point int_y_green;
   xpng_fixed_point int_x_blue;
   xpng_fixed_point int_y_blue;
#endif

} xpng_info;

typedef xpng_info FAR * xpng_infop;
typedef xpng_info FAR * FAR * xpng_infopp;

/* Maximum positive integer used in PNG is (2^31)-1 */
#define PNG_MAX_UINT ((xpng_uint_32)0x7fffffffL)

/* These describe the color_type field in xpng_info. */
/* color type masks */
#define PNG_COLOR_MASK_PALETTE    1
#define PNG_COLOR_MASK_COLOR      2
#define PNG_COLOR_MASK_ALPHA      4

/* color types.  Note that not all combinations are legal */
#define PNG_COLOR_TYPE_GRAY 0
#define PNG_COLOR_TYPE_PALETTE  (PNG_COLOR_MASK_COLOR | PNG_COLOR_MASK_PALETTE)
#define PNG_COLOR_TYPE_RGB        (PNG_COLOR_MASK_COLOR)
#define PNG_COLOR_TYPE_RGB_ALPHA  (PNG_COLOR_MASK_COLOR | PNG_COLOR_MASK_ALPHA)
#define PNG_COLOR_TYPE_GRAY_ALPHA (PNG_COLOR_MASK_ALPHA)
/* aliases */
#define PNG_COLOR_TYPE_RGBA  PNG_COLOR_TYPE_RGB_ALPHA
#define PNG_COLOR_TYPE_GA  PNG_COLOR_TYPE_GRAY_ALPHA

/* This is for compression type. PNG 1.0-1.2 only define the single type. */
#define PNG_COMPRESSION_TYPE_BASE 0 /* Deflate method 8, 32K window */
#define PNG_COMPRESSION_TYPE_DEFAULT PNG_COMPRESSION_TYPE_BASE

/* This is for filter type. PNG 1.0-1.2 only define the single type. */
#define PNG_FILTER_TYPE_BASE      0 /* Single row per-byte filtering */
#define PNG_INTRAPIXEL_DIFFERENCING 64 /* Used only in MNG datastreams */
#define PNG_FILTER_TYPE_DEFAULT   PNG_FILTER_TYPE_BASE

/* These are for the interlacing type.  These values should NOT be changed. */
#define PNG_INTERLACE_NONE        0 /* Non-interlaced image */
#define PNG_INTERLACE_ADAM7       1 /* Adam7 interlacing */
#define PNG_INTERLACE_LAST        2 /* Not a valid value */

/* These are for the oFFs chunk.  These values should NOT be changed. */
#define PNG_OFFSET_PIXEL          0 /* Offset in pixels */
#define PNG_OFFSET_MICROMETER     1 /* Offset in micrometers (1/10^6 meter) */
#define PNG_OFFSET_LAST           2 /* Not a valid value */

/* These are for the pCAL chunk.  These values should NOT be changed. */
#define PNG_EQUATION_LINEAR       0 /* Linear transformation */
#define PNG_EQUATION_BASE_E       1 /* Exponential base e transform */
#define PNG_EQUATION_ARBITRARY    2 /* Arbitrary base exponential transform */
#define PNG_EQUATION_HYPERBOLIC   3 /* Hyperbolic sine transformation */
#define PNG_EQUATION_LAST         4 /* Not a valid value */

/* These are for the sCAL chunk.  These values should NOT be changed. */
#define PNG_SCALE_UNKNOWN         0 /* unknown unit (image scale) */
#define PNG_SCALE_METER           1 /* meters per pixel */
#define PNG_SCALE_RADIAN          2 /* radians per pixel */
#define PNG_SCALE_LAST            3 /* Not a valid value */

/* These are for the pHYs chunk.  These values should NOT be changed. */
#define PNG_RESOLUTION_UNKNOWN    0 /* pixels/unknown unit (aspect ratio) */
#define PNG_RESOLUTION_METER      1 /* pixels/meter */
#define PNG_RESOLUTION_LAST       2 /* Not a valid value */

/* These are for the sRGB chunk.  These values should NOT be changed. */
#define PNG_sRGB_INTENT_PERCEPTUAL 0
#define PNG_sRGB_INTENT_RELATIVE   1
#define PNG_sRGB_INTENT_SATURATION 2
#define PNG_sRGB_INTENT_ABSOLUTE   3
#define PNG_sRGB_INTENT_LAST       4 /* Not a valid value */

/* This is for text chunks */
#define PNG_KEYWORD_MAX_LENGTH     79

/* Maximum number of entries in PLTE/sPLT/tRNS arrays */
#define PNG_MAX_PALETTE_LENGTH    256

/* These determine if an ancillary chunk's data has been successfully read
 * from the PNG header, or if the application has filled in the corresponding
 * data in the info_struct to be written into the output file.  The values
 * of the PNG_INFO_<chunk> defines should NOT be changed.
 */
#define PNG_INFO_gAMA 0x0001
#define PNG_INFO_sBIT 0x0002
#define PNG_INFO_cHRM 0x0004
#define PNG_INFO_PLTE 0x0008
#define PNG_INFO_tRNS 0x0010
#define PNG_INFO_bKGD 0x0020
#define PNG_INFO_hIST 0x0040
#define PNG_INFO_pHYs 0x0080
#define PNG_INFO_oFFs 0x0100
#define PNG_INFO_tIME 0x0200
#define PNG_INFO_pCAL 0x0400
#define PNG_INFO_sRGB 0x0800   /* GR-P, 0.96a */
#define PNG_INFO_iCCP 0x1000   /* ESR, 1.0.6 */
#define PNG_INFO_sPLT 0x2000   /* ESR, 1.0.6 */
#define PNG_INFO_sCAL 0x4000   /* ESR, 1.0.6 */
#define PNG_INFO_IDAT 0x8000L  /* ESR, 1.0.6 */

/* This is used for the transformation routines, as some of them
 * change these values for the row.  It also should enable using
 * the routines for other purposes.
 */
typedef struct xpng_row_info_struct
{
   xpng_uint_32 width; /* width of row */
   xpng_uint_32 rowbytes; /* number of bytes in row */
   xpng_byte color_type; /* color type of row */
   xpng_byte bit_depth; /* bit depth of row */
   xpng_byte channels; /* number of channels (1, 2, 3, or 4) */
   xpng_byte pixel_depth; /* bits per pixel (depth * channels) */
} xpng_row_info;

typedef xpng_row_info FAR * xpng_row_infop;
typedef xpng_row_info FAR * FAR * xpng_row_infopp;

/* These are the function types for the I/O functions and for the functions
 * that allow the user to override the default I/O functions with his or her
 * own.  The xpng_error_ptr type should match that of user-supplied warning
 * and error functions, while the xpng_rw_ptr type should match that of the
 * user read/write data functions.
 */
typedef struct xpng_struct_def xpng_struct;
typedef xpng_struct FAR * xpng_structp;

typedef void (PNGAPI *xpng_error_ptr) PNGARG((xpng_structp, xpng_const_charp));
typedef void (PNGAPI *xpng_rw_ptr) PNGARG((xpng_structp, xpng_bytep, xpng_size_t));
typedef void (PNGAPI *xpng_flush_ptr) PNGARG((xpng_structp));
typedef void (PNGAPI *xpng_read_status_ptr) PNGARG((xpng_structp, xpng_uint_32,
   int));
typedef void (PNGAPI *xpng_write_status_ptr) PNGARG((xpng_structp, xpng_uint_32,
   int));

#ifdef PNG_PROGRESSIVE_READ_SUPPORTED
typedef void (PNGAPI *xpng_progressive_info_ptr) PNGARG((xpng_structp, xpng_infop));
typedef void (PNGAPI *xpng_progressive_end_ptr) PNGARG((xpng_structp, xpng_infop));
typedef void (PNGAPI *xpng_progressive_row_ptr) PNGARG((xpng_structp, xpng_bytep,
   xpng_uint_32, int));
#endif

#if defined(PNG_READ_USER_TRANSFORM_SUPPORTED) || \
    defined(PNG_WRITE_USER_TRANSFORM_SUPPORTED) || \
    defined(PNG_LEGACY_SUPPORTED)
typedef void (PNGAPI *xpng_user_transform_ptr) PNGARG((xpng_structp,
    xpng_row_infop, xpng_bytep));
#endif

#if defined(PNG_USER_CHUNKS_SUPPORTED)
typedef int (PNGAPI *xpng_user_chunk_ptr) PNGARG((xpng_structp, xpng_unknown_chunkp));
#endif
#if defined(PNG_UNKNOWN_CHUNKS_SUPPORTED)
typedef void (PNGAPI *xpng_unknown_chunk_ptr) PNGARG((xpng_structp));
#endif

/* Transform masks for the high-level interface */
#define PNG_TRANSFORM_IDENTITY       0x0000    /* read and write */
#define PNG_TRANSFORM_STRIP_16       0x0001    /* read only */
#define PNG_TRANSFORM_STRIP_ALPHA    0x0002    /* read only */
#define PNG_TRANSFORM_PACKING        0x0004    /* read and write */
#define PNG_TRANSFORM_PACKSWAP       0x0008    /* read and write */
#define PNG_TRANSFORM_EXPAND         0x0010    /* read only */
#define PNG_TRANSFORM_INVERT_MONO    0x0020    /* read and write */
#define PNG_TRANSFORM_SHIFT          0x0040    /* read and write */
#define PNG_TRANSFORM_BGR            0x0080    /* read and write */
#define PNG_TRANSFORM_SWAP_ALPHA     0x0100    /* read and write */
#define PNG_TRANSFORM_SWAP_ENDIAN    0x0200    /* read and write */
#define PNG_TRANSFORM_INVERT_ALPHA   0x0400    /* read and write */
#define PNG_TRANSFORM_STRIP_FILLER   0x0800    /* WRITE only */

/* Flags for MNG supported features */
#define PNG_FLAG_MNG_EMPTY_PLTE     0x01
#define PNG_FLAG_MNG_FILTER_64      0x04
#define PNG_ALL_MNG_FEATURES        0x05

typedef xpng_voidp (*xpng_malloc_ptr) PNGARG((xpng_structp, xpng_size_t));
typedef void (*xpng_free_ptr) PNGARG((xpng_structp, xpng_voidp));

/* The structure that holds the information to read and write PNG files.
 * The only people who need to care about what is inside of this are the
 * people who will be modifying the library for their own special needs.
 * It should NOT be accessed directly by an application, except to store
 * the jmp_buf.
 */

struct xpng_struct_def
{
#ifdef PNG_SETJMP_SUPPORTED
   jmp_buf jmpbuf;            /* used in xpng_error */
#endif
   xpng_error_ptr error_fn;    /* function for printing errors and aborting */
   xpng_error_ptr warning_fn;  /* function for printing warnings */
   xpng_voidp error_ptr;       /* user supplied struct for error functions */
   xpng_rw_ptr write_data_fn;  /* function for writing output data */
   xpng_rw_ptr read_data_fn;   /* function for reading input data */
   xpng_voidp io_ptr;          /* ptr to application struct for I/O functions */

#if defined(PNG_READ_USER_TRANSFORM_SUPPORTED)
   xpng_user_transform_ptr read_user_transform_fn; /* user read transform */
#endif

#if defined(PNG_WRITE_USER_TRANSFORM_SUPPORTED)
   xpng_user_transform_ptr write_user_transform_fn; /* user write transform */
#endif

/* These were added in libpng-1.0.2 */
#if defined(PNG_USER_TRANSFORM_PTR_SUPPORTED)
#if defined(PNG_READ_USER_TRANSFORM_SUPPORTED) || \
    defined(PNG_WRITE_USER_TRANSFORM_SUPPORTED)
   xpng_voidp user_transform_ptr; /* user supplied struct for user transform */
   xpng_byte user_transform_depth;    /* bit depth of user transformed pixels */
   xpng_byte user_transform_channels; /* channels in user transformed pixels */
#endif
#endif

   xpng_uint_32 mode;          /* tells us where we are in the PNG file */
   xpng_uint_32 flags;         /* flags indicating various things to libpng */
   xpng_uint_32 transformations; /* which transformations to perform */

   z_stream zstream;          /* pointer to decompression structure (below) */
   xpng_bytep zbuf;            /* buffer for zlib */
   xpng_size_t zbuf_size;      /* size of zbuf */
   int zlib_level;            /* holds zlib compression level */
   int zlib_method;           /* holds zlib compression method */
   int zlib_window_bits;      /* holds zlib compression window bits */
   int zlib_mem_level;        /* holds zlib compression memory level */
   int zlib_strategy;         /* holds zlib compression strategy */

   xpng_uint_32 width;         /* width of image in pixels */
   xpng_uint_32 height;        /* height of image in pixels */
   xpng_uint_32 num_rows;      /* number of rows in current pass */
   xpng_uint_32 usr_width;     /* width of row at start of write */
   xpng_uint_32 rowbytes;      /* size of row in bytes */
   xpng_uint_32 irowbytes;     /* size of current interlaced row in bytes */
   xpng_uint_32 iwidth;        /* width of current interlaced row in pixels */
   xpng_uint_32 row_number;    /* current row in interlace pass */
   xpng_bytep prev_row;        /* buffer to save previous (unfiltered) row */
   xpng_bytep row_buf;         /* buffer to save current (unfiltered) row */
   xpng_bytep sub_row;         /* buffer to save "sub" row when filtering */
   xpng_bytep up_row;          /* buffer to save "up" row when filtering */
   xpng_bytep avg_row;         /* buffer to save "avg" row when filtering */
   xpng_bytep paeth_row;       /* buffer to save "Paeth" row when filtering */
   xpng_row_info row_info;     /* used for transformation routines */

   xpng_uint_32 idat_size;     /* current IDAT size for read */
   xpng_uint_32 crc;           /* current chunk CRC value */
   xpng_colorp palette;        /* palette from the input file */
   xpng_uint_16 num_palette;   /* number of color entries in palette */
   xpng_uint_16 num_trans;     /* number of transparency values */
   xpng_byte chunk_name[5];    /* null-terminated name of current chunk */
   xpng_byte compression;      /* file compression type (always 0) */
   xpng_byte filter;           /* file filter type (always 0) */
   xpng_byte interlaced;       /* PNG_INTERLACE_NONE, PNG_INTERLACE_ADAM7 */
   xpng_byte pass;             /* current interlace pass (0 - 6) */
   xpng_byte do_filter;        /* row filter flags (see PNG_FILTER_ below ) */
   xpng_byte color_type;       /* color type of file */
   xpng_byte bit_depth;        /* bit depth of file */
   xpng_byte usr_bit_depth;    /* bit depth of users row */
   xpng_byte pixel_depth;      /* number of bits per pixel */
   xpng_byte channels;         /* number of channels in file */
   xpng_byte usr_channels;     /* channels at start of write */
   xpng_byte sig_bytes;        /* magic bytes read/written from start of file */

#if defined(PNG_READ_FILLER_SUPPORTED) || defined(PNG_WRITE_FILLER_SUPPORTED)
#ifdef PNG_LEGACY_SUPPORTED
   xpng_byte filler;           /* filler byte for pixel expansion */
#else
   xpng_uint_16 filler;           /* filler bytes for pixel expansion */
#endif
#endif

#if defined(PNG_bKGD_SUPPORTED)
   xpng_byte background_gamma_type;
#  ifdef PNG_FLOATING_POINT_SUPPORTED
   float background_gamma;
#  endif
   xpng_color_16 background;   /* background color in screen gamma space */
#if defined(PNG_READ_GAMMA_SUPPORTED)
   xpng_color_16 background_1; /* background normalized to gamma 1.0 */
#endif
#endif /* PNG_bKGD_SUPPORTED */

#if defined(PNG_WRITE_FLUSH_SUPPORTED)
   xpng_flush_ptr output_flush_fn;/* Function for flushing output */
   xpng_uint_32 flush_dist;    /* how many rows apart to flush, 0 - no flush */
   xpng_uint_32 flush_rows;    /* number of rows written since last flush */
#endif

#if defined(PNG_READ_GAMMA_SUPPORTED) || defined(PNG_READ_BACKGROUND_SUPPORTED)
   int gamma_shift;      /* number of "insignificant" bits 16-bit gamma */
#ifdef PNG_FLOATING_POINT_SUPPORTED
   float gamma;          /* file gamma value */
   float screen_gamma;   /* screen gamma value (display_exponent) */
#endif
#endif

#if defined(PNG_READ_GAMMA_SUPPORTED) || defined(PNG_READ_BACKGROUND_SUPPORTED)
   xpng_bytep gamma_table;     /* gamma table for 8-bit depth files */
   xpng_bytep gamma_from_1;    /* converts from 1.0 to screen */
   xpng_bytep gamma_to_1;      /* converts from file to 1.0 */
   xpng_uint_16pp gamma_16_table; /* gamma table for 16-bit depth files */
   xpng_uint_16pp gamma_16_from_1; /* converts from 1.0 to screen */
   xpng_uint_16pp gamma_16_to_1; /* converts from file to 1.0 */
#endif

#if defined(PNG_READ_GAMMA_SUPPORTED) || defined(PNG_sBIT_SUPPORTED)
   xpng_color_8 sig_bit;       /* significant bits in each available channel */
#endif

#if defined(PNG_READ_SHIFT_SUPPORTED) || defined(PNG_WRITE_SHIFT_SUPPORTED)
   xpng_color_8 shift;         /* shift for significant bit tranformation */
#endif

#if defined(PNG_tRNS_SUPPORTED) || defined(PNG_READ_BACKGROUND_SUPPORTED) \
 || defined(PNG_READ_EXPAND_SUPPORTED) || defined(PNG_READ_BACKGROUND_SUPPORTED)
   xpng_bytep trans;           /* transparency values for paletted files */
   xpng_color_16 trans_values; /* transparency values for non-paletted files */
#endif

   xpng_read_status_ptr read_row_fn;   /* called after each row is decoded */
   xpng_write_status_ptr write_row_fn; /* called after each row is encoded */
#ifdef PNG_PROGRESSIVE_READ_SUPPORTED
   xpng_progressive_info_ptr info_fn; /* called after header data fully read */
   xpng_progressive_row_ptr row_fn;   /* called after each prog. row is decoded */
   xpng_progressive_end_ptr end_fn;   /* called after image is complete */
   xpng_bytep save_buffer_ptr;        /* current location in save_buffer */
   xpng_bytep save_buffer;            /* buffer for previously read data */
   xpng_bytep current_buffer_ptr;     /* current location in current_buffer */
   xpng_bytep current_buffer;         /* buffer for recently used data */
   xpng_uint_32 push_length;          /* size of current input chunk */
   xpng_uint_32 skip_length;          /* bytes to skip in input data */
   xpng_size_t save_buffer_size;      /* amount of data now in save_buffer */
   xpng_size_t save_buffer_max;       /* total size of save_buffer */
   xpng_size_t buffer_size;           /* total amount of available input data */
   xpng_size_t current_buffer_size;   /* amount of data now in current_buffer */
   int process_mode;                 /* what push library is currently doing */
   int cur_palette;                  /* current push library palette index */

#  if defined(PNG_TEXT_SUPPORTED)
     xpng_size_t current_text_size;   /* current size of text input data */
     xpng_size_t current_text_left;   /* how much text left to read in input */
     xpng_charp current_text;         /* current text chunk buffer */
     xpng_charp current_text_ptr;     /* current location in current_text */
#  endif /* PNG_PROGRESSIVE_READ_SUPPORTED && PNG_TEXT_SUPPORTED */

#endif /* PNG_PROGRESSIVE_READ_SUPPORTED */

#if defined(__TURBOC__) && !defined(_Windows) && !defined(__FLAT__)
/* for the Borland special 64K segment handler */
   xpng_bytepp offset_table_ptr;
   xpng_bytep offset_table;
   xpng_uint_16 offset_table_number;
   xpng_uint_16 offset_table_count;
   xpng_uint_16 offset_table_count_free;
#endif

#if defined(PNG_READ_DITHER_SUPPORTED)
   xpng_bytep palette_lookup;         /* lookup table for dithering */
   xpng_bytep dither_index;           /* index translation for palette files */
#endif

#if defined(PNG_READ_DITHER_SUPPORTED) || defined(PNG_hIST_SUPPORTED)
   xpng_uint_16p hist;                /* histogram */
#endif

#if defined(PNG_WRITE_WEIGHTED_FILTER_SUPPORTED)
   xpng_byte heuristic_method;        /* heuristic for row filter selection */
   xpng_byte num_prev_filters;        /* number of weights for previous rows */
   xpng_bytep prev_filters;           /* filter type(s) of previous row(s) */
   xpng_uint_16p filter_weights;      /* weight(s) for previous line(s) */
   xpng_uint_16p inv_filter_weights;  /* 1/weight(s) for previous line(s) */
   xpng_uint_16p filter_costs;        /* relative filter calculation cost */
   xpng_uint_16p inv_filter_costs;    /* 1/relative filter calculation cost */
#endif

#if defined(PNG_TIME_RFC1123_SUPPORTED)
   xpng_charp time_buffer;            /* String to hold RFC 1123 time text */
#endif

/* New members added in libpng-1.0.6 */

#ifdef PNG_FREE_ME_SUPPORTED
   xpng_uint_32 free_me;       /* flags items libpng is responsible for freeing */
#endif

#if defined(PNG_USER_CHUNKS_SUPPORTED)
   xpng_voidp user_chunk_ptr;
   xpng_user_chunk_ptr read_user_chunk_fn; /* user read chunk handler */
#endif

#if defined(PNG_UNKNOWN_CHUNKS_SUPPORTED)
   int num_chunk_list;
   xpng_bytep chunk_list;
#endif

/* New members added in libpng-1.0.3 */
#if defined(PNG_READ_RGB_TO_GRAY_SUPPORTED)
   xpng_byte rgb_to_gray_status;
   /* These were changed from xpng_byte in libpng-1.0.6 */
   xpng_uint_16 rgb_to_gray_red_coeff;
   xpng_uint_16 rgb_to_gray_green_coeff;
   xpng_uint_16 rgb_to_gray_blue_coeff;
#endif

/* New member added in libpng-1.0.4 (renamed in 1.0.9) */
#if defined(PNG_MNG_FEATURES_SUPPORTED) || \
    defined(PNG_READ_EMPTY_PLTE_SUPPORTED) || \
    defined(PNG_WRITE_EMPTY_PLTE_SUPPORTED)
/* changed from xpng_byte to xpng_uint_32 at version 1.2.0 */
#ifdef PNG_1_0_X
   xpng_byte mng_features_permitted;
#else
   xpng_uint_32 mng_features_permitted;
#endif /* PNG_1_0_X */
#endif

/* New member added in libpng-1.0.7 */
#if defined(PNG_READ_GAMMA_SUPPORTED) || defined(PNG_READ_BACKGROUND_SUPPORTED)
   xpng_fixed_point int_gamma;
#endif

/* New member added in libpng-1.0.9, ifdef'ed out in 1.0.12, enabled in 1.2.0 */
#if defined(PNG_MNG_FEATURES_SUPPORTED)
   xpng_byte filter_type;
#endif

#if defined(PNG_1_0_X) || (defined(PNG_DEBUG) && defined(PNG_USE_PNGGCCRD))
/* New member added in libpng-1.0.10, ifdef'ed out in 1.2.0 */
   xpng_uint_32 row_buf_size;
#endif

/* New members added in libpng-1.2.0 */
#if !defined(PNG_1_0_X) && defined(PNG_ASSEMBLER_CODE_SUPPORTED)
   xpng_byte     mmx_bitdepth_threshold;
   xpng_uint_32  mmx_rowbytes_threshold;
   xpng_uint_32  asm_flags;
#endif

/* New members added in libpng-1.0.2 but first enabled by default in 1.2.0 */
#ifdef PNG_USER_MEM_SUPPORTED
   xpng_voidp mem_ptr;                /* user supplied struct for mem functions */
   xpng_malloc_ptr malloc_fn;         /* function for allocating memory */
   xpng_free_ptr free_fn;             /* function for freeing memory */
#endif

/* New member added in libpng-1.0.13 and 1.2.0 */
   xpng_bytep big_row_buf;         /* buffer to save current (unfiltered) row */

#if defined(PNG_READ_DITHER_SUPPORTED)
/* The following three members were added at version 1.0.14 and 1.2.4 */
   xpng_bytep dither_sort;            /* working sort array */
   xpng_bytep index_to_palette;       /* where the original index currently is */
                                     /* in the palette */
   xpng_bytep palette_to_index;       /* which original index points to this */
                                     /* palette color */
#endif

};


/* This prevents a compiler error in png.c if png.c and png.h are both at
   version 1.2.5
 */
typedef xpng_structp version_1_2_5;

typedef xpng_struct FAR * FAR * xpng_structpp;

/* Here are the function definitions most commonly used.  This is not
 * the place to find out how to use libpng.  See libpng.txt for the
 * full explanation, see example.c for the summary.  This just provides
 * a simple one line description of the use of each function.
 */

/* Returns the version number of the library */
extern PNG_EXPORT(xpng_uint_32,xpng_access_version_number) PNGARG((void));

/* Tell lib we have already handled the first <num_bytes> magic bytes.
 * Handling more than 8 bytes from the beginning of the file is an error.
 */
extern PNG_EXPORT(void,xpng_set_sig_bytes) PNGARG((xpng_structp xpng_ptr,
   int num_bytes));

/* Check sig[start] through sig[start + num_to_check - 1] to see if it's a
 * PNG file.  Returns zero if the supplied bytes match the 8-byte PNG
 * signature, and non-zero otherwise.  Having num_to_check == 0 or
 * start > 7 will always fail (ie return non-zero).
 */
extern PNG_EXPORT(int,xpng_sig_cmp) PNGARG((xpng_bytep sig, xpng_size_t start,
   xpng_size_t num_to_check));

/* Simple signature checking function.  This is the same as calling
 * xpng_check_sig(sig, n) := !xpng_sig_cmp(sig, 0, n).
 */
extern PNG_EXPORT(int,xpng_check_sig) PNGARG((xpng_bytep sig, int num));

/* Allocate and initialize xpng_ptr struct for reading, and any other memory. */
extern PNG_EXPORT(xpng_structp,xpng_create_read_struct)
   PNGARG((xpng_const_charp user_xpng_ver, xpng_voidp error_ptr,
   xpng_error_ptr error_fn, xpng_error_ptr warn_fn));

/* Allocate and initialize xpng_ptr struct for writing, and any other memory */
extern PNG_EXPORT(xpng_structp,xpng_create_write_struct)
   PNGARG((xpng_const_charp user_xpng_ver, xpng_voidp error_ptr,
   xpng_error_ptr error_fn, xpng_error_ptr warn_fn));

extern PNG_EXPORT(xpng_uint_32,xpng_get_compression_buffer_size)
   PNGARG((xpng_structp xpng_ptr));

extern PNG_EXPORT(void,xpng_set_compression_buffer_size)
   PNGARG((xpng_structp xpng_ptr, xpng_uint_32 size));

/* Reset the compression stream */
extern PNG_EXPORT(int,xpng_reset_zstream) PNGARG((xpng_structp xpng_ptr));

/* New functions added in libpng-1.0.2 (not enabled by default until 1.2.0) */
#ifdef PNG_USER_MEM_SUPPORTED
extern PNG_EXPORT(xpng_structp,xpng_create_read_struct_2)
   PNGARG((xpng_const_charp user_xpng_ver, xpng_voidp error_ptr,
   xpng_error_ptr error_fn, xpng_error_ptr warn_fn, xpng_voidp mem_ptr,
   xpng_malloc_ptr malloc_fn, xpng_free_ptr free_fn));
extern PNG_EXPORT(xpng_structp,xpng_create_write_struct_2)
   PNGARG((xpng_const_charp user_xpng_ver, xpng_voidp error_ptr,
   xpng_error_ptr error_fn, xpng_error_ptr warn_fn, xpng_voidp mem_ptr,
   xpng_malloc_ptr malloc_fn, xpng_free_ptr free_fn));
#endif

/* Write a PNG chunk - size, type, (optional) data, CRC. */
extern PNG_EXPORT(void,xpng_write_chunk) PNGARG((xpng_structp xpng_ptr,
   xpng_bytep chunk_name, xpng_bytep data, xpng_size_t length));

/* Write the start of a PNG chunk - length and chunk name. */
extern PNG_EXPORT(void,xpng_write_chunk_start) PNGARG((xpng_structp xpng_ptr,
   xpng_bytep chunk_name, xpng_uint_32 length));

/* Write the data of a PNG chunk started with xpng_write_chunk_start(). */
extern PNG_EXPORT(void,xpng_write_chunk_data) PNGARG((xpng_structp xpng_ptr,
   xpng_bytep data, xpng_size_t length));

/* Finish a chunk started with xpng_write_chunk_start() (includes CRC). */
extern PNG_EXPORT(void,xpng_write_chunk_end) PNGARG((xpng_structp xpng_ptr));

/* Allocate and initialize the info structure */
extern PNG_EXPORT(xpng_infop,xpng_create_info_struct)
   PNGARG((xpng_structp xpng_ptr));

/* Initialize the info structure (old interface - DEPRECATED) */
extern PNG_EXPORT(void,xpng_info_init) PNGARG((xpng_infop info_ptr));
#undef xpng_info_init
#define xpng_info_init(info_ptr) xpng_info_init_3(&info_ptr, sizeof(xpng_info));
extern PNG_EXPORT(void,xpng_info_init_3) PNGARG((xpng_infopp info_ptr,
    xpng_size_t xpng_info_struct_size));

/* Writes all the PNG information before the image. */
extern PNG_EXPORT(void,xpng_write_info_before_PLTE) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr));
extern PNG_EXPORT(void,xpng_write_info) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr));

/* read the information before the actual image data. */
extern PNG_EXPORT(void,xpng_read_info) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr));

#if defined(PNG_TIME_RFC1123_SUPPORTED)
extern PNG_EXPORT(xpng_charp,xpng_convert_to_rfc1123)
   PNGARG((xpng_structp xpng_ptr, xpng_timep ptime));
#endif

#if !defined(_WIN32_WCE)
/* "time.h" functions are not supported on WindowsCE */
#if defined(PNG_WRITE_tIME_SUPPORTED)
/* convert from a struct tm to xpng_time */
extern PNG_EXPORT(void,xpng_convert_from_struct_tm) PNGARG((xpng_timep ptime,
   struct tm FAR * ttime));

/* convert from time_t to xpng_time.  Uses gmtime() */
extern PNG_EXPORT(void,xpng_convert_from_time_t) PNGARG((xpng_timep ptime,
   time_t ttime));
#endif /* PNG_WRITE_tIME_SUPPORTED */
#endif /* _WIN32_WCE */

#if defined(PNG_READ_EXPAND_SUPPORTED)
/* Expand data to 24-bit RGB, or 8-bit grayscale, with alpha if available. */
extern PNG_EXPORT(void,xpng_set_expand) PNGARG((xpng_structp xpng_ptr));
extern PNG_EXPORT(void,xpng_set_gray_1_2_4_to_8) PNGARG((xpng_structp xpng_ptr));
extern PNG_EXPORT(void,xpng_set_palette_to_rgb) PNGARG((xpng_structp xpng_ptr));
extern PNG_EXPORT(void,xpng_set_tRNS_to_alpha) PNGARG((xpng_structp xpng_ptr));
#endif

#if defined(PNG_READ_BGR_SUPPORTED) || defined(PNG_WRITE_BGR_SUPPORTED)
/* Use blue, green, red order for pixels. */
extern PNG_EXPORT(void,xpng_set_bgr) PNGARG((xpng_structp xpng_ptr));
#endif

#if defined(PNG_READ_GRAY_TO_RGB_SUPPORTED)
/* Expand the grayscale to 24-bit RGB if necessary. */
extern PNG_EXPORT(void,xpng_set_gray_to_rgb) PNGARG((xpng_structp xpng_ptr));
#endif

#if defined(PNG_READ_RGB_TO_GRAY_SUPPORTED)
/* Reduce RGB to grayscale. */
#ifdef PNG_FLOATING_POINT_SUPPORTED
extern PNG_EXPORT(void,xpng_set_rgb_to_gray) PNGARG((xpng_structp xpng_ptr,
   int error_action, double red, double green ));
#endif
extern PNG_EXPORT(void,xpng_set_rgb_to_gray_fixed) PNGARG((xpng_structp xpng_ptr,
   int error_action, xpng_fixed_point red, xpng_fixed_point green ));
extern PNG_EXPORT(xpng_byte,xpng_get_rgb_to_gray_status) PNGARG((xpng_structp
   xpng_ptr));
#endif

extern PNG_EXPORT(void,xpng_build_grayscale_palette) PNGARG((int bit_depth,
   xpng_colorp palette));

#if defined(PNG_READ_STRIP_ALPHA_SUPPORTED)
extern PNG_EXPORT(void,xpng_set_strip_alpha) PNGARG((xpng_structp xpng_ptr));
#endif

#if defined(PNG_READ_SWAP_ALPHA_SUPPORTED) || \
    defined(PNG_WRITE_SWAP_ALPHA_SUPPORTED)
extern PNG_EXPORT(void,xpng_set_swap_alpha) PNGARG((xpng_structp xpng_ptr));
#endif

#if defined(PNG_READ_INVERT_ALPHA_SUPPORTED) || \
    defined(PNG_WRITE_INVERT_ALPHA_SUPPORTED)
extern PNG_EXPORT(void,xpng_set_invert_alpha) PNGARG((xpng_structp xpng_ptr));
#endif

#if defined(PNG_READ_FILLER_SUPPORTED) || defined(PNG_WRITE_FILLER_SUPPORTED)
/* Add a filler byte to 24-bit RGB images. */
extern PNG_EXPORT(void,xpng_set_filler) PNGARG((xpng_structp xpng_ptr,
   xpng_uint_32 filler, int flags));
/* The values of the PNG_FILLER_ defines should NOT be changed */
#define PNG_FILLER_BEFORE 0
#define PNG_FILLER_AFTER 1
#endif /* PNG_READ_FILLER_SUPPORTED || PNG_WRITE_FILLER_SUPPORTED */

#if defined(PNG_READ_SWAP_SUPPORTED) || defined(PNG_WRITE_SWAP_SUPPORTED)
/* Swap bytes in 16-bit depth files. */
extern PNG_EXPORT(void,xpng_set_swap) PNGARG((xpng_structp xpng_ptr));
#endif

#if defined(PNG_READ_PACK_SUPPORTED) || defined(PNG_WRITE_PACK_SUPPORTED)
/* Use 1 byte per pixel in 1, 2, or 4-bit depth files. */
extern PNG_EXPORT(void,xpng_set_packing) PNGARG((xpng_structp xpng_ptr));
#endif

#if defined(PNG_READ_PACKSWAP_SUPPORTED) || defined(PNG_WRITE_PACKSWAP_SUPPORTED)
/* Swap packing order of pixels in bytes. */
extern PNG_EXPORT(void,xpng_set_packswap) PNGARG((xpng_structp xpng_ptr));
#endif

#if defined(PNG_READ_SHIFT_SUPPORTED) || defined(PNG_WRITE_SHIFT_SUPPORTED)
/* Converts files to legal bit depths. */
extern PNG_EXPORT(void,xpng_set_shift) PNGARG((xpng_structp xpng_ptr,
   xpng_color_8p true_bits));
#endif

#if defined(PNG_READ_INTERLACING_SUPPORTED) || \
    defined(PNG_WRITE_INTERLACING_SUPPORTED)
/* Have the code handle the interlacing.  Returns the number of passes. */
extern PNG_EXPORT(int,xpng_set_interlace_handling) PNGARG((xpng_structp xpng_ptr));
#endif

#if defined(PNG_READ_INVERT_SUPPORTED) || defined(PNG_WRITE_INVERT_SUPPORTED)
/* Invert monochrome files */
extern PNG_EXPORT(void,xpng_set_invert_mono) PNGARG((xpng_structp xpng_ptr));
#endif

#if defined(PNG_READ_BACKGROUND_SUPPORTED)
/* Handle alpha and tRNS by replacing with a background color. */
#ifdef PNG_FLOATING_POINT_SUPPORTED
extern PNG_EXPORT(void,xpng_set_background) PNGARG((xpng_structp xpng_ptr,
   xpng_color_16p background_color, int background_gamma_code,
   int need_expand, double background_gamma));
#endif
#define PNG_BACKGROUND_GAMMA_UNKNOWN 0
#define PNG_BACKGROUND_GAMMA_SCREEN  1
#define PNG_BACKGROUND_GAMMA_FILE    2
#define PNG_BACKGROUND_GAMMA_UNIQUE  3
#endif

#if defined(PNG_READ_16_TO_8_SUPPORTED)
/* strip the second byte of information from a 16-bit depth file. */
extern PNG_EXPORT(void,xpng_set_strip_16) PNGARG((xpng_structp xpng_ptr));
#endif

#if defined(PNG_READ_DITHER_SUPPORTED)
/* Turn on dithering, and reduce the palette to the number of colors available. */
extern PNG_EXPORT(void,xpng_set_dither) PNGARG((xpng_structp xpng_ptr,
   xpng_colorp palette, int num_palette, int maximum_colors,
   xpng_uint_16p histogram, int full_dither));
#endif

#if defined(PNG_READ_GAMMA_SUPPORTED)
/* Handle gamma correction. Screen_gamma=(display_exponent) */
#ifdef PNG_FLOATING_POINT_SUPPORTED
extern PNG_EXPORT(void,xpng_set_gamma) PNGARG((xpng_structp xpng_ptr,
   double screen_gamma, double default_file_gamma));
#endif
#endif

#if defined(PNG_READ_EMPTY_PLTE_SUPPORTED) || \
    defined(PNG_WRITE_EMPTY_PLTE_SUPPORTED)
/* Permit or disallow empty PLTE (0: not permitted, 1: permitted) */
/* Deprecated and will be removed.  Use xpng_permit_mng_features() instead. */
extern PNG_EXPORT(void,xpng_permit_empty_plte) PNGARG((xpng_structp xpng_ptr,
   int empty_plte_permitted));
#endif

#if defined(PNG_WRITE_FLUSH_SUPPORTED)
/* Set how many lines between output flushes - 0 for no flushing */
extern PNG_EXPORT(void,xpng_set_flush) PNGARG((xpng_structp xpng_ptr, int nrows));
/* Flush the current PNG output buffer */
extern PNG_EXPORT(void,xpng_write_flush) PNGARG((xpng_structp xpng_ptr));
#endif

/* optional update palette with requested transformations */
extern PNG_EXPORT(void,xpng_start_read_image) PNGARG((xpng_structp xpng_ptr));

/* optional call to update the users info structure */
extern PNG_EXPORT(void,xpng_read_update_info) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr));

/* read one or more rows of image data. */
extern PNG_EXPORT(void,xpng_read_rows) PNGARG((xpng_structp xpng_ptr,
   xpng_bytepp row, xpng_bytepp display_row, xpng_uint_32 num_rows));

/* read a row of data. */
extern PNG_EXPORT(void,xpng_read_row) PNGARG((xpng_structp xpng_ptr,
   xpng_bytep row,
   xpng_bytep display_row));

/* read the whole image into memory at once. */
extern PNG_EXPORT(void,xpng_read_image) PNGARG((xpng_structp xpng_ptr,
   xpng_bytepp image));

/* write a row of image data */
extern PNG_EXPORT(void,xpng_write_row) PNGARG((xpng_structp xpng_ptr,
   xpng_bytep row));

/* write a few rows of image data */
extern PNG_EXPORT(void,xpng_write_rows) PNGARG((xpng_structp xpng_ptr,
   xpng_bytepp row, xpng_uint_32 num_rows));

/* write the image data */
extern PNG_EXPORT(void,xpng_write_image) PNGARG((xpng_structp xpng_ptr,
   xpng_bytepp image));

/* writes the end of the PNG file. */
extern PNG_EXPORT(void,xpng_write_end) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr));

/* read the end of the PNG file. */
extern PNG_EXPORT(void,xpng_read_end) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr));

/* free any memory associated with the xpng_info_struct */
extern PNG_EXPORT(void,xpng_destroy_info_struct) PNGARG((xpng_structp xpng_ptr,
   xpng_infopp info_ptr_ptr));

/* free any memory associated with the xpng_struct and the xpng_info_structs */
extern PNG_EXPORT(void,xpng_destroy_read_struct) PNGARG((xpng_structpp
   xpng_ptr_ptr, xpng_infopp info_ptr_ptr, xpng_infopp end_info_ptr_ptr));

/* free all memory used by the read (old method - NOT DLL EXPORTED) */
extern void xpng_read_destroy PNGARG((xpng_structp xpng_ptr, xpng_infop info_ptr,
   xpng_infop end_info_ptr));

/* free any memory associated with the xpng_struct and the xpng_info_structs */
extern PNG_EXPORT(void,xpng_destroy_write_struct)
   PNGARG((xpng_structpp xpng_ptr_ptr, xpng_infopp info_ptr_ptr));

/* free any memory used in xpng_ptr struct (old method - NOT DLL EXPORTED) */
extern void xpng_write_destroy PNGARG((xpng_structp xpng_ptr));

/* set the libpng method of handling chunk CRC errors */
extern PNG_EXPORT(void,xpng_set_crc_action) PNGARG((xpng_structp xpng_ptr,
   int crit_action, int ancil_action));

/* Values for xpng_set_crc_action() to say how to handle CRC errors in
 * ancillary and critical chunks, and whether to use the data contained
 * therein.  Note that it is impossible to "discard" data in a critical
 * chunk.  For versions prior to 0.90, the action was always error/quit,
 * whereas in version 0.90 and later, the action for CRC errors in ancillary
 * chunks is warn/discard.  These values should NOT be changed.
 *
 *      value                       action:critical     action:ancillary
 */
#define PNG_CRC_DEFAULT       0  /* error/quit          warn/discard data */
#define PNG_CRC_ERROR_QUIT    1  /* error/quit          error/quit        */
#define PNG_CRC_WARN_DISCARD  2  /* (INVALID)           warn/discard data */
#define PNG_CRC_WARN_USE      3  /* warn/use data       warn/use data     */
#define PNG_CRC_QUIET_USE     4  /* quiet/use data      quiet/use data    */
#define PNG_CRC_NO_CHANGE     5  /* use current value   use current value */

/* These functions give the user control over the scan-line filtering in
 * libpng and the compression methods used by zlib.  These functions are
 * mainly useful for testing, as the defaults should work with most users.
 * Those users who are tight on memory or want faster performance at the
 * expense of compression can modify them.  See the compression library
 * header file (zlib.h) for an explination of the compression functions.
 */

/* set the filtering method(s) used by libpng.  Currently, the only valid
 * value for "method" is 0.
 */
extern PNG_EXPORT(void,xpng_set_filter) PNGARG((xpng_structp xpng_ptr, int method,
   int filters));

/* Flags for xpng_set_filter() to say which filters to use.  The flags
 * are chosen so that they don't conflict with real filter types
 * below, in case they are supplied instead of the #defined constants.
 * These values should NOT be changed.
 */
#define PNG_NO_FILTERS     0x00
#define PNG_FILTER_NONE    0x08
#define PNG_FILTER_SUB     0x10
#define PNG_FILTER_UP      0x20
#define PNG_FILTER_AVG     0x40
#define PNG_FILTER_PAETH   0x80
#define PNG_ALL_FILTERS (PNG_FILTER_NONE | PNG_FILTER_SUB | PNG_FILTER_UP | \
                         PNG_FILTER_AVG | PNG_FILTER_PAETH)

/* Filter values (not flags) - used in pngwrite.c, pngwutil.c for now.
 * These defines should NOT be changed.
 */
#define PNG_FILTER_VALUE_NONE  0
#define PNG_FILTER_VALUE_SUB   1
#define PNG_FILTER_VALUE_UP    2
#define PNG_FILTER_VALUE_AVG   3
#define PNG_FILTER_VALUE_PAETH 4
#define PNG_FILTER_VALUE_LAST  5

#if defined(PNG_WRITE_WEIGHTED_FILTER_SUPPORTED) /* EXPERIMENTAL */
/* The "heuristic_method" is given by one of the PNG_FILTER_HEURISTIC_
 * defines, either the default (minimum-sum-of-absolute-differences), or
 * the experimental method (weighted-minimum-sum-of-absolute-differences).
 *
 * Weights are factors >= 1.0, indicating how important it is to keep the
 * filter type consistent between rows.  Larger numbers mean the current
 * filter is that many times as likely to be the same as the "num_weights"
 * previous filters.  This is cumulative for each previous row with a weight.
 * There needs to be "num_weights" values in "filter_weights", or it can be
 * NULL if the weights aren't being specified.  Weights have no influence on
 * the selection of the first row filter.  Well chosen weights can (in theory)
 * improve the compression for a given image.
 *
 * Costs are factors >= 1.0 indicating the relative decoding costs of a
 * filter type.  Higher costs indicate more decoding expense, and are
 * therefore less likely to be selected over a filter with lower computational
 * costs.  There needs to be a value in "filter_costs" for each valid filter
 * type (given by PNG_FILTER_VALUE_LAST), or it can be NULL if you aren't
 * setting the costs.  Costs try to improve the speed of decompression without
 * unduly increasing the compressed image size.
 *
 * A negative weight or cost indicates the default value is to be used, and
 * values in the range [0.0, 1.0) indicate the value is to remain unchanged.
 * The default values for both weights and costs are currently 1.0, but may
 * change if good general weighting/cost heuristics can be found.  If both
 * the weights and costs are set to 1.0, this degenerates the WEIGHTED method
 * to the UNWEIGHTED method, but with added encoding time/computation.
 */
#ifdef PNG_FLOATING_POINT_SUPPORTED
extern PNG_EXPORT(void,xpng_set_filter_heuristics) PNGARG((xpng_structp xpng_ptr,
   int heuristic_method, int num_weights, xpng_doublep filter_weights,
   xpng_doublep filter_costs));
#endif
#endif /*  PNG_WRITE_WEIGHTED_FILTER_SUPPORTED */

/* Heuristic used for row filter selection.  These defines should NOT be
 * changed.
 */
#define PNG_FILTER_HEURISTIC_DEFAULT    0  /* Currently "UNWEIGHTED" */
#define PNG_FILTER_HEURISTIC_UNWEIGHTED 1  /* Used by libpng < 0.95 */
#define PNG_FILTER_HEURISTIC_WEIGHTED   2  /* Experimental feature */
#define PNG_FILTER_HEURISTIC_LAST       3  /* Not a valid value */

/* Set the library compression level.  Currently, valid values range from
 * 0 - 9, corresponding directly to the zlib compression levels 0 - 9
 * (0 - no compression, 9 - "maximal" compression).  Note that tests have
 * shown that zlib compression levels 3-6 usually perform as well as level 9
 * for PNG images, and do considerably fewer caclulations.  In the future,
 * these values may not correspond directly to the zlib compression levels.
 */
extern PNG_EXPORT(void,xpng_set_compression_level) PNGARG((xpng_structp xpng_ptr,
   int level));

extern PNG_EXPORT(void,xpng_set_compression_mem_level)
   PNGARG((xpng_structp xpng_ptr, int mem_level));

extern PNG_EXPORT(void,xpng_set_compression_strategy)
   PNGARG((xpng_structp xpng_ptr, int strategy));

extern PNG_EXPORT(void,xpng_set_compression_window_bits)
   PNGARG((xpng_structp xpng_ptr, int window_bits));

extern PNG_EXPORT(void,xpng_set_compression_method) PNGARG((xpng_structp xpng_ptr,
   int method));

/* These next functions are called for input/output, memory, and error
 * handling.  They are in the file pngrio.c, pngwio.c, and pngerror.c,
 * and call standard C I/O routines such as fread(), fwrite(), and
 * fprintf().  These functions can be made to use other I/O routines
 * at run time for those applications that need to handle I/O in a
 * different manner by calling xpng_set_???_fn().  See libpng.txt for
 * more information.
 */

#if !defined(PNG_NO_STDIO)
/* Initialize the input/output for the PNG file to the default functions. */
extern PNG_EXPORT(void,xpng_init_io) PNGARG((xpng_structp xpng_ptr, xpng_FILE_p fp));
#endif

/* Replace the (error and abort), and warning functions with user
 * supplied functions.  If no messages are to be printed you must still
 * write and use replacement functions. The replacement error_fn should
 * still do a longjmp to the last setjmp location if you are using this
 * method of error handling.  If error_fn or warning_fn is NULL, the
 * default function will be used.
 */

extern PNG_EXPORT(void,xpng_set_error_fn) PNGARG((xpng_structp xpng_ptr,
   xpng_voidp error_ptr, xpng_error_ptr error_fn, xpng_error_ptr warning_fn));

/* Return the user pointer associated with the error functions */
extern PNG_EXPORT(xpng_voidp,xpng_get_error_ptr) PNGARG((xpng_structp xpng_ptr));

/* Replace the default data output functions with a user supplied one(s).
 * If buffered output is not used, then output_flush_fn can be set to NULL.
 * If PNG_WRITE_FLUSH_SUPPORTED is not defined at libpng compile time
 * output_flush_fn will be ignored (and thus can be NULL).
 */
extern PNG_EXPORT(void,xpng_set_write_fn) PNGARG((xpng_structp xpng_ptr,
   xpng_voidp io_ptr, xpng_rw_ptr write_data_fn, xpng_flush_ptr output_flush_fn));

/* Replace the default data input function with a user supplied one. */
extern PNG_EXPORT(void,xpng_set_read_fn) PNGARG((xpng_structp xpng_ptr,
   xpng_voidp io_ptr, xpng_rw_ptr read_data_fn));

/* Return the user pointer associated with the I/O functions */
extern PNG_EXPORT(xpng_voidp,xpng_get_io_ptr) PNGARG((xpng_structp xpng_ptr));

extern PNG_EXPORT(void,xpng_set_read_status_fn) PNGARG((xpng_structp xpng_ptr,
   xpng_read_status_ptr read_row_fn));

extern PNG_EXPORT(void,xpng_set_write_status_fn) PNGARG((xpng_structp xpng_ptr,
   xpng_write_status_ptr write_row_fn));

#ifdef PNG_USER_MEM_SUPPORTED
/* Replace the default memory allocation functions with user supplied one(s). */
extern PNG_EXPORT(void,xpng_set_mem_fn) PNGARG((xpng_structp xpng_ptr,
   xpng_voidp mem_ptr, xpng_malloc_ptr malloc_fn, xpng_free_ptr free_fn));
/* Return the user pointer associated with the memory functions */
extern PNG_EXPORT(xpng_voidp,xpng_get_mem_ptr) PNGARG((xpng_structp xpng_ptr));
#endif

#if defined(PNG_READ_USER_TRANSFORM_SUPPORTED) || \
    defined(PNG_LEGACY_SUPPORTED)
extern PNG_EXPORT(void,xpng_set_read_user_transform_fn) PNGARG((xpng_structp
   xpng_ptr, xpng_user_transform_ptr read_user_transform_fn));
#endif

#if defined(PNG_WRITE_USER_TRANSFORM_SUPPORTED) || \
    defined(PNG_LEGACY_SUPPORTED)
extern PNG_EXPORT(void,xpng_set_write_user_transform_fn) PNGARG((xpng_structp
   xpng_ptr, xpng_user_transform_ptr write_user_transform_fn));
#endif

#if defined(PNG_READ_USER_TRANSFORM_SUPPORTED) || \
    defined(PNG_WRITE_USER_TRANSFORM_SUPPORTED) || \
    defined(PNG_LEGACY_SUPPORTED)
extern PNG_EXPORT(void,xpng_set_user_transform_info) PNGARG((xpng_structp
   xpng_ptr, xpng_voidp user_transform_ptr, int user_transform_depth,
   int user_transform_channels));
/* Return the user pointer associated with the user transform functions */
extern PNG_EXPORT(xpng_voidp,xpng_get_user_transform_ptr)
   PNGARG((xpng_structp xpng_ptr));
#endif

#ifdef PNG_USER_CHUNKS_SUPPORTED
extern PNG_EXPORT(void,xpng_set_read_user_chunk_fn) PNGARG((xpng_structp xpng_ptr,
   xpng_voidp user_chunk_ptr, xpng_user_chunk_ptr read_user_chunk_fn));
extern PNG_EXPORT(xpng_voidp,xpng_get_user_chunk_ptr) PNGARG((xpng_structp
   xpng_ptr));
#endif

#ifdef PNG_PROGRESSIVE_READ_SUPPORTED
/* Sets the function callbacks for the push reader, and a pointer to a
 * user-defined structure available to the callback functions.
 */
extern PNG_EXPORT(void,xpng_set_progressive_read_fn) PNGARG((xpng_structp xpng_ptr,
   xpng_voidp progressive_ptr,
   xpng_progressive_info_ptr info_fn, xpng_progressive_row_ptr row_fn,
   xpng_progressive_end_ptr end_fn));

/* returns the user pointer associated with the push read functions */
extern PNG_EXPORT(xpng_voidp,xpng_get_progressive_ptr)
   PNGARG((xpng_structp xpng_ptr));

/* function to be called when data becomes available */
extern PNG_EXPORT(void,xpng_process_data) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_bytep buffer, xpng_size_t buffer_size));

/* function that combines rows.  Not very much different than the
 * xpng_combine_row() call.  Is this even used?????
 */
extern PNG_EXPORT(void,xpng_progressive_combine_row) PNGARG((xpng_structp xpng_ptr,
   xpng_bytep old_row, xpng_bytep new_row));
#endif /* PNG_PROGRESSIVE_READ_SUPPORTED */

extern PNG_EXPORT(xpng_voidp,xpng_malloc) PNGARG((xpng_structp xpng_ptr,
   xpng_uint_32 size));

#if defined(PNG_1_0_X)
#  define xpng_malloc_warn xpng_malloc
#else
/* Added at libpng version 1.2.4 */
extern PNG_EXPORT(xpng_voidp,xpng_malloc_warn) PNGARG((xpng_structp xpng_ptr,
   xpng_uint_32 size));
#endif

/* frees a pointer allocated by xpng_malloc() */
extern PNG_EXPORT(void,xpng_free) PNGARG((xpng_structp xpng_ptr, xpng_voidp ptr));

#if defined(PNG_1_0_X)
/* Function to allocate memory for zlib. */
extern PNG_EXPORT(voidpf,xpng_zalloc) PNGARG((voidpf xpng_ptr, uInt items,
   uInt size));

/* Function to free memory for zlib */
extern PNG_EXPORT(void,xpng_zfree) PNGARG((voidpf xpng_ptr, voidpf ptr));
#endif

/* Free data that was allocated internally */
extern PNG_EXPORT(void,xpng_free_data) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_uint_32 free_me, int num));
#ifdef PNG_FREE_ME_SUPPORTED
/* Reassign responsibility for freeing existing data, whether allocated
 * by libpng or by the application */
extern PNG_EXPORT(void,xpng_data_freer) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, int freer, xpng_uint_32 mask));
#endif
/* assignments for xpng_data_freer */
#define PNG_DESTROY_WILL_FREE_DATA 1
#define PNG_SET_WILL_FREE_DATA 1
#define PNG_USER_WILL_FREE_DATA 2
/* Flags for xpng_ptr->free_me and info_ptr->free_me */
#define PNG_FREE_HIST 0x0008
#define PNG_FREE_ICCP 0x0010
#define PNG_FREE_SPLT 0x0020
#define PNG_FREE_ROWS 0x0040
#define PNG_FREE_PCAL 0x0080
#define PNG_FREE_SCAL 0x0100
#define PNG_FREE_UNKN 0x0200
#define PNG_FREE_LIST 0x0400
#define PNG_FREE_PLTE 0x1000
#define PNG_FREE_TRNS 0x2000
#define PNG_FREE_TEXT 0x4000
#define PNG_FREE_ALL  0x7fff
#define PNG_FREE_MUL  0x4220 /* PNG_FREE_SPLT|PNG_FREE_TEXT|PNG_FREE_UNKN */

#ifdef PNG_USER_MEM_SUPPORTED
extern PNG_EXPORT(xpng_voidp,xpng_malloc_default) PNGARG((xpng_structp xpng_ptr,
   xpng_uint_32 size));
extern PNG_EXPORT(void,xpng_free_default) PNGARG((xpng_structp xpng_ptr,
   xpng_voidp ptr));
#endif

extern PNG_EXPORT(xpng_voidp,xpng_memcpy_check) PNGARG((xpng_structp xpng_ptr,
   xpng_voidp s1, xpng_voidp s2, xpng_uint_32 size));

extern PNG_EXPORT(xpng_voidp,xpng_memset_check) PNGARG((xpng_structp xpng_ptr,
   xpng_voidp s1, int value, xpng_uint_32 size));

#if defined(USE_FAR_KEYWORD)  /* memory model conversion function */
extern void *xpng_far_to_near PNGARG((xpng_structp xpng_ptr,xpng_voidp ptr,
   int check));
#endif /* USE_FAR_KEYWORD */

/* Fatal error in PNG image of libpng - can't continue */
extern PNG_EXPORT(void,xpng_error) PNGARG((xpng_structp xpng_ptr,
   xpng_const_charp error_message));

/* The same, but the chunk name is prepended to the error string. */
extern PNG_EXPORT(void,xpng_chunk_error) PNGARG((xpng_structp xpng_ptr,
   xpng_const_charp error_message));

/* Non-fatal error in libpng.  Can continue, but may have a problem. */
extern PNG_EXPORT(void,xpng_warning) PNGARG((xpng_structp xpng_ptr,
   xpng_const_charp warning_message));

/* Non-fatal error in libpng, chunk name is prepended to message. */
extern PNG_EXPORT(void,xpng_chunk_warning) PNGARG((xpng_structp xpng_ptr,
   xpng_const_charp warning_message));

/* The xpng_set_<chunk> functions are for storing values in the xpng_info_struct.
 * Similarly, the xpng_get_<chunk> calls are used to read values from the
 * xpng_info_struct, either storing the parameters in the passed variables, or
 * setting pointers into the xpng_info_struct where the data is stored.  The
 * xpng_get_<chunk> functions return a non-zero value if the data was available
 * in info_ptr, or return zero and do not change any of the parameters if the
 * data was not available.
 *
 * These functions should be used instead of directly accessing xpng_info
 * to avoid problems with future changes in the size and internal layout of
 * xpng_info_struct.
 */
/* Returns "flag" if chunk data is valid in info_ptr. */
extern PNG_EXPORT(xpng_uint_32,xpng_get_valid) PNGARG((xpng_structp xpng_ptr,
xpng_infop info_ptr, xpng_uint_32 flag));

/* Returns number of bytes needed to hold a transformed row. */
extern PNG_EXPORT(xpng_uint_32,xpng_get_rowbytes) PNGARG((xpng_structp xpng_ptr,
xpng_infop info_ptr));

#if defined(PNG_INFO_IMAGE_SUPPORTED)
/* Returns row_pointers, which is an array of pointers to scanlines that was
returned from xpng_read_png(). */
extern PNG_EXPORT(xpng_bytepp,xpng_get_rows) PNGARG((xpng_structp xpng_ptr,
xpng_infop info_ptr));
/* Set row_pointers, which is an array of pointers to scanlines for use
by xpng_write_png(). */
extern PNG_EXPORT(void,xpng_set_rows) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_bytepp row_pointers));
#endif

/* Returns number of color channels in image. */
extern PNG_EXPORT(xpng_byte,xpng_get_channels) PNGARG((xpng_structp xpng_ptr,
xpng_infop info_ptr));

#ifdef PNG_EASY_ACCESS_SUPPORTED
/* Returns image width in pixels. */
extern PNG_EXPORT(xpng_uint_32, xpng_get_image_width) PNGARG((xpng_structp
xpng_ptr, xpng_infop info_ptr));

/* Returns image height in pixels. */
extern PNG_EXPORT(xpng_uint_32, xpng_get_image_height) PNGARG((xpng_structp
xpng_ptr, xpng_infop info_ptr));

/* Returns image bit_depth. */
extern PNG_EXPORT(xpng_byte, xpng_get_bit_depth) PNGARG((xpng_structp
xpng_ptr, xpng_infop info_ptr));

/* Returns image color_type. */
extern PNG_EXPORT(xpng_byte, xpng_get_color_type) PNGARG((xpng_structp
xpng_ptr, xpng_infop info_ptr));

/* Returns image filter_type. */
extern PNG_EXPORT(xpng_byte, xpng_get_filter_type) PNGARG((xpng_structp
xpng_ptr, xpng_infop info_ptr));

/* Returns image interlace_type. */
extern PNG_EXPORT(xpng_byte, xpng_get_interlace_type) PNGARG((xpng_structp
xpng_ptr, xpng_infop info_ptr));

/* Returns image compression_type. */
extern PNG_EXPORT(xpng_byte, xpng_get_compression_type) PNGARG((xpng_structp
xpng_ptr, xpng_infop info_ptr));

/* Returns image resolution in pixels per meter, from pHYs chunk data. */
extern PNG_EXPORT(xpng_uint_32, xpng_get_pixels_per_meter) PNGARG((xpng_structp
xpng_ptr, xpng_infop info_ptr));
extern PNG_EXPORT(xpng_uint_32, xpng_get_x_pixels_per_meter) PNGARG((xpng_structp
xpng_ptr, xpng_infop info_ptr));
extern PNG_EXPORT(xpng_uint_32, xpng_get_y_pixels_per_meter) PNGARG((xpng_structp
xpng_ptr, xpng_infop info_ptr));

/* Returns pixel aspect ratio, computed from pHYs chunk data.  */
#ifdef PNG_FLOATING_POINT_SUPPORTED
extern PNG_EXPORT(float, xpng_get_pixel_aspect_ratio) PNGARG((xpng_structp
xpng_ptr, xpng_infop info_ptr));
#endif

/* Returns image x, y offset in pixels or microns, from oFFs chunk data. */
extern PNG_EXPORT(xpng_int_32, xpng_get_x_offset_pixels) PNGARG((xpng_structp
xpng_ptr, xpng_infop info_ptr));
extern PNG_EXPORT(xpng_int_32, xpng_get_y_offset_pixels) PNGARG((xpng_structp
xpng_ptr, xpng_infop info_ptr));
extern PNG_EXPORT(xpng_int_32, xpng_get_x_offset_microns) PNGARG((xpng_structp
xpng_ptr, xpng_infop info_ptr));
extern PNG_EXPORT(xpng_int_32, xpng_get_y_offset_microns) PNGARG((xpng_structp
xpng_ptr, xpng_infop info_ptr));

#endif /* PNG_EASY_ACCESS_SUPPORTED */

/* Returns pointer to signature string read from PNG header */
extern PNG_EXPORT(xpng_bytep,xpng_get_signature) PNGARG((xpng_structp xpng_ptr,
xpng_infop info_ptr));

#if defined(PNG_bKGD_SUPPORTED)
extern PNG_EXPORT(xpng_uint_32,xpng_get_bKGD) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_color_16p *background));
#endif

#if defined(PNG_bKGD_SUPPORTED)
extern PNG_EXPORT(void,xpng_set_bKGD) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_color_16p background));
#endif

#if defined(PNG_cHRM_SUPPORTED)
#ifdef PNG_FLOATING_POINT_SUPPORTED
extern PNG_EXPORT(xpng_uint_32,xpng_get_cHRM) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, double *white_x, double *white_y, double *red_x,
   double *red_y, double *green_x, double *green_y, double *blue_x,
   double *blue_y));
#endif
#ifdef PNG_FIXED_POINT_SUPPORTED
extern PNG_EXPORT(xpng_uint_32,xpng_get_cHRM_fixed) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_fixed_point *int_white_x, xpng_fixed_point
   *int_white_y, xpng_fixed_point *int_red_x, xpng_fixed_point *int_red_y,
   xpng_fixed_point *int_green_x, xpng_fixed_point *int_green_y, xpng_fixed_point
   *int_blue_x, xpng_fixed_point *int_blue_y));
#endif
#endif

#if defined(PNG_cHRM_SUPPORTED)
#ifdef PNG_FLOATING_POINT_SUPPORTED
extern PNG_EXPORT(void,xpng_set_cHRM) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, double white_x, double white_y, double red_x,
   double red_y, double green_x, double green_y, double blue_x, double blue_y));
#endif
#ifdef PNG_FIXED_POINT_SUPPORTED
extern PNG_EXPORT(void,xpng_set_cHRM_fixed) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_fixed_point int_white_x, xpng_fixed_point int_white_y,
   xpng_fixed_point int_red_x, xpng_fixed_point int_red_y, xpng_fixed_point
   int_green_x, xpng_fixed_point int_green_y, xpng_fixed_point int_blue_x,
   xpng_fixed_point int_blue_y));
#endif
#endif

#if defined(PNG_gAMA_SUPPORTED)
#ifdef PNG_FLOATING_POINT_SUPPORTED
extern PNG_EXPORT(xpng_uint_32,xpng_get_gAMA) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, double *file_gamma));
#endif
extern PNG_EXPORT(xpng_uint_32,xpng_get_gAMA_fixed) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_fixed_point *int_file_gamma));
#endif

#if defined(PNG_gAMA_SUPPORTED)
#ifdef PNG_FLOATING_POINT_SUPPORTED
extern PNG_EXPORT(void,xpng_set_gAMA) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, double file_gamma));
#endif
extern PNG_EXPORT(void,xpng_set_gAMA_fixed) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_fixed_point int_file_gamma));
#endif

#if defined(PNG_hIST_SUPPORTED)
extern PNG_EXPORT(xpng_uint_32,xpng_get_hIST) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_uint_16p *hist));
#endif

#if defined(PNG_hIST_SUPPORTED)
extern PNG_EXPORT(void,xpng_set_hIST) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_uint_16p hist));
#endif

extern PNG_EXPORT(xpng_uint_32,xpng_get_IHDR) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_uint_32 *width, xpng_uint_32 *height,
   int *bit_depth, int *color_type, int *interlace_method,
   int *compression_method, int *filter_method));

extern PNG_EXPORT(void,xpng_set_IHDR) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_uint_32 width, xpng_uint_32 height, int bit_depth,
   int color_type, int interlace_method, int compression_method,
   int filter_method));

#if defined(PNG_oFFs_SUPPORTED)
extern PNG_EXPORT(xpng_uint_32,xpng_get_oFFs) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_int_32 *offset_x, xpng_int_32 *offset_y,
   int *unit_type));
#endif

#if defined(PNG_oFFs_SUPPORTED)
extern PNG_EXPORT(void,xpng_set_oFFs) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_int_32 offset_x, xpng_int_32 offset_y,
   int unit_type));
#endif

#if defined(PNG_pCAL_SUPPORTED)
extern PNG_EXPORT(xpng_uint_32,xpng_get_pCAL) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_charp *purpose, xpng_int_32 *X0, xpng_int_32 *X1,
   int *type, int *nparams, xpng_charp *units, xpng_charpp *params));
#endif

#if defined(PNG_pCAL_SUPPORTED)
extern PNG_EXPORT(void,xpng_set_pCAL) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_charp purpose, xpng_int_32 X0, xpng_int_32 X1,
   int type, int nparams, xpng_charp units, xpng_charpp params));
#endif

#if defined(PNG_pHYs_SUPPORTED)
extern PNG_EXPORT(xpng_uint_32,xpng_get_pHYs) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_uint_32 *res_x, xpng_uint_32 *res_y, int *unit_type));
#endif

#if defined(PNG_pHYs_SUPPORTED)
extern PNG_EXPORT(void,xpng_set_pHYs) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_uint_32 res_x, xpng_uint_32 res_y, int unit_type));
#endif

extern PNG_EXPORT(xpng_uint_32,xpng_get_PLTE) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_colorp *palette, int *num_palette));

extern PNG_EXPORT(void,xpng_set_PLTE) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_colorp palette, int num_palette));

#if defined(PNG_sBIT_SUPPORTED)
extern PNG_EXPORT(xpng_uint_32,xpng_get_sBIT) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_color_8p *sig_bit));
#endif

#if defined(PNG_sBIT_SUPPORTED)
extern PNG_EXPORT(void,xpng_set_sBIT) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_color_8p sig_bit));
#endif

#if defined(PNG_sRGB_SUPPORTED)
extern PNG_EXPORT(xpng_uint_32,xpng_get_sRGB) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, int *intent));
#endif

#if defined(PNG_sRGB_SUPPORTED)
extern PNG_EXPORT(void,xpng_set_sRGB) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, int intent));
extern PNG_EXPORT(void,xpng_set_sRGB_gAMA_and_cHRM) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, int intent));
#endif

#if defined(PNG_iCCP_SUPPORTED)
extern PNG_EXPORT(xpng_uint_32,xpng_get_iCCP) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_charpp name, int *compression_type,
   xpng_charpp profile, xpng_uint_32 *proflen));
   /* Note to maintainer: profile should be xpng_bytepp */
#endif

#if defined(PNG_iCCP_SUPPORTED)
extern PNG_EXPORT(void,xpng_set_iCCP) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_charp name, int compression_type,
   xpng_charp profile, xpng_uint_32 proflen));
   /* Note to maintainer: profile should be xpng_bytep */
#endif

#if defined(PNG_sPLT_SUPPORTED)
extern PNG_EXPORT(xpng_uint_32,xpng_get_sPLT) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_sPLT_tpp entries));
#endif

#if defined(PNG_sPLT_SUPPORTED)
extern PNG_EXPORT(void,xpng_set_sPLT) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_sPLT_tp entries, int nentries));
#endif

#if defined(PNG_TEXT_SUPPORTED)
/* xpng_get_text also returns the number of text chunks in *num_text */
extern PNG_EXPORT(xpng_uint_32,xpng_get_text) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_textp *text_ptr, int *num_text));
#endif

/*
 *  Note while xpng_set_text() will accept a structure whose text,
 *  language, and  translated keywords are NULL pointers, the structure
 *  returned by xpng_get_text will always contain regular
 *  zero-terminated C strings.  They might be empty strings but
 *  they will never be NULL pointers.
 */

#if defined(PNG_TEXT_SUPPORTED)
extern PNG_EXPORT(void,xpng_set_text) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_textp text_ptr, int num_text));
#endif

#if defined(PNG_tIME_SUPPORTED)
extern PNG_EXPORT(xpng_uint_32,xpng_get_tIME) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_timep *mod_time));
#endif

#if defined(PNG_tIME_SUPPORTED)
extern PNG_EXPORT(void,xpng_set_tIME) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_timep mod_time));
#endif

#if defined(PNG_tRNS_SUPPORTED)
extern PNG_EXPORT(xpng_uint_32,xpng_get_tRNS) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_bytep *trans, int *num_trans,
   xpng_color_16p *trans_values));
#endif

#if defined(PNG_tRNS_SUPPORTED)
extern PNG_EXPORT(void,xpng_set_tRNS) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_bytep trans, int num_trans,
   xpng_color_16p trans_values));
#endif

#if defined(PNG_tRNS_SUPPORTED)
#endif

#if defined(PNG_sCAL_SUPPORTED)
#ifdef PNG_FLOATING_POINT_SUPPORTED
extern PNG_EXPORT(xpng_uint_32,xpng_get_sCAL) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, int *unit, double *width, double *height));
#else
#ifdef PNG_FIXED_POINT_SUPPORTED
extern PNG_EXPORT(xpng_uint_32,xpng_get_sCAL_s) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, int *unit, xpng_charpp swidth, xpng_charpp sheight));
#endif
#endif
#endif /* PNG_sCAL_SUPPORTED */

#if defined(PNG_sCAL_SUPPORTED)
#ifdef PNG_FLOATING_POINT_SUPPORTED
extern PNG_EXPORT(void,xpng_set_sCAL) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, int unit, double width, double height));
#endif
#ifdef PNG_FIXED_POINT_SUPPORTED
extern PNG_EXPORT(void,xpng_set_sCAL_s) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, int unit, xpng_charp swidth, xpng_charp sheight));
#endif
#endif /* PNG_sCAL_SUPPORTED || PNG_WRITE_sCAL_SUPPORTED */

#if defined(PNG_UNKNOWN_CHUNKS_SUPPORTED)
/* provide a list of chunks and how they are to be handled, if the built-in
   handling or default unknown chunk handling is not desired.  Any chunks not
   listed will be handled in the default manner.  The IHDR and IEND chunks
   must not be listed.
      keep = 0: follow default behavour
           = 1: do not keep
           = 2: keep only if safe-to-copy
           = 3: keep even if unsafe-to-copy
*/
extern PNG_EXPORT(void, xpng_set_keep_unknown_chunks) PNGARG((xpng_structp
   xpng_ptr, int keep, xpng_bytep chunk_list, int num_chunks));
extern PNG_EXPORT(void, xpng_set_unknown_chunks) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_unknown_chunkp unknowns, int num_unknowns));
extern PNG_EXPORT(void, xpng_set_unknown_chunk_location)
   PNGARG((xpng_structp xpng_ptr, xpng_infop info_ptr, int chunk, int location));
extern PNG_EXPORT(xpng_uint_32,xpng_get_unknown_chunks) PNGARG((xpng_structp
   xpng_ptr, xpng_infop info_ptr, xpng_unknown_chunkpp entries));
#endif
#ifdef PNG_HANDLE_AS_UNKNOWN_SUPPORTED
PNG_EXPORT(int,xpng_handle_as_unknown) PNGARG((xpng_structp xpng_ptr, xpng_bytep
   chunk_name));
#endif

/* Png_free_data() will turn off the "valid" flag for anything it frees.
   If you need to turn it off for a chunk that your application has freed,
   you can use xpng_set_invalid(xpng_ptr, info_ptr, PNG_INFO_CHNK); */
extern PNG_EXPORT(void, xpng_set_invalid) PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, int mask));

#if defined(PNG_INFO_IMAGE_SUPPORTED)
/* The "params" pointer is currently not used and is for future expansion. */
extern PNG_EXPORT(void, xpng_read_png) PNGARG((xpng_structp xpng_ptr,
                        xpng_infop info_ptr,
                        int transforms,
                        xpng_voidp params));
extern PNG_EXPORT(void, xpng_write_png) PNGARG((xpng_structp xpng_ptr,
                        xpng_infop info_ptr,
                        int transforms,
                        xpng_voidp params));
#endif

/* Define PNG_DEBUG at compile time for debugging information.  Higher
 * numbers for PNG_DEBUG mean more debugging information.  This has
 * only been added since version 0.95 so it is not implemented throughout
 * libpng yet, but more support will be added as needed.
 */
#ifdef PNG_DEBUG
#if (PNG_DEBUG > 0)
#if !defined(PNG_DEBUG_FILE) && defined(_MSC_VER)
#include <crtdbg.h>
#if (PNG_DEBUG > 1)
#define xpng_debug(l,m)  _RPT0(_CRT_WARN,m)
#define xpng_debug1(l,m,p1)  _RPT1(_CRT_WARN,m,p1)
#define xpng_debug2(l,m,p1,p2) _RPT2(_CRT_WARN,m,p1,p2)
#endif
#else /* PNG_DEBUG_FILE || !_MSC_VER */
#ifndef PNG_DEBUG_FILE
#define PNG_DEBUG_FILE stderr
#endif /* PNG_DEBUG_FILE */
#if (PNG_DEBUG > 1)
#define xpng_debug(l,m) \
{ \
     int num_tabs=l; \
     fprintf(PNG_DEBUG_FILE,"%s"m,(num_tabs==1 ? "\t" : \
       (num_tabs==2 ? "\t\t":(num_tabs>2 ? "\t\t\t":"")))); \
}
#define xpng_debug1(l,m,p1) \
{ \
     int num_tabs=l; \
     fprintf(PNG_DEBUG_FILE,"%s"m,(num_tabs==1 ? "\t" : \
       (num_tabs==2 ? "\t\t":(num_tabs>2 ? "\t\t\t":""))),p1); \
}
#define xpng_debug2(l,m,p1,p2) \
{ \
     int num_tabs=l; \
     fprintf(PNG_DEBUG_FILE,"%s"m,(num_tabs==1 ? "\t" : \
       (num_tabs==2 ? "\t\t":(num_tabs>2 ? "\t\t\t":""))),p1,p2); \
}
#endif /* (PNG_DEBUG > 1) */
#endif /* _MSC_VER */
#endif /* (PNG_DEBUG > 0) */
#endif /* PNG_DEBUG */
#ifndef xpng_debug
#define xpng_debug(l, m)
#endif
#ifndef xpng_debug1
#define xpng_debug1(l, m, p1)
#endif
#ifndef xpng_debug2
#define xpng_debug2(l, m, p1, p2)
#endif

extern PNG_EXPORT(xpng_bytep,xpng_sig_bytes) PNGARG((void));

extern PNG_EXPORT(xpng_charp,xpng_get_copyright) PNGARG((xpng_structp xpng_ptr));
extern PNG_EXPORT(xpng_charp,xpng_get_header_ver) PNGARG((xpng_structp xpng_ptr));
extern PNG_EXPORT(xpng_charp,xpng_get_header_version) PNGARG((xpng_structp xpng_ptr));
extern PNG_EXPORT(xpng_charp,xpng_get_libxpng_ver) PNGARG((xpng_structp xpng_ptr));

#ifdef PNG_MNG_FEATURES_SUPPORTED
extern PNG_EXPORT(xpng_uint_32,xpng_permit_mng_features) PNGARG((xpng_structp
   xpng_ptr, xpng_uint_32 mng_features_permitted));
#endif

/* Added to version 1.2.0 */
#if defined(PNG_ASSEMBLER_CODE_SUPPORTED)
#define PNG_ASM_FLAG_MMX_SUPPORT_COMPILED  0x01  /* not user-settable */
#define PNG_ASM_FLAG_MMX_SUPPORT_IN_CPU    0x02  /* not user-settable */
#define PNG_ASM_FLAG_MMX_READ_COMBINE_ROW  0x04
#define PNG_ASM_FLAG_MMX_READ_INTERLACE    0x08
#define PNG_ASM_FLAG_MMX_READ_FILTER_SUB   0x10
#define PNG_ASM_FLAG_MMX_READ_FILTER_UP    0x20
#define PNG_ASM_FLAG_MMX_READ_FILTER_AVG   0x40
#define PNG_ASM_FLAG_MMX_READ_FILTER_PAETH 0x80
#define PNG_ASM_FLAGS_INITIALIZED          0x80000000  /* not user-settable */

#define PNG_MMX_READ_FLAGS ( PNG_ASM_FLAG_MMX_READ_COMBINE_ROW  \
                           | PNG_ASM_FLAG_MMX_READ_INTERLACE    \
                           | PNG_ASM_FLAG_MMX_READ_FILTER_SUB   \
                           | PNG_ASM_FLAG_MMX_READ_FILTER_UP    \
                           | PNG_ASM_FLAG_MMX_READ_FILTER_AVG   \
                           | PNG_ASM_FLAG_MMX_READ_FILTER_PAETH )
#define PNG_MMX_WRITE_FLAGS ( 0 )

#define PNG_MMX_FLAGS ( PNG_ASM_FLAG_MMX_SUPPORT_COMPILED \
                      | PNG_ASM_FLAG_MMX_SUPPORT_IN_CPU   \
                      | PNG_MMX_READ_FLAGS                \
                      | PNG_MMX_WRITE_FLAGS )

#define PNG_SELECT_READ   1
#define PNG_SELECT_WRITE  2


#if !defined(PNG_1_0_X)
/* pngget.c */
extern PNG_EXPORT(xpng_uint_32,xpng_get_mmx_flagmask)
   PNGARG((int flag_select, int *compilerID));

/* pngget.c */
extern PNG_EXPORT(xpng_uint_32,xpng_get_asm_flagmask)
   PNGARG((int flag_select));

/* pngget.c */
extern PNG_EXPORT(xpng_uint_32,xpng_get_asm_flags)
   PNGARG((xpng_structp xpng_ptr));

/* pngget.c */
extern PNG_EXPORT(xpng_byte,xpng_get_mmx_bitdepth_threshold)
   PNGARG((xpng_structp xpng_ptr));

/* pngget.c */
extern PNG_EXPORT(xpng_uint_32,xpng_get_mmx_rowbytes_threshold)
   PNGARG((xpng_structp xpng_ptr));

/* pngset.c */
extern PNG_EXPORT(void,xpng_set_asm_flags)
   PNGARG((xpng_structp xpng_ptr, xpng_uint_32 asm_flags));

/* pngset.c */
extern PNG_EXPORT(void,xpng_set_mmx_thresholds)
   PNGARG((xpng_structp xpng_ptr, xpng_byte mmx_bitdepth_threshold,
   xpng_uint_32 mmx_rowbytes_threshold));

#endif /* PNG_1_0_X */
#endif /* PNG_ASSEMBLER_CODE_SUPPORTED */

#if !defined(PNG_1_0_X)
/* png.c, pnggccrd.c, or pngvcrd.c */
extern PNG_EXPORT(int,xpng_mmx_support) PNGARG((void));

/* Strip the prepended error numbers ("#nnn ") from error and warning
 * messages before passing them to the error or warning handler. */
#ifdef PNG_ERROR_NUMBERS_SUPPORTED
extern PNG_EXPORT(void,xpng_set_strip_error_numbers) PNGARG((xpng_structp
   xpng_ptr, xpng_uint_32 strip_mode));
#endif
#endif /* PNG_1_0_X */

/* Maintainer: Put new public prototypes here ^, in libpng.3, and project defs */

#define PNG_HEADER_VERSION_STRING \
   " libpng version 1.2.5 - October 3, 2002 (header)\n"

#ifdef PNG_READ_COMPOSITE_NODIV_SUPPORTED
/* With these routines we avoid an integer divide, which will be slower on
 * most machines.  However, it does take more operations than the corresponding
 * divide method, so it may be slower on a few RISC systems.  There are two
 * shifts (by 8 or 16 bits) and an addition, versus a single integer divide.
 *
 * Note that the rounding factors are NOT supposed to be the same!  128 and
 * 32768 are correct for the NODIV code; 127 and 32767 are correct for the
 * standard method.
 *
 * [Optimized code by Greg Roelofs and Mark Adler...blame us for bugs. :-) ]
 */

 /* fg and bg should be in `gamma 1.0' space; alpha is the opacity          */

#  define xpng_composite(composite, fg, alpha, bg)                            \
     { xpng_uint_16 temp = (xpng_uint_16)((xpng_uint_16)(fg) * (xpng_uint_16)(alpha) \
                        +        (xpng_uint_16)(bg)*(xpng_uint_16)(255 -       \
                        (xpng_uint_16)(alpha)) + (xpng_uint_16)128);           \
       (composite) = (xpng_byte)((temp + (temp >> 8)) >> 8); }

#  define xpng_composite_16(composite, fg, alpha, bg)                         \
     { xpng_uint_32 temp = (xpng_uint_32)((xpng_uint_32)(fg) * (xpng_uint_32)(alpha) \
                        + (xpng_uint_32)(bg)*(xpng_uint_32)(65535L -           \
                        (xpng_uint_32)(alpha)) + (xpng_uint_32)32768L);        \
       (composite) = (xpng_uint_16)((temp + (temp >> 16)) >> 16); }

#else  /* standard method using integer division */

#  define xpng_composite(composite, fg, alpha, bg)                            \
     (composite) = (xpng_byte)(((xpng_uint_16)(fg) * (xpng_uint_16)(alpha) +    \
       (xpng_uint_16)(bg) * (xpng_uint_16)(255 - (xpng_uint_16)(alpha)) +       \
       (xpng_uint_16)127) / 255)

#  define xpng_composite_16(composite, fg, alpha, bg)                         \
     (composite) = (xpng_uint_16)(((xpng_uint_32)(fg) * (xpng_uint_32)(alpha) + \
       (xpng_uint_32)(bg)*(xpng_uint_32)(65535L - (xpng_uint_32)(alpha)) +      \
       (xpng_uint_32)32767) / (xpng_uint_32)65535L)

#endif /* PNG_READ_COMPOSITE_NODIV_SUPPORTED */

/* These next functions are used internally in the code.  They generally
 * shouldn't be used unless you are writing code to add or replace some
 * functionality in libpng.  More information about most functions can
 * be found in the files where the functions are located.
 */

#if defined(PNG_INTERNAL)

/* Various modes of operation.  Note that after an init, mode is set to
 * zero automatically when the structure is created.
 */
#define PNG_HAVE_IHDR               0x01
#define PNG_HAVE_PLTE               0x02
#define PNG_HAVE_IDAT               0x04
#define PNG_AFTER_IDAT              0x08
#define PNG_HAVE_IEND               0x10
#define PNG_HAVE_gAMA               0x20
#define PNG_HAVE_cHRM               0x40
#define PNG_HAVE_sRGB               0x80
#define PNG_HAVE_CHUNK_HEADER      0x100
#define PNG_WROTE_tIME             0x200
#define PNG_WROTE_INFO_BEFORE_PLTE 0x400
#define PNG_BACKGROUND_IS_GRAY     0x800
#define PNG_HAVE_PNG_SIGNATURE    0x1000

/* flags for the transformations the PNG library does on the image data */
#define PNG_BGR                0x0001
#define PNG_INTERLACE          0x0002
#define PNG_PACK               0x0004
#define PNG_SHIFT              0x0008
#define PNG_SWAP_BYTES         0x0010
#define PNG_INVERT_MONO        0x0020
#define PNG_DITHER             0x0040
#define PNG_BACKGROUND         0x0080
#define PNG_BACKGROUND_EXPAND  0x0100
                          /*   0x0200 unused */
#define PNG_16_TO_8            0x0400
#define PNG_RGBA               0x0800
#define PNG_EXPAND             0x1000
#define PNG_GAMMA              0x2000
#define PNG_GRAY_TO_RGB        0x4000
#define PNG_FILLER             0x8000L
#define PNG_PACKSWAP          0x10000L
#define PNG_SWAP_ALPHA        0x20000L
#define PNG_STRIP_ALPHA       0x40000L
#define PNG_INVERT_ALPHA      0x80000L
#define PNG_USER_TRANSFORM   0x100000L
#define PNG_RGB_TO_GRAY_ERR  0x200000L
#define PNG_RGB_TO_GRAY_WARN 0x400000L
#define PNG_RGB_TO_GRAY      0x600000L  /* two bits, RGB_TO_GRAY_ERR|WARN */

/* flags for xpng_create_struct */
#define PNG_STRUCT_PNG   0x0001
#define PNG_STRUCT_INFO  0x0002

/* Scaling factor for filter heuristic weighting calculations */
#define PNG_WEIGHT_SHIFT 8
#define PNG_WEIGHT_FACTOR (1<<(PNG_WEIGHT_SHIFT))
#define PNG_COST_SHIFT 3
#define PNG_COST_FACTOR (1<<(PNG_COST_SHIFT))

/* flags for the xpng_ptr->flags rather than declaring a byte for each one */
#define PNG_FLAG_ZLIB_CUSTOM_STRATEGY     0x0001
#define PNG_FLAG_ZLIB_CUSTOM_LEVEL        0x0002
#define PNG_FLAG_ZLIB_CUSTOM_MEM_LEVEL    0x0004
#define PNG_FLAG_ZLIB_CUSTOM_WINDOW_BITS  0x0008
#define PNG_FLAG_ZLIB_CUSTOM_METHOD       0x0010
#define PNG_FLAG_ZLIB_FINISHED            0x0020
#define PNG_FLAG_ROW_INIT                 0x0040
#define PNG_FLAG_FILLER_AFTER             0x0080
#define PNG_FLAG_CRC_ANCILLARY_USE        0x0100
#define PNG_FLAG_CRC_ANCILLARY_NOWARN     0x0200
#define PNG_FLAG_CRC_CRITICAL_USE         0x0400
#define PNG_FLAG_CRC_CRITICAL_IGNORE      0x0800
#define PNG_FLAG_FREE_PLTE                0x1000
#define PNG_FLAG_FREE_TRNS                0x2000
#define PNG_FLAG_FREE_HIST                0x4000
#define PNG_FLAG_KEEP_UNKNOWN_CHUNKS      0x8000L
#define PNG_FLAG_KEEP_UNSAFE_CHUNKS       0x10000L
#define PNG_FLAG_LIBRARY_MISMATCH         0x20000L
#define PNG_FLAG_STRIP_ERROR_NUMBERS      0x40000L
#define PNG_FLAG_STRIP_ERROR_TEXT         0x80000L
#define PNG_FLAG_MALLOC_NULL_MEM_OK       0x100000L

/* For use in xpng_set_keep_unknown, xpng_handle_as_unknown */
#define HANDLE_CHUNK_AS_DEFAULT   0
#define HANDLE_CHUNK_NEVER        1
#define HANDLE_CHUNK_IF_SAFE      2
#define HANDLE_CHUNK_ALWAYS       3

#define PNG_FLAG_CRC_ANCILLARY_MASK (PNG_FLAG_CRC_ANCILLARY_USE | \
                                     PNG_FLAG_CRC_ANCILLARY_NOWARN)

#define PNG_FLAG_CRC_CRITICAL_MASK  (PNG_FLAG_CRC_CRITICAL_USE | \
                                     PNG_FLAG_CRC_CRITICAL_IGNORE)

#define PNG_FLAG_CRC_MASK           (PNG_FLAG_CRC_ANCILLARY_MASK | \
                                     PNG_FLAG_CRC_CRITICAL_MASK)

/* save typing and make code easier to understand */
#define PNG_COLOR_DIST(c1, c2) (abs((int)((c1).red) - (int)((c2).red)) + \
   abs((int)((c1).green) - (int)((c2).green)) + \
   abs((int)((c1).blue) - (int)((c2).blue)))

/* variables declared in png.c - only it needs to define PNG_NO_EXTERN */
#if !defined(PNG_NO_EXTERN) || defined(PNG_ALWAYS_EXTERN)
/* place to hold the signature string for a PNG file. */
#ifdef PNG_USE_GLOBAL_ARRAYS
   PNG_EXPORT_VAR (const xpng_byte FARDATA) xpng_sig[8];
#else
#define xpng_sig xpng_sig_bytes(NULL)
#endif
#endif /* PNG_NO_EXTERN */

/* Constant strings for known chunk types.  If you need to add a chunk,
 * define the name here, and add an invocation of the macro in png.c and
 * wherever it's needed.
 */
#define PNG_IHDR const xpng_byte xpng_IHDR[5] = { 73,  72,  68,  82, '\0'}
#define PNG_IDAT const xpng_byte xpng_IDAT[5] = { 73,  68,  65,  84, '\0'}
#define PNG_IEND const xpng_byte xpng_IEND[5] = { 73,  69,  78,  68, '\0'}
#define PNG_PLTE const xpng_byte xpng_PLTE[5] = { 80,  76,  84,  69, '\0'}
#define PNG_bKGD const xpng_byte xpng_bKGD[5] = { 98,  75,  71,  68, '\0'}
#define PNG_cHRM const xpng_byte xpng_cHRM[5] = { 99,  72,  82,  77, '\0'}
#define PNG_gAMA const xpng_byte xpng_gAMA[5] = {103,  65,  77,  65, '\0'}
#define PNG_hIST const xpng_byte xpng_hIST[5] = {104,  73,  83,  84, '\0'}
#define PNG_iCCP const xpng_byte xpng_iCCP[5] = {105,  67,  67,  80, '\0'}
#define PNG_iTXt const xpng_byte xpng_iTXt[5] = {105,  84,  88, 116, '\0'}
#define PNG_oFFs const xpng_byte xpng_oFFs[5] = {111,  70,  70, 115, '\0'}
#define PNG_pCAL const xpng_byte xpng_pCAL[5] = {112,  67,  65,  76, '\0'}
#define PNG_sCAL const xpng_byte xpng_sCAL[5] = {115,  67,  65,  76, '\0'}
#define PNG_pHYs const xpng_byte xpng_pHYs[5] = {112,  72,  89, 115, '\0'}
#define PNG_sBIT const xpng_byte xpng_sBIT[5] = {115,  66,  73,  84, '\0'}
#define PNG_sPLT const xpng_byte xpng_sPLT[5] = {115,  80,  76,  84, '\0'}
#define PNG_sRGB const xpng_byte xpng_sRGB[5] = {115,  82,  71,  66, '\0'}
#define PNG_tEXt const xpng_byte xpng_tEXt[5] = {116,  69,  88, 116, '\0'}
#define PNG_tIME const xpng_byte xpng_tIME[5] = {116,  73,  77,  69, '\0'}
#define PNG_tRNS const xpng_byte xpng_tRNS[5] = {116,  82,  78,  83, '\0'}
#define PNG_zTXt const xpng_byte xpng_zTXt[5] = {122,  84,  88, 116, '\0'}

#ifdef PNG_USE_GLOBAL_ARRAYS
PNG_EXPORT_VAR (const xpng_byte FARDATA) xpng_IHDR[5];
PNG_EXPORT_VAR (const xpng_byte FARDATA) xpng_IDAT[5];
PNG_EXPORT_VAR (const xpng_byte FARDATA) xpng_IEND[5];
PNG_EXPORT_VAR (const xpng_byte FARDATA) xpng_PLTE[5];
PNG_EXPORT_VAR (const xpng_byte FARDATA) xpng_bKGD[5];
PNG_EXPORT_VAR (const xpng_byte FARDATA) xpng_cHRM[5];
PNG_EXPORT_VAR (const xpng_byte FARDATA) xpng_gAMA[5];
PNG_EXPORT_VAR (const xpng_byte FARDATA) xpng_hIST[5];
PNG_EXPORT_VAR (const xpng_byte FARDATA) xpng_iCCP[5];
PNG_EXPORT_VAR (const xpng_byte FARDATA) xpng_iTXt[5];
PNG_EXPORT_VAR (const xpng_byte FARDATA) xpng_oFFs[5];
PNG_EXPORT_VAR (const xpng_byte FARDATA) xpng_pCAL[5];
PNG_EXPORT_VAR (const xpng_byte FARDATA) xpng_sCAL[5];
PNG_EXPORT_VAR (const xpng_byte FARDATA) xpng_pHYs[5];
PNG_EXPORT_VAR (const xpng_byte FARDATA) xpng_sBIT[5];
PNG_EXPORT_VAR (const xpng_byte FARDATA) xpng_sPLT[5];
PNG_EXPORT_VAR (const xpng_byte FARDATA) xpng_sRGB[5];
PNG_EXPORT_VAR (const xpng_byte FARDATA) xpng_tEXt[5];
PNG_EXPORT_VAR (const xpng_byte FARDATA) xpng_tIME[5];
PNG_EXPORT_VAR (const xpng_byte FARDATA) xpng_tRNS[5];
PNG_EXPORT_VAR (const xpng_byte FARDATA) xpng_zTXt[5];
#endif /* PNG_USE_GLOBAL_ARRAYS */


/* Inline macros to do direct reads of bytes from the input buffer.  These
 * require that you are using an architecture that uses PNG byte ordering
 * (MSB first) and supports unaligned data storage.  I think that PowerPC
 * in big-endian mode and 680x0 are the only ones that will support this.
 * The x86 line of processors definitely do not.  The xpng_get_int_32()
 * routine also assumes we are using two's complement format for negative
 * values, which is almost certainly true.
 */
#if defined(PNG_READ_BIG_ENDIAN_SUPPORTED)
#  if defined(PNG_pCAL_SUPPORTED) || defined(PNG_oFFs_SUPPORTED)
#    define xpng_get_int_32(buf) ( *((xpng_int_32p) (buf)))
#  endif
#  define xpng_get_uint_32(buf) ( *((xpng_uint_32p) (buf)))
#  define xpng_get_uint_16(buf) ( *((xpng_uint_16p) (buf)))
#else
#  if defined(PNG_pCAL_SUPPORTED) || defined(PNG_oFFs_SUPPORTED)
PNG_EXTERN xpng_int_32 xpng_get_int_32 PNGARG((xpng_bytep buf));
#  endif
PNG_EXTERN xpng_uint_32 xpng_get_uint_32 PNGARG((xpng_bytep buf));
PNG_EXTERN xpng_uint_16 xpng_get_uint_16 PNGARG((xpng_bytep buf));
#endif /* !PNG_READ_BIG_ENDIAN_SUPPORTED */

/* Initialize xpng_ptr struct for reading, and allocate any other memory.
 * (old interface - DEPRECATED - use xpng_create_read_struct instead).
 */
extern PNG_EXPORT(void,xpng_read_init) PNGARG((xpng_structp xpng_ptr));
#undef xpng_read_init
#define xpng_read_init(xpng_ptr) xpng_read_init_3(&xpng_ptr, \
    PNG_LIBPNG_VER_STRING,  sizeof(xpng_struct));
extern PNG_EXPORT(void,xpng_read_init_3) PNGARG((xpng_structpp ptr_ptr,
    xpng_const_charp user_xpng_ver, xpng_size_t xpng_struct_size));
extern PNG_EXPORT(void,xpng_read_init_2) PNGARG((xpng_structp xpng_ptr,
    xpng_const_charp user_xpng_ver, xpng_size_t xpng_struct_size, xpng_size_t
    xpng_info_size));

/* Initialize xpng_ptr struct for writing, and allocate any other memory.
 * (old interface - DEPRECATED - use xpng_create_write_struct instead).
 */
extern PNG_EXPORT(void,xpng_write_init) PNGARG((xpng_structp xpng_ptr));
#undef xpng_write_init
#define xpng_write_init(xpng_ptr) xpng_write_init_3(&xpng_ptr, \
    PNG_LIBPNG_VER_STRING, sizeof(xpng_struct));
extern PNG_EXPORT(void,xpng_write_init_3) PNGARG((xpng_structpp ptr_ptr,
    xpng_const_charp user_xpng_ver, xpng_size_t xpng_struct_size));
extern PNG_EXPORT(void,xpng_write_init_2) PNGARG((xpng_structp xpng_ptr,
    xpng_const_charp user_xpng_ver, xpng_size_t xpng_struct_size, xpng_size_t
    xpng_info_size));

/* Allocate memory for an internal libpng struct */
PNG_EXTERN xpng_voidp xpng_create_struct PNGARG((int type));

/* Free memory from internal libpng struct */
PNG_EXTERN void xpng_destroy_struct PNGARG((xpng_voidp struct_ptr));

PNG_EXTERN xpng_voidp xpng_create_struct_2 PNGARG((int type, xpng_malloc_ptr
  malloc_fn, xpng_voidp mem_ptr));
PNG_EXTERN void xpng_destroy_struct_2 PNGARG((xpng_voidp struct_ptr,
   xpng_free_ptr free_fn, xpng_voidp mem_ptr));

/* Free any memory that info_ptr points to and reset struct. */
PNG_EXTERN void xpng_info_destroy PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr));

#ifndef PNG_1_0_X
/* Function to allocate memory for zlib. */
PNG_EXTERN voidpf xpng_zalloc PNGARG((voidpf xpng_ptr, uInt items, uInt size));

/* Function to free memory for zlib */
PNG_EXTERN void xpng_zfree PNGARG((voidpf xpng_ptr, voidpf ptr));

/* Next four functions are used internally as callbacks.  PNGAPI is required
 * but not PNG_EXPORT.  PNGAPI added at libpng version 1.2.3. */

PNG_EXTERN void PNGAPI xpng_default_read_data PNGARG((xpng_structp xpng_ptr,
   xpng_bytep data, xpng_size_t length));

#ifdef PNG_PROGRESSIVE_READ_SUPPORTED
PNG_EXTERN void PNGAPI xpng_push_fill_buffer PNGARG((xpng_structp xpng_ptr,
   xpng_bytep buffer, xpng_size_t length));
#endif

PNG_EXTERN void PNGAPI xpng_default_write_data PNGARG((xpng_structp xpng_ptr,
   xpng_bytep data, xpng_size_t length));

#if defined(PNG_WRITE_FLUSH_SUPPORTED)
#if !defined(PNG_NO_STDIO)
PNG_EXTERN void PNGAPI xpng_default_flush PNGARG((xpng_structp xpng_ptr));
#endif
#endif
#else /* PNG_1_0_X */
#ifdef PNG_PROGRESSIVE_READ_SUPPORTED
PNG_EXTERN void xpng_push_fill_buffer PNGARG((xpng_structp xpng_ptr,
   xpng_bytep buffer, xpng_size_t length));
#endif
#endif /* PNG_1_0_X */

/* Reset the CRC variable */
PNG_EXTERN void xpng_reset_crc PNGARG((xpng_structp xpng_ptr));

/* Write the "data" buffer to whatever output you are using. */
PNG_EXTERN void xpng_write_data PNGARG((xpng_structp xpng_ptr, xpng_bytep data,
   xpng_size_t length));

/* Read data from whatever input you are using into the "data" buffer */
PNG_EXTERN void xpng_read_data PNGARG((xpng_structp xpng_ptr, xpng_bytep data,
   xpng_size_t length));

/* Read bytes into buf, and update xpng_ptr->crc */
PNG_EXTERN void xpng_crc_read PNGARG((xpng_structp xpng_ptr, xpng_bytep buf,
   xpng_size_t length));

/* Decompress data in a chunk that uses compression */
#if defined(PNG_zTXt_SUPPORTED) || defined(PNG_iTXt_SUPPORTED) || \
    defined(PNG_iCCP_SUPPORTED) || defined(PNG_sPLT_SUPPORTED)
PNG_EXTERN xpng_charp xpng_decompress_chunk PNGARG((xpng_structp xpng_ptr,
   int comp_type, xpng_charp chunkdata, xpng_size_t chunklength,
   xpng_size_t prefix_length, xpng_size_t *data_length));
#endif

/* Read "skip" bytes, read the file crc, and (optionally) verify xpng_ptr->crc */
PNG_EXTERN int xpng_crc_finish PNGARG((xpng_structp xpng_ptr, xpng_uint_32 skip));

/* Read the CRC from the file and compare it to the libpng calculated CRC */
PNG_EXTERN int xpng_crc_error PNGARG((xpng_structp xpng_ptr));

/* Calculate the CRC over a section of data.  Note that we are only
 * passing a maximum of 64K on systems that have this as a memory limit,
 * since this is the maximum buffer size we can specify.
 */
PNG_EXTERN void xpng_calculate_crc PNGARG((xpng_structp xpng_ptr, xpng_bytep ptr,
   xpng_size_t length));

#if defined(PNG_WRITE_FLUSH_SUPPORTED)
PNG_EXTERN void xpng_flush PNGARG((xpng_structp xpng_ptr));
#endif


/* Place a 32-bit number into a buffer in PNG byte order (big-endian).
 * The only currently known PNG chunks that use signed numbers are
 * the ancillary extension chunks, oFFs and pCAL.
 */
PNG_EXTERN void xpng_save_uint_32 PNGARG((xpng_bytep buf, xpng_uint_32 i));

#if defined(PNG_WRITE_pCAL_SUPPORTED) || defined(PNG_WRITE_oFFs_SUPPORTED)
PNG_EXTERN void xpng_save_int_32 PNGARG((xpng_bytep buf, xpng_int_32 i));
#endif

/* Place a 16-bit number into a buffer in PNG byte order.
 * The parameter is declared unsigned int, not xpng_uint_16,
 * just to avoid potential problems on pre-ANSI C compilers.
 */
PNG_EXTERN void xpng_save_uint_16 PNGARG((xpng_bytep buf, unsigned int i));

/* simple function to write the signature */
PNG_EXTERN void xpng_write_sig PNGARG((xpng_structp xpng_ptr));

/* write various chunks */

/* Write the IHDR chunk, and update the xpng_struct with the necessary
 * information.
 */
PNG_EXTERN void xpng_write_IHDR PNGARG((xpng_structp xpng_ptr, xpng_uint_32 width,
   xpng_uint_32 height,
   int bit_depth, int color_type, int compression_method, int filter_method,
   int interlace_method));

PNG_EXTERN void xpng_write_PLTE PNGARG((xpng_structp xpng_ptr, xpng_colorp palette,
   xpng_uint_32 num_pal));

PNG_EXTERN void xpng_write_IDAT PNGARG((xpng_structp xpng_ptr, xpng_bytep data,
   xpng_size_t length));

PNG_EXTERN void xpng_write_IEND PNGARG((xpng_structp xpng_ptr));

#if defined(PNG_WRITE_gAMA_SUPPORTED)
#ifdef PNG_FLOATING_POINT_SUPPORTED
PNG_EXTERN void xpng_write_gAMA PNGARG((xpng_structp xpng_ptr, double file_gamma));
#endif
#ifdef PNG_FIXED_POINT_SUPPORTED
PNG_EXTERN void xpng_write_gAMA_fixed PNGARG((xpng_structp xpng_ptr, xpng_fixed_point
    file_gamma));
#endif
#endif

#if defined(PNG_WRITE_sBIT_SUPPORTED)
PNG_EXTERN void xpng_write_sBIT PNGARG((xpng_structp xpng_ptr, xpng_color_8p sbit,
   int color_type));
#endif

#if defined(PNG_WRITE_cHRM_SUPPORTED)
#ifdef PNG_FLOATING_POINT_SUPPORTED
PNG_EXTERN void xpng_write_cHRM PNGARG((xpng_structp xpng_ptr,
   double white_x, double white_y,
   double red_x, double red_y, double green_x, double green_y,
   double blue_x, double blue_y));
#endif
#ifdef PNG_FIXED_POINT_SUPPORTED
PNG_EXTERN void xpng_write_cHRM_fixed PNGARG((xpng_structp xpng_ptr,
   xpng_fixed_point int_white_x, xpng_fixed_point int_white_y,
   xpng_fixed_point int_red_x, xpng_fixed_point int_red_y, xpng_fixed_point
   int_green_x, xpng_fixed_point int_green_y, xpng_fixed_point int_blue_x,
   xpng_fixed_point int_blue_y));
#endif
#endif

#if defined(PNG_WRITE_sRGB_SUPPORTED)
PNG_EXTERN void xpng_write_sRGB PNGARG((xpng_structp xpng_ptr,
   int intent));
#endif

#if defined(PNG_WRITE_iCCP_SUPPORTED)
PNG_EXTERN void xpng_write_iCCP PNGARG((xpng_structp xpng_ptr,
   xpng_charp name, int compression_type,
   xpng_charp profile, int proflen));
   /* Note to maintainer: profile should be xpng_bytep */
#endif

#if defined(PNG_WRITE_sPLT_SUPPORTED)
PNG_EXTERN void xpng_write_sPLT PNGARG((xpng_structp xpng_ptr,
   xpng_sPLT_tp palette));
#endif

#if defined(PNG_WRITE_tRNS_SUPPORTED)
PNG_EXTERN void xpng_write_tRNS PNGARG((xpng_structp xpng_ptr, xpng_bytep trans,
   xpng_color_16p values, int number, int color_type));
#endif

#if defined(PNG_WRITE_bKGD_SUPPORTED)
PNG_EXTERN void xpng_write_bKGD PNGARG((xpng_structp xpng_ptr,
   xpng_color_16p values, int color_type));
#endif

#if defined(PNG_WRITE_hIST_SUPPORTED)
PNG_EXTERN void xpng_write_hIST PNGARG((xpng_structp xpng_ptr, xpng_uint_16p hist,
   int num_hist));
#endif

#if defined(PNG_WRITE_TEXT_SUPPORTED) || defined(PNG_WRITE_pCAL_SUPPORTED) || \
    defined(PNG_WRITE_iCCP_SUPPORTED) || defined(PNG_WRITE_sPLT_SUPPORTED)
PNG_EXTERN xpng_size_t xpng_check_keyword PNGARG((xpng_structp xpng_ptr,
   xpng_charp key, xpng_charpp new_key));
#endif

#if defined(PNG_WRITE_tEXt_SUPPORTED)
PNG_EXTERN void xpng_write_tEXt PNGARG((xpng_structp xpng_ptr, xpng_charp key,
   xpng_charp text, xpng_size_t text_len));
#endif

#if defined(PNG_WRITE_zTXt_SUPPORTED)
PNG_EXTERN void xpng_write_zTXt PNGARG((xpng_structp xpng_ptr, xpng_charp key,
   xpng_charp text, xpng_size_t text_len, int compression));
#endif

#if defined(PNG_WRITE_iTXt_SUPPORTED)
PNG_EXTERN void xpng_write_iTXt PNGARG((xpng_structp xpng_ptr,
   int compression, xpng_charp key, xpng_charp lang, xpng_charp lang_key,
   xpng_charp text));
#endif

#if defined(PNG_TEXT_SUPPORTED)  /* Added at version 1.0.14 and 1.2.4 */
PNG_EXTERN int xpng_set_text_2 PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_textp text_ptr, int num_text));
#endif

#if defined(PNG_WRITE_oFFs_SUPPORTED)
PNG_EXTERN void xpng_write_oFFs PNGARG((xpng_structp xpng_ptr,
   xpng_int_32 x_offset, xpng_int_32 y_offset, int unit_type));
#endif

#if defined(PNG_WRITE_pCAL_SUPPORTED)
PNG_EXTERN void xpng_write_pCAL PNGARG((xpng_structp xpng_ptr, xpng_charp purpose,
   xpng_int_32 X0, xpng_int_32 X1, int type, int nparams,
   xpng_charp units, xpng_charpp params));
#endif

#if defined(PNG_WRITE_pHYs_SUPPORTED)
PNG_EXTERN void xpng_write_pHYs PNGARG((xpng_structp xpng_ptr,
   xpng_uint_32 x_pixels_per_unit, xpng_uint_32 y_pixels_per_unit,
   int unit_type));
#endif

#if defined(PNG_WRITE_tIME_SUPPORTED)
PNG_EXTERN void xpng_write_tIME PNGARG((xpng_structp xpng_ptr,
   xpng_timep mod_time));
#endif

#if defined(PNG_WRITE_sCAL_SUPPORTED)
#if defined(PNG_FLOATING_POINT_SUPPORTED) && !defined(PNG_NO_STDIO)
PNG_EXTERN void xpng_write_sCAL PNGARG((xpng_structp xpng_ptr,
   int unit, double width, double height));
#else
#ifdef PNG_FIXED_POINT_SUPPORTED
PNG_EXTERN void xpng_write_sCAL_s PNGARG((xpng_structp xpng_ptr,
   int unit, xpng_charp width, xpng_charp height));
#endif
#endif
#endif

/* Called when finished processing a row of data */
PNG_EXTERN void xpng_write_finish_row PNGARG((xpng_structp xpng_ptr));

/* Internal use only.   Called before first row of data */
PNG_EXTERN void xpng_write_start_row PNGARG((xpng_structp xpng_ptr));

#if defined(PNG_READ_GAMMA_SUPPORTED)
PNG_EXTERN void xpng_build_gamma_table PNGARG((xpng_structp xpng_ptr));
#endif

/* combine a row of data, dealing with alpha, etc. if requested */
PNG_EXTERN void xpng_combine_row PNGARG((xpng_structp xpng_ptr, xpng_bytep row,
   int mask));

#if defined(PNG_READ_INTERLACING_SUPPORTED)
/* expand an interlaced row */
/* OLD pre-1.0.9 interface:
PNG_EXTERN void xpng_do_read_interlace PNGARG((xpng_row_infop row_info,
   xpng_bytep row, int pass, xpng_uint_32 transformations));
 */
PNG_EXTERN void xpng_do_read_interlace PNGARG((xpng_structp xpng_ptr));
#endif

/* GRR TO DO (2.0 or whenever):  simplify other internal calling interfaces */

#if defined(PNG_WRITE_INTERLACING_SUPPORTED)
/* grab pixels out of a row for an interlaced pass */
PNG_EXTERN void xpng_do_write_interlace PNGARG((xpng_row_infop row_info,
   xpng_bytep row, int pass));
#endif

/* unfilter a row */
PNG_EXTERN void xpng_read_filter_row PNGARG((xpng_structp xpng_ptr,
   xpng_row_infop row_info, xpng_bytep row, xpng_bytep prev_row, int filter));

/* Choose the best filter to use and filter the row data */
PNG_EXTERN void xpng_write_find_filter PNGARG((xpng_structp xpng_ptr,
   xpng_row_infop row_info));

/* Write out the filtered row. */
PNG_EXTERN void xpng_write_filtered_row PNGARG((xpng_structp xpng_ptr,
   xpng_bytep filtered_row));
/* finish a row while reading, dealing with interlacing passes, etc. */
PNG_EXTERN void xpng_read_finish_row PNGARG((xpng_structp xpng_ptr));

/* initialize the row buffers, etc. */
PNG_EXTERN void xpng_read_start_row PNGARG((xpng_structp xpng_ptr));
/* optional call to update the users info structure */
PNG_EXTERN void xpng_read_transform_info PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr));

/* these are the functions that do the transformations */
#if defined(PNG_READ_FILLER_SUPPORTED)
PNG_EXTERN void xpng_do_read_filler PNGARG((xpng_row_infop row_info,
   xpng_bytep row, xpng_uint_32 filler, xpng_uint_32 flags));
#endif

#if defined(PNG_READ_SWAP_ALPHA_SUPPORTED)
PNG_EXTERN void xpng_do_read_swap_alpha PNGARG((xpng_row_infop row_info,
   xpng_bytep row));
#endif

#if defined(PNG_WRITE_SWAP_ALPHA_SUPPORTED)
PNG_EXTERN void xpng_do_write_swap_alpha PNGARG((xpng_row_infop row_info,
   xpng_bytep row));
#endif

#if defined(PNG_READ_INVERT_ALPHA_SUPPORTED)
PNG_EXTERN void xpng_do_read_invert_alpha PNGARG((xpng_row_infop row_info,
   xpng_bytep row));
#endif

#if defined(PNG_WRITE_INVERT_ALPHA_SUPPORTED)
PNG_EXTERN void xpng_do_write_invert_alpha PNGARG((xpng_row_infop row_info,
   xpng_bytep row));
#endif

#if defined(PNG_WRITE_FILLER_SUPPORTED) || \
    defined(PNG_READ_STRIP_ALPHA_SUPPORTED)
PNG_EXTERN void xpng_do_strip_filler PNGARG((xpng_row_infop row_info,
   xpng_bytep row, xpng_uint_32 flags));
#endif

#if defined(PNG_READ_SWAP_SUPPORTED) || defined(PNG_WRITE_SWAP_SUPPORTED)
PNG_EXTERN void xpng_do_swap PNGARG((xpng_row_infop row_info, xpng_bytep row));
#endif

#if defined(PNG_READ_PACKSWAP_SUPPORTED) || defined(PNG_WRITE_PACKSWAP_SUPPORTED)
PNG_EXTERN void xpng_do_packswap PNGARG((xpng_row_infop row_info, xpng_bytep row));
#endif

#if defined(PNG_READ_RGB_TO_GRAY_SUPPORTED)
PNG_EXTERN int xpng_do_rgb_to_gray PNGARG((xpng_structp xpng_ptr, xpng_row_infop
   row_info, xpng_bytep row));
#endif

#if defined(PNG_READ_GRAY_TO_RGB_SUPPORTED)
PNG_EXTERN void xpng_do_gray_to_rgb PNGARG((xpng_row_infop row_info,
   xpng_bytep row));
#endif

#if defined(PNG_READ_PACK_SUPPORTED)
PNG_EXTERN void xpng_do_unpack PNGARG((xpng_row_infop row_info, xpng_bytep row));
#endif

#if defined(PNG_READ_SHIFT_SUPPORTED)
PNG_EXTERN void xpng_do_unshift PNGARG((xpng_row_infop row_info, xpng_bytep row,
   xpng_color_8p sig_bits));
#endif

#if defined(PNG_READ_INVERT_SUPPORTED) || defined(PNG_WRITE_INVERT_SUPPORTED)
PNG_EXTERN void xpng_do_invert PNGARG((xpng_row_infop row_info, xpng_bytep row));
#endif

#if defined(PNG_READ_16_TO_8_SUPPORTED)
PNG_EXTERN void xpng_do_chop PNGARG((xpng_row_infop row_info, xpng_bytep row));
#endif

#if defined(PNG_READ_DITHER_SUPPORTED)
PNG_EXTERN void xpng_do_dither PNGARG((xpng_row_infop row_info,
   xpng_bytep row, xpng_bytep palette_lookup, xpng_bytep dither_lookup));

#  if defined(PNG_CORRECT_PALETTE_SUPPORTED)
PNG_EXTERN void xpng_correct_palette PNGARG((xpng_structp xpng_ptr,
   xpng_colorp palette, int num_palette));
#  endif
#endif

#if defined(PNG_READ_BGR_SUPPORTED) || defined(PNG_WRITE_BGR_SUPPORTED)
PNG_EXTERN void xpng_do_bgr PNGARG((xpng_row_infop row_info, xpng_bytep row));
#endif

#if defined(PNG_WRITE_PACK_SUPPORTED)
PNG_EXTERN void xpng_do_pack PNGARG((xpng_row_infop row_info,
   xpng_bytep row, xpng_uint_32 bit_depth));
#endif

#if defined(PNG_WRITE_SHIFT_SUPPORTED)
PNG_EXTERN void xpng_do_shift PNGARG((xpng_row_infop row_info, xpng_bytep row,
   xpng_color_8p bit_depth));
#endif

#if defined(PNG_READ_BACKGROUND_SUPPORTED)
#if defined(PNG_READ_GAMMA_SUPPORTED)
PNG_EXTERN void xpng_do_background PNGARG((xpng_row_infop row_info, xpng_bytep row,
   xpng_color_16p trans_values, xpng_color_16p background,
   xpng_color_16p background_1,
   xpng_bytep gamma_table, xpng_bytep gamma_from_1, xpng_bytep gamma_to_1,
   xpng_uint_16pp gamma_16, xpng_uint_16pp gamma_16_from_1,
   xpng_uint_16pp gamma_16_to_1, int gamma_shift));
#else
PNG_EXTERN void xpng_do_background PNGARG((xpng_row_infop row_info, xpng_bytep row,
   xpng_color_16p trans_values, xpng_color_16p background));
#endif
#endif

#if defined(PNG_READ_GAMMA_SUPPORTED)
PNG_EXTERN void xpng_do_gamma PNGARG((xpng_row_infop row_info, xpng_bytep row,
   xpng_bytep gamma_table, xpng_uint_16pp gamma_16_table,
   int gamma_shift));
#endif

#if defined(PNG_READ_EXPAND_SUPPORTED)
PNG_EXTERN void xpng_do_expand_palette PNGARG((xpng_row_infop row_info,
   xpng_bytep row, xpng_colorp palette, xpng_bytep trans, int num_trans));
PNG_EXTERN void xpng_do_expand PNGARG((xpng_row_infop row_info,
   xpng_bytep row, xpng_color_16p trans_value));
#endif

/* The following decodes the appropriate chunks, and does error correction,
 * then calls the appropriate callback for the chunk if it is valid.
 */

/* decode the IHDR chunk */
PNG_EXTERN void xpng_handle_IHDR PNGARG((xpng_structp xpng_ptr, xpng_infop info_ptr,
   xpng_uint_32 length));
PNG_EXTERN void xpng_handle_PLTE PNGARG((xpng_structp xpng_ptr, xpng_infop info_ptr,
   xpng_uint_32 length));
PNG_EXTERN void xpng_handle_IEND PNGARG((xpng_structp xpng_ptr, xpng_infop info_ptr,
   xpng_uint_32 length));

#if defined(PNG_READ_bKGD_SUPPORTED)
PNG_EXTERN void xpng_handle_bKGD PNGARG((xpng_structp xpng_ptr, xpng_infop info_ptr,
   xpng_uint_32 length));
#endif

#if defined(PNG_READ_cHRM_SUPPORTED)
PNG_EXTERN void xpng_handle_cHRM PNGARG((xpng_structp xpng_ptr, xpng_infop info_ptr,
   xpng_uint_32 length));
#endif

#if defined(PNG_READ_gAMA_SUPPORTED)
PNG_EXTERN void xpng_handle_gAMA PNGARG((xpng_structp xpng_ptr, xpng_infop info_ptr,
   xpng_uint_32 length));
#endif

#if defined(PNG_READ_hIST_SUPPORTED)
PNG_EXTERN void xpng_handle_hIST PNGARG((xpng_structp xpng_ptr, xpng_infop info_ptr,
   xpng_uint_32 length));
#endif

#if defined(PNG_READ_iCCP_SUPPORTED)
extern void xpng_handle_iCCP PNGARG((xpng_structp xpng_ptr, xpng_infop info_ptr,
   xpng_uint_32 length));
#endif /* PNG_READ_iCCP_SUPPORTED */

#if defined(PNG_READ_iTXt_SUPPORTED)
PNG_EXTERN void xpng_handle_iTXt PNGARG((xpng_structp xpng_ptr, xpng_infop info_ptr,
   xpng_uint_32 length));
#endif

#if defined(PNG_READ_oFFs_SUPPORTED)
PNG_EXTERN void xpng_handle_oFFs PNGARG((xpng_structp xpng_ptr, xpng_infop info_ptr,
   xpng_uint_32 length));
#endif

#if defined(PNG_READ_pCAL_SUPPORTED)
PNG_EXTERN void xpng_handle_pCAL PNGARG((xpng_structp xpng_ptr, xpng_infop info_ptr,
   xpng_uint_32 length));
#endif

#if defined(PNG_READ_pHYs_SUPPORTED)
PNG_EXTERN void xpng_handle_pHYs PNGARG((xpng_structp xpng_ptr, xpng_infop info_ptr,
   xpng_uint_32 length));
#endif

#if defined(PNG_READ_sBIT_SUPPORTED)
PNG_EXTERN void xpng_handle_sBIT PNGARG((xpng_structp xpng_ptr, xpng_infop info_ptr,
   xpng_uint_32 length));
#endif

#if defined(PNG_READ_sCAL_SUPPORTED)
PNG_EXTERN void xpng_handle_sCAL PNGARG((xpng_structp xpng_ptr, xpng_infop info_ptr,
   xpng_uint_32 length));
#endif

#if defined(PNG_READ_sPLT_SUPPORTED)
extern void xpng_handle_sPLT PNGARG((xpng_structp xpng_ptr, xpng_infop info_ptr,
   xpng_uint_32 length));
#endif /* PNG_READ_sPLT_SUPPORTED */

#if defined(PNG_READ_sRGB_SUPPORTED)
PNG_EXTERN void xpng_handle_sRGB PNGARG((xpng_structp xpng_ptr, xpng_infop info_ptr,
   xpng_uint_32 length));
#endif

#if defined(PNG_READ_tEXt_SUPPORTED)
PNG_EXTERN void xpng_handle_tEXt PNGARG((xpng_structp xpng_ptr, xpng_infop info_ptr,
   xpng_uint_32 length));
#endif

#if defined(PNG_READ_tIME_SUPPORTED)
PNG_EXTERN void xpng_handle_tIME PNGARG((xpng_structp xpng_ptr, xpng_infop info_ptr,
   xpng_uint_32 length));
#endif

#if defined(PNG_READ_tRNS_SUPPORTED)
PNG_EXTERN void xpng_handle_tRNS PNGARG((xpng_structp xpng_ptr, xpng_infop info_ptr,
   xpng_uint_32 length));
#endif

#if defined(PNG_READ_zTXt_SUPPORTED)
PNG_EXTERN void xpng_handle_zTXt PNGARG((xpng_structp xpng_ptr, xpng_infop info_ptr,
   xpng_uint_32 length));
#endif

PNG_EXTERN void xpng_handle_unknown PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_uint_32 length));

PNG_EXTERN void xpng_check_chunk_name PNGARG((xpng_structp xpng_ptr,
   xpng_bytep chunk_name));

/* handle the transformations for reading and writing */
PNG_EXTERN void xpng_do_read_transformations PNGARG((xpng_structp xpng_ptr));
PNG_EXTERN void xpng_do_write_transformations PNGARG((xpng_structp xpng_ptr));

PNG_EXTERN void xpng_init_read_transformations PNGARG((xpng_structp xpng_ptr));

#ifdef PNG_PROGRESSIVE_READ_SUPPORTED
PNG_EXTERN void xpng_push_read_chunk PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr));
PNG_EXTERN void xpng_push_read_sig PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr));
PNG_EXTERN void xpng_push_check_crc PNGARG((xpng_structp xpng_ptr));
PNG_EXTERN void xpng_push_crc_skip PNGARG((xpng_structp xpng_ptr,
   xpng_uint_32 length));
PNG_EXTERN void xpng_push_crc_finish PNGARG((xpng_structp xpng_ptr));
PNG_EXTERN void xpng_push_save_buffer PNGARG((xpng_structp xpng_ptr));
PNG_EXTERN void xpng_push_restore_buffer PNGARG((xpng_structp xpng_ptr,
   xpng_bytep buffer, xpng_size_t buffer_length));
PNG_EXTERN void xpng_push_read_IDAT PNGARG((xpng_structp xpng_ptr));
PNG_EXTERN void xpng_process_IDAT_data PNGARG((xpng_structp xpng_ptr,
   xpng_bytep buffer, xpng_size_t buffer_length));
PNG_EXTERN void xpng_push_process_row PNGARG((xpng_structp xpng_ptr));
PNG_EXTERN void xpng_push_handle_unknown PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_uint_32 length));
PNG_EXTERN void xpng_push_have_info PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr));
PNG_EXTERN void xpng_push_have_end PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr));
PNG_EXTERN void xpng_push_have_row PNGARG((xpng_structp xpng_ptr, xpng_bytep row));
PNG_EXTERN void xpng_push_read_end PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr));
PNG_EXTERN void xpng_process_some_data PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr));
PNG_EXTERN void xpng_read_push_finish_row PNGARG((xpng_structp xpng_ptr));
#if defined(PNG_READ_tEXt_SUPPORTED)
PNG_EXTERN void xpng_push_handle_tEXt PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_uint_32 length));
PNG_EXTERN void xpng_push_read_tEXt PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr));
#endif
#if defined(PNG_READ_zTXt_SUPPORTED)
PNG_EXTERN void xpng_push_handle_zTXt PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_uint_32 length));
PNG_EXTERN void xpng_push_read_zTXt PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr));
#endif
#if defined(PNG_READ_iTXt_SUPPORTED)
PNG_EXTERN void xpng_push_handle_iTXt PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr, xpng_uint_32 length));
PNG_EXTERN void xpng_push_read_iTXt PNGARG((xpng_structp xpng_ptr,
   xpng_infop info_ptr));
#endif

#endif /* PNG_PROGRESSIVE_READ_SUPPORTED */

#ifdef PNG_MNG_FEATURES_SUPPORTED
PNG_EXTERN void xpng_do_read_intrapixel PNGARG((xpng_row_infop row_info,
   xpng_bytep row));
PNG_EXTERN void xpng_do_write_intrapixel PNGARG((xpng_row_infop row_info,
   xpng_bytep row));
#endif

#if defined(PNG_ASSEMBLER_CODE_SUPPORTED)
/* png.c */ /* PRIVATE */
PNG_EXTERN void xpng_init_mmx_flags PNGARG((xpng_structp xpng_ptr));
#endif
/* Maintainer: Put new private prototypes here ^ and in libpngpf.3 */

#endif /* PNG_INTERNAL */

#ifdef __cplusplus
}
#endif

#endif /* PNG_VERSION_INFO_ONLY */
/* do not put anything past this line */
#endif /* PNG_H */
