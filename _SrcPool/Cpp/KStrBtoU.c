/*$Workfile: KStrBtoU.c$: implementation file
  $Revision: 5$ $Date: 8/13/02 6:51:02 PM$
  $Author: Darko Kolakovic$

  Converts a binary string to DWORD value
  May 96 Darko Kolakovic
*/

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "KTChar.h"  /*_tcschr()*/

#ifdef _DEBUG
  #ifdef _WIN32
    #include <CrtDbg.h>	//_RPT macros Win NT, Win 95
  #endif
  static char THIS_FILE[] = __FILE__;
#endif

#ifndef DWORD
  #include "KTypedef.h"
#endif

/*///////////////////////////////////////////////////////////////////////////*/
/* Group=Strings                                                             */

/*BintoU()-------------------------------------------------------------------*/
/*Convert a binary string to DWORD value. String is expected to be without any
  whitespaces. If string has more than 32 binary digits, only last (less 
  significant) 32 bits are converted to double word value.

  Example:
    #include "KStrings.h"
    void main ()
      {
      char *buffer = "01111000100";
      DWORD dwNumber;
      dwNumber = BintoU(buffer);

      printf ( "Convert a binary string %s to unsigned integer: %u\n", 
               buffer, dwNumber);
      }
 */
DWORD BintoU(TCHAR* lpszValue /*zero-terminated source string*/
             )
{
#ifdef _DEBUG
  int iSizeOfDWORD = sizeof(DWORD)*8; /*number of bits in DWORD*/
#endif

int iBit = 0;
DWORD dwResult = 0;
while (lpszValue && *lpszValue && _tcschr(_T("01"), *lpszValue))
  {
  iBit = *lpszValue++ - _T('0');
  dwResult <<= 1;
  dwResult |= (iBit & 1);

  #ifdef _DEBUG
    #ifdef _WIN32
      iSizeOfDWORD --;
      if(iSizeOfDWORD < 0) /*Result is truncated, report warning only once     */
        _RPT0(_CRT_WARN,"BintoU()\tWarning: source string has more than 32 bits.");
    #endif
  #endif
  }

return dwResult; /*Result */
}
