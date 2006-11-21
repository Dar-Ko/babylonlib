/*$Workfile: TestDialogApp.cpp$: implementation file
  $Revision: 1$ $Date: 2006-09-27 22:52:56$
  $Author: Darko$

  Defines the class behaviors for the application.
  Copyright: CommonSoft Inc.
  2003-08-25 Darko Kolakovic
 */

#include "stdafx.h"
#include "TestDialogApp.h"     //TestDialogApp class

#ifdef _DEBUG
  #define new DEBUG_NEW
#endif

// The one and only TestDialogApp object
TestDialogApp theApp;

///////////////////////////////////////////////////////////////////////////////
// TestDialogApp

BEGIN_MESSAGE_MAP(TestDialogApp, CWinApp)
  ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// TestDialogApp construction

//-----------------------------------------------------------------------------
/*
 */
 TestDialogApp::TestDialogApp() 
{
  // TODO: add construction code here,
  // Place all significant initialization in InitInstance
}
#include "TestButtonDlg.h"  //CTestButtonDlg class

//-----------------------------------------------------------------------------
/*TestDialogApp initialization
 */
BOOL TestDialogApp::InitInstance()
{
TRACE(_T("TestDialogApp::InitInstance()\n"));
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
SetRegistryKey(_T("CommonSoftInc"));

if(SetMainWnd())
  {
  INT_PTR nResponse = ((CDialog*)m_pMainWnd)->DoModal();
  if (nResponse == IDOK)
    {
      TRACE(_T("  Dialog closes with IDOK=%d.\n"), IDOK);
      // TODO: Place code here to handle when the dialog is
      //  dismissed with OK
    }
  else if (nResponse == IDCANCEL)
    {
      TRACE(_T("  Dialog closes with IDCANCEL=%d.\n"), IDCANCEL);
      // TODO: Place code here to handle when the dialog is
      //  dismissed with Cancel
    }
  DestroyMainWnd();
  }
// Since the dialog has been closed, return FALSE so that we exit the
//  application, rather than start the application's message pump.
return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2006-09-27 22:52:56  Darko           
 * $
 *****************************************************************************/
