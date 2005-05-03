/*$Workfile: KTipBox.cpp$: implementation file
  $Revision: 5$ $Date: 2003-09-22 22:27:17$
  $Author: Darko$

  Simple Text Tip Window
  Copyright: CommonSoft Inc.
  Jun '97 Darko Kolakovic
 */ 

#include "KTipBox.h" //CTipBox window

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTipBox
//::m_bRegistered--------------------------------------------------------------
/*Set to FALSE If wnd class is not  registered; TRUE if wnd class 
  is registered
*/
BOOL CTipBox::m_bRegistered = FALSE;

//::m_strClassName-------------------------------------------------------------
/*Windows class name
 */
CString CTipBox::m_strClassName;

//::CTipBox()------------------------------------------------------------------
/*Creates the text tip window.
  
  Example:
        //Create self destructive  object
      CTipBox* pNewBox = new CTipBox(pParent,TRUE);
      pNewBox->SetFont(pParent->GetFont());
      pNewBox->SetBkColor(LIGHTGREEN);
      pNewBox->SetTextColor(LIGHTRED);
        //Time-out in 5 sec.
      pNewBox->ShowTip("Message",&CPoint(Rect.left,Rect.top),5);
 */
CTipBox::CTipBox(CWnd* pParent,    //= NULL parent window or NULL
                 BOOL bSelfDestroy,//= FALSE autodelete object created with operator new
                 DWORD dwStyle     //= WS_POPUP window's style WS_POPUP or WS_CHILD
                 ) :
       //Windows 95 only: Background color for tooltip controls.
     m_crBkColor((COLORREF)::GetSysColor(COLOR_INFOBK)),
       //Windows 95 only: Text color for tooltip controls.
     m_crTextColor((COLORREF)::GetSysColor(COLOR_INFOTEXT)),
     m_bAutoDelete (bSelfDestroy),
     m_hFont(NULL),
     m_pFontContainer(NULL),
     m_nIDTimer (0),
     m_iShadeSize(0),
     m_pParent(pParent)

{
m_hBkBrush = ::CreateSolidBrush (m_crBkColor);
if (m_hBkBrush == NULL)
  {
  TRACE0 ("CTipBox::CTipBox - CreateSolidBrush failed.\n");
  AfxThrowResourceException();
  }

HWND hwndParent;
if (pParent != NULL)
  hwndParent = pParent->GetSafeHwnd();
else
  hwndParent = NULL;

dwStyle |= WS_BORDER;
if ((dwStyle & WS_POPUP) == WS_POPUP)
  {
  if(!CreateEx( 0,
              RegisterClass(),
              _T( "" ),
              dwStyle,
              0,0,0,0,
              hwndParent,
              (HMENU)NULL))
    {
    ASSERT(FALSE);
    AfxThrowResourceException();
    return;
    }
  }
else   //Create WS_CHILD
  {
  ASSERT(::IsWindow(pParent->m_hWnd));
  if (!Create (NULL,
            _T(""),
            dwStyle | WS_CHILD,
            CRect(0,0,0,0),
            pParent,
            0))
    {
    ASSERT(FALSE);
    AfxThrowResourceException();
    return;
    }
  }
}

CTipBox::~CTipBox()
{
if (m_hBkBrush)  //Deletes the brush
  DeleteObject (m_hBkBrush);
if (m_pFontContainer != NULL)
  delete m_pFontContainer;
}

IMPLEMENT_DYNAMIC( CTipBox, CWnd );

/////////////////////////////////////////////////////////////////////////////
// CTipBox diagnostics
#ifdef _DEBUG

//::Dump()---------------------------------------------------------------------
/*Dumps the contents of your object to a CDumpContext object. 

  Parameters:
    dc   The diagnostic dump context for dumping, usually afxDump.
 */
void CTipBox::Dump(CDumpContext& dc) const
{
dc << "CTipBox::Dump()\n\t"
   << "Class Name " << m_strClassName << (m_bRegistered ? " registered\n\t" : " not registered\n\t")
   << "Auto Delete " << m_bAutoDelete << "\n\t";
CWnd::Dump(dc);
}

#endif //_DEBUG


