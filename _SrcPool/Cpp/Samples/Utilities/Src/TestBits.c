/*$RCSfile: TestBits.c,v $: implementation file
  $Revision: 1.1 $ $Date: 2011/05/10 18:42:51 $
  $Author: ddarko $

  Test bitwise operations.
  2011-05-10 Darko Kolakovic
*/

/* Group=Examples                                                            */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "stdafx.h"
#include "KTypedef.h"

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "stdafx.h"
#include "KTypedef.h"
#include "KBitMan.h"    //Bitwise operations

#include "KProgCst.h"
#include "KProgCst.inl"
#ifndef bool
  #include "KTypedef.h"
#endif

#ifndef _T
  #include "KTChar.h"
#endif

#ifndef TRACE0
  #include "KTrace.h"
#endif

#ifndef LOG_EOT
  #include "KTestLog.h"
#endif

#ifndef _ENDIAN_ORDER_
  #define _ENDIAN_ORDER_ 0
#endif

#include "KStrings.h"   //BintoA()

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
bool TestBits();

#ifndef CHAR_BIT
  const int CHAR_BIT = 8; //Number of bits in a byte
#endif

/*Data type allowing acces to indvidual bit-fields.

  Note: using bit-fields is potentially thread unsafe, if multiple mutexes
  are used to guard different fields. Use instead single mutex to protect
  all fields together.

  Note: The type-specifier for the bit-field declarator must be unsigned int,
  signed int or int.
  A Microsoft extension to the ANSI C standard allows char and long types
  (both signed and unsigned) for bit fields. Also bit-fields with types of the
  same size are packed to fit machine word (32 or 64 bit long). If types for
  adjacent bit-fields are of different sizes then the padding is inserted.

  Note: ANSI C standard does not prescribe bit-field order, allowing different
  compiler implementations. Typically, the order of bit-fields are reversed
  between big and little endian architectures.

  See also: BYTE_MSB
 */
typedef struct tagTestBitfield
    {
    int B0 :1; //Bit 0
    int B1 :1; //Bit 1
    int B2 :1; //Bit 2
    int B3 :1; //Bit 3
    int B4 :1; //Bit 4
    int B5 :1; //Bit 5
    int B6 :1; //Bit 6
    int B7 :1; //Bit 7
    } STestBitfield;  //Binary digit

/*---------------------------------------------------------------------------*/
/*Testing various operations with bits using predefined macros.

  Returns: true if successful, otherwise returns false.
 */
