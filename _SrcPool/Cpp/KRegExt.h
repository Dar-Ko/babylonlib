/*$Workfile: H:\_SrcPool\Cpp\KRegExt.h$: header file
  $Revision: 1.1 $ $Date: 2002/09/06 22:19:04 $
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
 *  11   Biblioteka1.10        1/29/02 10:21:39 PM  Darko           Used lbraries
 *       notes 
 *  10   Biblioteka1.9         1/24/02 6:19:19 PM   Darko           Updated
 *       comments
 *  9    Biblioteka1.8         8/19/01 10:54:52 PM  Darko           Butyfier
 *  8    Biblioteka1.7         7/7/01 12:02:18 AM   Darko           
 *  7    Biblioteka1.6         7/6/01 11:57:49 PM   Darko           
 *  6    Biblioteka1.5         7/6/01 11:57:26 PM   Darko           
 *  5    Biblioteka1.4         7/6/01 11:57:06 PM   Darko           
 *  4    Biblioteka1.3         7/6/01 11:56:30 PM   Darko           
 *  3    Biblioteka1.2         7/6/01 11:55:38 PM   Darko           include header
 *       file
 *  2    Biblioteka1.1         6/8/01 10:51:39 PM   Darko           VSS
 *  1    Biblioteka1.0         8/13/00 2:57:39 PM   Darko           
 * $
 *****************************************************************************/
