/*$RCSfile: TestSubstring.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2009/09/29 22:00:07 $
  $Author: ddarko $

  Test finding string tokens
  2009-09-22 Darko Kolakovic
*/

// Group=Examples

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */
#include "stdafx.h"
#include "KStrings.h" //GetSubstring()

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);

//----------------------------------------------------------------------------
/*Test searching for tokens or substrings..

  Returns: true if successful, otherwise returns false.
 */
bool TestSubstring()
{
TsWriteToView(_T("TestSubstring()\r\n"));
TESTENTRY logEntry;
bool& bRes = logEntry.m_bResult;
LPTSTR szSource = _T("Get pointer to the 5th word in this sentence.");

//Test common behaviour
logEntry.m_szObjectName = _T("GetSubstring(TCHAR*, TCHAR, int)");
logEntry.m_szFileName = _T("KStrGetS.cpp");

LPTSTR szWord = GetSubstring(szSource, _T(' '), 0);
TRACE(szWord);
bRes = (_tcscmp(szWord, szSource) == 0);  //Oth substring points to the source string
LogTest(&logEntry);

if (bRes)
  {
    /*
    //Test trimming leading and trailing spaces
  std::_tcout << szText << std::endl << "<EOT>" << std::endl
       << "Text length = " << iTextLen << std::endl
       << "Trim leading and trailing spaces:" << std::endl;

  _tcscpy(szBuffer, szText);
  StrTrim(szBuffer);
  iResultLen = (unsigned int)_tcslen(szBuffer);
  if (szBuffer[0] != _T('C'))
    bRes = false;
  else if (szBuffer[iResultLen - 1] != _T('.'))
    bRes = false;
  std::_tcout << szBuffer << std::endl << "<EOT>" << std::endl
       << "Text length = " << iResultLen << std::endl;

    //Test trimming on text without leading or trailing spaces
  if (bRes)
    {
    StrTrim(szBuffer);
    if (iResultLen != (unsigned int)_tcslen(szBuffer))
      bRes = false;
    else if (szBuffer[0] != _T('C'))
      bRes = false;
    else if (szBuffer[iResultLen - 1] != _T('.'))
      bRes = false;
    }

      //Test replacing multiple spaces with single character
    if (bRes)
      {
      std::_tcout << "Replace multiple spaces:" << std::endl;

        //Test replacing on text without leading or trailing spaces
      if (ReplaceSpaces(szBuffer) == NULL)
        bRes = false;
      else
        {
        iResultLen = (unsigned int)_tcslen(szBuffer);
        if (szBuffer[0] != _T('C'))
          bRes = false;
        else if (szBuffer[iResultLen-1] != _T('.'))
          bRes = false;

        std::_tcout << szBuffer << std::endl << "<EOT>" << std::endl
             << "Text length = " << iResultLen << std::endl;
        }

      //Test replacing on text with leading and trailing spaces
      if (bRes)
        {
        _tcscpy(szBuffer, szText);
        if (ReplaceSpaces(szBuffer) == NULL)
          bRes = false;
        else
          {
          if (iResultLen != (unsigned int)_tcslen(szBuffer))
            {
            bRes = false;
            iResultLen = (unsigned int)_tcslen(szBuffer);
            std::_tcout << "Text length = " << iResultLen << std::endl;
            }
          else if (szBuffer[0] != _T('C'))
            bRes = false;
          else if (szBuffer[iResultLen-1] != _T('.'))
            bRes = false;
          }
        }
      }
      */
  }

TsWriteToViewLn(LOG_EOT);
return bRes;
}

//-----------------------------------------------------------------------------
/*Test of string trimming and striping.

  Returns: true if successful, otherwise returns false.
 */
bool TestStrTok()
{
TsWriteToView(_T("TestStrTok()\r\n"));

TCHAR szSource[256];
bool bRes = false;
             //TODO
bRes = (StrTrimSlash(NULL) == NULL); //Nothing to do

  //Test empty string
if (bRes)
  {
  szSource[0] = _T('\0');
  StrTrimSlash(szSource);
  bRes = (_tcslen(szSource) == 0);
  }

TsWriteToViewLn(LOG_EOT);
return bRes;
}

//////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log:
 * 5    Biblioteka1.4         2007-06-15 17:28:36  Darko Kolakovic Console traget
 *      fixes
 * 4    Biblioteka1.3         2007-06-15 12:42:59  Darko Kolakovic
 * 3    Biblioteka1.2         2002-10-25 03:31:25  Darko Kolakovic Added
 *      TestTrim()
 * 2    Biblioteka1.1         2002-09-11 16:26:38  Darko Kolakovic Added
 *      TestStrDup()
 * 1    Biblioteka1.0         2002-09-10 18:51:14  Darko Kolakovic
 *$
 *****************************************************************************/
