/*$Workfile: KTaskIco.cpp$: implementation file
  $Revision: 4$ $Date: 2004-10-01 22:35:34$
  $Author: Darko$

  Adds icons to the Windows system taskbar
  Sep. 97 Darko Kolakovic
  1996 Paul DiLascia MSJ
*/

#include "stdafx.h"
#include "KTaskIco.h" //CTaskBarIcon class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// CTaskBarIcon
IMPLEMENT_DYNAMIC(CTaskBarIcon, CCmdTarget)

//::CTaskBarIcon()-------------------------------------------------------------
/*Constructs and initializes CTaskBarIcon class

  Example:
    #define WM_NOTIFY_TASKBAR  WM_USER //Message ID used for tray notifications
    class CMyWnd: public CWnd
      {
      ...
      CTaskBarIcon  m_ticoIcon; //Task bar icon

      //{{AFX_MSG(CMyWnd)
      afx_msg LRESULT OnTaskbarNotification(WPARAM wID, LPARAM lEvent);
      //}}AFX_MSG
      };
    ...
    BEGIN_MESSAGE_MAP(CMyWnd, CWnd)
      //{{AFX_MSG_MAP(CMyWnd)
      ...
      ON_MESSAGE(WM_NOTIFY_TASKBAR, OnTaskbarNotification)
      //}}AFX_MSG_MAP
    END_MESSAGE_MAP()
    ...
    int CMyWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
    {
      //Initialize tray icon
    m_ticoIcon.SetNotificationWnd(this, WM_NOTIFY_TRAY);
    m_ticoIcon.SetIcon(IDI_ICON);
    }
      //Handle notification from task bar icon
    LRESULT CMyWnd::OnTaskbarNotification(WPARAM wID, LPARAM lEvent)
    {
    TRACE0("OnTrayNotification()\n");
    //TO DO: Insert your code
      //Default message handling
    return m_ticoIcon.OnNotify(wID, lEvent);
    }
 */
CTaskBarIcon::CTaskBarIcon(UINT nID //[in] taskbar icon ID
                           )
{
ZeroMemory(&m_ShellNotify, sizeof(m_ShellNotify));
m_ShellNotify.cbSize = sizeof(m_ShellNotify);
m_ShellNotify.uID = nID;  //Application-defined identifier of the taskbar icon

if(nID != 0)//Set tip string
  {
  CString strTip;
  strTip.LoadString(nID);
  //Note: NOTIFYICONDATA is not UNICODE ready structure D.K.
  if(!strTip.IsEmpty())
    _tcsnccpy(m_ShellNotify.szTip,(LPCTSTR)strTip,sizeof(m_ShellNotify.szTip)-1);
  }
}

CTaskBarIcon::~CTaskBarIcon()
{
SetIcon(); //Remove icon from taskbar
}

//:SetID()---------------------------------------------------------------------
/*Sets a new identification number for the taskbar icon only if it is not
  previously set.
  Returns the new taskbar ID.
 */
UINT CTaskBarIcon::SetID(const UINT nID //[in] new taskbar icon ID
                         )
{
if (m_ShellNotify.uID == 0)
  m_ShellNotify.uID = nID;
return m_ShellNotify.uID;
}

//::SetNotificationMsg()-------------------------------------------------------
/*Set the window that receives notification messages associated with an icon in
  the taskbar notification area.
  The system uses the specified  notification messages that it sends to the
  window identified by hWnd whenever a mouse event occurs in the bounding
  rectangle of the icon.
*/
void CTaskBarIcon::SetNotificationMsg(
                HWND  hNotifyWnd,     //[in] receiving window
                const UINT nNotifyMsg //[in] application-defined message identifier
                                      )
{
ASSERT(nNotifyMsg == 0 || nNotifyMsg >= WM_USER);
ASSERT(::IsWindow(hNotifyWnd));

m_ShellNotify.hWnd = hNotifyWnd;
m_ShellNotify.uCallbackMessage = nNotifyMsg;
}

