/*$Workfile: main.cpp$: implementation file
  $Revision: 4$ $Date: 2005-03-11 03:11:29$
  $Author: Darko$

  Test debugging and tracing routines.
  Copyright: CommonSoft Inc.
  2004-08-12 Darko Kolakovic
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

extern int TestCommonAssert();
extern int TestCppConformance();

//-----------------------------------------------------------------------------
/*Validates different debugging and tracing routines. 
  Defines the entry point for the console application.

  Returns: EXIT_SUCCESS, which represents a value of 0, if succesfull. Otherwise
  a non-zero error code is returned.
 */
int main()
{
int nRetCode = TestCppConformance();
if (nRetCode == EXIT_SUCCESS)
  nRetCode = TestCommonAssert();
return nRetCode;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  4    Biblioteka1.3         2005-03-11 03:11:29  Darko           fixed typo
 *  3    Biblioteka1.2         2004-11-23 16:51:46  Darko Kolakovic fixed MSVC
 *       build
 *  2    Biblioteka1.1         2004-10-04 12:52:45  Darko           Renamed test
 *       script to TestCommonAssert
 *  1    Biblioteka1.0         2004-08-23 17:57:45  Darko           
 * $
 *****************************************************************************/
