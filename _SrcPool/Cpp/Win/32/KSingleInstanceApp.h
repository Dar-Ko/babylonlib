/*$Workfile: S:\_SrcPool\Cpp\Win\32\KSingleInstanceApp.h$: header file
  $Revision: 6$ $Date: 2005-04-26 11:35:30$
  $Author: Darko Kolakovic$

  Single instance Windows application
  Copyright: BRadovic
  2k3-07-17 Blazimir Radovic
 */
// Group=Windows

//$Workfile: S:\_SrcPool\Cpp\Win\32\KSingleInstanceApp.h$ sentry
#pragma once
#ifndef __AFXWIN_H__
  #error include 'stdafx.h' before including this file for PCH
#endif
#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif
#include <afxmt.h> //CCriticalSection class

///////////////////////////////////////////////////////////////////////////////
// CSingleInstanceApp class is the base class from which you derive a 
// Windows application object. This application object provides member
// functions for initializing single instance of your application and for
// running the application.
//
// See also: KB109175 How to Limit an MFC Application to a Single Instance
//
// Note: uses Microsoft Foundation Library (MFC);
//       Microsoft Windows specific (Win).
class CSingleInstanceApp : public CWinApp
{
public:
  CSingleInstanceApp(LPCTSTR szGuid);
  virtual ~CSingleInstanceApp(void);

public:
  static UINT  m_nMsgId;
private:
  static TCHAR m_szMutex[MAX_PATH];
  static DWORD  m_dwPid;

protected:
  bool IsFirstInstance();
  void RegisterDde();
  static BOOL CALLBACK FindFirstInstance(HWND hWnd, LPARAM lParam);
  virtual BOOL InitInstance();
  //virtual BOOL PreTranslateMessage(MSG* pMsg);

  //{{AFX_MSG(CSingleInstanceApp)
   //afx_msg void /*LRESULT*/ OnFindFirstInstance(WPARAM wp, LPARAM lp);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  6    Biblioteka1.5         2005-04-26 11:35:30  Darko Kolakovic Document groups
 *       and typo fixes
 *  5    Biblioteka1.4         2004-10-01 22:35:25  Darko           stdafx.h
 *  4    Biblioteka1.3         2003-09-15 02:44:22  Darko           Uses PID as
 *       unique identifier
 *  3    Biblioteka1.2         2003-09-15 01:53:23  Darko           Displaying top
 *       window mived to FindFirstInstance()
 *  2    Biblioteka1.1         2003-09-12 16:12:04  Darko           comment
 *  1    Biblioteka1.0         2003-09-12 13:09:28  Blazimir Radovic 
 * $
 *  0    2k3-07-17 Blazimir Radovic
 *****************************************************************************/
