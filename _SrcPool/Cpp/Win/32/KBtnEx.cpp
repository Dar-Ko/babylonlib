/*$Workfile: KBtnEx.cpp$: implementation file
  $Revision: 10$ $Date: 2004-10-01 21:33:41$
  $Author: Darko$

  Defines the class behaviors for the application.
  Copyright: CommonSoft Inc.
  Jan 97 Darko Kolakovic
 */

#include "stdafx.h"
#include "KBtnEx.h" //CButtonEx class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
  extern void DumpButtonStyle(HWND hButton);
  extern void DumpButtonStyle(UINT nBtnStyle);
#else
  #if _MSC_VER > 1200
    #define DumpButtonStyle __noop
  #else
    #define DumpButtonStyle (void(0))
  #endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CButtonEx

/*flag set when framework tags a buttons the default pushbutton.

  See also: OnGetDlgCode()
 */
const UINT CButtonEx::BTN_STANDBY = 0X00100000L;

/*flag indicating that button has hover style.

  See also: BS_FLAT
 */
const UINT CButtonEx::BTN_HOVER = 0X00200000L;

IMPLEMENT_DYNAMIC(CButtonEx, CButton)

CButtonEx::CButtonEx() :
  m_iStyle(0xFEFEFEFE),
  m_nState(BST_UNCHECKED),
  m_bMouseIn  (FALSE),
  m_clrBtnText(GetSysColor(COLOR_BTNTEXT)),
  m_clrBtnFace(GetSysColor(COLOR_BTNFACE))
{
}

CButtonEx::~CButtonEx()
{
}

BEGIN_MESSAGE_MAP(CButtonEx, CButton)
  //{{AFX_MSG_MAP(CButtonEx)
  ON_WM_MOUSEMOVE()
  ON_WM_LBUTTONUP()
  ON_WM_SETFOCUS()
  ON_WM_GETDLGCODE()
  ON_MESSAGE(BM_SETSTYLE, OnSetStyle)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
/*Changes the type and style of a button.
  The lowest 16 bit of the complete button style is the button-specific
  style.
  Button Control Types are mutually exclusive. Button's type could be changed
  with to the one of following values:

              Button Control Types
              BS_PUSHBUTTON       0x00L
              BS_DEFPUSHBUTTON    0x01L
              BS_CHECKBOX         0x02L
              BS_AUTOCHECKBOX     0x03L
              BS_RADIOBUTTON      0x04L
              BS_3STATE           0x05L
              BS_AUTO3STATE       0x06L
              BS_GROUPBOX         0x07L
              BS_USERBUTTON       0x08L
              BS_AUTORADIOBUTTON  0x09L
              BS_PUSHBOX          0x0AL
              BS_OWNERDRAW        0x0BL

              Button Control Type bitmask
              BS_TYPEMASK         0x0FL

  A Button Control control could have a combination of the following button
  styles:

              Button Control Styles
              BS_LEFTTEXT         0x20L
              Windows 95 and Windows NT 4.0 or greater (WINVER >= 0x0400)
              BS_TEXT             0x0000L
              BS_ICON             0x0040L
              BS_BITMAP           0x0080L
              BS_LEFT             0x0100L
              BS_RIGHT            0x0200L
              BS_CENTER           0x0300L
              BS_TOP              0x0400L
              BS_BOTTOM           0x0800L
              BS_VCENTER          0x0C00L
              BS_PUSHLIKE         0x1000L
              BS_MULTILINE        0x2000L
              BS_NOTIFY           0x4000L
              BS_FLAT             0x8000L
              BS_RIGHTBUTTON      BS_LEFTTEXT
              CButtonEx styles
              BTN_HOVER

  Note: CButton::SetButtonStyle() changes only low-order 8 bit flags; see afxwin2.inl.

  See also: winuser.h, afxwin2.inl, CButton::GetButtonStyle(), CButton::Create(),
  DumpButtonStyle()
 */
