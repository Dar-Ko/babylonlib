// LeftView.h : interface of the CLeftView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEFTVIEW_H__D536C674_0182_11D4_AD28_00606767A9D2__INCLUDED_)
#define AFX_LEFTVIEW_H__D536C674_0182_11D4_AD28_00606767A9D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyPropertySheet.h"
class CResizeDoc;

//##ModelId=3ECE52E701A7
class CLeftView : public CTreeView
{
protected: // create from serialization only
	//##ModelId=3ECE52E701BB
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

	//##ModelId=3ECE52E701D0
  MyPropertySheet m_sheetProperty;

// Attributes
public:
	//##ModelId=3ECE52E701E3
	CResizeDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeftView)
	public:
	//##ModelId=3ECE52E701ED
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	//##ModelId=3ECE52E701F8
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//##ModelId=3ECE52E7020B
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//##ModelId=3ECE52E7021F
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	//##ModelId=3ECE52E7023D
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//##ModelId=3ECE52E70252
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=3ECE52E70265
	virtual ~CLeftView();
#ifdef _DEBUG
	//##ModelId=3ECE52E70267
	virtual void AssertValid() const;
	//##ModelId=3ECE52E70270
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLeftView)
	//##ModelId=3ECE52E70283
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//##ModelId=3ECE52E702A2
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LeftView.cpp
inline CResizeDoc* CLeftView::GetDocument()
   { return (CResizeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEFTVIEW_H__D536C674_0182_11D4_AD28_00606767A9D2__INCLUDED_)
