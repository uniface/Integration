/* @(#)CONT_ID %fv: omswmain.h-15:incl:1 % %dc: Wed Sep 10 09:33:39 2014 % (#)@ */

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
date    refnum  version who description                                       
050405  d21498  9.1.01  mab One function for safe Unicode conversion sizes.   
060127  c23103  9.1.01  jdk Impl of the richtext editor widget.                                                                                             
120928  b29801  R131    jxa Labels and fields with no color are printed with a white background
*****************************************************************************/

#ifdef __cplusplus                                                   // @pr15 - start
extern "C"
{
#endif                                                               // @pr15 - end

// -- Functions exported by OMSWMAIN

void ctlSetInfo(HWND hwndCtl, void *pInfo);
void *ctlGetInfo(HWND hwndCtl);
void ctlRemoveInfo(HWND hwndCtl);
HBRUSH ctlColorBrush(COLORREF clr);                                  // @pr8

void ShowWindowBetter(HWND hwndCtl, BOOL bShow);                     // @pr2
int ovrGenerate(WMLINK wmlink, int iCount);                          // @pr3
BOOL oxsValid(WMLINK wmlink, POCHR pochr);                           // @pr7
int ProfileEsc();                                                    // @pr9, @pr15
UTF16 UnicodeProfileEsc();
BOOL ContainsProfileChars(char * pszText);                           // @pr9
BOOL ContainsUnicodeProfileChars(UTF16* pszText);                    // pr19
char *GetClipboardString(HWND hWndWidget);                           // @pr9
UTF16 *GetUnicodeClipboardString(HWND hWndWidget);                   // @pr19
long GetCharHeight(HDC hDC, HFONT hFont);                            // @pr11
void ChangeChars(char * pszText, char ch);                           // @pr12
void ChangeUnicodeChars(UTF16* pszText, UTF16 ch);                   // @pr19


// -- Functions exported by individual widgets

short CheckNotify(short sReason);
short CmdBtnNotify(short sReason);                                   // @pr5
short DragDropNotify(short sReason);                                 // @pr4
short DropNotify(short sReason);
short EditNotify(short sReason);
short OwiNotify(short sReason);                                      // @b29801
short HotspotNotify(short sReason);                                  // @pr1
short LabelNotify(short sReason);
short ListNotify(short sReason);
short RadioNotify(short sReason);
short SpinNotify(short sReason);
short VbxNotify(short sReason);
short PictureNotify(short sReason);                                  // @pr6
short MeterNotify(short sReason);                                    // @pr10
short MapNotify(short sReason);                                      // @pr18

#ifdef V8
short RichNotify(short sReason);                                     // @pr16  procbox
/*
** RichTextNotify must be after RichNotify. RichNotify loads
** the necessary dll RICHED20.DLL.
*/
short RichTextNotify(short sReason);                                 // @c23103 rich text editor widget
short MonthCalNotify(short sReason);

#endif
//short SliderNotify(short sReason);                                   // @pr10,13
        
// -- Color defines                                                  // @pr11 - begin
#define BLACK          RGB(0,0,0)
#define WHITE          RGB(255,255,255)                              // @pr11 - end

#ifdef V8
// ugetappi() is defined in URTL (mswsys.c)
#else
#define ugetappi ugethinst
#endif


BOOL useSystemColors( void );                                        // @pr17

BOOL useTransparentColorNo( void );                                 // @b29801

#ifdef __cplusplus                                                   // @pr15 - start
}
#endif                                                               // @pr15 - end

// EOF OMSWMAIN.CPP
