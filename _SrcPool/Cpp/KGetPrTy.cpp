/*$Workfile: KGetPrTy.cpp$: implementation file
  $Revision: 1.3 $ $Date: 2003/01/28 05:36:18 $
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
 *  6    Biblioteka1.5         29/01/2002 10:21:09 PMDarko           Used lbraries
 *       notes 
 *  5    Biblioteka1.4         29/01/2002 2:40:13 PMDarko           Tag update
 *  4    Biblioteka1.3         19/08/2001 10:53:57 PMDarko           Butyfier
 *  3    Biblioteka1.2         11/07/2001 9:51:40 PMDarko           
 *  2    Biblioteka1.1         08/06/2001 10:50:49 PMDarko           VSS
 *  1    Biblioteka1.0         13/08/2000 2:56:34 PMDarko           
 * $
 *****************************************************************************/
