/*$RCSfile: MainDlg.cpp,v $: implementation file
  $Revision: 1.6 $ $Date: 2009/05/11 14:05:47 $
  $Author: ddarko $

  implementation of the CMainDlg class
  2008-12-15
 */

#include "stdatl.h"

#include "resource.h"
#include "TestAtlAboutDlg.h" //CAboutDlg class
#include "MainDlg.h"
#include "KVerInfo.h" //CVersionInfo class

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
BOOL CMainDlg::OnInitDialog(CWindow /*wndFocus*/, //[in] control to receive
                      //the default keyboard focus if TRUE is returned.
                            LPARAM /*lInitParam*/ //[in] additional initialization
                      //data configured during creation of the dialog box.
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
InitListView(IDC_LISTTEST);

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
//List view handlers

//-----------------------------------------------------------------------------
/*Intilalizes embedded list view control.
 */
void CMainDlg::InitListView(const int idCtrl //[in] the identifier of the list
                            //view control to be initalized
                           )
{
ATLTRACE(_T("CMainDlg::InitListView(idCtrl = %d)\n"), idCtrl);
#ifndef  LB_ERR
  const int LB_ERR = -1;
#endif

m_ctrlListView = GetDlgItem(idCtrl);
m_ctrlListView.SetExtendedListViewStyle(LVS_EX_INFOTIP, LVS_EX_INFOTIP);
ATLVERIFY(m_ctrlListView.InsertColumn(0, _T("Column 1"), LVCFMT_LEFT, 150, -1) > LB_ERR);
ATLVERIFY(m_ctrlListView.InsertColumn(1, _T("Column 2"), LVCFMT_LEFT, 120,  1) > LB_ERR);

CVersionInfo verInfo;
CString strTemp;
ATLVERIFY(verInfo.GetProductName(strTemp));
ATLVERIFY(m_ctrlListView.InsertItem(0, strTemp) > LB_ERR);
ATLVERIFY(verInfo.GetProductVersion(strTemp));
ATLVERIFY(m_ctrlListView.AddItem(0, 1, strTemp) > LB_ERR);

ATLVERIFY(verInfo.GetFileDescription(strTemp));
ATLVERIFY(m_ctrlListView.InsertItem(1, strTemp) > LB_ERR);
ATLVERIFY(verInfo.GetLanguage(strTemp));
ATLVERIFY(m_ctrlListView.InsertItem(2, strTemp) > LB_ERR);
int iLangCode = verInfo.GetLanguageCode();
strTemp.Format(_T("%d"), iLangCode);
ATLVERIFY(m_ctrlListView.AddItem(2, 1, strTemp) > LB_ERR);

}

//-----------------------------------------------------------------------------
/*Handles request from the list-view control for additional text information
  to be displayed in a ToolTip.

  struct tagNMLVGETINFOTIP
    {
    NMHDR hdr;      //NMHDR structure that contains information on this
                    //notification message. 
    DWORD dwFlags;  //zero if the item text is truncated or LVGIT_UNFOLDED.
    LPTSTR pszText; //whole item text copy if item text is truncated
    int cchTextMax; //buffer size in characters, of the buffer pointed to
                    //by pszText.
    int iItem;      //index of the item to which this structure refers.
    int iSubItem;   //index of the subitem to which this structure refers.
    LPARAM lParam;  //reserved for future use.
    };

  The return value is ignored.

  See also: MSG_WM_NOTIFY_CODE(), MSG_WM_NOTIFY(), <commctrl.h>, NMLVGETINFOTIP,
  LVM_SETINFOTIP, LVSETINFOTIP
 */
LRESULT CMainDlg::OnGetInfoTip(NMLVGETINFOTIP* pHeader //[in/out] specifies
                                    //list-view item information for a ToolTip.
                         )
{
ATLTRACE(_T("CMainDlg::OnGetInfoTip()\n"));

ATLASSERT(pHeader);
CString sText;
sText.Format(_T("This is a tool tip for Item %d"), pHeader->iItem);
ZeroMemory(pHeader->pszText, pHeader->cchTextMax * sizeof (TCHAR));
_tcsncpy(pHeader->pszText, sText, pHeader->cchTextMax - 1);
return S_OK;
}

//-----------------------------------------------------------------------------
/*Handles an event that occurs when the user double-clicks certain elment
  within a control.

  The return value is ignored.
 */
LRESULT CMainDlg::OnDblClk(NMITEMACTIVATE*)
{
ATLTRACE(_T("CMainDlg::OnDblClk()\n"));

AtlMessageBox(m_hWnd,
              _T("NM_DBLCLK"),
              _T("Information"),
              MB_ICONINFORMATION | MB_OK);
return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: MainDlg.cpp,v $
 * Revision 1.6  2009/05/11 14:05:47  ddarko
 * Comment
 *
 * Revision 1.5  2009/04/24 19:58:24  ddarko
 * Cleaned warnings
 *
 * Revision 1.4  2009/04/21 21:33:18  ddarko
 * Initilalize List View control
 *
 * Revision 1.3  2009/02/24 21:42:33  ddarko
 * Test common control notification messages
 *
 ******************************************************************************/
