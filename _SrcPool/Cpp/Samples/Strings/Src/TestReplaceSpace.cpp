/*$Workfile: TestReplaceSpace.cpp$: implementation file
  $Revision: 7$ $Date: 2007-06-27 16:52:41$
  $Author: Darko Kolakovic$

  Test string trimming
  Copyright: CommonSoft Inc.
  Aug. 2k2 Darko Kolakovic
*/

// Group=Examples

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */
#include "stdafx.h"
#include "KStrings.h" //ChtoAscii()
#include "STL/KOStream.h" //std::_tcout

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);

//TestReplaceSpace()----------------------------------------------------------
/*Test reducing the number of whitespace characters in a string.

  Returns: true if successful, otherwise returns false.
 */
bool TestReplaceSpace()
{
TsWriteToView(_T("TestReplaceSpace()\r\n"));

bool bRes = true;
LPCTSTR szText = _T("\n\n\r\n\t  \
       CHAPTER VII      \
THE harder Tom tried to fasten his mind on his book, the more his ideas wandered.\r\n \
\t\t\t  \t\n  So at last, with a sigh and a yawn, he gave it up.\r\n  \
   \t \v");
int iTextLen = (unsigned int)_tcslen(szText);
LPTSTR szBuffer = new TCHAR[iTextLen + 1];

  //Test trimming a string with spaces only
std::_tcout << _T("Trim spaces from a string with blanks only.") << std::endl;
_tcscpy(szBuffer, _T("  \t  \v\f  \r"));
StrTrim(szBuffer);
unsigned int iResultLen = (unsigned int)_tcslen(szBuffer);
if (iResultLen != 0)
  bRes = false;

if (bRes)
  {
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
  }

delete[] szBuffer;
TsWriteToViewLn(LOG_EOT);
return bRes;
}

//TestTrim()-------------------------------------------------------------------
/*Test of string trimming and striping.

  Returns: true if successful, otherwise returns false.
 */
bool TestTrim()
{
TsWriteToView(_T("TestTrim()\r\n"));

TCHAR szSource[256];
bool bRes = false;

bRes = (StrTrimSlash(NULL) == NULL); //Nothing to do

  //Test empty string
if (bRes)
  {
  szSource[0] = _T('\0');
  StrTrimSlash(szSource);
  bRes = (_tcslen(szSource) == 0);
  }

  //Test a string with slashes only
if (bRes)
  {
  _tcscpy(szSource, _T("///\\//"));
  StrTrimSlash(szSource);
  bRes = (_tcslen(szSource) == 0);
  }

  //Test a string ending with '/'
if (bRes)
  {
  _tcscpy(szSource, _T("/Dir/SubDir/"));
  unsigned int iLen = (unsigned int)_tcslen(szSource);
  StrTrimSlash(szSource);
  bRes = (_tcslen(szSource) == (iLen - 1) && szSource[_tcslen(szSource) - 1] == _T('r') );
  }

  //Test a string ending with '\'
if (bRes)
  {
  _tcscpy(szSource, _T("\\Dir\\SubDir\\"));
  unsigned int iLen = (unsigned int)_tcslen(szSource);
  StrTrimSlash(szSource);
  bRes = (_tcslen(szSource) == (iLen - 1) && szSource[_tcslen(szSource) - 1] == _T('r') );
  }

  //Test a string ending with a letter
if (bRes)
  {
  unsigned int iLen = (unsigned int)_tcslen(szSource);
  StrTrimSlash(szSource);
  bRes = (_tcslen(szSource) == iLen && szSource[_tcslen(szSource) - 1] == _T('r') );
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