BEGIN_MESSAGE_MAP(CTipBox, CWnd)
  //{{AFX_MSG_MAP(CTipBox)
  ON_WM_PAINT()
  ON_MESSAGE(WM_SETTEXT, OnSetText)
  ON_WM_NCDESTROY()
  ON_WM_TIMER()
  ON_WM_ERASEBKGND()
  ON_WM_DESTROY()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//::RegisterClass()------------------------------------------------------------
/*The RegisterClass function registers a window class for subsequent use in 
  calls to the PreCreateWindow. If control is to be created from template, this
  function have to be invoked during application's initialization.
  If the function fails, the return value is NULL.
  To get extended error information, call GetLastError. 
  All window classes that an application registers are unregistered when it 
  terminates. 
  AfxRegisterWndClass() used for the registration maintains a list of unique 
  classes registered by your DLL and will automatically unregister then when 
  the DLL terminates. 
  */
LPCTSTR CTipBox::RegisterClass()
{
try
  {
  TRACE0("CTipBox::RegisterClass()\n");
  if (CTipBox::m_bRegistered)
    return (LPCTSTR)m_strClassName;

  if (m_hBkBrush == NULL)
    SetBkColor((COLORREF)::GetSysColor(COLOR_INFOBK),FALSE);

  LPCTSTR szClassName = ::AfxRegisterWndClass( WS_EX_TOOLWINDOW   | 
                                               CS_BYTEALIGNCLIENT | 
                                               CS_SAVEBITS        | 
                                               CS_HREDRAW         | 
                                               CS_VREDRAW         , 
                                               0, 
                                               NULL //Brush is not necessary, because
                                               );   //of OnEraseBkgnd()
  if (szClassName == NULL)
    AfxThrowResourceException();
  else
    {
    CTipBox::m_bRegistered = TRUE;
    m_strClassName = szClassName;
    return szClassName;
    }
  }
catch (CResourceException* r)
  {
  r->ReportError();
  r->Delete();
  }
return NULL;
}

//::SetTextColor()-------------------------------------------------------------
/*Sets the text color of a list view control.
 */
void CTipBox::SetTextColor(COLORREF crColor, //the new text color
                           BOOL bRedraw     //set the redraw flag
                           )
{
m_crTextColor = crColor;
if (( bRedraw ) && (m_hWnd != NULL))
  {
  ASSERT(::IsWindow(m_hWnd)); //Create wnd first!
  InvalidateRect(NULL);
  UpdateWindow();
  }
}

//::SetBkColor()---------------------------------------------------------------
/*Sets the background color of the edit control.
 */
void CTipBox::SetBkColor(
                         COLORREF crColor,     //the new background color
                         BOOL bRedraw         //set the redraw flag
                         )
{
  //Create a new brush
HBRUSH hBkBrush = ::CreateSolidBrush (crColor);
if (hBkBrush == NULL)
  {
  TRACE0 ("CTipBox::SetBkColor - CreateSolidBrush failed\n");
  AfxThrowResourceException();
  return;
  }
else
  {
  if (m_hBkBrush) //Delete the old brush
    DeleteObject (m_hBkBrush);
  m_crBkColor = crColor;
  m_hBkBrush = hBkBrush;
  }


if(bRedraw)
  {
  InvalidateRect(NULL);
  UpdateWindow();
  }
}

//::SetFont()------------------------------------------------------------------
#include "D_Font.h"   //CAppFont class
#include "D_GFont.h"  //font name
/*Set the text font. If pointer to new font is NULL, default font is set.
 */
void CTipBox::SetFont(CFont* pNewFont)
{
try
  {
  TRACE0("CTipBox::SetFont()\n");
  if (pNewFont != NULL)
    {
    if (pNewFont->GetSafeHandle() != NULL)
      {
      CWnd::SetFont(pNewFont);
      m_hFont = (HFONT)pNewFont->GetSafeHandle();
      }
    }
  else
    {
    if (m_pFontContainer != NULL)
      delete m_pFontContainer;
    m_pFontContainer = (CFont*) new CFont;

    CAppFont::CreateFont(NULL, 
                         *m_pFontContainer,    //result
                         g_szfontSansSerif,
                         8          //font height
                         );
    CWnd::SetFont(m_pFontContainer);
    m_hFont = (HFONT)m_pFontContainer->GetSafeHandle();
    }

  }  
catch(CResourceException* r)
  {
  r->ReportError();  
  r->Delete();
  TRACE0("\tFont creation failed!\n");
  }
}

