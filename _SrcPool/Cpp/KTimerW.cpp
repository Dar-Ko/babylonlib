/*$Workfile: KTimerW.cpp$: implementation file
  $Revision: 1.3 $ $Date: 2003/01/28 05:39:16 $
  $Author: ddarko $

  Copyright: CommonSoft Inc.
  Darko Kolakovic
  Jun 2k1 divided in 2 classes
  May 98 first release
 */ 
#include "KTimerW.h" //CTimerW class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

/////////////////////////////////////////////////////////////////////////////
// CTimerW

/*Deafult constructor. Starts the timer if nTimeOut is bigger than zero.
  If and owner handle hwndOwner is NULL no window is associated with the timer
  and WM_TIMER message will bes posted to the installing thread's message queue 
  when a timer expires. If callback function is not specified, you can process 
  the message by providing a WM_TIMER case in the main window procedure or in 
  CWinApp::PreTranslateMessage.
 */
CTimerW::CTimerW(UINT nTimeOut, //the time-out value [ms]
                 UINT nTimerID, // = ID_TIMER a nonzero timer identifier
                 TIMERPROC pfCallbackTimer, //callback function that processes 
                          //the WM_TIMER messages. If this parameter is NULL,
                          //the WM_TIMER messages are placed in the application’s
                          //message queue and handled by the CWnd object.
                 HWND hwndOwner //owner of windows message loop processing the 
                                //WM_TIMER messages
                 ) :
  CTimer(pfCallbackTimer,0),
  m_hOwner(hwndOwner)
  //m_pwndOwner(NULL) move out D.K.
{
TRACE0("CTimerW::CTimerW()\n");

  //If the HWND is NULL, this parameter is ignored.
#ifdef _DEBUG
  if (m_hOwner != NULL)
    ASSERT(nTimerID != 0); 
#endif

if (nTimeOut > 0)
  VERIFY(Start(nTimeOut,m_hOwner,nTimerID));
}

//::~CTimerW()------------------------------------------------------------------
/*Stops the timer and destroys associated window object of m_bAutoDestroy flag
  has been set to TRUE. A Window object is created if callback member function
  m_lpfnTimer is NULL.
 */
CTimerW::~CTimerW()
{
TRACE0("CTimerW::~CTimerW()\n");
Stop();
/*
if (m_hWnd !=NULL)
  {
  if (m_bAutoDestroy)
    DestroyWindow();
  }*/
}

/* We are not creating Cwnd here D.K. m_bAutoDestroy etc. should be moved to sperate class/module
IMPLEMENT_DYNCREATE(CTimerW, CWnd)

BEGIN_MESSAGE_MAP(CTimerW, CWnd)
	//{{AFX_MSG_MAP(CTimerW)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//::CreateOwner()--------------------------------------------------------------
/ *Creates an invisible window that will process WM_TIMER messages posted by this
  timer.
  Returns TRUE if successful; otherwise returns FALSE.
 * /
BOOL CTimerW::CreateOwner()
{
if(m_pwndOwner == NULL)
  {
  m_pwndOwner = new CWnd;
  ASSERT(m_pwndOwner != NULL);
  if(!CreateEx(WS_EX_TOOLWINDOW,
                AfxRegisterWndClass(CS_PARENTDC	),_T("KTimerW"),WS_MINIMIZE|WS_POPUP,0,0,0,0,
      NULL,(HMENU)0 ))
    return FALSE;
  else
//    m_bAutoDestroy = TRUE; //Destroy selfcreated window
    m_hOwner = m_pwndOwner->GetSafeHwnd();

  }
}

/////////////////////////////////////////////////////////////////////////////
// CTimerW message handlers

//::OnTimer()------------------------------------------------------------------
/ *Override it to make your own handling of the WM_TIMER message.
 * /
void CTimerW::OnTimer(UINT nIDEvent)
{
TRACE1("CTimerW::OnTimer(m_hWnd = %X)\n",m_hWnd);
if (nIDEvent == m_nTimerID)
  {
  MessageBeep(MB_OK);
  }
}

*/

//::Start()--------------------------------------------------------------------
/*Starts timer and no window is associated with the timer. The WM_TIMER message
  is posted to the installing thread's message queue when a timer expires. If 
  callback function is not specified, you can process the message by providing 
  a WM_TIMER case in the main window procedure or in CWinApp::PreTranslateMessage. 
  Repeated calls will reset time-out delay.
  Returns TRUE if a timer is created. In case of a failure result is FALSE. To 
  get extended error information, call GetLastError().
 */
BOOL CTimerW::Start(UINT nTimePeriod)
{
return Start(nTimePeriod,NULL,0);
}

/*Starts timer. Repeated calls will reset time-out delay.
  If hOwner is NULL, no window is associated with the timer and the nTimerID 
  parameter is ignored. 
  Returns TRUE if a timer is created. In case of a failure result is FALSE. To 
  get extended error information, call GetLastError().
 */
BOOL CTimerW::Start(UINT nTimePeriod,//the time-out value [ms] 
                    HWND hOwner,     //window that will process WM_TIMER messages
                    UINT nTimerID    //a nonzero timer identifier
                   ) 
{
TRACE2("CTimerW::Start(Timeout %d[ms], ID = %u)\n",nTimePeriod, nTimerID);
if(!((hOwner == NULL) || ::IsWindow(hOwner)))
  {
  TRACE0("\thOwner is not a window or NULL!\n");
  return FALSE;
  }

if (IsStarted()) //Stop previous timer
  {
  if(!Stop())
    {
    TRACE0("\tCTimerW couldn't be stopped!\n");
    return FALSE;
    }
  }

m_hOwner = hOwner; //Store new owner window handle

//Note: if hOwner is NULL, no window is associated with the timer and 
//      the nTimerID parameter is ignored. 
m_nTimerID = ::SetTimer(m_hOwner,nTimerID,nTimePeriod,m_lpfnTimer);

#if _DEBUG
  if (IsStarted())
    TRACE1("  timer ID = %u\n",m_nTimerID);
  else
	TRACE0("  failed to start a timer\n");
#endif
if (IsStarted())
  {
    //Get number of [ms] since the system was started
  m_dwStart = GetTickCount();
  return TRUE;
  }
return FALSE;
}

//::Stop()--------------------------------------------------------------------
/*Stops the timer.
  Return Value
    If the function succeeds, the return value is TRUE.
    If the function fails, the return value is FALSE. To get extended error 
    information, call GetLastError.
 */
BOOL CTimerW::Stop()
{
if(m_nTimerID > 0) 
  {
  TRACE1("CTimerW::Stop(ID=%d)\n",m_nTimerID);
  ASSERT((m_hOwner == NULL) || ::IsWindow(m_hOwner));
  if (! ::KillTimer(m_hOwner,m_nTimerID))
    {
    TRACE0("\tFailed!\n");
    return FALSE;
    }
  m_nTimerID = 0;
  m_dwStart  = 0;
  }

return TRUE;
}

//::Dump()---------------------------------------------------------------------
#ifdef _DEBUG 
/*CTimerW diagnostics
 */
void CTimerW::Dump() const
{
TRACE0("CTimerW::Dump()\n");
CTimer::Dump();
TRACE1("\towner handle = %Xh\n",m_hOwner);
}
#endif // _DEBUG

