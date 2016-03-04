/* @(#)CONT_ID %fv: owi.h-79:incl:2 % %dc: Tue Jul 14 14:13:32 2015 % (#)@ */

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
/***********************************************************************
date   refnum    version who description
050316 b26235    9.1.01  mab Meta info functionality extended.
050405 c21636    910102  jdk File dump and other missing bits and pieces
050526 c21961    910102  mbg Extend the capabilities with a 'property' request (for the IDE)
060314 c23137    910102  hkr Grid Widget Unicode enabled.
060615 c23683    910102  jdk Colorlist widget show the selection correct.
060829 c23528    910102  hkr Alignment of labels not picked up by Grid Widget
060919 c24774    910102  ete Removed obsolete OSYN_SPECIAL; added new OSYN_AUTOIME
061017 c25034    910102  jdk RichEditbox: <GOLD>G always restored font to Courier New
061129 c25293    N101    jya $paintedfieldproperties Zorder implementation
070809 b27256    O101    jya improve drag&drop control in tree widget (part 2).
071231 b27487    O103    jya Grid: Memory leak when restarting form component
080701 c26705    9.ajax  tsk RIA: Focus problems with NVU and HTML wizard
091214 c27881    940101  mbg Right mouse popup needed on FlowChartX
100127 b28484    O310    fd  NDI field should not show "Caps Locked" warning if it is not editable.
101117 b28948    9.5.01  jdk Configurable highlight color for $curocc_video("hlt").
                             Used asn setting $curocc_video_hlt = backcolor=<color> forecolor=<color>
120420 c29201    960101  jya $fieldhandle implementation, first phase
121020 b29795    960101  tsk  tab page widgets are destroyed if their parent is closed
121018 b29796    X101    jya Grid: Uniface attempting to read missing logical widget definitions repeatedly.
130108 c29611    960201  ago Ability to have 0px margin on attach properties
130403 b30041    MX01    sse Pass proc param block to widgetoperation
130723 b30333    MX02    jdk Inheritcolors:Load both foreground and background colors in one go.
140627 c30170    MX05    jxa MSAA support for the GUI objects general functions, editbox,and windows commandbutton.
141231 b30625    X602    jya Extended trigger Resized is not fired properly.
150714 b30973    X702    jya P_X11 print result editbox truncated on UNIX.
date   refnum    version who description
***********************************************************************/

#ifndef OWI_H
#define OWI_H

#include "unityp.h"

#ifndef WMLINK_typedef
# define WMLINK_typedef
  typedef struct _widinst *WMLINK; /* also in ucctype.h */
#endif

/***************************************************************************/
/* DEPENDENCIES                                                            */
/***************************************************************************/

/* The following types must be defined prior to including this file:       */

/* UCOLOR     platform dependent color (usually RGB encoded)               */
/* HPARENT    platform dependent (parent) window handle                    */
/* HWIDGET    platform dependent OWI widget handle (usually void*)         */
/* HCLIENT    platform dependent client process id (optional)              */
/* HANCHOR    platform dependent global context handle (optional)          */

/***************************************************************************/
/* CONSTANTS                                                               */
/***************************************************************************/

/* Data type IDs */

#define OTYP_STR                 1     /* null terminated string (conceptual format) */
#define OTYP_NUMBER              2     /* signed long integer */
#define OTYP_FLOAT               3     /* floating point */
#define OTYP_DATE                4     /* date (days since jan 1, 1970) */
#define OTYP_TIME                5     /* time (fractional days) */
#define OTYP_DATIM               6     /* date-time */
#define OTYP_RAW                 7     /* binary */
#define OTYP_BOOL                8     /* boolean */
#define OTYP_LDATE               9     /* linear date */
#define OTYP_LTIME               10    /* linear time */
#define OTYP_LDATIM              11    /* linear date-time */
#define OTYP_IMAGE               12    /* image (@filename, ^glyph or #blob) */
#define OTYP_NULL                13    /* null value */

/* Data option (must be or-ed in with a proper OTYP_*) */

#define OTYP_NATIVE              32    /* (all types) usm handle to data in native format */

/* Attribute IDs */
                                       /* TYPE       UNIT      SUMMARY */
#define OATT_ORIGIN              1     /* 2 shorts   pixels    upper left corner */
#define OATT_SIZE                2     /* 2 shorts   pixels    total widget size */
#define OATT_FOREGND             3     /* color      RGB       foreground color */
#define OATT_BACKGND             4     /* color      RGB       background color */
#define OATT_READONLY            5     /* long       Boolean   value is not editable */
#define OATT_NOECHO              6     /* long       Boolean   no input echo (password) */
#define OATT_RTL                 7     /* long       Boolean   right-to-left text - NOT USED */
#define OATT_ENABLED             8     /* long       Boolean   widget is enabled for input */
#define OATT_VISIBLE             9     /* long       Boolean   widget is visible */
#define OATT_FONT                10    /* string     name      font to use for widget - NOT USED */
#define OATT_DATATYPE            11    /* long       OTYP_*    datatype of field */
#define OATT_XPARENT             12    /* color      RGB       transparent color */
#define OATT_STATE               13    /* long       any       widget state info */
#define OATT_PROTOTYPE           14    /* long       Boolean   prototype mode */
#define OATT_FILLRECT            15    /* long       Boolean   Widget fills complete area as defined in gfp */
#define OATT_NEWPARENT           16    /* long       HWND      Windowhandle of the new parent */
#define OATT_COLUMNS             17    /* long       any       number off columns in entity widget @prxxx */
#define OATT_COLUMN              18    /* long       any       column nr in entity widget @prxxx */
#define OATT_HIGHLIGHT           19    /* long       Boolean   Highlight state. -- @pr25 */
#define OATT_ZORDER              20    /* long       HWND      HWND_TOP or HWND_BOTTOM -- @c25293 */
#define OATT_MAP                 21    /* long       Boolean   message tells widget when kernel maps/unmaps widget*/
#define OATT_COLORS              22    /* void *     OWIATT_COLORS structure */
#define OATT_LABEL               1000  /* label specific attributes start here */
#define OATT_GFP                 2000  /* form painter specific attributes start here */
#define OATT_PLATFORM            3000  /* platform specific attributes start here */
#define OATT_PRINT               3500  /* print attributes start here */
#define OATT_USER                4000  /* user defined attributes start here */

#define OATT_LABELFONT           1001  /* string     name      font to use for label - NOT USED */
#define OATT_LORIGIN             1002  /* 2 shorts   pixels    origin of label */
#define OATT_LSIZE               1003  /* 2 shorts   pixels    size of label */
#define OATT_LHALIGN             1004  /* long       (*)       horizontal alignment */
#define OATT_LVALIGN             1005  /* long       (*)       vertical alignment */
#define OATT_LFOREGND            1006  /* color      RGB       foreground color */
#define OATT_LBACKGND            1007  /* color      RGB       background color */
#define OATT_LXPARENT            1008  /* color      RGB       transparent color */
#define OATT_LHILITE             1009  /* long       Boolean   highlight label (focus) */
#define OATT_LTRANSPARENCY       1010  /* long       Boolean   Transparent or opaque. -- @pr28 */

