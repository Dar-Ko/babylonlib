/*$Workfile: KDlgRsiz.cpp$: implementation file
  $Revision: 7$ $Date: 2004-10-01 22:34:43$
  $Author: Darko$

  Handles resizing of the dialog box
  Copyright: CommonSoft Inc.
  Mar. 2k Darko Kolakovic
 */

#include "stdafx.h"
#include "KDlgRsiz.h" //CDialogResizable class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

    //Default key section name for Resizable Dialog Box
static LPCTSTR s_lpszDefaultSectionName = _T("CDLGR%u");

/////////////////////////////////////////////////////////////////////////////
// CDialogResizable dialog

//::CDialogResizable()---------------------------------------------------------
/*To construct a resource-based modal dialog box, call either form of 
  the constructor.
 */
CDialogResizable::CDialogResizable(LPCTSTR lpszTemplateName, //a null-terminated 
                                       //string that is the name of a dialog-box 
                                       //template resource.
                                  CWnd* pParentWnd //= NULL the parent or owner 
                                       //window. If it is NULL, the main 
                                       //application window is set as parent.
                                  ) :
  CDialog(lpszTemplateName, pParentWnd),
  m_bModeless(TRUE),
  m_dwDlgStyle(DFCS_SCROLLSIZEGRIP), //Set sizing grip orientation, gripper itself is disabled.
  m_ptMinTrackSize(0,0)
{
}

CDialogResizable::CDialogResizable(UINT nIDTemplate, //the ID number of a dialog-box
                                                     //template resource.
                                   CWnd* pParentWnd //= NULL
                                   ) :
  CDialog(nIDTemplate, pParentWnd),
  m_bModeless(TRUE),
  m_dwDlgStyle(DFCS_SCROLLSIZEGRIP),
  m_ptMinTrackSize(0,0)
{
}

BEGIN_MESSAGE_MAP(CDialogResizable, CDialog)
  //{{AFX_MSG_MAP(CDialogResizable)
  ON_WM_CREATE()
  ON_WM_PAINT()
  ON_WM_NCHITTEST()
  ON_WM_SIZE()
  ON_WM_GETMINMAXINFO()
  ON_WM_DESTROY()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//LoadSettings()---------------------------------------------------------------
#include "KWinPlac.h" //CWindowPlacement class
#define IDD_ABOUTBOX                    100
/*Read the window placement from the settings section of the application's .INI file.
  If the function succeeds, the return value is TRUE.
  If the function fails, the return value is FALSE.
 */
BOOL CDialogResizable::LoadSettings( 
       LPCTSTR lpszSection, //= NULL the name of the section containing the entry
       LPCTSTR lpszEntry    //= NULL the entry name of the value to be retrieved
       )
{
try
  {
  CWindowPlacement wpPos;

  if (lpszSection != NULL)
    {
    ASSERT(lpszSection[0] !='\0'); //Empty string
    wpPos.m_strSection = lpszSection;
    }
  else
    wpPos.m_strSection.Format(s_lpszDefaultSectionName, (UINT)m_lpszTemplateName);
    //Hack with m_lpszTemplateName introduced Paul DiLascia, MSJ Sep. 98, Q&A

  if (lpszEntry != NULL)
    {
    ASSERT(lpszEntry[0] !='\0'); //Empty string
    wpPos.m_strEntry = lpszEntry;
    }
  if(wpPos.LoadSettings())
    return wpPos.SetWindowPlacement(this);
  return FALSE;
  }
catch (...)
  {
  TRACE2("%s %d CDlgItemResizable failure.\n",THIS_FILE, __LINE__);
  return FALSE;
  }
}

//SaveSettings()---------------------------------------------------------------
/*Store the window placement to the registry (or profile) file.
  If the function succeeds, the return value is TRUE.
  If the function fails, the return value is FALSE.
  To get extended error information, call GetLastError.
*/
BOOL CDialogResizable::SaveSettings(
       LPCTSTR lpszSection,//= NULL the section containing the entry
       LPCTSTR lpszEntry   //= NULL the entry name into which the value is to be written
       )
{
try
  {
  CWindowPlacement wpPos;
  if (lpszSection != NULL)
    {
    ASSERT(lpszSection[0] !='\0'); //Empty string
    wpPos.m_strSection = lpszSection;
    }
  else
    wpPos.m_strSection.Format(s_lpszDefaultSectionName,(UINT)m_lpszTemplateName);

  if (lpszEntry != NULL)
    {
    ASSERT(lpszEntry[0] !='\0'); //Empty string
    wpPos.m_strEntry = lpszEntry;
    }
  if (wpPos.GetWindowPlacement(this))
    return wpPos.SaveSettings();
  return FALSE;
  }
catch (...)
  {
  TRACE2("%s %d CDlgItemResizable failure.\n",__FILE__, __LINE__);
  return FALSE;
  }
}

