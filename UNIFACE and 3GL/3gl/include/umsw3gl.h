/* @(#)CONT_ID %fv: umsw3gl.h-23:incl:3 % %dc: Tue Sep  9 10:08:19 2014 % (#)@ */

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

#ifndef UMSW3GL_H
#define UMSW3GL_H


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <malloc.h>
#include <windows.h>


#define XCALLBACK   __stdcall
#undef  XEXPORT
#define XEXPORT(A)  __declspec(dllexport) A
#define X3GL        __cdecl
typedef __declspec(dllexport) long (* XPROC)();

   /*
   ** These values are passed to UDLLEVENT.
   */

#define UEVT_INITDLL     1             /* DLL is being loaded     */
#define UEVT_EXITDLL     2             /* DLL is being unloaded   */
#define UEVT_INITCLIENT  3             /* A new client arrives    */
#define UEVT_EXITCLIENT  4             /* A client says goodbye   */
#define UEVT_INITGUI     5             /* Interactive mode starts */
#define UEVT_EXITGUI     6             /* Interactive mode ends   */

   /*
   ** These values are passed to UADVISE and UUNADVISE.
   */

#define UADV_PREKEY      1             /* Advise before key processed     */
#define UADV_POSTKEY     2             /* Advise after key processed      */
#define UADV_MODIFY      3             /* Advise after field modification */

#define UADV_ALL       -1L             /* All events in a class           */

   /*
   ** These values are returned from UDLLEVENT and other functions.
   */

#ifndef SUCCESS
#define SUCCESS  0
#endif

#ifndef FAILURE
#define FAILURE -1
#endif

/*
** You must declare all your 4GL callable functions with XEXPORT(A).
** Where A is the returned type
** Functions passed to UPROCINST must be declared XCALLBACK.
** Communication with UMSWLIB uses the X3GL calling sequence.
*/


/*
** Typedefs
*/

typedef unsigned char       USTRING;   /* Null terminated string */
typedef unsigned char       UARRAY;    /* Not null terminated */
typedef void *              VOIDPTR;
typedef struct unibas *     UNIBAS;
/* no USYSBAS in V9, use UNIBAS instead */
typedef unsigned char *     USMPTR;
typedef long                UPATH;
typedef struct ufile  *     UFILE;
typedef struct uassign *    UASSIGN;
typedef struct hitlist *    UHITLIST;
typedef struct uctrl *      UCTRL;
typedef int                 UBOOL;


#ifndef COMPONENTTYPE_DEF
#define COMPONENTTYPE_DEF
typedef enum {
    CT_FORM             = 4,    /*  ComponentType:  Form                */
    CT_SERVICE          = 5,    /*  ComponentType:  Service             */
    CT_REPORT           = 6,    /*  ComponentType:  Report              */
    CT_ESV              = 8,    /*  ComponentType:  Entity Service      */
    CT_SSV              = 7,    /*  ComponentType:  Session Service     */
    CT_APPLICATION      = 3,    /*  ComponentType:  Application         */
    CT_SERVERPAGE       = 9,    /*  ComponentType:  WebForm / ServerPage*/
    CT_DYNSERVERPAGE    = 10,   /*  ComponentType:  Dynamic Server Page */
    CT_HTMLFORM         = 128   /*  ComponentType:  HTML Form */

} ComponentType;
#endif

/*
** array positions for uversioninfoarray()
*/
#define UVIA_VERSION            0
#define UVIA_TRACK              1
#define UVIA_PATCH              2
#define UVIA_PLATFORM           3
#define UVIA_BDATE              4
#define UVIA_OPRSYS             5
#define UVIA_CPRT               6
#define UVIA_MAJOR              7
#define UVIA_MINOR              8
#define UVIA_MICRO              9

typedef long (XCALLBACK *   UPROC)();

/*
** External Globals
*/
#ifndef NOGLOBALS
extern UNIBAS unibas;
extern
#endif

/*
** The load/unload event notification function can be implemented
** by the custom 3GL code to allocate/deallocate resources, etc.
*/

short X3GL UDLLEVENT(short sReason);

#ifndef NO_SVC_PROTOTYPES


/*
    Documented user 3GL prototypes.
    Ideally we would just want #include "h3gl.h" here. But that does not
    compile, and we don't want to change all the makesfiles. So the
    functions from h3gl.h are duplicated here.

    ===========================================================================
    == NOTE : IF YOU CHANGE/ADD SOMETHING HERE, PLEASE ALSO DO IT in H3GL.H  ==
    ===========================================================================

*/

