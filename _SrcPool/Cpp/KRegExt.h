/*$Workfile: KRegExt.h$: header file
  $Revision: 1.3 $ $Date: 2003/01/28 05:37:44 $
  $Author: ddarko $

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
 *  11   Biblioteka1.10        29/01/2002 10:21:39 PMDarko           Used lbraries
 *       notes 
 *  10   Biblioteka1.9         24/01/2002 6:19:19 PMDarko           Updated
 *       comments
 *  9    Biblioteka1.8         19/08/2001 10:54:52 PMDarko           Butyfier
 *  8    Biblioteka1.7         07/07/2001 12:02:18 AMDarko           
 *  7    Biblioteka1.6         06/07/2001 11:57:49 PMDarko           
 *  6    Biblioteka1.5         06/07/2001 11:57:26 PMDarko           
 *  5    Biblioteka1.4         06/07/2001 11:57:06 PMDarko           
 *  4    Biblioteka1.3         06/07/2001 11:56:30 PMDarko           
 *  3    Biblioteka1.2         06/07/2001 11:55:38 PMDarko           include header
 *       file
 *  2    Biblioteka1.1         08/06/2001 10:51:39 PMDarko           VSS
 *  1    Biblioteka1.0         13/08/2000 2:57:39 PMDarko           
 * $
 *****************************************************************************/
