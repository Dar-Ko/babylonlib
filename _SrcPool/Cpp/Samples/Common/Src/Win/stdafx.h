/*$Workfile: stdafx.h$: header file
  $Revision: 21$  $Date: 2007-06-13 16:19:02$

  STandarD Application FrameworX
  header file includes standard system header files, or project specific header
  files that are used frequently, but are changed infrequently.
*/


#if !defined(_STDAFX_H_)
  /*$Workfile: stdafx.h$ sentry */
  #define _STDAFX_H_ 1532

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

//////////////////////////////////////////////////////////////////////////////
//Common header files

//-----------------------------------------------------------------------------
//Microsoft Windows 32b platforms
#ifdef _WIN32

  #ifdef _UNICODE
    #ifndef UNICODE
      //To enable Unicode character mapping for some Microsoft Visual C/C++
      //header files, the UNICODE definition is required.
      #define UNICODE
    #endif
  #endif

  #if _MSC_VER == 1310
      //Warning fix Q314963: WINVER not defined. Visual C++ .Net 2003 v7.1
      //Defaulting to 0x0501 (Windows XP and Windows .NET Server)
      #define WINVER 0x0501
  #endif // _MSC_VER > 1000

  #define VC_EXTRALEAN        // Exclude rarely-used stuff from Windows headers

  #ifdef __cplusplus
    #ifdef _AFXDLL
      //Build dependant of the Microsoft Foundation Class (MFC) dynamic
      //library (DLL). The library is an aggregatation of C++ classes used in
      //building software programs for the Microsoft Windows OS.
      #define _USE_MFC 201
      #ifndef _USE_AFX
        #define _USE_AFX _USE_MFC
      #endif
    #endif
  #else  //C compilation
     //MFC/AFX Library requires C++ compilation
    #undef _USE_AFX
    #undef _USE_MFC
  #endif //__cplusplus

  //---------------------------------------------------------------------------
  //For build dependant of the MFC dynamic library (DLL), include
  //following header files
  #if defined (_USE_MFC) || defined (_USE_AFX)
    #include <afx.h>
    #include <afxwin.h>         // MFC core and standard components
    #include <afxext.h>         // MFC extensions
    #include <afxdtctl.h>       // MFC support for Internet Explorer 4
                                // Common Controls

    #ifndef _AFX_NO_AFXCMN_SUPPORT
      #include <afxcmn.h>       // MFC support for Windows Common Controls
    #endif // _AFX_NO_AFXCMN_SUPPORT

    #ifndef _AFX_NO_DAO_SUPPORT
      //  #include <afxdao.h> //DAO Database support
      // Note: afxdao.h header file has enum duplicated in msado20.tlb resulting
      //       in numerous conflicts D.K.
    #endif

        //{{AFX_INSERT_LOCATION}}
        // Microsoft Visual C++ will insert additional declarations immediately
        // before the previous line.
  #else //!_USE_MFC  Windows SDK

    #include <wtypes.h>  //LPCTSTR typedef

  //---------------------------------------------------------------------------
  #endif //_USE_MFC

  #ifdef _MSC_VER
    #pragma comment( user, "Compiled on " __DATE__ " at " __TIME__ )

    /*Replaces library header file names with the compiler's aliases*/
    #ifdef _USE_STD_HEADERS
      //Microsoft Visual C/C++ compilers: replace custom header files With
      //vendor's files
      #pragma include_alias( "KTChar.h", "tchar.h" )  //TCHAR typedef
      #pragma include_alias( <KTChar.h>, <tchar.h> )  //TCHAR typedef
      #pragma include_alias( "KTime.h", "time.h" )    //tm struct
    #endif  //_USE_STD_HEADERS

    #ifndef YEAR_EPOCH_TM
      //Years in tm structure are represented as number of years since 1900.
      #define YEAR_EPOCH_TM  1900
    #endif
  #endif //_MSC_VER

//-----------------------------------------------------------------------------
#endif //_WIN32

#ifdef __cplusplus
  //===========================================================================
  //Standard Template Library header files
  //For build dependant of the Standard Template Library (STL)
  #if defined (_STL) || defined (_USE_STL)
    #ifdef _DEBUG
      #ifndef _STLP_DEBUG
        //#define _STLP_DEBUG 1  //Debug STLPort library
                                 //Note: have to be defined before STL header
                                 //files
      #endif
    #else
      #ifdef _STLP_DEBUG
        #undef _STLP_DEBUG
      #endif
    #endif

    /*Note: Include additional directory /I "..\..\STL\STLport\stlport" and
      appropriate STLport library in your make file, in order to replace
      compiler's native Standard Template Library.
     */

    #include "STL/KOStream.h" //ostream template, std::cout, std::endl
    #include <string>     //std::string

  //===========================================================================
  #endif //_STL
#else /*!__cplusplus (C compilation) */

  #ifdef __STDC__
    //ANSI C conformance (C99)
    #include <stdbool.h> //_Bool, bool typedef
  #else
    #include "KTypedef.h" /*_Bool, bool typedef*/
  #endif /*__STDC__ */

#endif //__cplusplus

///////////////////////////////////////////////////////////////////////////////
//Threading model
#ifndef _MT /*Defined when /MD or /MDd (Multithreaded DLL) or
             /MT or /MTd (Multithreaded) is specified.*/
  #ifndef _ST
    #define _ST 1998  /*singlethreaded application*/
  #endif
#endif

///////////////////////////////////////////////////////////////////////////////
//Project specific header files
#include "KTrace.h"   /*ASSERT_CL macro                         */
#include "KTestLog.h" /*CTestLog class                          */
#if !defined(UNUSED)
  #include "KProgCst.h"
#endif
// TODO: reference additional headers your program requires here

#ifndef PFUNCENTRY_TEST
  //Callback type for test entry point
  typedef int (*PFUNCENTRY_TEST) (void);
  #define PFUNCENTRY_TEST PFUNCENTRY_TEST
#endif PFUNCENTRY_TEST
  
///////////////////////////////////////////////////////////////////////////////
#endif // !defined(_STDAFX_H_)
/*****************************************************************************
 * $Log:
 *  10   Biblioteka1.9         2004-10-08 12:37:06  Darko
 *       _USE_STD_HEADERS
 *  9    Biblioteka1.8         2004-10-06 16:01:49  Darko           Unicode mapping
 *  8    Biblioteka1.7         2004-09-28 13:57:53  Darko           comments
 *  7    Biblioteka1.6         2004-09-28 12:21:16  Darko           comments
 *  6    Biblioteka1.5         2004-08-31 13:07:05  Darko           included
 *       KTestLog.h
 *  5    Biblioteka1.4         2004-08-26 13:20:38  Darko           Added C test
 *  4    Biblioteka1.3         2004-08-23 17:56:04  Darko           debugging macro
 *  3    Biblioteka1.2         2004-08-23 15:34:33  Darko
 *  2    Biblioteka1.1         2004-08-20 17:20:45  Darko           MFC depedencies
 *       enclosed with ifdef
 *  1    Biblioteka1.0         2004-08-17 18:30:28  Darko
 * $
 *****************************************************************************/
