/*$Workfile: KDlgRsiz.h$: header file
  $Revision: 7$ $Date: 2003-09-22 21:26:03$
  $Author: Darko$

  Handles resizing of the dialog box
  Copyright: CommonSoft Inc
  Mar. 2k Darko Kolakovic
 */ 

#ifndef _KDLGRSIZ_H_
    //KDlgRsiz.h sentry
  #define _KDLGRSIZ_H_

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

#include "KDlgItLs.h" //CDlgItemResizableList class

#define CDLGRESIZABLE_GRIP      0x1 //enable sizing grip (high word)
#define CDLGRESIZABLE_STOREPOS  0x2 //enable storing/loading placement (high word)

/////////////////////////////////////////////////////////////////////////////
// CDialogResizable class handles the resizing of the dialog box and embedded
// controls.
//
// Note: uses Microsoft Fundation Library (MFC).
class CDialogResizable : public CDialog
{
// Construction
public:
  CDialogResizable(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
  CDialogResizable(UINT nIDTemplate, CWnd* pParentWnd = NULL);

// Dialog Data
protected:
  CDlgItemResizableList m_arrControlList; //a list of the embedded controls.
  CPoint  m_ptMinTrackSize; //the minimum tracking width and height
private:
  BOOL m_bModeless;    //flag 'Modeless/Modal Dialog'. TRUE if dialog is modeless.
  DWORD m_dwDlgStyle;  //specifies different modes

  //{{AFX_DATA(CDialogResizable)
    // NOTE: the ClassWizard will add data members here
  //}}AFX_DATA
// Operations
public:
  void EnableSizingGrip(BOOL bVisible = TRUE);
  void EnablePlacement(BOOL bEnable = TRUE);
  void SetMinTrackSize(CRect rect);
  void SetMinTrackSize(UINT nWidth, UINT nHeight);
  BOOL IsGripEnabled() const;
  BOOL IsPlacementEnabled() const;
  BOOL RestorePlacement(LPCTSTR lpszSection = NULL, LPCTSTR lpszEntry = NULL);
  int  EnumerateControls(const CDlgItemResizable::RESIZING_TYPE& Type);
// Overrides
protected:
  virtual BOOL LoadSettings(LPCTSTR lpszSection = NULL, LPCTSTR lpszEntry = NULL);
  virtual BOOL SaveSettings(LPCTSTR lpszSection = NULL, LPCTSTR lpszEntry = NULL);
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CDialogResizable)
  public:
  virtual int DoModal();
  //}}AFX_VIRTUAL

// Implementation
protected:
  BOOL IsModal() const;
  void GetGripSize(CSize& size) const;
  void DrawGripper(CDC* pDC, CRect& rect) const;

