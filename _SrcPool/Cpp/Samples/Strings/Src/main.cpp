/*$Workfile: main.cpp$: implementation file
  $Revision: 9$ $Date: 25/10/2002 2:31:29 AM$
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

#include <iostream>
#include <iomanip.h>  //std::endl
#include <string>     //std::string
#include "KTrace.h"   //TRACE macro
#include "KTypedef.h" //BOOL typedef

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

extern bool TestStringClass();
extern bool TestGetLine(LPCTSTR szFileName, int iNoofLines);
extern bool TestStringConversion();
extern bool TestCharConversion();
extern bool TestReplaceSpace();
extern bool TestTrim();
extern bool TestStrDup();

extern std::string g_strTestFile;

//main()-----------------------------------------------------------------------
/*Validate different string routines.

  Returns: EXIT_SUCCESS, which represents a value of 0, if successful. Otherwise
  a non-zero error code is returned.
 */
int main(int   argc,   //[in] 1st argument is a text file name; 
                       //     2nd in number of lines in the text file 
         char* argv[]  //[in] a text file name 
         )
{
int iNoofLines = -1;
if(argc >= 2) //Get file name from command line
  g_strTestFile = argv[1];

if(argc >= 3) //Get file name from command line
  iNoofLines = atoi(argv[2]);

cout << "Start String tests" << endl << endl;

if(TestStringConversion())
  cout << "Succeeded." << endl << endl;
else
  {
  cout << "Failed!" << endl;
  return EXIT_FAILURE + 1;
  }

if(TestCharConversion())
  cout << "Succeeded." << endl << endl;
else
  {
  cout << "Failed!" << endl;
  return EXIT_FAILURE + 2;
  }

if(TestStringClass())
  cout << "Succeeded." << endl << endl;
else
  {
  cout << "Failed!" << endl;
  return EXIT_FAILURE + 3;
  }

if(TestStrDup())
  cout << "Succeeded." << endl << endl;
else
  {
  cout << "Failed!" << endl;
  return EXIT_FAILURE + 4;
  }

if(TestGetLine(g_strTestFile.c_str(), iNoofLines))
  cout << "Succeeded." << endl << endl;
else
  {
  cout << "Failed!" << endl;
  return EXIT_FAILURE + 5;
  }

if(TestReplaceSpace())
  cout << "Succeeded." << endl << endl;
else
  {
  cout << "Failed!" << endl;
  return EXIT_FAILURE + 6;
  }

if(TestTrim())
  cout << "Succeeded." << endl << endl;
else
  {
  cout << "Failed!" << endl;
  return EXIT_FAILURE + 7;
  }

return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  9    Biblioteka1.8         25/10/2002 2:31:29 AMDarko Kolakovic Added
 *       TestTrim()
 *  8    Biblioteka1.7         11/09/2002 3:26:42 PMDarko Kolakovic Added
 *       TestStrDup()
 *  7    Biblioteka1.6         10/09/2002 5:55:46 PMDarko Kolakovic 
 *  6    Biblioteka1.5         19/08/2002 9:32:53 AMDarko Kolakovic
 *       TestCharConversion()
 *  5    Biblioteka1.4         07/03/2002 4:12:55 PMDarko          
 *       TestStringConversion()
 *  4    Biblioteka1.3         12/02/2002 9:58:52 AMDarko           GNU compiler
 *       issues
 *  3    Biblioteka1.2         04/02/2002 5:37:35 PMDarko           
 *  2    Biblioteka1.1         03/02/2002 8:49:52 PMDarko           added new tests
 *  1    Biblioteka1.0         23/01/2002 6:17:12 PMDarko           
 * $
 *****************************************************************************/
