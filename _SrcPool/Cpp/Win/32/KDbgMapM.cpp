/*$Workfile: KDbgMapM.cpp$: implementation file
  $Revision: 6$ $Date: 2004-10-01 21:34:24$
  $Author: Darko$

  Dumps the current mapping mode
  Copyright: CommonSoft Inc.
  Aug. 97 Darko Kolakovic
 */

// Group=Diagnostic

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */
#include <AfxWin.h>

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;

///////////////////////////////////////////////////////////////////////////////

//DumpMapMode()----------------------------------------------------------------
/*Dumps the current mapping mode to the predefined CDumpContext object afxDump.  
  Mapping mode can be any one of the following values:

    MM_ANISOTROPIC  Logical units are converted to arbitrary units with arbitrarily 
                    scaled axes.
    MM_HIENGLISH    Each logical unit is converted to 0.001 inch. Positive x is to 
                    the right; positive y is up.
    MM_HIMETRIC     Each logical unit is converted to 0.01 millimeter. Positive x 
                    is to the right; positive y is up.
    MM_ISOTROPIC    Logical units are converted to arbitrary units with equally 
                    scaled axes; that is, 1 unit along the x-axis is equal to 1 unit
                    along the y-axis. Use the SetWindowExt and SetViewportExt member 
                    functions to specify the desired units and the orientation of 
                    the axes. GDI makes adjustments as necessary to ensure that 
                    the x and y units remain the same size.
    MM_LOENGLISH    Each logical unit is converted to 0.01 inch. Positive x is to 
                    the right; positive y is up.
    MM_LOMETRIC     Each logical unit is converted to 0.1 millimeter. Positive x is
                    to the right; positive y is up.
    MM_TEXT         Each logical unit is converted to 1 device pixel. Positive x is
                    to the right; positive y is down.
    MM_TWIPS        Each logical unit is converted to 1/20 of a point. (Because 
                    a point is 1/72 inch, a twip is 1/1440 inch.) Positive x is
                    to the right; positive y is up.
    
  Note: uses Microsoft Fundation Library (MFC).
        Microsoft Windows specific (Win).   
 */
void DumpMapMode(CDC* pDC //pointer to the current device-context
                )
{
afxDump << _T("Mapping mode for DC @ ") << (void*)pDC << _T(" is: ");
switch (pDC->GetMapMode())
  {
  case MM_ANISOTROPIC: afxDump << _T("MM_ANISOTROPIC\n"); break;
  case MM_HIENGLISH  : afxDump << _T("MM_HIENGLISH\n");   break;
  case MM_HIMETRIC   : afxDump << _T("MM_HIMETRIC\n");    break;
  case MM_ISOTROPIC  : afxDump << _T("MM_ISOTROPIC\n");   break;
  case MM_LOENGLISH  : afxDump << _T("MM_LOENGLISH\n");   break;
  case MM_LOMETRIC   : afxDump << _T("MM_LOMETRIC\n");    break;
  case MM_TEXT       : afxDump << _T("MM_TEXT\n");        break;
  case MM_TWIPS      : afxDump << _T("MM_TWIPS\n");       break;
  }
}

///////////////////////////////////////////////////////////////////////////////
#endif  //_DEBUG
