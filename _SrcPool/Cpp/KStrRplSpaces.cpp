/*$Workfile: KStrRplSpaces.cpp$: implementation file
  $Revision: 3$ $Date: 25/10/2002 2:26:29 AM$
  $Author: Darko Kolakovic$

  Replace consecutive white spaces with single character
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

//ReplaceSpaces()--------------------------------------------------------------
/*Replaces all consecutive white space characters (TAB, VT, FF, CR and SPACE)
  whit a single SPACE character. Consecutive new line characters (LF, 0xA) are
  replaced with single new line character, eliminating  empty lins from the text
  string.

  TODO: DOS version (\n\r = EOL)

  Returns: source string with compressed white spaces, or NULL in case of a failure
 */
LPTSTR ReplaceSpaces(LPTSTR szSource //[in/out] zero-terminated string to be compressed
                     )
{
if ( (szSource == NULL) || (szSource[0] == _T('/0')) )
    return szSource; //Nothing to do

LPTSTR szTemp = new TCHAR[_tcslen(szSource) + 1];
if (szTemp == NULL)
  return NULL; //Failed to allocate memory

unsigned int i = 0;
unsigned int j = 0;
while ( szSource[i] != _T('\0') )
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
 *  3    Biblioteka1.2         25/10/2002 2:26:29 AMDarko Kolakovic Cut-off
 *       trailing whitespace
 *  2    Biblioteka1.1         10/09/2002 5:54:18 PMDarko Kolakovic Fixed 1 byte
 *       offset
 *  1    Biblioteka1.0         09/09/2002 10:16:48 PMDarko           
 * $
 *****************************************************************************/
