/*$RCSfile: KEditRetCtrl.h,v $: implementation file
  $Revision: 1.1 $ $Date: 2013/08/29 22:38:57 $
  $Author: ddarko $
  Kristian Lippert
*/

#pragma once

#include <atlapp.h>
#include <atlctrls.h>


///////////////////////////////////////////////////////////////////////////////
/*
  Example:
  LRESULT CMainDlg::OnInitDialog(UINT, WPARAM, LPARAM, BOOL&)
 {
  CenterWindow();
  m_editRet.AttachToDlgItem(m_hWnd,IDC_EDIT_CTRL);
  ...
  }
 */
template <class T>
class CEditEnterAsTabT : public CWindowImpl<CEditEnterAsTabT<T> , CEdit>,  public CEditCommands<T>
{
public:
  BEGIN_MSG_MAP(CEditEnterAsTabT< T >)
    MESSAGE_HANDLER(WM_CHAR, OnChar)
    MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
    MESSAGE_RANGE_HANDLER(WM_KEYFIRST, WM_KEYLAST, OnKeyDown)
  END_MSG_MAP()

  CEditEnterAsTabT(HWND hWnd = NULL){ }


  CEditEnterAsTabT< T >& operator=(HWND hWnd)
  {
    m_hWnd = hWnd;
    return *this;
  }

  LRESULT OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
  {
    //ignore without a beep
    switch (wParam)
    {
    case VK_RETURN: //Carriage return
      return 0;
      break;
    }
    return DefWindowProc(uMsg, wParam, lParam);
  }

  LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
  {
    switch (wParam)
    {
    case VK_RETURN:
    case VK_TAB:
      ::PostMessage (m_parent, WM_NEXTDLGCTL, 0, 0L);
      return FALSE;
    }
    return DefWindowProc(uMsg, wParam, lParam);
  }

  BOOL AttachToDlgItem(HWND parent, UINT dlgID)
  {
    m_dlgItem = dlgID;
    m_parent = parent;

    HWND hWnd = ::GetDlgItem(parent,dlgID);
    return SubclassWindow(hWnd);
  }
private:
  UINT m_dlgItem;
  HWND m_parent;
};
///////////////////////////////////////////////////////////////////////////////
//

typedef CEditEnterAsTabT<CWindow>	CEditImpl;
///////////////////////////////////////////////////////////////////////////////


