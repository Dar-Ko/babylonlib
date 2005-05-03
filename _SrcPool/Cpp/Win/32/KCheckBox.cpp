/*$Workfile: KCheckBox.cpp$: implementation file
  $Revision: 5$ $Date: 2005-05-02 17:20:27$
  $Author: Darko Kolakovic$

  Defines the class behaviors for the application.
  Copyright: CommonSoft Inc.
  2003-08-29 Darko Kolakovic
 */

#include "stdafx.h"
#include "KCheckBox.h"  //CCheckBox class

///////////////////////////////////////////////////////////////////////////////
// CCheckBox

/*default outer size of a checkbox in pixels
 */
const UINT CCheckBox::BOX_SIZE = 13;

IMPLEMENT_DYNAMIC(CCheckBox, CButtonEx)
CCheckBox::CCheckBox()
{
}

CCheckBox::~CCheckBox()
{
}

BEGIN_MESSAGE_MAP(CCheckBox, CButtonEx)
  //{{AFX_MSG_MAP(CCheckBox)
  ON_MESSAGE(BM_SETCHECK, OnSetCheck)
  ON_MESSAGE(BM_GETCHECK, OnGetCheck)
  ON_CONTROL_REFLECT(BN_CLICKED, OnBnClicked)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//::OnDraw()-------------------------------------------------------------------
/*This function draws a checkbox with custom colors. Both 3D and flat styles are
  supported.
  Override this function to implement different look.
 */
