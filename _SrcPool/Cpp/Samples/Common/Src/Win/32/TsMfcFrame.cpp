/*$Workfile: TsMfcFrame.cpp$: implementation file
  $Revision: 5$ $Date: 2007-06-11 17:00:28$
  $Author: Darko Kolakovic$

  Defines the class behaviors for the application.

  Copyright: CommonSoft Inc.
  Jan. 2k Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#include "TsMfcApp.h"

#include "TsMfcFrame.h"

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestMainFrame

IMPLEMENT_DYNCREATE(CTestMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CTestMainFrame, CFrameWnd)
  //{{AFX_MSG_MAP(CTestMainFrame)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestMainFrame construction/destruction

CTestMainFrame::CTestMainFrame()
{
}

CTestMainFrame::~CTestMainFrame()
{
}

BOOL CTestMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestMainFrame diagnostics

#ifdef _DEBUG
  void CTestMainFrame::AssertValid() const
  {
  CFrameWnd::AssertValid();
  }

  void CTestMainFrame::Dump(CDumpContext& dc) const
  {
  CFrameWnd::Dump(dc);
  }

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestMainFrame message handlers
