/*$Workfile: TestCommonLibrary.cpp$: implementation file
  $Revision: 10$ $Date: 2005-05-16 14:24:17$
  $Author: Darko Kolakovic$

  Defines the entry point for the console application used to test libray
  functionality.
  2003-01 Darko Kolakovic
*/

// Group=Examples

#ifdef _MSC_VER     /*Microsoft Visual Studio C/C++ compiler                 */
  #ifndef _CONSOLE
    #error "define _CONSOLE macro in the project"
  #endif
#endif

#ifdef __GNUG__     /*GNU C++ compiler                                       */
  #ifndef _CONSOLE
    #warning "define _CONSOLE macro in the project"
  #endif
#endif

#include "stdafx.h"

extern bool TsWriteToViewLn(LPCTSTR lszText);
extern int TestCommonAssert(void);
extern "C" int TestCommonStdLib(void);
extern int TestCommonStreamIO();
extern int TestCommonConsole();
extern int TestCommonUtilities();
extern int TestCommonStringDyn();
extern int TestCommonNumeric();
extern int TestCommonDateTime();
extern int TestCommonHtmlIO();

//-----------------------------------------------------------------------------
/*Invokes different test routines used to validate functionality of the library.

  Returns: EXIT_SUCCESS, which represents a value of 0, if successful. Otherwise
  a non-zero error code is returned.
 */
int TestCommonLibrary()
{

//test recepies
int (* funcTest[])(void) =
  {
  TestCommonAssert,   //validates different debugging and tracing routines
  TestCommonStdLib,   //validates different C Standard Library routines
  TestCommonStreamIO, //validates routines using standard stream I/O.
  TestCommonConsole,  //validates different console helper routines.
  TestCommonUtilities,//validate various helper functions.
  TestCommonStringDyn,//validates a string class
  TestCommonNumeric,  //Validates different numerical methods
  TestCommonDateTime, //validates Date and Time conversions
  TestCommonHtmlIO,   //validates HTML and XML parsing
  };

  //Run all test scripts
int iTestCount = 0;
while (iTestCount < (sizeof(funcTest)/sizeof(PFUNC_TEST)) )
  {
  std::_tcout << _T("Test ") << iTestCount << _T(": ");
  TsWriteToViewLn(_T("Start--------"));
  bool bResult =
    ((funcTest[iTestCount] != NULL) && (funcTest[iTestCount]()==EXIT_SUCCESS));

  TsWriteToViewLn(_T("End of test-----------"));

  if (bResult)
    {
    TsWriteToViewLn(LOG_SUCCESS);
    TsWriteToViewLn(_T(""));
    }
  else
    {
    TsWriteToViewLn(LOG_FAILURE);
    }

  iTestCount++;
  }

return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log:
 *  10   Biblioteka1.9         2005-05-16 14:24:17  Darko Kolakovic new test
 *  9    Biblioteka1.8         2005-03-17 00:44:58  Darko           Test HTML IO
 *  8    Biblioteka1.7         2005-03-11 17:17:28  Darko Kolakovic Added Console
 *       project
 *  7    Biblioteka1.6         2004-10-08 12:36:43  Darko           added
 *       TestDateTime
 *  6    Biblioteka1.5         2004-10-04 23:42:12  Darko           Added numeric
 *       test script
 *  5    Biblioteka1.4         2004-10-04 13:11:07  Darko           Renamed test
 *       script to TestCommonLibrary
 *  4    Biblioteka1.3         2004-10-04 13:10:25  Darko
 *  3    Biblioteka1.2         2004-09-30 15:47:56  Darko           inserted global
 *       CTestLog
 *  2    Biblioteka1.1         2004-09-28 14:03:27  Darko           replaced cout
 *       with _tcout
 *  1    Biblioteka1.0         2004-06-03 14:29:38  Darko
 * $
 *****************************************************************************/

