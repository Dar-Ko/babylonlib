/*$Workfile: main.cpp$: implementation file
  $Revision: 11$ $Date: 2007-06-20 14:45:20$
  $Author: Darko Kolakovic$

  Console application used to test various string operations
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

extern int g_iNoofLines;
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern int TestCommonStrings();

//main()-----------------------------------------------------------------------
/*Validate different string routines.

  Returns: EXIT_SUCCESS, which represents a value of 0, if successful. Otherwise
  a non-zero error code is returned.
 */
int _tmain(int   argc,   //[in] 1st argument is a text file name;
                         //     2nd in number of lines in the text file
           char* argv[]  //[in] a text file name
          )
{
g_iNoofLines = -1;
if(argc >= 2) //Get file name from command line
  {
  extern void TsSetTesFile(LPCTSTR szFileName);
  TsSetTesFile(argv[1]);
  }

if(argc >= 3) //Get file name from command line
  g_iNoofLines = atoi(argv[2]);

TsWriteToViewLn(_T("Start String Tests"));
TsWriteToViewLn(_T(""));
int nRetCode = EXIT_SUCCESS;

nRetCode = TestCommonStrings();
return nRetCode;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log:
 *  10   Biblioteka1.9         2007-06-15 17:28:39  Darko Kolakovic Console traget
 *       fixes
 *  9    Biblioteka1.8         2002-10-25 03:31:29  Darko Kolakovic Added
 *       TestTrim()
 *  8    Biblioteka1.7         2002-09-11 16:26:42  Darko Kolakovic Added
 *       TestStrDup()
 *  7    Biblioteka1.6         2002-09-10 18:55:46  Darko Kolakovic
 *  6    Biblioteka1.5         2002-08-19 10:32:53  Darko Kolakovic
 *       TestCharConversion()
 *  5    Biblioteka1.4         2002-03-07 17:12:55  Darko
 *       TestStringConversion()
 *  4    Biblioteka1.3         2002-02-12 10:58:52  Darko           GNU compiler
 *       issues
 *  3    Biblioteka1.2         2002-02-04 18:37:35  Darko
 *  2    Biblioteka1.1         2002-02-03 21:49:52  Darko           added new tests
 *  1    Biblioteka1.0         2002-01-23 19:17:12  Darko
 * $
 *****************************************************************************/
