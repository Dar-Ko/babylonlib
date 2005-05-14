/*$Workfile: KStaticEx.cpp$: implementation file
  $Revision: 5$ $Date: 2005-05-05 22:57:57$
  $Author: Darko$

  Defines the class behavior.
  Copyright: CommonSoft Inc.
  2001-07-06 Darko Kolakovic
 */

#include "stdafx.h"
#include "KStaticEx.h"  //CStaticEx class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// CStaticEx class

IMPLEMENT_DYNAMIC(CStaticEx, CStatic);

BEGIN_MESSAGE_MAP(CStaticEx, CStatic)
  //{{AFX_MSG_MAP(CStaticEx)
  ON_WM_DRAWITEM_REFLECT()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()


//-----------------------------------------------------------------------------
/*Default constructor
 */
CStaticEx::CStaticEx() :
  m_clrText(GetSysColor(COLOR_BTNTEXT)),
  m_clrBkFace(GetSysColor(COLOR_BTNFACE))
{
}


//-----------------------------------------------------------------------------
/*Destructor
 */
CStaticEx::~CStaticEx()
{
}

//-----------------------------------------------------------------------------
/*Set controls's backround and text color.

  Example:
        #include "KCStaticEx.h"
        #include "KColorCt.h"
        ...
        void MyFunc(CWnd* pParentWnd)
            {
            CStaticEx* pStaticText = new CStaticEx();
            pStaticText->Create(_T("Some Text"),
                                WS_CHILD   |
                                WS_VISIBLE |
                                SS_CENTER,   //center text horizontally
                                CRect(10,10,150,50),
                                pParentWnd);
           pStaticText->SetTextColor(BLUE, BEIGE);
           pStaticText->RedrawWindow();
           ...
           delete pStaticText;
           }
 */
void CStaticEx::SetTextColor(COLORREF clrForeground, //[in] text color
                             COLORREF clrBackground  //[in] background
                                                     //color
                             )
{
m_clrText   = clrForeground;
m_clrBkFace = clrBackground;
}

//-----------------------------------------------------------------------------
/*This member function is called by the framework to allow other necessary
  subclassing to occur before the window is subclassed.
  BS_OWNERDRAW style is added to the list of the button styles.
 */
void CStaticEx::PreSubclassWindow()
{
TRACE(_T("CStaticEx::PreSubclassWindow()\n"));

CWnd::PreSubclassWindow();
DWORD dwStyle = GetStyle();
ModifyStyle(SS_TYPEMASK, SS_OWNERDRAW);
dwStyle = GetStyle();
CString str;
GetWindowText(str);
  Invalidate();

}

//-----------------------------------------------------------------------------
/*This function draws a button with custom colors. Both 3D and flat styles are
  supported.
  Override this function to implement different button look.
 */
void CStaticEx::OnDraw(const UINT itemState //[in] visual state of
                                  //the control after the current drawing
                                  //action takes place
                       )
{
CClientDC dc(this);
CRect rect;
GetClientRect(rect);

  //Paint the background
CBrush brFace;
brFace.CreateSolidBrush(m_clrBkFace);
CBrush* pOldBrush = dc.SelectObject(&brFace);
dc.FillRect(rect, &brFace);

  //Get control's caption
CString strText(_T(""));
GetWindowText(strText);
if (!strText.IsEmpty())
  {
  UINT nFormat = 0;
  DWORD dwStyle = GetStyle();

    //Convert static style settings to text format flags
  if (dwStyle & SS_CENTER)
    nFormat |= DT_CENTER;
  else if (dwStyle & SS_LEFT)
    nFormat |= DT_LEFT;
  else if (dwStyle & SS_RIGHT)
    nFormat |= DT_RIGHT;

    //TODO: vertical centering for multiple lines; now works only with a single line
  if (dwStyle & SS_CENTERIMAGE) 
    nFormat |= DT_VCENTER | DT_SINGLELINE;
  else
    nFormat |= DT_WORDBREAK;


  CFont* pFont = GetFont();

  //rect.left += m_nXMargin;
  //rect.top  += m_nYMargin;

  pFont = dc.SelectObject (pFont);
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
    clrOldText = dc.SetTextColor(m_clrText);

  dc.DrawText(strText, rect, nFormat);

  dc.SetBkMode(iOldMode);
  dc.SetTextColor(clrOldText);
  }
dc.SelectObject(pOldBrush);
}

//-----------------------------------------------------------------------------
/*Called by the framework when a visual aspect of an owner-drawn static control
  has changed. An owner-drawn controls has the SS_OWNERDRAW style set.
  The contrl receives a WM_DRAWITEM message whenever the control needs to
  be drawn.

  Override this member function to implement drawing for an owner-drawn
  CStatic object.
 */
void CStaticEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct //[in] information
                                         //about the type of drawing required
                         )
{
//m_rtSize.CopyRect(&lpDrawItemStruct->rcItem);
OnDraw(lpDrawItemStruct->itemState);
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2005-05-04 09:29:49  Darko Kolakovic
 * $
 *****************************************************************************/
