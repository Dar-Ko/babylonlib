/*$Workfile: KPropShR.cpp$: implementation file
  $Revision: 1.3 $ $Date: 2003/01/28 05:37:44 $
  $Author: ddarko $

  Handles resizing of the property sheet
  Copyright: CommonSoft Inc.
  Mar. 2k Darko Kolakovic
 */

#include "StdAfx.h"
#ifndef __AFXCMN_H__
  #include <AfxCmn.h> //CTabCtrl class
#endif
#include "KPropShR.h" //CPropertySheetResizable class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertySheetResizable


IMPLEMENT_DYNAMIC(CPropertySheetResizable, CPropertySheet)

CPropertySheetResizable::CPropertySheetResizable() :
  CPropertySheet(_T("")),
  m_ptMinTrackSize(0,0)
{
}

CPropertySheetResizable::CPropertySheetResizable(UINT nIDCaption, //[in] string
                                                     //resource ID of the title
                                                 CWnd* pParentWnd,//[in] parent
                                                     //window 
                                                 UINT iSelectPage //[in] active
                                                     //page ID
                                                ) :
	CPropertySheet(nIDCaption, pParentWnd, iSelectPage),
  m_ptMinTrackSize(0,0)
{
}

CPropertySheetResizable::CPropertySheetResizable(LPCTSTR pszCaption, //[in] title
                                                 CWnd* pParentWnd,
                                                 UINT iSelectPage) :
	CPropertySheet(pszCaption, pParentWnd, iSelectPage),
  m_ptMinTrackSize(0,0)
{
}

CPropertySheetResizable::~CPropertySheetResizable()
{
}


BEGIN_MESSAGE_MAP(CPropertySheetResizable, CPropertySheet)
	//{{AFX_MSG_MAP(CPropertySheetResizable)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//::RecalcLayout()-------------------------------------------------------------
/*Call this member function to correctly redisplay the window after you have
  resized parent window. If NULL has been passed for the pParent parameter,
  function takes size of the parent frame as valid.

  Example:
    #include "KPropShR.h"
    class CMyPropertySheet : public CPropertySheetResizable
      {
      ...
      };
    class CMyView : public CView
      {
      ...
      CMyPropertySheet m_PropertySheet;
      afx_msg void OnSize(UINT nType, int cx, int cy);
      ...
      };
      //The framework calls this member function after the windows size has changed.
    void CMyView::OnSize(UINT nType, int cx, int cy)
      {
      CView::OnSize(nType, cx, cy);
      if (nType != SIZE_MINIMIZED && 	::IsWindow(m_PropertySheet.GetSafeHwnd()))
        m_PropertySheet.RecalcLayout(this); //Resize embedded property sheet
      }
 */
void CPropertySheetResizable::RecalcLayout(CWnd* pParent //=NULL parent window
                                           )
{
CRect rect;
if (pParent == NULL)
  {
  CFrameWnd* pFrame = GetParentFrame();
  if (pFrame == NULL)
    return;   //No parent window
  pFrame->GetClientRect(&rect);
  SetWindowPos(NULL, 0, 0, rect.Width()-5, rect.Height(),
               SWP_NOACTIVATE|SWP_NOZORDER);
  }
else
  {
  ASSERT(::IsWindow(pParent->GetSafeHwnd()));
  pParent->GetWindowRect(rect);
  SetWindowPos(NULL,0,0,rect.Width(),rect.Height(),
               SWP_NOZORDER|SWP_NOACTIVATE);
  }
}

//::SetActivePageItem()--------------------------------------------------------
/*Replaces handle of property page with handle of the active property page.
 */
BOOL CPropertySheetResizable::SetActivePageItem()
{
HWND hWnd = GetActivePage()->GetSafeHwnd();
if ((m_arrControlList.GetElementCount() > 0) && (hWnd != NULL))
  {
    //1st element int the list of the controls is reserved for the active page window
  m_arrControlList[0].m_hWnd = GetActivePage()->GetSafeHwnd();
  return TRUE;
  }
return FALSE;
}

//::AddDefaultButtons()--------------------------------------------------------
/*The framework calls this member function during initialization of the
  resizable wizard property sheet. This function enables resizing of the Apply Now,
  OK, Cancel and Help buttons. Function is called from OnInitDialog().
  Override this function if different resizing behavior is needed.

  Note: Modeless property sheets displayed with a call to Create do not have
  OK, Cancel, Apply Now, and Help buttons as modal property sheets do.
 */
