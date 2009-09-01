/*MFC4CBar.cpp
  Fix up for the ControlBars

  Darko Kolakovic
  Aug.  2k
  */

#include "StdAfx.h"
#include "MFC4CBar.h"

#if _MFC_VER == 0x0400 || _MFC_VER == 0x0410
#include <AfxAdv.h> //CDockState
#ifndef __AFXPRIV_H__
  #include <AfxPriv.h> //CControlBarInfo
#endif

///////////////////////////////////////////////////////////////////////////////

//MFC41CleanUpControlBarState()------------------------------------------------
/*FIX: Internal State of ControlBars Corrupted ( MFC4.0, 4.1 )
  Article ID: Q151446
  
  Example:

     #include "MFC4CBar.h" //MFC41CleanUpControlBarState()
     void CMainFrame::OnClose()
       {
         //SaveBarState saves everything but the number of Columns in
         //the Palette we need to do that ourselves.
       SaveBarState(_T("General"));

         //Following code was added to the sample with Visual C++ 4.1
       #if _MFC_VER == 0x0400 || _MFC_VER == 0x0410
         MFC41CleanUpControlBarState(this, _T("General"));
       #endif
       ... 
       }

 */
void MFC41CleanUpControlBarState(CFrameWnd* pOwner, LPCTSTR szCtrlBar)
{
CDockState state;
pOwner->GetDockState(state);

for (int i = 0; i < state.m_arrBarInfo.GetSize(); i++)
  {
  CControlBarInfo* pInfo1 = (CControlBarInfo*)state.m_arrBarInfo[i];

  for (int j = 0; j < state.m_arrBarInfo.GetSize(); j++)
    {
    if (i == j)
      continue;

    CControlBarInfo* pInfo2 = (CControlBarInfo*)state.m_arrBarInfo[j];

    if (pInfo1->m_uMRUDockID == pInfo2->m_nBarID)
      continue;

    int nSize = pInfo2->m_arrBarID.GetSize();
    for (int k = 0; k < nSize - 1; k++)
      {
      if ((LONG)pInfo2->m_arrBarID[k] == (LONG)pInfo1->m_nBarID + 0x10000)
        pInfo2->m_arrBarID[k] = NULL;
      }
    }
  }

for (i = 0; i < state.m_arrBarInfo.GetSize(); i++)
  {
  CControlBarInfo* pInfo = (CControlBarInfo*)state.m_arrBarInfo[i];

  int nSize = pInfo->m_arrBarID.GetSize();
  for (int j = 0; j < nSize - 1; j++)
    {
    if (pInfo->m_arrBarID[j]==NULL)
      continue;

    for (int k = j + 1; k < nSize; k++)
      {
      if (pInfo->m_arrBarID[k]==NULL)
        continue;

      if (pInfo->m_arrBarID[k]==pInfo->m_arrBarID[j])
        pInfo->m_arrBarID[k] = NULL;
      }
    }

  while ((nSize!=0) && (pInfo->m_arrBarID[nSize-1]==NULL))
    {
    nSize--;
    pInfo->m_arrBarID.RemoveAt(nSize);
    }
  if (nSize)
    pInfo->m_arrBarID.InsertAt(nSize, (void*)NULL);
  }

state.SaveState(szCtrlBar);
}
///////////////////////////////////////////////////////////////////////////////
#endif //MFC4.0, 4.1
