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

  //Test conversion from string to long
  //Number in range
szTemp = _T("567");
lResult = OcttoL(szTemp);
std::_tcout << _T("octal ") << szTemp << _T(" = ") << lResult << std::endl;
bRes = (lResult == 375);

if (bRes)
  {
  lResult = HextoL(szTemp);
  std::_tcout << _T("hex ") << szTemp << _T(" = ") << lResult << std::endl;
  bRes = (lResult == 1383);
  }

  //Number is out of range
if (bRes)
  {
  szTemp = _T("567745516123476412444");
  lResult = OcttoL(szTemp);
  std::_tcout << _T("octal ") << szTemp << _T(" = ") << lResult << std::endl;
  bRes = (lResult == -1661332188);
  }

if (bRes)
  {
  lResult = HextoL(szTemp); //Truncates to 56774551
  std::_tcout << "hex " << szTemp << _T(" = ") << lResult << std::endl;
  bRes = (lResult == 1983980612);
  }

TCHAR szResult[64];
int iValue;

if (bRes)
  {
  iValue = 375;
  ItoOct(iValue, szResult);
  std::_tcout << iValue << _T(" = ") << _T("octal ") << szResult << std::endl;
  bRes = ( _tcscmp(szResult, _T("567")) == 0 );
  }

if (bRes)
  {
  iValue = 65535;
  ItoOct(iValue,szResult);
  std::_tcout << iValue << _T(" = ") << _T("octal ") << szResult << std::endl;
  bRes = ( _tcscmp(szResult, _T("177777")) == 0 );
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
