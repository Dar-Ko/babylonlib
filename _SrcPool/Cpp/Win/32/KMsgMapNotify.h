/*$RCSfile: KMsgMapNotify.h,v $: header file
  $Revision: 1.3 $ $Date: 2009/04/21 21:34:56 $
  $Author: ddarko $

  Windows common control notification message map macros
  Note: Microsoft Windows specific (Win32).
  Copyright: Alax.Info, 2006-2007
  2007-01-11 Roman Ryltsov
  2009-02-01 Darko Kolakovic
 */
// Group=Windows

#pragma once

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#include "atlcrack.h"  //Windows Template Library (WTL)

///////////////////////////////////////////////////////////////////////////////
// Notification message map handlers
// Note: for ATL 3.0, a message map using cracked handlers MUST use BEGIN_MSG_MAP_EX.
// For ATL 7.0 or higher, you can use BEGIN_MSG_MAP for CWindowImpl/CDialogImpl
// derived classes, but must use BEGIN_MSG_MAP_EX for classes that don't derive
// from CWindowImpl/CDialogImpl.
//
// Note: uses Microsoft Active Template Library (ATL);
//       Windows Template Library (WTL);
//       Microsoft Windows specific (Win32).
//
// See also: WTL/include/atlcrack.h, BEGIN_MSG_MAP_EX(), END_MSG_MAP()

//-----------------------------------------------------------------------------
/*WM_COMMAND Notification message is sent when the user selects a command item
  from a menu, when a control sends a notification message to its parent window,
  or when an accelerator keystroke is translated.

    Message source                  Message parameters
                    HIWORD(wParam)   LOWORD(wParam)          lParam
    Control         uNotifyCode      nIdentifier             control window handle
    Menu            0                Menu identifier or 0    0
    Accelerator     1                Accelerator identifier  0

  Parameters:
    uNotifyCode    Control-defined notification code
    nIdentifier    Control identifier
    func           Message handler

  Message handler:
    LRESULT OnCommand(UINT uNotifyCode, //[in] control-defined notification code
                      INT  nIdentifier, //[in] control identifier
                      HWND hwndCtl      //[in] handle to the control window
                     )

  See also: MSG_WM_COMMAND(), BEGIN_MSG_MAP_EX(), END_MSG_MAP(), WM_COMMAND
 */
#define MSG_WM_COMMAND_NOTIFY(uNotifyCode, nIdentifier, func) \
  if( uMsg == WM_COMMAND &&  \
      HIWORD(wParam)->code == uNotifyCode && \
      LOWORD(wParam) == nIdentifier) \
    { \
    SetMsgHandled(TRUE); \
    lResult = func((UINT) HIWORD(wParam), (INT) LOWORD(wParam), (HWND) lParam); \
    if(IsMsgHandled()) \
      return TRUE; \
    }

//-----------------------------------------------------------------------------
/*WM_NOTIFY message is sent by a common control to its parent window when
  an event has occurred or the control requires some information.

    Message parameters:
    wParam      nIdentifier
    lParam      NMHDR* or other structure with notification code
                and additional information

  Parameters:
    uNotifyCode    Control-defined notification code
    NotifyStruct   Structure with notification code and other data
    nIdentifier    Control identifier
    func           Message handler

  Message handler:
    LRESULT OnNotify(NotifyStruct* pNmh //[in] NMHDR or some other structure
                          //that has the NMHDR structure as its first member
                    )

  See also: MSG_WM_NOTIFY(), BEGIN_MSG_MAP_EX(), END_MSG_MAP(), WM_NOTIFY,
  HANDLE_WM_NOTIFY()
 */
#define MSG_WM_NOTIFY_CODE(uNotifyCode, NotifyStruct, nIdentifier, func) \
  if(uMsg == WM_NOTIFY && \
     ((NMHDR*) lParam)->code == uNotifyCode &&  \
     ((NMHDR*) lParam)->idFrom == nIdentifier) \
    { \
    SetMsgHandled(TRUE); \
    lResult = func((NotifyStruct*) lParam); \
    if(IsMsgHandled()) \
      return TRUE; \
    }

//=============================================================================
#if !defined(NOANIMATE)
  //----------------------------------------------------------------------------
  /*ACN_START notifies an animation control's parent window that the associated
    AVI clip has started playing. This notification message is sent in the form
    of a WM_COMMAND message.

  Parameters:
    nIdentifier    Control identifier
    func           Message handler

  Message handler:
    LRESULT OnAcnStart(UINT uNotifyCode, //[in] control-defined notification code
                       INT  nIdentifier, //[in] control identifier
                       HWND hwndCtl      //[in] handle to the control window
                      )
    The return value is ignored.

    See also: MSG_WM_COMMAND_NOTIFY(), <commctrl.h>
   */
  #define MSG_ACN_START(nIdentifier, func) \
          MSG_WM_COMMAND_NOTIFY(ACN_START, nIdentifier, func)

  //----------------------------------------------------------------------------
  /*ACN_STOP notifies an animation control's parent window that the associated
    AVI clip has stopped playing. This notification message is sent in the form
    of a WM_COMMAND message.

  Parameters:
    nIdentifier    Control identifier
    func           Message handler

  Message handler:
    LRESULT OnAcnStop(UINT uNotifyCode, //[in] control-defined notification code
                      INT  nIdentifier, //[in] control identifier
                      HWND hwndCtl      //[in] handle to the control window
                     )
    The return value is ignored.

    See also: MSG_WM_COMMAND_NOTIFY(), <commctrl.h>
   */
  #define MSG_ACN_STOP(nIdentifier, func) \
          MSG_WM_COMMAND_NOTIFY(ACN_STOP, nIdentifier, func)
