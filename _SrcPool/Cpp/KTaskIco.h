/*$Workfile: KTaskIco.h$: header file
  $Revision: 1.2 $ $Date: 2002/09/10 15:22:21 $
  $Author: ddarko $

  Adds icons to the Windows system taskbar
  Copyright: CommonSoft Inc.
  Sep. 97 Darko Kolakovic
 */

#ifndef _KTASKICO_H_
  //KTaskIco.h sentry
  #define _KTASKICO_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
//CTaskBarIcon class encapsulates NOTIFYICONDATA structure used to add icons to
//the system taskbar notification area.
//
//Note: Microsoft Windows specific (Win9x, WinNT).
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
	BOOL SetIcon(HICON hicon, LPCSTR szTooltip = NULL);
	BOOL SetIcon(LPCTSTR lpszIconName, LPCSTR szTooltip = NULL);
	BOOL SetIcon(const UINT nStandardIcoID, LPCSTR szTooltip);
  BOOL SetTooltip(LPCTSTR szTooltip = NULL);
	//{{AFX_MSG(CTaskBarIcon)
	virtual LRESULT OnNotify(WPARAM uID, LPARAM lEvent);
	//}}AFX_MSG
};


///////////////////////////////////////////////////////////////////////////////
#endif  //_KTASKICO_H_
/******************************************************************************
 *$Log: 
 * 2    Biblioteka1.1         7/16/02 1:41:34 AM   Darko           Fixed VSS Log 
 *      tag
 * 1    Biblioteka1.0         4/5/02 12:50:16 AM   Darko           
 *$
 *****************************************************************************/
	//This makes the ClassWizard very happy
	//{{AFX_VIRTUAL(CTaskBarIcon)
	//}}AFX_VIRTUAL
	//{{AFX_MSG_MAP(CTaskBarIcon)
	//}}AFX_MSG_MAP
