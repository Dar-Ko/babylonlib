// Test.cpp : Defines the class behaviors for the application.
//
// Darko Kolakovic
// Jan. 2k

#include "StdAfx.h"
#include "TestApp.h"

#include "MainFrm.h"
#include "TestDoc.h"
#include "TestView.h"

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

/* Note: Visual C++ version 4.1 with MFC 4.0 is last version that supports 
         building Win32s applications.
 */
#if _MSC_VER == 1000
  #pragma message ("Microsoft Visual C++ 4.0")
  #if _MFC_VER == 0x400
    #pragma message ("MFC 4.0")
    #pragma message ("Support for Win32s included")
  #endif
#endif

#if _MSC_VER == 1200
  #pragma message ("Microsoft Visual C++ 6.0")
  #if _MFC_VER == 0x600
    #pragma message ("MFC 4.2")
  #endif
#endif


/////////////////////////////////////////////////////////////////////////////
// CTestApp

BEGIN_MESSAGE_MAP(CTestApp, CWinApp)
	//{{AFX_MSG_MAP(CTestApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Standard file based document commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

//::CTestApp()-------------------------------------------------------------
/*CTestApp construction
 */
CTestApp::CTestApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTestApp object
CTestApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTestApp initialization

//::InitInstance()-------------------------------------------------------------
/*Instance initialization that runs each time a copy of the program runs, 
  including the first time. The framework’s implementation of WinMain calls
  this function.

  Note: The following Win32 features are not currently supported for Win32s

        MAPI 
        RPC 
        Console APIs 
        Unicode APIs (Win32s does support Code Page/Unicode translation APIs) 
        Security APIs 
        Comm APIs 
        Asynchronous File I/O 
        Threads 
        Paths (graphics object) 
        Enhanced Metafiles 
        Bezier curves 
 */
BOOL CTestApp::InitInstance()
{
// Standard initialization

LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

// Register document templates

CSingleDocTemplate* pDocTemplate;
pDocTemplate = new CSingleDocTemplate(IDR_MAINFRAME,
	                                    RUNTIME_CLASS(CTestDoc),
	                                    RUNTIME_CLASS(CMainFrame), // main SDI frame window
	                                    RUNTIME_CLASS(CTestView));
AddDocTemplate(pDocTemplate);
EnableShellOpen();                        //Enable DDE Execute open
// Parse command line for standard shell commands, DDE, file open
CCommandLineInfo cmdInfo;
ParseCommandLine(cmdInfo);

// Dispatch commands specified on the command line
// Create new document, main frame and view object, initialize m_pMainWnd 
if (!ProcessShellCommand(cmdInfo))
	return FALSE;
  //Execute initial testing
if (!DoTestInit())
  return FALSE;
return TRUE;
}


///////////////////////////////////////////////////////////////////////////////
// Operations

//::DoTestInit()---------------------------------------------------------------
/*Execute a test during instance initialization.
  Returns FALSE if testing is unsuccesfull.
 */
BOOL CTestApp::DoTestInit()
{
  //Acquire file version information
return TestVerInfo();
}

/////////////////////////////////////////////////////////////////////////////
// CTestApp commands


//::OnAppAbout()----------------------------------------------------------------
#include "TestAbout.h"   //CAboutDlg class
/*Open About dialog box
 */
void CTestApp::OnAppAbout()
{
CAboutDlg aboutDlg;
aboutDlg.DoModal();
}
