/*$Workfile: TsCalc.cpp$: implementation file
  $Revision: 4$ $Date: 30/01/2003 9:47:24 PM$
  $Author: Darko$

  Calculus test
  Copyright: CommonSoft Inc.
  Feb. 2k Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#include "KProgCst.h"
#include "KTestLog.h" //TESTENTRY struct

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

bool TestRealConversion();
extern bool TsWriteToView(LPCTSTR lszText);
static TESTENTRY s_logEntry = 
  {_T("NULL"), _T("KProgCst.h"), false};


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

//TestStrings()--------------------------------------------------------------
#include <math.h>       //log()
#include "KProgCst.inl" //IsNan()
/*Function testing various arithmetic expressions
 */
bool TestCalculus()
{
TsWriteToView(_T("TestCalculus()\r\n"));
TCHAR szText[512];

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

s_logEntry.m_szObjectName = _T("IsNaN()");
s_logEntry.m_szFileName  = _T("KProgCst.inl");
s_logEntry.m_bResult = bRes;
LogTest(&s_logEntry);

if (bRes == true) //Validate previous result
  {
    //String presentations of NaNs
  dTest = 0;
  dTest = CST_dNaN.dValue;
  _stprintf(szText,_T("Quiet NaN         %f\r\n"),dTest);
  TsWriteToView(szText); //Output: Quiet NaN         -1.#IND00
  _stprintf(szText,_T("%f"),dTest);
  bRes = (_tcsncmp(szText,_T("-1.#IND00"), 9) == 0);
  s_logEntry.m_szObjectName = _T("CST_dNaN");
  s_logEntry.m_bResult = bRes;
  LogTest(&s_logEntry);

  if (bRes)
    {
    dTest = (double)CST_dSNaN;
    _stprintf(szText,_T("Signaling NaN     %f\r\n"),dTest);
    TsWriteToView(szText); //Output: Signaling NaN     -1.#INF00
    _stprintf(szText,_T("%f"),dTest);
    bRes = (_tcsncmp(szText,_T("-1.#INF00"), 9) == 0);
    }
  s_logEntry.m_szObjectName = _T("CST_dSNaN");
  s_logEntry.m_bResult = bRes;
  LogTest(&s_logEntry);

  if (bRes)
    {
    dTest = (double)CST_dINF;
    _stprintf(szText,_T("Positive Infinity %f\r\n"),dTest);
    TsWriteToView(szText); //Output: Positive Infinity 1.#INF00
    _stprintf(szText,_T("%f"),dTest);
    bRes = (_tcsncmp(szText,_T("1.#INF00"), 8) == 0);
    }
  s_logEntry.m_szObjectName = _T("CST_dINF");
  s_logEntry.m_bResult = bRes;
  LogTest(&s_logEntry);
  }

 if (bRes)
  bRes = TestRealConversion();
return bRes;
}

//TestPoint()------------------------------------------------------
#include "KPoint.h"
#include "KPair.h"
/*Test of point functions
 */
bool TestPoint()
{
TsWriteToView(_T("TestPoint()\r\n"));
TCHAR szBuff[512];
bool bRes = false;

fPOINT ptPos(400, 500);
fPOINT ptOldPos(0.0F,0.0F);  //Old position

float fDeg;//[°]
float fMin;//[']
float fSec;//["]
Rad2DegMinSec((float)ptPos.Angle(), fDeg, fMin, fSec);
_stprintf(szBuff,_T("Point at P(%.2f,%.2f) r=%.2f,angle =%.2f°%.2f'%.2f\"\r\n"),
               ptPos.x,ptPos.y,ptPos.Distance(),fDeg, fMin,fSec);
TsWriteToView(szBuff);
bRes = ((fDeg == 51.F) && (fMin == 20.F) && (fSec >= 24.693F) && (fSec < 24.694F) );
s_logEntry.m_bResult = bRes;
s_logEntry.m_szFileName = _T("KMathCst.inl");
s_logEntry.m_szObjectName = _T("Rad2DegMinSec()");
LogTest(&s_logEntry);

if (bRes)
  {
  fPOINT ptDistance(ptPos - ptOldPos);       //Get difference between points
  double dDistance = ptDistance.Distance();
  _stprintf(szBuff,_T("Distance between new and old position is %.2f units\r\n"),
            dDistance);
  TsWriteToView(szBuff);
  bRes = ((dDistance >= 640.312) && (dDistance < 640.313)) ;
  }

if (bRes)
  {
    //Compare points
  TPair<LONG> P(240,180);
  bRes = P > TPair<LONG>(40,120);
  _stprintf(szBuff,_T("P(%d,%d) %s x(40,120)\r\n"),P.x,P.y,bRes?">":"<=");
  TsWriteToView(szBuff);
   //Validate comparaison
  bRes = (bRes == true);
  s_logEntry.m_bResult = bRes;
  s_logEntry.m_szFileName = _T("KPair.h");
  s_logEntry.m_szObjectName = _T("TPair");
  LogTest(&s_logEntry);
  }

s_logEntry.m_bResult = bRes;
s_logEntry.m_szFileName = _T("KPoint.h");
s_logEntry.m_szObjectName = _T("TPoint");
LogTest(&s_logEntry);
return bRes;
}