//::Show()---------------------------------------------------------------------
/*Show text tip. Text tip will be visible for the iSec seconds, or if iSec = -1
  until windows is not destroyed.
 */
void CTipBox::ShowTip(UINT IDS_TipText,     //text tip resource ID
                      LPPOINT lpptPos,      //position is in screen coordinates
                                            //for the topmost windows or in 
                                            //client coordinates for the child 
                                            //windows
                      const int& iSec       //time interval in [s] (-1 default)
                      )
{
CString strTipText;
if(strTipText.LoadString(IDS_TipText))
  ShowTip((LPCTSTR)strTipText,lpptPos,iSec);
#ifdef _DEBUG
else
  AfxMessageBox(_T("Error Loading String: IDS_TipText"));
#endif
}

void CTipBox::ShowTip(LPCTSTR strTipText,   //text tip string
                      LPPOINT lpptPos,      //position is in screen coordinates
                                            //for the topmost windows or in 
                                            //client coordinates for the child 
                                            //windows
                      const int& iSec       //time interval in [s] (-1 default)
                      )
{
TRACE0("CTipBox::ShowTip()\n");
ASSERT(strTipText != NULL);
if(_tcsclen(strTipText) == 0)
  {
  TRACE0("CTipBox::ShowTip(): Warning: Showing an empty string.\n");
  return; //Nothing to do
  }
ShowWindow(SW_HIDE);

SetWindowText(strTipText);

  //Insure that the text tip is visible on the desktop window
CRect rtFrame;
GetWindowRect(&rtFrame);
CRect rtDesktop;
::GetWindowRect(::GetDesktopWindow(),&rtDesktop);
if (lpptPos->y < 0)  //Left side have to be on the desktop window
  lpptPos->y = 0;
if ((lpptPos->y + rtFrame.Height()) > rtDesktop.bottom)
  lpptPos->y = rtDesktop.bottom - (rtFrame.Height() + 1);
if (lpptPos->x < 0)
  lpptPos->x = abs(lpptPos->x) - (rtFrame.Width() / 2);
if (lpptPos->x > rtDesktop.right)
  lpptPos->x = rtDesktop.right - (rtFrame.Width() + 1);


SetWindowPos(&wndTop, lpptPos->x, lpptPos->y, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE );
UpdateWindow();

  //Set timer; after iSec [s] elapsed TipBox will hide or destruct itself
if ((iSec > 0) && (m_nIDTimer == 0))
  {          
  m_nIDTimer = SetTimer(IDT_TEXTTIP,iSec*1000, NULL); //Install a system time
  if ( m_nIDTimer == 0)
    {
    TRACE0("\tTimer install failure\n");
    ASSERT(FALSE);
    }
  ASSERT(m_nIDTimer == IDT_TEXTTIP);
  }
ShowWindow(SW_SHOWNOACTIVATE);
}

/////////////////////////////////////////////////////////////////////////////
// CTipBox message handlers

//::OnPaint()------------------------------------------------------------------
/*The framework calls this member function when Windows or an application makes
  a request to repaint a portion of an application’s window. 
  The WM_PAINT message is sent when the UpdateWindow or RedrawWindow member 
  function is called.

  History:
    28.2.99 Added shade D.K.
*/
void CTipBox::OnPaint() 
{
CPaintDC dc(this); // device context for painting
extern BOOL ShadeRect(HDC hDC,LPRECT lpRect);

CRect rectClient;
GetClientRect(rectClient);

HGDIOBJ hfontOld = ::SelectObject(dc.GetSafeHdc(),m_hFont);
dc.SetTextAlign(TA_CENTER);
dc.SetBkMode(TRANSPARENT);
dc.SetTextColor(m_crTextColor);

CString strTextTip;
GetWindowText(strTextTip);
CSize size = dc.GetTextExtent(strTextTip);
if(m_iShadeSize > 0)
  {
  CRect rect;
  GetWindowRect(&rect);
  rect.OffsetRect(m_iShadeSize,m_iShadeSize);
  m_pParent->ScreenToClient(&rect);
  CDC* pParentDC = m_pParent->GetDC();
  ShadeRect(pParentDC->GetSafeHdc(), &rect);
  }
dc.TextOut(rectClient.right /2, (rectClient.bottom - size.cy )/2,strTextTip);
::SelectObject(dc.GetSafeHdc(),hfontOld);
}

