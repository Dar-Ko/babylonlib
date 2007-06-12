/*$Workfile: TsMfcApp.cpp$: implementation file
  $Revision: 7$ $Date: 2007-06-12 17:16:12$
  $Author: Darko Kolakovic$

  Defines the class behaviors for the application.

  Copyright: CommonSoft Inc.
  Jan. 2k Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#include "TsMfcApp.h"

#include "TsMfcFrame.h"
#include "TsMfcDoc.h"
#include "TsMfcView.h"

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

/*Note: when you build a Windows project created from the scratch, you may 
  get the following error message from linker:
      error LNK2001: unresolved external symbol _main
  To solve the problem, insure that target subsystem is not console, but
  windows. Click the Link tab and under Project Options, change 
    /subsystem:console to /subsystem:windows.
  Also replace preprocessor definition _CONSOLE with _WINDOWS. Click at 
  the C/C++ tab  and change preprocessor definitions.
 */
#ifdef _CONSOLE
  #error This is a Windows application; subsystem:console is prohibited
#endif
#ifndef _WINDOWS
  #error This is a Windows application; subsystem:windows is required
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

CTestApp::~CTestApp()
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
                                      RUNTIME_CLASS(CTestMainFrame), // main SDI frame window
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
  Returns FALSE if testing is unsuccesful.
 */
bool CTestApp::DoTestInit()
{
return false;
}

/////////////////////////////////////////////////////////////////////////////
// CTestApp commands


//::OnAppAbout()----------------------------------------------------------------
#include "TsMfcAbout.h"   //CTestAboutDlg class
/*Open About dialog box
 */
void CTestApp::OnAppAbout()
{
CTestAboutDlg aboutDlg;
aboutDlg.DoModal();
}
