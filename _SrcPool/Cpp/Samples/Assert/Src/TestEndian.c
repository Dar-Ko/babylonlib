/*$Workfile: TestEndian.c$: implementation file
  $Revision: 3$ $Date: 2004-11-23 15:51:34$
  $Author: Darko Kolakovic$

  Test machine architecture.
  Copyright: CommonSoft Inc.
  2004-09-13 Darko Kolakovic
*/

/* Group=Examples                                                            */

#if defined (_MSC_VER)   /*Microsoft Visual Studio C/C++ compiler */
  #if defined (_UNICODE) && !defined (UNICODE)
    #define UNICODE
  #endif

  #if defined (UNICODE) && !defined (_UNICODE)
    #define _UNICODE
  #endif

  #if _MSC_VER >= 800    /*Visual C++, 32-bit, version 1.0 */
    #include "KType32.h" /*uint8_t typedef*/
  #else
    #include "KType16.h" /*uint8_t typedef*/
  #endif
#else
  #include <stdint.h>
#endif

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

extern bool TsWriteToViewLn(LPCTSTR lszText);
bool TestEndian();

typedef union tagTestEndian
  {
  uint8_t   cByte[sizeof(uint32_t)];
  uint32_t  nInt;
  } UTestEndian;

/*---------------------------------------------------------------------------*/
/*Test a machine architecture.

  Returns: true if test is successful; if _ENDIAN_ORDER_ is wrongly defined or
  not define at all, returns false.

  See also: _ENDIAN_ORDER_, _ENDIAN_LITTLE_, _ENDIAN_BIG_
 */
bool TestEndian()
{
bool bResult = false;
unsigned int nEndian = _ENDIAN_ORDER_;
UTestEndian testValue;
testValue.nInt = 0x1;
TsWriteToViewLn(_T("TestEndian()"));

if (testValue.cByte[0] == (uint8_t)0x1)
  {
  TRACE0(_T("Little Endian"));
  TsWriteToViewLn(_T("Little Endian\n"));
  bResult = (bool)(nEndian == _ENDIAN_LITTLE_);
  }
else if (testValue.cByte[sizeof(uint32_t)-1] == (uint8_t)0x1)
  {
  TRACE0(_T("Big Endian"));
  TsWriteToViewLn(_T("Big  Endian\n"));
  bResult = (bool)(nEndian == _ENDIAN_BIG_);
  }
else if (testValue.cByte[sizeof(uint32_t)/2] == (uint8_t)0x1)
  {
  TRACE0(_T("PDP Endian"));
  TsWriteToViewLn(_T("PDP Endian\n"));
  bResult = (bool)(nEndian == _ENDIAN_PDP_);
  }
else
  {
  TRACE0(_T("unknown endian\n"));
  TsWriteToViewLn(_T("unknown endian"));
  }

TsWriteToViewLn(LOG_EOT);
return bResult;
}

/* ////////////////////////////////////////////////////////////////////////// */
/******************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2004-11-22 16:47:15  Darko Kolakovic
 * $
 *****************************************************************************/

