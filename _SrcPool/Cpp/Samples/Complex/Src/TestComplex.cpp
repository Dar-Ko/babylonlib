/*$Workfile: TestComplex.cpp$: implementation file
  $Revision: 15$ $Date: 2007-06-08 17:56:10$
  $Author: Darko Kolakovic$

  Complex number arithmetics test
  Copyright: CommonSoft Inc.
  Jan. 2k Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#include "KDbgMacr.h" //Compiler specific constants
#include "KProgCst.inl" //NaN constants
#include "KComplex.h" //CComplex class
#include "TestZAssert.h" //Test validation class

int s0 = g__WINVER;
#ifdef _MSC_VER
  int s1 = g__MSC_VER;
#endif
int s2 = g__cplusplus_VER;

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

#ifdef _MSC_VER
  //Microsoft Visual C/C++ compiler
  #ifdef  _STL
    #pragma message ("Using STL")
  #endif
  #ifdef  _COMPLEX_DEFINED
    #pragma message ("_COMPLEX_DEFINED")
  #endif
  #ifdef  __STD_COMPLEX
    #pragma message ("__STD_COMPLEX")
  #endif
  #ifdef _STLP_INTERNAL_COMPLEX //STLport library
    #pragma message ("_STLP_INTERNAL_COMPLEX")
  #endif
#endif


extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);

TestCComplex g_arrTestD[TESTSIZE] = 
  {
  TestCComplex(  0.0, 0.0), // 0: Z =  0
  TestCComplex(  1.0, 0.0), // 1: Z =  1 
  TestCComplex(  0.0, 1.0), // 2: Z =     j
  TestCComplex(  1.0, 1.0), // 3: Z =  1 +j
  TestCComplex( -1.0, 0.0), // 4: Z = -1 
  TestCComplex(  0.0,-1.0), // 5: Z =    -j
  TestCComplex( -1.0,-1.0), // 6: Z = -1 -j
  TestCComplex(  CST_PI_2, CST_PI_2), // 7: Z =  1.57  + j1.57
  TestCComplex(  CST_PI_4, CST_PI_4), // 8: Z =  0.785 + j0.785
  TestCComplex(  CST_PI  , CST_PI),   // 9: Z =  3.14  + j3.14
  TestCComplex( -CST_PI_2,-CST_PI_2), //10: Z = -1.57  - j1.57  
  TestCComplex( -CST_PI_4,-CST_PI_4), //11: Z = -0.785 - j0.785  
  TestCComplex( -CST_PI  ,-CST_PI),   //12: Z = -3.14  - j3.14  
  TestCComplex(  0.0,    3*CST_PI_4), //13: Z =        -(3/4)*3.14
  TestCComplex(  CST_SINPI_4, CST_SINPI_4),//14: Z =  0.707 + j0.707
  TestCComplex(  CST_SINPI_4,-CST_SINPI_4),//15: Z =  0.707 - j0.707
  TestCComplex(  3.2,  4.2 ), //16: Z =  3.2  +j4.2
  TestCComplex( -4.3,  6.1 ), //17: Z = -4.34 +j6.1
  TestCComplex(  1.2,  2.8 ), //18: Z =  1.2  +j2.8
  TestCComplex(  0.98,-1.78), //19: Z =  0.98 -j1.78
  TestCComplex( -3.2, -4.8 ), //20: Z = -3.2  -j4.8
  TestCComplex(  0.4, -0.4 ), //21: Z =  0.4  -j0.4
  TestCComplex(100.0,  0.0 ), //22: Z = -100
  TestCComplex( -1E3,  1E2 ), //23: Z = -1000 +j100
  TestCComplex(  CST_dINF, 0.0     ), //24: Z =  1.#INF 
  TestCComplex(  0.0,      CST_dINF), //25: Z =          j1.#INF
  TestCComplex(  CST_dINF, CST_dINF)  //26: Z =  1.#INF +j1.#INF

  };

//-----------------------------------------------------------------------------
/*Function evaluates additional operations with complex numbers.

  Returns: true if successful, otherwise returns false.
 */
