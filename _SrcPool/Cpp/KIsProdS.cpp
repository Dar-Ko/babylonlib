/*$Workfile: H:\_SrcPool\Cpp\KIsProdS.cpp$: implementation file
  $Revision: 1.1 $ $Date: 2002/09/06 22:16:05 $
  $Author: ddarko $

  Verifies if specific product is present on system with Windows NT/2k
  Copyright: CommonSoft Inc.
  Jan 2000 Darko Kolakovic
 */

#include "StdAfx.h"
#ifndef _WINREG_
  #include <WinReg.h>
#endif
#include "KWinVers.inl" //IsWinNT()

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
//

//IsProductSuiteInstalled()-----------------------------------------------------------
/*Returns TRUE if specified product suite is available on system with WinNT / Win2k

  Note: compatibility with Windows 95/98 requires ANSI compliance.

  Note: Microsoft Windows specific (Win).
 */
BOOL IsProductSuiteInstalled(LPCTSTR szProductSuite //[in] suite name to search for
                            )
{
BOOL bRes = FALSE;

if (IsWinNT())
  {
  HKEY hKey;
  LPTSTR lpszProductSuites = NULL;
  DWORD dwType = 0;
  DWORD dwSize = 0;
  LPCTSTR szKey = _T("ProductSuite");

  if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,
               "SYSTEM\\CurrentControlSet\\Control\\ProductOptions",
               0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)
    {
      //Get size of required buffer
    if(RegQueryValueEx(hKey,szKey,NULL,&dwType,NULL,&dwSize) == ERROR_SUCCESS)
      {
      if (dwSize > 0) //Entry is not an empty string array
        {
        lpszProductSuites = (LPTSTR) new BYTE[dwSize];
        if (lpszProductSuites != NULL)
          {
          if(RegQueryValueEx(hKey,szKey,NULL,&dwType,
                    (LPBYTE)lpszProductSuites,&dwSize) == ERROR_SUCCESS)
            {
            if (dwType == REG_MULTI_SZ) //Entry is an array of null-terminated strings
              {
                //Search for suite name in array of strings
              LPTSTR lpszEntry = lpszProductSuites;
              do
                {
                if (lstrcmpi(lpszEntry,szProductSuite) == 0)
                  {
                  bRes = TRUE;
                  break;
                  }
                lpszEntry += (lstrlen(lpszEntry) + 1);
                }
              while (*lpszEntry != _T('\0'));
              }
            }
          delete [] lpszProductSuites; 
          }
        }
      }

    RegCloseKey(hKey);
    }
  }
return bRes;
}