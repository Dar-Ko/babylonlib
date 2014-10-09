/*$RCSfile: KAbout.h$: header file
  $Revision: 7$ $Date: 2005-04-26 11:28:08$
  $Author: Darko Kolakovic$

  Interface of the CAboutDlg class
  Copyright: CommonSoft Inc
  Jan.96 Darko Kolakovic
 */
// Group=Windows

#ifndef __KABOUT_H__
  //$Workfile: KAbout.h$ sentry
  #define __KABOUT_H__

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#include "KHypLink.h" //CHyperLink class

///////////////////////////////////////////////////////////////////////////////
//Displays the version number the copyright notice of this application.
//
//Example:
//      #include "KAbout.h"  //CAboutDlg dialogue
//      /*Handles ID_APP_ABOUT command displaying the dialog
//       */
//      void CMyApp::OnAppAbout()
//      {
//      TRACE0("CMyApp::OnAppAbout()\n");
//      CAboutDlg aboutDlg;
//      if(-1 == aboutDlg.DoModal())
//        {
//        extern void SystemErrMessage(UINT uiSystemError);
//        TRACE("CAboutDlg::DoModal() returned error #h%x.\n", GetLastError());
//        #ifndef IDD_ABOUTBOX
//          #pragma message ("IDD_ABOUTBOX is not defined")
//        #else
//          TRACE("IDD_ABOUTBOX = %d.\n", IDD_ABOUTBOX);
//        #endif
//        SystemErrMessage(GetLastError());
//        }
//      }
//
//Note: uses Microsoft Foundation Library (MFC);
//      Microsoft Windows specific (Win).
class CAboutDlg : public CDialog
{
public:
  CAboutDlg(LPCTSTR lpszAppPath = NULL);
  virtual ~CAboutDlg();
  void SetUrl(LPCTSTR szUrl);
  void SetUrl(CString& strUrl);

protected:
  LPCTSTR m_lpszFilePath; //The path of module containing the version information
  // Dialog Data
  //{{AFX_DATA(CAboutDlg)
  CHyperLink  m_Copyright;
  //}}AFX_DATA

  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CAboutDlg)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:
  virtual BOOL OnInitDialog();
  //{{AFX_MSG(CAboutDlg)
  afx_msg void OnPaint();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

///////////////////////////////////////////////////////////////////////////////
#endif  //__KABOUT_H__
/*****************************************************************************
 * $Log:
 *  5    Biblioteka1.4         03/11/2003 1:15:00 PMDarko           Added SetUrl()
 *  4    Biblioteka1.3         13/08/2003 5:38:45 PMDarko           formatting
 *  3    Biblioteka1.2         06/08/2003 10:47:44 PMDarko           Modified
 *       dialog's resource ID
 *  2    Biblioteka1.1         06/08/2003 3:46:35 AMDarko           Prepared for
 *       Unicode
 *  1    Biblioteka1.0         05/08/2003 11:17:32 PMDarko
 * $
 *****************************************************************************/
