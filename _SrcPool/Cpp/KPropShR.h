/*KPropShR.h : header file
  $Revision: 1.3 $ $Date: 2003/01/28 05:37:44 $
  $Author: ddarko $
  
  Handles resizing of the property sheet
  CommonSoft Inc.
  Mar. 2k Darko Kolakovic
 */
#ifndef _KPROPSHR_H_
    //KPropShR.h sentry
  #define _KPROPSHR_H_

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

#include "KDlgItLs.h" //CDlgItemResizableList class

/////////////////////////////////////////////////////////////////////////////
// CPropertySheetResizable class handles the resizing of
// the property sheet and embedded controls.
//
// See Also: Diagnostic operator<<(CDumpContext& dc,PROPSHEETHEADER const& pshSrc)
//
// Note: Microsoft Windows specific (Win) and uses Microsoft Fundation Library (MFC).
//
// Pseudo code:
//
//    Construct CMyPropertySheet;
//    Create propery sheet window
//      {
//      OnCreate()
//        {
//        if window is modal
//          Set resizing style for the window;
//        };
//      };
//    Initialize CMyPropertySheet
//      {
//      OnInitDialog()
//        {
//        Enumerate all controls;
//        Set resizing style for the controls;
//        };
//      };
//    Change size
//      {
//      OnSize()
//        {
//        Change size and/or position of all controls;
//        };
//      };
//
class CPropertySheetResizable : public CPropertySheet
{
	DECLARE_DYNAMIC(CPropertySheetResizable)

// Construction
public:
  CPropertySheetResizable();
	CPropertySheetResizable(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPropertySheetResizable(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
protected:
  CDlgItemResizableList m_arrControlList; //a list of the embedded buttons
  CPoint  m_ptMinTrackSize; //the minimum tracking width and height

// Operations
public:
  void RecalcLayout(CWnd* pParent = NULL);
  void SetMinTrackSize(CRect rect);
  void SetMinTrackSize(UINT nWidth, UINT nHeight);
protected:
  BOOL AddActivePage();
private:
  BOOL IsModal() const;
	BOOL SetActivePageItem();

// Overrides
protected:
  virtual void AddDefaultButtons();
  virtual void AddWizardButtons();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertySheetResizable)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

  // Implementation
public:
	virtual ~CPropertySheetResizable();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPropertySheetResizable)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//::SetMinTrackSize()----------------------------------------------------------
/*Specifies the minimum tracking width and the minimum tracking
  height of the window. Size limit is used in handling the Windows message
  WM_GETMINMAXINFO.
  If modaless property sheet is used, parent frame tracking size have to be limited.
 */
inline void CPropertySheetResizable::SetMinTrackSize(CRect rect //minimal tracking rectangle, usually
                                                                //windows bounding rectangle
                                                                //obtained with GetwindowRect()
                                                     )
{
m_ptMinTrackSize.x = rect.Width();
m_ptMinTrackSize.y = rect.Height();
}

inline void CPropertySheetResizable::SetMinTrackSize(UINT nWidth, //minimal tracking width
                                                     UINT nHeight //minimal tracking height
                                                     )
{
m_ptMinTrackSize.x = nWidth;
m_ptMinTrackSize.y = nHeight;
}

//::IsModal()------------------------------------------------------------------
/*Returns TRUE if a modal property sheet has been created. In case of modeless
  property sheet, or if property sheet is not created yet, function returns FALSE.
 */
inline BOOL CPropertySheetResizable::IsModal() const
{
return !m_bModeless;
/*Note: If CPropertySheet is modeless, undocumented member m_bModeless is set;
  for modal CPropertySheet, member m_bModeless is FALSE. This member is used to
  determine mode of the property sheet. Another solution is to override
  CPropertySheet::DoModal() and set a new flag (for example m_bMyModal) before
  default processing. PSH_MODELESS flag from m_psh.dwFlags member could not be used,
  because default CPropertySheet::DoModal() enables this flag just before calling
  Create() and erases it after Create() returns.

    See MFC\Src\DlgProp.cpp\line:802
      int CPropertySheet::DoModal()
      {
      ...
    	// hook for creation of window
	    AfxHookWindowCreate(this);
	    psh->dwFlags |= PSH_MODELESS;   //Set modeless property sheet
	    m_nFlags |= WF_CONTINUEMODAL;
	    HWND hWnd = (HWND)::PropertySheet((PROPSHEETHEADER*)psh); //Create property sheet
      #ifdef _DEBUG
	    DWORD dwError = ::GetLastError();
      #endif
	    psh->dwFlags &= ~PSH_MODELESS;  //Set modal property sheet
    	AfxUnhookWindowCreate();
      ...
      }
  D.K.
*/
}

///////////////////////////////////////////////////////////////////////////////
// Helpers

//IsWizard()-------------------------------------------------------------------
/*Returns TRUE if CPropertySheet object is in Wizard mode.
 */
inline BOOL IsWizard(const CPropertySheet& cpSheet //property sheet object being examinated
                     )
{
return ((cpSheet.m_psh.dwFlags & (PSH_WIZARD | PSH_WIZARD97)) != 0);
}

//operator<<()-----------------------------------------------------------------

#ifdef _DEBUG
  #if _MFC_VER >= 0x600 //Name has been changed; See AfxDlgs.h(487) D.K.
    extern CDumpContext& AFXAPI operator << (CDumpContext& dc,AFX_OLDPROPSHEETHEADER const& pshSrc);
  #else
    extern CDumpContext& AFXAPI operator << (CDumpContext& dc,PROPSHEETHEADER const& pshSrc);
  #endif //_MFC_VER
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

///////////////////////////////////////////////////////////////////////////////
#endif // _KPROPSHR_H_
/*****************************************************************************
 * $Log: 
 *  6    Biblioteka1.5         04/04/2002 12:13:04 AMDarko           Documenation
 *       update
 *  5    Biblioteka1.4         24/01/2002 6:19:01 PMDarko           Updated
 *       comments
 *  4    Biblioteka1.3         19/08/2001 10:54:47 PMDarko           Butyfier
 *  3    Biblioteka1.2         11/07/2001 9:52:19 PMDarko           
 *  2    Biblioteka1.1         08/06/2001 10:51:28 PMDarko           VSS
 *  1    Biblioteka1.0         13/08/2000 2:57:10 PMDarko           
 * $
 *****************************************************************************/
