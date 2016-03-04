#include <stdio.h>
#include <windows.h>
#include <windowsx.h>
#include <strsafe.h>
//#include "resource.h"
#include "umsw3gl.h"

#include <Commctrl.h>
#pragma comment(lib, "Comctl32.lib")

// Enable Visual Style
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#pragma endregion

#ifdef __cplusplus
extern "C"
{
#endif

XEXPORT(long) notifyWindow(LPCWSTR windowName, char* text);
XEXPORT(long) notifyWindowHndl(HWND hwnd, char* text);
XEXPORT(long) hookWindow(HWND hwnd);
XEXPORT(long) getUnifaceChildWindows();
BOOL CALLBACK EnumUnifaceChildWindowsProc(HWND hwnd, LPARAM lparam);
LRESULT CALLBACK HookWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#ifdef __cplusplus
}
#endif

WNDPROC	originalAppWndProc;
WNDPROC	originalWndProc;
typedef struct tagMYREC
{
	char  message[16384];
	HWND  messageSource;
	int   messageLength;
} MYREC;


HRESULT hResult;

MYREC MyRec;
#define MYDISPLAY 1;
#define REG0  50                       
#define REG1  50+1
//
//   FUNCTION: ReportError(LPWSTR, DWORD)
//
//   PURPOSE: Display an error dialog for the failure of a certain function.
//
//   PARAMETERS:
//   * pszFunction - the name of the function that failed.
//   * dwError - the Win32 error code. 
//
void ReportError(LPCWSTR pszFunction, DWORD dwError = NO_ERROR)
{
    wchar_t szMessage[200];
    if (dwError == NO_ERROR)
    {
        StringCchPrintf((STRSAFE_LPWSTR) szMessage, ARRAYSIZE(szMessage), 
			(STRSAFE_LPWSTR)"%s failed", pszFunction);
    }
    else 
    {
		StringCchPrintf((STRSAFE_LPWSTR)szMessage, ARRAYSIZE(szMessage),
			(STRSAFE_LPWSTR)"%s failed w/err 0x%08lx", pszFunction, dwError);
    }

	MessageBox(NULL, (STRSAFE_LPWSTR)szMessage, (STRSAFE_LPWSTR)"Error", MB_ICONERROR);
}

XEXPORT(long) notifyWindow(LPCWSTR windowName, char* text) {


		COPYDATASTRUCT cds;
		hResult = StringCbCopy((STRSAFE_LPWSTR)MyRec.message, sizeof(MyRec.message), (STRSAFE_LPWSTR)text);
		MyRec.messageLength = strlen(text);
		MyRec.messageSource = ugethwnd();

		cds.dwData = MYDISPLAY;        // function identifier
		cds.cbData = sizeof(MyRec);  // size of data
		cds.lpData = &MyRec;           // data structure

		SendMessage(FindWindow(L"UniApplication", windowName), WM_COPYDATA, (WPARAM)cds.cbData, (LPARAM)(LPVOID)&cds);
		return strlen(text);
	return 0;
}
XEXPORT(long) notifyWindowHndl(HWND hwnd, char* text) {


	COPYDATASTRUCT cds;
	hResult = StringCbCopy((STRSAFE_LPWSTR)MyRec.message, sizeof(MyRec.message), (STRSAFE_LPWSTR)text);
	MyRec.messageLength = strlen(text);
	MyRec.messageSource = ugethwnd();

	cds.dwData = MYDISPLAY;        // function identifier
	cds.cbData = sizeof(MyRec);  // size of data
	cds.lpData = &MyRec;           // data structure

	SendMessage(hwnd, WM_COPYDATA, (WPARAM)cds.cbData, (LPARAM)(LPVOID)&cds);
	return strlen(text);
	return 0;
}

XEXPORT(long) hookWindow(HWND hwnd)
{
	LPSTR	className[255];
	USTRING	name[255] = "";
	UPROC	hookWndProc = NULL;
	char    messageData[16384];

	className[0] = 0;
	GetClassNameA((HWND) hwnd, (LPSTR) className, sizeof(className)-1);
	ugetname((HWND) hwnd, (USTRING*) name, sizeof(name)-1);
	sprintf_s(messageData, 300, "Processing window [%4X] with the name %s and class %s\n", hwnd, (unsigned char *) name, (unsigned char *) className);
	(void)uputames((unsigned char *)&messageData, sizeof(messageData));
	hookWndProc = (UPROC) UMAKEPROCINST((UPROC) HookWndProc);
	WNDPROC originalWndProc = reinterpret_cast<WNDPROC>(SetWindowLong(hwnd, GWL_WNDPROC, reinterpret_cast<LONG_PTR>(hookWndProc)));
    SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(originalWndProc));
	return 0;
}

