/*$Workfile: S:\_SrcPool\Cpp\KTraceFx.h$: implementation file
  $Revision: 3$ $Date: 2005-04-13 12:31:46$
  $Author: Darko Kolakovic$

  Debugging helpers
  Copyright: Alberto García-Baquero Vega
  Copyright: Darko Kolakovic 2001-05-01
  www.flipcode.com
 */

/* Group=Diagnostic                                                          */

#ifndef _KTRACEFX_H_
    /*$Workfile: S:\_SrcPool\Cpp\KTraceFx.h$ sentry*/
  #define _KTRACEFX_H_

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #ifdef _MSC_VER
    #pragma message ("   #include " __FILE__ )
  #endif
  #ifdef __GNUC__
    #warning "   #include KTraceFx.h"
  #endif
#endif

#ifndef KMESSAGE
  /*_MESSAGE preprocessor directive -----------------------------------------*/
  /*reserved: preprocessor needs two indirections to replace __LINE__ with
    actual string                                                            */
  #define _MESSAGE0(Msg)     #Msg
  /*Preprocessor needs two indirections to replace __LINE__ or __FILE__ with
    actual string.

    Note: Microsoft Visual Studio (MSVC) specific.                           */
  #define _MESSAGE1(Msg)    _MESSAGE0(Msg)

    /*Microsoft Visual Studio C/C++ compiler
     */
  #if defined (_MSC_VER)
    /*Creates message prolog with the name of the source file and the line
      number where a preprocessor message has been inserted.

      Note: Microsoft Visual Studio (MSVC) specific.

      Example:
          #pragma KMESSAGE(Your message)
          Output:
          C:\MyCode.cpp(111) : Your message
     */
    #define _MESSAGELINENO __FILE__ "(" _MESSAGE1(__LINE__) ") : "
  #endif /*_MSC_VER*/

    /*Metrowerks CodeWarrior Compiler
     */
  #if defined (__MWERKS__)
    /*Creates message prolog with the name of the source file and the line
      number where a preprocessor message has been inserted.

      Note: Metrowerks CodeWarrior (MWERKS) specific.

      Example:
         #pragma KMESSAGE(Your message)
         Output:
         MyCode.cpp line 111   Your message
     */
    #define _MESSAGELINENO __FILE__ " line " _MESSAGE1(__LINE__) "   "
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

       Output (Microsoft Visual Studio MSVC):
       C:\MyCode.cpp(111) : Warning: deprecated MyFunc; "MYMACRO"
   */
  #define deprecated( FuncName )  message( _MESSAGELINENO"Warning: deprecated " #FuncName )
#endif /*deprecated*/

#endif //_KTRACEFX_H_
/******************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2004-11-24 10:52:04  Darko Kolakovic
 * $
 * Darko Kolakovic: _MESSAGELINENO, KMESSAGE 2001-05-01; ComonSoftInc
 * Posted at BabylonLib.SourceForge.net
 * Alberto García-Baquero Vega: FIXME; TODO;
 * Posted at www.flipcode.com as Tip Of The Day.
 *****************************************************************************/
