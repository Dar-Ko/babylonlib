/*$Workfile: S:\_SrcPool\Cpp\Win\32\KStatusBarEx.cpp$: implementation file
  $Revision: 3$ $Date: 2005-05-04 17:50:23$
  $Author: Darko Kolakovic$

  Defines the class behaviors for the application.
  Copyright: CommonSoft Inc.
  Jan 96 Darko Kolakovic
 */

#include "stdafx.h"
#include "KStatusBarEx.h"  //CStatusBarEx class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatusBarEx

CStatusBarEx::CStatusBarEx() :
  m_bDisableSetText(FALSE)
{
}

CStatusBarEx::~CStatusBarEx()
{
}


BEGIN_MESSAGE_MAP(CStatusBarEx, CStatusBar)
  //{{AFX_MSG_MAP(CStatusBarEx)
    ON_MESSAGE( WM_SETTEXT, OnSetText )
  // NOTE - the ClassWizard will add and remove mapping macros here.
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()


//-----------------------------------------------------------------------------
/*Computes the width of a line of text using the current status bar font to
  determine the dimensions.

  Returns: the width of the string (in logical units).

  Example:
      void CChildFrame::OnUpdateIndicatorTest(CCmdUI* pCmdUI)
      {
        UINT nID = 0;
        UINT nStyle = 0;
        const int TESTPANEID = 1;
        CString strTest;
        strTest = _T("This is a test.");
        int iSize = CStatusBarEx::GetTextExtent(&m_wndStatusBar,
                                               TESTPANEID,
                                               strTest,
                                               nID,
                                               nStyle
        if(iSize > m_iOldSize)
          m_wndStatusBar.SetPaneInfo(TESTPANEID, nID, nStyle, iSize);
        pCmdUI->SetText(strTest);
        pCmdUI->Enable(TRUE);
      }
 */
int CStatusBarEx::GetTextExtent(CStatusBar* pStatusBar, //[in] status bar object to validate
                                 const int& iPaneId, //[in] index of the pane whose information is to be retrieved.
                                 const CString& strPaneText, //[in] text to be measured
                                 UINT& nID, //[out] Reference to a UINT that is set to the ID of the pane.
                                 UINT& nStyle //[out] Reference to a UINT that is set to the style of the pane.
                                 )

{
if(pStatusBar != NULL)
  {
  HGDIOBJ hOldFont = NULL;
  HFONT hFont = (HFONT)pStatusBar->SendMessage(WM_GETFONT);
  CClientDC dc(NULL);
  if(hFont != NULL)
    hOldFont = dc.SelectObject(hFont);

  int iWidth;
  pStatusBar->GetPaneInfo(iPaneId, nID, nStyle, iWidth);

  return (dc.GetTextExtent(strPaneText)).cx;
  }
ASSERT(pStatusBar != NULL);
return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CStatusBarEx message handlers
/*Response at a WM_SETTEXT message to set the text of a window.

  The frameworks WM_SETTEXT messages will be blocked when you set
  m_bEnableSetText flag to a non-zero value. The first pane of the status bar
  will be updated only when user update it with SetPaneText().
 */
LRESULT CStatusBarEx::OnSetText(WPARAM wParam, LPARAM lParam)
{
if ( !m_bDisableSetText )
  return CStatusBar::OnSetText( wParam, lParam );
return 0;  // Same as CStatusBar::OnSetText success
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2004-10-01 22:35:29  Darko           stdafx.h
 *  1    Biblioteka1.0         2003-08-13 14:35:30  Darko
 * $
 *****************************************************************************/
