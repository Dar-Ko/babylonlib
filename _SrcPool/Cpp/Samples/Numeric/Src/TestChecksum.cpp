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
extern unsigned int GetMod10(unsigned int* pnDigit, int iCount);

bool ValidateLuhn(const unsigned* pnDigit, int iCount);
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
  logEntry.m_szObjectName = _T("GetMod10()");

  
  const int VISALENGTH = 16;
  unsigned nAccountVisa[3][VISALENGTH] =
    {
    5,0,1,0,   1,2,0,0,   7,3,4,5,   1,1,5,8, //valid account number
    4,5,2,0,   0,1,0,1,   9,4,4,3,   4,1,0,8, //valid account number
    4,4,0,8,   0,4,1,2,   3,4,5,6,   7,8,9,0  //unvalid account number
    };

  std::_tcout << _T("Account number")  << std::endl;
  int i;
  for (i = 0; i < VISALENGTH; i++)
    std::_tcout << nAccountVisa[0][i];
  cChk = (uint8_t)GetMod10(&nAccountVisa[0][0], VISALENGTH -1);
  bRes = (nAccountVisa[0][VISALENGTH -1] == (unsigned)cChk);
  bRes ? std::_tcout << _T(" is valid.") << std::endl :
         std::_tcout << _T(" is not valid! ") << std::endl;
   //Verify the result
  bRes = (bRes && ValidateLuhn(&nAccountVisa[0][0], VISALENGTH));
  if (bRes)
    {
    for (i = 0; i < VISALENGTH; i++)
      std::_tcout << nAccountVisa[1][i];
    cChk = (uint8_t)GetMod10(&nAccountVisa[1][0], VISALENGTH -1);
    bRes = (nAccountVisa[1][VISALENGTH -1] == (unsigned)cChk);
    bRes ? std::_tcout << _T(" is valid.") << std::endl :
           std::_tcout << _T(" is not valid! ") << std::endl;
    //Verify the result
    bRes = (bRes && ValidateLuhn(&nAccountVisa[1][0], VISALENGTH));
    }
    
  if (bRes)  //Check unvalid number
    {
    for (i = 0; i < VISALENGTH; i++)
      std::_tcout << nAccountVisa[2][i];
    cChk = (uint8_t)GetMod10(&nAccountVisa[2][0], VISALENGTH -1);
    bRes = (nAccountVisa[2][VISALENGTH -1] != (unsigned)cChk);
    bRes ? std::_tcout << _T(" is not valid!") << std::endl :
           std::_tcout << _T(" is valid. ") << std::endl;
    //Verify the result
    bRes = (bRes && !ValidateLuhn(&nAccountVisa[2][0], VISALENGTH));
    }

  if (bRes)  
    {
    unsigned nBadNumber[]   = {1, 1, 1, 1};
    unsigned nValidNumber[] = {8, 7, 6, 3};
    cChk = (uint8_t)GetMod10(nBadNumber, 3);
    bRes = (nBadNumber[3] != (unsigned)cChk);
    if (bRes)
      {
      cChk = (uint8_t)GetMod10(nValidNumber, 3);
      bRes = (nValidNumber[3] == (unsigned)cChk);
      }
    }
    
  if (bRes)  
    {
    unsigned nAccountNo[] = {4,4,6,  6,6,7,  6,5,1};
    cChk = (uint8_t)GetMod10(nAccountNo, SIZEOFARR(nAccountNo) -1);
    bRes = ValidateLuhn(nAccountNo,SIZEOFARR(nAccountNo) );
    bRes = bRes && (nAccountNo[SIZEOFARR(nAccountNo) -1] == (unsigned)cChk);
    }
  
  if (bRes)  
    {
    unsigned nSerialNo[] = {1,2,8,3,7,9,7,1,9,2,3,7,5,9,9,2,3,4,7,8,0,2,3,4,8, 0xffff};
    //Calculate the checksum
    nSerialNo[SIZEOFARR(nSerialNo) -1] = GetMod10(nSerialNo, 
                                                  SIZEOFARR(nSerialNo) -1);
    //Validate the checksum                                                  
    bRes = ValidateLuhn(nSerialNo,SIZEOFARR(nSerialNo) );
    }
  
  logEntry.m_bResult = bRes;
  LogTest(&logEntry); //Write test log
  }

TsWriteToView(LOG_EOT);
TsWriteToView(_T("\r\n"));
return bRes;
}

//-----------------------------------------------------------------------------
/*Verifies if the last number in the given array is valid checksum calculated
  with naive implementation of the Luhn algorithm.

  Returns: true if checksum is valid, otherwise returns false.

  See also: GetMod10()
 */
bool ValidateLuhn(const unsigned* pnDigit, //[in] array of decimal digits from
                     //the set [0, 9]
                     int iCount //[in] size of the array
                     )
{
unsigned nSum = 0;
if ((pnDigit != NULL) && (iCount > 0))
  {
  bool bTransform = false; //marks a digit to be transformed
  iCount--; //index
  while (iCount >= 0)
    {
    unsigned nDigit = pnDigit[iCount];
    if (nDigit >= 10)
      return false; //not-a- digit error
    if (bTransform)
      {
      nDigit *= 2; //Double the value
      if (nDigit > 9)
        nDigit -= 9; //nDigit = (nDigit % 10) + 1
      }
    nSum += nDigit; //Sum the digits
    bTransform = !bTransform; //Alternate the transform
    iCount--;
    }
  }

return (nSum % 10 == 0);
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: $
 ******************************************************************************/
