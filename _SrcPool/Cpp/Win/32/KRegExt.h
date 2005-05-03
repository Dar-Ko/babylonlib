/*$Workfile: KRegExt.h$: header file
  $Revision: 13$ $Date: 2005-04-26 11:35:22$
  $Author: Darko Kolakovic$

  Windows Registry Extended handler
  Copyright: CommonSoft Inc
  Darko Kolakovic Nov 98
 */
// Group=Windows

#ifndef _KREGEXT_H_
    //$Workfile: KRegExt.h$ sentry
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
 *  13   Biblioteka1.12        2005-04-26 11:35:22  Darko Kolakovic Document groups
 *       and typo fixes
 *  12   Biblioteka1.11        2005-03-21 03:16:48  Darko           comments
 *  11   Biblioteka1.10        2002-01-29 23:21:39  Darko           Used lbraries
 *       notes 
 *  10   Biblioteka1.9         2002-01-24 19:19:19  Darko           Updated
 *       comments
 *  9    Biblioteka1.8         2001-08-19 23:54:52  Darko           Butyfier
 *  8    Biblioteka1.7         2001-07-07 01:02:18  Darko           
 *  7    Biblioteka1.6         2001-07-07 00:57:49  Darko           
 *  6    Biblioteka1.5         2001-07-07 00:57:26  Darko           
 *  5    Biblioteka1.4         2001-07-07 00:57:06  Darko           
 *  4    Biblioteka1.3         2001-07-07 00:56:30  Darko           
 *  3    Biblioteka1.2         2001-07-07 00:55:38  Darko           include header
 *       file
 *  2    Biblioteka1.1         2001-06-08 23:51:39  Darko           VSS
 *  1    Biblioteka1.0         2000-08-13 15:57:39  Darko           
 * $
 *****************************************************************************/
