/*$Workfile: KTraceAtl.h$: implementation file
  $Revision: 2$ $Date: 2007-03-11 02:13:52$
  $Author: Darko$

  Debugging helpers for the ATL application
 */

/* Group=Diagnostic                                                          */

#ifndef _KTRACEATL_H_
    /*$Workfile: KTraceAtl.h$ sentry*/
  #define _KTRACEATL_H_

/* ------------------------------------------------------------------------- */
#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files*/
  #ifdef _MSC_VER
    #pragma message ("   #include " __FILE__ )
  #endif
  #ifdef __GNUC__
    #warning "   #include KTrace.h"
  #endif

/* ------------------------------------------------------------------------- */
#endif /*_DEBUG_INCL_PREPROCESS*/

#ifdef __cplusplus
#ifdef _UNICODE  //for MSVC < 2005
 //TODO:
#endif

#ifdef ATL_VER //Microsoft Active Template Library
  #ifndef _USE_ATL
     //Using Microsoft Active Template Library
    #define _USE_ATL 20090702
  #endif
#endif

#ifdef _USE_ATL
  #ifndef _ATL
     //Microsoft Active Template Library
    #define _ATL 19610706
  #endif
#endif

#ifdef _ATL //Active Template Library

  //Convert MFC debugging and error reporting macros to ATL version
  #ifndef ASSERT
     //Generates a debug report when the expression is false.
    #define ASSERT ATLASSERT
  #endif
  #ifndef VERIFY
    //VERIFY macro evaluates its argument. In debug version, if the result is
    //FALSE, the macro also prints a diagnostic message and halts the program.
    //If the condition is TRUE, it does nothing, except evalution.
    //For example, if the expression is a function call, the call will be made.
    #define VERIFY ATLVERIFY
  #endif
  #ifndef TRACE
    //Reports warnings to to the debugger's output window.
    #define TRACE ATLTRACE2
  #endif
  #ifndef TRACE0
    //Reports warnings to to the debugger's output window.
    #define TRACE0 ATLTRACE2
  #endif
  #ifndef TRACE1
    //Reports warnings to to the debugger's output window.
    #define TRACE1 ATLTRACE2
  #endif
  #ifndef TRACE2
    //Reports warnings to to the debugger's output window.
    #define TRACE2 ATLTRACE2
  #endif
  #ifndef TRACE3
    //Reports warnings to to the debugger's output window.
    #define TRACE3 ATLTRACE2
  #endif
#else //!_ATL
  #pragma message("warning :  Requires Microsoft Active Template Library")
#endif //_ATL

/* Debug build version                                                       */
//#ifdef _DEBUG
//#else
//#endif

#else /*!__cplusplus*/
  #error Requires C++ compilation
#endif /*__cplusplus */

#endif  /*_KTRACEATL_H_ */
/******************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2007-03-11 02:13:52  Darko
 *  1    Biblioteka1.0         2007-03-06 15:36:13  Darko Kolakovic
 * $
 *****************************************************************************/
