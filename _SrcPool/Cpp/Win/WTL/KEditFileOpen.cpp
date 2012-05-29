/*$RCSfile: KEditFileOpen.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2012/05/29 20:41:01 $
  $Author: ddarko $

  Defines the class behaviors for the application.
  Copyright: CommonSoft Inc., 2002
 */

#include "stdafx.h"
#include "KEditFileOpen.h" //CEditFileOpen class

/////////////////////////////////////////////////////////////////////////////
// CEditFileOpen

CEditFileOpen::CEditFileOpen()
{
ATLTRACE("CEditFileOpen::CEditFileOpen()\n");
}

CEditFileOpen::~CEditFileOpen()
{
ATLTRACE("CEditFileOpen::~CEditFileOpen()\n");
}

//-----------------------------------------------------------------------------
/*Call this member function to dynamically subclass a window and attach it to
  this object. If function is successful, windows messages will route through 
  this object's message map and call its message handlers first. Messages that
  are passed to the base class will be passed to the default message handler
  in the window.

  See also: UnsubclassWindow()

  Returns nonzero if the function is successful; otherwise 0.
 */
BOOL CEditFileOpen::SubclassWindow(HWND hWnd //[in] handle to the window
                             )
{
ATLTRACE(L"CEditFileOpen::SubclassWindow()\n");
BOOL bRet = CWindowImpl<CEditFileOpen, CEdit>::SubclassWindow(hWnd);
if(bRet != FALSE)
  {
  if(m_btnBuddy.IsWindow() == FALSE)
    {
    m_btnBuddy.Create(m_hWnd, &rcDefault, NULL, WS_POPUP | BS_PUSHBUTTON | BS_NOTIFY);
    ATLASSERT(m_btnBuddy.IsWindow() == TRUE);
    bRet = m_btnBuddy.IsWindow();
    if (bRet == TRUE)
      {
      m_btnBuddy.SetFont((HFONT)::SendMessage(GetParent(), WM_GETFONT, 0, 0L));
      m_btnBuddy.SetWindowText(_T("..."));
      }
    }
  }
return bRet;
}

//-----------------------------------------------------------------------------
/*Call this member function to set WndProc back to its original value and detach
  the window identified by HWND from the CWnd object.
  Use only if you want to subclass before window is destroyed.

  Returns handle to the unsubclassed window.
 */
HWND CEditFileOpen::UnsubclassWindow(BOOL bForce //[in] = FALSE
                      )
{
ATLTRACE(L"CEditFileOpen::UnsubclassWindow()\n");
if(m_btnBuddy.IsWindow())
  m_btnBuddy.Detach();

HWND hWnd =  CWindowImpl<CEditFileOpen, CEdit>::UnsubclassWindow(bForce);
return hWnd;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: KEditFileOpen.cpp,v $
 * Revision 1.1  2012/05/29 20:41:01  ddarko
 * Copied from old repository
 *
 *****************************************************************************/
