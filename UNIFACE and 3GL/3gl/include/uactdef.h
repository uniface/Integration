/* @(#)CONT_ID %fv: uactdef.h-23:incl:2 % %dc: Tue Sep  9 10:03:33 2014 % (#)@ */

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
060209 b26627    M431    ahn Internal instance name to 64 bytes for TCP6 IP
                             changes moved to iccapi.h
date   refnum    version who description
*******************************************************************************/

#ifndef UACTDEF_H
#define UACTDEF_H


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* ----- Include Files --------------------------------------------------------------- */

#include "unityp.h"                  /* include UNIFACE types file                     */
#include "iccapi.h"                  /* include UNIFACE ICC API file                   */


/* ----- #defines -------------------------------------------------------------------- */


#define USE_COMPONENT_NAME   ((USTRING *)-1)


/* -- Macro constants */

/* UNIFACE environment error code for functions UECREATE(), UEOPEN() and UEDELETE() */
#define UINI_SUCCESS                         1
#define UINI_LOAD_ERROR                     -1
#define UINI_LICENCE_ERROR                  -2
#define UINI_ALLOC_ERROR                    -4

/* UNIFACE run modes for UECREATE() */
#define URUN_CLIENT                          0  /* Not supported yet */
#define URUN_BATCH_CLIENT                    1  /* As client in batch mode */
#define URUN_SERVER                          2  /* In server mode */

/*
 * New_instance communication modes
 */
#define UDEFAULT_COMM_MODE                   0
#define USYNC_COMM_MODE                      1
#define UASYNC_COMM_MODE                     2

/*
 * Null instance handle
*/
#define UHACT_NULL              0

/*
 * Parameter directions
 */
#define UPARM_INPUT           0x01
#define UPARM_OUTPUT          0x02

/*
 * Item list options
 */
#define UITEM_OPTION_NONE        0
#define UITEM_OPTION_ID          1
#define UITEM_OPTION_ID_CASE     2


/* -- Types */

typedef unsigned char       UCHAR;


/* -- Prototypes */

/*
 * Call in
 */

/* Initialization functions */
extern long UECREATE (int, UVOID *, UCHAR *, UCHAR *,
                      UCHAR *, UCHAR *, UHACT *);
extern long UEOPEN   (UHACT *);
extern long UEDELETE (UHACT, int);

/* Instance functions */
extern long UINSTNEW (UHACT, UCHAR *, UCHAR *, UCHAR *,
                      int, UCHAR *, UHACT *, long *);
extern long UINSTOPN (UHACT, UCHAR *, UHACT *);
extern long UINSTDEL (UHACT, long *);
extern long UINSTOPR (UHACT, UCHAR *, int, UHACT *);
extern long UCOMPOPR (UHACT, UCHAR *, UCHAR *, int, UCHAR *, UCHAR *, UHACT *);

/* Operation functions */
extern long UOPRACT  (UHACT, long *, long *);
extern long UOPRPRMS (UHACT, long *);

/* Basic and entity parameter functions */
extern long UPRMPUTH (UHACT, int, UHACT);
extern long UPRMGETH (UHACT, int, UBOOL, UHACT *);
extern long UPRMTYPE (UHACT, int *);
extern long UPRMPUTS (UHACT, UCHAR *);
extern long UPRMGETS (UHACT, UCHAR **);
extern long UPRMDIR  (UHACT, int, int *);

/* Entity functions */
extern long UENTOCCS (UHACT, long *);
extern long UENTFLDS (UHACT, long *);
extern long UENTCREO (UHACT, long);
extern long UENTREMO (UHACT, long);
extern long UENTSETO (UHACT, long);
extern long UENTGETO (UHACT, long *);

/* Item list functions */
extern long ULISTNEW (UHACT, UHACT *);
extern long ULISTGET (UHACT, int, int, UCHAR *, UCHAR **);
extern long ULISTPUT (UHACT, int, int, UCHAR *, UCHAR *);
extern long ULISTDEL (UHACT, int, int, UCHAR *);

/* Memory functions */
extern long UNIALLOC (UHACT, long, UVOID **);
extern long UNIFREE  (UHACT, UVOID *);
extern long UFREEH   (UHACT *);

/* Miscellaneous functions */
extern long UNINAME  (UHACT, int, int, UCHAR *);
extern long ULOGINFO (UHACT, long);    /* hkr_jci */

