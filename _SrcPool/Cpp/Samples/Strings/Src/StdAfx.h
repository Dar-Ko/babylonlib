// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#ifdef _MSC_VER
  #pragma comment( user, "Compiled on " __DATE__ " at " __TIME__ )
#endif

#define VC_EXTRALEAN    // Exclude rarely-used stuff from Windows headers

#ifdef _AFXDLL
  #include <AfxWin.h>         // MFC core and standard components
  #include <AfxExt.h>         // MFC extensions
  #ifndef _AFX_NO_AFXCMN_SUPPORT
    #include <AfxCmn.h>      // MFC support for Windows 95 Common Controls
  #endif // _AFX_NO_AFXCMN_SUPPORT
#else
  #ifdef VXWORKS /* VxWorks OS */
    #include <vxTypesOld.h> /*BOOL typedef */
  #endif
  #include "KTypedef.h"  //BOOL typedef
#endif //_AFXDLL


///////////////////////////////////////////////////////////////////////////////
//Function declarations
BOOL TestStrings();
void TestReplaceEscapeSeq();
