// ResizeDoc.cpp : implementation of the CResizeDoc class
//

#include "stdafx.h"
#include "Resize.h"

#include "ResizeDoc.h"
#include "CntrItem.h"
#include "SrvrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResizeDoc

IMPLEMENT_DYNCREATE(CResizeDoc, COleServerDoc)

BEGIN_MESSAGE_MAP(CResizeDoc, COleServerDoc)
	//{{AFX_MSG_MAP(CResizeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, COleServerDoc::OnUpdatePasteMenu)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE_LINK, COleServerDoc::OnUpdatePasteLinkMenu)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_CONVERT, COleServerDoc::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_OLE_EDIT_CONVERT, COleServerDoc::OnEditConvert)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, COleServerDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, COleServerDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, COleServerDoc::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CResizeDoc, COleServerDoc)
	//{{AFX_DISPATCH_MAP(CResizeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IResize to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {D536C664-0182-11D4-AD28-00606767A9D2}
static const IID IID_IResize =
{ 0xd536c664, 0x182, 0x11d4, { 0xad, 0x28, 0x0, 0x60, 0x67, 0x67, 0xa9, 0xd2 } };

BEGIN_INTERFACE_MAP(CResizeDoc, COleServerDoc)
	INTERFACE_PART(CResizeDoc, IID_IResize, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResizeDoc construction/destruction

//##ModelId=3ECE52E5035E
CResizeDoc::CResizeDoc()
{
	// Use OLE compound files
	EnableCompoundFile();

	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

//##ModelId=3ECE52E50399
CResizeDoc::~CResizeDoc()
{
	AfxOleUnlockApp();
}

//##ModelId=3ECE52E5037C
BOOL CResizeDoc::OnNewDocument()
{
	if (!COleServerDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CResizeDoc server implementation

//##ModelId=3ECE52E50371
COleServerItem* CResizeDoc::OnGetEmbeddedItem()
{
	// OnGetEmbeddedItem is called by the framework to get the COleServerItem
	//  that is associated with the document.  It is only called when necessary.

	CResizeSrvrItem* pItem = new CResizeSrvrItem(this);
	ASSERT_VALID(pItem);
	return pItem;
}



/////////////////////////////////////////////////////////////////////////////
// CResizeDoc serialization

//##ModelId=3ECE52E50386
void CResizeDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	// Calling the base class COleServerDoc enables serialization
	//  of the container document's COleClientItem objects.
	COleServerDoc::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CResizeDoc diagnostics

#ifdef _DEBUG
//##ModelId=3ECE52E503A3
void CResizeDoc::AssertValid() const
{
	COleServerDoc::AssertValid();
}

//##ModelId=3ECE52E503AD
void CResizeDoc::Dump(CDumpContext& dc) const
{
	COleServerDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CResizeDoc commands