#ifndef _CONSOLE //GUI Application
  static fPOINT ptOldPos(0.0F,0.0F);  //Old position
  /*Test calculation of the distance between two pointer positions
   */
  bool TestPoint(const CPoint& point)
  {
  TsWriteToView(_T("\tTestPoint:\r\n"));
  fPOINT ptPos(point);

  float fDeg;//[°]
  float fMin;//[']
  float fSec;//["]
  Rad2DegMinSec((float)ptPos.Angle(), fDeg, fMin, fSec);

  CString szText; 
  szText.Format(_T("Cursor at P(%.2f,%.2f) r=%.2f,angle =%.2f°%.2f'%.2f\"\r\n"),
                 ptPos.x,ptPos.y,ptPos.Distance(),fDeg, fMin,fSec);
  TsWriteToView((LPCTSTR)szText);

  fPOINT ptDistance(ptPos - ptOldPos);       //Get difference between points
  szText.Format(_T("Distance between new and old position is %.2f units\r\n"),
              ptDistance.Distance());
  TsWriteToView((LPCTSTR)szText);

  ptOldPos = ptPos; //Save current position
  //Compare points
  TPair<LONG> P(point.x, point.y);
  bool bRes = P > TPair<LONG>(40,120);
  szText.Format("P(%d,%d) %s x(40,120)\r\n",P.x,P.y,bRes?">":"<=");
  TsWriteToView((LPCTSTR)szText);
  }
#endif //GUI Application

//TestRealConversion()---------------------------------------------------------
#include "KReal4IE.h" //CFloatIEEE class
/*Test floating-point conversions
 */
bool TestRealConversion()
{
TsWriteToView(_T("\r\nTestRealConversion()\r\n"));
TCHAR szText[512];
bool bRes = false;
float fTemp = 273.15F;
CFloatIEEE cfTemp(fTemp);
_stprintf(szText, _T("Temperature = %.2fK = %s%d exp(%d)\r\n"),
               fTemp, ((cfTemp.iSign < 0) ? _T("-") :_T("+")),
               cfTemp.lMantissa,cfTemp.iExponent);
TsWriteToView(szText);
bRes = ((cfTemp.lMantissa == 561971) && (cfTemp.iExponent == 8));
  //Typecast test
fTemp = (float)cfTemp;

s_logEntry.m_bResult = bRes;
s_logEntry.m_szFileName = _T("KReal4IE.h");
s_logEntry.m_szObjectName = _T("CFloatIEEE");
LogTest(&s_logEntry);
return bRes;
}

//TestQuadraticEquation()---------------------------------------------------------
/*Test findig the roots of a quadratic equation.
 */
bool TestQuadraticEquation()
{
TsWriteToView(_T("TestQuadraticEquation()"));
TCHAR szText[512];
bool bRes = false;
double dA, dB, dC; //coeficients
double dX1, dX2;   //roots

const bool ROOTS_REAL = true;
const bool ROOTS_COMPLEX = false;

extern bool funcQuadratic(double a,double b,double c,double& x1,double& x2);
dA = 1.;
dB = 5.;
dC = 0.;
_stprintf(szText, _T("%.2fX^2 + %.2fX + %.2f = 0 have roots:\r\n"),dA, dB, dC);
TsWriteToView((LPCTSTR)szText);
if (bRes = funcQuadratic(dA, dB, dC, dX1, dX2))
  {
  _stprintf(szText, _T("\tx1=%.2f, x2=%.2f\r\n"),dX1, dX2);
  }
else //Roots are complex numbers
  {
  if (!IsNaN(dX2))
    {
    _stprintf(szText, _T("\tX1=%.2f + i%.2f\r\n"),dX1, dX2);
    TsWriteToView((LPCTSTR)szText);
    _stprintf(szText, _T("\tX2=%.2f - i%.2f\r\n"),dX1, dX2);
    }
  else
    {
    _stprintf(szText,_T("undefined (divide by zero error)\r\n"));
    }
  }
bRes = ((bRes == ROOTS_REAL) && (dX1 == 0.) && (dX2 == -5.));

//TODO: test of complex roots
TsWriteToView((LPCTSTR)szText);
s_logEntry.m_bResult = bRes;
s_logEntry.m_szFileName = _T("KfQuadEq.cpp");
s_logEntry.m_szObjectName = _T("funcQuadratic()");
LogTest(&s_logEntry);

return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  4    Biblioteka1.3         30/01/2003 9:47:24 PMDarko           Write results
 *       to the test log
 *  3    Biblioteka1.2         20/01/2003 3:15:29 AMDarko           Replaced BOOL
 *       with bool
 *  2    Biblioteka1.1         09/07/2001 11:43:08 PMDarko          
 *       TestQuadraticEquation()
 *  1    Biblioteka1.0         08/06/2001 9:43:58 PMDarko           
 * $
 *****************************************************************************/
