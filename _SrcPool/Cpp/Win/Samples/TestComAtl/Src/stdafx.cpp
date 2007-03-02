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

/*Group COM classes into categories when the module is registered.
  If Standard Component Categories Manager is installed on the system, each 
  class that has an associated OBJECT_ENTRY_AUTO or 
  OBJECT_ENTRY_NON_CREATEABLE_EX_AUTO will be categorized.
  {BAB17049-D0DE-4241-4149-4C4F4E4C4942}
 */
static const GUID CATID_BABYLONLIB = 
  { 0xBAB170499, 0xD0DE, 0x4241, { 0x41,0x49,0x4C,0x4F,0x4E,0x4C,0x49,0x42 } };
/*Group COM classes into categories when the module is registered.
  If Standard Component Categories Manager is installed on the system, each 
  class that has an associated OBJECT_ENTRY_AUTO or 
  OBJECT_ENTRY_NON_CREATEABLE_EX_AUTO will be categorized.
  {BAB17049-D0DE-4886-A995-6E2BE7F1E7E22}
*/
static const GUID CATID_BABYLONLIBTEST = 
  { 0xBAB170499, 0xD0DE, 0x4886, { 0xA9,0x95,0x6E,0x2B,0xE7,0xF1,0xE7,0xE2 } };
