/*$Workfile: TestStaticDlg.h$: header file
  $Revision: 3$ $Date: 2005-05-05 17:28:06$
  $Author: Darko Kolakovic$

  Interface of the CTestStaticDlg class
  Copyright: CommonSoft Inc
  2002-01-16 Darko Kolakovic
 */

// Group=Examples Windows

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestStaticDlg dialog

class CTestStaticDlg : public CDialog
{
  DECLARE_DYNAMIC(CTestStaticDlg);
// Construction
public:
  CTestStaticDlg(CWnd* pParent = NULL); // standard constructor

// Dialog Data
  //{{AFX_DATA(CTestStaticDlg)
  enum { IDD = IDD_TESTSTATIC_DIALOG };
    // NOTE: the ClassWizard will add data members here
  //}}AFX_DATA

  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CTestStaticDlg)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:
  HICON m_hIcon;

protected:
  void BexGroup(bool bDelete = false);
  void BxpGroup(bool bDelete = false);

  // Generated message map functions
  //{{AFX_MSG(CTestStaticDlg)
  virtual BOOL OnInitDialog();
  afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
  afx_msg void OnDestroy();
  afx_msg void OnPaint();
  afx_msg HCURSOR OnQueryDragIcon();
  afx_msg BOOL OnToolTipNotify(UINT id, NMHDR *pNMHDR, LRESULT *pResult);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  3    Biblioteka1.2         2005-05-05 17:28:06  Darko Kolakovic Testing new
 *       static controls
 *  2    Biblioteka1.1         2005-05-03 01:44:09  Darko            
 *  1    Biblioteka1.0         2005-05-02 17:04:49  Darko Kolakovic 
 * $
 *****************************************************************************/
