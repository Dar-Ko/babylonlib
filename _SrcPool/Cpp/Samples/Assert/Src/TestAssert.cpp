/*$Workfile: TestAssert.cpp$: implementation file
  $Revision: 4$ $Date: 2004-10-22 11:46:43$
  $Author: Darko Kolakovic$

  Test validation of the assertation
  Copyright: CommonSoft Inc.
  2004-08-12 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"


extern bool TsWriteToViewLn(LPCTSTR lszText);
bool TestAssert();

//-----------------------------------------------------------------------------
/*Test assertation. An assertion statement specifies a condition that you expect
  to hold true at some particular point in your program. If that condition does
  not hold true, the assertion fails and execution of your program is
  interrupted.

  Returns true if test is successful; otherwise returns false.
 */
bool TestAssert()
{
TsWriteToViewLn(_T("TestAssert()"));

bool bResult = true;


TsWriteToViewLn(LOG_EOT);

return bResult;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  4    Biblioteka1.3         2004-10-22 11:46:43  Darko Kolakovic CodeWarrior
 *  3    Biblioteka1.2         2004-09-28 12:59:18  Darko           comments
 *  2    Biblioteka1.1         2004-09-13 14:28:42  Darko           comments
 *  1    Biblioteka1.0         2004-08-23 16:58:05  Darko           
 * $
 *****************************************************************************/
