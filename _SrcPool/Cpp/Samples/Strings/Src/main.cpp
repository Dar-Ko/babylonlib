/*$Workfile: main.cpp$: implementation file
  $Revision: 8$ $Date: 9/11/02 4:26:42 PM$
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
 *  8    Biblioteka1.7         9/11/02 4:26:42 PM   Darko Kolakovic Added
 *       TestStrDup()
 *  7    Biblioteka1.6         9/10/02 6:55:46 PM   Darko Kolakovic 
 *  6    Biblioteka1.5         8/19/02 10:32:53 AM  Darko Kolakovic
 *       TestCharConversion()
 *  5    Biblioteka1.4         3/7/02 5:12:55 PM    Darko          
 *       TestStringConversion()
 *  4    Biblioteka1.3         2/12/02 10:58:52 AM  Darko           GNU compiler
 *       issues
 *  3    Biblioteka1.2         2/4/02 6:37:35 PM    Darko           
 *  2    Biblioteka1.1         2/3/02 9:49:52 PM    Darko           added new tests
 *  1    Biblioteka1.0         1/23/02 7:17:12 PM   Darko           
 * $
 *****************************************************************************/
