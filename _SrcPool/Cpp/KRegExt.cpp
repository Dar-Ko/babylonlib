/*$Workfile: KRegExt.cpp$: implementation file
  $Revision: 1.1 $ $Date: 2002/09/06 22:19:04 $
  $Author: ddarko $

  Windows Registry Extended handler
  Copyright: CommonSoft Inc.
  Darko Kolakovic Nov 98
 */ 

#include "StdAfx.h"
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
          //Find first white space
        int iPos = 1;
        while ( (iPos < strResult.GetLength()) && (!_istspace(strResult[iPos])) )
          iPos++;
        strResult = strResult.Left(iPos);
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
 *  5    Biblioteka1.4         1/25/02 3:57:44 PM   Darko           Updated
 *       comments
 *  4    Biblioteka1.3         8/16/01 11:37:51 PM  Darko           Update
 *  3    Biblioteka1.2         7/7/01 12:10:52 AM   Darko           
 *  2    Biblioteka1.1         6/8/01 10:51:37 PM   Darko           VSS
 *  1    Biblioteka1.0         8/13/00 2:57:23 PM   Darko           
 * $
 *****************************************************************************/
