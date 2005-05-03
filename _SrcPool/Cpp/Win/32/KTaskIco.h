/*$Workfile: S:\_SrcPool\Cpp\Win\32\KTaskIco.h$: header file
  $Revision: 5$ $Date: 2005-04-26 11:35:38$
  $Author: Darko Kolakovic$

  Adds icons to the Windows system taskbar
  Copyright: CommonSoft Inc.
  Sep. 97 Darko Kolakovic
 */
// Group=Windows

#ifndef _KTASKICO_H_
  //$Workfile: S:\_SrcPool\Cpp\Win\32\KTaskIco.h$ sentry
  #define _KTASKICO_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
//CTaskBarIcon class encapsulates NOTIFYICONDATA structure used to add icons to
//the system taskbar notification area.
//
//Note: uses Microsoft Foundation Library (MFC); 
//      Microsoft Windows specific (Win9x, WinNT).
class CTaskBarIcon : public CCmdTarget
{
// Construction
public:
  CTaskBarIcon(UINT nID = 0);
  ~CTaskBarIcon();

  DECLARE_DYNAMIC(CTaskBarIcon)

// Attributes
protected:
  NOTIFYICONDATA m_ShellNotify; //taskbar notification structure

// Operations
public:
  void SetNotificationMsg(CWnd* pNotifyWnd,const  UINT nNotifyMsg);
  void SetNotificationMsg(HWND  hNotifyWnd,const UINT nNotifyMsg);
  UINT SetID(const UINT nID);
  BOOL SetIcon(UINT uID = 0);
  BOOL SetIcon(HICON hicon, LPCTSTR szTooltip = NULL);
  BOOL SetIcon(LPCTSTR lpszIconName, LPCTSTR szTooltip = NULL);
  BOOL SetIcon(const UINT nStandardIcoId, LPCTSTR szTooltip);
  BOOL SetTooltip(LPCTSTR szTooltip = NULL);
  //{{AFX_MSG(CTaskBarIcon)
  virtual LRESULT OnNotify(WPARAM uID, LPARAM lEvent);
  //}}AFX_MSG
};


///////////////////////////////////////////////////////////////////////////////
#endif  //_KTASKICO_H_
/******************************************************************************
 *$Log: 
 * 5    Biblioteka1.4         2005-04-26 11:35:38  Darko Kolakovic Document groups
 *      and typo fixes
 * 4    Biblioteka1.3         2003-08-13 17:40:08  Darko           comment
 * 3    Biblioteka1.2         2003-08-13 14:38:26  Darko           Unicode
 * 2    Biblioteka1.1         2002-07-16 01:41:34  Darko           Fixed VSS Log 
 *      tag
 * 1    Biblioteka1.0         2002-04-05 00:50:16  Darko           
 *$
 *****************************************************************************/
  //This makes the ClassWizard very happy
  //{{AFX_VIRTUAL(CTaskBarIcon)
  //}}AFX_VIRTUAL
  //{{AFX_MSG_MAP(CTaskBarIcon)
  //}}AFX_MSG_MAP
