/*$Workfile: KHypLink.h$: header file
  $Revision: 1.1 $ $Date: 2002/09/06 22:16:05 $
  $Author: ddarko $

  HyperLink static control
  Chris Maunder, 1997
  D. Kolakovic  May 98 improved
 */
#ifndef _KHYPLINK_H_
    //KHypLink.k sentry
  #define _KHYPLINK_H_

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

//CHyperLink styles
enum HLNK_STYLE
     {
     HLNK_UNDERLINE =   1, //underline text
     HLNK_AUTOFIT   =   2, //adjust size to fit text
     };

/////////////////////////////////////////////////////////////////////////////
// CHyperLink control activates a hyperlink encoded as a URL.
// Use SetStyle() to change appreance of the hyperlink text.
//
// Note: uses Microsoft Fundation Library (MFC).
//
// Example:
//      #include "KHypLink.h" //CHyperLink class
//      class CMyDlg : public CDialog
//        {
//        ...
//        public:
//          // Dialog Data
//          CHyperLink    m_chlURL;
//        protected:
//          virtual BOOL OnInitDialog();
//          ...
//        };
//      BOOL CMyDlg::OnInitDialog()
//        {
//        CDialog::OnInitDialog();
//        ...
//        CString strURL = _T("http://www.Jump.com");
//        m_chlURL.SetURL(strURL); //Set URL link
//        return TRUE;
//        }
//      void CMyDlg::DoDataExchange(CDataExchange* pDX)
//        {
//        CDialog::DoDataExchange(pDX);
//        DDX_Control(pDX, IDC_HYPERLINK, m_chlURL);
//        }
//
// History: Chris Maunder, 1997
class CHyperLink : public CStatic
{
  // Construction
public:
    CHyperLink(BOOL bAutoDelete = FALSE);
    virtual ~CHyperLink();

// Attributes
protected:
    DWORD    m_dwStyle;               //Control's style
    COLORREF m_crTextColor;           //text color
    COLORREF m_crDone;                //'URL accessed' color
    COLORREF m_crInFocus;             //'Control is in Focus' color
    BOOL     m_bInFocus;              //flag 'In Focus'
    BOOL     m_bDone;                 //flag 'URL has been accessed'
    CString  m_strURL;                //hyperlink URL
    CFont    m_Font;                  //default font
    HCURSOR  m_hCursor;               //default cursor
    CToolTipCtrl m_ToolTip;           //control's tooltip
    BOOL     m_bAutoDelete;           //Self-destruction flag
// Operations
public:

    void     SetURL(CString& strURL);
    CString  GetURL() const;
    void     SetColors(COLORREF crTextColor, COLORREF crDone, COLORREF crInFocus = -1);
    COLORREF GetTextColor() const;
    COLORREF GetAccessedColor() const;
    COLORREF GetFocusColor() const;
    void     SetAccessed(BOOL bVisited = TRUE);
    BOOL     IsAccessed() const;
    void     SetDefCursor(HCURSOR hCursor);
    HCURSOR  GetDefCursor() const;
    void SetStyle(DWORD dwNewStyle =HLNK_UNDERLINE|HLNK_AUTOFIT );
    BOOL IsUnderline() const;
    BOOL IsAutoFit() const;

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
    friend HINSTANCE SpawnURL(LPCTSTR szURL,int nCmdShow);

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

//::GetURL()-------------------------------------------------------------------
/*Returns a hyperlink is encoded as a URL.
 */
inline CString CHyperLink::GetURL() const
{
return m_strURL;
}

//::IsUnderline()----------------------------------------------------
/*Returns TRUE if Underline style is enabled.
 */
inline BOOL CHyperLink::IsUnderline() const
{
return (((m_dwStyle &  HLNK_UNDERLINE) == HLNK_UNDERLINE) ? TRUE: FALSE);
}

//::IsAutoFit()----------------------------------------------------------------
/*Returns TRUE if AutoFit style is enabled.
 */
inline BOOL CHyperLink::IsAutoFit() const
{
return (((m_dwStyle &  HLNK_AUTOFIT) == HLNK_AUTOFIT) ? TRUE: FALSE);
}

//::IsAccessed()---------------------------------------------------------------
/*Returns TRUE if URL has been accessed.
 */
inline BOOL CHyperLink::IsAccessed() const
{
return m_bDone;
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
return m_crDone;
}

//::SetAccessed()--------------------------------------------------------------
/*Marks a hyperlink control as accessed.
 */
inline void CHyperLink::SetAccessed(BOOL bDone //= TRUE
                                    )
{
m_bDone = bDone;
if (::IsWindow(GetSafeHwnd()))
  Invalidate();
}

///////////////////////////////////////////////////////////////////////////////
#endif // _KHYPLINK_H_
/*****************************************************************************
 * $Log: 
 *  5    Biblioteka1.4         1/25/02 3:57:10 PM   Darko           Updated
 *       comments
 *  4    Biblioteka1.3         8/16/01 11:37:37 PM  Darko           Update
 *  3    Biblioteka1.2         7/7/01 12:09:59 AM   Darko           Example
 *  2    Biblioteka1.1         6/8/01 10:50:56 PM   Darko           VSS
 *  1    Biblioteka1.0         8/13/00 2:56:40 PM   Darko           
 * $
 *****************************************************************************/
