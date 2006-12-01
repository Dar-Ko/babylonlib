/*$Workfile: MFC40Hlp.inl$: header file
  $Revision: 2$ $Date: 2005-04-26 11:36:11$
  $Author: Darko Kolakovic$

  Fix: WinHelp Called Twice
  Copyright: CommonSoft Inc
  Oct 98  Darko Kolakovic
 */
// Group=Windows

#if (_MFC_VER <  0x0600)
#if (_MFC_VER >= 0x0400)
#ifndef _MFC40HLP_INL_
  //$Workfile: MFC40Hlp.inl$ sentry
  #define _MFC40HLP_INL_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif


//MFC40IsHelpKey()-------------------------------------------------------------
/*FIX: WinHelp Called Twice. Removes the accelerator table entry for F1.
  CWnd in MFC 4.0,5.0 has a handler for WM_HELP that sends a WM_COMMAND with an
  ID of ID_HELP. The AppWizard-generated application also has an accelerator
  for the F1 key. Both result in WinHelp being called.

  Example:
     BOOL CMyApp::PreTranslateMessage(MSG* pMsg)
      {
        //If on a system (NT4.0,95) that supports WM_HELP, cancel routing of F1 key.
      DWORD dwVersion = ::GetVersion();
      UINT nWinVer = (LOBYTE(dwVersion) << 8) + HIBYTE(dwVersion);
      if (nWinVer >= 0x333 && MFC40IsHelpKey(pMsg))
        return TRUE;
      return CWinApp::PreTranslateMessage(pMsg);
      }

  Note: Microsoft Windows specific (Win32)
        and uses Microsoft Foundation Library (MFC).

  See also: article Q139696.
 */
inline BOOL AFXAPI MFC40IsHelpKey(LPMSG lpMsg)

          // Return TRUE only for non-repeat F1 keydowns.
{
return lpMsg->message == WM_KEYDOWN &&
#ifndef _MAC
             lpMsg->wParam == VK_F1 &&
#else
           lpMsg->wParam == VK_HELP &&
#endif
  !(HIWORD(lpMsg->lParam) & KF_REPEAT) &&
            GetKeyState(VK_SHIFT) >= 0 &&
          GetKeyState(VK_CONTROL) >= 0 &&
                 GetKeyState(VK_MENU) >= 0;
}

///////////////////////////////////////////////////////////////////////////////
#endif  //_MFC40HLP_INL_

///////////////////////////////////////////////////////////////////////////////
#endif //(_MFC_VER >= 0x0400)
#endif //(_MFC_VER < 0x0600)
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2005-03-23 03:23:41  Darko
 * $
 *****************************************************************************/
