/*$Workfile: main.cpp$: implementation file
  $Revision: 10$ $Date: 2004-10-08 12:33:25$
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

#include "stdafx.h"
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern int TestCommonDateTime();


//main()-----------------------------------------------------------------------
/*Defines the entry point for the console application that validates different
  date and time routines.

  Returns: EXIT_SUCCESS, which represents a value of 0, if successful. Otherwise
  a non-zero error code is returned.
 */
int main()
{
TsWriteToViewLn(_T("Start Date and Time Tests"));
TsWriteToViewLn(_T(""));
int nRetCode = EXIT_SUCCESS;

nRetCode = TestCommonDateTime();

return nRetCode;
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