/*
XEXPORT(long) getUnifaceChildWindows()
{
	HWND    hApp;
	UPROC	hookWndProc = NULL;

	hApp = ugethwnd(); // Get application window handle
    EnumChildWindows(hApp, EnumUnifaceChildWindowsProc, 0); 

	return 0;
}

BOOL CALLBACK EnumUnifaceChildWindowsProc(HWND hwndChild, LPARAM lParam) 
{
	LPSTR	className[255];
	USTRING	name[255] = "";
	UPROC	hookWndProc = NULL;
	char    messageData[300];

	className[0] = 0;
	GetClassNameA((HWND) hwndChild, (LPSTR) className, sizeof(className)-1);
	if (_stricmp((const char *) className, "UniMDIForm") == 0 || _stricmp((const char *) className, "UniCanvas") == 0)
	{
		ugetname((HWND) hwndChild, (USTRING*) name, sizeof(name)-1);
		//u_printf("Processing window [%4X] with the name %s\n", hwndChild, (unsigned char *) name);
		sprintf_s(messageData, 300, "Processing window [%4X] with the name %s\n", hwndChild, (unsigned char *) name);
		(void)uputames((unsigned char *)&messageData, sizeof(messageData));
		hookWndProc = (UPROC) UMAKEPROCINST((UPROC) HookWndProc);
		WNDPROC originalWndProc = reinterpret_cast<WNDPROC>(SetWindowLong(hwndChild, GWL_WNDPROC, reinterpret_cast<LONG_PTR>(hookWndProc)));
		SetWindowLongPtr(hwndChild, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(originalWndProc));
	}
	return TRUE;
}
*/

//______________________________________________________________________
// HookWndProc
//
// The hook in window procedure for Uniface.  This intercepts
// windows messages before they are processed by the standard
// Uniface windows procedure.
//______________________________________________________________________

LRESULT CALLBACK HookWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	char messageData[16384];
	RECT rcClient;
	LPSTR	className[255];
	HWND hwndParent;

    // Retrieve the previously stored original button window procedure.
    WNDPROC originalWndProc = reinterpret_cast<WNDPROC>(
        GetWindowLongPtr(hwnd, GWLP_USERDATA));

	switch (uMsg) 
	{
	/*
		case WM_ENTERSIZEMOVE:
			strcpy(messageData, "WM_ENTERSIZEMOVE");
			(void)uputames((unsigned char *)&messageData, sizeof(messageData));
			break;

		case WM_SIZING:
			GetWindowRect(hwnd, &rcClient);
			sprintf(messageData, "WM_SIZING=LEFT[%i];TOP=[%i];RIGHT[%i];BOTTOM[%i]", rcClient.left, rcClient.top, rcClient.right, rcClient.bottom);
			(void)uputames((unsigned char *)&messageData, sizeof(messageData));
			break;
	*/

		case WM_EXITSIZEMOVE:
			//strcpy(messageData, "WM_EXITSIZEMOVE");
			GetWindowRect(hwnd, &rcClient);
			sprintf_s(messageData, 64, "WM_EXITSIZEMOVE=LEFT[%i];TOP=[%i];RIGHT[%i];BOTTOM[%i]", rcClient.left, rcClient.top, rcClient.right, rcClient.bottom);
			(void)uputames((unsigned char *)&messageData, sizeof(messageData));
			break;

		case WM_LBUTTONDOWN:
			strcpy_s(messageData, "WM_LBUTTONDOWN");
			(void)uputames((unsigned char *)&messageData, sizeof(messageData));
			hwndParent = hwnd;
			className[0] = 0;
			GetClassNameA((HWND) hwndParent, (LPSTR) className, sizeof(className)-1);
			//while (_stricmp((const char *) className, "UniMDIForm") != 0)
			while (_stricmp((const char *) className, "UniApplication") != 0)
			{
				hwndParent = GetParent(hwndParent);
				className[0] = 0;
				GetClassNameA((HWND) hwndParent, (LPSTR) className, sizeof(className)-1);
			}
			ReleaseCapture ();
			SendMessage (hwndParent, WM_NCLBUTTONDOWN, HTCAPTION, 0);
			(void)uputames((unsigned char *)"SetFocus", 8);
			break;

		case WM_LBUTTONDBLCLK:
			strcpy_s(messageData, "WM_LBUTTONDBLCLK");
			(void)uputames((unsigned char *)&messageData, sizeof(messageData));
			
			break;

		case WM_NCDESTROY:

	        // You must remove your window subclass before the window being 
		    // subclassed is destroyed. 
			if (0 == SetWindowLongPtr(hwnd, GWLP_WNDPROC, 
				reinterpret_cast<LONG_PTR>(originalWndProc)))
	        {
		        ReportError(L"SetWindowLongPtr in handling WM_NCDESTROY",
			        GetLastError());
	        }
		    return 0;
	}
	// Regardless of the message, leave the handling to Uniface.
	return CallWindowProc(originalWndProc, hwnd, uMsg, wParam, lParam);

}