#define OATT_GFPMODE          OATT_GFP /* long       Boolean   Widget created by Graphical Form Painter */

#define OATT_PRINTMODE           OATT_PRINT        /* long  Boolean   Widget created by print driver */
#define OATT_PRINTDEPTH         (OATT_PRINT + 1)   /* long  pixels    Height required to print complete widget */
#define OATT_PRINTMINDEPTH      (OATT_PRINT + 2)   /* long  pixels    Mimimal height the widget can print */

/* Attribute values */

#define OATT_LHALIGN_LEFT        0     /* left aligned */
#define OATT_LHALIGN_CENTER      1     /* centered */
#define OATT_LHALIGN_RIGHT       2     /* right aligned */

#define OATT_LVALIGN_TOP         0     /* top aligned */
#define OATT_LVALIGN_CENTER      1     /* centered */
#define OATT_LVALIGN_BOTTOM      2     /* bottom aligned */

#define OATT_LTNCY_DEFAULT       0     /* Transparency default. @pr28 */
#define OATT_LTNCY_ON            1     /* Transparent.          @pr28 */
#define OATT_LTNCY_OFF           2     /* Opaque.               @pr28 */

/* Capability IDs */
                                       /* TYPE       UNIT      SUMMARY */
#define OCAP_FOCUS               1     /* long       Boolean   widget can accept focus */
#define OCAP_SHOWFOCUS           2     /* long       Boolean   widget can show it has focus */
#define OCAP_MINSIZE             3     /* 2 shorts   pixels    minimum widget size */
#define OCAP_MAXSIZE             4     /* 2 shorts   pixels    maximum widget size */
#define OCAP_DEFSIZE             5     /* 2 shorts   pixels    default widget size */

#define OCAP_EXTENDEDTRIGGERS_LIST  6  /* string     list      list of extended triggers raised by widget */
#define OCAP_EXTENDEDTRIGGERS_TEXT  7  /* string     text      complete extended trigger text for widget */

#define OCAP_IS_CONTAINER        8     /** Is the widget able to contain forms (e.g. tab or form container) */
#define OCAP_IS_NOTEBOOK         9     /** Is the widget a tab/notebook/.... widget */

#define OCAP_LABELPOS            1001  /* long       (*)       supported relative label positions */

#define OCAP_GFPICON             2001  /* long                 bitmap for form painter */
#define OCAP_GFPFORM             2002  /* string     name      form to use for widget properties */
#define OCAP_GFPALLOW            2003  /* long       Boolean   allow widget to be painted */
#define OCAP_GFPXICON            2004  /* long                 transparent bitmap for formpainter. -- @pr24 */

#define OCAP_DESCRIBE            2100  /* string     text      description of a widget like: properties, name...ect. (called by U_ICI) */

#define OCAP_LABEL               1000  /* label specific capabilities start here */
#define OCAP_GFP                 2000  /* form painter specific capabilities start here */
#define OCAP_PLATFORM            3000  /* platform specific capabilities start here */
#define OCAP_PRINT               3500  /* print capabilities start here */
#define OCAP_ZOOMPANEL           3505  /* @pr17 Load zoom panel string. */
#define OCAP_USER                4000  /* user defined capabilities start here */


/* Capability values */

#define OCAP_LABELPOS_TOP        1     /* labels directly above widget supported */
#define OCAP_LABELPOS_BOTTOM     2     /* labels directly below widget supported */
#define OCAP_LABELPOS_LEFT       4     /* labels directly to the left of widget supported */
#define OCAP_LABELPOS_RIGHT      8     /* labels directly to the right of widget supported */
#define OCAP_LABELPOS_ELSEWHERE  16    /* labels not adjacent to widget supported */
#define OCAP_LABELPOS_ANYWHERE   31    /* all labels supported */

/* Widget requests */

#define OREQ_OPEN                1     /* open class */
#define OREQ_CLOSE               2     /* close class */
#define OREQ_CREATE              3     /* create instance */
#define OREQ_DESTROY             4     /* destroy instance */
#define OREQ_SETATTR             5     /* set instance attributes */
#define OREQ_GETATTR             6     /* get instance attributes */
#define OREQ_COMMAND             7     /* command to instance */
#define OREQ_GETCAPS             8     /* get capabilities */
#define OREQ_PRINT               9     /* print (part of) the widget */
#define OREQ_DRAGOVER            10    /* get drag over info from complex widget -- @pr9 */
#define OREQ_SELECTDROPTARGET    11    /* select (hilite) last dragged-over drop target-- @pr10 */
#define OREQ_CREATEFIELD         12    /* created field in container widget @prxxx */
#define OREQ_DESTROYFIELD        13    /* destroy field in container widget @prxxx *//* @27487 */
#define OREQ_SETFIELDATTR        14    /* Sets the field atrr in a container widget*/
#define OREQ_FIELDCOMMAND        15    /* command to field instance in container widget */
#define OREQ_GETFIELDATTR        16
#define OREQ_CALLWIDOPER         17    /* call widget operation @c29201 */
#define OREQ_BEFOREDESTROY       18    /**< before destruction of widget */ /* @b29795 */

#define OREQ_LABEL               1000  /* label specific requests start here */
#define OREQ_GFP                 2000  /* form painter specific requests start here */
#define OREQ_PLATFORM            3000  /* platform specific requests start here */
#define OREQ_USER                4000  /* user defined requests start here */

/* Widget commands */

#define OCMD_NEWDATA             1     /* new data was put, update presentation */
#define OCMD_NEWVALREP           2     /* new valrep was set, update presentation */
#define OCMD_PUTDATA             3     /* put modified data back */
#define OCMD_TAKEFOCUS           4     /* widget to grab physical input focus */
#define OCMD_LOSEFOCUS           5     /* widget loses logical input focus */
#define OCMD_SETUPCHANGE         6     /* some setup parameters have changed */
#define OCMD_FUNCTION            7     /* execute Uniface function */
#define OCMD_SMODACK             8     /* start Mod succeeded */
#define OCMD_NEWPROPS            9     /* new properties were set */
#define OCMD_GETFOCUS            10    /* widget receives logical input focus */
#define OCMD_LABELCLICKED        11    /* associated label received click */
#define OCMD_SHOWACCESSKEY       12    /* form scope access key enabled */
#define OCMD_HIDEACCESSKEY       13    /* form scope access key hidden */
#define OCMD_DOACCESSKEY         14    /* access key was pressed */
#define OCMD_ISWIDGETKEY         15    /* Handle keyboard input @pr5 */
#define OCMD_CLEARFIELD          16    /* @pr?? */
#define OCMD_CLEARENTITY         17    /* @pr21 */
#define ECMD_STARTUPDATE      18    /* Start blockupdate Entity Level Widgets. -- @pr27 */
#define ECMD_ENDUPDATE        19    /* End blockupdate Entity Level Widgets. -- @pr27 */

