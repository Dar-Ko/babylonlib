/*$Workfile: KStrIStr.c$: implementation file
  $Revision: 5$ $Date: 8/14/2003 11:35:36 AM$
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
 *  5    Biblioteka1.4         8/14/2003 11:35:36 AMDarko           comment
 *  4    Biblioteka1.3         8/14/2003 5:13:40 AM Darko           Renamed source
 *       file
 *  3    Biblioteka1.2         8/14/2003 5:12:35 AM Darko           Renamed source
 *       file
 *  2    Biblioteka1.1         8/14/2003 5:00:11 AM Darko           comment
 *  1    Biblioteka1.0         8/14/2003 4:57:23 AM Darko           
 * $
 *  0    Biblioteka1.0           Jan 1990 Darko Kolakovic
 *****************************************************************************/
