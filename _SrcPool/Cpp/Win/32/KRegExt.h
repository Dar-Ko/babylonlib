/*$Workfile: KRegExt.h$: header file
  $Revision: 11$ $Date: 2002-01-29 22:21:39$
  $Author: Darko$

  Windows Registry Extended handler
  Copyright: CommonSoft Inc
  Darko Kolakovic Nov 98
 */

#ifndef _KREGEXT_H_
    //KRegExt.h sentry
  #define _KREGEXT_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif
#include "KRegKey.h" //CRegistryKey class

/////////////////////////////////////////////////////////////////////////////
//CRegExt handles some specialized operations with registry file.
//
//Note: Microsoft Windows specific (Win).
class CRegExt : public CRegistryKey
{
// Construction
public:

// Attributes
public:
  static TCHAR m_szShellOpenCmd[];
// Operations
public:
  static CString GetAssociatedExecutable(LPCTSTR strExtension);
  BOOL OpenRemote(HKEY hKey = HKEY_LOCAL_MACHINE,LPCTSTR szServerName = NULL);
  CString GetComputerName();
  BOOL GetStringArrayValue(CStringArray& arrayResult,LPCTSTR lpszValueName = NULL);

// Overrides

// Implementation
protected:
};
///////////////////////////////////////////////////////////////////////////////
#endif  //_KREGEXT_H_
/*****************************************************************************
 * $Log: 
 *  11   Biblioteka1.10        2002-01-29 22:21:39  Darko           Used lbraries
 *       notes 
 *  10   Biblioteka1.9         2002-01-24 18:19:19  Darko           Updated
 *       comments
 *  9    Biblioteka1.8         2001-08-19 22:54:52  Darko           Butyfier
 *  8    Biblioteka1.7         2001-07-07 00:02:18  Darko           
 *  7    Biblioteka1.6         2001-07-06 23:57:49  Darko           
 *  6    Biblioteka1.5         2001-07-06 23:57:26  Darko           
 *  5    Biblioteka1.4         2001-07-06 23:57:06  Darko           
 *  4    Biblioteka1.3         2001-07-06 23:56:30  Darko           
 *  3    Biblioteka1.2         2001-07-06 23:55:38  Darko           include header
 *       file
 *  2    Biblioteka1.1         2001-06-08 22:51:39  Darko           VSS
 *  1    Biblioteka1.0         2000-08-13 14:57:39  Darko           
 * $
 *****************************************************************************/
