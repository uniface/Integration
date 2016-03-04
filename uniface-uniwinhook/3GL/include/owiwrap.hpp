/* @(#)CONT_ID %fv: owiwrap.hpp-70.1.2:incl:1 % %dc: Fri Aug  7 11:33:43 2015 % (#)@ */

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
050316 b26231    9.1.01  mng Adding string to a comboboc results in
                             addition of several substrings.
050316 b26236    9.1.01  mab New OWI service for obtaining special window
                             message used for resolving WMLINK by
                             automated testing tools.
060215 c23176    9.1.01 jdk  uniCodeStringWidget. Generic string class. Implementated
                             for colorboxwidget
060615 c23683    910102  jdk Colorlist widget show the selection correct.
060829 c23528    910102  hkr Alignment of labels not picked up by Grid Widget
060921 b26669    M441    nk  Form background color for an editbox needed
070814 b27296    N202    jdk Refix b27193 Color properties do not work anymore.(moved REDRAW defines etc to hpp file)
061214 c25403    920101  jya WinCE: Add more OWI widgets
070202 c25467    920101  hkr GUI: Non grid EditBox Changeable Mouse Pointer Implementation.
070214 c25515    920101  hkr GUI: Non grid EditBox Dynamic toolTip Implementation.
070411 c25821    920101  hkr GUI: Non Grid dropdownlist dynamic mouse cursor and dynamic tooltip implementation.
070816 b27289    N202    tsk Font reference counting completely f*cked up
071214 b27412    O102    nk  Inherit Entity Color (ENTCOLOR) does not work for editbox in entity on tabpage.
080701 c26705    9.ajax  tsk RIA: Focus problems with NVU and HTML wizard
101117 b28948    9.5.01  jdk Configurable highlight color for $curocc_video("hlt").
                             Used asn setting $curocc_video_hlt = backcolor=<color> forecolor=<color>
101222 b28992    950101  jya Hebrew Windows: cursor movement by quotation mark behaves incorrectly.
110930 b25147    E101    nhl Repaint problems with attaching grid on forms with splitbars.
120626 c29198    9.6.01  jxa Label attached image position support and Different image size supported.
120420 c29201    960101  jya $fieldhandle implementation, first phase
120419 b29672    960101  ago Windows 64 bits: Port GUI dll's
120814 c29338    960101  jdk HTML Widget: No all widgets show their data when used in a multi
                             occurrence list.
121020 b29795    960101  tsk  tab page widgets are destroyed if their parent is closed
120928 b29801    R131    jxa Labels and fields with no color are printed with a white background.
130226 b30023    x104    tsk Enable Keyboard Translation table on HTML widget
130320 b30053    MX01    jxa Acurate tab height and width are required.
130315 b29994    MX01    jxa Padding is required on button/tabex to make better layout.
130827 b30374    X301    jdk $labelproperties does not refresh the checkboxlabel when it is transparent.
140627 c30170    MX05    jxa MSAA support for the GUI objects general functions, editbox,and windows commandbutton.
141007 c30334    MX05    jya New ini setting 'AccessibleNameSeparator'.
141231 b30625    X602    jya Extended trigger Resized is not fired properly.
150304 c30648    MX06    jdk MSAA, removed all implementation from uOwiObject which is a wrapper class only c30334
150807 c31598    9.7.01  jdk GRID should have a border/frame like the button widget.
date   refnum    version who description
*******************************************************************************/

#ifndef OWIWRAP_HPP
#define OWIWRAP_HPP

#include <windows.h>    /* @pr34 hkr_movingHeaderFile */
#include <owimsw.h>
#include <owi.h>
#include <umsw3gl.h>
#include <set>

#define MAX_FIELDNAME   75                                          /*@pr21*/

#define US_CENTER    254                                            /*@pr27*/
#define US_RIGHT     255                                            /*@pr27*/


// -- Flags - used in m_uFlags member of the base class
// Most widgets use the OWF_* variant. The flags here are taken
// from the editcontrol widget and renamed to SWF_* (StringWidgetFlag).
// In the future the flags in the editcontrol should be changed to SWF and
// the OWF* should be renamed in the sources.
// Reason for SWF i.s.o OWF is to avoid conflicts
#define SWF_MODIFIED       0x000001      // Modified since last new data
#define SWF_MULTILINE      0x000002      // Multiple lines
#define SWF_READONLY       0x000004      // Read only
#define SWF_PASSWORD       0x000008      // Password
#define SWF_3D             0x000010      // 3D look
#define SWF_HSCROLL        0x000020      // Horizontal scrollbar
#define SWF_VSCROLL        0x000040      // Vertical scrollbar
#define SWF_DYNAMIC        0x000080      // Dynamic scrollbar behaviour
#define SWF_HUGE           0x000100      // Private heap for control
#define SWF_ZOOMED         0x000200      // Currently in zoomed state
#define SWF_DETAIL         0x000400      // Map doubleclick to ^DETAIL
#define SWF_AUTOSELECT     0x000800      // Select all on get focus           // @pr10
#define SWF_BORDER         0x001000      // Draw a standard border            // @pr13
#define SWF_DOAUTOSELECT   0x002000      // Process posted autoselect         // @pr25
#define SWF_OVERFLOW       0x004000      // Editbox has been overflown        // @pr35
#define SWF_FLAGAUTOSELECT 0x008000      // Do autoselect on next TakeFocus   // @pr36
#define SWF_PRINTMODE      0x010000      // Widget is a pridget               // @pr55
#define SWF_RTL            0x020000      // Hebrew/Arabic -- RTL flag         // @pr82
#define SWF_NATIVEKEYS     0x040000      // Native keyboard in richedit       // @pr3
#define SWF_RICHEDIT       0x080000      // @pr5 - object type
#define SWF_XAUTOSELECT    0x100000      // @pr6 - add extended autoselect
#define SWF_FFIELDLEFT     0x200000      // @pr16 - field leave flag
#define SWF_UNICODE        0x400000      // UNICODE data ?
// -- RTL flags

// -- Return values used internally @b27296
// -- Used in all widget implementations
#define UWID_RELOAD        0x2000           // attribute change requires reload
#define UWID_RESIZE        0x4000           // attribute change requires resize
#define UWID_REDRAW        0x8000           // attribute change requires redraw


typedef struct owiprint OWIPRINT;
typedef struct owidragover OWIDRAGOVER;                             // @pr22

// ---------------------------------------------------------------------------
// Class Hierarchy
// ---------------------------------------------------------------------------

class uOwiObject;               // wmlink based object
class uWidgetClass;             // class factory
class uUnicodeWidgetClass;      // Unicode class factory
class uWidget;                  // generic widget
class uUnicodeWidget;           // Unicode generic widget
class uBooleanWidget;           // boolean widget
class uNumberWidget;            // integer widget
class uFloatWidget;             // floating pt widget
class uUnicodeFloatWidget;      // @c25403 Unicode floating pt widget
class uDateWidget;              // date/time widget
class uSelectorWidget;          // one-of-n widget
class uUnicodeSelectorWidget;          // one-of-n widget
class uOwiImage;                // glyph, bitmap, metafile
class uPicture;                 // background picture
class uniCodeStringWidget;      // @c23176 - Base for all string based widgets (editbox,richedit,colorbox etc )

/*
** --------------------[MSAA]---------------------------------
** @c30648 forward definition of the uniface accessible object.
** UNIFACE accessible object is not made part of the uwidget class since
** this file is also linked to other dll's which will not support MSAA
** For instance the UOLE.dll etc
*/
#ifndef u_wce
  /* @c30648 MSAA object */
  class UAccessibleObject;
#endif
/*@c30648 ends */

/**
@short Encapsulates WMLINK and OWI services
** @c30648
** ---------------------------------------------------------------------------
** Please do NOT implement code in this wrapper class. It only wraps WMLINK!
** ---------------------------------------------------------------------------
*/
class uOwiObject
{
public:
    uOwiObject(WMLINK wmlink);
    virtual ~uOwiObject() {};                                        // @pr7
    operator WMLINK() const { return m_wmlink;   };                  // @pr14

    BOOL   owiNlsDBCSLead(char cTest) const;                         // @pr14
    char*  owiNlsStrChr(const char *pszStr, char cChar) const;       // @pr14


    static char*  owiNlsStrStr(const char *pszStr, const char *pszSearch);  // @pr14
    /*@pr41*/
    static UTF16*  owiUnicodeNlsStrStr(const UTF16 *pszStr, const UTF16 *pszSearch);

    WMLINK getWMLINK() const { return m_wmlink; }                   /* @pr32 hkr_QArun */

protected:
    WMLINK m_wmlink;                    // ticket to OWI services

protected:
    // Asn settings
    int    oGetCuroccHighlightClrs(long *plForeColor,    /*@b28948 long color def. -1 means off */
                                   long *plBackColor);
    // property access
    int    ocpBool(char* pszProp, int bDefault);
    long   ocpLong(char* pszProp, long lDefault);
    int    ocpBool(char* pszProp, int bDefault, char *pszPropertyString);

    double ocpDouble(char* pszProp, double fDefault);
    int    ocpString(char* pszProp, char* pszOut, int iMax);
    int    ocpString(char* pszProp, char* pszOut, int iMax, char *pszPropertyString);
    int    ocpKeyword(char* pszProp, int iDefault, ...);
    int    ocpFirst(char* pszOut, int iMax);
    int    ocpNext(char* pszOut, int iMax);
    // preference access
    int    opBool(char* pszKey, int bDefault);
    long   opLong(char* pszKey, long lDefault);
    double opDouble(char* pszKey, double fDefault);
    int    opString(char* pszKey, char* pszBuf, int iMax);
    int    opKeyword(char* pszKey, int iDefault, ...);
    int    opPutBool(char* pszKey, int bData);
    int    opPutLong(char* pszKey, long lData);
    int    opPutDouble(char* pszKey, double fData);
    int    opPutString(char* pszKey, char* pszData);
    // data access
    int    odGet(void* pValue, int iMax, int iType);
    int    odGetC(void* pValue, int iMax, int iType);
    int    odPut(void* pValue, int iMax, int iType);
    int    odPutC(void* pValue, int iMax, int iType);
    // label access
    int    olGet(USTR* pszLabel, int iMax);
    int    olGetC(USTR* pszLabel, int iMax);
    int    olPut(USTR* pszLabel);
    int    olPutC(USTR* pszLabel);
    // valrep access
    int    ovrCount();
    int    ovrByIndex(PVR pvr, int iIndex, int iType);
    int    ovrByValue(PVR pvr, void* pValue, int iType);
    int    ovrByRep(PVR pvr, char* pszRep, int iType);
    void   ovrFree(PVR pvr);
    int    ovrPut(PVR pvr);
    int    ovrPutC(PVR pvr);
    int    ovrNext(PVR pvr, void **pvCursor, int iType);  //@pr31
    int    ovrCreate(USTRING *pszValrep);                /* @c23683 */
    // access keys
    int    oxsParse(USTR* pszLabel, POCHR pochr);
    int    oxsAddKey(int iKey, int iScope);
    int    oxsRemoveKey(int iKey, int iScope);
    // miscellaneous
    int    oNotify(int iNotification, int iParam=0);
    long   oQuery(int iQuery, int iParam);
    int    oStrConv(USTR* in, USTR* out, int iMax, int iOptions);
    int    oChrConv(USTR* in, POCHR pout);
    int    oKeyMode(int iMode);
    void   oAttach(int iAttach);
    int    oGetMessage(USTR* key, USTR* out, int iMax);
    void   oMessage(USTR* msg, int iOptions);
    int    oGetObjectName(USTR* name, int iMax);
    int    oGetObjectRowIndex();                                        //@30170
    int    owiIsWMLinkRequest(UINT uMsg);                               //@b26236
    int    ewiGetEntityName(USTR* name, int iMax);                      //@pr29
    int    ewiFormIsPrinting();                                         //@pr35
    int    oGetFormName(USTR* name, int iMax);                          //@pr29

