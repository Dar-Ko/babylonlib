/*$RCSfile: TestSubstring.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2009/09/30 20:54:36 $
  $Author: ddarko $

  Test finding string tokens
  2009-09-22 Darko Kolakovic
*/

// Group=Examples

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */
#include "stdafx.h"
#include "KStrings.h" //GetSubstring()

#ifdef WIN32
  #include <shlwapi.h> //StrCmp()
#endif

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
//Token index:         0   1       2  3   4   5    6  7    8
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
  szWord = GetSubstring(szSource, _T(' '), 5);
  bRes = (StrCmp(szWord, _T("word in this sentence.")) == 0);
  if (bRes)
    {
    szWord = GetSubstring(szSource, _T(' '), 25);
    bRes = (*szWord == _T('\0')); //Empty string
    }
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
return true; //TODO strtok_r (reentrant)

TsWriteToView(_T("TestStrTok()\r\n"));
/*/TODO
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

TsWriteToViewLn(LOG_EOT);
return bRes;
*/
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
