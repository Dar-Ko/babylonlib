/*$Workfile: KStrIStr.c$: implementation file
  $Revision: 5$ $Date: 2003-08-14 10:35:36$
  $Author: Darko$

  Searches for a substring ignoring case.
  Copyright: CommonSoft Inc.
  Jan 1990s Darko Kolakovic
 */

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "KTChar.h"  /*LPCTSTR*/

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//StrIStr()--------------------------------------------------------------------
/*Searches source string for the first match of a substring ignoring case.
  The search does not include terminating null characters.

  Returns: a pointer to the first occurrence of szToken in source string, or 
  NULL if szToken does not appear in string. If szToken points to a string
  of zero length, the function returns source string.

  See also: KStrings.h, FindNoCase()
 */
LPTSTR StrIStr(LPCTSTR szSource,//[in] zero-terminated string to search
               LPCTSTR szToken  //[in] zero-terminated string to search for
              )
{
LPTSTR szTemp = (LPTSTR)szSource;
const size_t nLength = _tcslen(szToken);

  //If token is empty or null string, return source string
if ((szToken == NULL) || (szToken[0] == _T('\0')))
  return szTemp;

while(*szTemp != _T('\0'))
  {
  if( _tcsnicmp(szTemp, szToken, nLength) != 0 )
    break;
  szTemp++;
  }
  //If source does not contain token, return null
if( *szTemp == _T('\0') )
  return NULL;

return szTemp;
}

/* ///////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log: 
 *  5    Biblioteka1.4         2003-08-14 10:35:36  Darko           comment
 *  4    Biblioteka1.3         2003-08-14 04:13:40  Darko           Renamed source
 *       file
 *  3    Biblioteka1.2         2003-08-14 04:12:35  Darko           Renamed source
 *       file
 *  2    Biblioteka1.1         2003-08-14 04:00:11  Darko           comment
 *  1    Biblioteka1.0         2003-08-14 03:57:23  Darko           
 * $
 *  0    Biblioteka1.0           Jan 1990 Darko Kolakovic
 *****************************************************************************/