#endif // !defined(NOANIMATE)

//=============================================================================

#define MSG_NM_OUTOFMEMORY(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_OUTOFMEMORY, NMHDR, nIdentifier, func)
#define MSG_NM_CLICK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_CLICK, NMHDR, nIdentifier, func) // NMCLICK?
#define MSG_NM_DBLCLK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_DBLCLK, NMHDR, nIdentifier, func)
#define MSG_NM_RETURN(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_RETURN, NMHDR, nIdentifier, func)
#define MSG_NM_RCLICK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_RCLICK, NMHDR, nIdentifier, func) // NMCLICK?
#define MSG_NM_RDBLCLK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_RDBLCLK, NMHDR, nIdentifier, func)
#define MSG_NM_SETFOCUS(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_SETFOCUS, NMHDR, nIdentifier, func)
#define MSG_NM_KILLFOCUS(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_KILLFOCUS, NMHDR, nIdentifier, func)
#if (_WIN32_IE >= 0x0300)
  #define MSG_NM_CUSTOMDRAW(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_CUSTOMDRAW, NMCUSTOMDRAW, nIdentifier, func)
  #define MSG_NM_HOVER(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_HOVER, NMHDR, nIdentifier, func)
#endif // (_WIN32_IE >= 0x0300)
#if (_WIN32_IE >= 0x0400)
  #define MSG_NM_NCHITTEST(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_NCHITTEST, NMMOUSE, nIdentifier, func)
  #define MSG_NM_KEYDOWN(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_KEYDOWN, NMKEY, nIdentifier, func)
  #define MSG_NM_RELEASEDCAPTURE(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_RELEASEDCAPTURE, NMHDR, nIdentifier, func)
  #define MSG_NM_SETCURSOR(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_SETCURSOR, NMMOUSE, nIdentifier, func)
  #define MSG_NM_CHAR(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_CHAR, NMCHAR, nIdentifier, func)
#endif // (_WIN32_IE >= 0x0400)
#if (_WIN32_IE >= 0x0401)
  #define MSG_NM_TOOLTIPSCREATED(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_TOOLTIPSCREATED, NMTOOLTIPSCREATED, nIdentifier, func)
#endif // (_WIN32_IE >= 0x0401)
#if (_WIN32_IE >= 0x0500)
  #define MSG_NM_LDOWN(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(MSG_NM_LDOWN, NMKEY, nIdentifier, func)
  #define MSG_NM_RDOWN(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(MSG_NM_RDOWN, NMKEY, nIdentifier, func)
  #define MSG_NM_THEMECHANGED(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_THEMECHANGED, NMKEY, nIdentifier, func)
#endif // (_WIN32_IE >= 0x0500)

//=============================================================================
#if !defined(NOUSER)
#endif // !defined(NOUSER)

//=============================================================================
#if !defined(NOIMAGEAPIS)
#endif // !defined(NOIMAGEAPIS)

//=============================================================================
#if !defined(NOHEADER)
  #define MSG_HDN_RCLICK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_RCLICK, NMHDR, nIdentifier, func)
  #if (_WIN32_IE >= 0x0300)
    #define MSG_HDN_CUSTOMDRAW(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_CUSTOMDRAW, NMCUSTOMDRAW, nIdentifier, func)
  #endif // (_WIN32_IE >= 0x0300)
  #if (_WIN32_IE >= 0x0400)
    #define MSG_HDN_RELEASEDCAPTURE(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_RELEASEDCAPTURE, NMHDR, nIdentifier, func)
  #endif // (_WIN32_IE >= 0x0400)
  #define MSG_HDN_ITEMCHANGING(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(HDN_ITEMCHANGING, NMHEADER, nIdentifier, func)
  #define MSG_HDN_ITEMCHANGED(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(HDN_ITEMCHANGED, NMHEADER, nIdentifier, func)
  #define MSG_HDN_ITEMCLICK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(HDN_ITEMCLICK, NMHEADER, nIdentifier, func)
  #define MSG_HDN_ITEMDBLCLICK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(HDN_ITEMDBLCLICK, NMHEADER, nIdentifier, func)
  #define MSG_HDN_DIVIDERDBLCLICK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(HDN_DIVIDERDBLCLICK, NMHEADER, nIdentifier, func)
  #define MSG_HDN_BEGINTRACK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(HDN_BEGINTRACK, NMHEADER, nIdentifier, func)
  #define MSG_HDN_ENDTRACK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(HDN_ENDTRACK, NMHEADER, nIdentifier, func)
  #define MSG_HDN_TRACK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(HDN_TRACK, NMHEADER, nIdentifier, func)
  #if (_WIN32_IE >= 0x0300)
    #define MSG_HDN_GETDISPINFO(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(HDN_GETDISPINFO, NMHDDISPINFO, nIdentifier, func)
    #define MSG_HDN_BEGINDRAG(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(HDN_BEGINDRAG, NMHEADER, nIdentifier, func)
    #define MSG_HDN_ENDDRAG(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(HDN_ENDDRAG, NMHEADER, nIdentifier, func)
  #endif // (_WIN32_IE >= 0x0300)
  #if (_WIN32_IE >= 0x0500)
    #define MSG_HDN_FILTERCHANGE(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(HDN_FILTERCHANGE, NMHEADER, nIdentifier, func)
    #define MSG_HDN_FILTERBTNCLICK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(HDN_FILTERBTNCLICK, NMHDFILTERBTNCLICK, nIdentifier, func)
  #endif // (_WIN32_IE >= 0x0500)
