/*$Workfile: S:\_SrcPool\Cpp\Samples\StringDyn\Src\TestIsVowel.cpp$: implementation file
  $Revision: 1$ $Date: 2007-05-31 12:35:30$
  $Author: Darko Kolakovic$

  Test IsVowel methods
  Copyright: CommonSoft Inc.
  2007-05-31 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"

extern bool IsVowel(TCHAR ch);

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(const int& iValue);
extern bool TsWriteToViewLn(const int& iValue);

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------
/*Validates IsVowel methods.

  Returns: true if successful, otherwise returns false.

 */
bool TestIsVowel()
{
TsWriteToView(_T("TestIsVowel()\r\n"));


const int TESTCOUNT = 3;
struct tagTestVowelCase
{
  LPCTSTR m_szSource; //string to test
  LPCTSTR m_szResult; //expected result
} Test[TESTCOUNT] =
  {
  _T("Roma tibi subito motibus ibit amor."),           // 1
  _T(" o a  i i  u i o  o i u  i i  a o  "), 
  _T("Wash my transgressions, not only my face."),     // 2
  _T(" a        a    e  io     o  o        a e "),
  _T("Go hang a salami, I'm a lasagna hog."),          // 3
  _T(" o  a   a  a a i  I   a  a a  a  o  ")
  };

  //Test object creation
TESTENTRY logEntry =
  {_T("IsVowel()"), _T("KStrVowel.cpp"), false};

bool bRes = false;
int i = 0;
do
  {
  int j = 0;
  TsWriteToViewLn(Test[i].m_szSource);

  while (j < _tcslen(Test[i].m_szResult))
    {
    bool bVowel = IsVowel(Test[i].m_szSource[j]);
    bRes = !((bVowel) ^ (Test[i].m_szResult[j] != _T(' ')));
    if (!bRes)
      break;
    j++;
    }

  TsWriteToViewLn(Test[i].m_szResult);
  i++;
  } while ((i < TESTCOUNT) && bRes);
logEntry.m_bResult = bRes;
LogTest(&logEntry);

TsWriteToView(LOG_EOT);
TsWriteToView(_T("\r\n"));
return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2007-05-31 12:35:30  Darko Kolakovic 
 * $
 *****************************************************************************/