bool TestCComplexExt()
{
TsWriteToViewLn(_T("TestComplexExt()"));
typedef CComplex (*PFUNCCOMPLEXEXT_TEST) (const CComplex&);
struct tagSFuncTest
  {
  PFUNCCOMPLEXEXT_TEST m_func; //function to test
  LPCTSTR m_funcName;          //name of the function
  PFUNCCOMPLEXD_TEST m_funcT;  //validating function
  };
bool bRes = false;  

tagSFuncTest funcTest[] =
  {
  {I    , _T("I(const CComplex&)")    ,TsComplexD::CstI} , // 0
  {exp10, _T("exp10(const CComplex&)"),TsComplexD::Exp10}, // 1
  {log2 , _T("log2(const CComplex&)") ,TsComplexD::log2} , // 2
  {acos , _T("acos(const CComplex&)") ,TsComplexD::ACos} , // 3
  {asin , _T("asin(const CComplex&)") ,TsComplexD::ASin} , // 4
  {tan  , _T("tan(const CComplex&)")  ,TsComplexD::Tan } , // 5
  {atan , _T("atan(const CComplex&)") ,TsComplexD::ATan} , // 6
  {acosh, _T("acosh(const CComplex&)"),TsComplexD::ACosH}, // 7
  {asinh, _T("asinh(const CComplex&)"),TsComplexD::ASinH}, // 8
  {tanh , _T("tanh(const CComplex&)") ,TsComplexD::TanH} , // 9
  {atanh, _T("atanh(const CComplex&)"),TsComplexD::ATanH}, //10 
  {asech, _T("asech(const CComplex&)"),TsComplexD::arsech},//11
  {acoth, _T("acoth(const CComplex&)"),TsComplexD::arcoth},//12

  {NULL, NULL, NULL} //the end
  };

int f = 0; //function number
while (funcTest[f].m_func != NULL)
  {
  int c = 0; //tested value number
  g_arrTestD[0].m_szFileName = _T("KComplex.h");
  g_arrTestD[0].m_szObjectName = funcTest[f].m_funcName;
  g_arrTestD[0].m_bResult = true;
  while(c < TESTSIZE)
    {
        
    g_arrTestD[c] = funcTest[f].m_func(CComplex(g_arrTestD[c])); //Invoke a method
    g_arrTestD[c].Validate(funcTest[f].m_funcT); //Get test values

    g_arrTestD[c].m_szObjectName = funcTest[f].m_funcName;
    g_arrTestD[c].Write();
    
    if (!(g_arrTestD[0].m_bResult = g_arrTestD[c].m_bResult))
      break;
    c++;
    }
  LogTest(&g_arrTestD[0]);
  f++;
  }

return bRes; //fixme
}

#ifndef _CONSOLE //GUI application
//TestPointToComplex()------------------------------------------------------
/*Test conversion from CPoint to complex number.

  Returns: true if successful, otherwise returns false.
*/
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

//---------------------------------------------------------------------------
/*Function evaluates line input impedance calculation.

  Returns: true if successful, otherwise returns false.
*/
bool TestLineZin()
{
TsWriteToViewLn(_T("TestLineZin()"));
//Calculate line input impedance
extern CComplex GetLineZin(CComplex Zt, const CComplex& Zline, double dAttenuation,
  double dPhaseShift, const double& dLineLength);
TESTENTRY logEntryBase;
TCHAR szText[512];
bool bRes = true;  
CComplex C, D;
C.real(0);
C.imag(0); //Shortcut

D = GetLineZin(C, CComplex(50.0,0), 2.5,CST_PI/2.,10);
_stprintf(szText, _T("Load = %f + i%f, Zin =  %f + i%f\r\n"),
  C.real(),C.imag(),D.real(),D.imag());
TRACE0(szText);
TsWriteToView(szText);
logEntryBase.m_bResult =  (D.real() > 49.68300) && (D.real() < 49.68500) &&
  (D.imag() > -0.00001) && (D.imag() < 0.00001); //result and previous result

logEntryBase.m_szObjectName = _T("GetLineZin()");
logEntryBase.m_szFileName = _T("KZLineIn.cpp");
LogTest(&logEntryBase);
bRes = bRes && logEntryBase.m_bResult;

return bRes;
}

