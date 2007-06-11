/*$Workfile: TestComplex.h$: header file
  $Revision: 6$ $Date: 2007-06-08 17:56:11$
  $Author: Darko Kolakovic$

  Interface of the main test application

  Darko Kolakovic Jan. 2k Compiled with MSVC++ 4.0
*/

// Group=Examples

#ifndef _TSMFCAPP_H_
  //$Workfile: TestComplex.h$ sentry
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
  virtual BOOL DoTestInit();

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
  $Log: $
 */
