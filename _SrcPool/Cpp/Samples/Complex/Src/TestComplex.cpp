/*$Workfile: TsComplex.cpp$: implementation file
  $Revision: 5$ $Date: 2003-01-30 22:47:32$
  $Author: Darko$

  Complex number arithmetics test
  Copyright: CommonSoft Inc.
  Jan. 2k Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#include "KComplex.h" //CComplex class
#include "KTestLog.h" //TESTENTRY struct

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

#ifdef  _COMPLEX_DEFINED
  #pragma message ("_COMPLEX_DEFINED")
#endif
#ifdef  __STD_COMPLEX
  #pragma message ("__STD_COMPLEX")
#endif
extern bool TsWriteToView(LPCTSTR lszText);

//TestComplex()--------------------------------------------------------------
/*Function evaluates operations with complex numbers.
 */
bool TestComplex()
{
TCHAR szText[512];
bool bRes = true;
TESTENTRY logEntry = 
  {_T("CComplex"), _T("KComplex.h"), false};
TESTENTRY logEntryBase = 
  {_T("TComplexBase"), _T("KComplxB.h"), false};

#ifdef  _COMPLEX_DEFINED  //included <math.h>
    //Complex number as structure defined in <math.h>
  TsWriteToView(_T("_cabs() calculates the absolute value of a _complex number.\r\n"));
  _complex B;
  B.x = 3.2;  //Real part
  B.y = 4.2;  //Imaginary part
   //Calculate the absolute value of a complex number
   //(compatible with  Win 9x, Win NT).
  double dRho = _cabs(B);
  if ( dRho != HUGE_VAL) //Check for overflow
    {
    _stprintf(szText, _T("|B| = |%.2f+i%.2f| = %.2f\r\n"),B.x,B.y,dRho);
    TsWriteToView(szText);
    }

  logEntryBase.m_bResult = true;
  logEntryBase.m_szObjectName = _T("_complex");
#else  //<Math.h> not included
  TsWriteToView(_T("Complex numbers are not supported.\r\n"));
  TComplexBase<double>B(3.2,4.2); //Initialize B = x +iy

  logEntryBase.m_bResult = true;
#endif //_COMPLEX_DEFINED

LogTest(&logEntryBase);

#ifdef  __STD_COMPLEX //included <complex>

    //Complex number as template class as defined in <Complex>
  TsWriteToView(_T("\r\nstd::abs(A) calculates the absolute value of a std::complex<int> number\r\n"));
  std::complex<int> A(5,6);
  A << B; //Copy complex numbers
  _stprintf(szText, _T("std::complex<int> A = (int)B = %d+i%d\r\n"),A.real(),A.imag());
  TsWriteToView(szText);
    //The std::abs(A) function returns the magnitude of A
  _stprintf(szText, _T("|%d+i%d| = %d\r\n"),A.real(),A.imag(),std::abs(A));
  TsWriteToView(szText);
  logEntryBase.m_szObjectName = _T("std::complex");
  logEntryBase.m_bResult = true;
#else //<complex> not included
  TComplexBase<double>A(5,6); //Initialize A = x +iy
  TComplexBase<double> A1;
  A1 = A;            //A1 = x + iy
  A1 = 56;           //A1 = CONST + i0
  A1 /= 4;
  _stprintf(szText, _T("|%.2f+i%.2f| = %.2f\r\n"),A1.real(),A1.imag(),abs(A1));
  TsWriteToView(szText);
  logEntryBase.m_bResult = true;
#endif  //__STD_COMPLEX

LogTest(&logEntryBase);

CComplex C(B.x, B.y);
C = B;
C += A;
CComplex D(-4.3,6.1);

_stprintf(szText, _T("C = %f+i%f  D =  %f+i%f  "),C.real(),C.imag(),D.real(),D.imag());
TsWriteToView(szText);
C = D / C ;
_stprintf(szText, _T("D/C = %f+i%f\r\n"),C.real(),C.imag());
TsWriteToView(szText);

logEntry.m_bResult = true;
LogTest(&logEntry);

  //The function returns exponential of D, for base 10.
C = exp10(D); 
_stprintf(szText, _T("D E(10) = %f+i%f\r\n"),C.real(),C.imag());
TsWriteToView(szText);

TComplex<int> A2(-1,7);
TRACE2(_T("A = %d +j%d;"),A2.real(),A2.imag());
A2 = exp10(A2);
TRACE2(_T(" A E(10) = %d +j%d\n"),A2.real(),A2.imag());

logEntry.m_bResult = true;
logEntry.m_szObjectName = _T("exp10()");
LogTest(&logEntry);

  //Test acos
D = CComplex(1.2,2.8); //The function returns cosine of D
_stprintf(szText, _T("D = %f+i%f\r\n"),D.real(),D.imag());
TRACE0(szText);
TsWriteToView(szText);
C = cos(D);
_stprintf(szText, _T("cos(D) = %f+i%f "),C.real(),C.imag());
TRACE0(szText);
TsWriteToView(szText);
C = acos(C);
_stprintf(szText, _T("acos(C) = %f+i%f\r\n"),C.real(),C.imag());
TRACE0(szText);
TsWriteToView(szText);

bRes = bRes &&  (C.real() > 1.19999) && (C.real() < 1.20001) &&
                (C.imag() > 2.79999) && (C.imag() < 2.80001); //result and previous result
logEntry.m_bResult = bRes;
logEntry.m_szObjectName = _T("acos()");
LogTest(&logEntry);

  //Test asine
D = CComplex(1.2,2.8);
C = sin(D);  //The function returns sine of D
_stprintf(szText, _T("sin(D) = %f+i%f "),C.real(),C.imag());
TRACE0(szText);
TsWriteToView(szText);
C = asin(C);
_stprintf(szText, _T("asin(C) = %f+i%f\r\n"),C.real(),C.imag());
TRACE0(szText);
TsWriteToView(szText);

bRes = bRes &&  (C.real() > 1.19999) && (C.real() < 1.20001) &&
                (C.imag() > 2.79999) && (C.imag() < 2.80001); //result and previous result
logEntry.m_bResult = bRes;
logEntry.m_szObjectName = _T("asin()");
LogTest(&logEntry);

  //Test atan
TComplex<float> Phi(.94F,1.78F);
_stprintf(szText, _T("Phi = %f+i%f\r\n"),Phi.real(),Phi.imag());
TRACE0(szText);
TsWriteToView(szText);
TComplex<float> X = tan(Phi);  //The function returns tangent of Phi
_stprintf(szText, _T("tan(Phi) = %f+i%f "),X.real(),X.imag());
TRACE0(szText);
TsWriteToView(szText);
X = atan(X);
_stprintf(szText, _T("atan(X) = %f+i%f\r\n"),X.real(),X.imag());
TRACE0(szText);
TsWriteToView(szText);

bRes = bRes &&  (X.real() > 0.93999) && (X.real() < 0.94001) &&
                (X.imag() > 1.77999) && (X.imag() < 1.78001); //result and previous result
logEntry.m_bResult = bRes;
logEntry.m_szObjectName = _T("tan()");
LogTest(&logEntry);
logEntry.m_szObjectName = _T("atan()");
LogTest(&logEntry);

  //Test atanh
X = tanh(Phi);  //The function returns hyperbolic tangent of Phi
_stprintf(szText, _T("tanh(Phi) = %f+i%f "),X.real(),X.imag());
TRACE0(szText);
TsWriteToView(szText);
X = atanh(X);
_stprintf(szText, _T("atanh(X) = %f+i%f\r\n"),X.real(),X.imag());
TRACE0(szText);
TsWriteToView(szText);

bRes = bRes &&  (X.real() > 0.93999) && (X.real() < 0.94001) &&
                (X.imag() > 1.77999) && (X.imag() < 1.78001); //result and previous result
logEntry.m_bResult = bRes;
logEntry.m_szObjectName = _T("tanh()");
LogTest(&logEntry);
logEntry.m_szObjectName = _T("atanh()");
LogTest(&logEntry);


  //Dividing two complex numbers
C.real(-3.2);
C.imag(-4.8);
D.real(  .4);
D.imag(- .4);
_stprintf(szText, _T("C = %.3f + i%.3f  D =  %.3f + i%.3f\r\n"),
                 C.real(),C.imag(),D.real(),D.imag());
TRACE0(szText);
TsWriteToView(szText);
C/=D;
_stprintf(szText, _T("C / D = %f + i%f\r\n"),C.real(),C.imag());
TRACE0(szText);
TsWriteToView(szText);

C.real(-3.2);
C.imag(-4.8);
double dTemp = norm(D);
C *= conj(D);
C /= dTemp;
_stprintf(szText, _T("C / D = %f + i%f\r\n"),C.real(),C.imag());
TRACE0(szText);
TsWriteToView(szText);

  //Multiplying two complex numbers
C.real(-3.2);
C.imag(-4.8);
C *= D;
_stprintf(szText, _T("C * D = %f + i%f\r\n"),C.real(),C.imag());
TRACE0(szText);
TsWriteToView(szText);

C.real(-3.2);
C.imag(-4.8);
dTemp = C.real()*D.real() - C.imag()*D.imag();
C.imag(C.imag()*D.real() + C.real()*D.imag());
C.real(dTemp);
_stprintf(szText, _T("C * D = %f + i%f\r\n"),C.real(),C.imag());
TRACE0(szText);
TsWriteToView(szText);

if (C != D) //Test comparison
  {
  D = sqrt(C);  //Test square root function
  _stprintf(szText, _T("D = C**0.5 = %f + i%f\r\n"),D.real(),D.imag());
  TRACE0(szText);
  TsWriteToView(szText);

  C = pow(D,2);
  _stprintf(szText, _T("D**2 = %f + i%f\r\n"),C.real(),C.imag());
  TRACE0(szText);
  TsWriteToView(szText);
  }

  //conversion from polar coordinates to complex number
double dEff = 48;
D = polar(dEff);
_stprintf(szText, _T("Rho = %.0f D = %f + i%f\r\n"),dEff,D.real(),D.imag());
TRACE0(szText);
TsWriteToView(szText);
dEff = 220;
int iNom = 3;
double dPhi = CST_PI/iNom;
D = polar(dEff,dPhi); //D = 220*e(i*60[deg])
_stprintf(szText, _T("D = %.0fe**(i3.14/%d) = %f + i%f\r\n"),dEff,iNom,D.real(),D.imag());
TRACE0(szText);
TsWriteToView(szText);

  //Test log2
D = logN(C,2); //Returns the logarithm to base 2
_stprintf(szText, _T("D = log2(C) = %f + i%f\r\n"),D.real(),D.imag());
TRACE0(szText);
TsWriteToView(szText);
logEntryBase.m_bResult = true;
logEntryBase.m_szObjectName = _T("logN()");
logEntryBase.m_szFileName = _T("KMathCst.inl");
LogTest(&logEntryBase);

  //Test acoth
D = acoth(C); //Returns the hyperbolic arcus cosecant
_stprintf(szText, _T("acoth(C) = %f + i%f\r\n"),D.real(),D.imag());
TRACE0(szText);
TsWriteToView(szText);

logEntry.m_bResult = bRes;
logEntry.m_szObjectName = _T("acoth()");
LogTest(&logEntry);

  //Calculate line input impedance
extern CComplex GetLineZin(CComplex Zt, const CComplex& Zline, double dAttenuation,
                    double dPhaseShift, const double& dLineLength);
C.real(0);
C.imag(0);

D = GetLineZin(C, CComplex(50.0,0), 2.5,CST_PI/2.,10);
_stprintf(szText, _T("Load = %f + i%f, Zin =  %f + i%f\r\n"),
                 C.real(),C.imag(),D.real(),D.imag());
TRACE0(szText);
TsWriteToView(szText);
logEntryBase.m_bResult =  (D.real() > 49.68300) && (D.real() < 49.68500) &&
                (D.imag() > -0.00001) && (D.imag() < 0.00001); //result and previous result

logEntryBase.m_bResult = true;
logEntryBase.m_szObjectName = _T("GetLineZin()");
logEntryBase.m_szFileName = _T("KZLineIn.cpp");
LogTest(&logEntryBase);
bRes = bRes && logEntryBase.m_bResult;

return bRes;
}

