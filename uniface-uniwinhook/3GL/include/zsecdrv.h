/* CONT_ID %fv: zsecdrv.h-9:incl:1 % %dc: Tue Sep  9 10:00:46 2014 %"; */

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
080204 c26394    930101  ahn extend interface for SMTP security drivers
080205 c26395    930101  ahn Add SetSecurity
080206 c26395;1  930101  ahn Amend LogonSMTP
080218 c26406    930101  ahn Add GetSecurity
date   refnum    version who description
*******************************************************************************/

#ifndef zsecdrv_h
#define zsecdrv_h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/****************************************************************************/

typedef struct USecTag USecDrv;
typedef long (*SecFunc)(USecDrv *);

/* @c26395 the queue structure */
typedef struct USecDrvQtag USecDrvQ;
typedef enum
{
    USDQSTATE_INVALID = 0,      /* un-initialised value */
    USDQSTATE_CREATE = 1,       /* new queue should be created */           
    USDQSTATE_APPEND = 2,       /* append next driver to queue */
    USDQSTATE_LOCKED = 3        /* not allowed to change queue */
} USDQState;

struct USecDrvQtag
{
    USDQState state;
    USecDrv *drv;
};

struct USecTag
{
    struct unibas *unibas;                              /* Uniface internal use */
    SecFunc SecEntry;                                   /* Driver entry point */
    void *UserToken;                                    /* user token from validation */
    void *DrvArea;                                      /* Implementation work area */
    unsigned char *Username;                            /* username */
    unsigned char *Passwd;                              /* password */
    unsigned char *NewPasswd;                           /* new password */
    unsigned char *InBuf;                               /* Input buffer */
    unsigned char *OutBuf;                              /* Output buffer */
    unsigned char *ErrMsg;                              /* Error message for Error */
    long Error;                                         /* The error that occured */
    int InBufLen;                                       /* Length of input buffer */
    int OutBufLen;                                      /* Output buffer length */
    int InDataLen;                                      /* Length of data in InBuf */
    int OutDataLen;                                     /* Length of data in OutBuf */
    int ErrMsgLen;                                      /* Length of data in ErrMsg */
    int Flags1;                                         /* At least 16 flags */
    unsigned char Function;                             /* Requested driver function */

    /* @c26394 new members added at end so that older implementations of client server */
    /* drivers do not need to be re-compiled */
    USecDrv *fwd;                                       /* next security driver structure */
    USecDrv *bck;                                       /* previous security driver structure */
    unsigned char *Properties;                          /* driver properties */
    unsigned char *Parameters;                          /* driver parameters */
};

/* Macros for manipulating the Flags1 */
#define SecCodeConnectFlag      0x0001                  /* Encode/decode connection messages */
#define SecCodeMsgHdrFlag       0x0002                  /* Encode/decode message headers fields */
#define SecAuthenticateFlag     0x0004                  /* Perform username authentication */
#define SecUserPassInfoFlag     0x0008                  /* Get username password info */
#define SecPassChngFlag         0x0010                  /* Change password */
#define SecOpenMsgFlag          0x0020                  /* Authentication protocol messages */
#define SecCodeMsgFlag          0x0040                  /* Encode/decode complete messages */
#define SecCloseMsgFlag         0x0080                  /* End authenticated session protocol messages */
#define SecRTInfoFlag           0x0100                  /* Driver provides runtime information */
#define usec_reserved1          0x0200                  /* reserved */
#define usec_reserved2          0x0400                  /* reserved */
#define usec_reserved3          0x0800                  /* reserved */
#define usec_reserved4          0x1000                  /* reserved */
#define usec_reserved5          0x2000                  /* reserved */
#define SecUseMandFlag          0x4000                  /* Use of this module is mandatory */
#define SecInUseFlag            0x8000                  /* This module is in use for this connection */

#define USecIsConnectEnc(s)     ((s) ? (s)->Flags1 & SecCodeConnectFlag : 0)
#define USecSetConnectEnc(s)    ((s) ? (s)->Flags1 |= SecCodeConnectFlag : 0)
#define USecZeroConnectEnc(s)   ((s) ? (s)->Flags1 &= ~SecCodeConnectFlag : 0)

#define USecIsMsgHdrEnc(s)      ((s) ? (s)->Flags1 & SecCodeMsgHdrFlag : 0)
#define USecSetMsgHdrEnc(s)     ((s) ? (s)->Flags1 |= SecCodeMsgHdrFlag : 0)
#define USecZeroMsgHdrEnc(s)    ((s) ? (s)->Flags1 &= ~SecCodeMsgHdrFlag : 0)

#define USecIsUserPassVal(s)    ((s) ? (s)->Flags1 & SecAuthenticateFlag : 0)
#define USecSetUserPassVal(s)   ((s) ? (s)->Flags1 |= SecAuthenticateFlag : 0)
#define USecZeroUserPassVal(s)  ((s) ? (s)->Flags1 &= ~SecAuthenticateFlag : 0)

#define USecIsUserPassInfo(s)   ((s) ? (s)->Flags1 & SecUserPassInfoFlag : 0)
#define USecSetUserPassInfo(s)  ((s) ? (s)->Flags1 |= SecUserPassInfoFlag : 0)
#define USecZeroUserPassInfo(s) ((s) ? (s)->Flags1 &= ~SecUserPassInfoFlag : 0)

