/*$Workfile: S:\_SrcPool\Cpp\Samples\Strings\Src\TestCommonStrings.cpp$: implementation file
  $Revision: 1$ $Date: 2007-06-15 17:29:25$
  $Author: Darko Kolakovic$

  Test debugging and tracing routines.
  Copyright: CommonSoft Inc.
  2004-08-12 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"

extern bool TsWriteToViewLn(LPCTSTR lszText);

extern bool TestCharConversion();
extern bool TestZtoA();
extern bool TestStringConversion();
extern bool TestGetLine(LPCTSTR szFileName, int iNoofLines);
extern bool TestIsPalindrome();
extern bool TestIsVowel();
extern bool TestReplaceSpace();
extern bool TestTrim();
extern bool TestStrDup();
extern bool TestStrings();
extern bool TestReplaceEscapeSeq();


int g_iNoofLines = -1;
#ifdef _USE_MFC
   //Name of default text file used to test string functions
  CString     g_strTestFile = "../../Res/TomSawyer.txt";
#else
  #include <string>     //std::string
  std::string g_strTestFile = "../../Res/TomSawyer.txt";
#endif //_USE_MFC

//-----------------------------------------------------------------------------
/*Defines the entry point for the console application that validates a string
  manipulation routines.

  Returns: EXIT_SUCCESS, which represents a value of 0, if successful. Otherwise
  a non-zero error code is returned.
 */
int TestCommonStrings()
{
TsWriteToViewLn(_T("TestCommonStrings()"));
TsWriteToViewLn(_T(""));

PFUNC_TEST funcTest[] =
  {
  TestStringConversion,
  TestCharConversion,
  TestStrDup,
  TestReplaceSpace,
  TestTrim,
  TestStrings,
  TestReplaceEscapeSeq,
  TestIsPalindrome,
  TestIsVowel,
  TestZtoA
  };

int iTestCount = 0;
while (iTestCount < (sizeof(funcTest)/sizeof(PFUNC_TEST)) )
  {
  if ((funcTest[iTestCount] != NULL) && funcTest[iTestCount]())
    {
    TsWriteToViewLn(LOG_SUCCESS);
    TsWriteToViewLn(_T(""));
    }
  else
    {
    TsWriteToViewLn(LOG_FAILURE);
    return EXIT_FAILURE + 1 + iTestCount;
    }
  iTestCount++;
  }

if(TestGetLine(g_strTestFile.c_str(), g_iNoofLines))
  {
  TsWriteToViewLn(LOG_SUCCESS);
  TsWriteToViewLn(_T(""));
  }
else
  {
  TsWriteToViewLn(LOG_FAILURE);
  return EXIT_FAILURE + 1 + iTestCount;
  }

return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2007-06-15 17:29:25  Darko Kolakovic 
 * $
 *****************************************************************************/
