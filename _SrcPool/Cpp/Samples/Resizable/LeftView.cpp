// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "Resize.h"

#include "ResizeDoc.h"
#include "MyPropertySheet.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	//{{AFX_MSG_MAP(CLeftView)
	ON_WM_SIZE()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView construction/destruction

//##ModelId=3ECE52E701BB
CLeftView::CLeftView()
{
	// TODO: add construction code here

}

//##ModelId=3ECE52E70265
CLeftView::~CLeftView()
{
}

//##ModelId=3ECE52E701F8
BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
return CTreeView::PreCreateWindow(cs);
}



/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing

//##ModelId=3ECE52E701ED
void CLeftView::OnDraw(CDC* pDC)
{
	CResizeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


/////////////////////////////////////////////////////////////////////////////
// CLeftView printing

//##ModelId=3ECE52E7020B
BOOL CLeftView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

//##ModelId=3ECE52E7021F
void CLeftView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

//##ModelId=3ECE52E7023D
void CLeftView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

//##ModelId=3ECE52E70252
void CLeftView::OnInitialUpdate()
{
CTreeView::OnInitialUpdate();
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView diagnostics

#ifdef _DEBUG
//##ModelId=3ECE52E70267
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

//##ModelId=3ECE52E70270
void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

//##ModelId=3ECE52E701E3
CResizeDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CResizeDoc)));
	return (CResizeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers

//##ModelId=3ECE52E70283
void CLeftView::OnSize(UINT nType, int cx, int cy) 
{
CTreeView::OnSize(nType, cx, cy);
	
if (nType != SIZE_MINIMIZED && 	::IsWindow(m_sheetProperty.GetSafeHwnd()))
	{
	m_sheetProperty.RecalcLayout(this);
	}
	
}

//##ModelId=3ECE52E702A2
int CLeftView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
extern BOOL g_bStackedTabs;
extern BOOL g_bWizardMode;

  //Close and open the active document view to show new propert sheet mode
if(g_bWizardMode)
  m_sheetProperty.SetWizardMode();

m_sheetProperty.EnableStackedTabs(g_bStackedTabs); //Does not have any effect in the Wizard mode

m_sheetProperty.Create((CWnd*)this,
                         WS_CHILD |
                         WS_VISIBLE,
                         WS_EX_TRANSPARENT);
CRect rect;
m_sheetProperty.GetWindowRect(rect);

//lpCreateStruct->cx = rect.Width();
//lpCreateStruct->cy = rect.Height();

	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	
	return 0;
}

