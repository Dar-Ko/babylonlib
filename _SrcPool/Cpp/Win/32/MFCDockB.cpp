/*$RCSfile: MFCDockB.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2009/09/01 15:11:50 $
  $Author: ddarko $

  Fix: corrupted dockable toolbar's properties CDockState
  Darko Kolakovic
  Aug 2k
 */

// Group=Windows

#include "StdAfx.h"
#include <AfxAdv.h> //CDockState
#ifndef __AFXPRIV_H__
  #include <AfxPriv.h> //CControlBarInfo
#endif
#include "MFC4CBar.h"

///////////////////////////////////////////////////////////////////////////////

//LoadBarState()---------------------------------------------------------------
/*FIX: This is copy of CFrameWnd::LoadBarState() used to fix mangled toolbar properties,
  Note: If toolbar position is not valid (due corruption of the registry file)
  CFrameWnd::SetDockState() throws assertation and crashes with null pointer.
  Closing main frame while MDI child frame is still open could corrupt file. D.K. 14.8.2k
*/
void MFCLoadBarState(CFrameWnd* pFrameWnd, LPCTSTR lpszProfileName)
{
ASSERT_VALID(pFrameWnd);

CDockState state;
state.LoadState(lpszProfileName);
::MFCSetDockState(pFrameWnd, state);
}

//SetDockState()-------------------------------------------------------------
/*FIX: This is copy of CFrameWnd::SetDockState() used to fix mangled toolbar properties,
  Note: If toolbar position is not valid (due corruption of the registry file)
  CFrameWnd::SetDockState() throws assertation and crashes with null pointer.
 Closing main frame while MDI child frame is still open could corrupt file. D.K. 14.8.2k
*/
void MFCSetDockState(CFrameWnd* pOwnerFrame, CDockState& state)
{
//First pass through barinfo's sets the m_pBar member correctly
//creating floating frames if necessary
for (int i = 0; i < state.m_arrBarInfo.GetSize(); i++)
  {
  CControlBarInfo* pInfo = (CControlBarInfo*)state.m_arrBarInfo[i];
  ASSERT(pInfo != NULL);
  if (pInfo->m_bFloating)
    {
    // need to create floating frame to match
    CMiniDockFrameWnd* pDockFrame = pOwnerFrame->CreateFloatingFrame(
      pInfo->m_bHorz ? CBRS_ALIGN_TOP : CBRS_ALIGN_LEFT);
    ASSERT(pDockFrame != NULL);
    CRect rect(pInfo->m_pointPos, CSize(10, 10));
    pDockFrame->CalcWindowRect(&rect);
    pDockFrame->SetWindowPos(NULL, rect.left, rect.top, 0, 0,
      SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE);
    CDockBar* pDockBar =
      (CDockBar*)pDockFrame->GetDlgItem(AFX_IDW_DOCKBAR_FLOAT);
    ASSERT(pDockBar != NULL);
    ASSERT_KINDOF(CDockBar, pDockBar);
    pInfo->m_pBar = pDockBar;
    }
  else // regular dock bar or toolbar
    {
    pInfo->m_pBar = pOwnerFrame->GetControlBar(pInfo->m_nBarID);
    //Ignore this D.K.  ASSERT(pInfo->m_pBar != NULL); //toolbar id's probably changed
    if (pInfo->m_pBar == NULL) //D.K. 14.8.2k
      {
     state.m_arrBarInfo.RemoveAt(i); //D.K.
     delete pInfo;
     pInfo = NULL;
      }
    }
  if ((pInfo != NULL) && (pInfo->m_pBar != NULL)) //D.K. 14.8.2k
    pInfo->m_pBar->m_nMRUWidth = pInfo->m_nMRUWidth;
  }

// the second pass will actually dock all of the control bars and
//  set everything correctly
for (i = 0; i < state.m_arrBarInfo.GetSize(); i++)
  {
  CControlBarInfo* pInfo = (CControlBarInfo*)state.m_arrBarInfo[i];
  ASSERT(pInfo != NULL);
  if (pInfo->m_pBar != NULL)
    pInfo->m_pBar->SetBarInfo(pInfo, pOwnerFrame);
  }

// last pass shows all the floating windows that were previously shown
for (i = 0; i < state.m_arrBarInfo.GetSize(); i++)
  {
  CControlBarInfo* pInfo = (CControlBarInfo*)state.m_arrBarInfo[i];
  ASSERT(pInfo != NULL);
  if (pInfo->m_pBar == NULL) //Jump over toolbars with unvalid state stored 23.8.2k D.K.
    continue;

  ASSERT(pInfo->m_pBar != NULL);
  if (pInfo->m_bFloating)
    {
    CFrameWnd* pFrameWnd = pInfo->m_pBar->GetParentFrame();
    CDockBar* pDockBar = (CDockBar*)pInfo->m_pBar;
    ASSERT_KINDOF(CDockBar, pDockBar);
    if (pDockBar->GetDockedVisibleCount() > 0)
      {
      pFrameWnd->RecalcLayout();
      pFrameWnd->ShowWindow(SW_SHOWNA);
      }
    }
  }
pOwnerFrame->DelayRecalcLayout();
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: MFCDockB.cpp,v $
 * Revision 1.2  2009/09/01 15:11:50  ddarko
 * Reformatted
 *
 *****************************************************************************/

