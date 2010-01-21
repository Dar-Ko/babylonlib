/*$RCSfile: TestCommonWmi.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2010/01/21 22:18:19 $
  $Author: ddarko $

  Test WMI routines.
  2010-01-01 Darko Kolakovic
*/

// Group=Examples Windows

#include "stdafx.h"

extern bool TsWriteToViewLn(LPCTSTR lszText);
#ifdef _WIN32
  extern bool TestWmi();
#endif

int TestCommonWmi(int argc, TCHAR* argv[]);
int TestCommonWmi();

//-----------------------------------------------------------------------------
/*Validates different Windows Management Instrumentation (WMI) routines.
  Defines the entry point for an automated test.

  Returns: EXIT_SUCCESS, which represents a value of 0, if successful. Otherwise
  a non-zero error code is returned.
*/
int TestCommonWmi()
{
return TestCommonWmi(0, NULL);
}

//-----------------------------------------------------------------------------
/*Validates different Windows Management Instrumentation (WMI) routines..
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
TsWriteToViewLn(_T("Validation of WMI methods"));
TsWriteToViewLn(_T(""));

PFUNC_TEST funcTest[] =
  {
  #ifdef _WIN32
    TestWmi
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
 * $Log: TestCommonWmi.cpp,v $
 * Revision 1.1  2010/01/21 22:18:19  ddarko
 * Created
 *
 *****************************************************************************/
