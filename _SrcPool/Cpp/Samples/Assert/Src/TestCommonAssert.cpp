/*$Workfile: TestCommonAssert.cpp$: implementation file
  $Revision: 10$ $Date: 2004-11-22 16:47:56$
  $Author: Darko Kolakovic$

  Test debugging and tracing routines.
  Copyright: CommonSoft Inc.
  2004-08-12 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"

extern bool TsWriteToViewLn(LPCTSTR lszText);

extern bool TestPredefinedMacros();
extern "C" bool TestPredefinedMacrosC();
extern bool TestAssert();
extern "C" bool TestAssertC();
extern bool TestTrace();
extern "C" bool TestTraceC();
extern "C" bool TestEndian();

int TestCommonAssert(void);

//-----------------------------------------------------------------------------
/*Validates different debugging and tracing routines.
  Defines the entry point for the test.

  Returns: EXIT_SUCCESS, which represents a value of 0, if succesfull. Otherwise
  a non-zero error code is returned.
 */
int TestCommonAssert()
{
TsWriteToViewLn(_T("Validation of debugging and tracing methods"));
TsWriteToViewLn(_T(""));

PFUNC_TEST funcTest[] =
  {
  TestPredefinedMacrosC,
  TestPredefinedMacros,
  TestAssert,
  TestAssertC,
  TestTrace,
  TestTraceC,
  TestEndian
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
 *  9    Biblioteka1.8         2004-10-22 12:46:48  Darko Kolakovic CodeWarrior
 *  8    Biblioteka1.7         2004-10-04 12:52:43  Darko           Renamed test
 *       script to TestCommonAssert
 *  7    Biblioteka1.6         2004-10-04 12:52:18  Darko
 *  6    Biblioteka1.5         2004-09-28 13:59:20  Darko           comments
 *  5    Biblioteka1.4         2004-09-14 12:55:38  Darko           Comment
 *  4    Biblioteka1.3         2004-09-13 15:29:50  Darko           Added
 *       TestTrace()
 *  3    Biblioteka1.2         2004-08-31 13:06:15  Darko           Added
 *       TestPredefinedMacros
 *  2    Biblioteka1.1         2004-08-26 13:20:37  Darko           Added C test
 *  1    Biblioteka1.0         2004-08-23 17:57:15  Darko
 * $
 *****************************************************************************/
