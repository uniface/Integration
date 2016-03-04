/* @(#)CONT_ID %fv: unidbm.h-38.1.1.1.2:incl:1 % %dc: Thu May 28 17:34:46 2015 % (#)@ */

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
980910 e01637    8.0.02  KKN 728SYNC: wp2, UIODEF.H-10,11(#pr8)
971224 e01637    7.2.03  sse URB: Add TMEnabled/TMCapable flags
980914  12730    8.0.02  lra 728SYNC: Added changes made by Ruud
980921  13157    8.0.02  tti 728SYNC: wp34, uiodef.h-12,(#pr9)
970126 e02431    7.2.03  sse URB: two_phase != 0 means 2-phase commit driver
990223 e05963    8003A1  sse 728SYNC: 7204 DBMS/SP changes in uiodef.h-19
981201 e04447    7.2.04  sse Add uinfo SPEntry for DBMS Stored Procedures
011205 b17070    8.2.03  mwi Unsigned packed support
030526 b25204    B315    ahn perf: uctrl hitmeta becomes hitfmt
030612 e19520    8.4.01  jdk Allow more than 255 operations in sig
050411 c21710    910102  rl  implementation of pW characters and check size with StoreSize
050510 c21598    910102  sse Added pW packing code
050707 c22093    910102  sse Further changes for UNICODE packing code in kernel for DBMS driver
050725 c22150    910102  ete uflenchars added to ufldlst struct for W packing code
060117 b26603    M431    kh  Extend 10K limit to 10MB limit.
060223 c23135    910102  sse Being able to allocate less bytes for W packing code
060503 c23727    910102  sse Mark profile usage in flist
060117 b26603     M431   kh  Extend 10K limit to 10MB limit.
060125 b26551     M431   ete Make 'special string raw to graphic datatype' an
                             option that a driver (DB2 in this case) can set
                             and which causes special string raw fields to be
                             able to hold wildcards (dbmclaus.c)
080220 b27536     D603   ete uwdat & data are offsets into uctrl->uwlist; they
                             are "signed short"s so they can reach only 32767 bytes.
                             Make them of type ptrdiff_t
080910 b27848     O204   hhe Increase limit for key for MSS U4.0 driver to 900 bytes
120320 b29643     P229   ete 64 bit Solid writes a 64 bit field length into uflen, overwriting ufname
121010 b29683    R131    fd  Use operation descriptors for storing knowledge about
                             having string parameters that are Unicode strings.
140606 b30405     X501   ete Introduce dbmsmaxrecsiz. The existing recsiz is a short so it can't hold
                             big enough values. Also, changing it will cause existing overflow tables
                             to not work so it can't be changed. This new dbmsrecsiz can be changed
                             if a newer version of the DBMS allows bigger rowsizes.
                             If a driver does not set it (0) it defaults back to recsiz.
150519 c30487    970101  mbg Upscaled MAX_KEY_LENGTH. Hana System-Table contains very long combined unicode keys (each key=512byte long). 
date   refnum    version who description
*******************************************************************************/

#ifndef UNIDBM_H
#define UNIDBM_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/****************************************************************************
 *
 * Public typedefs, packing codes and string handling routines.
 *
 ****************************************************************************/
#include <stddef.h>
#include "unityp.h"
#include "unipck.h"
#include "unistr.h"

/****************************************************************************
 *
 * Public constants.
 *
 ****************************************************************************/

#define uiomax  8192                    /** driver transfer data-buffer size */
#define maxdrv  30
#define MAX_KEY_LENGTH	4096            /* @b27848: double the orginal key length size from 512 to 1024, Hana has long SYS-TABLE keys */

#define INPUT_BIT  (0x0400)             /** bit 9 INPUT parameter */
#define OUTPUT_BIT (0x0800)             /** bit 10 OUTPUT parameter */
#define MULVAL_BIT (0x1000)             /** bit 11 MULTI VALUE parameter */

#define OVERFLOW_PART_SEGM (1)          /** SEGM field indicator of the overflow table */
#define OVERFLOW_PART_DATA (2)          /** DATA field indicator of the overflow table */

/****************************************************************************
 *
 * Define type WAREA if not yet defined by includer,
 *
 ****************************************************************************/

#ifndef DRIVER_WAREA_DEFINED
typedef unsigned char WAREA;
#endif


/****************************************************************************
 *
 * Public data definitions.
 *
 * Note: data definitions contain elements which are reserved for private
 *       use by Uniface. Only access those elements which are covered by
 *       the DBMS Driver Cookbook.
 *
 ****************************************************************************/

/**
UNIFACE input/output control block
*/
struct uctrl
{
    struct uctrl   *uchfw;              /** address next control block */
    struct uctrl   *uchbw;              /** address previous control block */
    struct udriver *udrvtab;            /** pointer to driver control data */
    long (*dis)(struct uctrl *);        /** UNIFACE driver dispatch address */
    unsigned short func;                /** driver function */
    unsigned char  udrvcod;             /** pseudo code for dbms */
    short          udrvnum;             /** driver sequence number */
    unsigned long  tid;                 /** thread identification */
    long           udrverr;             /** driver error return code */
    struct unibas  *unibas;             /** base pointer to Uniface workarea */
    struct uiobas  *uiobas;             /** base pointer to Uniface io workarea */
    unsigned char  *iobuf;              /** I/O data buffer */
    unsigned char  *sqlbuf;             /** (sql) work buffer */
    unsigned char  *whrbuf;             /** (where) work buffer */
    struct udecode *udec;               /** decode information */
    struct uctrl   *mctrl;              /** link to overflow control block */
    WAREA *udrv;                        /** UNIFACE driver 'control data' */
    unsigned char  *uname;              /** file/table name string */
    unsigned char  *umisc;              /** miscellanious data */
    unsigned char  *ulit;               /** literal pool (idents) */
    unsigned char  *utrnin;             /** dbms idents conversion */
    unsigned char  *uident;             /** entity0schema0..... */
    unsigned char  *ufstring;           /** fieldnames string */
    struct uctrl   *ulink;              /** outer entity */
    struct ufldlst *uflist;             /** fieldlist (struct ufldlst) */
    struct uidxlst *uilist;             /** indexlist (struct uidxlst) */
    struct uwhrlst *uwlist;             /** wherelist (struct uwhrlst) */
    struct uordlst *uolist;             /** orderlist (struct uordlst) */
    unsigned char  *dbdastart;          /** start of db data record */
    struct hitlist *hitlist;
    struct hitlist *hitchain;
    short          dbdasegsiz;          /** segmentsize of dbdata */
    unsigned char  Conformance;         /** SQL conformance Level  */
    unsigned char  usubmode;            /** sub open, for RI support (FIRST_CALL,  LAST_CALL) */
    struct uactvinfo *actvinfo;
    struct uctrl   *uctrlList;          /** Internal tempory set of uctrls */
    UPATH          upathDest;           /** link to Destination path administration (on AS/400, it is not a long )  */
    struct unetsrc *netsource;          /** network source */
    struct unetrte *netroute;           /** network routing (if applicable) */
    struct unetdst *netdest;            /** network destination */
    unsigned char  blobToDo;            /** True when Blobs must be fetched */
    unsigned char  *ublob;              /** save information for blobs */
    unsigned char  *ublobcont;          /** start information for blobs */
    long           ubloblen;            /** save information for blobs */
    unsigned char  *sqldata;            /** sql transport pointer */
    struct hit     *uhitpad;            /** pointer to hit */
    UPATH          upath;               /** link to path administration (on AS/400, it is not a long ) */
    struct nctrl   *nctrl;              /** pointer to network control block */
    struct logdata *dblog;              /** dbms logon data */
    unsigned char  *urlink;             /** RIB table */
    struct uiflst  *uiflist;            /** iflist (struct uiflst) */
    short          ucache;              /** maximum caching size (0 = disable caching) */
    unsigned char  hitmode;             /** status for addhit */
    unsigned char  utrunc1;             /** if true truncation of trailing spaces, */
                                        /**< should leave one space */
    unsigned char  two_phase;           /** != 0 means support 2-phase commit */
    unsigned char  path_type;           /** internal only */
    short          uifnum;              /** # of iflist entries */
    unsigned short ustamp;              /** general I/O count number */
    short          uftot;               /** total nr of field/entity entries */
    short          uopen;               /** open indicator */
    short          Free_sh;             /** free for use */
    short          ulock;               /** lock indication i.e. if on no close */
                                        /**< request will be done by UNIFACE */
    short          ufnum;               /** # of db entries in fieldlist */
    short          uinum;               /** # of entries in indexlist */
    short          uwnum;               /** # of entries in wherelist */
    short          uonum;               /** # of entries in orderlist */
    short          umaxhits;            /** hitlist stepsize (0 = all) */
    short          uprimlen;            /** length (in bytes) of primary (logical) key */
    short          segcnt;              /** nr of overflow segments in db */
    short          lstfld;              /** last field required in external schema */
    short          udrvini;             /** driver logon initialising code */
    short          vsfnr;               /** field nr of first segmented field */
    short          TransActionNumber;   /** internal, only indication parallel TX */
    short          uerrtyp;             /** errortype */
    unsigned char  usumflag;            /** summation flag */
    unsigned char  ucbstat;             /** status control block, if not 0 control block marked for deletion */
    unsigned char  umod;                /** if true modifications on ucontrol made */
    unsigned char  where;               /** support of additional where clause */
    unsigned char  txtsearch;           /** support of where on long fields */
    unsigned char  udbms[3];            /** 3-character DBMS mnemonic */
    unsigned char  unet[3];             /** 3-character network mnemonic */
    unsigned char  upseudb;             /** 1-character pseudo DBMS mnemonic */
    unsigned char  ufixvar;             /** indication Fixed/Variable record; */
                                        /**< true if variable length / long field */
    unsigned char  uoverflw;            /** indication overflow control block */
    unsigned char  unoupd;              /** indication no update allowed */
    unsigned char  urdbykey;            /** true means 'do not use physical address' */
    unsigned char  uralen;              /** size of physical address of records/rows */
    unsigned char  ufiles;              /** file number of internal UNIFACE/IDF files */
    unsigned char  uversion;            /** field U_VERSION is available */
    unsigned char  uoptlock;            /** driver supports only optimistic locking */
    unsigned char  umode;               /** function modifier */
    unsigned char  udbtyp;              /** 0 = fieldlevel , 1 = record level I/O */
    unsigned char  udbsub;              /** driver sub-type 1 = link setup requested */
    unsigned char  uopnreq;             /** database open request needed */
    unsigned char  uforcfix;            /** force variable records into fixed records */
    unsigned char  unoconst;            /** 1, 2, 3: DBMS constraint handling */
    unsigned char  unetcod;             /** pseudo code for real network */
    unsigned char  udynopt;             /** dynamic optimistic locking request */
    unsigned char  uprofil[2];          /** profile ascii characters for any(*) */
                                        /**< and one character(%) */
    unsigned char  ucset;               /** characterset (0=DEC multi; 1=IBM RT...) */
    unsigned char  opnfil;              /** info->opnfil */
    unsigned char  segctrl;             /** write main rec before/after segs */
    unsigned char  fillercharacter;     /** blank (ascii or ebcdic) */
    unsigned char  like;                /** generate LIKE and NOT_LIKE */
    unsigned char  Type;                /** Table is a view (no primaryKey) addrec only */
    unsigned char  TableOpenLevel;
    long           udatlen;             /* I/O datalength @b266403 */
    long           urecsiz;             /* maximum record size @b266403 */
    unsigned char  SqlString;
    unsigned char  SqlNumber;
    unsigned char  SqlFloat;
    unsigned char  SqlDate;
    unsigned char  SqlTime;
    unsigned char  SqlDateTime;
    unsigned char  SqlBoolean;
    unsigned char  NotInDB;             /** Flag Entity Not-in-DB */
    int            OpenError;
    unsigned char  hitfmt;              /** now multi value field */
    int            FlatFile:1;          /** indicate that a control block belongs to a flatfile */
    int            IdleSignalToSend:1;
    int            offsetSpecified:1;   /** (@c29257) "offset" option is used, for the read statement. */
    int            FreeBits:13;
    long           ucounthits;          /** count # of addhits/addrecs in select request  */
    unsigned long  Options;             /** room for several Options see OPTION_... */
    unsigned char  TMEnabled;           /** Mark driver supports a TM control (0=no/1=yes) */
    short          *mapFids;            /** Internal Id's of Fields  */
    unsigned char  IdleSignalWanted;
    char           svavail;
    unsigned int   refCount;            /** Reference count */
    unsigned char  wcset;               /** Charset for pW storage */
    unsigned char  wcsetCharAllocSize;  /** Size to allocate for one wide character */

    /* Next fields are used to fill and scan for wide string data in DB fields */
    unsigned short wsizeSpecialChars;   /** Size in bytes of /m wProfileAny, /m wProfileOne and /m wFillerCharacter */
    unsigned char  wProfileAny[4];      /** 1-4 bytes for wide profile any match */
    unsigned char  wProfileOne[4];      /** 1-4 bytes for wide profile one match */
    unsigned char  wFillerCharacter[4]; /** 1-4 bytes for wide blank (ascii, ebcdic or unicode) */
    unsigned char  WCharBehavior;       /** U=Unicode; B=BMP; C=Charset  */
    long           ulimhits;            /** limitation of number of selected hits */
    long           selectOffset;        /** (@c29257) Offset for "select with offset" (pagination) */
};

#define OPTION_SUPPORT_SUBSET           1       /** Driver supports excluding of fields in I/O  */
#define OPTION_SUPPORT_FLUSH            2       /** Driver supports close mode #1 for cursor flush  */
#define OPTION_SUPPORT_SELECT_OFFSET    4       /** Driver supports select using offset and limit (@c29257) */
#define OPTION_SUPPORT_NOTRUNCATE       8       /** Driver requires full initialization of packed fields */
#define OPTION_SUPPORT_UNSIGNED_PACKED 16       /** Driver supports unsigned packed fields*/
#define OPTION_SUPPORT_SS_RAW_IS_DBCS  32       /*  Driver supports mapping of special string raw to a double byte string datatype @b26551 */

#define SS_RAW_IS_DBCS(uctrl)  (uctrl->Options & OPTION_SUPPORT_SS_RAW_IS_DBCS) /* @b26551 */

#define IDLESIGNALREAD			1
#define IDLESIGNALWRITE			2
#define IDLESIGNALMISC			4

#define pMAXPACKING     512                   /* # of Possible PackingCodes */

/**
UNIFACE driver info/characteristics data
*/
struct uinfo
{
    long  (*dis)(struct uctrl *);             /** address of UNIFACE driver dispatch address */
    short drvsiz;                             /** size of workspace for io driver 'control data' */
    short indexes;                            /** additional space for io driver per index */
    short fields;                             /** additional space for io driver per field */
    short maxhits;                            /** maximum nr of hits to select */
    short recsiz;                             /** Maximum record size.
                                                  0 = default = UNIFACE maximum = 8192 for the fixed
                                                  part of records with variable length fields;
                                                  for records with only fixed length fields
                                                  dbmsmaxrecsiz is used, unless it is 0 in which case
                                                  recsiz is used; if both are 0 it is unlimited.
                                               **/
    short sizmod;                             /** round up recordsize to multiple of sizmod */
    short maxkey;                             /** maximum key size supported by DBMS */
    short maxfield;                           /** maximum fieldsize */
    short maxcur;                             /** maximum cursors = install[d]->maxcur */
    short updef[16];                          /** type defaults ###NFDTEB */
    short upfmt[pMAXPACKING];                 /** C,U,R,LC,LU,LR,#,#, N1-32, P1-16, Q1-16, */
                                              /**< I1, I2, I3, I4, I8, F4 ,F8 ,F16, D1-16, */
                                              /**< T1-16, E1-16, B1-B8,M1-M8, J1-32, O1-32, */
                                              /**< Y1-8, Z1-8 */
    unsigned char drvnum;                     /** driver sequence number */
    unsigned char dbms[3];                    /** 3-character DBMS mnemonic */
    unsigned char dbtyp;                      /** 0 = fieldlevel , 1 = record level I/O */
    unsigned char ralen;                      /** size of  record/row address */
    unsigned char opnfil;                     /** maximum simultaneous active (open) files */
    unsigned char osegm;                      /** segmented primary key for overflow */
    unsigned char bound;                      /** field line up on 2-4 byte boundary */
    unsigned char filll;                      /** # of filler bytes preceding the fields */
    unsigned char fillt;                      /** # of filler bytes after the fields */
    unsigned char fillv;                      /** # of filler bytes in front of the long */
                                              /**< and variable length fields */
    unsigned char limkey;                     /** if true: key(s) are ASCII characters only */
    unsigned char limvar;                     /** if true: variable length fields are */
                                              /**< ASCII characters only */
    unsigned char num[6];                     /** packing code data type numeric/float */
                                              /**< if available (10,10,10,11,11,) */
    unsigned char nsize[6];                   /** packing sizes if available, */
                                              /**< (1,2,4,4,8,minimum); */
                                              /**< array: [0] for I1 (char), */
                                              /**< [1] for I2 (short), */
                                              /**< [2] for I4 (long), */
                                              /**< [3] for F (float), */
                                              /**< [4] for D (double), */
                                              /**< [5] for N (number) */
    unsigned char date;                       /** packing code DATE fields */
    unsigned char datsiz;                     /** size of DATE fields */
    unsigned char datfmt;                     /** format of DATE fields */
    unsigned char time;                       /** packing code TIME fields */
    unsigned char timsiz;                     /** size of TIME fields */
    unsigned char timfmt;                     /** format of TIME fields */
    unsigned char dtime;                      /** packing code DATE-TIME fields */
    unsigned char dtimsiz;                    /** size of DATE-TIME fields */
    unsigned char dtimfmt;                    /** format of DATE-TIME fields */
    unsigned char mode;                       /** 0 = general info request; */
                                              /**< 1 = get login string in usql */
    unsigned char fixrec;                     /** DBMS supports only fixed length records */
    unsigned char recoverh;                   /** # of overhead bytes / record */
    unsigned char link;                       /** dbms needs links to outer entities */
    unsigned char alrec;                      /** align (fill out) total record m* n-byte */
    unsigned char ali2;                       /** align 2-byte integer on n-bytes */
    unsigned char ali4;                       /** align 4-byte integer on n-bytes */
    unsigned char alfloat;                    /** align 4-byte float on n-bytes */
    unsigned char aldoub;                     /** align 8-byte double on n-bytes */
    unsigned char aldate;                     /** align DATE fields on n-bytes */
    unsigned char altime;                     /** align TIME fields on n-bytes */
    unsigned char ale9;                       /** align E9 data types on n-bytes */
    unsigned char alm6;                       /** align M6 data types on n-bytes */
    unsigned char optlock;                    /** optimistic locking wanted */
    unsigned char binpack;                    /** packing Binary fields (U,B) default [B] */
    unsigned char noconst;                    /** 1 = DBMS handles DELETE constraints; */
                                              /**< 2 = DBMS handles UPDATE constraints; */
                                              /**< 4 = No intermediate COMMIT on import; */
                                              /**< combinations allowed (0 ... 7) */
    unsigned char profil[2];                  /** profile ascii characters for any(*) */
                                              /**< and one character(%) */
    unsigned char autovarsiz;                 /** maximum size when 'S' and 'B' fields */
                                              /**< should get the varchar indicator */
    unsigned char boundv;                     /** allign varchar type fields */
    unsigned char filltv;                     /** fill trailing for varchar */
    unsigned char supzero;                    /** suppress leading zero's */
                                              /**< (make leading spaces for numeric) */
    unsigned char alseg;                      /** allign for segmented type fields */
    unsigned char lenseg;                     /** support and size of segmented indirection */
    unsigned char txtsearch;                  /** support of where on long fields */
    unsigned char where;                      /** support of additional where clause */
    unsigned char segctrl;                    /** write main rec before/after segs */
    unsigned char twophase;                   /** != 0 means support 2-phase commit */
    unsigned char tabname;                    /** 0 = File name; */
                                              /**< 1 = Table name (ignore usys expansion); */
                                              /**< 2 = driver will be requested for (overflow) name */
    short primlen;                            /** polyserver may alter this field only */
    unsigned char mapmode;                    /** for undefines: 1 = don't map; 2 = map to dbms */
    unsigned char incent;                     /** true if support for included entities */
    unsigned char like;                       /** generate LIKE and NOT_LIKE */
    unsigned char Conformance;                /** SQL conformance Level */
    unsigned char TableOpenLevel;
    unsigned char NewFloatingPointMapping;
    unsigned char SqlString;
    unsigned char SqlNumber;
    unsigned char SqlFloat;
    unsigned char SqlDate;
    unsigned char SqlTime;
    unsigned char SqlDateTime;
    unsigned char SqlBoolean;
    unsigned char NullTerm;                     /** null terminated character fields + delete trailing spaces */
    unsigned char TMCapable;                    /** Mark driver capable of TM control (0=no/1=yes) */
    unsigned char svtabid[130];
    unsigned long Options;                      /** room for several Options see OPTION_... */
    long (*SPEntry)(int Major, int Minor, void ** funcs);   /** driver entry point for Stored Procedures */
    unsigned char IdleSignalWanted;
    unsigned char drvCharset[32];               /** standard charset name for driver communication (in ASCII) */ /*@c21598*/
    unsigned char wideCharset[32];              /** standard charset name for Unicode communication (in ASCII) */ /*@c21598*/
    unsigned char wideCharAllocSize;            /** to adjust the size of the wide character (in bytes) */
    long dbmsmaxrecsiz;                         /** The maximum record size the DBMS supports.
                                                    If it is 0 then it defaults to recsiz; if recsiz is
                                                    also 0 then it is unlimited.
                                                    If it is -1 then it is also unlimited; recsiz can still be non-zero, it
                                                    will then specify the fixed length part of a record with variable length fields.
                                                 **/
};

/**
Field list
*/
struct ufldlst
{
    long ufmax;                               /** maximum size of entity/field data */
                                              /**< (null = variable length) */
    long uflen;                               /** actual size of entity/field data */
#ifdef u_msw64
    long high32;                              /** Solid writes 64 bits into uflen, a long is only 32 bits, so it is overwriting ufname!
                                                  So we need 32 extra bits for Solid to write the 2nd 32 bits into
                                                  (all zero's unless uflen is negative; SQL_NULL_DATA is -1) */
#endif
    short ufname;                             /** offset to entity/field in label string */

                                              /**< (null = variable length) */
    short ufvar;                              /** offset to 'variable length specs' */
                                              /**< if negative: "sub fields possible" */
    unsigned short ufbits;                    /** bit 0 true: field is possible pointer; */
                                              /**< bit 1 true: field not in LUV; */
                                              /**< bit 2 true: field is varchar; */
                                              /**< bit 3 is segmented string; */
                                              /**< bit 4 true: read by key; */
                                              /**< bit 5 true means field has binary id; */
                                              /**< bit 6 indicates mandatory field; */
                                              /**< bit 7 generate leading spaces for numeric */
                                              /**<       instead of leading zero's; */
                                              /**< bit 8 packing code A..; */
#define PROFILE_BIT (0x0200)                  /**< bit 10 profile is used in actual data; */
#define INPUT_BIT  (0x0400)                   /**< bit 10 INPUT parameter; */
#define OUTPUT_BIT (0x0800)                   /**< bit 11 OUTPUT parameter; */
#define MULVAL_BIT (0x1000)                   /**< bit 12 MULTI VALUE parameter; */
#define NULLTERM_BIT (0x2000)                 /**< bit 13 Null terminated field; */
#define UNSIGNED_PACKED_BIT (0x4000)          /**< bit 14 unsigned packed data */
#define UNICODE_STRING (0x8000)               /**< bit 15 Unicode-string parameter (@b29683); */
    int ufpos;                                /* offset to entity/field data in iobuf @b266403 */
    int ufocc;                                /* entity/field occurrence length @b266403 */


    short         udbfmt;                     /** Uniface database packing list code */
    short         ucsfmt;                     /** Uniface conceptual packing list code */
    unsigned char uftyp;                      /** data type: Raw, String, Numeric, Float, */
                                              /**< Date, Time, Edate-time */
    unsigned char ufpack;                     /** data packing (coded, 0 <= packing  < 100 */
    unsigned char ufscal;                     /** for numeric fields scaling, */
                                              /**< for date/time fields format */
    unsigned char uindex;                     /** if field belongs to one or more indexes, */
                                              /**< number of lowest index */
    unsigned char ulevel;                     /** hierarchic level, for fields/entity */
    unsigned char ufix;                       /** 0 = variable length (in variable part); */
                                              /**< 1 = fixed length (in variable part); */
                                              /**< 2 = fixed length (in fixed part) */
    unsigned char ufutyp;                     /** UNIFACE data type */
    long ufmaxchars;                          /** maximum number of chars of field data */ /*@c21598*/
    long uflenchars;                          /** actual number of chars of field data */  /*@c22150*/
    unsigned char uoverflowpart;              /** field indicator in overflow table. 1: SEGM, 2: DATA */ /* @b30857 */
};

/**
Where list
*/
struct uwhrlst
{
    short ufnr;                               /** entry nr in ufldlst. */
                                              /**< 0 = physical key; < 0 = index number */
    ptrdiff_t uwdat;                          /** offset to profile field data; @b27536: ptrdiff_t */
    short uwlen;                              /** actual length of profile field data */
    short wtype;
    unsigned char uqual;                      /** qualifier;  0 = like, */
                                              /**< 1 = less then, */
                                              /**< 2 = less equal, */
                                              /**< 3 = equal, */
                                              /**< 4 = greater equal, */
                                              /**< 5 = greater then */
    unsigned char uquals;                     /** additional qualifier; */
                                              /**< bit 0 = "not" */
                                              /**< bit 1 = "or" */
                                              /**< bit 2 = "optional" */
                                              /**< bit 3 = "null" */
    unsigned char wcalc[48];
    unsigned char uprof;                      /** Profiled search */
};

/**
If list for u_where
*/
struct uiflst
{
    ptrdiff_t data;                           /** offset to data @b27536: ptrdiff_t */
    short len;
    unsigned short pack;                      /** field packing (type / packing) */
    unsigned char  datyp;                     /** uniface data type */
    unsigned char  opr;                       /** operator */
    unsigned char  level;                     /** nesting level */
    unsigned char  prio;                      /** priority operator */
    unsigned char  iftype;
    unsigned char  ifopr;
    unsigned char  ifdata[48];                /** value of data */
    unsigned char  ifcalc[48];
};

/**
Index list
*/
struct uidxlst
{
    short ufnr;                               /** entry nr in ufldlst */
    unsigned char uidxnr;                     /** index number */
    unsigned char uidxsnr;                    /** index sequence number */
    unsigned char uidxuni;                    /** indicator unique */
    unsigned char uidxtest;                   /** Internal use */
};

/**
Order by list
*/
struct uordlst
{
    short ufnr;                               /** entry nr in ufldlst */
    short uorder;                             /** ordering type: 0 = ascending, 1 = descending */
};

#define FIRST_CALL 0x01
#define LAST_CALL  0x02

typedef enum _ForeignKeyRuleType
{
    RESTRICT,
    CASCADE,
    NULLIFY
} ForeignKeyRuleType;

typedef enum _KeyTypeType
{
    PRIMARY_KEY,
    CANDIDATE_KEY
} KeyTypeType;

typedef struct _RelationshipType
{
    unsigned char *RelationshipName;          /** Null terminated name of the */
                                              /**<  relationship (user defined). */
    unsigned char *OneConceptualSchemaName;   /** The name of the conceptual schema */
                                              /**<  in which the one entity resides. */
    unsigned char *ManyConceptualSchemaName;  /** The name of the conceptual schema */
                                              /**<  in which the many entity resides. */
    unsigned char *RelatedEntityName;         /** The name of the related entity, */
                                              /**<  as defined in the conceptual schema, */
                                              /**<  i.e. before entity assignment. */
    unsigned char *RelatedTableName;          /** The name of the related table after */
                                              /**<  entity assignment. May contain full */
                                              /**<  OS file name. The driver must parse */
                                              /**<  the name, like it does with */
                                              /**<  uctrl->uname in modes 0, 1 and 2. */
    int IsOverflow;                           /** Boolean value indication whether the */
                                              /**<  relationship is between a table and */
                                              /**<  it's overflow table. */
    int KeyNumber;                            /** UNIFACE index number of the referenced */
                                              /**<  key in the one-table. */
    KeyTypeType KeyType;                      /** Type of the referenced key in the */
                                              /**<  one-table. UNIFACE does not currently */
                                              /**<  support relationships on type */
                                              /**<  CANDIDATE_KEY. */
    int RIFields;                             /** The number of fields in the foreign */
                                              /**<  key and in the referenced key. */
    int *RIFieldNumberList;                   /** An array of 'RIFields' field numbers. */
                                              /**<  These identify the fields in the key */
                                              /**<  (primary, candidate or foreign) of the */
                                              /**<  current table in the relationship */
                                              /**<  (that is the table which is described */
                                              /**<  by the current control block). */
    unsigned char **RIFieldNameList;          /** An array of 'RIFields' pointers to */
                                              /**<  null-terminated field names. */
                                              /**<  These identify the fields in the key */
                                              /**<  (primary, candidate or foreign) of the */
                                              /**<  related table in the relationship */
                                              /**<  (that is the table which is not */
                                              /**<  described by the current control */
                                              /**<  block). */
    ForeignKeyRuleType OnDelete;              /** RESTRICT, CASCADE, NULLIFY. */
} RelationshipType;

typedef struct _RelationshipInfoType
{
    RelationshipType *OneRelationshipList;    /** An array of RelationshipType */
                                              /**<  structures describing the */
                                              /**<  relationships in which the */
                                              /**<  table described by the current */
                                              /**<  control block has the `one' */
                                              /**<  role. */
    int OneRelationships;                     /** Number of elements in the */
                                              /**<  OneRelationshipList. */
    RelationshipType *ManyRelationshipList;   /** An array of RelationshipType */
                                              /**<  structures describing the */
                                              /**<  relationships in which the */
                                              /**<  table described by the current */
                                              /**<  control block has the `many' */
                                              /**<  role. */
    int ManyRelationships;                    /** Number of elements in the */
                                              /**<  ManyRelationshipList. */
} RelationshipInfoType;


/****************************************************************************
 *
 * Public prototypes.
 *
 ****************************************************************************/
long ucnvint(UCTRL, USTRING *, USTRING *, int);
long ucnvext(UCTRL, USTRING *, USTRING *, int);
void usumhit(struct uctrl *);
void usumfld(UCTRL, USTRING *, short , short);
short udcurscnt(UCTRL, short, short);
short udfilcnt(UCTRL, short, short);
short udpathset(UCTRL, short, short);
short udgetasn(UCTRL, USTRING *, USTRING *, short);
short ugethit(UCTRL, USTRING *, USTRING *);
void uaddsql(UCTRL, USTRING *);
void uaddhit(UCTRL, USTRING *, short, USTRING *, short, USTRING *, short);
void uaddrec(UCTRL, USTRING *, short, USTRING *, short, USTRING *, short);
short uready(UCTRL);
short uhitchk(UCTRL, short, USTRING *);
void unullify(UCTRL, int);
void ubldprm(UCTRL, short);
void ubldprim(UCTRL, USTRING *);
short uprimpos(UCTRL, short);
short ufgetp(UCTRL, USTRING *, USTRING *, short);
void uputblob(UCTRL, int, USTRING *, long, int);
long ugetblob(UCTRL, int, USTRING *, long, int);
short udbconv(UCTRL, USTRING *, USTRING *, short, struct ufldlst *, short);
short uconvdb(UCTRL, USTRING *, USTRING *, short, struct ufldlst *, short);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* UNIDBM_H */
