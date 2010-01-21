/*$Workfile: TestCommonService.cpp$: implementation file
  $Revision: 1.1 $ $Date: 2010/01/21 21:51:53 $
  $Author: ddarko $

  Test system service (deamon) routines.
  Copyright: CommonSoft Inc.
  2007-02-02 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"

extern bool TsWriteToViewLn(LPCTSTR lszText);
#ifdef _WIN32
  extern bool TestWinService();
#endif

int TestCommonService(int argc, TCHAR* argv[]);
int TestCommonService();

//-----------------------------------------------------------------------------
/*Validates different system service (deamon) routines.
Defines the entry point for an automated test.

Returns: EXIT_SUCCESS, which represents a value of 0, if successful. Otherwise
a non-zero error code is returned.
*/
int TestCommonService()
{
return TestCommonService(0, NULL);
}

//-----------------------------------------------------------------------------
/*Validates different system service (deamon) routines.
  Defines the entry point for the test.

  Returns: EXIT_SUCCESS, which represents a value of 0, if successful. Otherwise
  a non-zero error code is returned.
 */
int TestCommonService(int argc, //[in] specifies how many arguments are passed
                          // to the program from the command line. The value of
                          // argc is at least one: the program name.
                      TCHAR* argv[] //[in] the program arguments as an array of
                          //pointers to null-terminated strings. The first string
                          //(argv[0]) is the program name. The end of the array
                          //(argv[argc]) is indicated by a NULL pointer.
                      )
{
TsWriteToViewLn(_T("Validation of system service methods"));
TsWriteToViewLn(_T(""));

PFUNC_TEST funcTest[] =
  {
  #ifdef _WIN32
    TestWinService
  #else
    NULL  //Break testing
  #endif
  
  };
if (funcTest != NULL)
  {
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
      return EXIT_FAILURE + iTestCount;
      }
    iTestCount++;
    }
  }
else
  TsWriteToViewLn(_T("No tests are defined."));
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
