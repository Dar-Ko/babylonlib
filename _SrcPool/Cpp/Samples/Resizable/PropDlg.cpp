// PropDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Resize.h"
#include "PropDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropDlg dialog


//##ModelId=3ECE52E60065
CPropDlg::CPropDlg(LPCTSTR lpszTemplateName, CWnd* pParent /*=NULL*/)
	: CDialogResizable(lpszTemplateName, pParent)
{
		// NOTE: copy the ClassWizard initialization here

}

//##ModelId=3ECE52E60070
void CPropDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogResizable::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropDlg, CDialogResizable)
	//{{AFX_MSG_MAP(CPropDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropDlg message handlers

//##ModelId=3ECE52E60083
BOOL CPropDlg::OnInitDialog() 
{
CDialogResizable::OnInitDialog();
EnumerateControls(CDlgItemResizable::ALL_PROPORTIONAL);
  //Load position and size from profile.
if (IsPlacementEnabled())
  {
  //Note: m_arrControlList  have to be initialized.
  //Only elements from m_arrControlList  would be resized.
  LoadSettings ();
  }

return TRUE;  // return TRUE unless you set the focus to a control
              // EXCEPTION: OCX Property Pages should return FALSE
}
