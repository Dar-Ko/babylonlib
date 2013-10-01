/*$RCSfile: KRegKey.cpp$: implementation file
  $Revision: 14$ $Date: 2007-05-10 16:56:29$
  $Author: Darko Kolakovic$

  Copyright: CommonSoft Inc.
  Darko Kolakovic
  May 94 (16b)
  Nov 98 (NT ver)
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

//#include "stdafx.h"

///////////////////////////////////////////////////////////////////////////////
//Win 32b
#ifdef _WIN32

#ifndef __AFXWIN_H__
  #pragma message (__FILE__ " #include <windows.h>")
  #include <windows.h>
#endif
#pragma hdrstop
#include "KRegKey.h"  //CRegistryKey class

#ifdef _DEBUG
  #pragma message (__FILE__ " _DEBUG")
  #undef THIS_FILE
  #ifdef __AFXWIN_H__
    static char BASED_CODE THIS_FILE[] = __FILE__;
  #else
    #include <assert.h>
    #ifndef ASSERT
      #define ASSERT(expression) assert(expression)
    #endif
  #endif
#else
  #ifndef __AFXWIN_H__
    #pragma message (__FILE__ " NODEBUG")
    #ifndef ASSERT
      #if _MSC_VER < 1300
        #define ASSERT(e)  ((void)0)
      #else
        #define ASSERT(e)  __noop
      #endif
    #endif
  #endif
#endif

const int MAX_KEY_LENGTH = 256; //Size of temporary buffer

/////////////////////////////////////////////////////////////////////////////
/* CRegistryKey
 */


//::Create()-------------------------------------------------------------------
/*The function creates the specified key and if the key already exists in the
  registry opens it.
  Predefined reserved key handle values are:

    HKEY_CLASSES_ROOT
    HKEY_CURRENT_USER
    HKEY_LOCAL_MACHINE
    HKEY_USERS
    HKEY_PERFORMANCE_DATA
    HKEY_PERFORMANCE_TEXT
    HKEY_PERFORMANCE_NLSTEXT
    HKEY_CURRENT_CONFIG
    HKEY_DYN_DATA

  The subkey specified must be a subkey of the key identified by the hKey
  parameter and it can be up to 32 levels deep in the registry tree.
 */
BOOL CRegistryKey::Create(HKEY hKey,        //Identifies a currently open key
                                            //or any of the predefined
                                            //reserved handle values
                        LPCTSTR lpszKeyName,//name of subkey to open and cannot
                                            //be NULL.
                        REGSAM  samDesired  //desired security access
                         )
{
ASSERT(hKey != NULL);
if( (lpszKeyName == NULL) || (lpszKeyName[0] == _T('\0')) )
  return FALSE; //Subkey parameter cannot be NULL.

DWORD dwDisposition; //a variable that receives one of the following disposition values:
                     //REG_CREATED_NEW_KEY     The key did not exist and was created.
                     //REG_OPENED_EXISTING_KEY The key existed and was simply opened
                     //                        without being changed.

return (RegCreateKeyEx(hKey,        // handle of an open key
                       lpszKeyName, // address of subkey name
                       _RESERVED_FOR_FUTURE_USE, // reserved
                       REG_NONE,    // address of class string
                       REG_OPTION_NON_VOLATILE, // special options flag
                       samDesired,              // desired security access
                       NULL,                    // address of key security structure
                       &m_hKey,          // address of buffer for opened handle
                       &dwDisposition   // address of disposition value buffer
        ) == ERROR_SUCCESS);
}