#endif // !defined(NOHEADER)

//=============================================================================
#if !defined(NOTOOLBAR)
  #define MSG_TBN_RCLICK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_RCLICK, NMMOUSE, nIdentifier, func)
  #define MSG_TBN_RDBLCLK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_RDBLCLK, NMHDR, nIdentifier, func)
  #if (_WIN32_IE >= 0x0300)
    #if (_WIN32_IE >= 0x0400)
      #define MSG_TBN_CUSTOMDRAW(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_CUSTOMDRAW, NMTBCUSTOMDRAW, nIdentifier, func) // NMCUSTOMDRAW prior to 4.71
    #else
      #define MSG_TBN_CUSTOMDRAW(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_CUSTOMDRAW, NMCUSTOMDRAW, nIdentifier, func)
    #endif // (_WIN32_IE >= 0x0400)
  #endif // (_WIN32_IE >= 0x0300)
  #if (_WIN32_IE >= 0x0400)
    #define MSG_TBN_KEYDOWN(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_KEYDOWN, NMKEY, nIdentifier, func)
    #define MSG_TBN_RELEASEDCAPTURE(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_RELEASEDCAPTURE, NMHDR, nIdentifier, func)
    #define MSG_TBN_CHAR(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_CHAR, NMCHAR, nIdentifier, func)
  #endif // (_WIN32_IE >= 0x0400)
  #if (_WIN32_IE >= 0x0401)
    #define MSG_TBN_TOOLTIPSCREATED(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_TOOLTIPSCREATED, NMTOOLTIPSCREATED, nIdentifier, func)
  #endif // (_WIN32_IE >= 0x0401)
  #if (_WIN32_IE >= 0x0500)
    #define MSG_TBN_LDOWN(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(MSG_TBN_LDOWN, NMKEY, nIdentifier, func)
  #endif // (_WIN32_IE >= 0x0500)
  #if !defined(_UNICODE)
    #define MSG_TBN_GETBUTTONINFO(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TBN_GETBUTTONINFO, NMTOOLBAR, nIdentifier, func)
  #endif // !defined(_UNICODE)
  #define MSG_TBN_BEGINDRAG(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TBN_BEGINDRAG, NMTOOLBAR, nIdentifier, func)
  #define MSG_TBN_ENDDRAG(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TBN_ENDDRAG, NMTOOLBAR, nIdentifier, func)
  #define MSG_TBN_BEGINADJUST(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TBN_BEGINADJUST, NMTOOLBAR, nIdentifier, func)
  #define MSG_TBN_ENDADJUST(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TBN_ENDADJUST, NMTOOLBAR, nIdentifier, func)
  #define MSG_TBN_RESET(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TBN_RESET, NMHDR, nIdentifier, func)
  #define MSG_TBN_QUERYINSERT(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TBN_QUERYINSERT, NMTOOLBAR, nIdentifier, func)
  #define MSG_TBN_QUERYDELETE(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TBN_QUERYDELETE, NMTOOLBAR, nIdentifier, func)
  #define MSG_TBN_TOOLBARCHANGE(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TBN_TOOLBARCHANGE, NMHDR, nIdentifier, func)
  #if (_WIN32_IE >= 0x0300)
    #define MSG_TBN_DROPDOWN(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TBN_DROPDOWN, NMTOOLBAR, nIdentifier, func)
  #endif // (_WIN32_IE >= 0x0300)
  #if (_WIN32_IE >= 0x0400)
    #define MSG_TBN_GETOBJECT(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TBN_GETOBJECT, NMOBJECTNOTIFY, nIdentifier, func)
    #define MSG_TBN_HOTITEMCHANGE(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TBN_HOTITEMCHANGE, NMTBHOTITEM, nIdentifier, func)
    #define MSG_TBN_DRAGOUT(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TBN_DRAGOUT, NMTOOLBAR, nIdentifier, func)
    #define MSG_TBN_DELETINGBUTTON(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TBN_DELETINGBUTTON, NMTOOLBAR, nIdentifier, func)
    #define MSG_TBN_GETDISPINFO(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TBN_GETDISPINFOA, NMTBDISPINFO, nIdentifier, func)
    #define MSG_TBN_GETINFOTIP(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TBN_GETINFOTIPW, NMTBDISPINFO, nIdentifier, func)
    #if defined(_UNICODE)
      #define MSG_TBN_GETBUTTONINFO(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TBN_GETBUTTONINFO, NMTOOLBAR, nIdentifier, func)
    #endif // defined(_UNICODE)
  #endif // (_WIN32_IE >= 0x0400)
  #if (_WIN32_IE >= 0x0500)
    #define MSG_TBN_RESTORE(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TBN_RESTORE, NMRESTORE, nIdentifier, func)
    #define MSG_TBN_SAVE(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TBN_SAVE, NMSAVE, nIdentifier, func)
    #define MSG_TBN_INITCUSTOMIZE(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TBN_INITCUSTOMIZE, NMHDR, nIdentifier, func)
  #endif // (_WIN32_IE >= 0x0500)
#endif // !defined(NOTOOLBAR)