//TestPointToComplex()------------------------------------------------------
/*Test conversion from CPoint to complex number
 */
#ifndef _CONSOLE //GUI application
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
  _stprintf(szText, _T("%.2f+i%.2f = %.2fe(i%.2f)\r\n"),ccPos.real(),ccPos.imag(),dRho,dAngle);
  TsWriteToView(szText);
  return bRes;
  }
#else
  bool TestPointToComplex()
  {
  bool bRes = true;
  TESTENTRY logEntry = 
    {_T("CComplex"), _T("KComplex.h"), false};

  CComplex ccPos(220,50);
  double dRho;   //magnitude
  double dAngle; //phase angle

  dRho   = ccPos.Rho();   //The function returns the magnitude of ccPos
  bRes = (dRho > 225.61028) && (dRho < 225.610285);
  logEntry.m_bResult = bRes;
  logEntry.m_szObjectName = _T("Rho()");
  LogTest(&logEntry);

  dAngle = ccPos.Angle(); //The function returns the phase angle of ccPos
  logEntry.m_bResult = (dAngle > 0.22340) && (dAngle < 0.22349);
  logEntry.m_szObjectName = _T("Angle()");
  LogTest(&logEntry);
  bRes = bRes && logEntry.m_bResult;

  TRACE2(_T("ccPos = %f e(j%f)\n"),abs(ccPos),arg(ccPos));
  TsWriteToView(_T("Coordinates are "));
  TCHAR szText[512];
  _stprintf(szText, _T("%.2f+i%.2f = %.2fe(i%.2f)\r\n"),ccPos.real(),ccPos.imag(),dRho,dAngle);
  TsWriteToView(szText);
  return bRes;
  }
#endif //_CONSOLE

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  5    Biblioteka1.4         2003-01-30 22:47:32  Darko           Write results
 *       to the test log
 *  4    Biblioteka1.3         2003-01-22 23:22:35  Darko           
 *  3    Biblioteka1.2         2003-01-20 04:15:32  Darko           Replaced BOOL
 *       with bool
 *  2    Biblioteka1.1         2001-07-11 22:59:43  Darko           
 *  1    Biblioteka1.0         2001-06-08 22:53:44  Darko           
 * $
 *****************************************************************************/

