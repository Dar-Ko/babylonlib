/*$Workfile: KTimer.h$: header file
  $Revision: 1.2 $ $Date: 2002/09/10 15:22:21 $
  $Author: ddarko $
  
  Simple Timer with callback function for Windows applications
  Darko Kolakovic
  June 2k1 simplified version; CWnd moved
  May '98
*/

#ifndef _KTIMER_H_
    //KTimer.h sentry
  #define _KTIMER_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif


#ifndef __AFXWIN_H__
	#include <AfxWin.h> //Windows definitions
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimer is a simple timer class that creates a Windows system timer.
// The timer is associated with the window with NULL handle.
//
// Timers are a limited global resource; therefore it is important that
// an application check the value returned by the Start() member function
// to verify that a timer is actually available.
// Because the accuracy of a timer depends on the system clock rate and how
// often the application retrieves messages from the message queue, the time-out
// value is only approximate.
// The WM_TIMER message is posted to the installing thread's message queue when
// a timer expires. The message is posted by the GetMessage or PeekMessage
// function. You can process the message by providing a WM_TIMER case in the
// window procedure. Otherwise, the default window procedure will call the
// associated TimerProc callback function specified in the call to the
// SetTimerProc() function used to install the timer.
// To send subsequent WM_TIMER message, system waits until prevoius message has
// not been processed by thread's message queue (in timer's owner message loop,
// or with associated callback function.
//
// Elapsed time since timer started is a 32-bit value and it will wrap around to
// zero if the system is run continuously for 49.7 days.
//
// Note: Microsoft Windows specific (Win).
//
// Example:
//
//      #include "KTimer.h" //CTimer class
//      extern "C"
//      VOID CALLBACK MyTimerProc(HWND  hwnd,   //handle of window processing timer messages
//                                UINT  uMsg,   //WM_TIMER message
//                                UINT  idEvent,//timer identifier
//                                DWORD  dwTime //current system time
//                                )
//        {
//        MessageBeep(MB_OK);
//        }
//
//      void CreateTimer()
//        {
//        const int TIME_OUT = 300;//time interval [ms]
//        static CTimer ctTimer1;
//        ctTimer1.SetTimerProc(MyTimerProc);
//        ctTimer1.Start(TIME_OUT);
//
//        static CTimer ctTimer2(MyTimerProc);
//        ctTimer2.Start(4*TIME_OUT);
//        ...
//        if(ctTimer1.IsStarted())
//          ctTimer1.Stop();
//        }
//
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
  UINT      m_nTimerID; //timer indentifier
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
		                              UINT nTimerID,DWORD dwTime);
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
/*Returns timer indtification number. If timer has not been created, ID is zero.
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
 *  4    Biblioteka1.3         1/24/02 7:19:45 PM   Darko           Updated
 *       comments
 *  3    Biblioteka1.2         8/17/01 12:38:18 AM  Darko           Update
 *  2    Biblioteka1.1         6/25/01 11:44:04 PM  Darko           Simpilfied
 *       version
 *  1    Biblioteka1.0         6/9/01 12:01:48 AM   Darko           
 * $
 *****************************************************************************/
