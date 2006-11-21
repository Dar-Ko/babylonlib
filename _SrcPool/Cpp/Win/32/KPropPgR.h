/*$Workfile: KPropPgR.h$: header file
  $Revision: 7$ $Date: 2005-05-24 16:23:09$
  $Author: Darko Kolakovic$

  Handles resizing of the property page
  Copyright: CommonSoft Inc
  Mar. 2k Darko Kolakovic
 */

// Group=Windows

#ifndef _KPROPPGR_H_
    //$Workfile: KPropPgR.h$ sentry
  #define _KPROPPGR_H_

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXDLGS_H__
  #include <afxdlgs.h>   //CPropertyPage class
#endif

#include "KDlgItLs.h" //CDlgItemResizableList class

/////////////////////////////////////////////////////////////////////////////
/*CPropertyPageResizable dialog class handles the resizing of
  the property page and embedded controls.

  Note: Microsoft Windows specific (Win) and
        uses Microsoft Fundation Library (MFC).
 */
class CPropertyPageResizable : public CPropertyPage
{
// Construction
  DECLARE_DYNAMIC(CPropertyPageResizable)
public:
  CPropertyPageResizable();
  CPropertyPageResizable(UINT nIDTemplate, UINT nIDCaption = 0);
  CPropertyPageResizable(LPCTSTR lpszTemplateName, UINT nIDCaption = 0);

// Attributes
protected:
  CDlgItemResizableList m_arrControlList; //a list of the embedded controls

// Overrides
  // ClassWizard generate virtual function overrides
  //{{AFX_VIRTUAL(CPropertyPageResizable)
  public:
  virtual BOOL OnSetActive();
  //}}AFX_VIRTUAL

// Implementation
public:
  virtual ~CPropertyPageResizable();


  // Generated message map functions
  //{{AFX_MSG(CPropertyPageResizable)
  virtual BOOL OnInitDialog();
  afx_msg void OnSize(UINT nType, int cx, int cy);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

};

///////////////////////////////////////////////////////////////////////////////
// Helpers

extern BOOL IsWizard(const CPropertySheet& cpSheet);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

///////////////////////////////////////////////////////////////////////////////
#endif // _KPROPPGR_H_
/*****************************************************************************
 * $Log:
 *  6    Biblioteka1.5         2002-01-29 23:21:36  Darko           Used lbraries
 *       notes
 *  5    Biblioteka1.4         2002-01-24 19:18:57  Darko           Updated
 *       comments
 *  4    Biblioteka1.3         2001-08-19 23:54:33  Darko           Butyfier
 *  3    Biblioteka1.2         2001-07-11 22:52:13  Darko
 *  2    Biblioteka1.1         2001-06-08 23:51:23  Darko           VSS
 *  1    Biblioteka1.0         2000-08-13 15:57:04  Darko
 * $
 *****************************************************************************/
