/*$Workfile: TestStaticApp.cpp$: implementation file
  $Revision: 1$ $Date: 2005-05-02 17:04:45$
  $Author: Darko Kolakovic$

  Initializes main window object.
  Copyright: CommonSoft Inc.
  2002-01-16 Darko Kolakovic
 */
// Group=Examples Windows

#include "stdafx.h"
#include "TestDialogApp.h"  //CTestDialogApp class
#include "Resource.h"
#include "TestStaticDlg.h"  //CTestStaticDlg class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif



//-----------------------------------------------------------------------------
/*Creates a dialog and store a pointer to thread's main window object.
  Call this metohod as a part of TestDialogApp initialization.

  Returns: true if main window is not null object; otherwise returns false.

  See also: MSDN: Windows Flash and Disappear in Dialog-Based 
  Applications Q138681, m_pMainWnd
 */
bool CTestDialogApp::SetMainWnd()
{
TRACE(_T("CTestDialogApp::SetMainWnd()\n"));
m_pMainWnd = (CWnd*) new CTestStaticDlg();
return (m_pMainWnd != NULL);
}

//-----------------------------------------------------------------------------
/*Deletes a dialog created in SetMainWnd().
  Call this metohod as a part of TestDialogApp initialization.

  Note: In our dialog-based application, the main window is a modal dialog
  box, that closes itself with one of exit buttons.
  In an MFC application when the main window associated with the application
  is about to be destroyed, PostQuitMessage() is called indicating to Windows
  that a thread has made a request to terminate. Then a WM_QUIT message is 
  posted to the application, the main window is destroyed and m_pMainWnd is
  set to NULL. 
  
  See also: MSDN: Windows Flash and Disappear in Dialog-Based 
  Applications Q138681, m_pMainWnd
 */
void CTestDialogApp::DestroyMainWnd(CWnd* pObject //[in]= NULL pointer to 
                                                  //dialog object
                                   )
{
TRACE(_T("CTestDialogApp::DestroyMainWnd()\n"));
if (pObject != NULL)
  {
  ASSERT( pObject->IsKindOf(RUNTIME_CLASS( CTestStaticDlg )) );
  delete (CTestStaticDlg*)pObject;
  }
else if (m_pMainWnd != NULL) //Try with main window
  {
  ASSERT( m_pMainWnd->IsKindOf(RUNTIME_CLASS( CTestStaticDlg )) );
  delete (CTestStaticDlg*)m_pMainWnd;
  }
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2005-05-02 17:04:45  Darko Kolakovic 
 * $
 *****************************************************************************/
