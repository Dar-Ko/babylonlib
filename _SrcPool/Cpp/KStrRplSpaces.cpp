/*$Workfile: KStrRplSpaces.cpp$: implementation file
  $Revision: 6$ $Date: 2004-06-01 17:53:35$
  $Author: Darko$

  Replace consecutive white spaces with single character
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

//ReplaceSpaces()--------------------------------------------------------------
/*Replaces all consecutive white space characters (TAB, VT, FF, CR and SPACE)
  with a single SPACE character. Consecutive new line characters (LF, 0xA) are
  replaced with single new line character, eliminating empty lines from the text
  string.

  TODO: DOS version (\n\r = EOL)

  Returns: source string with compressed white spaces, or NULL in case of 
  a failure.
 */
LPTSTR ReplaceSpaces(LPTSTR szSource //[in/out] zero-terminated string to be compressed
                     )
{
if ( (szSource == NULL) || (szSource[0] == 0) )
    return szSource; //Nothing to do

LPTSTR szTemp = new TCHAR[_tcslen(szSource) + 1];
if (szTemp == NULL)
  return NULL; //Failed to allocate memory

unsigned int i = 0;
unsigned int j = 0;
while ( szSource[i] != 0 )
  {
  if ( !_istspace(szSource[i]) ) //If character is not [0x09, 0x0D] or 0x20
    {
    szTemp[j] = szSource[i];
    j++;
    i++;
    }
  else
    {
    if ( j > 0) //Trim leading white space
      {
      //TODO: in MSDOS first char is \r 0xD
      if(szSource[i] != _T('\n')) //If character is not LF (0xA), replace whit space
        szTemp[j] = _T(' ');
      else
        szTemp[j] = _T('\n');
      j++;
      i++;
      while(_istspace(szSource[i])) //Skip consecutive white spaces
        i++;
      }
    else
      i++;
    }

  }

while(_istspace(szTemp[j-1])) //Cut-off trailing whitespace
  j--;

szTemp[j] = _T('\0');
_tcscpy(szSource, szTemp); //Copy back the result
delete[] szTemp;
return szSource;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  6    Biblioteka1.5         2004-06-01 17:53:35  Darko           time sync
 *  5    Biblioteka1.4         2003-11-03 13:12:11  Darko           Unicode fix
 *  4    Biblioteka1.3         2003-08-06 22:52:31  Darko           Comment
 *  3    Biblioteka1.2         2002-10-25 03:26:29  Darko Kolakovic Cut-off
 *       trailing whitespace
 *  2    Biblioteka1.1         2002-09-10 18:54:18  Darko Kolakovic Fixed 1 byte
 *       offset
 *  1    Biblioteka1.0         2002-09-09 23:16:48  Darko           
 * $
 *****************************************************************************/
