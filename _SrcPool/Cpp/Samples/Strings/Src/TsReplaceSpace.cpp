/*$Workfile: H:\_SrcPool\Cpp\Samples\Strings\Src\TsReplaceSpace.cpp$: implementation file
  $Revision: 1$ $Date: 9/10/02 6:51:14 PM$
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
extern TCHAR* ByteToHex(BYTE cValue, TCHAR* szResult);

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
int iTextLen =  _tcslen(szText);

  //Test triming leading and trailing spaces
cout << szText << endl << "<EOT>" << endl 
     << "Text lenght = " << iTextLen << endl
     << "Trim leading and trailing spaces:" << endl;

LPTSTR szBuffer = new TCHAR[iTextLen + 1];
_tcscpy(szBuffer, szText);
StrTrim(szBuffer);
int iResultLen =  _tcslen(szBuffer);
if (szBuffer[0] != _T('C'))
  bRes = false;
else if (szBuffer[iResultLen - 1] != _T('.'))
  bRes = false;
cout << szBuffer << endl << "<EOT>" << endl 
     << "Text lenght = " << iResultLen << endl;

  //Test replacing multiple spaces with single character
if (bRes)
  {
  cout << "Replace multiple spaces:" << endl;
  _tcscpy(szBuffer, szText);
  if (ReplaceSpaces(szBuffer) == NULL)
    bRes = false;
  else
    {
    iResultLen =  _tcslen(szBuffer);
    if (szBuffer[0] != _T('C'))
      bRes = false;
    else if (szBuffer[iResultLen] != _T('.'))
      bRes = false;

    cout << szBuffer << endl << "<EOT>" << endl 
         << "Text lenght = " << iResultLen << endl;

    }
  }

delete[] szBuffer;
TsWriteToView("======================\r\n");
return bRes;
}

//////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: 
 * 1    Biblioteka1.0         9/10/02 6:51:14 PM   Darko Kolakovic 
 *$
 *****************************************************************************/
