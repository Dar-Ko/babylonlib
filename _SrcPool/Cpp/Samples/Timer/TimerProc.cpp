// TimerProc.cpp : implementation file
//

#include "StdAfx.h"
#include "KTimer.h"    //CTimer class
#include "Resource.h" 
#include "TimerDlg.h" //CTimerDlg class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

/*Timer procedure used as an example for timer callaback function.
  The timer procedure is an application-defined callback function that processes 
  WM_TIMER messages.

  Note: The elapsed time is stored as a DWORD value. Therefore, the time will wrap 
        around to zero if the system is run continuously for 49.7 days. 

  See also: TIMERPROC
 */
VOID CALLBACK MyTimerProc(HWND hWnd, //handle of window processing timer messages
                           UINT uMsg,         //WM_TIMER message
                           UINT nTimerID,     //timer identifier
                           DWORD dwTime       //number of milliseconds that have 
						                      //elapsed since the system was started 
                          )
{
TRACE2("MyTimerProc(hWnd = %x, ID = %d, elapsed time = ",hWnd,nTimerID);
extern CTimer* g_pctTimer1;
extern CTimer* g_pctTimer2;
CTimerDlg* pMainWnd = (CTimerDlg*)AfxGetMainWnd();
ASSERT(pMainWnd != NULL);

DWORD dwElapsedTime; //elapsed time [ms]
CString strOutput;   //output text
CWnd* pWnd;          //output control
 
if (nTimerID == g_pctTimer1->GetID())
  {
  dwElapsedTime = g_pctTimer1->GetElapsedTime(dwTime);
  pWnd = pMainWnd->GetDlgItem(ID_TIMER1);
  TRACE1("%u [ms])\n",dwElapsedTime);
  }
else if (nTimerID == g_pctTimer2->GetID())
  {
  dwElapsedTime = g_pctTimer2->GetElapsedTime(dwTime);
  pWnd = pMainWnd->GetDlgItem(ID_TIMER2);
  TRACE1("%u [ms])\n",dwElapsedTime);
  MessageBeep(MB_OK);
  }

strOutput.Format(IDS_ELAPSEDTIME,(double)dwElapsedTime/1000.);
pWnd->SetWindowText((LPCTSTR)strOutput);

}

