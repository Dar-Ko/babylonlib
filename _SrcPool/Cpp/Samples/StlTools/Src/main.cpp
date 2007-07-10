/*$Workfile: main.cpp$: implementation file
  $Revision: 4$ $Date: 2007-07-10 17:47:13$
  $Author: Darko Kolakovic$

  Defines the entry point for the console application used to test STL
  functionality and tools using Standard Template Library.
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

#include "stdstl.h"

extern int TestCommonStlTools();

//main()-----------------------------------------------------------------------
/*Defines the entry point for the console application that validates different
  routines using Standard Template Library.

  Returns: EXIT_SUCCESS, which represents a value of 0, if successful. Otherwise
  a non-zero error code is returned.

  Note: uses Standard Template Library (STL).
 */
int main(  int argc,      //[in] specifies how many arguments are passed to the
                          //program from the command line. The value of argc is
                          //at least one: the program name.
            char* argv[]  //[in] the program arguments as an array of pointers
                          //to null-terminated strings. The first string 
                          //(argv[0]) is the program name. The end of the array
                          //(argv[argc]) is indicated by a NULL pointer.
        )
{
_tcout << _T("Start testing STL tools") << endl << endl;

int nRetCode = EXIT_SUCCESS;

nRetCode = TestCommonStlTools();
return nRetCode;
}
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  4    Biblioteka1.3         2007-07-10 17:47:13  Darko Kolakovic _tcout
 *  3    Biblioteka1.2         2007-07-10 16:45:33  Darko Kolakovic standardized
 *       test entry point
 *  2    Biblioteka1.1         2007-07-10 16:14:16  Darko Kolakovic 
 *  1    Biblioteka1.0         2003-02-10 16:14:45  Darko           
 * $
 *****************************************************************************/