//______________________________________________________________________
// HookWndProc
//
// The hook in window procedure for Uniface.  This intercepts
// windows messages before they are processed by the standard
// Uniface windows procedure.
//______________________________________________________________________

LRESULT CALLBACK HookAppWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	char messageData[16384];
	PCOPYDATASTRUCT pMyCDS;
	RECT rcClient;

	switch (uMsg) 
	{
	/*
		case WM_ENTERSIZEMOVE:
			strcpy(messageData, "WM_ENTERSIZEMOVE");
			(void)uputames((unsigned char *)&messageData, sizeof(messageData));
			break;

		case WM_SIZING:
			GetWindowRect(hwnd, &rcClient);
			sprintf(messageData, "WM_SIZING=LEFT[%i];TOP=[%i];RIGHT[%i];BOTTOM[%i]", rcClient.left, rcClient.top, rcClient.right, rcClient.bottom);
			(void)uputames((unsigned char *)&messageData, sizeof(messageData));
			break;
	*/
		case WM_EXITSIZEMOVE:
			//strcpy(messageData, "WM_EXITSIZEMOVE");
			GetWindowRect(hwnd, &rcClient);
			sprintf_s(messageData, 64, "WM_EXITSIZEMOVE=LEFT[%i];TOP=[%i];RIGHT[%i];BOTTOM[%i]", rcClient.left, rcClient.top, rcClient.right, rcClient.bottom);
			(void)uputames((unsigned char *)&messageData, sizeof(messageData));
			break;
		case WM_COPYDATA:
/*			int  msgLen; */
			pMyCDS = (PCOPYDATASTRUCT)lParam;
/*			msgLen = pMyCDS->cbData;           */
/*			(void)uputames((unsigned char *)pMyCDS->lpData, msgLen);  */
			(void)uputames((unsigned char *)(LPSTR)pMyCDS->lpData, (short)(LPSTR)pMyCDS->cbData);
			UPUTREGS(REG0, (unsigned char *)(LPSTR)pMyCDS->lpData);
			char dataCount[10];
			sprintf_s(dataCount, "%d", pMyCDS->cbData);
			UPUTREGS(REG1, (unsigned char *)dataCount);
			break;
/*		case WM_LBUTTONDOWN:
			strcpy_s(messageData, "WM_LBUTTONDOWN");
			(void)uputames((unsigned char *)&messageData, sizeof(messageData));
			ReleaseCapture ();
			SendMessage (hwnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
			break; */
	}
	// Regardless of the message, leave the handling to Uniface.
	return CallWindowProc(originalAppWndProc, hwnd, uMsg, wParam, lParam);

}

//______________________________________________________________________
// UDLLEVENT
//
// Handle DLL load/unload events.  Hook in the replacement for the
// Uniface window procedure (a process called "subclassing").
//
// Input
// wEvent - Event code:
//          UEVT_INITDLL     The DLL is loaded by Windows
//          UEVT_INITCLIENT  A Uniface application connects to the DLL
//          UEVT_INITGUI     Interactive mode starts
//          UEVT_EXITGUI     Interactive mode ends
//          UEVT_EXITCLIENT  A Uniface application disconnects from the DLL
//          UEVT_EXITDLL     The DLL is unloaded by Windows
//
// Output
// SUCCESS  Accept the load or connect attempt
// FAILURE  Reject the load or connect attempt
// Ignored for other events
//______________________________________________________________________

short X3GL UDLLEVENT(short sEvent)
{
	HWND	hWnd;
	UPROC	hookAppWndProc = NULL;

	switch (sEvent)
	{
		case UEVT_INITGUI:
			hWnd = ugethwnd();
			// Set the window hook procedure to trap the WM_TIMER message.
			hookAppWndProc = (UPROC) UMAKEPROCINST((UPROC) HookAppWndProc);
			originalAppWndProc = (WNDPROC) SetWindowLong(hWnd, GWL_WNDPROC, (long) hookAppWndProc);
			break;
		case UEVT_EXITGUI:
			// End of the interactive session.
			UFREEPROCINST(hookAppWndProc);
			break;
	}
	return SUCCESS;
}