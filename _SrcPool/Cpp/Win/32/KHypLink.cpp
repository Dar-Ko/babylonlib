/*$Workfile: KHypLink.cpp$: implementation file
  $Revision: 9$ $Date: 2004-10-01 21:35:03$
  $Author: Darko$

  HyperLink static control.
  Copyright: CommonSoft Inc.
  D. Kolakovic May 98 Documentation
 */ 

#include "stdafx.h"

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

CHyperLink::CHyperLink(bool bAutoDelete //[in] = false if true allows that
                                        //a control created with new operator
                                        //deletes itself in same time when 
                                        //window had been destroyed.
                       ) :
    m_hCursor       (NULL),               // No cursor as yet
    m_crTextColor   (LIGHTBLUE),
    m_crAccessed    (MAGENTA),
    m_crInFocus     (::GetSysColor(COLOR_3DHILIGHT)),
    m_bInFocus      (FALSE),             //Cursor not yet over control
    m_bAccessed     (FALSE),             //Hasn't been visited yet.
    m_dwStyle       (HLNK_UNDERLINE|HLNK_AUTOFIT),
    m_bAutoDelete   (bAutoDelete)
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

///////////////////////////////////////////////////////////////////////////////
// CHyperLink message handlers

//-----------------------------------------------------------------------------
/*Called by class CWinApp to translate window messages before they are
  dispatched to the TranslateMessage and DispatchMessage Windows functions.

  The MSG structure contains message information from a thread's message queue. 

      typedef struct tagMSG 
        {
        HWND hwnd;    //window whose window procedure receives the message.
        UINT message; //message number.
        WPARAM wParam;//additional information about the message.
        LPARAM lParam;//additional information about the message.
        DWORD time;   //time at which the message was posted.
        POINT pt;     //screen coordinates of the cursor position, when 
                      //the message was posted.
        } MSG;


  Returns: nonzero if the message was translated and should not be dispatched; 
  0 if the message was not translated and should be dispatched.
 */
BOOL CHyperLink::PreTranslateMessage(MSG* pMsg //[in] structure that contains 
                                               //the message to process.
                                     )
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
int iResult = 0xFFFF; //Success code
m_bAccessed = ((iResult = ::SpawnURL(m_strURL, SW_SHOWNORMAL)) > 32);
if (!m_bAccessed)
  {
  MessageBeep(MB_ICONEXCLAMATION);     // Unable to follow link
  ReportError(iResult);
  }
else
  SetAccessed();                        // Repaint to show visited colour
}

//::CtlColor()-----------------------------------------------------------------
#pragma warning( disable : 4100 ) //Warning :unreferenced formal parameter
/*Handles WM_CTLCOLOR reflected message to set colors of the hyperlink text.
  For non-text controls, does nothing.
 */
