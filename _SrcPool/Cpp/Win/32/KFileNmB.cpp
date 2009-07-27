/*$Workfile: KFileNmB.cpp$: implementation file
  $Revision: 5$ $Date: 2007-05-03 15:53:07$
  $Author: Darko Kolakovic$

  File Name Browser
  Copyright: CommonSoft Inc.
  May 94 Darko Kolakovic
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#ifdef WIN32 //Microsoft Win32 platform dependant

#ifdef _AFXDLL //use MFC library
  #include <afxwin.h>
#else          //use MS SDK
  #ifndef _USE_ATL
    #include <windows.h>
    #ifndef TRACE0
      #ifndef _T
        #include "KTChar.h"
      #endif
      #include "KTrace.h" //Debugging macros
    #endif
  #else
    #include "KTraceAtl.h"
  #endif
#endif

#include "KFileNmB.h" //CFileNameBrowser class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileNameBrowser

/*If the construction succeeds, the m_Handle member is used in a subsequent call
  to iteration operator. If the function fails, the value of m_Handle is
  INVALID_HANDLE_VALUE. Use IsFileFound() to validate the handle.
  To get extended error information, call GetLastError().
 */
CFileNameBrowser::CFileNameBrowser(LPCTSTR szFileName //[in] null-terminated
                                   //string with name of the file to search for
                                   ) :
  m_Handle(::FindFirstFile(szFileName, &m_FindData)),
  m_bDone(FALSE)
{
}

CFileNameBrowser::~CFileNameBrowser()
{
if (m_Handle != INVALID_HANDLE_VALUE)
  #ifdef _DEBUG
    if (!::FindClose(m_Handle))
      TRACE0("FindClose() failed! \n");
  #else
    ::FindClose(m_Handle);
  #endif
}

//::operator ++()----------------------------------------------------
/*Prefix operator continues a file search from a previous call to
  the FindFirstFile() or operator ++(). Returns file name found.

 Example:
  #include "KFileNmB.h" //CFileNameBrowser class
  ...
  CFileNameBrowser FileName(szFileName);
  while(!FileName.IsLastFileFound())
    {
    TRACE0("File %s\n",++FileName);
    }

 */
LPCTSTR CFileNameBrowser::operator ++()
{
if (!::FindNextFile(m_Handle, &m_FindData))
  {
  m_bDone = TRUE;
  if (GetLastError() != ERROR_NO_MORE_FILES)
    {
    TRACE0("::FindNextFile() failed\n");
    return NULL; //an error occured (see GetLastError() result)
    }
  }
return  FindData().cFileName;
}

///////////////////////////////////////////////////////////////////////////////
#endif //WIN32
/******************************************************************************
 *$Log:
 * 3    Biblioteka1.2         2002-07-16 01:40:59  Darko           Fixed VSS Log
 *      tag
 * 2    Biblioteka1.1         2002-03-13 00:38:14  Darko
 * 1    Biblioteka1.0         2002-03-12 23:00:49  Darko
 *$
 *****************************************************************************/
