/*$Workfile: TestCommonUtilities.cpp$: implementation file
  $Revision: 2$ $Date: 2007-02-02 13:30:41$
  $Author: Darko Kolakovic$

  Test various helper functions.
  Copyright: CommonSoft Inc.
  2005-05-17 Darko Kolakovic
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

#define _USE_STL  //TODO: replace STL with generic console << LOG_SUCCESS;
#include "stdafx.h"

extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TestBeep();
extern bool TestGuid();


//-----------------------------------------------------------------------------
/*Validate various helper functions.

  Returns: EXIT_SUCCESS, which represents a value of 0, if succesful. Otherwise
  a non-zero error code is returned.
 */
int TestCommonUtilities()
{
TsWriteToViewLn(_T("Validation of various helper functions"));
TsWriteToViewLn(_T(""));

PFUNC_TEST funcTest[] =
  {
  TestBeep,
  TestGuid
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
 *  1    Biblioteka1.0         2005-05-16 14:21:31  Darko Kolakovic
 * $
 *****************************************************************************/
