// SrvrItem.h : interface of the CResizeSrvrItem class
//

#if !defined(AFX_SRVRITEM_H__D536C677_0182_11D4_AD28_00606767A9D2__INCLUDED_)
#define AFX_SRVRITEM_H__D536C677_0182_11D4_AD28_00606767A9D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//##ModelId=3ECE52E50097
class CResizeSrvrItem : public COleServerItem
{
	DECLARE_DYNAMIC(CResizeSrvrItem)

// Constructors
public:
	//##ModelId=3ECE52E500AA
	CResizeSrvrItem(CResizeDoc* pContainerDoc);

// Attributes
	//##ModelId=3ECE52E500B5
	CResizeDoc* GetDocument() const
		{ return (CResizeDoc*)COleServerItem::GetDocument(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResizeSrvrItem)
	public:
	//##ModelId=3ECE52E500BF
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	//##ModelId=3ECE52E500D3
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=3ECE52E500E7
	~CResizeSrvrItem();
#ifdef _DEBUG
	//##ModelId=3ECE52E500F0
	virtual void AssertValid() const;
	//##ModelId=3ECE52E500FA
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//##ModelId=3ECE52E50105
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRVRITEM_H__D536C677_0182_11D4_AD28_00606767A9D2__INCLUDED_)