  // Generated message map functions
  //{{AFX_MSG(CDialogResizable)
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnPaint();
  afx_msg UINT OnNcHitTest(CPoint point);
  virtual BOOL OnInitDialog();
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
  afx_msg void OnDestroy();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//::IsModal()------------------------------------------------------------------
/*Returns TRUE if a modal dialog has been created. In case of modeless 
  dialog, or if dialog box is not created yet, function returns FALSE.
 */
inline BOOL CDialogResizable::IsModal() const
{
return !m_bModeless;
}

//::IsGripEnabled()------------------------------------------------------------
/*Returns TRUE if sizing grip is enabled.
 */
inline BOOL CDialogResizable::IsGripEnabled() const
{
return ((HIWORD(m_dwDlgStyle) & CDLGRESIZABLE_GRIP) == CDLGRESIZABLE_GRIP);
}

//::IsPlacementEnabled()-------------------------------------------------------
/*Returns TRUE if storing /loading of dialog's placement is enabled.
 */
inline BOOL CDialogResizable::IsPlacementEnabled() const
{
return ((HIWORD(m_dwDlgStyle) & CDLGRESIZABLE_STOREPOS) == CDLGRESIZABLE_STOREPOS);
}

//::GetGripSize()--------------------------------------------------------------
/*Returns dimensions of the sizing grip rectangle, that can be used to resize 
  the dialog.
 */
inline void CDialogResizable::GetGripSize(CSize& size //sizing grip dimensions
                                          ) const
{
size.cx = ::GetSystemMetrics(SM_CXHSCROLL);
size.cy = ::GetSystemMetrics(SM_CYVSCROLL);
}

//::DrawGripper()--------------------------------------------------------------
/*Draws the sizing grip rectangle, that can be used to resize 
  the dialog.
*/
inline void CDialogResizable::DrawGripper(CDC* pDC,  //device-context of the sizing 
                                                     //grip being drawn
                                          CRect& rect//sizing grip rectangle
                                          ) const
{
ASSERT_VALID(this);
ASSERT_VALID(pDC);
  //Only draw the gripper if it is specified
if (IsGripEnabled())
  {
  CSize sizeGrip;
  GetGripSize(sizeGrip);
  rect.TopLeft() = rect.BottomRight() - sizeGrip;
  pDC->DrawFrameControl(rect,DFC_SCROLL, LOWORD(m_dwDlgStyle));
  }
}

//:EnableSizingGrip()----------------------------------------------------------
/*Enables or disables the sizing grip used to resize the dialog.
 */
inline void CDialogResizable::EnableSizingGrip(BOOL bVisible//=TRUE If TRUE, enables
                                                            //sizing grip
                                              )
{
/*Note: frame styles
  DFCS_SCROLLSIZEGRIP      0x0008 Size grip in bottom-right corner of window.
  DFCS_SCROLLSIZEGRIPRIGHT 0x0010 Size grip in bottom-left corner of window. 
*/
UINT nHiWord = HIWORD(m_dwDlgStyle);
if (bVisible)
  nHiWord |= CDLGRESIZABLE_GRIP;
else
  nHiWord &= ~CDLGRESIZABLE_GRIP;

if(::IsWindow(m_hWnd))
  m_dwDlgStyle = MAKELONG(((GetExStyle() & WS_EX_LAYOUTRTL) ? DFCS_SCROLLSIZEGRIPRIGHT : 
                                                               DFCS_SCROLLSIZEGRIP),
                            nHiWord);
else //Adjust style after dialog creation
  m_dwDlgStyle = MAKELONG(DFCS_SCROLLSIZEGRIP, nHiWord);
}

//::EnablePlacement()----------------------------------------------------------
/*Enables or disables storing and loading the show state and the normal, 
  minimized, and maximized positions of the dialog.

  Example:
    #include "KDlgRsiz.h" //CDialogResizable class
    class CMyDialog : public CDialogResizable
      {
      ...
      };
    void MyFunc()
      {
      CMyDialog dlg;
      dlg.EnablePlacement();
      dlg.DoModal();
      }
    BOOL  CMyDialog::OnInitDialog() 
      {
      BOOL  bResult = CDialogResizable::OnInitDialog();
        //Load position and size from profile.
      if (IsPlacementEnabled())
        {
        //Note: m_arrControlList  have to be initialized.
        //Only elements from m_arrControlList  would be resized.
        LoadSettings();
        }
      return bResult;
      } 
 */
inline void CDialogResizable::EnablePlacement(BOOL bEnable//=TRUE enable or disable placement loading 
                                              )
{
UINT nHiWord = HIWORD(m_dwDlgStyle);
if (bEnable)
  nHiWord |= CDLGRESIZABLE_STOREPOS;
else
  nHiWord &= ~CDLGRESIZABLE_STOREPOS;
m_dwDlgStyle = MAKELONG(LOWORD(m_dwDlgStyle), nHiWord);
}

//::SetMinTrackSize()----------------------------------------------------------
/*Specifies the minimum tracking width and the minimum tracking 
  height of the window. Size limit is used in handling the Windows message 
  WM_GETMINMAXINFO. 
  If modeless property sheet is used, parent frame tracking size have to be limited.
 */
inline void CDialogResizable::SetMinTrackSize(CRect rect //minimal tracking rectangle, usually
                                                                //windows bounding rectangle
                                                                //obtained with GetWindowRect()
                                             )
{
m_ptMinTrackSize.x = rect.Width();
m_ptMinTrackSize.y = rect.Height();
}

inline void CDialogResizable::SetMinTrackSize(UINT nWidth, //minimal tracking width 
                                              UINT nHeight //minimal tracking height
                                             )
{
m_ptMinTrackSize.x = nWidth;
m_ptMinTrackSize.y = nHeight;
}


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

///////////////////////////////////////////////////////////////////////////////
#endif // _KDLGRSIZ_H_
/*****************************************************************************
 * $Log: 
 *  7    Biblioteka1.6         2003-09-22 21:26:03  Darko           formatting
 *  6    Biblioteka1.5         2002-01-29 22:20:46  Darko           Used lbraries
 *       notes 
 *  5    Biblioteka1.4         2002-01-25 15:56:54  Darko           Updated
 *       comments
 *  4    Biblioteka1.3         2001-07-19 23:53:32  Darko           Comments
 *  3    Biblioteka1.2         2001-07-11 21:51:10  Darko           
 *  2    Biblioteka1.1         2001-06-08 22:50:29  Darko           VSS
 *  1    Biblioteka1.0         2000-08-13 14:56:16  Darko           
 * $
 *****************************************************************************/
