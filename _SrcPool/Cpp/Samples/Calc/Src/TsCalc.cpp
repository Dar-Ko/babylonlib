// TsCalc.cpp
// $Revision: 2$	$Date: 7/9/01 11:43:08 PM$
// Calculus
//
// Darko Kolakovic
// Feb. 2k

#include "StdAfx.h"
#include "KProgCst.h"

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

extern BOOL TsWriteToView(LPCTSTR lszText);

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
#include <Math.h>       //log()
#include "KProgCst.inl" //IsNan()
/*Function testing various arithmetic expressions
 */
BOOL TestCalculus()
{
TsWriteToView(_T("\tTestCalculus:\r\n"));
CString strText; 
double dTest = log(0);
BOOL bRes = IsNaN(dTest);
strText.Format(_T("Is log(0) undefined? %s\r\n"),bRes ? _T("Yes"):_T("No"));
TsWriteToView((LPCTSTR)strText);

dTest *= 0.0;
bRes = IsNaN(dTest);
strText.Format(_T("Is 0*log(0) undefined? %s\r\n"),bRes ? _T("Yes"):_T("No"));
TsWriteToView((LPCTSTR)strText);


  //String presentations of NaNs
dTest = 0;
dTest = CST_dNaN.dValue;
strText.Format(_T("Quiet NaN         %f\r\n"),dTest);
TsWriteToView((LPCTSTR)strText);
dTest = (double)CST_dSNaN;
strText.Format(_T("Signaling NaN     %f\r\n"),dTest);
TsWriteToView((LPCTSTR)strText);
dTest = (double)CST_dINF;
strText.Format(_T("Positive Infinity %f\r\n"),dTest);
TsWriteToView((LPCTSTR)strText);


TestRealConversion();
return TRUE;
}


//TestPoint()------------------------------------------------------
#include "KPoint.h"
#include "KPair.h"
static fPOINT ptOldPos(0.0F,0.0F);  //Old position
/*Test of point functions
 */
void TestPoint(const CPoint& point)
{
TsWriteToView(_T("\tTestPoint:\r\n"));
fPOINT ptPos(point);

float fDeg;//[°]
float fMin;//[']
float fSec;//["]
Rad2DegMinSec((float)ptPos.Angle(), fDeg, fMin,fSec);

CString strText; 
strText.Format(_T("Cursor at P(%.2f,%.2f) r=%.2f,angle =%.2f°%.2f'%.2f\"\r\n"),
               ptPos.x,ptPos.y,ptPos.Distance(),fDeg, fMin,fSec);
TsWriteToView((LPCTSTR)strText);
fPOINT ptDistance(ptPos - ptOldPos);       //Get difference between points
strText.Format(_T("Distance between new and old position is %.2f units\r\n"),
              ptDistance.Distance());
TsWriteToView((LPCTSTR)strText);

ptOldPos = ptPos; //Save current position
  //Compare points
TPair<LONG> P(point.x, point.y);
BOOL bRes = P > TPair<LONG>(40,120);
strText.Format("P(%d,%d) %s x(40,120)\r\n",P.x,P.y,bRes?">":"<=");
TsWriteToView((LPCTSTR)strText);
}


//TestRealConversion()---------------------------------------------------------
#include "KReal4IE.h" //CFloatIEEE class
/*Test floating-point conversions
 */
void TestRealConversion()
{
TsWriteToView(_T("\tTestRealConversion:\r\n"));
CString strText;
float fTemp = 273.15F;
CFloatIEEE cfTemp(fTemp);
strText.Format(_T("Temperature = %.2fK = %s%d exp(%d)\r\n"),
               fTemp, ((cfTemp.iSign < 0) ? _T("-") :_T("+")),
               cfTemp.lMantissa,cfTemp.iExponent);
TsWriteToView((LPCTSTR)strText);
fTemp = (float)cfTemp;

}

//TestQuadraticEquation()---------------------------------------------------------
/*Test findig the roots of a quadratic equation.
 */
void TestQuadraticEquation()
{
TsWriteToView(_T("\tTestQuadraticEquation:\r\n"));
CString strText;
double dA, dB, dC; //coeficients
double dX1, dX2;   //roots

extern BOOL funcQuadratic(double a,double b,double c,double& x1,double& x2);
dA = 1.;
dB = 5.;
dC = 0.;
strText.Format(_T("%.2fX^2 + %.2fX + %.2f = 0 have roots:\r\n"),dA, dB, dC);
TsWriteToView((LPCTSTR)strText);
if (funcQuadratic(dA, dB, dC, dX1, dX2))
  {
  strText.Format(_T("\tx1=%.2f, x2=%.2f\r\n"),dX1, dX2);
  }
else //Roots are complex numbers
  {
  if (!IsNaN(dX2))
    {
    strText.Format(_T("\tX1=%.2f + i%.2f\r\n"),dX1, dX2);
    TsWriteToView((LPCTSTR)strText);
    strText.Format(_T("\tX2=%.2f - i%.2f\r\n"),dX1, dX2);
    }
  else
    {
    strText =_T("undefined (divide by zero error)\r\n");
    }
  }

TsWriteToView((LPCTSTR)strText);
}