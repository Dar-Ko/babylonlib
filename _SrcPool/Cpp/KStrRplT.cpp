/*$Workfile: KStrRplT.cpp$: implementation file
  $Revision: 8$ $Date: 2007-06-15 17:24:36$
  $Author: Darko Kolakovic$

  Replace TAB characterts in CString with spaces
  May '97 Darko Kolakovic
*/
/* Group=Strings                                                             */

#include "stdafx.h"
#ifndef _USE_MFC
  #include "KStringHandler.h"
  #include "KString.h"  //CString class
#endif //_USE_MFC

#include "KStrExt.h"  //Declarations

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//Functions using MFC
#ifdef __AFXWIN_H__

//ReplaceTabs()----------------------------------------------------------------
/*Call this function to replace all occurences of the automatic stops (TAB)
  with the Space characters. Resulting columns of text will be aligned to the
  give tabulator postion iTabPos.

  Returns: source string with replaced characters.

  Note: uses Microsoft Foundation Library (MFC).

  Example:
     CString strTest("Summer\ttime\tis the\tbest");
     TRACE((LPTSTR)ReplaceTabs(strTest,4);

     Output:
     Summer  time    is the  best
     ^   ^   ^   ^   ^   ^   ^    - automatic stops

  TODO: replace MFC D.K.
 */
CString& ReplaceTabs(CString& strSource, //[in/out] string to be replaced
                     const int iTabPos   //[in] Tabulator position in characters
                     )
{
TCHAR* szSeparation = new TCHAR[iTabPos+1];
int iPos;
while ((iPos = strSource.Find(_T('\t'))) >= 0)
  {
  int i =  iTabPos - iPos % iTabPos;
  szSeparation[i] = _T('\0');
  while (i > 0)
    szSeparation[i--] = _T(' ');
  strSource = strSource.Left(iPos) + szSeparation + strSource.Mid(iPos + 1);
  }

delete[] szSeparation;
return strSource;
}

///////////////////////////////////////////////////////////////////////////////
#endif //__AFXWIN_H__

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  8    Biblioteka1.7         2007-06-15 17:24:36  Darko Kolakovic _USE_MFC for
 *       CString
 *  7    Biblioteka1.6         2005-04-26 16:39:28  Darko Kolakovic fixed typo
 *  6    Biblioteka1.5         2004-06-01 17:53:37  Darko           time sync
 *  5    Biblioteka1.4         2003-09-04 11:18:55  Darko           StdAfx.h
 *       excluded
 *  4    Biblioteka1.3         2003-08-14 04:56:49  Darko           header file
 *  3    Biblioteka1.2         2002-01-29 23:22:05  Darko           Used lbraries
 *       notes 
 *  2    Biblioteka1.1         2002-01-25 16:58:37  Darko           Updated
 *       comments
 *  1    Biblioteka1.0         2001-12-23 00:21:04  Darko           
 * $
 *  0    Biblioteka0           Darko Kolakovic  May '97
 *****************************************************************************/
