// ECCSTAPITestDlg.h : header file
//

#if !defined(AFX_ECCSTAPITESTDLG_H__0FB1B3B3_A98B_4806_87C1_1207B96CF6C9__INCLUDED_)
#define AFX_ECCSTAPITESTDLG_H__0FB1B3B3_A98B_4806_87C1_1207B96CF6C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CECCSTAPITestDlg dialog

class CECCSTAPITestDlg : public CDialog
{
// Construction
public:
	CECCSTAPITestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CECCSTAPITestDlg)
	enum { IDD = IDD_ECCSTAPITEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CECCSTAPITestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CECCSTAPITestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ECCSTAPITESTDLG_H__0FB1B3B3_A98B_4806_87C1_1207B96CF6C9__INCLUDED_)
