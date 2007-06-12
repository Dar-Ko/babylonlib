/*$Workfile: TsMfcWriteTxt.cpp$: implementation file
  $Revision: 2$ $Date: 2007-06-12 17:16:18$
  $Author: Darko Kolakovic$

  Outputs text to the  MFC View window
  Copyright: CommonSoft Inc.
  Jan. 2k2 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#ifndef LPCTSTR
  #include "KTChar.h"
#endif
#include "TsMfcFrame.h" //CTestMainFrame class
#include "TsMfcDoc.h"
#include "TsMfcView.h"  //CTestView class


#ifdef _CONSOLE
  #error This is a Windows application; subsystem:console is prohibited
#endif
#ifndef _WINDOWS
  #error This is a Windows application; subsystem:windows is required
#endif


//TsWriteToView()--------------------------------------------------------------
/*Writes a character string at the View window. Requires CTestView class.

  Returns: true if succesful, otherwise returns false.

  Note: Microsoft Windows specific (Win32) 
        and uses Microsoft Foundation Library (MFC).
 */
bool TsWriteToView(LPCTSTR lszText //[in] text to output or NULL
                  )
{
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
      //Append a string text at the end of the text
    return ((CTestView*)pView)->AppendText(lszText);
    }
  }
return false;
}

//TsWriteToViewLn()------------------------------------------------------------
/*Writes a line of the text at the View window. New line
  delimiter (EOL) is appended to the end of the text. Requires CTestView class.

  Returns: true if succesful, otherwise returns false.

  Note: Microsoft Windows specific (Win32) 
        and uses Microsoft Foundation Library (MFC).
 */
bool TsWriteToViewLn(LPCTSTR lszText //[in] line of text to output
                     )
{
if(TsWriteToView(lszText))
  return TsWriteToView(_T("\r\n"));
return false;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  2    Biblioteka1.1         2007-06-12 17:16:18  Darko Kolakovic
 *       subsystem:windows
 *  1    Biblioteka1.0         2007-06-12 15:39:18  Darko Kolakovic 
 * $
 *****************************************************************************/
