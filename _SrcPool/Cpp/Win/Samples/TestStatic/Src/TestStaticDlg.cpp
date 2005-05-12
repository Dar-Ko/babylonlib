/*$Workfile: TestStaticDlg.cpp$: implementation file
  $Revision: 4$ $Date: 2005-05-05 22:57:46$
  $Author: Darko$

  Implementation file
  Copyright: CommonSoft Inc.
  2002-01-16 Darko Kolakovic
 */


#define _DEBUG_INCL_PREPROCESS

#include "stdafx.h"
#include "Resource.h"

#include "TestDialogApp.h"  //CTestDialogApp class
#include "TestStaticDlg.h"  //CTestStaticDlg class
#include "Res/TestResource.h"
#include "TestAboutDlg.h"   //CAboutDlg class
#include "KProgCst.inl"     //SizeOfArray()
#include "KStaticEx.h"      //CStaticEx class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestStaticDlg dialog

IMPLEMENT_DYNAMIC( CTestStaticDlg, CDialog );

//-----------------------------------------------------------------------------
/*
 */
CTestStaticDlg::CTestStaticDlg(CWnd* pParent /*=NULL*/)
  : CDialog(CTestStaticDlg::IDD, pParent)
{
  //{{AFX_DATA_INIT(CTestStaticDlg)
    // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
  // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

//-----------------------------------------------------------------------------
/*
 */
void CTestStaticDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CTestStaticDlg)
    // NOTE: the ClassWizard will add DDX and DDV calls here
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestStaticDlg, CDialog)
  //{{AFX_MSG_MAP(CTestStaticDlg)
  ON_WM_SYSCOMMAND()
  ON_WM_DESTROY()
  ON_WM_PAINT()
  ON_WM_QUERYDRAGICON()
  ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipNotify)
  ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipNotify)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
/*Creates or deletes extended controls. Call this method as a part of dialog's
  initialization and destruction.
 */
void CTestStaticDlg::BexGroup(bool bDelete //[in]=false if false controls are
                              //attached to the new custom controls; if true 
                              //custom controls objects are deleted
                             )
{
TRACE(_T("CTestStaticDlg::BexGroup(%s)\n"), bDelete ? _T("delete") :
                                                      _T("create"));
static UINT nBexIdArray[] =
  {
  IDC_STATIC_TITLE , IDC_STATIC_LEFT        , IDC_STATIC_RIGHT    ,
  IDC_STATIC_CENTER, IDC_STATIC_RIGHT2LEFT  , IDC_STATIC_DISABLED 
  };

int iIndex = (int)SizeOfArray(nBexIdArray)-1;

if (bDelete) //Delete controls from the memory
  {
  while(iIndex >= 0)
    {
    CWnd* pBtn = GetDlgItem(nBexIdArray[iIndex]);
    if (::IsWindow(pBtn->GetSafeHwnd()) && pBtn->IsKindOf(RUNTIME_CLASS(CStaticEx)))
      delete (CStaticEx*)pBtn;
    else
      ASSERT(false);
    iIndex--;
    }
  }
else //Create new controls
  {
  while(iIndex >= 0)
    {
    CStaticEx* pBtn = new CStaticEx();
    pBtn->SubclassDlgItem(nBexIdArray[iIndex--], this);
    if (::IsWindow(pBtn->GetSafeHwnd()))
      {
      pBtn->SetTextColor(0x225252-9800*iIndex, 0xFFB0C0+64*iIndex);
      }
    }
  }
}

//-----------------------------------------------------------------------------
/*Creates or deletes custom controls. Call this method as a part of dialog's
  initialization and destruction.
 */
