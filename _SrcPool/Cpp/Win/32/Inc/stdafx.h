/*$Workfile: stdafx.h$: header file
  $Revision: 16$  $Date: 2005-05-16 14:28:55$

  STandarD Application FrameworX
  header file includes standard system header files, or project specific header
  files that are used frequently, but are changed infrequently.
*/

#ifndef _STDAFX_H_
  /*$Workfile: stdafx.h$ sentry */
  #define _STDAFX_H_ 1432

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

  #if _MSC_VER == 1310
    #if !defined(WINVER)
      //Warning fix Q314963: WINVER not defined. Visual C++ .Net 2003 v7.1
      //Defaulting to 0x0501 (Windows XP and Windows .NET Server)
      #define WINVER 0x0501
    #endif
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

 #ifdef _UNICODE
    #if defined (_ATL_VER) && (_ATL_VER < 0x0700)
      #if !defined (UNICODE)
        //To enable Unicode character mapping for some Microsoft Visual C/C++
        //header files, the UNICODE definition is required.
        #define UNICODE
      #endif
    #endif //_ATL_VER
  #endif

//-----------------------------------------------------------------------------
#endif //_WIN32

#ifdef __cplusplus
  //===========================================================================
  //Standard Template Library header files
  //For build dependant of the Standard Template Library (STL)
  #ifdef _STL
    #ifdef _DEBUG
      #ifndef _STLP_DEBUG
        #define _STLP_DEBUG 1    //Debug STLPort library
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
//Project specific header files
#include "KTrace.h"   /*ASSERT_CL macro                         */
#include "KTestLog.h" /*CTestLog class                          */
#if !defined(UNUSED)
  #include "KProgCst.h"
#endif

// TODO: reference additional headers your program requires here

///////////////////////////////////////////////////////////////////////////////
#endif // !defined(_STDAFX_H_)
/*****************************************************************************
 * $Log:
 *  10   Biblioteka1.9         2005-04-28 18:11:36  Darko Kolakovic _STDAFX_H_
 *  9    Biblioteka1.8         2005-04-28 10:57:00  Darko Kolakovic
 *  8    Biblioteka1.7         2005-04-13 15:07:19  Darko Kolakovic defined
 *       _USE_AFX
 *  7    Biblioteka1.6         2004-11-02 15:32:35  Darko Kolakovic generalized for
 *       SDK
 *  6    Biblioteka1.5         2004-10-01 22:35:56  Darko           stdafx.h
 *  5    Biblioteka1.4         2003-09-24 18:40:39  Darko           Fixed VC++ .Net
 *       7.1 (2003) compilation
 *  4    Biblioteka1.3         2003-08-14 14:18:51  Darko           deleted
 *       afxdao.h
 *  3    Biblioteka1.2         2003-08-13 17:39:55  Darko           DAO Database
 *       support
 *  2    Biblioteka1.1         2003-08-13 13:55:32  Darko           Q314963
 *  1    Biblioteka1.0         2001-07-07 01:13:52  Darko
 * $
 *****************************************************************************/
