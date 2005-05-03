/*$Workfile: KBtnEx.cpp$: implementation file
  $Revision: 10$ $Date: 2004-10-01 22:33:41$
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
 * $Log: $
 * 0:   Jan 98 Darko Kolakovic
 *****************************************************************************/