#define ECMD_GETEWIAREANAME            20      /* @pr31 hkr_QArun start */
#define ECMD_GETFIELDATPOINT           21
#define ECMD_GETFIELDSCOUNTS           22
#define ECMD_GETOCCURRENCESCOUNT       23
#define ECMD_GETFIELDRECT              24
#define ECMD_GETFIELDLINK              25
#define ECMD_ISFIELDINVIEW             26
#define ECMD_BRINGFIELDINVIEW          27
#define ECMD_ISFIELDVISIBLE            28
#define ECMD_ISFIELDENABLED            29
#define ECMD_SETFOCUSONFIELD           30
#define ECMD_GETEDITCONTROLATFOCUS     31       /* @pr31 hkr_QArun end */
#define ECMD_GETROWHEADERINFO          32       /* @pr35 QArun extension start */
#define ECMD_GETCOLUMNHEADERINFO       33
#define ECMD_GETCORNERBUTTONINFO       34       /* @pr35 end */
#define OCMD_FIELDLEFT                 35       /* @pr40 command for field left */
#define OCMD_CHECKFOCUS                36       /**< Return TRUE if no focus change of parent needed */ /* @c26705 */
#define ECMD_COLUMN                    37       /* @columns - Column info has been changed by the 4GL*/
#define OCMD_ENDUPDATE                 38       /* @b30625 */
#define OCMD_NEWLABEL            1001  /* label changed */

#define OCMD_LABEL               1000  /* label specific commands start here */
#define OCMD_GFP                 2000  /* form painter specific commands start here */
#define OCMD_PLATFORM            3000  /* platform specific commands start here */
#define OCMD_USER                4000  /* user defined commands start here */

/* Notifications (oNotify) */

#define ONTF_REQUESTFOCUS          1     /* user attempts to set focus to the widget */
#define ONTF_STARTMOD              2     /* the value of the widget is about to change */
#define ONTF_VALUECHANGE           3     /* the value of the widget has changed */
#define ONTF_KEY                   4     /* a keystroke was received by the widget */
#define ONTF_FUNCTION              5     /* queue a function for execution by the client */
#define ONTF_CONTAINERVALUECHANGED 6     /* notebook value has changed: page to be updated */
#define ONTF_DETAIL                7     /* request to execute procs from <detail> trigger */
#define ONTF_CONTAINERDESTROYED    8     /* notebook will be destroyed: release children */

#define ONTF_LREQUESTFOCUS       1001  /* user attempts to set focus to the label */

#define ONTF_LABEL               1000  /* label specific notifications start here */
#define ONTF_GFP                 2000  /* form painter specific notifications start here */
#define ONTF_PLATFORM            3000  /* platform specific notifications start here */
#define ONTF_USER                4000  /* user defined notifications start here */

/* Notification parameter value (oNotify's iParam) */                /* @pr8 begin */

/* _VALUECHANGE: Note that a ONTF_PARAM_TRIG_xxx must be
**               combined with a ONTF_PARAM_DO_xxx
*/
#define ONTF_PARAM_TRIG_SMOD    (0x0000) /* Fire only StartMod, if neccesary                   */
#define ONTF_PARAM_TRIG_VCHG    (0x0001) /* Fire StartMod (if neccesary) and ValueChange       */
#define ONTF_PARAM_DO_SET       (0x0000) /* Overwrite any outstanding oNotify request (if any) */
#define ONTF_PARAM_DO_QUEUE     (0x0002) /* Queue this oNotify request on the Uniface queue    */
                                                                     /* @pr8 end */
/* Queries (oQuery) */

#define OMET_XCELL               1     /* width of a character cell in pixels */
#define OMET_YCELL               2     /* height of a character cell in pixels */
#define OMET_XCHAR               3     /* width of a font character in pixels */
#define OMET_YCHAR               4     /* height of a font character in pixels */
#define OMET_ASCENT              5     /* number of character pixels above baseline */
#define OMET_FOREGND             6     /* foreground color from color/video index */
#define OMET_BACKGND             7     /* background color from color/video index */
#define OMET_BASELINE            8     /* distance from top of charactercell to baseline */
#define OMET_POINTSIZE           9     /* @c25034 return pointsize */
#ifdef u_wce
# define OMET_XSCREEN            10    /* width of the screen in pixels */
# define OMET_YSCREEN            11    /* height of the screen in pixels */
# define OMET_APPL_WND           12    /* Window of the application shell */
#endif
#define OLAY_ALIGNMENT           101   /* layout alignment */
#define OLAY_DIRECTION           102   /* direction LTR=0 or RTL=1 @pr4*/
#define OLAY_DIRECTION_RTL       0x0001/* @pr4*/

#define OSYN_AUTOIME             201   /* syntax auto IME (YIME/NIME) */
#define OSYN_MINLENGTH           202   /* syntax min length (LEN) */
#define OSYN_MAXLENGTH           203   /* syntax max length (LEN) */
#define OSYN_UPPERCASE           204   /* syntax uppercase (UPC) */
#define OSYN_LOWERCASE           205   /* syntax lowercase (LOW) */
#define OSYN_ONELINE             206   /* syntax one line (NCR/YCR) */
#define OSYN_MINREP              207   /* syntax minimum subfields (REP) */
#define OSYN_MAXREP              208   /* syntax maximum subfields (REP) */
#define OSYN_IMAGETYPE           209   /* image subtype (0, '@', '#' or '^') */
#define OSYN_AUTOJUMP            210   /* syntax autojump (true,false) @pr18*/
#define OSYN_NOECHO              211   /* syntax NDI nodisplay (true , false ), @pr30 */
#define OSYN_HID                 212   /* syntax HID (NPR, NDI, and NED) -- @pr38 */
#define OSYN_NED                 213   /* syntax NED non-editable (@b28484) */

#define OQRY_BUSY                301   /* is app busy? */
#define OQRY_FOCUS               302   /* does widget have focus? */
#define OQRY_FONTMASK            303   /* mask to clear invalid font bits */
#define OQRY_DBCS_FONT           304   /* first DBCS font */
#define OQRY_DBCS_BASE           305   /* first DBCS character */
#define OQRY_DBCS_CSET           306   /* DBCS characterset id */
#define OQRY_RTL                 307   /* is the default widget style right-to-left? (note :will become obsolete in 7.2) */
#define OQRY_TESTMODE            308   /* @pr26 is the form in testmode */
#define OQRY_DIMMED              309   /* @pr27 is the widget enabled (grayed) or not. */
#define EQRY_CUROCC              310   /* @pr29 If iftab is not in the current occ. it returns an the first promptable iftab in the current occ*/
#define EQRY_WIDFROMLINK         311   /* @pr29 Return OWI widget handle belonging to the wmlink*/
#define OQRY_PROCSTATUS          312   /* Get content of funcchar -- @b26231 */

