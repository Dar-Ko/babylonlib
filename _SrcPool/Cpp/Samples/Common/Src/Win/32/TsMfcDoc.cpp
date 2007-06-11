/*$Workfile: TsMfcDoc.cpp$: implementation file
  $Revision: 6$ $Date: 2007-06-11 17:00:41$
  $Author: Darko Kolakovic$

  Defines the class behaviors for the application.

  Copyright: CommonSoft Inc.
  Jan. 2k Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#include "TsMfcApp.h"

#include "TsMfcDoc.h"

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestDoc

IMPLEMENT_DYNCREATE(CTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestDoc, CDocument)
  //{{AFX_MSG_MAP(CTestDoc)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDoc construction/destruction

CTestDoc::CTestDoc()
{
}

CTestDoc::~CTestDoc()
{
}


/////////////////////////////////////////////////////////////////////////////
// CTestDoc serialization

//::Serialize()----------------------------------------------------------------
/*Reads or writes text from or to associated edit control.
 */
void CTestDoc::Serialize(CArchive& ar)
{
CEditView* pView = (CEditView*)m_viewList.GetHead();
ASSERT(pView->IsKindOf(RUNTIME_CLASS(CEditView)));
  //Read or write the text in the CEditView object to a text file
pView->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CTestDoc diagnostics

#ifdef _DEBUG
void CTestDoc::AssertValid() const
{
  CDocument::AssertValid();
}

void CTestDoc::Dump(CDumpContext& dc) const
{
  CDocument::Dump(dc);
}
#endif //_DEBUG


//::SetText()------------------------------------------------------------------
/*Sets text within the associated edit control.
 */
BOOL CTestDoc::SetText(LPCTSTR lpszText)
{
CEditView* pView = (CEditView*)m_viewList.GetHead();
ASSERT(pView->IsKindOf(RUNTIME_CLASS(CEditView)));
pView->GetEditCtrl().SetWindowText(lpszText);
pView->GetEditCtrl().SetSel(-1, -1);    //Move caret at the end
pView->Invalidate();
return TRUE;
}

//::AppendText()------------------------------------------------------------------
#include "TsMfcView.h" //CTestView class
/*Appends text within the associated edit control.
 */
BOOL CTestDoc::AppendText(LPCTSTR lpszText)
{
CEditView* pView = (CEditView*)m_viewList.GetHead();
ASSERT(pView->IsKindOf(RUNTIME_CLASS(CTestView)));
if(!((CTestView*)pView)->AppendText(lpszText))
  return FALSE;
pView->Invalidate();
return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CTestDoc commands

//::OnNewDocument() -----------------------------------------------------------
/*Called by the framework as part of the File New command. The default
  implementation of this function calls the DeleteContents member function to
  ensure that the document is empty and then marks the new document as clean.
 */
BOOL CTestDoc::OnNewDocument()
{
if (!CDocument::OnNewDocument())
  return FALSE;


CString strTitle;
strTitle.LoadString(AFX_IDS_APP_TITLE);
  //Set document's title
SetTitle((LPCTSTR)strTitle);
  //Display a title
strTitle += _T("\r\n");           //CRLF
AppendText((LPCTSTR)strTitle);

return TRUE;
}
