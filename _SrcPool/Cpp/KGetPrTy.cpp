/*$Workfile: KGetPrTy.cpp$: implementation file
  $Revision: 1.2 $ $Date: 2002/09/10 15:22:21 $
  $Author: ddarko $

  Retrieve a type of WinNT platform
  Copyright: CommonSoft Inc.
  Jan 97 Darko Kolakovic
 */

#include "StdAfx.h"
#ifndef _WINREG_
  #include <WinReg.h>
#endif
#include "KWinVers.h" //ENV_WINSERVER

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
             "SYSTEM\\CurrentControlSet\\Control\\ProductOptions",
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
        if (lstrcmpi("WINNT", szProductType) == 0)
          iRes = ENV_WINWRKSTN;
        if (lstrcmpi("SERVERNT", szProductType) == 0 )
          iRes = ENV_WINSERVER;
        if (lstrcmpi("LANMANNT", szProductType) == 0 )
          iRes = ENV_WINSERADV;
        }
  RegCloseKey(hKey);
  }

return iRes;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  6    Biblioteka1.5         1/29/02 11:21:09 PM  Darko           Used lbraries
 *       notes 
 *  5    Biblioteka1.4         1/29/02 3:40:13 PM   Darko           Tag update
 *  4    Biblioteka1.3         8/19/01 11:53:57 PM  Darko           Butyfier
 *  3    Biblioteka1.2         7/11/01 10:51:40 PM  Darko           
 *  2    Biblioteka1.1         6/8/01 11:50:49 PM   Darko           VSS
 *  1    Biblioteka1.0         8/13/00 3:56:34 PM   Darko           
 * $
 *****************************************************************************/