#define OCHR_BOILER              401   /* @pr34 Query function for field characteristics. */

#define OQRY_LABEL               1000  /* label specific queries start here */
#define OQRY_GFP                 2000  /* form painter specific queries start here */
#define OQRY_PLATFORM            3000  /* platform specific queries start here */
#define OQRY_USER                4000  /* user defined queries start here */

/* String conversion options (oStrConv) */

#define OCNV_INT2EXT             1     /* convert from internal to external format */
#define OCNV_EXT2INT             2     /* convert from external to internal format */
#define OCNV_XSRECOG             4     /* recognize access key mnemonics (%) in input */
#define OCNV_XSXLATE             8     /* translate access key mnemonics to output */
#define OCNV_PROFILE             16    /* recognize/generate profile characters */
#define OCNV_FULLSET             32    /* do not strip styles and nonrepresentable characters */
#define OCNV_XSESCAPE            64    /* escape access key mnemonics & escapes in output */
#define OCNV_UTF16               128   /* external character for convertors is UNICODE - UTF16 */
#define OCNV_UTF8                256   /* external character for convertors is UNICODE - UTF8 */
#define OCNV_UTF                 OCNV_UTF16 | OCNV_UTF8   /* external character for convertors is UNICODE - UTF8 */
#define OCNV_UNICODE             OCNV_UTF16   /* If Unicode: external character for convertors is UTF16  */
#define OCNV_CHARSET             512   /* @b30973 external character for convertors is a specified charset */

/* Compatible old style oStrConv options */

#define OCNV_MNEMOUT             OCNV_XSRECOG
#define OCNV_MNEMIN              OCNV_XSXLATE      /* implies OCNV_RECOG and OCNV_XSESCAPE */

/* Character styles (oChrConv) */

#define OFNT_UNDERLINE           1     /* character is underlined */
#define OFNT_ITALIC              2     /* character is italic */
#define OFNT_BOLD                4     /* character is bold */
#define OFNT_STRIKEOUT           8     /* character is struck out - NOT USED */

#define OFNT_PRINTER             16    /* create a font for the printer not for the screen */

/* Attach options (oAttach) */

#define OATTACH_T                1     /* attach top of widget to top of form */
#define OATTACH_L                2     /* attach left */
#define OATTACH_B                4     /* attach bottom */
#define OATTACH_R                8     /* attach right */
#define OATTACH_TT               0     /* attach top    relative to top    */
#define OATTACH_TB              16     /* attach top    relative to bottom */
#define OATTACH_LL               0     /* attach left   relative to left   */
#define OATTACH_LR              32     /* attach left   relative to right  */
#define OATTACH_BT               0     /* attach bottom relative to top    */
#define OATTACH_BB              64     /* attach bottom relative to bottom */
#define OATTACH_RL               0     /* attach right  relative to right  */
#define OATTACH_RR             128     /* attach right  relative to left   */
#define OATTACH_CUSTOM         256     /* @c29611: attach using the custom margin   */
#define OATTACH_HMOVE       (OATTACH_LR | OATTACH_RR)
#define OATTACH_HSIZE       (OATTACH_LL | OATTACH_RR)
#define OATTACH_H           (OATTACH_LL | OATTACH_LR | OATTACH_RL | OATTACH_RR)
#define OATTACH_VMOVE       (OATTACH_TB | OATTACH_BB)
#define OATTACH_VSIZE       (OATTACH_BB | OATTACH_TT)
#define OATTACH_V           (OATTACH_TT | OATTACH_TB | OATTACH_BT | OATTACH_BB)

/* Message options (oMessage) */

#define OMSG_NOBEEP              1     /* silent message */
#define OMSG_HINT                2     /* do not log message */
#define OMSG_INFO                4     /* confirmed message with Info icon */
#define OMSG_WARNING             8     /* confirmed message with Warning icon */
#define OMSG_ERROR               16    /* confirmed message with Error icon */

/* Access key scopes (oxsAddKey,oxsRemoveKey) */

#define OXSK_FIELD               1     /* field scope access key */
#define OXSK_FORM                2     /* form scope access key */

/*
** @c21636 oFileOpen modes
*/
/* Creation: */
#define OFILE_CREATE_BIN        'G' /* 'G':Create binary form file              */
#define OFILE_CREATE_PRINT      'P' /* 'P':Open print file                      */
#define OFILE_CREATE_BIN_RANDOM 'W' /* 'W':Create binary file for random access */
#define OFILE_CREATE_ASCII      'C' /* 'C':Create default C ascii file          */
#define OFILE_CREATE_UTF8       'D' /* 'D':Create UTF8 file                     */
#define OFILE_CREATE_UTF16      'E' /* 'E':Create UTF16 file                    */
#define OFILE_CREATE_UTF32      'Q' /* 'Q':Create UTF32 file                    */
/* Read:     */
#define OFILE_READ_BIN_RANDOM   'R' /* 'R':Open binary file for random read access*/
#define OFILE_READ_ASCII        'I' /* 'I':Open ascii file for read access        */
#define OFILE_READ_UTF8         'J' /* 'J':Open UTF8 file for read access         */
#define OFILE_READ_UTF16        'K' /* 'K':Open UTF16 file for read access        */
#define OFILE_READ_UTF32        'L' /* 'L':Open UTF32 file for read access        */

/* Object types (oGetLink) */

#define OOBJ_FIELD               0     /* field widget */
#define OOBJ_LABEL               1     /* label widget */

/* Uniface functions */

#define FN(a,b)                  ((a==127) ? (0-b) : (-1000 -b)) /* FC(b) or CC(b) -- @pr39 */