void CTestStaticDlg::BxpGroup(bool bDelete //[in]=false if false controls are
                              //attached to the new custom controls; if true 
                              //custom controls objects are deleted
                              )
{
TRACE(_T("CTestStaticDlg::BxpGroup(%s)\n"), bDelete ? _T("delete") :
                                                      _T("create"));
static UINT nBxpIdArray[] =
  {
  IDC_STATIC_WIN32_TITLE , IDC_STATIC_WIN32_LEFT        , IDC_STATIC_WIN32_RIGHT    ,
  IDC_STATIC_WIN32_CENTER, IDC_STATIC_WIN32_RIGHT2LEFT  , IDC_STATIC_WIN32_DISABLED 
  };

int iIndex = (int)SizeOfArray(nBxpIdArray)-1;

if (bDelete) //Delete controls from the memory
  {
  while(iIndex >= 0)
    {
    CWnd* pBtn = GetDlgItem(nBxpIdArray[iIndex]);
    if (::IsWindow(pBtn->GetSafeHwnd()) && pBtn->IsKindOf(RUNTIME_CLASS(CStatic)))
      delete (CStatic*)pBtn;
    else
      ASSERT(false);
    iIndex--;
    }
  }
else //Create new controls
  {
  while(iIndex >= 0)
    {
    CStatic* pBtn = new CStatic();
    pBtn->SubclassDlgItem(nBxpIdArray[iIndex--], this);
    if (::IsWindow(pBtn->GetSafeHwnd()))
      {
      //pBtn->SetTextColor( 0x10F0F0-9800*iIndex, 0xFF0000+100*iIndex );
      //pBtn->m_clrBtnFace = 0xFF0000+100*iIndex;
      //pBtn->m_clrBtnText = 0x00FBFB-10*iIndex;
      }
    }
  }
}

/////////////////////////////////////////////////////////////////////////////
// CTestStaticDlg message handlers

//-----------------------------------------------------------------------------
/*This method is called by the framework in response to the
  WM_INITDIALOG message. This message is sent to the dialog box during the
  Create(), CreateIndirect() or DoModal() calls, which occur immediately before
  the dialog box is displayed.

  Returns: FALSE if the input focus to a control is set by this method or TRUE
  if Windows should set the focus to the first control in the dialog box.
 */
BOOL CTestStaticDlg::OnInitDialog()
{
TRACE(_T("CTestStaticDlg::OnInitDialog()\n"));
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

EnableToolTips(TRUE);

  //Test custom static control look and feel
BexGroup();
BxpGroup();

return TRUE;  // return TRUE  unless you set the focus to a control
}

//-----------------------------------------------------------------------------
/*
 */
void CTestStaticDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
/*This method is called by the framework to inform the CDialog object that it 
  is being destroyed. OnDestroy() is called after the CDialog object is removed 
  from the screen. 
 */
void CTestStaticDlg::OnDestroy()
{
BexGroup(true);
BxpGroup(true);
TRACE(LOG_EOT);
WinHelp(0L, HELP_QUIT);
CDialog::OnDestroy();
}

//-----------------------------------------------------------------------------
/*If you add a minimize button to your dialog, you will need the code below
  to draw the icon.  For MFC applications using the document/view model,
  this is automatically done for you by the framework.
 */
void CTestStaticDlg::OnPaint()
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

//-----------------------------------------------------------------------------
/*The system calls this to obtain the cursor to display while the user drags
  the minimized window.
 */
HCURSOR CTestStaticDlg::OnQueryDragIcon()
{
  return (HCURSOR) m_hIcon;
}

//-----------------------------------------------------------------------------
/*Notification handler
 */
BOOL CTestStaticDlg::OnToolTipNotify(UINT id,
                                NMHDR *pNMHDR,
                                LRESULT *pResult
                               )
{
   // need to handle both ANSI and UNICODE versions of the message
   TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
   TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
   CString strTipText;
   UINT nID = pNMHDR->idFrom;
   if (pNMHDR->code == TTN_NEEDTEXTA && (pTTTA->uFlags & TTF_IDISHWND) ||
      pNMHDR->code == TTN_NEEDTEXTW && (pTTTW->uFlags & TTF_IDISHWND))
   {
      // idFrom is actually the HWND of the tool
      nID = ::GetDlgCtrlID((HWND)nID);
   }

   if (nID != 0) // will be zero on a separator
      strTipText.Format(_T("Control ID = %d"), nID);
#ifndef _UNICODE
   if (pNMHDR->code == TTN_NEEDTEXTA)
      lstrcpyn(pTTTA->szText, strTipText, sizeof(pTTTA->szText));
   else
      _mbstowcsz(pTTTW->szText, strTipText, sizeof(pTTTW->szText));
#else
   _tcsncpy(pTTTW->szText, (LPCTSTR)strTipText, strTipText.GetLength());
#pragma todo("solve UNICODE mumbo-jumbo!")
#endif
   *pResult = 0;

   return TRUE;    // message was handled
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  4    Biblioteka1.3         2005-05-05 22:57:46  Darko            
 *  3    Biblioteka1.2         2005-05-05 17:28:04  Darko Kolakovic Testing new
 *       static controls
 *  2    Biblioteka1.1         2005-05-03 01:43:44  Darko            
 *  1    Biblioteka1.0         2005-05-02 17:04:47  Darko Kolakovic 
 * $
 *****************************************************************************/
