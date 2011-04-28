/*$RCSfile: TestBtoA.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2011/04/28 21:59:22 $
  $Author: ddarko $

  Test converting an array of bits to the string.
  Copyright: CommonSoft Inc.
  2011-04-25 Darko Kolakovic
*/

// Group=Examples

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */
#include "stdafx.h"
#include "KStrings.h" //BintoA()
#include "STL/KOStream.h" //_tcout

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);

//-----------------------------------------------------------------------------
/*Basic test of method converting an array of bits to the string.

  Returns: true if successful, otherwise returns false.

  See also: KStrings.h, BintoA();
 */
bool TestBintoA(LPTSTR szOutput,    //[in/out] text representation of
                                     //the binary value
                const uint32 dwTest //[in] value to convert
               )
{
bool bRes = true;

LPTSTR szResult = BintoA(szOutput, dwTest, 32, 0, _T('1'), _T('0'));
if (szOutput != NULL)
  bRes = (szResult != NULL); //Check if result is valid string
//Check if string length is appropriate
bRes = bRes && (szOutput[sizeof(uint32) * CHAR_BIT] == _T('\0'));

return bRes;
}

//-----------------------------------------------------------------------------
/*Test converting an array of bits to the string.

  Returns: true if successful, otherwise returns false.

  See also: KStrings.h, BintoA();
 */
bool TestBintoA()
{
TESTENTRY logEntry;
bool& bRes = logEntry.m_bResult;
bRes = true;
#ifndef CHAR_BIT
  const int CHAR_BIT = 8 ; //Number of bits in a byte
#endif
logEntry.m_szObjectName = _T("BintoA()");
logEntry.m_szFileName = _T("KStrBtoA.c");

TsWriteToView(_T("TestBintoA()\r\n"));
  //Test BintoA()
uint32 dwTest = 0x0A0A0101; //b1010 0000 1010 0000 0001 0000 0001
TCHAR szOutput[(sizeof(dwTest) + 1) * CHAR_BIT] =
  {
  _T('B'),_T('A'),_T('D'),_T('E'),
  _T('B'),_T('A'),_T('D'),_T('E'),
  _T('B'),_T('A'),_T('D'),_T('E'),
  _T('B'),_T('A'),_T('D'),_T('E'),
  _T('B'),_T('A'),_T('D'),_T('E'),
  _T('B'),_T('A'),_T('D'),_T('E'),
  _T('B'),_T('A'),_T('D'),_T('E'),
  _T('B'),_T('A'),_T('D'),_T('E'),
  _T('B'),_T('A'),_T('D'),_T('E'),
  _T('B'),_T('A'),_T('D'),_T('E')
  };

bRes = TestBintoA(szOutput, dwTest);
//Check if buffer is not overflown, since the function omits this validation
bRes = bRes &&
       (szOutput[sizeof(uint32) * CHAR_BIT + 1] == _T('A')) &&
       (szOutput[sizeof(uint32) * CHAR_BIT + 2] == _T('D')) &&
       (szOutput[sizeof(uint32) * CHAR_BIT + 3] == _T('E'));

//Check for correct conversion
bRes = bRes &&
       (szOutput[ 0] == _T('0')) &&
       (szOutput[ 1] == _T('0')) &&
       (szOutput[ 2] == _T('0')) &&
       (szOutput[ 3] == _T('0'));
bRes = bRes &&
       (szOutput[ 4] == _T('1')) &&
       (szOutput[ 5] == _T('0')) &&
       (szOutput[ 6] == _T('1')) &&
       (szOutput[ 7] == _T('0'));
bRes = bRes &&
       (szOutput[ 8] == _T('0')) &&
       (szOutput[ 9] == _T('0')) &&
       (szOutput[10] == _T('0')) &&
       (szOutput[11] == _T('0'));
bRes = bRes &&
       (szOutput[12] == _T('1')) &&
       (szOutput[13] == _T('0')) &&
       (szOutput[14] == _T('1')) &&
       (szOutput[15] == _T('0'));

bRes = bRes &&
       (szOutput[16] == _T('0')) &&
       (szOutput[17] == _T('0')) &&
       (szOutput[18] == _T('0')) &&
       (szOutput[19] == _T('0'));
bRes = bRes &&
       (szOutput[20] == _T('0')) &&
       (szOutput[21] == _T('0')) &&
       (szOutput[22] == _T('0')) &&
       (szOutput[23] == _T('1'));
bRes = bRes &&
       (szOutput[24] == _T('0')) &&
       (szOutput[25] == _T('0')) &&
       (szOutput[26] == _T('0')) &&
       (szOutput[27] == _T('0'));
bRes = bRes &&
       (szOutput[28] == _T('0')) &&
       (szOutput[29] == _T('0')) &&
       (szOutput[30] == _T('0')) &&
       (szOutput[31] == _T('1'));

LogTest(&logEntry);
TsWriteToViewLn(LOG_EOT);
return bRes;
}
//////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: TestBtoA.cpp,v $
 *Revision 1.1  2011/04/28 21:59:22  ddarko
 *Created
 *
 *****************************************************************************/
