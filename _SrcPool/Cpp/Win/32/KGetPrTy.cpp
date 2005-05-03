/*$Workfile: KGetPrTy.cpp$: implementation file
  $Revision: 8$ $Date: 2004-10-01 22:34:59$
  $Author: Darko$

  Retrieve a type of WinNT platform
  Copyright: CommonSoft Inc.
  Jan 97 Darko Kolakovic
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#ifndef _WINNT_
  #include <winnt.h>  //ACCESS_MASK typedef
#endif
#ifndef _WINREG_
  #include <winreg.h>
#endif
#include "KWinVers.h" //ENV_WINSERVER

/* link with required Advapi32.lib advanced API library */
#pragma comment (lib, "Advapi32")

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//GetProductType()------------------------------------------------------------
/*Obtains additional information about the WinNT or Win2k system.

  Returns: -1 if registry key with product type exist or one of following values:

    ENV_WINWRKSTN for workstations,
    ENV_WINSERVER for servers
    ENV_WINSERADV for advanced servers.


  Note: compatibility with Windows 95/98 requires ANSI compliance.

  Note: Microsoft Windows specific (Win).
 */
int GetProductType()
{
HKEY hKey;
TCHAR szProductType[32];
DWORD dwType = 0;
DWORD dwSize = 32;
int iRes = -1;
LPCTSTR szKey = _T("ProductType");

if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,
             _T("SYSTEM\\CurrentControlSet\\Control\\ProductOptions"),
             0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)
  {
  #ifdef _DEBUG
    UINT nErr;
    if((nErr = RegQueryValueEx(hKey,szKey,NULL,&dwType,(LPBYTE)szProductType,&dwSize)) != ERROR_SUCCESS)
      TRACE1("GetProductType(): RegQueryValueEx returned error %u\n", nErr);
    else
  #else
    if(RegQueryValueEx(hKey,szKey,NULL,&dwType,(LPBYTE)szProductType,&dwSize) == ERROR_SUCCESS)
  #endif
      if (dwType == REG_SZ)
        {
        if (lstrcmpi(_T("WINNT"), szProductType) == 0)
          iRes = ENV_WINWRKSTN;
        if (lstrcmpi(_T("SERVERNT"), szProductType) == 0 )
          iRes = ENV_WINSERVER;
        if (lstrcmpi(_T("LANMANNT"), szProductType) == 0 )
          iRes = ENV_WINSERADV;
        }
  RegCloseKey(hKey);
  }

return iRes;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  7    Biblioteka1.6         2003-09-05 13:14:57  Darko           Unicode
 *  6    Biblioteka1.5         2002-01-29 23:21:09  Darko           Used lbraries
 *       notes
 *  5    Biblioteka1.4         2002-01-29 15:40:13  Darko           Tag update
 *  4    Biblioteka1.3         2001-08-19 23:53:57  Darko           Butyfier
 *  3    Biblioteka1.2         2001-07-11 22:51:40  Darko
 *  2    Biblioteka1.1         2001-06-08 23:50:49  Darko           VSS
 *  1    Biblioteka1.0         2000-08-13 15:56:34  Darko
 * $
 *****************************************************************************/
