/* @(#)CONT_ID %fv: unityp.h-11:incl:1 % %dc: Tue Sep  9 09:59:53 2014 % (#)@ */

/*******************************************************************************
Copyright © 2014 Uniface B.V. All rights reserved.
U.S. GOVERNMENT RIGHTS-Use, duplication, or disclosure by the U.S. Government
is subject to restrictions as set forth inapplicable license agreement with
Uniface B.V. and/or its predecessor in interest and as provided in DFARS
227.7202-1(a) and 227.7202-3(a) (1995), DFARS 252.227-7013(c)(1)(ii)(OCT 1988),
FAR 12.212(a)(1995), FAR 52.227-19, or FAR 52.227-14(ALTIII), as applicable.
Uniface B.V.

You have a royalty-free right to use, modify, reproduce and distribute
this sample code (and/or any modified version) in any way you find useful,
provided that you agree that Uniface B.V. has no warranty obligations or
liability for any sample code which has been modified.
*******************************************************************************/
/*******************************************************************************
date   refnum    version who description
date   refnum    version who description
*******************************************************************************/

#ifndef UNITYP_H
#define UNITYP_H


/* ----- typedefs -------------------------------------------------------------------- */
typedef struct _unicolordef {
    long lclrback; /* signed -1 means off. other values  */
    long lclrfore; /* signed -1 means off. other values  */
}UNICOLORDEF, *pUNICOLORDEF;

typedef void                 UVOID;
typedef long                 ULONGINT;
typedef unsigned char        UBYTE;
typedef UBYTE                UARRAY;     /* buffer values 0-255  */
typedef UARRAY               USTRING;    /* buffer values 1-255 closed with 0 */
typedef void *               UNATIVE;    /* OTYP_NATIVE */
typedef int                  UBOOL;      /* OTYP_BOOL   */
typedef long                 UNUMBER;    /* OTYP_NUMBER */
typedef double               UFLOAT;     /* OTYP_FLOAT  */
typedef double               UNIDATE;    /* OTYP_(L)DATE, OTYP_(L)TIME, OTYP_(L)DATIM  */
typedef unsigned char        USTR;       /* OTYP_STR, OTYP_RAW, OTYP_IMAGE */
typedef struct uctrl         *UCTRL;     /* control block */
typedef struct AnyInfo       *UHACT;     /* handle information struct */

/**
@short (Partial) Unicode character in UTF-8 format (1 byte)
One Unicode character ::UTF32 is translated into 1 ~ 4 UTF-8 characters.
Meta in V9 is in this UTF-8 storage format. The font system of V8 and earlier
is no longer used by Uniface 9.
ASCII characters are the same in UTF-8.
*/
typedef char              UTF8;
/**
@short Unicode character in UTF-16 format (2 bytes)
One Unicode character ::UTF32 is translation to 1 or 2 UTF-16 characters.
The windows GUI driver uses this format.
*/
#if (_MSC_VER >= 1400) /* Microsoft V8 compiler */
# include <wchar.h>
 typedef wchar_t              UTF16;
#else
 typedef unsigned short       UTF16;
#endif

#ifdef _WIN64
 typedef __w64 long          UPATH;
#elif __OS400__
  typedef long long          UPATH;
#else
  typedef long               UPATH;
#endif

#if defined(_WIN32) || defined(_WIN64)
 typedef unsigned __int32 UINT32; 
 typedef unsigned __int64 UINT64; 
#elif defined(__SASC__)
 typedef unsigned int       UINT32;
 typedef unsigned long long UINT64;
#else
# include <inttypes.h>
 typedef uint32_t UINT32;
# ifndef _INCLUDE_HPUX_SOURCE
 typedef uint64_t UINT64;
# else
#  include  <dlfcn.h>
# endif
#endif

/* ----- #defines -------------------------------------------------------------------- */


#define NO_STRING            (USTRING *) NULL



/* ----- Macros ---------------------------------------------------------------------- */


#define UMAX(a,b)            (((a) > (b)) ? (a) :  (b))
#define UMIN(a,b)            (((a) < (b)) ? (a) :  (b))
#define UABS(a)              (((a) >= 0)  ? (a) : -(a))


/* ----------------------------------------------------------------------------------- */


#endif      /* UNITYP_H */

/* End of File unityp.h */
