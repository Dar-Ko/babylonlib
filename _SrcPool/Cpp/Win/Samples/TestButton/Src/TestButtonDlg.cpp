/*$Workfile: TestButtonDlg.cpp$: implementation file
  $Revision: 8$ $Date: 2005-05-05 17:28:50$
  $Author: Darko Kolakovic$

  Implementation file
  Copyright: CommonSoft Inc.
  2003-08-25 Darko Kolakovic
 */


#include "stdafx.h"
#include "resource.h"
#include "TestDialogApp.h"  //CTestDialogApp class
#include "TestButtonDlg.h"  //CTestButtonDlg class
#include "TestAboutDlg.h"   //CAboutDlg class
//#include "KColorCt.h"       //color constants
#include "KProgCst.inl"     //SizeOfArray()
#include "KCheckBox.h"      //CCheckBox class
#include "KTestLog.h"       //string constants
#ifndef IDS_ABOUTBOX
  #include "Res\TestResource.h"
#endif
#ifdef _DEBUG
  #define new DEBUG_NEW
#endif

//-----------------------------------------------------------------------------
/*Constructs the resource-based dialog box.
 */
CTestButtonDlg::CTestButtonDlg(CWnd* pParent  //[in]=NULL parent or owner window
                             //object (of type CWnd) to which the dialog object
                             //belongs. If it is NULL, the dialog object's parent
                             //window is set to the main application window.
                               )
  : CDialog(CTestButtonDlg::IDD, pParent)
{
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

//-----------------------------------------------------------------------------
/*
 */
CTestButtonDlg::~CTestButtonDlg()
{
}

//-----------------------------------------------------------------------------
/*Called by the framework to exchange and validate dialog data.
  It is called by the UpdateData() member function.
 */
void CTestButtonDlg::DoDataExchange(CDataExchange* pDX //[in] pointer to
                                                      //a CDataExchange object
                                    )
{
  CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestButtonDlg, CDialog)
  ON_WM_SYSCOMMAND()
  ON_WM_PAINT()
  ON_WM_QUERYDRAGICON()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
// CTestButtonDlg message handlers

//-----------------------------------------------------------------------------
/*This method is called by the framework in response to the
  WM_INITDIALOG message. This message is sent to the dialog box during the
  Create(), CreateIndirect() or DoModal() calls, which occur immediately before
  the dialog box is displayed.

  Returns: FALSE if the input focus to a control is set by this method or TRUE
  if Windows should set the focus to the first control in the dialog box.
 */
BOOL CTestButtonDlg::OnInitDialog()
{
TRACE(_T("CTestButtonDlg::OnInitDialog()\n"));

CDialog::OnInitDialog();

// Add "About..." menu item to system menu.

// IDM_ABOUTBOX must be in the system command range.
ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
ASSERT(IDM_ABOUTBOX < 0xF000);

CMenu* pSysMenu = GetSystemMenu(FALSE);
if (pSysMenu != NULL)
  {
  CString strAboutMenu;
  strAboutMenu.LoadString(IDS_ABOUTBOX);
  if (!strAboutMenu.IsEmpty())
    {
    pSysMenu->AppendMenu(MF_SEPARATOR);
    pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
    }
  }

// Set the icon for this dialog.  The framework does this automatically
//  when the application's main window is not a dialog
SetIcon(m_hIcon, TRUE);     // Set big icon
SetIcon(m_hIcon, FALSE);    // Set small icon

  //Test reading button types and styles
extern bool TestDumpButtonStyle(HWND hButton =NULL);
bool bRes = TestDumpButtonStyle();
TRACE(_T("%s\n\n"), bRes ? LOG_SUCCESS : LOG_FAILURE);

  //Test custom button look and feel
BexGroup();
BxpGroup();

return TRUE;  // return TRUE  unless you set the focus to a control
}

//-----------------------------------------------------------------------------
/*Creates or deletes custom button controls. Call this method as a part of dialog's
  initialization and destruction.
 */
void CTestButtonDlg::BexGroup(bool bDelete //[in]=false if false buttons are attached
                              //to the new custom button controls; if true custom
                              //controls objects are deleted
                                  )
{
TRACE(_T("CTestButtonDlg::BexGroup(%s)\n"), bDelete ? _T("delete") :
                                                          _T("create"));
static UINT nBexIdArray[] =
  {
  IDC_BEX_BTN            , IDC_BEX_BTNDEFAULT     , IDC_BEX_BTNFLAT        ,
  IDC_BEX_BTNFLATDISABLED, IDC_BEX_RADIO          , IDC_BEX_CHECK          ,
  IDC_BEX_RADIOFLAT      , IDC_BEX_CHECKFLAT      , IDC_BEX_RADIOFLATPUSH  ,
  IDC_BEX_CHECKPUSH
  };

int iIndex = (int)SizeOfArray(nBexIdArray)-1;

if (bDelete)
  {
  while(iIndex >= 0)
    {
    CWnd* pBtn = GetDlgItem(nBexIdArray[iIndex]);
    if (::IsWindow(pBtn->GetSafeHwnd()) && pBtn->IsKindOf(RUNTIME_CLASS(CCheckBox)))
      delete (CCheckBox*)pBtn;
    else
      ASSERT(false);
    iIndex--;
    }
  }
else
  {
  while(iIndex >= 0)
    {
    CCheckBox* pBtn = new CCheckBox();
    pBtn->SubclassDlgItem(nBexIdArray[iIndex--], this);
    if (::IsWindow(pBtn->GetSafeHwnd()))
      {
      pBtn->m_clrBtnFace = 0xFF0000+100*iIndex;
      pBtn->m_clrBtnText = 0x10F0F0-9800*iIndex;
      }
    }
  }
}

#ifdef BTN_ST
  #include "T:\Adwel\Samples.new\BtnST.39\BtnST.h"
#endif
//-----------------------------------------------------------------------------
/*Creates or deletes custom button controls. Call this method as a part of dialog's
  initialization and destruction.
 */
void CTestButtonDlg::BxpGroup(bool bDelete //[in]=false if false buttons are attached
                              //to the new custom button controls; if true custom
                              //controls objects are deleted
                                  )
{
TRACE(_T("CTestButtonDlg::BxpGroup(%s)\n"), bDelete ? _T("delete") :
                                                     _T("create"));
#ifdef BTN_ST
  static UINT nBxpIdArray[] =
    {
    IDC_BXP_BTN            , IDC_BXP_BTNDEFAULT     , IDC_BXP_BTNFLAT        ,
    IDC_BXP_BTNFLATDISABLED, IDC_BXP_RADIO          , IDC_BXP_CHECK          ,
    IDC_BXP_RADIOFLAT      , IDC_BXP_CHECKFLAT      , IDC_BXP_RADIOFLATPUSH  ,
    IDC_BXP_CHECKPUSH
    };

  int iIndex = (int)SizeOfArray(nBxpIdArray)-1;


  if (bDelete)
    {
    while(iIndex >= 0)
      {
      CWnd* pBtn = GetDlgItem(nBxpIdArray[iIndex]);
      if (::IsWindow(pBtn->GetSafeHwnd()) && pBtn->IsKindOf(RUNTIME_CLASS(CButtonST)))
        delete (CCheckBox*)pBtn;
      else
        ASSERT(false);
      iIndex--;
      }
    }
  else
    {
    while(iIndex >= 0)
      {
      CButtonST* pBtn = new CButtonST();
      pBtn->SubclassDlgItem(nBxpIdArray[iIndex--], this);
      if (::IsWindow(pBtn->GetSafeHwnd()))
        {
        pBtn->SetTextColor( 0x10F0F0-9800*iIndex, 0xFF0000+100*iIndex );
        //pBtn->m_clrBtnFace = 0xFF0000+100*iIndex;
        //pBtn->m_clrBtnText = 0x00FBFB-10*iIndex;
        }
      }
    }
#endif
}

//-----------------------------------------------------------------------------
/*
 */
void CTestButtonDlg::OnSysCommand(UINT nID, //[in]
                                  LPARAM lParam //[in]
                                  )
{
if ((nID & 0xFFF0) == IDM_ABOUTBOX)
  {
  CAboutDlg dlgAbout;
  dlgAbout.DoModal();
  }
else
  {
  CDialog::OnSysCommand(nID, lParam);
  }
}

//-----------------------------------------------------------------------------
/*
 */
void CTestButtonDlg::OnPaint()
{
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
if (IsIconic())
  {
  CPaintDC dc(this); // device context for painting

  SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

//-----------------------------------------------------------------------------
/*The system calls this function to obtain the cursor to display while the user
  drags the minimized window.
 */
HCURSOR CTestButtonDlg::OnQueryDragIcon()
{
return static_cast<HCURSOR>(m_hIcon);
}

//-----------------------------------------------------------------------------
/*This function destroys the specified dialog box.
  The function sends a WM_DESTROY message to the dialog to deactivate it and
  removes the keyboard focus from it. It does not delete or destroy the dialog
  object itself, but Windows window attached to this object.

  Returns: TRUE to indicate success or FALSE in case of indicates failure.
  To get extended error information, call GetLastError().
 */
BOOL CTestButtonDlg::DestroyWindow()
{
BexGroup(true);
BxpGroup(true);
TRACE(LOG_EOT);
CDialog::OnClose();
return CDialog::DestroyWindow();
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  5    Biblioteka1.4         2004-10-01 22:22:44  Darko           stdafx.h
 *  4    Biblioteka1.3         2003-09-02 01:09:24  Darko           Added text
 *       colors
 *  3    Biblioteka1.2         2003-08-29 08:51:43  Darko           new test cases
 *  2    Biblioteka1.1         2003-08-27 18:12:00  Darko           renamed class
 *  1    Biblioteka1.0         2003-08-26 01:36:11  Darko
 * $
 *****************************************************************************/




