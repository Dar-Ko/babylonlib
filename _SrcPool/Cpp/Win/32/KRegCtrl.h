/*$Workfile: S:\_SrcPool\Cpp\Win\32\KRegCtrl.h$: header file
  $Revision: 3$ $Date: 2005-04-26 11:35:19$
  $Author: Darko Kolakovic$
  
  Interface of the CRegisterCtrl class 
  Copyright: CommonSoft Inc
  May. 94 Darko Kolakovic
 */
// Group=Windows

#ifndef __KREGCTRL_H__
  //$Workfile: S:\_SrcPool\Cpp\Win\32\KRegCtrl.h$ sentry
  #define __KREGCTRL_H__

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
//CRegisterCtrl helper class TODO: description.

//Note: uses Microsoft Foundation Library (MFC); 
//      Microsoft Windows specific (Win).
class CRegisterCtrl
{
public:
  CRegisterCtrl();
  virtual ~CRegisterCtrl();

public:
  bool IsRegistered(LPCTSTR szProgID);
  bool Register(LPCTSTR szPath);
  bool Register(LPCTSTR szProgID, LPCTSTR szControlName);
};

///////////////////////////////////////////////////////////////////////////////
#endif  //__KREGCTRL_H__
/*****************************************************************************
 * $Log: 
 *  3    Biblioteka1.2         2005-04-26 11:35:19  Darko Kolakovic Document groups
 *       and typo fixes
 *  2    Biblioteka1.1         2004-10-01 22:35:13  Darko           stdafx.h
 *  1    Biblioteka1.0         2003-08-13 17:36:42  Darko           
 * $
 *****************************************************************************/