void CButtonEx::SetButtonStyle(UINT nStyle,//[in] specifies the button new style
                               bool bRedraw//[in]= true specifies whether the 
                                           //button is to be redrawn
                               )
{
HWND hWnd = GetSafeHwnd();
ASSERT(::IsWindow(hWnd));

if (hWnd != NULL)
  {
  LONG nOldStyle = ::GetWindowLong(hWnd, GWL_STYLE);
  //Store original button's type, usually set in resource template
  m_iStyle = (int)(nOldStyle & 0XFFFF);
  if ((nStyle & BTN_HOVER) != 0)
    m_iStyle |= BTN_HOVER;
  ::SetWindowLong(hWnd, GWL_STYLE, (nOldStyle & ~BS_TYPEMASK) | (nStyle & 0XFFFF));
  if (bRedraw) 
    Invalidate();
  }
}

/////////////////////////////////////////////////////////////////////////////
// CButtonEx message handlers

//-----------------------------------------------------------------------------
/*The framework calls this member function when the mouse cursor moves.
 */
void CButtonEx::OnMouseMove(UINT nFlags, //[in] virtual keys flags
                            CPoint point //[in] coordinates of the cursor
                            )
{
if (GetCapture()!=this)
  {
  if (m_rtSize.PtInRect(point))
    {
    m_bMouseIn = TRUE;
    SetCapture();
    }
  }
else
  {
  if (!m_rtSize.PtInRect(point))
    {
    m_bMouseIn = FALSE;
    ReleaseCapture();
    }
  }

if (IsHoverStyle())
  Invalidate(); //D.K. 20030825 Coluld be handled on WM_MOUSELEAVE message 
                //(OnMouseLeave)

CButton::OnMouseMove(nFlags, point);
}

//-----------------------------------------------------------------------------
/*The framework calls this member function when the user releases the left
  mouse button.
 */
void CButtonEx::OnLButtonUp(UINT nFlags, //[in] virtual keys flags.
                            CPoint point //[in] cursor's coordinate relative to
                                         //the upper-left corner of the window
                            )
{
if (GetCapture()==this)
  {
  m_bMouseIn = FALSE;
  }
Invalidate();
CButton::OnLButtonUp(nFlags, point);
}

//::PreSubclassWindow()--------------------------------------------------------
/*This member function is called by the framework to allow other necessary 
  subclassing to occur before the window is subclassed.
  BS_OWNERDRAW style is added to the list of the button styles.
 */
void CButtonEx::PreSubclassWindow()
{
TRACE(_T("CButtonEx::PreSubclassWindow()\n"));

CButton::PreSubclassWindow();
#ifdef _DEBUG
  TRACE("  Original  ");
  DumpButtonStyle(GetSafeHwnd());
#endif

SetButtonStyle((GetButtonStyle() & ~BS_TYPEMASK) | BS_OWNERDRAW);

#ifdef _DEBUG
  DumpButtonStyle(GetSafeHwnd());
#endif
}

//-----------------------------------------------------------------------------
/*
  This implemetation converts WM_LBUTTONDBLCLK messages to WM_LBUTTONDOWN.
 */
BOOL CButtonEx::PreTranslateMessage(MSG* pMsg //[in]
                                    )
{
if (pMsg->message == WM_LBUTTONDBLCLK)
  pMsg->message = WM_LBUTTONDOWN;

return CButton::PreTranslateMessage(pMsg);
}

//-----------------------------------------------------------------------------
/*Called for a control so the control can process arrow-key and TAB-key 
  input itself.

  Returns: one or more of the following values, indicating which type of input
  the application processes: 

      DLGC_BUTTON           Button (generic). 
      DLGC_DEFPUSHBUTTON    Default pushbutton. 
      DLGC_HASSETSEL        EM_SETSEL messages. 
      DLGC_UNDEFPUSHBUTTON  No default pushbutton processing.
                            (An application can use this flag with DLGC_BUTTON
                            to indicate that it processes button input but relies
                            on the system for default pushbutton processing.) 
      DLGC_RADIOBUTTON      Radio button. 
      DLGC_STATIC           Static control. 
      DLGC_WANTALLKEYS      All keyboard input. 
      DLGC_WANTARROWS       Arrow keys. 
      DLGC_WANTCHARS        WM_CHAR messages. 
      DLGC_WANTMESSAGE      All keyboard input. The application passes this
                            message on to the control. 
      DLGC_WANTTAB          TAB key. 

  History: Paolo Messina Aug 2001
 */
