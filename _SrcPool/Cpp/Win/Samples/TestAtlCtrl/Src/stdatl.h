/*$RCSfile: stdatl.h,v $: header file
  $Revision: 1.2 $  $Date: 2009/02/23 16:34:17 $

  STandarD Application Template Library
  header file includes standard system header files, or project specific header
  files that are used frequently, but are changed infrequently.
*/

#pragma once

//Note: Change these values to use different versions
#define WINVER        0x0500
#define _WIN32_WINNT  0x0501    //Windows XP and Windows .NET Server
#define _WIN32_IE     0x0501
#define _RICHEDIT_VER 0x0200

#ifdef __cplusplus
  #include <atlbase.h>
  #include <atlwin.h> //ATL

  //Windows Template Library (WTL) header files
  #include "atlapp.h"  //CAppModule template (WTL)
  extern CAppModule _Module;    //application's main module

  #include "atlframe.h"
  #include "atlctrls.h"
  #include "atldlgs.h"
#endif

///////////////////////////////////////////////////////////////////////////////
//Project specific header files
#include "KTrace.h"   /*ASSERT_CL macro                         */
#include "KTestLog.h" /*CTestLog class                          */

/******************************************************************************
 * $Log: stdatl.h,v $
 * Revision 1.2  2009/02/23 16:34:17  ddarko
 * Sorted include files
 *
 ******************************************************************************/
