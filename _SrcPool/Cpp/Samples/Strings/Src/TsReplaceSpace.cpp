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

  //Test trimming leading and trailing spaces
cout << szText << endl << "<EOT>" << endl 
     << "Text length = " << iTextLen << endl
     << "Trim leading and trailing spaces:" << endl;

LPTSTR szBuffer = new TCHAR[iTextLen + 1];
_tcscpy(szBuffer, szText);
StrTrim(szBuffer);
int iResultLen = _tcslen(szBuffer);
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
    else if (szBuffer[iResultLen] != _T('.'))
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
        bRes = false;
      else if (szBuffer[0] != _T('C'))
        bRes = false;
      else if (szBuffer[iResultLen] != _T('.'))
        bRes = false;
      }
    }
  }

delete[] szBuffer;
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
