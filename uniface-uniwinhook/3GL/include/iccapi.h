/* CONT_ID %fv: iccapi.h-13:incl:2 % %dc: Tue Sep  9 10:04:56 2014 % */

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
121010 b29683    R131    fd  Use operation descriptors for storing knowledge about
                             having string parameters that are Unicode strings.
date   refnum    version who description
*******************************************************************************/

/* File ICCAPI.H */

#ifndef ICCAPI_H
#define ICCAPI_H

/* -- Include Files */
#include "unilimit.h"

/*
 * Activate error codes
 */
#define UACT_SUCCESS                   0 
#define UACT_FAILURE                  -1

/*
 * Name size definitions
 */
#define UFSZ_F16          (16*MAXLENGTH_UTF8)
#define UFSZ_F32          (32*MAXLENGTH_UTF8)

#define ULIBNAMESIZE      (MAXLENGTH_LIBRARY*MAXLENGTH_UTF8)                        /* library */
#define UCPTNAMESIZE      (MAXLENGTH_COMPONENT*MAXLENGTH_UTF8)                      /* component */
#define ULIBCPTNAMESIZE   ((ULIBNAMESIZE + UCPTNAMESIZE)*MAXLENGTH_UTF8 + 1)        /* library + '.' + component */
#define UINSTNAMESIZE     (MAXLENGTH_INSTANCE*MAXLENGTH_UTF8)                       /* instance */
#define UEXTINSTNAMESIZE  (UFSZ_F32)                                                /* @b26627 external instance */
#define UOPRNAMESIZE      (MAXLENGTH_OPERATION*MAXLENGTH_UTF8)                      /* operation */
#define UPRMNAMESIZE      ((MAXLENGTH_ENTITY + MAXLENGTH_MODEL)*MAXLENGTH_UTF8 + 1) /* parameter (entity + '.' + model) */

/*
 * Data type definitions
 */
#define UTYPE_UNKNOWN            0
#define UTYPE_STRING             1
#define UTYPE_BOOLEAN            2
#define UTYPE_NUMERIC            3
#define UTYPE_FLOAT              4
#define UTYPE_DATE               5
#define UTYPE_TIME               6
#define UTYPE_DATETIME           7
#define UTYPE_LDATE              8
#define UTYPE_LTIME              9
#define UTYPE_LDATETIME         10
#define UTYPE_RAW               11
#define UTYPE_IMAGE             12
#define UTYPE_ENTITY            13
#define UTYPE_OCC               14
#define UTYPE_INCL_ENTITY       15
#define UTYPE_HANDLE            16

#define UCHARSET_UTF16          17
#define UCHARSET_CODEPAGE       18

/*
 * Parameter directions
 */
#define UPARM_INPUT           0x01
#define UPARM_OUTPUT          0x02
#define UPARM_INOUT           0x03

#ifndef IOERR_H

#define IOSERR_EXCEPTIONAL            -3   /* I/O error */
#define NETERR_LOGON_ERROR            -21  /* Network logon error */
#define ACTERR_PROTOCOL               -52  /* Protocol error */
#define ACTERR_PARAMETER_GET          -55  /* Parameter get error */
#define ACTERR_PARAMETER_PUT          -56  /* Parameter put error */
#define ACTERR_NO_COMPONENT           -58  /* Component not found */
#define ACTERR_OCC_NOT_ALLOWED        -66  /* Not allowed on occurrence parameter */
#define ACTERR_UNKNOWN                -150 /* Activation error occurred */
#define ACTERR_WRONG_IMPLEMENTATION   -156 /* Wrong/undefined implementation */
#define ACTERR_BAD_HANDLE             -165 /* Invalid 3GL Call In handle  */
#define ACTERR_STATELESS              -166 /* URB/foreign middle ware: NEW_INSTANCE on stateless component*/
#define PROCERR_DATETIME             -1006 /* Invalid datetime */
#define PROCERR_RANGE                -1203 /* Value out of range */
#define PROCERR_MEMORY               -1406 /* Memory allocation failure */

#endif /* IOERR_H */


/* -- Constants */

/* version identification of this API */

#define UICC_MAJOR_VERSION_1    1

#define UICC_MINOR_VERSION_0    0
#define UICC_MINOR_VERSION_1    1

/* indication of instance deletion by operation */

#define UACT_INST_DELETED            -9999

