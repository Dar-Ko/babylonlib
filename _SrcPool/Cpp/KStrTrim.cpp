/*$Workfile: KStrTrim.cpp$: implementation file
  $Revision: 2$ $Date: 9/10/02 6:55:04 PM$
  $Author: Darko Kolakovic$

  Trims leading and trailing whitespace characters
  Copyright: CommonSoft Inc.
  Sep. 2k2 Darko Kolakovic
*/

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "KTChar.h"  /*TCHAR*/
#include "KStrings.h" //Declaration

#ifdef _DEBUG
  static char THIS_FILE[] = __FILE__;
#endif

//StrTrim()--------------------------------------------------------------------
/*Removes leading and trailing whitespace characters from a string.
  Whitespace characters are '\t','\n','\v','\f','\r' [0x09,0x0D] and ' ' (0x20).

  Returns: source string whitout leading and trailing whitespace characters,
  or NULL in case of a failure.
 */
LPTSTR StrTrim(LPTSTR szSource //[in/out] zero-terminated string to be trimmed
              )
{
if ( (szSource == NULL) || (szSource[0] == _T('/0')) )
  return szSource; //Nothing to do

  //Count leading white spaces
unsigned int iHead = 0;
while(_istspace(szSource[iHead]))
  iHead++;

  //When string has only white spaces, iHead is equal to string length.
unsigned int iTail = _tcslen(szSource);
if (iTail > iHead)
  {
    //Count trailing white spaces.
  iTail--;
  while(_istspace(szSource[iTail]))
    iTail--;

    //Move valid portion of the string to the begining
  if (iHead > 0)
    {
    unsigned int i = 0;
    while ( i <= (iTail - iHead) )
      {
      szSource[i] = szSource[iHead + i];
      i++;
      }
    }
  szSource[iTail - iHead + 1] = _T('\0'); //Cut off trailing white spaces
  }
else
  szSource[0] = _T('\0');

return szSource;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  2    Biblioteka1.1         9/10/02 6:55:04 PM   Darko Kolakovic Fixed tail
 *       trimming
 *  1    Biblioteka1.0         9/9/02 11:16:54 PM   Darko           
 * $
 *****************************************************************************/