UINT CButtonEx::OnGetDlgCode()
{
UINT nCode = CButton::OnGetDlgCode();

//Handle standard control types
switch (GetButtonType())
  {
  case BS_RADIOBUTTON:
  case BS_AUTORADIOBUTTON:
    nCode |= DLGC_RADIOBUTTON;
    break;

  case BS_GROUPBOX:
    nCode = DLGC_STATIC;
    break;
  }

  //Tell the system if we want default state handling
  //(losing default state always allowed)
  //if (m_bCanBeDefault || m_bDefault)
nCode |= (IsDefPushButton() ? DLGC_DEFPUSHBUTTON : DLGC_UNDEFPUSHBUTTON);

return nCode;
}

//::OnDraw()-------------------------------------------------------------------
/*This function draws a button with custom colors. Both 3D and flat styles are
  supported.
  Override this function to implement different button look.

  History: Yuheng Zhao 1998, Darko Kolakovic 1999, 2000, 2003
 */
void CButtonEx::OnDraw(const UINT itemState //[in] visual state of
                                  //the control after the current drawing
                                  //action takes place
                       )
{
CClientDC dc(this);
CRect rect = m_rtSize;
bool bMouseDown = IsSelected(itemState) || (m_nState != BST_UNCHECKED);

const COLORREF clrBtnShadow   = GetSysColor(COLOR_3DSHADOW);
const COLORREF clrBtnDkShadow = GetSysColor(COLOR_3DDKSHADOW);
const COLORREF clrBtnHilite   = GetSysColor(COLOR_3DHILIGHT);
const COLORREF clrBtnFrame    = GetSysColor(COLOR_3DLIGHT);
const COLORREF clrBtnDefault  = RGB(0,0,0); //Black
const COLORREF clrBtnIndeterminated = GetSysColor(COLOR_SCROLLBAR);

CBrush brFace;
brFace.CreateSolidBrush((m_nState != BST_INDETERMINATE) ? 
                        m_clrBtnFace : 
                        clrBtnIndeterminated);
CBrush* pOldBrush = dc.SelectObject(&brFace);
dc.FillRect(rect, &brFace);

CPen penFrame(PS_SOLID, 1, clrBtnFrame);
CPen* pOldPen = dc.SelectObject(&penFrame);

if(IsFlat()) //Flat frame
  {
  if (!m_bMouseIn)
    dc.Rectangle(m_rtSize);
  else if (m_bMouseIn && bMouseDown)
    dc.Draw3dRect(rect,clrBtnShadow, clrBtnHilite);
  else if (m_bMouseIn && (!bMouseDown))
    dc.Draw3dRect(rect, clrBtnHilite, clrBtnShadow);
  }
else //3D frame
  {

  if (!bMouseDown)
    {
    dc.Rectangle(rect);
    rect.DeflateRect(1, 1);
    dc.Draw3dRect(rect,clrBtnHilite, clrBtnDkShadow);
    rect.DeflateRect(1, 1);
    dc.Draw3dRect(rect,clrBtnFrame, clrBtnShadow);
    }
  else
    {
    dc.Rectangle(rect);
    rect.DeflateRect(1, 1);
    dc.Draw3dRect(rect,clrBtnShadow, clrBtnHilite);
    }
  rect = m_rtSize;
  }

  //Draw focused control
if (IsFocused(itemState))
  {
  rect.DeflateRect(3, 3);
  dc.DrawFocusRect(&rect);
  rect = m_rtSize;
  }

  //Draw control's border
if(IsDefPushButton())
  {
  dc.Draw3dRect(rect,clrBtnDefault, clrBtnDefault);
  }

  //Draw button's caption
CString strText;
GetWindowText(strText);
if (!strText.IsEmpty())
  {
  CFont* pFont = GetFont();
  pFont = dc.SelectObject (pFont);

  if (m_bMouseIn && (!bMouseDown))
    rect.OffsetRect(-1,-1);

  UINT nStyle = (UINT)GetWindowLong(m_hWnd, GWL_STYLE);
  UINT nFormat;  //text style
  if ((nStyle & BS_CENTER) == BS_CENTER) //Windows 95 only
    nFormat = DT_CENTER;
  else
    {
    if ((nStyle & BS_LEFT) != 0) 
      {
      nFormat = DT_LEFT;
      rect.left += 4;
      }
    else if ((nStyle & BS_RIGHT) != 0)
      {
      nFormat = DT_RIGHT;
      rect.right -= 4;
      }
    else //Default value
      nFormat = DT_CENTER;
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
    case BS_CENTER:
      nFormat |= DT_CENTER;
    default: //TODO: Default value depends on system's localization. Currently is fixed for left-to-right scripts D.K.
      nFormat |= DT_LEFT;
    }

  if (nStyle & BS_MULTILINE)
    nFormat |= DT_WORDBREAK;
  else
    nFormat |= DT_SINGLELINE;

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
dc.SelectObject(pOldPen);
}

//::DrawItem()-----------------------------------------------------------------
/*Called by the framework when a visual aspect of an owner-drawn button has 
  changed. An owner-drawn button has the BS_OWNERDRAW style set. Override this 
  member function to implement drawing for an owner-drawn CButton object.
 */
void CButtonEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct //[in] information
                                         //about the type of drawing required
                         )
{
m_rtSize.CopyRect(&lpDrawItemStruct->rcItem);
OnDraw(lpDrawItemStruct->itemState);
}

