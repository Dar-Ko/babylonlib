/*$Workfile: S:\_SrcPool\Cpp\Samples\StlTools\Src\TestCommonStlTools.cpp$: implementation file
  $Revision: 1$ $Date: 2007-07-10 17:46:49$
  $Author: Darko Kolakovic$

  Test system service (deamon) routines.
  Copyright: CommonSoft Inc.
  2007-02-02 Darko Kolakovic
*/

// Group=Examples

#include "stdstl.h"

//extern bool TestWinService();

int TestCommonStlTools();

//-----------------------------------------------------------------------------
/*Validate different helper routines.

  Returns: EXIT_SUCCESS, which represents a value of 0, if succesful. Otherwise
  a non-zero error code is returned.

  Note: uses Standard Template Library (STL).
*/
int TestCommonStlTools()
{
_tcout << _T("TestCommonStlTools()") << endl << endl;

PFUNC_TEST funcTest[] =
  {
    NULL  //Break testing
  };
if (funcTest != NULL)
  {
  int iTestCount = 0;
  while (iTestCount < (sizeof(funcTest)/sizeof(PFUNC_TEST)) )
    {
    if ((funcTest[iTestCount] != NULL) && funcTest[iTestCount]())
      {
      std::_tcout << LOG_SUCCESS << std::endl << std::endl;
      }
    else
      {
      std::_tcout << LOG_FAILURE << std::endl;
      return EXIT_FAILURE + 1 + iTestCount;
      }
    iTestCount++;
    }
  }
else
  std::_tcout << _T("No tests are defined.");
return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2007-07-10 17:46:49  Darko Kolakovic 
 * $
 *****************************************************************************/