void CCheckBox::OnDraw(const UINT itemState //[in] visual state of
                                  //the control after the current drawing
                                  //action takes place
                       )
{
if(((m_iStyle & BS_PUSHLIKE) == BS_PUSHLIKE) || !(IsCheckbox() || IsTristate()))
  {
  CButtonEx::OnDraw(itemState);
  return;
  }

CClientDC dc(this);
UINT nStyle = (UINT)GetWindowLong(m_hWnd, GWL_STYLE);

CRect rect(0,0,BOX_SIZE,BOX_SIZE);
if ((nStyle & BS_LEFTTEXT) == BS_LEFTTEXT) //Draw check box on the right side
  {
  #if (_MFC_VER < 0x0700)
    rect.left  -= (m_rtSize.right - BOX_SIZE);
    rect.right -= (m_rtSize.right - BOX_SIZE);
  #else
    rect.MoveToX(m_rtSize.right - BOX_SIZE);
  #endif
  }

const COLORREF clrBtnShadow   = GetSysColor(COLOR_3DSHADOW);
const COLORREF clrBtnDkShadow = GetSysColor(COLOR_3DDKSHADOW);
const COLORREF clrBtnHilite   = GetSysColor(COLOR_3DHILIGHT);
const COLORREF clrBtnFrame    = GetSysColor(COLOR_3DLIGHT);
const COLORREF clrBtnDefault  = RGB(0,0,0); //Black
const COLORREF clrBtnIndeterminated = GetSysColor(COLOR_SCROLLBAR);


CBrush brFace;
brFace.CreateSolidBrush(IsIndeterminated() ? clrBtnIndeterminated : m_clrBtnFace);
CBrush* pOldBrush = dc.SelectObject(&brFace);
dc.FillRect(rect, &brFace);

CPen* pOldPen = dc.GetCurrentPen();

if(IsFlat()) //Flat frame
  {
  CPen penFrame(PS_SOLID, 2, clrBtnDefault);
  pOldPen = dc.SelectObject(&penFrame);
  dc.Rectangle(rect.left + 1, rect.top + 1, rect.right, rect.bottom);
  }
else //3D frame
  {
  dc.Draw3dRect(rect,clrBtnShadow, clrBtnHilite);
  rect.DeflateRect(1, 1);
  dc.Draw3dRect(rect,clrBtnDkShadow, clrBtnFrame);
  rect.InflateRect(1, 1);
  }

if (!IsUnchecked())
  {
    //Draw check mark 2px thick if state is BST_CHECKED or BST_INDETERMINATE
  CPen penText(PS_SOLID, 1, IsChecked() ? m_clrBtnText : clrBtnShadow);
  dc.SelectObject(&penText);
  dc.MoveTo(rect.left + 3, 7); //    23456789A
  dc.LineTo(rect.left + 5, 9); //  3 .......C.
  dc.LineTo(rect.left + 9, 5); //  4 ......CC.
  dc.LineTo(rect.left + 9, 3); //  5 .C...CCC.
  dc.LineTo(rect.left + 4, 8); //  6 .CC.CCC..
  dc.LineTo(rect.left + 3, 5); //  7 .CCCCC...
  dc.LineTo(rect.left + 5, 8); //  8 ..CCC....
  dc.LineTo(rect.left + 9, 4); //  9 ...C.....
  penText.DeleteObject();
  }
  //Draw focused control
if (IsFocused(itemState))
  {
  //rect.DeflateRect(3, 3);
  //dc.DrawFocusRect(&rect);
  rect = m_rtSize;
  }

  //Draw control's border
if(IsDefPushButton())
  {
  //dc.Draw3dRect(rect,clrBtnDefault, clrBtnDefault);
  }

  //Draw button's caption
CString strText;
GetWindowText(strText);
if (!strText.IsEmpty())
  {
  CFont* pFont = GetFont();
  pFont = dc.SelectObject (pFont);

  UINT nFormat;  //text style
  //CSize sizeText = dc.GetTextExtent(strText);
  rect = m_rtSize;
  //rect.SetRect(16, 1,                    //upper-left corner
  //                16 + sizeText.cx, 15); //lower-right corner
  if (nStyle & BS_MULTILINE)
    nFormat = DT_WORDBREAK;
  else
    nFormat = DT_SINGLELINE | DT_VCENTER;//DT_CENTER|DT_VCENTER|DT_SINGLELINE;
//  if ((nStyle & BS_CENTER) == BS_CENTER) //Windows 95 only
//    nFormat = DT_CENTER | DT_SINGLELINE;
//  else
//    {
    if ((nStyle & BS_LEFTTEXT) == BS_LEFTTEXT) 
      {
//      nFormat |= DT_RIGHT;
      rect.right -= (BOX_SIZE + 4);
      }
    else //if ((nStyle & BS_RIGHT) != 0)
      {
//      nFormat |= DT_LEFT;
      rect.left += (BOX_SIZE + 4);
      }
//    else
//      nFormat = DT_CENTER | DT_SINGLELINE;
//    }

  switch (nStyle & BS_CENTER)
    {
    case BS_LEFT:     
      nFormat |= DT_LEFT;
      break;
    case BS_RIGHT:  
      nFormat |= DT_RIGHT;
      break;
    case BS_CENTER:
      nFormat |= DT_CENTER;
    default: //TODO: Default value depends on system's localization. Currently is fixed for left-to-right scripts D.K.
      nFormat |= DT_LEFT;
    }

  switch (nStyle & BS_VCENTER)
    {
    case BS_TOP:     
      nFormat |= DT_TOP;
      rect.top += 4;  
      break;
    case BS_BOTTOM:  
      nFormat |= DT_BOTTOM;
      rect.bottom -=  4;
      break;
    default: //BS_VCENTER
      nFormat |= DT_VCENTER;
    }

  int iOldMode = dc.SetBkMode(TRANSPARENT);
  COLORREF clrOldText;

  if (IsDisabled(itemState))
    {
    rect.OffsetRect(1, 1);
    clrOldText = dc.SetTextColor(::GetSysColor(COLOR_3DHILIGHT));
    dc.DrawText(strText, rect, nFormat);
    rect.OffsetRect(-1, -1);
    dc.SetTextColor(::GetSysColor(COLOR_3DSHADOW));
    }
  else
    clrOldText = dc.SetTextColor(m_clrBtnText);

  dc.DrawText(strText, rect, nFormat);

  dc.SetBkMode(iOldMode);
  dc.SetTextColor(clrOldText);
  }

dc.SelectObject(pOldBrush);
if (pOldPen != NULL)
  dc.SelectObject(pOldPen);
}

