/*$Workfile: H:\_SrcPool\Cpp\KFileNmB.cpp$: implementation file
  $Revision: 1.1 $ $Date: 2002/09/06 22:14:10 $
  $Author: ddarko $

  File Name Browser
  Copyright: CommonSoft Inc.
  May 94 Darko Kolakovic
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#ifdef WIN32 //Microsoft Win32 platform dependant

#ifdef _AFXDLL //use MFC library
  #include <AfxWin.h>
#else          //use MS SDK
  #include <Windows.h>
#endif

#include "KFileNmB.h" //CFileNameBrowser class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileNameBrowser

/*If the construction succeeds, the m_Handle member is used in a subsequent call to
  iteration operator. If the function fails, the value of m_Handle is
  INVALID_HANDLE_VALUE. To get extended error information, call GetLastError().
 */
CFileNameBrowser::CFileNameBrowser(LPCTSTR szFileName //[in] null-terminated string
                                   //with name of the file to search for
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
 * 3    Biblioteka1.2         7/16/02 1:40:59 AM   Darko           Fixed VSS Log 
 *      tag
 * 2    Biblioteka1.1         3/13/02 12:38:14 AM  Darko           
 * 1    Biblioteka1.0         3/12/02 11:00:49 PM  Darko           
 *$
 *****************************************************************************/
