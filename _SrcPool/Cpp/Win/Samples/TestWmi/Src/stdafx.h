/*$RCSfile: stdafx.h,v $: header file
  $Revision: 1.1 $  $Date: 2010/01/21 22:18:19 $

  STandarD Application Template Library
  header file includes standard system header files or project specific header
  files that are used frequently, but are changed infrequently.
*/

#pragma once

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

//Note: Modify the following defines if you have to target a platform prior to
//the ones specified below. Refer to MSDN for the latest info on corresponding
//values for different platforms.
#ifndef WINVER  //Allow use of features specific to Windows XP or later.
  #define WINVER 0x0501 //Change this to the appropriate value to target
                        //other versions of Windows.
#endif

#ifndef _WIN32_WINNT  //Allow use of features specific to Windows XP or later.
  #define _WIN32_WINNT 0x0501 //Windows XP and Windows .NET Server
#endif

#ifndef _WIN32_WINDOWS  //Allow use of features specific to Windows 98 or later.
  #define _WIN32_WINDOWS 0x0410 //Change this to the appropriate value to target 
                                //Windows Me or later.
#endif

#ifndef _WIN32_IE         //Allow use of features specific to IE 6.0 or later.
  #define _WIN32_IE 0x0600  //Change this to the appropriate value to target
                            //other versions of IE.
#endif

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#include <stdio.h>
#include <tchar.h>

#ifdef __cplusplus
  #include <iostream>
  //Active Template Libaray (ATL)
  #define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS //Some CString constructors will be explicit
  #include <atlbase.h>
  //#include <atlwin.h> 
  #include <atlstr.h>

  #include "KTraceAtl.h"
  //Windows Template Library (WTL) header files
  #define _WTL_NO_CSTRING
#endif

///////////////////////////////////////////////////////////////////////////////
//Project specific header files

/******************************************************************************
 * $Log: stdafx.h,v $
 * Revision 1.1  2010/01/21 22:18:19  ddarko
 * Created
 *
 ******************************************************************************/
