// MyPage4.cpp : implementation file
//

#include "stdafx.h"
#include "Resize.h"
#include "MyPage4.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MyPage4 property page

IMPLEMENT_DYNCREATE(MyPage4, CPropertyPageResizable)

//##ModelId=3ECE52E6017E
MyPage4::MyPage4() : CPropertyPageResizable(MyPage4::IDD)
{
	//{{AFX_DATA_INIT(MyPage4)
	//}}AFX_DATA_INIT
}

//##ModelId=3ECE52E60188
MyPage4::~MyPage4()
{
}

//##ModelId=3ECE52E60193
void MyPage4::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageResizable::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MyPage4)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MyPage4, CPropertyPageResizable)
	//{{AFX_MSG_MAP(MyPage4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MyPage4 message handlers

//##ModelId=3ECE52E601A6
BOOL MyPage4::OnInitDialog() 
{
CPropertyPageResizable::OnInitDialog();
	
m_arrControlList.Add(IDOK,           CDlgItemResizable::POS_FLOATVER);
m_arrControlList.Add(IDCANCEL,       CDlgItemResizable::POS_FLOATBOTH);	
m_arrControlList.Add(IDC_STATIC1,    CDlgItemResizable::SIZE_EXPANDBOTH);	
m_arrControlList.Add(IDC_STATIC2,    CDlgItemResizable::SIZE_EXPANDHOR|CDlgItemResizable::POS_FLOATVER);	
m_arrControlList.Add(IDC_STATICICON, CDlgItemResizable::SIZE_PROPORTIONAL);	
m_arrControlList.Add(IDC_BUTTON1,    CDlgItemResizable::POS_FLOATHOR);	
	
return TRUE;  // return TRUE unless you set the focus to a control
              // EXCEPTION: OCX Property Pages should return FALSE
}

//##ModelId=3ECE52E60189
BOOL MyPage4::OnSetActive() 
{
  //Set Wizard's buttons: enable the Back button and disable the Next button.
CPropertySheet* psheet = DYNAMIC_DOWNCAST(CPropertySheet,GetParent());   
psheet->SetWizardButtons(PSWIZB_BACK|PSWIZB_FINISH);

SetModified(TRUE);	
return CPropertyPageResizable::OnSetActive();
}
