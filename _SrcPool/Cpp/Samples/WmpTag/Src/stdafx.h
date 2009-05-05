/*$RCSfile: stdafx.h,v $: header file
  $Revision: 1.2 $  $Date: 2009/05/05 20:15:34 $

  STandarD Application Template Library
  header file includes standard system header files or project specific header
  files that are used frequently, but are changed infrequently.
*/

#pragma once

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

//Note: Change these values to use different versions
#define WINVER        0x0500
#define _WIN32_WINNT  0x0501    //Windows XP and Windows .NET Server
#define _WIN32_IE     0x0501
#define _RICHEDIT_VER 0x0200

#ifdef __cplusplus
  #include <iostream>
  #include <tchar.h>
  //Active Template Libaray (ATL)
  #define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS //Some CString constructors will be explicit
  #include <atlbase.h>
  #include <atlwin.h> 
  #include <atlstr.h>

  #include "KTraceAtl.h"
  //Windows Template Library (WTL) header files
  #define _WTL_NO_CSTRING
#endif

///////////////////////////////////////////////////////////////////////////////
//Project specific header files

/******************************************************************************
 * $Log: stdafx.h,v $
 * Revision 1.2  2009/05/05 20:15:34  ddarko
 * *** empty log message ***
 *
 ******************************************************************************/
