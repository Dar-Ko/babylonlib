// stdafx.cpp : source file that includes just the standard includes
//  stdafx.pch will be the pre-compiled header
//  stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include "KDbgMacr.h" //Dumps values of some compiler-specific predefined macros

#if _MSC_VER < 1300 //Microsoft Visual Studio .Net 2002 v7.0
  #define EXCLUDE_DEPRECATED //Excludes deprecated files
#endif

#ifdef _ATL_STATIC_REGISTRY
  #include <statreg.h>
  #ifndef EXCLUDE_DEPRECATED
    //Required with Microsoft Visual C/C++ 6.0
    #include <statreg.cpp>
  #endif
#endif

#ifndef EXCLUDE_DEPRECATED
  //Required with Microsoft Visual C/C++ 6.0
  #include <atlimpl.cpp>
#endif
