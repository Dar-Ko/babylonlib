/*$Workfile: StdPfhR.h$: header file
  $Revision: 3$  $Date: 2004-10-27 18:16:57$

  Codewarrior standard prefix header file included before each source code
  Release Mode
  Copyright: CommonSoft Inc.
  Darko Kolakovic 2004-10-21
*/
/* Group=Diagnostic                                                          */


#ifdef __MWERKS__ /* Metrowerks CodeWarrior Compiler                    */
/* Note: to include this project settings before each source code file,
   open in CodeWarrior IDE following menu item:
      Edit : <project name> Settings... |
      Language Settings | C/C++ Language | Prefix file
      and type in edit box the name of this file
 */

  #if __MWERKS__ >= 0x3000
    #pragma once
  #endif //__MWERKS__ >= 0x3000

  #if !defined(_STDPFHR_H_)
    //$Workfile: StdPfhR.h$ sentry
    #define _STDPFHR_H_

  #if (__dest_os == __palm_os)
    #ifndef __PALMOS__
      #define __PALMOS__ PALMOS_SDK_VERSION
    #endif
  #endif
  
  #define NDEBUG
  #undef DEBUG
  #undef _DEBUG
  #undef _MSL_DEBUG

  #define UNICODE
  #define _UNICODE

  #ifndef ERROR_CHECK_LEVEL
    #define ERROR_CHECK_LEVEL ERROR_CHECK_NONE
  #endif

  #include "stdafx.h"

  #endif //_STDPFHR_H_
#endif //__MWERKS__
////////////////////////////////////////////////////////////////////////////////