#define OKEY_RETSEQ              FN(127, 3)
#define OKEY_RETRIEVE            FN(127, 5)
#define OKEY_ERASE               FN(127, 8)
#define OKEY_ACCEPT              FN(127, 9)
#define OKEY_QUIT                FN(127, 10)
#define OKEY_STORE               FN(127, 11)
#define OKEY_CLEAR               FN(127, 12)
#define OKEY_CURSOR_UP           FN(127, 16)
#define OKEY_CURSOR_DOWN         FN(127, 17)
#define OKEY_CURSOR_LEFT         FN(127, 18)
#define OKEY_CURSOR_RIGHT        FN(127, 19)
#define OKEY_TOP_OF_FORM         FN(127, 20)
#define OKEY_BOTTOM_OF_FORM      FN(127, 21)
#define OKEY_HOME                FN(127, 22)
#define OKEY_BOTTOM              FN(127, 23)
#define OKEY_CURSOR_FAST_UP      FN(127, 25)
#define OKEY_CURSOR_FAST_DOWN    FN(127, 26)
#define OKEY_CURSOR_FAST_LEFT    FN(127, 27)
#define OKEY_CURSOR_FAST_RIGHT   FN(127, 28)
#define OKEY_FIRST_OCC           FN(127, 37)
#define OKEY_LAST_OCC            FN(127, 38)
#define OKEY_NEXT_OCC            FN(127, 39)
#define OKEY_PREV_OCC            FN(127, 40)
#define OKEY_INS_OCC             FN(127, 43)
#define OKEY_ADD_OCC             FN(127, 44)
#define OKEY_REM_OCC             FN(127, 45)
#define OKEY_NEXT_FIELD          FN(127, 46)
#define OKEY_PREV_FIELD          FN(127, 47)
#define OKEY_PREV_GROUP          FN(127, 48)
#define OKEY_NEXT_GROUP          FN(127, 49)
#define OKEY_REFRESH             FN(127, 67)
#define OKEY_EDIT_TFO            FN(127, 71)
#define OKEY_KEY_HELP            FN(127, 72)
#define OKEY_VIEW                FN(127, 73)
#define OKEY_FDETAIL             FN(127, 76)
#define OKEY_ATTRIBUTE           FN(127, 78)
#define OKEY_RULER               FN(127, 81)
#define OKEY_PULLDOWN            FN(127, 86)
#define OKEY_PROFILE             FN(127, 87)
#define OKEY_COMPOSE             FN(127, 88)
#define OKEY_FRAME               FN(127, 89)
#define OKEY_HELP                FN(127, 92)
#define OKEY_MESSAGE             FN(127, 93)
#define OKEY_DETAIL              FN(127, 94)
#define OKEY_ZOOM                FN(127, 95)
#define OKEY_QUICK_ZOOM          FN(127, 96)
#define OKEY_SQL                 FN(127, 97)
#define OKEY_PRINT               FN(127, 98)
#define OKEY_PRINT_ATTS          FN(127, 99)
#define OKEY_SWITCH              FN(127, 100)
#define OKEY_MENU                FN(127, 101)
#define OKEY_LAST_TEXT           FN(127, 128)
#define OKEY_FIRST_TEXT          FN(127, 129)
#define OKEY_NEXT_LINE           FN(127, 136)
#define OKEY_PREV_LINE           FN(127, 137)
#define OKEY_NEXT_WORD           FN(127, 140)
#define OKEY_PREV_WORD           FN(127, 141)
#define OKEY_NEXT_CHAR           FN(127, 142)
#define OKEY_PREV_CHAR           FN(127, 143)
#define OKEY_INSOVR              FN(127, 146)
#define OKEY_BOLD                FN(127, 147)
#define OKEY_ITALIC              FN(127, 148)
#define OKEY_UNDERLINE           FN(127, 149)
#define OKEY_FIND_TEXT           FN(127, 150)
#define OKEY_FONT                FN(127, 151)
#define OKEY_FFIND               FN(127, 154)
#define OKEY_BFIND               FN(127, 155)
#define OKEY_SAVE_FILE           FN(127, 158)
#define OKEY_MOVE                FN(127, 160)
#define OKEY_PREV_TEXT           FN(127, 162)
#define OKEY_NEXT_TEXT           FN(127, 163)
#define OKEY_MOV_FILE            FN(127, 165)
#define OKEY_REM_FIELD           FN(127, 166)
#define OKEY_REM_LINE            FN(127, 167)
#define OKEY_REM_WORD            FN(127, 169)
#define OKEY_REM_CHAR            FN(127, 172)
#define OKEY_RUB_CHAR            FN(127, 173)
#define OKEY_REM_SEL_CHAR        FN(127, 174)
#define OKEY_RUB_SEL_CHAR        FN(127, 175)
#define OKEY_INS_TEXT            FN(127, 177)
#define OKEY_SAVE                FN(127, 179)
#define OKEY_INS_FILE            FN(127, 180)
#define OKEY_INS_FIELD           FN(127, 181)
#define OKEY_INS_LINE            FN(127, 182)
#define OKEY_INS_WORD            FN(127, 183)
#define OKEY_INS_CHAR            FN(127, 184)
#define OKEY_BEGIN_LINE          FN(127, 188)
#define OKEY_END_LINE            FN(127, 189)
#define OKEY_QSELECT             FN(127, 190)
#define OKEY_QUNDO_SELECT        FN(127, 191)
#define OKEY_REM_FILE            FN(127, 192)
#define OKEY_SELECT              FN(127, 193)
#define OKEY_REM_SELECT          FN(127, 194)
#define OKEY_INS_SELECT          FN(127, 195)
#define OKEY_UNDO_SELECT         FN(127, 196)
#define OKEY_PAGE_UP             FN(127, 197)
#define OKEY_PAGE_DOWN           FN(127, 198)
#define OKEY_UNDO                FN(127, 201)                        /*@pr14*/
#define OKEY_REDO                FN(127, 202)                        /*@pr14*/
#define OKEY_FIND_REPLACE        FN(127, 203)                        /*@pr16*/

/* Access keys. */          /* @pr32 hkr_EXTGRID_1 start */
#define OBTN_SUBMIT   0x0D
#define OBTN_CANCEL   0x1B  /* @pr32 hkr_EXTGRID_1 end */


/* @b26235 start */

/* Object types (labels, fields etc). */
#define OBJTYP_NONE          0
#define OBJTYP_FIELD         1
#define OBJTYP_LABEL         2

/* @b26235 end */


/* @c27881 Context menu definitions for FlowChartX. */
#define UM_CONTEXTMENU_FCX WM_USER+1550

/***************************************************************************/
/* DATA TYPES                                                              */
/***************************************************************************/

/* Uniface data types */

/* Attributes and capabilities */

typedef union _owiattv                 /* attribute value variant */
{
   long    i;                          /* as long int */
   short   s[2];                       /* as two shorts */
   char   *psz;                        /* as string */
   UCOLOR  clr;                        /* as color (RGB) */
   void   *pv;
} OWIATTV, *POWIATTV;

typedef struct _owiattr                /* attribute list entry */
{
   int      id;                        /* attribute ID */
   OWIATTV  d;                         /* attribute value */
} OWIATTR, *POWIATTR;

typedef struct _owicmd_egetewiareaname  /* @pr31 hkr_QArun start */
{
   int      areaId;         /* in   : the area Id */
   char     *pStr;          /* out  : the area name */

} OWICMD_EGETEWIAREANAME, *POWICMD_EGETEWIAREANAME;

