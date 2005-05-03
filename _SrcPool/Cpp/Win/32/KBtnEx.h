/*$Workfile: S:\_SrcPool\Cpp\Win\32\KBtnEx.h$: header file
  $Revision: 8$ $Date: 2005-04-26 11:28:24$
  $Author: Darko Kolakovic$

  Interface of the CButtonEx class
  Copyright: CommonSoft Inc
  Jan.97 Darko Kolakovic
 */
// Group=Windows

#ifndef _KBTNEXT_H_
  //$Workfile: S:\_SrcPool\Cpp\Win\32\KBtnEx.h$ sentry
  #define _KBTNEXT_H_

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif


#if _MSC_VER < 1310 //Compilers older than Microsoft Visual C/C++ .Net v7.1
                    //See also: winuser.h
  #ifndef BS_PUSHBOX
    #define BS_PUSHBOX          0x0000000AL
  #endif
  #ifndef BS_TYPEMASK
    #define BS_TYPEMASK         0x0000000FL
  #endif
#endif


///////////////////////////////////////////////////////////////////////////////
//CButtonEx extends functionality of the MFC Button class.
//
//Example:
//      //Dynamically subclass a button created from a dialog template
//      //and attach it to a CButtonEx object
//      class CAboutDlg : public CDialog
//      {
//      ...
//      public:
//        CButtonEx m_myButton;
//      };
//
//      BOOL CAboutDlg::OnInitDialog()
//      {
//      CDialog::OnInitDialog();
//      /*IDC_BTN_CUSTOM is the ID for a button on the dialog template used
//        for CAboutDlg.*/
//      m_myButton.SubclassDlgItem(IDC_BTN_CUSTOM, this);
//      /*When a button is dynamically subclassed, windows messages will route
//        through the CButtonEx's message map and call message handlers in
//        the CButtonEx's class first.*/
//      ...
//      return TRUE;
//      }
//
//Note: uses Microsoft Foundation Library (MFC);
//      Microsoft Windows specific (Win).
class CButtonEx : public CButton
{
// Construction
public:
  CButtonEx();
  virtual ~CButtonEx();

// Attributes
public:
  CRect m_rtSize;        //boundaries of the button
  BOOL  m_bMouseIn;      //flag 'pointer is on the button'
  COLORREF m_clrBtnText; //button text color
  COLORREF m_clrBtnFace; //button background color
  static const UINT BTN_STANDBY;
  static const UINT BTN_HOVER;
protected:
  int  m_iStyle;         //control's virtual style and type
  UINT m_nState;  //current state of the control: BST_UNCHECKED, BST_CHECKED,
                  //BST_INDETERMINATE

  // Operations
public:
  DECLARE_DYNAMIC(CButtonEx)

  void SetTextColor(COLORREF clrForeground, COLORREF clrBackground);
  bool IsDefPushButton() const;
  bool IsFlat() const;
  bool IsHoverStyle() const;
  bool IsSelected(const UINT itemState) const;
  bool IsFocused(const UINT itemState) const;
  bool IsDisabled(const UINT itemState) const;
  void SetButtonStyle(UINT nStyle, bool bRedraw = true);
  int  GetButtonType() const;
// Implementation
public:


// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CButtonEx)
  protected:
  virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
  virtual void PreSubclassWindow();
  virtual BOOL PreTranslateMessage(MSG* pMsg);
  //}}AFX_VIRTUAL
protected:
  virtual void OnDraw(const UINT itemState);

  // Generated message map functions
protected:
  //{{AFX_MSG(CButtonEx)
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg UINT OnGetDlgCode();
  afx_msg LRESULT OnSetStyle(WPARAM wParam, LPARAM lParam);

  //}}AFX_MSG

