/*$Workfile: KDateCrl.cpp$: implementation file
  $Revision: 1.1 $ $Date: 2002/09/06 22:09:08 $
  $Author: ddarko $

  Date Edit Control
  Copyright: CommonSoft Inc.
  Darko Kolakovic Dec '97
 */
 
#include "KDateCrl.h" //CDateCtrl class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
const int CST_YEARSTART = 1600;
const int CST_YEAREND   = 2137;

/////////////////////////////////////////////////////////////////////////////
// CDateCtrl

LPCTSTR CDateCtrl::DCTRLSTRCLASSNAME = "DDateEditCtrl";   //Window class name
const int GAP_X = 6; //Gap between columns in the Day Table
const int GAP_Y = 4; //Gap between rows in the Day Table
  //Month length table
static const UINT s_MonthLength[12] =
  {  31, 28, 31, 30, 31, 30,
     31, 31, 30, 31, 30, 31 };

//::m_bRegistered-----------------------------------------------------------
/*Set to FALSE If wnd class is not  registered; TRUE if wnd class
  is registered
 */
BOOL CDateCtrl::m_bRegistered = FALSE;

//::DCtrlWndProc()-------------------------------------------------------------
/*Handle window messages for the control by creating MFC object which will trap
  the messages. The first message sent to any window when it is initially
  created (dynamically or from dialog template) is WM_NCCREATE. If window class
  is properly registered, the dialog manager constructing a control from a
  template calls ::CreateWindow() with the class name for the control which
  sends messages to control's procedure and first message is WM_NCCREATE.
 */
LRESULT CALLBACK CDateCtrl::DCtrlWndProc(HWND hWnd, UINT uiMsg,
                                           WPARAM wParam, LPARAM lParam)
{
switch (uiMsg)
  {
  case WM_NCCREATE:
    {
    TRACE0("CDateCtrl::DCtrlWndProc() WM_NCCREATE\n");
    //Create a C++ object to handle the messages
    CDateCtrl* pCtl;
    if( ((LPCREATESTRUCT)lParam)->lpCreateParams  == NULL)  //Create object
      {
      pCtl = new CDateCtrl;
      ASSERT_VALID(pCtl);
      ASSERT(pCtl->m_hWnd == NULL);     //Only attach once, detach on destroy
      pCtl->m_bAutoDelete = TRUE;
       //Attach the window handle to the new object to reroute the messages
      if(!pCtl->SubclassWindow(hWnd))
        {
        ASSERT(FALSE);
        return FALSE;
        }
      }
    else              //Object has been created
      {
      pCtl = (CDateCtrl*)((LPCREATESTRUCT)lParam)->lpCreateParams;
      ASSERT(pCtl);
      ASSERT_VALID(pCtl);
      }

    ASSERT((CDateCtrl*)CWnd::FromHandlePermanent(hWnd) == pCtl);
    }
    break;

  default:  //Default message handling
    return ::DefWindowProc(hWnd, uiMsg, wParam, lParam);
    }

return TRUE;
}

/*Construction ----------------------------------------------------------------
 */
IMPLEMENT_DYNAMIC(CDateCtrl, CWnd)
  //Default constructor
CDateCtrl::CDateCtrl() :
  m_bAutoDelete (FALSE),
  m_hAccel(NULL),  //Accelerator table
  m_bHasBeenModified(FALSE)
{
CTime CurrentDate(CTime::GetCurrentTime());
m_iDay   = CurrentDate.GetDay()  ;
m_iMonth = CurrentDate.GetMonth();
m_iYear  = CurrentDate.GetYear() ;

SetFirstAndLastDay();  //Set week day of the 1st day
}

CDateCtrl::CDateCtrl(const POINT& pos, //position in client coordinates of pParentWnd.
                     CWnd* pParentWnd, //the parent window
                     UINT nID //= IDD_DDATEEDITCTRL the ID of the child window
                     ):
  m_bAutoDelete (FALSE),
  m_hAccel(NULL),  //Accelerator table
  m_bHasBeenModified(FALSE)
{
CTime CurrentDate(CTime::GetCurrentTime());
m_iDay   = CurrentDate.GetDay()  ;
m_iMonth = CurrentDate.GetMonth();
m_iYear  = CurrentDate.GetYear() ;
SetFirstAndLastDay();  //Set week day of the 1st day
VERIFY(Create(pos,pParentWnd,nID));
}

