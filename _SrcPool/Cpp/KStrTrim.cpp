/*$Workfile: KStrTrim.cpp$: implementation file
  $Revision: 1$ $Date: 9/9/02 11:16:54 PM$
  $Author: Darko$

  Trims leading and trailing whitespace characters
  Copyright: CommonSoft Inc.
  Sep. 2k2 Darko Kolakovic
*/

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "KTChar.h"  /*TCHAR*/

#ifdef _DEBUG
  static char THIS_FILE[] = __FILE__;
#endif

//StrTrim()--------------------------------------------------------------------
/*Trims leading and trailing whitespace characters from the string.

  Returns: source string whitout leading and trailing whitespace characters,
  or NULL in case of a failure
 */
LPTSTR StrTrim(LPTSTR szSource //[in/out] zero-terminated szSource to be trimmed
              )
{
if ( (szSource == NULL) || (szSource[0] == _T('/0')) )
    return szSource; //Nothing to do

  //Count leading white spaces
unsigned int iHead = 0;
while(_istspace(szSource[iHead]))
  iHead++;

  //Count trailing white spaces
unsigned int iTail = _tcslen(szSource);
while(_istspace(szSource[iTail]))
  iTail--;
  //Move valid portion of the string to the begining
if (iHead > 0)
  {
  unsigned int i = 0;
  while ( i < (iTail - iHead) )
    {
    szSource[i] = szSource[iHead + i];
    i++;
    }
  }
szSource[iTail] = _T('\0'); //Cout of trailing white spaces
return szSource;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         9/9/02 11:16:54 PM   Darko           
 * $
 *****************************************************************************/
