// Resize.h : main header file for the RESIZE application
//

#if !defined(AFX_RESIZE_H__D536C667_0182_11D4_AD28_00606767A9D2__INCLUDED_)
#define AFX_RESIZE_H__D536C667_0182_11D4_AD28_00606767A9D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CResizeApp:
// See Resize.cpp for the implementation of this class
//

//##ModelId=3ECE52E503CB
class CResizeApp : public CWinApp
{
public:
	//##ModelId=3ECE52E60001
	CResizeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResizeApp)
	public:
	//##ModelId=3ECE52E6000B
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//##ModelId=3ECE52E60016
	COleTemplateServer m_server;
		// Server object for document creation
	//{{AFX_MSG(CResizeApp)
	//##ModelId=3ECE52E60029
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESIZE_H__D536C667_0182_11D4_AD28_00606767A9D2__INCLUDED_)