//::Open()----------------------------------------------------------------------
/*The function opens the specified key. If lpszKeyName parameter is NULL or a
  pointer to an empty string, the function initializes m_hKey member to the same
  handle that was passed in.
  If user is a restricted access user, opening a key will fail. 
  A single registry key can be opened only 65534 times; after that function fails.

  Predefined reserved key handle values are:

    HKEY_CLASSES_ROOT
    HKEY_CURRENT_USER
    HKEY_LOCAL_MACHINE
    HKEY_USERS
    HKEY_PERFORMANCE_DATA   (Windows NT/2000)
    HKEY_PERFORMANCE_TEXT
    HKEY_PERFORMANCE_NLSTEXT
    HKEY_CURRENT_CONFIG
    HKEY_DYN_DATA           (Windows 95/98)

  Registry Specific Access Rights         Description (REGSAM WinNT.h)
    KEY_ALL_ACCESS                     Combination of KEY_QUERY_VALUE,
                                       KEY_ENUMERATE_SUB_KEYS,
                                       KEY_NOTIFY, KEY_CREATE_SUB_KEY,
                                       KEY_CREATE_LINK,
                                       and KEY_SET_VALUE access.
    KEY_CREATE_LINK                32  Permission to create a symbolic link.
    KEY_CREATE_SUB_KEY              4  Permission to create subkeys.
    KEY_ENUMERATE_SUB_KEYS          8  Permission to enumerate subkeys.
    KEY_EXECUTE                        Permission for read access.
    KEY_NOTIFY                     16  Permission for change notification.
    KEY_QUERY_VALUE                 1  Permission to query subkey data.
    KEY_READ                           Combination of KEY_QUERY_VALUE,
                                       KEY_ENUMERATE_SUB_KEYS,
                                       and KEY_NOTIFY access.
    KEY_SET_VALUE                   2  Permission to set subkey data.
    KEY_WRITE                          Combination of KEY_SET_VALUE and
                                       KEY_CREATE_SUB_KEY access.

  Example:
    CRegistryKey regKey;
    if (regKey.Open(HKEY_LOCAL_MACHINE,
                    _T("SYSTEM\\CurrentControlSet\\Services\\EventLog\\Application"),
                    KEY_WRITE))
     {
      TRACE0(_T("Succes\n"));
      }

 */
BOOL CRegistryKey::Open(HKEY hKey,          //handle to an open registry key
                                            //or any of the predefined
                                            //reserved handle values
                        LPCTSTR lpszKeyName, //name of subkey to open or NULL.
                        //If this parameter is NULL or a pointer to an empty
                        //string, the function will open a new handle to the key
                        //identified by the hKey parameter.
                        REGSAM  samDesired   //desired security access

                        )
{
ASSERT(hKey != NULL);
//Note: ERROR_NO_SYSTEM_RESOURCES is returned if the key is opened more than
//65534 times.
return (RegOpenKeyEx(hKey, lpszKeyName, _RESERVED_FOR_FUTURE_USE,
                     samDesired, &m_hKey) == ERROR_SUCCESS);
}

//-----------------------------------------------------------------------------
/*The function opens the specified key for the reading only.
  If lpszKeyName parameter is NULL or a pointer to an empty string, the function 
  initializes m_hKey member to the same handle that was passed in.
  Use this method if user is a restricted access user.
  A single registry key can be opened only 65534 times; after that function fails.
  
  Returns TRUE if successful, otherwise returns FALSE;
  
  See also: CRegistryKey::Open(), RegOpenKeyEx()
 */
BOOL CRegistryKey::OpenToRead(HKEY hKey, LPCTSTR szSubkey)
{
ASSERT(hKey != NULL);
//Note: ERROR_NO_SYSTEM_RESOURCES is returned if the key is opened more than
//65534 times.
return (RegOpenKeyEx(hKey, szSubkey, _RESERVED_FOR_FUTURE_USE,
                     KEY_READ, &m_hKey) == ERROR_SUCCESS);
}

//-----------------------------------------------------------------------------
/*
 */
BOOL CRegistryKey::HasKey(LPCTSTR szSubkey)
{
ASSERT(m_hKey != NULL);
return CRegistryKey::HasKey(m_hKey, szSubkey);
}

//-----------------------------------------------------------------------------
/*Determine if the specified subkey exists. Key names are not case sensitive.
 */
