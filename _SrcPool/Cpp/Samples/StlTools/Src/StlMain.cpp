/*$Workfile: S:\_SrcPool\Cpp\Samples\_LibraryTest\Src\_TestMain.cpp$: implementation file
  $Revision: 1.1 $ $Date: 2003/01/31 03:16:58 $
  $Author: ddarko $

  Defines the entry point for the console application used to test libray 
  functionality.
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
#include "KTrace.h"   //TRACE macro
#include "KTypedef.h" //BOOL typedef

extern bool TestLeapYear();
//main()-----------------------------------------------------------------------
/*Validates different date and time routines.

  Returns: EXIT_SUCCESS, which represents a value of 0, if successful. Otherwise
  a non-zero error code is returned.
 */
int _tmain(int argc, 
           TCHAR* argv[]
          )
{
cout << _T("Start Date and Time String") << endl << endl;

if(TestLeapYear())
  cout << "Succeeded." << endl << endl;
else
  {
  cout << "Failed!" << endl;
  return EXIT_FAILURE + 1;
  }


return EXIT_SUCCESS;
}
