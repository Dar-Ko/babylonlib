/*$Workfile: KStrHtoL.c$: implementation file
  $Revision: 8$ $Date: 8/14/2003 5:04:22 AM$
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
 * 8    Biblioteka1.7         8/14/2003 5:04:22 AM Darko           comment
 * 7    Biblioteka1.6         8/19/2002 10:40:09 AMDarko Kolakovic 
 * 6    Biblioteka1.5         7/16/2002 1:41:24 AM Darko           Fixed VSS Log 
 *      tag
 * 5    Biblioteka1.4         3/7/2002 5:10:33 PM  Darko           updated
 *      comments
 * 4    Biblioteka1.3         12/23/2001 12:12:11 AMDarko           Unicode
 *      mappings
 * 3    Biblioteka1.2         7/11/2001 10:52:50 PMDarko           
 * 2    Biblioteka1.1         6/8/2001 11:51:55 PM Darko           VSS
 * 1    Biblioteka1.0         9/21/2000 1:13:34 AM Darko           
 *$
 *****************************************************************************/
