#if !defined(AFX_ABOUTDLG_H__50B5EF88_106C_11D4_AD28_00606767A9D2__INCLUDED_)
#define AFX_ABOUTDLG_H__50B5EF88_106C_11D4_AD28_00606767A9D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AboutDlg.h : header file
//

#include "KDlgRsiz.h" //CDialogResizable class

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog

//##ModelId=3ECE52EC000A
class CAboutDlg : public CDialogResizable
{
// Construction
public:
	//##ModelId=3ECE52EC0028
	CAboutDlg(CWnd* pParent = NULL);   // standard constructor
	//##ModelId=3ECE52EC0033
  CAboutDlg(LPCTSTR lpszTemplateName, CWnd* pParent =NULL);
// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	//##ModelId=3ECE52EC0046
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAboutDlg)
	//##ModelId=3ECE52EC005A
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ABOUTDLG_H__50B5EF88_106C_11D4_AD28_00606767A9D2__INCLUDED_)
