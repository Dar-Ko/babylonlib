/*$Workfile: H:\_SrcPool\Cpp\Samples\Random\TestRandomUniform.cpp$: implementation file
  $Revision: 6$ $Date: 7/16/02 1:41:49 AM$
  $Author: Darko$

  Test uniform random number generator
  Mar 2k2  A. Janicijevic
*/

// Group=Examples

#include "stdafx.h"
#include <iostream>
#include <iomanip.h>
#include <math.h> //sqrt()

//TestRandomUniform()----------------------------------------------------------
#include "KRandomUniform.h" //CRandomUniform class
/*Test of uniform random number generator.

  Use seads 1802 and 9373 to test the random number generator. 
  If the random number generator is working properly, then random numbers from
  20000 to 20006 should be:

           6533892.0  14220222.0  7275067.0
           6172232.0  8354498.0   10633180.0

 */
bool TestRandomUniform()
{
cout << "TestRandomUniform()" << endl;
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
cout << "Range (" << dRange[MIN]<< ',' << dRange[MAX] << ')' << endl;
cout << "Mean: " << dSum/NO_COUNT << endl;
cout << "Standard deviation: " << sqrt((dSum2 - dSum*dSum/NO_COUNT)/NO_COUNT) << endl;
if ( (dRange[MIN] >= 0.) && (dRange[MAX] < 1.) )
  {
  //Validate from 20000th to 20006th number
  unsigned long nTestArray[6] = 
    {6533892, 14220222, 7275067, 6172232, 8354498, 10633180};
  
  for(i = NO_COUNT; (NO_COUNT == 20000 && i < NO_COUNT+6); i++)
    {
    dResult = clRandomNo.Get();
    dResult *= 4096.*4096.;
    cout << i << ": ";
    cout << setw(12) << setiosflags(ios::fixed) << setprecision(0)
         << dResult  << setprecision (6) << endl;
    if (nTestArray[i-20000] != (unsigned long) dResult)
      {
      bRes = false;
      break;
      }
    }
  }
else
  bRes = false;

if (bRes)
  cout << "============================" << endl;
else
  cout << "  Test failed!" << endl;

return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: 
 * 6    Biblioteka1.5         7/16/02 1:41:49 AM   Darko           Fixed VSS Log 
 *      tag
 * 5    Biblioteka1.4         4/3/02 4:31:42 PM    Darko Kolakovic Added stdev and
 *      mean results
 * 4    Biblioteka1.3         4/2/02 7:29:31 PM    Darko Kolakovic Updated test
 *      cases
 * 3    Biblioteka1.2         4/2/02 7:06:34 PM    Darko Kolakovic 
 * 2    Biblioteka1.1         3/14/02 10:51:11 PM  Darko           
 * 1    Biblioteka1.0         3/14/02 6:56:23 PM   Aleksandar Janicijevic 
 *$
 *****************************************************************************/