//-----------------------------------------------------------------------------
/*Handles BM_SETSTYLE messages received by framework.

  Returns: This message always returns zero.

  See also: CButtonEx::SetButtonStyle(), CButton::SetButtonStyle()
 */
LRESULT CButtonEx::OnSetStyle(WPARAM wParam,//[in] new style
                              LPARAM lParam //[in] low-order word of lParam
                              //specifies whether the button is to be redrawn
                              )
{
TRACE(_T("CButtonEx::OnSetStyle(%X, hWnd %x)\n"), wParam, m_hWnd);
#ifdef _DEBUG_SETSTYLE
  TRACE(_T("\n  Changed from "));
  DumpButtonStyle((UINT)m_iStyle);
  TRACE(_T("  to new "));
  DumpButtonStyle((UINT)wParam);
#endif

  //Draw default pushbutton rectangle if virtual type is BS_DEFPUSHBUTTON or
  //BS_PUSHBUTTON
if(GetButtonType() <= BS_DEFPUSHBUTTON)
  {
  if ((wParam & BS_TYPEMASK) == BS_DEFPUSHBUTTON)
    m_iStyle |= BTN_STANDBY;
  else
    m_iStyle &= ~BTN_STANDBY;
  }

/*Let the system process changes to style bits and redrawing, while 
  keeping owner-draw type.
 */
return DefWindowProc(BM_SETSTYLE,
                     (wParam & ~BS_TYPEMASK) | BS_OWNERDRAW,
                     lParam);
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  10   Biblioteka1.9         2004-10-01 21:33:41  Darko           stdafx.h
 *  9    Biblioteka1.8         2003-09-02 16:20:06  Darko           Horizontal
 *       aligment
 *  8    Biblioteka1.7         2003-09-02 00:06:17  Darko           pushlike
 *       checkbox handling
 *  7    Biblioteka1.6         2003-08-29 14:50:08  Darko           Fixed BTN_HOVER
 *  6    Biblioteka1.5         2003-08-29 07:51:07  Darko           focus handling
 *  5    Biblioteka1.4         2003-08-26 00:34:05  Darko          
 *       IMPLEMENT_DYNAMIC
 *  4    Biblioteka1.3         2003-08-25 00:17:32  Darko           formatting
 *  3    Biblioteka1.2         2003-08-25 00:13:57  Darko           formatting
 *  2    Biblioteka1.1         2003-08-24 13:17:27  Darko           
 *  1    Biblioteka1.0         2003-08-24 13:02:43  Darko           
 * $
 *****************************************************************************/
