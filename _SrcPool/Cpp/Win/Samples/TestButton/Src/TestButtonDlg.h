/*$Workfile: TestButtonDlg.h$: header file
  $Revision: 5$ $Date: 2005-05-02 17:08:32$
  $Author: Darko Kolakovic$

  Interface of the CTestButtonDlg class
  Copyright: CommonSoft Inc
  2003-08-25 Darko Kolakovic
 */

// Group=Examples Windows

#pragma once

///////////////////////////////////////////////////////////////////////////////
//CTestButtonDlg dialog
//
//Note: uses Microsoft Foundation Library (MFC);
//      Microsoft Windows specific (Win).
class CTestButtonDlg : public CDialog
{
// Construction
public:
  CTestButtonDlg(CWnd* pParent = NULL); // standard constructor
  virtual ~CTestButtonDlg();

// Dialog Data
  enum { IDD = IDD_TESTBUTTON_DIALOG };



// Implementation
protected:
  HICON m_hIcon;

protected:
  void BexGroup(bool bDelete = false);
  void BxpGroup(bool bDelete = false);

  virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV support
  // Generated message map functions
  virtual BOOL OnInitDialog();
  afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
  afx_msg void OnPaint();
  afx_msg HCURSOR OnQueryDragIcon();
  DECLARE_MESSAGE_MAP()
public:
//  afx_msg void OnClose();
  virtual BOOL DestroyWindow();
};

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  3    Biblioteka1.2         2003-08-29 08:51:45  Darko           new test cases
 *  2    Biblioteka1.1         2003-08-27 18:12:02  Darko           renamed class
 *  1    Biblioteka1.0         2003-08-26 01:36:13  Darko
 * $
 *****************************************************************************/