///////////////////////////////////////////////////////////////////////////////
// CCheckBox message handlers

//-----------------------------------------------------------------------------
/*An application sends a BM_SETCHECK message to set the check state of a check
  box or radio button.
  Check state parameter can be one of the following values:

      BST_UNCHECKED      0x0000 Set the button state to unchecked.
      BST_CHECKED        0x0001 Set the button state to checked.
      BST_INDETERMINATE  0x0002 Set the button state to indeterminate. This 
                                value can be used only if the button has the
                                BS_3STATE or BS_AUTO3STATE style.

  Returns: message always returns zero.

  See also: winuser.h, CButton::SetCheck(), afxwin2.inl
 */
LRESULT CCheckBox::OnSetCheck(WPARAM wCheckState, //[in] specifies the check state.
                              LPARAM lParam  //not used, must be zero
                              )
{
UNUSED_ALWAYS(lParam);
TRACE(_T("CCheckBox::OnSetCheck(state=%d)\n"),wCheckState);

switch((UINT)wCheckState)
  {
  case BST_UNCHECKED:
  case BST_CHECKED:
    m_nState = (UINT)wCheckState;
    break;
  case BST_INDETERMINATE:
    if (IsCheckbox())
      m_nState = BST_CHECKED; //Handle indeterminate state as checked state.
    else
      m_nState = BST_INDETERMINATE;
    break;
  default: //If garbage received, keep pervious state
    TRACE0("  received unsupported state!\n");
  }

Invalidate(); //Redraw the control with new state
return 0;
}

//-----------------------------------------------------------------------------
/*An application sends a BM_GETCHECK message to retrieve the check state of
  a check box or radio button.

  Returns: one of the following values, if control is of BS_AUTOCHECKBOX,
  BS_AUTORADIOBUTTON, BS_AUTO3STATE, BS_CHECKBOX, BS_RADIOBUTTON, 
  or BS_3STATE type:
  
      BST_UNCHECKED      0x0000 button state to unchecked.
      BST_CHECKED        0x0001 button state to checked.
      BST_INDETERMINATE  0x0002 button state to indeterminate. This 
                                value can be used only if the button is 
                                of the BS_3STATE or BS_AUTO3STATE type.

  If the button has any other style, the return value is BST_UNCHECKED.

  See also: winuser.h, CButton::GetCheck(), afxwin2.inl
  */
LRESULT CCheckBox::OnGetCheck(WPARAM ,//wParam, not used, must be zero
                              LPARAM  //lParam  not used, must be zero
                              )
{
return (LRESULT)m_nState;
}

//-----------------------------------------------------------------------------
/*Handles BN_CLICKED message.
  The BN_CLICKED notification code is sent when the user clicks a button. 
 */
void CCheckBox::OnBnClicked()
{
if( !(IsCheckbox() || IsTristate()))
  return;

  //Change the state of the checkbox
switch (m_nState)
  {
  case BST_UNCHECKED: 
    m_nState = BST_CHECKED;
    break;
  case BST_CHECKED: 
    m_nState = IsCheckbox() ? BST_UNCHECKED : BST_INDETERMINATE;
    break;
  default: 
    //Only tri-state boxes are expected to have BST_INDETERMINATE state
    ASSERT(m_nState == BST_INDETERMINATE);
    m_nState = BST_UNCHECKED;
    break;
  }
//SetFocus();
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  5    Biblioteka1.4         2005-05-02 17:20:27  Darko Kolakovic fixed MSVC6
 *       build
 *  4    Biblioteka1.3         2004-10-01 22:33:44  Darko           stdafx.h
 *  3    Biblioteka1.2         2003-09-04 15:50:18  Darko           Handling of
 *       errorneus states in OnSetCheck()
 *  2    Biblioteka1.1         2003-09-02 17:20:08  Darko           Horizontal
 *       aligment
 *  1    Biblioteka1.0         2003-09-02 01:05:10  Darko           
 * $
 *****************************************************************************/