int              X3GL u_printf               (const char*, ... );
short            X3GL udetailpos             (LPPOINT);
short            X3GL ufget                  (unsigned char*, unsigned char *, short);
short            X3GL ufgetc                 (unsigned char*, unsigned char *, short);
short            X3GL uflab                  (unsigned char*);
short            X3GL uflabdbm               (unsigned char*, unsigned char *);
short            X3GL ufput                  (unsigned char*, unsigned char *, short);
short            X3GL ufputext               (unsigned char*, unsigned char *, short);
short            X3GL ufputc                 (unsigned char*, unsigned char *, short);
short            X3GL ufputi                 (unsigned char*, unsigned char *, short);
short            X3GL ugetames               (unsigned char*);
int              X3GL ugetbind               (unsigned char*, unsigned char *);
HWND             X3GL ugethwnd               (void);
long             X3GL uenableforms           (int);
long             X3GL uprimarywindow         (unsigned char*, unsigned char*,
                                              int, int, int, int,
                                              DWORD, HWND*);
long             X3GL uwprimarywindow        (wchar_t*, wchar_t*,
                                              int, int, int, int,
                                              DWORD, HWND*);
long             X3GL uactivatewindow        (HWND);
unsigned char*   X3GL uGetName               (HWND, unsigned char*, int);
unsigned char*   X3GL ugetprofile            (void);
wchar_t*         X3GL uwgetprofile           (void);
long             X3GL ugetreg                (short);
double           X3GL ugetregf               (short);
long             X3GL ugetregs               (short, unsigned char*, short);
long             X3GL uwgetregs              (short, wchar_t*, short);
long             X3GL umgetregs              (short, unsigned char*, short);
long             X3GL ugettxt                (unsigned char*, char*, long);
long             X3GL ugettxtc               (unsigned char*, long);
unsigned char*   X3GL UGETULDA               (void);
unsigned char*   X3GL UGETUOPENFLAG          (void);
short            X3GL ugget                  (unsigned char*, unsigned char*, short);
short            X3GL uggetc                 (unsigned char*, unsigned char*, short);
short            X3GL uglab                  (unsigned char*);
short            X3GL uglabdbm               (unsigned char*);
short            X3GL ugput                  (unsigned char*, unsigned char*, short);
short            X3GL ugputc                 (unsigned char*, unsigned char*, short);
int              X3GL UNIFBEG                (int);
int              X3GL UNIFEND                (int);
int              X3GL unifmes                (unsigned char*);
long             X3GL upaddocc               (unsigned char*, long);
long             X3GL updelocc               (unsigned char*, long);
long             X3GL updisocc               (unsigned char*, long, long);
int              X3GL UPostMessage           (char*, char*, char*, char *);
long             X3GL upsetocc               (unsigned char*, long);
short            X3GL uputames               (unsigned char*, short);
void             X3GL uputmess               (unsigned char*);
long             X3GL uputreg                (short, long);
long             X3GL uputregf               (short, double);
long             X3GL uputregs               (short, unsigned char*);
long             X3GL uwputregs              (short, wchar_t *utf16, int utf16len);
int              X3GL uReadStringSysSetting  (char*, char*, char*, char*, int, char*);
long             X3GL urun                   (unsigned char*, short, short, short, short);
long             X3GL usetparm               (short, unsigned char*, unsigned char*);
long             X3GL usysparm               (short, unsigned char*, short);
void             X3GL uversioninfo           (unsigned char*, unsigned char*, unsigned char*, unsigned char*,
                                              unsigned char*, unsigned char*, int*, int*, int*);
void             X3GL uversioninfoarray      (void **, int);
int              X3GL uWriteStringSysSetting (char*, char*, char*, char*);
short            X3GL uxget                  (unsigned char*, short);
short            X3GL uxgetc                 (unsigned char*, short);
short            X3GL uxput                  (unsigned char*, short);
short            X3GL uxputc                 (unsigned char*, short);