bool TestBits()
{
bool bResult = false;
int iResult = 0;
uint32_t nValue     = 0x1111000; //b0000 0001 0001 0001 0001 0000 0000 0000
uint32_t nMaskTrue  = 0x0011000; //b0000 0000 0000 0001 0001 0000 0000 0000
uint32_t nMaskFalse = 0x0001100; //b0000 0000 0000 0000 0001 0001 0000 0000

unsigned int nEndian = _ENDIAN_ORDER_;
struct tagTestEntry logEntry;
TCHAR szOutput[sizeof(uint32_t) * CHAR_BIT + 1];

STestBitfield testValue;
testValue.B0 = 0x0;
testValue.B1 = 0x1;
testValue.B2 = 0x1;
testValue.B3 = 0x0;
testValue.B4 = 0x0;
testValue.B5 = 0x0;
testValue.B6 = 0x0;
testValue.B7 = 0x1;

TsWriteToViewLn(_T("TestBits()"));

switch (nEndian)
  {
  case _ENDIAN_LITTLE_:
    TRACE0(_T("Little Endian\n"));
    TsWriteToViewLn(_T("Little Endian\n"));
    break;
  case _ENDIAN_BIG_:
    TRACE0(_T("Big Endian\n"));
    TsWriteToViewLn(_T("Big  Endian\n"));
    break;
  case _ENDIAN_PDP_:
    TRACE0(_T("PDP Endian\n"));
  default:
    TRACE0(_T("unsupported endian\n"));
    TsWriteToViewLn(_T("unsupported endian"));
  };

//Test ANSI C bit-field compliance
logEntry.m_szObjectName = _T("bit-field");
logEntry.m_szFileName   = _T("C compiler");

bResult =  ((testValue.B0 == 0x0) &&
            (testValue.B1 != 0x0) &&  //MSVC: testValue.B1 = 0XFFFFFFFF
            (testValue.B2 != 0x0) &&  //MSVC: testValue.B2 = 0XFFFFFFFF
            (testValue.B3 == 0x0) &&
            (testValue.B4 == 0x0) &&
            (testValue.B5 == 0x0) &&
            (testValue.B6 == 0x0) &&
            (testValue.B7 != 0x0)  );

iResult = sizeof(STestBitfield);
TRACE1(_T("sizeof(STestBitfield) = %d bytes."), iResult);

TsWriteToView(_T("Bit-fields: "));
BintoA(szOutput,*(unsigned long*)&testValue, CHAR_BIT, 0, _T('1'), _T('0'));
TsWriteToViewLn(szOutput);

logEntry.m_bResult = bResult;
LogTest(&logEntry);
TsWriteToViewLn(logEntry.m_szObjectName);

//Test seting and clearing bits of basic types
logEntry.m_szFileName   = _T("KBitMan.h");
logEntry.m_szObjectName = _T("SET_MBITS()");
SET_MBITS(nValue, nMaskFalse);
logEntry.m_bResult = (nValue == 0x01111100);
LogTest(&logEntry);
TsWriteToViewLn(logEntry.m_szObjectName);
bResult = bResult && logEntry.m_bResult;

logEntry.m_szObjectName = _T("CLR_MBITS()");
CLR_MBITS(nValue, nMaskTrue);
logEntry.m_bResult = (nValue == 0x01100100);
LogTest(&logEntry);
TsWriteToViewLn(logEntry.m_szObjectName);
bResult = bResult && logEntry.m_bResult;

logEntry.m_szObjectName = _T("TGL_MBITS()");
TGL_MBITS(nValue, nMaskFalse);
logEntry.m_bResult = (nValue == 0x01101000);
LogTest(&logEntry);
TsWriteToViewLn(logEntry.m_szObjectName);
bResult = bResult && logEntry.m_bResult;

logEntry.m_szObjectName = _T("GET_MBITS()");
iResult = (int)GET_MBITS(nValue, nMaskTrue);
logEntry.m_bResult = (iResult == 0x00001000);
LogTest(&logEntry);
TsWriteToViewLn(logEntry.m_szObjectName);
bResult = bResult && logEntry.m_bResult;

logEntry.m_szObjectName = _T("SET_BIT()");
TsWriteToViewLn(logEntry.m_szObjectName);
iResult = _MASK_nBIT(16);
BintoA(szOutput,iResult, CHAR_BIT * sizeof(iResult), 0, _T('1'), _T('0'));
TsWriteToView(_T("Mask: "));
TsWriteToViewLn(szOutput);

SET_BIT(nValue, 16);
logEntry.m_bResult = (nValue == 0x01111000);
SET_BIT(nValue, 0);  //Set the Least Significant Bit (LSB)
logEntry.m_bResult = (nValue == 0x01111001) && logEntry.m_bResult;
SET_BIT(nValue, 20);  //Try to set bit previously set
logEntry.m_bResult = (nValue == 0x01111001) && logEntry.m_bResult;
LogTest(&logEntry);
bResult = bResult && logEntry.m_bResult;

TsWriteToViewLn(LOG_EOT);
return bResult;
}

/* ////////////////////////////////////////////////////////////////////////// */
/******************************************************************************
 * $Log: TestBits.c,v $
 * Revision 1.1  2011/05/10 18:42:51  ddarko
 * Created
 *
 *****************************************************************************/

