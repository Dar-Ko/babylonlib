// MyPropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "Resize.h"
#include "MyPropertySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MyPropertySheet

IMPLEMENT_DYNAMIC(MyPropertySheet, CPropertySheetResizable)

//##ModelId=3ECE52E600C9
MyPropertySheet::MyPropertySheet()
{
AddPage(&m_Page1);
AddPage(&m_Page2);
AddPage(&m_Page3);
AddPage(&m_Page4);
}

//##ModelId=3ECE52E600CA
MyPropertySheet::MyPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheetResizable(nIDCaption, pParentWnd, iSelectPage)
{
AddPage(&m_Page1);
AddPage(&m_Page2);
AddPage(&m_Page3);
AddPage(&m_Page4);
}

//##ModelId=3ECE52E600DE
MyPropertySheet::MyPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheetResizable(pszCaption, pParentWnd, iSelectPage)
{
AddPage(&m_Page1);
AddPage(&m_Page2);
AddPage(&m_Page3);
AddPage(&m_Page4);
}

//##ModelId=3ECE52E60142
MyPropertySheet::~MyPropertySheet()
{
}


BEGIN_MESSAGE_MAP(MyPropertySheet, CPropertySheetResizable)
	//{{AFX_MSG_MAP(MyPropertySheet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MyPropertySheet message handlers


