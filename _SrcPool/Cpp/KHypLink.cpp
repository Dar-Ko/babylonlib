/*$Workfile: KHypLink.cpp$: implementation file
  $Revision: 5$ $Date: 1/29/02 2:40:23 PM$
  $Author: Darko$

  HyperLink static control.
  Copyright: CommonSoft Inc.
  D. Kolakovic May 98 Documentation
 */ 

#include "StdAfx.h"

#ifndef __AFXCMN_H__
  #include <AfxCmn.h> //CToolTipCtrl class
#endif

#include "KHypLink.h" //CHyperLink class
#include "KColorCt.h" //Color constants

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

  //default tooltip ID used with CHyperLink control
#define TOOLTIP_ID 1

/////////////////////////////////////////////////////////////////////////////
// CHyperLink

CHyperLink::CHyperLink(BOOL bAutoDelete //= FALSE
                       ) :
    m_hCursor       (NULL),               // No cursor as yet
    m_crTextColor   (LIGHTBLUE),
    m_crDone        (MAGENTA),
    m_crInFocus     (::GetSysColor(COLOR_3DHILIGHT)),
    m_bInFocus      (FALSE),             //Cursor not yet over control
    m_bDone         (FALSE),             //Hasn't been visited yet.
    m_dwStyle       (HLNK_UNDERLINE|HLNK_AUTOFIT),
    m_bAutoDelete  (bAutoDelete)
{
}

CHyperLink::~CHyperLink()
{
m_Font.DeleteObject();
}