void CTaskBarIcon::SetNotificationMsg(
                  CWnd* pNotifyWnd,
                  const  UINT nNotifyMsg //application-defined message identifier
                                 )
{
ASSERT(pNotifyWnd != NULL);
SetNotificationMsg(pNotifyWnd->GetSafeHwnd(),nNotifyMsg);
}


//::SetIcon()------------------------------------------------------------------
/*Loads task bar icon and tip string from the resource, or if icon ID is 0,
  deletes the icon from the taskbar.
*/
BOOL CTaskBarIcon::SetIcon(UINT nID //[in]= 0 ID of the taskbar icon to display or
                                    //remove (default)
                          )
{
if (nID != 0)
  {
  CString strTip;
  strTip.LoadString(nID);
  _tcsnccpy(m_ShellNotify.szTip,(LPCTSTR)strTip,sizeof(m_ShellNotify.szTip)-1);
  }
return SetIcon((nID == 0)? NULL:AfxGetApp()->LoadIcon(nID), NULL);
}

BOOL CTaskBarIcon::SetIcon(LPCTSTR lpszIconName,  //[in]icon resource name
                           LPCTSTR szTooltip       //[in]= NULL tooltip string
                           )
{
return SetIcon((lpszIconName == NULL) ?
               AfxGetApp()->LoadIcon(lpszIconName) : NULL, szTooltip);
}

BOOL CTaskBarIcon::SetIcon(HICON hicon, //[in]handle of the taskbar icon to display
                                        //if NULL, icon will be deleted from task bar
                           LPCTSTR szTooltip //[in]= NULL tooltip string
                           )
{
DWORD dwMessage;
m_ShellNotify.uFlags = 0;

if (hicon) //Prepare to display the icon
  {
  // Add or replace icon in system tray
  dwMessage = m_ShellNotify.hIcon ? NIM_MODIFY : NIM_ADD;
  m_ShellNotify.hIcon = hicon;
  m_ShellNotify.uFlags |= NIF_ICON;
  }
else //Prepare to erase the taskbar icon
  {
  if (m_ShellNotify.hIcon==NULL)
    return TRUE;    // already deleted
  dwMessage = NIM_DELETE;
  }

if (szTooltip != NULL) //Set the tooltip
  _tcsnccpy(m_ShellNotify.szTip, szTooltip, sizeof(m_ShellNotify.szTip)-1);
if (m_ShellNotify.szTip[0])
  m_ShellNotify.uFlags |= NIF_TIP;

  //Enable notification message if set
if (m_ShellNotify.uCallbackMessage && m_ShellNotify.hWnd)
  m_ShellNotify.uFlags |= NIF_MESSAGE;

  //Display the icon
BOOL bRet = Shell_NotifyIcon(dwMessage, &m_ShellNotify);
if (dwMessage == NIM_DELETE || !bRet)
  {
  m_ShellNotify.hIcon = NULL;
  }
return bRet;
}

//::SetIcon()------------------------------------------------------------------
/*Loads a Windows predefined icon and displays it on the system's task bar.

  Parameters:
    nStandardIcoID  1   Default application icon. IDI_APPLICATION
                    2   Asterisk (used in informative messages). IDI_ASTERISK
                    3   Exclamation point (used in warning messages). IDI_EXCLAMATION
                    4   Hand-shaped icon (used in serious warning messages). IDI_HAND
                    5   Question mark (used in prompting messages). IDI_QUESTION
                    6   Windows 95 only: Windows logo. IDI_WINLOGO
                        any other value will delete the icon from the taskbar
 */
BOOL CTaskBarIcon::SetIcon(const UINT nStandardIcoId, //[in]
                           LPCTSTR szTooltip//[in] pointer to the tooltip string or NULL
                           )
{
LPCTSTR  lpIconName;
switch (nStandardIcoId)
  {
  case 1: lpIconName = IDI_APPLICATION; break;
  case 2: lpIconName = IDI_ASTERISK   ; break;
  case 3: lpIconName = IDI_EXCLAMATION; break;
  case 4: lpIconName = IDI_HAND       ; break;
  case 5: lpIconName = IDI_QUESTION   ; break;
  case 6: lpIconName = IDI_WINLOGO    ; break;
  default:
    return SetIcon((UINT)0);
  }
return SetIcon(::LoadIcon(NULL, lpIconName), szTooltip);
}

