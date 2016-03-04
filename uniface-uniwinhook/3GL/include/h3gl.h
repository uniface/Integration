/* @(#)CONT_ID %fv: h3gl.h-17:incl:5 % %dc: Tue Sep  9 10:03:04 2014 % (#)@ */

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

#ifndef H3GL_H
#define H3GL_H

#ifdef __cplusplus
extern "C" {
#endif 

#ifdef _WIN32
#   include <windows.h>
#   ifndef EXPORT
#       define EXPORT __declspec(dllexport)
#   endif
#   ifndef X3GL
#       define X3GL   __cdecl
#   endif 
#else
#   include "unityp.h"
#   ifndef EXPORT
#       define EXPORT
#   endif 
#   ifndef X3GL
#       define X3GL
#   endif 
#endif

#ifndef XEXPORT
#define XEXPORT(A)  EXPORT  A
#endif

#define u_lowercase
#include "uactdef.h"


/*
	==============================================================================
	== NOTE : IF YOU CHANGE/ADD SOMETHING HERE, PLEASE ALSO DO IT IN UMSW3GL.H  ==
	==============================================================================
*/
#ifndef U_NLONG
# ifdef __ILEC400__
#  define U_NULONG unsigned long long
#  define U_NLONG  long long
# else
#  define U_NULONG unsigned long
#  define U_NLONG  long
# endif
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


/*
  Note: most of the below functions expect string data to be in the system character set,
        (i.e. $SYS_CHARSET) and string data returned by them will be in the system character
        set. Exceptions to this rule are the functions that start with 'uw': they expect
        the string data to be in UTF16 format (i.e. UTF16 datatype), and the functions
        that start with 'um': they expect string data to be in Uniface-Meta character set,
        which is UTF8 with some Uniface-specific modifications, for example, the end-of-line
        character in Uniface-Meta is CR on every platform.
 */

#ifdef _WIN32
extern int              u_printf               (const char*, ... );
extern short            udetailpos             (LPPOINT);
#endif

extern short            ufget                  (unsigned char*, unsigned char *, short);
extern short            ufgetc                 (unsigned char*, unsigned char *, short);
extern short            uflab                  (unsigned char*);
extern short            uflabdbm               (unsigned char*, unsigned char *);
extern short            ufput                  (unsigned char*, unsigned char *, short);
extern short            ufputext               (unsigned char*, unsigned char *, short);
extern short            ufputc                 (unsigned char*, unsigned char *, short);
extern short            ufputi                 (unsigned char*, unsigned char *, short);
extern short            ugetames               (unsigned char*);
extern int              ugetbind               (unsigned char*, unsigned char *);

#ifdef _WIN32
extern HWND             ugethwnd               (void);
extern unsigned char*   uGetName               (HWND, unsigned char*, int);
extern unsigned char*   ugetprofile            (void);
extern UTF16*           uwgetprofile           (void);
#endif

extern long             ugetreg                (short);
extern double           ugetregf               (short);
extern long             ugetregs               (short, unsigned char*, short);
extern long             umgetregs              (short, unsigned char*, short);
extern long             uwgetregs              (short, UTF16*, short);
extern long             ugettxt                (unsigned char*, char*, long);
extern long             ugettxtc               (unsigned char*, long);
extern unsigned char*   UGETULDA               (void);
extern unsigned char*   UGETUOPENFLAG          (void);
extern short            ugget                  (unsigned char*, unsigned char*, short);
extern short            uggetc                 (unsigned char*, unsigned char*, short);
extern short            uglab                  (unsigned char*);
extern short            uglabdbm               (unsigned char*);
extern short            ugput                  (unsigned char*, unsigned char*, short);
extern short            ugputc                 (unsigned char*, unsigned char*, short);
extern int              UNIFBEG                (int);
extern int              UNIFEND                (int);
extern int              unifmes                (unsigned char*);
extern long             upaddocc               (unsigned char*, long);
extern long             updelocc               (unsigned char*, long);
extern long             updisocc               (unsigned char*, long, long);

#ifdef _WIN32
extern int              UPostMessage           (char*, char*, char*, char *);
#endif

extern long             upsetocc               (unsigned char*, long);
extern short            uputames               (unsigned char*, short);
extern void             uputmess               (unsigned char*);
extern long             uputreg                (short, long);
extern long             uputregf               (short, double);
extern long             uputregs               (short, unsigned char*);
extern long             umputregs              (short, unsigned char*);
extern long             uwputregs              (short, UTF16*, int);

#ifdef _WIN32
extern int              uReadStringSysSetting  (char*, char*, char*, char*, int, char*);
extern long             urun                   (unsigned char*, short, short, short, short);
#endif

extern long             usetparm               (short, unsigned char*, unsigned char*);
extern long             usysparm               (short, unsigned char*, short);
extern void             uversioninfo           (unsigned char*, unsigned char*, unsigned char*, unsigned char*,
                                                unsigned char*, unsigned char*, int*, int*, int*);
extern void             uversioninfoarray      (void **, int);

#ifdef _WIN32
extern int              uWriteStringSysSetting (char*, char*, char*, char*);
#endif

extern short            uxget                  (unsigned char*, short);
extern short            uxgetc                 (unsigned char*, short);
extern short            uxput                  (unsigned char*, short);
extern short            uxputc                 (unsigned char*, short);




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
#define UMGETREGS               umgetregs
#define UWGETREGS               uwgetregs
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
#define UMPUTREGS               umputregs
#define UWPUTREGS               uwputregs
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

/* Obsolete: */
#define UGETREGSUNICODE         uwgetregs 
#define ugetregsunicode         uwgetregs 
#define UGETREGSMETA            umgetregs 
#define ugetregsmeta            umgetregs 
/* End Obsolete */

#ifdef __cplusplus
}
#endif

#endif /* H3GL_H */