BEGIN_MESSAGE_MAP(CHyperLink, CStatic)
    //{{AFX_MSG_MAP(CHyperLink)
    ON_WM_CTLCOLOR_REFLECT()
    ON_WM_SETCURSOR()
    ON_WM_MOUSEMOVE()
    ON_WM_KILLFOCUS()
    ON_WM_NCHITTEST()
    ON_CONTROL_REFLECT(STN_CLICKED, OnClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHyperLink message handlers

BOOL CHyperLink::PreTranslateMessage(MSG* pMsg)
{
m_ToolTip.RelayEvent(pMsg);
return CStatic::PreTranslateMessage(pMsg);
}

//::OnClicked()----------------------------------------------------------------
/*The STN_CLICKED notification message is sent when the user clicks a static
  control that has the SS_NOTIFY style. The parent window of the control
  receives this notification message through the WM_COMMAND message.
  This implemetation activates hyperlink.

      STN_CLICKED
      (int) LOWORD(wParam)  identifier of static control
      (HWND)LOWORD(lParam)  handle of static control
 */
void CHyperLink::OnClicked()
{
m_bInFocus = FALSE;
int result = (int)(::SpawnURL(m_strURL, SW_SHOW));
m_bDone = (result > HINSTANCE_ERROR);
if (!m_bDone)
  {
  MessageBeep(MB_ICONEXCLAMATION);     // Unable to follow link
  ReportError(result);
  }
else
  SetAccessed();                        // Repaint to show visited colour
}

//::CtlColor()-----------------------------------------------------------------
#pragma warning( disable : 4100 ) //Warning :unreferenced formal parameter
/*Handles WM_CTLCOLOR reflected message to set colors of the hyperlink text.
  For non-text controls, does nothing.
 */
HBRUSH CHyperLink::CtlColor(CDC* pDC,      //current device context
                            UINT nCtlColor //specifyies the type of control
                            )
{
ASSERT(nCtlColor == CTLCOLOR_STATIC);
DWORD dwStyle = GetStyle();
if ((dwStyle & 0xFF) <= SS_RIGHT) //Check if control is with text
  {
  if (m_bInFocus)
    pDC->SetTextColor(m_crInFocus);
  else if (IsAccessed())
    pDC->SetTextColor(m_crDone);
  else
    pDC->SetTextColor(m_crTextColor);

  //Return hollow brush to preserve parent background color
  pDC->SetBkMode(TRANSPARENT);
  return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
  }
return NULL;
}
#pragma warning( default : 4100 )//Warning :unreferenced formal parameter

//::OnMouseMove()--------------------------------------------------------------
/*The framework calls this member function when the mouse cursor moves. If the
  mouse is not captured, the WM_MOUSEMOVE message is received by the CWnd object
  beneath the mouse cursor; otherwise, the message goes to the window that has
  captured the mouse.
 */
void CHyperLink::OnMouseMove(UINT nFlags, CPoint point)
{
CStatic::OnMouseMove(nFlags, point);

if (m_bInFocus)        // Cursor is currently over control
  {
  CRect rect;
  GetClientRect(rect);

  if (!rect.PtInRect(point))
    {
    m_bInFocus = FALSE;
    ReleaseCapture();
    RedrawWindow();
    }
  }
else                      // Cursor has just moved over control
  {
  m_bInFocus = TRUE;
  RedrawWindow();
  SetCapture();
  }
}

//::OnSetCursor()--------------------------------------------------------------
/*The framework calls this member function if mouse input is not captured and
  the mouse causes cursor movement within the CWnd object.
 */
BOOL CHyperLink::OnSetCursor(CWnd* /*pWnd*/, UINT /*nHitTest*/, UINT /*message*/)
{
if (m_hCursor)
  {
  ::SetCursor(m_hCursor);
  return TRUE;
  }
return FALSE;
}

//::OnKillFocus()--------------------------------------------------------------
/*The framework calls this member function immediately before losing the input focus.
 */
void CHyperLink::OnKillFocus(CWnd* pNewWnd)
{
CStatic::OnKillFocus(pNewWnd);

m_bInFocus = FALSE;
Invalidate();
}

//::PreSubclassWindow()--------------------------------------------------------
/*This member function is called by the framework to allow other necessary
  subclassing to occur before the window is subclassed.
 */
void CHyperLink::PreSubclassWindow()
{
  //Notify mouse clicks via STN_CLICKED
DWORD dwStyle = GetStyle();
::SetWindowLong(GetSafeHwnd(), GWL_STYLE, dwStyle | SS_NOTIFY);

if (m_strURL.IsEmpty()) //Set the URL as the window text
  GetWindowText(m_strURL);

  //Check that the window text isn't empty. If it is, set it as the URL.
CString strWndText;
GetWindowText(strWndText);
if (strWndText.IsEmpty())
  {
  ASSERT(!m_strURL.IsEmpty());    //Initialize URL or static text first!
  SetWindowText(m_strURL);
  }

  //Create the font
LOGFONT lf;
GetFont()->GetLogFont(&lf);
lf.lfUnderline = (BYTE)IsUnderline();
m_Font.CreateFontIndirect(&lf);
SetFont(&m_Font);

PositionWindow();        // Adjust size of window to fit URL if necessary
SetDefaultCursor();      // Try and load up a "hand" cursor

  //Create the tooltip
CRect rect;
GetClientRect(rect);
m_ToolTip.Create(this);
m_ToolTip.AddTool(this, m_strURL, rect, TOOLTIP_ID);

CStatic::PreSubclassWindow();
}

/////////////////////////////////////////////////////////////////////////////
// CHyperLink operations

/*Initialize hyperlink

  Example:
    #include "KHypLink.h"  //CHyperLink class
      {
      ...
      CString strURL = _T("mailto:Name@Address.net")
      CHyperLink chlHyperLink;
      chlHyperLink.SetURL(strURL);
      }
 */
void CHyperLink::SetURL(CString& strURL)
{
m_strURL = strURL;
if (::IsWindow(GetSafeHwnd()))
  {
  PositionWindow();
  m_ToolTip.UpdateTipText(m_strURL, this, TOOLTIP_ID);
  }
}

//::SetColors()----------------------------------------------------------------
/*Set control's colors
 */
void CHyperLink::SetColors(COLORREF crTextColor,
                           COLORREF crDone,
                           COLORREF crInFocus //= -1
                           )
{
m_crTextColor    = crTextColor;
m_crDone = crDone;

if (crInFocus == -1)
	m_crInFocus = ::GetSysColor(COLOR_HIGHLIGHT);
else
	m_crInFocus = crInFocus;

  if (::IsWindow(m_hWnd))
      Invalidate();
}

//::SetDefCursor()-------------------------------------------------------------
/*Set default cursor
 */
void CHyperLink::SetDefCursor(HCURSOR hCursor)
{
m_hCursor = hCursor;
if (m_hCursor == NULL)
  SetDefaultCursor();
}

//::SetStyle()-----------------------------------------------------------------
/*Changes a style of the control.
 */
void CHyperLink::SetStyle(DWORD dwNewStyle //=HLNK_UNDERLINE | HLNK_AUTOFIT
                          )
{
if (::IsWindow(GetSafeHwnd()))
  {
  BOOL bUnderline = (((dwNewStyle &  HLNK_UNDERLINE) == HLNK_UNDERLINE) ? TRUE: FALSE);
  BOOL bAutoSize  = (((dwNewStyle &  HLNK_AUTOFIT  ) == HLNK_AUTOFIT  ) ? TRUE: FALSE);
  if (bUnderline != IsUnderline())
    {
    LOGFONT lf;
    GetFont()->GetLogFont(&lf);
    lf.lfUnderline = (BYTE) bUnderline;

    m_Font.DeleteObject();
    m_Font.CreateFontIndirect(&lf);
    SetFont(&m_Font);
    Invalidate();
    }
  if (bAutoSize != IsAutoFit())
    {
    if (bAutoSize)
      m_dwStyle = m_dwStyle | HLNK_AUTOFIT;
    else
      m_dwStyle = m_dwStyle & ~HLNK_AUTOFIT;
    PositionWindow();
    }
  }
m_dwStyle = dwNewStyle;
}

//::PositionWindow()-----------------------------------------------------------
/*Move and resize the window so that the window is the same size as
  the hyperlink text. This stops the hyperlink cursor being active when it is
  not directly over the text. If the text is left justified then the window is
  merely shrunk, but if it is centered or right justified then the window will
  have to be moved as well.

  History:
    Auto-size and window caption changes. Pål K. Tønder
 */
void CHyperLink::PositionWindow()
{
if (!::IsWindow(GetSafeHwnd()) || !IsAutoFit())
  return;

  //Get the current window position
CRect rect;
GetWindowRect(rect);
CWnd* pParent = GetParent();
if (pParent)
  pParent->ScreenToClient(rect);

  //Get the size of the window text
CString strWndText;
GetWindowText(strWndText);

CDC* pDC = GetDC();
CFont* pOldFont = pDC->SelectObject(&m_Font);
CSize Extent = pDC->GetTextExtent(strWndText);
pDC->SelectObject(pOldFont);
ReleaseDC(pDC);

  //Get the text justification via the window style
DWORD dwStyle = GetStyle();

  //Recalculate the window size and position based on the text justification
if (dwStyle & SS_CENTERIMAGE)
  rect.DeflateRect(0, (rect.Height() - Extent.cy)/2);
else
  rect.bottom = rect.top + Extent.cy;

if (dwStyle & SS_CENTER)
  rect.DeflateRect((rect.Width() - Extent.cx)/2, 0);
else if (dwStyle & SS_RIGHT)
  rect.left  = rect.right - Extent.cx;
else // SS_LEFT = 0, so we can't test for it explicitly
  rect.right = rect.left + Extent.cx;

  //Move the window
SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), SWP_NOZORDER);
}