//=============================================================================
#if !defined(NOREBAR)
  #if (_WIN32_IE >= 0x0300)
    #define MSG_RBN_CUSTOMDRAW(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_CUSTOMDRAW, NMCUSTOMDRAW, nIdentifier, func)
  #endif // (_WIN32_IE >= 0x0300)
  #if (_WIN32_IE >= 0x0400)
    #define MSG_RBN_NCHITTEST(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_NCHITTEST, NMMOUSE, nIdentifier, func)
    #define MSG_RBN_RELEASEDCAPTURE(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_RELEASEDCAPTURE, NMHDR, nIdentifier, func)
  #endif // (_WIN32_IE >= 0x0400)
    #define MSG_RBN_HEIGHTCHANGE(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(RBN_HEIGHTCHANGE, NMHDR, nIdentifier, func)
  #if (_WIN32_IE >= 0x0400)
    #define MSG_RBN_GETOBJECT(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(RBN_GETOBJECT, NMOBJECTNOTIFY, nIdentifier, func)
    #define MSG_RBN_LAYOUTCHANGED(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(RBN_LAYOUTCHANGED, NMHDR, nIdentifier, func)
    #define MSG_RBN_AUTOSIZE(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(RBN_AUTOSIZE, NMRBAUTOSIZE, nIdentifier, func)
    #define MSG_RBN_BEGINDRAG(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(RBN_BEGINDRAG, NMREBAR, nIdentifier, func)
    #define MSG_RBN_ENDDRAG(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(RBN_ENDDRAG, NMREBAR, nIdentifier, func)
    #define MSG_RBN_DELETINGBAND(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(RBN_DELETINGBAND, NMREBAR, nIdentifier, func)
    #define MSG_RBN_DELETEDBAND(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(RBN_DELETEDBAND, NMREBAR, nIdentifier, func)
    #define MSG_RBN_CHILDSIZE(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(RBN_CHILDSIZE, NMREBARCHILDSIZE, nIdentifier, func)
  #endif // (_WIN32_IE >= 0x0400)
  #if (_WIN32_IE >= 0x0500)
    #define MSG_RBN_CHEVRONPUSHED(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(RBN_CHEVRONPUSHED, NMREBARCHEVRON, nIdentifier, func)
    #define MSG_RBN_MINMAX(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(RBN_MINMAX, NMHDR, nIdentifier, func) // MSDN does not specify header type
  #endif // (_WIN32_IE >= 0x0500)
  #if (_WIN32_WINNT >= 0x0501)
    #define MSG_RBN_AUTOBREAK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(RBN_AUTOBREAK, NMREBARAUTOBREAK, nIdentifier, func)
  #endif // (_WIN32_WINNT >= 0x0501)
#endif // !defined(NOREBAR)

//=============================================================================
#if !defined(NOIMAGEAPIS)
#endif // !defined(NOIMAGEAPIS)

//=============================================================================
#if !defined(NOTOOLTIPS)
  #if (_WIN32_IE >= 0x0300)
    #define MSG_TTN_CUSTOMDRAW(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_CUSTOMDRAW, NMTTCUSTOMDRAW, nIdentifier, func)
  #endif // (_WIN32_IE >= 0x0300)
  #define MSG_TTN_GETDISPINFO(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TTN_GETDISPINFO, NMTTDISPINFO, nIdentifier, func)
  #define MSG_TTN_SHOW(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TTN_SHOW, NMHDR, nIdentifier, func)
  #define MSG_TTN_POP(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TTN_POP, NMHDR, nIdentifier, func)
  #define MSG_TTN_LINKCLICK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TTN_LINKCLICK, NMHDR, nIdentifier, func)
#endif // !defined(NOTOOLTIPS)

//=============================================================================
#if !defined(NOSTATUSBAR)
  #define MSG_SBN_CLICK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_CLICK, NMMOUSE, nIdentifier, func)
  #define MSG_SBN_DBLCLK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_DBLCLK, NMMOUSE, nIdentifier, func)
  #define MSG_SBN_RCLICK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_RCLICK, NMMOUSE, nIdentifier, func)
  #define MSG_SBN_RDBLCLK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_RDBLCLK, NMMOUSE, nIdentifier, func)
  #if (_WIN32_IE >= 0x0400)
    #define SBN_SIMPLEMODECHANGE    (SBN_FIRST - 0)
  #endif // (_WIN32_IE >= 0x0400)
#endif // !defined(NOSTATUSBAR)

//=============================================================================
#if !defined(NOMENUHELP)
#endif // !defined(NOMENUHELP)

//=============================================================================
#if !defined(NOTRACKBAR)
//#if (_WIN32_IE >= 0x0300)
//  #define MSG_TBN_CUSTOMDRAW(nIdentifier, func) \
//          MSG_WM_NOTIFY_CODE(NM_CUSTOMDRAW, NMCUSTOMDRAW, nIdentifier, func)
//#endif // (_WIN32_IE >= 0x0300)
//#if (_WIN32_IE >= 0x0400)
//  #define MSG_TBN_RELEASEDCAPTURE(nIdentifier, func) \
//          MSG_WM_NOTIFY_CODE(NM_RELEASEDCAPTURE, NMHDR, nIdentifier, func)
//#endif // (_WIN32_IE >= 0x0400)
#endif // !defined(NOTRACKBAR)

//=============================================================================
#if !defined(NODRAGLIST)
//#define MSG_DL_BEGINDRAG(nIdentifier, func) \
//          MSG_WM_NOTIFY_CODE(DL_BEGINDRAG, DRAGLISTINFO, nIdentifier, func)
//#define MSG_DL_DRAGGING(nIdentifier, func) \
//          MSG_WM_NOTIFY_CODE(DL_DRAGGING, DRAGLISTINFO, nIdentifier, func)
//#define MSG_DL_DROPPED(nIdentifier, func) \
//          MSG_WM_NOTIFY_CODE(DL_DROPPED, DRAGLISTINFO, nIdentifier, func)
//#define MSG_DL_CANCELDRAG(nIdentifier, func) \
//          MSG_WM_NOTIFY_CODE(DL_CANCELDRAG, DRAGLISTINFO, nIdentifier, func)
#endif // !defined(NODRAGLIST)