void CPropertySheetResizable::AddDefaultButtons()
{
if(!::IsWindow(m_arrControlList.m_hParent))
  m_arrControlList.SetParent(this);

if (GetDlgItem(IDOK) != NULL)
	m_arrControlList.Add(IDOK,         CDlgItemResizable::POS_FLOATBOTH);

if (GetDlgItem(IDCANCEL) != NULL)
	m_arrControlList.Add(IDCANCEL,     CDlgItemResizable::POS_FLOATBOTH);

if ((GetDlgItem(ID_APPLY_NOW) != NULL) &&
    ((m_psh.dwFlags & PSH_NOAPPLYNOW) != PSH_NOAPPLYNOW))
	m_arrControlList.Add(ID_APPLY_NOW, CDlgItemResizable::POS_FLOATBOTH);

if ((GetDlgItem(IDHELP) != NULL) &&
   ((m_psh.dwFlags & PSH_HASHELP) == PSH_HASHELP))
	m_arrControlList.Add(IDHELP,       CDlgItemResizable::POS_FLOATBOTH);
}

//::AddWizardButtons()---------------------------------------------------------
        //Property sheet wizard separator (undocumented ID)
#define __IDS_SEPARATORLINE1_    ID_WIZFINISH + 1
        //Property sheet wizard separator 2 (undocumented ID)
#define __IDS_SEPARATORLINE2_    ID_WIZFINISH + 2
/*The framework calls this member function during initialization of the
  resizable wizard property sheet. This function enables resizing of the Back,
  Next and Finish buttons. Function is called from OnInitDialog().
  Override this function if different resizing behavior is needed.
 */
void CPropertySheetResizable::AddWizardButtons()
{
if(!::IsWindow(m_arrControlList.m_hParent))
  m_arrControlList.SetParent(this);

if (GetDlgItem(ID_WIZBACK) != NULL)
  m_arrControlList.Add(ID_WIZBACK,   CDlgItemResizable::POS_FLOATBOTH);

if (GetDlgItem(ID_WIZNEXT) != NULL)
	m_arrControlList.Add(ID_WIZNEXT,   CDlgItemResizable::POS_FLOATBOTH);

if (GetDlgItem(ID_WIZFINISH) != NULL)
	m_arrControlList.Add(ID_WIZFINISH, CDlgItemResizable::POS_FLOATBOTH);

if (GetDlgItem(__IDS_SEPARATORLINE1_) != NULL)
	m_arrControlList.Add(__IDS_SEPARATORLINE1_, 
	                     CDlgItemResizable::SIZE_EXPANDHOR | 
	                     CDlgItemResizable::POS_FLOATVER);

if (GetDlgItem(__IDS_SEPARATORLINE2_) != NULL)
	m_arrControlList.Add(__IDS_SEPARATORLINE2_, 
	                     CDlgItemResizable::SIZE_EXPANDHOR | 
	                     CDlgItemResizable::POS_FLOATVER);
}

//::AddActivePage()------------------------------------------------------------
/*Initializes first item in the list of controls with active property page
  parameters. Function overwrites previous content of the item.
  Returns TRUE if succesfull.
 */