BOOL CRegistryKey::HasKey(HKEY hKey, LPCTSTR szSubkey)
{
ASSERT(szSubkey[0] != '\\');
HKEY hSubkey;
LONG lResult = ::RegOpenKeyEx(hKey, 
              LPCTSTR(szSubkey), 
              0,
              KEY_READ, 
              &hSubkey);
::RegCloseKey(hSubkey);
if (lResult == ERROR_FILE_NOT_FOUND)
  return FALSE;

return TRUE;  //ERROR_SUCCESS, Access right or other errors
}


//-----------------------------------------------------------------------------
/*
 */
BOOL CRegistryKey::SetValue(const DWORD dwValue,
                            LPCTSTR szValueName //[in] = NULL
                            )
{
ASSERT(m_hKey != NULL);
const DWORD dwType = REG_DWORD;
  
if(::RegSetValueEx(m_hKey, 
                    szValueName, 
          _RESERVED_FOR_FUTURE_USE, 
          dwType, 
          (LPBYTE)&dwValue, 
          sizeof(DWORD)) == ERROR_SUCCESS)
  {
  ::RegFlushKey(m_hKey);
  return TRUE;
  }
return FALSE;
}

//-----------------------------------------------------------------------------
/*
 */
BOOL CRegistryKey::GetValue(DWORD& dwValue,
                         LPCTSTR szValueName //[in] = NULL
                         )
{
ASSERT(m_hKey != NULL);

DWORD dwType = REG_DWORD;
DWORD lpcbData = sizeof(DWORD);
dwValue = 0;  
    
BOOL bRet = (RegQueryValueEx(m_hKey,
                              szValueName,
                              _RESERVED_FOR_FUTURE_USE,
                              &dwType, 
                              (LPBYTE)&dwValue,
                              &lpcbData) == ERROR_SUCCESS);

return bRet;
}

//::SetStringValue()-----------------------------------------------------------
/*The function associates a text string with a specified key. This value must
  be a text string and cannot have a name.
 */
BOOL CRegistryKey::SetValue(LPCTSTR lpszValue,
                            LPCTSTR lpszValueName //[in] = NULL
                            )
{
ASSERT(m_hKey != NULL);
return (RegSetValueEx(m_hKey, lpszValueName, _RESERVED_FOR_FUTURE_USE, REG_SZ,
                     (BYTE * const)lpszValue,
                     (lstrlen(lpszValue)+1)*sizeof(TCHAR)) == ERROR_SUCCESS);
//Note: For data types REG_SZ, REG_EXPAND_SZ, or REG_MULTI_SZ, cbData must include
//the size of the terminating null character.
}

//::GetStringValue()-----------------------------------------------------------
#ifdef __AFXWIN_H__         //Include MFC library
/*
 */
BOOL CRegistryKey::GetValue(CString& strResult,
                            LPCTSTR lpszValueName //[in] = NULL The key name of
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
BOOL CRegistryKey::GetValue(LPTSTR szResult,
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
  dwCount = *pnBufferSize;
  lRes = RegQueryValueEx(m_hKey, 
                         (LPTSTR)lpszValueName,
                        NULL, 
                        &dwType,
                        (LPBYTE)szResult, 
                        pnBufferSize);
  ASSERT(lRes == ERROR_SUCCESS);
  *pnBufferSize = dwCount; //Return real string length
  return TRUE;
  }

*pnBufferSize = 0;
return FALSE;
}
#endif  //__AFXWIN_H__

//-----------------------------------------------------------------------------
/*Get the number of subkeys.

  Returns -1 in case of a failure.
 */
