/*$Workfile: KPropPgR.cpp$: implementation file
  $Revision: 6$ $Date: 2005-05-24 16:23:05$
  $Author: Darko Kolakovic$

  Handles resizing of the property page
  Copyright: CommonSoft Inc.
  Mar. 2k Darko Kolakovic
 */

#include "stdafx.h"
#include "KPropPgR.h" //CPropertyPageResizable class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageResizable property page

IMPLEMENT_DYNAMIC(CPropertyPageResizable, CPropertyPage)


//::CPropertyPageResizable()---------------------------------------------------
/*Constructs a CPropertyPageResizable object.
 */
CPropertyPageResizable::CPropertyPageResizable()
{
}

CPropertyPageResizable::CPropertyPageResizable(UINT nIDTemplate, //[in] ID of
                                             //the template used for this page
                                               UINT nIDCaption //[in]= 0 string
                                             //resource ID of the title.
                                             //If 0, the name will be taken from
                                             //the dialog template for this page.
                                               ) :
  CPropertyPage(nIDTemplate,nIDCaption)
{
}

CPropertyPageResizable::CPropertyPageResizable(LPCTSTR lpszTemplateName,//[in]
                                         //resource name of the dialog template
                                               UINT nIDCaption //= 0 string
                                         //resource ID of the title.
                                         //If 0, the name will be taken from
                                         //the dialog template for this page.
                                               ) :
  CPropertyPage(lpszTemplateName,nIDCaption)
{
}

CPropertyPageResizable::~CPropertyPageResizable()
{
}

BEGIN_MESSAGE_MAP(CPropertyPageResizable, CPropertyPage)
  //{{AFX_MSG_MAP(CPropertyPageResizable)
  ON_WM_SIZE()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageResizable message handlers

//::OnInitDialog()-------------------------------------------------------------
/*The framework calls this function when the property page is initialized.
  Override it if any special action is required when the dialog is initialized.
  The default implementation returns FALSE.

  Example:
    #include "KPropPgR.h" //CPropertyPageResizable class
    class MyPage1 : public CPropertyPageResizable
      {
      ...
      virtual BOOL OnInitDialog();
      };
    BOOL CMyPage::OnInitDialog()
      {
      CPropertyPageResizable::OnInitDialog();
      m_arrControlList.Add(IDOK,         CDlgItemResizable::POS_FLOATHOR   );
      m_arrControlList.Add(IDCANCEL,     CDlgItemResizable::POS_FLOATHOR   );
      m_arrControlList.Add(IDC_STATIC1,  CDlgItemResizable::SIZE_EXPANDBOTH);
      m_arrControlList.Add(IDC_LIST1,    CDlgItemResizable::SIZE_EXPANDBOTH);
      return TRUE;
      }
 */
BOOL CPropertyPageResizable::OnInitDialog()
{
BOOL bResult = CPropertyPage::OnInitDialog();

  //Initialize control list
VERIFY(m_arrControlList.OnInitDialog(STATIC_DOWNCAST(CWnd,this)));

return bResult;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}

//::OnSize()-------------------------------------------------------------------
/*The framework calls this member function after the windows size has changed.
 */
void CPropertyPageResizable::OnSize(UINT nType, //[in] type of resizing requested
                                    int cx,     //[in] new width of the client area
                                    int cy      //[in] new height of the client area
                                    )
{
CPropertyPage::OnSize(nType, cx, cy);
if (nType != SIZE_MINIMIZED)
  {
  m_arrControlList.OnSize(nType,cx,cy);
  Invalidate();
  }
}

//::OnSetActive()--------------------------------------------------------------
#include "KPropShR.h" //IsWizard()
/*This member function is called by the framework when the page is chosen by
  the user and becomes the active page. Override this member function to perform
  tasks when a page is activated.
 */
BOOL CPropertyPageResizable::OnSetActive()
{
TRACE1("CPropertyPageResizable::OnSetActive() HWND = $%X\n",m_hWnd);
CPropertyPage::OnSetActive();    //Redraw controls with new size

    //Force resizing in Wizard mode
CWnd* pWnd = GetParent();
CPropertySheet* pSheet = DYNAMIC_DOWNCAST(CPropertySheet,pWnd);
if ((pSheet != NULL) && ::IsWizard(*pSheet))
  {
  CRect rect;
  pSheet->GetClientRect(rect);
  pSheet->PostMessage(WM_SIZE,SIZE_RESTORED,MAKELPARAM(rect.Width(),rect.Height()));
  }

return TRUE;
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  5    Biblioteka1.4         2002-01-29 15:41:00  Darko           Tag update
 *  4    Biblioteka1.3         2001-08-19 23:54:24  Darko           Butyfier
 *  3    Biblioteka1.2         2001-07-11 22:52:09  Darko
 *  2    Biblioteka1.1         2001-06-08 23:51:21  Darko           VSS
 *  1    Biblioteka1.0         2000-08-13 15:57:03  Darko
 * $
 *****************************************************************************/
