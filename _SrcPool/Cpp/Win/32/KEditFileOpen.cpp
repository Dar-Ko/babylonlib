/*$RCSfile: KEditFileOpen.cpp,v $: implementation file
  $Revision: 1.5 $ $Date: 2012/06/05 21:27:55 $
  $Author: ddarko $

  Implementation for a MFC control to get a filename using the file open/save
  as common dialogs
  Copyright: 1997 - 2011 by PJ Naughter
  Created: PJN / 19-03-1997
 */

///////////////////////////////// Includes ////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "KEditFileOpen.h"


///////////////////////////////// Macros / Defines ////////////////////////////

#ifdef _DEBUG
  #define new DEBUG_NEW
#endif


///////////////////////////////// Implementation //////////////////////////////



BEGIN_MESSAGE_MAP(CEditFileOpen, CEdit)
  ON_WM_ENABLE()
END_MESSAGE_MAP()

CEditFileOpen::CEditFileOpen() : m_dwCommonDialogFlags(OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT),
                                             m_bAutoComplete(FALSE), //FixMe: exception on destroy, if AutoComplete = TRUE
                                             m_dwAutoCompleteFlags(ACO_AUTOSUGGEST | ACO_FILTERPREFIXES),
                                           #if (_MSC_VER >= 1500)
                                             m_bVistaStyle(TRUE),
                                           #endif
                                             m_dwCommonDialogSize(0)
{
}

BOOL CEditFileOpen::SubclassEdit(HWND hEdit, UINT nModifyButtonID)
{
  ATLTRACE(_T("CEditFileOpen::SubclassEdit()\n"));
  //test our inputs
  if (!IsWindow(hEdit))
  {
    TRACE(_T("  Window handle is invalid!\n"));
    ASSERT(FALSE);
    return FALSE;
  }

  //subclass the control
  if (SubclassWindow(hEdit))
  {
    LoadStringResources();
    InitializeAutoComplete(); //Failing to setup auto complete is not considered a critical error
    return AddModifyButton(nModifyButtonID);
  }
  else
  {
    TRACE(_T("  Could not subclass edit control!\n"));
    ASSERT(FALSE);
    return FALSE;
  }
}

//-----------------------------------------------------------------------------
/*Handles pressed Enter key (VK_RETURN) event.

  Returns nonzero if the message was translated and should not be dispatched; 
  FALSE if the message was not translated and should be dispatched.
 */
BOOL CEditFileOpen::PreTranslateMessage(MSG* pMsg)
{
if ( pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN )
  {
  //const int idCtrl= GetFocus()->GetDlgCtrlID();
  if ( pMsg->hwnd == GetSafeHwnd() )
    {
    Notify();
    return TRUE;
    }
  }

return CEdit::PreTranslateMessage(pMsg);
}

//-----------------------------------------------------------------------------
/*
 */
void CEditFileOpen::SetAutoComplete(BOOL bAutoComplete)
{
  //Save the setting in the member variable
  m_bAutoComplete = bAutoComplete;

  //Also let the auto complete object know
  if (m_pAutoCompleteObject != NULL)
  {
    if (m_bAutoComplete == TRUE)
    {
      HRESULT hr = m_pAutoCompleteObject->SetOptions(m_dwAutoCompleteFlags);
      if (FAILED(hr))
        TRACE(_T("CEditFileOpen::SetAutoComplete, failed to set AutoComplete object options, Error:%08X\n"), hr);
    }
    else
    {
      HRESULT hr = m_pAutoCompleteObject->SetOptions(ACO_NONE);
      if (FAILED(hr))
        TRACE(_T("CEditFileOpen::SetAutoComplete, failed to set AutoComplete object options, Error:%08X\n"), hr);
    }
  }
}

