/*$Workfile: KTraceFx.h$: implementation file
  $Revision: 3$ $Date: 2005-04-13 11:31:46$
  $Author: Darko Kolakovic$

  Debugging helpers
  Copyright: Alberto García-Baquero Vega
  Copyright: Darko Kolakovic 2001-05-01
  www.flipcode.com
 */

/* Group=Diagnostic                                                          */

#ifndef _KTRACEFX_H_
    /*$Workfile: KTraceFx.h$ sentry*/
  #define _KTRACEFX_H_

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #ifdef _MSC_VER
    #pragma message ("   #include " __FILE__ )
  #endif
  #ifdef __GNUC__
    #warning "   #include KTraceFx.h"
  #endif
#endif

/* ========================================================================= */
#ifdef _MSC_VER /*Microsoft C/C++, ... */
  #ifndef _PRAGMAMESSAGE
    /*
      Example:
        #pragma _PRAGMAMESSAGE(Your message)
        is equivalent to
        #pragma message(Your message)
     */
    #define _PRAGMAMESSAGE(Msg) message(Msg)
  #endif
#endif /*_MSC_VER*/

#ifdef __GNUC__ /*GNU C/C++ compiler*/
  #ifndef _PRAGMAMESSAGE
    /*
      Example:
        #warning _PRAGMAMESSAGE(Your message)
        is equivalent to
        #warning "Your message"
     */
    #define _PRAGMAMESSAGE(Msg) "Msg"
  #endif
#endif /*__GNUC__*/
/* ========================================================================= */

/*_MESSAGE preprocessor directive -----------------------------------------*/
/*Helper to macro converting argument into a string constant.                        */
#define _MESSAGE0(Msg)     #Msg
/*Converts a macro argument into a string constant.                        */
#define _STRINGCST(Msg)    _MESSAGE0(Msg)

#ifdef _UNICODE
  #ifndef __LOC__
    /*Creates text with current file name and line number in following format:
         FileName(LineNumber)
     */
    #define __LOC__  _MESSAGELINENO __WFILE__ "(" _STRINGCST(__LINE__) ")"
  #endif
#else
  #ifndef __LOC__
    /*Creates text with current file name and line number in following format:
         FileName(LineNumber)
     */
    #define __LOC__  _MESSAGELINENO __FILE__ "(" _STRINGCST(__LINE__) ")"
  #endif
#endif

#ifndef KMESSAGE
    /*Microsoft Visual Studio C/C++ compiler
     */
  #if defined (_MSC_VER)
    /*Creates message prolog with the name of the source file and the line
      number where a preprocessor message has been inserted.
      Preprocessor needs two indirections to replace __LINE__ or __FILE__ with
      actual string.

      Note: Microsoft Visual Studio (MSVC) specific.

      Example:
          #pragma KMESSAGE(Your message)
          Output:
          C:\MyCode.cpp(111) : Your message
     */
    #define _MESSAGELINENO __FILE__ "(" _STRINGCST(__LINE__) ") : "
  #endif /*_MSC_VER*/

    /*Metrowerks CodeWarrior Compiler
     */
  #if defined (__MWERKS__)
    /*Creates message prolog with the name of the source file and the line
      number where a preprocessor message has been inserted.
      Preprocessor needs two indirections to replace __LINE__ or __FILE__ with
      actual string.

      Note: Metrowerks CodeWarrior (MWERKS) specific.

      Example:
         #pragma KMESSAGE(Your message)
         Output:
         MyCode.cpp line 111   Your message
     */
    #define _MESSAGELINENO __FILE__ " line " _STRINGCST(__LINE__) "   "
  #endif /*__MWERKS__*/

  /*Inserts the name of the source file and the line number where
      a preprocessor message has been inserted.

    Example:
       #pragma KMESSAGE(Your message)

       Output (Microsoft Visual Studio MSVC):
       C:\MyCode.cpp(111) : Your message
       Output (Metrowerks CodeWarrior MWERKS):
       MyCode.cpp line 111   Your message
   */
  #define KMESSAGE(Msg)  message(_MESSAGELINENO #Msg)
#endif /*KMESSAGE*/

#ifndef TODO
  /*Inserts a reminder into the compiler's output.

    Example:
       #pragma TODO(Your message)

       Output (Metrowerks CodeWarrior MWERKS):
       MyCode.cpp line 111
       +------
       |TODO: Your message
       +------
   */
  #define TODO( Msg )  message( _MESSAGELINENO"\n"           \
          "+------\n" \
          "|TODO: " #Msg "\n" \
          "+------" )
#endif /*TODO*/

#ifndef FIXME
  /*Inserts a warning message into the compiler's output.

    Example:
       #pragma FIXME(Your message)

       Output (Microsoft Visual Studio MSVC):
       C:\MyCode.cpp(111) :
       +------
       |FixMe! Your message
       +------
   */
  #define FIXME( Msg )  message(  _MESSAGELINENO"\n"           \
        "+------\n" \
        "|FixMe! " #Msg "\n" \
        "+------" )
#endif /*FIXME*/

#ifndef todo
  /*Inserts a reminder into the compiler's output.

    Example:
       #pragma todo(Your message)

       Output (Metrowerks CodeWarrior MWERKS):
       MyCode.cpp line 111   TODO: Your message
   */
  #define todo( Msg )  message( _MESSAGELINENO"TODO: " #Msg )
