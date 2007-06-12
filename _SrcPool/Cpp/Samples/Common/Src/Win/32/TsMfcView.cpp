/*$Workfile: TsMfcView.cpp$: implementation file
  $Revision: 6$ $Date: 2007-06-12 17:14:13$
  $Author: Darko Kolakovic$

  Defines the class behaviors for the application.

  Copyright: CommonSoft Inc.
  Jan. 2k Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#include "TsMfcApp.h"

#include "TsMfcDoc.h"
#include "TsMfcView.h" //CTestView class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestView

IMPLEMENT_DYNCREATE(CTestView, CEditView)

BEGIN_MESSAGE_MAP(CTestView, CEditView)
  //{{AFX_MSG_MAP(CTestView)
  ON_WM_LBUTTONDBLCLK()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestView construction/destruction

CTestView::CTestView() : m_PointTest(NULL)

{
}

CTestView::~CTestView()
{
m_PointTest = NULL;
}

//::PreCreateWindow()----------------------------------------------------------
/*Called by the framework before the creation of the Windows window attached to
  this CWnd object.
  Any combination of edit styles could be applied:

    ES_AUTOHSCROLL   Automatically scrolls text to the right by 10 characters
    ES_AUTOVSCROLL   Automatically scrolls text up one page when the user presses ENTER
    ES_CENTER   Centers text in a multiline edit control.
    ES_LEFT   Aligns text flush left.
    ES_LOWERCASE   Converts all characters to lowercase as they are typed into the edit control.
    ES_MULTILINE   Designates a multiple-line edit control.
    ES_NOHIDESEL   Make selection when the control loses the input focus visible
    ES_OEMCONVERT   Text entered in the edit control is converted from the ANSI to the OEM
    ES_PASSWORD   Displays all characters as an asterisk (*) as they are typed
    ES_RIGHT   Aligns text flush right in a multiline edit control.
    ES_UPPERCASE   Converts all characters to uppercase as they are typed into the edit control.
    ES_READONLY   Prevents the user from entering or editing text in the edit control.
    ES_WANTRETURN   Specifies that a carriage return be inserted when the user presses the ENTER key

 */
BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
BOOL bRes = CEditView::PreCreateWindow(cs);
cs.style = AFX_WS_DEFAULT_VIEW |
           WS_VSCROLL     |
           ES_AUTOHSCROLL |
           ES_AUTOVSCROLL |
           ES_MULTILINE   |
           ES_READONLY    |
           ES_NOHIDESEL;
return bRes;
}

/////////////////////////////////////////////////////////////////////////////
// CTestView drawing

//::OnDraw()-------------------------------------------------------------------
/*Called by the framework to render an image of the document. The framework calls
  this function to perform screen display, printing, and print preview, and it
  passes a different device context in each case.
 */
void CTestView::OnDraw(CDC* )
{
CTestDoc* pDoc = GetDocument();
ASSERT_VALID(pDoc);
}



/////////////////////////////////////////////////////////////////////////////
// CTestView diagnostics

#ifdef _DEBUG
void CTestView::AssertValid() const
{
  CEditView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
  CEditView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() // non-debug version is inline
{
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
  return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG

///////////////////////////////////////////////////////////////////////////////
// Operations

//::AppendText()---------------------------------------------------------------
/*Appends new text and scrolls the viewport to make it visible
 */
bool CTestView::AppendText(LPCTSTR lpszText //[in] text to append
                          )
{
if (lpszText == NULL)
  return false;

CEdit& ctrlEdit = GetEditCtrl();//Get associated edit control
ctrlEdit.SetSel(-1, -1, TRUE);  //Find the end of the text
ctrlEdit.ReplaceSel(lpszText);  //Append new text

return true;
}

/////////////////////////////////////////////////////////////////////////////
// CTestView message handlers


//::OnLButtonDblClk()------------------------------------------------------
/*Invokes point test method.
 */
void CTestView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
//Note: use point in your test cases
if (m_PointTest != NULL)
  m_PointTest(point);

CEditView::OnLButtonDblClk(nFlags, point);
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  6    Biblioteka1.5         2007-06-12 17:14:13  Darko Kolakovic Moved out
 *       TsWriteToView()
 *  5    Biblioteka1.4         2007-06-11 17:00:36  Darko Kolakovic Windows MFC
 *       application
 *  4    Biblioteka1.3         2007-06-11 16:06:08  Darko Kolakovic 
 *  3    Biblioteka1.2         2007-05-24 11:51:37  Darko Kolakovic Formatting
 *  2    Biblioteka1.1         2001-07-10 00:43:29  Darko          
 *       TestQuadraticEquation()
 *  1    Biblioteka1.0         2001-06-08 22:43:56  Darko           
 * $
 *****************************************************************************/
