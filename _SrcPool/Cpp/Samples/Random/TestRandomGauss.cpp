/*$Workfile: TestRandomGauss.cpp$: implementation file
  $Revision: 5$ $Date: 7/16/02 1:41:43 AM$
  $Author: Darko$

  Test random number generator with Gauss distribution
  Copyright: CommonSoft Inc
  Mar 2k2  Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#include <iostream>
#include <iomanip.h>
#include <math.h> //sqrt()

//TestRandomGauss()------------------------------------------------------------
#include "KRandomGauss.h" //CRandomGauss class
/*Test Gauss distribution of random numbers.
 */
void TestRandomGauss()
{
cout << "TestRandomGauss()" << endl;

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
cout << "Mean: " << dSum/NO_COUNT << endl;
cout << "Standard deviation: " << sqrt((dSum2 - dSum*dSum/NO_COUNT)/NO_COUNT) << endl;

cout << "============================" << endl;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: 
 * 5    Biblioteka1.4         7/16/02 1:41:43 AM   Darko           Fixed VSS Log 
 *      tag
 * 4    Biblioteka1.3         4/3/02 4:31:37 PM    Darko Kolakovic Added stdev and
 *      mean results
 * 3    Biblioteka1.2         4/2/02 7:29:26 PM    Darko Kolakovic Updated test
 *      cases
 * 2    Biblioteka1.1         4/2/02 7:06:30 PM    Darko Kolakovic 
 * 1    Biblioteka1.0         3/18/02 5:32:20 PM   Darko Kolakovic 
 *$
 *****************************************************************************/
