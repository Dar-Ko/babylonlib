/*$Workfile: TestNaN.cpp$: implementation file
  $Revision: 2$ $Date: 2007-05-31 16:41:38$
  $Author: Darko Kolakovic$

  Calculus test
  Copyright: CommonSoft Inc.
  Feb. 2k Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#include <math.h>       //log()
#include "KProgCst.inl" //IsNan()
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

/* Definitions of _HUGE and HUGE_VAL - respectively the XENIX and ANSI names
 * for a value returned in case of error by a number of the floating point
 * math routines
 */
#ifdef HUGE_VAL
  #pragma message ("HUGE_VAL")
#endif

#ifdef HUGE
  #pragma message ("HUGE")
#else
  #ifdef _MSC_VER
    /*Microsoft VC++; See math.h */
    #define HUGE HUGE
  #endif
#endif

#ifdef _HUGE
  #pragma message ("_HUGE")
#else
  #ifdef _MSC_VER
    /*Microsoft VC++; See math.h */
    #define _HUGE _HUGE
  #endif
#endif

//-----------------------------------------------------------------------------
/*Function testing not-a-numbers
 */
bool TestNaN()
{
TsWriteToView(_T("TestNaN() C++\r\n"));
TCHAR szText[512];

TESTENTRY logEntry = 
  {_T("NULL"), _T("math.h"), false};

#ifdef HUGE
  const double dHuge = HUGE;
  _stprintf(szText,_T("HUGE = %E\r\n"), dHuge);
  TsWriteToView(szText);
  TRACE0(szText);
  logEntry.m_bResult = true;
  logEntry.m_szObjectName = _T("HUGE");
  LogTest(&logEntry);
#endif
#ifdef _HUGE
  /*ANCI C: __STDC__*/
  const double d_Huge = _HUGE;
  _stprintf(szText,_T("_HUGE = %E\r\n"), d_Huge);
  TsWriteToView(szText);
  TRACE0(szText);
  logEntry.m_bResult = true;
  logEntry.m_szObjectName = _T("_HUGE");
  LogTest(&logEntry);
#endif
#ifdef HUGE_VAL
  const double dHugeVal = HUGE_VAL;
  _stprintf(szText,_T("HUGE_VAL = %E\r\n"), dHugeVal);
  TsWriteToView(szText);
  TRACE0(szText);
  logEntry.m_bResult = true;
  logEntry.m_szObjectName = _T("HUGE_VAL");
  LogTest(&logEntry);
#endif


logEntry.m_szFileName = _T("KProgCst.inl");

double dTest = log(double(0));
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
    dTest = (double)CST_dSNaN;
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
    dTest = (double)CST_dINF;
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
 *  2    Biblioteka1.1         2007-05-31 16:41:38  Darko Kolakovic Test NaN
 *  1    Biblioteka1.0         2007-05-31 12:36:01  Darko Kolakovic 
 * $
 *****************************************************************************/
