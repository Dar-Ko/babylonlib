/*$Workfile: KStrHtoL.c$: implementation file
  $Revision: 8$ $Date: 2003-08-14 04:04:22$
  $Author: Darko$

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
 
  Returns: value of the string number.

  See also: KStrings.h
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
 * 8    Biblioteka1.7         2003-08-14 04:04:22  Darko           comment
 * 7    Biblioteka1.6         2002-08-19 09:40:09  Darko Kolakovic 
 * 6    Biblioteka1.5         2002-07-16 00:41:24  Darko           Fixed VSS Log 
 *      tag
 * 5    Biblioteka1.4         2002-03-07 16:10:33  Darko           updated
 *      comments
 * 4    Biblioteka1.3         2001-12-22 23:12:11  Darko           Unicode
 *      mappings
 * 3    Biblioteka1.2         2001-07-11 21:52:50  Darko           
 * 2    Biblioteka1.1         2001-06-08 22:51:55  Darko           VSS
 * 1    Biblioteka1.0         2000-09-21 00:13:34  Darko           
 *$
 *****************************************************************************/
