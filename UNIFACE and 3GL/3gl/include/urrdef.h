/* @(#)CONT_ID %fv: urrdef.h-24:incl:2 % %dc: Wed Sep 10 09:27:43 2014 % (#)@ */

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
070416 c25860    920101  ahn operation properties in signature
080328 c26475    9.ajax  fd  Introduce new component type DSP (Dynamic Server Page)
100518 b28614    P211    hhe Uniface ignores specified character set when generating C Call-Out Stub Code 
120224 c29166    960101  ago Add XML to the parameter
120917 c29409    960101  mzu remove CORBA references
130220 c29993   1010101  tsk Local-only handles/allow newinstance
date   refnum    version who description
*******************************************************************************/

#ifndef URRDEF_H
#define URRDEF_H

/* -- Include files */

#include "uactdef.h"



#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* -- Macro constants */

/* Error numbers */
#define URRAPI_SUCCESS           0
#define URRAPI_HANDLE_NOT_VALID -1
#define URRAPI_ALLOCATION_ERROR -2
#define URRAPI_INFO_ID_ERROR    -3
#define URRAPI_CANNOT_FIND      -4

/* Component types */
#define UANY 0                   /* Any     */
#define US3C 1                   /* 3GL     */
#define URPT 2                   /* Report  */
#define USVC 3                   /* Service */
#define UFRM 4                   /* Form    */
#define USOS 5                   /* OS      */
#define UTUX 6                   /* Tuxedo  */
#define UENC 7                   /* Encina  */
#define UCIC 8                   /* CICS    */
#define UCOM 10                  /* COM     */
#define UJAV 11                  /* Java    */
#define UIMD 12                  /* IMS-DC  */
#define USSP 13                  /* Stored procedures */
#define UUSP 14                  /* UNIFACE Server Page */
#define UUEC 15                  /* Reserved for future usage */
#define UESV 16                  /* Entity Service */
#define USSV 17                  /* Session Service Component */
#define UURC 18                  /* Uniface Reference Collection */
#define UKNL 19                  /* Pseudo component */
#define UNIN 20                  /* Non-instanciatable object */
#define USOP 22                  /* Web Service call out (SOAP) */
#define UDSP 23                  /* Dynamic Server Page (@c26475) */
#define UHFM 24       
#define UPOR 25                  /**< Locally (3gl) implemented object reference */ /* @c29993 */
#define ULASTTYPE UPOR           /* Set it to the last type in list!!!! */

/* Return value */
#define URET_VOID   11           /* function returns void */
#define URET_STATUS 12           /* return value is in $status */
#define URET_PRM    13           /* return value is in Parameter 1 */

/* Component information (generic) */
#define UGEN_NAME            101 /* Component name, <= 32 bytes + '\0'              */
#define UGEN_LIBRARY         102 /* Library name, <= 16 bytes + '\0'                */
#define UGEN_ID              103 /* Unique ID, <= 64 bytes + '\0'                   */
#define UGEN_SUBSYSTEM       104 /* Subsystem name, <= 16 bytes + '\0'              */
#define UGEN_DEFIMPNAME      105 /* Default implementation name, <= 32 bytes + '\0' */
#define UGEN_DEFPATH         106 /* Default path, <= 3 bytes + '\0'                 */
#define UGEN_SCOPE           107 /* Component scope, <= 3 bytes + '\0'              */
#define UGEN_EXECDEF         108 /* Sync/Async, 1 byte + '\0'                       */
#define UGEN_NOSTATE         109 /* State/Stateless, 1 byte + '\0'                  */
#define UGEN_TRANSATTR       110 /* Transactional, 1 byte + '\0' (boolean)          */
#define UGEN_TXTYPE          111 /* Transaction type, 3 bytes + '\0'                */
#define UGEN_TXAUTOCOMMIT    112 /* Transaction auto commit, 1 byte + '\0' (boolean)*/

