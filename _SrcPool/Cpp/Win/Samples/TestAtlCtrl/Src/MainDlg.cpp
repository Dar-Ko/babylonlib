/*$RCSfile: MainDlg.cpp,v $: implementation file
  $Revision: 1.3 $ $Date: 2009/02/24 21:42:33 $
  $Author: ddarko $

  implementation of the CMainDlg class
  2008-12-15
 */

#include "stdatl.h"

#include "resource.h"
#include "TestAtlAboutDlg.h" //CAboutDlg class
#include "MainDlg.h"
//-----------------------------------------------------------------------------
/*Translates window messages before they are dispatched to the TranslateMessage
  and DispatchMessage Windows functions.

  Returns TRUE if the message was translated and should not be dispatched or
  FALSE if the message was not translated and should be dispatched.
 */
BOOL CMainDlg::PreTranslateMessage(MSG* pMsg //[in] a MSG structure that 
                                             //contains the message to process.
                                  )
{
return CWindow::IsDialogMessage(pMsg);
}

//-----------------------------------------------------------------------------
/*OnIdle is called in the default message loop when the application's message 
  queue is empty. The WM_ENTERIDLE message is sent to the owner window of a modal
  dialog box or menu that is entering an idle state. A modal dialog box or menu
  enters an idle state when no messages are waiting in its queue after it has
  processed one or more previous messages.
  For dialogs with style DS_NOIDLEMSG = 0x100, WM_ENTERIDLE message will not be
  sent.
  Override this member function to perform idle-time processing.
  
  Note: Do not perform lengthy tasks during OnIdle because your application 
  cannot process user input until OnIdle returns.

  Returns FALSE if the message is processed, TRUE if message is not handled. 

 */
BOOL CMainDlg::OnIdle()
{
#ifdef _DBG_VERBOSE
  ATLTRACE(_T("CMainDlg::OnIdle()\n"));
#endif
UIUpdateChildWindows(); //Update embedded controls
return FALSE;
}


//-----------------------------------------------------------------------------
/*This method is called in response to the WM_INITDIALOG message, sent to 
  the dialog box during the Create, CreateIndirect, or DoModal calls, which 
  occur immediately before the dialog box is displayed.

  Override this method if you want to perform special processing when the dialog 
  box is initialized. In the overridden version, first call the base class 
  OnInitDialog() but ignore its return value. You will typically return TRUE 
  from your overridden method.

  Returns TRUE to set the input focus to the default location, which is the first
  control in the dialog box. Return FALSE if this method has explicitly set the
  input focus to one of the controls in the dialog box.
 */
LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/,
                               WPARAM /*wParam*/,
                               LPARAM /*lParam*/,
                               BOOL& /*bHandled*/
                               )
{
ATLTRACE(_T("CMainDlg::OnInitDialog()\n"));
// center the dialog on the screen
CenterWindow();

// set icons
HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(),
                                 MAKEINTRESOURCE(IDR_MAINFRAME),
                                 IMAGE_ICON,
                                 ::GetSystemMetrics(SM_CXICON),
                                 ::GetSystemMetrics(SM_CYICON),
                                 LR_DEFAULTCOLOR);
SetIcon(hIcon, TRUE);
HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(),
                                      MAKEINTRESOURCE(IDR_MAINFRAME),
                                      IMAGE_ICON,
                                      ::GetSystemMetrics(SM_CXSMICON),
                                      ::GetSystemMetrics(SM_CYSMICON),
                                      LR_DEFAULTCOLOR);
SetIcon(hIconSmall, FALSE);

/*Allow the WM_PARENTNOTIFY messages for the Cancel button, if one exist.
  See also: MSDN KB142481: Special Case 2;
 */
if(GetDlgItem(IDCANCEL).IsWindow())
  GetDlgItem(IDCANCEL).ModifyStyleEx(WS_EX_NOPARENTNOTIFY,0);

//Register object for message filtering and idle updates
CMessageLoop* pLoop = _Module.GetMessageLoop();
ATLASSERT(pLoop != NULL);
pLoop->AddMessageFilter(this);
pLoop->AddIdleHandler(this);

UIAddChildWindowContainer(m_hWnd); //Enable updating of child windows

