/*$Workfile: H:\_SrcPool\Cpp\Samples\Utilities\Src\TsMain.cpp$: implementation file
  $Revision: 1$ $Date: 9/16/02 5:58:59 PM$
  $Author: Darko Kolakovic$

  Console application used to test various helper functions
  Copyright: CommonSoft Inc
  Sep 2k2 Darko Kolakovic
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

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

#include <iostream>
#include <iomanip.h>  //std::endl
#include <string>     //std::string
#include "KTrace.h"   //TRACE macro
#include "KTypedef.h" //BOOL typedef

extern bool TestBeep();

//TsWriteToView()--------------------------------------------------------------
/*Writes a character string at the console standard output stream.

  Returns: TRUE always.
  
  Note: uses Standard Template Library (STL).
 */
bool TsWriteToView(LPCTSTR lszText)
{
if (lszText != NULL)
  cout << lszText;
else
  cout << "<null>";
cout.flush();
return true;
}

//main()-----------------------------------------------------------------------
/*Validate different utility routines.

  Returns: EXIT_SUCCESS, which represents a value of 0, if successful. Otherwise
  a non-zero error code is returned.
 */
int main()
{
cout << "Start Utility tests:" << endl << endl;

if(TestBeep())
  TsWriteToView("Succeeded.\r\n\r\n");
else
  {
  TsWriteToView("Failed!.\a\r\n");
  return EXIT_FAILURE + 1;
  }

return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         9/16/02 5:58:59 PM   Darko Kolakovic 
 * $
 *****************************************************************************/
