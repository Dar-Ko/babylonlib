// AboutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Resize.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog



//##ModelId=3ECE52EC0028
CAboutDlg::CAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialogResizable(CAboutDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAboutDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
EnableSizingGrip();
}

//##ModelId=3ECE52EC0033
CAboutDlg::CAboutDlg(LPCTSTR lpszTemplateName, CWnd* pParent /*=NULL*/)
	: CDialogResizable(lpszTemplateName, pParent)
{
		// NOTE: copy the ClassWizard initialization here
EnableSizingGrip();
}

//##ModelId=3ECE52EC0046
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogResizable::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialogResizable)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg message handlers

//##ModelId=3ECE52EC005A
BOOL CAboutDlg::OnInitDialog() 
{
extern BOOL g_bSavePosition;

CDialogResizable::OnInitDialog();
	
m_arrControlList.Add(IDOK,     CDlgItemResizable::POS_FLOATHOR);
m_arrControlList.Add(IDC_STATIC1, CDlgItemResizable::SIZE_PROPORTIONAL);
m_arrControlList.Add(IDC_STATIC2, CDlgItemResizable::POS_FLOATHOR);
m_arrControlList.Add(IDC_STATIC3, CDlgItemResizable::POS_FLOATBOTH);
m_arrControlList.Add(IDC_STATIC4, CDlgItemResizable::POS_FLOATBOTH);

  //Load and save dialog's state, position and size
if (g_bSavePosition)
  VERIFY(RestorePlacement());

return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

