/*$Workfile: TestCommonStrings.cpp$: implementation file
  $Revision: 4$ $Date: 2007-06-27 16:52:18$
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

int TestCommonStrings(void);

int g_iNoofLines = -1;
LPCTSTR TESTFILE = _T("../../../Strings/Res/TomSawyer.txt");

#ifdef _USE_MFC
   //Name of default text file used to test string functions
  CString g_strTestFile = TESTFILE;
  PFUNCENTRY_TEST g_startTest = TestCommonStrings; //test entry point

#else
  #include <string> //std::basic_string
  #include "STL/KTString.h" //tstring typedef
  class TsString : public tstring
    {
    public:
      TsString(LPCTSTR szString = NULL)
        {
        if (szString != NULL)
          *((tstring*)this) = szString;
        };
      virtual ~TsString() {};
      operator LPCTSTR() const
        {
        return c_str();
        };
    };

  TsString g_strTestFile = TESTFILE;
#endif //_USE_MFC

//-----------------------------------------------------------------------------
/*Helper functions stores the name of a test text file.
 */
void TsSetTesFile(LPCTSTR szFileName //[in] name of a text file
                 )
{
if (szFileName != NULL)
  g_strTestFile = szFileName;
}

//-----------------------------------------------------------------------------
/*Validates environment values.

  Returns: true if successful, otherwise returns false.
 */
bool TestCharacterSet()
{
bool bRes = true;
#ifdef _UNICODE
  TsWriteToViewLn(_T("Unicode character set"));
#endif
#ifdef _MBCS
  TsWriteToViewLn(_T("Multi-byte character set"));
#endif
#ifdef _SBCS
  TsWriteToViewLn(_T("Single-byte character set"));
#endif
switch (sizeof(TCHAR))
  {
  case 1: TsWriteToViewLn(_T("Character is 1 byte.")); break;
  case 2: TsWriteToViewLn(_T("Character is 2 bytes.")); break;
  case 4: TsWriteToViewLn(_T("Character is 4 bytes.")); break;
  default:
    TsWriteToViewLn(_T("Character size is unvalid."));
    bRes = false;
  }

return bRes;
}

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
  TestCharacterSet,
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

if(TestGetLine(LPCTSTR(g_strTestFile), g_iNoofLines))
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
 *  2    Biblioteka1.1         2007-06-19 16:31:56  Darko Kolakovic
 *       TestCharacterSet()
 *  1    Biblioteka1.0         2007-06-15 17:29:25  Darko Kolakovic
 * $
 *****************************************************************************/
