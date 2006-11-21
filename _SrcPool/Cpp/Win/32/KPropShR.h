/*KPropShR.h : header file
  $Revision: 7$ $Date: 2005-05-24 16:23:13$
  $Author: Darko Kolakovic$

  Handles resizing of the property sheet
  CommonSoft Inc.
  Mar. 2k Darko Kolakovic
 */

// Group=Windows

#ifndef _KPROPSHR_H_
    //$Workfile: KPropShR.h$ sentry
  #define _KPROPSHR_H_

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

#include "KDlgItLs.h" //CDlgItemResizableList class

/////////////////////////////////////////////////////////////////////////////
/*CPropertySheetResizable class handles the resizing of
  the property sheet and embedded controls.

  See also: Diagnostic operator<<(CDumpContext& dc,PROPSHEETHEADER const& pshSrc)

  Note: Microsoft Windows specific (Win),
        uses Microsoft Fundation Library (MFC).

  Example:
        Construct CMyPropertySheet;
        Create propery sheet window
          {
          OnCreate()
            {
            if window is modal
              Set resizing style for the window;
            };
          };
        Initialize CMyPropertySheet
          {
          OnInitDialog()
            {
            Enumerate all controls;
            Set resizing style for the controls;
            };
          };
        Change size
          {
          OnSize()
            {
            Change size and/or position of all controls;
            };
          };
 */
class CPropertySheetResizable : public CPropertySheet
{
  DECLARE_DYNAMIC(CPropertySheetResizable)

// Construction
public:
  CPropertySheetResizable();
  CPropertySheetResizable(UINT nIDCaption,
                          CWnd* pParentWnd = NULL,
                          UINT iSelectPage = 0);
  CPropertySheetResizable(LPCTSTR pszCaption,
                          CWnd* pParentWnd = NULL,
                          UINT iSelectPage = 0);

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
  If modaless property sheet is used, parent frame tracking size have to be
  limited.
 */
inline void CPropertySheetResizable::SetMinTrackSize(CRect rect //[in] minimal
                       //tracking rectangle, usually windows bounding rectangle
                       //obtained with GetwindowRect()
                                                     )
{
m_ptMinTrackSize.x = rect.Width();
m_ptMinTrackSize.y = rect.Height();
}

inline void CPropertySheetResizable::SetMinTrackSize(UINT nWidth, //[in] minimal
                                                             //tracking width
                                                     UINT nHeight //[in] minimal
                                                             //tracking height
                                                     )
{
m_ptMinTrackSize.x = nWidth;
m_ptMinTrackSize.y = nHeight;
}

//::IsModal()------------------------------------------------------------------
/*Verifies if property sheet is modal.

  Modal property sheets are topmost, dominant, forms that requires user's
  action if the process is going to proceed.

  Returns: TRUE if a modal property sheet has been created. In case of modeless
  property sheet, or if property sheet is not created yet, function returns FALSE.
 */
inline BOOL CPropertySheetResizable::IsModal() const
{
return !m_bModeless;
/*Note: If CPropertySheet is modeless, undocumented member m_bModeless is set;
  for modal CPropertySheet, member m_bModeless is FALSE. This member is used to
  determine mode of the property sheet. Another solution is to override
  CPropertySheet::DoModal() and set a new flag (for example m_bMyModal) before
  default processing. PSH_MODELESS flag from m_psh.dwFlags member could not be
  used, because default CPropertySheet::DoModal() enables this flag just before
  calling Create() and erases it after Create() returns.

    See MFC\Src\DlgProp.cpp\line:802
      int CPropertySheet::DoModal()
      {
      ...
      // hook for creation of window
      AfxHookWindowCreate(this);
      psh->dwFlags |= PSH_MODELESS;   //Set modeless property sheet
      m_nFlags |= WF_CONTINUEMODAL;
        //Create property sheet
      HWND hWnd = (HWND)::PropertySheet((PROPSHEETHEADER*)psh);
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
inline BOOL IsWizard(const CPropertySheet& cpSheet //[in] property sheet object
                                                   //being examinated
                     )
{
return ((cpSheet.m_psh.dwFlags & (PSH_WIZARD | PSH_WIZARD97)) != 0);
}

//operator<<()-----------------------------------------------------------------

#ifdef _DEBUG
  #if _MFC_VER >= 0x600 //Name has been changed; See AfxDlgs.h(487) D.K.
    extern CDumpContext& AFXAPI operator << (CDumpContext& dc,
                                             AFX_OLDPROPSHEETHEADER const& pshSrc);
  #else
    extern CDumpContext& AFXAPI operator << (CDumpContext& dc,
                                             PROPSHEETHEADER const& pshSrc);
  #endif //_MFC_VER
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

///////////////////////////////////////////////////////////////////////////////
#endif // _KPROPSHR_H_
/*****************************************************************************
 * $Log:
 *  6    Biblioteka1.5         2002-04-04 01:13:04  Darko           Documenation
 *       update
 *  5    Biblioteka1.4         2002-01-24 19:19:01  Darko           Updated
 *       comments
 *  4    Biblioteka1.3         2001-08-19 23:54:47  Darko           Butyfier
 *  3    Biblioteka1.2         2001-07-11 22:52:19  Darko
 *  2    Biblioteka1.1         2001-06-08 23:51:28  Darko           VSS
 *  1    Biblioteka1.0         2000-08-13 15:57:10  Darko
 * $
 *****************************************************************************/
