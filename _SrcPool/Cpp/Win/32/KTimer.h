/*$Workfile: KTimer.h$: header file
  $Revision: 8$ $Date: 2007-03-06 18:03:18$
  $Author: Darko Kolakovic$

  Simple Timer with callback function for Windows applications
  Darko Kolakovic
  June 2k1 simplified version; CWnd moved
  May '98
*/
// Group=Windows

#ifndef _KTIMER_H_
  //$Workfile: KTimer.h$ sentry
  #define _KTIMER_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifndef _WINUSER_
   //Timer callback function is defined in <winuser.h>
  #define TIMERPROC TIMERPROC
#endif
#ifndef TIMERPROC
  /*Windows timer callback function that handles WM_TIMER messages.

    Parameters:
      hwnd [in] Handle to the window associated with the timer. 
      uMsg [in] Specifies the WM_TIMER message. 
      idEvent [in] Specifies the timer's identifier. 
      dwTime  [in] Specifies the number of milliseconds that have 
              elapsed since the system was started. This is the value returned 
              by the GetTickCount function. 
  */
  typedef void (CALLBACK* TIMERPROC)(HWND, UINT, UINT_PTR, DWORD);
  //Windows timer callback function defined 
  #define TIMERPROC TIMERPROC
#endif

/////////////////////////////////////////////////////////////////////////////
/*CTimer is a simple timer class that creates a Windows system timer.
  The timer is associated with the window with NULL handle.
 
  Timers are a limited global resource; therefore it is important that
  an application check the value returned by the Start() member function
  to verify that a timer is actually available.
  Because the accuracy of a timer depends on the system clock rate and how
  often the application retrieves messages from the message queue, the time-out
  value is only approximate.
  The WM_TIMER message is posted to the installing thread's message queue when
  a timer expires. The message is posted by the GetMessage or PeekMessage
  function. You can process the message by providing a WM_TIMER case in the
  window procedure. Otherwise, the default window procedure will call the
  associated TimerProc callback function specified in the call to the
  SetTimerProc() function used to install the timer.
  To send subsequent WM_TIMER message, system waits until previous message has
  not been processed by thread's message queue (in timer's owner message loop,
  or with associated callback function.
 
  Elapsed time since timer started is a 32-bit value and it will wrap around to
  zero if the system is run continuously for 49.7 days.
 
  Note: Microsoft Windows specific (Win).
 
  Example:
 
       #include "KTimer.h" //CTimer class
       extern "C"
       VOID CALLBACK MyTimerProc(HWND     hwnd,   //handle of window processing 
                                                  //timer messages
                                 UINT     uMsg,   //WM_TIMER message
                                 UINT_PTR idEvent,//timer identifier
                                 DWORD    dwTime  //current system time
                                 )
         {
         MessageBeep(MB_OK);
         }
 
       void CreateTimer()
         {
         const int TIME_OUT = 300;//time interval [ms]
         static CTimer ctTimer1;
         ctTimer1.SetTimerProc(MyTimerProc);
         ctTimer1.Start(TIME_OUT);
         ...
         static CTimer ctTimer2(MyTimerProc);
         ctTimer2.Start(4*TIME_OUT);
         ...
         if(ctTimer1.IsStarted())
           ctTimer1.Stop();
         }
*/
class CTimer
{
// Construction
public:
  CTimer(TIMERPROC pfCallbackTimer = NULL,
         UINT nTimePeriod = 0
        );

// Attributes
public:

protected:
  UINT      m_nTimerID; //timer identifier
  TIMERPROC m_lpfnTimer;//timer callback function
  DWORD     m_dwStart;  //time elapsed between system start and timer start [ms]

// Operations
public:
  void SetTimerProc(TIMERPROC pfCallbackTimer);

// Implementation
public:
  virtual ~CTimer();
  #ifdef _DEBUG
    virtual void Dump() const;
  static VOID CALLBACK DbgTimerProc(HWND hWnd,UINT uMsg,
                                    UINT_PTR nTimerID,DWORD dwTime);
  #endif
  BOOL IsStarted() const;
  UINT GetID() const;

// Overrides
public:
  virtual BOOL Start(UINT nTimePeriod);
  virtual BOOL Stop();
  virtual DWORD GetElapsedTime(DWORD dwSystemElapsedTime) const;
};

/////////////////////////////////////////////////////////////////////////////
// Inlines

//::IsStarted()----------------------------------------------------------------
/*Check if timer is running.
  Returns TRUE if timer is activated.
 */
inline BOOL CTimer::IsStarted() const
{
return (m_nTimerID > 0);
}

//::SetTimerProc()----------------------------------------------------------------
/*Set timer's callback function.
 */
inline void CTimer::SetTimerProc(TIMERPROC pfCallbackTimer //pointer to timer
                                                           //callback function
                                )
{
ASSERT (pfCallbackTimer != NULL);
m_lpfnTimer = pfCallbackTimer;
}

//::GetID()--------------------------------------------------------------------
/*Returns timer identification number. If timer has not been created, ID is zero.
 */
inline UINT CTimer::GetID() const
{
return m_nTimerID;
}

/////////////////////////////////////////////////////////////////////////////
#endif  //_KTIMER_H_

//This makes class Wizard happy
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CTimer)
  //}}AFX_VIRTUAL
  //{{AFX_MSG(CTimer)
  //}}AFX_MSG
  //{{AFX_MSG_MAP(CTimer)
  //}}AFX_MSG_MAP

/*****************************************************************************
 * $Log:
 *  6    Biblioteka1.5         2005-04-26 11:35:40  Darko Kolakovic Document groups
 *       and typo fixes
 *  5    Biblioteka1.4         2003-09-22 22:27:11  Darko           formatting
 *  4    Biblioteka1.3         2002-01-24 19:19:45  Darko           Updated
 *       comments
 *  3    Biblioteka1.2         2001-08-17 00:38:18  Darko           Update
 *  2    Biblioteka1.1         2001-06-25 23:44:04  Darko           Simpilfied
 *       version
 *  1    Biblioteka1.0         2001-06-09 00:01:48  Darko
 * $
 *****************************************************************************/
