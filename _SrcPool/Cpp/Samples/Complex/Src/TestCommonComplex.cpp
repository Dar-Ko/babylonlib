/*$Workfile: S:\_SrcPool\Cpp\Samples\Complex\Src\TestCommonComplex.cpp$: implementation file
  $Revision: 1$ $Date: 2007-05-22 17:37:00$
  $Author: Darko Kolakovic$

  Testing complex number calculations.

  Copyright: CommonSoft Inc.
  2004-09-27 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"

extern bool TsWriteToViewLn(LPCTSTR lszText);

extern bool TestComplex();
extern bool TestPointToComplex();

int TestCommonComplex();

//-----------------------------------------------------------------------------
/*Validates complex arithmetics and functions using complex numbers.
  Defines the entry point for the test.

  Returns: EXIT_SUCCESS, which represents a value of 0, if succesful. Otherwise
  a non-zero error code is returned.
 */
int TestCommonComplex()
{
TsWriteToViewLn(_T("Start validation of various complex number calculations"));
TsWriteToViewLn(_T(""));

#ifdef KSTL_IO
  TRACE1(_T("  KSTL_IO version %d.\n"), KSTL_IO);
#else
  TRACE0("  KSTL_IO is not defined.\n");
#endif

PFUNC_TEST funcTest[] =
  {
  TestComplex,
  TestPointToComplex,
  NULL
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
    return EXIT_FAILURE + 50 + iTestCount;
    }
  iTestCount++;
  }

return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log:
 *  6    Biblioteka1.5         2004-10-06 16:01:34  Darko           Unicode mapping
 *  5    Biblioteka1.4         2004-10-04 12:49:12  Darko           Renamed  test
 *       script to TestCommonComplex
 *  4    Biblioteka1.3         2004-10-04 12:47:39  Darko
 *  3    Biblioteka1.2         2004-09-30 15:47:54  Darko           inserted global
 *       CTestLog
 *  2    Biblioteka1.1         2004-09-29 13:23:29  Darko           improved tests
 *  1    Biblioteka1.0         2004-09-28 13:59:58  Darko
 * $
 *****************************************************************************/
