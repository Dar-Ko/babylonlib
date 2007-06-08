/*$Workfile: KStrVowel.cpp$: implementation file
  $Revision: 1$ $Date: 2007-05-31 12:34:41$
  $Author: Darko Kolakovic$

  Verifies if a character is a vowel.
  Copyright: CommonSoft Inc.
  2004-06-06 Darko Kolakovic
*/
/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#include "KTChar.h"   //TCHAR
#include "KStrings.h" //Declarations
#include "KTrace.h"   //Assert macro

#ifndef LANG_CURRENT
  #define LANG_CURRENT LANG_ENGLISH
#endif

//----------------------------------------------------------------------------
/*Validates if a character is a vowel.

  Returns: true a character is a vowel or false if it is not.
 */
bool IsVowel(TCHAR ch //[in] character to validate
             )
{
TRACE1("IsVowel(%c)\n", ch);
//TODO: localization
#if (LANG_CURRENT == LANG_ENGLISH)
  LPCTSTR szVowelSet = _T("AEIOUaeiou");

  int i = 0;
  while (szVowelSet[i] != _T('\0'))
    {
    if (szVowelSet[i] == ch)
      return true;
    i++;
    }
#endif

#if (LANG_CURRENT == LANG_GERMAN)

#endif

return false; 
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2007-05-31 12:34:41  Darko Kolakovic 
 * $
 *****************************************************************************/
