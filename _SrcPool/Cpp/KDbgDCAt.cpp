/*$Workfile: KDbgDCAt.cpp$: implementation file
  $Revision: 1.3 $ $Date: 2003/01/28 05:35:28 $
  $Author: ddarko $

  Dumps the current device-context attributes
  Copyright: CommonSoft Inc.
  Aug. 97 Darko Kolakovic
 */

// Group=Diagnostic

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */
#include <AfxWin.h>

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;

///////////////////////////////////////////////////////////////////////////////

//DumpDC()---------------------------------------------------------------------
/*Dumps the current device-context attributes to the predefined CDumpContext
  object afxDump.

  Note: uses Microsoft Fundation Library (MFC).
        Microsoft Windows specific (Win).
 */
void DumpDC(CDC* pDC //pointer to the current device-context
            )
{
afxDump << _T("Current device context is: ") << pDC;
DumpMapMode(pDC);
afxDump << _T("Current viewport origin is: ") << pDC->GetViewportOrg() << _T("[device units]\n")
        << _T("Current viewport extent is: ") << pDC->GetViewportExt() << _T("[device units]\n")
        << _T("Current origin of the window is: ") << pDC->GetWindowOrg() << _T("[logical units]\n")
        << _T("Current extent of the window is: ") << pDC->GetWindowExt() << _T("[logical units]\n")
        << _T("Current background color is: ") << pDC->GetBkColor() 
        << _T("\nCurrent text color is ") << pDC->GetTextColor() 
        <<  _T("\n");
if(pDC->m_hDC != pDC->m_hAttribDC)
  {
  afxDump << _T("The attribute-device context\n");
  CDC* pAttribDC = CDC::FromHandle(pDC->m_hAttribDC);
  DumpMapMode(pAttribDC);
  afxDump << _T("Current viewport origin is: ") << pAttribDC->GetViewportOrg() << _T("[device units]\n")
          << _T("Current viewport extent is: ") << pAttribDC->GetViewportExt() << _T("[device units]\n")
          << _T("Current origin of the window is: ") << pAttribDC->GetWindowOrg() << _T("[logical units]\n")
          << _T("Current extent of the window is: ") << pAttribDC->GetWindowExt() << _T("[logical units]\n")
          << _T("Current background color is: ") << pAttribDC->GetBkColor() 
          << _T("\nCurrent text color is ") << pAttribDC->GetTextColor() 
          <<  _T("\n");

  }
}

///////////////////////////////////////////////////////////////////////////////
#endif  //_DEBUG