/*
    Next define's make that any function can be used in either uppercase of lowercase
    (even if the original function is defined in mixed case, e.g. uReadStringSysSetting)
*/
#define U_PRINTF                u_printf
#define UDETAILPOS              udetailpos
#define UFGET                   ufget
#define UFGETC                  ufgetc
#define UFLAB                   uflab
#define UFLABDBM                uflabdbm
#define UFPUT                   ufput
#define UFPUTEXT                ufputext
#define UFPUTC                  ufputc
#define UFPUTI                  ufputi
#define UGETAMES                ugetames
#define UGETBIND                ugetbind
#define UGETHWND                ugethwnd
#define UENABLEFORMS            uenableforms
#define UPRIMARYWINDOW          uprimarywindow
#define UWPRIMARYWINDOW         uwprimarywindow
#define UACTIVATEWINDOW         uactivatewindow
#define ugetname                uGetName
#define UGETNAME                uGetName
#define UGETPROFILE             ugetprofile
#define UWGETPROFILE            uwgetprofile
#define UGETREG                 ugetreg
#define UGETREGF                ugetregf
#define UGETREGS                ugetregs
#define UWGETREGS               uwgetregs
#define UMGETREGS               umgetregs
#define UGETTXT                 ugettxt
#define UGETTXTC                ugettxtc
#define ugetulda                UGETULDA
#define ugetuopenflag           UGETUOPENFLAG
#define UGGET                   ugget
#define UGLAB                   uglab
#define UGLABDBM                uglabdbm
#define UGPUT                   ugput
#define UGPUTC                  ugputc
#define unifbeg                 UNIFBEG
#define unifend                 UNIFEND
#define UNIFMES                 unifmes
#define UPADDOCC                upaddocc
#define UPDELOCC                updelocc
#define UPDISOCC                updisocc
#define upostmessage            UPostMessage
#define UPOSTMESSAGE            UPostMessage
#define UPSETOCC                upsetocc
#define UPUTAMES                uputames
#define UPUTMESS                uputmess
#define UPUTREG                 uputreg
#define UPUTREGF                uputregf
#define UPUTREGS                uputregs
#define UWPUTREGS               uwputregs
#define UMPUTREGS               umputregs
#define UPUTREGSUNICODE         uwputregs
#define uputregsunicode         uwputregs
#define ureadstringsyssetting   uReadStringSysSetting
#define UREADSTRINGSYSSETTING   uReadStringSysSetting
#define URUN                    urun
#define USETPARM                usetparm
#define USYSPARM                usysparm
#define UVERSIONINFO            uversioninfo
#define UVERSIONINFOARRAY       uversioninfoarray
#define uwritestringsyssetting  uWriteStringSysSetting
#define UWRITESTRINGSYSSETTING  uWriteStringSysSetting
#define UXGET                   uxget
#define UXGETC                  uxgetc
#define UXPUT                   uxput
#define UXPUTC                  uxputc

/* End of documented user 3GL prototypes */

/* Obsolete: */
#define UGETREGSUNICODE         uwgetregs
#define ugetregsunicode         uwgetregs
#define UGETREGSMETA            umgetregs
#define ugetregsmeta            umgetregs
/* End Obsolete */

/* ---------- Service functions (yrtl) ---------- */
    long      X3GL ucurfld(void);                                    /* Windows */
    USTRING*  X3GL uGetFormName(HWND hWnd, USTRING* pszInput,
                                int iMax);                           /* Windows */
    short     X3GL uadvise(short, long, UPROC);                      /* Windows */
    short     X3GL ucfget(USTRING *pField, USTRING *pData, short sMax,
                          UARRAY *pType);
    short     X3GL ucfgetc(USTRING *pField, USTRING *pData, short sMax);
    long      X3GL uexec(USTRING *formname);
    long      X3GL ufldlink(USTRING *, long *);                      /* Windows */
    short     X3GL ufldname(long, USTRING *);                        /* Windows */
    XPROC     X3GL uget3gl(USTRING *);                               /* Windows */
    long      X3GL ugetgvr(USTRING *name, USTRING *buf, long max);
    long      X3GL ugetgvrc(USTRING *buf, long max);
    HINSTANCE X3GL ugethinst(void);                                  /* Windows */
    long      X3GL uload(ComponentType Aotype, USTRING *loadname,
                         USTRING *formname, short vpos, short hpos,
                         short vmax, short hmax);
    long      X3GL uputgvr(USTRING *name, USTRING *buf, long len);
    long      X3GL uputgvrc(USTRING *buf, long len);
    short     X3GL urclr(short sSource);
    long      X3GL uruninst(USTRING *loadname, USTRING *formname,
                            short vpos, short hpos, short vmax, short hmax);
    long      X3GL usndmsg(USTRING *msg_to, USTRING *msg_id,
                           USTRING *msg_data, long data_len,
                           short synchronous);
    USTRING*  X3GL ustringcnv(USTRING *, USTRING *, int);            /* Windows */
    int       X3GL usysmessage(UNIBAS unibas, int iErr,
                               USTRING *pBuf);                       /* Windows */
    short     X3GL uunadvise(short, long, UPROC);                    /* Windows */
    void      X3GL uunload(USTRING *formname);
    void      X3GL uwantchars(short bWantChar);                      /* Windows */
    long      X3GL umputregs(short, unsigned char*);

