/*$Workfile: KStrGetF.cpp$: implementation file
  $Revision: 5$ $Date: 2004-06-01 17:53:16$
  $Author: Darko$

  Retrieve position of first white character
  Copyright: CommonSoft Inc.
  May '97 Darko Kolakovic
*/

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#include <TChar.h>  /*TCHAR*/
#include "KStrings.h" /*Declaration                                          */

//GetFirstSpace()--------------------------------------------------------------------
/*Returns pointer to first white space or null-character found.
 */
TCHAR* GetFirstSpace(TCHAR* lpszSource  //[in] pointer to a source string
                     )
{
while( (*lpszSource != _T('\0')) && (!_istspace(*lpszSource)) )
  lpszSource++;
return lpszSource;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  5    Biblioteka1.4         2004-06-01 17:53:16  Darko           time sync
 *  4    Biblioteka1.3         2003-09-04 11:22:05  Darko           comment
 *  3    Biblioteka1.2         2002-01-25 16:58:18  Darko           Updated
 *       comments
 *  2    Biblioteka1.1         2001-12-23 18:05:00  Darko           TCHAR typo
 *       corrected
 *  1    Biblioteka1.0         2001-08-18 16:04:17  Darko           
 * $
 *  0    Biblioteka0           Darko Kolakovic  May '97
 *****************************************************************************/
