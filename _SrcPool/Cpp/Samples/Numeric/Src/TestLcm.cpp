/*$Workfile: TestLcm.cpp$: implementation file
  $Revision: 2$ $Date: 2005-06-20 17:21:14$
  $Author: Darko Kolakovic$

  Test least common multiple calculation
  Copyright: CommonSoft Inc.
  2005-06-20 Darko Kolakovic
*/
// Group=Examples

#include "stdafx.h"
#include "KTrace.h"        //ASSERT macro
#include "STL/KBoolStream.h"
#ifndef KSTL_IO
  #include "STL/KOStream.h"
#endif
#include "KTypedef.h" //int64 typedef
#include <math.h> //fmod() TODO: move to KMatGcdDouble.inl
#include "KMatLcm.h"  //lcm() template

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(const int& iValue);
extern bool TsWriteToViewLn(const int& iValue);

bool TestLcm();

template <typename DATATYPE>
struct TestLcmData
  {
  DATATYPE m_lOp1; //first operand
  DATATYPE m_lOp2; //second operand
  DATATYPE m_lLcm; //least common multiple
  };

//------------------------------------------------------------------------------
/*Test least common multiple calculation.
  The least common multiple (lcm) is the smallest positive integer which is
  a multiple of given integers.

  Returns: true if successful, otherwise returns false.
 */
bool TestLcm()
{
TsWriteToViewLn(_T("TestLcm()"));

bool bRes = true;
const unsigned int TESTCOUNT = 10;
  //numbers to test
TestLcmData<long> testLcm [TESTCOUNT] =
  {
    {-12, 30, 60},       // 0  (-A,  B)
    {  0,  0,  0},       // 1  ( 0,  0)
    {  0, 30,  0},       // 2  ( 0,  B)
    { 12,  0,  0},       // 3  ( A,  0)
    {  1, 30, 30},       // 4  ( 1,  B)
    { 12,  1, 12},       // 5  ( A,  1)
    { 12, 30, 60},       // 6  ( A,  B)
    { 12,-30, 60},       // 7  ( A, -B)
    { 30, 77,2310},      // 8
    {329, 990, 325710}   // 9
  };

/*TODO: lcm test
const unsigned int TESTCOUNT64 = 5;
TestLcmData<int64> testLcm64 [TESTCOUNT64] = //TODO: 64-bit test
  {
    {4294967295, 5, ?}, //12    truncated' to 'long'(-1)
    {4294967295, 4, ?}, //13    truncated' to 'long'(-1)
    {4294967295, 3, 3}, //14    truncated' to 'long'(-1)
    {4294967295,2147483646, ?}, //15  truncated' to 'long'(-1)
    {51474836488992, 3, ?}      //16 requires int64 truncated' to 'long'(-346553568)
  };

TestLcmData<double> testLcmReal [TESTCOUNT64] =
  {
    {4294967295, 5, ?},         // 0
    {4294967295, 4, ?},         // 1
    {4294967295, 3, ?},         // 2
    {4294967295,2147483646, ?}, // 3
    {51474836488992, 3, ?}      // 4
  };
*/

//Test template function
TESTENTRY logEntry =
  {_T("lcm<long>()"), _T("KMatLcm.h"), false};

int i = 0;
while (( i < TESTCOUNT ) && bRes)
  {
  long lLcm = lcm<long>(testLcm[i].m_lOp1, testLcm[i].m_lOp2);
  bRes = (testLcm[i].m_lLcm == lLcm);
  std::_tcout << _T("lcm(") << testLcm[i].m_lOp1 << _T(", ")
                      << testLcm[i].m_lOp2 << _T(") = ")
        << lLcm << _T(" == ") << (tbool)bRes << std::endl;
  i++;
  }
logEntry.m_bResult = bRes;
LogTest(&logEntry); //Write test log

/*
logEntry.m_szObjectName = _T("lcm<double>()");
i = 0;
while (( i < TESTCOUNT ) && bRes)
  {
  double dLcm = GreatestCommonDivisor<double>(testLcm[i].m_lOp1, testLcm[i].m_lOp2);
  bRes = (dLcm == (double)testLcm[i].m_lLcm);
  std::_tcout << _T("lcm(") << (double)testLcm[i].m_lOp1 << _T(", ")
                            << (double)testLcm[i].m_lOp2 << _T(") = ")
        << dLcm << _T(" == ") << (tbool)bRes << std::endl;
  i++;
  }
i = 0;
while (( i < TESTCOUNT64 ) && bRes)
  {
  double dLcm = lcm<double>(testLcmReal[i].m_lOp1, testLcmReal[i].m_lOp2);
  bRes = (testLcmReal[i].m_lLcm == dLcm);
  std::_tcout << _T("lcmgcd(") << testLcmReal[i].m_lOp1 << _T(", ")
                            << testLcmReal[i].m_lOp2 << _T(") = ")
        << dLcm << _T(" == ") << (tbool)bRes << std::endl;
  i++;
  }
*/

TsWriteToView(LOG_EOT);
TsWriteToView(_T("\r\n"));
return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  2    Biblioteka1.1         2005-06-20 17:21:14  Darko Kolakovic comment
 *  1    Biblioteka1.0         2005-06-20 10:43:29  Darko Kolakovic 
 * $
 ******************************************************************************/
