/*$Workfile: TsGetLine.cpp$: implementation file
  $Revision: 6$ $Date: 10/09/2002 5:55:42 PM$
  $Author: Darko Kolakovic$

  Test for obtaining a text line
  Copyright: CommonSoft Inc.
  Jan. 2k2 Darko Kolakovic
*/

// Group=Examples


/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#include "KTypedef.h"  //LPCTSTR typedef
#include "KTrace.h"    //ASSERT macro
#include "KStrings.h"  //GetLine()
extern BOOL TsWriteToView(LPCTSTR lszText);
extern LPTSTR FileRead(LPCTSTR szFileName, 
             LPTSTR szBuffer = NULL, 
             int iCount = -1);

//TestGetLine()------------------------------------------------------------
/*Function shows how to use GetLine().

  Returns: true if successful, otherwise returns false.
 */
bool TestGetLine(LPCTSTR szFileName, //[in] text file to be tested
                 int iNoofLines      //[in] number of lines in the text file;
                         //a negative number skips the "number of lines" test
                 )
{
TsWriteToView("TestGetLine(");
TsWriteToView(szFileName);
TsWriteToView(")\r\n");

bool bRes = true;
int iLineCount = 0;
  //Get line without EOL markers
LPTSTR szTestEmpty = _T("");
LPTSTR szSource = szTestEmpty;
LPTSTR szLine;
while(GetLine(szSource, szLine) > 0)
  {
  iLineCount++;
  TsWriteToView("Empty Line test failed!\n");
  if(szLine != NULL)
    {
    TsWriteToView(szLine);
    TsWriteToView("<EOL>\n");
    delete[] szLine;
    }
  bRes = false;
  break;
  }

  //Get line without EOL markers
if(bRes)
  {
  iLineCount = 0;
  LPTSTR szTestNoEol = _T("01234567890123456789");
  szSource = szTestNoEol;
  while(GetLine(szSource, szLine) > 0)
    {
    iLineCount++;
    if(szLine != NULL)
      {
      TsWriteToView(szLine);
      TsWriteToView("<EOL>\n");
      delete[] szLine;
      }
    }

  if(iLineCount != 1)
    {
    TsWriteToView("szTestNoEol Line test failed!\n");
    bRes = false;
    }
  }

  //Get line with single EOL marker
if(bRes)
  {
  iLineCount = 0;
  LPTSTR szTestOneLf = _T("\n");
  szSource = szTestOneLf;
  while(GetLine(szSource, szLine) > 0)
    {
    iLineCount++;
    if(szLine != NULL)
      {
      TsWriteToView(szLine);
      TsWriteToView("<EOL>\n");
      delete[] szLine;
      }
    }

  if(iLineCount != 1)
    {
    TsWriteToView("szTestOneLf Line test failed!\n");
    bRes = false;
    }
  }

  //Get line with single Mac EOL marker
if(bRes)
  {
  iLineCount = 0;
  LPTSTR szTestOneCr = _T("\r");
  szSource = szTestOneCr;
  while(GetLine(szSource, szLine) > 0)
    {
    iLineCount++;
    if(szLine != NULL)
      {
      TsWriteToView(szLine);
      TsWriteToView("<EOL>\n");
      delete[] szLine;
      }
    }

  if(iLineCount != 1)
    {
    TsWriteToView("szTestOneCr Line test failed!\n");
    bRes = false;
    }
  }

  //Get line with single DOS EOL marker
if(bRes)
  {
  iLineCount = 0;
  LPTSTR szTestOneCrLf = _T("\r\n");
  szSource = szTestOneCrLf;
  while(GetLine(szSource, szLine) > 0)
    {
    iLineCount++;
    if(szLine != NULL)
      {
      TsWriteToView(szLine);
      TsWriteToView("<EOL>\n");
      delete[] szLine;
      }
    }

  if(iLineCount != 1)
    {
    TsWriteToView("szTestOneCrLf Line test failed!\n");
    bRes = false;
    }
  }

  //Get line with LF at the end
if(bRes)
  {
  iLineCount = 0;
  LPTSTR szTestLfEnd = _T("01234567890123456789\n");
  szSource = szTestLfEnd;
  while(GetLine(szSource, szLine) > 0)
    {
    iLineCount++;
    if(szLine != NULL)
      {
      TsWriteToView(szLine);
      TsWriteToView("<EOL>\n");
      delete[] szLine;
      }
    }

  if(iLineCount != 1)
    {
    TsWriteToView("szTestLfEnd Line test failed!\n");
  bRes = false;
    }
  }

  //Get line with CR at the end
if(bRes)
  {
  iLineCount = 0;
  LPTSTR szTestCrEnd = _T("01234567890123456789\r");
  szSource = szTestCrEnd;
  while(GetLine(szSource, szLine) > 0)
    {
    iLineCount++;
    if(szLine != NULL)
      {
      TsWriteToView(szLine);
      TsWriteToView("<EOL>\n");
      delete[] szLine;
      }
    }

  if(iLineCount != 1)
    {
    TsWriteToView("szTestCrEnd Line test failed!\n");
    bRes = false;
    }
  }

  //Get line with CRLF at the end
if (bRes)
  {
  iLineCount = 0;
  LPTSTR szTestCrLfEnd = _T("01234567890123456789\r\n");
  szSource = szTestCrLfEnd;
  while(GetLine(szSource, szLine) > 0)
    {
    iLineCount++;
    if(szLine != NULL)
      {
      TsWriteToView(szLine);
      TsWriteToView("<EOL>\n");
      delete[] szLine;
      }
    }

  if(iLineCount != 1)
    {
    TsWriteToView("szTestCrLfEnd Line test failed!\n");
    bRes = false;
    }
  }

  //Get line with LFCR at the end
if(bRes)
  {
  iLineCount = 0;
  LPTSTR szTestLfCrEnd = _T("01234567890123456789\n\r");
  szSource = szTestLfCrEnd;
  while(GetLine(szSource, szLine) > 0)
    {
    iLineCount++;
    if(szLine != NULL)
      {
      TsWriteToView(szLine);
      TsWriteToView("<EOL>\n");
      delete[] szLine;
      }
    }

  if(iLineCount != 2)
    {
    TsWriteToView("szTestLfCrEnd Line test failed!\n");
    bRes = false;
    }
  }

  //Read text
if(bRes)
  {
  char* szText = FileRead(szFileName);
  if(szText == NULL)
    {
    TsWriteToView("Cannot open file ");
    TsWriteToView(szFileName);
    TsWriteToView("\n");
    bRes =  false;
    }
  if (bRes)
    {
    iLineCount = 0;
    szSource = szText;
    while(GetLine(szSource, szLine) > 0)
      {
      iLineCount++;
      if(szLine != NULL)
        {
        TsWriteToView(szLine);
        TsWriteToView("<EOL>\n");
        delete[] szLine;
        }
      }

    TsWriteToView(szFileName);
    TsWriteToView(" has ");
    TsWriteToView(_itot(iLineCount,szText,10));
    TsWriteToView(" lines.\r\n");
    delete szText;
    if ((iNoofLines >=0 ) && (iLineCount != iNoofLines))
      bRes = false;
    }
  }

TsWriteToView("======================\r\n");
return bRes;
}

//////////////////////////////////////////////////////////////////////////////