/* Component middleware information (generic) */
#define UGEN_TUXPROP         121 /* Tuxedo properties, <= 255 bytes + '\0'          */
#define UGEN_ENCPROP         122 /* Encina properties, <= 255 bytes + '\0'          */
#define UGEN_JAVPROP         123 /* Java properties, <= 255 bytes + '\0'            */
#define UGEN_COMPROP         124 /* COM properties, <= 255 bytes + '\0'             */
/* Encina */
#define UGEN_ENC_UUID        125 /* Encina UUID, <= 64 bytes + '\0'                 */
#define UGEN_ENC_VERSION     126 /* Encina TIDL version, <= 16 bytes + '\0'         */
/* Tuxedo */
#define UGEN_TUX_PRIO        127 /* Tuxedo priority, <= 3 bytes + '\0'              */
#define UGEN_TUX_TIMEOUT     128 /* Tuxedo timeout, <= 1 byte + '\0' (boolean)      */
/* COM */
#define UGEN_COM_PROGID      129 /* COM ProgID, <= 255 bytes + '\0'                 */
#define UGEN_COM_CLSID       130 /* COM CLSID, <= 36 bytes + '\0'                   */
#define UGEN_COM_IMPLID      131 /* COM impl ID, Unique ID, <= 64 bytes + '\0'      */
/* Java */
#define UGEN_JAV_CLASSNAME   132 /* Java class name, <= 128 bytes + '\0'            */

/* Component information (implementation) */
#define UIMPL_NAME           151 /* Name, <= 32 bytes + '\0'                        */
#define UIMPL_ID             152 /* ID, <= 64 bytes + '\0'                          */
#define UIMPL_CONTEXT        153 /* Context, <= 1 byte + '\0' (boolean)             */
#define UIMPL_OUTPUT         154 /* Output, <= 64 bytes + '\0'                      */
#define UIMPL_INCLUDE        155 /* Include, <= 64 bytes + '\0'                     */
#define UIMPL_ATTR           156 /* Implementation attributes, <= n bytes + '\0'    */
#define UIMPL_LITNAME        157 /* Literal name, <= 32 bytes + '\0'                */
#define UIMPL_CHARSET        158 /* @b28614                                         */

/* Component middleware information (implementation) */
/* Encina */
#define UIMPL_ENC_UUID       171 /* Encina UUID, <= 64 bytes + '\0'                 */
#define UIMPL_ENC_VERSION    172 /* Encina TIDL version, <= 16 bytes + '\0'         */
/* Tuxedo */
#define UIMPL_TUX_PRIO       173 /* Tuxedo priority, <= 3 bytes + '\0'              */
#define UIMPL_TUX_TIMEOUT    174 /* Tuxedo timeout, <= 1 byte + '\0' (boolean)      */
#define UIMPL_TUX_BUFTYPE    175 /* Tuxedo buffer type, <= 64 bytes + '\0'          */
#define UIMPL_TUX_VIEW       176 /* Tuxedo view, <= 64 bytes + '\0'                 */
#define UIMPL_TUX_BUFCHECK   177 /* Tuxedo strong buffer type checking, <= 1 byte + '\0' (boolean) */
/* COM */
#define UIMPL_COM_PROGID     178 /* COM ProgID, <= 255 bytes + '\0'                 */
#define UIMPL_COM_CLSID      179 /* COM CLSID, <= 36 bytes + '\0'                   */

/* Operation information (generic) */
#define UGOPR_NAME           201 /* Operation name, <= 32 bytes + '\0'              */
#define UGOPR_EXECTYPE       202 /* Sync/Oneway, 1 byte + '\0'                      */
#define UGOPR_PRMS           203 /* Number of parameters, 4 bytes + '\0'            */
#define UGOPR_NOSTATE        204 /* State/Stateless, 1 byte + '\0'                  */

/* Operation information (implementation) */
#define UIOPR_NAME           251 /* Operation name, <= 32 bytes + '\0'              */
#define UIOPR_LITNAME        252 /* Opeation literal name, <= 64 bytes + '\0'       */
#define UIOPR_RETVAL         253 /* Return value, <= 2 bytes + '\0'                 */
#define UIOPR_CONTEXT        254 /* Context, <= 4 bytes + '\0'                      */
#define UIOPR_RETTYPE        255 /* Return type, <= 6 bytes + '\0'                  */
#define UIOPR_ATTR           256 /* @c25860 Operation attributes, <= n bytes + '\0' */