    int    oMessageBox(int iMsg);                                    // @pr13
    // entity level widget services
    int    ewiGetColLabelInfo(USTR *pszLabel, int iMax, int iCol, int* hAlign, int* vAlign);      // @pr26    /* @c23528 */
    void   oGetMetaInfo(POWIGETMETAINFO pMetaInfo);        /* @pr33 hkr_EXTGRID_1 */
    // set the iunknown in the iftab structure
    int    oSetIUnknown(void *pUnkown,char *pszComponent);            // @pr28
    int    oDestroyIUnknown(void);                                    // @pr28
    // Shorthands
    int    RequestFocus();
    int    ValueChanged(BOOL bFire=TRUE);
    int    Detail();
    // Windows specific
    LRESULT   owiDefWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, WNDPROC pfDefWndProc);  /* @b29672 */
    BOOL   owiKeyFilter(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    HFONT  owiCreateFont(char* pszLogicalName, UINT uStyle);
    BOOL   owiResizePage(void);                                      // @pr20
    int    owiRefreshParent(LPRECT lprUpdate);
    int    owiUpdateParent(LPRECT lprUpdate); /*@b30374 - same as owiRefreshParent. But does an synchupdate of the widrect*/
    void   owiDestroyFont(HFONT hFont);
    BOOL   owiDrawText(HDC hdc, char* pszText, HFONT hFont, LPRECT lpr, int hAlign, int vAlign, UINT uFlags);
    BOOL   owiDrawTextEx(HDC hdc, char *pszText, HFONT hFont, LPRECT lpr, int hAlign, int vAlign, UINT uFlags,
                         UINT iFirstLine, UINT iLastline);           // @pr14
    BOOL uOwiObject::owiDefKeyProc(HWND    hWindow, UINT    uMsg,  WPARAM  wParam, LPARAM  lParam);
    /* @pr36
    **
    ** Unicode version of owiDrawTextEX(). This method writes Unicode UTF16 strings
    ** to the given device context.
    */
    BOOL   owiDrawUnicodeTextEx(HDC hdc, UTF16 *pszText, HFONT hFont, LPRECT lpr,
                                int hAlign, int vAlign, UINT uFlags,
                                UINT iFirstLine, UINT iLastline);
#ifndef u_wce
    /*------------------[MSAA] Wrappers------------------------------------------------*/
    BOOL   owiGetAccessibilityIni(int *iAccessbilityIni);               /* @c30170 */
    int    owiGetObjectAccessName(UTF16 *pszOut, int iMax,BOOL l_AddRow); /*@c30648*/
    BOOL   owiGetAccessibleNameSeparator(wchar_t *pszName, int iMax);   /* owi..calls GUI driver @c30648*/
    /*------------------[MSAA] Wrappers ends-------------------------------------------*/
#endif
    /* @pr36
    **
    ** Normal and Double Byte word wrap.
    */
#ifndef u_wce
    char* owiWordWrap
    (
       HDC hDC,
       char *pszText,
       HFONT hFont,
       int cx,
       UINT &iLines
    );
#endif

    /* @pr36
    **
    ** Unicode (UTF16) string word wrapper.
    */
    UTF16* owiUnicodeWordWrap
    (
       HDC hDC,
       UTF16 *pszText,
       HFONT hFont,
       int cx,
       UINT &iLines
    );


    POWIIMG owiGetImage(char cType, void* pData, int cx=0, int cy=0, int nDepth=0, UINT uFlags=OIMG_STDPALETTE);
    /*@pr41*/
    POWIIMG owiUnicodeGetImage(UTF16 cType, void* pData, int cx=0, int cy=0, int nDepth=0, UINT uFlags=OIMG_STDPALETTE);
    BOOL   owiDrawFrameType(HDC hdc, UFRAMETYPE l_FrameType, int l_FrameWidth, long l_FrameColor, RECT l_FrameRect); /*@c31598*/
    BOOL   owiAdjustFrameRect(UFRAMETYPE l_FrameType,int l_FrameWidth,RECT *l_pFrameRect);  /*@c31598*/
    void   owiFreeImage(POWIIMG pImage);
    BOOL   owiDrawImage(HDC hdc, POWIIMG pImage, LPRECT lpr, int hScale, int vScale,
                        int hAlign, int vAlign, int hOffset, int vOffset, UINT uFlags);
    BOOL owiDrawImageLabel(HDC hdc, RECT *rArea, RECT *rAreaLeft, RECT rLabelSize, int iHorzLabelAlignment, int iImagelabelAlign,int iImageSize,
                           POWIIMG pImg, int cxMargin, int cyMargin, UINT uFlags); //@c29198, @c29327, @b30053
    BOOL   owiDrawImageLabelPadding(HDC hdc, RECT *rArea, RECT *rAreaLeft, RECT rLabelSize, int iHorzLabelAlignment, int iImagelabelAlign,
                                    int iImageSize,POWIIMG pImg, RECT rPadding, int iHoriSepMargin, int iVertSepMargin, UINT uFlags); //@b29994
    BOOL   owiSplitText(char *pszRep, char **pszImage, char **pszLabel);  // @c29198
    HWND   owiCreateMDIChild(MDICREATESTRUCT* pMDI);
    void   owiDestroyMDIChild(HWND hWnd);
    long   owiGetState(void);                                        // @pr7
    long   owiNlsStyle(int iStyleRequest);                           // @pr12
    int    owiNlsRichEditLangOptions(HWND hWnd);                     // @b28992
    LPVOID owiGetFocusWid(void);                                     // @pr15
    BOOL   owiSetFocusWid(LPVOID lpWid);                             // @pr15
    LONG   owiSetProperty(int iProperty);                            // @pr22
    LONG   owiSetPropertyInt(int iProperty, int *iReturn);           // @pr22@b30988
    LONG   owiRegisterDropTarget(HWND hwnd, BOOL bWantDropOver);     // @pr22
    LONG   owiStartDrag(char *pszDragValue, char *pszDragFormat);    // @pr22
    /*@pr41*/
    LONG   owiUnicodeStartDrag(UTF16 *pszDragValue, UTF16 *pszDragFormat);


    // Widget events                                                 // @pr24
    LONG   owiWidgetEvent(char *pszEventName,     // in  : Event name (max 32 characters)
                          char cEventType,        // in  : 'A' or 'S' (A/Synchronous)
                          int nArguments,         // in  : Number of arguments
                          short *pTypes,          // in  : Array of argument types (only OTYP_STR now)
                          void **pArguments);     // in/out: Array of arguments
    // Overloaded versions for convenience
    LONG   owiWidgetEvent(char *pszEventName,     // in  : Event name (max 32 characters)
                          char cEventType,        // in  : 'A' or 'S' (A/Synchronous)
                          char *pszArgument1);    // in  : Argument 1 (string)
    LONG   owiWidgetEvent(char *pszEventName,     // in  : Event name (max 32 characters)
                          char cEventType,        // in  : 'A' or 'S' (A/Synchronous)
                          char *pszArgument1,     // in  : Argument 1 (string)
                          char *pszArgument2);    // in  : Argument 2 (string)
    LONG   owiWidgetEvent(char *pszEventName,     // in  : Event name (max 32 characters)
                          char cEventType,        // in  : 'A' or 'S' (A/Synchronous)
                          char *pszArgument1,     // in  : Argument 1 (string)
                          char *pszArgument2,     // in  : Argument 2 (string)
                          char *pszArgument3);    // in  : Argument 3 (string)
    LONG   owiWidgetEvent(char *pszEventName,     // in  : Event name (max 32 characters)
                          char cEventType,        // in  : 'A' or 'S' (A/Synchronous)
                          char *pszArgument1,     // in  : Argument 1 (string)
                          char *pszArgument2,     // in  : Argument 2 (string)
                          char *pszArgument3,     // in  : Argument 3 (string)
                          char *pszArgument4);    // in  : Argument 4 (string)
    int    owiGetApplName(char *pszName, int iSize);  // @pr30
    long   owiGetEntColor(COLORREF *forcolor, COLORREF *backcolor);         /* @b27412 */

    int    ProcStatus(); /*@b26231 */
    BOOL   owiDisplayCursor(char* pszCursorName, char* pszCursorFileName);  /* @c25467 */
    BOOL   owiCreateToolTip(HWND hwnd, char* pszToolTipText);       /* @c25515 */   /* @c25821 */
    BOOL   owiCreateToollTip(HWND hwnd, POWIIMG pImage);            /* @c25515 start */
    BOOL   owiCreateUnicodeToolTip(HWND hwnd, UTF16 * pszToolTipText);                  /* @c25515 start */
    BOOL   owiRemoveToolTip(HWND hwnd);                             /* @c25515 */
};

/**
@short class registration, widget instantiation, request dispatching
*/
class uWidgetClass : public uOwiObject
{
public:

    /* Normal Widget Class constructor (the one used by default). */
    uWidgetClass(char* pszClass, char* pszSuperClass=0);

    virtual ~uWidgetClass() {};                                      // @pr7
    int Request(owirequest& req);

protected:
    int     m_iOpenTally;               // Open/Close tally
    HANCHOR m_hAnchor;                  // global context handle
    char*   m_pszClass;                 // class name. -- @pr36
    char*   m_pszSuperClass;            // superclass name. -- @pr36
    WNDPROC m_pfDefWndProc;             // superclass proc

    char    m_szFieldName[MAX_FIELDNAME]; /*@pr21*/
    virtual uWidget* Instantiate(HCLIENT hClient, WMLINK wmlink) = 0;
    virtual UINT ClassStyle();
    virtual HCURSOR ClassCursor();
    virtual HBRUSH ClassBrush();

    /* @pr36
    **
    ** Widget class registration.
    */
    virtual int RegWindowClass(HINSTANCE hInstance);

    /* @pr36
    **
    ** Widget window creator.
    */
    virtual BOOL CreateWindowObjects(uWidget *pWidget, HPARENT hParent);

    virtual int Open(WMLINK wmlink, HANCHOR hAnchor, HCLIENT& hClient);
    virtual int Close(HCLIENT hClient);
    virtual int GetCaps(int nCaps, POWIATTR pCaps);
    virtual int GetCapability(int id, OWIATTV& d);
    /*@pr21 - added fieldname to create */
    virtual int Create(HCLIENT hClient, WMLINK wmlink, HPARENT hParent, int nAttr, POWIATTR pAttr,char *pszField, HWIDGET& hWidget);
};

// ---------------------------------------------------------------------------
//
// @pr36
//
// ---------------------------------------------------------------------------
/**
@short class registration, widget instantiation, request and dispatching for for Unicode Widgets.
*/
class uUnicodeWidgetClass : public uWidgetClass
{
public:

    /* Unicode Widget class constructor. */
    uUnicodeWidgetClass(UTF16 *pszClass, UTF16 *pszSuperClass=0);

protected:

    UTF16*  m_pszUCClass;               // UTF16 class name.
    UTF16*  m_pszUCSuperClass;          // UTF16 super class name.

    /* Widget class registration. */
    virtual int RegWindowClass(HINSTANCE hInstance);

    /* Widget window creator. */
    virtual BOOL CreateWindowObjects(uWidget *pWidget, HPARENT hParent);

    /* Unicode Widget specific open request handler. */
    virtual int GetCapability(int id, OWIATTV& d);
};

/* @b27289 New class */
/**
@short an OWI object that has a visual representation

An OWI object that has a visual representation
Serves as base class for light-weight visual objects such as fields in an
entity-level widget, and for full-blown visual objects such as widgets.

Please keep this class light-weight!
*/

class uVisualOwiObject : public uOwiObject
{
private:
    typedef uOwiObject Base;
public:

    uVisualOwiObject(WMLINK wmlink);
    virtual ~uVisualOwiObject();

    BOOL  SetFont(HFONT hFont) { return (BOOL)(m_hFont = hFont); }
    HFONT GetFont() { return m_hFont; }

    virtual int SetAttr(int nAttr, POWIATTR pAttr);
    virtual int GetAttr(int nAttr, POWIATTR pAttr);

    virtual int SetAttribute(int id, OWIATTV d);
    virtual int GetAttribute(int id, OWIATTV& d);

    long     m_clrFore;                 /**< foreground color ( Signed ) */
    long     m_clrBack;                 /**< background color ( Signed ) */
    long     m_clrXparent;              /**< various colors @pr6 ( Signed ) */
    long     m_clrXParentForeColor;     /**< parent foreground color> cr29446 - we need an OATT_XFOREPARENT msg @c29446 */
    long     m_clrBackProperty;         /**< Background color set by backcolor property ( Signed ) */
    long     m_clrForeProperty;         /**< Foreround color set by forecolor property ( Signed ) */
    long     m_clrBackSystem;           /**< System background implemented by the specific widgets (Signed) */
    long     m_clrForeSystem;           /**< System foreground implemented by the specific widgets (Signed) */
    long     m_clrBackIndex;            /* @b30297 index background color by the specific widgets */
    long     m_clrForeIndex;            /* @b30297 index foreground color by the specific widgets */
#ifndef u_wce
    /* defined in uVisualOwiObject wchar_t    *m_cAccessName;@c30648 MSAA Label Accessname */
    UAccessibleObject *m_pAccessibleObject;
    wchar_t  *m_cAccessName;            /* @30170 */
#endif

    /*@b28948 - following attributes are influenced by the ASN setting
    **$curocc_video_hlt = [ backcolor=<colordefinition> forecolor=<colordefinition> ] which on its
    ** turn defines the HLT color in the 4GL statement $curoccvideo(<entity>)="hlt"
    ** Static - all widgets share these value's
    */
    BOOL            m_bHighlight;        /* @b28948 - moved to base class. Field uses MS-Windows highlight colors. -- @pr47 */