CDateCtrl::~CDateCtrl()
{
}

//::RegisterClass()------------------------------------------------------------
/*The RegisterClass function registers a window class for subsequent use in
  calls to the PreCreateWindow. If control is to be created from template, this
  function have to be invoked during application's initialization.
  If the function fails, the return value is
  FALSE. To get extended error information, call GetLastError.
  All window classes that an application registers are unregistered when it
  terminates. When using RegisterClass in a DLL, you must insure that all
  classes are unregistered when the DLL is terminated (in your DllMain
  function). Failure to do so may cause RegisterClass to fail unexpectedly
  when your DLL is used by another client application.
 */
BOOL CDateCtrl::RegisterClass()
{
if (!CDateCtrl::m_bRegistered)
  {
    //Register the window class of the control
  WNDCLASS wc;
  wc.style = CS_GLOBALCLASS |
             CS_SAVEBITS    |
             CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = CDateCtrl::DCtrlWndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = NULL;
  wc.hIcon = NULL;
  wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE+1);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = CDateCtrl::DCTRLSTRCLASSNAME;

  if (!::RegisterClass(&wc))
    {
    ASSERT(0);
    return FALSE;
    }
  CDateCtrl::m_bRegistered = TRUE;  //Wnd class is registered
  TRACE0("CDateCtrl::RegisterClass() OK\n");
  }

return CDateCtrl::m_bRegistered;
}

//::SetFont()------------------------------------------------------------------
#include "UTextMtr.h" //CTextMetric class
/*Sets the control’s current font to the specified font
  Parameters:
  nPointSize   Requested font height in tenths of a point. (For instance, pass
               120 to request a 12-point font.)
  lpszFaceName A CString or pointer to a null-terminated string that specifies
               the typeface name of the font. The length of this string must not
               exceed 30 characters.
 */
void CDateCtrl::SetFont(int nPointSize,   //font height in tenths of a point
                        LPCTSTR lpszFaceName //the typeface name
                        )
{
CWindowDC DC((GetSafeHwnd() != NULL) ? this : NULL);

if (m_Font.GetSafeHandle() != NULL)
  m_Font.Detach();//Detach a Windows GDI object from a CGdiObject object

m_Font.CreatePointFont(nPointSize,lpszFaceName,&DC);
CFont* pOldFont = DC.SelectObject(&m_Font);
CTextMetric tm(&DC);
m_dxFont = tm.tmAveCharWidth;
m_dyFont = tm.GetLineHeight();
m_posDay.x = GAP_X / 2;   //Position of the 'Day of the month' box
m_posDay.y = 2 *(m_dyFont+GAP_Y);
DC.SelectObject(pOldFont);
}

//::SelectDay()----------------------------------------------------------------
/*Highlight the selected day of the month
 */
void CDateCtrl::SelectDay(CDC* pDC, UINT nDayOfMonth)
{
ASSERT (pDC != NULL);
ASSERT((nDayOfMonth > 0) && (nDayOfMonth < 32)); //Month have 31 day (0 based)

nDayOfMonth--;
TCHAR strDay[3];

CRect rectDay;
rectDay.left   = m_posDay.x + (((nDayOfMonth+m_nFirstDay)%7) * (2*m_dxFont+GAP_X)) + 2;
rectDay.top    = m_posDay.y+( (nDayOfMonth+m_nFirstDay)/7) *(m_dyFont+GAP_Y);
rectDay.right  = rectDay.left +(2*m_dxFont+GAP_X)+GAP_X/2;
rectDay.bottom = rectDay.top  +(m_dyFont+GAP_Y)+1;

CBrush brushDay(GetSysColor(COLOR_HIGHLIGHT));
CBrush* pOldBrush = pDC->SelectObject(&brushDay);
int iOldMode = pDC->SetBkMode(TRANSPARENT);
COLORREF rgbOldText = pDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));

pDC->Rectangle(rectDay);
_itoa(nDayOfMonth+1,strDay,10);
pDC->TextOut(rectDay.right-GAP_X/2 -2,
             rectDay.top,
             strDay,strlen(strDay));

