/* @(#)CONT_ID %fv: owimsw.h-71.1.10:incl:1 % %dc: Fri Aug  7 15:08:40 2015 % (#)@ */

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
/****************************************************************************
date   refnum    version who description
050316 b26236    9.1.01  mab New OWI service for obtaining special window
                             message used for resolving WMLINK by
                             automated testing tools.
050526 c21961    910102  mbg Extend the capabilities with a 'describe' request
                             for the IDE).
051019 e22529    910102  mab Functionality to paint Uniface compatible shaped
                             texts.
060314 c23137    910102  hkr Grid Widget Unicode enabled.
061011 c24516    910102  mng Shortkey combination ucomposer window
061017 c23483    910102  jdk RichEditbox: No visual selection of Toolbar options
061129 c25293    N101    jya $paintedfieldproperties Zorder implementation
070205 c25517    920101  jya support transparent background.
060622 c21499    910102  jdk Conflicting defines in the owimsw.h file.
070202 c25467    920101  hkr GUI: Non grid EditBox Changeable Mouse Pointer Implementation.
060921 b26669    M441    nk  Form background color for an editbox needed
070923 b27300    N203    jdk It should be possible to store the layout of Grid and Split Bar independently
070309 c25564    920101  hkr GUI: Grid EditBox Changeable Mouse Pointer Implementation.
070323 c25752    920101  jya WinCE: fix the transparent handling problem.
070411 c25821    920101  hkr GUI: Non Grid dropdownlist dynamic mouse cursor and dynamic tooltip implementation.
070923 b27300    N203    jdk It should be possible to store the layout of Grid and Split Bar independently
071213 b27431    O102    jya A gif file with "transparent" color for the background does not print well.
071214 b27412    O102    nk  Inherit Entity Color (ENTCOLOR) does not work for editbox in entity on tabpage.
080514 b27677    O201    ete Title of filebox is now in UTF16
080606 b27703    O201    jya Implement wordwrap only at the blank space.
100223 b28502    P209    jya Font is changed in Proc editor on Japanese Windows.
100406 b28613    P211    jdk Formtext migration cannot use the standard label implementation.
100527 b28680    P212    jdk Changes in formtext font behavior not taken into account when printing.
101222 b28992    P218    jya Hebrew Windows: cursor movement by quotation mark behaves incorrectly.
111012 c28976    950101  jya GRID: too many call Viewport_Resized on Windows 7.
111102 b29728    R120    jdk Hourglass persists when clicking on a hyperlink that triggers a print.
120221 b29590    9.6.01  jdk Setting for labels to inherit the parents back and foreground color is needed.
120221 c29164    960101  jya add include files to avoid the compile errors.
120425 b28224    9.6.01  jdk White color of tabpage in Windows Vista/7 using Aero theme is not white.
120626 c29198    9.6.01  jxa Label attached image position support and Different image size supported.
120726 c29327    9.6.01  jxa Label better to be centred in the whole rect not in the remaining rect.
121203 b29864    X102    ago "Delete current layout geometry from settings ..." doesn't work on grid layout.
130320 b30053    MX01    jxa Acurate tab height and width are required.
130315 b29994    MX01    jxa Padding is required on button/tabex to make better layout.
130516 b30080    X201    jdk UF96: InheritColors is working inconsistently when using "entcolor" in editbox
130530 b30052    X201    jya The 3GL header file owimsw.h is referring to a non-existing header file.
130723 b30333    MX02    jdk INHERITCOLORS: And area frames do not work correctly. Related to 30248
140112 c29980    10.1.01 tsk Add RGBA as image format for Scintilla
140522 b30605    X501    jya RTL: Hyperlink is shown on the wrong place on a tabpage after clear.
140627 c30170    MX05    jxa MSAA support for the GUI objects general functions, editbox,and windows commandbutton.
141007 c30334    MX05    jya New ini setting 'AccessibleNameSeparator'.
141006 b30581    MX05    jdk Grid: It is not possible to store only the layout of Grid (and not of split bars)
150310 c30648    MX06    jdk MSAA support
150728 b30988    9.7.01  jdk Attach properties on editbox show one pixel margin i.s.o two pixel margin
date   refnum    version who description
*****************************************************************************/
/***************************************************************************/
/* ATTENTION:                                                              */
/* This file is distributed as a part of the OWI header files              */
/* in the 3GL\include directory of the Uniface installation.               */
/* Therefore if you modify this file, please take extra care about it,     */
/* for example, you cannot use something only available inside of Uniface. */
/***************************************************************************/

#ifndef OWIMSW_H
#define OWIMSW_H

#include "unityp.h"                              /* @c29164 definition for UTF16. */
#include "wmtypes.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/***************************************************************************/
/* DEPENDENCIES                                                            */
/***************************************************************************/

/* include windows.h before this file to define the following types:       */

/* UINT       unsigned int                                                 */
/* HWND       window handle                                                */
/* WPARAM     first message parameter                                      */
/* LPARAM     second message parameter                                     */
/* HFONT      font handle                                                  */
/* HBITMAP    bitmap (DDB) handle                                          */
/* HMETAFILE  metafile handle                                              */
/* HPALETTE   palette handle                                               */
/* RECT       rectangle                                                    */
/* COLORREF   rgb triple                                                   */
/* WNDPROC    window procedure pointer                                     */
/* MDICREATESTRUCT parameter structure for WM_MDICREATE                    */

/***************************************************************************/
/* CONSTANTS                                                               */
/***************************************************************************/

/* @pr41 hkr_EXTGRID_PICTURE start */
/* Opaque setting. */
#define UPCT_SCWINDOW    0x01             // Window system color.
#define UPCT_SC3D        0x02             // 3D system color
// -- Some useful defines / typedefs
#define FRAME_OFF         0               // No frame around picture
#define FRAME_ON          1               // Frame around picture
#define FRAME_ROUND       2               // Round frame around picture

