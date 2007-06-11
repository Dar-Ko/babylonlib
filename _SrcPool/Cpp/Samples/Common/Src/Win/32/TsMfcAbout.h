/*$Workfile: TestComplex.h$: header file
  $Revision: 6$ $Date: 2007-06-08 17:56:11$
  $Author: Darko Kolakovic$

  Interface of the document's view

  Darko Kolakovic Jan. 2k Compiled with MSVC++ 4.0
*/

// Group=Examples

#ifndef _TSMFCABOUT_H_
  //$Workfile: TestComplex.h$ sentry
  #define _TSMFCABOUT_H_

/////////////////////////////////////////////////////////////////////////////
/*CTestAboutDlg dialog used for application's About Help.

  Note: Microsoft Windows specific (Win32) 
        and uses Microsoft Foundation Library (MFC).
 */
class CTestAboutDlg : public CDialog
{
public:
  CTestAboutDlg();

// Dialog Data
  //{{AFX_DATA(CTestAboutDlg)
  enum { IDD = IDD_ABOUTBOX };
  //}}AFX_DATA

  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CTestAboutDlg)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:
  //{{AFX_MSG(CTestAboutDlg)
    // No message handlers
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

#endif //_TSMFCABOUT_H_
////////////////////////////////////////////////////////////////////////////////
/*
  $Log: $
 */