pDC->SetTextColor(rgbOldText);
pDC->SetBkMode(iOldMode);
pDC->SelectObject(pOldBrush);
}

//::SetFirstAndLastDay()-------------------------------------------------------
#include "UFileTme.h" //CFileTime class
/*Set the week day of the first day of the current month based on the current
  local time and number of the days in the month [28,31]
  0 = Sunday, 1 = Monday, ..., 6 = Saturday.
 */
void CDateCtrl::SetFirstAndLastDay()
{
SYSTEMTIME Month_1st;
ZeroMemory(&Month_1st, sizeof(SYSTEMTIME));
Month_1st.wYear = (WORD)m_iYear ;
Month_1st.wMonth= (WORD)m_iMonth;
Month_1st.wDay  = (WORD)1       ;
CFileTime cftTemp(&Month_1st);
Month_1st =(SYSTEMTIME)cftTemp;
m_nFirstDay = (UINT)(Month_1st.wDayOfWeek);
m_nLastDay  = s_MonthLength[m_iMonth-1];
if (m_iMonth == 2)  //In February check leap year
  {
  if (IsLeapYear(m_iYear))
    m_nLastDay++;
  }
}

//::IsLeapYear()---------------------------------------------------------------
/*Check if the year is leap year
 */
BOOL CDateCtrl::IsLeapYear(const int& iYear)
{
TRACE2("CDateCtrl::IsLeapYear(%d) %s\n",iYear,
       ((iYear&3) == 0 && iYear%100 != 0 || iYear % 400 == 0)?"TRUE":"FALSE");
return (iYear&3) == 0 && iYear%100 != 0 || iYear % 400 == 0;
}

