// MyPage1.cpp : implementation file
//

#include "stdafx.h"
#include "Resize.h"
#include "MyPage1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MyPage1 property page

IMPLEMENT_DYNCREATE(MyPage1, CPropertyPageResizable)

//##ModelId=3ECE52E60318
MyPage1::MyPage1() : CPropertyPageResizable(MyPage1::IDD)
{
	//{{AFX_DATA_INIT(MyPage1)
	m_ctrlEdit = _T("");
	//}}AFX_DATA_INIT
}

//##ModelId=3ECE52E60319
MyPage1::~MyPage1()
{
}

//##ModelId=3ECE52E6035E
void MyPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageResizable::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MyPage1)
	DDX_Control(pDX, IDC_PROGRESS1, m_ctrlProgress);
	DDX_Control(pDX, IDC_COMBO1, m_comboboxDir);
	DDX_Text(pDX, IDC_EDIT1, m_ctrlEdit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MyPage1, CPropertyPageResizable)
	//{{AFX_MSG_MAP(MyPage1)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MyPage1 message handlers

//##ModelId=3ECE52E60373
BOOL MyPage1::OnInitDialog() 
{
CPropertyPageResizable::OnInitDialog();
m_arrControlList.Add(IDOK,         CDlgItemResizable::POS_FLOATHOR   );
m_arrControlList.Add(IDCANCEL,     CDlgItemResizable::POS_FLOATHOR   );
m_arrControlList.Add(IDC_STATIC1,  CDlgItemResizable::SIZE_EXPANDBOTH);
m_arrControlList.Add(IDC_LIST1,    CDlgItemResizable::SIZE_EXPANDBOTH);
m_arrControlList.Add(IDC_EDIT1,    CDlgItemResizable::PROPORTIONAL_HOR|CDlgItemResizable::POS_FLOATVER);
m_arrControlList.Add(IDC_PROGRESS1,CDlgItemResizable::PROPORTIONAL_HOR|CDlgItemResizable::POS_FLOATVER);
m_arrControlList.Add(IDC_COMBO1,   CDlgItemResizable::PROPORTIONAL_HOR|CDlgItemResizable::POS_FLOATVER);
m_arrControlList.Add(IDC_LIST2,    CDlgItemResizable::SIZE_EXPANDHOR  |CDlgItemResizable::POS_FLOATVER);
m_arrControlList.Add(IDC_STATIC2,  CDlgItemResizable::POS_FLOATBOTH);
m_arrControlList.Add(IDC_SLIDER1,  CDlgItemResizable::POS_FLOATBOTH);

  //Additional initialization
m_comboboxDir.Dir(0, _T("*.*"));
m_comboboxDir.SetCurSel(0);

return TRUE;  // return TRUE unless you set the focus to a control
              // EXCEPTION: OCX Property Pages should return FALSE
}

//##ModelId=3ECE52E60386
void MyPage1::OnSize(UINT nType, int cx, int cy) 
{
CPropertyPageResizable::OnSize(nType, cx, cy);
if (m_ctrlProgress.m_hWnd != NULL)
  m_ctrlProgress.SetPos((cx*100)/m_arrControlList.m_sizeParent.cx -101);	
}
