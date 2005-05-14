/*$Workfile: KRegK16.cpp$: implementation file
  $Revision: 6$ $Date: 2005-04-26 11:37:40$
  $Author: Darko Kolakovic$

  Registry Key helper
  Copyright: CommonSoft Inc
  May 94 (16b) Darko Kolakovic
  Nov 98 (NT ver) D.K.
*/
// Group=Windows

#include "AfxWin.h"
#ifndef __AFXWIN_H__
  #include <Windows.h>
  #ifdef _DEBUG
    #include <Assert.h>
    #define ASSERT(expression) assert(expression)
  #else
    #define ASSERT(e)  ((void)0)
  #endif
#endif
#include <WinReg.h>
#include "KRegKey.h"  //CRegistryKey class

#ifdef _DEBUG
  #undef THIS_FILE
  #ifdef __AFXWIN_H__
    static char BASED_CODE THIS_FILE[] = __FILE__;
  #endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegistryKey

void CRegistryKey::Close()
{
if (m_hKey != NULL)
  {
  LONG lRes = RegCloseKey(m_hKey);
  ASSERT(lRes == ERROR_SUCCESS);
  m_hKey = NULL;
  }
}

#ifndef _WIN32
///////////////////////////////////////////////////////////////////////////////
//Win 16b

//::Create()-------------------------------------------------------------------
/*The function creates the specified key and if the key already exists in the
  registry opens it.
  Predefined reserved key handle values are:

    HKEY_CLASSES_ROOT
    HKEY_CURRENT_USER
    HKEY_LOCAL_MACHINE
    HKEY_USERS

  Note: Microsoft Windows 16b specific (Win16).
 */
BOOL CRegistryKey::Create(HKEY hKey,        //Identifies a currently open key
                                            //or any of the predefined
                                            //reserved handle values
                        LPCTSTR lpszKeyName //name of subkey to open or NULL
                         )
{
ASSERT(hKey != NULL);
return (RegCreateKey(hKey, lpszKeyName, &m_hKey) == ERROR_SUCCESS);
}

//::Open()----------------------------------------------------------------------
/*The function opens the specified key. If lpszKeyName parameter is NULL or a
  pointer to an empty string, the function initializes m_hKey member to the same
  handle that was passed in.
  Predefined reserved key handle values are:

    HKEY_CLASSES_ROOT
    HKEY_CURRENT_USER
    HKEY_LOCAL_MACHINE
    HKEY_USERS

  Note: Microsoft Windows 16b specific (Win16).
 */
BOOL CRegistryKey::Open(HKEY hKey,          //Identifies a currently open key
                                            //or any of the predefined
                                            //reserved handle values
                        LPCTSTR lpszKeyName //name of subkey to open or NULL.
                       )
{
ASSERT(hKey != NULL);
return (RegOpenKey(hKey, lpszKeyName, &m_hKey) == ERROR_SUCCESS);
}

//::SetStringValue()-----------------------------------------------------------
/*The function associates a text string with a specified key. This value must
  be a text string and cannot have a name.

  Note: Microsoft Windows 16b specific (Win16).
 */
BOOL CRegistryKey::SetStringValue(LPCTSTR lpszValue,
                                  LPCTSTR lpszValueName //NULL
                                  )
{
ASSERT(m_hKey != NULL);
return (RegSetValue(m_hKey, lpszValueName, REG_SZ,
                      lpszValue,
                      _tcslen(lpszValue)) == ERROR_SUCCESS);
}

//::GetStringValue()-----------------------------------------------------------
#ifdef __AFXWIN_H__         //Include MFC library
/*The function retrieves the value associated with the unnamed value for
  a specified key in the registry.

  Note: uses Microsoft Foundation Library (MFC).
        Microsoft Windows 16b specific (Win16).
 */
BOOL CRegistryKey::GetStringValue(CString& strResult,
                                  LPCTSTR lpszValueName //=NULL The key name of
                                                        //the string to be queried
                                  )
{
ASSERT(m_hKey != NULL);
strResult.Empty();
DWORD dwCount = 0;
  //Check if registry exist
LONG lRes = RegQueryValue(m_hKey,(LPTSTR)lpszValueName,
                          NULL, &dwCount);
  //Read the string registry
if (lRes == ERROR_SUCCESS)
  {
  ASSERT(dwType == REG_SZ); //Validate if registry is a string

  LPTSTR lpsz = strResult.GetBufferSetLength(dwCount);
  lRes = RegQueryValue(m_hKey, (LPTSTR)lpszValueName,
                       lpsz, &dwCount);
  ASSERT(lRes == ERROR_SUCCESS);
  strResult.ReleaseBuffer();
  return TRUE;
  }
return FALSE;
}

#else //__AFXWIN_H__
//::GetStringValue()-----------------------------------------------------------
/*
  Note: Microsoft Windows 16b specific (Win16).
 */
BOOL CRegistryKey::GetStringValue(LPTSTR szResult,
                                  size_t* pnBufferSize, //buffer size
                                  LPCTSTR lpszValueName// = NULL
                                  )
{
ASSERT(m_hKey != NULL);
DWORD dwCount = 0;
  //Check if registry exist
LONG lRes = RegQueryValue(m_hKey,(LPTSTR)lpszValueName,
                          NULL, &dwCount);
  //Read the string registry
if (lRes == ERROR_SUCCESS)
  {
  ASSERT(dwType == REG_SZ); //Validate if registry is a string
  dwCount = *pnBufferSize
  lRes = RegQueryValue(m_hKey, (LPTSTR)lpszValueName,
                       szResult, pnBufferSize);
  ASSERT(lRes == ERROR_SUCCESS);
  *pnBufferSize = dwCount; //Return real string length
  return TRUE;
  }

*pnBufferSize = 0;
return FALSE;
}
#endif  //__AFXWIN_H__

///////////////////////////////////////////////////////////////////////////////
#endif  //~_WIN32

