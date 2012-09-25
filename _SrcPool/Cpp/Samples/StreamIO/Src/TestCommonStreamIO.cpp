/*$Workfile: TestCommonStreamIO.cpp$: implementation file
  $Revision: 8$ $Date: 2007-05-03 15:57:33$
  $Author: Darko Kolakovic$

  Testing routines using standard stream I/O.

  Copyright: CommonSoft Inc.
  2004-09-27 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"

extern bool TsWriteToViewLn(LPCTSTR lszText);

extern bool TestGetLines(LPCTSTR szFileName);
extern bool TestFilename();
extern bool TestFileFolder();

int TestCommonStreamIO();
int TestCommonStreamIO(LPCTSTR szFileName);

//-----------------------------------------------------------------------------
/*Validates routines using standard stream I/O.
  Defines the entry point for the test.

  Returns: EXIT_SUCCESS, which represents a value of 0, if succesful. Otherwise
  a non-zero error code is returned.
 */
int TestCommonStreamIO()
{
return TestCommonStreamIO(NULL);
}

//-----------------------------------------------------------------------------
/*Validates routines using standard stream I/O.
  Defines the entry point for the test.

  Returns: EXIT_SUCCESS, which represents a value of 0, if succesful. Otherwise
  a non-zero error code is returned.
 */
int TestCommonStreamIO(LPCTSTR szFileName //[in] file name of the testing subject
                    )
{
TsWriteToViewLn(_T("Start validation of various stream I/O methods"));
TsWriteToViewLn(_T(""));

#ifdef KSTL_IO
  TRACE1(_T("  KSTL_IO version %d.\n"), KSTL_IO);
#else
  TRACE0("  KSTL_IO is not defined.\n");
#endif

PFUNC_TEST funcTest[] =
  {
  //TODO: add Test
  TestFilename,
  TestFileFolder,
  NULL
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
    return EXIT_FAILURE + 50 + iTestCount;
    }
  iTestCount++;
  }

 //List with test file names
//TODO: replace path with current directory
TCHAR* szTestFile[] =
  {
   //Zero length file
  _T("S:\\_SrcPool\\Cpp\\Samples\\StreamIO\\Res\\Test0b.txt"  ),   //Test 0
   //26 letters
  _T("S:\\_SrcPool\\Cpp\\Samples\\StreamIO\\Res\\Test26ch.txt"),   //Test 1
   //Long file name (175 characters)
  _T("S:\\_SrcPool\\Cpp\\Samples\\StreamIO\\Res\\Test Incredibly Long File Name With All Allowed Characters Like {}[]()!.@#$%^&,.`~ AndSoOnAllLettersAlsoABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz numbers 0123456789.txt"), //Test 2
   //File with non-printable characters (EOT, DC1, ...)
  _T("S:\\_SrcPool\\Cpp\\Samples\\StreamIO\\Res\\TestCanc.bin"),   //Test 3
   //File with zeroes and one 0xFF byte
  _T("S:\\_SrcPool\\Cpp\\Samples\\StreamIO\\Res\\TestEOBach.bin"), //Test 4
   //1025 bytes
  _T("S:\\_SrcPool\\Cpp\\Samples\\StreamIO\\Res\\Test1kTest.bin"), //Test 5
   //416.145 characters long text CRLF
  _T("S:\\_SrcPool\\Cpp\\Samples\\StreamIO\\Res\\TomSawyer.txt"),  //Test 6
   //416.145 characters long text LF ISO-8859-1
  _T("S:\\_SrcPool\\Cpp\\Samples\\StreamIO\\Res\\Voyage au Centre de la Terre.txt"),  //Test 7
   NULL  //End of string list
  };

if (szFileName == NULL)
  {
  //Test predefined files
  int iTestFileNo = 0;
  while (szTestFile[iTestFileNo] != NULL)
    {
    if(!TestGetLines(szTestFile[iTestFileNo]))
      {
      TsWriteToViewLn(LOG_FAILURE);
      return EXIT_FAILURE + 1 + iTestFileNo; //Failed test
      }
    else
      {
      TsWriteToViewLn(LOG_SUCCESS);
      TsWriteToViewLn(_T(""));
      }
    iTestFileNo++;
    }
  }
else
  {
  //Test user's input
    if(!TestGetLines(szFileName))
      {
      TsWriteToViewLn(LOG_FAILURE);
      return EXIT_FAILURE + 1; //Failed test
      }
    else
      {
      TsWriteToViewLn(LOG_SUCCESS);
      TsWriteToViewLn(_T(""));
      }
  }

return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log:
 *  6    Biblioteka1.5         2004-10-06 16:01:34  Darko           Unicode mapping
 *  5    Biblioteka1.4         2004-10-04 12:49:12  Darko           Renamed  test
 *       script to TestCommonStreamIO
 *  4    Biblioteka1.3         2004-10-04 12:47:39  Darko
 *  3    Biblioteka1.2         2004-09-30 15:47:54  Darko           inserted global
 *       CTestLog
 *  2    Biblioteka1.1         2004-09-29 13:23:29  Darko           improved tests
 *  1    Biblioteka1.0         2004-09-28 13:59:58  Darko
 * $
 *****************************************************************************/
