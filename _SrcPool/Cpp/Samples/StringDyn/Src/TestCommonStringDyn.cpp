/*$Workfile: TestCommonStringDyn.cpp$: implementation file
  $Revision: 1$ $Date: 2004-10-04 12:15:29$
  $Author: Darko$

  Test debugging and tracing routines.
  Copyright: CommonSoft Inc.
  2004-08-12 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"

extern bool TsWriteToViewLn(LPCTSTR lszText);

extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TestStringHandler();
extern bool TestIsPalindrome();

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
  TestIsPalindrome
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
 *  1    Biblioteka1.0         2004-10-04 12:15:29  Darko           
 * $
 *****************************************************************************/
