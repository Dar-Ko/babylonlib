// ResizeView.h : interface of the CResizeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESIZEVIEW_H__D536C672_0182_11D4_AD28_00606767A9D2__INCLUDED_)
#define AFX_RESIZEVIEW_H__D536C672_0182_11D4_AD28_00606767A9D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CResizeCntrItem;

//##ModelId=3ECE52E501AE
class CResizeView : public CListView
{
protected: // create from serialization only
	//##ModelId=3ECE52E501C2
	CResizeView();
	DECLARE_DYNCREATE(CResizeView)

// Attributes
public:
	//##ModelId=3ECE52E501CC
	CResizeDoc* GetDocument();
	// m_pSelection holds the selection to the current CResizeCntrItem.
	// For many applications, such a member variable isn't adequate to
	//  represent a selection, such as a multiple selection or a selection
	//  of objects that are not CResizeCntrItem objects.  This selection
	//  mechanism is provided just to help you get started.

	// TODO: replace this selection mechanism with one appropriate to your app.
	//##ModelId=3ECE52E501E1
	CResizeCntrItem* m_pSelection;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResizeView)
	public:
	//##ModelId=3ECE52E501EA
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	//##ModelId=3ECE52E501FE
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//##ModelId=3ECE52E50209
	virtual void OnInitialUpdate(); // called first time after construct
	//##ModelId=3ECE52E5021C
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//##ModelId=3ECE52E50230
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	//##ModelId=3ECE52E5024F
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//##ModelId=3ECE52E50263
	virtual BOOL IsSelected(const CObject* pDocItem) const;// Container support
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=3ECE52E50277
	virtual ~CResizeView();
#ifdef _DEBUG
	//##ModelId=3ECE52E50281
	virtual void AssertValid() const;
	//##ModelId=3ECE52E5028B
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CResizeView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//##ModelId=3ECE52E50296
	afx_msg void OnDestroy();
	//##ModelId=3ECE52E502A9
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//##ModelId=3ECE52E502BD
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//##ModelId=3ECE52E502DB
	afx_msg void OnInsertObject();
	//##ModelId=3ECE52E502E6
	afx_msg void OnCancelEditCntr();
	//##ModelId=3ECE52E502F9
	afx_msg void OnCancelEditSrvr();
	//}}AFX_MSG
	//##ModelId=3ECE52E50303
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ResizeView.cpp
inline CResizeDoc* CResizeView::GetDocument()
   { return (CResizeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESIZEVIEW_H__D536C672_0182_11D4_AD28_00606767A9D2__INCLUDED_)