HRESULT CEditFileOpen::InitializeAutoComplete()
{
  ATLTRACE(_T("CEditFileOpen::InitializeAutoComplete() m_bAutoComplete = %d\n"), m_bAutoComplete);
  if ((m_bAutoComplete == TRUE) && (m_pAutoCompleteObject == NULL))
  {
    //Create the auto complete object
    HRESULT hr = m_pAutoCompleteObject.CoCreateInstance(CLSID_AutoComplete, NULL, CLSCTX_INPROC_SERVER);
    if (FAILED(hr))
    {
      TRACE(_T("  failed to create AutoComplete object, Error: %08X\n"), hr);
      return hr;
    }

    //Create the auto complete source object, note we need to use the raw CoCreateInstance call because
    //IACList2 (or IACList for that matter) do not have a UUID associated with it
    ATLASSERT(m_pAutoCompleteSourceObject == NULL);
    hr = CoCreateInstance(CLSID_ACListISF, NULL, CLSCTX_INPROC_SERVER, IID_IACList2, reinterpret_cast<void**>(&m_pAutoCompleteSourceObject));
    if (FAILED(hr))
    {
      TRACE(_T("  failed to create AutoComplete filesystem source object, Error: %08X\n"), hr);
      return hr;
    }

    //Tell the auto complete source object to only return file system entries
    hr = m_pAutoCompleteSourceObject->SetOptions(ACLO_FILESYSONLY);
    if (FAILED(hr))
    {
      TRACE(_T("  failed to set AutoComplete filesystem source object options, Error: %08X\n"), hr);
      return hr;
    }

    //Finally set the options and hook up the edit control
    hr = m_pAutoCompleteObject->SetOptions(m_dwAutoCompleteFlags);
    if (FAILED(hr))
    {
      TRACE(_T("  failed to set AutoComplete object options, Error: %08X\n"), hr);
      return hr;
    }
    hr = m_pAutoCompleteObject->Init(GetSafeHwnd(), m_pAutoCompleteSourceObject, NULL, NULL);
    if (FAILED(hr))
    {
      TRACE(_T("  failed to initialize AutoComplete object, Error: %08X\n"), hr);
      return hr;
    }
  }

  return S_OK;
}

