/*$RCSfile: KNotifyBox.h,v $: header file
  $Revision: 1.1 $ $Date: 2011/10/03 20:34:17 $
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

///////////////////////////////////////////////////////////////////////////////
/*CStaticEx class displays a text label.
  A static control normally takes no input and provides no output.
  Base class also displays box, rectangle, icon, cursor, bitmap or enhanced
  metafile.

  Note: uses Microsoft Foundation Library (MFC);
        Microsoft Windows specific (Win).

  See also: MessageBox
 */
class CNotifyBox : public CDialog
{
  DECLARE_DYNAMIC(CNotifyBox)

public:
  CNotifyBox(UINT nIDTemplate, CWnd* pParent = NULL);   // standard constructor
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
///////////////////////////////////////////////////////////////////////////////
#endif  //_KNOTIFYBOX_H_
/*****************************************************************************
 * $Log: KNotifyBox.h,v $
 * Revision 1.1  2011/10/03 20:34:17  ddarko
 * Created
 *
 *****************************************************************************/

