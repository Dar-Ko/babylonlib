/*$Workfile: TestKeywordTypename.cpp$: implementation file
  $Revision: 2$ $Date: 2004-11-23 16:51:43$
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
bool TestKeywordTypename();

class CTestKeywordTypenameT
  {
  public:
    typedef long TESTTYPE;
  };


#if !defined (HAS_NO_EXPLICIT_KEYWORD)
  template <class T> class CTestKeywordTypenameA
    {
    public:
      typedef typename T::TESTTYPE A; //treat A as a type

      CTestKeywordTypenameA(const A& aValue) { m_aValue = aValue; };
      virtual ~CTestKeywordTypenameA() {};
      A m_aValue;
    };
#endif

/*---------------------------------------------------------------------------*/
/*Validates C++ compiler conformance. Compiler will report an error if
  typename keyword is not supported and HAS_NO_TYPENAME_KEYWORD is not defined.

  The typename keyword tells the compiler that an unknown identifier
  in a template definition, is a type.

  Returns: true if test is successful; otherwise returns false.
 */
bool TestKeywordTypename()
{
#if defined (HAS_NO_EXPLICIT_KEYWORD)
  TsWriteToViewLn(_T("HAS_NO_TYPENAME_KEYWORD"));
  return true;
#else
  TsWriteToViewLn(_T("TestKeywordTypename()"));

  CTestKeywordTypenameA<CTestKeywordTypenameT> testA(42);

  TsWriteToViewLn(LOG_EOT);

  return (testA.m_aValue == 42);
#endif
}

/* ////////////////////////////////////////////////////////////////////////// */
/******************************************************************************
 * $Log: 
 *  2    Biblioteka1.1         2004-11-23 16:51:43  Darko Kolakovic fixed MSVC
 *       build
 *  1    Biblioteka1.0         2004-11-23 14:04:19  Darko Kolakovic 
 * $
 *****************************************************************************/
