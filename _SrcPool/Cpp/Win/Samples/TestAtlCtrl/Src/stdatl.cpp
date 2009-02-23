/*$RCSfile: stdatl.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2009/02/23 16:34:17 $
  $Author: ddarko $

  Includes just the standard header files, producing the pre-compiled header
  .pch file
 */

#include "stdatl.h"
#include "KDbgMacr.h" //Dumps values of some compiler-specific predefined macros

#if (_ATL_VER < 0x0700)
  #include <atlimpl.cpp>
#endif //(_ATL_VER < 0x0700)
