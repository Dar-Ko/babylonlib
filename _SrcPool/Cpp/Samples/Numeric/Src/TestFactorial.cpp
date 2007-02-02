/*$Workfile: TestFactorial.cpp$: implementation file
  $Revision: 1$ $Date: 2005-06-01 16:15:02$
  $Author: Darko Kolakovic$

  Test Test factorial calculation
  Copyright: CommonSoft Inc.
  2005-05-22 Darko Kolakovic
*/
// Group=Examples

#include "stdafx.h"
#include "KTrace.h"        //ASSERT macro
#include "STL/KBoolStream.h"
#ifndef KSTL_IO
  #include "STL/KOStream.h"
#endif

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(const int& iValue);
extern bool TsWriteToViewLn(const int& iValue);

unsigned int factorial(unsigned char nValue);
double factorial(unsigned int nValue);

bool TestFactorial();


//------------------------------------------------------------------------------
/*Test factorial calculation.

  Returns: true if successful, otherwise returns false.
 */
bool TestFactorial()
{
TsWriteToViewLn(_T("TestFactorial()"));
TESTENTRY logEntry =
  {_T("factorial(unsigned char)"), _T("KMatFact.cpp"), false};

bool bRes = true;
unsigned int nValue;
switch (sizeof(int))
  {
  case 2:  nValue =  8; break; //Int16
  case 4:  nValue = 12; break; //Int32
  case 8:  nValue = 20; break; //Int64
  default: nValue = 12; break; //Int32
  }

double dFactorial;
unsigned int i = 0;
while (( i <= nValue ) && bRes)
  {
  dFactorial = factorial(i);
  unsigned long nFactorial = factorial(byte(i));
  bRes = (dFactorial == (double)nFactorial);
  std::_tcout << i << _T("!") << _T(" = ")
              << nFactorial << _T(";") << std::endl;
  i++;
  }

double dResult = dFactorial;
nValue = 33;
while (( i <= nValue ) && bRes)
  {
  dResult *= i;
  dFactorial = factorial(i);
  
  bRes = ((dFactorial/dResult) <= (1.0 + 1.0e-9) && 
          (dFactorial/dResult) >= (1.0 - 1.0e-9)    );
  std::_tcout << i << _T("!") << _T(" = ")
              << dFactorial << _T(";") << std::endl;
  i++;
  }
  //Write test log
logEntry.m_bResult = bRes;
LogTest(&logEntry);

TsWriteToView(LOG_EOT);
TsWriteToView(_T("\r\n"));
return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2005-06-01 16:15:02  Darko Kolakovic 
 * $
 *****************************************************************************/