//::RestorePlacement()---------------------------------------------------------
/*Load dialog's state, position and size from profile or registry and store
  same data when dialog ends. If successful, returns TRUE.

  Example:
      class CMyD :public CDialogResizable
        {
        ...
        virtual BOOL OnInitDialog();
        };
      BOOL CAboutDlg::OnInitDialog() 
        {
        CDialogResizable::OnInitDialog();
        m_arrControlList.Add(IDOK,     CDlgItemResizable::POS_FLOATHOR);
        m_arrControlList.Add(IDCANCEL, CDlgItemResizable::POS_FLOATBOTH);
          //Restore state and position after dialog's initialization
        VERIFY(RestorePlacement());
        return TRUE; 
        }
 */
BOOL CDialogResizable::RestorePlacement(LPCTSTR lpszSection,//= NULL the section containing the entry
                                        LPCTSTR lpszEntry   //= NULL the entry name into which the value is to be written
                                       )
{
if(!::IsWindow(m_hWnd))
  {
  TRACE0("Warning! CDialogResizable::RestorePlacement() Create derived object first!\n");
  return FALSE;
  }

  //Note: m_arrControlList have to be initialized. Only elements from 
  //m_arrControlList would be resized.
if(!::IsWindow(m_arrControlList.m_hParent))
  {
  TRACE0("Warning! CDialogResizable::RestorePlacement() Initialize control list first!\n");
  return FALSE;
  }

EnablePlacement();    //Set placement flag
return LoadSettings(lpszSection,lpszEntry);//Load position and size from profile.
}

//::EnumerateControls()--------------------------------------------------------
/*Enumerate dialog controls and set resizing mode for each control found.
  Returns the index of the last added item or -1 in case of failure.
  Throws CMemoryException.
 */
int CDialogResizable::EnumerateControls(const CDlgItemResizable::RESIZING_TYPE& Type //resizing mode
                                        )
{
int iRes = m_arrControlList.EnumerateControls();
if (iRes > -1)
  {
  while (iRes >= 0)
    {
    m_arrControlList[iRes].SetStyle(Type);
    iRes--;
    }
  iRes = m_arrControlList.GetElementCount()-1;
  }
return iRes;
}

//::DoModal()------------------------------------------------------------------
/*This member function to creates the modal dialog box.
  Returns value that specifies the value of the nResult parameter that was passed
  to the CDialog::EndDialog() member function, which is used to close the dialog 
  box.
 */
int CDialogResizable::DoModal()
{
m_bModeless = FALSE;
int iRes =  CDialog::DoModal();
m_bModeless = TRUE;
return iRes;
}

/////////////////////////////////////////////////////////////////////////////
// CDialogResizable message handlers

//::OnCreate()-----------------------------------------------------------------
#include "KBitMan.h"  //GetFlag()
/*The framework calls this member function when an application requests that 
  the Windows window be created by calling the Create or CreateEx member function.
  The CWnd object receives this call after the window is created but before it 
  becomes visible. OnCreate is called before the Create or CreateEx member 
  function returns.

  Note: This implementation adjusts some windows and sizing grip styles. You are on
  your own if you override this member function, or if you change windows style  
  (WS_EX_LAYOUTRTL in particular) sometime after this point.
 */
int CDialogResizable::OnCreate(LPCREATESTRUCT lpCreateStruct//structure that contains 
                               //information about the CWnd object being created
                               ) 
{

if (CDialog::OnCreate(lpCreateStruct) == -1)
  return -1; //Failure

LONG lStyle;
lStyle = GetWindowLong(m_hWnd,GWL_EXSTYLE);

  //Adjust sizing grip style
if (IsGripEnabled())
  { 
  m_dwDlgStyle = MAKELONG((GetFlag(lStyle, WS_EX_LAYOUTRTL) ? DFCS_SCROLLSIZEGRIPRIGHT : 
                                                              DFCS_SCROLLSIZEGRIP),
                          HIWORD(m_dwDlgStyle));
  }

if(IsModal()) //If property sheet is modal, add resizing border
  {
     //Adjust the extended window style
  if (!GetFlag(lStyle,WS_EX_DLGMODALFRAME))
    {
    #if (WINVER >= 0x0400)
      EnableFlag(lStyle,WS_EX_WINDOWEDGE);
      SetWindowLong(m_hWnd,GWL_EXSTYLE,lStyle);
    #endif
    }
  else
    {
    DisableFlag(lStyle,WS_EX_DLGMODALFRAME);
    SetWindowLong(m_hWnd,GWL_EXSTYLE,lStyle);
    }

    //Adjust the window style
  lStyle = GetWindowLong(m_hWnd,GWL_STYLE); 
  if (GetFlag(lStyle,DS_MODALFRAME))
    DisableFlag(lStyle,DS_MODALFRAME);
  EnableFlag( lStyle,WS_THICKFRAME);
  SetWindowLong(m_hWnd,GWL_STYLE,lStyle);
  }

return 0;
}

