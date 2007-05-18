/*$Workfile: main.cpp$: implementation file
  $Revision: 7$ $Date: 2007-05-18 12:59:11$
  $Author: Darko Kolakovic$

  Test random number generators
  Mar 2k2 A. Janicijevic
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
extern int TestCommonRandom();

//main()-----------------------------------------------------------------------
/*Defines the entry point for the console application.
  Validates random number generation routines.

  Returns: EXIT_SUCCESS, which represents a value of 0, if succesful. Otherwise
  a non-zero error code is returned.
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
TsWriteToViewLn(_T("Start Random Number Generator Tests"));
TsWriteToViewLn(_T(""));
int nRetCode = EXIT_SUCCESS;

nRetCode = TestCommonRandom();

return nRetCode;
}

///////////////////////////////////////////////////////////////////////////////
/****************************************************************************** 
 *$Log: 
 * 7    Biblioteka1.6         2007-05-18 12:59:11  Darko Kolakovic Added test log
 * 6    Biblioteka1.5         2007-05-18 11:46:28  Darko Kolakovic 
 * 5    Biblioteka1.4         2002-07-16 01:41:37  Darko           Fixed VSS Log 
 *      tag
 * 4    Biblioteka1.3         2002-04-03 16:31:33  Darko Kolakovic Added stdev and
 *      mean results
 * 3    Biblioteka1.2         2002-03-18 17:33:45  Darko Kolakovic Added Gaussian
 *      Rand No
 * 2    Biblioteka1.1         2002-03-14 16:47:33  Darko Kolakovic Added srand()
 * 1    Biblioteka1.0         2002-03-13 20:26:21  Aleksandar Janicijevic 
 *$
 *****************************************************************************/
