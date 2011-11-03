/*$RCSfile: KGetModuleVersion.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2011/11/03 00:07:44 $
  $Author: ddarko $

  Retrieve file version of a module.
  Copyright: Artisitic License.
  Jan 97 Darko Kolakovic
 */

#include "stdafx.h"

#pragma comment(lib,"version.lib")
#ifndef uint16
  typedef unsigned short uint16;
#endif
#ifndef uint32
  typedef unsigned long uint32;
#endif

//-----------------------------------------------------------------------------
/*
  A file version number is a 64-bit number that holds the version number for
  a file as follows:

    - the first 16 bits are the FileMajorPart number.
    - the next 16 bits are the FileMinorPart number.
    - the third set of 16 bits are the FileBuildPart number.
    - the last 16 bits are the FilePrivatePart number.

  The FileVersionInfo properties are based on version resource information 
  built into the file. Version resources are often built into binary files 
  such as .exe or .dll files; text files do not have version resource 
  information.
  Version resources are typically specified in a Win32 resource file or
  in assembly attributes. 

  Note: Microsoft Windows specific (Win).

 */
bool GetModuleVersion(LPCTSTR szModuleName, //[in]
                      uint16& MajorVersion, //[out]
                      uint16& MinorVersion, //[out]
                      uint16& nBuild,       //[out]
                      uint16& nRevision     //[out]
                      )
{
bool bResult = false;
if ((szModuleName == NULL) || (szModuleName[0] == _T('\0')))
  {
  TRACE(_T("GetModuleVersion(NULL)"));
  return bResult;
  }

TRACE1(_T("GetModuleVersion(%s)"), szModuleName);
uint32 dwHandle = 0; 

#if _MSC_VER > 1200
  LPCTSTR& pModuleName = szModuleName;
#else //MSVC 6.0
  LPTSTR pModuleName = const_cast<LPTSTR>(szModuleName);
#endif

uint32 nLength = GetFileVersionInfoSize(pModuleName, &dwHandle);

if (nLength > 0)
  {
  LPBYTE lpVersionInfo = (LPBYTE)new char[nLength];
  ASSERT(lpVersionInfo != NULL);
  if (GetFileVersionInfo( pModuleName, 0, nLength, lpVersionInfo) == TRUE)
    {
    VS_FIXEDFILEINFO* pFileInfo = NULL;
    UINT nFileInfoSize = 0;
    if(VerQueryValue(lpVersionInfo, "\\", (LPVOID*)&pFileInfo, &nFileInfoSize) == TRUE)
      {
      MajorVersion = HIWORD(pFileInfo->dwFileVersionMS);
      MinorVersion = LOWORD(pFileInfo->dwFileVersionMS);
      nBuild       = HIWORD(pFileInfo->dwFileVersionLS);
      nRevision    = LOWORD(pFileInfo->dwFileVersionLS);
      bResult = true;
      }
    }
  delete[] lpVersionInfo;
  }
else
  {
  TRACE1(_T("  failed (error 0X%08X)!\n"), GetLastError());
  }
return bResult;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: KGetModuleVersion.cpp,v $
 * Revision 1.2  2011/11/03 00:07:44  ddarko
 * MSVC 6.0 build
 *
 * Revision 1.1  2011/09/19 22:44:03  ddarko
 * Moved from old repository
 *
 *****************************************************************************/
