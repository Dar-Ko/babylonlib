/*$RCSfile: KNotifyBox.h,v $: header file
  $Revision: 1.2 $ $Date: 2011/12/22 16:15:25 $
  $Author: ddarko $

  Display modeless message box
  Copyright: artistic license
  2000-05-05 Darko Kolakovic
 */
/* Group=Windows*/

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
  #pragma once
#endif

#ifndef _KNOTIFYBOX_H_
    //$RCSfile: KNotifyBox.h,v $ sentry
  #define _KNOTIFYBOX_H_

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

#if _MFCVER >= 0x800
  #ifdef _USE_MSFLUENUI_
    /*Note: The MFC C++ library source code for the Microsoft Office Fluent User
      Interface (the Fluent UI) is provided only as referential material to 
      supplement the Microsoft Foundation Classes Reference and related
      electronic documentation provided with the MFC C++ library software.
      License terms to copy, use or distribute the Microsoft Fluent UI are
      available separately.
     */
    #include "afxDesktopAlertWnd.h" //CMFCDesktopAlertWnd class
    ///////////////////////////////////////////////////////////////////////////
    /*The class implements the functionality of a modeless dialog box which
      appears on the screen to inform the user about an event.

      Note: uses Microsoft Foundation Library (MFC);
            Microsoft Windows specific (Win).

      See also: MessageBox, CMFCDesktopAlertWnd
      Reference: Microsoft Fluent UI
     */
    class CNotifyBox : public CMFCDesktopAlertWnd
      {
      public:
        CNotifyBox(UINT nIDTemplate, CWnd* pParent = NULL);
        virtual ~CNotifyBox();

      }
  #endif //_USE_MSFLUENUI_
#else
  #undef _USE_MSFLUENUI_

///////////////////////////////////////////////////////////////////////////////
/*The class implements the functionality of a modeless dialog box which
  appears on the screen to inform the user about an event.

  Note: uses Microsoft Foundation Library (MFC);
        Microsoft Windows specific (Win).

  See also: MessageBox, CMFCDesktopAlertWnd
  Reference: Microsoft Fluent UI
 */
class CNotifyBox : public CDialog
{
  DECLARE_DYNAMIC(CNotifyBox)

public:
  CNotifyBox(UINT nIDTemplate, CWnd* pParent = NULL);
  virtual ~CNotifyBox();

public:
  CWnd* m_pwndParent;  //owner window
  CString m_strText;   //message text

protected:
  DECLARE_MESSAGE_MAP()
  
public:
  afx_msg void OnBnClickedOk();
  afx_msg void OnBnClickedCancel();
protected:
  virtual void PostNcDestroy();
};
#endif
///////////////////////////////////////////////////////////////////////////////
#endif  //_KNOTIFYBOX_H_
/*****************************************************************************
 * $Log: KNotifyBox.h,v $
 * Revision 1.2  2011/12/22 16:15:25  ddarko
 * Microsoft Fluent UI implementation
 *
 * Revision 1.1  2011/10/03 20:34:17  ddarko
 * Created
 *
 *****************************************************************************/
