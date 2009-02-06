/*$RCSfile: ATL70SafeWinImpl.h,v $: header file
  $Revision: 1.5 $ $Date: 2009/02/06 17:19:54 $
  $Author: ddarko $

  Fix: ATL's CWindowImpl crashes when OnFinalMessage contains code to destroy
  the class instance.

  http://vcfaq.mvps.org/com/10.htm
  May 04, 2003 Alexander Nickolov (agnickolov@mvps.org)
 */

#if !defined(_ATL_VER)
  #error ERROR: This header requires ATL!
#endif


#ifndef _KSAFEWINIMPL_H_
  //$RCSfile: ATL70SafeWinImpl.h,v $ sentry
  #define _KSAFEWINIMPL_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

// Group=Windows

/////////////////////////////////////////////////////////////////////////////
/*This class allows you to create a new window or to make an existing windows
  into a subclass.The window procedure uses a message map to direct messages
  to the appropriate handlers.

  FIX: The class is to be used in place of CWindowImpl. It adds 4 bytes overhead
  to the window class instance data, otherwise it's completely equivalent to
  ATL CWindowImpl.
  You can simply include this header it in stdsfx.h after atlwin.h and replace
  all instances of CWindowImpl with CWindowImplSafe.
  In ATL 3 fixes crashes when OnFinalMessage destroys the class instance.
  In ATL 7 this class fixes the other bug - invalid m_hWnd after DestroyWindow.

  ATL's main support class for implementing general-purpose windows is CWindowImpl.
  It has a feature that allows the class instance to be dynamically allocated
  and automatically manage its lifetime. All the derived class has to do is
  implement a method named OnFinalMessage:

    //Typical OnFinalMessage implementation
    virtual void OnFinalMessage(HWND hWnd)
      {
      _UNUSED(hWnd);
      delete this;
      }
  This method is called when the window is destroyed - when processing the last
  message sent to any window - WM_NCDESTROY. This happens within DestroyWindow.
  The problem arises when you call DestroyWindow from within a message handler
   within the same class:

    LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
      {
      //...
      DestroyWindow();
      }
  What happens is your OnFinalMessage is called from within DestroyWindow when
  the windowproc processes WM_NCDESTROY. At that moment your code destroys
  the class instance, so when DestroyWindow returns, you have no instance anymore.
  The next thing after you return from your message handler is the windowproc
  performs some housekeeping and while accessing the class' <this> pointer, causing
  an catastrophic failure.
  The above sequence of events holds true for ATL 3.0 and has been fixed in
  ATL 7.0. So if you have upgraded to VC 7.0, or even better to VC 7.1, you
  don't get the crash. The fix has introduced another subtler bug though.
  The original code in ATL 3.0 cleared the class' m_hWnd member immediately before
  firing up OnFinalMessage when handling WM_NCDESTROY. And that is the correct
  behavior - m_hWnd is NULL after DestroyWindow returns.
  The fix in ATL 7 doesn't do that though, so you have an invalid HWND stored in
  m_hWnd. This wouldn't be a big problem if all programmers always checked if
  the window is valid via IsWindow(). Unfortunately, it's a mass practice to
  write that test as m_hWnd == NULL.

  Parameters:
  T        Your class, derived from CWindowImplSafe.
  Base     The base class of your new class. The default base class is CWindow.
  Traits   A traits class that defines styles for your window. The default is
           CControlWinTraits.

  Note: Microsoft Windows specific (Win32)
        and uses Active Template Library (ATL).

  See also: CWindowImpl template, CWindow, CWindowImplBaseT methods
 */