//::SetTooltip()---------------------------------------------------------------
/*Sets tooltip text to display for the taskbar icon, or if parameter is NULL
  erases current tooltip text.

  Note: Only first 63 characters will be displayed as tooltips.
        NOTIFYICONDATA is not UNICODE ready structure.
 */
BOOL CTaskBarIcon::SetTooltip(LPCTSTR szTooltip //=NULL tooltip string
                              )
{
if (szTooltip != NULL)
  {
  //Note: NOTIFYICONDATA is not UNICODE ready structure D.K.
  _tcsnccpy(m_ShellNotify.szTip, szTooltip, sizeof(m_ShellNotify.szTip)-1);
  }
else
  ZeroMemory(&m_ShellNotify.szTip,sizeof(m_ShellNotify.szTip));

m_ShellNotify.uFlags = NIF_TIP;

  //Changet the tooltip
return Shell_NotifyIcon(NIM_MODIFY, &m_ShellNotify);
}

//::OnNotify()-----------------------------------------------------------------
/* Default event handler handles WM_RBUTTONUP and WM_LBUTTONDBLCLK messages.
   Call this function from your own notification handler.

  Example:
      //Handle notification from task bar icon
    LRESULT CMyWnd::OnTaskbarNotification(WPARAM wID, LPARAM lEvent)
    {
    TRACE0("OnTrayNotification()\n");
    //TO DO: Insert your code
      //Default message handling
    return m_ticoIcon.OnNotify(wID, lEvent);
    }

  History:
    1996 Microsoft Systems Journal Paul DiLascia
*/
LRESULT CTaskBarIcon::OnNotify(WPARAM wID, LPARAM lEvent)
{
if ( (m_ShellNotify.uID == 0)   ||
     (wID != m_ShellNotify.uID) ||
     (lEvent!=WM_RBUTTONUP && lEvent!=WM_LBUTTONDBLCLK))
  return 0;

  //If there's a resource menu with the same ID as the icon, use it as
  //the right-button popup menu. CTaskBarIcon will interprets the first
  //item in the menu as the default command for WM_LBUTTONDBLCLK
CMenu menu;
if (!menu.LoadMenu(m_ShellNotify.uID))
  return 0;
CMenu* pSubMenu = menu.GetSubMenu(0);
if (!pSubMenu)
  return 0;

if (lEvent==WM_RBUTTONUP)
  {

    //Make first menu item the default (bold font)
  ::SetMenuDefaultItem(pSubMenu->m_hMenu, 0, TRUE);

    //Display the menu at the current mouse location. There's a "bug"
    //(Microsoft calls it a feature) in Windows 95 that requires calling
    //SetForegroundWindow. To find out more, search for Q135788 in MSDN.
  CPoint mouse;
  GetCursorPos(&mouse);
  ::SetForegroundWindow(m_ShellNotify.hWnd);
  ::TrackPopupMenu(pSubMenu->m_hMenu, 0, mouse.x, mouse.y, 0,
  m_ShellNotify.hWnd, NULL);
  }
else  // double click: execute first menu item
  ::SendMessage(m_ShellNotify.hWnd, WM_COMMAND, pSubMenu->GetMenuItemID(0), 0);

return 1; // handled
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: 
 * 4    Biblioteka1.3         2004-10-01 22:35:34  Darko           stdafx.h
 * 3    Biblioteka1.2         2003-08-13 14:38:23  Darko           Unicode
 * 2    Biblioteka1.1         2002-07-16 01:41:30  Darko           Fixed VSS Log 
 *      tag
 * 1    Biblioteka1.0         2002-04-05 00:50:13  Darko           
 *$
 * 1996 Microsoft Systems Journal Paul DiLascia
 *****************************************************************************/