// Resize.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Resize.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "IpFrame.h"
#include "ResizeDoc.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResizeApp

BEGIN_MESSAGE_MAP(CResizeApp, CWinApp)
	//{{AFX_MSG_MAP(CResizeApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResizeApp construction

//##ModelId=3ECE52E60001
CResizeApp::CResizeApp()
{
#ifdef _DEBUG
  extern void DumpOSVI();
#endif
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
#ifdef _DEBUG
  DumpOSVI(); //Dump the operating system version information
#endif
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CResizeApp object

CResizeApp theApp;

// This identifier was generated to be statistically unique for your app.
// You may change it if you prefer to choose a specific identifier.

// {D536C662-0182-11D4-AD28-00606767A9D2}
static const CLSID clsid =
{ 0xd536c662, 0x182, 0x11d4, { 0xad, 0x28, 0x0, 0x60, 0x67, 0x67, 0xa9, 0xd2 } };

/////////////////////////////////////////////////////////////////////////////
// CResizeApp initialization

//##ModelId=3ECE52E6000B
BOOL CResizeApp::InitInstance()
{
	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_RESIZETYPE,
		RUNTIME_CLASS(CResizeDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CLeftView));
	pDocTemplate->SetContainerInfo(IDR_RESIZETYPE_CNTR_IP);
	pDocTemplate->SetServerInfo(
		IDR_RESIZETYPE_SRVR_EMB, IDR_RESIZETYPE_SRVR_IP,
		RUNTIME_CLASS(CInPlaceFrame));
	AddDocTemplate(pDocTemplate);

	// Connect the COleTemplateServer to the document template.
	//  The COleTemplateServer creates new documents on behalf
	//  of requesting OLE containers by using information
	//  specified in the document template.
	m_server.ConnectTemplate(clsid, pDocTemplate, FALSE);

	// Register all OLE server factories as running.  This enables the
	//  OLE libraries to create objects from other applications.
	COleTemplateServer::RegisterAll();
		// Note: MDI applications register all server objects without regard
		//  to the /Embedding or /Automation on the command line.

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Check to see if launched as OLE server
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Application was run with /Embedding or /Automation.  Don't show the
		//  main window in this case.
		return TRUE;
	}

	// When a server application is launched stand-alone, it is a good idea
	//  to update the system registry in case it has been damaged.
	m_server.UpdateRegistry(OAT_INPLACE_SERVER);
	COleObjectFactory::UpdateRegistryAll();

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CResizeApp message handlers

#include "AboutDlg.h"
// App command to run the dialog
//##ModelId=3ECE52E60029
void CResizeApp::OnAppAbout()
{
CAboutDlg aboutDlg;//("Proportional");
aboutDlg.DoModal();
}
