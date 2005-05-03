/*$Workfile: S:\_SrcPool\Cpp\Win\32\KCheckBox.h$: header file
  $Revision: 4$ $Date: 2005-04-26 16:42:08$
  $Author: Darko Kolakovic$

  Interface of the CCheckBox class
  Copyright: CommonSoft Inc
  2003-08-29 Darko Kolakovic
 */
// Group=Windows

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#include "KBtnEx.h" //CButtonEx class

///////////////////////////////////////////////////////////////////////////////
/*CCheckBox extends functionality of the MFC Button class.
  The CHECKBOX resource-definition statement creates a check box control.
  The control is a small rectangle (check box) that has the specified text
  displayed next to it (typically, to the right). When the user selects the
  control, the control highlights the rectangle and sends a message to its
  parent window.
  The STATE3 resource-definition statement defines a three-state check box
  control. The control is identical to a CHECKBOX, except that it has three
  states: checked, unchecked, and indeterminated (grayed).

  Note: uses Microsoft Foundation Library (MFC);
        Microsoft Windows specific (Win).
  */
class CCheckBox : public CButtonEx
{
  DECLARE_DYNAMIC(CCheckBox)

public:
  CCheckBox();
  virtual ~CCheckBox();
public:
  static const UINT BOX_SIZE;

  // Operations
public:
  bool IsCheckbox() const;
  bool IsTristate() const;
  bool IsChecked() const;
  bool IsIndeterminated() const;
  bool IsUnchecked() const;

protected:
  virtual void OnDraw(const UINT itemState);

protected:
  //{{AFX_MSG(CCheckBox)
  afx_msg LRESULT OnGetCheck (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnSetCheck (WPARAM wCheckState, LPARAM lParam);
  afx_msg void OnBnClicked();
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP()

public:
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Verifies if the control is a checkbox.

  Returns: true if the button has BS_CHECKBOX style; otherwise returns false.
 */
inline bool CCheckBox::IsCheckbox() const
{
return ( (GetButtonType() == BS_AUTOCHECKBOX) ||
         (GetButtonType() == BS_CHECKBOX) );
}

//-----------------------------------------------------------------------------
/*Verifies if the control is a tri-state checkbox.

  Returns: true if the button has BS_3STATE style; otherwise returns false.
 */
inline bool CCheckBox::IsTristate() const
{
return ( (GetButtonType() == BS_AUTO3STATE) ||
         (GetButtonType() == BS_3STATE) );
}

//-----------------------------------------------------------------------------
/*Verifies if the control's in checked state.
  This method determines if checkbox state is BST_CHECKED.

  Returns: true if the checkbox is in checked state; otherwise returns false.

  See also: winuser.h
 */
inline bool CCheckBox::IsChecked() const
{
return ((m_nState & BST_CHECKED) == BST_CHECKED);
}

//-----------------------------------------------------------------------------
/*Verifies if the control's in unchecked state.
  This method determines if checkbox state is BST_UNCHECKED.

  Returns: true if the checkbox is unchecked; otherwise returns false.

  See also: winuser.h
 */
inline bool CCheckBox::IsUnchecked() const
{
return (m_nState == BST_UNCHECKED);
}

//-----------------------------------------------------------------------------
/*Verifies if the control's in indeterminated state.
  This method determines if checkbox state is BST_INDETERMINATE. Only tri-state
  boxes could be in this state.

  Returns: true if the checkbox is in indeterminated state; otherwise returns
  false.

  See also: winuser.h
 */
inline bool CCheckBox::IsIndeterminated() const
{
return ((m_nState & BST_INDETERMINATE) == BST_INDETERMINATE);
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2003-09-02 17:20:10  Darko           Horizontal
 *       aligment
 *  1    Biblioteka1.0         2003-09-02 01:05:27  Darko
 * $
 *****************************************************************************/