//=============================================================================
#if !defined(NOUPDOWN)
  #if (_WIN32_IE >= 0x0400)
    #define MSG_UDN_RELEASEDCAPTURE(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_RELEASEDCAPTURE, NMHDR, nIdentifier, func)
  #endif // (_WIN32_IE >= 0x0400)
  #define MSG_UDN_DELTAPOS(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(UDN_DELTAPOS, NMUPDOWN, nIdentifier, func)
#endif // !defined(NOUPDOWN)

//=============================================================================
#if !defined(NOPROGRESS)
#endif // !defined(NOPROGRESS)

//=============================================================================
#if !defined(NOHOTKEY)
#endif // !defined(NOHOTKEY)

//=============================================================================
#if !defined(NOLISTVIEW)
  #if (_WIN32_IE >= 0x0400)
    #define MSG_LVN_CLICK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_CLICK, NMITEMACTIVATE, nIdentifier, func) // NMHDR prior to 4.71

  //---------------------------------------------------------------------------
  /*NM_DBLCLK notifies a control's parent window that the user has
    double-clicked the left mouse button within the control.
    This notification message is sent in the form of a WM_NOTIFY message.

  MSG_LVN_DBLCLK parameters:
    nIdentifier    Control identifier
    func           Message handler

  Message handler:
    Handles an event that occurs when the user double-clicks certain elment
    within a control.
    The return value is ignored.

    Shell version 4.0 to 4.71
    LRESULT OnDblClk(NMHDR* pHeader //[in] specifies the information
                                    //about clicked item.
                         )

    Shell version 4.71 or higher
    LRESULT OnDblClk(NMITEMACTIVATE* pHeader //[in] specifies the information
                                             //about clicked item.
                         )

    Note: starting with version 4.71, the Shell and common controls DLLs, among
    others, began exporting DllGetVersion. This function can be called by
    an application to determine which DLL version is present on the system.
    It returns a structure that contains version information.

    See also: MSG_WM_NOTIFY_CODE(), <commctrl.h>, NMITEMACTIVATE,
    {html: <a href="http://msdn.microsoft.com/en-us/library/bb776779(VS.85).aspx">
    DLL Version Numbers</a>}
   */
    #define MSG_LVN_DBLCLK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_DBLCLK, NMITEMACTIVATE, nIdentifier, func)
  #else
    #define MSG_LVN_CLICK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_CLICK, NMHDR, nIdentifier, func)
    #define MSG_LVN_DBLCLK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_DBLCLK, NMHDR, nIdentifier, func)
  #endif // (_WIN32_IE >= 0x0400)
  #define MSG_LVN_RETURN(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_RETURN, NMHDR, nIdentifier, func)
  #if (_WIN32_IE >= 0x0400)
    #define MSG_LVN_RCLICK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_CLICK, NMITEMACTIVATE, nIdentifier, func) // NMHDR prior to 4.71
    #define MSG_LVN_RDBLCLK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_DBLCLK, NMITEMACTIVATE, nIdentifier, func) // NMHDR prior to 4.71
  #else
    #define MSG_LVN_RCLICK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_RCLICK, NMHDR, nIdentifier, func)
    #define MSG_LVN_RDBLCLK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_RDBLCLK, NMHDR, nIdentifier, func)
  #endif // (_WIN32_IE >= 0x0400)
  #define MSG_LVN_SETFOCUS(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_SETFOCUS, NMHDR, nIdentifier, func)
  #define MSG_LVN_KILLFOCUS(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_KILLFOCUS, NMHDR, nIdentifier, func)
  #if (_WIN32_IE >= 0x0300)
    #define MSG_LVN_CUSTOMDRAW(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_CUSTOMDRAW, NMLVCUSTOMDRAW, nIdentifier, func)
    #define MSG_LVN_HOVER(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_HOVER, NMHDR, nIdentifier, func)
  #endif // (_WIN32_IE >= 0x0300)
  #if (_WIN32_IE >= 0x0400)
    #define MSG_LVN_RELEASEDCAPTURE(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_RELEASEDCAPTURE, NMHDR, nIdentifier, func)
  #endif // (_WIN32_IE >= 0x0400)
  #define MSG_LVN_ITEMCHANGING(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(LVN_ITEMCHANGING, NMLISTVIEW, nIdentifier, func)
  #define MSG_LVN_ITEMCHANGED(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(LVN_ITEMCHANGED, NMLISTVIEW, nIdentifier, func)
  #define MSG_LVN_INSERTITEM(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(LVN_INSERTITEM, NMLISTVIEW, nIdentifier, func)
  #define MSG_LVN_DELETEITEM(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(LVN_DELETEITEM, NMLISTVIEW, nIdentifier, func)
  #define MSG_LVN_DELETEALLITEMS(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(LVN_DELETEALLITEMS, NMLISTVIEW, nIdentifier, func)
  #define MSG_LVN_BEGINLABELEDIT(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(LVN_BEGINLABELEDIT, NMLVDISPINFO, nIdentifier, func)
  #define MSG_LVN_ENDLABELEDIT(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(LVN_ENDLABELEDIT, NMLVDISPINFO, nIdentifier, func)
  #define MSG_LVN_COLUMNCLICK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(LVN_COLUMNCLICK, NMLISTVIEW, nIdentifier, func)
  #define MSG_LVN_BEGINDRAG(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(LVN_BEGINDRAG, NMLISTVIEW, nIdentifier, func)
  #define MSG_LVN_BEGINRDRAG(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(LVN_BEGINRDRAG, NMLISTVIEW, nIdentifier, func)
  #if (_WIN32_IE >= 0x0300)
    #define MSG_LVN_ODCACHEHINT(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(LVN_ODCACHEHINT, NMLVCACHEHINT, nIdentifier, func)
    #define MSG_LVN_ODFINDITEM(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(LVN_ODFINDITEM, NMLVFINDITEM, nIdentifier, func)
    #if (_WIN32_IE >= 0x0400)
      #define MSG_LVN_ITEMACTIVATE(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(LVN_ITEMACTIVATE, NMITEMACTIVATE, nIdentifier, func) // NMHDR prior to 4.71
    #else
      #define MSG_LVN_ITEMACTIVATE(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(LVN_ITEMACTIVATE, NMHDR, nIdentifier, func)
    #endif // (_WIN32_IE >= 0x0400)
    #define MSG_LVN_ODSTATECHANGED(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(LVN_ODSTATECHANGED, NMLVODSTATECHANGE, nIdentifier, func)
  #endif // (_WIN32_IE >= 0x0300)
  #if (_WIN32_IE >= 0x0400)
    #define MSG_LVN_HOTTRACK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(LVN_HOTTRACK, NMLISTVIEW, nIdentifier, func)
  #endif // (_WIN32_IE >= 0x0400)
  //---------------------------------------------------------------------------
  /*LVN_GETDISPINFO notifies a list-view control's parent window that the control
    requires needed to display or sort a list-view item. This notification message
    is sent in the form of a WM_NOTIFY message.

  Parameters:
    nIdentifier    Control identifier
    func           Message handler

  Message handler:
    LRESULT OnGetDispInfo(NMLVDISPINFO* pHeader //[in/out] specifies the attributes
                                                //of a list-view item.
                         )
    The return value is ignored.

    See also: MSG_WM_NOTIFY_CODE(), <commctrl.h>, LVITEM, NMLVDISPINFO,
    LV_DISPINFO
   */
  #define MSG_LVN_GETDISPINFO(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(LVN_GETDISPINFO, NMLVDISPINFO, nIdentifier, func)

  //---------------------------------------------------------------------------
  /*LVN_SETDISPINFO notifies a list-view control's parent window that it must
    update the information it maintains for a list-view item.
    This notification message is sent in the form of a WM_NOTIFY message.

  Parameters:
    nIdentifier    Control identifier
    func           Message handler

  Message handler:
    LRESULT OnSetDispInfo(NMLVDISPINFO* pHeader //[in] specifies the information
                                                //for the changed list-view item.
                         )
    The return value is ignored.(?? TODO: verify this)

    See also: MSG_WM_NOTIFY_CODE(), <commctrl.h>, LVITEM, NMLVDISPINFO,
    LV_DISPINFO
   */
  #define MSG_LVN_SETDISPINFO(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(LVN_SETDISPINFO, NMLVDISPINFO, nIdentifier, func)

  #define MSG_LVN_KEYDOWN(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(LVN_KEYDOWN, NMLVKEYDOWN, nIdentifier, func)
  #if (_WIN32_IE >= 0x0300)
    #define MSG_LVN_MARQUEEBEGIN(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(LVN_MARQUEEBEGIN, NMHDR, nIdentifier, func)
  #endif // (_WIN32_IE >= 0x0300)
  #if (_WIN32_IE >= 0x0400)
  //---------------------------------------------------------------------------
  /*LVN_GETINFOTIP notifies a list-view control's parent window that the control
    with the LVS_EX_INFOTIP extended style requires text information to be
    displayed in a ToolTip. The notification is sent only for subitem 0.
    This notification message is sent in the form of a WM_NOTIFY message.

  WM_NOTIFY parameters
    - wParam   identifier of the common control sending the message.
               This identifier is not guaranteed to be unique.
    - lParam   pointer to an NMLVGETINFOTIP structure that contains information
               about this notification. 
  
  An application should use the hwndFrom or idFrom member of the NMHDR
  structure (passed as the lParam parameter) to identify the control.

  MSG_LVN_GETINFOTIP parameters:
    nIdentifier    Control identifier
    func           Message handler

  Message handler:
    Handles request from the list-view control for additional text information
    to be displayed in a ToolTip.

      struct tagNMLVGETINFOTIP
        {
        NMHDR hdr;      //NMHDR structure that contains information on this
                        //notification message. 
        DWORD dwFlags;  //zero if the item text is truncated or LVGIT_UNFOLDED.
        LPTSTR pszText; //whole item text copy if item text is truncated
        int cchTextMax; //buffer size in characters, of the buffer pointed to
                        //by pszText.
        int iItem;      //index of the item to which this structure refers.
        int iSubItem;   //index of the subitem to which this structure refers.
        LPARAM lParam;  //reserved for future use.
        };

    The return value is ignored.

    LRESULT OnGetInfoTip(NMLVGETINFOTIP* pHeader //[in/out] specifies list-view
                                                 //item information for a ToolTip.
                         )

    See also: MSG_WM_NOTIFY_CODE(), MSG_WM_NOTIFY(), <commctrl.h>, NMLVGETINFOTIP,
    LVM_SETINFOTIP, LVSETINFOTIP
   */
    #define MSG_LVN_GETINFOTIP(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(LVN_GETINFOTIP, NMLVGETINFOTIP, nIdentifier, func)
  #endif // (_WIN32_IE >= 0x0400)
  #if (_WIN32_WINNT >= 0x0501)
    #define MSG_LVN_BEGINSCROLL(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(LVN_BEGINSCROLL, NMLVSCROLL, nIdentifier, func)
    #define MSG_LVN_ENDSCROLL(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(LVN_ENDSCROLL, NMLVSCROLL, nIdentifier, func)
  #endif // (_WIN32_WINNT >= 0x0501)