//---------------------------------------------------------------------------
/*Function evaluates the arcus cosine of complex number.

  Returns: true if successful, otherwise returns false.
*/
bool TestACos()
{
TsWriteToViewLn(_T("TestACos()"));
extern _complex acos(const _complex&);

bool bRes = true;  

int c = 0; //tested value number
g_arrTestD[0].m_szFileName = _T("KMatAcosC.cpp");
g_arrTestD[0].m_szObjectName = _T("acos(const _complex&)");
g_arrTestD[0].m_bResult = true;
while(c < TESTSIZE)
{

  g_arrTestD[c] = acos(_complex(g_arrTestD[c])); //Invoke a method
  g_arrTestD[c].Validate(TsComplexD::ACos); //Get test values

  g_arrTestD[c].m_szObjectName = _T("acos(const _complex&)");
  g_arrTestD[c].Write();

  if (!(g_arrTestD[0].m_bResult = g_arrTestD[c].m_bResult))
    break;
  c++;
}
LogTest(&g_arrTestD[0]);

return bRes; //fixme
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  15   Biblioteka1.14        2007-06-08 17:56:10  Darko Kolakovic New test cases
 *  14   Biblioteka1.13        2007-06-04 16:57:59  Darko Kolakovic Fixed
 *       validation of NaNs
 *  13   Biblioteka1.12        2007-06-01 17:34:52  Darko Kolakovic Test cases
 *  12   Biblioteka1.11        2007-05-31 16:41:23  Darko Kolakovic Test NaN
 *  11   Biblioteka1.10        2007-05-30 16:47:01  Darko Kolakovic Automate test
 *  10   Biblioteka1.9         2007-05-29 16:37:23  Darko Kolakovic Inserted
 *       complex number validation
 *  9    Biblioteka1.8         2007-05-28 17:07:33  Darko Kolakovic
 *       _STLP_INTERNAL_COMPLEX
 *  8    Biblioteka1.7         2007-05-25 17:28:32  Darko Kolakovic g__MSC_VER
 *  7    Biblioteka1.6         2007-05-24 16:54:06  Darko Kolakovic Test atanh
 *  6    Biblioteka1.5         2007-05-22 16:54:05  Darko Kolakovic 
 *  5    Biblioteka1.4         2003-01-30 22:47:32  Darko           Write results
 *       to the test log
 *  4    Biblioteka1.3         2003-01-22 23:22:35  Darko           
 *  3    Biblioteka1.2         2003-01-20 04:15:32  Darko           Replaced BOOL
 *       with bool
 *  2    Biblioteka1.1         2001-07-11 22:59:43  Darko           
 *  1    Biblioteka1.0         2001-06-08 22:53:44  Darko           
 * $
 *****************************************************************************/

//TestComplex()--------------------------------------------------------------
/*Function evaluates operations with complex numbers.

Returns: true if successful, otherwise returns false.
* /
bool TestComplex()
{
TsWriteToViewLn(_T("TestComplex()"));

TCHAR szText[512];
bool bRes = true;
TESTENTRY logEntry = 
{_T("CComplex"), _T("KComplex.h"), false};
TESTENTRY logEntryBase = 
{_T("TComplexBase"), _T("KComplxB.h"), false};

double EPSMIN = 1e-10; //rounding error

#ifdef  _COMPLEX_DEFINED  //included <math.h>
//Complex number as structure defined in <math.h>
TsWriteToView(_T("_cabs() calculates the absolute value of a _complex number.\r\n"));
_complex B;
B.x = 3.2;  //Real part
B.y = 4.2;  //Imaginary part
TsComplexD testB(B.x, B.y);

//Calculate the absolute value of a complex number
//(compatible with  Win 9x, Win NT).
double dRho = _cabs(B);
if ( dRho != HUGE_VAL) //Check for overflow
{
_stprintf(szText, _T("|B| = |%.2f+i%.2f| = %.2f\r\n"),B.x,B.y,dRho);
TsWriteToView(szText);
}

double dTs = TsComplexD::Abs(TsComplexD(B.x, B.y));
bRes = (dRho == dTs);

logEntryBase.m_bResult = bRes;
logEntryBase.m_szFileName = _T("math.h");
logEntryBase.m_szObjectName = _T("abs(_complex)");
LogTest(&logEntryBase);


logEntryBase.m_bResult = (dRho == Absolute(B));
logEntryBase.m_szFileName = _T("KMathCst.inl");
logEntryBase.m_szObjectName = _T("Absolute(_complex)");
LogTest(&logEntryBase);

#else  //<Math.h> not included
TsWriteToView(_T("Complex numbers are not supported.\r\n"));
TComplexBase<double>B(3.2,4.2); //Initialize B = x +iy
TsComplexD testB(B.real(), B.imag());

logEntryBase.m_bResult = true;
#endif //_COMPLEX_DEFINED


#ifdef  __STD_COMPLEX //included <complex>

//Complex number as template class as defined in <Complex>
TsWriteToView(_T("\r\nstd::abs(A) calculates the absolute value of a std::complex<int> number\r\n"));
std::complex<int> A(45,46);
A.real(5); //Test assigning number parts
A.imag(6);
A << B; //Copy complex numbers
#ifdef  _COMPLEX_DEFINED
logEntry.m_bResult = ((A.real() == (int)B.x) && (A.imag() == (int)B.y));
logEntry.m_szFileName = _T("KComplex.h");
logEntry.m_szObjectName = _T("operator <<(std::complex<int>&,_complex)");
#else
logEntry.m_bResult = ((A.real() == (int)B.real()) && (A.imag() == (int)B.imag()));
logEntry.m_szFileName = _T("KComplex.h");
logEntry.m_szObjectName = _T("operator <<(std::complex<int>&,TComplexBase<double>)");
#endif
LogTest(&logEntry);

_stprintf(szText, _T("std::complex<int> A = (int)B = %d+i%d\r\n"),A.real(),A.imag());
TsWriteToView(szText);
//The std::abs(A) function returns the magnitude of A
_stprintf(szText, _T("|%d+i%d| = %d\r\n"),A.real(),A.imag(),std::abs(A));
TsWriteToView(szText);
logEntryBase.m_szObjectName = _T("abs(std::complex)");
logEntryBase.m_szFileName = _T("complex");
logEntryBase.m_bResult = true;
LogTest(&logEntryBase);

logEntryBase.m_bResult = (std::abs(A) == (double)Absolute(A));
logEntryBase.m_szFileName = _T("KMathCst.inl");
logEntryBase.m_szObjectName = _T("Absolute(std::complex)");
LogTest(&logEntryBase);

#else //<complex> not included
TComplexBase<double>A(5,6); //Initialize A = x +iy
TComplexBase<double> A1;
A1 = A;            //A1 = x + iy
A1 = 56;           //A1 = CONST + i0
A1 /= 4;
_stprintf(szText, _T("|%.2f+i%.2f| = %.2f\r\n"),A1.real(),A1.imag(),abs(A1));
TsWriteToView(szText);
logEntryBase.m_szObjectName = _T("abs()");
logEntryBase.m_szFileName = _T("KComplxB.h");
logEntryBase.m_bResult = true;
LogTest(&logEntryBase);
#endif  //__STD_COMPLEX

TsComplexD testA(A.real(), A.imag());
TsComplexD testC = testB + testA;

CComplex C(B.x, B.y);
C = B;
C += A;
bRes = (C.real() == testC.Re()) && (C.imag() == testC.Im());

logEntry.m_bResult = bRes;
logEntry.m_szObjectName = _T("CComplex::operator+=(CComplex)");
LogTest(&logEntry);
if (!bRes)
return bRes;

CComplex D(-4.3,6.1);
TsComplexD testD(D.real(),D.imag()); //test case D

_stprintf(szText, _T("C = %f+i%f  D =  %f+i%f  "),C.real(),C.imag(),D.real(),D.imag());
TsWriteToView(szText);
C = D / C ;
testC = testD / testC;

_stprintf(szText, _T("D/C = %f+i%f\r\n"),C.real(),C.imag());
TsWriteToView(szText);

bRes = (abs(C.real() - testC.Re()) <= EPSMIN) && 
(abs(C.imag() - testC.Im()) <= EPSMIN);

logEntry.m_bResult = bRes;
logEntry.m_szObjectName = _T("CComplex::operator/(CComplex)");
LogTest(&logEntry);
if (!bRes)
return bRes;

//The function returns exponential of Z, for base 10.
TComplex<int> A2(-1, 7);
D = CComplex(A2.real(), A2.imag());  

_stprintf(szText, _T(" A = %d+j%d\r\n"),A2.real(),A2.imag());
TsWriteToView(szText);
TRACE0(szText);

A2 = exp10(A2);
TRACE2(_T(" 10^A = %d +j%d\n"), A2.real(), A2.imag());

logEntry.m_bResult = false; //TODO: validation! D.K. <int> rounding error
logEntry.m_szObjectName = _T("exp10(TComplex<int>)");
LogTest(&logEntry);
if (!bRes)
return bRes;

C = exp10(D);
_stprintf(szText, _T("D = A; 10^D = %f+i%f\r\n"),C.real(),C.imag());
TsWriteToView(szText);
TRACE0(szText);

logEntry.m_bResult = false; //TODO: validation! D.K. 
logEntry.m_szObjectName = _T("exp10(TComplex<double>)");
LogTest(&logEntry);
if (!bRes)
return bRes;

//Test cos
D = CComplex(1.2,2.8); //The function returns cosine of D
testD.m_fRe = D.real();
testD.m_fIm = D.imag();

_stprintf(szText, _T("D = %f+i%f\r\n"),D.real(),D.imag());
TRACE0(szText);
TsWriteToView(szText);
C = cos(D);
testC = TsComplexD::Cos(testD);

_stprintf(szText, _T("cos(D) = %f+i%f "),C.real(),C.imag());
TRACE0(szText);
TsWriteToView(szText);

bRes = (abs(C.real() - testC.Re()) <= EPSMIN) && 
(abs(C.imag() - testC.Im()) <= EPSMIN);

logEntry.m_bResult = bRes;
logEntry.m_szObjectName = _T("CComplex::cos(CComplex)");
LogTest(&logEntry);
if (!bRes)
return bRes;


//Test acos
C = acos(C);
testC = TsComplexD::ACos(testC);
_stprintf(szText, _T("acos(C) = %f+i%f\r\n"),C.real(),C.imag());
TRACE0(szText);
TsWriteToView(szText);

bRes = (abs(C.real() - testC.Re()) <= EPSMIN) && 
(abs(C.imag() - testC.Im()) <= EPSMIN);

logEntry.m_bResult = bRes;
logEntry.m_szObjectName = _T("CComplex::acos(CComplex)");
LogTest(&logEntry);
if (!bRes)
return bRes;

//Test sin
D = CComplex(1.2,2.8);
testD.m_fRe = D.real();
testD.m_fIm = D.imag();

C = sin(D);  //The function returns sine of D
testC = TsComplexD::Sin(testD);
_stprintf(szText, _T("sin(D) = %f+i%f "),C.real(),C.imag());
TRACE0(szText);
TsWriteToView(szText);

bRes = (abs(C.real() - testC.Re()) <= EPSMIN) && 
(abs(C.imag() - testC.Im()) <= EPSMIN);

logEntry.m_bResult = bRes;
logEntry.m_szObjectName = _T("CComplex::sin(CComplex)");
LogTest(&logEntry);
if (!bRes)
return bRes;

//Test asin
C = asin(C);
testC = TsComplexD::ASin(testC);
_stprintf(szText, _T("asin(C) = %f+i%f\r\n"),C.real(),C.imag());
TRACE0(szText);
TsWriteToView(szText);

bRes = (abs(C.real() - testC.Re()) <= EPSMIN) && 
(abs(C.imag() - testC.Im()) <= EPSMIN);

logEntry.m_bResult = bRes;
logEntry.m_szObjectName = _T("CComplex::asin(CComplex)");
LogTest(&logEntry);
if (!bRes)
return bRes;

//Test tan
TComplex<float> Phi(.94F,1.78F);
_stprintf(szText, _T("Phi = %f+i%f\r\n"),Phi.real(),Phi.imag());
TRACE0(szText);
TsWriteToView(szText);
TComplex<float> X = tan(Phi);  //The function returns tangent of Phi
_stprintf(szText, _T("tan(Phi) = %f+i%f "),X.real(),X.imag());
TRACE0(szText);
TsWriteToView(szText);

testD.m_fRe = Phi.real();
testD.m_fIm = Phi.imag();
testC = TsComplexD::Tan(testD);

bRes = (abs(X.real() - testC.Re()) <= EPSMIN) && 
(abs(X.imag() - testC.Im()) <= EPSMIN);

logEntry.m_bResult = bRes;
logEntry.m_szObjectName = _T("tan(TComplex<float>)");
LogTest(&logEntry);
if (!bRes)
return bRes;

//Test atan
X = atan(X);
_stprintf(szText, _T("atan(X) = %f+i%f\r\n"),X.real(),X.imag());
TRACE0(szText);
TsWriteToView(szText);

testC = TsComplexD::ATan(testC);

bRes = (abs(X.real() - testC.Re()) <= EPSMIN) && 
(abs(X.imag() - testC.Im()) <= EPSMIN);

logEntry.m_bResult = bRes;
logEntry.m_szObjectName = _T("atan(TComplex<float>)");
LogTest(&logEntry);
if (!bRes)
return bRes;

//Test tanh(x+j0)
CComplex R(1.0, 0.0); //Real number
C = tanh(R);

testC = TsComplexD::ATan(TsComplexD(R.real(), R.imag()));

bRes = (abs(C.real() - testC.Re()) <= EPSMIN) && 
(abs(C.imag() - testC.Im()) <= EPSMIN);

logEntry.m_bResult = bRes;
logEntry.m_szObjectName = _T("CComplex::tanh(double)");
LogTest(&logEntry);
if (!bRes)
return bRes;

//Test atanh(x+j0)
if (bRes)
{
C = atanh(C);
bRes = ( (C.imag() == 0.0) && 
(C.real() >= 0.99999) && (C.real() <= 1.00005) );
}
logEntry.m_bResult = bRes;
logEntry.m_szObjectName = _T("CComplex::atanh(double)");
LogTest(&logEntry);

if (!bRes)
return bRes;

X = tanh(Phi);  //The function returns hyperbolic tangent of Phi
_stprintf(szText, _T("tanh(Phi) = %f+i%f "), X.real(), X.imag());
TRACE0(szText);
TsWriteToView(szText);

testD.m_fRe = Phi.real();
testD.m_fIm = Phi.imag();
testC = TsComplexD::TanH(testD);
bRes = (X.real() == testC.Re()) && (X.imag() == testC.Im());

logEntry.m_bResult = bRes;
logEntry.m_szObjectName = _T("tanh(TComplex<float>)");
LogTest(&logEntry);
if (!bRes)
return bRes;

//Test atanh
X = atanh(X);
_stprintf(szText, _T("atanh(X) = %f+i%f\r\n"), X.real(), X.imag());
TRACE0(szText);
TsWriteToView(szText);

bRes = bRes &&  (X.real() > 0.93999) && (X.real() < 0.94001) &&
(X.imag() > 1.77999) && (X.imag() < 1.78001); //result and previous result
logEntry.m_bResult = bRes;
logEntry.m_szObjectName = _T("atanh(TComplex<float>)");
LogTest(&logEntry);
if (!bRes)
return bRes;

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
D = polar(dEff, dPhi); //D = 220*e(i*60[deg])
_stprintf(szText, _T("D = %.0fe**(i3.14/%d) = %f + i%f\r\n"),dEff,iNom,D.real(),D.imag());
TRACE0(szText);
TsWriteToView(szText);

//Test log2
D = logN(C,2); //Returns the logarithm to base 2
_stprintf(szText, _T("D = log2(C) = %f + i%f\r\n"),D.real(),D.imag());
TRACE0(szText);
TsWriteToView(szText);
logEntryBase.m_bResult = bRes; //TODO: Check result
logEntryBase.m_szObjectName = _T("logN()");
logEntryBase.m_szFileName = _T("KMathCst.inl");
LogTest(&logEntryBase);
if (!bRes)
return bRes;

//Test acoth
D = acoth(C); //Returns the hyperbolic arcus cosecant
_stprintf(szText, _T("acoth(C) = %f + i%f\r\n"),D.real(),D.imag());
TRACE0(szText);
TsWriteToView(szText);

logEntry.m_bResult = bRes; //TODO: Check result
logEntry.m_szObjectName = _T("acoth()");
LogTest(&logEntry);
if (!bRes)
return bRes;


logEntryBase.m_szObjectName = _T("GetLineZin()");
logEntryBase.m_szFileName = _T("KZLineIn.cpp");
LogTest(&logEntryBase);
bRes = bRes && logEntryBase.m_bResult;

return bRes;
}*/
