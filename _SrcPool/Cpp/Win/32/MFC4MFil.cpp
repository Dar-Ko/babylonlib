/*$RCSfile: MFC4MFil.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2009/09/01 15:11:50 $
  $Author: ddarko $

  Fix: CMirrorFile memory overrun (MSDN Q163253)
  Darko Kolakovic
  March 99
 */

// Group=Windows

#include "StdAfx.h"
#include "MFC4MFil.h" //CFixMirrorFile class

#ifdef _MFC40
  #define _FIX_Q163253
#endif
#ifdef _MFC41
  #define _FIX_Q163253
#endif
#ifdef _MFC42
  #define _FIX_Q163253
#endif

#ifdef _FIX_Q163253
  #pragma message (__FILE__ " MFC Version 4.x")

/*Note: 1. Open Visual C++ Menu Tools/Options...
        2. select tab Directories
        3. select Show directories for: Include files
        4. type X:\MSDev\MFC\Src\
 */
#include "AfxImpl.h" // \MSDev\MFC\Src\AfxImpl.h
///////////////////////////////////////////////////////////////////////////////
//Open()-----------------------------------------------------------------------
/*FIX: "Out of Memory" Error When Saving to an Existing File ( MFC4.0 4.1 4.2 )
  When you save to an existing file in a Visual C++ MFC application, an
  "Out of memory" error occurs. The error occurs only when you save over an
  existing file on a non-NT platform, such as Windows 95, that is on a network.
  Article ID: Q163253
 */
BOOL CFixMirrorFile::Open(LPCTSTR lpszFileName,
                         UINT nOpenFlags,
                         CFileException* pError
                         )
{
ASSERT(lpszFileName != NULL);
m_strMirrorName.Empty();

#ifndef _MAC
  CFileStatus status;
  if (nOpenFlags & CFile::modeCreate) //opened for writing
    {
    if (CFile::GetStatus(lpszFileName, status))
      {
      CString strRoot;
      AfxGetRoot(lpszFileName, strRoot);

      DWORD dwSecPerClus, dwBytesPerSec, dwFreeClus, dwTotalClus;
      int nBytes = 0;
      if (GetDiskFreeSpace(strRoot,
                           &dwSecPerClus,
                           &dwBytesPerSec,
                           &dwFreeClus,
                           &dwTotalClus))
        {
        nBytes = dwFreeClus*dwSecPerClus*dwBytesPerSec;
        }

      if (nBytes > 2*status.m_size) // at least 2x free space avail
        {
        // get the directory for the file
        TCHAR szPath[_MAX_PATH];
        LPTSTR lpszName;
        GetFullPathName(lpszFileName, _MAX_PATH, szPath, &lpszName);
        *lpszName = NULL;

        //let's create a temporary file name
        GetTempFileName(szPath, _T("MFC"), 0,
           m_strMirrorName.GetBuffer(_MAX_PATH+1));
        m_strMirrorName.ReleaseBuffer();
        }
      }
    }
#endif  // not _MAC

if (!m_strMirrorName.IsEmpty() &&
     CFile::Open(m_strMirrorName, nOpenFlags, pError))
  {
  m_strFileName = lpszFileName;

  #ifndef _MAC
    FILETIME ftCreate, ftAccess, ftModify;
    if (::GetFileTime((HANDLE)m_hFile, &ftCreate, &ftAccess, &ftModify))
      {
      AfxTimeToFileTime(status.m_ctime, &ftCreate);
      SetFileTime((HANDLE)m_hFile, &ftCreate, &ftAccess, &ftModify);
      }

      // If GetFileSecurity returns an error, don't do anything with
      // file securities.
    DWORD dwLength = 0;
    PSECURITY_DESCRIPTOR pSecurityDescriptor = NULL;
    if (GetFileSecurity(lpszFileName,
                        DACL_SECURITY_INFORMATION,
                        NULL,
                        dwLength,
                        &dwLength))
      {
      pSecurityDescriptor = (PSECURITY_DESCRIPTOR) new BYTE[dwLength];
      if (::GetFileSecurity(lpszFileName,
                            DACL_SECURITY_INFORMATION,
                            pSecurityDescriptor,
                            dwLength,
                            &dwLength))
        {
        SetFileSecurity(m_strMirrorName,
                        DACL_SECURITY_INFORMATION, pSecurityDescriptor);
        }
      delete[] (BYTE*)pSecurityDescriptor;
      }
  #endif   //not _MAC #2

  return TRUE;
  }
m_strMirrorName.Empty();
return CFile::Open(lpszFileName, nOpenFlags, pError);
}

///////////////////////////////////////////////////////////////////////////////
#endif //_FIX_Q163253
/*****************************************************************************
 * $Log: MFC4MFil.cpp,v $
 * Revision 1.2  2009/09/01 15:11:50  ddarko
 * Reformatted
 *
 *****************************************************************************/

