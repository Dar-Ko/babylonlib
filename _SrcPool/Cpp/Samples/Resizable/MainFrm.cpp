// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Resize.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_COMMAND(IDM_VIEWPROPERTYSHEET, OnViewPropertySheet)
	ON_COMMAND(ID_WIZARD, OnWizard)
	ON_COMMAND(ID_SCROLLINGTABS, OnScrollingTabs)
	ON_UPDATE_COMMAND_UI(ID_SCROLLINGTABS, OnUpdateScrollinTtabs)
	ON_UPDATE_COMMAND_UI(ID_WIZARD, OnUpdateWizard)
	ON_COMMAND(ID_RESIZABLEDIALOG_SAVEPOSITION, OnResizableDialogSavePosition)
	ON_UPDATE_COMMAND_UI(ID_RESIZABLEDIALOG_SAVEPOSITION, OnUpdateResizableDialogSavePosition)
	ON_COMMAND(ID_RESIZABLEDIALOG_PROPORTIONAL, OnResizableDialogProportional)
	ON_COMMAND(ID_WIZARD97, OnWizard97)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

//##ModelId=3ECE52E70035
CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

//##ModelId=3ECE52E70049
CMainFrame::~CMainFrame()
{
}

//##ModelId=3ECE52E700A3
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
LoadBarState( _T("MainToolBarState") ); //Load toolbar position 25.3.2k D.K.
	return 0;
}

//##ModelId=3ECE52E70036
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
//##ModelId=3ECE52E70053
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

//##ModelId=3ECE52E7005D
void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


//##ModelId=3ECE52E700B7
void CMainFrame::OnClose() 
{
SaveBarState( _T("MainToolBarState") ); //Load toolbar position 25.3.2k D.K.	
	CMDIFrameWnd::OnClose();
}

//::OnViewPropertySheet------------------------------------------------------------------
#include "MyPropertySheet.h"  //MyPropertySheet class
/*
  Note: KB Q148304: VC++ 4.0-5.0 CPropertySheet::DoModal() causes first chance 
  exception in Windows 95. 
 */
//##ModelId=3ECE52E700C1
void CMainFrame::OnViewPropertySheet() 
{
MyPropertySheet sheet;
if(g_bWizardMode)
  sheet.SetWizardMode();

sheet.EnableStackedTabs(g_bStackedTabs); //Does not have any effect in the Wizard mode

sheet.DoModal();	
}


//::OnWizard------------------------------------------------------------------
/*Wizard property sheet
 */
//##ModelId=3ECE52E700CC
void CMainFrame::OnWizard() 
{
if(g_bWizardMode)
  g_bWizardMode = FALSE;
else
  g_bWizardMode = TRUE;
}

//##ModelId=3ECE52E700DF
void CMainFrame::OnScrollingTabs() 
{
if(g_bStackedTabs)
  g_bStackedTabs = FALSE;
else
  g_bStackedTabs = TRUE;
}

//##ModelId=3ECE52E700F3
void CMainFrame::OnUpdateScrollinTtabs(CCmdUI* pCmdUI) 
{
pCmdUI->SetCheck(!g_bStackedTabs);
}

//##ModelId=3ECE52E70108
void CMainFrame::OnUpdateWizard(CCmdUI* pCmdUI) 
{
pCmdUI->SetCheck(g_bWizardMode);
}

//##ModelId=3ECE52E70125
void CMainFrame::OnResizableDialogSavePosition() 
{
if(g_bSavePosition)
  g_bSavePosition = FALSE;
else
  g_bSavePosition = TRUE;
}

//##ModelId=3ECE52E7012F
void CMainFrame::OnUpdateResizableDialogSavePosition(CCmdUI* pCmdUI) 
{
pCmdUI->SetCheck(g_bSavePosition);
}

#include "PropDlg.h"
//##ModelId=3ECE52E70143
void CMainFrame::OnResizableDialogProportional() 
{
CPropDlg dlg("Proportional");
dlg.EnableSizingGrip();
dlg.EnablePlacement(g_bSavePosition);
dlg.DoModal();
}

//##ModelId=3ECE52E7014E
void CMainFrame::OnWizard97() 
{
MyPropertySheet sheet;
/*
if(g_bWizardMode)
  sheet.SetWizardMode();
*/
sheet.m_psh.dwFlags =        PSH_WIZARD97|PSH_WATERMARK|PSH_HEADER;
//sheet.m_psh.pszbmWatermark = MAKEINTRESOURCE(IDB_WATERMARK);
//sheet.m_psh.pszbmHeader =    MAKEINTRESOURCE(IDB_BITMAP1);


sheet.EnableStackedTabs(g_bStackedTabs); //Does not have any effect in the Wizard mode

sheet.DoModal();	
}
