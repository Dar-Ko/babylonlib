/*$Workfile: TsComplex.cpp$: implementation file
  $Revision: 1.1 $ $Date: 2003/01/28 05:46:55 $
  $Author: ddarko $

  Complex number arithmetics test
  Copyright: CommonSoft Inc.
  Jan. 2k Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#include "KComplex.h" //CComplex class

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
CString strResult;

#ifdef  _COMPLEX_DEFINED  //included <Math.h>
    //Complex number as structure defined in <Math.h>
  TsWriteToView(_T("_cabs() calculates the absolute value of a _complex number.\r\n"));
  _complex B;
  B.x = 3.2;  //Real part
  B.y = 4.2;  //Imaginary part
   //Calculate the absolute value of a complex number
   //(compatible with  Win 9x, Win NT).
  double dRho = _cabs(B);
  if ( dRho != HUGE_VAL) //Check for overflow
    {
    strResult.Format(_T("|B| = |%.2f+i%.2f| = %.2f\r\n"),B.x,B.y,dRho);
    TsWriteToView((LPCTSTR)strResult);
    }
#else  //<Math.h> not included
  TsWriteToView(_T("Complex numbers are not supported.\r\n"));
  TComplexBase<double>B(3.2,4.2); //Initialize B = x +iy
#endif //_COMPLEX_DEFINED


#ifdef  __STD_COMPLEX //included <complex>

    //Complex number as template class as defined in <Complex>
  TsWriteToView(_T("\r\nstd::abs(A) calculates the absolute value of a std::complex<int> number\r\n"));
  std::complex<int> A(5,6);
  A << B; //Copy complex numbers
  strResult.Format(_T("std::complex<int> A = (int)B = %d+i%d\r\n"),A.real(),A.imag());
  TsWriteToView((LPCTSTR)strResult);
    //The std::abs(A) function returns the magnitude of A
  strResult.Format(_T("|%d+i%d| = %d\r\n"),A.real(),A.imag(),std::abs(A));
  TsWriteToView((LPCTSTR)strResult);
#else //<complex> not included
  TComplexBase<double>A(5,6); //Initialize A = x +iy
  TComplexBase<double> A1;
  A1 = A;            //A1 = x + iy
  A1 = 56;           //A1 = CONST + i0
  A1 /= 4;
  strResult.Format(_T("|%.2f+i%.2f| = %.2f\r\n"),A1.real(),A1.imag(),abs(A1));
  TsWriteToView((LPCTSTR)strResult);
#endif  //__STD_COMPLEX

CComplex C(B.x, B.y);
C = B;
C += A;
CComplex D(-4.3,6.1);

strResult.Format(_T("C = %f+i%f  D =  %f+i%f  "),C.real(),C.imag(),D.real(),D.imag());
TsWriteToView((LPCTSTR)strResult);
C = D / C ;
strResult.Format(_T("D/C = %f+i%f\r\n"),C.real(),C.imag());
TsWriteToView((LPCTSTR)strResult);

C = exp10(D); //The function returns exponential of D, for base 10.
strResult.Format(_T("D E(10) = %f+i%f\r\n"),C.real(),C.imag());
TsWriteToView((LPCTSTR)strResult);

TComplex<int> A2(-1,7);
TRACE2(_T("A = %d +j%d;"),A2.real(),A2.imag());
A2 = exp10(A2);
TRACE2(_T(" A E(10) = %d +j%d\n"),A2.real(),A2.imag());

D = CComplex(1.2,2.8);
strResult.Format(_T("D = %f+i%f\r\n"),D.real(),D.imag());
TRACE0((LPCTSTR)strResult);
TsWriteToView((LPCTSTR)strResult);
C = cos(D); //The function returns cosine of D
strResult.Format(_T("cos(D) = %f+i%f "),C.real(),C.imag());
TRACE0((LPCTSTR)strResult);
TsWriteToView((LPCTSTR)strResult);
C = acos(C);
strResult.Format(_T("acos(C) = %f+i%f\r\n"),C.real(),C.imag());
TRACE0((LPCTSTR)strResult);
TsWriteToView((LPCTSTR)strResult);

C = sin(D);  //The function returns sine of D
strResult.Format(_T("sin(D) = %f+i%f "),C.real(),C.imag());
TRACE0((LPCTSTR)strResult);
TsWriteToView((LPCTSTR)strResult);
C = asin(C);
strResult.Format(_T("asin(C) = %f+i%f\r\n"),C.real(),C.imag());
TRACE0((LPCTSTR)strResult);
TsWriteToView((LPCTSTR)strResult);

TComplex<float> Phi(.94F,1.78F);
strResult.Format(_T("Phi = %f+i%f\r\n"),Phi.real(),Phi.imag());
TRACE0((LPCTSTR)strResult);
TsWriteToView((LPCTSTR)strResult);
TComplex<float> X = tan(Phi);  //The function returns tangent of Phi
strResult.Format(_T("tan(Phi) = %f+i%f "),X.real(),X.imag());
TRACE0((LPCTSTR)strResult);
TsWriteToView((LPCTSTR)strResult);
X = atan(X);
strResult.Format(_T("atan(X) = %f+i%f\r\n"),X.real(),X.imag());
TRACE0((LPCTSTR)strResult);
TsWriteToView((LPCTSTR)strResult);

X = tanh(Phi);  //The function returns hyperbolic tangent of Phi
strResult.Format(_T("tanh(Phi) = %f+i%f "),X.real(),X.imag());
TRACE0((LPCTSTR)strResult);
TsWriteToView((LPCTSTR)strResult);
X = atanh(X);
strResult.Format(_T("atanh(X) = %f+i%f\r\n"),X.real(),X.imag());
TRACE0((LPCTSTR)strResult);
TsWriteToView((LPCTSTR)strResult);

  //Dividing two complex numbers
C.real(-3.2);
C.imag(-4.8);
D.real(  .4);
D.imag(- .4);
strResult.Format(_T("C = %.3f + i%.3f  D =  %.3f + i%.3f\r\n"),
                 C.real(),C.imag(),D.real(),D.imag());
TRACE0((LPCTSTR)strResult);
TsWriteToView((LPCTSTR)strResult);
C/=D;
strResult.Format(_T("C / D = %f + i%f\r\n"),C.real(),C.imag());
TRACE0((LPCTSTR)strResult);
TsWriteToView((LPCTSTR)strResult);

C.real(-3.2);
C.imag(-4.8);
double dTemp = norm(D);
C *= conj(D);
C /= dTemp;
strResult.Format(_T("C / D = %f + i%f\r\n"),C.real(),C.imag());
TRACE0((LPCTSTR)strResult);
TsWriteToView((LPCTSTR)strResult);

  //Multiplying two complex numbers
C.real(-3.2);
C.imag(-4.8);
C *= D;
strResult.Format(_T("C * D = %f + i%f\r\n"),C.real(),C.imag());
TRACE0((LPCTSTR)strResult);
TsWriteToView((LPCTSTR)strResult);

C.real(-3.2);
C.imag(-4.8);
dTemp = C.real()*D.real() - C.imag()*D.imag();
C.imag(C.imag()*D.real() + C.real()*D.imag());
C.real(dTemp);
strResult.Format(_T("C * D = %f + i%f\r\n"),C.real(),C.imag());
TRACE0((LPCTSTR)strResult);
TsWriteToView((LPCTSTR)strResult);

if (C != D) //Test comparison
  {
  D = sqrt(C);  //Test square root function
  strResult.Format(_T("D = C**0.5 = %f + i%f\r\n"),D.real(),D.imag());
  TRACE0((LPCTSTR)strResult);
  TsWriteToView((LPCTSTR)strResult);

  C = pow(D,2);
  strResult.Format(_T("D**2 = %f + i%f\r\n"),C.real(),C.imag());
  TRACE0((LPCTSTR)strResult);
  TsWriteToView((LPCTSTR)strResult);
  }

  //conversion from polar coordinates to complex number
double dEff = 48;
D = polar(dEff);
strResult.Format(_T("Rho = %.0f D = %f + i%f\r\n"),dEff,D.real(),D.imag());
TRACE0((LPCTSTR)strResult);
TsWriteToView((LPCTSTR)strResult);
dEff = 220;
int iNom = 3;
double dPhi = CST_PI/iNom;
D = polar(dEff,dPhi); //D = 220*e(i*60[deg])
strResult.Format(_T("D = %.0fe**(i3.14/%d) = %f + i%f\r\n"),dEff,iNom,D.real(),D.imag());
TRACE0((LPCTSTR)strResult);
TsWriteToView((LPCTSTR)strResult);

D = logN(C,2); //Returns the logarithm to base 2
strResult.Format(_T("D = log2(C) = %f + i%f\r\n"),D.real(),D.imag());
TRACE0((LPCTSTR)strResult);
TsWriteToView((LPCTSTR)strResult);

D = acoth(C); //Returns the hyperbolic arcus cosecant
strResult.Format(_T("acoth(C) = %f + i%f\r\n"),D.real(),D.imag());
TRACE0((LPCTSTR)strResult);
TsWriteToView((LPCTSTR)strResult);

  //Calculate line input impedance
extern CComplex GetLineZin(CComplex Zt, const CComplex& Zline, double dAttenuation,
                    double dPhaseShift, const double& dLineLength);
C.real(0);
C.imag(0);

D = GetLineZin(C, CComplex(50.0,0), 2.5,CST_PI/2.,10);
strResult.Format(_T("Load = %f + i%f, Zin =  %f + i%f\r\n"),
                 C.real(),C.imag(),D.real(),D.imag());
TRACE0((LPCTSTR)strResult);
TsWriteToView((LPCTSTR)strResult);

return TRUE;
}


//TestPointToComplex()------------------------------------------------------
/*Test conversion from CPoint to complex number
 */
void TestPointToComplex(CPoint& ptPos)
{
CComplex ccPos = ptPos;
double dRho;   //magnitude
double dAngle; //phase angle

dRho   = ccPos.Rho();   //The function returns the magnitude of ccPos
dAngle = ccPos.Angle(); //The function returns the phase angle of ccPos

TRACE2(_T("ccPos = %f e(j%f)\n"),abs(ccPos),arg(ccPos));
TsWriteToView(_T("Mouse position is "));
CString strResult;
strResult.Format(_T("%.2f+i%.2f = %.2fe(i%.2f)\r\n"),ccPos.real(),ccPos.imag(),dRho,dAngle);
TsWriteToView((LPCTSTR)strResult);
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  4    Biblioteka1.3         22/01/2003 10:22:35 PMDarko           
 *  3    Biblioteka1.2         20/01/2003 3:15:32 AMDarko           Replaced BOOL
 *       with bool
 *  2    Biblioteka1.1         11/07/2001 9:59:43 PMDarko           
 *  1    Biblioteka1.0         08/06/2001 9:53:44 PMDarko           
 * $
 *****************************************************************************/

