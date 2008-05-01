/*$Workfile: KAfxLib.h$: header file
  $Revision: 1.1 $ $Date: 2008/05/01 20:31:09 $
  $Author: ddarko $

  Fix: LNK2005 error involving nafxcwd.lib
  Copyright: CommonSoft Inc
  2008-04-26  Darko Kolakovic
 */

// Group=Windows

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
  #pragma once
#endif

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#if _AFX
///////////////////////////////////////////////////////////////////////////////
/*{group=Windows}
  FIX: A LNK2005 error occurs when the CRT library and MFC libraries are linked
  in the wrong order in Visual C++.

  When the C Run-Time (CRT) library and Microsoft Foundation Class (MFC)
  libraries are linked in the wrong order, you may receive one of the following
  LNK2005 errors:
      nafxcwd.lib(afxmem.obj) : error LNK2005:
      "void * __cdecl operator new(unsigned int)"(??2@YAPAXI@Z)
      already defined in LIBCMTD.lib(new.obj)

  When you use the MFC libraries, you must make sure that they are linked before
  the CRT library is linked. You can do this by making sure that every file in
  your project includes Msdev\Mfc\Include\Afx.h first, either directly
  (#include <afx.h>) or indirectly (#include <stdafx.h>).
  The afx.h include file forces the correct order of the libraries, by using
  the #pragma comment (lib,"<libname>") directive.
  If the source file has a .c extension, or the file has a .cpp extension but
  does not use MFC, you can create and include a small header file (KAfxLib.h)
  at the top of the module.
  This new header makes sure that the library search order is correct.

  Note: Microsoft Windows specific (Win32)
       and uses Microsoft Fundation Library (MFC).

  See also: MSDN article ID 148652 http://support.microsoft.com/kb/148652
*/
#ifndef _AFX_NOFORCE_LIBS

/////////////////////////////////////////////////////////////////////////////
// MFC libraries (MFC and afx)
// Note: the code for enforcing libraries linkage is extracted from
// Microsoft's <afx.h>

#ifndef _AFXDLL
  #ifndef _UNICODE
    #ifdef _DEBUG
      #pragma comment(lib, "nafxcwd.lib")
    #else
      #pragma comment(lib, "nafxcw.lib")
    #endif
  #else
    #ifdef _DEBUG
      #pragma comment(lib, "uafxcwd.lib")
    #else
      #pragma comment(lib, "uafxcw.lib")
    #endif
  #endif
#else
  //Microsoft Fundation Class (MFC) Library v7.1
  //Microsfot Visual C++ .Net 2003 v.7.1
  #ifndef _UNICODE
    #ifdef _DEBUG
      #pragma comment(lib, "mfc71d.lib")
      #pragma comment(lib, "mfcs71d.lib")
    #else
      #pragma comment(lib, "mfc71.lib")
      #pragma comment(lib, "mfcs71.lib")
    #endif
  #else
    #ifdef _DEBUG
      #pragma comment(lib, "mfc71ud.lib")
      #pragma comment(lib, "mfcs71ud.lib")
    #else
      #pragma comment(lib, "mfc71u.lib")
      #pragma comment(lib, "mfcs71u.lib")
    #endif
  #endif

  #if _MSC_VER < 1300 //MSVC less than ver 7.0
    //Microsfot Visual C/C++ v.6.0
    #pragma message ("MSVC ver. 6.0 or less")
    //Microsoft Fundation Class (MFC) Library v6.0 (see _MFC_VER = 0x600 in afxver_h.h)
    #ifndef _UNICODE
      #ifdef _DEBUG
        #pragma comment(lib, "mfc42d.lib")
        #pragma comment(lib, "mfcs42d.lib")
      #else
        #pragma comment(lib, "mfc42.lib")
        #pragma comment(lib, "mfcs42.lib")
      #endif
    #else
      #ifdef _DEBUG
        #pragma comment(lib, "mfc42ud.lib")
        #pragma comment(lib, "mfcs42ud.lib")
      #else
        #pragma comment(lib, "mfc42u.lib")
        #pragma comment(lib, "mfcs42u.lib")
      #endif
    #endif

  #endif
#endif

/////////////////////////////////////////////////////////////////////////////
// Win32 libraries

#ifdef _DLL
  #if !defined(_AFX_NO_DEBUG_CRT) && defined(_DEBUG)
    #pragma comment(lib, "msvcrtd.lib")
  #else
    #pragma comment(lib, "msvcrt.lib")
  #endif
#else
  #ifdef _MT
    #if !defined(_AFX_NO_DEBUG_CRT) && defined(_DEBUG)
      #pragma comment(lib, "libcmtd.lib")
    #else
      #pragma comment(lib, "libcmt.lib")
    #endif
  #else
    #if !defined(_AFX_NO_DEBUG_CRT) && defined(_DEBUG)
      #pragma comment(lib, "libcd.lib")
    #else
      #pragma comment(lib, "libc.lib")
    #endif
  #endif
#endif

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#if _MSC_VER >= 1300 //MSVC ver 7.0
  #pragma message ("MSVC ver. 7.0 or greater")
  #pragma comment(lib, "msimg32.lib")
#endif
#pragma comment(lib, "comdlg32.lib")
#pragma comment(lib, "winspool.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "comctl32.lib")
#if _MSC_VER >= 1300 //MSVC ver 7.0
  #pragma comment(lib, "shlwapi.lib")
#endif

// force inclusion of NOLIB.OBJ for /disallowlib directives
#pragma comment(linker, "/include:__afxForceEXCLUDE")

// force inclusion of DLLMODUL.OBJ for _USRDLL
#ifdef _USRDLL
  #pragma comment(linker, "/include:__afxForceUSRDLL")
#endif

// force inclusion of STDAFX.OBJ for precompiled types
#ifdef _AFXDLL
  #pragma comment(linker, "/include:__afxForceSTDAFX")
#endif

#endif //!_AFX_NOFORCE_LIBS

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: KAfxLib.h,v $
 * Revision 1.1  2008/05/01 20:31:09  ddarko
 * Fix: LNK2005 error
 *
 *****************************************************************************/
