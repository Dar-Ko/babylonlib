/*$Workfile: H:\_SrcPool\Cpp\Samples\Random\RandomTest.cpp$: implementation file
  $Revision: 5$ $Date: 7/16/02 1:41:37 AM$
  $Author: Darko$

  Test random number generators
  Mar 2k2 A. Janicijevic
*/

// Group=Examples

#include "StdAfx.h"
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
 * 5    Biblioteka1.4         7/16/02 1:41:37 AM   Darko           Fixed VSS Log 
 *      tag
 * 4    Biblioteka1.3         4/3/02 4:31:33 PM    Darko Kolakovic Added stdev and
 *      mean results
 * 3    Biblioteka1.2         3/18/02 5:33:45 PM   Darko Kolakovic Added Gaussian
 *      Rand No
 * 2    Biblioteka1.1         3/14/02 4:47:33 PM   Darko Kolakovic Added srand()
 * 1    Biblioteka1.0         3/13/02 8:26:21 PM   Aleksandar Janicijevic 
 *$
 *****************************************************************************/
