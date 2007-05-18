/*$Workfile: TestRandomNo.cpp$: implementation file
  $Revision: 3$ $Date: 2007-05-18 12:59:10$
  $Author: Darko Kolakovic$

  Test rand() random number generator
  Mar 2k2 D. Kolakovic
*/

// Group=Examples

#include "stdafx.h"

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(const int& iValue);
extern bool TsWriteToViewLn(const int& iValue);

//TestRandomNo()---------------------------------------------------------------
#include <Limits.h>   //UINT_MAX
#include <stdlib.h>   //srand() and rand()
#include "KRandom.h"  //CRandomNo class
/*Test of random number generator (standard library)

  Returns: true if successful, otherwise returns false.
 */
bool TestRandomNo()
{
TsWriteToViewLn(_T("TestRandomNo()"));
TESTENTRY logEntry =
  {_T("CRandomNo::CRandomNo()"), _T("KRandom.h"), false};
bool bRes = true;

const unsigned long TheSeed = 1701UL;
unsigned int nLimes = 15000;
CRandomNo RandNo1;
RandNo1.SetSeed(); //Uses current time as a seed
CRandomNo RandNo2(TheSeed);
CRandomNo RandNo3;
RandNo3.SetSeed(1);

int i = 0;
while ( i < 10)
  {
  std::_tcout << std::setw(6) << _T('\t') << RandNo1(nLimes);
  std::_tcout << std::setw(6) << _T('\t') << RandNo2.Get(nLimes);
  std::_tcout << std::setw(6) << _T('\t') << RandNo3(nLimes);
  std::_tcout << std::endl;
  i++;
  }

  //Write test log
logEntry.m_bResult = bRes;
LogTest(&logEntry);

TsWriteToViewLn(LOG_EOT);
return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log:
 * 2    Biblioteka1.1         2002-07-16 01:41:46  Darko           Fixed VSS Log
 *      tag
 * 1    Biblioteka1.0         2002-03-14 16:44:41  Darko Kolakovic
 *$
 *****************************************************************************/