/* Parameter conversion functions */
extern long UCHAR2UF (UHACT, int, UBYTE);
extern long UINT2UF  (UHACT, int, int);
extern long ULONG2UF (UHACT, int, long);
extern long UFLT2UF  (UHACT, int, float);
extern long UDBL2UF  (UHACT, int, double);
extern long USTR2UF  (UHACT, int, UCHAR *);
extern long UWSTR2UF (UHACT, int, UCHAR *, int);/*cr21626*/
extern long UBIN2UF  (UHACT, int, UBYTE *, long);
extern long ULIST2UF (UHACT, int, UHACT);
extern long UINST2UF (UHACT, int, UHACT);
extern long UEXOB2UF (UHACT, int, const char *, void *);
extern long UUF2CHAR (UHACT, int, UBYTE *);
extern long UUF2INT  (UHACT, int, int *);
extern long UUF2LONG (UHACT, int, long *);
extern long UUF2FLT  (UHACT, int, float *);
extern long UUF2DBL  (UHACT, int, double *);
extern long UUF2STR  (UHACT, int, UCHAR **);
extern long UUF2WSTR (UHACT, int, UCHAR **, int); /*cr21626*/
extern long UUF2BIN  (UHACT, int, UBYTE **, long *);
extern long UUF2LIST (UHACT, int, UHACT);
extern long UUF2INST (UHACT, int, UHACT *);
extern long UUF2EXOB (UHACT, int, const char *, void * *);
extern long UTF82UNIF (UHACT, int, UCHAR *);    /* hkr_jci_doublebyte start */
extern long UNIF2UTF8 (UHACT, int, UCHAR **);   /* hkr_jci_doublebyte end */
/*
 * Call out
 */

/* Parameter functions */
extern long UGETPARM (UCTRL, UVOID *, int);
extern long UPUTPARM (UCTRL, UVOID *, int);


/* To map functions from lower case to upper case */
#ifdef u_lowercase

/* Initialization functions */
#define uecreate    UECREATE
#define ueopen      UEOPEN
#define uedelete    UEDELETE

/* Instance functions */
#define uinstnew    UINSTNEW
#define uinstopn    UINSTOPN
#define uinstdel    UINSTDEL
#define uinstopr    UINSTOPR
#define ucompopr    UCOMPOPR

/* Operation functions */
#define uopract     UOPRACT
#define uoprprms    UOPRPRMS

/* Basic and entity parameter functions */
#define uprmputh    UPRMPUTH
#define uprmgeth    UPRMGETH
#define uprmtype    UPRMTYPE
#define uprmputs    UPRMPUTS
#define uprmgets    UPRMGETS
#define uprmdir     UPRMDIR

/* Entity functions */
#define uentoccs    UENTOCCS
#define uentflds    UENTFLDS
#define uentcreo    UENTCREO
#define uentremo    UENTREMO
#define uentseto    UENTSETO
#define uentgeto    UENTGETO

/* Item list functions */
#define ulistnew    ULISTNEW
#define ulistget    ULISTGET
#define ulistput    ULISTPUT
#define ulistdel    ULISTDEL

/* Memory functions */
#define unialloc    UNIALLOC
#define unifree     UNIFREE 
#define ufreeh      UFREEH  

/* Miscellaneous functions */
#define uniname     UNINAME
#define uloginfo    ULOGINFO    /* hkr_jci */

/* Parameter conversion functions */
#define uchar2uf    UCHAR2UF
#define uint2uf     UINT2UF 
#define ulong2uf    ULONG2UF
#define uflt2uf     UFLT2UF 
#define udbl2uf     UDBL2UF 
#define ustr2uf     USTR2UF 
#define uwstr2uf    UWSTR2UF /*cr21626*/
#define ubin2uf     UBIN2UF 
#define ulist2uf    ULIST2UF
#define uinst2uf    UINST2UF
#define uexob2uf    UEXOB2UF
#define uuf2char    UUF2CHAR
#define uuf2int     UUF2INT 
#define uuf2long    UUF2LONG
#define uuf2flt     UUF2FLT 
#define uuf2dbl     UUF2DBL 
#define uuf2str     UUF2STR 
#define uuf2wstr    UUF2WSTR  /*cr21626*/
#define uuf2bin     UUF2BIN 
#define uuf2list    UUF2LIST
#define uuf2inst    UUF2INST
#define uuf2exob    UUF2EXOB
#define utf82unif   UTF82UNIF    /* hkr_jci_doublebyte start */
#define unif2utf8   UNIF2UTF8    /* hkr_jci_doublebyte end */

/*
 * Call out
 */

#define ugetparm    UGETPARM
#define uputparm    UPUTPARM

#endif  /* u_lowercase */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* UACTDEF_H */

/* End of file uactdef.h */
