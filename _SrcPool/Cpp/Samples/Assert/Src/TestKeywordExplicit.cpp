/*$Workfile: TestKeywordExplicit.cpp$: implementation file
  $Revision: 2$ $Date: 2004-11-23 16:51:36$
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
bool TestKeywordExplicit();

#if !defined (HAS_NO_EXPLICIT_KEYWORD)
  class CTestKeywordExplicitA
    {
    public:
      CTestKeywordExplicitA() { m_iValue =0;};
      explicit CTestKeywordExplicitA(int iValue) {m_iValue = iValue;}
      virtual ~CTestKeywordExplicitA() {};
      int m_iValue;
    };
#endif

/*---------------------------------------------------------------------------*/
/*Validates C++ compiler conformance. Compiler will report an error if
  explicit keyword is not supported and HAS_NO_EXPLICIT_KEYWORD is not defined.

  The explicit keyword is a declaration specifier that can only be applied to
  in-class constructor declarations. Constructors declared explicit will
  not be considered for implicit conversions.

  Returns: true if test is successful; otherwise returns false.
 */
bool TestKeywordExplicit()
{
#if defined (HAS_NO_EXPLICIT_KEYWORD)
  TsWriteToViewLn(_T("HAS_NO_EXPLICIT_KEYWORD"));
  return true;
#else
  TsWriteToViewLn(_T("TestKeywordExplicit()"));

  CTestKeywordExplicitA testA;
  CTestKeywordExplicitA testB(42);

  TsWriteToViewLn(LOG_EOT);

  return (testB.m_iValue == 42);
#endif
}

/* ////////////////////////////////////////////////////////////////////////// */
/******************************************************************************
 * $Log: 
 *  2    Biblioteka1.1         2004-11-23 16:51:36  Darko Kolakovic fixed MSVC
 *       build
 *  1    Biblioteka1.0         2004-11-23 14:04:13  Darko Kolakovic 
 * $
 *****************************************************************************/