#endif // !defined(NOLISTVIEW)

//=============================================================================
#if !defined(NOTREEVIEW)
  #define MSG_TVN_CLICK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_CLICK, NMHDR, nIdentifier, func)
  #define MSG_TVN_DBLCLK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_DBLCLK, NMHDR, nIdentifier, func)
  #define MSG_TVN_RETURN(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_RETURN, NMHDR, nIdentifier, func)
  #define MSG_TVN_RCLICK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_RCLICK, NMHDR, nIdentifier, func)
  #define MSG_TVN_RDBLCLK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_RDBLCLK, NMHDR, nIdentifier, func)
  #define MSG_TVN_SETFOCUS(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_SETFOCUS, NMHDR, nIdentifier, func)
  #define MSG_TVN_KILLFOCUS(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_KILLFOCUS, NMHDR, nIdentifier, func)
  #if (_WIN32_IE >= 0x0300)
    #define MSG_TVN_CUSTOMDRAW(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_CUSTOMDRAW, NMTVCUSTOMDRAW, nIdentifier, func)
  #endif // (_WIN32_IE >= 0x0300)
  #if (_WIN32_IE >= 0x0400)
    #define MSG_TVN_SETCURSOR(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_SETCURSOR, NMMOUSE, nIdentifier, func)
  #endif // (_WIN32_IE >= 0x0400)
  #define MSG_TVN_SELCHANGING(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TVN_SELCHANGING, NMTREEVIEW, nIdentifier, func)
  #define MSG_TVN_SELCHANGED(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TVN_SELCHANGED, NMTREEVIEW, nIdentifier, func)
  #define MSG_TVN_GETDISPINFO(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TVN_GETDISPINFO, NMTVDISPINFO, nIdentifier, func)
  #define MSG_TVN_SETDISPINFO(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TVN_SETDISPINFO, NMTVDISPINFO, nIdentifier, func)
  #define MSG_TVN_ITEMEXPANDING(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TVN_ITEMEXPANDING, NMTREEVIEW, nIdentifier, func)
  #define MSG_TVN_ITEMEXPANDED(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TVN_ITEMEXPANDED, NMTREEVIEW, nIdentifier, func)
  #define MSG_TVN_BEGINDRAG(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TVN_BEGINDRAG, NMTREEVIEW, nIdentifier, func)
  #define MSG_TVN_BEGINRDRAG(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TVN_BEGINRDRAG, NMTREEVIEW, nIdentifier, func)
  #define MSG_TVN_DELETEITEM(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TVN_DELETEITEM, NMTREEVIEW, nIdentifier, func)
  #define MSG_TVN_BEGINLABELEDIT(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TVN_BEGINLABELEDIT, NMTVDISPINFO, nIdentifier, func)
  #define MSG_TVN_ENDLABELEDIT(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TVN_ENDLABELEDIT, NMTVDISPINFO, nIdentifier, func)
  #define MSG_TVN_KEYDOWN(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TVN_KEYDOWN, NMTVKEYDOWN, nIdentifier, func)
    #if (_WIN32_IE >= 0x0400)
    #define MSG_TVN_GETINFOTIP(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TVN_GETINFOTIP, NMTVGETINFOTIP, nIdentifier, func)
    #define MSG_TVN_SINGLEEXPAND(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TVN_SINGLEEXPAND, NMTREEVIEW, nIdentifier, func)
  #endif // (_WIN32_IE >= 0x0400)
