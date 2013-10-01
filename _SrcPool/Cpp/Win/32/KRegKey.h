/*$RCSfile: KRegKey.h$: header file
  $Revision: 9$ $Date: 2007-05-10 11:12:57$
  $Author: Darko Kolakovic$

  Windows Registry handler
  Copyright: CommonSoft Inc
  Darko Kolakovic May 94
 */
// Group=Windows

#ifndef _KREGKEY_H_
    //$RCSfile: KRegKey.h$ sentry
  #define _KREGKEY_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#if defined _USE_ATL || defined _ATL_VER
  #include <atlbase.h> //CRegKey class
  #include <atlstr.h>  //CString class
  #ifndef ASSERT
    #include "KTraceAtl.h"
  #endif
#else
  #include "ATL/CRegKey.h" //CRegKey class
#endif

#ifndef _WINREG_
  #include <winreg.h>
#endif

#ifndef _RESERVED_FOR_FUTURE_USE
  //Reserved for the future use
  #define _RESERVED_FOR_FUTURE_USE 0
#endif
/////////////////////////////////////////////////////////////////////////////
/*CRegistryKey handles operations with registry file.


    Predefined Value Types        VALUE   Description (WinNT.h)
    REG_NONE                        0  No value type
    REG_SZ                          1  Unicode nul terminated string
    REG_EXPAND_SZ                   2  Unicode nul terminated string with
                                       environment variable references)
    REG_BINARY                      3  Free form binary
    REG_DWORD                       4  32-bit number
    REG_DWORD_LITTLE_ENDIAN         4  32-bit number (same as REG_DWORD)
    REG_DWORD_BIG_ENDIAN            5  32-bit number
    REG_LINK                        6  Symbolic Link (unicode)
    REG_MULTI_SZ                    7  Multiple Unicode strings
    REG_RESOURCE_LIST               8  Resource list in the resource map
    REG_FULL_RESOURCE_DESCRIPTOR    9  Resource list in the hardware description
    REG_RESOURCE_REQUIREMENTS_LIST  10


    Registry Specific Access Rights       Description (REGSAM WinNT.h)
    KEY_ALL_ACCESS                   Combination of KEY_QUERY_VALUE,
                                                    KEY_ENUMERATE_SUB_KEYS,
                                                    KEY_NOTIFY,
                                                    KEY_CREATE_SUB_KEY,
                                                    KEY_CREATE_LINK and
                                                    KEY_SET_VALUE access.
    KEY_CREATE_LINK              32  Permission to create a symbolic link.
    KEY_CREATE_SUB_KEY            4  Permission to create subkeys.
    KEY_ENUMERATE_SUB_KEYS        8  Permission to enumerate subkeys.
    KEY_EXECUTE                      Permission for read access.
    KEY_NOTIFY                   16  Permission for change notification.
    KEY_QUERY_VALUE               1  Permission to query subkey data.
    KEY_READ                         Combination of KEY_QUERY_VALUE,
                                                    KEY_ENUMERATE_SUB_KEYS,
                                                and KEY_NOTIFY access.
    KEY_SET_VALUE                 2  Permission to set subkey data.
    KEY_WRITE                        Combination of KEY_SET_VALUE and
                                                    KEY_CREATE_SUB_KEY access.
  See also: CRegKey
  Note: Microsoft Windows specific (Win).
 */
class CRegistryKey : public CRegKey
{
public:
  CRegistryKey();
  virtual ~CRegistryKey();

// Attributes
//public:
//  HKEY m_hKey;

// Operations
public:
  BOOL Create(HKEY hKey, LPCTSTR lpszKeyName = NULL, REGSAM samDesired = KEY_ALL_ACCESS);
  BOOL Open  (HKEY hKey, LPCTSTR lpszKeyName = NULL, REGSAM samDesired = KEY_ALL_ACCESS);
  BOOL OpenToRead(HKEY hKey, LPCTSTR szSubkey);
  BOOL Save(LPCTSTR lpszFileName);
  BOOL Delete(HKEY hKey, LPCTSTR szSubKey);
  BOOL Load(HKEY hKey, LPCTSTR lpszSubKey, LPCTSTR lpszFileName);
  BOOL Restore(LPCTSTR lpszFileName, DWORD dwFlags);
  BOOL HasKey(LPCTSTR szSubkey);
  static BOOL HasKey(HKEY hKey, LPCTSTR szSubkey);
  int  Enumerate();
  BOOL DeleteTree(LPTSTR pKeyName, HKEY hTreeKey);
   