#define SCROLL_OFF        0               // No scrollbars
#define SCROLL_ON         1               // Scrollbars always
#define SCROLL_AUTO       2               // Scrollbars as required

#define ALIGN_LEFTTOP     0               // Aligned smaller picture to left
#define ALIGN_CENTER      1               // Center smaller picture
#define ALIGN_RIGHTBOTTOM 2               // Aligned smaller picture to right

#define ELLIPSEWIDTH      20              // width and height of rounded frame
#define ELLIPSEHEIGHT     20

// -- pseudo private Uniface clipboard formats
#define UCF_GLYPH          0x0500          // format "^glyphname"; actual id is wGlyphFormat
// Resolve naming conflict: CF_FILENAME defined differently in olestd.h
// @c21499 CF_FILENAME  renamed to UCF_FILENAME.
#define UCF_FILE_NAME      0x0501          // format "@filename"; actual id is wFileNameFormat
/* @pr41 hkr_EXTGRID_PICTURE end */

/* Palette management */

#define OCMD_PALETTECHANGED     OCMD_PLATFORM+1
#define ONTF_PALETTECHANGED     ONTF_PLATFORM+1
#define OATT_PALETTE            OATT_PLATFORM+1


/* OCMD_SETUPCHANGE ids */

#define OINI_UPI                 1      /* [upi] section */
#define OINI_TOOLBAR             2      /* [toolbar] section */
#define OINI_COLOR               3      /* [foreground] and/or [background] section */
#define OINI_SCREEN              4      /* [screen] section (fonts) */
#define OINI_SYSCOLOR            5      /* sys color changes @pr25  */

/* owiGetImageEx styles */

#define OIMG_UNATIVE             0x0001 /* pData format is UNATIVE */
#define OIMG_DIALOG              0x0002 /* popup filter dialog if applicable */
#define OIMG_GSCALE              0x0004 /* map to grayscale */
#define OIMG_STDPALETTE          0x0008 /* map to standard palette */
#define OIMG_QDITHER             0x0010 /* quick (ordered) dither - NOT YET */
#define OIMG_DITHER              0x0020 /* dither (error diffusion) - NOT YET */
#define OIMG_GETDIB              0x0040 /* request image in DIB format */ /* @pr6 */
#define OIMG_GETRGBA             0x0080 /**< request image in RGBA format */ /* @c29980 */

/* owiDrawText/Image styles */
                                        /* I=Image only, T=Text only, B=Both */
#define ODRW_ISOTROPIC           0x0001 /* I: preserve aspect ratio */
#define ODRW_GRAYED              0x0002 /* B: draw grayed out */
#define ODRW_3D                  0x0004 /* T: draw with 3d effect */
#define ODRW_XPARENT             0x0008 /* B: do not draw background */
#define ODRW_NOCLIP              0x0010 /* B: do not clip to format rect */
#define ODRW_MNEMONIC            0x0020 /* T: draw mnemonic characters underlined */
#define ODRW_NOWRAP              0x0040 /* T: do not wordwrap */
#define ODRW_NLSSTYLE            0x0080 /* @pr16: Draw text in Nls style, e.g. RTL */
#define ODRW_WRAPPERNLSSTYLE     0x0100 /* @pr16: Leave NLS styles up to Owidrawtext(ex)*/
#define ODRW_FORMTEXT            0x0200 /* @b28613 Migrated formtext*/
#define ODRW_CALCRECT            0x1000 /* B: calculate rectangle only */
#define ODRW_PRERENDER           0x2000 /* I: render metafile on bitmap only */
#define ODRW_UPDATECOLORS        0x4000 /* B: update colors after palettechange only */
#define ODRW_SHAPEDTEXT          0x8000 /* T: Take UTF16 shaped characters into account. */

/* owiTooltip - tooltip sub functions */
#define OTIP_CREATE              0x0000 /* @pr15 Create new tooltip     */
#define OTIP_DELETE              0x0001 /* @pr15 Delete current tooltip */
#define OTIP_ACTIVE              0x0002 /* @pr15 Is tooltip active?     */

/* owiSetProperty - property identifiers (for performance reasons) */
#define OPROP_ATTACH             1      // @pr20 "attach"
#define OPROP_DRAGFORMAT         2      // @pr20 "dragformat"
#define OPROP_DROPFORMAT         3      // @pr20 "dropformat"
#define OPROP_DROPACTIONS        4      // @pr20 "dropactions"

/* Win32 control color message mappings */

#ifndef WM_CTLCOLORBTN
   #define WM_CTLCOLORBTN               WM_CTLCOLOR
   #define WM_CTLCOLORDLG               WM_CTLCOLOR
   #define WM_CTLCOLORLISTBOX           WM_CTLCOLOR
   #define WM_CTLCOLORMSGBOX            WM_CTLCOLOR
   #define WM_CTLCOLORSCROLLBAR         WM_CTLCOLOR
   #define WM_CTLCOLORSTATIC            WM_CTLCOLOR
   #define WM_CTLCOLOREDIT              WM_CTLCOLOR
#endif /* !WM_CTLCOLORBTN */

/* Win32 control color message cracker mappings */
#if 0
#ifndef HANDLE_WM_CTLCOLORBTN
   #define HANDLE_WM_CTLCOLORBTN        HANDLE_WM_CTLCOLOR
   #define HANDLE_WM_CTLCOLORDLG        HANDLE_WM_CTLCOLOR
   #define HANDLE_WM_CTLCOLORLISTBOX    HANDLE_WM_CTLCOLOR
   #define HANDLE_WM_CTLCOLORMSGBOX     HANDLE_WM_CTLCOLOR
   #define HANDLE_WM_CTLCOLORSCROLLBAR  HANDLE_WM_CTLCOLOR
   #define HANDLE_WM_CTLCOLORSTATIC     HANDLE_WM_CTLCOLOR
   #define HANDLE_WM_CTLCOLOREDIT       HANDLE_WM_CTLCOLOR