    static long     m_clrForeOccHighlight;     /** -1 by def. Otherwise set by ASN file setting $curocc_video_hlt */
    static long     m_clrBackOccHighlight;     /** -1 by def. Otherwise set by ASN file setting $curocc_video_hlt */
    /* @b28948 ends */

    static BOOL     m_bTransparentColorNo;     /* @b29801 */
    static int      m_iAccessibilityIni;       /* @c30170 */

    HBRUSH   m_hbrBack;                 /**< background brush */

private:
    HFONT    m_hFont;                   /**< font for printing (widget is responsible) */

protected:
    /* @b30297 - the following function is implemented for applying the inheritcolors property on
    ** the necessary widgets. It is called during the erase background and influence paint function.
    ** That's also why it is named PaintInhericolors.
    ** The input variable bForceColor means whether force the parent to use system color. If true,
    ** anyway the parent will return a color. If false, the parent might have -1 returned.
    */
    BOOL  PaintInheritcolors(BOOL bForceColor);
};

/**
@short an OWI widget
*/
class uWidget: public uVisualOwiObject
{
private:
    typedef uVisualOwiObject Base;
public:
    /* Normal Widget instance constructor. */
    uWidget(HCLIENT hClient, HANCHOR hAnchor, WMLINK wmlink);

    virtual ~uWidget();

    virtual void AttachWnd(HWND hwnd);
    virtual HWND DetachWnd();
    virtual int Create(HPARENT hParent, const char* pszClass, WNDPROC pfDefWndProc);
    /* @b29795 */
    virtual int BeforeDestroy();
    virtual int Destroy();
    virtual int PresetAttr(int nAttr, POWIATTR pAttr);
    virtual int SetAttr(int nAttr, POWIATTR pAttr);

    virtual int Command(int id, int iParam);
    // Printing
    virtual long CalcPrintDepth(int iType);
    virtual long Print(OWIPRINT &);
    BOOL         IsPrinting();
    BOOL         IsPrinting(POWIATTR pAttr, int nAttr);
    void         setPrinting( BOOL bPrinting = TRUE );              /*@pr21*/
    HWND         GetWindowHandle( void ){ return m_hwnd; }          /*@c29338*/
    // Drag-n-Drop
    virtual int  DragOver(OWIDRAGOVER &);                           // @pr22
    virtual int  SelectDropTarget(BOOL bSelect);                    // @pr23
    virtual BOOL IsWidgetVisible() {return IsWindowVisible(m_hwnd);}    /* @pr37 */
    virtual int  CallWidgetOperation(char *OperationName, VOIDPTR pPrmBlock);    /* @c29201 */

protected:
    virtual LONG WindowStyle();
    virtual DWORD WindowExStyle();
    virtual int PresetAttribute(int id, OWIATTV d);
    virtual int SetAttribute(int id, OWIATTV d);
    virtual int GetAttribute(int id, OWIATTV& d);
    virtual int NewData();
    virtual int PutData();
    virtual int NewValRep();
    virtual int NewProps();
    virtual int NewLabel();
    virtual int GetFocus();
    virtual int TakeFocus();
    virtual int LoseFocus();
    virtual int FieldLeft();                                /* @pr38 */
    virtual int Function(int iFunction);
    virtual int SetupChange(int iParam);
    virtual int LabelClicked();
    virtual int ShowAccessKey(int iKey);
    virtual int HideAccessKey(int iKey);
    virtual int DoAccessKey(int iKey);
    virtual int PaletteChanged();
    virtual void Refresh();
    virtual int IsWidgetKey(LPMSG pMsg);                              //@pr18
    virtual int CheckFocus();               /** return SUCCESS if parent form does not need to be raised *//* @c26705 */
    virtual int EndUpdate();                                         /* @b30625 */

    // Windows specific
    LRESULT DefWndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);                                /* @b29672 */
    BOOL KeyFilter(UINT uMsg, WPARAM wParam, LPARAM lParam);
    // Message handlers
    virtual HBRUSH OnCtlColor(HDC hdc, HWND hwndChild, int type);

    // -- Keyboard translation table support (generic Function() stuff)

    void DisplayFunctionChar(HWND a_hwnd, WNDPROC pfEditProc, int iFunction); // @pr15
    virtual void DisplayProfileChar(HWND hWnd, WNDPROC pfEditProc, int iProfile, int iChar, UTF16 UnicodeProfileEsc);
    int Function2Profile(int iFunction);

    virtual void SendChar(HWND a_hwnd, WNDPROC pfEditProc, int iChar);
protected:
    friend LRESULT XCALLBACK WidgetWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam); /* @b29672 */
    virtual LRESULT WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);                           /* @b29672 */
    static uWidget* DerefWnd(HWND hwnd);

protected:
    int    NewProps(unsigned long *ulAction);


protected:
    HWND     m_hwnd;                    // window handle
    WNDPROC  m_pfDefWndProc;            // superclass proc
    long     m_clrBackPrinting;         // Printing background implemented by the specific widgets (Signed)
    long     m_clrForePrinting;         // Printing foreground implemented by the specific widgets (Signed)
    HWND     m_hwndZoom;                // zoom window, if zoomed
    enum {CALC_DEPTH, CALC_MINDEPTH};
    HDC      m_hdcPrint;                // print dc
    BOOL     m_IsPrinting;              // print flag: TRUE->print widget
    int      m_iPrintWidth;             // @pr8
    int      m_iPrintHeight;            // @pr8
    int      m_iAttach;                 // @pr19
    long     m_lPropertyAction;         // result of prop change REDRAW etc.
    BOOL     m_bDimmBackGround;         // @pr38 dimmed background color (TRUE)| FALSE
    DWORD    m_uFlags;                  // Flags (OWF_*)              @c22921 - made general
    BOOL     m_bCreatedbyGfp;           // Is widget created by GFP?? @c22921 - Set by OATT_GFP
};

/*---------------------------------------------------------------------------*/
// @c29198 - attached image relative to label alignment
typedef enum
{
    imagelabel_left,  // default
    imagelabel_right,
    imagelabel_top,
    imagelabel_bottom,
    imagelabel_lefttop,
    imagelabel_leftbottom,
    imagelabel_righttop,
    imagelabel_rightbottom
}IMAGELABELALIGN;
// ---------------------------------------------------------------------------
//
// @pr36
//
// uUnicodeWidget - an Unicode OWI widget
// ---------------------------------------------------------------------------
class uUnicodeWidget: public uWidget
{
private:
    typedef uWidget Base;
public:
    /* Unicode specific window attachment method. */
    virtual void AttachWnd(HWND hwnd);
    virtual HWND DetachWnd();

    /* Constructor. */
    uUnicodeWidget(HCLIENT hClient, HANCHOR hAnchor, WMLINK wmlink);

    /* Creation method specially for Unicode Widgets. */
    virtual int Create(HPARENT hParent, const UTF16* pszClass, WNDPROC pfDefWndProc);
};
// ---------------------------------------------------------------------------
// uniCodeStringWidget - an Unicode OWI widget for string handling @c23176
// ---------------------------------------------------------------------------
class uniCodeStringWidget: public  uUnicodeWidget
{
public:
    /* Constructor. */
    uniCodeStringWidget(HCLIENT hClient, HANCHOR hAnchor, WMLINK wmlink);
    virtual ~uniCodeStringWidget();
    // Printing
    virtual long CalcPrintDepth(int iType);
    virtual long Print(OWIPRINT &);

private:
    void * retrieveStringData( void );
    int  PutStringData(char *szEdit,int iNumChars,int iProfEsc );
    void changeUnicodeChars(UTF16* pszText, UTF16 ch);

protected:
    static   int m_iProfEsc;              // Static - one profesc char definition for all instances of this class.
    int      m_iNoDisplay;                // Character to use for nodisplay (password) mode. Inherited widget should fill this one in.
    int      m_iNumLines;                 // # of lines in the (ML) editbox
                                          // SWF_UNICODE in the m_uFlags defined how data should be loaded from kernel
                                          // if m_uFlags == SWF_UNICODE data will end in m_pszUniCodeData on a newdata()
                                          // otherwise data will be moved to m_pszData.
    UTF16*   m_pszUniCodeData;            // Unicode string data
    char *   m_pszData;                   // Code page string data

    virtual int NewData();
    virtual int PutData();
};
// ---------------------------------------------------------------------------
// uBooleanWidget - a boolean widget
// ---------------------------------------------------------------------------

class uBooleanWidget: public uWidget
{
public:
    uBooleanWidget(HANCHOR hAnchor, HCLIENT hClient, WMLINK wmlink);

protected:
    BOOL   m_bNull;                     // value is null
    UBOOL  m_bValue;                    // boolean value

    virtual int NewData();
    virtual int PutData();
};

// ---------------------------------------------------------------------------
// uNumberWidget - an integer number widget
// ---------------------------------------------------------------------------

class uNumberWidget: public uWidget
{
public:
    uNumberWidget(HANCHOR hAnchor, HCLIENT hClient, WMLINK wmlink);

protected:
    BOOL    m_bNull;                    // value is null
    UNUMBER m_nValue;                   // integer value

    virtual int NewData();
    virtual int PutData();
};

// ---------------------------------------------------------------------------
// uFloatWidget - a floating point widget
// ---------------------------------------------------------------------------

class uFloatWidget: public uWidget
{
public:
    uFloatWidget(HANCHOR hAnchor, HCLIENT hClient, WMLINK wmlink);

protected:
    BOOL   m_bNull;                     // value is null
    UFLOAT m_fValue;                    // floating point value

    virtual int NewData();
    virtual int PutData();
};

// @c25403
// ---------------------------------------------------------------------------
// uUnicodeFloatWidget - a floating point widget (unicode version)
// ---------------------------------------------------------------------------

class uUnicodeFloatWidget: public uUnicodeWidget
{
public:
    uUnicodeFloatWidget(HANCHOR hAnchor, HCLIENT hClient, WMLINK wmlink);

protected:
    BOOL   m_bNull;                     // value is null
    UFLOAT m_fValue;                    // floating point value

    virtual int NewData();
    virtual int PutData();
};

// ---------------------------------------------------------------------------
// uDateWidget - a date widget
// ---------------------------------------------------------------------------

class uDateWidget: public uWidget
{
public:
    uDateWidget(HANCHOR hAnchor, HCLIENT hClient, WMLINK wmlink);

protected:
    BOOL     m_bNull;                     // value is null
    UNIDATE  m_dValue;                    // date value ,@pr11

    virtual int NewData();
    virtual int PutData();
};

// ---------------------------------------------------------------------------
// uSelectorWidget - a "one of n" selector widget
// ---------------------------------------------------------------------------

class uSelectorWidget: public uWidget
{
public:
    uSelectorWidget(HANCHOR hAnchor, HCLIENT hClient, WMLINK wmlink);

protected:
    int    m_iIndex;                    // selection (-1 if none)
    int    m_iDataType;                 // datatype

    virtual int NewData();              // @pr17
    virtual int PutData();              // @pr17

    virtual int PresetAttribute(int id, OWIATTV d);
};

class uUnicodeSelectorWidget: public uUnicodeWidget /*@pr42*/
{
public:
    uUnicodeSelectorWidget(HANCHOR hAnchor, HCLIENT hClient, WMLINK wmlink);

protected:
    int    m_iIndex;                    // selection (-1 if none)
    int    m_iDataType;                 // datatype

    virtual int NewData();              // @pr17
    virtual int PutData();              // @pr17

    virtual int PresetAttribute(int id, OWIATTV d);
};

// ---------------------------------------------------------------------------
// uOwiImage - glyph, bitmap, metafile, etc
// ---------------------------------------------------------------------------

class uOwiImage : public uOwiObject
{
public:
    uOwiImage(WMLINK wmlink, char* pszImage=0, int cx=0, int cy=0);
    virtual ~uOwiImage();

    virtual void SetSize(int cx, int cy);
    virtual void SetScroll(int hOffset, int vOffset);
    virtual void SetCache(BOOL bCache);
    virtual void SetIsotropic(BOOL bIsotropic);
    virtual void SetStdPalette(BOOL bStdPalette);
    virtual void SetColorize(BOOL bColorize);
    virtual void SetAlignment(int hAlign, int vAlign);
    virtual void SetScale(int hScale, int vScale);

    virtual int Load(char* pszData, char cType=0);
    virtual int Load(USTR* pszData, char cType=0);
    virtual int Load(UNATIVE uData, char cType=0);