//::SetDefaultCursor()---------------------------------------------------------
/*Loads default cursor from the WinHlp32.exe module. If member m_hCursor is
  NULL, this function retrieves cursor #106 from WinHlp32.exe, which is a hand
  pointer.

  History:
    Paul DiLascia's Jan 1998 MSJ
 */
void CHyperLink::SetDefaultCursor()
{
if (m_hCursor == NULL)  //No cursor handle - load a hand pointer
  {
    //Get the windows directory
  CString strWndDir;
  GetWindowsDirectory(strWndDir.GetBuffer(MAX_PATH), MAX_PATH);
  strWndDir.ReleaseBuffer();

  strWndDir += _T("\\WinHlp32.exe");
    //This retrieves cursor #106 from WinHlp32.exe, which is a hand pointer
  HMODULE hModule = LoadLibrary(strWndDir);
  if (hModule)
    {
    HCURSOR hHandCursor = ::LoadCursor(hModule, MAKEINTRESOURCE(106));
    if (hHandCursor)
      m_hCursor = CopyCursor(hHandCursor);
    }
  FreeLibrary(hModule);
  }
}

/*Shell API errors

  See Also: ShellAPI.h

  TODO: Internationalization (CShellException)
 */
void CHyperLink::ReportError(int nError)
{
    CString str;
    switch (nError) {
        case 0:                       str = "The operating system is out\nof memory or resources."; break;
        case SE_ERR_PNF:              str = "The specified path was not found."; break;
        case SE_ERR_FNF:              str = "The specified file was not found."; break;
        case ERROR_BAD_FORMAT:        str = "The .EXE file is invalid\n(non-Win32 .EXE or error in .EXE image)."; break;
        case SE_ERR_ACCESSDENIED:     str = "The operating system denied\naccess to the specified file."; break;
        case SE_ERR_ASSOCINCOMPLETE:  str = "The filename association is\nincomplete or invalid."; break;
        case SE_ERR_DDEBUSY:          str = "The DDE transaction could not\nbe completed because other DDE transactions\nwere being processed."; break;
        case SE_ERR_DDEFAIL:          str = "The DDE transaction failed."; break;
        case SE_ERR_DDETIMEOUT:       str = "The DDE transaction could not\nbe completed because the request timed out."; break;
        case SE_ERR_DLLNOTFOUND:      str = "The specified dynamic-link library was not found."; break;
        case SE_ERR_NOASSOC:          str = "There is no application associated\nwith the given filename extension."; break;
        case SE_ERR_OOM:              str = "There was not enough memory to complete the operation."; break;
        case SE_ERR_SHARE:            str = "A sharing violation occurred. ";
        default:                      str.Format("Unknown Error (%d) occurred.", nError); break;
    }
    str = "Unable to open hyperlink:\n\n" + str;
    AfxMessageBox(str, MB_ICONEXCLAMATION | MB_OK);
}

