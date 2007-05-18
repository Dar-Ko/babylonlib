/*$Workfile: S:\_SrcPool\Cpp\Samples\Random\Src\TestCommonRandom.cpp$: implementation file
  $Revision: 1$ $Date: 2007-05-18 12:58:45$
  $Author: Darko Kolakovic$

  Test random number generators.
  Copyright: CommonSoft Inc.
  2007-05-07 D.Kolakovic
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
extern bool TestRandomNo();
extern bool TestRandomUniform();
extern bool TestRandomCongr();
extern bool TestRandomGauss();


//-----------------------------------------------------------------------------
/*Validate different random number generators.

  Returns: EXIT_SUCCESS, which represents a value of 0, if succesful. Otherwise
  a non-zero error code is returned.
 */
int TestCommonRandom()
{
TsWriteToViewLn(_T("Validation of random number generators"));
TsWriteToViewLn(_T(""));

PFUNC_TEST funcTest[] =
  {
  TestRandomNo,
  TestRandomUniform,
  TestRandomCongr,
  TestRandomGauss,
  };

int iTestCount = 0;
while (iTestCount < (sizeof(funcTest)/sizeof(PFUNC_TEST)) )
  {
  if ((funcTest[iTestCount] != NULL) && funcTest[iTestCount]())
    std::_tcout << LOG_SUCCESS << std::endl << std::endl;
  else
    {
    TsWriteToViewLn(LOG_FAILURE);
    return EXIT_FAILURE + 1 + iTestCount;
    }
  iTestCount++;
  }

return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2004-10-04 23:26:39  Darko
 * $
 *****************************************************************************/
