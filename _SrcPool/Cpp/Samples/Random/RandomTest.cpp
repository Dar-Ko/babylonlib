/*$Workfile: RandomTest.cpp$: implementation file
  $Revision: 5$ $Date: 16/07/2002 12:41:37 AM$
  $Author: Darko$

  Test random number generators
  Mar 2k2 A. Janicijevic
*/

// Group=Examples

#include "stdafx.h"
#include <iostream>
#include <iomanip.h>

extern void TestRandomNo();
extern bool TestRandomUniform();
extern void TestRandomCongr();
extern void TestRandomGauss();

//using std::cout;
using std::endl;

//main()-----------------------------------------------------------------------
/*Defines the entry point for the console application.
 */
int main(int argc, char* argv[])
{
TestRandomNo();
TestRandomCongr();
if(!TestRandomUniform())
  return EXIT_FAILURE;
TestRandomGauss();

return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/****************************************************************************** 
 *$Log: 
 * 5    Biblioteka1.4         16/07/2002 12:41:37 AMDarko           Fixed VSS Log 
 *      tag
 * 4    Biblioteka1.3         03/04/2002 3:31:33 PMDarko Kolakovic Added stdev and
 *      mean results
 * 3    Biblioteka1.2         18/03/2002 4:33:45 PMDarko Kolakovic Added Gaussian
 *      Rand No
 * 2    Biblioteka1.1         14/03/2002 3:47:33 PMDarko Kolakovic Added srand()
 * 1    Biblioteka1.0         13/03/2002 7:26:21 PMAleksandar Janicijevic 
 *$
 *****************************************************************************/
