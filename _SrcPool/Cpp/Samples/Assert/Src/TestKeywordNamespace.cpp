/*$Workfile: TestKeywordNamespace.cpp$: implementation file
  $Revision: 2$ $Date: 2004-11-23 16:51:41$
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
bool TestKeywordNamespace();

#if !defined (HAS_NO_NAMESPACE_KEYWORD)
  namespace TestNamespaceA
    {
    int TestKeywordNamespace(int iTestValue);
    int TestKeywordNamespace(int iTestValue)
      {
      return iTestValue;
      }
    }

  namespace TestNamespaceB
    {
    int TestKeywordNamespace(int iTestValue);
    int TestKeywordNamespace(int iTestValue)
      {
      return iTestValue;
      }
    }
#endif

/*---------------------------------------------------------------------------*/
/*Validates C++ compiler conformance. Compiler will report an error if
  namespace keyword is not supported and HAS_NO_NAMESPACE_KEYWORD is not defined.

  The namespace declaration identifies and assigns a unique name to
  a user-declared namespace. Such namespaces are used to solve the problem of
  name collision in large programs and libraries.

  Returns: true if test is successful; otherwise returns false.
 */
bool TestKeywordNamespace()
{
#if defined (HAS_NO_NAMESPACE_KEYWORD)
  TsWriteToViewLn(_T("HAS_NO_NAMESPACE_KEYWORD"));
  return true;
#else
  TsWriteToViewLn(_T("TestKeywordNamespace()"));
  int iTestA = TestNamespaceA::TestKeywordNamespace(42);
  int iTestB = TestNamespaceB::TestKeywordNamespace(43);
  bool bResult = (iTestA < iTestB);
  if (bResult)
    {
    using namespace TestNamespaceA;
    iTestA = TestKeywordNamespace(43);
    bResult = (iTestA == iTestB);
    }
  TsWriteToViewLn(LOG_EOT);

  return bResult;
#endif
}

/* ////////////////////////////////////////////////////////////////////////// */
/******************************************************************************
 * $Log: 
 *  2    Biblioteka1.1         2004-11-23 16:51:41  Darko Kolakovic fixed MSVC
 *       build
 *  1    Biblioteka1.0         2004-11-23 14:04:17  Darko Kolakovic 
 * $
 *****************************************************************************/
