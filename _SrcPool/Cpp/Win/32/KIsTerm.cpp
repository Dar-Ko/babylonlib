/*$Workfile: KIsTerm.cpp$: implementation file
  $Revision: 2$ $Date: 28/04/2005 8:46:46 PM$
  $Author: Darko$

  Checks if application is about to terminate.
  Copyright: CommonSoft Inc.
  Nov. 96 D. Kolakovic
 */

#ifndef __AFXWIN_H__
  #include <afxwin.h> // MFC core and standard components
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

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  2    Biblioteka1.1         28/04/2005 8:46:46 PMDarko           Comments
 *  1    Biblioteka1.0         08/03/2002 2:40:09 AMDarko Kolakovic 
 * $
 *****************************************************************************/