BOOL CEditFileOpen::AddModifyButton(UINT nModifyButtonID)
{
  //Validate our parameters
  CWnd* pParent = GetParent();
  AFXASSUME(pParent);

  //Work out the dimensions of the modify button and the resized edit control
  CRect editRect;
  GetWindowRect(editRect);
  pParent->ScreenToClient(editRect);
  CRect btnRect;
  btnRect.top    = editRect.top;
  btnRect.bottom = editRect.bottom;
  btnRect.right  = editRect.right;

  //Calculate the width of the button based on the text we are going to put on in
  CDC* pDC = pParent->GetDC();
  int nButtonWidth = 0;
  if (pDC)
  {
    //Setup the DC
    CFont* pNewFont = pParent->GetFont();
    CFont* pOldFont = pDC->SelectObject(pNewFont);

    //Get the button width
    CSize SizeText = pDC->GetTextExtent(_T("    "), 4); //We allow for some space around the button caption
    pDC->LPtoDP(&SizeText);
    nButtonWidth = SizeText.cx;
    SizeText = pDC->GetTextExtent(m_sModifyButtonCaption, m_sModifyButtonCaption.GetLength());
    pDC->LPtoDP(&SizeText);
    nButtonWidth += SizeText.cx;

    //Restore the DC
    pDC->SelectObject(pOldFont);
  }
  else
    nButtonWidth = btnRect.Height()*8/10;  //width is 8/10 of height

  //Now that we have the width we can fill out the rest of the buttons rect position
  btnRect.left = btnRect.right - nButtonWidth;

  //Tidy up the device context
  pParent->ReleaseDC(pDC);

  //Resize the edit control
  SetWindowPos(NULL, 0, 0, editRect.Width() - btnRect.Width() - 1, editRect.Height(), SWP_NOACTIVATE | SWP_NOMOVE | SWP_SHOWWINDOW | SWP_NOZORDER);

  //dynamically create the modify button control
  DWORD dwButtonStyles = WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_GROUP;
  if (GetStyle() & WS_DISABLED)
    dwButtonStyles |= WS_DISABLED;
  if (!m_ctrlModifyButton.Create(m_sModifyButtonCaption, dwButtonStyles, btnRect, pParent, nModifyButtonID))
    return FALSE;

  //Set the tab order of the button
  m_ctrlModifyButton.SetWindowPos(this, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

  //tell the button to call this class when it is clicked
  m_ctrlModifyButton.SetBuddy(this);

  //ensure it is using the same font as the parent
  m_ctrlModifyButton.SetFont(pParent->GetFont());

  return TRUE;
}

void CEditFileOpen::OnEnable(BOOL bEnable)
{
  //Let the base class do its thing
  CEdit::OnEnable(bEnable);

  //reflect the enabled state of this control to the buddy button control
  m_ctrlModifyButton.EnableWindow(bEnable);
}

//-----------------------------------------------------------------------------
/*
 */
void CEditFileOpen::Edit()
{
  ATLTRACE(_T("  CEditFileOpen::Edit()\n"));
  //Retrieve the current filename to use as the initial value
  CString sCurrentFilename;
  GetWindowText(sCurrentFilename);

  //Make sure the browse button at least works if a directory is
  //currently selected
  int nCurrentFilenameLength = sCurrentFilename.GetLength();
  if (nCurrentFilenameLength)
  {
    if (sCurrentFilename.GetAt(nCurrentFilenameLength-1) == _T('\\'))
      sCurrentFilename += _T("*.*");
  }

  //Bring up the common dialog
  #if (_MSC_VER >= 1500)
    CDDXFileFileNameDialog dlg(TRUE, NULL, sCurrentFilename, m_dwCommonDialogFlags,
                               m_sCommonDialogExtFilter, GetParent(), 
                               m_dwCommonDialogSize, m_bVistaStyle);
  #else
    CDDXFileFileNameDialog dlg(TRUE, NULL, sCurrentFilename, m_dwCommonDialogFlags, 
                               m_sCommonDialogExtFilter, GetParent(), 
                               m_dwCommonDialogSize);
  #endif
  dlg.SetBuddy(this);

  //Modify the title to the desired value
  if (m_sCommonDialogTitle.GetLength())
    dlg.m_ofn.lpstrTitle = m_sCommonDialogTitle;

  #if (_MSC_VER >= 1500)
    #if (WINVER >= 0x0600)
      //Modify the text on the OK button to be the specified value, since it will
      //not be done via OnInitDone which is where we change OK button text for
      //non Vista style File dialogs.
      //This is because OnInitDone is not supported for Vista style File dialogs
      if (dlg.UsingVistaStyle())
      {
        CComPtr<IFileOpenDialog> pFileOpenDialog;
        pFileOpenDialog.Attach(dlg.GetIFileOpenDialog());
        if (pFileOpenDialog)
          pFileOpenDialog->SetOkButtonLabel(CStringW(m_sCommonDialogOkCaption));
      }
    #endif
  #endif

  //bring up the dialog and if the user hits ok, then set the text in this control to the new filename
  if (dlg.DoModal() == IDOK)
    {
    CWnd::SetWindowText(dlg.GetPathName());
    Notify(); //Notify the owner about the update
    }
}

//-----------------------------------------------------------------------------
/*Notify current update to the parent .
  The WM_NOTIFY message is sent to buddy window when an event has occurred 
  Sent with the message is notification information with code NM_RETURN.
 */
void CEditFileOpen::Notify()
{
ATLTRACE(_T("  CEditFileOpen::Notify()\n"));

CWnd* pOwner = GetOwner();
if (pOwner != NULL)
  {
  ASSERT_VALID(pOwner);
  NMHDR hdr;   //information about a notification message
  hdr.hwndFrom = m_hWnd;//Handle to control sending message
  hdr.idFrom =          //Identifier of control sending message
       GetDlgCtrlID();
  hdr.code = NM_RETURN; //Notification code

  #ifdef _DEBUG
    LRESULT pResult =
  #endif
      pOwner->SendMessage(WM_NOTIFY,
                         (WPARAM)GetDlgCtrlID(),
                         (LPARAM)&hdr);
  }
}

//-----------------------------------------------------------------------------
/*Set default titles and captions.
  Returns TRUE if succesful or FALSE if a resource string fails to load.
 */
BOOL CEditFileOpen::LoadStringResources()
{
  //Use the default strings, a derived class can change this implementation or 
  //call the "Set.." functions directly
  if (m_sCommonDialogOkCaption.IsEmpty())
  {
    if (!m_sCommonDialogOkCaption.LoadString(IDS_DDXFILE_OK))
      return FALSE;
  }
  if (m_sModifyButtonCaption.IsEmpty())
  {
    if (!m_sModifyButtonCaption.LoadString(IDS_DDXFILE_EDIT_TEXT))
      return FALSE;
  }
  if (m_sModifyButtonToolTipText.IsEmpty())
  {
    if (!m_sModifyButtonToolTipText.LoadString(IDS_DDXFILE_TT_MODIFY))
      return FALSE;
  }
  if (m_sCommonDialogTitle.IsEmpty())
  {
    if (!m_sCommonDialogTitle.LoadString(IDS_DDXFILE_PROMPT_FILENAME))
      return FALSE;
  }
  if (m_sCommonDialogExtFilter.IsEmpty())
  {
    if (!m_sCommonDialogExtFilter.LoadString(IDS_DDXFILE_ALL_EXT_FILTER))
      return FALSE;
  }

  return TRUE;
}

CString CEditFileOpen::GetOverwritePromptString(const CString& sFilename)
{
  CString sReturn;
  AfxFormatString1(sReturn, IDP_DDXFILE_OVERWRITE_PROMPT, sFilename);
  return sReturn;
}

///////////////////////////////////////////////////////////////////////////////
//DDX/DDV Helpers

void DDX_FilenameControl(CDataExchange* pDX, int nIDC, CEditFileOpen& rControl, UINT nModifyButtonID)
{
  if ((rControl.m_hWnd == NULL) && (rControl.GetControlUnknown() == NULL)) //not subclassed yet
  {
    ASSERT(!pDX->m_bSaveAndValidate);

    pDX->PrepareEditCtrl(nIDC);
    HWND hWndCtrl;
    pDX->m_pDlgWnd->GetDlgItem(nIDC, &hWndCtrl);
    if ((hWndCtrl != NULL) && !rControl.SubclassEdit(hWndCtrl, nModifyButtonID))
    {
      ASSERT(FALSE); //possibly trying to subclass twice?
      AfxThrowNotSupportedException();
    }
#ifndef _AFX_NO_OCC_SUPPORT
    else
    {
     if (hWndCtrl == NULL)
     {
       if (pDX->m_pDlgWnd->GetOleControlSite(nIDC) != NULL)
         rControl.AttachControlSite(pDX->m_pDlgWnd, nIDC);
     }
     else
     {
       //If the control has reparented itself (e.g., invisible control),
       //make sure that the CWnd gets properly wired to its control site.
       if (pDX->m_pDlgWnd->m_hWnd != ::GetParent(rControl.m_hWnd))
         rControl.AttachControlSite(pDX->m_pDlgWnd);
     }
    }
#endif //!_AFX_NO_OCC_SUPPORT
  }
}

void DDX_FilenameValue(CDataExchange* pDX, CEditFileOpen& rControl, CString& sFile)
{
  if (pDX->m_bSaveAndValidate)
    rControl.GetWindowText(sFile);
  else
    rControl.SetWindowText(sFile);
}

void DDV_FilenameControlNotFolder(CDataExchange* pDX, CEditFileOpen& rControl, UINT nFailureResourceID, UINT nHelpID)
{
  if (pDX->m_bSaveAndValidate)
  {
    CString sFile;
    rControl.GetWindowText(sFile);
    DWORD dwAttributes = GetFileAttributes(sFile);

    if ((dwAttributes != INVALID_FILE_ATTRIBUTES) && (dwAttributes & FILE_ATTRIBUTE_DIRECTORY))
    {
      AfxMessageBox(nFailureResourceID, MB_OK | MB_ICONEXCLAMATION, nHelpID);
      pDX->PrepareEditCtrl(rControl.GetDlgCtrlID());
      pDX->Fail();
    }
  }
}

void DDV_FilenameControlMustExist(CDataExchange* pDX, CEditFileOpen& rControl, UINT nFailureResourceID, UINT nHelpID)
{
  if (pDX->m_bSaveAndValidate)
  {
    CString sFile;
    rControl.GetWindowText(sFile);
    DWORD dwAttributes = GetFileAttributes(sFile);

    //Check to see if the file exists
    if (dwAttributes == INVALID_FILE_ATTRIBUTES)
    {
      AfxMessageBox(nFailureResourceID, MB_OK | MB_ICONEXCLAMATION, nHelpID);
      pDX->PrepareEditCtrl(rControl.GetDlgCtrlID());
      pDX->Fail();
    }
  }
}

void DDV_FilenameControlOverwritePrompt(CDataExchange* pDX, CEditFileOpen& rControl, UINT nHelpID)
{
  if (pDX->m_bSaveAndValidate)
  {
    CString sFile;
    rControl.GetWindowText(sFile);
    DWORD dwAttributes = GetFileAttributes(sFile);

    if (dwAttributes != INVALID_FILE_ATTRIBUTES)
    {
      //Prompt the user if we can overwrite and if we get a negative indication, then fail the validation
      if (AfxMessageBox(rControl.GetOverwritePromptString(sFile), MB_YESNO | MB_ICONQUESTION, nHelpID) != IDYES)
      {
        pDX->PrepareEditCtrl(rControl.GetDlgCtrlID());
        pDX->Fail();
      }
    }
  }
}

void DDV_FilenameControlNotEmpty(CDataExchange* pDX, CEditFileOpen& rControl, UINT nFailureResourceID, UINT nHelpID)
{
  if (pDX->m_bSaveAndValidate)
  {
    CString sFile;
    rControl.GetWindowText(sFile);

    //Check to see if the file exists
    if (sFile.IsEmpty())
    {
      AfxMessageBox(nFailureResourceID, MB_OK | MB_ICONEXCLAMATION, nHelpID);
      pDX->PrepareEditCtrl(rControl.GetDlgCtrlID());
      pDX->Fail();
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
// CDDXFileModifyButton

BEGIN_MESSAGE_MAP(CDDXFileModifyButton, CButton)
  ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
END_MESSAGE_MAP()

CDDXFileModifyButton::CDDXFileModifyButton() : m_pBuddy(NULL),
                                               m_bFirstPreTranslateMessageCall(TRUE)
{
}

void CDDXFileModifyButton::SetBuddy(CEditFileOpen* pBuddy)
{
  //Validate our parameters
  ASSERT(pBuddy);

  m_pBuddy = pBuddy;
}

BOOL CDDXFileModifyButton::PreTranslateMessage(MSG* pMsg)
{
  //Validate our parameters
  ASSERT(m_pBuddy);

  //create the tooltip
  if (m_bFirstPreTranslateMessageCall)
  {
    AFXASSUME(m_pBuddy);
    CString sTTText(m_pBuddy->GetModifyButtonToolTipText());
    if (sTTText.GetLength())
    {
      m_ToolTip.Create(this);
      m_ToolTip.Activate(TRUE);
      m_ToolTip.AddTool(this, sTTText);
    }
    m_bFirstPreTranslateMessageCall = FALSE;
  }

  //give the tooltip a chance to handle the message if is is valid
  if (m_ToolTip.GetSafeHwnd() != NULL)
    m_ToolTip.RelayEvent(pMsg);

  return CButton::PreTranslateMessage(pMsg);
}

void CDDXFileModifyButton::OnClicked()
{
  ATLTRACE(_T("CDDXFileModifyButton::OnClicked()\n"));
  //Validate our parameters
  AFXASSUME(m_pBuddy);

  //Ask the buddy to show the dialog
  m_pBuddy->Edit();
}

///////////////////////////////////////////////////////////////////////////////
// CDDXFileFileNameDialog

IMPLEMENT_DYNAMIC(CDDXFileFileNameDialog, CFileDialog)

#if (_MSC_VER >= 1500)
CDDXFileFileNameDialog::CDDXFileFileNameDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt,
              LPCTSTR lpszFileName, DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd, 
              DWORD dwSize,  BOOL bVistaStyle) :  
    CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, 
                lpszFilter, pParentWnd, dwSize, bVistaStyle),
#else
CDDXFileFileNameDialog::CDDXFileFileNameDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt,
                                LPCTSTR lpszFileName, DWORD dwFlags, LPCTSTR lpszFilter, 
                                CWnd* pParentWnd, DWORD dwSize) :
    CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, 
                lpszFilter, pParentWnd, dwSize),