HBRUSH CHyperLink::CtlColor(CDC* pDC,      //[in] current device context
                            UINT nCtlColor //[in] specifyies the type of control
                            )
{
ASSERT(nCtlColor == CTLCOLOR_STATIC);
DWORD dwStyle = GetStyle();
if ((dwStyle & 0xFF) <= SS_RIGHT) //Check if control is with text
  {
  if (m_bInFocus)
    pDC->SetTextColor(m_crInFocus);
  else if (IsAccessed())
    pDC->SetTextColor(m_crAccessed);
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

  nFlags parameter can be any combination of the following values:

      MK_CONTROL   Set if the CTRL key is down.
      MK_LBUTTON   Set if the left mouse button is down.
      MK_MBUTTON   Set if the middle mouse button is down.
      MK_RBUTTON   Set if the right mouse button is down.
      MK_SHIFT     Set if the SHIFT key is down.

 */
void CHyperLink::OnMouseMove(UINT nFlags, //[in] indicates whether various virtual
                             //keys are down
                             CPoint point //[in] coordinates of the cursor
                             )
{
CStatic::OnMouseMove(nFlags, point);

if (m_bInFocus)        // Cursor is currently over control
  {
  CRect rect;
  GetClientRect(rect);

  if (!rect.PtInRect(point))
    {
    m_bInFocus = false;
    ReleaseCapture();
    RedrawWindow();
    }
  }
else                      // Cursor has just moved over control
  {
  m_bInFocus = true;
  RedrawWindow();
  SetCapture();
  }
}

//::OnSetCursor()--------------------------------------------------------------
/*The framework calls this member function if mouse input is not captured and
  the mouse causes cursor movement within the CWnd object.
  This implemetation changes cursor to m_hCursor.
 */
BOOL CHyperLink::OnSetCursor(CWnd*, //[unused] pointer to the window 
                             //that contains the cursor. The pointer may be 
                             //temporary and should not be stored for later use. 
                             UINT,//nHitTest [unused]  hit-test area code. 
                             //The hit test determines the cursor's location.
                             //See also: Mouse Enumerated Values
                             UINT //message [unused]  mouse message number
                             )
{
if (m_hCursor)
  {
  ::SetCursor(m_hCursor);
  return TRUE;
  }
return FALSE;
}

//::OnKillFocus()--------------------------------------------------------------
/*The framework calls this member function immediately before losing the input
  focus.
 */
void CHyperLink::OnKillFocus(CWnd* pNewWnd //[in] pointer to the window that
                                      //receives the input focus (may be
                                      //temporary) or NULL. 
                             )
{
CStatic::OnKillFocus(pNewWnd);

m_bInFocus = false;
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

/*Changes the hyperlink reference. The reference is a Uniform Resource 
  Locator string. This implementation also updates a tooltip binded to 
  the hyperlink control.
  The Uniform Resource Locators (URLs) are formatted strings or streams 
  that an Internet application can use to reference resources on the Internet
  or an intranet.
  URL string has following form:
  
    protocol:resource, //host/localinfo, 
    where protocol  specifies the means of accessing the object, 
                    such as HTTP or FTP;
          resource     is a string passed to the protocol handler.

  Resource in case of HTTP or FTP has following form:

      //host/localinfo
      where host      specifies the remote location where the object resides and 
            localinfo is a string, often a file name at the remote location.

  Example:
    #include "KHypLink.h"  //CHyperLink class
      {
      ...
      CString strUrl = _T("mailto:Name@Address.net")
      CHyperLink chlHyperLink;
      chlHyperLink.SetUrl(strUrl);
      }
 */
void CHyperLink::SetUrl(CString& strUrl //[in] Uniform Resource Locator
                        )
{
m_strURL = strUrl;
if (::IsWindow(GetSafeHwnd()))
  {
  PositionWindow();
  m_ToolTip.UpdateTipText(m_strURL, this, TOOLTIP_ID);
  }
}

//::SetColors()----------------------------------------------------------------
/*Set control's colors
 */
void CHyperLink::SetColors(COLORREF crTextColor, //[in] color of the hyperlink 
                                                 //text
                           COLORREF crAccessed,  //[in] color of the accessed 
                                                 //hyperlink
                           COLORREF crInFocus    //[in] = -1 color of the hyperlink 
                                                 //text when cursors hovers over;
                                                 //default color is COLOR_HIGHLIGHT
                           )
{
m_crTextColor = crTextColor;
m_crAccessed  = crAccessed;

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
void CHyperLink::SetDefCursor(HCURSOR hCursor //[in] handle of the new 
                                              //default cursor
                             )
{
m_hCursor = hCursor;
if (m_hCursor == NULL)
  SetDefaultCursor();
}

//::SetStyle()-----------------------------------------------------------------
/*Changes the style of the control.

  See also: HLNK_STYLE
 */
void CHyperLink::SetStyle(DWORD dwNewStyle //[in]=HLNK_UNDERLINE | HLNK_AUTOFIT one
                          //or more outlook flags
                          )
{
if (::IsWindow(GetSafeHwnd()))
  {
  bool bUnderline = ((dwNewStyle &  HLNK_UNDERLINE) == HLNK_UNDERLINE);
  bool bAutoSize  = ((dwNewStyle &  HLNK_AUTOFIT  ) == HLNK_AUTOFIT  );
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

//-----------------------------------------------------------------------------
/*Shell API errors

  See Also: ShellAPI.h

  TODO: Internationalization (CShellException)
 */
void CHyperLink::ReportError(int nError //[in] error code
                             )
{
    CString str;
    switch (nError) {
        case 0:                      str = _T("The operating system is out\nof memory or resources."); break;                                              // 0
        // ERROR_FILE_NOT_FOUND = SE_ERR_FNF = 2 The specified file was not found.
        case SE_ERR_FNF:             str = _T("The specified file was not found."); break;                                                                 // 2
        // ERROR_PATH_NOT_FOUND = SE_ERR_PNF = 3 The specified path was not found.
        case SE_ERR_PNF:             str = _T("The specified path was not found."); break;                                                                 // 3
        case SE_ERR_ACCESSDENIED:    str = _T("The operating system denied\naccess to the specified file."); break;                                        // 5
        case SE_ERR_OOM:             str = _T("There was not enough memory to complete the operation."); break;                                            // 8
        case ERROR_BAD_FORMAT:       str = _T("The .EXE file is invalid\n(non-Win32 .EXE or error in .EXE image)."); break;                                //11
        case SE_ERR_SHARE:           str = _T("A sharing violation occurred.");                                                                           //26
        case SE_ERR_ASSOCINCOMPLETE: str = _T("The filename association is\nincomplete or invalid."); break;                                               //27
        case SE_ERR_DDETIMEOUT:      str = _T("The DDE transaction could not\nbe completed because the request timed out."); break;                        //28
        case SE_ERR_DDEFAIL:         str = _T("The DDE transaction failed."); break;                                                                       //29
        case SE_ERR_DDEBUSY:         str = _T("The DDE transaction could not\nbe completed because other DDE transactions\nwere being processed."); break; //30
        case SE_ERR_NOASSOC:         str = _T("There is no application associated\nwith the given filename extension."); break;                            //31
        case SE_ERR_DLLNOTFOUND:     str = _T("The specified dynamic-link library was not found."); break;                                                 //32
        default:                     str.Format(_T("Unknown Error (%d) occurred."), nError); break;
    }
    str = _T("Unable to open hyperlink:\n\n") + str;
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
UINT CHyperLink::OnNcHitTest(CPoint point //[in] screen coordinates of the cursor
                            )
{
return HTCLIENT;
}
#pragma warning(default: 4100) // warning C4100: unreferenced formal parameter

//::PostNcDestroy()------------------------------------------------------------
/*Called by the default OnNcDestroy member function after the window has been
 destroyed.
 This implemetation allows that a static control created with new operator
 deletes itself in same time when window had been destroyed, if the member
 m_bAutoDestroy is true.
 */
void CHyperLink::PostNcDestroy()
{
if (m_bAutoDelete)
  delete this;
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  9    Biblioteka1.8         2004-10-01 21:35:03  Darko           stdafx.h
 *  8    Biblioteka1.7         2003-11-03 12:20:04  Darko           Replaced BOOL
 *       with bool
 *  7    Biblioteka1.6         2003-09-22 21:26:15  Darko           formatting
 *  6    Biblioteka1.5         2003-08-06 02:46:37  Darko           Prepared for
 *       Unicode 
 *  5    Biblioteka1.4         2002-01-29 14:40:23  Darko           Tag update
 *  4    Biblioteka1.3         2001-08-16 23:37:33  Darko           Update
 *  3    Biblioteka1.2         2001-07-07 00:09:29  Darko           Example
 *  2    Biblioteka1.1         2001-06-08 22:50:54  Darko           VSS
 *  1    Biblioteka1.0         2000-08-13 14:56:38  Darko           
 * $
 *****************************************************************************/
