/*$Workfile: TestButtonApp.cpp$: implementation file
  $Revision: 5$ $Date: 2005-05-02 17:08:27$
  $Author: Darko Kolakovic$

  Initializes main window object.
  Copyright: CommonSoft Inc.
  2003-08-25 Darko Kolakovic
 */
// Group=Examples Windows

#include "stdafx.h"
#include "TestDialogApp.h"  //CTestDialogApp class
#include "TestButtonDlg.h"  //CSTestButtonDlg class
#include "KProgCst.inl"     //DELETE_POBJECT

#ifdef _DEBUG
  #define new DEBUG_NEW
#endif

  //Contains pointer to newly created test dialog
static CTestButtonDlg* s_pTestMainDlg = NULL;

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
s_pTestMainDlg = new CTestButtonDlg();
m_pMainWnd = (CWnd*) s_pTestMainDlg;

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
UNUSED(pObject);
DELETE_POBJECT(s_pTestMainDlg);
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  3    Biblioteka1.2         2004-10-01 22:22:42  Darko           stdafx.h
 *  2    Biblioteka1.1         2003-08-27 18:11:58  Darko           renamed class
 *  1    Biblioteka1.0         2003-08-26 01:36:10  Darko
 * $
 *****************************************************************************/
