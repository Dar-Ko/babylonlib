#if !defined(AFX_MyPage4_H__FB10CE15_0EE1_11D4_AD28_00606767A9D2__INCLUDED_)
#define AFX_MyPage4_H__FB10CE15_0EE1_11D4_AD28_00606767A9D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyPage4.h : header file
//
#include "KPropPgR.h" //CPropertyPageResizable class

/////////////////////////////////////////////////////////////////////////////
// MyPage4 dialog

//##ModelId=3ECE52E60160
class MyPage4 : public CPropertyPageResizable
{
	DECLARE_DYNCREATE(MyPage4)

// Construction
public:
	//##ModelId=3ECE52E6017E
	MyPage4();
	//##ModelId=3ECE52E60188
	~MyPage4();

// Dialog Data
	//{{AFX_DATA(MyPage4)
	enum { IDD = IDD_DIALOG4 };
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(MyPage4)
	public:
	//##ModelId=3ECE52E60189
	virtual BOOL OnSetActive();
	protected:
	//##ModelId=3ECE52E60193
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(MyPage4)
	//##ModelId=3ECE52E601A6
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MyPage4_H__FB10CE15_0EE1_11D4_AD28_00606767A9D2__INCLUDED_)
