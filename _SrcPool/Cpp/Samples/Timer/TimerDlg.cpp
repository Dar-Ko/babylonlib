// TimerDlg.cpp : implementation file
//

#include "StdAfx.h"
#include "Timer.h"
#include "TimerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

//##ModelId=3ECE708B01DA
class CAboutDlg : public CDialog
{
public:
	//##ModelId=3ECE708B01F8
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	//##ModelId=3ECE708B0202
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//##ModelId=3ECE708B01F8
CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

//##ModelId=3ECE708B0202
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

///////////////////////////////////////////////////////////////////////////////

const int TIME_OUT = 1000;//time interval [ms]

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimerDlg dialog

//##ModelId=3ECE708901CD
CTimerDlg::CTimerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTimerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTimerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

//##ModelId=3ECE708901D7
void CTimerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTimerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTimerDlg, CDialog)
	//{{AFX_MSG_MAP(CTimerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_TIMER1, OnTimer1)
	ON_BN_CLICKED(ID_TIMER2, OnTimer2)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTimerDlg message handlers
//CTimerW* pTimer = NULL;
//##ModelId=3ECE7089023B
BOOL CTimerDlg::OnInitDialog()
{
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
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
    m_ctwTimer1.Start(2*TIME_OUT, GetSafeHwnd(), CTimerDlg::IDD);
    m_ctwTimer2.Start(3*TIME_OUT, GetSafeHwnd(), CTimerDlg::IDD+1);
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE  unless you set the focus to a control
}

//##ModelId=3ECE70890250
void CTimerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

//##ModelId=3ECE70890265
void CTimerDlg::OnPaint() 
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
//##ModelId=3ECE70890278
HCURSOR CTimerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//::OnOK()---------------------------------------------------------------------
#include "KTimer.h" //CTimer class
/*Called when the user clicks the OK button (the button with an ID of IDOK).
  Creates new timers.
 */
//##ModelId=3ECE70890282
void CTimerDlg::OnOK() 
{
TRACE0("CTimerDlg::OnOK()\n");	
CreateCallbackTimer();
}

//::CreateCallbackTimer()--------------------------------------------------------------
/*Testing creation of new timers. The timers are using callback function. System uses
  DWORD value to pass time elapsed since it was started and will wrap to zero after
  49.7 days.
 */
//##ModelId=3ECE70890231
void CTimerDlg::CreateCallbackTimer()
{
TRACE0("CTimerDlg::CreateCallbackTimer()\n");	
  //Create simple timers with assigned callback function
extern VOID CALLBACK MyTimerProc(HWND hWnd,UINT uMsg,UINT nTimerID,DWORD dwTime);
extern CTimer* g_pctTimer1;
extern CTimer* g_pctTimer2;

  //Initialize timers
if (g_pctTimer1 == NULL)
  g_pctTimer1 = new CTimer();
if (g_pctTimer2 == NULL)
  {
  g_pctTimer2 = new CTimer(MyTimerProc);
  g_pctTimer1->SetTimerProc(MyTimerProc);
  }

  //Run timers
g_pctTimer1->Start(TIME_OUT);
g_pctTimer2->Start(4*TIME_OUT);
}

//::OnCancel()-----------------------------------------------------------------
/*Called when the user clicks the Cancel button (the button with an ID of IDCANCEL).
  Deletes timers.
 */
//##ModelId=3ECE7089028D
void CTimerDlg::OnCancel() 
{
TRACE0("CTimerDlg::OnCancel()\n");
extern CTimer* g_pctTimer1;
extern CTimer* g_pctTimer2;
if (g_pctTimer1 != NULL)
  {
  #ifdef _DEBUG
    g_pctTimer1->Dump();
  #endif
  delete g_pctTimer1;
  g_pctTimer1 = NULL;
  }
if (g_pctTimer2 != NULL)
  {
  #ifdef _DEBUG
    g_pctTimer2->Dump();
  #endif
  delete g_pctTimer2;
  g_pctTimer2 = NULL;
  }

m_ctwTimer1.Stop();
m_ctwTimer2.Stop();	
CDialog::OnCancel();
}

//::OnTimer1()-----------------------------------------------------------------
/*Called when the user clicks the Timer 1 button (the button with an ID of ID_TIMER1).
  Stops or starts first callback timer.
 */
//##ModelId=3ECE708902A0
void CTimerDlg::OnTimer1() 
{
extern CTimer* g_pctTimer1;
if (g_pctTimer1 != NULL)
  {
  if(g_pctTimer1->IsStarted())
    g_pctTimer1->Stop();
  else
    g_pctTimer1->Start(TIME_OUT);
  }
}

//::OnTimer2()-----------------------------------------------------------------
/*Called when the user clicks the Timer 2 button (the button with an ID of ID_TIMER2).
  Stops or starts second callback timer.
 */
//##ModelId=3ECE708902AA
void CTimerDlg::OnTimer2() 
{
extern CTimer* g_pctTimer2;
if (g_pctTimer2 != NULL)
  {
  if(g_pctTimer2->IsStarted())
    g_pctTimer2->Stop();
  else
    g_pctTimer2->Start(4*TIME_OUT);
  }
}

//::OnTimer()--------------------------------------------------------
/*Handles WM_TIMER messages sent by m_ctwTimer2.
 */
//##ModelId=3ECE708902B5
void CTimerDlg::OnTimer(UINT nIDEvent) 
{
TRACE1("CTimerDlg::OnTimer(ID = %d)\n",nIDEvent);
switch(nIDEvent)
  {
  case CTimerDlg::IDD:

      break;

  case (CTimerDlg::IDD +1):

      break;
  }
	
CDialog::OnTimer(nIDEvent);
}
