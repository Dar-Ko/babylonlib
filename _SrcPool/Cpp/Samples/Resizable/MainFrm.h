// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__D536C66C_0182_11D4_AD28_00606767A9D2__INCLUDED_)
#define AFX_MAINFRM_H__D536C66C_0182_11D4_AD28_00606767A9D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

extern BOOL g_bStackedTabs; //Stacked or scrolled tabs
extern BOOL g_bWizardMode;
extern BOOL g_bSavePosition;

//##ModelId=3ECE52E70017
class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	//##ModelId=3ECE52E70035
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	//##ModelId=3ECE52E70036
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=3ECE52E70049
	virtual ~CMainFrame();
#ifdef _DEBUG
	//##ModelId=3ECE52E70053
	virtual void AssertValid() const;
	//##ModelId=3ECE52E7005D
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	//##ModelId=3ECE52E70072
	CStatusBar  m_wndStatusBar;
	//##ModelId=3ECE52E70086
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	//##ModelId=3ECE52E700A3
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//##ModelId=3ECE52E700B7
	afx_msg void OnClose();
	//##ModelId=3ECE52E700C1
	afx_msg void OnViewPropertySheet();
	//##ModelId=3ECE52E700CC
	afx_msg void OnWizard();
	//##ModelId=3ECE52E700DF
	afx_msg void OnScrollingTabs();
	//##ModelId=3ECE52E700F3
	afx_msg void OnUpdateScrollinTtabs(CCmdUI* pCmdUI);
	//##ModelId=3ECE52E70108
	afx_msg void OnUpdateWizard(CCmdUI* pCmdUI);
	//##ModelId=3ECE52E70125
	afx_msg void OnResizableDialogSavePosition();
	//##ModelId=3ECE52E7012F
	afx_msg void OnUpdateResizableDialogSavePosition(CCmdUI* pCmdUI);
	//##ModelId=3ECE52E70143
	afx_msg void OnResizableDialogProportional();
	//##ModelId=3ECE52E7014E
	afx_msg void OnWizard97();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__D536C66C_0182_11D4_AD28_00606767A9D2__INCLUDED_)
