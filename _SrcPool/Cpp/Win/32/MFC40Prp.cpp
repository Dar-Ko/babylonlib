/*$RCSfile: MFC40Prp.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2009/09/01 15:11:50 $
  $Author: ddarko $

  Fix: Creating CPropertySheet objects (MFC4.0, Q147206)
  Darko Kolakovic March 98
 */

// Group=Windows

#include "StdAfx.h"
#include "MFC40Prp.h"

#ifdef _MFC40
///////////////////////////////////////////////////////////////////////////////

//MFC40PropSheetCallback()-----------------------------------------------------
/*FIX: Border of Modeless CPropertySheet Is Not 3D in Windows NT ( MFC4.0 )
  Article ID: Q147206
 */
int CALLBACK  MFC40PropSheetCallback(HWND, UINT message, LPARAM lParam)
{
switch (message)
  {
  case PSCB_PRECREATE:
    {
    _AFX_THREAD_STATE* pState = AfxGetThreadState();
    LPDLGTEMPLATE lpTemplate = (LPDLGTEMPLATE)lParam;
    if (lpTemplate->style != pState->m_dwPropStyle ||
        lpTemplate->dwExtendedStyle != pState->m_dwPropExStyle)
      {
      //Original line disables DS_MODALFRAME D.K.
      //lpTemplate->style &= ~DS_MODALFRAME;
      lpTemplate->style = MAKELONG(
        LOWORD(lpTemplate->style), HIWORD(pState->m_dwPropStyle));
      lpTemplate->dwExtendedStyle = pState->m_dwPropExStyle;
      return TRUE;
      }
    return FALSE;
    }
  }

return 0;
}

///////////////////////////////////////////////////////////////////////////////
// C++ Hack to access protected members in the property sheet
class CFixPropertySheet : public CPropertySheet
  {
  public:
    BOOL Create(CWnd* pParentWnd = NULL,
                DWORD dwStyle = WS_SYSMENU | WS_POPUP | WS_CAPTION |
                                DS_MODALFRAME | WS_VISIBLE,
                DWORD dwExStyle = WS_EX_DLGMODALFRAME );

  };

//::Create()-------------------------------------------------------------------
/*This is the copy of the code from CPropertySheet::Create() in DlgProp.cpp
  (MFC 4.0). Win95 could not create child property sheet when function is
  called from MFC40.dll. Reason unknown. D.K.
 */
BOOL CFixPropertySheet::Create(CWnd* pParentWnd,
                               DWORD dwStyle,
                               DWORD dwExStyle)
{
TRACE3("CFixPropertySheet::Create()\t%s, style %d, exstyle %d\n",
       this->GetRuntimeClass()->m_lpszClassName, dwStyle,dwExStyle );

_AFX_THREAD_STATE* pState = AfxGetThreadState();
pState->m_dwPropStyle = dwStyle;
pState->m_dwPropExStyle = dwExStyle;

ASSERT_VALID(this);
ASSERT(m_hWnd == NULL);

//WS_SYSMENU must not be set if a property sheet is created as a child

if (dwStyle & WS_CHILD)
  dwStyle &= ~WS_SYSMENU;

//Finish building PROPSHEETHEADER structure
BuildPropPageArray();
m_bModeless = TRUE;

//Specifies a callback function
m_psh.dwFlags |= (PSH_MODELESS|PSH_USECALLBACK);
m_psh.pfnCallback = MFC40PropSheetCallback;
m_psh.hwndParent = pParentWnd->GetSafeHwnd();

//Hook the window creation process
AfxHookWindowCreate(this);
//MFC 4.2 defines AFX_OLDPROPSHEETHEADER instead PROPSHEETHEADER 17.3.2k D.K.
HWND hWnd = (HWND)PropertySheet((LPCPROPSHEETHEADER)&m_psh);

//Clean up on failure, otherwise return TRUE
if (!AfxUnhookWindowCreate())
  PostNcDestroy();     //Cleanup if Create fails

if (hWnd == NULL || hWnd == (HWND)-1)
  return FALSE;
ASSERT(hWnd == m_hWnd);

return TRUE;
}

//MC40PropSheetCreate()--------------------------------------------------------
/*FIX: Border of Modeless CPropertySheet Is Not 3D in Windows NT ( MFC4.0 )
  Article ID: Q147206
  FIX: Win95 does not open child property sheet
  D.K.
 */
BOOL MFC40PropSheetCreate(CPropertySheet* pSheet, CWnd* pParentWnd,
                          DWORD dwStyle, DWORD dwExStyle)
{
if (pSheet == NULL)
  return FALSE;
CFixPropertySheet* pFixSheet = (CFixPropertySheet*)pSheet;
return pFixSheet->Create(pParentWnd,dwStyle,dwExStyle);
}

///////////////////////////////////////////////////////////////////////////////
#endif //_MFC40
/*****************************************************************************
 * $Log: MFC40Prp.cpp,v $
 * Revision 1.2  2009/09/01 15:11:50  ddarko
 * Reformatted
 *
 * Jan.  2000 Compiled with MSVC 60 (MFC4.2) D.K.
 *****************************************************************************/