#define UCFGET                  ucfget
#define UCFGETC                 ucfgetc
#define UEXEC                   uexec
#define UGETGVR                 ugetgvr
#define UGETGVRC                ugetgvrc
#define ULOAD                   uload
#define UPUTGVR                 uputgvr
#define UPUTGVRC                uputgvrc
#define URCLR                   urclr
#define URUNINST                uruninst
#define USNDMSG                 usndmsg
#define UUNLOAD                 uunload
#define USETUPISPY              usetupispy
#define UGET3GL                 uget3gl
#define UGETHINST               ugethinst
#define USYSMESSAGE             usysmessage
#define UADVISE                 uadvise
#define UUNADVISE               uunadvise
#define UCURFLD                 ucurfld
#define UFLDLINK                ufldlink
#define UFLDNAME                ufldname
#define USTRINGCNV              ustringcnv
#define UWANTCHARS              uwantchars
#define UGETFORMNAME            uGetFormName
#define UVERSIONINFO            uversioninfo
#define UVERSIONINFOARRAY       uversioninfoarray
#define UMPUTREGS               umputregs


/* ---------- Support functions (ulib) ---------- */
    HINSTANCE X3GL ugetappi(void);                                   /* Windows */
    UBOOL     X3GL uisguiactive(void);                               /* Windows */
    void*     X3GL ucalloc(size_t num, size_t size);
    void      X3GL ufilclose(UNIBAS, UFILE);
    int       X3GL ufildel(UNIBAS, USTRING *);
    UFILE     X3GL ufilopen(UNIBAS, USTRING *, int);
    int       X3GL ufilparse(UNIBAS , USTRING *, int *, int *, int *);
    int       X3GL ufilread(UNIBAS, UFILE, UARRAY *, int);
    int       X3GL ufilwild(UNIBAS, USTRING *, int, USTRING *);
    int       X3GL ufilwrite(UNIBAS, UFILE, UARRAY *, int);
    void      X3GL ufree(void *);                                    /* Windows */
    UPATH     X3GL ugetasn(UNIBAS, UASSIGN, int, USTRING *, USTRING *, USTRING *, int);
    int       X3GL ugetenv(UNIBAS, USTRING *, USTRING *);
    UNIBAS    X3GL ugetuni(UNIBAS);
    void      X3GL ulogprint(UNIBAS, const USTRING *);
    int       X3GL ulstrcpy(USTRING *, const USTRING *);
    void*     X3GL umalloc(size_t);                                  /* Windows */
    void*     X3GL urealloc(void * pOld, size_t size);               /* Windows */
    UARRAY*   X3GL ustrdup(UNIBAS, UARRAY *);
    int       X3GL ustrim(USTRING *, int);
    char*     X3GL ustringdup(char * pszText);                       /* Windows */

#define            UGETAPPI        ugetappi
#define            UFILCLOSE       ufilclose
#define            UFILDEL         ufildel
#define            UFILOPEN        ufilopen
#define            UFILPARSE       ufilparse
#define            UFILREAD        ufilread
#define            UFILSEEK        ufilseek
#define            UFILWILD        ufilwild
#define            UFILWRITE       ufilwrite
#define            UGETASN         ugetasn
#define            UGETENV         ugetenv
#define            UGETUNI         ugetuni
#define            ULOGPRINT       ulogprint
#define            ULSTRCPY        ulstrcpy
#define            USTRDUP         ustrdup
#define            USTRIM          ustrim
#define            UISGUIACTIVE    uisguiactive

