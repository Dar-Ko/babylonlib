/*$Workfile: main.cpp$: implementation file
  $Revision: 7$ $Date: 2004-10-08 11:36:13$
  $Author: Darko$

  Console application used to test dynamic string classes.
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
#pragma message ("   #include " __FILE__ )

#include "stdafx.h"
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern int TestCommonStringDyn();

//main()-----------------------------------------------------------------------
/*Defines the entry point for the console application that validates 
  manipulations with a string objects.

  Returns: EXIT_SUCCESS, which represents a value of 0, if successful. Otherwise
  a non-zero error code is returned.
 */
int main()
{
TsWriteToViewLn(_T("Start Dynamic String Tests"));
TsWriteToViewLn(_T(""));
int nRetCode = EXIT_SUCCESS;

nRetCode = TestCommonStringDyn();

return nRetCode;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  7    Biblioteka1.6         2004-10-08 11:36:13  Darko           comment
 *  6    Biblioteka1.5         2004-10-04 12:15:58  Darko           moved to
 *       TestCommonnStringDyn
 *  5    Biblioteka1.4         2004-10-01 21:59:44  Darko           deleted pragma
 *  4    Biblioteka1.3         2004-06-08 15:37:21  Darko          
 *       TestIsPalindrome()
 *  3    Biblioteka1.2         2004-06-08 15:36:40  Darko          
 *       TestIsPalindrome()
 *  2    Biblioteka1.1         2004-06-04 23:40:51  Darko          
 *       TestStringHandler()
 *  1    Biblioteka1.0         2004-06-03 13:31:37  Darko           
 * $
 *****************************************************************************/