#endif /*todo*/

#ifndef fixme
  /*Inserts a warning message into the compiler's output.

    Example:
       #pragma fixme(Your message)

       Output (Microsoft Visual Studio MSVC):
       C:\MyCode.cpp(111) : FixMe! Your message
   */
  #define fixme( Msg )  message( _MESSAGELINENO"FixMe! " #Msg )
#endif /*fixme*/


#if defined (_MSC_VER)
  #if (_MSC_VER >= 1300) /*Visual C++ .Net 2002, 32-bit, version 7.0*/
    /*Note: See Compiler Warning (level 1) C4995 for the Visual C++ .Net
     */
    #define deprecated deprecated
  #endif /*_MSC_VER < 1300*/
#endif

#ifndef deprecated
  /*The deprecated pragma lets you indicate that a function may no longer
    be supported in a future releases and that should no longer be used.

    Example:
       #pragma deprecated(MyFunc; "MYMACRO")
       void MyMethod()
         {
         #pragma deprecated(__FUNCTION__)
         ...
         };
       Output (Microsoft Visual Studio MSVC):
       C:\MyCode.cpp(111) : Warning: deprecated MyFunc; "MYMACRO"
       C:\MyCode.cpp(114) : Warning: deprecated MyMethod
   */
  #define deprecated( FuncName )  message( _MESSAGELINENO"Warning: deprecated " #FuncName )
#endif /*deprecated*/


#if __STDC_VERSION__ < 199901L
  #if __GNUC__ >= 2
    /*__func__  C99 standard: The identifier __func__ is implicitly declared by
              the translator as if, immediately following the opening brace of
              each function definition, the declaration:
              static const char __func__[] = "function-name";
              It is the undecorated name of the enclosing function.
     */
    #define __func__ __FUNCTION__
  #else /*not C99 standard*/
    #define __func__ __FILE__
  #endif
#endif /*__STDC_VERSION__*/

#ifndef __func__ /*__func__ is treated as macro*/
  #ifdef __FUNCTION__ /*__FUNCTION__ is treated as macro*/
    /*__func__  C99 standard: The identifier __func__ is implicitly declared by
              the translator as if, immediately following the opening brace of
              each function definition, the declaration:
              static const char __func__[] = "function-name";
              It is the undecorated name of the enclosing function.
     */
    #define __func__ __FUNCTION__
  #else
    #define __func__ __FILE__

  #endif
#endif /*__func__*/

#ifndef TRACEMETHOD
  #ifdef __FUNCTION__
    /*Function Names:
      __func__  C99 standard: The identifier __func__ is implicitly declared by
                the translator as if, immediately following the opening brace of
                each function definition, the declaration:
                static const char __func__[] = "function-name";
                It is the undecorated name of the enclosing function.

      __FUNCTION__  MSVC 7.0 and later: __FUNCTION__ is Valid only within a
                function and returns the undecorated name of the enclosing
                function (as a string). __FUNCTION__ is not expanded if you
                use the /EP or /P compiler option.
                GCC: __FUNCTION__ is another name for __func__, recognized by
                older version of the compiler, when __func__ was not been
                standardized.
                GCC C compiler 3.3 and earlier: __FUNCTION__ is string literal
                (it not preprocessor macro).
                GCC C compiler 3.4 and later: __FUNCTION__ is string variable
                like __func__ (it not preprocessor macro).
                GCC C++ compiler: __FUNCTION__ is string variable like __func__.

      __PRETTY_FUNCTION__  GCC C compiler 3.3 and earlier: __PRETTY_FUNCTION__
                is string literal with the name of the enclosing function (it not
                preprocessor macro).
                GCC C compiler 3.4 and later: __PRETTY_FUNCTION__ is string variable
                like __func__ with the name of the enclosing function (it not
                preprocessor macro).
                GCC C++ compiler: __PRETTY_FUNCTION__ is string variable like
                __func__ with the name and type of the enclosing function.

      __FUNCDNAME__  MSVC 7.0 and later: Valid only within a function and returns
                the decorated name of the enclosing function (as a string).
                __FUNCDNAME__ is not expanded if you use the /EP or /P compiler
                option.

      __FUNCSIG__  MSVC 7.0 and later: Valid only within a function and returns
                the signature of the enclosing function (as a string). __FUNCSIG__
                is not expanded if you use the /EP or /P compiler option.
                On a 64-bit operating system, the calling convention is __cdecl
                by default.
     */
    #define TRACEMETHOD() TRACE1(_T("%s()\n"), __FUNCTION__)
  #else
    #define __FUNCTION__ _MESSAGELINENO
    #define TRACEMETHOD() TRACE1(_T("%sfunc()\n"), __FUNCTION__)
  #endif
#endif /*TRACEMETHOD*/

#endif /*_KTRACEFX_H_*/
/******************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2004-11-24 10:52:04  Darko Kolakovic
 * $
 * Darko Kolakovic: _MESSAGELINENO, KMESSAGE 2001-05-01; ComonSoftInc
 * Posted at BabylonLib.SourceForge.net
 * Alberto García-Baquero Vega: FIXME; TODO;
 * Posted at www.flipcode.com as Tip Of The Day.
 *****************************************************************************/
