// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#define VC_EXTRALEAN    // Exclude rarely-used stuff from Windows headers

#include <AfxWin.h>         // MFC core and standard components
#include <AfxExt.h>         // MFC extensions
#ifndef _AFX_NO_AFXCMN_SUPPORT
  #include <AfxCmn.h>      // MFC support for Windows 95 Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#pragma comment( user, "Compiled on " __DATE__ " at " __TIME__ )

///////////////////////////////////////////////////////////////////////////////
//Function declarations
BOOL TestWinOS();
BOOL GetWindowsVersion (CString& strWinVersion);