#endif
  m_bSetOkCaption(FALSE)
{
}

BEGIN_MESSAGE_MAP(CDDXFileFileNameDialog, CFileDialog)
END_MESSAGE_MAP()

void CDDXFileFileNameDialog::SetBuddy(CEditFileOpen* pBuddy)
{
  //Valiate our parameters
  ASSERT(pBuddy);

  m_pBuddy = pBuddy;
}

void CDDXFileFileNameDialog::OnInitDone()
{
  //Validate our parameters
  AFXASSUME(m_pBuddy);

  //Modify the text on the IDOK button to be the specified value, nominally "Ok"
  CString sOkCaption(m_pBuddy->GetCommonDialogOkCaption());
  if (sOkCaption.GetLength())
    SetControlText(IDOK, sOkCaption);
}

//-----------------------------------------------------------------------------
/*This method is called by File Open dialog to validate the filename entered 
  in the dialog box.

  Returns TRUE if the filename is not a valid filename; otherwise returns FALSE.
  If TRUE (1) is returned, the dialog box will remain displayed for the user to 
  enter another filename. The dialog procedure dismisses the dialog if the return
  is FALSE (0).
 */
BOOL CDDXFileFileNameDialog::OnFileNameOK()
{
  ATLTRACE("CDDXFileFileNameDialog::OnFileNameOK()\n");
  //Let the base class do its thing
  BOOL rVal = CFileDialog::OnFileNameOK();
  if (!rVal)  //if the filename passed the parent tests then put it through our own tests
  {
    //check for overwrite if that flag is used, since the file open
    //common dialog will not bother looking at this flag
    if (m_ofn.Flags & OFN_OVERWRITEPROMPT)
    {
      //Retrieve the filename selected
      CString strPath(GetFolderPath());

      //check to see if the file already exists
      CFileStatus fs;
      if (GetFileAttributes(strPath) != INVALID_FILE_ATTRIBUTES)
      {
        ASSERT(m_pBuddy);
        CString strMessage(m_pBuddy->GetOverwritePromptString(strPath));

        //ensure the title is the same as the common dialog caption
        CString strCaption(m_pBuddy->GetCommonDialogTitle());
        rVal = (MessageBox(strMessage, strCaption, MB_YESNO | MB_ICONQUESTION) != IDYES);
      }
    }
  }
  return rVal;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: KEditFileOpen.cpp,v $
 * Revision 1.5  2012/06/05 21:27:55  ddarko
 * *** empty log message ***
 *
 * Revision 1.4  2012/06/05 20:38:07  ddarko
 * Added notification to parent on VK_RETURN or CFileDialog IDOK events
 *
 * Revision 1.2  2012/06/04 21:00:41  ec11691
 * http://www.naughter.com
 *
 * Created: PJN / 19-03-1997
 *
 *****************************************************************************
/*Copyright (c) 1997 - 2011 by PJ Naughter (Web: www.naughter.com,
  Email: pjna@naughter.com)
  All rights reserved.

  Copyright / Usage Details:
  You are allowed to include the source code in any product (commercial,
  shareware, freeware or otherwise)   when your product is released in binary
  form. You are allowed to modify the source code in any way you want except
  you cannot modify the copyright details at the top of each module.
 */
