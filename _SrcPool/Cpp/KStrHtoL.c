/*$Workfile: KStrHtoL.c$: implementation file
  $Revision: 7$ $Date: 8/19/02 10:40:09 AM$
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
 * 7    Biblioteka1.6         8/19/02 10:40:09 AM  Darko Kolakovic 
 * 6    Biblioteka1.5         7/16/02 1:41:24 AM   Darko           Fixed VSS Log 
 *      tag
 * 5    Biblioteka1.4         3/7/02 5:10:33 PM    Darko           updated
 *      comments
 * 4    Biblioteka1.3         12/23/01 12:12:11 AM Darko           Unicode
 *      mappings
 * 3    Biblioteka1.2         7/11/01 10:52:50 PM  Darko           
 * 2    Biblioteka1.1         6/8/01 11:51:55 PM   Darko           VSS
 * 1    Biblioteka1.0         9/21/00 1:13:34 AM   Darko           
 *$
 *****************************************************************************/
