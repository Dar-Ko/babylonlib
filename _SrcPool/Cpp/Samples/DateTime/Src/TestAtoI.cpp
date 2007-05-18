/*$Workfile: TestAtoI.cpp$: implementation file
  $Revision: 1$ $Date: 2004-10-08 12:30:23$
  $Author: Darko$

  Test Date conversions
  Copyright: CommonSoft Inc.
  2003-09-20 Darko Kolakovic
*/

// Group=Examples

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#include <stdlib.h> //_tstoi()
#ifndef _tstoi
  #include "KTChar.h"  //_tstoi()
#endif
//#include "KTChar.h"    //TCHAR typedef
#include "KTypedef.h"  //LPCTSTR typedef
//#include "KTrace.h"    //ASSERT macro
#include "STL/KOStream.h"    //ostream template
#include "KTestLog.h"  //TESTENTRY struct

//#define _STL //include standard streams operator<<

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------
/*Function validates conversion of a string to an integer.

  Returns: true if successful, otherwise returns false.
 */
bool TestAtoI()
{
TsWriteToView(_T("TestAtoI()\r\n"));
bool bRes = true;
TESTENTRY logEntry =
  {_T("AtoI()"), _T("KStrAtoI.cpp"), bRes};

extern int AtoI(LPCTSTR strSource, uint_fast16_t& nLen);
extern int AtoI(LPCTSTR* pszSource);

const int TESTCOUNT = 8;
struct tagTestAtoi
{
  LPCTSTR m_szSource; //string to parse
  int     m_iResult;  //expected result
} Test[TESTCOUNT] =
  {
  _T("  Garbage"),               0,  // 0
  _T("\t  +100"),              100,  // 1
  _T("-100"),                 -100,  // 2
  _T("+0  "),                    0,  // 3
  _T("  -2147483648"),     INT_MIN,  // 4
  _T("2147483647"),        INT_MAX,  // 5
  _T("  -123456789Y5555"),-123456789,// 6
  _T("9999999999"),         000000   // 7 overflow
  };

  //Overflow result
switch(sizeof(int))
  {
  case 2: /*TODO*/                        break;
  case 4: Test[7].m_iResult = 1410065407; break;
  case 8: /*TODO*/                        break;
  }

int iResult1, iResult2, iResult3;
unsigned nLen;
int i = 0;
while((i < TESTCOUNT) && bRes)
  {
  std::_tcout << i << _T(". ") << Test[i].m_szSource;
  iResult1 = _tstoi(Test[i].m_szSource); //stdlib
  LPCTSTR szSource = Test[i].m_szSource;
  iResult2 = AtoI(&szSource);
  if (*szSource != _T('\0'))
    std::_tcout << _T(" Rem: ")  << szSource;
  bRes = (iResult2 == iResult1);

  if (bRes)
    {
    nLen = _tcslen(Test[i].m_szSource);
    std::_tcout << _T(" Len: ")  << nLen;
    iResult3 = AtoI(Test[i].m_szSource, nLen);
    std::_tcout << _T(" Res: ")  << nLen << _T(" char") << std::endl;
    bRes = (iResult3 == Test[i].m_iResult);
    }
  i++;
  }

  //Test zero case
if (bRes)
  {
  nLen = 0;
  std::_tcout << i << _T(". ") << Test[5].m_szSource;
  std::_tcout << _T(" Len: ")  << nLen;
  iResult3 = AtoI(Test[5].m_szSource, nLen);
  std::_tcout << _T(" Res: ")  << nLen << _T(" char") << std::endl;
  bRes = (iResult3 == 0);
  }
 //Test fixed legth string
if (bRes)
  {
  i++;
  nLen = 7;
  std::_tcout << i << _T(". ") << Test[6].m_szSource;
  std::_tcout << _T(" Len: ")  << nLen;
  iResult3 = AtoI(Test[6].m_szSource, nLen);
  std::_tcout << _T(" Res: ")  << nLen << _T(" char") << std::endl;
  bRes = (iResult3 == -1234);
  }

logEntry.m_bResult = bRes;
LogTest(&logEntry);

TsWriteToViewLn(LOG_EOT);
return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2004-10-08 12:30:23  Darko           
 * $
 *****************************************************************************/
