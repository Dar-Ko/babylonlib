/*$Workfile: KStrRpl.cpp$: implementation file
  $Revision: 6$ $Date: 2004-06-01 16:53:32$
  $Author: Darko$

  Replace characters in CString
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

//ReplaceChar()----------------------------------------------------------------
/*Call this function to replace all occurences of the chOld with the chNew.

  Note: uses Microsoft Fundation Library (MFC).

  TODO: replace MFC D.K.
 */
CString& ReplaceChar(CString& strSource, //[in/out] source string
                     TCHAR chOld,        //[in] character to be replaced
                     TCHAR chNew         //[in] new character
                     )
{
int iPos = strSource.Find(chOld);
while (iPos != -1)
  {
  strSource.SetAt(iPos, chNew);
  iPos = strSource.Find(chOld);
  }
return strSource;
}

///////////////////////////////////////////////////////////////////////////////
#endif //__AFXWIN_H__

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  6    Biblioteka1.5         2004-06-01 16:53:32  Darko           time sync
 *  5    Biblioteka1.4         2003-09-04 10:23:56  Darko           StdAfx.h
 *       excluded
 *  4    Biblioteka1.3         2002-01-29 22:21:58  Darko           Used lbraries
 *       notes 
 *  3    Biblioteka1.2         2002-01-25 15:58:32  Darko           Updated
 *       comments
 *  2    Biblioteka1.1         2001-12-22 18:26:08  Darko           Header updated
 *  1    Biblioteka1.0         2001-08-18 15:04:31  Darko           
 * $
 *  0    Biblioteka0           Darko Kolakovic  May '97
 *****************************************************************************/