typedef struct _owicmd_egetfieldatpoint
{
   int      x;              /* in   : x coordinate of the mouse inside the active area */
   int      y;              /* in   : y coordinate of the mouse inside the active area */
   int      *pFiN;          /* out  : the Field Number */
   long     *pOcN;          /* out  : the Occurrence Number */

} OWICMD_EGETFIELDATPOINT, *POWICMD_EGETFIELDATPOINT;

typedef struct _owicmd_egetfieldscount
{
   int      *pFiCounts;     /* out  : Fields Counts */
} OWICMD_EGETFIELDSCOUNT, *POWICMD_EGETFIELDSCOUNT;

typedef struct _owicmd_egetoccurrencescount
{
   long     *pOcCounts;     /* out  : Fields Counts */
} OWICMD_EGETOCCURRENCESCOUNT, *POWICMD_EGETOCCURRENCESCOUNT;

typedef struct _owicmd_egetfieldrect
{
   int      FiN;            /* in   : Field Number */
   long     OcN;            /* in   : Occurrence Number */
   void     *pRect;         /* out  : Field RECT */
} OWICMD_EGETFIELDRECT, *POWICMD_EGETFIELDRECT;

typedef struct _owicmd_egetfieldlink
{
    int     FiN;            /* in   : Field Number */
    long    OcN;            /* in   : Occurrence Number */
    WMLINK  *pfwmlink;      /* out  : the WMLINK of the Field */
} OWICMD_EGETFIELDLINK, *POWICMD_EGETFIELDLINK;

typedef struct _owicmd_eisfieldinview
{
    UBOOL    *pinview;         /* out  : true if the field in view */
} OWICMD_EISFIELDINVIEW, *POWICMD_EISFIELDINVIEW;

typedef struct _owicmd_eisfieldvisible
{
    UBOOL    *pvisible;        /* out  : true if the field is visible */
} OWICMD_EISFIELDVISIBLE, *POWICMD_EISFIELDVISIBLE;

typedef struct _owicmd_eisfieldenabled
{
    UBOOL    *penabled;        /* out  : true if the field is enabled */
} OWICMD_EISFIELDENABLED, *POWICMD_EISFIELDENABLED;

typedef struct _owicmd_esetfocusonfield
{
    UBOOL    *presult;         /* out  : true if setting the focus was succeeded */
} OWICMD_ESETFOCUSONFIELD, *POWICMD_ESETFOCUSONFIELD;

typedef struct _owicmd_egeteditcontrolatfocus
{
    void    *phWindow;        /* out  : the window handle of the currently on focus field */
} OWICMD_EGETEDITCONTROLATFOCUS, *POWICMD_EGETEDITCONTROLATFOCUS;   /* @pr31 hkr_QArun end */

typedef struct _owicmd_egetrowheaderinfo        /* @pr35 QArun extension */
{
    long        OcN;                            /* in   : Occurrence Number */
    const UTF16 **ppszHeaderText;               /* out  : Header Text *//* @c23137 */
    long        *iTopPos;                       /* out  : RowHeader Top Position*/
    long        *iBottomPos;                    /* out  : RowHeader Bottom Position*/
} OWICMD_EGETROWHEADERINFO, *POWICMD_EGETROWHEADERINFO;

typedef struct _owicmd_egetcolumnheaderinfo     /* @pr35 QArun extension */
{
    int         FiN;                            /* in   : Field Number */
    const UTF16 **ppszHeaderText;               /* out  : Header Text *//* @c23137 */
    long        *iLeftPos;                      /* out  : ColumnHeader Left Position*/
    long        *iRightPos;                     /* out  : ColumnHeader Right Position*/
} OWICMD_EGETCOLUMNHEADERINFO, *POWICMD_EGETCOLUMNHEADERINFO;

typedef struct _owicmd_egetcornerbuttoninfo     /* @pr35 QArun extension */
{
    const UTF16 **ppszHeaderText;               /*  out  : Header Text *//* @c23137 */
} OWICMD_EGETCORNERBUTTONINFO, *POWICMD_EGETCORNERBUTTONINFO;

typedef struct _owicmd_getmetainfo      /* @pr32 hkr_EXTGRID_1 */
{

    unsigned char   *pWidgetType;       /* Widget type for fields. */
    int             *pObjType;          /* Objec type (label, field etc). -- @b26235 */

} OWIGETMETAINFO, *POWIGETMETAINFO;
/*
** @b30333
** All members should be set to zero except for the color which should be set
** to -1 to switch them off and get them filled in by owiGetColors()
** The layout of the struct is fixed and in synch with an internal struct of the
** gui driver. Changes made here should also be made to the xmgetcolors struct.
*/
typedef struct _owiatt_colors
{
    long ulBackColor;       /* background color -1 meanse off*/
    long ulForeColor;       /* foreground color -1 meanse off*/
    long  lFlags;           /* Should be zero used internally by the GUI driver.     */
    UBOOL bForceBackGround; /* DO NOT USE Reserved for editcontrol with ENTCOLOR*/
    UBOOL bForceForeGround; /* DO NOT USE Reserved for editcontrol with ENTCOLOR*/
    long  x;                /* DO NOT USE Reserved for internal communication */
    long  y;
}OWIATT_COLORS;

/* ValRep */

typedef union _value                   /* data value variant */
{
   UBOOL   b;                          /* as boolean */
   UNUMBER n;                          /* as long int */
   UFLOAT  f;                          /* as floating pt */
   UNIDATE d;                          /* as date */
   USTR   *ps;                         /* as string */
   UNATIVE u;                          /* as usm handle */
} VALUE, *POVALUE;

typedef struct _valrep                 /* ValRep entry */
{
   int    iIndex;                      /* entry # */
   int    iType;                       /* variant type of lo, hi */
   VALUE  lo;                          /* low end of range */
   VALUE  hi;                          /* high end of range */
   char  *pszRep;                      /* representation */
} VR, *PVR;

/* Character */

typedef struct _ochr                   /* translated character */
{
   int  iStyle;                        /* character style (OFNT_*) */
   int  iCharSet;                      /* external characterset number */
   USTR sz[16];                        /* up to 15 characters */
} OCHR, *POCHR;

/* Request parameters */

struct owiopen
{
   int     request;                    /* OREQ_OPEN */
   WMLINK  wmlink;                     /* in: dummy link */
   HANCHOR hAnchor;                    /* in: global context handle */
   HCLIENT hClient;                    /* out: client handle */
};

struct owiclose
{
   int     request;                    /* OREQ_CLOSE */
   WMLINK  wmlink;                     /* Dummy link. -- @pr24 */
   HCLIENT hClient;                    /* in: client handle */
};

