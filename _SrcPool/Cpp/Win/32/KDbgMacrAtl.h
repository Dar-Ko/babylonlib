/*$Workfile: S:\_SrcPool\Cpp\Win\32\KDbgMacrAtl.h$: header file
  $Revision: 1$ $Date: 2007-03-06 14:36:11$
  $Author: Darko Kolakovic$

  Dumps values of some compiler-specific predefined macros
  Copyright: CommonSoft Inc.
  Darko Kolakovic April 1988
*/
/* Group=Diagnostic                                                          */

#ifndef _KDBGMACR_H_
    /*$Workfile: S:\_SrcPool\Cpp\Win\32\KDbgMacrAtl.h$ sentry */
  #define _KDBGMACR_H_

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

