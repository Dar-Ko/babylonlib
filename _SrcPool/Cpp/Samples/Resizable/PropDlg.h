#if !defined(AFX_PROPDLG_H__E21077FC_1146_11D4_AD28_00606767A9D2__INCLUDED_)
#define AFX_PROPDLG_H__E21077FC_1146_11D4_AD28_00606767A9D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropDlg.h : header file
//

#include "KDlgRsiz.h" //CDialogResizable class

/////////////////////////////////////////////////////////////////////////////
// CPropDlg dialog

//##ModelId=3ECE52E60047
class CPropDlg : public CDialogResizable
{
// Construction
public:
	//##ModelId=3ECE52E60065
  CPropDlg(LPCTSTR lpszTemplateName, CWnd* pParent =NULL);

// Dialog Data
	//{{AFX_DATA(CPropDlg)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropDlg)
	protected:
	//##ModelId=3ECE52E60070
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPropDlg)
	//##ModelId=3ECE52E60083
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPDLG_H__E21077FC_1146_11D4_AD28_00606767A9D2__INCLUDED_)