typedef enum {
UICC_3GLTYPE_C_CHAR     = 0,
UICC_3GLTYPE_C_STRING   = 1,    /*C type char* */
UICC_3GLTYPE_C_SHORT    = 2,
UICC_3GLTYPE_C_INT      = 3,
UICC_3GLTYPE_C_LONG     = 4,
UICC_3GLTYPE_C_FLOAT    = 5,
UICC_3GLTYPE_C_DOUBLE   = 6,
UICC_3GLTYPE_RAW        = 7,
UICC_3GLTYPE_ZONED      = 8,
UICC_3GLTYPE_PACKED     = 9,
UICC_3GLTYPE_CONSTRUCTED = 10,
UICC_3GLTYPE_OBJECT     = 11
/* UICC_3GLTYPE_LONG8   future */
} UICC3GLType;

typedef enum {
UICC_3GLRETTYPE_NONE        = 0,
UICC_3GLRETTYPE_FIRSTPAR    = 1,
UICC_3GLRETTYPE_STATUS_CHAR = 2,
UICC_3GLRETTYPE_STATUS_SHORT = 3,
UICC_3GLRETTYPE_STATUS_INT  = 4,
UICC_3GLRETTYPE_STATUS_LONG = 5
} UICC3GLRetType;

typedef enum {
UICC_UNIFACE    = 0,
UICC_3GL        = 1,
UICC_TUX        = 2,  
UICC_ENC        = 3,  
UICC_CIC        = 4,  
UICC_OVS        = 5,  
UICC_COM        = 6,  
UICC_JAV        = 7,  
UICC_IMD        = 8,  
UICC_SSP        = 9   
} UICCInterfaceType;

typedef enum {
UICC_ERR_PARAMETER      = -3,       /* return immediately if parameter is wrong */
UICC_ERR_NEWINTERFACE   = -2,       /* return from UICCxxx if only newer interface supported*/
UICC_ERR_OLDINTERFACE   = -1,       /* return from UICCxxx if only older interface supported*/
UICC_OK                 =  0,
UICC_ERR_MEM            =  1,       /* allocation failed */
UICC_ERR_UFINPAR        =  2,       /* UNIFACE parameter failure */
UICC_ERR_UFOUTPAR       =  3,       /* UNIFACE parameter failure */
UICC_ERR_CONN           =  4,       /* connection to mw failed */
UICC_ERR_CONN_ALREADY   =  5,       /* if already connected and only one connection possible */
UICC_ERR_DISCONN        =  6,       /* disconnection from mw failed */
UICC_ERR_CALL           =  7,       /* function/service/method calling failed */
UICC_ERR_CALLUNKN       =  8,       /* unknown function/service/method called */
UICC_ERR_INPAR          =  9,       /* mw parameter failure */
UICC_ERR_OUTPAR         = 10,       /* mw parameter failure */
UICC_ERR_TX_FAILED      = 11,       /* server could not share client transaction */
UICC_ERR_TX_NO_SUPPORT  = 12,       /* server does not support TX transactions */
UICC_ERR_MISC           = 13        /* mw other errors */
} UICCResultClass;

typedef enum { 
UICC_SUCCESS    = 0,
UICC_ERROR      = 1,
UICC_WARNING    = 2,
UICC_INFO       = 3
} UICCSeverity;

typedef enum { 
UICC_PRMNAME        = 0,
UICC_PRMLITNAME     = 1,
UICC_PRMTYPENAME    = 2,
UICC_PRMLITTYPENAME = 3
} UICCNameClass;

/* (@b29683) For use with GETPRMINFO, SETPRMINFO, GETOPERINFO and SETOPERINFO. */
typedef enum {
UICC_PRMUNICODE     = 0
} UICCPrmInfoKind;

/* maximums */

/*#define UICC_MAX_FLDSIZE  32767*/

/*#define UICC_MAX_STRSIZE    255 */    /* maximum of all interface strings */
#define UICC_MAX_STRSIZE    UPRMNAMESIZE     /* maximum of all interface strings */
#define UICC_MAX_LOGFLDSIZE 64      /* maximum of user, password etc logon fields */

/* -- Structures */

typedef struct {
unsigned long low;
long          high;
} LONG8;

typedef struct {
void *  a;  
long    b;
int     c;
} UICCLogonHandle;

