/*$Workfile: S:\_SrcPool\Cpp\Samples\DateTime\Src\TestCommonDateTime.cpp$: implementation file
  $Revision: 1$ $Date: 2004-10-08 12:32:32$
  $Author: Darko$

  Console application used to test various operations with date and time.
  Jan. 90 Darko Kolakovic
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

#ifndef _STL
  #define _STL //include standard streams
#endif

#include "stdafx.h"

#ifndef _STL
  //if standard streams aren't included through stdafx.h, include them here
  #include "KOStream.h"
#endif

extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TestLeapYear();
extern bool TestDateConversion();
extern bool TestDate();
extern bool TestAtoI();
extern bool TestTmConversion();

//-----------------------------------------------------------------------------
/*Defines the entry point for the console application that alidates different
  date and time routines.

  Returns: EXIT_SUCCESS, which represents a value of 0, if successful. Otherwise
  a non-zero error code is returned.
 */
int TestCommonDateTime()
{
TsWriteToViewLn(_T("Date and Time Tests"));
TsWriteToViewLn(_T(""));
PFUNC_TEST funcTest[] =
  {
  TestLeapYear,
  TestAtoI,
  TestDateConversion,
  TestDate,
  TestTmConversion
  };

int iTestCount = 0;
while (iTestCount < (sizeof(funcTest)/sizeof(PFUNC_TEST)) )
  {
  if ((funcTest[iTestCount] != NULL) && funcTest[iTestCount]())
    std::_tcout << LOG_SUCCESS << std::endl << std::endl;
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
 *  6    Biblioteka1.5         2003-09-30 09:14:29  Darko           Test reading
 *       ISO 8601
 *  5    Biblioteka1.4         2003-09-27 12:18:58  Darko
 *       TsWriteToViewLn()
 *  4    Biblioteka1.3         2003-09-25 01:24:45  Darko
 *       TsWriteToViewLn()
 *  3    Biblioteka1.2         2003-09-24 18:42:36  Darko           TestDate()
 *  2    Biblioteka1.1         2003-09-22 21:58:01  Darko           Unicode
 *  1    Biblioteka1.0         2003-01-15 01:29:47  Darko
 * $
 *****************************************************************************/
