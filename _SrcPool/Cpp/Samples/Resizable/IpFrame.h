// IpFrame.h : interface of the CInPlaceFrame class
//

#if !defined(AFX_IPFRAME_H__D536C679_0182_11D4_AD28_00606767A9D2__INCLUDED_)
#define AFX_IPFRAME_H__D536C679_0182_11D4_AD28_00606767A9D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//##ModelId=3ECE52EB012B
class CInPlaceFrame : public COleIPFrameWnd
{
	DECLARE_DYNCREATE(CInPlaceFrame)
public:
	//##ModelId=3ECE52EB013F
	CInPlaceFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInPlaceFrame)
	public:
	//##ModelId=3ECE52EB0149
	virtual BOOL OnCreateControlBars(CFrameWnd* pWndFrame, CFrameWnd* pWndDoc);
	//##ModelId=3ECE52EB015D
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=3ECE52EB0171
	virtual ~CInPlaceFrame();
#ifdef _DEBUG
	//##ModelId=3ECE52EB0173
	virtual void AssertValid() const;
	//##ModelId=3ECE52EB017C
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//##ModelId=3ECE52EB0190
	CToolBar    m_wndToolBar;
	//##ModelId=3ECE52EB01AE
	COleDropTarget	m_dropTarget;
	//##ModelId=3ECE52EB01CC
	COleResizeBar   m_wndResizeBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CInPlaceFrame)
	//##ModelId=3ECE52EB01DF
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPFRAME_H__D536C679_0182_11D4_AD28_00606767A9D2__INCLUDED_)
