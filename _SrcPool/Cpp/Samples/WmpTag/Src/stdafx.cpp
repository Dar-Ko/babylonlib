/*$RCSfile: stdafx.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2009/05/05 20:15:34 $
  $Author: ddarko $

  Includes just the standard header files, producing the pre-compiled header
  .pch file
 */

#include "stdafx.h"
#include "KDbgMacr.h" //Dumps values of some compiler-specific predefined macros

#if (_ATL_VER < 0x0700)
  #include <atlimpl.cpp>
#endif //(_ATL_VER < 0x0700)