#endif /* !HANDLE_WM_CTLCOLORBTN */
#endif
#define UM_EGETEWILINK      (WM_USER + 1100)    /* @pr38 hkr_QArun */

/***************************************************************************/
/* ATTRUBUTES                                                    @pr4      */
/***************************************************************************/

#define OATT_PRINTDC    OATT_PLATFORM       // @pr4 : HDC to print to

/* Capability IDs */
                                                /* TYPE       UNIT      SUMMARY */
#define OCAP_NO_ALT_ACCESS  OCAP_PLATFORM+1     /* long       Boolean   needs no ALT for access keys @pr23 */


/* @pr43 start */
#define OCAP_UNICODE         OCAP_PLATFORM+3    /* long       Boolean    This capability indicates
                                                **                       if the OWI Widget supports
                                                **                       Unicode or not. The capability
                                                **                       is FALSE when the Widget does
                                                **                       not support Unicode. The Boolean
                                                **                       is TRUE when Unicode is supported.
                                                */
/* @pr43 end */

/***************************************************************************/
/* DATA TYPES                                                              */
/***************************************************************************/

/* Define the data type for general purpose. */
typedef void*                      VOIDPTR; /* @b30052 */

/* Platform dependent types for OWI.H */

typedef struct _widinst*           WMLINK;  /* link to GUI driver widget instance */
typedef COLORREF                   UCOLOR;  /* color spec */
typedef struct HWND__ NEAR * HPARENT;       /* parent window handle @pr1, @pr3 */
typedef void*                      HWIDGET; /* handle to OWI widget instance */
typedef void*                      HCLIENT; /* handle to OWI client instance - NOT USED IN WINDOWS */
typedef void*                      HANCHOR; /* handle to global context - NOT USED IN WINDOWS */

/* Image structure */

typedef struct _owiimg
{
    UINT      uStyle;                    /* internal use */
    HBITMAP   hbImage;                   /* main bitmap */
    int       nColors;                   /* number of colors */
    HPALETTE  hPalette;                  /* palette */
    int       cx;                        /* width of bitmap */
    int       cy;                        /* height of bitmap */
    HMETAFILE hMeta;                     /* metafile */
    RECT      rMeta;                     /* metafile extent */
    HBITMAP   hbIconANDMask;             /* icon mask */
    HANDLE    hDIB;                      /* DIB version */
    HANDLE    hGreyBitmap;               /* greyed bitmap */
    HANDLE    hDIBMask;                  /* DIB mask *//* @b27431 */
    unsigned  char*     pRGBA;           /**< RGBA byte buffer */ /* @c29980 */
} OWIIMG, *POWIIMG;


typedef enum _panelitemtype
{
    PANELITEM_TYPE_BUTTON,
    PANELITEM_TYPE_COLORLIST,
    PANELITEM_TYPE_COMBOFONTLIST,  /* Combobox with fontnames */
    PANELITEM_TYPE_COMBOFONTSIZE
} panelitemtype;


typedef struct _panelitem
{
    panelitemtype itemType;
    int  itemID;
    char szGlyphName[128];
    UTF16 szFontName[128];
    int  iFontSize;
    HWND hOwner;
} PANELITEM,*PPANELITEM;

/***************************************************************************/
/* SERVICES                                                                */
/***************************************************************************/

/* Message handling */

