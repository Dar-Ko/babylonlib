/*$RCSfile: KDbgMacrMsvc.h,v $: header file
  $Revision: 1.1 $ $Date: 2008/09/09 19:52:31 $
  $Author: ddarko $

  Dumps values of some Microsoft specific predefined macros
  Copyright: CommonSoft Inc.
  Darko Kolakovic April 1988, 2008-09
*/
/* Group=Diagnostic                                                          */

#ifndef _KDBGMACRMSVC_H_
    /*$RCSfile: KDbgMacrMsvc.h,v $ sentry */
  #define _KDBGMACRMSVC_H_

#ifdef _MSC_VER /*Microsoft Visual C/C++ Compiler pragmas                     */

  #if _MSC_VER > 1000
    #pragma once
  #endif // _MSC_VER > 1000

  #ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
    #pragma message ("   #include " __FILE__ )
  #endif

  /*Microsoft-Specific macros ---------------------------------------------- */

  #if _MSC_VER >= 1300
    #pragma message ("Microsoft Visual C++.NET compiler")
  #else
    #if _MSC_VER >= 800
      #pragma message ("Microsoft Visual C/C++ compiler")
    #else
     #if _MSC_VER > 600
       #pragma message ("Microsoft C/C++ compiler")
      #else
        #pragma message ("Microsoft C compiler")
      #endif
    #endif
  #endif

 /*Current version of Microsoft compiler.
   The _MSC_VER macro will have one of the following values depending upon
   the particular Microsoft compiler:

      Compiler                             _MSC_VER value

      C Compiler version 6.0                     600
      C/C++ compiler version 7.0                 700
      Visual C++, Windows, version 1.0           800
      Visual C++, 32-bit, version 1.0            800
      Visual C++, Windows, version 1.5           850
      Visual C++, Windows, version 2.0           900
      Visual C++, 32-bit, version 2.x            900
      Visual C++, 32-bit, version 4.0           1000
      Visual C++, 32-bit, version 4.2           1020
      Visual C++, 32-bit, version 5.0           1100
      Visual C++, 32-bit, version 6.0           1200
      Visual C++ .Net 2002, 32-bit, version 7.0 1300
      Visual C++ .Net 2003, 32-bit, version 7.1 1310
      Visual C/C++ 2005, version 8.0            1400

   See also: Q65472
  */
  const int g__MSC_VER = _MSC_VER;
  #if _MSC_VER == 600
    #pragma message ("  ver. 6.0")
    #define DBGMSC_VER 0x0600 /*Trace MSVC version*/
  #endif
  #if _MSC_VER == 700
    #pragma message ("  ver. 7.0")
    #define DBGMSC_VER 0x0700 /*Trace MSVC version*/
  #endif
  #if _MSC_VER == 800
    #pragma message ("  ver. 1.0")
    #define DBGMSC_VER 0x0800 /*Trace MSVC version*/
  #endif
  #if _MSC_VER == 850
    #pragma message ("  ver. 1.5")
    #define DBGMSC_VER 0x0850 /*Trace MSVC version*/
  #endif
  #if _MSC_VER == 900
    #pragma message ("  ver. 2.0")
    #define DBGMSC_VER 0x0900 /*Trace MSVC version*/
  #endif
  #if _MSC_VER == 1000
    #pragma message ("  ver. 4.0")
    #define DBGMSC_VER 0x1000 /*Trace MSVC version*/
  #endif
  #if _MSC_VER == 1020
    #pragma message ("  ver. 4.2")
    #define DBGMSC_VER 0x1200 /*Trace MSVC version*/
  #endif
  #if _MSC_VER == 1100
    #pragma message ("  ver. 5.0")
    #define DBGMSC_VER 0x1100 /*Trace MSVC version*/
  #endif
  #if _MSC_VER == 1200
    #pragma message ("  ver. 6.0")
    #define DBGMSC_VER 0x1200 /*Trace MSVC version*/
  #endif
  #if _MSC_VER == 1210
    #pragma message ("  ver. 6.1")
    #define DBGMSC_VER 0x1210 /*Trace MSVC version*/
  #endif
  #if _MSC_VER == 1300
    #pragma message ("  2002 ver. 7.0")
    #define DBGMSC_VER 0x1300 /*Trace MSVC version*/
  #endif
  #if _MSC_VER == 1310
    #pragma message ("  2003 ver. 7.1")
    #define DBGMSC_VER 0x1310 /*Trace MSVC version*/
  #endif
  #if _MSC_VER == 1400
    #pragma message ("  2005 ver. 8.0")
    #define DBGMSC_VER 0x1400 /*Trace MSVC version*/
  #endif
  #ifndef DBGMSC_VER
    #pragma message ("  ver. unknown")
  #endif

  /*--------------------------------------------------------------------------*/
  /*Compilation conditions
   */
  #ifdef _DEBUG
     #pragma message ("Debug version")
  #else
    #pragma message ("Release version")
  #endif
  /*Preprocessor Directives for Generic-Text Mappings                      */
  #if defined UNICODE || defined _UNICODE
    /*Unicode character (16-bit)
      ISO 10646-1 Universal Multiple Octet Coded Character Set (UCS).
     */
    #pragma message ("Unicode (wide-character) text mapping")
  #endif
  #if defined _MBCS && !defined _UNICODE
    #pragma message ("Multibyte-character text mapping")
  #endif
  #if !defined _MBCS && !defined _UNICODE
    /*ASCII character (8-bit)*/
    #pragma message ("Singlebyte-character (SBCS or ASCII) text mapping")
  #endif

#ifdef _MSC_EXTENSIONS
    #pragma message ("Enabled compiler extensions.")
  #endif
  #ifdef _CPPUNWIND
    #pragma message ("Enabled Exception Handling.")
  #endif
  #ifdef _CPPRTTI
    #pragma message ("Enabled Run-Time Type Information.")
  #endif
  #ifdef _MT
    /*Defined when /MD or /MDd (Multithreaded DLL) or /MT
     or /MTd (Multithreaded) is specified.*/
    #pragma message ("Enabled Multithreading.")
  #else
    #ifndef _STH
      #define _STH 1998
    #endif
    #pragma message ("Single-threaded application.")
  #endif
  #ifdef _DLL
    #pragma message ("Multithread DLL is specified.")
  #endif

  /*--------------------------------------------------------------------------
    Microsoft Visual Studio 2005 v8.0
    Windows Mobile, Windows Embedded CE
   */
  #ifdef _CRT_SECURE_NO_DEPRECATE
    /*The C Runtime (CRT) library is enhanced with more secure function versions.
      If a new secure function exists, the older, less secure version is marked 
      as deprecated and the new version has the _s ("secure") suffix.
      To disable the deprecation warnings, define _CRT_SECURE_NO_DEPRECATE or
      use the warning pragma. 
     */
    #pragma message ("Unsecure CRT deprecation warnings disabled.")
  #endif
  #ifdef _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES
    #pragma message ("CRT Secure Template Overloads defined;")
    #if _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES == 1
      /*To overload unsecure C Runtime (CRT) library functions with enhanced
        versions, define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES as 1.
       */
      #pragma message ("Use CRT Secure Template Overloads (C++).")
    #endif
  #endif

#endif /*_MSC_VER */

/* ///////////////////////////////////////////////////////////////////////// */
#endif /*_KDBGMACRMSVC_H_                                                     */
/*****************************************************************************
 * $Log: KDbgMacrMsvc.h,v $
 * Revision 1.1  2008/09/09 19:52:31  ddarko
 * Moved MSVC macros
 *
 *****************************************************************************/
