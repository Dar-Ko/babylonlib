/*$Workfile: KGetPrSu.cpp$: implementation file
  $Revision: 1.3 $ $Date: 2003/01/28 05:36:18 $
  $Author: ddarko $

  Retrieve a list of installed products on WinNT
  Based on MSDN article: Detecting If Terminal Services is Installed Aug. 99
  Copyright: CommonSoft Inc.
  Jan 2k Darko Kolakovic
 */

#include "StdAfx.h"
#ifndef _WINREG_
  #include <WinReg.h>
#endif

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//GetProductSuite()------------------------------------------------------------
/*Obtains a list of installed products (like Terminal Service or BackOffice) on
  systems running windows NT or Windows 2000.
  Returns: TRUE if registry key with product options exist and TAB delimited text
  with installed products (or empty string if none of product suites are installed).
  Returns FALSE  and empty string if registry does not exist.

  Note: compatibility with Windows 95/98 requires ANSI compliance.

  Note: Microsoft Windows specific (Win).

  History: MSDN Aug. 99
 */
BOOL GetProductSuite(CString& strProductSuite //the list with installed products
                     )
{
HKEY hKey;
LPTSTR lpszProductSuites = NULL;
DWORD dwType = 0;
DWORD dwSize = 0;
LPCTSTR szKey = _T("ProductSuite");

strProductSuite.Empty();

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
          if (dwType == REG_MULTI_SZ) //Entry is an array of 
                                      //null-terminated strings
            {
              //Convert an array of null-terminated strings 
              //to TAB delimited text
            LPTSTR lpszEntry = lpszProductSuites;

            while (*lpszEntry != _T('\0'))  //Array is terminated by
              {                             //two null characters
              while (*lpszEntry != _T('\0'))
                lpszEntry++;
              *lpszEntry = _T('\t');
              lpszEntry++;
              }
              //Erase last TAB character
            lpszEntry --;
            *lpszEntry = _T('\0');

              //Result
            strProductSuite = lpszProductSuites;
            }
          }
        delete [] lpszProductSuites; 
        }
      }
    }

  RegCloseKey(hKey);
  return TRUE;
  }
return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  6    Biblioteka1.5         29/01/2002 10:21:06 PMDarko           Used lbraries
 *       notes 
 *  5    Biblioteka1.4         29/01/2002 2:40:08 PMDarko           Tag update
 *  4    Biblioteka1.3         11/08/2001 12:04:00 AMDarko           version tags
 *  3    Biblioteka1.2         11/07/2001 9:51:37 PMDarko           
 *  2    Biblioteka1.1         08/06/2001 10:50:47 PMDarko           VSS
 *  1    Biblioteka1.0         13/08/2000 2:56:33 PMDarko           
 * $
 *
 * Revision 0  1999/08/07 MSDN
 * Based on MSDN article: Detecting If Terminal Services is Installed Aug. 99
 *
 *****************************************************************************/