//::OnInitDialog()-------------------------------------------------------------
/*The framework calls this function when the dialog is initialized.
  Override it if any special action is required when the dialog is initialized. 
  The default implementation returns FALSE.

  Example:
      #include "KDlgRsiz.h" //CDialogResizable class
      class CMyD :public CDialogResizable
        {
        ...
        virtual BOOL OnInitDialog();
        };
      BOOL CAboutDlg::OnInitDialog() 
        {
        CDialogResizable::OnInitDialog();
        m_arrControlList.Add(IDOK,     CDlgItemResizable::POS_FLOATHOR);
        m_arrControlList.Add(IDCANCEL, CDlgItemResizable::POS_FLOATBOTH);
        return TRUE; 
        }
 */
BOOL CDialogResizable::OnInitDialog() 
{
BOOL bResult = CDialog::OnInitDialog();

CRect rect;
GetWindowRect(rect);
SetMinTrackSize(rect);
  
  //Initialize control list
VERIFY(m_arrControlList.OnInitDialog(STATIC_DOWNCAST(CWnd,this)));

return bResult;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}

//::OnNcHitTest()--------------------------------------------------------------
/*The framework calls this member function every time the mouse is moved.
  This implementation includes sizing grip into non-client area.
 */
UINT CDialogResizable::OnNcHitTest(CPoint point //the screen coordinates of 
                                   //the cursor
                                   ) 
{
UINT nRes = CWnd::OnNcHitTest(point);
  //If sizing grip is visible, enlarge non-client area
if((nRes == HTCLIENT) && IsGripEnabled()) 
  {
  CSize size;
  CRect rect;
  GetGripSize(size);
  GetClientRect(rect);
  rect.TopLeft() = rect.BottomRight() - size;
  ScreenToClient((LPPOINT)&point);
  if(rect.PtInRect(point)) 
    nRes = HTBOTTOMRIGHT; 
  } 
return nRes; 
}

//::OnPaint()------------------------------------------------------------------
/*$Description
 */
void CDialogResizable::OnPaint() 
{
CPaintDC dc(this); // device context for painting
  // paint inside client area
CRect rect;
GetClientRect(rect);
DrawGripper(&dc, rect);
}

//::OnSize()-------------------------------------------------------------------
/*The framework calls this member function after the window’s size has changed. 
 */
void CDialogResizable::OnSize(UINT nType, //the type of resizing requested
                              int cx,     //the new width of the client area
                              int cy      //the new height of the client area
                              ) 
{
CDialog::OnSize(nType, cx, cy);
if (nType != SIZE_MINIMIZED)
  {
  m_arrControlList.OnSize(nType,cx,cy);
  Invalidate();
  }
}

//::OnGetMinMaxInfo------------------------------------------------------------------
/*The framework calls this member function whenever Windows needs to know the maximized 
  position or dimensions, or the minimum or maximum tracking size. 
  This implementation limits minimal tracking size to the size of the property sheet 
  on creation.
 */
void CDialogResizable::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI //structure that contains 
                                                             //tracking size
                                       ) 
{
CDialog::OnGetMinMaxInfo(lpMMI);

lpMMI->ptMinTrackSize.x = m_ptMinTrackSize.x;
lpMMI->ptMinTrackSize.y = m_ptMinTrackSize.y;
}


//::OnDestroy------------------------------------------------------------------
/*The framework calls this member function to inform the CWnd object that it 
  is being destroyed. OnDestroy is called after the CWnd object is removed from 
  the screen. This implemetation saves window placement, if requested.
 */
void CDialogResizable::OnDestroy() 
{
ASSERT(IsWindow(m_hWnd));
if (IsPlacementEnabled())
  VERIFY(SaveSettings());
CDialog::OnDestroy();
}
