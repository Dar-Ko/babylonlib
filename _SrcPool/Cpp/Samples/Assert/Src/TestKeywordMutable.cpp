/*$Workfile: TestKeywordMutable.cpp$: implementation file
  $Revision: 2$ $Date: 2004-11-23 15:51:39$
  $Author: Darko Kolakovic$

  Test C++ compiler conformance.
  Copyright: CommonSoft Inc.
  2004-09-13 Darko Kolakovic
*/

/* Group=Examples                                                            */

#include "TestConformance.h"
#ifndef _T
  #include "KTChar.h"
#endif
#ifndef LOG_EOT
  #include "KTestLog.h"
#endif

extern bool TsWriteToViewLn(LPCTSTR lszText);
bool TestKeywordMutable();

#if !defined (HAS_NO_MUTABLE_KEYWORD)
  class CTestKeywordMutableA
    {
    public:
      CTestKeywordMutableA() { m_iValue = 0;};
      CTestKeywordMutableA(int iValue) /*const*/
       { m_iValue = iValue; }
      virtual ~CTestKeywordMutableA() {};
      mutable int m_iValue;
    };
#endif

/*---------------------------------------------------------------------------*/
/*Validates C++ compiler conformance. Compiler will report an error if
  mutable keyword is not supported and HAS_NO_MUTABLE_KEYWORD is not defined.

  The mutable keyword can only be applied to non-static and non-const data
  members of a class. If a data member is declared mutable, then it is legal to
  assign a value to this data member from a const member function.

  Returns: true if test is successful; otherwise returns false.
 */
bool TestKeywordMutable()
{
#if defined (HAS_NO_MUTABLE_KEYWORD)
  TsWriteToViewLn(_T("HAS_NO_MUTABLE_KEYWORD"));
  return true;
#else
  TsWriteToViewLn(_T("TestKeywordMutable()"));

  CTestKeywordMutableA testA;
  CTestKeywordMutableA testB(42);

  TsWriteToViewLn(LOG_EOT);

  return (testB.m_iValue == 42);
#endif
}

/* ////////////////////////////////////////////////////////////////////////// */
/******************************************************************************
 * $Log: 
 *  2    Biblioteka1.1         2004-11-23 15:51:39  Darko Kolakovic fixed MSVC
 *       build
 *  1    Biblioteka1.0         2004-11-23 13:04:15  Darko Kolakovic 
 * $
 *****************************************************************************/