BEGIN_MESSAGE_MAP(CDateCtrl, CWnd)
	//{{AFX_MSG_MAP(CDateCtrl)
	ON_WM_NCDESTROY()
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_NCCREATE()
	ON_WM_RBUTTONUP()
  ON_COMMAND(IDOK, OnOK)
  ON_COMMAND(IDCANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDateCtrl message handlers
//::Create()-------------------------------------------------------------------
#include "D_GFont.h"  //font names globals
/*Initializes the control’s class name and window name and registers values for
  its style, parent, and ID.
  This functions is used when control is created dynamically by using
  the constructor CDateCtrl() and as second step, by calling the Create()
  member function of newly created CDateCtrl.
  Function calls base class Create() member, which invokes PreCreateWindow() and
  OnNcCreate()

    Date    Range
    nYear   1600–2038
    nMonth  1–12
    nDay    1–31

 TODO: International support (CDateCtrl)

  Example:
    int CParentView::OnCreate(LPCREATESTRUCT lpCreateStruct)
      {
	    if (CView::OnCreate(lpCreateStruct) == -1)
		    return -1;

      m_Date.Create(CPoint(15,15),this);
	    return 0;
      }
 */
BOOL CDateCtrl::Create(const POINT& pos,//=(0,0) position in client coordinates of pParentWnd.
                       CWnd* pParentWnd,//=NULL the parent window
                       UINT nID,        //=IDD_DDATEEDITCTRL the ID of the child window
                       DWORD dwStyle    //=WS_VISIBLE|WS_BORDER the window style attributes
                                      )
{
TRACE0("CDateCtrl::Create()\n");

CWnd* pWnd = this;
     //Attach the window handle to the new object to reroute the messages
ASSERT(m_hWnd == NULL);     // only attach once, detach on destroy
ASSERT(FromHandlePermanent(m_hWnd) == NULL);

HWND hwndParent;
if (pParentWnd != NULL)
  {
  ASSERT(::IsWindow(pParentWnd->m_hWnd));
  dwStyle |= WS_CHILD;
  hwndParent = pParentWnd->GetSafeHwnd();
  }
else
  hwndParent = NULL;

SetFont(80,g_szfontSansSerif);  //Set control's font
const int SPIN_WIDTH = 2*m_dxFont+ GAP_X;
  //The CWnd::Create() function sends WM_NCCREATE, WM_NCCALCSIZE, and WM_CREATE
  //messages to the window being created.
if(!pWnd->CreateEx(WS_EX_CLIENTEDGE | WS_EX_CONTROLPARENT,
                    DCTRLSTRCLASSNAME,NULL,
                  dwStyle,pos.x,pos.y,
                  7 *(2*m_dxFont+GAP_X)+ 3*(GAP_X),
                  8 *(m_dyFont+GAP_Y)+3*GAP_Y,
                  hwndParent,(HMENU)nID))
  {
  TRACE0("\tCreateEx() failure\n");
  return FALSE;
  }
  //Create controls
const DWORD dwSpinStyle = WS_VISIBLE | UDS_WRAP |
                      UDS_SETBUDDYINT | UDS_ALIGNRIGHT |
                      UDS_ARROWKEYS | UDS_HORZ | UDS_NOTHOUSANDS;
const DWORD dwEditStyle = WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP | ES_AUTOHSCROLL ;

CRect rect(GAP_X/2,GAP_Y/2,2*m_dxFont+ GAP_X + GAP_X/2 + SPIN_WIDTH,m_dyFont+GAP_Y/2);
if (!m_editMonth.Create(dwEditStyle,rect,this,IDC_DDEDITMONTH))
  {
  TRACE0("\tCreate edit() failure\n");
  return FALSE;
  }

rect.left = rect.right + GAP_X;  //Offset Year edit ctrl position
rect.right = rect.left + 4*m_dxFont+ GAP_X + GAP_X/2 + SPIN_WIDTH;
if (!m_editYear.Create(dwEditStyle,rect,this,IDC_DDEDITYEAR))
  {
  TRACE0("\tCreate edit() failure\n");
  return FALSE;
  }

if(!m_spinMonth.Create(dwSpinStyle,rect,this,IDC_DDSPINMONTH))
  {
  TRACE0("\tCreate spin() failure\n");
  return FALSE;
  }

if(!m_spinYear.Create(dwSpinStyle,rect,this,IDC_DDSPINYEAR))
  {
  TRACE0("\tCreate spin() failure\n");
  return FALSE;
  }

  //Set controls parameters
m_spinMonth.SetBuddy(&m_editMonth);
m_spinMonth.SetRange(1,12);
m_spinMonth.SetPos(m_iMonth);
m_spinYear.SetBuddy(&m_editYear);

m_spinYear.SetRange(CST_YEARSTART,CST_YEAREND);
m_spinYear.SetPos(m_iYear);

m_editMonth.SetFont(GetFont());
m_editYear.SetFont(GetFont());

  //Create Day Table header
rect.left = m_posDay.x;
rect.top += rect.bottom + GAP_Y;
rect.right = 7 *(2*m_dxFont+GAP_X) +GAP_X;
rect.bottom = m_dyFont + GAP_Y + rect.top;
//TODO: International support (CDateCtrl)

VERIFY(m_staticDayOfWeek.Create(" S   M   T   W   T   F   S",
                         WS_CHILD | WS_VISIBLE |
                         SS_SIMPLE ,
                         rect,
                         this,
                         IDC_DDDAYOFWEEK));
m_staticDayOfWeek.SetFont(GetFont());
  //Set accelerator table
const int TABLE_ENTRIES = 2;	//number of structures in the array
ACCEL AccelTable[TABLE_ENTRIES]; //Array with accelerator data
AccelTable[0].fVirt = FVIRTKEY;
AccelTable[0].key   = VK_ESCAPE;
AccelTable[0].cmd   = IDCANCEL;
AccelTable[1].fVirt = FVIRTKEY;
AccelTable[1].key   = VK_RETURN;
AccelTable[1].cmd   = IDOK;
if (!m_hAccel)
  {
  m_hAccel = CreateAcceleratorTable(AccelTable,TABLE_ENTRIES);
  SetFocus(); //Claim the input focus.
  }
return TRUE;
}

//::GetModify()----------------------------------------------------------------
/*Returns TRUE if the edit-control content have been modified, otherwise returns
  FALSE if it have remained unchanged.

  Example:
      void MyFunc (CDateCtrl* pEditDlg)
        {
        if (pEditDlg->GetModify())
          {
          CFrameWnd* pFrameWnd = STATIC_DOWNCAST(CFrameWnd, AfxGetMainWnd());
          ASSERT_VALID(pFrameWnd);
          CDocument* pDoc = pFrameWnd->GetActiveFrame()->GetActiveDocument();
            //The document has been modified and changes should be saved (Save As
            //dialog appears on exit)
          if(pDoc != NULL)
            pDoc->SetModifiedFlag();
          }
        }
 */
BOOL CDateCtrl::GetModify() const
{
return m_bHasBeenModified;
}

//::DoDataExchange()-----------------------------------------------------------
/*Called by the framework to exchange and validate dialog data.

  Note: Validation failure creates CUserException and debug message:
        First-chance exception in Premium.exe (MFC40D.DLL): 0xAddr:
        Microsoft C++ Exception.
        Don't catch CUserException because UpdateData handles it and
        returns FALSE.
 */
void CDateCtrl::DoDataExchange(CDataExchange* pDX)
{

	//{{AFX_DATA_MAP(CDateCtrl)
	DDX_Control(pDX, IDC_DDSPINMONTH, m_spinMonth);
	DDX_Control(pDX, IDC_DDSPINYEAR,  m_spinYear);
	DDX_Text(pDX, IDC_DDEDITMONTH, m_iMonth);
  DDV_MinMaxInt(pDX, m_iMonth,1,12);
	DDX_Text(pDX, IDC_DDEDITYEAR , m_iYear);
	//}}AFX_DATA_MAP
  DDV_MinMaxInt(pDX, m_iYear,CST_YEARSTART,CST_YEAREND+1);

}

//::PreCreateWindow()----------------------------------------------------------
/*Called by the framework before the creation of the Windows window attached to
  this CWnd object.
*/
BOOL CDateCtrl::PreCreateWindow(CREATESTRUCT& cs)
{
TRACE0("CDateCtrl::PreCreateWindow()\n");
VERIFY(RegisterClass());  //Registering window class

return CWnd::PreCreateWindow(cs);
}

//::PreTranslateMessage()------------------------------------------------------
/*Used by class CWinApp to translate window messages before they are dispatched
  to the TranslateMessage and DispatchMessage Windows functions.
  The TranslateAccelerator function processes accelerator keys.
 */
BOOL CDateCtrl::PreTranslateMessage(MSG* pMsg)
{
if(!(m_hAccel && (::TranslateAccelerator(m_hWnd, m_hAccel, pMsg)  )))
  {
  return CWnd::PreTranslateMessage(pMsg);
  }
else
  return TRUE;
}

//::OnNcCreate()---------------------------------------------------------------
/*This member function is called by the framework after Create() and
 PreCreateWindow() to allow your application to handle a Windows message.
 */
BOOL CDateCtrl::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
lpCreateStruct->lpCreateParams = this; //Pass this object to WM_NCCREATE handler

return (CWnd::OnNcCreate(lpCreateStruct));
}

