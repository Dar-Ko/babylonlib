/*$RCSfile: TestAtlAboutDlg.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2009/02/23 20:06:44 $
  $Author: ddarko $

  implementation of the CAboutDlg class
 */

#include "stdatl.h"
#include "resource.h"

#include "TestAtlAboutDlg.h"

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
LRESULT CAboutDlg::OnInitDialog(UINT /*uMsg*/,
                                WPARAM /*wParam*/,
                                LPARAM /*lParam*/,
                                BOOL& /*bHandled*/
                               )
{
ATLTRACE(_T("CAboutDlg::OnInitDialog()\n"));
CenterWindow(GetParent());
return TRUE;
}

//-----------------------------------------------------------------------------
/*Called by the framework on command to terminate a modal dialog box.
 */
LRESULT CAboutDlg::OnCloseCmd(WORD /*wNotifyCode*/,
                              WORD wID,
                              HWND /*hWndCtl*/,
                              BOOL& /*bHandled*/
                             )
{
ATLTRACE(_T("CAboutDlg::OnCloseCmd()\n"));
EndDialog(wID); //Terminate a modal dialog box
return S_OK;
}
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: TestAtlAboutDlg.cpp,v $
 * Revision 1.2  2009/02/23 20:06:44  ddarko
 * Test application for  ATL/WTL controls
 *
 ******************************************************************************/
