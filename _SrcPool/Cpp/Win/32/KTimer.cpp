/*$Workfile: KTimer.cpp$: implementation file
  $Revision: 6$ $Date: 2004-10-01 22:35:37$
  $Author: Darko$

  Copyright: CommonSoft Inc.
  Darko Kolakovic May 98
 */
 
#include "KTimer.h" //CTimer class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

/////////////////////////////////////////////////////////////////////////////
// CTimer

//::CTimer()-------------------------------------------------------------------
/*Default constructor starts the timer if callback function and time period are
  non-zero.
 */
CTimer::CTimer(TIMERPROC pfCallbackTimer, //callback function that processes 
                          //the WM_TIMER messages. If this parameter is NULL,
                          //the WM_TIMER messages are placed in the application’s
                          //message queue and handled by the CWnd object.
               UINT nTimePeriod //the time-out value [ms]
               ) :
  m_lpfnTimer(pfCallbackTimer),
  m_nTimerID (0),
  m_dwStart  (0)
{
TRACE0("CTimer::CTimer()\n");
if ((nTimePeriod > 0) && (pfCallbackTimer != NULL))
  Start(nTimePeriod);
}


//::~CTimer()------------------------------------------------------------------
/*Stops the timer.
 */
CTimer::~CTimer()
{
TRACE0("CTimer::~CTimer()\n");
Stop();
}

//::Start()--------------------------------------------------------------------
/*Start timer. Repeated call will reset time-out period.
  Returns TRUE if a timer is created. In case of a failure result is FALSE. To 
  get extended error information, call GetLastError().
 */
BOOL CTimer::Start(UINT nTimePeriod//the time-out value [ms] 
                  ) 
{
#ifdef _DEBUG
  if (IsStarted())  
    TRACE2("CTimer::Start(Timeout %d[ms], ID=%d)\n",nTimePeriod,m_nTimerID);
  else
    TRACE1("CTimer::Start(Timeout %d[ms])\n",nTimePeriod);
#endif

if (IsStarted()) //Stop running timer
  {
  if(!Stop())
    {
    TRACE0("\tCTimer couldn't be stopped!\n");
    return FALSE;
    }
  }
  
ASSERT(m_lpfnTimer != NULL);
  //Create timer owned by desktop window
m_nTimerID = ::SetTimer(NULL, 0,nTimePeriod,m_lpfnTimer);

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
BOOL CTimer::Stop()
{
if(m_nTimerID > 0)
  {
  TRACE1("CTimer::Stop(ID=%d)\n",m_nTimerID);
  if (! ::KillTimer(NULL,m_nTimerID))
    {
    TRACE0("\tFailed!\n");
    return FALSE;
    }
  m_nTimerID = 0;
  m_dwStart  = 0;
  }

return TRUE;
}

//::GetElapsedTime()-----------------------------------------------------------
/*Returns time in milliseconds since the timer was started. The current time is
  given thoriugh dwSystemElapsedTime argument and represnets the number of 
  milliseconds that have elapsed since the system was started. That number could
  be obtained with call to GetTickCount() or as a parameter in associated callback
  function (see TIMERPROC).

  Note: The elapsed time is stored as a DWORD value. Therefore, the time will wrap 
        around to zero if the system is run continuously for 49.7 days. 
 */
DWORD CTimer::GetElapsedTime(DWORD dwSystemElapsedTime //time that have elapsed 
                              //since the system was started [ms] 
                   ) const
{
if(!IsStarted())
  return 0;
DWORD dwElapsedTime = dwSystemElapsedTime - m_dwStart;
  //Handle timer wrap around to zero
if (dwElapsedTime < 0)
  dwElapsedTime += 0xffffffff; //Maximum unsigned 32-bit value is 4294967295
return dwElapsedTime;
}

//::Dump()---------------------------------------------------------------------
#ifdef _DEBUG 
/*CTimer diagnostics
 */
void CTimer::Dump() const
{
TRACE0("CTimer::Dump()\n");
TRACE1("\tTimer ID     = %d\n",m_nTimerID);
TRACE1("\tTIMERPROC    = %ph\n",m_lpfnTimer);
TRACE1("\telapsed time = %u [ms]\n",IsStarted() ? 
                                    GetElapsedTime(GetTickCount()) : 0);
}
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTimer message handlers

//DbgTimerProc()------------------------------------------------------------------
#ifdef _DEBUG
/*Debugging timer procedure used as an example for timer callaback function.
  The timer procedure is an application-defined callback function that processes 
  WM_TIMER messages.

  Note: The elapsed time is stored as a DWORD value. Therefore, the time will wrap 
        around to zero if the system is run continuously for 49.7 days. 

  See also: TIMERPROC
 */
VOID CALLBACK CTimer::DbgTimerProc(HWND hWnd, //handle of window processing timer messages
                           UINT uMsg,         //WM_TIMER message
                           UINT nTimerID,     //timer identifier
                           DWORD dwTime       //number of milliseconds that have 
                                  //elapsed since the system was started 
                           )
{
TRACE3("DbgTimerProc(hWnd = %x, ID = %d, time = %u [ms])\n",hWnd,nTimerID,dwTime);
MessageBeep(MB_ICONEXCLAMATION);
}
#endif

/*****************************************************************************
 * $Log: 
 *  6    Biblioteka1.5         2004-10-01 22:35:37  Darko           stdafx.h
 *  5    Biblioteka1.4         2003-09-22 22:27:08  Darko           formatting
 *  4    Biblioteka1.3         2002-01-25 16:59:05  Darko           Updated
 *       comments
 *  3    Biblioteka1.2         2001-07-18 23:32:57  Darko           VSS tags
 *  2    Biblioteka1.1         2001-06-25 23:44:00  Darko           Simpilfied
 *       version
 *  1    Biblioteka1.0         2001-06-09 00:01:46  Darko           
 * $
 *****************************************************************************/