//::OnNcHitTest()--------------------------------------------------------------
#pragma warning(disable: 4100) // warning C4100: unreferenced formal parameter
/*The framework calls this member function for the CWnd object that contains
  the cursor every time the mouse is moved.
  Returns one of the mouse hit-test enumerated values.

  Note: Windows doesn't send WM_CTLCOLOR to bitmap static controls.
        Returning HTCLIENT achieves the same effect as SS_NOTIFY, but works in
        all cases
 */
UINT CHyperLink::OnNcHitTest(CPoint point)
{
return HTCLIENT;
}
#pragma warning(default: 4100) // warning C4100: unreferenced formal parameter

//::PostNcDestroy()------------------------------------------------------------
/*Called by the default OnNcDestroy member function after the window has been
 destroyed.
 This implemetation allows that a static control created with new opeartor
 deletes itself in same time when winodow had been destroyed, if the member
 m_bAutoDestroy is TRUE.
 */
void CHyperLink::PostNcDestroy()
{
if (m_bAutoDelete)
  delete this;
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  5    Biblioteka1.4         1/29/02 2:40:23 PM   Darko           Tag update
 *  4    Biblioteka1.3         8/16/01 11:37:33 PM  Darko           Update
 *  3    Biblioteka1.2         7/7/01 12:09:29 AM   Darko           Example
 *  2    Biblioteka1.1         6/8/01 10:50:54 PM   Darko           VSS
 *  1    Biblioteka1.0         8/13/00 2:56:38 PM   Darko           
 * $
 *****************************************************************************/
