#if !defined(AFX_MYPAGE1_H__E8F99401_03C8_11D4_AD28_00606767A9D2__INCLUDED_)
#define AFX_MYPAGE1_H__E8F99401_03C8_11D4_AD28_00606767A9D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyPage1.h : header file
//
#include "KPropPgR.h" //CPropertyPageResizable class

/////////////////////////////////////////////////////////////////////////////
// MyPage1 dialog

//##ModelId=3ECE52E602FA
class MyPage1 : public CPropertyPageResizable
{
	DECLARE_DYNCREATE(MyPage1)

// Construction
public:
	//##ModelId=3ECE52E60318
	MyPage1();
	//##ModelId=3ECE52E60319
	~MyPage1();

// Dialog Data
	//{{AFX_DATA(MyPage1)
	enum { IDD = IDD_DIALOG1 };
	//##ModelId=3ECE52E6032D
	CProgressCtrl	m_ctrlProgress;
	//##ModelId=3ECE52E60341
	CComboBox	m_comboboxDir;
	//##ModelId=3ECE52E60354
	CString	m_ctrlEdit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(MyPage1)
	protected:
	//##ModelId=3ECE52E6035E
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(MyPage1)
	//##ModelId=3ECE52E60373
	virtual BOOL OnInitDialog();
	//##ModelId=3ECE52E60386
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPAGE1_H__E8F99401_03C8_11D4_AD28_00606767A9D2__INCLUDED_)
