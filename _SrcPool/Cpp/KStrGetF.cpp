/*$Workfile: KStrGetF.cpp$: implementation file
  $Revision: 3$ $Date: 1/25/02 4:58:18 PM$
  $Author: Darko$

  Retreive postion of first white character
  Copyright: CommonSoft Inc.
  May '97 Darko Kolakovic
*/

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include <TChar.h>  /*TCHAR*/
#include "KStrings.h" /*Declaration                                          */

//GetFirstSpace()--------------------------------------------------------------------
/*Returns pointer to first white space or null-character found.
 */
TCHAR* GetFirstSpace(TCHAR* lpszSource  //pointer to a source string
                     )
{
while( (*lpszSource != _T('\0')) && (!_istspace(*lpszSource)) )
  lpszSource++;
return lpszSource;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  0    Biblioteka0           Darko Kolakovic  May '97
 * $
 *****************************************************************************/
