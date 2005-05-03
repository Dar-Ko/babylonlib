/*$Workfile: KTimerW.h$: header file
  $Revision: 5$ $Date: 2005-04-26 11:35:43$
  $Author: Darko Kolakovic$

  Simple Timer for Windows applications with WM_TIMER message
  Copyright: CommonSoft Inc
  Darko Kolakovic  May '98
*/
// Group=Windows

#ifndef _KTIMERW_H_
  //$Workfile: KTimerW.h$ sentry
  #define _KTIMERW_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifndef __AFXWIN_H__
  #include <AfxWin.h>
#endif
#include "KTimer.h"  //CTimer class

/////////////////////////////////////////////////////////////////////////////
// CTimerW is a simple timer class that creates a Windows system timer.
// The WM_TIMER message is posted to the timer's owner message queue when 
// a timer expires. The message is posted by the GetMessage or PeekMessage 
// function. You can process the message by providing a WM_TIMER case in the 
// window procedure. Otherwise, the default window procedure will call the 
// associated TimerProc callback function specified in the call to the 
// SetTimerProc() function used to install the timer. 
// To send subsequent WM_TIMER message, system waits until prevoius message has 
// not been processed by thread's message queue (in timer's owner message loop, 
// or with associated callback function.
// The timer identifier by default is ID_TIMER = 14965.
// Timers are a limited global resource; therefore it is important that 
// an application check the value returned by the Start() member function 
// to verify that a timer is actually available.
// Because the accuracy of a timer depends on the system clock rate and how 
// often the application retrieves messages from the message queue, the time-out 
// value is only approximate.
// To send subsequent WM_TIMER message, system waits until prevoius message has 
// not been processed by thread's message queue (in timer's owner message loop, 
// or with associated callback function.
//
// Note: Microsoft Windows specific (Win).
class CTimerW : /*public CWnd,*/ public CTimer
{
//>> move to separate class D.K. Note: CWnd class have to be first in the inheritance row in order AFX_MSG_MAP 
//  created by classWizard work properly. 

// Construction
public:
  CTimerW(UINT nTimeOut = 0,
          UINT nTimerID = ID_TIMER,
          TIMERPROC pfCallbackTimer = NULL,
          HWND hwndOwner = NULL);
  //DECLARE_DYNCREATE(CTimerW)

// Attributes
public:
  enum 
    {
    ID_TIMER = 14965,   //default timer ID
    };

private:
//  CWnd* m_pwndOwner;  //self created owner window >> move to separate class D.K.
  HWND  m_hOwner;     //owner of the windows message loop

// Operations
public:

// Implementation
public:
  //virtual BOOL CreateOwner();  >> move to separate class D.K.

  virtual ~CTimerW();
  #ifdef _DEBUG 
    virtual void Dump() const;
  #endif

// Overrides
public:
  virtual BOOL Start(UINT nTimePeriod, HWND hwndOwner, UINT nTimerID);
  virtual BOOL Start(UINT nTimePeriod);
  virtual BOOL Stop();
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CTimerW)
  //}}AFX_VIRTUAL

  // Generated message map functions
public:
  //{{AFX_MSG(CTimerW)
//    virtual  afx_msg void OnTimer(UINT nIDEvent);>> move to separate class D.K.
  //}}AFX_MSG
//  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// Inlines

/////////////////////////////////////////////////////////////////////////////
#endif  //_KTIMERW_H_
/*****************************************************************************
 * $Log: 
 *  5    Biblioteka1.4         2005-04-26 11:35:43  Darko Kolakovic Document groups
 *       and typo fixes
 *  4    Biblioteka1.3         2003-09-22 22:27:15  Darko           formatting
 *  3    Biblioteka1.2         2002-01-24 19:19:49  Darko           Updated
 *       comments
 *  2    Biblioteka1.1         2001-07-18 23:33:00  Darko           VSS tags
 *  1    Biblioteka1.0         2001-06-25 23:44:58  Darko           
 * $
 *****************************************************************************/
