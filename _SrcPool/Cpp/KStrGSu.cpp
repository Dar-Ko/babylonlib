/*$Workfile: KStrGSu.cpp$: implementation file
  $Revision: 5$ $Date: 2004-06-01 17:53:14$
  $Author: Darko$

  String helpers and CString extension
  Copyright: CommonSoft Inc.
  May '97 Darko Kolakovic
*/

/* Group=Strings                                                             */

//#include "stdafx.h"
#include <afxwin.h>
#include "KStrExt.h"  //Declarations

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//Functions using MFC
#ifdef __AFXWIN_H__
///////////////////////////////////////////////////////////////////////////////
// CString Extension functions

//GetSubstring()---------------------------------------------------------------
/*Finds the iSubstringIndex token in strSource. The set of characters in
  Delimiters specifies possible delimiters of the token to be found in
  strSource. If token is not found, strSource is returned.
  iSubstringIndex is the zero-based index of substring to be found.
  
  Note: uses Microsoft Fundation Library (MFC).

  Example:
    #include "KStrExt.h"
    {
    ...
    CString strSource("\\Machine/SharedDir\Subdir/FileName.ext");
    CString strFileName;
    strFileName = GetSubstring(strSource,_T("/\\"),4);
    ASSERT(strFileName = _T("FileName.ext"));
    strFileName = GetSubstring(strSource,_T("/\\"),3);
    ASSERT(strFileName = _T("Subdir/FileName.ext"));
    }

  TODO: replace MFC D.K.
*/
CString GetSubstring(CString& strSource, //[in] string to parse
                     LPCTSTR Delimiters, //[in] characters that delimits fields
                     int iSubstringIndex //[in] token to return starting index of
                     )
{
CString strToken(strSource);
int nPos,nCount = 0;
   //Parse source string and return result
while ((nPos = strToken.Find(Delimiters)) != -1)
  {
  if (nCount == iSubstringIndex)
    {
    strToken = strToken.Left(nPos);
    break;
    }
  nCount++;
  strToken = strToken.Mid(nPos + 1);
  }
return strToken;
}

///////////////////////////////////////////////////////////////////////////////
#endif //__AFXWIN_H__

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  5    Biblioteka1.4         2004-06-01 17:53:14  Darko           time sync
 *  4    Biblioteka1.3         2003-09-04 11:21:19  Darko           Unicode
 *  3    Biblioteka1.2         2002-01-25 16:58:13  Darko           Updated
 *       comments
 *  2    Biblioteka1.1         2001-12-23 01:20:05  Darko           
 *  1    Biblioteka1.0         2001-08-18 16:04:12  Darko           
 * $
 *  0    Biblioteka0           Darko Kolakovic  May '97
  ****************************************************************************/