//::OnNcDestroy()--------------------------------------------------------------
/*Called by the framework when the nonclient area is being destroyed, and is
  the last member function called when the Windows window is destroyed.
*/
void CDateCtrl::OnNcDestroy()
{
try
  {
  TRACE0("CDateCtrl::OnNcDestroy()\n");
  if (m_hAccel != NULL) //Destroy the accelerator table.
    {
    VERIFY(DestroyAcceleratorTable(m_hAccel));
    m_hAccel = NULL;
    }

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

//::OnPaint()------------------------------------------------------------------
/*The framework calls this member function when Windows or an application makes
  a request to repaint a portion of an application’s window.
*/
void CDateCtrl::OnPaint()
{
try
  {
  CPaintDC DC(this); //Device context for painting
  CFont* pOldFont = DC.SelectObject(GetFont());
  DC.SetTextAlign(TA_RIGHT);
  DC.SetBkMode(TRANSPARENT);
  DC.DrawEdge(CRect(m_posDay.x,m_posDay.y,
                    7 *(2*m_dxFont+GAP_X)+m_posDay.x+GAP_X,
                    8 *(m_dyFont+GAP_Y) + GAP_Y),
              EDGE_SUNKEN,BF_RECT | BF_ADJUST);
    //Print Day Table
  UINT nDay = 0;      //Day of the month [0,30]

  TCHAR strDay[3];
  while (nDay < m_nLastDay)
    {
    _itoa(nDay+1,strDay,10);
    DC.TextOut( m_posDay.x + ((((nDay+m_nFirstDay)%7)+1) * (2*m_dxFont+GAP_X)),
                m_posDay.y + (  (nDay+m_nFirstDay)/7) *      (m_dyFont+GAP_Y) + 1,
                strDay,strlen(strDay));
    nDay ++;
    }

  SelectDay(&DC,m_iDay); //Current day

  DC.SelectObject(pOldFont);
  }

catch(CResourceException* r)
  {
  TRACE0("CDateCtrl::OnPaint() Error!\n");
  r->Delete();
  ASSERT(FALSE);
  }
}

///////////////////////////////////////////////////////////////////////////////
//Mouse input handlers

//::OnLButtonUp()--------------------------------------------------------------
#pragma warning( disable : 4100 ) //Warning :unreferenced formal parameter
/*Release the mouse button and highlight selected day
 */
void CDateCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
CRect rectDayBox(m_posDay.x,m_posDay.y,
                    7 *(2*m_dxFont+GAP_X)+m_posDay.x+GAP_X,
                    8 *(m_dyFont+GAP_Y) + GAP_Y);
if (rectDayBox.PtInRect(point)) //If mouse points to the Day Box
  {                             //get selected day
    //Get day of the week
  point.x -= m_posDay.x;
  point.x /= rectDayBox.Width()/7;
  if ((point.x < 0) || (point.x > 6))
    return;
  point.y -= m_posDay.y;
  point.y /= rectDayBox.Height()/6;
  if ((point.y < 0) || (point.y > 5))
    return;
  int iDay = (point.y)*7+ point.x - m_nFirstDay + 1;
  if ((iDay < 1) || (iDay > (int)m_nLastDay))
    return;  //Not valid selection

    //Check if different day has been selected  Mar. 2k D.K.
  if (m_iDay != iDay)
    {
    m_iDay = iDay;
    m_bHasBeenModified = TRUE;
    RedrawWindow();
    }
  }
}
#pragma warning( default : 4100 )//Warning :unreferenced formal parameter

//::OnRButtonUp()--------------------------------------------------------------
#pragma warning( disable : 4100 ) //Warning :unreferenced formal parameter

/*Release the mouse button, notify current date to the owner
 and destroy the window;
 */
void CDateCtrl::OnRButtonUp(UINT nFlags, CPoint point)
{
OnOK();
}
#pragma warning( default : 4100 )//Warning :unreferenced formal parameter

//::OnNotify()-----------------------------------------------------------------
/*The WM_NOTIFY message informs the parent window of a control that an event
  has occurred in the control or that the control requires some kind of
  information. Override this function if you need different behavior.
 */
BOOL CDateCtrl::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
WORD wCtrlID  = LOWORD(wParam);
//WORD wCtrlMsg	= HIWORD(wParam); Not used 6.1.00 D.K.
//HWND hCtrl    = (HWND)lParam;   Not used 6.1.00 D.K.
if (wCtrlID == IDC_DDSPINMONTH)
  {
  TRACE0("CDateCtrl::OnNotify(IDC_DDSPINMONTH,0)\n");
  m_editMonth.SetModify(TRUE); //Indicate that the text has been modified
  //TODO: Notify the parent month have changed
  }
if (wCtrlID == IDC_DDSPINYEAR)
  {
  TRACE0("CDateCtrl::OnNotify(IDC_DDSPINYEAR,0)\n");
  m_editYear.SetModify(TRUE); //Indicate that the text has been modified
  //TODO:  Notify the parent year have changed
  }

return CWnd::OnNotify(wParam, lParam, pResult);
}

