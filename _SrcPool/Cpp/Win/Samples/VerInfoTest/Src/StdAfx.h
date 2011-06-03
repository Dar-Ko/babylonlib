/*$RCSfile: StdAfx.h,v $: header file
  $Revision: 1.3 $  $Date: 2011/06/03 17:17:36 $

  STandarD Application FrameworX
  header file includes standard system header files or project specific header
  files that are used frequently, but are changed infrequently.
*/

#define VC_EXTRALEAN    // Exclude rarely-used stuff from Windows headers

#include <AfxWin.h>         // MFC core and standard components
#include <AfxExt.h>         // MFC extensions
#ifndef _AFX_NO_AFXCMN_SUPPORT
  #include <AfxCmn.h>      // MFC support for Windows 95 Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#pragma comment( user, "Compiled on " __DATE__ " at " __TIME__ )
#include "KType32.h"
#include "KProgCst.h"

///////////////////////////////////////////////////////////////////////////////
//Function declarations
BOOL TestVerInfo();
