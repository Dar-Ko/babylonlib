// TestView.cpp : implementation of the CTestView class
// $Revision: 2$  $Date: 09/07/2001 11:43:29 PM$
//
// Darko Kolakovic
// Jan. 2k


#include "stdafx.h"
#include "TestApp.h"

#include "TestDoc.h"
#include "TestView.h" //CTestView class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// Helper functions

//TsWriteToView()--------------------------------------------------------------
#include "MainFrm.h"  //CMainFrame class
/*Writes a character string at the View window
 */

BOOL TsWriteToView(LPCTSTR lszText)
{
CWnd* pFrame = AfxGetMainWnd();
ASSERT(pFrame != NULL);
ASSERT_VALID(pFrame);

if (pFrame != NULL)
  {
  ASSERT_KINDOF(CMainFrame, pFrame);
  ASSERT (pFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)));
  CView* pView = ((CMainFrame*)pFrame)->GetActiveView();
  if (pView != NULL)
    {
    ASSERT_KINDOF(CTestView, pView);
    ASSERT(pView->IsKindOf(RUNTIME_CLASS(CTestView)));
      //Append a string text at the end of the text
    return ((CTestView*)pView)->AppendText(lszText);
    }
  }
return FALSE;
}

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

CTestView::CTestView()
{
}

CTestView::~CTestView()
{
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
BOOL CTestView::AppendText(LPCTSTR lpszText //Text to append
                          )
{
if (lpszText == NULL)
  return FALSE;

CEdit& ctrlEdit = GetEditCtrl();//Get associated edit control
ctrlEdit.SetSel(-1, -1, TRUE);  //Find the end of the text
ctrlEdit.ReplaceSel(lpszText);  //Append new text
  
return TRUE;  
}

/////////////////////////////////////////////////////////////////////////////
// CTestView message handlers


//::OnLButtonDblClk()------------------------------------------------------
/*Test TPoint class
 */
void CTestView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
TestPoint(point);
CEditView::OnLButtonDblClk(nFlags, point);
}