/* Call back functions 
   the call back functions are needed to get operation and parameter 
   info and data; they can have the Operation Handle as input or a 
   requested entity parameter handle. We use the same names as the callin API 
   but without the starting 'u' and offer new functions if callin does not 
   provide one.
*/
#ifdef FREE
#  undef FREE
#endif
typedef struct {
long (*PRMDIR     ) ( void* hOp, int seqNr, int* pParmDirection);
long (*PRMUTYPE   ) ( void* hOpOrEnt, int seqNr, int* pType);
long (*PRMPC      ) ( void* hOpOrEnt, int seqNr, int* pPC);
long (*PRMLEN     ) ( void* hOpOrEnt, int seqNr, long* pLen);
long (*PRM3GLTYPE ) ( void* hOpOrEnt, int seqNr, UICC3GLType* p3glType);
long (*PRM3GLARRSIZE) ( void* hOp, int seqNr, long* p3glArrSize);
long (*PRMGETH    ) ( void* hOp, int seqNr, int bDetach, void** phEnt);
long (*FREEH      ) ( void** hEnt);
long (*ENTOCCS    ) ( void* hEnt, long* pOccCount);
long (*ENTFLDS    ) ( void* hEnt, long* pFldCount);
long (*ENTCREO    ) ( void* hEnt, long occNr);
long (*ENTSETO    ) ( void* hEnt, long occNr);
int  (*ENTOCCSFLD ) ( void* hEnt, int seqnr);         
long (*CHAR2UF    ) ( void* hOpOrEnt, int seqNr, char exChar);
long (*INT2UF     ) ( void* hOpOrEnt, int seqNr, int exInt);
long (*LONG2UF    ) ( void* hOpOrEnt, int seqNr, long exLong);
long (*DBL2UF     ) ( void* hOpOrEnt, int seqNr, double exDouble);
long (*STR2UF     ) ( void* hOpOrEnt, int seqNr, char* exString);
long (*BIN2UF     ) ( void* hOpOrEnt, int seqNr, void* exData, long exLength);
long (*BOOL2UF    ) ( void* hOpOrEnt, int seqNr, char* exBoolean, long exLength);
long (*DATE2UF    ) ( void* hOpOrEnt, int seqNr, char* exDate);
long (*ZONED2UF   ) ( void* hOpOrEnt, int seqNr, char* exZoned);
long (*PACKED2UF  ) ( void* hOpOrEnt, int seqNr, char* exPacked);    
long (*UF2CHAR    ) ( void* hOpOrEnt, int seqNr, char* pExChar);
long (*UF2INT     ) ( void* hOpOrEnt, int seqNr, int* pExInt);
long (*UF2LONG    ) ( void* hOpOrEnt, int seqNr, long* pExLong);
long (*UF2DBL     ) ( void* hOpOrEnt, int seqNr, double* pExDouble);
long (*UF2STR     ) ( void* hOpOrEnt, int seqNr, char** pExString);
long (*UF2BIN     ) ( void* hOpOrEnt, int seqNr, void** pExData, long* pExLength);
long (*UF2BOOL    ) ( void* hOpOrEnt, int seqNr, char* pExBoolean, long* pExLength);
long (*UF2DATE    ) ( void* hOpOrEnt, int seqNr, char** pExDate);
long (*UF2ZONED   ) ( void* hOpOrEnt, int seqNr, char** pExZoned);
long (*UF2PACKED  ) ( void* hOpOrEnt, int seqNr, char** pExPacked);
long (*FREE       ) ( void* hOpOrEnt, void* memory);
long (*NAME       ) ( void* hOpOrEnt, int seqNr, UICCNameClass className, char* pName);
long (*LOGON      ) ( UICCLogonHandle hLogon, char** fieldv, int fieldc, char * ErrorString);
/*  The following are for UICC_MAJOR_VERSION_1, UICC_MINOR_VERSION_1 */
long (*EXOB2UF    ) ( void* hOp, int seqNr, char* driverName, void* hExtObj);
long (*UF2EXOB    ) ( void* hOp, int seqNr, char* driverName, void** hExtObj);
long (*UF2EXOBSTR ) (void *	hOp,int	seqNr, char *driverName,  char **pInstanceName); /* @pr1 */
/*@e21626: Added for Unicode */
long (*WSTR2UF    ) ( void* hOpOrEnt, int seqNr, void* exString);
long (*UF2WSTR    ) ( void* hOpOrEnt, int seqNr, void** pExString);
/* (@b29683) Get and set information about parameters and operations. */
long (*SETPRMINFO ) ( void* hOp, int seqNr, UICCPrmInfoKind infoKind, void* info);
long (*GETPRMINFO ) ( void* hOp, int seqNr, UICCPrmInfoKind infoKind, void** pInfo);
long (*SETOPERINFO) ( void* hOp, UICCPrmInfoKind infoKind, void* info);
long (*GETOPERINFO) ( void* hOp, UICCPrmInfoKind infoKind, void** pInfo);
} UICCCallbackFuncs;


