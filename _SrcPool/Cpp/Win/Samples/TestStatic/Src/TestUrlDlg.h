/*$Workfile: TestUrlDlg.h$: header file
  $Revision: 3$ $Date: 2005-05-03 00:44:13$
  $Author: Darko$

  Interface of the CHTTPUtilsDlg class
  Copyright: CommonSoft Inc
  2001-07-07 Darko Kolakovic
 */

// Group=Examples Windows

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

#include "KHypLink.h" //CHyperLink class

/////////////////////////////////////////////////////////////////////////////
// CHTTPUtilsDlg dialog

class CHTTPUtilsDlg : public CDialog
{
// Construction
public:
  CHTTPUtilsDlg(CWnd* pParent = NULL);  // standard constructor

// Dialog Data
  //{{AFX_DATA(CHTTPUtilsDlg)
  enum { IDD = IDD_HTTPUTILS_DIALOG };
  CStatic m_staticDisplay;
  CHyperLink  m_chlURL;
  //}}AFX_DATA

  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CHTTPUtilsDlg)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:
  HICON m_hIcon;

  // Generated message map functions
  //{{AFX_MSG(CHTTPUtilsDlg)
  virtual BOOL OnInitDialog();
  afx_msg void OnPaint();
  afx_msg HCURSOR OnQueryDragIcon();
  virtual void OnOK();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  3    Biblioteka1.2         2005-05-03 00:44:13  Darko            
 *  2    Biblioteka1.1         2005-05-03 00:08:37  Darko           
 *  1    Biblioteka1.0         2001-07-07 00:20:33  Darko           
 * $
 *****************************************************************************/