    virtual HPALETTE GetPalette();
    virtual RECT GetRect(RECT& r);
    virtual void Draw(HDC hdc, RECT& r, unsigned uFlags=0);

protected:
    virtual int LoadImage();

protected:
    POWIIMG m_pImage;                   // OWI image structure
    char*   m_pData;                    // image filename/glyphname/blob
    char    m_cType;                    // image type
    // options
    int     m_cx;                       // optimal width
    int     m_cy;                       // optimal height
    int     m_hOffset;                  // horizontal scrolling offset
    int     m_vOffset;                  // vertical scrolling offset
    BOOL    m_bCache:1;                 // cache metafiles on bitmap
    BOOL    m_bNative:1;                // m_pszImage is UNATIVE
    // properties
    BOOL    m_bIsotropic:1;             // preserve aspect ratio
    BOOL    m_bStdPalette:1;            // force use of standard palette
    BOOL    m_bColorize:1;              // colorize monochrome
    int     m_hAlign:2;                 // horizontal alignment
    int     m_vAlign:2;                 // vertical alignment
    int     m_hScale;                   // horizontal scaling
    int     m_vScale;                   // vertical scaling
};

// ---------------------------------------------------------------------------
// uPicture - widget background picture
// ---------------------------------------------------------------------------

class uPicture : public uOwiImage
{
public:
    uPicture(WMLINK wmlink, HWND hwnd=NULL, RECT* prc=NULL);
    virtual ~uPicture();

    virtual void AttachWnd(HWND hwnd);
    virtual HWND DetachWnd();

    virtual void SetRect(RECT* prc=NULL);
    virtual RECT GetRect();
    virtual void SetAutoGray(BOOL bGray);
    virtual void Invalidate(BOOL bErase=FALSE);
    virtual void Paint(HDC hdcPaint=NULL, unsigned uFlags=0);
    virtual POINT PhysicalPt(float x, float y);
    virtual void LogicalPt(POINT pt, float& x, float& y);
    virtual BOOL NewProps();

protected:
    virtual int LoadImage();
    virtual BOOL OnEraseBkgnd(HDC hdc);
    virtual void OnPaint();
    virtual void OnSize(UINT state, int cx, int cy);
    virtual void OnEnable(BOOL fEnable);
    virtual void OnDestroy();

protected:
    friend LONG XCALLBACK PictureWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    virtual LONG WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
    static uPicture* DerefWnd(HWND hwnd);

protected:
    HWND    m_hwnd;                     // window to draw picture in
    WNDPROC m_pfDefWndProc;             // previous window proc
    RECT    m_rFormat;                  // area to draw picture in
    RECT    m_rPicture;                 // area where picture actually appears
    BOOL    m_bAutoFormat:1;            // automatically size to full window
    BOOL    m_bAutoGray:1;              // gray when window disabled
};

namespace owi
{

/* @b30023 Factored out from OCX container to allow unified handling of UnifaceKeys propery */
/**
@brief A set of key definitions that a keystroke can be matched against.
*/
class KeySet
{
private:
    /**
    Array that maps string representation of key to virtual key code
    */
    static const struct _keys     /* @b29520 */
    {
        const char  *pszKey;
        WORD  wVirtKey;
    } g_keys[];

    bool m_wantTab;     /**< TRUE if the TAB key is wanted by the widget, and should not be nmatched in the keyset */
    bool m_defaultKeys; /**< TRUE if a default set of keys must be mapped:
                                ctrl-a through ctrl-z, function keys, escape key, tab key (depending on m_wantTab), with or without ALT/SHIFT
                        */

    std::set<WORD> m_keys;  /**< The set of keys */
    /**
    Find a key in the set of explicit keys (not taking m_defaultKeys into account)
    */
    bool FindUnifaceKey(WPARAM wParam, LPARAM lParam);
    /**
    Parse a string of the form [(alt|ctrl|shift)+]<character>, create a key code from it
    */
    WORD GetVirtKeyFromString(char* pszString);

public:
    /**
    @brief Construct an empty key set
    */
    KeySet();

    /**
    @brief tell the set not to match the TAB; we want it ourselves
    */
    void WantTab(bool a_wantTab);
    /**
    @brief parse a Uniface list containing key definitions of the form [(alt|ctrl|shift)+]<character>

    Sets the KeySet to contain (only) the keys defined by the a_keyset parameter

    @remark side effect: 'keyset' parameter is modified!
    */
    void Parse(char* a_keyset);

    /**
    @brief Match a windows key event to a key in the keyset, taking m_defaultKeys into account

    @retval true
        the key was found in the keyset
    */
    bool Match(UINT uMsg, WPARAM wParam, LPARAM lParam);

    /**
    @brief Translate a virtual key code to a string representation

    e.g. 'ESC' or 'PGDN'
    */
    static std::string KeyToString(WPARAM wParam);
};

}
//---------------------------------------------------------------------------
// windowsx.h like message cracker macros
//---------------------------------------------------------------------------

#define DISPATCH_MSG(message, fn)    \
    case (message): return DISPATCH_##message((wParam), (lParam), (fn))

/* void Cls:OnCompacting(UINT compactRatio) */
#define DISPATCH_WM_COMPACTING(wParam, lParam, fn) \
    ((fn)((UINT)(wParam)), 0L)
#define DELEGATE_WM_COMPACTING(compactRatio, fn) \
    (void)(fn)(WM_COMPACTING, (WPARAM)(UINT)(compactRatio), 0L)

/* void Cls:OnWinIniChange(LPCTSTR lpszSectionName) */
#define DISPATCH_WM_WININICHANGE(wParam, lParam, fn) \
    ((fn)((LPCTSTR)(lParam)), 0L)
#define DELEGATE_WM_WININICHANGE(lpszSectionName, fn) \
    (void)(fn)(WM_WININICHANGE, 0L, (LPARAM)(LPCTSTR)(lpszSectionName))

/* void Cls:OnSysColorChange() */
#define DISPATCH_WM_SYSCOLORCHANGE(wParam, lParam, fn) \
    ((fn)(), 0L, 0L)
#define DELEGATE_WM_SYSCOLORCHANGE(fn) \
    (void)(fn)(WM_SYSCOLORCHANGE, 0L, 0L)

/* BOOL Cls:OnQueryNewPalette() */
#define DISPATCH_WM_QUERYNEWPALETTE(wParam, lParam, fn) \
    MAKELRESULT((BOOL)(fn)(), 0L)
#define DELEGATE_WM_QUERYNEWPALETTE(fn) \
    (BOOL)(DWORD)(fn)(WM_QUERYNEWPALETTE, 0L, 0L)

/* void Cls:OnPaletteIsChanging(HWND hwndPaletteChange) */
#define DISPATCH_WM_PALETTEISCHANGING(wParam, lParam, fn) \
    ((fn)((HWND)(wParam)), 0L)
#define DELEGATE_WM_PALETTEISCHANGING(hwndPaletteChange, fn) \
    (void)(fn)(WM_PALETTEISCHANGING, (WPARAM)(HWND)(hwndPaletteChange), 0L)

/* void Cls:OnPaletteChanged(PaletteChange) */
#define DISPATCH_WM_PALETTECHANGED(wParam, lParam, fn) \
    ((fn)((HWND)(wParam)), 0L)
#define DELEGATE_WM_PALETTECHANGED(hwndPaletteChange, fn) \
    (void)(fn)(WM_PALETTECHANGED, (WPARAM)(HWND)(hwndPaletteChange), 0L)

/* void Cls:OnFontChange() */
#define DISPATCH_WM_FONTCHANGE(wParam, lParam, fn) \
    ((fn)(), 0L)
#define DELEGATE_WM_FONTCHANGE(fn) \
    (void)(fn)(WM_FONTCHANGE, 0L, 0L)

/* void Cls:OnSpoolerStatus(UINT status, int cJobInQueue) */
#define DISPATCH_WM_SPOOLERSTATUS(wParam, lParam, fn) \
    ((fn)((UINT)(wParam), (int)(short)LOWORD(lParam)), 0L)
#define DELEGATE_WM_SPOOLERSTATUS(status, cJobInQueue, fn) \
    (void)(fn)(WM_SPOOLERSTATUS, (WPARAM)(status), MAKELPARAM((cJobInQueue), 0))

/* void Cls:OnDevModeChange(LPCTSTR lpszDeviceName) */
#define DISPATCH_WM_DEVMODECHANGE(wParam, lParam, fn) \
    ((fn)((LPCTSTR)(lParam)), 0L)
#define DELEGATE_WM_DEVMODECHANGE(lpszDeviceName, fn) \
    (void)(fn)(WM_DEVMODECHANGE, 0L, (LPARAM)(LPCTSTR)(lpszDeviceName))

/* void Cls:OnTimeChange() */
#define DISPATCH_WM_TIMECHANGE(wParam, lParam, fn) \
    ((fn)(), 0L)
#define DELEGATE_WM_TIMECHANGE(fn) \
    (void)(fn)(WM_TIMECHANGE, 0L, 0L)

/* void Cls:OnPower(int code) */
#define DISPATCH_WM_POWER(wParam, lParam, fn) \
    ((fn)((int)(wParam)), 0L)
#define DELEGATE_WM_POWER(code, fn) \
    (void)(fn)(WM_POWER, (WPARAM)(int)(code), 0L)

/* BOOL Cls:OnQueryEndSession() */
#define DISPATCH_WM_QUERYENDSESSION(wParam, lParam, fn) \
    MAKELRESULT((BOOL)(fn)(), 0L)
#define DELEGATE_WM_QUERYENDSESSION(fn) \
    (BOOL)(DWORD)(fn)(WM_QUERYENDSESSION, 0L, 0L)

/* void Cls:OnEndSession(BOOL fEnding) */
#define DISPATCH_WM_ENDSESSION(wParam, lParam, fn) \
    ((fn)((BOOL)(wParam)), 0L)
#define DELEGATE_WM_ENDSESSION(fEnding, fn) \
    (void)(fn)(WM_ENDSESSION, (WPARAM)(BOOL)(fEnding), 0L)

/* void Cls:OnQuit(int exitCode) */
#define DISPATCH_WM_QUIT(wParam, lParam, fn) \
    ((fn)((int)(wParam)), 0L)
#define DELEGATE_WM_QUIT(exitCode, fn) \
    (void)(fn)(WM_QUIT, (WPARAM)(exitCode), 0L)

/* This message is in Windows 3.1 only */
/* void Cls:OnSystemError(int errCode) */
#define DISPATCH_WM_SYSTEMERROR(wParam, lParam, fn) 0L
#define DELEGATE_WM_SYSTEMERROR(errCode, fn) 0L

/* BOOL Cls:OnCreate(LPCREATESTRUCT lpCreateStruct) */
#define DISPATCH_WM_CREATE(wParam, lParam, fn) \
    ((fn)((LPCREATESTRUCT)(lParam)) ? 0L : (LRESULT)-1L)
#define DELEGATE_WM_CREATE(lpCreateStruct, fn) \
    (BOOL)(DWORD)(fn)(WM_CREATE, 0L, (LPARAM)(LPCREATESTRUCT)(lpCreateStruct))

/* BOOL Cls:OnNCCreate(LPCREATESTRUCT lpCreateStruct) */
#define DISPATCH_WM_NCCREATE(wParam, lParam, fn) \
    (LRESULT)(DWORD)(BOOL)(fn)((LPCREATESTRUCT)(lParam))
#define DELEGATE_WM_NCCREATE(lpCreateStruct, fn) \
    (BOOL)(DWORD)(fn)(WM_NCCREATE, 0L, (LPARAM)(LPCREATESTRUCT)(lpCreateStruct))

/* void Cls:OnDestroy() */
#define DISPATCH_WM_DESTROY(wParam, lParam, fn) \
    ((fn)(), 0L)
#define DELEGATE_WM_DESTROY(fn) \
    (void)(fn)(WM_DESTROY, 0L, 0L)

/* void Cls:OnNCDestroy() */
#define DISPATCH_WM_NCDESTROY(wParam, lParam, fn) \
    ((fn)(), 0L)
#define DELEGATE_WM_NCDESTROY(fn) \
    (void)(fn)(WM_NCDESTROY, 0L, 0L)

/* void Cls:OnShowWindow(BOOL fShow, UINT status) */
#define DISPATCH_WM_SHOWWINDOW(wParam, lParam, fn) \
    ((fn)((BOOL)(wParam), (UINT)(lParam)), 0L)
#define DELEGATE_WM_SHOWWINDOW(fShow, status, fn) \
    (void)(fn)(WM_SHOWWINDOW, (WPARAM)(BOOL)(fShow), (LPARAM)(UINT)(status))

/* void Cls:OnSetRedraw(BOOL fRedraw) */
#define DISPATCH_WM_SETREDRAW(wParam, lParam, fn) \
    ((fn)((BOOL)(wParam)), 0L)
#define DELEGATE_WM_SETREDRAW(fRedraw, fn) \
    (void)(fn)(WM_SETREDRAW, (WPARAM)(BOOL)(fRedraw), 0L)

/* void Cls:OnEnable(BOOL fEnable) */
#define DISPATCH_WM_ENABLE(wParam, lParam, fn) \
    ((fn)((BOOL)(wParam)), 0L)
#define DELEGATE_WM_ENABLE(fEnable, fn) \
    (void)(fn)(WM_ENABLE, (WPARAM)(BOOL)(fEnable), 0L)

