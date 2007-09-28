/*$Workfile: TestConversionToStr.cpp$: implementation file
  $Revision: 8$ $Date: 2007-06-27 16:52:22$
  $Author: Darko Kolakovic$

  Test different conversions from and to string
  Copyright: CommonSoft Inc.
  Jan. 2k2 Darko Kolakovic
*/
// Group=Examples


/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */
#include "stdafx.h"
#include "KStrings.h" //OcttoL()
#include "STL/KOStream.h" //std::_tcout

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern "C" LPTSTR ItoOct(int iValue, LPTSTR szResult);
extern LPCTSTR BooltoA(const bool bValue, LPCTSTR szTrue = NULL, LPCTSTR szFalse = NULL);

//TestStringConversion()-------------------------------------------------------
/*Test different conversions from and to string.

  Returns: true if successful, otherwise returns false.
 */
bool TestStringConversion()
{
TsWriteToView(_T("TestStringConversion()\r\n"));
bool bRes = false;
LPTSTR szTemp;
long lResult;

TESTENTRY logEntry =
  {_T("OcttoL()"), _T("KStrOtoL.c"), false};

//Test conversion from string to long

//Test an octal number
szTemp = _T("567"); //Number in the range
lResult = OcttoL(szTemp);
std::_tcout << _T("octal ") << szTemp << _T(" = ") << lResult << std::endl;
bRes = (lResult == 375);

if (bRes)
  {
  szTemp = _T("567745516123476412444"); //Number is out of range
  lResult = OcttoL(szTemp);
  std::_tcout << _T("octal ") << szTemp << _T(" = ") << lResult << std::endl;
  bRes = (lResult == -1661332188);
  }

logEntry.m_bResult = bRes;
LogTest(&logEntry);

//Test a hexadecimal number
if (bRes)
  {
  logEntry.m_szObjectName = _T("HextoL()");
  logEntry.m_szFileName = _T("KStrHtoL.c");

  szTemp = _T("567"); //Number in the range

  lResult = HextoL(szTemp);
  std::_tcout << _T("hex ") << szTemp << _T(" = ") << lResult << std::endl;
  bRes = (lResult == 1383);

  if (bRes)
    {
    szTemp = _T("567745516123476412444"); //Number is out of range

    lResult = HextoL(szTemp); //Truncates to 56774551
    std::_tcout << "hex " << szTemp << _T(" = ") << lResult << std::endl;
    bRes = (lResult == 1983980612);
    }

  logEntry.m_bResult = bRes;
  LogTest(&logEntry);
  }

TCHAR szResult[64];
int iValue;

//Test conversion to an octal number
if (bRes)
  {
  logEntry.m_szObjectName = _T("ItoOct()");
  logEntry.m_szFileName = _T("KItoOct.c");

  iValue = 375;
  ItoOct(iValue, szResult);
  std::_tcout << iValue << _T(" = ") << _T("octal ") << szResult << std::endl;
  bRes = ( _tcscmp(szResult, _T("567")) == 0 );

  if (bRes)
    {
    iValue = 65535;
    ItoOct(iValue,szResult);
    std::_tcout << iValue << _T(" = ") << _T("octal ") << szResult << std::endl;
    bRes = ( _tcscmp(szResult, _T("177777")) == 0 );
    }

  logEntry.m_bResult = bRes;
  LogTest(&logEntry);
  }

//Test boolean

if (bRes)
  {
  logEntry.m_szObjectName = _T("BooltoA()");
  logEntry.m_szFileName = _T("KStrBool.cpp");

  bRes = ( _tcscmp(_T("T"), BooltoA(iValue > 0)) == 0 );
  std::_tcout << iValue << _T(" > 0 ? ") << BooltoA(iValue > 0) << std::endl;
  if (bRes)
    {
    bRes = ( _tcscmp(_T("F"), BooltoA(iValue == 0)) == 0 );
    std::_tcout << iValue << _T(" = 0 ? ") << BooltoA(iValue == 0) << std::endl;
    }

  if (bRes)
    {
    bRes = ( _tcscmp(_T("positive"), BooltoA((iValue > 0), 
                                             _T("positive"), 
                                             _T("negative"))) == 0 );
    std::_tcout << iValue << _T(" is a ") << BooltoA((iValue > 0), 
                                             _T("positive"), 
                                             _T("negative")) << _T(" number.") << std::endl;
    }

  logEntry.m_bResult = bRes;
  LogTest(&logEntry);
  }

TsWriteToViewLn(LOG_EOT);
return bRes;
}

//////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log:
 * 6    Biblioteka1.5         2007-06-15 17:28:31  Darko Kolakovic Console traget
 *      fixes
 * 5    Biblioteka1.4         2007-06-15 12:42:42  Darko Kolakovic
 * 4    Biblioteka1.3         2002-08-19 10:35:58  Darko Kolakovic
 * 3    Biblioteka1.2         2002-08-13 18:52:51  Darko Kolakovic
 * 2    Biblioteka1.1         2002-07-16 01:41:52  Darko           Fixed VSS Log
 *      tag
 * 1    Biblioteka1.0         2002-03-07 17:01:24  Darko
 *$
 *****************************************************************************/
