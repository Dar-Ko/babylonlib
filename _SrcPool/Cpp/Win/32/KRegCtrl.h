/*$Workfile: KRegCtrl.h$: header file
  $Revision: 2$ $Date: 2004-10-01 21:35:13$
  $Author: Darko$
  
  Interface of the CRegisterCtrl class 
  Copyright: CommonSoft Inc
  May. 94 Darko Kolakovic
 */
#ifndef __KREGCTRL_H__
  //KRegCtrl.h sentry
  #define __KREGCTRL_H__

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
//CRegisterCtrl helper class TODO: description.

//Note: uses Microsoft Fundation Library (MFC); 
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
 *  2    Biblioteka1.1         2004-10-01 21:35:13  Darko           stdafx.h
 *  1    Biblioteka1.0         2003-08-13 16:36:42  Darko           
 * $
 *****************************************************************************/
