#if !defined(AFX_MYPAGE3_H__FB10CE14_0EE1_11D4_AD28_00606767A9D2__INCLUDED_)
#define AFX_MYPAGE3_H__FB10CE14_0EE1_11D4_AD28_00606767A9D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyPage3.h : header file
//
#include "KPropPgR.h" //CPropertyPageResizable class

/////////////////////////////////////////////////////////////////////////////
// MyPage3 dialog

//##ModelId=3ECE52E601CE
class MyPage3 : public CPropertyPageResizable
{
	DECLARE_DYNCREATE(MyPage3)

// Construction
public:
	//##ModelId=3ECE52E601EC
	MyPage3();
	//##ModelId=3ECE52E601ED
	~MyPage3();

// Dialog Data
	//{{AFX_DATA(MyPage3)
	enum { IDD = IDD_DIALOG3 };
	//##ModelId=3ECE52E601F7
	CListBox	m_ctrlListBox;
	//##ModelId=3ECE52E6020B
	CHotKeyCtrl	m_HotSpot;
	//##ModelId=3ECE52E60229
	CComboBoxEx	m_ctrlComboBox;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(MyPage3)
	protected:
	//##ModelId=3ECE52E6023C
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(MyPage3)
	//##ModelId=3ECE52E60250
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPAGE3_H__FB10CE14_0EE1_11D4_AD28_00606767A9D2__INCLUDED_)