/* void Cls:OnSetText(LPCTSTR lpszText) */
#define DISPATCH_WM_SETTEXT(wParam, lParam, fn) \
    ((fn)((LPCTSTR)(lParam)), 0L)
#define DELEGATE_WM_SETTEXT(lpszText, fn) \
    (void)(fn)(WM_SETTEXT, 0L, (LPARAM)(LPCTSTR)(lpszText))

/* INT Cls:OnGetText(int cchTextMax, LPTSTR lpszText) */
#define DISPATCH_WM_GETTEXT(wParam, lParam, fn) \
    (LRESULT)(DWORD)(int)(fn)((int)(wParam), (LPTSTR)(lParam))
#define DELEGATE_WM_GETTEXT(cchTextMax, lpszText, fn) \
    (int)(DWORD)(fn)(WM_GETTEXT, (WPARAM)(int)(cchTextMax), (LPARAM)(LPTSTR)(lpszText))

/* INT Cls:OnGetTextLength() */
#define DISPATCH_WM_GETTEXTLENGTH(wParam, lParam, fn) \
    (LRESULT)(DWORD)(int)(fn)()
#define DELEGATE_WM_GETTEXTLENGTH(fn) \
    (int)(DWORD)(fn)(WM_GETTEXTLENGTH, 0L, 0L)

/* BOOL Cls:OnWindowPosChanging(LPWINDOWPOS lpwpos) */
#define DISPATCH_WM_WINDOWPOSCHANGING(wParam, lParam, fn) \
    (LRESULT)(DWORD)(BOOL)(fn)((LPWINDOWPOS)(lParam))
#define DELEGATE_WM_WINDOWPOSCHANGING(lpwpos, fn) \
    (BOOL)(DWORD)(fn)(WM_WINDOWPOSCHANGING, 0L, (LPARAM)(LPWINDOWPOS)(lpwpos))

/* void Cls:OnWindowPosChanged(const LPWINDOWPOS lpwpos) */
#define DISPATCH_WM_WINDOWPOSCHANGED(wParam, lParam, fn) \
    ((fn)((const LPWINDOWPOS)(lParam)), 0L)
#define DELEGATE_WM_WINDOWPOSCHANGED(lpwpos, fn) \
    (void)(fn)(WM_WINDOWPOSCHANGED, 0L, (LPARAM)(const LPWINDOWPOS)(lpwpos))

/* void Cls:OnMove(int x, int y) */
#define DISPATCH_WM_MOVE(wParam, lParam, fn) \
    ((fn)((int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam)), 0L)
#define DELEGATE_WM_MOVE(x, y, fn) \
    (void)(fn)(WM_MOVE, 0L, MAKELPARAM((x), (y)))

/* void Cls:OnSize(UINT state, int cx, int cy) */
#define DISPATCH_WM_SIZE(wParam, lParam, fn) \
    ((fn)((UINT)(wParam), (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam)), 0L)
#define DELEGATE_WM_SIZE(state, cx, cy, fn) \
    (void)(fn)(WM_SIZE, (WPARAM)(UINT)(state), MAKELPARAM((cx), (cy)))

/* void Cls:OnClose() */
#define DISPATCH_WM_CLOSE(wParam, lParam, fn) \
    ((fn)(), 0L)
#define DELEGATE_WM_CLOSE(fn) \
    (void)(fn)(WM_CLOSE, 0L, 0L)

/* BOOL Cls:OnQueryOpen() */
#define DISPATCH_WM_QUERYOPEN(wParam, lParam, fn) \
    MAKELRESULT((BOOL)(fn)(), 0L)
#define DELEGATE_WM_QUERYOPEN(fn) \
    (BOOL)(DWORD)(fn)(WM_QUERYOPEN, 0L, 0L)

/* void Cls:OnGetMinMaxInfo(LPMINMAXINFO lpMinMaxInfo) */
#define DISPATCH_WM_GETMINMAXINFO(wParam, lParam, fn) \
    ((fn)((LPMINMAXINFO)(lParam)), 0L)
#define DELEGATE_WM_GETMINMAXINFO(lpMinMaxInfo, fn) \
    (void)(fn)(WM_GETMINMAXINFO, 0L, (LPARAM)(LPMINMAXINFO)(lpMinMaxInfo))

/* void Cls:OnPaint() */
#define DISPATCH_WM_PAINT(wParam, lParam, fn) \
    ((fn)(), 0L)
#define DELEGATE_WM_PAINT(fn) \
    (void)(fn)(WM_PAINT, 0L, 0L)

/* BOOL Cls:OnEraseBkgnd(HDC hdc) */
#define DISPATCH_WM_ERASEBKGND(wParam, lParam, fn) \
    (LRESULT)(DWORD)(BOOL)(fn)((HDC)(wParam))
#define DELEGATE_WM_ERASEBKGND(hdc, fn) \
   (BOOL)(DWORD)(fn)(WM_ERASEBKGND, (WPARAM)(HDC)(hdc), 0L)

/* BOOL Cls:OnIconEraseBkgnd(HDC hdc) */
#define DISPATCH_WM_ICONERASEBKGND(wParam, lParam, fn) \
    (LRESULT)(DWORD)(BOOL)(fn)((HDC)(wParam))
#define DELEGATE_WM_ICONERASEBKGND(hdc, fn) \
    (BOOL)(DWORD)(fn)(WM_ICONERASEBKGND, (WPARAM)(HDC)(hdc), 0L)

/* void Cls:OnNCPaint(HRGN hrgn) */
#define DISPATCH_WM_NCPAINT(wParam, lParam, fn) \
    ((fn)((HRGN)(wParam)), 0L)
#define DELEGATE_WM_NCPAINT(hrgn, fn) \
    (void)(fn)(WM_NCPAINT, (WPARAM)(HRGN)(hrgn), 0L)

/* UINT Cls:OnNCCalcSize(BOOL fCalcValidRects, NCCALCSIZE_PARAMS * lpcsp) */
#define DISPATCH_WM_NCCALCSIZE(wParam, lParam, fn) \
    (LRESULT)(DWORD)(UINT)(fn)((BOOL)(0), (NCCALCSIZE_PARAMS *)(lParam))
#define DELEGATE_WM_NCCALCSIZE(fCalcValidRects, lpcsp, fn) \
    (UINT)(DWORD)(fn)(WM_NCCALCSIZE, 0L, (LPARAM)(NCCALCSIZE_PARAMS *)(lpcsp))

/* UINT Cls:OnNCHitTest(int x, int y) */
#define DISPATCH_WM_NCHITTEST(wParam, lParam, fn) \
    (LRESULT)(DWORD)(UINT)(fn)((int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam))
#define DELEGATE_WM_NCHITTEST(x, y, fn) \
    (UINT)(DWORD)(fn)(WM_NCHITTEST, 0L, MAKELPARAM((x), (y)))

/* HICON Cls:OnQueryDragIcon() */
#define DISPATCH_WM_QUERYDRAGICON(wParam, lParam, fn) \
    (LRESULT)(DWORD)(UINT)(fn)()
#define DELEGATE_WM_QUERYDRAGICON(fn) \
    (HICON)(UINT)(DWORD)(fn)(WM_QUERYDRAGICON, 0L, 0L)

#ifdef _INC_SHELLAPI
/* void Cls:OnDropFiles(HDROP hdrop) */
#define DISPATCH_WM_DROPFILES(wParam, lParam, fn) \
    ((fn)((HDROP)(wParam)), 0L)
#define DELEGATE_WM_DROPFILES(hdrop, fn) \
    (void)(fn)(WM_DROPFILES, (WPARAM)(HDROP)(hdrop), 0L)
#endif  /* _INC_SHELLAPI */

/* void Cls:OnActivate(UINT state, HWND hwndActDeact, BOOL fMinimized) */
#define DISPATCH_WM_ACTIVATE(wParam, lParam, fn) \
    ((fn)((UINT)LOWORD(wParam), (HWND)(lParam), (BOOL)HIWORD(wParam)), 0L)
#define DELEGATE_WM_ACTIVATE(state, hwndActDeact, fMinimized, fn) \
    (void)(fn)(WM_ACTIVATE, MAKEWPARAM((state), (fMinimized)), (LPARAM)(HWND)(hwndActDeact))

/* void Cls:OnActivateApp(BOOL fActivate, DWORD dwThreadId) */
#define DISPATCH_WM_ACTIVATEAPP(wParam, lParam, fn) \
    ((fn)((BOOL)(wParam), (DWORD)(lParam)), 0L)
#define DELEGATE_WM_ACTIVATEAPP(fActivate, dwThreadId, fn) \
    (void)(fn)(WM_ACTIVATEAPP, (WPARAM)(BOOL)(fActivate), (LPARAM)(dwThreadId))

/* BOOL Cls:OnNCActivate(BOOL fActive, HWND hwndActDeact, BOOL fMinimized) */
#define DISPATCH_WM_NCACTIVATE(wParam, lParam, fn) \
    (LRESULT)(DWORD)(BOOL)(fn)((BOOL)(wParam), 0L, 0L)
#define DELEGATE_WM_NCACTIVATE(fActive, hwndActDeact, fMinimized, fn) \
    (BOOL)(DWORD)(fn)(WM_NCACTIVATE, (WPARAM)(BOOL)(fActive), 0L)

/* void Cls:OnSetFocus(HWND hwndOldFocus) */
#define DISPATCH_WM_SETFOCUS(wParam, lParam, fn) \
    ((fn)((HWND)(wParam)), 0L)
#define DELEGATE_WM_SETFOCUS(hwndOldFocus, fn) \
    (void)(fn)(WM_SETFOCUS, (WPARAM)(HWND)(hwndOldFocus), 0L)

/* void Cls:OnKillFocus(HWND hwndNewFocus) */
#define DISPATCH_WM_KILLFOCUS(wParam, lParam, fn) \
    ((fn)((HWND)(wParam)), 0L)
#define DELEGATE_WM_KILLFOCUS(hwndNewFocus, fn) \
    (void)(fn)(WM_KILLFOCUS, (WPARAM)(HWND)(hwndNewFocus), 0L)

/* void Cls:OnKey(UINT vk, BOOL fDown, int cRepeat, UINT flags) */
#define DISPATCH_WM_KEYDOWN(wParam, lParam, fn) \
    ((fn)((UINT)(wParam), TRUE, (int)(short)LOWORD(lParam), (UINT)HIWORD(lParam)), 0L)
#define DELEGATE_WM_KEYDOWN(vk, cRepeat, flags, fn) \
    (void)(fn)(WM_KEYDOWN, (WPARAM)(UINT)(vk), MAKELPARAM((cRepeat), (flags)))

/* void Cls:OnKey(UINT vk, BOOL fDown, int cRepeat, UINT flags) */
#define DISPATCH_WM_KEYUP(wParam, lParam, fn) \
    ((fn)((UINT)(wParam), FALSE, (int)(short)LOWORD(lParam), (UINT)HIWORD(lParam)), 0L)
#define DELEGATE_WM_KEYUP(vk, cRepeat, flags, fn) \
    (void)(fn)(WM_KEYUP, (WPARAM)(UINT)(vk), MAKELPARAM((cRepeat), (flags)))

/* void Cls:OnChar(TCHAR ch, int cRepeat) */
#define DISPATCH_WM_CHAR(wParam, lParam, fn) \
    ((fn)((TCHAR)(wParam), (int)(short)LOWORD(lParam)), 0L)
#define DELEGATE_WM_CHAR(ch, cRepeat, fn) \
    (void)(fn)(WM_CHAR, (WPARAM)(TCHAR)(ch), MAKELPARAM((cRepeat),0))

/* void Cls:OnDeadChar(TCHAR ch, int cRepeat) */
#define DISPATCH_WM_DEADCHAR(wParam, lParam, fn) \
    ((fn)((TCHAR)(wParam), (int)(short)LOWORD(lParam)), 0L)
#define DELEGATE_WM_DEADCHAR(ch, cRepeat, fn) \
    (void)(fn)(WM_DEADCHAR, (WPARAM)(TCHAR)(ch), MAKELPARAM((cRepeat),0))

/* void Cls:OnSysKey(UINT vk, BOOL fDown, int cRepeat, UINT flags) */
#define DISPATCH_WM_SYSKEYDOWN(wParam, lParam, fn) \
    ((fn)((UINT)(wParam), TRUE, (int)(short)LOWORD(lParam), (UINT)HIWORD(lParam)), 0L)
#define DELEGATE_WM_SYSKEYDOWN(vk, cRepeat, flags, fn) \
    (void)(fn)(WM_SYSKEYDOWN, (WPARAM)(UINT)(vk), MAKELPARAM((cRepeat), (flags)))

/* void Cls:OnSysKey(UINT vk, BOOL fDown, int cRepeat, UINT flags) */
#define DISPATCH_WM_SYSKEYUP(wParam, lParam, fn) \
    ((fn)((UINT)(wParam), FALSE, (int)(short)LOWORD(lParam), (UINT)HIWORD(lParam)), 0L)
