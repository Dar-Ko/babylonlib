/*$Workfile: KRegKey.h$: header file
  $Revision: 5$ $Date: 2003-09-22 21:26:43$
  $Author: Darko$

  Windows Registry handler
  Copyright: CommonSoft Inc
  Darko Kolakovic May 94
 */
 
#ifndef _KREGKEY_H_
    //KRegKey.h sentry
  #define _KREGKEY_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifndef _WINREG_
  #include <WinReg.h>
#endif

/////////////////////////////////////////////////////////////////////////////
//CRegistryKey handles operations with registry file.
//
//Note: Microsoft Windows specific (Win).
class CRegistryKey
{
public:
  CRegistryKey();
  ~CRegistryKey();

// Attributes
public:
  HKEY m_hKey;

// Operations
public:
  BOOL Create(HKEY hKey, LPCTSTR lpszKeyName = NULL, REGSAM samDesired = KEY_ALL_ACCESS);
  BOOL Open  (HKEY hKey, LPCTSTR lpszKeyName = NULL, REGSAM samDesired = KEY_ALL_ACCESS);
  void Close();
  BOOL SetStringValue(LPCTSTR lpszValue, LPCTSTR lpszValueName = NULL);
  #ifdef __AFXWIN_H__   //MFC library
    BOOL GetStringValue(CString& strResult, LPCTSTR lpszValueName = NULL);
  #else
    BOOL GetStringValue(LPTSTR szResult, DWORD* pnBufferSize, LPCTSTR lpszValueName = NULL);
  #endif
// Overrides
  virtual BOOL GetData(LPBYTE lpData, DWORD* pnBufferSize,LPCTSTR lpszValueName = NULL);
  virtual BOOL SetData(LPBYTE lpData, DWORD  nBufferSize,LPCTSTR lpszValueName = NULL);
// Implementation
protected:
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

inline CRegistryKey::CRegistryKey() :
  m_hKey(NULL)
{}

inline CRegistryKey::~CRegistryKey()
{
Close();
}

///////////////////////////////////////////////////////////////////////////////

CString& operator<<(CString& strDestination, CRegistryKey& regSource);

#ifdef _DEBUG
//operator<<()-----------------------------------------------------------------
/*Outputs the CRegistryKey object to the dump context.

  Note: uses Microsoft Fundation Library (MFC).

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
#endif

///////////////////////////////////////////////////////////////////////////////
#endif  //_KREGKEY_H_
/*****************************************************************************
 * $Log: 
 *  5    Biblioteka1.4         2003-09-22 21:26:43  Darko           formatting
 *  4    Biblioteka1.3         2002-01-29 22:21:46  Darko           Used lbraries
 *       notes 
 *  3    Biblioteka1.2         2002-01-24 18:19:23  Darko           Updated
 *       comments
 *  2    Biblioteka1.1         2001-08-16 23:38:00  Darko           Update
 *  1    Biblioteka1.0         2001-07-07 00:13:47  Darko           
 * $
 *****************************************************************************/
