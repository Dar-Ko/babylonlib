/*$Workfile: TestZAssert.h$: header file
  $Revision: 5$ $Date: 2007-06-08 17:56:12$
  $Author: Darko Kolakovic$

  Complex number validation
  Copyright: CommonSoft Inc.
  2007-05 Darko Kolakovic
*/

// Group=Examples
#ifndef _TESTZASSERT_H_
    //$Workfile: TestZAssert.h$ sentry
  #define _TESTZASSERT_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#include <math.h>
#include "KTestLog.h" //TESTENTRY struct
#include "TestComplex.h" //TsComplexD test complex number class

//Validating function type
typedef TsComplexD (*PFUNCCOMPLEXD_TEST) (const TsComplexD&);
const int TESTSIZE = 27; //number of test values

///////////////////////////////////////////////////////////////////////////////
/*Test class used to automate validation of complex number arithmetic.
 */
template<class TYPE> class TestZAssert : public TESTENTRY, public TsComplexD
{
public:
  TestZAssert(TYPE ReZ = 0, TYPE ImZ = 0, TYPE ReT = 0, TYPE ImT = 0);
  virtual ~TestZAssert();
  //Attributes
  TYPE m_ReZ; //real part of a complex number to validate
  TYPE m_ImZ; //imaginary part of a complex number to validate
  TYPE m_ReT; //real part of the expected result
  TYPE m_ImT; //imaginary part of the expected result
  const double m_dEps; //epsilon error

  //Operations
  bool Validate(TYPE ReZ, TYPE ImZ, TYPE ReT, TYPE ImT);
  bool Validate(PFUNCCOMPLEXD_TEST functValidator);
  double AvgErr() const;
  double AbsErr() const;
  void Write();
  
  operator CComplex() const;
  operator _complex() const;
  operator TComplexBase<TYPE>() const;

  TestZAssert& operator =(const CComplex& Value);
};

//-----------------------------------------------------------------------------
template<class TYPE>
TestZAssert<TYPE>::TestZAssert(TYPE ReZ, TYPE ImZ, TYPE ReT, TYPE ImT) :
m_ReZ(ReZ), m_ImZ(ImZ), TsComplexD(ReZ, ImZ), m_ReT(ReT), m_ImT(ImT), m_dEps(1e-10)
{
}

template<class TYPE>
TestZAssert<TYPE>::~TestZAssert()
{
}

//-----------------------------------------------------------------------------
/*Evaluates complex numbers rounding error
 */
template<class TYPE>
bool TestZAssert<TYPE>::Validate(TYPE ReZ, TYPE ImZ, TYPE ReT, TYPE ImT)
{
if (ReZ == ReT)
  m_bResult = true;
else if ((_isnan((double)ReZ) != 0) &&  (_isnan((double)ReT) != 0))
  m_bResult = true;
else //Check if the error is less or equal to epsilon
  m_bResult = (abs(double(ReZ - ReT)) <= m_dEps);
 
if (m_bResult)
  {
  if (ImZ == ImT)
    m_bResult = true;
  else if ((_isnan((double)ImZ) != 0) &&  (_isnan((double)ImT) != 0))
    m_bResult = true;
  else //Check if the error is less or equal to epsilon
    m_bResult = (abs(double(ImZ - ImT)) <= m_dEps);
  }
  
return m_bResult;
}

template<class TYPE>
bool TestZAssert<TYPE>::Validate(PFUNCCOMPLEXD_TEST functValidator)
{
if (functValidator != NULL)
  {
  TsComplexD CTemp = functValidator(TsComplexD(*this));
  m_ReT = (TYPE)CTemp.Re();
  m_ImT = (TYPE)CTemp.Im();
  //Result of the validated operation is kept in (m_ReZ, m_ImZ);
  //result of the validating operation is kept in (m_ReT, m_ImT).
  return Validate(m_ReZ, m_ImZ, m_ReT, m_ImT);
  }
return (m_bResult = false);
}

