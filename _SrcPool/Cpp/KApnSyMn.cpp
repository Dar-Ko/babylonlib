/*$Workfile: KApnSyMn.cpp$: implementation file
  $Revision: 1.3 $ $Date: 2003/01/28 04:15:24 $
  $Author: ddarko $

  Append an item to the system menu.
  Copyright: CommonSoft Inc
  Nov. 96 D.Kolakovic
*/

#ifndef __AFXWIN_H__
  #include <AfxWin.h>
#endif

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif


//AppendSysMenu() -------------------------------------------------------------
/*Append an item to the system menu.
  Parameter uIDM is used as ID for both menu item control, and the resource 
  string table item.
  Range of acceptable values for uIDM is [16,65534].
  
  In WM_SYSCOMMAND messages, the four low-order bits of the nID parameter 
  are used internally by Windows. When an application tests the value of nID,
  it must combine the value 0xFFF0 with the nID value by using the bitwise-AND
  operator to obtain the correct result.
  The menu items in a Control menu can be modified with the GetSystemMenu, 
  AppendMenu, InsertMenu, and ModifyMenu member functions. Applications 
  that modify the Control menu must process WM_SYSCOMMAND messages, and 
  any WM_SYSCOMMAND messages not handled by the application must be 
  passed on to OnSysCommand. Any command values added by an application must 
  be processed by the application and cannot be passed to OnSysCommand.

  An application can carry out any system command at any time by passing a 
  WM_SYSCOMMAND message to OnSysCommand. 
  Accelerator (shortcut) keystrokes that are defined to select items from the
  Control menu are translated into OnSysCommand calls; all other accelerator
  keystrokes are translated into WM_COMMAND messages.

  Note: uses Microsoft Fundation Library (MFC).
        Microsoft Windows specific (Win). 
  */
void AppendSysMenu(HWND hMainWnd, //[in] handle of menu owner
                   UINT uIDM,     //[in] Control ID of the new menu item and 
                                  //resource string ID. Valid range is [16,65534].
                   BOOL bAddSeparator //[in] if TRUE a separator will be inserted
                                      //before new menu item
                   )
{
// IDM_menu_item must be in the system command range.
ASSERT((uIDM & 0xFFF0) >= 0x10);
ASSERT(uIDM < 0xF000);
ASSERT(::IsWindow(hMainWnd));

HMENU hSysMenu = ::GetSystemMenu(hMainWnd,FALSE);
CString strMenu;

strMenu.LoadString(uIDM);
if (!strMenu.IsEmpty())
  {
  if(bAddSeparator)
    VERIFY(::AppendMenu(hSysMenu,MF_SEPARATOR,0,NULL));
  VERIFY(::AppendMenu(hSysMenu,MF_STRING, uIDM, (LPCTSTR)strMenu));
  }

}

/*Note: uses Microsoft Fundation Library (MFC).
        Microsoft Windows specific (Win). 
 */
void AppendSysMenu(CWnd *pWnd,//[in] If pWnd is NULL, item will be appended to
                              // main window system menu. 
                   UINT uIDM, //[in] Control ID of the new menu item and 
                              //resource string ID. Valid range is [16,65534].
                   BOOL bAddSeparator //[in] if TRUE a separator will be inserted
                                      //before new menu item
                   )
{
if (pWnd == NULL)
  {
  pWnd = AfxGetApp()->m_pMainWnd;
  if (pWnd == NULL)
    {
    ASSERT(FALSE);
    TRACE0("AppendSysMenu() Initialization error.\n");
    return;
    }
  }
ASSERT_VALID(pWnd);
AppendSysMenu(pWnd->m_hWnd,uIDM,bAddSeparator);
}

