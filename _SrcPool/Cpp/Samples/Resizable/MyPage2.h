#if !defined(AFX_MYPAGE2_H__E8F99402_03C8_11D4_AD28_00606767A9D2__INCLUDED_)
#define AFX_MYPAGE2_H__E8F99402_03C8_11D4_AD28_00606767A9D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyPage2.h : header file
//
#include "KPropPgR.h" //CPropertyPageResizable class

/////////////////////////////////////////////////////////////////////////////
// MyPage2 dialog

//##ModelId=3ECE52E60278
class MyPage2 : public CPropertyPageResizable
{
	DECLARE_DYNCREATE(MyPage2)

// Construction
public:
	//##ModelId=3ECE52E6028C
	MyPage2();
	//##ModelId=3ECE52E60296
	~MyPage2();

// Dialog Data
	//{{AFX_DATA(MyPage2)
	enum { IDD = IDD_DIALOG2 };
	//##ModelId=3ECE52E602A1
	CIPAddressCtrl	m_IPAddress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(MyPage2)
	protected:
	//##ModelId=3ECE52E602B4
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(MyPage2)
	//##ModelId=3ECE52E602C8
	virtual BOOL OnInitDialog();
	//##ModelId=3ECE52E602D2
	afx_msg void OnRadio1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPAGE2_H__E8F99402_03C8_11D4_AD28_00606767A9D2__INCLUDED_)
