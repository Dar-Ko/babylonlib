/*$Workfile: KStrLowC.c$: implementation file
  $Revision: 8$ $Date: 2004-11-12 16:55:13$
  $Author: Darko Kolakovic$

  Converts uppercase characters to lower case
  Feb 1989 Darko Kolakovic
*/

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include <tchar.h>  /*_totlower()*/

  /*Microsoft Visual C++.NET 2003 v7.1 compiler                              */
#if _MSC_VER == 1310
  #if !defined _MBCS && !defined _UNICODE
    #include <stdlib.h> /*tolower()*/
  #endif
#endif

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
  while (*(_tcsinc(szDestination) =
            (TCHAR)( (iChar = *(_tcsinc(szSrc)) >= _T('A') && iChar  <= _T('Z') ?
                                          _totlower((TCHAR)iChar) : iChar) );
return szRes;
}

/*****************************************************************************
 * $Log:
 *  7    Biblioteka1.6         2004-06-01 17:53:25  Darko           time sync
 *  6    Biblioteka1.5         2003-08-26 01:41:38  Darko           SBCS text map
 *       resolved
 *  5    Biblioteka1.4         2003-08-14 05:04:39  Darko           Unicode
 *  4    Biblioteka1.3         2002-02-12 17:39:21  Darko           Replaced
 *       tchar.h with KTChar.h
 *  3    Biblioteka1.2         2001-07-11 22:52:53  Darko
 *  2    Biblioteka1.1         2001-06-08 23:51:57  Darko           VSS
 *  1    Biblioteka1.0         2000-08-13 16:00:03  Darko
 * $
 *****************************************************************************/
