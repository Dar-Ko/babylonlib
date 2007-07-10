/*$Workfile: TestCharConversion.cpp$: implementation file
  $Revision: 6$ $Date: 2007-06-27 16:52:15$
  $Author: Darko Kolakovic$

  Test different character conversions
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
extern TCHAR* ByteToHex(BYTE cValue, TCHAR* szResult);

//TestCharConversion()----------------------------------------------------------
/*Test different conversions of a character from and to string.

  Returns: true if successful, otherwise returns false.
 */
bool TestCharConversion()
{
TsWriteToView(_T("TestCharConversion()\r\n"));

bool bRes = true;
TCHAR szResult[16];

BYTE chTable[] =
  {
  0xFE    , _T('\0'), 0xb1, 0x4A, 1      ,
  _T('\n'), _T('\t'), 0x90, 154 , _T('A')
  };

TCHAR* szHexTable[] =
  {
  _T("FE"), _T("00"), _T("B1"), _T("4A"), _T("01"),
  _T("0A"), _T("09"), _T("90"), _T("9A"),  _T("41")
  };

TCHAR* szAsciiTable[] =
  {
  _T("<?>") , _T("<NUL>"), _T("<?>"), _T("J")  , _T("<SOH>"),
  _T("<LF>"), _T("<HT>") , _T("<?>"), _T("<?>"), _T("A")
  };

int i = 0;
while ( i < sizeof(chTable) )
  {
  std::_tcout << (int)chTable[i] << " = 0x"
       << ByteToHex(chTable[i], szResult)
       << _T(", ")
       << ChtoAscii(chTable[i])
       << std::endl;
  if ( _tcscmp(szHexTable[i], szResult) != 0 )
    {
    std::_tcout << "  " << BoolToA(bRes = false)
         << _T(" wrong hex value") << std::endl;
    }
  if ( _tcscmp(szAsciiTable[i], ChtoAscii(chTable[i])) != 0 )
    {
    std::_tcout << "  " << BoolToA(bRes = false)
         << _T(" wrong ASCII value") << std::endl;
    }

  i++;
  }

TsWriteToViewLn(LOG_EOT);
return bRes;
}

//////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log:
 * 4    Biblioteka1.3         2007-06-15 17:28:28  Darko Kolakovic Console traget
 *      fixes
 * 3    Biblioteka1.2         2007-06-15 12:42:28  Darko Kolakovic
 * 2    Biblioteka1.1         2002-09-10 18:55:38  Darko Kolakovic
 * 1    Biblioteka1.0         2002-08-19 10:16:44  Darko Kolakovic
 *$
 *****************************************************************************/
