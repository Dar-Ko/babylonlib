/*$Workfile: KStrLowC.c$: implementation file
  $Revision: 4$ $Date: 2/12/02 5:39:21 PM$
  $Author: Darko$

  Converts uppercase characters to lower case
  Feb 1989 Darko Kolakovic
*/

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include <TChar.h>  /*_totlower()*/

#ifdef _DEBUG
  static char THIS_FILE[] = __FILE__;
#endif
#ifndef NULL
  #define NULL 0x0
#endif

/*StrToLower()---------------------------------------------------------------*/
/*The function convert a string with characters in range from 0x0 to 0x7F
  to lowercase string if possible and appropriate.

  Returns a pointer to the converted string.

  Example:
    #include <StdLib.h>
    #include <TChar.h>
    #include "KStrings.h"
    void MyFunc()
      {
      LPTSTR szText = _T("TEXT");
      TCHAR* szResult= (TCHAR*)malloc (sizeof(TCHAR) * (_tcsclen(szText) +1));
      if (szResult  != NULL)
        {
        StrToLower(szResult, szText);
        wprintf(szResult);
        free(szResult);
        }
      }

 */
TCHAR* StrToLower(TCHAR* szDestination  /*result                                   */,
                  TCHAR* szSource       /*pointer to a null-terminated string      */
                 )
{
TCHAR* szSrc = szSource;
TCHAR* szRes = szDestination;
int iChar ;

if (szDestination == NULL || szSrc == NULL)
  szRes = NULL;
else
  while (*szDestination++ = 
            (TCHAR)( (iChar = *szSrc++) >= _T('A') && iChar  <= _T('Z') ? _totlower(iChar) : iChar) );
return szRes;
}
