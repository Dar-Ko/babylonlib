/*$Workfile: KTrace.h$: implementation file
  $Revision: 11$ $Date: 30/01/2003 9:43:05 PM$
  $Author: Darko$

  Debugging helpers
 */

/* Group=Diagnostic                                                          */

#ifndef _KTRACE_H_
    /*KTrace.h sentry                                                        */
  #define _KTRACE_H_

/* ///////////////////////////////////////////////////////////////////////// */
/* DEBUG Macros */
#ifdef _DEBUG

  /*Compile-time assertion produces compiler error if expression is false.
   */
  #define ASSERT_CL(expr) typedef char __AssertCompiler__[(expr) ? 1 : -1]

  /* ======================================================================= */
  #ifdef __GNUC__
    #ifdef __INCvxWorksh /*VxWorks.h*/
      #ifndef __INCstdioh
        #warning "__INCvxWorksh"
        #include <StdIO.h>
      #endif
      #include <Assert.h>
    #else /*!__INCvxWorksh*/
    #ifdef _GNU_H_WINDOWS32_DEFINES  /*Included \host\x86-win32\i386-pc-mingw32\sys-include\Windows32\Defines.h*/
        #warning "_GNU_H_WINDOWS32_DEFINES"
        #define __INCntcontexth /*Exclude \target\h\arch\simnt\NTContext.h */
        #define __INCstddefh    /*Exclude \target\h\StdDef.h               */
        #include <sys-include/StdDef.h> /*wint_t typedef*/
        #include <sys-include/StdIO.h>
        #include <sys-include/Assert.h>
      #else /*!_GNU_H_WINDOWS32_DEFINES*/
        #warning "default path/StdIO.h "
        #include <StdIO.h>
        #include <Assert.h>
      #endif /*_GNU_H_WINDOWS32_DEFINES*/
    #endif  /*__INCvxWorksh*/
  #endif   /*__GNUC__*/

  #ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files*/
    #ifdef _MSC_VER
      #pragma message ("   #include " __FILE__ )
    #endif
    #ifdef __GNUC__
      #warning "   #include KTrace.h"
    #endif
  #endif

  /* ----------------------------------------------------------------------- */
  /* Dump Traces to a log file. Declare  DbgStdOut as global and initialize it
     with file stream or standard output stream.

     Example:
       #ifdef _DEBUGTOLOG
         #pragma message (__FILE__ " _DEBUGTOLOG defined")
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

     TODO: Redirect default TRACE to stdout - delete printfs D.K.*/
  #ifdef _DEBUGTOLOG
    #ifndef _DEBUGTOLOGFILE
      extern FILE* DbgStdOut;
    #endif
    #undef TRACE
    #undef TRACE0
    #undef TRACE1
    #undef TRACE2
    #undef TRACE3
    #define TRACE fprintf
    #define TRACE0(format)              TRACE(DbgStdOut,format);fflush(DbgStdOut)
    #define TRACE1(format, p1)          TRACE(DbgStdOut,format, p1);fflush(DbgStdOut)
    #define TRACE2(format, p1, p2)      TRACE(DbgStdOut,format, p1, p2);fflush(DbgStdOut)
    #define TRACE3(format, p1, p2, p3)  TRACE(DbgStdOut,format, p1, p2, p3);fflush(DbgStdOut)

  /* ----------------------------------------------------------------------- */
  /* Dump Traces to a standard I/O stream                                    */
  #else /*!_DEBUGTOLOG */

    /* --------------------------------------------------------------------- */
    #ifdef _MSC_VER /*Microsoft Visual Studio*/
      //D.K. 12.2.2k2 #ifdef __cplusplus
      //TODO: separate C and C++ traces (replace fprintf with a class Trace)
        #ifndef __AFX_H__ /*MFC not included and all TRACE macros are undefined*/
          #define THIS_FILE          __FILE__

            /*Only if Mac or Win32 targets are supported*/
          #if defined(_WIN32) || defined(_MAC)
            #include <CrtDbg.h> /*_CrtDbgReport()*/

            /*Evaluates an expression when the _DEBUG flag has been defined and
              if the result is FALSE, prints a diagnostic message and aborts 
              the program.
             */
            #define ASSERT(expr) \
                do{ if (!(expr) && \
                    (1 == _CrtDbgReport(_CRT_ASSERT, THIS_FILE, __LINE__, NULL, NULL))) \
                     _CrtDbgBreak(); \
                  } while (0)         

            #define TRACE0( szMsg) \
                _CrtDbgReport( _CRT_WARN, NULL, 0, NULL, "%s\n", szMsg)

          #endif  /*Mac or Win32*/
          
          #ifdef _DOS    
            #include <assert.h>
            #define ASSERT(expr) ( (expr) ? (void) 0 : _assert(expr, __FILE__, __LINE__) )
          #endif /*_DOS*/

          #include <stdio.h> /*fprintf()*/
          /*In the Debug environment, the TRACE macro output goes to Standard 
            Error Stream stderr. In the Release environment, it does nothing.
            
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
            
            TODO: MS SDK version 
           */ 
          #ifndef TRACE0
            #define TRACE0(format)              fprintf(stderr,format);fflush(stderr)
          #endif
          #ifndef TRACE1
            #define TRACE1(format, p1)          fprintf(stderr,format, p1);fflush(stderr)
          #endif
          #ifndef TRACE2
            #define TRACE2(format, p1, p2)      fprintf(stderr,format, p1, p2);fflush(stderr)
          #endif
          #ifndef TRACE3
             #define TRACE3(format, p1, p2, p3) fprintf(stderr,format, p1, p2, p3);fflush(stderr)
          #endif

        #endif /*!__AFX_H__ */
     //D.K. 12.2.2k2 #endif /*__cplusplus*/

      //D.K. 12.2.2k2 #ifndef _MFC_VER
        //D.K. 12.2.2k2 #include <StdIO.h> /*printf()*/
      //D.K. 12.2.2k2 #endif


    /* --------------------------------------------------------------------- */
    #else /* !_MSC_VER Microsoft Visual Studio*/

      #ifndef TRACE0
        #define TRACE0(format) printf(format)
      #endif
      #ifndef TRACE1
        #define TRACE1(format,param1)  printf(format,param1)
      #endif
      #ifndef TRACE2
        #define TRACE2(format,param1,param2)  printf(format,param1,param2)
      #endif
      #ifndef TRACE3
        #define TRACE3(format,p1, p2, p3)  printf(format,p1, p2, p3)
      #endif

      #ifndef ASSERT
        #ifdef __GNUC__
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
                   fflush  (stdout);   \
                   fprintf (stderr, "\nAssertion failed: %s, line %u\n",  \
                       __FILE__, __LINE__);   \
                   fflush  (stderr);  \
                   abort();  \
                   }
          #endif /* assert */
        #endif
      #endif  /* ASSERT */
    #endif /*_MSC_VER*/
  #endif /*_DEBUGTOLOG */

/* ========================================================================= */
#else /* NDEBUG */
  #ifdef _MSC_VER
    #ifndef TRACE0
      #define TRACE0(format) (void(0))
    #endif
    #ifndef TRACE1
      #define TRACE1(format,param1) (void(0,0))
    #endif
    #ifndef TRACE2
      #define TRACE2(format,param1,param2) (void(0,0,0))
    #endif
    #ifndef TRACE3
      #define TRACE3(format,p1, p2, p3) (void(0,0,0))
    #endif

    #ifndef ASSERT
      #define ASSERT(exp) ((void)0)
    #endif

  #else /* !_MSC_VER*/
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
    #ifndef ASSERT
      #define ASSERT(exp)
    #endif

  #endif /*_MSC_VER */

 #define ASSERT_CL ASSERT

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
 * Aug. 96 renamed macroes to be MFC-like (source-level compatibility) D.K.
 * Oct. 94 created D.K.
 * $
 *****************************************************************************/