#endif // !defined(NOTREEVIEW)

//=============================================================================
#if !defined(NOUSEREXCONTROLS)
  #if (_WIN32_IE >= 0x0400)
    #define MSG_CBEN_SETCURSOR(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_SETCURSOR, NMMOUSE, nIdentifier, func)
  #endif // (_WIN32_IE >= 0x0400)
  #define MSG_CBEN_INSERTITEM(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(CBEN_INSERTITEM, NMCOMBOBOXEX, nIdentifier, func)
  #define MSG_CBEN_DELETEITEM(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(CBEN_DELETEITEM, NMCOMBOBOXEX, nIdentifier, func)
  #define MSG_CBEN_BEGINEDIT(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(CBEN_BEGINEDIT, NMHDR, nIdentifier, func)
  #define MSG_CBEN_ENDEDIT(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(CBEN_ENDEDIT, NMCBEENDEDIT, nIdentifier, func)
  #if (_WIN32_IE >= 0x0400)
    #define MSG_CBEN_GETDISPINFO(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(CBEN_GETDISPINFO, NMCOMBOBOXEX, nIdentifier, func)
    #define MSG_CBEN_DRAGBEGIN(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(CBEN_DRAGBEGIN, NMCBEDRAGBEGIN, nIdentifier, func)
  #endif // (_WIN32_IE >= 0x0400)
#endif // !defined(NOUSEREXCONTROLS)