//::OnCommand()----------------------------------------------------------------
/*The framework calls this member function when the user selects an item from
  a menu, when a child control - in this case month or year edit control -
  sends a notification message
 */
BOOL CDateCtrl::OnCommand(WPARAM wParam, LPARAM lParam)
{
 //Check a notification message
WORD wCtrlID  = LOWORD(wParam);
WORD wCtrlMsg	= HIWORD(wParam);
//HWND hCtrl    = (HWND)lParam; Not used 6.1.00 D.K.
if (wCtrlMsg == EN_UPDATE)
  {
  if (wCtrlID == IDC_DDEDITMONTH)
    {
    TRACE0("CDateCtrl::OnCommand(IDC_DDEDITMONTH,EN_UPDATE)\n");
      //Validate edit entry
    m_iMonth = LOWORD(m_spinMonth.GetPos());
    m_spinMonth.SetPos(m_iMonth);
    SetFirstAndLastDay();
    RedrawWindow();
    }
  if (wCtrlID == IDC_DDEDITYEAR)
    {
    TRACE0("CDateCtrl::OnCommand(IDC_DDEDITYEAR,EN_UPDATE)\n");
      //Validate edit entry
    m_iYear = LOWORD(m_spinYear.GetPos());
    m_spinYear.SetPos(m_iYear);
    SetFirstAndLastDay();
    RedrawWindow();
    }
  }


return CWnd::OnCommand(wParam, lParam);
}

