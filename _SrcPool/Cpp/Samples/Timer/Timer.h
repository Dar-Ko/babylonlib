// Timer.h : main header file for the TIMER application
//

#if !defined(AFX_TIMER_H__383E4A3B_64E2_11D5_AB38_000103BE4653__INCLUDED_)
#define AFX_TIMER_H__383E4A3B_64E2_11D5_AB38_000103BE4653__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTimerApp:
// See Timer.cpp for the implementation of this class
//

//##ModelId=3ECE708902E6
class CTimerApp : public CWinApp
{
public:
	//##ModelId=3ECE70890304
	CTimerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimerApp)
	public:
	//##ModelId=3ECE70890305
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTimerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMER_H__383E4A3B_64E2_11D5_AB38_000103BE4653__INCLUDED_)
