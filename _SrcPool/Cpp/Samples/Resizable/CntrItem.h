// CntrItem.h : interface of the CResizeCntrItem class
//

#if !defined(AFX_CNTRITEM_H__D536C67B_0182_11D4_AD28_00606767A9D2__INCLUDED_)
#define AFX_CNTRITEM_H__D536C67B_0182_11D4_AD28_00606767A9D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CResizeDoc;
class CResizeView;

//##ModelId=3ECE52EB022F
class CResizeCntrItem : public COleClientItem
{
	DECLARE_SERIAL(CResizeCntrItem)

// Constructors
public:
	//##ModelId=3ECE52EB024D
	CResizeCntrItem(CResizeDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	//##ModelId=3ECE52EB0257
	CResizeDoc* GetDocument()
		{ return (CResizeDoc*)COleClientItem::GetDocument(); }
	//##ModelId=3ECE52EB0261
	CResizeView* GetActiveView()
		{ return (CResizeView*)COleClientItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResizeCntrItem)
	public:
	//##ModelId=3ECE52EB0262
	virtual void OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam);
	//##ModelId=3ECE52EB027F
	virtual void OnActivate();
	protected:
	//##ModelId=3ECE52EB0289
	virtual void OnGetItemPosition(CRect& rPosition);
	//##ModelId=3ECE52EB029D
	virtual void OnDeactivateUI(BOOL bUndoable);
	//##ModelId=3ECE52EB02B1
	virtual BOOL OnChangeItemPosition(const CRect& rectPos);
	//##ModelId=3ECE52EB02C5
	virtual BOOL CanActivate();
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=3ECE52EB02CF
	~CResizeCntrItem();
#ifdef _DEBUG
	//##ModelId=3ECE52EB02D9
	virtual void AssertValid() const;
	//##ModelId=3ECE52EB02DB
	virtual void Dump(CDumpContext& dc) const;
#endif
	//##ModelId=3ECE52EB02ED
	virtual void Serialize(CArchive& ar);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__D536C67B_0182_11D4_AD28_00606767A9D2__INCLUDED_)
