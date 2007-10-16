/*$Workfile: KDbgMAns.h$: header file
  $Revision: 50$ $Date: 2007-05-31 16:43:23$
  $Author: Darko Kolakovic$

  Dumps values of some ANSI compiler-specific predefined macros
  Copyright: CommonSoft Inc.
  2007-10-10 Darko Kolakovic extracted from KDbgMacr.h
  1988-04-01 Darko Kolakovic first version
*/
/* Group=Diagnostic                                                          */

#ifndef _KDBGMANS_H_
    /*$Workfile: KDbgMAns.h$ sentry */
  #define _KDBGMANS_H_

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #ifdef _MSC_VER
    #pragma message ("   #include " __FILE__ )
  #endif
  #ifdef __GNUC__
    #warning "   #include KTraceFx.h"
  #endif
#endif

#ifndef _PRAGMAMESSAGE
  #include "KTraceFx.h"
#endif

/* ////////////////////////////////////////////////////////////////////////// */
/*C99 Predefined Macros
  Defined per the C99 Standard 6.10.8 when compiling C programs.

 __STDC__ If defined, ANSI C (C98+,C99) conformance enabled
  __DATE__ Always defined. Set to compilation date in the form "Mmm dd yyyy".
  __TIME__  Always defined. Set to compilation time in the form "hh:mm:ss".
  __FILE__ Always defined. Set to name of file being compiled enclosed in "".
  __LINE__Always defined. Set to current line of source file.
  For ANSI C99 __STDC_VERSION__ is 199901L
  For ANSI C95 __STDC_VERSION__ is 199409L.

  Some compiler specific additions:
  __STDC_HOSTED__ Always defined and set to 0.
  __STDC_IEC_559__  IEC 60559 floating point arithmetic conformance.
  __STDC_IEC_559_COMPLEX__ IEC 60559 complex floating point arithmetic conformance.
  __TIMESTAMP__ Always defined. Set to compilation time in
        the form "Ddd Mmm dd hh:mm:ss yyyy".

  string literals:
  __func__  Name of the function as variable
  __FUNCTION__  Same as __FUNC__. Provided for Gnu CC compatibility.
  __PRETTY_FUNCTION__ Same as __FUNC__, but pretty-printed (
        C++ functions become more readable). Provided for Gnu CC compatibility.

  Notes:
   1. Predefined macro names cannot be the subject of a #define or #undef
      preprocessor directive.
   2. The predefined ANSI/ISO Standard macro names consist of two underscore
      (__) characters immediately preceding the name, the name in uppercase
      letters, and two underscore characters immediately following the name.
 */

/* ========================================================================= */
#ifdef __GNUC__  /*GNU C/C++ Compiler                                        */
  /*ANSI C macros ---------------------------------------------------------- */
  #ifdef __STDC__
    /*Macro expands to the constant 1, to signify that this is
      ANSI Standard C. (Whether that is actually true depends on what
      C compiler will operate on the output from the preprocessor.)          */
    #warning "__STDC__: C98, C99 or newer conformance (ISO/ANSI)."
  #else
    #warning "ISO/ANSI C non-conformance."
  #endif

  #ifdef __STDC_VERSION__
    /*ISO/ANSI C Standard's version number is a long integer in form: yyyymm where
      yyyy and mm are the year and month of the Standard version.
      This signifies which version of the C Standard the preprocessor
      conforms to.
      For ANSI C99 __STDC_VERSION__ is 199901L.
      For ANSI C95 __STDC_VERSION__ is 199409L.
    */
    #if __STDC_VERSION__ > 199900L
      #warning "C99: 1999-01 conformance."
    #else
      #if __STDC_VERSION__ > 199400L
        #warning "C95: 1994-09 conformance."
      #else
        #warning "C??: 19xx-xx conformance."
      #endif
    #endif
  #else /*!__STDC_VERSION__*/
    #ifdef __STDC__
      #warning "__STDC_VERSION__: <undefined>."
    #endif
  #endif /*__STDC_VERSION__*/

  /*Indicates that the compiler is a C++ compiler and it is always set to 199711L.
    This macro is not defined for C.
   */
  #ifdef __cplusplus
    #warning "C++ compilation."

    #if __cplusplus < 199711L
      #warning "C++: non-standard conformance."
    #endif
    #if __cplusplus == 199711L
      #warning "C++: ISO 199711 conformance."
    #endif
    #if __cplusplus > 199711L
      #warning "C++: unknown conformance."
    #endif
  #else /*!__cplusplus*/
    #warning "C compilation."
  #endif /*__cplusplus*/

  #ifdef __DATE__
    /*Macro expands to a string constant that describes the date on which
      the preprocessor is being run. The format is as following:
          "Mon dd yyyy".
      where:
      - Mon represents the month in an abbreviated form
        (Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, or Dec).
      - dd represents the day of the month.
      - yyyy represents the year.
     */
    #warning "Date: __DATE__"
  #else
    #warning "__DATE__: <undefined>."
  #endif

  #ifdef __TIME__
    /*Macro expands to a string constant that describes the time at which
      the preprocessor is being run. The format is 24 hour clock and looks
      like "hh:mm:ss".                                                       */
    #warning "Time: __TIME__"
  #else
    #warning "__TIME__: <undefined>."
  #endif

  #ifdef __FILE__
    /*Always defined as a character string literal containing the name enclosed
      in "" of the file being compiled .
     */
    #warning "File: __FILE__"
  #else
    #warning "__FILE__: <undefined>."
  #endif

  #ifdef __LINE__
   /*Defined to be an integer representing the current source line number.
     See also: #line preprocessor directive.
    */
    #warning "Line: __LINE__"
  #else
    #warning "__LINE__: <undefined>."
  #endif

  #ifdef __FUNC__
    /*__FUNC__ is the name of the function as a literal. This validates if
      the macro is defined also.
     */
    #warning "Fuction: __FUNC__"
  #else
    #warning "__FUNC__: <undefined>."
  #endif

  #ifdef __TIMESTAMP__
    /*The date and time of the last modification of the current source file,
      expressed as a string literal in the form
        Day Mmm Date hh:mm:ss yyyy,
      where Day is the abbreviated day of the week and
      Date is an integer from 1 to 31.
     */
    #warning __TIMESTAMP__
  #else
    #warning "__TIMESTAMP__: <undefined>."
  #endif

  #ifdef __STDC_HOSTED__
    /*Macro is always defined and set to 0 or 1, depending of the compiler.
       Note: Intel C++ Compiler specific
     */
    #warning "__STDC_HOSTED__: defined."
  #else
    #warning "__STDC_HOSTED__: <undefined>."
  #endif

  #ifdef __STRICT_ANSI__
    /*Macro is defined if and only if the "-ansi" switch was specified when
      GNU C was invoked. Its definition is the null string. This macro exists
      primarily to direct certain GNU header files not to define certain
      traditional Unix constructs which are incompatible with ANSI C.
      Note: GNU C Compiler specific.
     */
    #warning "Strict ANSI defined."
  #else
    #warning "__STRICT_ANSI__: <undefined>."
  #endif

  #ifdef _ANSI_C_SOURCE
    /*ISO C and ANSI C Standards Conformance.
      Note: DEC C Compiler specific
     */
    #warning "_ANSI_C_SOURCE: ISO/ANSI C conformance."
  #else
    #warning "_ANSI_C_SOURCE: <undefined>."
  #endif