//Attach and populate the list view
//DDX_Control_Handle(IDC_LISTTEST, m_ctrlListView, FALSE);
m_ctrlListView = GetDlgItem(IDC_LISTTEST);
m_ctrlListView.SetExtendedListViewStyle(LVS_EX_INFOTIP, LVS_EX_INFOTIP);
ATLVERIFY(m_ctrlListView.InsertColumn(0, _T("Column 1"), LVCFMT_LEFT, 150, -1) >= 0);
ATLVERIFY(m_ctrlListView.InsertColumn(1, _T("Column 2"), LVCFMT_LEFT, 120, 1) >= 0);
ATLVERIFY(m_ctrlListView.InsertItem(0, LPSTR_TEXTCALLBACK) >= 0);
ATLVERIFY(m_ctrlListView.InsertItem(1, LPSTR_TEXTCALLBACK) >= 0);
ATLVERIFY(m_ctrlListView.InsertItem(2, LPSTR_TEXTCALLBACK) >= 0);

//DoDataExchange(FALSE);  //Attach controls and intialize child windows captions
return TRUE;
}

//-----------------------------------------------------------------------------
/*The framework calls this member function when the CWnd object is destroyed 
  and removed from the screen.
 */
LRESULT CMainDlg::OnDestroy(UINT /*uMsg*/,
                            WPARAM /*wParam*/,
                            LPARAM /*lParam*/,
                            BOOL& /*bHandled*/
                            )
{
ATLTRACE(_T("CMainDlg::OnDestroy()\n"));
// unregister message filtering and idle updates
CMessageLoop* pLoop = _Module.GetMessageLoop();
ATLASSERT(pLoop != NULL);
pLoop->RemoveMessageFilter(this);
pLoop->RemoveIdleHandler(this);

return S_OK;
}

//-----------------------------------------------------------------------------
/*The framework calls this member function to handle ID_APP_ABOUT message 
  generated when the user clicks 'About...' menu item.
  This implemetation creates a modal dialog box displaying basic information
  about this application main module.
 */
LRESULT CMainDlg::OnAppAbout(WORD /*wNotifyCode*/,
                             WORD /*wID*/,
                             HWND /*hWndCtl*/,
                             BOOL& /*bHandled*/
                             )
{
ATLTRACE(_T("CMainDlg::OnAppAbout()\n"));

CAboutDlg dlg;
dlg.DoModal();
return S_OK;
}

//-----------------------------------------------------------------------------
/*The framework calls this member function to handle IDOK Command generated
  when the user clicks the OK button. Override this method to perform actions
  when the OK button is activated. If the dialog box includes automatic data
  validation and exchange, the default implementation of this method validates
  the dialog box data and updates the appropriate variables in your application.
 */
LRESULT CMainDlg::OnOK(WORD /*wNotifyCode*/,
                       WORD wID,
                       HWND /*hWndCtl*/,
                       BOOL& /*bHandled*/
                      )
{
ATLTRACE(_T("CMainDlg::OnOK()\n"));
//Note: Any form validation is done when a control lost focus.

// TODO: Add validation code
CloseDialog(wID);
return S_OK;
}

//-----------------------------------------------------------------------------
/*The framework calls this member function to handle IDCANCEL command generated
  when the user clicks the Cancel button, menu item or presses the ESC key in 
  a modal or modeless dialog box.
 */
LRESULT CMainDlg::OnCancel(WORD /*wNotifyCode*/,
                           WORD wID,
                           HWND /*hWndCtl*/,
                           BOOL& /*bHandled*/
                           )
{
ATLTRACE(_T("CMainDlg::OnCancel()\n"));

CloseDialog(wID);
return S_OK;
}

//-----------------------------------------------------------------------------
/*Closes the modeless dialog.
  The method destroys the window associated with the dialog object and sets
  m_hWnd to NULL and requests the system to terminate (quit) by posting
  a WM_QUIT message.
 */
void CMainDlg::CloseDialog(int nVal //[in] an application exit code, used as
                           //the wParam parameter of the WM_QUIT message.
                          )
{
ATLTRACE(_T("CMainDlg::CloseDialog(%d)\n"), nVal);

DestroyWindow();
::PostQuitMessage(nVal);
}
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: MainDlg.cpp,v $
 * Revision 1.3  2009/02/24 21:42:33  ddarko
 * Test common control notification messages
 *
 ******************************************************************************/
