/*$Workfile: KPropPgR.h$: header file
  $Revision: 1.3 $ $Date: 2003/01/28 05:37:44 $
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
 *  6    Biblioteka1.5         29/01/2002 10:21:36 PMDarko           Used lbraries
 *       notes 
 *  5    Biblioteka1.4         24/01/2002 6:18:57 PMDarko           Updated
 *       comments
 *  4    Biblioteka1.3         19/08/2001 10:54:33 PMDarko           Butyfier
 *  3    Biblioteka1.2         11/07/2001 9:52:13 PMDarko           
 *  2    Biblioteka1.1         08/06/2001 10:51:23 PMDarko           VSS
 *  1    Biblioteka1.0         13/08/2000 2:57:04 PMDarko           
 * $
 *****************************************************************************/