//=============================================================================
#if !defined(NOTABCONTROL)
  #define MSG_TCN_CLICK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_CLICK, NMHDR, nIdentifier, func)
  #define MSG_TCN_RCLICK(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_RCLICK, NMHDR, nIdentifier, func)
  #if (_WIN32_IE >= 0x0400)
    #define MSG_TCN_RELEASEDCAPTURE(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_RELEASEDCAPTURE, NMHDR, nIdentifier, func)
  #endif // (_WIN32_IE >= 0x0400)
  #define MSG_TCN_KEYDOWN(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TCN_KEYDOWN, NMTCKEYDOWN, nIdentifier, func)
  #define MSG_TCN_SELCHANGE(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TCN_SELCHANGE, NMHDR, nIdentifier, func)
  #define MSG_TCN_SELCHANGING(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TCN_SELCHANGING, NMHDR, nIdentifier, func)
  #if (_WIN32_IE >= 0x0400)
    #define MSG_TCN_GETOBJECT(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TCN_GETOBJECT, NMOBJECTNOTIFY, nIdentifier, func)
  #endif // (_WIN32_IE >= 0x0400)
  #if (_WIN32_IE >= 0x0500)
    #define MSG_TCN_FOCUSCHANGE(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(TCN_FOCUSCHANGE, NMHDR, nIdentifier, func) // MSDN does not specify header type
  #endif // (_WIN32_IE >= 0x0500)
#endif // !defined(NOTABCONTROL)

//=============================================================================
#if !defined(NOMONTHCAL)
  #if (_WIN32_IE >= 0x0400)
    #define MSG_MCN_RELEASEDCAPTURE(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_RELEASEDCAPTURE, NMHDR, nIdentifier, func)
  #endif // (_WIN32_IE >= 0x0400)
  #define MSG_MCN_SELCHANGE(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(MCN_SELCHANGE, NMSELCHANGE, nIdentifier, func)
  #define MSG_MCN_GETDAYSTATE(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(MCN_GETDAYSTATE, NMDAYSTATE, nIdentifier, func)
  #define MSG_MCN_SELECT(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(MCN_SELECT, NMSELCHANGE, nIdentifier, func)
#endif // !defined(NOMONTHCAL)

//=============================================================================
#if !defined(NODATETIMEPICK)
  #define MSG_DTN_SETFOCUS(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_SETFOCUS, NMHDR, nIdentifier, func)
  #define MSG_DTN_KILLFOCUS(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_KILLFOCUS, NMHDR, nIdentifier, func)
  #define MSG_DTN_DATETIMECHANGE(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(DTN_DATETIMECHANGE, NMDATETIMECHANGE, nIdentifier, func)
  #define MSG_DTN_USERSTRING(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(DTN_USERSTRINGW, NMDATETIMESTRING, nIdentifier, func)
  #define MSG_DTN_WMKEYDOWN(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(DTN_WMKEYDOWNA, NMDATETIMEWMKEYDOWN, nIdentifier, func)
  #define MSG_DTN_FORMAT(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(DTN_FORMATA, NMDATETIMEFORMAT, nIdentifier, func)
  #define MSG_DTN_FORMATQUERY(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(DTN_FORMATQUERYW, NMDATETIMEFORMATQUERY, nIdentifier, func)
  #define MSG_DTN_DROPDOWN(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(DTN_DROPDOWN, NMHDR, nIdentifier, func)
  #define MSG_DTN_CLOSEUP(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(DTN_CLOSEUP, NMHDR, nIdentifier, func)
#endif // !defined(NODATETIMEPICK)

//=============================================================================
#if !defined(NOIPADDRESS)
  #define MSG_IPN_FIELDCHANGED(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(IPN_FIELDCHANGED, NMIPADDRESS, nIdentifier, func)
#endif // !defined(NOIPADDRESS)

//=============================================================================
#if !defined(NOPAGESCROLLER)
#endif // !defined(NOPAGESCROLLER)

//=============================================================================
#if !defined(NONATIVEFONTCTL)
#endif // !defined(NONATIVEFONTCTL)

//=============================================================================
#if !defined(NOBUTTON)
  #if (_WIN32_IE >= 0x0300)
    #define MSG_BCN_CUSTOMDRAW(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(NM_CUSTOMDRAW, NMCUSTOMDRAW, nIdentifier, func)
  #endif // (_WIN32_IE >= 0x0300)
    #define MSG_BCN_HOTITEMCHANGE(nIdentifier, func) \
          MSG_WM_NOTIFY_CODE(BCN_HOTITEMCHANGE, NMBCHOTITEM, nIdentifier, func)
#endif // !defined(NOBUTTON)

//=============================================================================
#if !defined(NOSTATIC)
#endif // !defined(NOSTATIC)

//=============================================================================
#if !defined(NOEDIT)
#endif // !defined(NOEDIT)

//=============================================================================
#if !defined(NOLISTBOX)
#endif // !defined(NOLISTBOX)

//=============================================================================
#if !defined(NOCOMBOBOX)
#endif // !defined(NOCOMBOBOX)

//=============================================================================
#if !defined(NOSCROLLBAR)
#endif // !defined(NOSCROLLBAR)

//=============================================================================
#if !defined(NOMUI)
#endif // !defined(NOMUI)

//=============================================================================
#if !defined(NOTRACKMOUSEEVENT)
#endif // !defined(NOTRACKMOUSEEVENT)

//=============================================================================
#if !defined(NOFLATSBAPIS)
#endif // !defined(NOFLATSBAPIS)

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: KMsgMapNotify.h,v $
 * Revision 1.3  2009/04/21 21:34:56  ddarko
 * Updated comments
 *
 * Revision 1.2  2009/02/24 21:42:33  ddarko
 * Test common control notification messages
 *
 *****************************************************************************/

///////////////////////////////////////////////////////////////////////////////
// Copyright (C) Alax.Info, 2006-2007
// http://alax.info
//
// A permission to use the source code is granted as long as reference to
// source website http://alax.info is retained.
