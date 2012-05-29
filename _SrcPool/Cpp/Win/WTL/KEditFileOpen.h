/*$RCSfile: KEditFileOpen.h,v $: header file
  $Revision: 1.1 $ $Date: 2012/05/29 20:41:01 $
  $Author: ddarko $

  Interface of the CEditFileOpen class
  Copyright: CommonSoft Inc., 2002
 */
// Group=Windows

#ifndef _KEDITFILEOPEN_H_
  //$RCSfile: KEditFileOpen.h,v $ sentry
  #define _KEDITFILEOPEN_H_

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#include "atlctrls.h" //CEditT

///////////////////////////////////////////////////////////////////////////////
//CEditFileOpen extends functionality of the MFC Button class.
//
//Note: uses Active Template Library (ATL);
//      Microsoft Windows specific (Win).
class CEditFileOpen : public CWindowImpl<CEditFileOpen, CEdit>
{
  //Construction
public:
  CEditFileOpen();
  virtual ~CEditFileOpen();

  //Attributes
protected:
//  CButton m_wndInButton;
//  RECT m_rcButton;
//  BOOL m_bHideButton;
//  UINT m_nButtonWidht;

  class CButtonBuddy : public CWindowImpl<CButtonBuddy, CButton>
  {
    //Construction
  public:
    CButtonBuddy();

    //Generated message map functions
  public:
    BEGIN_MSG_MAP(CButtonBuddy)
    END_MSG_MAP()
  } m_btnBuddy;

  //Operations
public:
  BOOL SubclassWindow(HWND hWnd);
  HWND UnsubclassWindow(BOOL bForce = FALSE);

  //Implementation
public:


  //Overrides
protected:

  //Generated message map functions
protected:
  BEGIN_MSG_MAP(CEditFileOpen)
    //MESSAGE_HANDLER(WM_NCHITTEST, OnNcHitTest)
    //MESSAGE_HANDLER(WM_SIZE, OnSize)
    //MESSAGE_HANDLER(EM_SETMARGINS, OnSetMargins)
    //MESSAGE_HANDLER(EM_SETRECT, OnSetRect)
    //MESSAGE_HANDLER(EM_SETRECTNP, OnSetRectNP)
    //COMMAND_CODE_HANDLER(BN_CLICKED, OnButtonNotifyClicked)

//    MESSAGE_HANDLER(WM_PAINT, OnPaint)
    //MESSAGE_HANDLER(WM_TIMER, OnTimer)
//    MESSAGE_HANDLER(WM_SYSCOLORCHANGE, OnSysColorChange)
    //MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
    //MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
  END_MSG_MAP()
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*
 */
inline CEditFileOpen::CButtonBuddy::CButtonBuddy()
{
ATLTRACE(L"CEditFileOpen::CButtonBuddy::CButtonBuddy()\n");

}

///////////////////////////////////////////////////////////////////////////////
#endif  //_KEDITFILEOPEN_H_
/*****************************************************************************
 * $Log: KEditFileOpen.h,v $
 * Revision 1.1  2012/05/29 20:41:01  ddarko
 * Copied from old repository
 *
 *****************************************************************************/
