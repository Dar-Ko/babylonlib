// ChildFrm.h : interface of the CChildFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDFRM_H__D536C66E_0182_11D4_AD28_00606767A9D2__INCLUDED_)
#define AFX_CHILDFRM_H__D536C66E_0182_11D4_AD28_00606767A9D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CResizeView;

//##ModelId=3ECE52EB0329
class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	//##ModelId=3ECE52EB0347
	CChildFrame();

// Attributes
protected:
	//##ModelId=3ECE52EB0353
	CSplitterWnd m_wndSplitter;
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFrame)
	public:
	//##ModelId=3ECE52EB0366
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//##ModelId=3ECE52EB0384
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=3ECE52EB038F
	virtual ~CChildFrame();
#ifdef _DEBUG
	//##ModelId=3ECE52EB0399
	virtual void AssertValid() const;
	//##ModelId=3ECE52EB03A2
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//##ModelId=3ECE52EB03AD
	CResizeView* GetRightPane();
// Generated message map functions
protected:
	//{{AFX_MSG(CChildFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	//##ModelId=3ECE52EB03C0
	afx_msg void OnUpdateViewStyles(CCmdUI* pCmdUI);
	//##ModelId=3ECE52EB03D4
	afx_msg void OnViewStyle(UINT nCommandID);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFRM_H__D536C66E_0182_11D4_AD28_00606767A9D2__INCLUDED_)
