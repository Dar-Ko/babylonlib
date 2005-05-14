/*$Workfile: KRegK16.h$: header file
  $Revision: 6$ $Date: 2005-04-26 11:37:42$
  $Author: Darko Kolakovic$

  Windows Registry handler
  May 94 Darko Kolakovic
 */
// Group=Windows

#ifndef _KREGKEY_H_
    //$Workfile: KRegK16.h$ sentry
  #define _KREGKEY_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

/////////////////////////////////////////////////////////////////////////////
//CRegistryKey handles operations with registry file.
//
//Note: Microsoft Windows 16b specific (Win16).
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
  BOOL Create(HKEY hKey, LPCTSTR lpszKeyName);
  BOOL Open  (HKEY hKey, LPCTSTR lpszKeyName);
  void Close();
  BOOL SetStringValue(LPCTSTR lpszValue, LPCTSTR lpszValueName = NULL);
  #ifdef __AFXWIN_H__   //MFC library
    BOOL GetStringValue(CString& strResult, LPCTSTR lpszValueName = NULL);
  #else
    BOOL GetStringValue(LPTSTR szResult, size_t* pnBufferSize, LPCTSTR lpszValueName = NULL);
  #endif
// Overrides

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
#endif  //_KREGKEY_H_
