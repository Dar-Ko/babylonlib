/*$RCSfile: stdafx.h,v $: header file
  $Revision: 1.3 $ $Date: 2008/07/15 20:37:10 $
  $Author: ddarko $

  Include file for standard system include files or project specific include
  files that are used frequently, but are changed infrequently.
  This is a part of the Active Template Library.
  Copyright: (C) 1996-1998 Microsoft Corporation. All rights reserved.
  PSDK 2006-03 (R2 3790.2075) Win DDK 2005-03 (3790.1830)
 */
// Group=Windows

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #ifdef _MSC_VER
    //Microsoft Visual C/C++ compiler
    #pragma message ("   #include " __FILE__ )
  #endif
#endif

#define _WIN32_WINNT 0x0500
#define _ATL_FREE_THREADED
#define _CONVERSION_USES_THREAD_LOCALE
#define _ATL_DLL_IMPL
//#define _ATL_DEBUG_QI

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <atlctl.h>
#include <statreg.h>

////////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: stdafx.h,v $
 * Revision 1.3  2008/07/15 20:37:10  ddarko
 * Borland CC build and fixes
 *
 * Revision 1.1.2.2  2008/07/15 15:42:57  ddarko
 * ATL 3.00 Platform SDK (R2 3790.2075) 2006-03 / Borland CC build
 *
 *****************************************************************************/
