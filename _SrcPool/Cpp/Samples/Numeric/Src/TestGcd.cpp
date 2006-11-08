/*$Workfile: TestGcd.cpp$: implementation file
  $Revision: 9$ $Date: 2005-06-20 17:21:21$
  $Author: Darko Kolakovic$

  Test greatest common divisor calculation
  Copyright: CommonSoft Inc.
  2005-05-22 Darko Kolakovic
*/
// Group=Examples

#include "stdafx.h"
#include "KTrace.h"        //ASSERT macro
#include "STL/KBoolStream.h"
#ifndef KSTL_IO
  #include "STL/KOStream.h"
#endif
#include "KTypedef.h" //int64 typedef
#include <math.h> //fmod()  TODO: move to KMatGcdDouble.inl
#include "KMatGcd.h"  //GreatestCommonDivisor() template

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(const int& iValue);
extern bool TsWriteToViewLn(const int& iValue);
extern "C" long gcd(long Operand1, long Operand2);

bool TestGcd();
long test_gcd(long lOperand1, long lOperand2);

template <typename DATATYPE>
struct TestGcdData
  {
  DATATYPE m_lOp1; //first operand
  DATATYPE m_lOp2; //second operand
  DATATYPE m_lGcd; //greatest common divisor
  };

//------------------------------------------------------------------------------
/*Test greatest common divisor calculation. The greatest common divisor (gcd) or
  highest common factor (hcf) of two integers which are not both zero is the
  largest integer that divides both numbers.

  Returns: true if successful, otherwise returns false.
 */
