/*$Workfile: KStrEnum.cpp$: implementation file
  $Revision: 3$ $Date: 1/25/02 4:57:59 PM$
  $Author: Darko$

  Retreive substrings
  Copyright: CommonSoft Inc.
  May '97 Darko Kolakovic
*/
/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include <TChar.h>  /*TCHAR*/
#include "KStrings.h" //Declarations

//EnumSubstring()--------------------------------------------------------------
/*Determine the number of substrings delimited with separator character
 */
int EnumSubstring(const TCHAR* strSource,TCHAR chDelimiter/* = '\n'*/)
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

int EnumSubstring(const TCHAR* strSource,const TCHAR* Delimiters)
{
int iSubstringIndex = 0;    //Substring count
const int iDelimSize = strlen(Delimiters);
if ((strSource != NULL) || (iDelimSize > 0))
  {
  TCHAR* lpsz = const_cast<TCHAR*>(strSource);
  TCHAR* lpszNew;
  while ((lpszNew =_tcsstr(lpsz, Delimiters)) != NULL)
    {
    lpsz = lpszNew + iDelimSize;
    iSubstringIndex++;
    }
  }
return iSubstringIndex;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  0    Biblioteka0           Darko Kolakovic  May '97
 * $
 *****************************************************************************/
