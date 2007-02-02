/*$Workfile: TestCommonConsole.cpp$: implementation file
  $Revision: 4$ $Date: 2007-02-02 13:20:14$
  $Author: Darko Kolakovic$

  Test console helper.
  Copyright: CommonSoft Inc.
  2005-03-01 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"

extern bool TsWriteToViewLn(LPCTSTR lszText);

extern bool TestCmdLineParser(int argc, TCHAR* argv[]);
extern "C" bool TestAscii();


int TestCommonConsole(int argc, TCHAR* argv[]);
int TestCommonConsole();

//-----------------------------------------------------------------------------
/*Validates different console helper routines.
  Defines the entry point for an automated test.

  Returns: EXIT_SUCCESS, which represents a value of 0, if succesful. Otherwise
  a non-zero error code is returned.
 */
int TestCommonConsole()
{
return TestCommonConsole(0, NULL);
}

//-----------------------------------------------------------------------------
/*Validates different console helper routines.
  Defines the entry point for the test.

  Returns: EXIT_SUCCESS, which represents a value of 0, if succesful. Otherwise
  a non-zero error code is returned.
 */
int TestCommonConsole(int argc, //[in] specifies how many arguments are passed
                          // to the program from the command line. The value of
                          // argc is at least one: the program name.
                      TCHAR* argv[] //[in] the program arguments as an array of
                          //pointers to null-terminated strings. The first string
                          //(argv[0]) is the program name. The end of the array
                          //(argv[argc]) is indicated by a NULL pointer.
                      )
{
TsWriteToViewLn(_T("Validation of console utility methods"));
TsWriteToViewLn(_T(""));

if (TestCmdLineParser(argc, argv))
  {
  TsWriteToViewLn(LOG_SUCCESS);
  TsWriteToViewLn(_T(""));
  }
else
  {
  TsWriteToViewLn(LOG_FAILURE);
  return EXIT_FAILURE + 1;
  }


PFUNC_TEST funcTest[] =
  {
//  TestTraceC,
  TestAscii
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
 *  2    Biblioteka1.1         2005-03-11 16:17:25  Darko Kolakovic Added Console
 *       project
 *  1    Biblioteka1.0         2005-03-11 02:13:52  Darko
 * $
 *****************************************************************************/
