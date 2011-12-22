/*$RCSfile: KIsProdS.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2011/12/22 15:53:40 $
  $Author: ddarko $

  Verifies if specific product is present on system with Windows NT/2k
  Copyright: CommonSoft Inc.
  Jan 2000 Darko Kolakovic
 */

#include "stdafx.h"
#ifndef _WINREG_
  #include <winreg.h>
#endif
#include "KWinVers.inl" //IsWinNT()

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
//

//----------------------------------------------------------------------------
/*Returns true if specified product suite is available on system with
   WinNT / Win2k.

  Note: compatibility with Windows 95/98 requires ANSI compliance.

  Note: Microsoft Windows specific (Win32).
 */
bool IsProductSuiteInstalled(LPCTSTR szProductSuite //[in] suite name to
                                                    //search for
                            )
{
bool bRes = false;

if (IsWinNT())
  {
  HKEY hKey;
  LPTSTR lpszProductSuites = NULL;
  DWORD dwType = 0;
  DWORD dwSize = 0;
  LPCTSTR szKey = _T("ProductSuite");

  if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,
               _T("SYSTEM\\CurrentControlSet\\Control\\ProductOptions"),
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
                  bRes = true;
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
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: KIsProdS.cpp,v $
 * Revision 1.1  2011/12/22 15:53:40  ddarko
 * Moved from local repository
 *
 *  6    Biblioteka1.5         28/04/2005 8:46:39 PMDarko           Comments
 *  5    Biblioteka1.4         29/01/2002 11:21:20 PMDarko           Used lbraries
 *       notes 
 *  4    Biblioteka1.3         29/01/2002 3:40:32 PMDarko           Tag update
 *  3    Biblioteka1.2         11/07/2001 10:51:46 PMDarko           
 *  2    Biblioteka1.1         08/06/2001 11:50:58 PMDarko           VSS
 *  1    Biblioteka1.0         13/08/2000 3:56:43 PMDarko           
 *****************************************************************************/
