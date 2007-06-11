/*$Workfile: TestCommonComplex.cpp$: implementation file
  $Revision: 3$ $Date: 2007-06-08 17:56:09$
  $Author: Darko Kolakovic$

  Defines the class behaviors for the application.

  Copyright: CommonSoft Inc.
  Jan. 2k Darko Kolakovic
*/

// Group=Examples

#pragma comment(exestr, "CommonSoft Inc, D.K. 10.01.2k, Bgd")

#include "stdafx.h"
#include "TsMfcRes.h"    //IDD_ABOUTBOX
#include "TsMfcAbout.h"  //CTestAboutDlg class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

CTestAboutDlg::CTestAboutDlg() : CDialog(CTestAboutDlg::IDD)
{
  //{{AFX_DATA_INIT(CTestAboutDlg)
  //}}AFX_DATA_INIT
}

void CTestAboutDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CTestAboutDlg)
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestAboutDlg, CDialog)
  //{{AFX_MSG_MAP(CTestAboutDlg)
    // No message handlers
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()
