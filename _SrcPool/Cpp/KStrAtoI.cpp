/*$Workfile: KStrAtoI.cpp$: implementation file
  $Revision: 5$ $Date: 2004-10-08 11:34:32$
  $Author: Darko$

  Converts a string to integer
  Copyright: CommonSoft Inc.
  2003-09-23 Darko Kolakovic
*/

/* Group=Strings                                                             */
//

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

/*Replaces library header file names with the compiler's aliases*/
#ifdef _USE_STD_HEADERS
  #ifdef _WIN32
    #ifdef _MSC_VER //Micorsoft Visual Studio C++ compiler
      #ifdef _UNICODE
        #ifndef UNICODE
          //To enable Unicode for some Microsoft Visual C/C++ header files,
          //the UNICODE definition is required
          #define UNICODE
        #endif
      #endif
      #include <wtypes.h> //LPCTSTR struct
      #pragma include_alias("KTypedef.h", "stdint.h")
      #pragma include_alias("KTChar.h", "tchar.h")
    #endif  //_MSC_VER
  #endif  //_WIN32
#endif  //_USE_STD_HEADERS

#include "KTChar.h"
#include "KTypedef.h"


//-----------------------------------------------------------------------------
/*Convert an array of decimal digits to integer.
  Function parses until last digit found up to maximum nLen characters.
  The array could contain leading white space characters and sign character.
  The function stops reading the input string at the first character that it
  cannot recognize as part of a number.

  Returns: integer value produced by interpreting the input characters
  as a number or 0 if the input cannot be converted and number of characters
  successfuly parsed. The return value is undefined in case of overflow.

  Example:
    extern int AtoI(LPCTSTR strSource, uint_fast16_t& nLen);
    LPCTSTR szStr = _T("  -123456789 5555");
    int iResult = AtoI(szStr, 7); //iResult = -1234

 */
int AtoI(LPCTSTR strSource, //[in] pointer to array of digits to be
                             //converted.
         uint_fast16_t& nLen //[in/out] number of characters to parse;
                             //return value is number characters parsed or
                             //0 in case of failure.
         )
{
int iResult = 0;
uint_fast16_t nCount = 0; //parsed characters count
int iSign = 1;
  //Trim leading whitespace characters
while(_istspace (*strSource) && (nCount < nLen))
  {
  strSource++;
  nCount++;
  }

if (nCount < nLen)
  {
  if (*strSource == _T('-'))
    {
    iSign = -1;
    strSource++;
    nCount++;
    }
  else
    {
    iSign = 1;
    if (*strSource == _T('+'))
      {
      strSource++;
      nCount++;
      }
    }

  uint_fast16_t nDigits = nCount;
  while(_istdigit (*strSource) && (nCount < nLen))
    {
    iResult = 10 * iResult + *strSource++ - _T('0');
    nCount++;
    }
  if (nDigits == nCount)
    nCount = 0; //String does not conatin any digits
  }
nLen = nCount;
return (iSign  * iResult);
}

/*Convert a string to integer. The string could contain decimal digits,
  leading white space characters and sign character.

  The string argument for the function has the form:

      [whitespace] [sign]digits

  The function stops reading the input string at the first character that it
  cannot recognize as part of a number.

  Returns: integer value produced by interpreting the input characters
  as a number or 0 if the input cannot be converted. The return value is
  undefined in case of overflow. Also returns pointer to the character
  after the last parsed digit.

  Example:
    extern int AtoI(LPCTSTR* pszSource);
    LPCTSTR szStr = _T("  -123456789 5555");
    LPCTSTR szSource = szStr;
    int iResult = AtoI(&szSource); //iResult = -123456789
    iResult = AtoI(&szSource);     //iResult = 5555

  See also: atoi(), stdlib.h
 */
int AtoI(LPCTSTR* pszSource //[in/out] pointer to zero-terminated string to
                            //be converted; returns pointer to the first
                            //character not parsed.
         )
{
LPCTSTR pHead = *pszSource;
  //Trim leading whitespace characters
while(_istspace (*pHead))
  ++pHead;
int iSign;
if (*pHead == _T('-'))
  {
  iSign = -1;
  pHead++;
  }
else
  {
  iSign = 1;
  if (*pHead == _T('+'))
    pHead++;
  }

int iResult = 0;
while(_istdigit (*pHead))
  {
  iResult = 10 * iResult + *pHead++ - _T('0');
  }
*pszSource = pHead;
return (iSign * iResult);
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  3    Biblioteka1.2         2004-06-01 17:52:53  Darko           time sync
 *  2    Biblioteka1.1         2003-09-25 01:27:45  Darko           comment
 *  1    Biblioteka1.0         2003-09-23 17:08:14  Darko
 * $
 *****************************************************************************/
