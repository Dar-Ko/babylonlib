/*$Workfile: TestCommonStdLib.c$: implementation file
  $Revision: 4$ $Date: 2004-11-25 20:57:40$
  $Author: Darko$

  Source file that includes the standard includes and globals used in various
  builds. Object file will contain the pre-compiled type information.
  Reference any additional headers you need in stdafx.h and not in this file.

  Copyright: CommonSoft Inc.
  2004-08-14 Darko Kolakovic
*/

/* Group=Examples */

/*Microsoft C Compilers */
#ifdef _MSC_VER
  #include "stdafx.h" /*CTestLog class                          */
#endif
extern bool TsWriteToViewLn(LPCTSTR lszText);

extern bool TestLimits();
//extern bool TestTraceC();

//-----------------------------------------------------------------------------
/*Validates different C Standard Library routines. 
  Defines the entry point for the test.

  Returns: EXIT_SUCCESS, which represents a value of 0, if succesfull. Otherwise
  a non-zero error code is returned.
 */
int TestCommonStdLib()
{
TsWriteToViewLn(_T("Validation of standard C routines"));
TsWriteToViewLn(_T(""));

PFUNC_TEST funcTest[] = {NULL};
  {
  TestLimits//,
  //TestTraceC
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
 *  4    Biblioteka1.3         2004-11-25 20:57:40  Darko           TestLimits
 *       added
 *  3    Biblioteka1.2         2004-10-04 11:51:17  Darko           Renamed test
 *       script to TestCommonStdLib
 *  2    Biblioteka1.1         2004-10-04 11:50:55  Darko           
 *  1    Biblioteka1.0         2004-09-14 11:54:50  Darko           
 * $
 *****************************************************************************/
