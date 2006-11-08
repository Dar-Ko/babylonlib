/*$Workfile: TestFibonnaci.cpp$: implementation file
  $Revision: 1$ $Date: 2005-01-21 15:43:07$
  $Author: Darko Kolakovic$

  Test Fibonnaci number generator
  Copyright: CommonSoft Inc.
  2005-01-21 DarkoKolakovic
*/

// Group=Examples

#include "stdafx.h"

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(const int& iValue);
extern bool TsWriteToViewLn(const double& iValue);

extern double funcFibonnaci(unsigned int nValue);

 //Fibonnaci Table
unsigned long g_tblFibonnaci[] =
{
           0,         1,         1,         2,         3,
           5,         8,        13,        21,        34,
          55,        89,       144,       233,       377,
         610,       987,      1597,      2584,      4181,
        6765,     10946,     17711,     28657,     46368,
       75025,    121393,    196418,    317811,    514229,
      832040,   1346269,   2178309,   3524578,   5702887,
     9227465,  14930352,  24157817,  39088169

};

//-----------------------------------------------------------------------------
/*Test generation of the Fibonnaci numbers.

  Returns: true if test is successful; otherwise returns false.
 */
bool TestFibonnaci()
{
TsWriteToViewLn(_T("TestFibonnaci()"));

bool bResult = true;

TESTENTRY logEntry =
  {_T("funcFibonnaci()"), _T("KfFibonacci.cpp"), false};

int i = 0;
   /*number of elements in the control array*/
int j = sizeof(g_tblFibonnaci)/sizeof(unsigned long);
if (sizeof(unsigned long) == 2) //16-bit integer
    j = 25; //integer overflow for n > 25 ( F(25) <= 0xFFFF)

double dFibonnaci;

while( (i < j) &&  bResult)
  {
  dFibonnaci = funcFibonnaci(i);

  TsWriteToView(_T("F("));
  TsWriteToView(i);
  TsWriteToView(_T(") = "));
  TsWriteToViewLn(dFibonnaci);

  bResult = (g_tblFibonnaci[i] == (unsigned long)dFibonnaci);
  i++;
  }

  //Write to test log
logEntry.m_bResult = bResult;
LogTest(&logEntry);

TsWriteToViewLn(LOG_EOT);
return bResult;
}

///////////////////////////////////////////////////////////////////////////////
