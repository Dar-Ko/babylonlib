/*$Workfile: KIsTerm.cpp$: implementation file
  $Revision: 1.2 $ $Date: 2002/09/10 15:22:21 $
  $Author: ddarko $

  Checks if application is about to terminate.
  Copyright: CommonSoft Inc.
  Nov. 96 D. Kolakovic
 */ 

#ifndef __AFXWIN_H__
  #include <AfxWin.h> // MFC core and standard components
#endif

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//IsTerminating()--------------------------------------------------------------
/*Checks if application is about to terminate.
  The WM_QUIT message indicates a request to terminate an application.

  Returns: TRUE if application is about to terminate, otherwise returns FALSE.

  Note: uses Microsoft Fundation Library (MFC).
        Microsoft Windows specific (Win). 
*/
BOOL IsTerminating(CWinApp* pApp //[in] pointer to the Windows application object
                  )
{
MSG msg;
while (PeekMessage(&msg,0,0,0,PM_NOREMOVE))
  {
    //If message is available for caller's application, return TRUE
  if (msg.message == WM_QUIT)
    return TRUE; 
  //If message is available for the another application,yield control
  pApp->PumpMessage();
  }
return FALSE;
}
