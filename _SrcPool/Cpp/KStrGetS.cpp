/*$Workfile: KStrGetS.cpp$: implementation file
  $Revision: 4$ $Date: 04/02/2002 6:56:22 PM$
  $Author: Darko$

  Retreive substrings
  Copyright: CommonSoft Inc.
  May '97 Darko Kolakovic
*/

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

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
TCHAR* GetSubstring(TCHAR* szSource,         //null-terminated string to parse
                    TCHAR  chDelimiter,      //delimiter
                    int    iSubstringIndex   //token to return starting index of
                    )
{
LPSTR strToken = szSource;
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
 *  0    Biblioteka0           Darko Kolakovic  May '97
 * $
 *****************************************************************************/