extern long    owiDefWndProc(WMLINK wmlink, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, WNDPROC pfDefProc);
extern BOOL    owiKeyFilter(WMLINK wmlink, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/* Fonts */

extern HFONT   owiCreateFont(WMLINK wmlink, char *pszLogicalName, UINT uStyle);
extern void    owiDestroyFont(WMLINK wmlink, HFONT hFont);

/* Images */

extern POWIIMG owiGetImage(WMLINK wmlink, char cType, char *pszImage);
extern POWIIMG owiGetImageEx(WMLINK wmlink, char cType, void *pData, int cx, int cy, int nDepth, UINT uFlags);

/*@pr46*/
extern POWIIMG owiUnicodeGetImage(WMLINK wmlink, UTF16 cType, UTF16 *pszImage);
extern POWIIMG owiUnicodeGetImageEx(WMLINK wmlink, UTF16 cType, void *pData, int cx, int cy, int nDepth, UINT uFlags);

extern void    owiFreeImage(WMLINK wmlink, POWIIMG pImage);
extern BOOL    owiDrawImage(WMLINK wmlink, HDC hdc, POWIIMG pImage, LPRECT lpr, int hScale, int vScale,
                            int hAlign, int vAlign, int hOffset, int vOffset, UINT uFlags);
/*@b30444*/
extern BOOL    owiDrawFrame(WMLINK wmlink, 
                            HDC hdc,    
                            char    *pszSelector,       /* IN: String containing the selector name. For areaframes this is the componentname */
                            char    *pszFrameName,      /* IN: The frame name */
                            char    *pszClass,          /* IN: Class name. For instance "frame"*/
                            RECT    *prBoundingRects,   /* IN: Rectangles to paint */
                            int     iBoundingRectAngles);/* IN: number of rects to paint*/
/*@b30444 ends*/
/*@c31598*/
/**
@ short - draw a frame/border inside the given rectangle with the specified properties.

@param    wmlink               in : link to GUI driver widget instance
@param    hdc                  in : device context
@param    UFRAMETYPE           in : defines the type of border/frame to be drawn
@param    l_FrameWidth         in : width of border/frame in pixels
@param    l_FrameColor         in : Color of the frame
@param    l_FrameRect          in : Rectangle wherein the frame/border should be drawn

@returns     a boolean. Always true.
*/
extern BOOL owiDrawFrameType(WMLINK     wmlink,
                             HDC        hdc, 
                             UFRAMETYPE l_FrameType, 
                             int        l_FrameWidth, 
                             long       l_FrameColor, 
                             RECT       l_FrameRect); /*@c31598*/
/*@c31598*/
/**
@ short - Adjust the given rectangle based on the frame/border properties

@param    wmlink               in : link to GUI driver widget instance
@param    UFRAMETYPE           in : defines the type of border/frame to be drawn
@param    l_FrameWidth         in : width of border/frame in pixels
@param    *l_FrameRect        out : Reference of the rectangle

@returns     a boolean. Always true.
*/
extern BOOL owiAdjustFrameRect(WMLINK     wmlink,
                               UFRAMETYPE l_FrameType,
                               int        l_FrameWidth,
                               RECT      *l_pFrameRect);  /*@c31598*/
/* c29198 */
/**
@short - draw the image defined in front of the label with specified position relative to the label.

@param    wmlink               in : link to GUI driver widget instance
@param    hdc                  in : device context
@param    rArea                in : the full area containing both the image and the label
@param    rAreaLeft            out: the left over rect remained for the label draw
@param    rLabelSize           in : label size rect
@param    iHorzLabelAlignment  in : label required alignment
@param    iImagelabelAlign     in : image position relative to the label
@param    iImageSize           in : image size
@param    pImg                 in : the image defined in front of the label
@param    cxMargin             in : in x-coordinate, give text or image some space from the border or the space between image and label
@param    cyMargin             in : in y-coordinate, give text or image some space from the border or the space between image and label
@param    uFlags               in : the style of the image

@returns     a boolean indicates that the image is drawed successfully and the rect remained for the label is returned by pr.
*/
extern BOOL owiDrawImageLabel(WMLINK wmlink, HDC hdc,
                              RECT *rArea,
                              RECT *rAreaLeft,
                              RECT rLabelSize,
                              int iHorzLabelAlignment,
                              int iImagelabelAlign,
                              int iImageSize,
                              POWIIMG pImg,
                              int cxMargin,
                              int cyMargin,
                              UINT uFlags);

/* c29198 */

/* @b29994 */
/**
@short - draw the image defined in front of the label with specified position relative to the label.

@param    wmlink                in : link to GUI driver widget instance
@param    hdc                   in : device context
@param    rArea                 in : the full area containing both the image and the label
@param    rAreaLeft             out: the left over rect remained for the label draw
@param    rLabelSize            in : label size rect
@param    iHorzLabelAlignment   in : label required horizontal alignment
@param    iImagelabelAlign      in : image position relative to the label
@param    iImageSize            in : image size
@param    pImg                  in : the image defined in front of the label
@param    rPadding              in : the rect of the padding
@param    iHoriSepMargin        in : in x-coordinate, give some space between image and label
@param    iVertSepMargin        in : in y-coordinate, give some space between image and label
@param    uFlags                in : the style of the image

@returns  a boolean indicates that the image is drawed successfully and the rect remained for the label is returned by pr.
*/
extern BOOL  owiDrawImageLabelPadding(WMLINK wmlink, HDC hdc,
                                      RECT *rArea,
                                      RECT *rAreaLeft,
                                      RECT rLabelSize,
                                      int iHorzLabelAlignment,
                                      int iImagelabelAlign,
                                      int iImageSize,
                                      POWIIMG pImg,
                                      RECT rPadding,
                                      int iHoriSepMargin,
                                      int iVertSepMargin,
                                      UINT uFlags);

/**
@short - Description  : in the rep part of the valrep there can be a glyph this
                        stripped out when it is available.
                        Format: [<glyphname><gold>!]<representation>=value

@param    wmlink               in : link to GUI driver widget instance
@param    pszRep               in : the data content with [<glyphname><gold>!]<representation>
@param    pszImage             out: the image splitted
@param    pszLabel             out: the label splitted

@returns     a boolean value of whether split successfully or not
*/
extern BOOL    owiSplitText(WMLINK wmlink, char *pszRep, char **pszImage, char **pszLabel);

/* Text */

extern BOOL    owiDrawText(WMLINK wmlink, HDC hdc, char *pszText, HFONT hFont, LPRECT lpr, int hAlign, int vAlign, UINT uFlags);

/* @pr43
**
** Unicode version of owiDrawText(). This method writes Unicode UTF16 strings
** to the given device context.
*/
extern BOOL owiDrawUnicodeText
(
    WMLINK wmlink,
    HDC hdc,
    UTF16 *pszText,
    HFONT hFont,
    LPRECT lpr,
    int hAlign,
    int vAlign,
    UINT uFlags
);

/* @e22529
**
** Draws shaped (bold, italic, underline etc) Unicode UTF16 strings.
*/
extern BOOL owiDrawShapedUnicodeText
(
    WMLINK wmlink,
    HDC hdc,
    UTF16 *pszText,
    VOIDPTR pShapeFonts,
    LPRECT lpr,
    int hAlign,
    int vAlign,
    UINT uFlags
);

extern BOOL    owiDrawTextEx(WMLINK wmlink, HDC hdc, char *pszText, HFONT hFont, LPRECT lpr, int hAlign, int vAlign, UINT uFlags, UINT iFirstLine, UINT iLastline);

/* @pr43
**
** Unicode version of owiDrawTextEX(). This method writes Unicode UTF16 strings
** to the given device context.
*/
extern BOOL owiDrawUnicodeTextEx
(
    WMLINK wmlink,
    HDC hdc,
    UTF16 *pszText,
    HFONT hFont,
    LPRECT lpr,
    int hAlign,
    int vAlign,
    UINT uFlags,
    UINT iFirstLine,
    UINT iLastline
);

/* @e22529
**
** Paints shaped Unicode strings in a certain line range.
*/
extern BOOL owiDrawShapedUnicodeTextEx
(
    WMLINK wmlink,
    HDC hdc,
    UTF16 *pszText,
    VOIDPTR pShapeFonts,
    LPRECT lpr,
    int hAlign,
    int vAlign,
    UINT uFlags,
    UINT iFirstLine,
    UINT iLastline
);

/*
** @pr18 -Service function for linking the widget to the windowhandle
** Specially needed for widget which can create and destroy windows
** on the fly, like the OCX widget.
*/
extern LONG owiLinkWidget(
                 WMLINK link,         //in: Link to owi interface.
                 HWND   hParent);     //in: windowhandle of widget.


extern LONG owiUnlinkWidget(
                 WMLINK link,         //in: Link to owi interface.
                 HWND   hParent);     //in: windowhandle of widget.
/*
** @pr15 -Service function for maintaining a tooltip in a widget.
*/
extern BOOL owiTooltip(               //out: 1 | 0  on iAction = 0
                 WMLINK link,         //in: Link to owi interface.
                 char   *pszTipText,  //in: Text for tooltip.
                 HWND   hParent,      //in: Parent windowhandle
                 int    iAction);     //in: OTIP_NEW|OTIP_DEL|OTIP_SHOW

/*@pr46*/
extern BOOL owiUnicodeTooltip(               //out: 1 | 0  on iAction = 0
                 WMLINK link,         //in: Link to owi interface.
                 UTF16   *pszTipText,  //in: Text for tooltip.
                 HWND   hParent,      //in: Parent windowhandle
                 int    iAction);     //in: OTIP_NEW|OTIP_DEL|OTIP_SHOW

extern BOOL owiSrvCreateToolTip(            /* @c25821 start */
                 WMLINK wmlink,
                 HWND hwnd,
                 char* pszToolTipText);

extern BOOL owiImageTooltip(
                 WMLINK wmlink,
                 POWIIMG pImage,
                 HWND hParent,
                 int iAction);

extern BOOL owiSrvRemoveToolTip(
                 WMLINK wmlink,
                 HWND hwnd);                /* @c25821 end */

extern BOOL owiSrvCreateUnicodeToolTip(WMLINK wmlink, HWND hwnd, UTF16* pszToolTipText);

extern BOOL owiSrvCreateImageToolTip(WMLINK m_wmlink, HWND hwnd, POWIIMG pImage);                     /* @c25821 */

/* MDI window management */
#ifdef u_wce
#  define MDICREATESTRUCT HWND
#endif
extern HWND    owiCreateMDIChild(WMLINK wmlink, MDICREATESTRUCT *pMDI);
extern void    owiDestroyMDIChild(WMLINK wmlink, HWND hWnd);

extern int     owiDetailPos(WMLINK wmlink, int xPos, int yPos);      // @pr2
#ifndef u_wce
extern char *  owiWordWrap(WMLINK wmlink, HDC hDC, char * pszText, HFONT hFont, int cx, UINT * piLines);
#endif

/* @pr41
**
** Unicode version of owiWordWrap().
*/
extern UTF16* owiUnicodeWordWrap
(
    WMLINK wmlink,
    HDC hDC,
    UTF16 *pszText,
    HFONT hFont,
    int cx,
    UINT *piLines
);

/*
** @b27703
** Unicode version of owiWordWrap() and word wrap only at the blank space.
*/
extern UTF16* owiUnicodeWordWrapAtSpace
(
    WMLINK wmlink,
    HDC hDC,
    UTF16 *pszText,
    HFONT hFont,
    int cx,
    UINT *piLines
);

/* @e22529
**
** Unicode version of owiWordWrap() with shaped text.
*/
extern UTF16* owiShapedUnicodeWordWrap
(
    WMLINK wmlink,
    HDC hDC,
    UTF16 *pszText,
    VOIDPTR pFont,
    int cx,
    UINT *piLines,
    UINT uiFlags        /*@b28680*/
);

/*
** @b27703
** Unicode version of owiWordWrap() with shaped text, and word wrap only at the blank space.
*/
extern UTF16* owiShapedUnicodeWordWrapAtSpace
(
    WMLINK wmlink,
    HDC hDC,
    UTF16 *pszText,
    VOIDPTR pFont,
    int cx,
    UINT *piLines,
    unsigned int uiFlag /* @b28613 - interface change for migrated formtext ODRW_FORMTEXT*/
);

extern long  owiGetState(WMLINK wmlink);                           // @pr8

/*
** @pr11 zoom service functions, to be used in combination with the
** OATT_NEWPARENT attrib.
** Widget may not call this when OATT_NEWPARENT is not supported.
*/
long owiZoom(WMLINK wmlink,
             long lZoom,          /* 1 = Quick zoom 0 = normal zoom */
             char *pszTitle,     /* Text in titlebar of zoom window*/
             BOOL bNoQuit);      /* true if quit not possible @pr17 */

/* @pr43
**
** Unicode version of owiZoom() function. The difference with
** owiZoom() is that owiUnicodeZoom() shows Unicode
** titles instead of normal titles.
*/
long owiUnicodeZoom
(
    WMLINK wmlink,
    long lZoom,      /* 1 = Quick zoom 0 = normal zoom */
    UTF16 *pszTitle, /* Text in titlebar of zoom window*/
    BOOL bNoQuit     /* true if quit not possible */
);

long owiUnZoom(WMLINK wmlink);     /* @pr11 */

extern long    owiNlsStyle(WMLINK wmlink, int iStyleRequest);        // @pr10
extern BOOL    owiNlsDBCSLead(WMLINK wmlink, char cTest);            // @pr12 @pr13
extern int     owiNlsRichEditLangOptions(WMLINK wmlink, HWND hWnd);  // @b28992

/* Message from UPI to OWI widgets */                                // @pr7

#define WM_UPIOWI           (WM_USER+2000)
#define WM_CANCELCAPTURE    WM_UPIOWI
                                                                                                  // @pr5 - end
/* Askmess-style message box */

extern int     oMessageBox(WMLINK wmlink, int iMsg);                 // @pr9

/* @pr14 Widget focus services */

extern LPVOID   owiGetFocusWid(WMLINK wmlink);                       // @pr14
extern BOOL     owiSetFocusWid(WMLINK wmlink, LPVOID lpWid);         // @pr14

extern BOOL     owiResizePage(WMLINK wmlink);        // @pr19

/* @pr20 Drag & drop services */

extern LONG owiSetProperty(
                WMLINK wmlink,          //in: Link to owi interface.
                int iProperty);         //in: Property index OPROP_...
/*@b30988*/
extern LONG owiSetPropertyInt(
                WMLINK wmlink,          //in: Link to owi interface.
                int iProperty,          //in: Property index OPROP_...
                 int *iReturn);         // @b30988 

extern LONG owiRegisterDropTarget(                                  // @pr21
                WMLINK wmlink,          //in: Link to owi interface.
                HWND hwnd,              //in: Window handle
                BOOL bWantDragOver);    //in: OREQ_DRAGOVER

extern LONG owiStartDrag(
                WMLINK wmlink,          //in: Link to owi interface.
                char *pszDragValue,     //in: Value of the dragged item
                char *pszDragFormat);   //in: Drag formats list

/*@pr46*/
extern LONG owiUnicodeStartDrag(
                WMLINK wmlink,          //in: Link to owi interface.
                UTF16 *pszDragValue,     //in: Value of the dragged item
                UTF16 *pszDragFormat);   //in: Drag formats list


/* @pr22 Widget events */

extern LONG owiWidgetEvent(
                WMLINK wmlink,          //in: Link to owi interface.
                char *pszEventName,     //in: Event name (max 32 characters)
                char cEventType,        //in: 'A' or 'S' (A/Synchronous)
                int nArguments,         //in: Number of arguments
                short *pTypes,          //in: Array of argument types (OTYP_STR only now)
                void **pArguments);     //in/out: Array of arguments

/* @pr39 extended entity level triggers */
extern LONG ewiWidgetEvent(
                WMLINK ewmlink,         //in:
                char *pszEventName,     //in: Event name (max 32 characters)
                char cEventType,        //in: 'A' or 'S' (A/Synchronous)
                int nArguments,         //in: Number of arguments
                short *pTypes,          //in: Array of argument types (OTYP_STR only now)
                void **pArguments);     //in/out: Array of arguments

/* @pr24 */
extern long owiProcFunc(
                WMLINK wmlink,          //in: Link to owi interface.
                char *pszFunc,          //in: Null terminating string containing token to examine.
                int   iType);           //in: Token type, KEYWORD=0,FUNCTION=1,REGISTER=2.

extern long owiRegisterDialog(
                WMLINK wmlink,          //in: Link to owi interface.
                HWND hWndDialog);       //in: WindowHandle of the dialog to be registered.

extern long owiUnRegisterDialog(
                WMLINK wmlink,          //in: Link to owi interface.
                HWND hWndDialog);       //in: WindowHandle of the dialog to be registered.

/*cr24516 - begin*/
extern long owiRegAccel( WMLINK wmlink, //in: Link to owi interface
                        HWND hWnd);     //in: WindowHandle to be registered

extern long owiUnRegAccel( WMLINK wmlink, //in: Link to owi interface
                          HWND hWnd);     //in: WindowHandle to be un-registered
/*cr24516 - end*/

extern long owiFileBox(
                WMLINK wmlink,          //in: Link to owi interface.
                UTF16 *wszTitle,        //in: Title of filedialog (@b27677)
                char  *pszFilename,     //out: Filename
                int    iLen,            //in: Filename length
                char  *pszFilter,       //in: Filter *.* or *.trx etc
                int    iMode);          //in: 1 = save 0 = load

extern long owiCompleteFunc(
                WMLINK wmlink,          //in: Link to owi interface.
                char *pszFunc,          //in: Null terminating string containing token to examine.
                int   iType,            //in: Token type, KEYWORD=0,FUNCTION=1,REGISTER=2.
                char **pszComp,         //out:Complete token found by kernel.
                void **pvFind);         //in/out: Reference to kernel find structure.



/* @pr24 ends */

extern BOOL     owiLabelLog(WMLINK wmlink, char *pszLabel, int ixOver); // @pr25

extern BOOL     owiUnicodeLabelLog(WMLINK wmlink, UTF16 *pszLabel, int ixOver); /* @pr47 hkr */

extern int      owiRefreshParent(WMLINK wmlink, LPRECT lprUpdate); // @pr26

extern int      owiUpdateParent(WMLINK wmlink, LPRECT lprUpdate); // @b30374 - forces a synch update of the parent area.

extern int      ewiLoadEntityData(WMLINK wmlink, int iScrollPosition); //@pr27

extern int      owiChameleon(WMLINK wmlink, long *pLretColor); //@pr34

/* @pr29 start */

/* Draws a themed surface. */
extern BOOL owiThemedBackground
(
    WMLINK wmlink,        // in : Link to OWI interface.
    HWND hWindow,         // in : Window handle.
    LPCWSTR pszClassList, // in : class name of theme.
    HDC hdc,              // in : device context.
    int iPartId,          // in : themed part.
    int iStateId,         // in : state of themed part.
    RECT *pRect           // in : rect to paint.
);

/* Checks whether we are running in themed mode or not. */
extern BOOL owiIsThemedMode(WMLINK wmlink);
/* @pr29 end */

/* @pr30 start */
extern BOOL owiGetThemePartSize
(
    WMLINK wmlink,
    HWND hWindow,
    LPCWSTR pszClassList,
    HDC hdc,
    int iPartId,
    int iStateId,
    RECT* prc,
    SIZE* psz
);
/* @pr30 end */

/*
** @pr35 - get the application name. Wraps getapplicationname in wmswini.
** Just to stay in synch with the splitterbar history position in the reg.
*/
int owiGetApplName(WMLINK wmlink,char *pszName, int iSize);  // @pr35
long owiGetEntColor(WMLINK wmlink, COLORREF *forcolor, COLORREF *backcolor);            /* @b26669 @b27214*/
/*
** @b29590 owiGetParentColor returns the foreground and background color of the parent widget.
** this can be the entity or the form. The colors can be used in the OATT_FOREGND and OATT_BACKGND messages.
*/
long owiGetParentColor(WMLINK wmlink,
                       long *forcolor,  /* OUT : long color. -1 means no color found */
                       long *backcolor  /* OUT : long color. -1 means no color found */
                       );   /* @29590*/

/*
** @b30080 owiGetParentColorEx returns the foreground and background color of the parent widget.
** this can be the entity or the form. The colors can be used in the OATT_FOREGND and OATT_BACKGND messages.
** The function will always return a valid color in "backcolor" when the forceBackColor parameter is set to true.
** Even when the form or entity has color=NO (-1) the function will return the visible backcolor on screen.
*/
long owiGetParentColorEx(WMLINK wmlink,
                       long *forcolor,  /* OUT : long color. -1 means no color found */
                       long *backcolor, /* OUT : long color. -1 means no color found */
                       BOOL bForceBackColor);   /* @30080*/

/*
** @b30333,@b30248 Loads background, foreground colors in one structure
**
** void *pvColors is a void pointer to a struct named OWIATT_COLORS.
** See owi.h for documentation
*/
long owiGetColors(WMLINK wmlink, void *pvColors);
/*
** @b29994 owiGetPadding returns padding rect from the padding property string.
*/
BOOL owiGetPadding(WMLINK wmlink,
                   char *cPadding,     /* In  : padding string. */
                   RECT *rPaddingRect  /* OUT : padding rect */
                   );   /* @b29994*/

/*----------------------------------[MSAA]-----------------------------------*/
extern BOOL owiGetAccessibilityIni
(
    WMLINK wmlink,
    int *iAccessbilityIni
);    /* @c30170 */

/*@c30648 - made interface accessible for non owiwrap widgets like label*/
extern BOOL owiGetAccessibleNameSeparator
(
    WMLINK wmlink,
    wchar_t *pszName,
    int iMax
);

extern BOOL owiGetObjectAccessName
(
    WMLINK wmlink,
    UTF16 *pszOut,
    int iMaxBytes,
    BOOL l_AddRow
);
/*----------------------------------[MSAA]-----------------------------------*/

/* @pr32 start */
extern BOOL owiDefKeyProc
(
    WMLINK  wmlink,
    HWND    hWindow,
    UINT    uMsg,
    WPARAM  wParam,     /* @b29800 */
    LPARAM  lParam      /* @b29800 */
);
/* @pr32 end */

/* @pr33 start */
extern int owiPopupMenu
(
    WMLINK wmlink,
    HWND   hWindow,
    POINT  ptMenu
);
/* @pr33 end */

/* @pr36 start */
extern int owiTncyWidRect
(
    WMLINK wmlink,
    BOOL   bCanvasOpaque
);
/* @pr36 end */

/* @pr37 start */
extern int owiTncyEntRect
(
    WMLINK wmlink,
    BOOL   bCanvasOpaque
);
/* @pr37 end */

extern WMLINK eGetEWILink           /* @pr38 hkr_QArun start */
(
    HPARENT hWindow,
    int     *pAreaId
);
extern void eGetEWIAreaName
(
    WMLINK  wmlink,
    int     areaId,
    char    *pStr
);
extern void eGetFieldAtPoint
(
    WMLINK  wmlink,
    int     x,
    int     y,
    int     *pFiN,
    long    *pOcN
);
extern int eGetFieldsCount(
    WMLINK  wmlink
);
extern long eGetOccurrencesCount(
    WMLINK  wmlink
);
extern void eGetFieldRect(
    WMLINK  wmlink,
    int     FiN,
    long    OcN,
    RECT    *pRect
);
extern WMLINK eGetFieldLink(
    WMLINK  wmlink,
    int     FiN,
    long    OcN
);
extern BOOL eIsFieldInView(
    WMLINK  fwmlink
);
extern void eBringFieldInView(
    WMLINK  fwmlink
);
extern BOOL eIsFieldVisible(
    WMLINK  fwmlink
);
extern BOOL eIsFieldEnabled(
    WMLINK  fwmlink
);
extern BOOL eSetFocusOnField(
    WMLINK  fwmlink
);
extern HWND eGetEditControlAtFocus(
    WMLINK  wmlink
);                                  /* @pr38 hkr_QArun end */

extern void eGetRowHeaderInfo(      /* @pr40 */
    WMLINK      wmlink,
    long        OcN,
    const UTF16 **ppStr,            /* @c23137 */
    long        *iTopPos,
    long        *iBottomPos
);

extern void eGetColumnHeaderInfo(   /* @pr40 */
    WMLINK      wmlink,
    int         FiN,
    const UTF16 **ppStr,            /* @c23137 */
    long        *iLeftPos,
    long        *iRightPos
);

extern void eGetCornerButtonInfo(   /* @pr40 */
    WMLINK      wmlink,
    const UTF16 **ppStr             /* @c23137 */
);

/* Request for confirming focus gain. -- @pr42  */
extern int owiConfirmFocus(WMLINK wmlink);
/* @pr44  */
extern int owiString2Color(WMLINK wmlink, char *pszColor,unsigned long *ulColor);
extern int owiWString2Color(WMLINK wmlink, UTF16 *pszColor,unsigned long *ulColor);
extern int owiColorIndex2String(WMLINK wmlink,int iType,int iIndex, UTF16 *pszColor,int iLen);

/* Request for retrieving registry state key string. -- @pr45 */
extern int owiGetRegStateKey
(
    WMLINK wmlink,
    char *szRegStateKey,
    int iLength,
    int *iStorageType /*@b30581 - return the type of storage used in parent (component)*/
);
/* @b27300
**
** This service routine gets the layout storage value of the form component.
** Based on
** Window property :"LAYOUTSTORAGE"
** values       : "COMPONENT"| "INSTANCE" | "PROCESS" (= default)
**
** returns:
** KEEPLAYOUT_NONE       0x01     No storage for layout at all. Switched off in ini file.
** KEEPLAYOUT_COMPONENT  0x02     Storage by component name.
** KEEPLAYOUT_INSTANCE   0x04     Storage by instance name.
** KEEPLAYOUT_PROCESS    0x08     Keep only during process
**
*/
extern int owiGetSorageType(WMLINK wmlink);

/* @b29864
**
** This service routine deletes all the layout stored formats from the history
** manager.
**
*/
extern int owiDeleteLayoutOnExit(WMLINK wmlink);

/* @b26236
**
** Request to find out if a certain window message was sent
** in order to obtain a WMLINK out of a Widget.
*/
extern int owiIsWMLinkRequest
(
    WMLINK wmlink,
    UINT uMsg
);

extern int owiAdd2Describe /* @c21961 */
(
    WMLINK wmlink,
    char *szAdd2DescribeID,
    char *szAdd2DescribeIDlist
);

extern int owiCreateShapeFonts /* @e22529 */
(
    WMLINK wmlink,
    char *szName,
    VOIDPTR *ppFontList
);

extern int owiDeleteShapeFonts /* @e22529 */
(
    WMLINK  wmlink,
    VOIDPTR pFontList
);

long owiGetCharHeightByShape  /* @e22529 */
(
    WMLINK wmlink,
    HDC hdc,
    VOIDPTR pShapeFont,
    int iShape
);

long owiGetFaceNameForHandle(WMLINK wmlink, HFONT hFont, wchar_t *wszFaceName, int iBytes); /* @c25034 */


HFONT owiShapeIndexToFont     /* @e22529 */
(
    WMLINK wmlink,
    VOIDPTR pShapeFonts,
    int iShapeIndex
);

/*
** Owi panel functions, allow maintenance of a panel with a given owi widget
*/
extern int owiCreatePanel(WMLINK  m_wmlink,
                          int iItems,               /* Number of items to create on panel               */
                          PANELITEM *panelItems,    /* Array of panel items (button/colorlist/fontlist)*/
                          void **pvPanel);          /* Out - a reference to a panel */


extern int  owiSetSizePosPanel(
                               WMLINK m_wmlink,
                               void *pvPanel,       /* void reference to the created panel (GUI driver owns it )*/
                               int xPos,            /* X-position */
                               int yPos,            /* Y-position */
                               int cx,              /* Height     */
                               int cy,              /* Width      */
                               int iOptions);       /* SWP_NOMOVE or SWP_NOSIZE */

/* @c25293 set Z-order */
extern int  owiSetZorderPanel(
                              WMLINK m_wmlink,
                              void *pvPanel,
                              HWND zOrder);

extern long owiGetPanelSize(                        /* Returns in a long width & height Use HIWORD/LOWORD macros*/
                            WMLINK wmlink,
                            void *pvPanel);

extern int  owiDestroyPanel(                        /* Just destroy panel */
                            WMLINK m_wmlink,
                            void *pvPanel);

extern int owiSetPanelParent(WMLINK m_wmlink,       /* Called from oatt_setparent on a zoom action */
                             void *pvPanel,
                             HWND hNewParent);


extern int owiSetPanelItemValue(WMLINK wmlink,      /* @c23483 */
                         void *pvPanel,             /* void reference to the created panel (GUI driver owns it )*/
                         int  iPanelItemID,         /* Panelitem ID */
                         void *pvNewValue);         /* New Value as UTF16 string and long value's are passed */

extern int owiSetPanelItemState(WMLINK wmlink,      /* @c23483 */
                         void *pvPanel,             /* void reference to the created panel (GUI driver owns it )*/
                         int  iPanelItemID,         /* Panelitem ID */
                         BOOL bChecked);            /* Set button in locked or unlocked state */

#ifdef u_wce    /* @c25517 */
extern int owiDrawClientBG(WMLINK wmlink, HDC hdc);         /* @c25752 */
#endif
extern BOOL owiDisplayCursor(WMLINK m_wmlink,               /* @c25467 */
                             char*  pszCursorName,          /* Reference to the mouse cursor logical name */
                             char*  pszCursorFileName);     /* Reference to the full file name holding the mouse cursor */

/*
** @b28502
** get Face Name, CharSet, Point Size and Attributes of a logical font
*/
int owiSplitFontLine(WMLINK wmlink,
                     const UTF16 *pszLine,          /* IN: logical font name */
                     UTF16 *pszFontFaceName,        /* OUT: font face name e.g. "MS Gothic" */
                     int *iFontCharSet,             /* OUT: charset number e.g. 0 (ANSI), 1 (DEFAULT), 128 (SHIFTJIS) etc. */
                     int *iFontPoint,               /* OUT: point size e.g. 10 (points) */
                     int *iFontAttribute);          /* OUT: font attribute combination of ATT_BOLD, ATT_ITALIC, ATT_UNDERLINE */

/* @c28976 check PFORM->bInSizeMove to see the form is still resizing. */
BOOL owiFormIsSizing(WMLINK wmlink);
/*
** @b29306
** Check whether the LEFT mouse button is down. Takes care of mousebutton swapping and
** and mobile devices with stylus input
*/
BOOL owiIsLeftMouseButtonDown(WMLINK wmlink);
/*
** @b29728
** Check is the gui driver is busy. You need this function for instance in the WM_SETCURSOR.
** check in the message handling first if the gui driver is busy. If the driver is busy
** your function should return false to windows and not overwrite the hourglass set by the gui driver
*/
BOOL owiIsGuiDriverBusy(WMLINK wmlink);

/*
** @b30605
** Get the widget position in the canvas taking the scroll into account.
** For example, when the widget original position is (0,0) and the canvas is scrolled
** one cell up so that the widget is located outside of the canvas, the widget position
** returned by this function will be (0,-yCell).
*/
int owiWidgetScrollPos(WMLINK wmlink, int *wid_x, int *wid_y);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !OWIMSW_H */
