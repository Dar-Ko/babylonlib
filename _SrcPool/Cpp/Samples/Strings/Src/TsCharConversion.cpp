/*$Workfile: TsCharConversion.cpp$: implementation file
  $Revision: 2$ $Date: 10/09/2002 5:55:38 PM$
  $Author: Darko Kolakovic$

  Test different character conversions
  Copyright: CommonSoft Inc.
  Aug. 2k2 Darko Kolakovic
*/

// Group=Examples

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#include "KStrings.h"  //ChtoAscii()
#include <iostream>
#include <iomanip.h>  //std::endl

extern BOOL TsWriteToView(LPCTSTR lszText);
extern TCHAR* ByteToHex(BYTE cValue, TCHAR* szResult);

//TestCharConversion()----------------------------------------------------------
/*Test different conversions of a character from and to string.

  Returns: true if successful, otherwise returns false.
 */
bool TestCharConversion()
{
TsWriteToView("TestCharConversion()\r\n");

bool bRes = true;
char szResult[16];

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
  cout << (int)chTable[i] << " = 0x" 
       << ByteToHex(chTable[i], szResult) 
       << ", "
       << ChtoAscii(chTable[i])
       << endl;
  if ( strcmp(szHexTable[i], szResult) != 0 )
    {
    cout << "  " << BoolToA(bRes = false) 
         << " wrong hex value" << endl;
    }
  if (strcmp(szAsciiTable[i], ChtoAscii(chTable[i])) != 0 )
    {
    cout << "  " << BoolToA(bRes = false) 
         << " wrong ASCII value" << endl;
    }

  i++;
  }

TsWriteToView("======================\r\n");
return bRes;
}

//////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: 
 * 2    Biblioteka1.1         10/09/2002 5:55:38 PMDarko Kolakovic 
 * 1    Biblioteka1.0         19/08/2002 9:16:44 AMDarko Kolakovic 
 *$
 *****************************************************************************/
