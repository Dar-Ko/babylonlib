// MyPage2.cpp : implementation file
//

#include "stdafx.h"
#include "Resize.h"
#include "MyPage2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MyPage2 property page

IMPLEMENT_DYNCREATE(MyPage2, CPropertyPageResizable)

//##ModelId=3ECE52E6028C
MyPage2::MyPage2() : CPropertyPageResizable(MyPage2::IDD)
{
	//{{AFX_DATA_INIT(MyPage2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

//##ModelId=3ECE52E60296
MyPage2::~MyPage2()
{
}

//##ModelId=3ECE52E602B4
void MyPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageResizable::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MyPage2)
	DDX_Control(pDX, IDC_IPADDRESS1, m_IPAddress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MyPage2, CPropertyPageResizable)
	//{{AFX_MSG_MAP(MyPage2)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MyPage2 message handlers

//##ModelId=3ECE52E602C8
BOOL MyPage2::OnInitDialog() 
{
CPropertyPageResizable::OnInitDialog();
	
m_arrControlList.Add(IDOK,     CDlgItemResizable::SIZE_EXPANDVER|CDlgItemResizable::POS_FLOATHOR);
m_arrControlList.Add(IDCANCEL, CDlgItemResizable::POS_FLOATBOTH);	
m_arrControlList.Add(IDC_MONTHCALENDAR1, CDlgItemResizable::SIZE_EXPANDBOTH);	
m_arrControlList.Add(IDC_CHECK2,      CDlgItemResizable::POS_FLOATBOTH);	
m_arrControlList.Add(IDC_RADIO1,      CDlgItemResizable::POS_FLOATBOTH);	
m_arrControlList.Add(IDC_IPADDRESS1,  CDlgItemResizable::POS_FLOATBOTH);
m_IPAddress.SetAddress(0xCD,0xB2,0xAE,'F');

return TRUE;  // return TRUE unless you set the focus to a control
	            // EXCEPTION: OCX Property Pages should return FALSE
}

  //SpawnnURL function
//##ModelId=3ECE52E602D2
void MyPage2::OnRadio1() 
{
BYTE Adr[4];
m_IPAddress.GetAddress(Adr[0],Adr[1],Adr[2],Adr[3]);
CString szURL;
szURL.Format(_T("http://%u.%u.%u.%u"),Adr[0],Adr[1],Adr[2],Adr[3]);

HINSTANCE hInst = ShellExecute(NULL, _T("open"), szURL, NULL,NULL, SW_SHOW);
  //If it failed, get the .htm regkey and lookup the program
if ((UINT)hInst <= HINSTANCE_ERROR) 
  {
  TRACE0("Spawn Shell failed\n");
  }
}
