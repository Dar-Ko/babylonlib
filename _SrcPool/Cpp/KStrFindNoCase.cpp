/*$Workfile: S:\_SrcPool\Cpp\KStrFindNoCase.cpp$: implementation file
  $Revision: 4$ $Date: 2005-04-26 16:39:20$
  $Author: Darko Kolakovic$

  Searches for a substring ignoring case.
  2003-08 Darko Kolakovic
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

//-----------------------------------------------------------------------------
/*Searches source string for the first match of a substring ignoring case.

  Returns: zero-based index of the first character in strSource object 
  that matches the requested substring or characters; -1 if the substring or
  character is not found.

  See also: StrIStr()

  Note: uses Microsoft Foundation Library (MFC).

  TODO: Replace CString form afxwin.h with CString form KString.h D.K.
 */
int FindNoCase(const CString& strSource, //[in] source string
               LPCTSTR szToken, //[in] substring to search for
               const unsigned nStart //[in]= 0 index of the character in
               //the string to begin the search with, or 0 to start from the beginning.
               )

{
CString strLower = strSource;
strLower.MakeLower();

CString strToken = szToken;
strToken.MakeLower();

return strLower.Find(strToken, nStart);
}

///////////////////////////////////////////////////////////////////////////////
#endif //__AFXWIN_H__

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  4    Biblioteka1.3         2005-04-26 16:39:20  Darko Kolakovic fixed typo
 *  3    Biblioteka1.2         2004-06-01 17:53:10  Darko           time sync
 *  2    Biblioteka1.1         2003-08-19 16:12:56  Darko           comment
 *  1    Biblioteka1.0         2003-08-14 11:34:34  Darko           
 * $
 *****************************************************************************/
