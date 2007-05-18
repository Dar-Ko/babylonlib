/*$Workfile: TestRandomCongr.cpp$: implementation file
  $Revision: 4$ $Date: 2007-05-18 12:59:09$
  $Author: Darko Kolakovic$

  Test congruential random number generator
  Copyright: CommonSoft Inc
  Mar 2k2 D. Kolakovic
*/

// Group=Examples

#include "stdafx.h"

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(const int& iValue);
extern bool TsWriteToViewLn(const int& iValue);

//TestRandomCongr()---------------------------------------------------------------
#include "KRandomCongr.h"  //CRandomCongr class
/*Test of congruential random number generator

  Returns: true if successful, otherwise returns false.
 */
bool TestRandomCongr()
{
TsWriteToViewLn(_T("TestRandomCongr()"));
TESTENTRY logEntry =
  {_T("CRandomCongr::CRandomCongr()"), _T("KRandomCongr.h"), false};
bool bRes = true;

const unsigned long TheSeed = 1701UL;
unsigned int nLimes = 15000;
CRandomCongr RandNo1; //uses current time as a seed
CRandomCongr RandNo2(TheSeed);
CRandomCongr RandNo3;
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
 * 3    Biblioteka1.2         2002-07-16 01:41:40  Darko           Fixed VSS Log
 *      tag
 * 2    Biblioteka1.1         2002-03-18 17:34:30  Darko Kolakovic Updated
 *      comments
 * 1    Biblioteka1.0         2002-03-14 16:44:31  Darko Kolakovic
 *$
 *****************************************************************************/
