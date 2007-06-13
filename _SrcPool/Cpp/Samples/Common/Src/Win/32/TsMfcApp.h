/*$Workfile: TsMfcApp.h$: header file
  $Revision: 6$ $Date: 2007-06-13 16:20:14$
  $Author: Darko Kolakovic$

  Interface of the main test application

  Darko Kolakovic Jan. 2k Compiled with MSVC++ 4.0
*/

// Group=Examples

#ifndef _TSMFCAPP_H_
  //$Workfile: TsMfcApp.h$ sentry
  #define _TSMFCAPP_H_

#ifndef __AFXWIN_H__
  #error include 'stdafx.h' before including this file for PCH
#endif

#if defined(_AFXDLL) && !defined(_DLL)
  #error Please use the multithreaded DLL C-runtime (/MD switch) for MFC builds
#endif

#if defined(_AFXDLL) && !defined(_MT)
  #error Please use the multithreaded DLL C-runtime (/MD switch) for MFC builds
#endif

#include "TsMfcRes.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
/*The base class for the Windows OS Version test application.

  Note: Microsoft Windows specific (Win32) 
        and uses Microsoft Foundation Library (MFC).
 */
class CTestApp : public CWinApp
{
public:
  CTestApp();
  virtual ~CTestApp();

//Operations
public:
  virtual int DoTestInit();

//Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CTestApp)
  public:
  virtual BOOL InitInstance();
  //}}AFX_VIRTUAL

//Implementation

  //{{AFX_MSG(CTestApp)
  afx_msg void OnAppAbout();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

#endif //_TSMFCAPP_H_
////////////////////////////////////////////////////////////////////////////////
/*
  $Log: 
   6    Biblioteka1.5         2007-06-13 16:20:14  Darko Kolakovic Entry point for
        the test
   5    Biblioteka1.4         2007-06-11 17:00:25  Darko Kolakovic Windows MFC
        application
   4    Biblioteka1.3         2007-06-11 13:45:21  Darko Kolakovic 
   3    Biblioteka1.2         2007-05-24 11:51:31  Darko Kolakovic Formatting
   2    Biblioteka1.1         2001-07-11 22:36:42  Darko           
   1    Biblioteka1.0         2001-06-08 22:43:48  Darko           
  $
 */
