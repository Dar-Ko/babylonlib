/*$Workfile: TestCommonStlTools.cpp$: implementation file
  $Revision: 3$ $Date: 2007-07-17 12:02:36$
  $Author: Darko Kolakovic$

  Test system service (deamon) routines.
  Copyright: CommonSoft Inc.
  2007-02-02 Darko Kolakovic
*/

// Group=Examples

#include "stdstl.h"

extern bool TestStlLimits();
extern bool TestNullChar();
extern bool TestStlStringCfg();
extern bool TestReplaceEol();
extern bool TestStrToUpper();
extern bool TestUcstoHex();
extern bool TestWideChar();

int TestCommonStlTools();

//-----------------------------------------------------------------------------
/*Validate different helper routines.

  Returns: EXIT_SUCCESS, which represents a value of 0, if succesful. Otherwise
  a non-zero error code is returned.

  Note: uses Standard Template Library (STL).
*/
int TestCommonStlTools()
{
std::_tcout << _T("TestCommonStlTools()") << std::endl << std::endl;

PFUNC_TEST funcTest[] =
  {
  TestStlLimits,
  TestNullChar,
  TestStlStringCfg,
  TestWideChar,
  TestReplaceEol,
  TestStrToUpper,
  TestUcstoHex
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
 *  3    Biblioteka1.2         2007-07-17 12:02:36  Darko Kolakovic UscToHex()
 *  2    Biblioteka1.1         2007-07-16 17:53:29  Darko Kolakovic TestStlLimits()
 *  1    Biblioteka1.0         2007-07-10 17:46:49  Darko Kolakovic 
 * $
 *****************************************************************************/
