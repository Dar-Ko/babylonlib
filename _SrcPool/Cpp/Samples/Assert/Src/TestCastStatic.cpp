/*$Workfile: TestCastStatic.cpp$: implementation file
  $Revision: 4$ $Date: 2004-11-23 15:51:31$
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
bool TestCastStatic();

class CTestCastStaticA
  {
  public:
    CTestCastStaticA() {};
    virtual ~CTestCastStaticA() {};
  };

class CTestCastStaticB : public CTestCastStaticA
  {
  public:
    CTestCastStaticB() {};
    virtual ~CTestCastStaticB() {};
  };

/*---------------------------------------------------------------------------*/
/*Validates C++ compiler conformance. Compiler will report an error if
  operator static_cast is not supported and HAS_NO_STATIC_CAST is not defined.

        static_cast < type-id > ( expression )
  The static_cast operator converts expression to the type of type-id.
  No run-time type check is made to ensure the safety of the conversion.

  Returns: true if test is successful; otherwise returns false.
 */
bool TestCastStatic()
{
#if defined (HAS_NO_STATIC_CAST)
  TsWriteToViewLn(_T("HAS_NO_STATIC_CAST"));
  return true;
#else
  TsWriteToViewLn(_T("TestCastStatic()"));

  CTestCastStaticB testB;

  //Safe conversion
  CTestCastStaticA* pTestA = static_cast<CTestCastStaticA*>(&testB);

  //Conversion of a reference
  CTestCastStaticB (& testC) (testB);
  CTestCastStaticA* pTestC = static_cast<CTestCastStaticA*>(&testC);

  TsWriteToViewLn(LOG_EOT);

  return (pTestC == pTestA);
#endif
}

/* ////////////////////////////////////////////////////////////////////////// */
/******************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2004-11-22 18:48:21  Darko Kolakovic fixed
 *       unresolved TsWriteToViewLn()
 *  1    Biblioteka1.0         2004-11-22 16:47:09  Darko Kolakovic
 * $
 *****************************************************************************/


