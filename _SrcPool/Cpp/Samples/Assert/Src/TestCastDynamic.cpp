/*$Workfile: TestCastDynamic.cpp$: implementation file
  $Revision: 4$ $Date: 2004-11-23 16:51:26$
  $Author: Darko Kolakovic$

  Test C++ compiler conformance.
  Copyright: CommonSoft Inc.
  2004-09-13 Darko Kolakovic
*/

/* Group=Examples                                                            */

#ifdef __GNUG__ /*GNU C++ compiler */
  #include <typeinfo>
#endif // __GNUG__
#include "TestConformance.h"
#ifndef _T
  #include "KTChar.h"
#endif
#ifndef LOG_EOT
  #include "KTestLog.h"
#endif

extern bool TsWriteToViewLn(LPCTSTR lszText);
bool TestCastDynamic();

class CTestCastDynamicA
  {
  public:
    CTestCastDynamicA() {};
    virtual ~CTestCastDynamicA() {};
  };

class CTestCastDynamicB : public CTestCastDynamicA
  {
  public:
    CTestCastDynamicB() {};
    virtual ~CTestCastDynamicB() {};
  };

class CTestCastDynamicC : public CTestCastDynamicB
  {
  public:
    CTestCastDynamicC() {};
    virtual ~CTestCastDynamicC() {};
  };

/*---------------------------------------------------------------------------*/
/*Validates C++ compiler conformance. Compiler will report an error if
  operator dynamic_cast is not supported and HAS_NO_DYNAMIC_CAST is not defined.

        dynamic_cast < type-id > ( expression )
  The dynamic_cast converts the operand expression to an object of type type-id.
  The type-id must be a pointer or a reference to a previously defined class
  type or a “pointer to void”. The type of expression must be a pointer
  if type-id is a pointer, or an l-value if type-id is a reference.

  Returns: true if test is successful; otherwise returns false.
 */
bool TestCastDynamic()
{
#if defined (HAS_NO_DYNAMIC_CAST)
  TsWriteToViewLn(_T("HAS_NO_DYNAMIC_CAST"));
  return true;
#else
  TsWriteToViewLn(_T("TestCastDynamic()"));

  CTestCastDynamicC testC;
  CTestCastDynamicB* pTestB = dynamic_cast<CTestCastDynamicB*>(&testC);
  CTestCastDynamicA* pTestA = dynamic_cast<CTestCastDynamicA*>(&testC);

  TsWriteToViewLn(LOG_EOT);

  return (pTestB == pTestA);
#endif
}

/* ////////////////////////////////////////////////////////////////////////// */
/******************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2004-11-22 18:48:16  Darko Kolakovic fixed
 *       unresolved TsWriteToViewLn()
 *  1    Biblioteka1.0         2004-11-22 16:47:06  Darko Kolakovic
 * $
 *****************************************************************************/