  DECLARE_MESSAGE_MAP()
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//::SetTextColor()-------------------------------------------------------------
/*Set button's backround and text color.
 */
inline void CButtonEx::SetTextColor(COLORREF clrForeground, //[in] text color
                                    COLORREF clrBackground  //[in] background
                                                            //color
                                    )
{
m_clrBtnText = clrForeground;
m_clrBtnFace = clrBackground;
}

//-----------------------------------------------------------------------------
/*Verifies if the button is the default button.

  Note: Windows framework changes button's style to BS_DEFPUSHBUTTON if control
  is selected. After changing the focus, the style would be reversed to
  BS_PUSHBUTTON.

  Returns: true if the button has BS_DEFPUSHBUTTON style; otherwise returns false.
 */
inline bool CButtonEx::IsDefPushButton() const
{
return ((m_iStyle & BTN_STANDBY) == BTN_STANDBY);
}

//-----------------------------------------------------------------------------
/*Verifies if the button has the flat style.

  Returns: true if the button has BS_FLAT style; otherwise returns false.
 */
inline bool CButtonEx::IsFlat() const
{
return ((m_iStyle & BS_FLAT) == BS_FLAT);
}

//-----------------------------------------------------------------------------
/*Verifies if the button has the hover style.

  Returns: true if the button has BS_FLAT style; otherwise returns false.
 */
inline bool CButtonEx::IsHoverStyle() const
{
return ((m_iStyle & BTN_HOVER) == BTN_HOVER);
}

//-----------------------------------------------------------------------------
/*Verifies if the button's status is selected.
  To validate visual state of the button control pass DRAWITEMSTRUCT::itemState
  structure member as the itemState parameter.

  Returns: true if the button is selected; otherwise returns false.
 */
inline bool CButtonEx::IsSelected(const UINT itemState //[in] visual state of
                                  //the control after the current drawing
                                  //action takes place
                                  ) const
{
return ((itemState & ODS_SELECTED) == ODS_SELECTED);
}

//-----------------------------------------------------------------------------
/*Verifies if the button has input focus.
  To validate visual state of the button control pass DRAWITEMSTRUCT::itemState
  structure member as the itemState parameter.

  Returns: true if the button has input focus; otherwise returns false.
 */
inline bool CButtonEx::IsFocused(const UINT itemState //[in] visual state of
                                  //the control after the current drawing
                                  //action takes place
                                 ) const
{
//TODO: Add masking bit m_MaskStyle to disable drawing focus rect in OnDraw()
return ((itemState & ODS_FOCUS) == ODS_FOCUS);
}

//-----------------------------------------------------------------------------
/*Verifies if the button has is disabled.
  To validate visual state of the button control pass DRAWITEMSTRUCT::itemState
  structure member as the itemState parameter.

  Returns: true if the button is to be drawn as disabled; otherwise returns false.
 */
inline bool CButtonEx::IsDisabled(const UINT itemState //[in] visual state of
                                  //the control after the current drawing
                                  //action takes place
                                  ) const
{
return ((itemState & ODS_DISABLED) == ODS_DISABLED);
}

//-----------------------------------------------------------------------------
/*Obtains control's virtual type. Button's actual type is set to BS_OWNERDRAW.

  Returns: one of the following values:

              BS_PUSHBUTTON       0x00
              BS_DEFPUSHBUTTON    0x01
              BS_CHECKBOX         0x02
              BS_AUTOCHECKBOX     0x03
              BS_RADIOBUTTON      0x04
              BS_3STATE           0x05
              BS_AUTO3STATE       0x06
              BS_GROUPBOX         0x07
              BS_USERBUTTON       0x08
              BS_AUTORADIOBUTTON  0x09
              BS_PUSHBOX          0x0A
              BS_OWNERDRAW        0x0B
              unknown             0xFE
 */
inline int CButtonEx::GetButtonType() const
{
return (m_iStyle & BS_TYPEMASK);
}

///////////////////////////////////////////////////////////////////////////////
#endif  //_KBTNEXT_H_
/*****************************************************************************
 * $Log:
 *  7    Biblioteka1.6         2003-09-02 01:06:20  Darko           pushlike
 *       checkbox handling
 *  6    Biblioteka1.5         2003-08-29 15:50:10  Darko           Fixed BTN_HOVER
 *  5    Biblioteka1.4         2003-08-29 08:51:09  Darko           focus handling
 *  4    Biblioteka1.3         2003-08-26 01:34:07  Darko
 *       IMPLEMENT_DYNAMIC
 *  3    Biblioteka1.2         2003-08-25 01:12:39  Darko           comments
 *  2    Biblioteka1.1         2003-08-24 14:17:42  Darko
 *  1    Biblioteka1.0         2003-08-24 14:02:45  Darko
 * $
 *****************************************************************************/
