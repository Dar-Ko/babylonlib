/*$Workfile: TestUrlDlg.cpp$: implementation file
  $Revision: 3$ $Date: 2005-05-03 01:44:11$
  $Author: Darko$

  Implementation file
  Copyright: CommonSoft Inc.
  2001-07-07 Darko Kolakovic
 */

#include "stdafx.h"
#include "Resource.h"
#include "TestUrlDlg.h" //CHTTPUtilsDlg class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHTTPUtilsDlg dialog

CHTTPUtilsDlg::CHTTPUtilsDlg(CWnd* pParent /*=NULL*/)
  : CDialog(CHTTPUtilsDlg::IDD, pParent)
{
  //{{AFX_DATA_INIT(CHTTPUtilsDlg)
  //}}AFX_DATA_INIT
  // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHTTPUtilsDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CHTTPUtilsDlg)
  DDX_Control(pDX, IDC_DISPLAY, m_staticDisplay);
  DDX_Control(pDX, IDC_HYPERLINK, m_chlURL);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHTTPUtilsDlg, CDialog)
  //{{AFX_MSG_MAP(CHTTPUtilsDlg)
  ON_WM_PAINT()
  ON_WM_QUERYDRAGICON()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHTTPUtilsDlg message handlers

BOOL CHTTPUtilsDlg::OnInitDialog()
{
CDialog::OnInitDialog();

// Set the icon for this dialog.  The framework does this automatically
//  when the application's main window is not a dialog
SetIcon(m_hIcon, TRUE);     // Set big icon
SetIcon(m_hIcon, FALSE);    // Set small icon

CString strURL = _T("http://www.Yahoo.com");
m_chlURL. SetUrl(strURL); //Set URL link


return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHTTPUtilsDlg::OnPaint()
{
if (IsIconic())
  {
  CPaintDC dc(this); // device context for painting

  SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

  // Center icon in client rectangle
  int cxIcon = GetSystemMetrics(SM_CXICON);
  int cyIcon = GetSystemMetrics(SM_CYICON);
  CRect rect;
  GetClientRect(&rect);
  int x = (rect.Width() - cxIcon + 1) / 2;
  int y = (rect.Height() - cyIcon + 1) / 2;

  // Draw the icon
  dc.DrawIcon(x, y, m_hIcon);
  }
else
  {
  CDialog::OnPaint();
  }
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHTTPUtilsDlg::OnQueryDragIcon()
{
  return (HCURSOR) m_hIcon;
}

//::OnOK()---------------------------------------------------------------------
/*Handles clicking on IDOK button. Validates RAS connection and display static
  text.
 */
void CHTTPUtilsDlg::OnOK()
{
extern BOOL IsRASConnected();
if (IsRASConnected())
  m_staticDisplay.SetWindowText(_T("RAS Connected"));
else
  m_staticDisplay.SetWindowText(_T("RAS is not connected"));
}


///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  3    Biblioteka1.2         2005-05-03 01:44:11  Darko            
 *  2    Biblioteka1.1         2005-05-03 01:08:17  Darko           
 *  1    Biblioteka1.0         2001-07-07 01:20:30  Darko           
 * $
 *****************************************************************************/