template<typename T, typename Base = CWindow, typename Traits = CControlWinTraits>
class CWindowImplSafe :
  public CWindowImpl<T, Base, Traits>
{
public:
  CWindowImplSafe() :
    m_hwndSave(NULL)
  {
  }

public:
  /*Returns WindowProc, the current window procedure. Override this method to
    replace the window procedure with your own.
   */
  virtual WNDPROC GetWindowProc()
    {
    return WindowProcSafe;
    }
  static LRESULT CALLBACK WindowProcSafe(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Implementation helpers
protected:
  HWND m_hwndSave;
};

#if (_ATL_VER >= 0x0700) /*Active Template Library version 7.0*/
//------------------------------------------------------------------------------
/*This static function implements the window procedure.
  Method uses the default message map (declared with BEGIN_MSG_MAP) to direct
  messages to the appropriate handlers. If necessary, method calls
  DefWindowProc for additional message processing. If the final message is not
  handled, procedure does the following:
  - Performs unsubclassing if the window was unsubclassed.
  - Clears m_hWnd.
  - Calls OnFinalMessage before the window is destroyed.
  You can override this method to provide a different mechanism for handling
  messages.

  Returns: result of the message processing.

  See also: CWindowImpl::WindowProc()
 */
template <typename T, typename Base, typename Traits>
LRESULT CALLBACK CWindowImplSafe<T, Base, Traits>::WindowProcSafe(
                             HWND hWnd,     //[in] handle to the window
                             UINT uMsg,     //[in] message sent to the window
                             WPARAM wParam, //[in] additional message-specific information
                             LPARAM lParam  //[in] additional message-specific information
                                                                  )
{
  CWindowImplSafe<T, Base, Traits>* pThis = (CWindowImplSafe<T, Base, Traits>*)hWnd;
  //Set a ptr to this message and save the old value
  _ATL_MSG msg(pThis->m_hWnd, uMsg, wParam, lParam);
  const _ATL_MSG* pOldMsg = pThis->m_pCurrentMsg;
  pThis->m_pCurrentMsg = &msg;
  // pass to the message map to process
  LRESULT lRes;
  BOOL bRet = pThis->ProcessWindowMessage(pThis->m_hWnd, uMsg, wParam, lParam, lRes, 0);
  //Restore saved value for the current message
  ATLASSERT(pThis->m_pCurrentMsg == &msg);
  pThis->m_pCurrentMsg = pOldMsg;
  //Do the default processing if message was not handled
  if(!bRet)
    {
    if(uMsg != WM_NCDESTROY)
      lRes = pThis->DefWindowProc(uMsg, wParam, lParam);
    else
      {
      //Unsubclass, if needed
      LONG_PTR pfnWndProc = ::GetWindowLongPtr(pThis->m_hWnd, GWLP_WNDPROC);
      lRes = pThis->DefWindowProc(uMsg, wParam, lParam);
      if(pThis->m_pfnSuperWindowProc != ::DefWindowProc &&
         ::GetWindowLongPtr(pThis->m_hWnd, GWLP_WNDPROC) == pfnWndProc)
        ::SetWindowLongPtr(pThis->m_hWnd, GWLP_WNDPROC, (LONG_PTR)pThis->m_pfnSuperWindowProc);
      //Mark window as destroyed
      pThis->m_dwState |= WINSTATE_DESTROYED;
      pThis->m_hwndSave = pThis->m_hWnd;
      pThis->m_hWnd     = NULL;
      }
    }
  if((pThis->m_dwState & WINSTATE_DESTROYED) && (pThis->m_pCurrentMsg == NULL))
    {
    //Clear out the saved handle
    HWND hWnd = pThis->m_hwndSave;
    pThis->m_hwndSave = NULL;
    pThis->m_dwState &= ~WINSTATE_DESTROYED;
    //Clean up after window is destroyed
    pThis->OnFinalMessage(hWnd);
    }
  return lRes;
}

#else /*Active Template Library version 3.0*/

//------------------------------------------------------------------------------
/*This static function implements the window procedure.
  Method uses the default message map (declared with BEGIN_MSG_MAP) to direct
  messages to the appropriate handlers. If necessary, method calls
  DefWindowProc for additional message processing. If the final message is not
  handled, procedure does the following:
  - Performs unsubclassing if the window was unsubclassed.
  - Clears m_hWnd.
  - Calls OnFinalMessage before the window is destroyed.
  You can override this method to provide a different mechanism for handling
  messages.

  Returns: result of the message processing.

  See also: CWindowImpl::WindowProc()
 */
template <typename T, typename Base, typename Traits>
LRESULT CALLBACK CWindowImplSafe<T, Base, Traits>::WindowProcSafe(
                             HWND hWnd,     //[in] handle to the window
                             UINT uMsg,     //[in] message sent to the window
                             WPARAM wParam, //[in] additional message-specific information
                             LPARAM lParam  //[in] additional message-specific information
                                                                  )
{
CWindowImplSafe<T, Base, Traits>* pThis = (CWindowImplSafe<T, Base, Traits>*)hWnd;
//Set a ptr to this message and save the old value
MSG msg = { pThis->m_hWnd, uMsg, wParam, lParam, 0, { 0, 0 } };
const MSG* pOldMsg = pThis->m_pCurrentMsg;
pThis->m_pCurrentMsg = &msg;
//Pass to the message map to process
LRESULT lRes;
BOOL bRet = pThis->ProcessWindowMessage(pThis->m_hWnd, uMsg, wParam, lParam, lRes, 0);
//Restore saved value for the current message
ATLASSERT(pThis->m_pCurrentMsg == &msg);
pThis->m_pCurrentMsg = pOldMsg;
//Do the default processing if message was not handled
if(!bRet)
  {
  if(uMsg != WM_NCDESTROY)
    lRes = pThis->DefWindowProc(uMsg, wParam, lParam);
  else
    {
    //Unsubclass, if needed
    LONG pfnWndProc = ::GetWindowLong(pThis->m_hWnd, GWL_WNDPROC);
    lRes = pThis->DefWindowProc(uMsg, wParam, lParam);
    if(pThis->m_pfnSuperWindowProc != ::DefWindowProc &&
       ::GetWindowLong(pThis->m_hWnd, GWL_WNDPROC) == pfnWndProc)
      ::SetWindowLong(pThis->m_hWnd, GWL_WNDPROC, (LONG)pThis->m_pfnSuperWindowProc);
    //Clear out window handle
    pThis->m_hwndSave = pThis->m_hWnd;
    pThis->m_hWnd     = NULL;
    }
  }
if ((pThis->m_hwndSave != NULL) && (pThis->m_pCurrentMsg == NULL))
  {
  //Clear out the saved handle
  HWND hWnd = pThis->m_hwndSave;
  pThis->m_hwndSave = NULL;
  //Clean up after window is destroyed
  pThis->OnFinalMessage(hWnd);
  }
return lRes;
}

#endif

///////////////////////////////////////////////////////////////////////////////
#endif /* !_KSAFEWINIMPL_H_ */
/*****************************************************************************
 * $Log: ATL70SafeWinImpl.h,v $
 * Revision 1.5  2009/02/06 17:19:54  ddarko
 * *** empty log message ***
 *
 * Revision 1.4  2008/07/17 21:38:22  ddarko
 * MSVC6.0 build
 *
 * Revision 1.3  2008/07/15 20:57:09  ddarko
 * *** empty log message ***
 *
 * Revision 1.2  2008/07/09 14:19:56  ddarko
 * Comments
 *
 * Revision 1.1  2008/07/07 21:37:41  ddarko
 * Bug fix: ATL3.0 /ATL 7.0
 *
 * Revision 1.1.2.1  2008/07/07 21:35:39  dkolakovic
 * bug fix
 *
 *****************************************************************************/
