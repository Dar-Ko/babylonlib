/*$RCSfile: stdafx.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2010/01/21 22:18:19 $
  $Author: ddarko $

  Includes just the standard header files, producing the pre-compiled header
  .pch file
 */

#include "stdafx.h"
#include "KDbgMacr.h" //Dumps values of some compiler-specific predefined macros

#if (_ATL_VER < 0x0700)
  #include <atlimpl.cpp>
#endif //(_ATL_VER < 0x0700)
