/*$Workfile: KStrRpl.cpp$: implementation file
  $Revision: 8$ $Date: 2007-06-15 17:24:35$
  $Author: Darko Kolakovic$

  Replace characters in CString
  May '97 Darko Kolakovic
*/
/* Group=Strings                                                             */

#include "stdafx.h"
#ifndef _USE_MFC
  #include "KStringHandler.h"
  #include "KString.h"
#endif
#include "KStrExt.h"  //Declarations

#ifdef _DEBUG
  #ifdef _USE_MFC
    #define new DEBUG_NEW
  #endif //_USE_MFC
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//Functions using MFC
#ifdef __AFXWIN_H__

//ReplaceChar()----------------------------------------------------------------
/*Call this function to replace all occurrences of the chOld with the chNew.

  Note: uses Microsoft Foundation Library (MFC).

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
 *  8    Biblioteka1.7         2007-06-15 17:24:35  Darko Kolakovic _USE_MFC for
 *       CString
 *  7    Biblioteka1.6         2005-04-26 16:39:26  Darko Kolakovic fixed typo
 *  6    Biblioteka1.5         2004-06-01 17:53:32  Darko           time sync
 *  5    Biblioteka1.4         2003-09-04 11:23:56  Darko           StdAfx.h
 *       excluded
 *  4    Biblioteka1.3         2002-01-29 23:21:58  Darko           Used lbraries
 *       notes 
 *  3    Biblioteka1.2         2002-01-25 16:58:32  Darko           Updated
 *       comments
 *  2    Biblioteka1.1         2001-12-22 19:26:08  Darko           Header updated
 *  1    Biblioteka1.0         2001-08-18 16:04:31  Darko           
 * $
 *  0    Biblioteka0           Darko Kolakovic  May '97
 *****************************************************************************/
