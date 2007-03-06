/*$Workfile: S:\_SrcPool\Cpp\Win\32\KTraceAtl.h$: implementation file
  $Revision: 1$ $Date: 2007-03-06 14:36:13$
  $Author: Darko Kolakovic$

  Debugging helpers for the ATL application
 */

/* Group=Diagnostic                                                          */

#ifndef _KTRACEATL_H_
    /*$Workfile: S:\_SrcPool\Cpp\Win\32\KTraceAtl.h$ sentry*/
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

#ifdef ATL_VER
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
 *  1    Biblioteka1.0         2007-03-06 14:36:13  Darko Kolakovic 
 * $
 *****************************************************************************/
