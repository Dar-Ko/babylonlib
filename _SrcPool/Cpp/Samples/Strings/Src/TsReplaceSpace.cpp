/*$Workfile: TsReplaceSpace.cpp$: implementation file
  $Revision: 2$ $Date: 9/11/02 4:26:38 PM$
  $Author: Darko Kolakovic$

  Test string trimming 
  Copyright: CommonSoft Inc.
  Aug. 2k2 Darko Kolakovic
*/

// Group=Examples

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "KStrings.h"	//ChtoAscii()
#include <iostream>
#include <iomanip.h>  //std::endl

extern BOOL TsWriteToView(LPCTSTR lszText);

//TestReplaceSpace()----------------------------------------------------------
/*Test reducing the number of whitespace characters in a string.

  Returns: true if successful, otherwise returns false.
 */
bool TestReplaceSpace()
{
TsWriteToView("TestReplaceSpace()\r\n");

bool bRes = true;
LPCTSTR szText = _T("\n\n\r\n\t  \
       CHAPTER VII      \
THE harder Tom tried to fasten his mind on his book, the more his ideas wandered.\r\n \
\t\t\t  \t\n  So at last, with a sigh and a yawn, he gave it up.\r\n  \
   \t \v");
int iTextLen = _tcslen(szText);
LPTSTR szBuffer = new TCHAR[iTextLen + 1];

  //Test trimming a string with spaces only
cout << "Trim spaces from a string with blanks only." << endl;
_tcscpy(szBuffer, "  \t  \v\f  \r");
StrTrim(szBuffer);
int iResultLen = _tcslen(szBuffer);
if (iResultLen != 0)
  bRes = false;
  
if (bRes)
  {
    //Test trimming leading and trailing spaces
  cout << szText << endl << "<EOT>" << endl 
       << "Text length = " << iTextLen << endl
       << "Trim leading and trailing spaces:" << endl;

  _tcscpy(szBuffer, szText);
  StrTrim(szBuffer);
  iResultLen = _tcslen(szBuffer);
  if (szBuffer[0] != _T('C'))
    bRes = false;
  else if (szBuffer[iResultLen - 1] != _T('.'))
    bRes = false;
  cout << szBuffer << endl << "<EOT>" << endl 
       << "Text length = " << iResultLen << endl;

    //Test trimming on text without leading or trailing spaces
  if (bRes)
    {
    StrTrim(szBuffer);
    if (iResultLen != _tcslen(szBuffer))
      bRes = false;
    else if (szBuffer[0] != _T('C'))
      bRes = false;
    else if (szBuffer[iResultLen - 1] != _T('.'))
      bRes = false;
    }

      //Test replacing multiple spaces with single character
    if (bRes)
      {
      cout << "Replace multiple spaces:" << endl;

        //Test replacing on text without leading or trailing spaces
      if (ReplaceSpaces(szBuffer) == NULL)
        bRes = false;
      else
        {
        iResultLen = _tcslen(szBuffer);
        if (szBuffer[0] != _T('C'))
          bRes = false;
        else if (szBuffer[iResultLen-1] != _T('.'))
          bRes = false;

        cout << szBuffer << endl << "<EOT>" << endl 
             << "Text length = " << iResultLen << endl;
        }

      //Test replacing on text with leading and trailing spaces
      if (bRes)
        {
        _tcscpy(szBuffer, szText);
        if (ReplaceSpaces(szBuffer) == NULL)
          bRes = false;
        else
          {
          if (iResultLen != _tcslen(szBuffer))
            {
            bRes = false;
            iResultLen = _tcslen(szBuffer);
            cout << "Text length = " << iResultLen << endl;
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
TsWriteToView("======================\r\n");
return bRes;
}

//TestTrim()-------------------------------------------------------------------
/*Test of string trimming and striping.

  Returns: true if successful, otherwise returns false.
 */
bool TestTrim()
{
TsWriteToView("TestTrim()\r\n");

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
  int iLen = _tcslen(szSource);
  StrTrimSlash(szSource);
  bRes = (_tcslen(szSource) == (iLen - 1) && szSource[_tcslen(szSource) - 1] == _T('r') );
  }

  //Test a string ending with '\'
if (bRes)
  {
  _tcscpy(szSource, _T("\\Dir\\SubDir\\"));
  int iLen = _tcslen(szSource);
  StrTrimSlash(szSource);
  bRes = (_tcslen(szSource) == (iLen - 1) && szSource[_tcslen(szSource) - 1] == _T('r') );
  }

  //Test a string ending with a letter
if (bRes)
  {
  int iLen = _tcslen(szSource);
  StrTrimSlash(szSource);
  bRes = (_tcslen(szSource) == iLen && szSource[_tcslen(szSource) - 1] == _T('r') );
  }

TsWriteToView("======================\r\n");
return bRes;
}

//////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: 
 * 2    Biblioteka1.1         9/11/02 4:26:38 PM   Darko Kolakovic Added
 *      TestStrDup()
 * 1    Biblioteka1.0         9/10/02 6:51:14 PM   Darko Kolakovic 
 *$
 *****************************************************************************/