/* ---------- Driver support functions (urtl) ---------- */
    void    X3GL uaddhit(UCTRL, UARRAY *, short, UARRAY *, short, UARRAY *, short);
    void    X3GL uaddrec(UCTRL, UARRAY *, short, UARRAY *, short, UARRAY *, short);
    void    X3GL uaddsql(UCTRL, USTRING *);
    void    X3GL ubldprm(UCTRL, short);
    short   X3GL uconvdb(UCTRL, UARRAY *, UARRAY *, short, struct ufldlst *, short);
    short   X3GL udbconv(UCTRL, USTRING *, USTRING *, short, struct ufldlst *, short);
    short   X3GL udcurscnt(UCTRL, short, short);
    short   X3GL udfilcnt(UCTRL, short, short);
    short   X3GL udpathset(UCTRL, short, short);
    long    X3GL ugetblob(UCTRL, int, UARRAY *, long, int);
    short   X3GL ugethit(struct uctrl *, UARRAY *, UARRAY *);
    short   X3GL uhitchk(UCTRL, short, UARRAY *);
    void    X3GL unullify(UCTRL, int);
    short   X3GL uprimpos(UCTRL, short);
    void    X3GL uputblob(UCTRL, int, UARRAY *, long, int);
    short   X3GL uready(UCTRL);
    int     X3GL usort(UNIBAS, UHITLIST);
    void    X3GL usumfld(UCTRL, UARRAY *, short, short);
    void    X3GL usumhit(UCTRL);
    UARRAY* X3GL usysalloc(UNIBAS, unsigned int, int, int);
    int     X3GL usyserr(UNIBAS unibas, int iErr);
    UARRAY* X3GL usysfree(UNIBAS, UARRAY *);
    UARRAY* X3GL usysrealloc(UNIBAS, UARRAY *, unsigned, int, int);

#define          UADDHIT         uaddhit
#define          UADDSQL         uaddsql
#define          UBLDPRM         ubldprm
#define          UCONVDB         uconvdb
#define          UDBCONV         udbconv
#define          UDCURSCNT       udcurscnt
#define          UDFILCNT        udfilcnt
#define          UDPATHSET       udpathset
#define          UGETBLOB        ugetblob
#define          UGETHIT         ugethit
#define          UHITCHK         uhitchk
#define          ULOADCB(arg)    (arg)
#define          UNULLIFY        unullify
#define          UPRIMPOS        uprimpos
#define          UPUTBLOB        uputblob
#define          UREADY          uready
#define          USORT           usort
#define          USUMFLD         usumfld
#define          USUMHIT         usumhit
#define          USYSALLOC       usysalloc
#define          USYSERR         usyserr
#define          USYSFREE        usysfree
#define          USYSREALLOC     usysrealloc
#define          UADDREC         uaddrec
#define          uloadcb(arg)    (arg)



   /*
   ** Windows specific service functions.
   */
    XEXPORT(void X3GL) ULOADDS(void);                                     /* mswwrap.c */
#define         uloadds ULOADDS
    UPROC   X3GL umakeprocinst(UPROC);                                    /* mswwrap.c */
    UPROC   X3GL UMAKEPROCINST(UPROC);                                    /* mswwrap.c */
    void    X3GL UFREEPROCINST(UPROC);                                    /* mswwrap.c */
    void    X3GL ufreeprocinst(UPROC);                                    /* mswwrap.c */
    short   X3GL UCLIENT(void);                                           /* mswwrap.c */
    short   X3GL uclient(void);                                           /* mswwrap.c */
    HINSTANCE X3GL ULIBINST(void);                                        /* mswwrap.c */
    HINSTANCE X3GL ulibinst(void);                                        /* mswwrap.c */




   /*
   ** In version 6.1.d, malloc maps to umalloc, giving the benefits of UNIFACE memory
   ** management to our 3rd party widget writers.
   ** In version 7, malloc isn't mapped anymore, thus falls back to the c-runtime malloc.
   ** The define USE_NATIVE_MEMORY allows you to use C-runtime memory functions, so by default
   ** UNIFACE memory management is used.
   ** In version 8 the default was changed to native memory,
   ** Define USE_UNIFACE_MEMORY if you want to use UNIFACE memory management.
   ** In version 9 this is still the case.
   */


#ifdef USE_UNIFACE_MEMORY
#define malloc(n)       umalloc(n)
#define free(p)         ufree(p)
#define calloc(n,s)     ucalloc(n, s)
#define realloc(p, s)   urealloc(p, s)
#define _strdup(p)      ustringdup(p)
#endif /* USE_UNIFACE_MEMORY */

typedef struct __UPIWIDPARAMS
{
   void          *pwid;   /* Pointer to a widget. */
   unsigned      message; /* OWI-message. */
   long          lp;      /* First param of ulMsg. */
   void          *pp;     /* Second param of ulMsg. */
} UPIWIDPARAMS ;

#define CALLUPIWIDPROC(a,b,c,d,e) (a)(b,c,d,e)

#endif /* NO_SVC_PROTOTYPES */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !UMSW3GL_H */
