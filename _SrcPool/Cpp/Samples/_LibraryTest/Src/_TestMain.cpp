/*$Workfile: _TestMain.cpp$: implementation file
  $Revision: 1.1 $ $Date: 2003/01/31 03:05:28 $
  $Author: ddarko $

  Defines the entry point for the console application used to test libray 
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
#include "KTrace.h"   //TRACE macro
#include "KTypedef.h" //BOOL typedef

extern bool TestCalculus();
extern bool TestPoint();
extern bool TestQuadraticEquation();
extern bool TestComplex();
extern bool TestPointToComplex();
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
cout << _T("Libarary validation") << endl << endl;
CTestLog logTest;

cout << _T("Start Calculus test") << endl << endl;
if(TestCalculus())
  cout << "Succeeded." << endl << endl;
else
  {
  cout << "Failed!" << endl;
  return EXIT_FAILURE + 1;
  }

if(TestPoint())
  cout << "Succeeded." << endl << endl;
else
  {
  cout << "Failed!" << endl;
  return EXIT_FAILURE + 2;
  }

if(TestQuadraticEquation())
  cout << "Succeeded." << endl << endl;
else
  {
  cout << "Failed!" << endl;
  return EXIT_FAILURE + 3;
  }

cout << _T("Start Complex number test") << endl << endl;
if(TestComplex())
  cout << "Succeeded." << endl << endl;
else
  {
  cout << "Failed!" << endl;
//TODO:  return EXIT_FAILURE + 4;
  }

if(TestPointToComplex())
  cout << "Succeeded." << endl << endl;
else
  {
  cout << "Failed!" << endl;
  return EXIT_FAILURE + 5;
  }

cout << _T("Start Date and Time String test") << endl << endl;
if(TestLeapYear())
  cout << "Succeeded." << endl << endl;
else
  {
  cout << "Failed!" << endl;
  return EXIT_FAILURE + 6;
  }

return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
