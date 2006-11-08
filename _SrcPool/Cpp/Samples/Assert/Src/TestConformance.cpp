/*$Workfile: TestConformance.cpp$: implementation file
  $Revision: 4$ $Date: 2005-03-21 15:01:00$
  $Author: Darko Kolakovic$

  Validates the conformance of a C++ compiler.
  Copyright: CommonSoft Inc.
  2004-09-13 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"

extern bool TsWriteToViewLn(LPCTSTR lszText);

extern bool TestCastConst();
extern bool TestCastStatic();
extern bool TestCastDynamic();
extern bool TestCastReinterpret();
extern bool TestCastOverload();
extern bool TestKeywordNamespace();
extern bool TestKeywordTypename();
extern bool TestKeywordExplicit();
extern bool TestKeywordMutable();

int TestCppConformance(void);

//-----------------------------------------------------------------------------
/*Validates the conformance of a C++ compiler.
  Defines the entry point for the test.

  Returns: EXIT_SUCCESS, which represents a value of 0, if succesfull. Otherwise
  a non-zero error code is returned.
 */
int TestCppConformance()
{
TsWriteToViewLn(_T("Evaluation of a C++ compiler"));
TsWriteToViewLn(_T(""));

PFUNC_TEST funcTest[] =
  {
  TestCastConst,
  TestCastStatic,
  TestCastDynamic,
  TestCastReinterpret,
  TestCastOverload,
  TestKeywordNamespace,
  TestKeywordTypename,
  TestKeywordExplicit,
  TestKeywordMutable

  };

int iTestCount = 0;
while (iTestCount < (sizeof(funcTest)/sizeof(PFUNC_TEST)) )
  {
  if ((funcTest[iTestCount] != NULL) && funcTest[iTestCount]())
    {
    TsWriteToViewLn(LOG_SUCCESS);
    TsWriteToViewLn(_T(""));
    }
  else
    {
    TsWriteToViewLn(LOG_FAILURE);
    return EXIT_FAILURE + 1 + iTestCount;
    }
  iTestCount++;
  }

return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2004-11-22 18:48:23  Darko Kolakovic fixed
 *       unresolved TsWriteToViewLn()
 *  1    Biblioteka1.0         2004-11-22 16:47:11  Darko Kolakovic
 * $
 *****************************************************************************/
