/*$Workfile: KGetFileExtension.cpp$: implementation file
  $Revision: 3$ $Date: 2004-06-01 16:50:28$
  $Author: Darko$

  Copyright: CommonSoft Inc.
  2003-08 Darko Kolakovic
 */ 

  //Fix MS VC .Net 7.1 problem: without precompiled header WINVER not defined
#if _MSC_VER == 1310
  #ifndef WINVER
    #define WINVER 0x400
  #endif
#endif

//#include "stdafx.h"
#include <afxwin.h>


//-----------------------------------------------------------------------------
/*Call this function to extract the file extension from a filename.
  For example, if the name of the file entered is DATA.TXT, GetFileExt returns
  "TXT".

  Returns: extension of the filename.

  Note: uses Microsoft Fundation Library (MFC).

  TODO: Replace CString form afxwin.h with CString form KString.h D.K.
 */
CString GetFileExt(CString& strFileName //[in] filename
                   )
{
CString strExtension = 
  strFileName.Right(strFileName.GetLength() - strFileName.Find(_T("."))-1);
return strExtension;

/*Note: Win specific implementation replaced D.K.
      CString GetFileExt(LPCTSTR szFileName) 
      {
      TCHAR szExt[_MAX_EXT];
      _tsplitpath(szFileName, NULL, NULL, NULL, szExt);
      return CString(&szExt[1]);
      }
 */
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  3    Biblioteka1.2         2004-06-01 16:50:28  Darko           time sync
 *  2    Biblioteka1.1         2003-09-04 08:01:45  Darko           MSVC++ 7.1
 *       WINVER
 *  1    Biblioteka1.0         2003-08-19 15:13:34  Darko           
 * $
 *****************************************************************************/
