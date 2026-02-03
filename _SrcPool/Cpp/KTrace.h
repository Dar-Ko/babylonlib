/*$Workfile: KTrace.h$: implementation file
  $Revision: 49$ $Date: 2007-06-27 16:46:08$
  $Author: Darko Kolakovic$

  Debugging helpers
 */

/* Group=Diagnostic                                                          */

#ifndef _KTRACE_H_
    /*$Workfile: KTrace.h$ sentry*/
  #define _KTRACE_H_

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

#ifndef WIDECHAR
  #define _WIDECHAR_(x) L ## x
  /*Specify a wide-character string literal (wchar_t[])

    See also: KTypedef.h
   */
  #define WIDECHAR(x) _WIDECHAR_(x)
#endif /*WIDECHAR*/

/* ------------------------------------------------------------------------- */
#if (defined _UNICODE) || (defined UNICODE)
  #ifndef __TFILE__
    /*Wide string version of __FILE__ */
    #define __TFILE__ WIDECHAR(__FILE__)
  #endif /*__TFILE__*/

  #ifndef _TSFORMAT_
    /*Format string for tracing text*/
    #define _TSFORMAT_ "%ws"
  #endif /*_TSFORMAT_*/

#else /*!_UNICODE == Singlebyte-character (SBCS or ASCII) or multibyte-character
        (_MBCS) text mapping*/
  #ifndef __TFILE__
    #define __TFILE__ __FILE__
  #endif /*__TFILE__*/

  #ifndef _TSFORMAT_
    /*Format string for tracing text*/
    #define _TSFORMAT_ "%s"
  #endif /*_TSFORMAT_*/

/* ------------------------------------------------------------------------- */
#endif /*_UNICODE*/



#ifndef KMESSAGE
  /*KMESSAGE preprocessor directive*/
  #include "KTraceFx.h"
#endif /*KMESSAGE*/

/* ///////////////////////////////////////////////////////////////////////// */
/* Debuging validation and text dump macros                                  */

#ifdef _WIN32
  #ifdef __cplusplus
    #if defined (_USE_MFC) || defined (_USE_AFX) || defined (_AFXDLL)
       //Build dependant of the Microsoft Foundation Class (MFC) library
      #ifndef _WINDOWS_ //if windows.h is already included, skip afx.h.
        #include <afx.h> //TRACE, ASSSERT macros
      #endif

    #else
      #pragma todo(Move MSVC macros to Win/32/KTraceWin32.h) //TODO:
      //#include "Win/32/KTraceWin32.h" //TRACE, ASSSERT macros
    #endif /*USE_MFC*/
  #else /*C compilation*/
    /*#include "Win/32/KTraceWin32.h"*/
  #endif /*__cplusplus*/
#endif /*_WIN32*/

/* ========================================================================= */
/* Debug build version                                                       */
#ifdef _DEBUG

  /*Compile-time assertion produces compiler error if expression is false.
   */
