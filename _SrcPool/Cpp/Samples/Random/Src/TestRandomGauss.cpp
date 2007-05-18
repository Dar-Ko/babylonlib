/*$Workfile: TestRandomGauss.cpp$: implementation file
  $Revision: 6$ $Date: 2007-05-18 12:59:09$
  $Author: Darko Kolakovic$

  Test random number generator with Gauss distribution
  Copyright: CommonSoft Inc
  Mar 2k2  Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#include <math.h> //sqrt()

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(const int& iValue);
extern bool TsWriteToViewLn(const int& iValue);

//TestRandomGauss()------------------------------------------------------------
#include "KRandomGauss.h" //CRandomGauss class
/*Test Gauss distribution of random numbers.

  Returns: true if successful, otherwise returns false.
 */
bool TestRandomGauss()
{
TsWriteToViewLn(_T("TestRandomGauss()"));
TESTENTRY logEntry =
  {_T("CRandomGauss::CRandomGauss(double, double)"), _T("KRandomGauss.cpp"), false};
bool bRes = true;

CRandomGauss clRandomNo(1.0,0.5);
clRandomNo.SetSeed(1802,9373);
const int NO_COUNT = 100000;
double dSum = 0;
double dSum2 = 0;

for(int i = 0; i < NO_COUNT; i++)
  {
  double dResult = clRandomNo.Get();
  dSum += dResult;
  dSum2 += (dResult*dResult);
  }
std::_tcout << "Mean: " << dSum/NO_COUNT << std::endl;
std::_tcout << "Standard deviation: " <<
                sqrt((dSum2 - dSum*dSum/NO_COUNT)/NO_COUNT) << std::endl;

  //Write test log
logEntry.m_bResult = bRes;
LogTest(&logEntry);

TsWriteToViewLn(LOG_EOT);
return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log:
 * 5    Biblioteka1.4         2002-07-16 01:41:43  Darko           Fixed VSS Log
 *      tag
 * 4    Biblioteka1.3         2002-04-03 16:31:37  Darko Kolakovic Added stdev and
 *      mean results
 * 3    Biblioteka1.2         2002-04-02 19:29:26  Darko Kolakovic Updated test
 *      cases
 * 2    Biblioteka1.1         2002-04-02 19:06:30  Darko Kolakovic
 * 1    Biblioteka1.0         2002-03-18 17:32:20  Darko Kolakovic
 *$
 *****************************************************************************/