struct owicreate
{
   int      request;                   /* OREQ_CREATE  && OREQ_CREATEFIELD */
   HCLIENT  hClient;                   /* in: client handle */
   WMLINK   wmlink;                    /* in: handle to WM driver widget instance */
   HPARENT  hParent;                   /* in: parent window handle */
   int      nAttr;                     /* in: number of attributes */
   POWIATTR pAttr;                     /* in: attributes */
   USTRING *pszField;                  /* in: fieldname @pr12*/
   HWIDGET  hContainer;                /* in: container widget @prxxx */
   HWIDGET  hWidget;                   /* out: widget handle */
};

struct owidestroy
{
   int      request;                   /* OREQ_DESTROY && OREQ_DESTROYFIELD */
   HWIDGET  hWidget;                   /* in: widget handle */
   HWIDGET  hContainer;                /* in: widget handle */
};


struct owisetattr
{
   int      request;                   /* OREQ_SETATTR */
   HWIDGET  hWidget;                   /* in: widget handle */
   HWIDGET  hContainer;                /* in: widget handle */
   int      nAttr;                     /* in: number of attributes */
   POWIATTR pAttr;                     /* in: attributes */
};

struct owigetattr
{
   int      request;                   /* OREQ_GETATTR */
   HWIDGET  hWidget;                   /* in: widget handle */
   HWIDGET  hContainer;                /* in: widget handle */
   int      nAttr;                     /* in: number of attributes */
   POWIATTR pAttr;                     /* in/out: attributes */
};

struct owicommand
{
   int      request;                   /* OREQ_COMMAND */
   HWIDGET  hWidget;                   /* in: widget handle */
   int      id;                        /* in: command ID (OCMD_*) */
   int      iParam;                    /* in: command dependent parameter */
};


struct owifieldcommand
{
   int      request;                   /* OREQ_COMMAND */
   HWIDGET  hContainer;                /* in: widget handle */
   HWIDGET  hWidget;                   /* in: widget handle */
   int      id;                        /* in: command ID (OCMD_*) */
   int      iParam;                    /* in: command dependent parameter */
};

struct owigetcaps
{
   int      request;                   /* OREQ_GETCAPS */
   HWIDGET  hWidget;                   /* in: widget handle */
   int      nAttr;                     /* in: number of capabilities */
   POWIATTR pAttr;                     /* in/out: capabilities */
   WMLINK   wmlink;                    /* in: handle to WM driver widget instance */
};

struct owiprint
{
   int      request;                   /* OREQ_PRINT */
   HWIDGET  hWidget;                   /* in:  widget handle */
   int      xOrg;                      /* in:  origin to start printing */
   int      yOrg;                      /* in:  origin to start printing*/
   int      iStart;                    /* in:  vertical range of the widget to be printed */
   int      iEnd;                      /* in:  vertical range of the widget to be printed*/
   int      nAttr;                     /* in:  extra attribute information */
   POWIATTR pAttr;                     /* in:  extra attribute information */
   long     lPrinted;                  /* out: printed vertical space */
};

struct owidragover                     /* @pr9 */
{
   int      request;                   /* OREQ_DRAGOVER */
   HWIDGET  hWidget;                   /* in:  widget handle */
   void *   hwnd;                      /* in:  window handle */
   int      xPos;                      /* in:  x position of the mouse */
   int      yPos;                      /* in:  y position of the mouse */
   UBOOL    bDragEnter;                /* in:  Is this a DragEnter event? *//* @b27256 */
   UBOOL    bDropAllowed;              /* out: drop allowed on the position ? */
   UBOOL    bNewObject;                /* out: dragged over a new object? */
   char *   pszDropFormat;             /* out: dropformats for dragged-over object */
   char *   pszValue;                  /* out: value of dragged-over object*/
   char *   pszDropActions;            /* out: dropactions of dragged-over object */
};

struct owiselectdroptarget             /* @pr10 */
{
   int      request;                   /* OREQ_SELECTDROPTARGET */
   HWIDGET  hWidget;                   /* in:  widget handle */
   UBOOL    bSelect;                   /* in:  select or deselect */
};

/* @c29201, @b30041 call widget operation */
struct owicallwidoper
{
   int      request;                   /* OREQ_CALLWIDOPER */
   HWIDGET  hWidget;                   /* in:  widget handle */
   char     *OperationName;            /* in:  operation name */
   VOIDPTR  prmBlock;                  /* in:  parameters in UPRMBLOCK */
};

union owirequest                       /* consolidates all request structures */
{
   int      request;
   struct   owiopen      open;
   struct   owiclose     close;
   struct   owicreate    create;
   struct   owidestroy   destroy;
   struct   owisetattr   setattr;
   struct   owigetattr   getattr;
   struct   owicommand   command;
   struct   owigetcaps   getcaps;
   struct   owiprint     print;
   struct   owidragover  dragover;     /* @pr9 */
   struct   owiselectdroptarget  selectdroptarget;     /* @pr10 */
   struct   owifieldcommand fieldcommand;              /* @prxxx*/
   struct   owicallwidoper callwidoper;                /* @c29201 */
};

/* Miscellaneous */

typedef long (*OWIENTRY)(union owirequest *); /* widget entrypoint pointer */

/***************************************************************************/
/* SERVICES                                                                */
/***************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/* Asn setting */
extern int    oGetCuroccHighlightClrs(WMLINK wmlink,long *plForeColor,long *plBackColor);

/* Properties */

extern int    ocpBool(WMLINK wmlink, char *pszProp, int iDefault);
extern int    ocpSubBool(WMLINK wmlink, char *pszProp, int iDefault, char *pszPropertyString);
extern long   ocpLong(WMLINK wmlink, char *pszProp, long lDefault);
extern double ocpDouble(WMLINK wmlink, char *pszProp, double fDefault);
extern int    ocpString(WMLINK wmlink, char *pszProp, char *pszBuf, int iMax);
extern int    ocpSubString(WMLINK wmlink, char *pszProp, char *pszBuf, int iMax, char *pszPropertyString);
extern int    ocpFirst(WMLINK wmlink, char *pszOut, int iMax);
extern int    ocpNext(WMLINK wmlink, char *pszOut, int iMax);

/* Preferences */

extern int    opBool(WMLINK wmlink, char *pszKey, int bDefault);
extern long   opLong(WMLINK wmlink, char *pszKey, long lDefault);
extern double opDouble(WMLINK wmlink, char *pszKey, double fDefault);
extern int    opString(WMLINK wmlink, char *pszKey, char *pszBuf, int iMax);
extern int    opPutBool(WMLINK wmlink, char *pszKey, int bData);
extern int    opPutLong(WMLINK wmlink, char *pszKey, long lData);
extern int    opPutDouble(WMLINK wmlink, char *pszKey, double fData);
extern int    opPutString(WMLINK wmlink, char *pszKey, char *pszData);

/* Data */

extern int    odGet(WMLINK wmlink, void *pValue, int iMax, int iType);
extern int    odGetC(WMLINK wmlink, void *pValue, int iMax, int iType);
extern int    odPut(WMLINK wmlink, void *pValue, int iMax, int iType);
extern int    odPutC(WMLINK wmlink, void *pValue, int iMax, int iType);

