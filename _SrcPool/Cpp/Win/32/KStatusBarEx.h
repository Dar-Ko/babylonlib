/*$Workfile: KStatusBarEx.h$: header file
  $Revision: 3$ $Date: 2003-08-25 00:16:29$
  $Author: Darko$
  
  Interface of the CStatusBarEx class 
  Copyright: CommonSoft Inc
  Jan.96 Darko Kolakovic
 */
#ifndef _KSTATUSBAREX_H_
  //KStatusBarEx.h sentry
  #define _KSTATUSBAREX_H_

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

/////////////////////////////////////////////////////////////////////////////
//CStatusBarEx extends functionality of the MFC Status Bar class
//
//Note: uses Microsoft Fundation Library (MFC); 
//      Microsoft Windows specific (Win).
class CStatusBarEx : public CStatusBar
{
// Construction
public:
  CStatusBarEx();

// Attributes
public:
  BOOL m_bDisableSetText;  //enable/disable default OnSetText()
// Operations
public:
  static int GetTextExtent(CStatusBar* pStatusBar, const int& iPaneId,
                           const CString& strPaneText,
                           UINT& nID, UINT& nStyle);
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CStatusBarEx)
  //}}AFX_VIRTUAL

// Implementation
public:
  virtual ~CStatusBarEx();

  // Generated message map functions
protected:
  //{{AFX_MSG(CStatusBarEx)
  afx_msg LRESULT OnSetText(WPARAM, LPARAM);
    // NOTE - the ClassWizard will add and remove member functions here.
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

///////////////////////////////////////////////////////////////////////////////
#endif  //_KSTATUSBAREX_H_
/*****************************************************************************
 * $Log: 
 *  3    Biblioteka1.2         2003-08-25 00:16:29  Darko           comment
 *  2    Biblioteka1.1         2003-08-13 16:40:24  Darko           comment
 *  1    Biblioteka1.0         2003-08-13 13:35:32  Darko           
 * $
 *****************************************************************************/
