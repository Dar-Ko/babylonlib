/*$Workfile: KStrTrim.cpp$: implementation file
  $Revision: 6$ $Date: 2004-06-01 17:53:41$
  $Author: Darko$

  Trims leading and trailing whitespace characters
  Copyright: CommonSoft Inc.
  Sep. 2k2 Darko Kolakovic
*/

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#include "KTChar.h"  /*TCHAR*/
#include "KStrings.h" //Declaration

#ifdef _DEBUG
  static char THIS_FILE[] = __FILE__;
#endif

//StrTrim()--------------------------------------------------------------------
/*Removes leading and trailing whitespace characters from a string.
  Whitespace characters are '\t','\n','\v','\f','\r' [0x09,0x0D] and ' ' (0x20).

  Returns: source string without leading and trailing whitespace characters,
  or NULL in case of a failure.
 */
LPTSTR StrTrim(LPTSTR szSource //[in/out] zero-terminated string to be trimmed
              )
{
if ( (szSource == NULL) || (szSource[0] == 0) )
  return szSource; //Nothing to do

  //Count leading white spaces
unsigned int iHead = 0;
while(_istspace(szSource[iHead]))
  iHead++;

  //When string has only white spaces, iHead is equal to string length.
unsigned int nTail = (unsigned int)_tcslen(szSource);
if (nTail > iHead)
  {
    //Count trailing white spaces.
  nTail--;
  while(_istspace(szSource[nTail]))
    nTail--;

    //Move valid portion of the string to the begining
  if (iHead > 0)
    {
    unsigned int i = 0;
    while ( i <= (nTail - iHead) )
      {
      szSource[i] = szSource[iHead + i];
      i++;
      }
    }
  szSource[nTail - iHead + 1] = _T('\0'); //Cut off trailing white spaces
  }
else
  szSource[0] = _T('\0');

return szSource;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  6    Biblioteka1.5         2004-06-01 17:53:41  Darko           time sync
 *  5    Biblioteka1.4         2003-11-03 13:12:34  Darko           Unicode fix
 *  4    Biblioteka1.3         2003-09-04 11:25:12  Darko           fixed cast to
 *       unsigned int
 *  3    Biblioteka1.2         2002-10-25 03:28:16  Darko Kolakovic Handled strings
 *       with spaces only
 *  2    Biblioteka1.1         2002-09-10 18:55:04  Darko Kolakovic Fixed tail
 *       trimming
 *  1    Biblioteka1.0         2002-09-09 23:16:54  Darko           
 * $
 *****************************************************************************/
