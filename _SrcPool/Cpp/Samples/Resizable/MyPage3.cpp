// MyPage3.cpp : implementation file
//

#include "stdafx.h"
#include "Resize.h"
#include "MyPage3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MyPage3 property page

IMPLEMENT_DYNCREATE(MyPage3, CPropertyPageResizable)

//##ModelId=3ECE52E601EC
MyPage3::MyPage3() : CPropertyPageResizable(MyPage3::IDD)
{
	//{{AFX_DATA_INIT(MyPage3)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

//##ModelId=3ECE52E601ED
MyPage3::~MyPage3()
{
}

//##ModelId=3ECE52E6023C
void MyPage3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageResizable::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MyPage3)
	DDX_Control(pDX, IDC_LIST2, m_ctrlListBox);
	DDX_Control(pDX, IDC_HOTKEY1, m_HotSpot);
	DDX_Control(pDX, IDC_COMBOBOXEX1, m_ctrlComboBox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MyPage3, CPropertyPageResizable)
	//{{AFX_MSG_MAP(MyPage3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MyPage3 message handlers

//##ModelId=3ECE52E60250
BOOL MyPage3::OnInitDialog() 
{
CPropertyPageResizable::OnInitDialog();

m_arrControlList.Add(IDC_LIST2,       CDlgItemResizable::SIZE_EXPANDBOTH);	
m_arrControlList.Add(IDC_HOTKEY1,     CDlgItemResizable::POS_FLOATBOTH );
m_arrControlList.Add(IDC_COMBOBOXEX1, CDlgItemResizable::POS_FLOATBOTH);	

m_ctrlListBox.Dir(0, "*.*");

return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
