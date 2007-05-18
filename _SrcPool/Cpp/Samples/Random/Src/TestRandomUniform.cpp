/*$Workfile: TestRandomUniform.cpp$: implementation file
  $Revision: 7$ $Date: 2007-05-18 12:59:11$
  $Author: Darko Kolakovic$

  Test uniform random number generator
  Mar 2k2  A. Janicijevic
*/

// Group=Examples

#include "stdafx.h"
#include <math.h> //sqrt()

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(const int& iValue);
extern bool TsWriteToViewLn(const int& iValue);

//TestRandomUniform()----------------------------------------------------------
#include "KRandomUniform.h" //CRandomUniform class
/*Test of uniform random number generator.

  Use seads 1802 and 9373 to test the random number generator.
  If the random number generator is working properly, then random numbers from
  20000 to 20006 should be:

           6533892.0  14220222.0  7275067.0
           6172232.0  8354498.0   10633180.0

  Returns: true if successful, otherwise returns false.
 */
bool TestRandomUniform()
{
TsWriteToViewLn(_T("TestRandomUniform()"));
TESTENTRY logEntry =
  {_T("CRandomUniform::CRandomUniform(uint16, uint16)"), _T("KRandomUniform.cpp"), false};

bool bRes = true;

CRandomUniform clRandomNo (1802, 9373);
double dRange[2] = {1e32, -1e32};
const int MIN = 0, MAX = 1;
double dResult;

double dSum  = 0.;
double dSum2 = 0.;

//Generate 20000 random numbers
const int NO_COUNT = 20000;
for(int i = 0; i < NO_COUNT; i++)
  {
  dResult = clRandomNo.Get();

    //Check range
  if (dResult < dRange[MIN])
    dRange[MIN] = dResult;
  if (dResult > dRange[MAX])
    dRange[MAX] = dResult;
  dSum += dResult;
  dSum2 += (dResult*dResult);
  }
std::_tcout << "Range (" << dRange[MIN]<< ',' << dRange[MAX] << ')' << std::endl;
std::_tcout << "Mean: " << dSum/NO_COUNT << std::endl;
std::_tcout << "Standard deviation: "
            << sqrt((dSum2 - dSum*dSum/NO_COUNT)/NO_COUNT) << std::endl;
if ( (dRange[MIN] >= 0.) && (dRange[MAX] < 1.) )
  {
  //Validate from 20000th to 20006th number
  unsigned long nTestArray[6] =
    {6533892, 14220222, 7275067, 6172232, 8354498, 10633180};

  for(i = NO_COUNT; (NO_COUNT == 20000 && i < NO_COUNT+6); i++)
    {
    dResult = clRandomNo.Get();
    dResult *= 4096.*4096.;
    std::_tcout << i << ": ";
    std::_tcout << std::setw(12) 
         << std::setiosflags(std::ios::fixed) << std::setprecision(0)
         << dResult  << std::setprecision (6) << std::endl;
    if (nTestArray[i-20000] != (unsigned long) dResult)
      {
      bRes = false;
      break;
      }
    }
  }
else
  bRes = false;

  //Write test log
logEntry.m_bResult = bRes;
LogTest(&logEntry);

TsWriteToViewLn(LOG_EOT);
return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log:
 * 6    Biblioteka1.5         2002-07-16 01:41:49  Darko           Fixed VSS Log
 *      tag
 * 5    Biblioteka1.4         2002-04-03 16:31:42  Darko Kolakovic Added stdev and
 *      mean results
 * 4    Biblioteka1.3         2002-04-02 19:29:31  Darko Kolakovic Updated test
 *      cases
 * 3    Biblioteka1.2         2002-04-02 19:06:34  Darko Kolakovic
 * 2    Biblioteka1.1         2002-03-14 22:51:11  Darko
 * 1    Biblioteka1.0         2002-03-14 18:56:23  Aleksandar Janicijevic
 *$
 *****************************************************************************/
