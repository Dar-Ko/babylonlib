/*$Workfile: TestMfcComplex.cpp$: implementation file
  $Revision: 2$ $Date: 2007-06-13 17:14:27$
  $Author: Darko Kolakovic$

  Complex number arithmetics test
  Copyright: CommonSoft Inc.
  Jan. 2k Darko Kolakovic
*/

// Group=Examples


#include "stdafx.h"

#ifdef _CONSOLE
  #error This is a Windows application; subsystem:console is prohibited
#endif

#ifdef _WINDOWS //GUI application
  #include "KComplex.h" //CComplex class
  #include "TsMfcFrame.h" //CTestMainFrame class
  #include "TsMfcDoc.h"
  #include "TsMfcView.h"  //CTestView class

/*Note: when you build a Windows project created from the scratch, you may 
  get the following error message from linker:
      error LNK2001: unresolved external symbol _main
  To solve the problem, insure that target subsystem is not console, but
  windows. Click the Link tab and under Project Options, change 
    /subsystem:console to /subsystem:windows.
  Also replace preprocessor definition _CONSOLE with _WINDOWS. Click at 
  the C/C++ tab  and change preprocessor definitions.
 */

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

extern bool TsWriteToView(LPCTSTR lszText);

//TestPointToComplex()------------------------------------------------------
/*Test conversion from CPoint to complex number.

  Returns: true if successful, otherwise returns false.

  See also: CTestView::OnLButtonDblClk()
*/
  bool TestPointToComplex(CPoint& ptPos //[in] current pointer position
                         )
  {
  bool bRes = true;
  CComplex ccPos = ptPos;
  double dRho;   //magnitude
  double dAngle; //phase angle

  dRho   = ccPos.Rho();   //The function returns the magnitude of ccPos
  dAngle = ccPos.Angle(); //The function returns the phase angle of ccPos

  TRACE2(_T("ccPos = %f e(j%f)\n"),abs(ccPos),arg(ccPos));
  TsWriteToView(_T("Mouse position is "));
  TCHAR szText[512];
  _stprintf(szText, _T("%.2f+i%.2f = %.2fe(i%.2f)\r\n"),
                  ccPos.real(), ccPos.imag(), dRho, dAngle);
  TsWriteToView(szText);
  return bRes;
  }

  bool TestPointToComplex()
  {
  //Obtain current view
  CWnd* pFrame = AfxGetMainWnd();
  ASSERT(pFrame != NULL);
  ASSERT_VALID(pFrame);

  if (pFrame != NULL)
    {
    ASSERT_KINDOF(CTestMainFrame, pFrame);
    ASSERT (pFrame->IsKindOf(RUNTIME_CLASS(CTestMainFrame)));
    CView* pView = ((CTestMainFrame*)pFrame)->GetActiveView();
    if (pView != NULL)
      {
      ASSERT_KINDOF(CTestView, pView);
      ASSERT(pView->IsKindOf(RUNTIME_CLASS(CTestView)));
        //Set the testing method
      ((CTestView*)pView)->m_PointTest = TestPointToComplex;
      }
    }

  return TestPointToComplex(CPoint(220, 50));
  }
  
#endif //_WINDOWS

  ///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  2    Biblioteka1.1         2007-06-13 17:14:27  Darko Kolakovic formatting
 *  1    Biblioteka1.0         2007-06-12 17:17:47  Darko Kolakovic 
 * $
 *****************************************************************************/

