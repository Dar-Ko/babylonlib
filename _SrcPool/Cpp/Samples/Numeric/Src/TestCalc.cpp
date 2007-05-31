/*$Workfile: TestCalc.cpp$: implementation file
  $Revision: 7$ $Date: 2007-05-31 16:39:51$
  $Author: Darko Kolakovic$

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
   //Validate comparison
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

#ifndef _CONSOLE //GUI (MFC) Application
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
#include "KProgCst.inl" //IsNan()
/*Test finding the roots of a quadratic equation.
 */
bool TestQuadraticEquation()
{
TsWriteToView(_T("TestQuadraticEquation()\r\n"));
TCHAR szText[512];
bool bRes = false;
double dA, dB, dC; //coefficients
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
 *  7    Biblioteka1.6         2007-05-31 16:39:51  Darko Kolakovic Moved NaN
 *       testing
 *  6    Biblioteka1.5         2007-05-22 17:38:47  Darko Kolakovic TestCalc
 *  5    Biblioteka1.4         2007-05-22 12:19:47  Darko Kolakovic 
 *  4    Biblioteka1.3         2003-01-30 22:47:24  Darko           Write results
 *       to the test log
 *  3    Biblioteka1.2         2003-01-20 04:15:29  Darko           Replaced BOOL
 *       with bool
 *  2    Biblioteka1.1         2001-07-10 00:43:08  Darko          
 *       TestQuadraticEquation()
 *  1    Biblioteka1.0         2001-06-08 22:43:58  Darko           
 * $
 *****************************************************************************/
