// ECCSTAPITest.h : main header file for the ECCSTAPITEST application
//

#if !defined(AFX_ECCSTAPITEST_H__690A3B70_120F_42A5_8C7F_B7EA0DF9FAC0__INCLUDED_)
#define AFX_ECCSTAPITEST_H__690A3B70_120F_42A5_8C7F_B7EA0DF9FAC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CECCSTAPITestApp:
// See ECCSTAPITest.cpp for the implementation of this class
//

class CECCSTAPITestApp : public CWinApp
{
public:
	CECCSTAPITestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CECCSTAPITestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CECCSTAPITestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ECCSTAPITEST_H__690A3B70_120F_42A5_8C7F_B7EA0DF9FAC0__INCLUDED_)