#define ASSERT_CL(expr) {typedef char __AssertCompiler__[(expr) ? 1 : -1];}

  /* ----------------------------------------------------------------------- */
  /* GNU C/C++ compiler                                                      */
  #ifdef __GNUC__

    /* ...................................................................... */
    /* Platform: WindRiver VxWorks                                            */
    /*Include required header files before KTrace.h */
    #ifdef __INCvxWorksh /*vxworks.h*/
      #ifndef _VXWORKS
        #define _VXWORKS  71
      #endif
      #ifndef __INCstdioh
        #warning "__INCvxWorksh"
        #include <stdio.h>
      #endif
      #include <assert.h>

    /* ...................................................................... */
    /* Platform: Other than WindRiver's VxWorks                               */
    #else /*!__INCvxWorksh*/

      /* .................................................................... */
      /* Platform: WindRiver VxWorks (emulator) on Microsoft Windows 32b host */
      /*Included \host\x86-win32\i386-pc-mingw32\sys-include\windows32\defines.h*/
      #ifdef _GNU_H_WINDOWS32_DEFINES
        #warning "_GNU_H_WINDOWS32_DEFINES"
        #define __INCntcontexth /*Exclude \target\h\arch\simnt\ntcontext.h */
        #define __INCstddefh    /*Exclude \target\h\stddef.h               */
        #include <sys-include/stddef.h> /*wint_t typedef*/
        #include <sys-include/stdio.h>
        #include <sys-include/assert.h>

      /* .......................................................  ........... */
      /* Platform: Other than WindRiver's VxWorks emulator                    */
      #else /*!_GNU_H_WINDOWS32_DEFINES*/

        #warning "default path/stdio.h "
        #include <stdio.h>
        #include <assert.h>
      #endif /*_GNU_H_WINDOWS32_DEFINES*/

    /* ...................................................................... */
    #endif  /*__INCvxWorksh*/
  /* ----------------------------------------------------------------------- */
  #endif   /*__GNUC__*/



  /* ----------------------------------------------------------------------- */
  /* Dump Traces to a log file. Declare DbgStdOut as global and initialize it
     with file stream or standard output stream.

     Example:
       #ifdef _DEBUGTOLOG
         #pragma message (__FILE__ " _DEBUGTOLOG defined")
         #include <stdio.h>  //FILE struct
         FILE* DbgStdOut = stderr;
         #define _DEBUGTOLOGFILE //global DbgStdOut is defined here
         #include "KTrace.h"  //TRACE0 macro
       #endif
       void main()
         {
         #ifdef _DEBUGTOLOG
              //Open a debug log file.
           FILE* fileDbg = fopen("Debug.log","w+");
           if (fileDbg != NULL)
             DbgStdOut = fileDbg;
           else
             TRACE0("Failed to open Debug.log\n");
         #endif
         TRACE0("Main()\n");
         ...
         #ifdef _DEBUGTOLOG
           if (fileDbg != NULL)
             {
             fflush(fileDbg);
             fclose(fileDbg);
             }
         #endif
         }
  */
  #ifdef _DEBUGTOLOG

    #ifndef _DEBUGTOLOGFILE
      extern FILE* DbgStdOut; /*Log file is used dump debugging messages*/
    #endif

  /* ----------------------------------------------------------------------- */
  /* Dump Traces to a standard I/O stream                                    */
  #else /*!_DEBUGTOLOG */
    /*Standard error I/O stream is used to dump debugging messages*/
    #define DbgStdOut  stderr

  /* ----------------------------------------------------------------------- */
  #endif /*_DEBUGTOLOG */


  /* ----------------------------------------------------------------------- */
  /* Microsoft C/C++ compilers are using own debugging API.
   */
  #ifdef _MSC_VER /*Microsoft Visual C/C++*/

    #ifdef _UNICODE
      #ifndef UNICODE
        //To enable Unicode for some Microsoft Visual C/C++ header files,
        //the UNICODE definition is required
        #define UNICODE
      #endif
    #endif

    #if (_MSC_VER < 1400) //Less than Visual C++ 2005
      #ifdef _UNICODE
        #ifndef _TCRTDBGREPORT

          #ifndef _CRTIMP
            #ifdef CRTDLL
              #define _CRTIMP __declspec(dllexport)
            #else  /* CRTDLL */
              #ifdef _DLL
                #define _CRTIMP __declspec(dllimport)
              #else  /* _DLL */
                #define _CRTIMP
              #endif  /* _DLL */
            #endif  /* CRTDLL */
          #endif  /* _CRTIMP */

          #ifndef LPCTSTR
            #include "KTypedef.h" //LPCTSTR
          #endif

          //Note: requires KDbgRpt.cpp
          #ifdef __cplusplus
            extern "C" _CRTIMP int __cdecl tCrtDbgReport( int nRptType,
                                                          LPCTSTR szFile,
                                                          int nLine,
                                                          LPCTSTR szModule,
                                                          LPCTSTR szFormat,
                                                          ...);
          #else
            extern  _CRTIMP int __cdecl tCrtDbgReport( int nRptType,
                                                       LPCTSTR szFile,
                                                       int nLine,
                                                       LPCTSTR szModule,
                                                       LPCTSTR szFormat,
                                                       ...);
          #endif
          //SBCS (ASCII) version of the debug report.
          #define _TCRTDBGREPORT tCrtDbgReport
          #undef _TSFORMAT_
          #define _TSFORMAT_ _T("%s")
        #endif
      #else  //SCBS
        #ifndef _TCRTDBGREPORT
          //SBCS (ASCII) version of the debug report.
          #define _TCRTDBGREPORT _CrtDbgReport
        #endif
      #endif //(_UNICODE)

    #else //(_MSC_VER >= 1400)
      #ifdef _UNICODE
        #ifndef _TCRTDBGREPORT
          //Wide character version of the debug report is available in Visual C++ 2005
          #define _TCRTDBGREPORT _CrtDbgReportW
          #undef _TSFORMAT_
          #define _TSFORMAT_ _T("%s")
        #endif
      #else  //SCBS
        #ifndef _TCRTDBGREPORT
            /*SBCS (ASCII) version of the debug report.
              _CrtDbgReport(int             nRptType    //report type
                            const char*    szFile      //file name
                            int             nLine       //line number
                            const char*    szModule    //module name
                            const char*    szFormat    //format string
                            ...                         //var args
                            )
            */
          #define _TCRTDBGREPORT _CrtDbgReport
        #endif
      #endif //(_UNICODE)
    #endif //(_MSC_VER < 1400)

    //D.K. 12.2.2k2 #ifdef __cplusplus
    //TODO: separate C and C++ traces (replace fprintf with a class Trace)

    #ifndef _DBG_WARN
      #define _DBG_WARN   _CRT_WARN    /*Warning report type*/
    #endif
    #ifndef _DBG_ERROR
      #define _DBG_ERROR  _CRT_ERROR   /*Erroneous Condition report type*/
    #endif
    #ifndef _DBG_ASSERT
      #define _DBG_ASSERT _CRT_ASSERT  /*Assertion Failure report type*/
    #endif

    #ifdef _DEBUGTOLOG
     //#include <io.h> //_get_osfhandle()
     //_CrtSetReportMode(_CRT_WARN,   _CRTDBG_MODE_FILE);
     //_CrtSetReportFile(_CRT_WARN,   (void*)_get_osfhandle(_fileno(DbgStdOut)));
     //_CrtSetReportMode(_CRT_ERROR,  _CRTDBG_MODE_FILE);
     //_CrtSetReportFile(_CRT_ERROR,  (void*)_get_osfhandle(_fileno(DbgStdOut)));
     //_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
     //_CrtSetReportFile(_CRT_ASSERT, (void*)_get_osfhandle(_fileno(DbgStdOut)));
    #endif

    /* ...................................................................... */
    #ifdef __AFX_H__
      //Define MFC tag as in afxver_h, MSVC/C++ .Net (2003, 7.1)
      #ifndef _AFX
        #define _AFX 19610706 //Microsoft Application Framework Classes (AFX/MFC)
      #endif
    #endif //__AFX_H__

    /*ATL/WTL version without MFC                                             */
    #ifdef __cplusplus
      #ifndef _AFX  //!AFX/MFC
        #ifdef _ATL //Active Template Library (ATL). See also: <atldef.h>
          #include "KTraceAtl.h" //Convert MFC macros to ATL
        #endif
        #ifdef _ATL_VER //Active Template Library (ATL). See also: <atldef.h>
          #include "KTraceAtl.h" //Convert MFC macros to ATL
        #endif
      #endif //!AFX/MFC
    #endif //__cplusplus

    #if !defined(_AFX) && !defined(_ATL) /*MFC and ATL not included and all
                                           TRACE macros are undefined*/
      /*Windows SDK version                                                   */
      #ifdef _MFC_VER
        #error Use MFC debugging macros
      #endif
      #ifdef _ATL_VER
        #error Use ATL debugging macros
      #endif

      /*  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  . */
      #if _MSC_VER >= 1300 /*_MSC_VER >= 1300 MS Visual C++.Net v7.0; 7.1     */
        /*Disable warning C4127: conditional expression in ASSERT is constant
         in included header files; #pragma(warning(disable: 4127)) in source
         is still required to suppress the warning*/
        #define _VALIDATE_( expr ) \
            __pragma(warning(push)) \
            __pragma(warning(disable: 4127)) \
            if( expr ) \
              __pragma(warning(pop))

      #else /*_MSC_VER < 1300*/
        #define _VALIDATE_( expr ) if( expr )
      /*  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  */
      #endif /*_MSC_VER < 1300*/


      /*  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  */
      /*Only if Mac or Win32 targets are supported*/
      #if (defined(_WIN32) || defined(_MAC)) && !defined(_WIN32_WCE)

        #include <crtdbg.h> /*_CrtDbgReport()*/

        /*Evaluates an expression when the _DEBUG flag has been defined and
          if the result is false, prints a diagnostic message and aborts
          the program.
         */
        #define ASSERT(expr) \
            do{ _VALIDATE_ (!(expr) && \
                (1 == _TCRTDBGREPORT(_CRT_ASSERT, (LPCTSTR)__TFILE__, __LINE__, NULL, NULL))) \
                 _CrtDbgBreak(); \
              } while (0)

        /*Evaluates an expression when the _DEBUG flag has been defined and
          if the result is false, prints a diagnostic message and aborts
          the program. In the release version evaluates the expression but
          does not print or interrupt the program.
         */
        #define VERIFY(exp)  ASSERT(exp)
        #define TRACE( szMsg) \
            _TCRTDBGREPORT( _CRT_WARN, NULL, 0, NULL, _TSFORMAT_, szMsg)
        #define TRACE0( szMsg) \
            _TCRTDBGREPORT( _CRT_WARN, NULL, 0, NULL, _TSFORMAT_, szMsg)
        #define TRACE1( szMsg, p1) \
            _TCRTDBGREPORT( _CRT_WARN, NULL, 0, NULL, szMsg, p1)
        #define TRACE2( szMsg, p1, p2) \
            _TCRTDBGREPORT( _CRT_WARN, NULL, 0, NULL, szMsg, p1, p2)
        #define TRACE3( szMsg, p1, p2, p3) \
            _TCRTDBGREPORT( _CRT_WARN, NULL, 0, NULL, szMsg, p1, p2, p3)
        #define TRACEINFO( szMsg) \
            _TCRTDBGREPORT(_CRT_WARN, __TFILE__, __LINE__, NULL, _TSFORMAT_, szMsg)
      /*  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  */
      #endif  /*_WIN32 || _MAC */

      /*WinCE*/
      #ifdef _WIN32_WCE
        #include <dbgapi.h> /*ASSERT macro definition*/

        #define TRACE( szMsg) \
            NKDbgPrintfW( _T("%s"), szMsg)
        #define TRACE0( szMsg) \
            NKDbgPrintfW( szMsg)
        #define TRACE1( szMsg, p1) \
            NKDbgPrintfW( szMsg, p1)
        #define TRACE2( szMsg, p1, p2) \
            NKDbgPrintfW( szMsg, p1, p2)
        #define TRACE3( szMsg, p1, p2, p3) \
            NKDbgPrintfW( szMsg, p1, p2, p3)
        #define TRACEINFO NKDbgPrintfW("%s(%i): ",__TFILE__, __LINE__); \
            NKDbgPrintfW
      #endif /*_WIN32_WCE*/

      #ifdef _DOS
        #include <assert.h>
        #define ASSERT(expr) ( (expr) ? (void) 0 : _assert(expr, __FILE__, __LINE__) )

        #include <stdio.h> /*fprintf()*/

        /*In the Debug environment, the TRACE macro output goes to Standard
          Error Stream stderr. In the Release environment, it does nothing.
         */
        #define _TRACE_OUTPUT 1224

      #endif /*_DOS*/


    /*.......................................................................*/
    /*Windows MFC version                                                    */
    #else
      #ifndef __cplusplus
        #error Requires C++ compilation
      #endif

      #ifdef _MFC_VER
        /*Dumps a formatted string and the line position of the tracing
          macro. The macro is a convenient way to navigating the code quickly
          while debugging.
          Requires Debug build (_DEBUG have to be defined).
          In the Release environment, it does nothing.

          TODO: Unicode version, ATL version
        */
        #define TRACEINFO ::AfxTrace(_T("%s(%i): "), __TFILE__, __LINE__); ::AfxTrace

        /* TODO: MS MFC version for log file */
        /*
          ...
          */
      #endif

    /* ....................................................................*/
    #endif /*!__AFX_H__ */
  //D.K. 12.2.2k2 #endif /*__cplusplus*/

  /* --------------------------------------------------------------------- */
  #endif /*_MSC_VER Microsoft C/C++ compiler*/

  /* ----------------------------------------------------------------------- */
  /*PalmOS
   */
  #ifndef __palm_os
    /*Defined because expressions in the
        #if constant-expression
        #endif
      directives must have integral type and can include only integer constants,
      character constants and the defined operator.
     */
    #define __palm_os 0XFFFF
  #endif
  #if defined(__PALMOS__) || (__dest_os == __palm_os)
    #include "Palm/KTracePalm.h"
  #endif /*__PALMOS__ */

  /* ----------------------------------------------------------------------- */
  /* Dump debugging messages to an I/O stream                                */
  #ifdef _TRACE_OUTPUT

    #ifndef _TRACE_HANDLER
      #define _TRACE_HANDLER fprintf
    #endif

    #ifndef ASSERT

      #ifdef __GNUC__
        #include <assert.h> //assert
        #ifdef assert
          /*The ANSI assert macro is typically used to identify logic errors
            during program development, by implementing the expression
            argument to evaluate to false only when the program is operating
            incorrectly.
           */
          #define ASSERT assert
        #else
          /*Evaluates an expression when the _DEBUG flag has been defined and
            if the result is FALSE, aborts the program.
           */
          #define ASSERT(expr) \
               if (!(expr) )   \
                 {            \
                 fflush  (DbgStdOut);   \
                 fprintf (DbgStdOut, "\n%s(%d): Assertion failed\n",  \
                     __FILE__, __LINE__);   \
                 fflush  (DbgStdOut);  \
                 abort();  \
                 }
        #endif /* assert */
      #endif /*__GNUC__*/
    #endif  /* ASSERT */

    /*Evaluates an expression when the _DEBUG flag has been defined and
      if the result is false, prints a diagnostic message and aborts
      the program. In the release version evaluates the expression but
      does not print or interrupt the program.
     */
    #define VERIFY(exp)  ASSERT(exp)

    #undef TRACE
    #undef TRACE0
    #undef TRACE1
    #undef TRACE2
    #undef TRACE3

    /*ISO 1999 C99 compliant compiler*/
    #if defined __STDC_VERSION__ && __STDC_VERSION__ >=199901L
    /*Dumps formatted string to a output device such as a file or debug monitor.
      Requires Debug build (_DEBUG have to be defined).
      In the Release environment, it does nothing.

      TODO: Unicode version
     */
      #define TRACE(...)  \
                _TRACE_HANDLER(DbgStdOut,__VA_ARGS__);fflush(DbgStdOut)

    #elif defined __GNUC__ /*GNU C/C++ compiler*/
      /*Note: requires variable-argument preprocessor support*/
      #define TRACE(param...)  \
                _TRACE_HANDLER(DbgStdOut,param);fflush(DbgStdOut)
    #else
      #define TRACE(format)  \
                _TRACE_HANDLER(DbgStdOut,format);fflush(DbgStdOut)
    #endif /*__STDC_VERSION__*/

    /*Dumps a message to a output device such as a file or debug monitor.
      Requires Debug build (_DEBUG have to be defined).
      In the Release environment, it does nothing.

      Note: if used in statement block, enclose a macro with brackets

      Example:

        if( p == NULL)
          {
          TRACE0("NULL pointer\n");
          }
        else
          {
          TRACE1("p = %p\n", p);
          }

      TODO: Unicode version
     */
    #define TRACE0(format)  \
            _TRACE_HANDLER(DbgStdOut,format);fflush(DbgStdOut)
    /*Dumps a formatted string and one variable to a output device such as
      a file or debug monitor. The macro is a convenient way to track the value
      of variables as your program executes.
      Requires Debug build (_DEBUG have to be defined).
      In the Release environment, it does nothing.

      TODO: Unicode version
     */
    #define TRACE1(format, p1)  \
            _TRACE_HANDLER(DbgStdOut,format, p1);fflush(DbgStdOut)

    /*Dumps a formatted string and two variables to a output device such as
      a file or debug monitor. The macro is a convenient way to track the value
      of variables as your program executes.
      Requires Debug build (_DEBUG have to be defined).
      In the Release environment, it does nothing.

      TODO: Unicode version
     */
    #define TRACE2(format, p1, p2)  \
        _TRACE_HANDLER(DbgStdOut,format, p1, p2);fflush(DbgStdOut)

    /*Dumps a formatted string and three variables to a output device such as
      a file or debug monitor. The macro is a convenient way to track the value
      of variables as your program executes.
      Requires Debug build (_DEBUG have to be defined).
      In the Release environment, it does nothing.

      TODO: Unicode version
     */
    #define TRACE3(format, p1, p2, p3)  \
        _TRACE_HANDLER(DbgStdOut,format, p1, p2, p3); fflush(DbgStdOut)

    /*Dumps a formatted string and the line position of the tracing
      macro. The macro is a convenient way to navigating the code quickly while
      debugging.
      Requires Debug build (_DEBUG have to be defined).
      In the Release environment, it does nothing.

      TODO: Unicode version
     */
    #define TRACEINFO TRACE2(_T("%s(%i): "),__TFILE__,__LINE__); _TRACE_HANDLER

  #endif  /*_TRACE_OUTPUT*/