#define USecIsPassChng(s)       ((s) ? (s)->Flags1 & SecPassChngFlag : 0)
#define USecSetPassChng(s)      ((s) ? (s)->Flags1 |= SecPassChngFlag : 0)
#define USecZeroPassChng(s)     ((s) ? (s)->Flags1 &= ~SecPassChngFlag : 0)
/* @c26394 */
#define USecIsOpenMsg(s)       ((s) ? (s)->Flags1 & SecOpenMsgFlag : 0)
#define USecSetOpenMsg(s)      ((s) ? (s)->Flags1 |= SecOpenMsgFlag : 0)
#define USecZeroOpenMsg(s)     ((s) ? (s)->Flags1 &= ~SecOpenMsgFlag : 0)

#define USecIsCodeMsg(s)       ((s) ? (s)->Flags1 & SecCodeMsgFlag : 0)
#define USecSetCodeMsg(s)      ((s) ? (s)->Flags1 |= SecCodeMsgFlag : 0)
#define USecZeroCodeMsg(s)     ((s) ? (s)->Flags1 &= ~SecCodeMsgFlag : 0)

#define USecIsCloseMsg(s)       ((s) ? (s)->Flags1 & SecCloseMsgFlag : 0)
#define USecSetCloseMsg(s)      ((s) ? (s)->Flags1 |= SecCloseMsgFlag : 0)
#define USecZeroCloseMsg(s)     ((s) ? (s)->Flags1 &= ~SecCloseMsgFlag : 0)
/* @c26395 */
#define USecIsUseMand(s)       ((s) ? (s)->Flags1 & SecUseMandFlag : 0)
#define USecSetUseMand(s)      ((s) ? (s)->Flags1 |= SecUseMandFlag : 0)
#define USecZeroUseMand(s)     ((s) ? (s)->Flags1 &= ~SecUseMandFlag : 0)
/* @c26395;1 */
#define USecIsInUse(s)       ((s) ? (s)->Flags1 & SecInUseFlag : 0)
#define USecSetInUse(s)      ((s) ? (s)->Flags1 |= SecInUseFlag : 0)
#define USecZeroInUse(s)     ((s) ? (s)->Flags1 &= ~SecInUseFlag : 0)
/* @c26406 */
#define USecIsRTInfo(s)       ((s) ? (s)->Flags1 & SecRTInfoFlag : 0)
#define USecSetRTInfo(s)      ((s) ? (s)->Flags1 |= SecRTInfoFlag : 0)
#define USecZeroRTInfo(s)     ((s) ? (s)->Flags1 &= ~SecRTInfoFlag : 0)

/* macros to define the avialable functions */
#define USEC_DRVINFO            'I'                     /* Specify functionality */
#define USEC_ENCODE             'E'                     /* Encode InBuf to OutBuf */
#define USEC_DECODE             'D'                     /* Decode InBuf to OutBuf */
#define USEC_AUTHENTICATE       'A'                     /* validate username password */
#define USEC_USERPASSINFO       'U'                     /* get username password information */
#define USEC_PASSCHNG           'P'                     /* change password */
#define USEC_CLOSE              'C'                     /* close */

/* @c26394 */
#define USEC_VERIFY             'V'                     /* verify supported functionality */
#define USEC_OPENMSG            'O'                     /* provide authentication protocol messages */
#define USEC_CLOSEMSG           'S'                     /* provide end of authenticated session messages */
/* @c26406 */
#define USEC_RTINFO             'R'                     /* provide runtime information */

#define SecFuncStr(S)   \
(((S)->Function == USEC_DRVINFO) ? "USEC_DRVINFO" : \
 ((S)->Function == USEC_ENCODE) ? "USEC_ENCODE" : \
 ((S)->Function == USEC_DECODE) ? "USEC_DECODE" : \
 ((S)->Function == USEC_AUTHENTICATE) ? "USEC_AUTHENTICATE" : \
 ((S)->Function == USEC_USERPASSINFO) ? "USEC_USERPASSINFO" : \
 ((S)->Function == USEC_PASSCHNG) ? "USEC_PASSCHNG" : \
 ((S)->Function == USEC_CLOSE) ? "USEC_CLOSE" : \
 ((S)->Function == USEC_VERIFY) ? "USEC_VERIFY" : \
 ((S)->Function == USEC_OPENMSG) ? "USEC_OPENMSG" : \
 ((S)->Function == USEC_RTINFO) ? "USEC_RTINFO" : \
 ((S)->Function == USEC_CLOSEMSG) ? "USEC_CLOSEMSG" : "Unknown function")

/* macros to define drivers return status */
#define USEC_SUCCESS            0
#define USEC_INFO               1
#define USEC_ERROR              2
#define USEC_CONTINUE           3
#define USEC_WRITEONLY          4
#define USEC_READONLY           5

#define SecRetStr(r) \
(((r) == USEC_SUCCESS) ? "USEC_SUCCESS" : \
 ((r) == USEC_INFO) ? "USEC_INFO" : \
 ((r) == USEC_CONTINUE) ? "USEC_CONTINUE" : \
 ((r) == USEC_WRITEONLY) ? "USEC_WRITEONLY" : \
 ((r) == USEC_READONLY) ? "USEC_READONLY" : \
 ((r) == USEC_ERROR) ? "USEC_ERROR" : "Unknown status")
/******************************************************************************/
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* zsecdrv_h */