#define DELEGATE_WM_SYSKEYUP(vk, cRepeat, flags, fn) \
    (void)(fn)(WM_SYSKEYUP, (WPARAM)(UINT)(vk), MAKELPARAM((cRepeat), (flags)))

/* void Cls:OnSysChar(TCHAR ch, int cRepeat) */
#define DISPATCH_WM_SYSCHAR(wParam, lParam, fn) \
    ((fn)((TCHAR)(wParam), (int)(short)LOWORD(lParam)), 0L)
#define DELEGATE_WM_SYSCHAR(ch, cRepeat, fn) \
    (void)(fn)(WM_SYSCHAR, (WPARAM)(TCHAR)(ch), MAKELPARAM((cRepeat), 0))

/* void Cls:OnSysDeadChar(TCHAR ch, int cRepeat) */
#define DISPATCH_WM_SYSDEADCHAR(wParam, lParam, fn) \
    ((fn)((TCHAR)(wParam), (int)(short)LOWORD(lParam)), 0L)
#define DELEGATE_WM_SYSDEADCHAR(ch, cRepeat, fn) \
    (void)(fn)(WM_SYSDEADCHAR, (WPARAM)(TCHAR)(ch), MAKELPARAM((cRepeat), 0))

/* void Cls:OnMouseMove(int x, int y, UINT keyFlags) */
#define DISPATCH_WM_MOUSEMOVE(wParam, lParam, fn) \
    ((fn)((int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define DELEGATE_WM_MOUSEMOVE(x, y, keyFlags, fn) \
    (void)(fn)(WM_MOUSEMOVE, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y)))

/* void Cls:OnLButtonDown(BOOL fDoubleClick, int x, int y, UINT keyFlags) */
#define DISPATCH_WM_LBUTTONDOWN(wParam, lParam, fn) \
    ((fn)(FALSE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define DELEGATE_WM_LBUTTONDOWN(fDoubleClick, x, y, keyFlags, fn) \
    (void)(fn)((fDoubleClick) ? WM_LBUTTONDBLCLK : WM_LBUTTONDOWN, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y)))

/* void Cls:OnLButtonDown(BOOL fDoubleClick, int x, int y, UINT keyFlags) */
#define DISPATCH_WM_LBUTTONDBLCLK(wParam, lParam, fn) \
    ((fn)(TRUE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)

/* void Cls:OnLButtonUp(int x, int y, UINT keyFlags) */
#define DISPATCH_WM_LBUTTONUP(wParam, lParam, fn) \
    ((fn)((int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define DELEGATE_WM_LBUTTONUP(x, y, keyFlags, fn) \
    (void)(fn)(WM_LBUTTONUP, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y)))

/* void Cls:OnRButtonDown(BOOL fDoubleClick, int x, int y, UINT keyFlags) */
#define DISPATCH_WM_RBUTTONDOWN(wParam, lParam, fn) \
    ((fn)(FALSE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define DELEGATE_WM_RBUTTONDOWN(fDoubleClick, x, y, keyFlags, fn) \
    (void)(fn)((fDoubleClick) ? WM_RBUTTONDBLCLK : WM_RBUTTONDOWN, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y)))

/* void Cls:OnRButtonDown(BOOL fDoubleClick, int x, int y, UINT keyFlags) */
#define DISPATCH_WM_RBUTTONDBLCLK(wParam, lParam, fn) \
    ((fn)(TRUE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)

/* void Cls:OnRButtonUp(int x, int y, UINT flags) */
#define DISPATCH_WM_RBUTTONUP(wParam, lParam, fn) \
    ((fn)((int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define DELEGATE_WM_RBUTTONUP(x, y, keyFlags, fn) \
    (void)(fn)(WM_RBUTTONUP, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y)))

/* void Cls:OnMButtonDown(BOOL fDoubleClick, int x, int y, UINT keyFlags) */
#define DISPATCH_WM_MBUTTONDOWN(wParam, lParam, fn) \
    ((fn)(FALSE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define DELEGATE_WM_MBUTTONDOWN(fDoubleClick, x, y, keyFlags, fn) \
    (void)(fn)((fDoubleClick) ? WM_MBUTTONDBLCLK : WM_MBUTTONDOWN, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y)))

/* void Cls:OnMButtonDown(BOOL fDoubleClick, int x, int y, UINT keyFlags) */
#define DISPATCH_WM_MBUTTONDBLCLK(wParam, lParam, fn) \
    ((fn)(TRUE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)

/* void Cls:OnMButtonUp(int x, int y, UINT flags) */
#define DISPATCH_WM_MBUTTONUP(wParam, lParam, fn) \
    ((fn)((int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define DELEGATE_WM_MBUTTONUP(x, y, keyFlags, fn) \
    (void)(fn)(WM_MBUTTONUP, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y)))

/* void Cls:OnNCMouseMove(int x, int y, UINT codeHitTest) */
#define DISPATCH_WM_NCMOUSEMOVE(wParam, lParam, fn) \
    ((fn)((int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define DELEGATE_WM_NCMOUSEMOVE(x, y, codeHitTest, fn) \
    (void)(fn)(WM_NCMOUSEMOVE, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)))

/* void Cls:OnNCLButtonDown(BOOL fDoubleClick, int x, int y, UINT codeHitTest) */
#define DISPATCH_WM_NCLBUTTONDOWN(wParam, lParam, fn) \
    ((fn)(FALSE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define DELEGATE_WM_NCLBUTTONDOWN(fDoubleClick, x, y, codeHitTest, fn) \
    (void)(fn)((fDoubleClick) ? WM_NCLBUTTONDBLCLK : WM_NCLBUTTONDOWN, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)))

/* void Cls:OnNCLButtonDown(BOOL fDoubleClick, int x, int y, UINT codeHitTest) */
#define DISPATCH_WM_NCLBUTTONDBLCLK(wParam, lParam, fn) \
    ((fn)(TRUE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)

/* void Cls:OnNCLButtonUp(int x, int y, UINT codeHitTest) */
#define DISPATCH_WM_NCLBUTTONUP(wParam, lParam, fn) \
    ((fn)((int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define DELEGATE_WM_NCLBUTTONUP(x, y, codeHitTest, fn) \
    (void)(fn)(WM_NCLBUTTONUP, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)))

/* void Cls:OnNCRButtonDown(BOOL fDoubleClick, int x, int y, UINT codeHitTest) */
#define DISPATCH_WM_NCRBUTTONDOWN(wParam, lParam, fn) \
    ((fn)(FALSE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define DELEGATE_WM_NCRBUTTONDOWN(fDoubleClick, x, y, codeHitTest, fn) \
    (void)(fn)((fDoubleClick) ? WM_NCRBUTTONDBLCLK : WM_NCRBUTTONDOWN, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)) )

/* void Cls:OnNCRButtonDown(BOOL fDoubleClick, int x, int y, UINT codeHitTest) */
#define DISPATCH_WM_NCRBUTTONDBLCLK(wParam, lParam, fn) \
    ((fn)(TRUE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)

/* void Cls:OnNCRButtonUp(int x, int y, UINT codeHitTest) */
#define DISPATCH_WM_NCRBUTTONUP(wParam, lParam, fn) \
    ((fn)((int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define DELEGATE_WM_NCRBUTTONUP(x, y, codeHitTest, fn) \
    (void)(fn)(WM_NCRBUTTONUP, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)) )

/* void Cls:OnNCMButtonDown(BOOL fDoubleClick, int x, int y, UINT codeHitTest) */
#define DISPATCH_WM_NCMBUTTONDOWN(wParam, lParam, fn) \
    ((fn)(FALSE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define DELEGATE_WM_NCMBUTTONDOWN(fDoubleClick, x, y, codeHitTest, fn) \
    (void)(fn)((fDoubleClick) ? WM_NCMBUTTONDBLCLK : WM_NCMBUTTONDOWN, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)) )

/* void Cls:OnNCMButtonDown(BOOL fDoubleClick, int x, int y, UINT codeHitTest) */
#define DISPATCH_WM_NCMBUTTONDBLCLK(wParam, lParam, fn) \
    ((fn)(TRUE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)

/* void Cls:OnNCMButtonUp(int x, int y, UINT codeHitTest) */
#define DISPATCH_WM_NCMBUTTONUP(wParam, lParam, fn) \
    ((fn)((int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define DELEGATE_WM_NCMBUTTONUP(x, y, codeHitTest, fn) \
    (void)(fn)(WM_NCMBUTTONUP, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)) )

/* int Cls:OnMouseActivate(HWND hwndTopLevel, UINT codeHitTest, UINT msg) */
#define DISPATCH_WM_MOUSEACTIVATE(wParam, lParam, fn) \
    (LRESULT)(DWORD)(int)(fn)((HWND)(wParam), (UINT)LOWORD(lParam), (UINT)HIWORD(lParam))
#define DELEGATE_WM_MOUSEACTIVATE(hwndTopLevel, codeHitTest, msg, fn) \
    (int)(DWORD)(fn)(WM_MOUSEACTIVATE, (WPARAM)(HWND)(hwndTopLevel), MAKELPARAM((codeHitTest), (msg)))

/* void Cls:OnCancelMode() */
#define DISPATCH_WM_CANCELMODE(wParam, lParam, fn) \
    ((fn)(), 0L)
#define DELEGATE_WM_CANCELMODE(fn) \
    (void)(fn)(WM_CANCELMODE, 0L, 0L)

/* void Cls:OnTimer(UINT id) */
#define DISPATCH_WM_TIMER(wParam, lParam, fn) \
    ((fn)((UINT)(wParam)), 0L)
#define DELEGATE_WM_TIMER(id, fn) \
    (void)(fn)(WM_TIMER, (WPARAM)(UINT)(id), 0L)

/* void Cls:OnInitMenu(HMENU hMenu) */
#define DISPATCH_WM_INITMENU(wParam, lParam, fn) \
    ((fn)((HMENU)(wParam)), 0L)
#define DELEGATE_WM_INITMENU(hMenu, fn) \
    (void)(fn)(WM_INITMENU, (WPARAM)(HMENU)(hMenu), 0L)

/* void Cls:OnInitMenuPopup(HMENU hMenu, UINT item, BOOL fSystemMenu) */
#define DISPATCH_WM_INITMENUPOPUP(wParam, lParam, fn) \
    ((fn)((HMENU)(wParam), (UINT)LOWORD(lParam), (BOOL)HIWORD(lParam)), 0L)
#define DELEGATE_WM_INITMENUPOPUP(hMenu, item, fSystemMenu, fn) \
    (void)(fn)(WM_INITMENUPOPUP, (WPARAM)(HMENU)(hMenu), MAKELPARAM((item),(fSystemMenu)))

/* void Cls:OnMenuSelect(HMENU hmenu, int item, HMENU hmenuPopup, UINT flags) */
#define DISPATCH_WM_MENUSELECT(wParam, lParam, fn)                  \
    ((fn)((HMENU)(lParam),  \
    (int)(LOWORD(wParam)),          \
    (HIWORD(wParam) & MF_POPUP) ? GetSubMenu((HMENU)lParam, LOWORD(wParam)) : 0L, \
    (UINT)(((short)HIWORD(wParam) == -1) ? 0xFFFFFFFF : HIWORD(wParam))), 0L)
#define DELEGATE_WM_MENUSELECT(hmenu, item, hmenuPopup, flags, fn) \
    (void)(fn)(WM_MENUSELECT, MAKEWPARAM((item), (flags)), (LPARAM)(HMENU)((hmenu) ? (hmenu) : (hmenuPopup)))

/* DWORD Cls:OnMenuChar(UINT ch, UINT flags, HMENU hmenu) */
#define DISPATCH_WM_MENUCHAR(wParam, lParam, fn) \
    (LRESULT)(DWORD)(fn)((UINT)(LOWORD(wParam)), (UINT)HIWORD(wParam), (HMENU)(lParam))
#define DELEGATE_WM_MENUCHAR(ch, flags, hmenu, fn) \
    (DWORD)(fn)(WM_MENUCHAR, MAKEWPARAM(flags, (WORD)(ch)), (LPARAM)(HMENU)(hmenu))

/* void Cls:OnCommand(int id, HWND hwndCtl, UINT codeNotify) */
#define DISPATCH_WM_COMMAND(wParam, lParam, fn) \
    ((fn)((int)(LOWORD(wParam)), (HWND)(lParam), (UINT)HIWORD(wParam)), 0L)
#define DELEGATE_WM_COMMAND(id, hwndCtl, codeNotify, fn) \
    (void)(fn)(WM_COMMAND, MAKEWPARAM((UINT)(id),(UINT)(codeNotify)), (LPARAM)(HWND)(hwndCtl))

/* void Cls:OnHScroll(HWND hwndCtl, UINT code, int pos) */
#define DISPATCH_WM_HSCROLL(wParam, lParam, fn) \
    ((fn)((HWND)(lParam), (UINT)(LOWORD(wParam)), (int)(short)HIWORD(wParam)), 0L)
#define DELEGATE_WM_HSCROLL(hwndCtl, code, pos, fn) \
    (void)(fn)(WM_HSCROLL, MAKEWPARAM((UINT)(int)(code),(UINT)(int)(pos)), (LPARAM)(UINT)(hwndCtl))

/* void Cls:OnVScroll(HWND hwndCtl, UINT code, int pos) */
#define DISPATCH_WM_VSCROLL(wParam, lParam, fn) \
    ((fn)((HWND)(lParam), (UINT)(LOWORD(wParam)),  (int)(short)HIWORD(wParam)), 0L)
#define DELEGATE_WM_VSCROLL(hwndCtl, code, pos, fn) \
    (void)(fn)(WM_VSCROLL, MAKEWPARAM((UINT)(int)(code),(UINT)(int)(pos)), (LPARAM)(HWND)(hwndCtl))

/* void Cls:OnCut() */
#define DISPATCH_WM_CUT(wParam, lParam, fn) \
    ((fn)(), 0L)
#define DELEGATE_WM_CUT(fn) \
    (void)(fn)(WM_CUT, 0L, 0L)

/* void Cls:OnCopy() */
#define DISPATCH_WM_COPY(wParam, lParam, fn) \
    ((fn)(), 0L)
#define DELEGATE_WM_COPY(fn) \
    (void)(fn)(WM_COPY, 0L, 0L)

/* void Cls:OnPaste() */
#define DISPATCH_WM_PASTE(wParam, lParam, fn) \
    ((fn)(), 0L)
#define DELEGATE_WM_PASTE(fn) \
    (void)(fn)(WM_PASTE, 0L, 0L)

/* void Cls:OnClear() */
#define DISPATCH_WM_CLEAR(wParam, lParam, fn) \
    ((fn)(), 0L)
#define DELEGATE_WM_CLEAR(fn) \
    (void)(fn)(WM_CLEAR, 0L, 0L)

/* void Cls:OnUndo() */
#define DISPATCH_WM_UNDO(wParam, lParam, fn) \
    ((fn)(), 0L)
#define DELEGATE_WM_UNDO(fn) \
    (void)(fn)(WM_UNDO, 0L, 0L)

/* HANDLE Cls:OnRenderFormat(UINT fmt) */
#define DISPATCH_WM_RENDERFORMAT(wParam, lParam, fn) \
    (LRESULT)(DWORD)(UINT)(HANDLE)(fn)((UINT)(wParam))
#define DELEGATE_WM_RENDERFORMAT(fmt, fn) \
    (HANDLE)(UINT)(DWORD)(fn)(WM_RENDERFORMAT, (WPARAM)(UINT)(fmt), 0L)

/* void Cls:OnRenderAllFormats() */
#define DISPATCH_WM_RENDERALLFORMATS(wParam, lParam, fn) \
    ((fn)(), 0L)
#define DELEGATE_WM_RENDERALLFORMATS(fn) \
    (void)(fn)(WM_RENDERALLFORMATS, 0L, 0L)

/* void Cls:OnDestroyClipboard() */
#define DISPATCH_WM_DESTROYCLIPBOARD(wParam, lParam, fn) \
    ((fn)(), 0L)
#define DELEGATE_WM_DESTROYCLIPBOARD(fn) \
    (void)(fn)(WM_DESTROYCLIPBOARD, 0L, 0L)

/* void Cls:OnDrawClipboard() */
#define DISPATCH_WM_DRAWCLIPBOARD(wParam, lParam, fn) \
    ((fn)(), 0L)
#define DELEGATE_WM_DRAWCLIPBOARD(fn) \
    (void)(fn)(WM_DRAWCLIPBOARD, 0L, 0L)

/* void Cls:OnPaintClipboard(HWND hwndCBViewer, const LPPAINTSTRUCT lpPaintStruct) */
#define DISPATCH_WM_PAINTCLIPBOARD(wParam, lParam, fn) \
    ((fn)((HWND)(wParam), (const LPPAINTSTRUCT)GlobalLock((HGLOBAL)(lParam))), GlobalUnlock((HGLOBAL)(lParam)), 0L)
#define DELEGATE_WM_PAINTCLIPBOARD(hwndCBViewer, lpPaintStruct, fn) \
    (void)(fn)(WM_PAINTCLIPBOARD, (WPARAM)(HWND)(hwndCBViewer), (LPARAM)(LPPAINTSTRUCT)(lpPaintStruct))

/* void Cls:OnSizeClipboard(HWND hwndCBViewer, const LPRECT lprc) */
#define DISPATCH_WM_SIZECLIPBOARD(wParam, lParam, fn) \
    ((fn)((HWND)(wParam), (const LPRECT)GlobalLock((HGLOBAL)(lParam))), GlobalUnlock((HGLOBAL)(lParam)), 0L)
#define DELEGATE_WM_SIZECLIPBOARD(hwndCBViewer, lprc, fn) \
    (void)(fn)(WM_SIZECLIPBOARD, (WPARAM)(HWND)(hwndCBViewer), (LPARAM)(LPRECT)(lprc))

/* void Cls:OnVScrollClipboard(HWND hwndCBViewer, UINT code, int pos) */
#define DISPATCH_WM_VSCROLLCLIPBOARD(wParam, lParam, fn) \
    ((fn)((HWND)(wParam), (UINT)LOWORD(lParam), (int)(short)HIWORD(lParam)), 0L)
#define DELEGATE_WM_VSCROLLCLIPBOARD(hwndCBViewer, code, pos, fn) \
    (void)(fn)(WM_VSCROLLCLIPBOARD, (WPARAM)(HWND)(hwndCBViewer), MAKELPARAM((code), (pos)))

/* void Cls:OnHScrollClipboard(HWND hwndCBViewer, UINT code, int pos) */
#define DISPATCH_WM_HSCROLLCLIPBOARD(wParam, lParam, fn) \
    ((fn)((HWND)(wParam), (UINT)LOWORD(lParam), (int)(short)HIWORD(lParam)), 0L)
#define DELEGATE_WM_HSCROLLCLIPBOARD(hwndCBViewer, code, pos, fn) \
    (void)(fn)(WM_HSCROLLCLIPBOARD, (WPARAM)(HWND)(hwndCBViewer), MAKELPARAM((code), (pos)))

/* void Cls:OnAskCBFormatName(int cchMax, LPTSTR rgchName) */
#define DISPATCH_WM_ASKCBFORMATNAME(wParam, lParam, fn) \
    ((fn)((int)(wParam), (LPTSTR)(lParam)), 0L)
#define DELEGATE_WM_ASKCBFORMATNAME(cchMax, rgchName, fn) \
    (void)(fn)(WM_ASKCBFORMATNAME, (WPARAM)(int)(cchMax), (LPARAM)(rgchName))

/* void Cls:OnChangeCBChain(HWND hwndRemove, HWND hwndNext) */
#define DISPATCH_WM_CHANGECBCHAIN(wParam, lParam, fn) \
    ((fn)((HWND)(wParam), (HWND)(lParam)), 0L)
#define DELEGATE_WM_CHANGECBCHAIN(hwndRemove, hwndNext, fn) \
    (void)(fn)(WM_CHANGECBCHAIN, (WPARAM)(HWND)(hwndRemove), (LPARAM)(HWND)(hwndNext))

/* BOOL Cls:OnSetCursor(HWND hwndCursor, UINT codeHitTest, UINT msg) */
#define DISPATCH_WM_SETCURSOR(wParam, lParam, fn) \
    (LRESULT)(DWORD)(BOOL)(fn)((HWND)(wParam), (UINT)LOWORD(lParam), (UINT)HIWORD(lParam))
#define DELEGATE_WM_SETCURSOR(hwndCursor, codeHitTest, msg, fn) \
    (BOOL)(DWORD)(fn)(WM_SETCURSOR, (WPARAM)(HWND)(hwndCursor), MAKELPARAM((codeHitTest), (msg)))

/* void Cls:OnSysCommand(UINT cmd, int x, int y) */
#define DISPATCH_WM_SYSCOMMAND(wParam, lParam, fn) \
    ((fn)((UINT)(wParam), (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam)), 0L)
#define DELEGATE_WM_SYSCOMMAND(cmd, x, y, fn) \
    (void)(fn)(WM_SYSCOMMAND, (WPARAM)(UINT)(cmd), MAKELPARAM((x), (y)))

/* HWND Cls:MDICreate(const LPMDICREATESTRUCT lpmcs) */
#define DISPATCH_WM_MDICREATE(wParam, lParam, fn) \
    (LRESULT)(DWORD)(UINT)(fn)((LPMDICREATESTRUCT)(lParam))
#define DELEGATE_WM_MDICREATE(lpmcs, fn) \
    (HWND)(UINT)(DWORD)(fn)(WM_MDICREATE, 0L, (LPARAM)(LPMDICREATESTRUCT)(lpmcs))

/* void Cls:MDIDestroy(HWND hwndDestroy) */
#define DISPATCH_WM_MDIDESTROY(wParam, lParam, fn) \
    ((fn)((HWND)(wParam)), 0L)
#define DELEGATE_WM_MDIDESTROY(hwndDestroy, fn) \
    (void)(fn)(WM_MDIDESTROY, (WPARAM)(hwndDestroy), 0L)

/* NOTE: Usable only by MDI client windows */
/* void Cls:MDIActivate(BOOL fActive, HWND hwndActivate, HWND hwndDeactivate) */
#define DISPATCH_WM_MDIACTIVATE(wParam, lParam, fn) \
    ((fn)((BOOL)(lParam == (LPARAM)hwnd), (HWND)(lParam), (HWND)(wParam)), 0L)
#define DELEGATE_WM_MDIACTIVATE(fActive, hwndActivate, hwndDeactivate, fn) \
    (void)(fn)(WM_MDIACTIVATE, (WPARAM)(hwndDeactivate), (LPARAM)(hwndActivate))

/* void Cls:MDIRestore(HWND hwndRestore) */
#define DISPATCH_WM_MDIRESTORE(wParam, lParam, fn) \
    ((fn)((HWND)(wParam)), 0L)
#define DELEGATE_WM_MDIRESTORE(hwndRestore, fn) \
    (void)(fn)(WM_MDIRESTORE, (WPARAM)(hwndRestore), 0L)

/* HWND Cls:MDINext(HWND hwndCur, BOOL fPrev) */
#define DISPATCH_WM_MDINEXT(wParam, lParam, fn) \
    (LRESULT)(HWND)(fn)((HWND)(wParam), (BOOL)lParam)
#define DELEGATE_WM_MDINEXT(hwndCur, fPrev, fn) \
    (HWND)(UINT)(DWORD)(fn)(WM_MDINEXT, (WPARAM)(hwndCur), (LPARAM)(fPrev))

/* void Cls:MDIMaximize(HWND hwndMaximize) */
#define DISPATCH_WM_MDIMAXIMIZE(wParam, lParam, fn) \
    ((fn)((HWND)(wParam)), 0L)
#define DELEGATE_WM_MDIMAXIMIZE(hwndMaximize, fn) \
    (void)(fn)(WM_MDIMAXIMIZE, (WPARAM)(hwndMaximize), 0L)

/* BOOL Cls:MDITile(UINT cmd) */
#define DISPATCH_WM_MDITILE(wParam, lParam, fn) \
    (LRESULT)(DWORD)(fn)((UINT)(wParam))
#define DELEGATE_WM_MDITILE(cmd, fn) \
    (BOOL)(DWORD)(fn)(WM_MDITILE, (WPARAM)(cmd), 0L)

/* BOOL Cls:MDICascade(UINT cmd) */
#define DISPATCH_WM_MDICASCADE(wParam, lParam, fn) \
    (LRESULT)(DWORD)(fn)((UINT)(wParam))
#define DELEGATE_WM_MDICASCADE(cmd, fn) \
    (BOOL)(DWORD)(fn)(WM_MDICASCADE, (WPARAM)(cmd), 0L)

/* void Cls:MDIIconArrange() */
#define DISPATCH_WM_MDIICONARRANGE(wParam, lParam, fn) \
    ((fn)(), 0L)
#define DELEGATE_WM_MDIICONARRANGE(fn) \
    (void)(fn)(WM_MDIICONARRANGE, 0L, 0L)

/* HWND Cls:MDIGetActive() */
#define DISPATCH_WM_MDIGETACTIVE(wParam, lParam, fn) \
    (LRESULT)(DWORD)(UINT)(fn)(hwnd)
#define DELEGATE_WM_MDIGETACTIVE(fn) \
    (HWND)(UINT)(DWORD)(fn)(WM_MDIGETACTIVE, 0L, 0L)

/* HMENU Cls:MDISetMenu(BOOL fRefresh, HMENU hmenuFrame, HMENU hmenuWindow) */
#define DISPATCH_WM_MDISETMENU(wParam, lParam, fn) \
    (LRESULT)(DWORD)(UINT)(fn)((BOOL)(wParam), (HMENU)(wParam), (HMENU)(lParam))
#define DELEGATE_WM_MDISETMENU(fRefresh, hmenuFrame, hmenuWindow, fn) \
    (HMENU)(UINT)(DWORD)(fn)(WM_MDISETMENU, (WPARAM)((fRefresh) ? (hmenuFrame) : 0), (LPARAM)(hmenuWindow))

/* void Cls:OnChildActivate() */
#define DISPATCH_WM_CHILDACTIVATE(wParam, lParam, fn) \
    ((fn)(), 0L)
#define DELEGATE_WM_CHILDACTIVATE(fn) \
    (void)(fn)(WM_CHILDACTIVATE, 0L, 0L)

/* BOOL Cls:OnInitDialog(HWND hwndFocus, LPARAM lParam) */
#define DISPATCH_WM_INITDIALOG(wParam, lParam, fn) \
    (LRESULT)(DWORD)(UINT)(BOOL)(fn)((HWND)(wParam), lParam)
#define DELEGATE_WM_INITDIALOG(hwndFocus, lParam, fn) \
    (BOOL)(DWORD)(fn)(WM_INITDIALOG, (WPARAM)(HWND)(hwndFocus), (lParam))

/* HWND Cls:OnNextDlgCtl(HWND hwndSetFocus, BOOL fNext) */
#define DISPATCH_WM_NEXTDLGCTL(wParam, lParam, fn) \
    (LRESULT)(DWORD)(UINT)(HWND)(fn)((HWND)(wParam), (BOOL)(lParam))
#define DELEGATE_WM_NEXTDLGCTL(hwndSetFocus, fNext, fn) \
    (HWND)(UINT)(DWORD)(fn)(WM_NEXTDLGCTL, (WPARAM)(HWND)(hwndSetFocus), (LPARAM)(fNext))

/* void Cls:OnParentNotify(UINT msg, HWND hwndChild, int idChild) */
#define DISPATCH_WM_PARENTNOTIFY(wParam, lParam, fn) \
    ((fn)((UINT)LOWORD(wParam), (HWND)(lParam), (UINT)HIWORD(wParam)), 0L)
#define DELEGATE_WM_PARENTNOTIFY(msg, hwndChild, idChild, fn) \
    (void)(fn)(WM_PARENTNOTIFY, MAKEWPARAM(msg, idChild), (LPARAM)(hwndChild))

/* void Cls:OnEnterIdle(UINT source, HWND hwndSource) */
#define DISPATCH_WM_ENTERIDLE(wParam, lParam, fn) \
    ((fn)((UINT)(wParam), (HWND)(lParam)), 0L)
#define DELEGATE_WM_ENTERIDLE(source, hwndSource, fn) \
    (void)(fn)(WM_ENTERIDLE, (WPARAM)(UINT)(source), (LPARAM)(HWND)(hwndSource))

/* UINT Cls:OnGetDlgCode(LPMSG lpmsg) */
#define DISPATCH_WM_GETDLGCODE(wParam, lParam, fn) \
    (LRESULT)(DWORD)(UINT)(fn)((LPMSG)(lParam))
#define DELEGATE_WM_GETDLGCODE(lpmsg, fn) \
    (UINT)(DWORD)(fn)(WM_GETDLGCODE, (lpmsg ? lpmsg->wParam : 0), (LPARAM)(LPMSG)(lpmsg))

/* HBRUSH Cls:OnCtlColor(HDC hdc, HWND hwndChild, int type) */
#define DISPATCH_WM_CTLCOLORMSGBOX(wParam, lParam, fn) \
    (LRESULT)(DWORD)(UINT)(HBRUSH)(fn)((HDC)(wParam), (HWND)(lParam), CTLCOLOR_MSGBOX)
#define DELEGATE_WM_CTLCOLORMSGBOX(hdc, hwndChild, fn) \
    (HBRUSH)(UINT)(DWORD)(fn)(WM_CTLCOLORMSGBOX, (WPARAM)(HDC)(hdc), (LPARAM)(HWND)(hwndChild))

#define DISPATCH_WM_CTLCOLOREDIT(wParam, lParam, fn) \
    (LRESULT)(DWORD)(UINT)(HBRUSH)(fn)((HDC)(wParam), (HWND)(lParam), CTLCOLOR_EDIT)
#define DELEGATE_WM_CTLCOLOREDIT(hdc, hwndChild, fn) \
    (HBRUSH)(UINT)(DWORD)(fn)(WM_CTLCOLOREDIT, (WPARAM)(HDC)(hdc), (LPARAM)(HWND)(hwndChild))

#define DISPATCH_WM_CTLCOLORLISTBOX(wParam, lParam, fn) \
    (LRESULT)(DWORD)(UINT)(HBRUSH)(fn)((HDC)(wParam), (HWND)(lParam), CTLCOLOR_LISTBOX)
#define DELEGATE_WM_CTLCOLORLISTBOX(hdc, hwndChild, fn) \
    (HBRUSH)(UINT)(DWORD)(fn)(WM_CTLCOLORLISTBOX, (WPARAM)(HDC)(hdc), (LPARAM)(HWND)(hwndChild))

#define DISPATCH_WM_CTLCOLORBTN(wParam, lParam, fn) \
    (LRESULT)(DWORD)(UINT)(HBRUSH)(fn)((HDC)(wParam), (HWND)(lParam), CTLCOLOR_BTN)
#define DELEGATE_WM_CTLCOLORBTN(hdc, hwndChild, fn) \
    (HBRUSH)(UINT)(DWORD)(fn)(WM_CTLCOLORBTN, (WPARAM)(HDC)(hdc), (LPARAM)(HWND)(hwndChild))

#define DISPATCH_WM_CTLCOLORDLG(wParam, lParam, fn) \
    (LRESULT)(DWORD)(UINT)(HBRUSH)(fn)((HDC)(wParam), (HWND)(lParam), CTLCOLOR_DLG)
#define DELEGATE_WM_CTLCOLORDLG(hdc, hwndChild, fn) \
    (HBRUSH)(UINT)(DWORD)(fn)(WM_CTLCOLORDLG, (WPARAM)(HDC)(hdc), (LPARAM)(HWND)(hwndChild))

#define DISPATCH_WM_CTLCOLORSCROLLBAR(wParam, lParam, fn) \
    (LRESULT)(DWORD)(UINT)(HBRUSH)(fn)((HDC)(wParam), (HWND)(lParam), CTLCOLOR_SCROLLBAR)
#define DELEGATE_WM_CTLCOLORSCROLLBAR(hdc, hwndChild, fn) \
    (HBRUSH)(UINT)(DWORD)(fn)(WM_CTLCOLORSCROLLBAR, (WPARAM)(HDC)(hdc), (LPARAM)(HWND)(hwndChild))

#define DISPATCH_WM_CTLCOLORSTATIC(wParam, lParam, fn) \
    (LRESULT)(DWORD)(UINT)(HBRUSH)(fn)((HDC)(wParam), (HWND)(lParam), CTLCOLOR_STATIC)
#define DELEGATE_WM_CTLCOLORSTATIC(hdc, hwndChild, fn) \
    (HBRUSH)(UINT)(DWORD)(fn)(WM_CTLCOLORSTATIC, (WPARAM)(HDC)(hdc), (LPARAM)(HWND)(hwndChild))

/* void Cls:OnSetFont(Ctl, HFONT hfont, BOOL fRedraw) */
#define DISPATCH_WM_SETFONT(wParam, lParam, fn) \
    ((fn)((HFONT)(wParam), (BOOL)(lParam)), 0L)
#define DELEGATE_WM_SETFONT(hfont, fRedraw, fn) \
    (void)(fn)(WM_SETFONT, (WPARAM)(HFONT)(hfont), (LPARAM)(BOOL)(fRedraw))

/* HFONT Cls:OnGetFont() */
#define DISPATCH_WM_GETFONT(wParam, lParam, fn) \
    (LRESULT)(DWORD)(UINT)(HFONT)(fn)(hwnd)
#define DELEGATE_WM_GETFONT(fn) \
    (HFONT)(UINT)(DWORD)(fn)(WM_GETFONT, 0L, 0L)

/* void Cls:OnDrawItem(const DRAWITEMSTRUCT * lpDrawItem) */
#define DISPATCH_WM_DRAWITEM(wParam, lParam, fn) \
    ((fn)((const DRAWITEMSTRUCT *)(lParam)), 0L)
#define DELEGATE_WM_DRAWITEM(lpDrawItem, fn) \
    (void)(fn)(WM_DRAWITEM, (WPARAM)(((const DRAWITEMSTRUCT *)lpDrawItem)->CtlID), (LPARAM)(const DRAWITEMSTRUCT *)(lpDrawItem))

/* void Cls:OnMeasureItem(MEASUREITEMSTRUCT * lpMeasureItem) */
#define DISPATCH_WM_MEASUREITEM(wParam, lParam, fn) \
    ((fn)((MEASUREITEMSTRUCT *)(lParam)), 0L)
#define DELEGATE_WM_MEASUREITEM(lpMeasureItem, fn) \
    (void)(fn)(WM_MEASUREITEM, (WPARAM)(((MEASUREITEMSTRUCT *)lpMeasureItem)->CtlID), (LPARAM)(MEASUREITEMSTRUCT *)(lpMeasureItem))

/* void Cls:OnDeleteItem(const DELETEITEMSTRUCT * lpDeleteItem) */
#define DISPATCH_WM_DELETEITEM(wParam, lParam, fn) \
    ((fn)((const DELETEITEMSTRUCT *)(lParam)), 0L)
#define DELEGATE_WM_DELETEITEM(lpDeleteItem, fn) \
    (void)(fn)(WM_DELETEITEM, (WPARAM)(((const DELETEITEMSTRUCT *)(lpDeleteItem))->CtlID), (LPARAM)(const DELETEITEMSTRUCT *)(lpDeleteItem))

/* int Cls:OnCompareItem(const COMPAREITEMSTRUCT * lpCompareItem) */
#define DISPATCH_WM_COMPAREITEM(wParam, lParam, fn) \
    (LRESULT)(DWORD)(int)(fn)((const COMPAREITEMSTRUCT *)(lParam))
#define DELEGATE_WM_COMPAREITEM(lpCompareItem, fn) \
    (int)(DWORD)(fn)(WM_COMPAREITEM, (WPARAM)(((const COMPAREITEMSTRUCT *)(lpCompareItem))->CtlID), (LPARAM)(const COMPAREITEMSTRUCT *)(lpCompareItem))

/* int Cls:OnVkeyToItem(UINT vk, HWND hwndListbox, int iCaret) */
#define DISPATCH_WM_VKEYTOITEM(wParam, lParam, fn) \
    (LRESULT)(DWORD)(int)(fn)((UINT)LOWORD(wParam), (HWND)(lParam), (int)(short)HIWORD(wParam))
#define DELEGATE_WM_VKEYTOITEM(vk, hwndListBox, iCaret, fn) \
    (int)(DWORD)(fn)(WM_VKEYTOITEM, MAKEWPARAM((vk), (iCaret)), (LPARAM)(hwndListBox))

/* int Cls:OnCharToItem(UINT ch, HWND hwndListbox, int iCaret) */
#define DISPATCH_WM_CHARTOITEM(wParam, lParam, fn) \
    (LRESULT)(DWORD)(int)(fn)((UINT)LOWORD(wParam), (HWND)(lParam), (int)(short)HIWORD(wParam))
#define DELEGATE_WM_CHARTOITEM(ch, hwndListBox, iCaret, fn) \
    (int)(DWORD)(fn)(WM_CHARTOITEM, MAKEWPARAM((UINT)(iCaret), (UINT)(ch)), (LPARAM)(hwndListBox))

/* void Cls:OnQueueSync() */
#define DISPATCH_WM_QUEUESYNC(wParam, lParam, fn) \
    ((fn)(), 0L)
#define DELEGATE_WM_QUEUESYNC(fn) \
    (void)(fn)(WM_QUEUESYNC, 0L, 0L)
#if (WINVER >= 0x030a)
/* void Cls:OnCommNotify(int cid, UINT flags) */
#define DISPATCH_WM_COMMNOTIFY(wParam, lParam, fn) \
    ((fn)((int)(wParam), (UINT)LOWORD(lParam)), 0L)
#define DELEGATE_WM_COMMNOTIFY(cid, flags, fn) \
    (void)(fn)(WM_COMMNOTIFY, (WPARAM)(cid), MAKELPARAM((flags), 0))
#endif


#ifndef FIELDOFFSET
#define FIELDOFFSET(type, field)    ((int)(&((type NEAR*)1)->field)-1)
#endif

#endif /* !OWIWRAP_HPP */
