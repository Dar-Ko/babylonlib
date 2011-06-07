/*$RCSfile: KDbgMacrMsvc.h,v $: header file
  $Revision: 1.3 $ $Date: 2011/06/07 19:41:14 $
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

  #if _MSC_VER >= 1400
    #pragma message ("Microsoft Visual Studio C++ compiler")
  #else
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
  #endif
 /*Current version of Microsoft compiler. Version number is combined of
   the major and minor number. The major number is the first component of
   the period-delimited version number and the minor number is 
   the second component.
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
      Visual Studio C/C++ 2005, version 8.0     1400
      Visual Studio C/C++ 2008, version 9.0     1500
      Visual Studio C/C++ 2010, version 10.0    1600

   See also: Q65472, _MSC_VER
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
  #if _MSC_VER == 1500
    #pragma message ("  2008 ver. 9.0")
    #define DBGMSC_VER 0x1500 /*Trace MSVC version*/
  #endif
  #if _MSC_VER == 1600
    #pragma message ("  2010 ver. 10.0")
    #define DBGMSC_VER 0x1600 /*Trace MSVC version*/
  #endif
  #ifndef DBGMSC_VER
    #pragma message ("  ver. unknown")
  #endif

  /*--------------------------------------------------------------------------*/
  /*Compilation conditions
   */
  #ifdef _DEBUG
     /*Defined when you compile with /LDd, /MDd, and /MTd.*/
     #pragma message ("Debug version")
  #else
     /*NDEBUG defineded isnatd _DEBUG*/
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
       
       
  #ifdef _Wp64
     /*Defined when specifying /Wp64 (Detect 64-Bit Portability Issues)
      */
     #pragma message ("Detecting 64-Bit Portability Issues.")
  #endif
  #ifdef _VC_NODEFAULTLIB
     /*Defined when /Zl is used; see /Zl (Omit Default Library Name)
      */
     #pragma message ("Omit Default Library Names.")
  #endif
  #ifdef _OPENMP
     /*Defined when compiling with /openmp, returns an integer representing 
       the date of the OpenMP specification implemented by Visual C++.
       Example:
          // _OPENMP_dir.cpp; compile with: /openmp 
          #include <stdio.h> 
          int main() 
            {
            printf("%d\n", _OPENMP);
            }       
      */
     #pragma message ("OpenMP specification used.")
  #endif
        
  /*Managed application specification*/      
    #ifdef __CLR_VER
    /*The version of the common language runtime (CLR) used when
      the application was compiled.
      The value returned will be in the following format:
            Mmmbbbbb where:
            M is the major version of the runtime
            mm is the minor version of the runtime
            bbbbb is the build number.
      Example:
          //compile with: /clr
          using namespace System;
          int main() 
            {
            Console::WriteLine(__CLR_VER);
            }
     */
    const int g__CLR_VER = __CLR_VER;
  #endif  
  #ifdef _MANAGED
    /*Defined /clr is specified. Value of _MANAGED is 1.
      Creates CLR metadata for the application.
     */
     #pragma message ("Create Managed Assemblies.")
  #endif
  #ifdef __cplusplus_cli
    /*Defined when you compile with /clr, /clr:pure, or /clr:safe. 
      Value of __cplusplus_cli is 200406.
      __cplusplus_cli is in effect throughout the translation unit.
     
     */ 
     #pragma message ("Create Microsoft Intermediate Language (MSIL) output.")
  #endif
       
#endif /*_MSC_VER */

/* ///////////////////////////////////////////////////////////////////////// */
#endif /*_KDBGMACRMSVC_H_                                                     */
/*****************************************************************************
 * $Log: KDbgMacrMsvc.h,v $
 * Revision 1.3  2011/06/07 19:41:14  ddarko
 * MSVC 2010
 *
 * Revision 1.2  2008/12/17 15:56:46  ddarko
 * Formating
 *
 * Revision 1.1  2008/09/09 19:52:31  ddarko
 * Moved MSVC macros
 *
 *****************************************************************************/
