/*$Workfile: KStrGetS.cpp$: implementation file
  $Revision: 6$ $Date: 2004-06-01 16:53:20$
  $Author: Darko$

  Retreive substrings
  Copyright: CommonSoft Inc.
  May '97 Darko Kolakovic
*/

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#ifndef _TCHAR_DEFINED
  #include "KTChar.h" //TCHAR typedef
#endif
#include "KStrings.h" /*Declaration                                          */

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//GetSubstring()---------------------------------------------------------------
/*Function returns pointer to beginning of iSubstringIndex token.
  If the null terminator is found before requested token, function returns
  a pointer to the null terminator.
*/
TCHAR* GetSubstring(TCHAR* szSource,         //[in] null-terminated string to parse
                    TCHAR  chDelimiter,      //[in] delimiter
                    int    iSubstringIndex   //[in] token to return starting index of
                    )
{
LPTSTR strToken = szSource;
int   nCount = 0;
  //return string itself
if (iSubstringIndex == 0)
  return szSource;
   //Parse source string and return result
while (*strToken != _T('\0'))
  {
  if (*strToken++ == chDelimiter)
    {
    nCount++;

    if (iSubstringIndex == nCount)
      return strToken;
    }
  }

return strToken;
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  6    Biblioteka1.5         2004-06-01 16:53:20  Darko           time sync
 *  5    Biblioteka1.4         2003-09-04 10:23:01  Darko           Unicode
 *  4    Biblioteka1.3         2002-02-04 18:56:22  Darko           include
 *       KTChar.h
 *  3    Biblioteka1.2         2002-01-25 15:58:23  Darko           Updated
 *       comments
 *  2    Biblioteka1.1         2001-12-23 00:21:01  Darko           _DEBUG
 *  1    Biblioteka1.0         2001-08-18 15:04:21  Darko           
 * $
 *  0    Biblioteka0           Darko Kolakovic  May '97
 *****************************************************************************/
