/*$Workfile: TestCommonStringDyn.cpp$: implementation file
  $Revision: 3$ $Date: 2007-06-15 17:28:30$
  $Author: Darko Kolakovic$

  Test debugging and tracing routines.
  Copyright: CommonSoft Inc.
  2004-08-12 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"

extern bool TsWriteToViewLn(LPCTSTR lszText);

extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TestStringHandler();
extern bool TestStringClass();
extern bool TestIsPalindrome();
extern bool TestIsVowel();

//-----------------------------------------------------------------------------
/*Defines the entry point for the console application that validates a string
  class.

  Returns: EXIT_SUCCESS, which represents a value of 0, if successful. Otherwise
  a non-zero error code is returned.
 */
int TestCommonStringDyn()
{
TsWriteToViewLn(_T("Validation of Dynamic String class"));
TsWriteToViewLn(_T(""));

PFUNC_TEST funcTest[] =
  {
  TestStringHandler,
  TestStringClass,
  TestIsPalindrome,
  TestIsVowel
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
 *  3    Biblioteka1.2         2007-06-15 17:28:30  Darko Kolakovic Console traget
 *       fixes
 *  2    Biblioteka1.1         2007-05-31 16:41:22  Darko Kolakovic Test NaN
 *  1    Biblioteka1.0         2004-10-04 13:15:29  Darko           
 * $
 *****************************************************************************/
