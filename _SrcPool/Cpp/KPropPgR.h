/*$Workfile: KPropPgR.h$: header file
  $Revision: 1.2 $ $Date: 2002/09/10 15:22:21 $
  $Author: ddarko $

  Handles resizing of the property page
  Copyright: CommonSoft Inc
  Mar. 2k Darko Kolakovic
 */

#ifndef _KPROPPGR_H_
    //KPropPgR.h sentry
  #define _KPROPPGR_H_

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXDLGS_H__
  #include <AfxDlgs.h>   //CPropertyPage class
#endif

#include "KDlgItLs.h" //CDlgItemResizableList class

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageResizable dialog class handles the resizing of
// the property page and embedded controls.
//
// Note:  Microsoft Windows specific (Win) and uses Microsoft Fundation Library (MFC).
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
 *  6    Biblioteka1.5         1/29/02 11:21:36 PM  Darko           Used lbraries
 *       notes 
 *  5    Biblioteka1.4         1/24/02 7:18:57 PM   Darko           Updated
 *       comments
 *  4    Biblioteka1.3         8/19/01 11:54:33 PM  Darko           Butyfier
 *  3    Biblioteka1.2         7/11/01 10:52:13 PM  Darko           
 *  2    Biblioteka1.1         6/8/01 11:51:23 PM   Darko           VSS
 *  1    Biblioteka1.0         8/13/00 3:57:04 PM   Darko           
 * $
 *****************************************************************************/