bool TestGcd()
{
TsWriteToViewLn(_T("TestGcd()"));

bool bRes = true;
const unsigned int TESTCOUNT = 20;
  //numbers to test
TestGcdData<long> testGcd [TESTCOUNT] =
  {
    {12, 18,  6},       // 0
    {-4, 14,  2},       // 1 neg, pos
    { 0,  7,  7},       // 2 0, odd
    { 2,  0,  2},       // 3 even, 0
    {36, 45,  9},       // 4 even, odd
    {63, 27,  9},       // 5 odd, odd
    { 5,  2,  1},       // 6
    { 7,  1,  1},       // 7
    {24, 36, 12},       // 8
    {13,  5,  1},       // 9 prime, prime
    {16,256, 16},       //10
    { 5, 10,  5},       //11
    {2322,654,6},       //12
    { 0,  0,  0},       //13 0, 0
    {2147483647, 5, 1}, //14 max odd
    {2147483647, 4, 1}, //15
    {2147483647, 3, 1}, //16
    {2147483647,2147483646, 1}, //17 max odd, max even
    {40902, 24140, 34}, //18 Knuth
    {756, 1386, 126}    //19
  };

const unsigned int TESTCOUNT64 = 5;
TestGcdData<int64> testGcd64 [TESTCOUNT64] = //TODO: 64-bit test
  {
    {4294967295, 5, 5}, //12    truncated' to 'long'(-1)
    {4294967295, 4, 1}, //13    truncated' to 'long'(-1)
    {4294967295, 3, 3}, //14    truncated' to 'long'(-1)
    {4294967295,2147483646, 3}, //15  truncated' to 'long'(-1)
    {51474836488992, 3, 3}      //16 requires int64 truncated' to 'long'(-346553568)
  };

TestGcdData<double> testGcdReal [TESTCOUNT64] =
  {
    {4294967295, 5, 5},         // 0
    {4294967295, 4, 1},         // 1
    {4294967295, 3, 3},         // 2
    {4294967295,2147483646, 3}, // 3
    {51474836488992, 3, 3}      // 4
  };

//Test helper function
int i = 0;
while (( i < TESTCOUNT ) && bRes)
  {
  long lGcd = test_gcd(testGcd[i].m_lOp1, testGcd[i].m_lOp2);
  bRes = (testGcd[i].m_lGcd == lGcd);
  i++;
  }

//Test template function
TESTENTRY logEntry =
  {_T("GreatestCommonDivisor<long>()"), _T("KMatGcd.h"), false};

i = 0;
while (( i < TESTCOUNT ) && bRes)
  {
  long lGcd = GreatestCommonDivisor<long>(testGcd[i].m_lOp1, testGcd[i].m_lOp2);
  bRes = (testGcd[i].m_lGcd == lGcd);
  std::_tcout << _T("gcd(") << testGcd[i].m_lOp1 << _T(", ")
                      << testGcd[i].m_lOp2 << _T(") = ")
        << lGcd << _T(" == ") << (tbool)bRes << std::endl;
  i++;
  }
logEntry.m_bResult = bRes;
LogTest(&logEntry); //Write test log

logEntry.m_szObjectName = _T("GreatestCommonDivisor<double>()");
i = 0;
while (( i < TESTCOUNT ) && bRes)
  {
  double dGcd = GreatestCommonDivisor<double>(testGcd[i].m_lOp1, testGcd[i].m_lOp2);
  bRes = (dGcd == (double)testGcd[i].m_lGcd);
  std::_tcout << _T("gcd(") << (double)testGcd[i].m_lOp1 << _T(", ")
                            << (double)testGcd[i].m_lOp2 << _T(") = ")
        << dGcd << _T(" == ") << (tbool)bRes << std::endl;
  i++;
  }
i = 0;
while (( i < TESTCOUNT64 ) && bRes)
  {
  double dGcd = GreatestCommonDivisor<double>(testGcdReal[i].m_lOp1, testGcdReal[i].m_lOp2);
  bRes = (testGcdReal[i].m_lGcd == dGcd);
  std::_tcout << _T("gcd(") << testGcdReal[i].m_lOp1 << _T(", ")
                            << testGcdReal[i].m_lOp2 << _T(") = ")
        << dGcd << _T(" == ") << (tbool)bRes << std::endl;
  i++;
  }

if (bRes)
  {
  //Test template Greatest Common Divisor of an array
  logEntry.m_szObjectName = _T("GreatestCommonDivisor<int>(array, count)");
  int nTestArray[] =
    { 1, 0, 1, 5, 7, -13, 32, 48, -60};

  int nGcd = GreatestCommonDivisor<int>(nTestArray, 1);
  if (bRes = (nGcd == 1))
    {
    nGcd = GreatestCommonDivisor<int>(&nTestArray[5], 1);
    bRes = (nGcd == 13);
    }
  
  if (bRes)
    {
    nGcd = GreatestCommonDivisor<int>(nTestArray, 6);
    bRes = (nGcd == 1);

    std::_tcout << _T("gcd( 1, 0, 1, 5, 7, -13) = ")
        << nGcd << _T(" == ") << (tbool)bRes << std::endl;
    }

  if (bRes)
    {
    nGcd = GreatestCommonDivisor<int>(&nTestArray[6], 3);
    bRes = (nGcd == 4);
    }

  logEntry.m_bResult = bRes;
  LogTest(&logEntry); //Write test log
  }

//Test gcd() function
logEntry.m_szObjectName = _T("gcd()");
logEntry.m_szFileName = _T("KMatGcd.c");

i = 0;
while (( i < TESTCOUNT ) && bRes)
  {
  long lGcd = gcd(testGcd[i].m_lOp1, testGcd[i].m_lOp2);

  bRes = (testGcd[i].m_lGcd == lGcd);
  i++;
  }
logEntry.m_bResult = bRes;
LogTest(&logEntry); //Write test log

TsWriteToView(LOG_EOT);
TsWriteToView(_T("\r\n"));
return bRes;
}

//-----------------------------------------------------------------------------
/*Calculate Greatest Common Divisor (gcd), using Euclid's algorithm.

  Returns: Greatest Common Divisor (gcd).
 */
long test_gcd(long lOperand1, //[in] first operand
              long lOperand2  //[in] second operand
             )
{
  //Get absoulte values of operands
if (lOperand1 < 0)
  lOperand1 = -lOperand1;

if (lOperand2 < 0)
  lOperand2 = -lOperand2;

while (lOperand2 != 0)
  {
  long lRemainder = lOperand1 % lOperand2;
  lOperand1 = lOperand2;
  lOperand2 = lRemainder;
  }

return lOperand1; //return gcd
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2005-05-30 09:51:39  Darko Kolakovic
 * $
 ******************************************************************************/