/* Parameter information (generic) */
#define UGPRM_NAME           301 /* Parameter name, <= 32 bytes + '\0'              */ 
#define UGPRM_SEQNUMBER      302 /* ASCII number, <= 4 bytes + '\0'                 */
#define UGPRM_DIRECTION      303 /* In/Out/Both, 1 byte + '\0'                      */
#define UGPRM_TYPE           304 /* Basic/Constructed, 1 byte + '\0'                */
#define UGPRM_DATATYPE       305 /* 1-letter datatype, 1 byte + '\0'                */
#define UGPRM_OBJECTREF      306 /* Object reference (component name, <= 32 bytes + '\0' */
#define UGPRM_REFQUAL        307 /* Reference qualifier (byval, byref) */

#define UGENT_NAME           401 /* Entity name, <= 32 bytes + '\0'                 */
#define UGENT_MODEL          402 /* Model name, <= 32 bytes + '\0'                  */
#define UGENT_FIELDS         403 /* Number of fields, <= 4 bytes + '\0'             */

#define UGFLD_NAME           501 /* Field name, <= 32 bytes + '\0'                  */
#define UGFLD_SEQNUMBER      502 /* ASCII number, <= 4 bytes + '\0'                 */
#define UGFLD_DATATYPE       503 /* 1-letter datatype, 1 byte + '\0'                */
#define UGFLD_SIZE           504 /* ASCII number, <= 12 bytes + '\0'                */
#define UGFLD_BASETYPE       505 /* Packing code translated to c type as string, e.g. "char *" */
#define UGFLD_PACKCODE       506 /* Pure Packing code */
#define UGFLD_SCALE          507 /* Scaling */
#define UGFLD_MANDATORY      508 /* Mandatory */

/* Parameter information (implementation) */
#define UIPRM_NAME           351 /* Parameter name, <= 32 bytes + '\0'              */
#define UIPRM_LITNAME        352 /* Parameter literal name, <= 255 bytes + '\0'     */
#define UIPRM_ARRAYSIZE      353 /* Parameter array size, <= 4 bytes + '\0'         */
#define UIPRM_GLAB           354 /* Subtype, <= 32 bytes + '\0'                     */
#define UIPRM_BASETYPE       355 /* Parameter base type                             */
#define UIPRM_FORMAT         356 /* Parameter format                                */
#define UIPRM_LENGTH         357 /* Parameter length                                */
#define UIPRM_ACCESSMETHOD   358 /* Occurence access method                         */
#define UIPRM_XMLTEMP        359 /* @c29166: XML Template in the parameter          */

/* URR API Functions */
extern long UHCLGET  (UHACT, UCHAR *, UCHAR *, UHACT *);
extern long UHCPTGET (UHACT, int, UHACT *);
extern long UHOPRGET (UHACT, int, UHACT *);
extern long UHPRMGET (UHACT, int, UHACT *);
extern long UHENTGET (UHACT, UHACT *);
extern long UHFLDGET (UHACT, int, UHACT *);
extern long URRSINFO (UHACT, int, int, UCHAR *);
extern long URRLINFO (UHACT, int, int, long *);
extern long URRHFREE (UHACT *);


/* To map functions from lower case to upper case */
#ifdef u_lowercase

/* URR API Functions */
#define uhclget     UHCLGET
#define uhcptget    UHCPTGET
#define uhoprget    UHOPRGET
#define uhprmget    UHPRMGET
#define uhentget    UHENTGET
#define uhfldget    UHFLDGET
#define urrsinfo    URRSINFO
#define urrlinfo    URRLINFO
#define urrhfree    URRHFREE

#endif /* u_lowercase */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* URRDEF_H */

/* End of file urrdef.h */
