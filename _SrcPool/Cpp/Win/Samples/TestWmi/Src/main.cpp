/*$RCSfile: main.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2010/01/21 22:18:19 $
  $Author: ddarko $

  Entry point for the applcation
  2007-01-05 Darko Kolakovic
*/

// Group=Examples Windows

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
extern int TestCommonWmi(int argc, TCHAR* argv[]);

//-----------------------------------------------------------------------------
/*Validates different debugging and tracing routines.
  Defines the entry point for the console application.

  Returns: EXIT_SUCCESS, which represents a value of 0, if successful. Otherwise
  a non-zero error code is returned.
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
TsWriteToViewLn(_T("Start System Services Tests"));
TsWriteToViewLn(_T(""));
int nRetCode = EXIT_SUCCESS;

nRetCode = TestCommonWmi(argc, argv);
return nRetCode;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: main.cpp,v $
 * Revision 1.1  2010/01/21 22:18:19  ddarko
 * Created
 *
 *****************************************************************************/
