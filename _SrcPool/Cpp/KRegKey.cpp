/*$Workfile: KRegKey.cpp$: implementation file
  $Revision: 1.3 $ $Date: 2003/01/28 05:37:44 $
  $Author: ddarko $

  Copyright: CommonSoft Inc.
  Darko Kolakovic
  May 94 (16b)
  Nov 98 (NT ver)
 */ 

#ifdef _WIN32
///////////////////////////////////////////////////////////////////////////////
//Win 32b

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include <AfxWin.h>
#ifndef __AFXWIN_H__
  #pragma message (__FILE__ " #include <Windows.h>")
  #include <Windows.h>
#endif
#pragma hdrstop
#include "KRegKey.h"  //CRegistryKey class

#ifdef _DEBUG
  #pragma message (__FILE__ " _DEBUG")
  #undef THIS_FILE
  #ifdef __AFXWIN_H__
    static char BASED_CODE THIS_FILE[] = __FILE__;
  #else
    #include <Assert.h>
    #ifndef ASSERT
      #define ASSERT(expression) assert(expression)
    #endif
  #endif
#else
  #ifndef __AFXWIN_H__
    #pragma message (__FILE__ " NODEBUG")
    #ifndef ASSERT
      #define ASSERT(e)  ((void)0)
    #endif
  #endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegistryKey
//
// Predefined Value Types        VALUE   Description (WinNT.h)
// REG_NONE                        0  No value type
// REG_SZ                          1  Unicode nul terminated string
// REG_EXPAND_SZ                   2  Unicode nul terminated string(with environment variable references)
// REG_BINARY                      3  Free form binary
// REG_DWORD                       4  32-bit number
// REG_DWORD_LITTLE_ENDIAN         4  32-bit number (same as REG_DWORD)
// REG_DWORD_BIG_ENDIAN            5  32-bit number
// REG_LINK                        6  Symbolic Link (unicode)
// REG_MULTI_SZ                    7  Multiple Unicode strings
// REG_RESOURCE_LIST               8  Resource list in the resource map
// REG_FULL_RESOURCE_DESCRIPTOR    9  Resource list in the hardware description
// REG_RESOURCE_REQUIREMENTS_LIST  10
//
//
// Registry Specific Access Rights         Description (REGSAM WinNT.h)
// KEY_ALL_ACCESS                   Combination of KEY_QUERY_VALUE, KEY_ENUMERATE_SUB_KEYS, KEY_NOTIFY, KEY_CREATE_SUB_KEY, KEY_CREATE_LINK, and KEY_SET_VALUE access.
// KEY_CREATE_LINK              32  Permission to create a symbolic link.
// KEY_CREATE_SUB_KEY            4  Permission to create subkeys.
// KEY_ENUMERATE_SUB_KEYS        8  Permission to enumerate subkeys.
// KEY_EXECUTE                      Permission for read access.
// KEY_NOTIFY                   16  Permission for change notification.
// KEY_QUERY_VALUE               1  Permission to query subkey data.
// KEY_READ                         Combination of KEY_QUERY_VALUE, KEY_ENUMERATE_SUB_KEYS, and KEY_NOTIFY access.
// KEY_SET_VALUE                 2  Permission to set subkey data.
// KEY_WRITE                        Combination of KEY_SET_VALUE and KEY_CREATE_SUB_KEY access.


//::Close()--------------------------------------------------------------------
/*The function releases the handle of the specified key.
 */
void CRegistryKey::Close()
{
if (m_hKey != NULL)
  {
  LONG lRes = RegCloseKey(m_hKey);
  ASSERT(lRes == ERROR_SUCCESS);
  m_hKey = NULL;
  }
}


//::Create()-------------------------------------------------------------------
/*The function creates the specified key and if the key already exists in the
  registry opens it.
  Predefined reserved key handle values are:

    HKEY_CLASSES_ROOT
    HKEY_CURRENT_USER
    HKEY_LOCAL_MACHINE
    HKEY_USERS
 */
