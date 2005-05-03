/*$Workfile: KRegExt.cpp$: implementation file
  $Revision: 8$ $Date: 2004-10-01 22:35:15$
  $Author: Darko$

  Windows Registry Extended handler
  Copyright: CommonSoft Inc.
  Darko Kolakovic Nov 98
 */ 

#include "stdafx.h"
#ifndef _WINREG_
  #include <WinReg.h>
#endif
#include "KRegExt.h"  //CRegExt class

#ifdef _DEBUG
  #undef THIS_FILE
  static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

TCHAR CRegExt::m_szShellOpenCmd[] =  {_T("\\Shell\\Open\\Command")};

/////////////////////////////////////////////////////////////////////////////
// CRegExt

//::GetAssociatedExecutable()---------------------------------------------------
/*Returns the application name of the executable associated with the file type or
  empty string if application's name could not be found. This is static member.

  Example:
    TRACE1("Text files are associated with %s\n",
            CRegExt::GetAssociatedExecutable(".txt"));
    Output:
      Text files are associated with notepad.exe
 */
CString CRegExt::GetAssociatedExecutable(LPCTSTR strExtension //file name extension of the
                                                     //file types associated with an
                                                     //executable. String is not validated.
                                        )

{
CRegExt regkeyExe;
CString strResult;

if (regkeyExe.Open(HKEY_CLASSES_ROOT, strExtension))
  {
    //Find application ID
  if (regkeyExe.GetStringValue(strResult,NULL))
    {
    regkeyExe.Close();
    CString strOpenCommandID;
    strOpenCommandID = strResult + CRegExt::m_szShellOpenCmd;
      //Get application name
    if (regkeyExe.Open(HKEY_CLASSES_ROOT, strOpenCommandID))
      if (regkeyExe.GetStringValue(strResult,NULL))
        {
          //Cut command line arguments, if any
        strResult.TrimLeft(); //Strip off leading spaces
          /*Get everything before command line parameters
            Examples:
            "C:\Program Files\Internet Explorer\iexplore.exe" -nohome
            "C:\WINDOWS\hh.exe" "%1"
            C:\WinNT\notepad.exe "%1"
            "D:\CVS\bin\CVS.exe" -u "%1"
             TODO: "C:\Progra~1\Zip\Unzip %1"
            "C:\Program Files\Internet Search\WebQuery.exe"
           */

           //If long file name begins with quote, take first quoted string
        int iPos = 1;
        if (strResult[0] == _T('"'))
          {
          while ( (iPos < strResult.GetLength()) && (strResult[iPos] != _T('"')) )
            iPos++;
          strResult = strResult.Left(iPos+1);
          }
        else //8.3 file name or long file name without quotes
          {
          //Find first white space
          while ( (iPos < strResult.GetLength()) && (!_istspace(strResult[iPos])) )
            iPos++;
          strResult = strResult.Left(iPos);
          }
        }
    }
  }
return strResult;
}

//::OpenRemote()---------------------------------------------------------------
/*Function establishes a connection to a predefined registry handle on another
  computer. Currently, the following values can be used:
  HKEY_LOCAL_MACHINE and HKEY_USERS
 */
BOOL CRegExt::OpenRemote(HKEY hKey,       //= HKEY_LOCAL_MACHINE Identifies
                                          //any of the predefined reserved handle values
                         LPCTSTR szServerName//= NULL Remote Server (computer) name;
                                              //if NULL opens a registry on local
                                              //server. The string has the following form:
                                              // \\ComputerName


                        )
{
TRACE1("RegExt::OpenRemote(%s)\n",(szServerName== NULL)? GetComputerName() : szServerName);
if ( hKey == HKEY_CLASSES_ROOT || hKey == HKEY_CURRENT_USER )
  {
  if ( szServerName != NULL )
    {
     //Remote connection with HKEY_CLASSES_ROOT and HKEY_CURRENT_USERkeys are not allowed
    SetLastError(ERROR_INVALID_HANDLE);
    TRACE0("\tRemote connection is not allowed!\n");
    return FALSE;
    }
  else
    return Open(hKey); //Open local key with default security access
  }
else
  {
  if(!(hKey == HKEY_LOCAL_MACHINE     ||
         hKey == HKEY_PERFORMANCE_DATA  ||
         hKey == HKEY_USERS
         #if ( WINVER >= 0x400 )
                                        ||
           hKey == HKEY_CURRENT_CONFIG  ||
           hKey == HKEY_DYN_DATA
         #endif
         ))
    return FALSE;

  if (::RegConnectRegistry( (LPTSTR) szServerName, hKey, &m_hKey ) != ERROR_SUCCESS)
    return FALSE;
  }

return TRUE;
}

//::GetComputerName()----------------------------------------------------------
/*Retrieves the computer name of the current system from the registry. If an
  empty string is returned, to get extended error information, call GetLastError().
 */
CString CRegExt::GetComputerName()
{
CString strResult;
DWORD  nSize = MAX_COMPUTERNAME_LENGTH + 1;
LPTSTR szBuff = strResult.GetBuffer(nSize);
VERIFY(::GetComputerName(szBuff,&nSize));
strResult.ReleaseBuffer();
return strResult;
}

//::GetStringArrayValue()------------------------------------------------------
/*The function retrieves an array of strings from a specified registry.
 */
BOOL CRegExt::GetStringArrayValue(CStringArray& arrayResult,
                                  LPCTSTR lpszValueName //=NULL The key name of
                                                        //the string to be queried
                                  )

{
DWORD dwDataLength = 0;
DWORD dwType = 0; //Type is not required

//Note: The key identified by the m_hKey parameter must have been opened with
//KEY_QUERY_VALUE access (KEY_READ access includes KEY_QUERY_VALUE access).

  //Check if registry exist
LONG lRes = RegQueryValueEx(m_hKey,(LPTSTR)lpszValueName,
                            NULL, &dwType,
                            NULL, &dwDataLength);
  //Read the multiple string registry
if ((lRes == ERROR_SUCCESS) && (dwType == REG_MULTI_SZ))
  {
  BOOL bRes = FALSE;
  LPTSTR pData = (LPTSTR) new BYTE[dwDataLength];
  if (pData == NULL)
    return FALSE;
  if ((bRes = GetData((LPBYTE)pData,&dwDataLength,(LPTSTR)lpszValueName)) == TRUE)
    {
    LPTSTR szTmp = pData;
    arrayResult.RemoveAll();
    while(szTmp[ 0 ] != _T('\0'))
      {
      CString* pNewString = new CString;
      *pNewString = (LPCTSTR) szTmp;
      arrayResult.Add(*pNewString);
      szTmp += ( _tcslen( (LPCTSTR) szTmp ) + 1 );
      }
    }
  delete [] (LPBYTE)pData;
  return bRes;
  }

return FALSE;
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  8    Biblioteka1.7         2004-10-01 22:35:15  Darko           stdafx.h
 *  7    Biblioteka1.6         2003-11-03 13:21:01  Darko           Fixed long file
 *       names parsing in GetAssociatedExecutable()
 *  6    Biblioteka1.5         2003-09-22 22:26:36  Darko           formatting
 *  5    Biblioteka1.4         2002-01-25 16:57:44  Darko           Updated
 *       comments
 *  4    Biblioteka1.3         2001-08-17 00:37:51  Darko           Update
 *  3    Biblioteka1.2         2001-07-07 01:10:52  Darko           
 *  2    Biblioteka1.1         2001-06-08 23:51:37  Darko           VSS
 *  1    Biblioteka1.0         2000-08-13 15:57:23  Darko           
 * $
 *****************************************************************************/