  BOOL DeleteValue(LPCTSTR lpValueName);
  int EnumerateValue();
  BOOL GetValue(DWORD& dwValue, LPCTSTR szValueName = NULL);
  BOOL SetValue(const DWORD dwValue, LPCTSTR szValueName = NULL);
  BOOL SetValue(LPCTSTR lpszValue, LPCTSTR szValueName = NULL);
  #ifdef __AFXWIN_H__   //MFC library
    BOOL GetValue(CString& strResult, LPCTSTR lpszValueName = NULL);
  #else
    BOOL GetValue(LPTSTR szResult, DWORD* pnBufferSize, LPCTSTR lpszValueName = NULL);
  #endif
  int GetDataSize(LPCTSTR lpszValueName);
  DWORD GetDataType(LPCTSTR lpszValueName);
// Overrides
  virtual BOOL GetData(LPBYTE lpData, DWORD* pnBufferSize, LPCTSTR lpszValueName = NULL);
  virtual BOOL SetData(LPBYTE lpData, DWORD  nBufferSize, LPCTSTR lpszValueName = NULL);
// Implementation
protected:
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

inline CRegistryKey::CRegistryKey()
{
}

inline CRegistryKey::~CRegistryKey()
{
Close();
}

//-----------------------------------------------------------------------------
/*Deletes a subkey and its values. Note that key names are not case sensitive.
  If the function succeeds, the return value is TRUE. If the function fails, 
  the return value is FALSE.
 */
inline BOOL CRegistryKey::Delete(HKEY hKey, LPCTSTR szSubKey)
{  
return (::RegDeleteKey(hKey, szSubKey) == ERROR_SUCCESS);
}

//-----------------------------------------------------------------------------
/*
 */
inline BOOL CRegistryKey::Load(HKEY hKey, LPCTSTR lpszSubKey, LPCTSTR lpszFileName)
{
 return (::RegLoadKey(hKey, lpszSubKey, lpszFileName) == ERROR_SUCCESS);
}

//-----------------------------------------------------------------------------
/*Saves the open key and all of its subkeys and values to a new file, in 
  the standard format.

  See also: RegSaveKey(), RegSaveKeyEx()
 */
inline BOOL CRegistryKey::Save(LPCTSTR lpszFileName)
{
  ASSERT(m_hKey != NULL);
  //Note: If the file already exists, the function fails with the ERROR_ALREADY_EXISTS error.
  return (::RegSaveKey(m_hKey, lpszFileName, NULL) == ERROR_SUCCESS);
}

//-----------------------------------------------------------------------------
/*Reads the registry information in a specified file and copies it over the 
 open key. This registry information may be in the form of a key and multiple
 levels of subkeys.

 Note: There are two different registry hive file formats. Registry hives 
 created on current operating systems typically cannot be loaded by earlier ones.
 
 See also: RegRestoreKey()
 */
inline BOOL CRegistryKey::Restore(LPCTSTR lpszFileName, //[in] name of the file 
                                  //with the registry information
                                  DWORD dwFlags //[in] indicate how the keys
    //are to be restored:
    // - REG_FORCE_RESTORE (Windows NT:  This value is not supported)
    // - REG_WHOLE_HIVE_VOLATILE
                                  )
{
  ASSERT(m_hKey != NULL);
  return (::RegRestoreKey(m_hKey, lpszFileName, dwFlags) == ERROR_SUCCESS);
}

//-----------------------------------------------------------------------------
/*Removes the specified value from the open registry key.
  The key must have been opened with the KEY_SET_VALUE access right at least.
  
  See also: RegDeleteValue(), CRegKey::DeleteValue()
 */
inline BOOL CRegistryKey::DeleteValue(LPCTSTR lpValueName)
{  
return (::RegDeleteValue(m_hKey, lpValueName) == ERROR_SUCCESS);
}
///////////////////////////////////////////////////////////////////////////////

CString& operator<<(CString& strDestination, CRegistryKey& regSource);

#ifdef _DEBUG
  #ifdef __AFXWIN_H__         //Include MFC library
  //operator<<()-----------------------------------------------------------------
  /*Outputs the CRegistryKey object to the dump context.

    Note: uses Microsoft Foundation Library (MFC).

    Group=Diagnostic
   */
  inline CDumpContext& AFXAPI operator<<(CDumpContext& dc, CRegistryKey& Data)
  {
  dc << _T("CRegistryKey @")
     << (PVOID)&Data
     << _T(" HKEY ");
  if (Data.m_hKey == NULL)
    dc << _T("NULL");
  else
    dc << Data.m_hKey;
  dc << _T("\n");
  return dc;
  }
  #endif //__AFXWIN_H__
#endif

///////////////////////////////////////////////////////////////////////////////
#endif  //_KREGKEY_H_
/*****************************************************************************
 * $Log: $
 *  8    Biblioteka1.7         2005-05-04 01:27:19  Darko           path character
 *       case
 *  7    Biblioteka1.6         2005-04-26 11:35:27  Darko Kolakovic Document groups
 *       and typo fixes
 *  6    Biblioteka1.5         2005-03-21 03:16:53  Darko           comments
 *  5    Biblioteka1.4         2003-09-22 22:26:43  Darko           formatting
 *  4    Biblioteka1.3         2002-01-29 23:21:46  Darko           Used libraries
 *       notes
 *  3    Biblioteka1.2         2002-01-24 19:19:23  Darko           Updated
 *       comments
 *  2    Biblioteka1.1         2001-08-17 00:38:00  Darko           Update
 *  1    Biblioteka1.0         2001-07-07 01:13:47  Darko
 *****************************************************************************/
