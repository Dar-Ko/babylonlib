/*$Workfile: TestCommonNumeric.cpp$: implementation file
  $Revision: 9$ $Date: 2007-05-31 16:41:21$
  $Author: Darko Kolakovic$

  Test numerical and machine dependent routines.
  Copyright: CommonSoft Inc.
  July 2k1 D.Kolakovic
*/

// Group=Examples


#ifdef _MSC_VER     /*Microsoft Visual Studio C/C++ compiler                 */
  #ifndef _CONSOLE
    #error "define _CONSOLE macro in the project"
  #endif
#endif

#ifdef __GNUG__     /*GNU C++ compiler                                       */
  #ifndef _CONSOLE
    #warning "define _CONSOLE macro in the project"
  #endif
#endif

#include "stdafx.h"

extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TestNewtonRaphson();
extern bool TestByteSwap();
extern bool TestEndian();
extern bool TestNetByteOrder();
extern bool TestPrimes();
extern bool TestSwapRows();
extern bool TestRound();
extern bool TestFibonnaci();
extern bool TestSinglyLinkedList();
extern bool TestGcd();
extern bool TestFactorial();
extern bool TestLcm();
extern bool TestNaN();
extern bool TestPoint();
extern bool TestQuadraticEquation();
extern bool TestRealConversion();


//-----------------------------------------------------------------------------
/*Validate different numerical and machine dependent routines.

  Returns: EXIT_SUCCESS, which represents a value of 0, if succesful. Otherwise
  a non-zero error code is returned.
 */
int TestCommonNumeric()
{
TsWriteToViewLn(_T("Validation of different numerical methods"));
TsWriteToViewLn(_T(""));

PFUNC_TEST funcTest[] =
  {
  TestEndian,
  TestNaN,
  TestRealConversion,
  TestPoint,
  TestQuadraticEquation,
  TestGcd,
  TestLcm,
  TestFactorial,
  TestSinglyLinkedList,
  TestByteSwap,
  TestSwapRows,
  TestNetByteOrder,
  TestNewtonRaphson,
  TestPrimes,
  TestRound,
  TestFibonnaci
  };

int iTestCount = 0;
while (iTestCount < (sizeof(funcTest)/sizeof(PFUNC_TEST)) )
  {
  if ((funcTest[iTestCount] != NULL) && funcTest[iTestCount]())
    std::_tcout << LOG_SUCCESS << std::endl << std::endl;
  else
    {
    TsWriteToViewLn(LOG_FAILURE);
    return EXIT_FAILURE + 1 + iTestCount;
    }
  iTestCount++;
  }

return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2004-10-04 23:26:39  Darko
 * $
 *****************************************************************************/
