/*$Workfile: KDirGetExe.cpp$: implementation file
  $Revision: 3$ $Date: 02/05/2005 9:38:08 PM$
  $Author: Darko$

  Get directory of from the full executable file path.
  Copyright: CommonSoft Inc.
  Jan 98 Darko Kolakovic
 */
// Group=Windows

#include <stdafx>

#if !defined(_USE_MFC)
  #include "KString.h"  //CString.h
#endif

CString GetExeDirectory();

//GetExeDirectory()------------------------------------------------------------
/*Retrieves the full path for the executable file used to create the calling
  process.

  Returns: string object containing executable directory.
 */
CString GetExeDirectory()
{
TRACE(_T("GetExeDirectory()"));

CString strResult;
LPSTR szBuff = strResult.GetBuffer(_MAX_PATH);
      //Get path of the current module
VERIFY(::GetModuleFileName(NULL, szBuff, _MAX_PATH));
GetFileDirectory(szBuff,szBuff,_MAX_PATH);
strResult.ReleaseBuffer();

TRACE(_T("  executable directory is %s.\n"), strResult);
return strResult;
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  3    Biblioteka1.2         02/05/2005 9:38:08 PMDarko           Comments
 *  2    Biblioteka1.1         02/05/2005 8:46:35 PMDarko           
 *  1    Biblioteka1.0         02/05/2005 8:44:32 PMDarko           
 * $
 * 0:   Jan 98 Darko Kolakovic
 *****************************************************************************/