int CRegistryKey::Enumerate()
{
DWORD dwSubKeyCount;
DWORD dwValueCount;
DWORD dwClassNameLength = MAX_KEY_LENGTH;
DWORD dwMaxSubKeyName;
DWORD dwMaxValueName; 
DWORD dwMaxValueLength;
FILETIME ftLastWritten;
_TCHAR szClassBuffer[MAX_KEY_LENGTH];
//Retrieve information about the specified registry key.
LONG lResult = ::RegQueryInfoKey(m_hKey, 
                                 szClassBuffer, 
                 &dwClassNameLength,
                                 NULL, 
                 &dwSubKeyCount, 
                 &dwMaxSubKeyName, 
                 NULL, &dwValueCount,
                               &dwMaxValueName, &dwMaxValueLength, 
                 NULL, &ftLastWritten);
      
if (lResult != ERROR_SUCCESS) 
  return -1;
return (int)dwSubKeyCount;
}

//-----------------------------------------------------------------------------
/*Get the number of values that are associated with the key.

  Returns -1 in case of a failure.
 */
int CRegistryKey::EnumerateValue()
{
DWORD dwSubKeyCount;
DWORD dwValueCount;
DWORD dwClassNameLength = MAX_KEY_LENGTH;
DWORD dwMaxSubKeyName;
DWORD dwMaxValueName; 
DWORD dwMaxValueLength;
FILETIME ftLastWritten;
_TCHAR szClassBuffer[MAX_KEY_LENGTH];
//Retrieve information about the specified registry key.
LONG lResult = ::RegQueryInfoKey(m_hKey, 
                                 szClassBuffer, 
                 &dwClassNameLength,
                                 NULL, 
                 &dwSubKeyCount, 
                 &dwMaxSubKeyName, 
                 NULL, &dwValueCount,
                               &dwMaxValueName, &dwMaxValueLength, 
                 NULL, &ftLastWritten);
      
if (lResult != ERROR_SUCCESS) 
  return -1;
return (int)dwValueCount;
}

//::GetData()------------------------------------------------------------------
/*The function retrieves the data for a specified value name
  associated with an open registry key. If the buffer specified by lpData
  parameter is not large enough to hold the data, the function returns
  the value ERROR_MORE_DATA.

  Predefined Value Types        VALUE   Description (WinNT.h)
  REG_NONE                        0  No value type
  REG_SZ                          1  Unicode nul terminated string
  REG_EXPAND_SZ                   2  Unicode nul terminated string with
                                     environment variable references
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

//::SetData()------------------------------------------------------------------
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

//-----------------------------------------------------------------------------
/*Obtain the size, in bytes, of a data value associated with the current key.

  Returns the size of the data value. In case of a failure returns -1.
 */
int CRegistryKey::GetDataSize(LPCTSTR lpszValueName //[in] name of the data value to query
                              )
{
DWORD dwSize = 1;
LONG lResult = ::RegQueryValueEx(m_hKey, 
                                 lpszValueName,
                                 NULL, NULL, NULL, &dwSize);

if (lResult != ERROR_SUCCESS) 
   return -1;
return (int)dwSize;
}

//-----------------------------------------------------------------------------
/*
 */
DWORD CRegistryKey::GetDataType(LPCTSTR lpszValueName //[in] name of the data value to query
                              )
{
DWORD dwType = 1;
LONG lResult = ::RegQueryValueEx(m_hKey, 
                                  lpszValueName,
                              NULL, &dwType, NULL, NULL);

if (lResult == ERROR_SUCCESS) 
  return dwType;

return 0;
}