/* ========================================================================= */
/* Release (non-debug) build version                                         */
#else /* NDEBUG */

  #define ASSERT_CL ASSERT

  /* ----------------------------------------------------------------------- */
  /* Microsoft C/C++ Compiler                                                */
  #ifdef _MSC_VER
    #if _MSC_VER > 1200
      #ifndef TRACE
        #define TRACE(format) __noop
      #endif
      #ifndef TRACE0
        #define TRACE0(format) __noop
      #endif
      #ifndef TRACE1
        #define TRACE1(format,param1) __noop
      #endif
      #ifndef TRACE2
        #define TRACE2(format,param1,param2) __noop
      #endif
      #ifndef TRACE3
        #define TRACE3(format,p1, p2, p3) __noop
      #endif
        #ifndef TRACEINFO
          #define TRACEINFO(format) __noop
        #endif

      #ifndef ASSERT
        #define ASSERT(exp) __noop
      #endif

      #ifndef VERIFY
        #define VERIFY(exp)          ((void)(exp))
      #endif

    #else /*_MSC_VER <= 1200 MS Visual Studio C/C++ v6.0 or less*/
      #ifdef __cplusplus
        #ifndef TRACE
          #define TRACE(format) (void(0))
        #endif
        #ifndef TRACE0
          #define TRACE0(format) (void(0))
        #endif
        #ifndef TRACE1
          #define TRACE1(format,param1) (void(0))
        #endif
        #ifndef TRACE2
          #define TRACE2(format,param1,param2) (void(0))
        #endif
        #ifndef TRACE3
          #define TRACE3(format,p1, p2, p3) (void(0))
        #endif
        #ifndef TRACEINFO
          #define TRACEINFO(format)
        #endif
        #ifndef ASSERT
          #define ASSERT(exp) ((void)0)
        #endif
        #ifndef VERIFY
          #define VERIFY(exp)          ((void)(exp))
        #endif

      #else /*__c*/
        #ifndef TRACE
          #define TRACE(format)
        #endif
        #ifndef TRACE0
          #define TRACE0(format)
        #endif
        #ifndef TRACE1
          #define TRACE1(format,param1)
        #endif
        #ifndef TRACE2
          #define TRACE2(format,param1,param2)
        #endif
        #ifndef TRACE3
          #define TRACE3(format,p1, p2, p3)
        #endif
        #ifndef TRACEINFO
          #define TRACEINFO(format)
        #endif
        #ifndef ASSERT
          #define ASSERT(exp)
        #endif
        #ifndef VERIFY
          #define VERIFY(exp)          (exp)
        #endif
      #endif /*__cplusplus*/
    #endif /*_MSC_VER <= 1200 */

  /* ----------------------------------------------------------------------- */
  /* Other than Microsoft's compilers                                        */
  #else /* !_MSC_VER*/
    #if defined(__MWERKS__)/* Metrowerks CodeWarrior Compiler                */
       #ifndef TRACEINFO
        #define TRACEINFO(...) do{}while(0) //Won't generate any code
      #endif
      #ifndef TRACE
        #define TRACE(...)     do{}while(0) //Won't generate any code
      #endif
    #endif

    #ifndef TRACE
      #define TRACE(format)
    #endif
    #ifndef TRACE0
      #define TRACE0(format)
    #endif
    #ifndef TRACE1
      #define TRACE1(format,param1)
    #endif
    #ifndef TRACE2
      #define TRACE2(format,param1,param2)
    #endif
    #ifndef TRACE3
      #define TRACE3(format,p1, p2, p3)
    #endif
    #ifndef TRACEINFO
      #define TRACEINFO(format)
    #endif
    #ifndef ASSERT
      #define ASSERT(exp)
    #endif
    #ifndef VERIFY
      #define VERIFY(exp)          (exp)
    #endif

  /* ----------------------------------------------------------------------- */
  #endif /*_MSC_VER */

/* ========================================================================= */
#endif  /*!_DEBUG */
/* ////////////////////////////////////////////////////////////////////////// */
#endif  /*_KTRACE_H_ */
/******************************************************************************
 * $Log:
 *  3    Biblioteka1.2         20/07/2001 1:00:38 AMDarko           MSC ASSERT
 *  2    Biblioteka1.1         11/07/2001 10:53:16 PMDarko
 *  1    Biblioteka1.0         09/06/2001 12:01:49 AMDarko
 *  4    User: Dkolakovic   5/01/01 6:08p  _GNUG_
 *  3    User: Dkolakovic   4/27/01 1:38p  #elif !__INCvxWorksh
 *  2    User: Dkolakovic   4/18/01 5:33p  wint_t typedef
 *  1    User: Dkolakovic   4/18/01 3:46p  ASSERT
 *  2    User: Dkolakovic   4/17/01 2:18p  Replaced output with stdio printf (VxWorks)
 * $
 * Aug. 96 renamed macros to be MFC-like (source-level compatibility) D.K.
 * Oct. 94 created D.K.
 *****************************************************************************/
