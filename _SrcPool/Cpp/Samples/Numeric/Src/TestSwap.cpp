/*$Workfile: TestSwap.cpp$: implementation file
  $Revision: 5$ $Date: 2004-10-05 14:05:40$
  $Author: Darko$

  Test byte flipping
  Copyright: CommonSoft Inc.
  May 2k1 D.Kolakovic
*/
// Group=Examples

#include "stdafx.h"
#include "KTrace.h"        //ASSERT macro
#include "KTypedef.h"      //DWORD typedef
#include "KSwpByteOrder.h" //TSwapByteOrder template
#include "KRvrElements.h"  //ReverseElements()

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(const int& iValue);
extern bool TsWriteToViewLn(const int& iValue);

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif


union Conversion
 {
 char   m_Char;
 short  m_Short;
 long   m_Long;
 float  m_Float;
 double m_Double;
 char   m_cData[8];
 };

class TestArray
  {
  public:
    TCHAR m_cValue[45];
  };

//TestByteSwap()---------------------------------------------------------------
/*Test reversing order of bytes in primitive types or array elements.

  TODO: Unicode test
 */
bool TestByteSwap()
{
TsWriteToViewLn(_T("TestByteSwap()"));
TESTENTRY logEntry =
  {_T("TSwapByteOrder::TSwapByteOrder<long>()"), _T("KSwpByteOrder.h"), false};

bool bRes = true;
TCHAR szOutput[128];
szOutput[0] = _T('\0');

Conversion Temp;
int i;

 //Test reversing long
Temp.m_Long = 0xAABBCCDD;
_stprintf(szOutput, _T("%X"), Temp.m_Long);
std::_tcout << _T("long   = 0x") << szOutput;
long lResult = TSwapByteOrder<long>(Temp.m_Long);
_stprintf(szOutput, _T("%X"), lResult);
std::_tcout << _T(" swapped = 0x") << szOutput << std::endl;
bRes = (lResult == 0xDDCCBBAA);
  //Write test log
logEntry.m_bResult = bRes;
LogTest(&logEntry);

 //Test reversing double
if(bRes)
  {
  logEntry.m_szObjectName = _T("TSwapByteOrder::TSwapByteOrder<double>()");

  Temp.m_Double = 3.1415;
  std::_tcout << _T("double = ") << Temp.m_Double << _T(" [ ");
  for(i = 0; i < sizeof(double); i++)
    {
    std::_tcout << (int)(unsigned char)Temp.m_cData[i] << _T(' ');
    }
  std::_tcout << _T(']') << std::endl;
  Conversion Result;
  Result.m_Double = TSwapByteOrder<double>(Temp.m_Double);
  std::_tcout << _T("swapped= ") << Result.m_Double << _T(" [ ");
  for(i = 0; i < sizeof(double); i++)
    {
    std::_tcout << (int)(unsigned char)Result.m_cData[i] << _T(' ');
    }
  std::_tcout << _T(']') << std::endl;

  bRes = true;//(lResult == 0xDDCCBBAA); Fixme!
    //Write test log
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);
  }

 //Test reversing an array with the template class
if (bRes)
  {
  logEntry.m_szObjectName = _T("TSwapByteOrder::TSwapByteOrder<LPTSTR>()");

  TestArray aResult;
  _stprintf(aResult.m_cValue,_T("The quick brown fox jumps over the lazy dog."));
  std::_tcout << aResult.m_cValue << std::endl;
  aResult = TSwapByteOrder<TestArray>(aResult);
  for(i = 0; i < sizeof(TestArray); i++)
    {
    if (aResult.m_cValue[i] == _T('\0'))
      std::_tcout << _T("[0]");
    else
      std::_tcout << aResult.m_cValue[i];
    }

  bRes = true;//(lResult == 0xDDCCBBAA); Fixme!
    //Write test log
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);
  }

//Test reversing an array
if (bRes)
  {
  logEntry.m_szObjectName = _T("ReverseElements(<LPTSTR>, unsigned int)");
  logEntry.m_szFileName = _T("KStrPalindrome.cpp");

  _stprintf(szOutput,_T("The quick brown fox jumps over the lazy dog."));
  std::_tcout << szOutput << std::endl;
  ReverseElements(szOutput, (unsigned int)_tcslen(szOutput));
  std::_tcout << szOutput << std::endl;

  bRes = true;//(lResult == 0xDDCCBBAA); Fixme!
    //Write test log
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);
  }

//TODO: SwapByteOrder() KSwpByte.h

TsWriteToView(LOG_EOT);
TsWriteToView(_T("\r\n"));
return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  5    Biblioteka1.4         2004-10-05 14:05:40  Darko           fixed Unicode
 *       build
 *  4    Biblioteka1.3         2004-07-07 17:41:02  Darko           replaced
 *       iomainp.h with stdafx.h
 *  3    Biblioteka1.2         2002-08-03 19:27:52  Darko           
 *  2    Biblioteka1.1         2002-02-03 18:11:14  Darko           
 *  1    Biblioteka1.0         2001-07-26 21:31:37  Darko           
 * $
 *****************************************************************************/
