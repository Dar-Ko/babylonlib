/*$Workfile: S:\_SrcPool\Cpp\Samples\StlTools\Src\TestStl.cpp$: implementation file
  $Revision: 1$ $Date: 2007-07-16 17:51:50$
  $Author: Darko Kolakovic$

  Test some STL constants
  Copyright: CommonSoft Inc.
  2007-07-10 Darko Kolakovic
*/

// Group=Examples
#include "stdstl.h"

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(const int& iValue);
extern bool TsWriteToViewLn(const int& iValue);

extern "C" LPCTSTR g_szText[]; //test cases

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------
/*Dumps certain Standard Template Library constants.

  Returns: true if successful, otherwise returns false.
 */
bool TestStlLimits()
{
TsWriteToViewLn(_T("TestStlLimits()"));

  //Test object creation
TESTENTRY logEntry =
  {_T("DumpLimits()"), _T("KDbgLimits.cpp"), false};

extern void DumpLimits();

bool bRes = true;
DumpLimits();

  //Write test log
logEntry.m_bResult = bRes;
LogTest(&logEntry);


TsWriteToViewLn(LOG_EOT);
return bRes;
}

//-----------------------------------------------------------------------------
/*Test handling strings with null characters.

  Returns: true if successful, otherwise returns false.
  
  Note: uses Standard Template Library (STL).
*/
bool TestNullChar() 
{
TsWriteToViewLn(_T("TestNullChar()"));

  //Test object creation
TESTENTRY logEntry =
  {_T("tstring::operator=(text\\0text\\0)"), _T("KTString.h"), false};
  
bool bRes = true;
LPCTSTR pszTestNull = _T("Null after this\001and after this.");

tstring strTest = pszTestNull;

//Output to the console
std::_tcout << pszTestNull << std::endl;

//Write test log
logEntry.m_bResult = bRes;
LogTest(&logEntry);


TsWriteToViewLn(LOG_EOT);
return bRes;
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2007-07-16 17:51:50  Darko Kolakovic 
 * $
 *****************************************************************************/
