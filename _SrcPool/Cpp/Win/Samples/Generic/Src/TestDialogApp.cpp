/*$Workfile: TestDialogApp.cpp$: implementation file
  $Revision: 5$ $Date: 2005-05-03 01:43:42$
  $Author: Darko$

  Defines the class behaviors for the application.
  Copyright: CommonSoft Inc.
  2003-08-25 Darko Kolakovic
 */

#include "stdafx.h"
#include "resource.h"
#include "TestDialogApp.h"     //CTestDialogApp class
#include "Res/TestResource.h"

#ifdef _DEBUG
  #define new DEBUG_NEW
#endif

// The one and only CTestDialogApp object
CTestDialogApp theApp;

///////////////////////////////////////////////////////////////////////////////
// CTestDialogApp

BEGIN_MESSAGE_MAP(CTestDialogApp, CWinApp)
  ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTestDialogApp construction

//-----------------------------------------------------------------------------
/*
 */
 CTestDialogApp::CTestDialogApp()
{
  // TODO: add construction code here,
  // Place all significant initialization in InitInstance
}

//-----------------------------------------------------------------------------
/*CTestDialogApp initialization
 */
BOOL CTestDialogApp::InitInstance()
{
TRACE(_T("CTestDialogApp::InitInstance()\n"));
// InitCommonControls() is required on Windows XP if an application
// manifest specifies use of ComCtl32.dll version 6 or later to enable
// visual styles. Otherwise, any window creation will fail.
InitCommonControls();

CWinApp::InitInstance();

AfxEnableControlContainer();

// Standard initialization
// If you are not using these features and wish to reduce the size
// of your final executable, you should remove from the following
// the specific initialization routines you do not need
// Change the registry key under which our settings are stored
// TODO: You should modify this string to be something appropriate
// such as the name of your company or organization

#if _MFC_VER < 0x0500
  #ifdef _AFXDLL
    Enable3dControls();     //Call this when using MFC in a shared DLL
  #else
    Enable3dControlsStatic();//Call this when linking to MFC statically
  #endif
#endif

SetRegistryKey(_T("CommonSoftInc"));

if(SetMainWnd())
  {
  //Store pointer to the dialog for post processing
  CWnd* pDlgTemp = m_pMainWnd;
  /*Note: In our dialog-based application, the main window is a modal dialog
    box, that closes itself with one of exit buttons.
    In an MFC application when the main window associated with the application
    is about to be destroyed, PostQuitMessage() is called indicating to Windows
    that a thread has made a request to terminate. Then a WM_QUIT message is
    posted to the application, the main window is destroyed and m_pMainWnd is
    set to NULL.
   */
  INT_PTR nResponse;
  if( !m_pMainWnd->IsKindOf(RUNTIME_CLASS( CDialog)) )
    nResponse = -1;
  else
    {
    //Invoke the modal dialog box and return the dialog-box result when done.
    nResponse = ((CDialog*)m_pMainWnd)->DoModal();
    }

  switch ( nResponse )
    {
    case -1:
      AfxMessageBox(IDS_DLGBOXEXITERR2); //Dialog box could not be created!
      break;
    case IDABORT:
      // TODO: Place code here to handle when the dialog is
      //  dismissed with Abort
      break;
    case IDOK:
      TRACE(_T("  Dialog closes with IDOK=%d.\n"), IDOK);
      // TODO: Place code here to handle when the dialog is
      //  dismissed with OK
      break;
    case IDCANCEL:
      TRACE(_T("  Dialog closes with IDCANCEL=%d.\n"), IDCANCEL);
      // TODO: Place code here to handle when the dialog is
      //  dismissed with Cancel
      break;
    default:
      // Unhandled dialog closing.
      AfxMessageBox(IDS_DLGBOXEXITERR1); //Unhandled Dialog box exit code!
      break;
    };

  DestroyMainWnd(pDlgTemp);
  }

// Since the dialog has been closed, return FALSE so that we exit the
//  application, rather than start the application's message pump.
return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  5    Biblioteka1.4         2005-05-03 01:43:42  Darko
 *  4    Biblioteka1.3         2005-05-02 17:09:46  Darko Kolakovic Changed class
 *       name
 *  3    Biblioteka1.2         2004-10-01 22:22:46  Darko           stdafx.h
 *  2    Biblioteka1.1         2003-08-27 18:12:04  Darko           renamed class
 *  1    Biblioteka1.0         2003-08-26 01:37:13  Darko
 * $
 *****************************************************************************/
