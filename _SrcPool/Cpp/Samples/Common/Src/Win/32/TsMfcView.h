/*$Workfile: TsMfcView.h$: header file
  $Revision: 5$ $Date: 2007-06-11 17:00:38$
  $Author: Darko Kolakovic$

  Interface of the document's view

  Darko Kolakovic Jan. 2k Compiled with MSVC++ 4.0
*/

// Group=Examples

#ifndef _TSMFCVIEW_H_
  //$Workfile: TsMfcView.h$ sentry
  #define _TSMFCVIEW_H_


/////////////////////////////////////////////////////////////////////////////
/*Interface of the CTestView class.

  Note: Microsoft Windows specific (Win32) 
        and uses Microsoft Foundation Library (MFC).
 */
class CTestView : public CEditView
{
protected: // create from serialization only
  CTestView();
  DECLARE_DYNCREATE(CTestView)

// Attributes
public:
  CTestDoc* GetDocument();

// Operations
public:
  bool AppendText(LPCTSTR lpszText);
// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CTestView)
  public:
  virtual void OnDraw(CDC* pDC);  // overridden to draw this view
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
  protected:
  //}}AFX_VIRTUAL

// Implementation
public:
  virtual ~CTestView();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
  //{{AFX_MSG(CTestView)
  afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

////////////////////////////////////////////////////////////////////////////////

#ifndef _DEBUG  // debug version in TestView.cpp
inline CTestDoc* CTestView::GetDocument()
  { 
  return (CTestDoc*)m_pDocument; 
  }
#endif

#endif //_TSMFCVIEW_H_
////////////////////////////////////////////////////////////////////////////////
/*
  $Log: 
   5    Biblioteka1.4         2007-06-11 17:00:38  Darko Kolakovic Windows MFC
        application
   4    Biblioteka1.3         2007-06-11 16:06:19  Darko Kolakovic 
   3    Biblioteka1.2         2007-05-24 11:51:38  Darko Kolakovic Formatting
   2    Biblioteka1.1         2001-07-11 22:36:58  Darko           
   1    Biblioteka1.0         2001-06-08 22:43:57  Darko           
  $
 */

