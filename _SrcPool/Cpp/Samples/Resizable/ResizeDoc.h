// ResizeDoc.h : interface of the CResizeDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESIZEDOC_H__D536C670_0182_11D4_AD28_00606767A9D2__INCLUDED_)
#define AFX_RESIZEDOC_H__D536C670_0182_11D4_AD28_00606767A9D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CResizeSrvrItem;

//##ModelId=3ECE52E50349
class CResizeDoc : public COleServerDoc
{
protected: // create from serialization only
	//##ModelId=3ECE52E5035E
	CResizeDoc();
	DECLARE_DYNCREATE(CResizeDoc)

// Attributes
public:
	//##ModelId=3ECE52E50367
	CResizeSrvrItem* GetEmbeddedItem()
		{ return (CResizeSrvrItem*)COleServerDoc::GetEmbeddedItem(); }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResizeDoc)
	protected:
	//##ModelId=3ECE52E50371
	virtual COleServerItem* OnGetEmbeddedItem();
	public:
	//##ModelId=3ECE52E5037C
	virtual BOOL OnNewDocument();
	//##ModelId=3ECE52E50386
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=3ECE52E50399
	virtual ~CResizeDoc();
#ifdef _DEBUG
	//##ModelId=3ECE52E503A3
	virtual void AssertValid() const;
	//##ModelId=3ECE52E503AD
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CResizeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CResizeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESIZEDOC_H__D536C670_0182_11D4_AD28_00606767A9D2__INCLUDED_)
