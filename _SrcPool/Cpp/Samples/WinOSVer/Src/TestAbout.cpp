// TestAbout.cpp : implementation of the CAboutDlg class
//
// Darko Kolakovic
// Jan. 2k

#pragma comment(exestr, "CommonSoft Inc, D.K. 10.01.2k,Bgd)

#include "stdafx.h"
#include "Resource.h"   //IDD_ABOUTBOX
#include "TestAbout.h"  //CAboutDlg class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
  //{{AFX_DATA_INIT(CAboutDlg)
  //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CAboutDlg)
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
  //{{AFX_MSG_MAP(CAboutDlg)
    // No message handlers
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()