//-----------------------------------------------------------------------------
/*Deletes the subkeys and values of the specified key recursively.
 
  See also: SHDeleteKey(), SHDeleteEmptyKey(), RegDeleteTree(), MSDN Q142491 
 */
 BOOL CRegistryKey::DeleteTree(LPTSTR szSubkey, HKEY hTreeKey)
{
/*MSDN: Q142491 http://support.microsoft.com/kb/142491
  Ref.: "Deleting a Key with Subkeys"  http://msdn.microsoft.com/en-us/library/ms724235%28VS.85%29.aspx
  In Windows 95, the RegDeleteKey function not only deletes the particular key 
  specified but also any subkey descendants. In contrast, the Windows NT version
  of this function deletes only the particular key specified and will not delete 
  any key that has subkey descendants.
    To delete a key and all of its subkeys in Windows NT, a recursive delete 
  function is implemented using RegEnumKeyEx and RegDeleteKey. This recursive
  delete function uses the following simple two-step algorithm:
     1. Traverse down each subkey branch, one branch at a time, enumerating keys 
      at each subkey level, until the last subkey leaf is reached.
     2. Individually delete each subkey in reverse succession, one branch at 
      a time, until the specified key is deleted.
  Note: always enumerate subkey index zero (that is, DWORD iSubkey = 0). 
  Because keys are re-indexed after each key is deleted, the use of a non-zero 
  subkey index would result in keys not being deleted. This in turn would 
  result in the failure of the RegDeleteKey function when an attempt is made
  to delete the subkey's parent key. 
 */  
ASSERT(hTreeKey != NULL);
LONG lResult;
if ( (szSubkey != NULL) &&  lstrlen(szSubkey)) //Do not allow NULL or empty key name
{

  HKEY  hKey = NULL;
  //Note: If, between the time of the delete privilege test and the actual
  //attempt to delete, the key protection is altered, the recursive delete function 
  //will ail. 
  if( (lResult = RegOpenKeyEx(hTreeKey,
                              szSubkey,
                              _RESERVED_FOR_FUTURE_USE, 
                              KEY_ENUMERATE_SUB_KEYS | DELETE, 
                              &hKey )) == ERROR_SUCCESS)
  {

    while (lResult == ERROR_SUCCESS )
    {
      DWORD dwSubKeyLength = MAX_KEY_LENGTH;
      TCHAR   szSubKey[MAX_KEY_LENGTH]; // (256) this should be dynamic.
      //LPTSTR  pSubKey = NULL;

      lResult = RegEnumKeyEx(hKey,
                              0,       // always index zero
                              szSubKey,
                              &dwSubKeyLength,
                              NULL,
                              NULL,
                              NULL,
                              NULL
                              );

      if(lResult == ERROR_NO_MORE_ITEMS)
      {
        lResult = RegDeleteKey(hTreeKey, szSubkey);
        break;
      }
      else 
      {
        if(lResult == ERROR_SUCCESS)
          lResult = DeleteTree(szSubKey, hKey);
      }
    }
    RegCloseKey(hKey);
    // Do not save return code because error
    // has already occurred
  }
}
else
  lResult = ERROR_BADKEY;

return lResult; 
}
 
///////////////////////////////////////////////////////////////////////////////
#endif  //_WIN32

///////////////////////////////////////////////////////////////////////////////

//operator<<()-----------------------------------------------------------------
/*Translates predefined HKEY to readable text.

  Note: uses Microsoft Foundation Library (MFC).
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
 * $Log: $
 *  12   Biblioteka1.11        2005-05-04 01:27:33  Darko           stdafx
 *  11   Biblioteka1.10        2005-05-03 11:16:09  Darko Kolakovic Unicode build
 *  10   Biblioteka1.9         2005-04-26 11:35:24  Darko Kolakovic Document groups
 *       and typo fixes
 *  9    Biblioteka1.8         2005-04-18 15:20:40  Darko Kolakovic header file
 *       name
 *  8    Biblioteka1.7         2005-03-21 03:16:51  Darko           comments
 *  7    Biblioteka1.6         2004-10-01 22:35:17  Darko           stdafx.h
 *  6    Biblioteka1.5         2003-09-03 20:09:01  Darko           defined NDEBUG
 *       ASSERT
 *  5    Biblioteka1.4         2003-08-09 14:11:16  Darko           formatting
 *  4    Biblioteka1.3         2002-01-29 23:21:42  Darko           Used libraries
 *       notes
 *  3    Biblioteka1.2         2002-01-25 16:57:49  Darko           Updated
 *       comments
 *  2    Biblioteka1.1         2001-08-17 00:37:56  Darko           Update
 *  1    Biblioteka1.0         2001-07-07 01:13:45  Darko
 *****************************************************************************/

