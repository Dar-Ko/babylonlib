// TimerDlg.h : header file
//

#if !defined(AFX_TIMERDLG_H__383E4A3D_64E2_11D5_AB38_000103BE4653__INCLUDED_)
#define AFX_TIMERDLG_H__383E4A3D_64E2_11D5_AB38_000103BE4653__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KTimerW.h"  //CTimerW class

/////////////////////////////////////////////////////////////////////////////
// CTimerDlg dialog
//##ModelId=3ECE708901B0
class CTimerDlg : public CDialog
{
// Construction
public:
	//##ModelId=3ECE708901CD
	CTimerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTimerDlg)
	enum { IDD = IDD_TIMER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimerDlg)
	protected:
	//##ModelId=3ECE708901D7
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//##ModelId=3ECE708901EB
	HICON m_hIcon;
	//##ModelId=3ECE70890200
    CTimerW m_ctwTimer1; //first timer with private message loop
	//##ModelId=3ECE7089021E
    CTimerW m_ctwTimer2; //second timer
	//##ModelId=3ECE70890231
    void CreateCallbackTimer();

	// Generated message map functions
	//{{AFX_MSG(CTimerDlg)
	//##ModelId=3ECE7089023B
	virtual BOOL OnInitDialog();
	//##ModelId=3ECE70890250
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//##ModelId=3ECE70890265
	afx_msg void OnPaint();
	//##ModelId=3ECE70890278
	afx_msg HCURSOR OnQueryDragIcon();
	//##ModelId=3ECE70890282
	virtual void OnOK();
	//##ModelId=3ECE7089028D
	virtual void OnCancel();
	//##ModelId=3ECE708902A0
	afx_msg void OnTimer1();
	//##ModelId=3ECE708902AA
	afx_msg void OnTimer2();
	//##ModelId=3ECE708902B5
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMERDLG_H__383E4A3D_64E2_11D5_AB38_000103BE4653__INCLUDED_)