/* Label */

extern int    olGet(WMLINK wmlink, USTR *pszLabel, int iMax);
extern int    olGetC(WMLINK wmlink, USTR *pszLabel, int iMax);
extern int    olPut(WMLINK wmlink, USTR *pszLabel);
extern int    olPutC(WMLINK wmlink, USTR *pszLabel);

/* ValRep */

extern int    ovrCount(WMLINK wmlink);
extern int    ovrByIndex(WMLINK wmlink, PVR pvr, int iIndex, int iType);
extern int    ovrByValue(WMLINK wmlink, PVR pvr, void *pValue, int iType);
extern int    ovrByRep(WMLINK wmlink, PVR pvr, char *pszRep, int iType);
extern void   ovrFree(WMLINK wmlink, PVR pvr);
extern int    ovrPut(WMLINK wmlink, PVR pvr);
extern int    ovrPutC(WMLINK wmlink, PVR pvr);
extern int    ovrNext(WMLINK wmlink, PVR pvr, void **pvC, int iType);
extern int    ovrCreate(WMLINK wmlink, USTRING *pszValrep);

/* Access keys */

extern int    oxsParse(WMLINK wmlink, USTR *pszLabel, POCHR pochr);
extern int    oxsAddKey(WMLINK wmlink, int iKey, int iScope);
extern int    oxsRemoveKey(WMLINK wmlink, int iKey, int iScope);

/* Miscellaneous */

extern int    oNotify(WMLINK wmlink, int iNotification, int iParam);
extern long   oQuery(WMLINK wmlink, int iQuery, int iParam);
extern int    oStrConvEx(WMLINK wmlink, USTR *in, USTR *out, int iMax, int iOptions, char *csname);    /* @b30973 */
extern int    oStrConv(WMLINK wmlink, USTR *in, USTR *out, int iMax, int iOptions);
extern int    oChrConv(WMLINK wmlink, USTR *in, POCHR pout);
extern int    oKeyMode(WMLINK wmlink, int iMode);
extern void   oAttach(WMLINK wmlink, int iAttach);
extern int    oGetMessage(WMLINK wmlink, USTR *key, USTR *out, int iMax);
extern void   oMessage(WMLINK wmlink, USTR *msg, int iOptions);
extern int    oGetObjectName(WMLINK wmlink, USTR *pszOut, int iMax);
extern int    oGetObjectRowIndex(WMLINK wmlink);                         /* @c30170 */
extern int    oGetLogicalObjectName(WMLINK wmlink, USTR *pszOut, int iMax);
extern int    ewiGetEntityName(WMLINK wmlink, USTR *pszOut, int iMax);              /*  @pr26 */
extern int    ewiFormIsPrinting(WMLINK m_wmlink);                                   /* @pr36 */
extern int    oGetPhysicalWidgetName(WMLINK wmlink, USTR *pszLogicalName, USTR *pszOut);  /* @b29796 */
extern int    oGetFormNameFromLink(WMLINK wmlink, USTR *pszOut, int iMax);        /*  @pr26 */
extern int    oRegChannelListener(WMLINK wmlink,int iChannel,int iFormat);
extern int    oUnRegChannelListener(WMLINK wmlink,int iChannel);

extern void * oFileOpen(WMLINK wmlink,          /* in @c21636 */
                        char *pszFileName,      /* in  - Does not use assignment re-direction !*/
                        int iCode);             /* in  - File open code */

extern int    oFileClose(WMLINK wmlink,         /* in @c21636 */
                         void *pvFile);         /* in  - File to close  */


extern int    oFileWriteLine(WMLINK wmlink,     /* in @c21636 */
                             void *pvFile,      /* in  - File  */
                             char *pszLine,     /* in  - Textline in internal meta format    */
                             UBOOL bEol);       /* in  - Add end of line marker TRUE | FALSE */

extern int    oFileWriteTextBuf(WMLINK wmlink,  /* in @c21636 */
                                void *pvFile,   /* in  - File  */
                                char *pszBuf);  /* in  - Zero terminating UTF8/Meta formatted text buffer*/


/* 3GL interface */

extern int    oGetWidget(USTR *field, HWIDGET *wid, WMLINK *wmlink, OWIENTRY *owientry, USTR *logwid, USTR *physwid);
extern int    oGetFormName(void *uniwidget, USTR *pszOut, int iMax);
extern WMLINK oGetLink(HPARENT window);

/* @pr20 entity level services */
extern int ewiGetColLabelInfo(WMLINK wmlink, USTR *pszLabel, int iMax, int iCol, int* hAlign, int* vAlign);     /* @c23528 */
/* @pr22 */
extern int oSetIUnknown(WMLINK wmlink, void *pUnknown, char *pszComponent);
extern int oDestroyIUnknown(WMLINK wmlink);
extern long oWrapExtComObject(WMLINK wmlink,            /* in : wmlink - ticket to kernel       */
                         void *pdispVal,                /* in : dispatch pointer                */
                         char *pszInterfaceName,        /* in : Interface name or class name    */
                         char *pszOutInstanceName,      /* out: Name ICC_<addr> used by urb     */
                         int  iSize);                   /* in : size of supplied buf with pszOutInstanceName*/
extern void oGetMetaInfo(WMLINK, POWIGETMETAINFO);      /* @pr32 hkr_EXTGRID_1 */
extern int  oGetObjType(WMLINK, int *);                 /* Function for obtaining object type. -- @b26235 */
/*
** @columns - called on a ECMD_COLUMN message. UNIFACE kernel sends a ECMD_COLUMN to an entity level
** widget when $columnsyntax() has changed the behaviour of the column
*/
extern int ewiGetColumnInfo(WMLINK wmlink,int iCol, unsigned long *ulflags );     /* @columns*/
/*
** @c30648 - gets the address of a field or label in codepage string
** may require in the control a translation to UTF16
** Used for MSAA interface and testing tools
**
** Parameters:
**
** WMLINK wmlink  -  the field link  [ IN ]
** UTF16 *pszOut  -  contains the complete address
** int  iMax      -  maximum length in bytes what can be copied into pszOut
** BOOL l_bLabel  -  When TRUE the pszOut contains a label address for the assoc label.
**                   otherwise a field addres is returned.
** BOOL l_AddRow  -  Add a row number to the address when set to TRUE.
**
** FIELDADDRESS = <model>.<entity>.<fieldname>.<occnr>
** LABELADDRESS = <model>.<entity>.LABEL_<fieldname>.<occnr>
*/

int oGetObjectAccessName(WMLINK wmlink, UTF16 *pszOut, int iMax, UBOOL l_bLabel, UBOOL l_AddRow);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !OWI_H */
