/*$Workfile: main.cpp$: implementation file
  $Revision: 2$ $Date: 2004-10-12 10:50:47$
  $Author: Darko$

  Defines the entry point for the console application used to test library 
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
extern int TestCommonLibrary();

//-----------------------------------------------------------------------------
/*Invokes different test routines used to validate functionality of the library.

  Returns: EXIT_SUCCESS, which represents a value of 0, if successful. Otherwise
  a non-zero error code is returned.

  Note: Microsoft Windows specific (Win).

 */
int _tmain(int argc,      //[in] specifies how many arguments are passed to the
                          //program from the command line. The value of argc is
                          //at least one: the program name.
           TCHAR* argv[]  //[in] the program arguments as an array of pointers
                          //to null-terminated strings. The first string 
                          //(argv[0]) is the program name. The end of the array
                          //(argv[argc]) is indicated by a NULL pointer.
          )
{
TsWriteToViewLn(_T("Library validation"));
int nRetCode = EXIT_SUCCESS;

nRetCode = TestCommonLibrary();

return nRetCode;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  2    Biblioteka1.1         2004-10-12 10:50:47  Darko           formatting
 *  1    Biblioteka1.0         2004-10-04 12:10:53  Darko           
 * $
 *****************************************************************************/
