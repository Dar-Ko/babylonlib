/*$Workfile: KStrEnum.cpp$: implementation file
  $Revision: 5$ $Date: 2004-06-01 16:53:01$
  $Author: Darko$

  Retreive substrings
  Copyright: CommonSoft Inc.
  May '97 Darko Kolakovic
*/
/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#include "KTChar.h"  /*TCHAR*/
#include "KStrings.h" //Declarations

//EnumSubstring()--------------------------------------------------------------
/*Determines the number of substrings delimited with separator character.

  Returns: number of delimited text parts.
 */
int EnumSubstring(const TCHAR* strSource, //[in] zero-terminated string to search
                  TCHAR chDelimiter//[in]= '\n' text separator
                  )
{
int iSubstringIndex = 0;    //Substring count

if (strSource != NULL)
  while (*(TCHAR *)strSource != '\0')
    {
    if (*(TCHAR *)strSource == chDelimiter)
      iSubstringIndex++;
    strSource++;
    }

return iSubstringIndex;
}

/*Determine the number of substrings delimited with separator word.

  Returns: number of delimited text parts or 0 if separator word is an empty
  string.
 */
int EnumSubstring(const TCHAR* strSource, //[in] zero-terminated string to search
                  const TCHAR* szDelimiter //[in] a zero-terminated word used as 
                                           //text separator
                  )
{
int iSubstringIndex = 0;    //Substring count
const unsigned int nDelimSize = (unsigned int)_tcslen(szDelimiter);
if ((strSource != NULL) || (nDelimSize > 0))
  {
  TCHAR* lpsz = const_cast<TCHAR*>(strSource);
  TCHAR* lpszNew;
  while ((lpszNew =_tcsstr(lpsz, szDelimiter)) != NULL)
    {
    lpsz = lpszNew + nDelimSize;
    iSubstringIndex++;
    }
  }
return iSubstringIndex;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  5    Biblioteka1.4         2004-06-01 16:53:01  Darko           time sync
 *  4    Biblioteka1.3         2003-08-25 01:53:39  Darko           Unicode
 *  3    Biblioteka1.2         2002-01-25 15:57:59  Darko           Updated
 *       comments
 *  2    Biblioteka1.1         2001-08-19 22:55:06  Darko           Butyfier
 *  1    Biblioteka1.0         2001-08-18 15:04:03  Darko           
 * $
 *  0    Biblioteka0           Darko Kolakovic  May '97
 *****************************************************************************/
