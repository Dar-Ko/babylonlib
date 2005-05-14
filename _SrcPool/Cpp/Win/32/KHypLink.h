/*$Workfile: KHypLink.h$: header file
  $Revision: 12$ $Date: 2005-05-03 01:46:18$
  $Author: Darko$

  HyperLink static control
  Chris Maunder, 1997
  D. Kolakovic  May 98 improved
 */
// Group=Windows

#ifndef _KHYPLINK_H_
    //$Workfile: KHypLink.h$ sentry
  #define _KHYPLINK_H_

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

//CHyperLink outlook styles
enum HLNK_STYLE
     {
     HLNK_UNDERLINE =   1, //underline text
     HLNK_AUTOFIT   =   2, //adjust size to fit text
     };

/////////////////////////////////////////////////////////////////////////////
//CHyperLink control activates a hyperlink encoded as a URL.
//Use SetStyle() to change appreance of the hyperlink text.
//
//
//Example:
//     #include "KHypLink.h" //CHyperLink class
//     class CMyDlg : public CDialog
//       {
//       ...
//       public:
//         // Dialog Data
//         CHyperLink    m_chlURL;
//       protected:
//         virtual BOOL OnInitDialog();
//         ...
//       };
//     BOOL CMyDlg::OnInitDialog()
//       {
//       CDialog::OnInitDialog();
//       ...
//       CString strUrl = _T("http://www.Jump.com");
//       m_chlURL.SetUrl(strUrl); //Set URL link
//       return TRUE;
//       }
//     void CMyDlg::DoDataExchange(CDataExchange* pDX)
//       {
//       CDialog::DoDataExchange(pDX);
//       DDX_Control(pDX, IDC_HYPERLINK, m_chlURL);
//       }
//
//History: Chris Maunder, 1997
//
//Note: uses Microsoft Foundation Library (MFC); 
//      Microsoft Windows specific (Win).
class CHyperLink : public CStatic
{
  // Construction
public:
  CHyperLink(bool bAutoDelete = false);
  virtual ~CHyperLink();

// Attributes
protected:
  DWORD    m_dwStyle;               //Control's style
  COLORREF m_crTextColor;           //text color
  COLORREF m_crAccessed;            //'URL accessed' color
  COLORREF m_crInFocus;             //'Control is in Focus' color
  bool     m_bInFocus;              //flag 'In Focus'
  bool     m_bAccessed;             //flag 'URL has been accessed'
  CString  m_strURL;                //hyperlink URL
  CFont    m_Font;                  //default font
  HCURSOR  m_hCursor;               //default cursor
  CToolTipCtrl m_ToolTip;           //control's tooltip
  bool     m_bAutoDelete;           //Self-destruction flag

  // Operations
public:

  void     SetUrl(CString& strUrl);
  CString  GetUrl() const;
  void     SetColors(COLORREF crTextColor, COLORREF crAccessed, COLORREF crInFocus = -1);
  COLORREF GetTextColor() const;
  COLORREF GetAccessedColor() const;
  COLORREF GetFocusColor() const;
  void     SetAccessed(bool bAccessed = true);
  bool     IsAccessed() const;
  void     SetDefCursor(HCURSOR hCursor);
  HCURSOR  GetDefCursor() const;
  void SetStyle(DWORD dwNewStyle =HLNK_UNDERLINE|HLNK_AUTOFIT );
  bool IsUnderline() const;
  bool IsAutoFit() const;

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CHyperLink)
  public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
  protected:
    virtual void PreSubclassWindow();
  virtual void PostNcDestroy();
  //}}AFX_VIRTUAL

// Implementation
protected:
  void ReportError(int nError);
  void PositionWindow();
  void SetDefaultCursor();
  friend int SpawnURL(LPCTSTR szURL,int nCmdShow);

  // Generated message map functions
protected:
  //{{AFX_MSG(CHyperLink)
    afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg UINT OnNcHitTest(CPoint point);
  //}}AFX_MSG
  afx_msg void OnClicked();
  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// Inlines

//::GetUrl()-------------------------------------------------------------------
/*Returns a hyperlink is encoded as a URL.
 */
inline CString CHyperLink::GetUrl() const
{
return m_strURL;
}

//::IsUnderline()----------------------------------------------------
/*Returns TRUE if Underline style is enabled.
 */
inline bool CHyperLink::IsUnderline() const
{
return ((m_dwStyle &  HLNK_UNDERLINE) == HLNK_UNDERLINE);
}

//::IsAutoFit()----------------------------------------------------------------
/*Returns TRUE if AutoFit style is enabled.
 */
inline bool CHyperLink::IsAutoFit() const
{
return ((m_dwStyle &  HLNK_AUTOFIT) == HLNK_AUTOFIT);
}

//::IsAccessed()---------------------------------------------------------------
/*Returns TRUE if URL has been accessed.
 */
inline bool CHyperLink::IsAccessed() const
{
return m_bAccessed;
}

//::GetCursor()----------------------------------------------------------------
/*Returns a handle to the default cursor, or NULL if no cursor has
  been set.
 */
inline HCURSOR CHyperLink::GetDefCursor() const
{
return m_hCursor;
}

//::GetFocusColor()------------------------------------------------------------
/*Returns 'Control is in Focus' color.
 */
inline COLORREF CHyperLink::GetFocusColor() const
{
return m_crInFocus;
}

//::GetTextColor()------------------------------------------------------------
/*Retrieves the text color of a hyperlink control.
 */
inline COLORREF CHyperLink::GetTextColor() const
{
return m_crTextColor;
}

//::GetAccessedColor()---------------------------------------------------------
/*Retrieves the text color of a accessed hyperlink control.
 */
inline COLORREF CHyperLink::GetAccessedColor() const
{
return m_crAccessed;
}

//::SetAccessed()--------------------------------------------------------------
/*Changes the state of the hyperlink control to accessed or unaccessed.
 */
inline void CHyperLink::SetAccessed(bool bAccessed //[in]= true new state of 
                                    //the hyperlink
                                    )
{
m_bAccessed = bAccessed;
if (::IsWindow(GetSafeHwnd()))
  Invalidate();
}

///////////////////////////////////////////////////////////////////////////////
#endif // _KHYPLINK_H_
/*****************************************************************************
 * $Log: 
 *  12   Biblioteka1.11        2005-05-03 01:46:18  Darko           comments, case
 *       of included files
 *  11   Biblioteka1.10        2005-04-26 11:29:53  Darko Kolakovic Document groups
 *       and typo fixes
 *  10   Biblioteka1.9         2005-03-21 03:16:47  Darko           comments
 *  9    Biblioteka1.8         2003-11-03 13:20:07  Darko           Replaced BOOL
 *       with bool
 *  8    Biblioteka1.7         2003-08-13 17:40:49  Darko           formatting
 *  7    Biblioteka1.6         2003-08-06 03:46:39  Darko           Prepared for
 *       Unicode 
 *  6    Biblioteka1.5         2003-08-05 23:16:40  Darko           Added notes
 *  5    Biblioteka1.4         2002-01-25 16:57:10  Darko           Updated
 *       comments
 *  4    Biblioteka1.3         2001-08-17 00:37:37  Darko           Update
 *  3    Biblioteka1.2         2001-07-07 01:09:59  Darko           Example
 *  2    Biblioteka1.1         2001-06-08 23:50:56  Darko           VSS
 *  1    Biblioteka1.0         2000-08-13 15:56:40  Darko           
 * $
 *****************************************************************************/
