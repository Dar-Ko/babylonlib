/*$Workfile: main.cpp$: implementation file
  $Revision: 1$ $Date: 15/01/2003 12:29:47 AM$
  $Author: Darko$

  Console application used to test various operations with date and time
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

#include <iostream>
#include <iomanip.h>  //std::endl
#include <string>     //std::string
#include "KTrace.h"   //TRACE macro
#include "KTypedef.h" //BOOL typedef

extern bool TestLeapYear();

//TsWriteToView()--------------------------------------------------------------
/*Writes a character string at the console standard output stream.

  Returns: TRUE always.
  
  Note: uses Standard Template Library (STL).
 */
BOOL TsWriteToView(LPCTSTR lszText)
{
if (lszText != NULL)
  cout << lszText;
else
  cout << "<null>";
cout.flush();
return TRUE;
}

//main()-----------------------------------------------------------------------
/*Validates different date and time routines.

  Returns: EXIT_SUCCESS, which represents a value of 0, if successful. Otherwise
  a non-zero error code is returned.
 */
int main()
{
cout << "Start Date and Time String " << endl << endl;

if(TestLeapYear())
  cout << "Succeeded." << endl << endl;
else
  {
  cout << "Failed!" << endl;
  return EXIT_FAILURE + 1;
  }


return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         15/01/2003 12:29:47 AMDarko           
 * $
 *****************************************************************************/
