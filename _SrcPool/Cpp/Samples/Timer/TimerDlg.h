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
class CTimerDlg : public CDialog
{
// Construction
public:
  CTimerDlg(CWnd* pParent = NULL);  // standard constructor

// Dialog Data
  //{{AFX_DATA(CTimerDlg)
  enum { IDD = IDD_TIMER_DIALOG };
    // NOTE: the ClassWizard will add data members here
  //}}AFX_DATA

  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CTimerDlg)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:
  HICON m_hIcon;
    CTimerW m_ctwTimer1; //first timer with private message loop
    CTimerW m_ctwTimer2; //second timer
    void CreateCallbackTimer();

  // Generated message map functions
  //{{AFX_MSG(CTimerDlg)
  virtual BOOL OnInitDialog();
  afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
  afx_msg void OnPaint();
  afx_msg HCURSOR OnQueryDragIcon();
  virtual void OnOK();
  virtual void OnCancel();
  afx_msg void OnTimer1();
  afx_msg void OnTimer2();
  afx_msg void OnTimer(UINT nIDEvent);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMERDLG_H__383E4A3D_64E2_11D5_AB38_000103BE4653__INCLUDED_)
