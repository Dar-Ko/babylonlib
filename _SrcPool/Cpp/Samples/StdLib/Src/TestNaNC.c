/*$Workfile: S:\_SrcPool\Cpp\Samples\StdLib\Src\TestNaNC.c$: implementation file
  $Revision: 1$ $Date: 2007-05-31 12:35:10$
  $Author: Darko Kolakovic$

  Calculus test
  Copyright: CommonSoft Inc.
  Feb. 2k Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#include "KTChar.h"
#include "KProgCst.h"
#include "KTestLog.h" //TESTENTRY struct

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

extern bool TsWriteToView(LPCTSTR lszText);

#ifdef _MSC_VER
  //Microsoft Visual C preprocessor
  #pragma message ("Compiler option:")
  #if _M_IX86 == 600
    #pragma message ("    Intel Pentium Pro")
  #elif _M_IX86 == 500
    #pragma message ("    Intel  Pentium")
  #elif _M_IX86 == 400
    #pragma message ("    Intel  80486")
  #elif _M_IX86 == 300
    #pragma message ("    Intel  80386")
  #else
    #pragma message ("    Unsupported CPU")
  #endif
#endif
//-----------------------------------------------------------------------------
#include <math.h>       //log()
#include <stdio.h>      //_stprintf()
#include "KProgCst.inl" //IsNan()
/*Function testing not-a-numbers
 */
bool TestNaN()
{
//TsWriteToView(_T("TestNaN() C compilation\r\n"));
TCHAR szText[512];

TESTENTRY logEntry = 
  {_T("NULL"), _T("KProgCst.inl"), false};

double dTest = log(0);
bool bRes = IsNaN(dTest); //log(0) is defined number
_stprintf(szText, _T("Is log(0) undefined? %s\r\n"),bRes ? _T("Yes"):_T("No"));
TsWriteToView(szText); //Output: Is log(0) undefined? No
if (bRes == false) //Validate result
  {
  dTest *= 0.0;
  bRes = IsNaN(dTest); //0*log(0) is undefined number
  _stprintf(szText, _T("Is 0*log(0) undefined? %s\r\n"),bRes ? _T("Yes"):_T("No"));
  TsWriteToView(szText); //Output: Is 0*log(0) undefined? Yes
  }

logEntry.m_szObjectName = _T("IsNaN()");
logEntry.m_bResult = bRes;
LogTest(&logEntry);

if (bRes == true) //Validate previous result
  {
    //String presentations of NaNs
  dTest = 0;
  dTest = CST_dQNaN.dValue;
  _stprintf(szText,_T("Quiet NaN         %f\r\n"),dTest);
  TsWriteToView(szText); //Output: Quiet NaN         -1.#IND00
  _stprintf(szText,_T("%f"),dTest);
  bRes = (_tcsncmp(szText,_T("-1.#IND00"), 9) == 0);
  logEntry.m_szObjectName = _T("CST_dQNaN");
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  if (bRes)
    {
    dTest = CST_dSNaN.dValue;
    _stprintf(szText,_T("Signaling NaN     %f\r\n"),dTest);
    TsWriteToView(szText); //Output: Signaling NaN     -1.#INF00
    _stprintf(szText,_T("%f"),dTest);
    bRes = (_tcsncmp(szText,_T("-1.#INF00"), 9) == 0);
    }
  logEntry.m_szObjectName = _T("CST_dSNaN");
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  if (bRes)
    {
    dTest = CST_dINF.dValue;
    _stprintf(szText,_T("Positive Infinity %f\r\n"),dTest);
    TsWriteToView(szText); //Output: Positive Infinity 1.#INF00
    _stprintf(szText,_T("%f"),dTest);
    bRes = (_tcsncmp(szText,_T("1.#INF00"), 8) == 0);
    }
  logEntry.m_szObjectName = _T("CST_dINF");
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);
  }

return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2007-05-31 12:35:10  Darko Kolakovic 
 * $
 *****************************************************************************/
