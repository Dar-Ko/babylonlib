/*$Workfile: KStrHtoL.c$: implementation file
  $Revision: 7$ $Date: 19/08/2002 9:40:09 AM$
  $Author: Darko Kolakovic$

  Converts hexadecimal string to long integer
  Jan. 96 Darko Kolakovic
*/

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "KTChar.h" /*_tcschr()*/

#ifdef _DEBUG
  static char THIS_FILE[] = __FILE__;
#endif

/*HextoL()-------------------------------------------------------------------*/

/*Convert hexadecimal string to long integer.
  The scan ends when a non-hexadecimal character is hit.
*/
long HextoL(LPCTSTR szSource //[in] zero-terminated string representing a 
                             //hexadecimal number
           )
{
register long lResult = 0;

while(_istxdigit(*szSource))
  {
  lResult <<= 4;
  if(_istdigit(*szSource)) 
    lResult |= (*szSource - _T('0'));
  else 
    lResult |= (_toupper(*szSource) - _T('A') + 10);
  szSource++;
  }
return lResult;
}
/*///////////////////////////////////////////////////////////////////////////*/
/******************************************************************************
 *$Log: 
 * 7    Biblioteka1.6         19/08/2002 9:40:09 AMDarko Kolakovic 
 * 6    Biblioteka1.5         16/07/2002 12:41:24 AMDarko           Fixed VSS Log 
 *      tag
 * 5    Biblioteka1.4         07/03/2002 4:10:33 PMDarko           updated
 *      comments
 * 4    Biblioteka1.3         22/12/2001 11:12:11 PMDarko           Unicode
 *      mappings
 * 3    Biblioteka1.2         11/07/2001 9:52:50 PMDarko           
 * 2    Biblioteka1.1         08/06/2001 10:51:55 PMDarko           VSS
 * 1    Biblioteka1.0         21/09/2000 12:13:34 AMDarko           
 *$
 *****************************************************************************/
