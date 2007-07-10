/*$Workfile: KStrPalindrome.cpp$: implementation file
  $Revision: 5$ $Date: 2007-06-27 16:45:55$
  $Author: Darko Kolakovic$

  Verifies if a string is a palindrome.
  Copyright: CommonSoft Inc.
  2004-06-06 Darko Kolakovic
*/
/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#include "KTChar.h"   //TCHAR
#include "KStrings.h" //Declarations
#include "KTrace.h"   //Assert macro

//----------------------------------------------------------------------------
/*Validates if a string is a palindrome.
  Palindrome (from Greek, palin dromo, to run back again) is a word, number,
  phrase, clause, or sentence that can be read the same backwards as forwards.
  A palindrome has more than one letter or digit.

  Returns: true if a string is a palindrome; if the source string is
  the null-pointer or if it is not a palindrome, returns false.

  Example:
      #include "KStrings.h" //Declarations
      {
      ...
      LPCTSTR szPalindrome = _T("Roma tibi subito motibus ibit amor.");
      ASSERT(IsPalindrome(szPalindrome) == true);
      ...
      }

 */
bool IsPalindrome(LPCTSTR szSource //[in] zero-terminated string to validate
                  )
{
ASSERT(szSource != NULL);
return( IsPalindrome(szSource, (unsigned int)_tcslen(szSource)) );
}


bool IsPalindrome(LPCTSTR strSource,  //[in] string to validate
                 unsigned int nLength //[in] length of the string in characters
                  )
{
TRACE2(_T("IsPalindrome(%s, %d)\n"), strSource, nLength);

if ((strSource != NULL) && (nLength > 1 ))
  {
  bool bResult = true;
  unsigned int nHead = 0;
    //Ignore all leading and tailing white-space and marks.
    //Note: using array indexes instead pointers allows same code to be
    //reused for ASCII (char), MBSC and Unicode (wchar_t). The proper compiler
    //should optimize the code for the char and wchar_t types with no cost.
  while (!_istalnum(strSource[nHead]) && (nHead < nLength))
    nHead++;

  nLength--; //Tail index is actual length -1
  while (!_istalnum(strSource[nLength]) && (nLength > nHead))
    nLength--;

    //nHead walks forwards through string, nLength walks backwards.
  while(nLength > nHead)
    {
      /* Check if letters not equal, if so unset boolean. */
    if (_totlower(strSource[nHead]) != _totlower(strSource[nLength]))
      {
      bResult = false;
      break;
      }

      /* Move each pointer, ignore non-letters. */
    for(nHead++;   !_istalnum(strSource[nHead])  ; nHead++);
    for(nLength--; !_istalnum(strSource[nLength]); nLength--);
    }

  return bResult;
  }

return false; //Failed minimum criteria for a palindrome

}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2004-06-08 16:41:40  Darko
 * $
 *****************************************************************************/
