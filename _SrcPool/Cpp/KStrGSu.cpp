/*$Workfile: KStrGSu.cpp$: implementation file
  $Revision: 3$ $Date: 1/25/02 4:58:13 PM$
  $Author: Darko$

  String helpers and CString extension
  Copyright: CommonSoft Inc.
  May '97 Darko Kolakovic
*/

/* Group=Strings                                                             */

#include "StdAfx.h"
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
*/
CString GetSubstring(CString& strSource, //[in] string to parse
                     LPCSTR Delimiters,  //[in] characters that delimits fields
                     int iSubstringIndex //[in] token to return starting index of
                     )
{
CString strToken(strSource);
int nPos,nCount = 0;
   //Parse source string and return result
while ((nPos = strToken.Find(_T(Delimiters))) != -1)
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
 *  0    Biblioteka0           Darko Kolakovic  May '97
 * $
 *****************************************************************************/