/* -------------------------------------------------------------------------- */
/* Data types validation                                                     */
  #ifdef __CHAR_UNSIGNED__
    /*Macro is defined if and only if the data type char is unsigned on the
      target machine. It exists to cause the standard header file limit.h to
      work correctly.                                                        */
    #warning "__CHAR_UNSIGNED__: char type defined as unsigned char"
  #else
    #warning "__CHAR_UNSIGNED__: <undefined>."
  #endif

 #ifdef __SIGNED_CHARS__
   /*Defined when plain char is signed. This is used in the <limits.h> header
     file to get the proper definitions of CHAR_MAX and CHAR_MIN.
     Note: Comeau C++ 4.0 Compiler specific
    */
    #warning "__SIGNED_CHARS__: char type defined as signed char"
  #else
    #warning "__SIGNED_CHARS__: <undefined>."
  #endif

#ifdef __STDC_IEC_559__
  /*IEC 60559 floating point arithmetic conformance.
   */
    #warning "IEC 60559 floating point arithmetic conformance."
  #else
    #warning "__STDC_IEC_559__: <undefined>."
#endif

#ifdef __STDC_IEC_559_COMPLEX__
  /*IEC 60559 complex floating point arithmetic conformance.
   */
    #warning "IEC 60559 complex floating point arithmetic conformance."
  #else
    #warning "__STDC_IEC_559_COMPLEX__: <undefined>."
#endif

#ifdef __STDC_ISO_10646__
  /*ISO/IEC 10646 wchar_t conformance.
    __STDC_ISO_10646__ macro evaluates to an integer constant of the form
      yyyymmL indicating all amendments to standard and
      technical corrigenda as of the specified year and month.
   */
    #warning "ISO 10646 conformance."
  #else
    #warning "__STDC_ISO_10646__: <undefined>."
#endif

/* ========================================================================= */
#endif /*__GNUC__                                                            */

/* ========================================================================= */
#ifdef _MSC_VER  /*Microsoft C/C++ Compiler                                  */
//TODO: FixMe!
/* ========================================================================= */
#endif /*_MSC_VER                                                            */

/* ========================================================================= */
/* Constants                                                                 */

#ifdef __cplusplus
  /*Indicates that the compiler is a C++ compiler and it is always set to 199711L.
   */
  const long g__cplusplus_VER = __cplusplus;
#endif

#ifdef __STDC_VERSION__
  /*ISO/ANSI C Standard's version number is a long integer in form: yyyymm where
    yyyy and mm are the year and month of the Standard version.
    This signifies which version of the C Standard the preprocessor
    conforms to.
    For ANSI C99 __STDC_VERSION__ is 199901L.
    For ANSI C95 __STDC_VERSION__ is 199409L.
  */
  const long g___STDC_VERSION__ = __STDC_VERSION__;
#endif

/* ///////////////////////////////////////////////////////////////////////// */
#endif /*_KDBGMANS_H_                                                        */
/*****************************************************************************
 * $Log: $
 *****************************************************************************/
