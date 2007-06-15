/*$Workfile: KStrGetS.cpp$: implementation file
  $Revision: 7$ $Date: 2007-06-15 17:24:29$
  $Author: Darko Kolakovic$

  Retrieve substrings
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
  #ifdef _USE_MFC
    #define new DEBUG_NEW
  #endif //_USE_MFC
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
 *  7    Biblioteka1.6         2007-06-15 17:24:29  Darko Kolakovic _USE_MFC for
 *       CString
 *  6    Biblioteka1.5         2004-06-01 17:53:20  Darko           time sync
 *  5    Biblioteka1.4         2003-09-04 11:23:01  Darko           Unicode
 *  4    Biblioteka1.3         2002-02-04 19:56:22  Darko           include
 *       KTChar.h
 *  3    Biblioteka1.2         2002-01-25 16:58:23  Darko           Updated
 *       comments
 *  2    Biblioteka1.1         2001-12-23 01:21:01  Darko           _DEBUG
 *  1    Biblioteka1.0         2001-08-18 16:04:21  Darko           
 * $
 *  0    Biblioteka0           Darko Kolakovic  May '97
 *****************************************************************************/