//-----------------------------------------------------------------------------
/*Calculate average error.
*/
template<class TYPE>
double TestZAssert<TYPE>::AvgErr() const
{
double AbsZ = sqrt(m_ReZ*(double)m_ReZ + m_ImZ*(double)m_ImZ);
double AbsT = sqrt(m_ReT*(double)m_ReT + m_ImT*(double)m_ImT);
return 2*AbsErr()/(AbsZ + AbsT);
}

//-----------------------------------------------------------------------------
/*Calculate absolute error.
*/
template<class TYPE>
double TestZAssert<TYPE>::AbsErr() const
{
double R = double(m_ReZ - m_ReT);
double I = double(m_ImZ - m_ImT);
return sqrt(R*R+I*I);
}

//-----------------------------------------------------------------------------
template<class TYPE>
void TestZAssert<TYPE>::Write()
{
extern bool TsWriteToView(LPCTSTR lszText);
extern LPTSTR ZtoA(double dReal,double dImag, LPTSTR szResult, unsigned int iSize);
TCHAR szMessage[126];
TsWriteToView(m_szObjectName);
const int BUFFSIZE = 100;
TCHAR szZ[BUFFSIZE];     //input value
TCHAR szOpRes[BUFFSIZE]; //result of the operation
ZtoA(Re(), Im(), szZ, BUFFSIZE);   //Tested value
ZtoA(m_ReZ, m_ImZ, szOpRes, BUFFSIZE); //Result of the operation
//Note: result of the validing operation is kept in (m_ReT, m_ImT)

#ifdef UNICODE
  _stprintf(szMessage, _T(" = f(%ws) = %ws"), szZ, szOpRes);
#else
  _stprintf(szMessage, _T(" = f(%s) = %s"), szZ, szOpRes);
#endif
TsWriteToView(szMessage);
TRACE2(_T("%s%s\n"), m_szObjectName, szMessage);
if (m_bResult)
  TsWriteToView(_T(": OK\r\n"));
else
  {
  _stprintf(szMessage, _T(": Failure. Avg err = %e\r\n"), AvgErr());
  TsWriteToView(szMessage);
  }
}

//-----------------------------------------------------------------------------
template<class TYPE>
TestZAssert<TYPE>::operator CComplex() const
{
//Get values from the base class
return CComplex(Re(), Im());
}

//-----------------------------------------------------------------------------
template<class TYPE>
TestZAssert<TYPE>::operator _complex() const
{
_complex sRes;
sRes.x = Re(); //Get values from the base class
sRes.y = Im();
return sRes;
}

//-----------------------------------------------------------------------------
template<class TYPE>
TestZAssert<TYPE>::operator TComplexBase<TYPE>() const
{
TComplexBase<TYPE> sRes;
sRes.real(Re()); //Get values from the base class
sRes.imag(Im());
return sRes;
}

//-----------------------------------------------------------------------------
template<class TYPE>
TestZAssert<TYPE>& TestZAssert<TYPE>::operator =(const CComplex& Value) 
{
m_ReZ = Value.real(); 
m_ImZ = Value.imag();
return (*this);
}

///////////////////////////////////////////////////////////////////////////////

typedef TestZAssert<double> TestCComplex; //double precision validation
typedef TestZAssert<float>  TestFComplex; //float  precision validation
typedef TestZAssert<int>    TestIComplex; //integer validation

#endif  //_TESTZASSERT_H_

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  5    Biblioteka1.4         2007-06-08 17:56:12  Darko Kolakovic New test cases
 *  4    Biblioteka1.3         2007-06-04 16:58:01  Darko Kolakovic Fixed
 *       validation of NaNs
 *  3    Biblioteka1.2         2007-06-01 17:34:54  Darko Kolakovic Test cases
 *  2    Biblioteka1.1         2007-05-31 16:42:05  Darko Kolakovic operator
 *       CComplex()
 *  1    Biblioteka1.0         2007-05-30 16:45:51  Darko Kolakovic 
 * $
 *****************************************************************************/

