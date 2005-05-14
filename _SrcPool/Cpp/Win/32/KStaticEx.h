/*$Workfile: KStaticEx.h$: header file
  $Revision: 2$ $Date: 2005-05-05 17:24:48$
  $Author: Darko Kolakovic$

  Colored text labels
  Copyright: CommonSoft Inc
  2001-07-06 Darko Kolakovic
 */
/* Group=Windows*/

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
  #pragma once
#endif

#ifndef _KSTATICEX_H_
    //$Workfile: KStaticEx.h$ sentry
  #define _KSTATICEX_H_

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif


///////////////////////////////////////////////////////////////////////////////
/*CStaticEx class displays a text label.
  A static control normally takes no input and provides no output.
  Base class also displays box, rectangle, icon, cursor, bitmap or enhanced
  metafile.

  Note: uses Microsoft Foundation Library (MFC);
        Microsoft Windows specific (Win).

  See also: CStatic
 */
class CStaticEx: public CStatic
{
public:

  CStaticEx();
  CStaticEx(const CStaticEx& dtValue);

  virtual ~CStaticEx();

// Attributes
public:
  COLORREF m_clrText;   //text color
  COLORREF m_clrBkFace; //control's background color

  // Operations
public:
  DECLARE_DYNCREATE(CStaticEx)
  void SetTextColor(COLORREF clrForeground, COLORREF clrBackground);
  bool IsDisabled(const UINT itemState) const;

// Overrides
protected:
  //{{AFX_VIRTUAL(CStaticEx)
  virtual void PreSubclassWindow();
  virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
  //}}AFX_VIRTUAL
  //void  DrawText(CDC* pDC, CRect* pRect, CString strText);
  virtual void OnDraw(const UINT itemState);

  // Generated message map functions
protected:
  //{{AFX_MSG(CStaticEx)
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Verifies if the control has is disabled.
  To validate visual state of the control pass DRAWITEMSTRUCT::itemState
  structure member as the itemState parameter.

  Returns: true if the button is to be drawn as disabled; otherwise returns false.
 */
inline bool CStaticEx::IsDisabled(const UINT itemState //[in] visual state of
                                  //the control after the current drawing
                                  //action takes place
                                  ) const
{
return ((itemState & ODS_DISABLED) == ODS_DISABLED);
}

///////////////////////////////////////////////////////////////////////////////
#endif  //_KSTATICEX_H_
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2005-05-04 09:29:51  Darko Kolakovic
 * $
 *****************************************************************************/
