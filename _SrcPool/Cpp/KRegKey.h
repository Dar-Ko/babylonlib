/*$Workfile: KRegKey.h$: header file
  $Revision: 1.2 $ $Date: 2002/09/10 15:22:21 $
  $Author: ddarko $

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
 *  4    Biblioteka1.3         1/29/02 11:21:46 PM  Darko           Used lbraries
 *       notes 
 *  3    Biblioteka1.2         1/24/02 7:19:23 PM   Darko           Updated
 *       comments
 *  2    Biblioteka1.1         8/17/01 12:38:00 AM  Darko           Update
 *  1    Biblioteka1.0         7/7/01 1:13:47 AM    Darko           
 * $
 *****************************************************************************/