BOOL CRegistryKey::Create(HKEY hKey,        //Identifies a currently open key
                                            //or any of the predefined
                                            //reserved handle values
                        LPCTSTR lpszKeyName,//name of subkey to open or NULL
                        REGSAM  samDesired  //desired security access
                         )
{
ASSERT(hKey != NULL);
DWORD dwDisposition; //a variable that receives one of the following disposition values:
                     //REG_CREATED_NEW_KEY     The key did not exist and was created.
                     //REG_OPENED_EXISTING_KEY The key existed and was simply opened
                     //                        without being changed.

return (RegCreateKeyEx(hKey,        // handle of an open key
                       lpszKeyName, // address of subkey name
                       0,           // reserved
                       REG_NONE,    // address of class string
                       REG_OPTION_NON_VOLATILE, // special options flag
                       samDesired,              // desired security access
                       NULL,                    // address of key security structure
                       &m_hKey,	        // address of buffer for opened handle
                       &dwDisposition   // address of disposition value buffer
        ) == ERROR_SUCCESS);
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

  Registry Specific Access Rights         Description (REGSAM WinNT.h)
    KEY_ALL_ACCESS                     Combination of KEY_QUERY_VALUE, KEY_ENUMERATE_SUB_KEYS,
                                       KEY_NOTIFY, KEY_CREATE_SUB_KEY, KEY_CREATE_LINK,
                                       and KEY_SET_VALUE access.
    KEY_CREATE_LINK                32  Permission to create a symbolic link.
    KEY_CREATE_SUB_KEY              4  Permission to create subkeys.
    KEY_ENUMERATE_SUB_KEYS          8  Permission to enumerate subkeys.
    KEY_EXECUTE                        Permission for read access.
    KEY_NOTIFY                     16  Permission for change notification.
    KEY_QUERY_VALUE                 1  Permission to query subkey data.
    KEY_READ                           Combination of KEY_QUERY_VALUE, KEY_ENUMERATE_SUB_KEYS,
                                       and KEY_NOTIFY access.
    KEY_SET_VALUE                   2  Permission to set subkey data.
    KEY_WRITE                          Combination of KEY_SET_VALUE and KEY_CREATE_SUB_KEY access.

  Example:
    CRegistryKey regKey;
    if (regKey.Open(HKEY_LOCAL_MACHINE,_T("SYSTEM\\CurrentControlSet\\Services\\EventLog\\Application"),
                      KEY_WRITE))
      {
      TRACE0(_T("Succes\n"));
      }


 */
BOOL CRegistryKey::Open(HKEY hKey,          //Identifies a key to open
                                            //or any of the predefined
                                            //reserved handle values
                        LPCTSTR lpszKeyName, //name of subkey to open or NULL.
                        REGSAM  samDesired   //desired security access

                        )
{
ASSERT(hKey != NULL);
return (RegOpenKeyEx(hKey, lpszKeyName, 0, samDesired, &m_hKey) == ERROR_SUCCESS);
}

//::SetStringValue()-----------------------------------------------------------
/*The function associates a text string with a specified key. This value must
  be a text string and cannot have a name.
 */
BOOL CRegistryKey::SetStringValue(LPCTSTR lpszValue,
                                  LPCTSTR lpszValueName //NULL
                                  )
{
ASSERT(m_hKey != NULL);
return (RegSetValueEx(m_hKey, lpszValueName, NULL, REG_SZ,
                    (BYTE * const)lpszValue,
                      (lstrlen(lpszValue)+1)*sizeof(TCHAR)) == ERROR_SUCCESS);
//Note: For data types REG_SZ, REG_EXPAND_SZ, or REG_MULTI_SZ, cbData must include
//the size of the terminating null character.
}

//::GetStringValue()-----------------------------------------------------------
#ifdef __AFXWIN_H__         //Include MFC library
/*
 */
BOOL CRegistryKey::GetStringValue(CString& strResult,
                                  LPCTSTR lpszValueName //=NULL The key name of
                                                        //the string to be queried
                                  )
{
ASSERT(m_hKey != NULL);
strResult.Empty();
DWORD dwCount = 0;
DWORD dwType = 0; //Type is not required

//Note: The key identified by the m_hKey parameter must have been opened with
//KEY_QUERY_VALUE access (KEY_READ access includes KEY_QUERY_VALUE access).

  //Check if registry exist
LONG lRes = RegQueryValueEx(m_hKey,(LPTSTR)lpszValueName,
                            NULL, &dwType,
                            NULL, &dwCount);
  //Read the string registry
if (lRes == ERROR_SUCCESS)
  {
  ASSERT(dwType == REG_SZ); //Validate if registry is a string

  LPTSTR lpsz = strResult.GetBufferSetLength(dwCount);
  lRes = RegQueryValueEx(m_hKey, (LPTSTR)lpszValueName, NULL,
                        &dwType, (BYTE*)lpsz, &dwCount);
  ASSERT(lRes == ERROR_SUCCESS);
  strResult.ReleaseBuffer();
  return TRUE;
  }
return FALSE;
}

#else
//::GetStringValue()-----------------------------------------------------------
/*
 */
BOOL CRegistryKey::GetStringValue(LPTSTR szResult,
                                  DWORD* pnBufferSize, //Points to a variable
                                  //that specifies the size, in bytes, of the buffer
                                  //pointed to by the szResult parameter. When
                                  //the function returns, this variable contains
                                  //the size of the data copied to lpData.
                                  LPCTSTR lpszValueName// = NULL
                                  )
{
ASSERT(m_hKey != NULL);
DWORD dwCount = 0;
DWORD dwType;
  //Check if registry exist
LONG lRes = RegQueryValueEx(m_hKey,(LPTSTR)lpszValueName,
                           NULL, &dwType,
                           NULL, &dwCount);
if (szResult == NULL)
  {
  *pnBufferSize = dwCount; //Return real size
  return TRUE;
  }
  //Read the string registry
if (lRes == ERROR_SUCCESS)
  {
  ASSERT(dwType == REG_SZ); //Validate if registry is a string
  dwCount = *pnBufferSize
	lRes = RegQueryValueEx(m_hKey, (LPTSTR)lpszValueName,
                        NULL, &dwType,
                        szResult, pnBufferSize);
	ASSERT(lRes == ERROR_SUCCESS);
  *pnBufferSize = dwCount; //Return real string length
	return TRUE;
  }

*pnBufferSize = 0;
return FALSE;
}
#endif  //__AFXWIN_H__

//::GetData()------------------------------------------------------------------
/*The function retrieves the data for a specified value name
  associated with an open registry key. If the buffer specified by lpData
  parameter is not large enough to hold the data, the function returns
  the value ERROR_MORE_DATA.

  Predefined Value Types        VALUE   Description (WinNT.h)
  REG_NONE                        0  No value type
  REG_SZ                          1  Unicode nul terminated string
  REG_EXPAND_SZ                   2  Unicode nul terminated string(with environment variable references)
  REG_BINARY                      3  Free form binary
  REG_DWORD                       4  32-bit number
  REG_DWORD_LITTLE_ENDIAN         4  32-bit number (same as REG_DWORD)
  REG_DWORD_BIG_ENDIAN            5  32-bit number
  REG_LINK                        6  Symbolic Link (unicode)
  REG_MULTI_SZ                    7  Multiple Unicode strings
  REG_RESOURCE_LIST               8  Resource list in the resource map
  REG_FULL_RESOURCE_DESCRIPTOR    9  Resource list in the hardware description
  REG_RESOURCE_REQUIREMENTS_LIST  10

  Example:
    {
    CRegistryKey regKey;
    if (regKey.Open(HKEY_LOCAL_MACHINE,
                    _T("HKEY_CURRENT_USER\\Software\\MyCopmany\\Application"),
                    KEY_READ))
      {
      long lSize = MAX_PATH;
      TCHAR data[MAX_PATH];
      regKey.GetData(data, &lSize);
      regKey.Close();
      }
 */
BOOL CRegistryKey::GetData(LPBYTE lpData, //points to a buffer that receives
                                   //the value's data. This parameter can be
                                   //NULL if the data is not required.
                           DWORD* pnBufferSize, //points to a variable
                                   //that specifies the size, in bytes, of the buffer
                                  //pointed to by the szResult parameter. When
                                  //the function returns, this variable contains
                                  //the size of the data in the registry.
                           LPCTSTR lpszValueName// = NULL
                           )
{
ASSERT(m_hKey != NULL);
DWORD dwCount = 0;
DWORD dwType;
  //Check if registry exist
LONG lRes = RegQueryValueEx(m_hKey,(LPTSTR)lpszValueName,
                           NULL, &dwType,
                           NULL, &dwCount);
if (lpData == NULL)
  {
  *pnBufferSize = dwCount; //Return real size
  return TRUE;
  }
  //Read the string registry
if (lRes == ERROR_SUCCESS)
  {
  dwCount = *pnBufferSize;
	lRes = RegQueryValueEx(m_hKey, (LPTSTR)lpszValueName,
                        NULL, &dwType,
                        lpData, pnBufferSize);
	ASSERT(lRes == ERROR_SUCCESS);
  *pnBufferSize = dwCount; //Return real size
	return TRUE;
  }

*pnBufferSize = 0;
return FALSE;
}

//::GetSetDataData()------------------------------------------------------------------
/*Function stores data in the value field of an open registry key.
  Value lengths are limited by available memory. Long values (more than 2048 bytes)
  should be stored as files with the filenames stored in the registry. This helps
  the registry perform efficiently.  If a value with lpszValueName name is not already
  present in the key, the function adds it to the key.
 */
BOOL CRegistryKey::SetData(LPBYTE lpData, //points to a buffer that receives
                                   //the value's data. This parameter can be
                                   //NULL if the data is not required.
                           DWORD nBufferSize, //points to a variable
                                   //that specifies the size, in bytes, of the buffer
                                  //pointed to by the szResult parameter. When
                                  //the function returns, this variable contains
                                  //the size of the data in the registry.
                           LPCTSTR lpszValueName// = NULL
                           )
{
//TODO: test,improve dwType
ASSERT(m_hKey != NULL);
DWORD dwType = REG_NONE;
LONG lRes;
lRes = ::RegSetValueEx(m_hKey,lpszValueName,
                      0, dwType,
                      lpData, nBufferSize);
if(lRes == ERROR_SUCCESS)
  return TRUE;


return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
#endif  //_WIN32

///////////////////////////////////////////////////////////////////////////////

//operator<<()-----------------------------------------------------------------
/*Translates predefined HKEY to readable text.

  Note: uses Microsoft Fundation Library (MFC).
 */
CString& operator<<(CString& strDestination, CRegistryKey& regSource)
{
if ( regSource.m_hKey == HKEY_LOCAL_MACHINE )
  strDestination += _T( "HKEY_LOCAL_MACHINE" );
else if ( regSource.m_hKey == HKEY_CLASSES_ROOT )
  strDestination += _T( "HKEY_CLASSES_ROOT" );
else if ( regSource.m_hKey == HKEY_USERS )
  strDestination += _T( "HKEY_USERS" );
else if ( regSource.m_hKey == HKEY_CURRENT_USER )
  strDestination += _T( "HKEY_CURRENT_USER" );
else if ( regSource.m_hKey == HKEY_PERFORMANCE_DATA )
  strDestination += _T( "HKEY_PERFORMANCE_DATA" );

#if ( WINVER >= 0x400 )
  else if ( regSource.m_hKey == HKEY_CURRENT_CONFIG )
    strDestination += _T( "HKEY_CURRENT_CONFIG" );
  else if ( regSource.m_hKey == HKEY_DYN_DATA )
    strDestination += _T( "HKEY_DYN_DATA" );
#endif

#ifdef _DEBUG
  TRACE0("HKEY is not one of predefined keys!\n");
#endif

return strDestination;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  4    Biblioteka1.3         29/01/2002 10:21:42 PMDarko           Used lbraries
 *       notes 
 *  3    Biblioteka1.2         25/01/2002 3:57:49 PMDarko           Updated
 *       comments
 *  2    Biblioteka1.1         16/08/2001 11:37:56 PMDarko           Update
 *  1    Biblioteka1.0         07/07/2001 12:13:45 AMDarko           
 * $
 *****************************************************************************/