BOOL CPropertySheetResizable::AddActivePage()
{
if (!::IsWindow(m_arrControlList.m_hParent))
  {
    //List is not initialized; see CDlgItemResizableList::OnInitDialog()
  return FALSE;
  }

CRect rtTabSize;
CPropertyPage* pPropertyPage = GetActivePage();
pPropertyPage->GetWindowRect(rtTabSize);
ScreenToClient(rtTabSize);

  //If array has not elements, add one.
if(m_arrControlList.GetElementCount() <= 0)
  m_arrControlList.Add(CDlgItemResizable());
  //Get first element
CDlgItemResizable& dlgrItem = m_arrControlList[0];

dlgrItem.m_hWnd = pPropertyPage->m_hWnd;
dlgrItem.SetStyle(CDlgItemResizable::SIZE_EXPANDBOTH);
dlgrItem = rtTabSize;

#ifdef _DEBUG
  afxDump << "CPropertySheetResizable::AddActivePage()\n\t" << dlgrItem;
#endif
return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CPropertySheetResizable message handlers

//::OnCreate()-----------------------------------------------------------------
#include "KBitMan.h"  //GetFlag()
/*The framework calls this member function when an application requests that
  the Windows window be created by calling the Create or CreateEx member function.
  The CWnd object receives this call after the window is created but before it
  becomes visible. OnCreate is called before the Create or CreateEx member
  function returns.

  Note: KB Q148304: VC++ 4.0-5.0 CPropertySheet::DoModal() causes first chance
  exception in Windows 95.
 */
int CPropertySheetResizable::OnCreate(LPCREATESTRUCT lpCreateStruct //structure that
                                      //contains information about the CWnd object being created
                                      )
{
if (CPropertySheet::OnCreate(lpCreateStruct) == -1)
	return -1;

if(IsModal()) //If property sheet is modal, add resizing border
  {
  LONG lStyle;
    //Adjust the window style
  lStyle = GetWindowLong(m_hWnd,GWL_STYLE);
  if (GetFlag(lStyle,DS_MODALFRAME))
    {
    DisableFlag(lStyle,DS_MODALFRAME);
    EnableFlag( lStyle,WS_THICKFRAME);
	  SetWindowLong(m_hWnd,GWL_STYLE,lStyle);
    }
     //Adjust the extended window style
  lStyle = GetWindowLong(m_hWnd,GWL_EXSTYLE);
  if (GetFlag(lStyle,WS_EX_DLGMODALFRAME))
    {
    DisableFlag(lStyle,WS_EX_DLGMODALFRAME);
	  SetWindowLong(m_hWnd,GWL_EXSTYLE,lStyle);
    }
  else
    {
    #if (WINVER >= 0x0400)
      EnableFlag(lStyle,WS_EX_WINDOWEDGE);
	    SetWindowLong(m_hWnd,GWL_EXSTYLE,lStyle);
    #endif
    }
  }

return 0;
}

//::OnInitDialog()-------------------------------------------------------------
/*The framework calls this function when the property sheet is initialized.
  Override it if any special action is required when the dialog is initialized.
  The default implementation returns FALSE.
 */
BOOL CPropertySheetResizable::OnInitDialog()
{
BOOL bResult = CPropertySheet::OnInitDialog();

CRect rect;
GetWindowRect(rect);
SetMinTrackSize(rect);

  //Initialize control list
VERIFY(m_arrControlList.OnInitDialog(STATIC_DOWNCAST(CWnd,this)));
  //Append controls
if (!::IsWizard(*this))
  {
    //1st element is reserved for the active page window
  AddActivePage();

  m_arrControlList.Add(AFX_IDC_TAB_CONTROL, CDlgItemResizable::SIZE_EXPANDBOTH);
  }
else
  {
    //In Wizard mode, tab control should not be visible, so it is moved to
    //the galaxy far, far away. This reduces garbage on the screen left by
    //tab control when property pages are with fixed size, or not derived from
    //CResizablePropertyPage
  CTabCtrl* pTab = GetTabControl();
  if (pTab != NULL)
    {
    pTab->SetWindowPos(NULL,0, 0, 0, 0, SWP_NOZORDER|SWP_NOACTIVATE);
    }
    //1st element is reserved for the active page window
  AddActivePage();
  }

  //Append more items to the list
AddDefaultButtons();
AddWizardButtons();

#ifdef _DEBUG
  afxDump << m_psh;
#endif
return bResult;
}

//::OnSize()-------------------------------------------------------------------
/*The framework calls this member function after the windows size has changed.
 */
void CPropertySheetResizable::OnSize(UINT nType,//the type of resizing requested
                                     int cx,    //the new width of the client area
                                     int cy     //the new height of the client area
                                     )
{
CPropertySheet::OnSize(nType, cx, cy);

if (nType != SIZE_MINIMIZED)
  {
  if(SetActivePageItem()) //Resize only active page
    {
    m_arrControlList.OnSize(nType,cx,cy);
    Invalidate();
    }
  }
}

//::OnGetMinMaxInfo------------------------------------------------------------------
/*The framework calls this member function whenever Windows needs to know the maximized
  position or dimensions, or the minimum or maximum tracking size.
  This implemetation limits minimal tracking size to the size of the propert sheet
  on creation.
 */
void CPropertySheetResizable::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI //structure that contains
                                                                    //tracking size
                                              )
{
CPropertySheet::OnGetMinMaxInfo(lpMMI);

lpMMI->ptMinTrackSize.x = m_ptMinTrackSize.x;
lpMMI->ptMinTrackSize.y = m_ptMinTrackSize.y;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  5    Biblioteka1.4         29/01/2002 2:41:05 PMDarko           Tag update
 *  4    Biblioteka1.3         19/08/2001 10:54:39 PMDarko           Butyfier
 *  3    Biblioteka1.2         11/07/2001 9:52:16 PMDarko           
 *  2    Biblioteka1.1         08/06/2001 10:51:25 PMDarko           VSS
 *  1    Biblioteka1.0         13/08/2000 2:57:08 PMDarko           
 * $
 *****************************************************************************/
