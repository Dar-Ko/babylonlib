/*$Workfile: TestLcm.cpp$: implementation file
  $Revision: 2$ $Date: 2005-06-20 17:21:14$
  $Author: Darko Kolakovic$

  Test checksum methods
  Copyright: CommonSoft Inc.
  2007-06-13 Darko Kolakovic
*/
// Group=Examples

#include "stdafx.h"
#include "KTrace.h"        //ASSERT macro
#include "STL/KBoolStream.h"
#ifndef KSTL_IO
  #include "STL/KOStream.h"
#endif
#include "KTypedef.h" //int64 typedef
#ifndef ETX
  #include "KCharCst.h" //ETX
#endif

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(const int& iValue);
extern bool TsWriteToViewLn(const int& iValue);

extern "C" uint8_t GetLRC(uint8_t* pbData,int iCount);
extern bool IsLRCValid(const BYTE chReceivedLRC, BYTE* pbData, int iCount);
extern int GetMod10(char* pbData);

//------------------------------------------------------------------------------
/*Test checksum calculation.

  Returns: true if successful, otherwise returns false.
 */
bool TestChecksum()
{
TsWriteToViewLn(_T("TestChecksum()"));

bool bRes = true;

uint8_t cArray[] = { 10,   0,  11, 255,  15,   2,  13,  18, 127, 192, ETX, 80};
int iSize = sizeof(cArray);

const int DATAGRAMSIZE = iSize - sizeof(uint8_t); //length of message block
const int DATASIZE = DATAGRAMSIZE - sizeof(uint8_t); //length of data

                    //without termination character
uint8_t cChk = 0; //checksum
const uint8_t LRCa = 83; //LRC of arraye less termination character

//Test Longitudinal Redundancy Checksum
TESTENTRY logEntry =
  {_T("GetLRC()"), _T("KGetLRC.cpp"), false};

cChk = GetLRC(cArray, DATASIZE);

bRes = (cChk == LRCa);
std::_tcout << _T("Longitudinal Redundancy Checksum is ")
            << (tbool)bRes << _T("  ") << (int)cChk  << std::endl;

logEntry.m_bResult = bRes;
LogTest(&logEntry); //Write test log

if (bRes)
  {
  logEntry.m_szFileName = _T("KIsLRC.cpp");
  logEntry.m_szObjectName = _T("IsLRCValid()");
  //This method requires termination character
  bRes = !IsLRCValid(cChk, cArray, DATASIZE);
  bRes ? std::_tcout << _T("Data array is not valid (OK).") << std::endl: //Expected result
         std::_tcout << _T("Data array validation failed!") << std::endl;
  if(bRes)
    {
    bRes = IsLRCValid(cArray[DATAGRAMSIZE], cArray, DATAGRAMSIZE);
    bRes ? std::_tcout << _T("LRC is valid.") << std::endl :
           std::_tcout << _T("LRC is not valid! ") << std::endl;
    }

  logEntry.m_bResult = bRes;
  LogTest(&logEntry); //Write test log
  }

if (bRes)
  {
  logEntry.m_szFileName = _T("KMod10.cpp");
  logEntry.m_szObjectName = _T("mod10()");
  GetMod10(cArray);
  }

TsWriteToView(LOG_EOT);
TsWriteToView(_T("\r\n"));
return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: $
 ******************************************************************************/
