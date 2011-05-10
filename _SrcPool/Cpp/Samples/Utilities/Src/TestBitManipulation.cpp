/*$RCSfile: TestBitManipulation.cpp,v $: implementation file
  $Revision: 1.5 $ $Date: 2011/05/10 18:43:19 $
  $Author: ddarko $

  Test bitwise operations
  Copyright: CommonSoft Inc.
  2011-04-24 Darko Kolakovic
*/

// Group=Examples

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "stdafx.h"
#include "KTypedef.h"
#include "STL/KBinStream.h" //BintoStream()
#include "KBitMan.h"  //Bitwise operations
#include "KGuid.h"    //CGuid class
#include "KStrings.h" //BintoA()

extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToView(const int& iValue);

//-----------------------------------------------------------------------------
/*Testing various operations with bits.

  Returns: true if successful, otherwise returns false.
 */
bool TestBitManipulation()
{
TsWriteToViewLn(_T("TestBitManipulation()"));
bool bRes = true;
#ifndef CHAR_BIT
  const T CHAR_BIT = 8; //Number of bits in a byte
#endif
TCHAR szOutput[sizeof(uint32_t) * CHAR_BIT + 1];

  //Test log creation
TESTENTRY logEntry =
  {_T("STATUS8.BIT"), _T("KProgCst.h"), false};

/*Test accessing bit fields
 */
#ifdef _MSC_VER 
  /*Note: A Microsoft extension to the ANSI C standard allows char and
    long types (both signed and unsigned) for bit fields. Otherwise
    the type-specifier for the declarator must be unsigned int, signed int
    or int.
   */
  STATUS8 Status;
  Status.BYTE = (uint8)0xD2; //b1101 0010
  bRes = ((Status.BIT.B0 == 0) && 
          (Status.BIT.B1 == 1) &&
          (Status.BIT.B2 == 0) &&
          (Status.BIT.B3 == 0) &&
          (Status.BIT.B4 == 1) &&
          (Status.BIT.B5 == 0) &&
          (Status.BIT.B6 == 1) &&
          (Status.BIT.B7 == 1));
#endif

TsWriteToView(_T("Status = "));
TsWriteToView(Status.BYTE);
TsWriteToView(_T(" = "));
BintoA(szOutput, Status.BYTE, CHAR_BIT, 0, _T('1'), _T('0'));
TsWriteToViewLn(szOutput);

  //Write test log
logEntry.m_bResult = bRes;
LogTest(&logEntry);

//Test bitwise manipulators
logEntry.m_szObjectName = _T("ReverseBits<T>()");
logEntry.m_szFileName   = _T("KBitMan.h");

#ifdef _UNICODE
  LPCTSTR FORMAT1 = _T("nValue = %ws\n");
#else
  LPCTSTR FORMAT1 = _T("nValue = %s\n");
#endif
uint32_t nValue = 0xD2E31200; //b1101 0010 1110 0011 0001 0010 0000 0000
TRACE1(FORMAT1, BintoA(szOutput, nValue, 32, 0, _T('1'), _T('0')));

std::_tcout << _T("value   = "); 
BintoStream<uint32_t>(std::_tcout, nValue) << std::endl;

uint32_t nResult = ReverseBits<uint32_t>(nValue);
TRACE1(FORMAT1, BintoA(szOutput, nResult, 32, 0, _T('1'), _T('0')));
std::_tcout << _T("reverse = ");
BintoStream<uint32_t>(std::_tcout, nResult) << std::endl;

bRes = bRes && (nValue == ReverseBits<uint32_t>(nResult));  //Validate result

nValue = 0xD2E30021; //b1101 0010 1110 0011 0000 0000 0010 0001

nResult = ReverseBits<uint32_t>(nValue);
bRes = bRes && (nValue == ReverseBits<uint32_t>(nResult));

CGuid nTestData; //data structure used for testing
nTestData.m_uPack.b.Data1 = 0x04030201; //b0000 0100 0000 0011 0000 0010 0000 0001
#ifdef TEST_C2676
  /*Following will produce compiler error: 
    'CGuid' does not define binary '>' operator (MSVC++ error C2676)
   */
  CGuid nTestRes = ReverseBits<CGuid>(nTestData);
#endif
  //Write test log
logEntry.m_bResult = bRes;
LogTest(&logEntry);

//Test parity macro
logEntry.m_szObjectName = _T("PARITY()");

nResult = nValue;      //value to compute the parity of
bool bParity = false;  //parity of nValue

while (nResult != 0)   //Count all bits set to 1
  {
  bParity = !bParity;  //true if bit count is odd number
  nResult = nResult & (nResult - 1);
  }

PARITY(nValue);

bRes = (bParity == (nValue == 1)); //check odd parity

nValue = 0x1111000;

nResult = nValue;  //value to compute the parity of
bParity = false;   //parity of nValue

while (nResult != 0)   //Count all bits set to 1
  {
  bParity = !bParity;  //false if bit count is even number
  nResult = nResult & (nResult - 1);
  }

PARITY(nValue);
bRes = bRes && (bParity == (nValue == 1)); //check even parity
//TODO: PARITY64

  //Write test log
logEntry.m_bResult = bRes;
LogTest(&logEntry);

//Test bit masks
nValue = 0x1111000;              //b0000 0001 0001 0001 0001 0000 0000 0000
uint32_t nMaskTrue  = 0x0011000; //b0000 0000 0000 0001 0001 0000 0000 0000
uint32_t nMaskFalse = 0x0001100; //b0000 0000 0000 0000 0001 0001 0000 0000

logEntry.m_szObjectName = _T("GetFlag<>()");

bRes = bRes && ( GetFlag(nValue, nMaskTrue));  //check if flags are up
bRes = bRes && (!GetFlag(nValue, nMaskFalse)); //check if one flag is down

  //Write test log
logEntry.m_bResult = bRes;
LogTest(&logEntry);

if (bRes)
  {
  //Test obtaining flag value from the chunk of data
  logEntry.m_szObjectName = _T("GET_FLAG(x, p)");
  nValue = 0;
  int p;
  while(nValue <= 255)
    {
    std::_tcout << nValue << _T(" = ");
    p = CHAR_BIT;
    while (--p >= 0)
      {
      std::_tcout << (nResult = GET_FLAG(nValue, p));
      //Validate test result
      bRes = bRes && ( nResult == (((nValue & (1 << p)) != 0) ? 1 : 0) );
      //FixMe: reverse bit order D.K.
      }
    std::_tcout << std::endl;
    nValue++;
    }

  if(bRes)
    {
    p = sizeof((GUID)nTestData) * CHAR_BIT;
    while(--p >= 0)
      {
      nResult = GET_FLAG((GUID)nTestData, p);
      std::_tcout << nResult;
      if ((p % 4) == 0)
        std::_tcout << _T(" ");
      }
    std::_tcout << std::endl;

    //Validate (127-32)th bit
    bRes = bRes && 
           (GET_FLAG((GUID)nTestData,
              ((sizeof((GUID)nTestData) - sizeof(uint32_t)) * CHAR_BIT -1)) == 1);
    }

    //Write test log
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  //Test setting a flag on arbitrary sized data chunk
  logEntry.m_szObjectName = _T("SET_FLAG(x, p)");

  nValue = 0x1111000;              //b0000 0001 0001 0001 0001 0000 0000 0000
  p = 0;//sizeof(nValue) * CHAR_BIT;
  while (p < 255)
    {
    std::_tcout << p << _T(". ")                     << std::endl <<
     (       p % 8 ) << _T(": ") << (      p & 7  )  << _T(" counter [0, 7]") << std::endl <<
     (    8-(p % 8)) << _T(": ") << (    7-(p & 7))  << _T(" counter [7, 0]") << std::endl <<
     (0x80>>(p % 8)) << _T(": ") << (0x80>>(p & 7))  << _T(" increment 2^p ") << std::endl <<
     (       p % 8 ) << _T(": ") << (      p & 7  )  << _T(" counter [0, 7]") << std::endl <<
     (       p / 8 ) << _T(": ") << (      p >> 3 )  << _T(" div 8") << std::endl;
p++;
    }
 p= 0;
 while (p < sizeof(nValue) * CHAR_BIT)
 {
   nValue = 0;
   SET_FLAG(nValue, p);
BintoStream<uint32_t>(std::_tcout, nValue) << std::endl;
   p++;
 }
  p = 30;
  nValue = 0x1111000;    
  ((int8_t*)&nValue)[(p)/CHAR_BIT] |=  (0x80>>((p)%CHAR_BIT));

    SET_FLAG(nValue, p);  //0x41111000 = b0100 0001 0001 0001 0001 0000 0000 0000

//  #define SET_FLAG(x, pos) (x[(pos)/CHAR_BIT] |=  (0x80>>((pos)%CHAR_BIT)))

    //Write test log
//  logEntry.m_bResult = bRes;
//  LogTest(&logEntry);

//#define CLR_FLAG(X, pos) (x[(pos)/BICHAR_BITTS] &= ~(0x80>>((pos)%CHAR_BIT)))

    //Write test log
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  TsWriteToViewLn(LOG_EOT);
  }
return bRes;
}

//////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: TestBitManipulation.cpp,v $
 *Revision 1.5  2011/05/10 18:43:19  ddarko
 *Aded TestBits
 *
 *Revision 1.4  2011/05/09 21:44:21  ddarko
 **** empty log message ***
 *
 *Revision 1.3  2011/05/05 21:28:21  ddarko
 *GET_FLAG()
 *
 *Revision 1.2  2011/05/02 22:10:58  ddarko
 *testing <bitset>
 *
 *Revision 1.1  2011/04/28 21:59:22  ddarko
 *Created
 *
 *****************************************************************************/

/*Reference: Bit Twiddling Hacks by Sean Eron Anderson
  http://graphics.stanford.edu/~seander/bithacks.html 
 */