//::OnOK()---------------------------------------------------------------------
/*Notify current date to the owner and destroy the window;

  Example:
    #include "KDateCrl.h" //CDateCtrl class
    class CParentView : public CView
      {
      ...
      CDateCtrl m_Date;
      virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
      ...
      };
    BOOL CParentView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
      {
      WORD wCtrlID  = LOWORD(wParam);
      WORD wCtrlMsg	= HIWORD(wParam);
      if (wCtrlID == m_Date.GetDlgCtrlID())
        {
        DDATE_RETURN* pNotification = (DDATE_RETURN*)lParam;
        TRACE3("%d.%d.%d\n",pNotification->iDay,
                            pNotification->iMonth,
                            pNotification->iYear);
        *pResult = 1;
        return TRUE;
        }

      return CView::OnNotify(wParam, lParam, pResult);
      }
 */
void CDateCtrl::OnOK()
{
TRACE0("CDateCtrl::OnOK()\n");

CWnd* pOwner = GetOwner();
if (pOwner != NULL)
  {
  ASSERT_VALID(pOwner);
  DDATE_RETURN Notification;
  Notification.hdr.hwndFrom = m_hWnd;//Handle to control sending message
  Notification.hdr.idFrom =          //Identifier of control sending message
       GetDlgCtrlID();
  Notification.hdr.code = NM_RETURN; //Notification code
  Notification.iDay   = m_iDay;
  Notification.iMonth = m_iMonth;
  Notification.iYear  = m_iYear;

#ifdef _DEBUG_MSGRES
  LRESULT pResult =
#endif
  pOwner->SendMessage(WM_NOTIFY,
                           (WPARAM)GetDlgCtrlID(),
                           (LPARAM)&Notification);
  pOwner->SendMessage(WM_COMMAND,MAKEWPARAM(IDOK,0),(LPARAM)GetSafeHwnd());

  }

  //Data have been modified
if (m_editMonth.GetModify() || m_editYear.GetModify())
  m_bHasBeenModified = TRUE;

DestroyWindow();
}

//::OnCancel()-----------------------------------------------------------------
/*Override this member function to perform Cancel action. The default simply
  terminates a control by calling DestroyWindow(). The framework calls this
  member function when the user presses the ESC key.
 */
void CDateCtrl::OnCancel()
{
TRACE0("CDateCtrl::OnCancel()\n");
CWnd* pOwner = GetOwner();
if (pOwner != NULL)
  pOwner->SendMessage(WM_COMMAND,MAKEWPARAM(IDCANCEL,0),(LPARAM)GetSafeHwnd());
	// TODO: Add extra cleanup here when the user presses the ESC key (CDateCtrl)

  //Signal that modification has been canceled
m_bHasBeenModified = FALSE;

DestroyWindow();
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  4    Biblioteka1.3         8/16/01 11:37:22 PM  Darko           Update
 *  3    Biblioteka1.2         7/7/01 11:10:15 PM   Darko           $Revision: 1.1 $
 *       inserted
 *  2    Biblioteka1.1         6/8/01 10:49:22 PM   Darko           VSS
 *  1    Biblioteka1.0         8/13/00 2:55:44 PM   Darko           
 * $
 *****************************************************************************/
