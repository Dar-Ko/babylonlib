/*$Workfile: TestRandomNo.cpp$: implementation file
  $Revision: 2$ $Date: 7/16/02 1:41:46 AM$
  $Author: Darko$

  Test rand() random number generator
  Mar 2k2 D. Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#include <iostream>
#include <iomanip.h>

//TestRandomNo()---------------------------------------------------------------
#include <Limits.h>	  //UINT_MAX
#include <stdlib.h>   //srand() and rand()
#include "KRandom.h"  //CRandomNo class
/*Test of random number generator (standard library)
 */
void TestRandomNo()
{
cout << "TestRandomNo()" << endl;
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
 * 2    Biblioteka1.1         7/16/02 1:41:46 AM   Darko           Fixed VSS Log 
 *      tag
 * 1    Biblioteka1.0         3/14/02 4:44:41 PM   Darko Kolakovic 
 *$
 *****************************************************************************/