typedef struct {
UICCCallbackFuncs const * CallbackFuncs;
char *                    DrvParams;        /* USYS$xxx_PARAMS */
char *                    LogonInfo;        /* xxx:node|user|password|etc */
UICCLogonHandle           hLogon;           /* 1st param of LOGON callback function */
int                       ServerId;
} UICCInitInfo;

typedef struct {
char *              Name;
char *              Props;            /* PROC NEW_INSTANCE property string */
/* 
** @pr1 -  External alias generated by COM driver 32 chars + zero as defined for alias generation 
*/
char                extAliasName[UINSTNAMESIZE + 1];       /* @b26627 */ 
} UICCInstInfo;

typedef struct {
char *              Name;
char *              LitName;
char *              InterfaceID;
UICCInterfaceType   InterfaceType; 
int                 SyncMode;
int                 Transactional;  /* supply trans-id with call or not */
char *              Props;          /* from repository (UIMPLATTR.USIMPLE) */
int                 Statefull;
} UICCCompInfo;

typedef struct {
char *              Name;
char *              LitName;
long                PrmCount;
UICC3GLRetType      Opr3GLRetType;
char *              Props;          /* future */
int                 Statefull;      /* from repository */
void *              hOper;          /* Operation handle: needed for call back */
} UICCOperInfo;

typedef struct {
long                UFProcError;  /* UNIFACE $PROCERROR, if you leave it zero */
                                  /* Class will be mapped to a suitable UNIFACE error */
UICCResultClass     Class;          
UICCSeverity        Severity; 
long                ForeignStatus;
char                ForeignStatusMessage[UICC_MAX_STRSIZE+1];
} UICCStatusInfo;

typedef struct {
int MajorVersion;
int MinorVersion;

/* Initialization functions (mandatory) */
long (*UICCInit)(               void              **hConnect,
                                UICCInitInfo       *InitInfo, 
                                UICCStatusInfo     *StatusInfo);
long (*UICCExit)(               void               *hConnect,
                                UICCStatusInfo     *StatusInfo);

/* Statefull components/operation functions (optional, so can be NULL) */
long (*UICCNewInst)(            void               *hConnect,
                                UICCInstInfo       *InstInfo,
                                UICCCompInfo       *CompInfo,
                                void              **hInst,
                                UICCStatusInfo     *StatusInfo);
long (*UICCDelInst)(            void               *hConnect,
                                void               *hInst, 
                                UICCCompInfo       *CompInfo,
                                UICCStatusInfo     *StatusInfo);
long (*UICCInvokeOperation)(    void               *hConnect,
                                void               *hInst,
                                UICCInstInfo       *InstInfo,
                                UICCCompInfo       *CompInfo,
                                UICCOperInfo       *OperInfo, 
                                long               *CompReturnStatus,
                                UICCStatusInfo     *StatusInfo);

/* Stateless operation function (mandatory) */
long (*UICCInvokeService)(      void               *hConnect,
                                UICCCompInfo       *CompInfo,
                                UICCOperInfo       *OperInfo, 
                                long               *CompReturnStatus, 
                                UICCStatusInfo     *StatusInfo);

/* Transaction functions (optional, so can be NULL) */
long (*UICCBeginTransaction)(   UICCStatusInfo     *StatusInfo);
long (*UICCPrepareCommit)(      UICCStatusInfo     *StatusInfo);
long (*UICCCommit)(             UICCStatusInfo     *StatusInfo);
long (*UICCRollback)(           UICCStatusInfo     *StatusInfo);

/*  The following are for UICC_MAJOR_VERSION_1, UICC_MINOR_VERSION_1 */
/*  Ask driver to wrap an external object so that it looks like a call-out instance */
long (*UICCWrapExtObj)(         void               *hConnect,
                                void               *hExtObj,
                                UICCInstInfo       *InstInfo,
                                UICCCompInfo       *CompInfo,
                                void              **hInst,
                                UICCStatusInfo     *StatusInfo);
/*  Ask driver to expose an instance as a call-in external object */
long (*UICCExposeInstance)(     void               *hConnect,
                                void               *hIn,
                                UICCCompInfo       *CompInfo,
                                void              **hExtObj,
                                UICCStatusInfo     *StatusInfo);
} UICCFuncs;

#endif /* ICCAPI_H */
