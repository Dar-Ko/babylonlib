/*$Workfile: TestRandomCongr.cpp$: implementation file
  $Revision: 3$ $Date: 16/07/2002 1:41:40 AM$
  $Author: Darko$

  Test congruential random number generator
  Copyright: CommonSoft Inc
  Mar 2k2 D. Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#include <iostream>
#include <iomanip.h>

//TestRandomCongr()---------------------------------------------------------------
#include "KRandomCongr.h"  //CRandomCongr class
/*Test of congruential random number generator
 */
void TestRandomCongr()
{
cout << "TestRandomCongr()" << endl;

const unsigned long TheSeed = 1701UL;
unsigned int nLimes = 15000;
CRandomCongr RandNo1; //uses current time as a seed
CRandomCongr RandNo2(TheSeed);
CRandomCongr RandNo3;
RandNo3.SetSeed(1);

int i = 0;
while ( i < 10)
  {
  cout << setw(6) << '\t' << RandNo1(nLimes); 
  cout << setw(6) << '\t' << RandNo2.Get(nLimes);
  cout << setw(6) << '\t' << RandNo3(nLimes);
  cout << endl;
  i++;
  }

cout << "============================" << endl;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: 
 * 3    Biblioteka1.2         16/07/2002 1:41:40 AMDarko           Fixed VSS Log 
 *      tag
 * 2    Biblioteka1.1         18/03/2002 5:34:30 PMDarko Kolakovic Updated
 *      comments
 * 1    Biblioteka1.0         14/03/2002 4:44:31 PMDarko Kolakovic 
 *$
 *****************************************************************************/
