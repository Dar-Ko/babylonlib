/*$Workfile: KStrRpl.cpp$: implementation file
  $Revision: 4$ $Date: 1/29/02 10:21:58 PM$
  $Author: Darko$

  Replace characters in CString
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

//ReplaceChar()----------------------------------------------------------------
/*Call this function to replace all occurences of the chOld with the chNew.

  Note: uses Microsoft Fundation Library (MFC).
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
 *  0    Biblioteka0           Darko Kolakovic  May '97
 * $
 *****************************************************************************/
