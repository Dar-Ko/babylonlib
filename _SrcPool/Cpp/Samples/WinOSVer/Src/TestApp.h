// TestApp.h : main header file for the TestApp application
// Windows OS Version test application
// Interface of the CTestApp class
//
// Compiled with MSVC++ 4.0
//
// Darko  Kolakovic
// Jan. 2k


#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif

#include "Resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestApp:
// See TestApp.cpp for the implementation of this class
//

//The base class for the Windows OS Version test application
class CTestApp : public CWinApp
{
public:
	CTestApp();
// Operations
public:
  virtual BOOL DoTestInit();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