//::OnSetText()----------------------------------------------------------------
/*An application sends a WM_SETTEXT message to set the text of a window. 
  The return value is TRUE if the text is set. It is FALSE if insufficient space
  is available to set the text.
 */
LRESULT CTipBox::OnSetText(WPARAM,      //not used; must be zero 
                           LPARAM lpsz  //(LPCTSTR) address of window-text string 
                          )

{
TRACE0("CTipBox::OnSetText()\n");
const int XMARGINFACTOR = 5;
const int YMARGINFACTOR = 4;
CRect Rect;
GetWindowRect(&Rect);

CClientDC dc(this);
CFont *pfontOld = dc.SelectObject(CFont::FromHandle(m_hFont));
CSize sizeText = dc.GetTextExtent((LPCSTR)lpsz, _tcslen((LPCSTR)lpsz));
Rect.right = Rect.left + sizeText.cx + 
             (XMARGINFACTOR*GetSystemMetrics(SM_CXBORDER));
Rect.bottom = Rect.top + sizeText.cy + 
             (YMARGINFACTOR*GetSystemMetrics(SM_CYBORDER));
MoveWindow(&Rect);
dc.SelectObject(pfontOld);

return CWnd::Default();
}

//::OnTimer()------------------------------------------------------------------
/*The framework calls this member function after each interval specified in the
  SetTimer member function used to install a timer. The DispatchMessage Windows
  function sends a WM_TIMER message when no other messages are in 
  the application’s message queue.

  Note: Timer ID is fixed to IDT_TEXTTIP = 26788 D.K.
*/
void CTipBox::OnTimer(UINT nIDEvent //the identifier of the timer.

                      ) 
{
if(nIDEvent == IDT_TEXTTIP)
  {
  TRACE1("CTipBox::OnTimer(TimerID = %d)\n",nIDEvent);
  ASSERT(KillTimer(nIDEvent));
  m_nIDTimer = 0;
  if (m_bAutoDelete)
    DestroyWindow();
  else
    ShowWindow(SW_HIDE);
  }
else
  {  
  CWnd::OnTimer(nIDEvent);
  }
}

//::OnEraseBkgnd()-------------------------------------------------------------
/*The framework calls this member function when the CWnd object background needs
  erasing (for example, when resized). It is called to prepare an invalidated 
  region for painting. The default implementation erases the background using 
  the window class background brush specified by the hbrBackground member of 
  the window class structure. 
 */
BOOL CTipBox::OnEraseBkgnd(CDC* pDC)
{
  //Set brush to desired background color
  //Save the old brush
ASSERT(m_hBkBrush != NULL);
HGDIOBJ hOldBrush = ::SelectObject(pDC->GetSafeHdc(),m_hBkBrush);

  //Get the current clipping boundary
CRect rect;
pDC->GetClipBox(&rect);

  //Erase the area needed
pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(),
     PATCOPY);
  //Select the old brush back
::SelectObject(pDC->GetSafeHdc(),hOldBrush); 
return TRUE;  //Message handled
}

//::OnNcDestroy()--------------------------------------------------------------
/*Called by the framework when the nonclient area is being destroyed, and is 
  the last member function called when the Windows window is destroyed. 
 */
void CTipBox::OnNcDestroy() 
{
try
  {
  TRACE0("CTipBox::OnNcDestroy()\n");
  if (m_nIDTimer != 0)
    KillTimer(m_nIDTimer);

  CWnd::OnNcDestroy();
  ASSERT(m_hWnd == NULL);


  if(m_bAutoDelete)
    delete this;//Delete this object since it won't be destroyed otherwise
  }
catch(CException* e)
  {
  e->ReportError();  
  e->Delete();
  }
}

void CTipBox::OnDestroy() 
{
if(m_iShadeSize > 0)
  {
  CRect rect;
  GetWindowRect(&rect);
  rect.InflateRect(m_iShadeSize,m_iShadeSize);
  m_pParent->ScreenToClient(&rect);
  m_pParent->InvalidateRect(&rect);
  m_pParent->UpdateWindow();
  }

CWnd::OnDestroy();
}
