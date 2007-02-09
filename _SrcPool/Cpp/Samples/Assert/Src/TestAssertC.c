/*$Workfile: TestAssertC.c$: implementation file
  $Revision: 7$ $Date: 2007-02-09 18:48:42$
  $Author: Darko Kolakovic$

  Test validation of the assertion in C functions
  Copyright: CommonSoft Inc.
  2004-08-12 Darko Kolakovic
*/

/* Group=Examples                                                            */
#include "stdafx.h"

extern bool TsWriteToViewLn(LPCTSTR lszText);
bool TestAssertC();

/*---------------------------------------------------------------------------*/
/*Test assertion. An assertion statement specifies a condition that you expect
  to hold true at some particular point in your program. If that condition does
  not hold true, the assertion fails and execution of your program is
  interrupted.

  Returns true if test is successful; otherwise returns false.
 */
bool TestAssertC()
{
bool bResult = true;
TsWriteToViewLn(_T("TestAssertC()"));
//TESTENTRY logEntry = {_T(""), _T(""), false};

#ifdef _UNICODE
  #ifdef _DEBUG
    TsWriteToViewLn(_T("Write a message to the debugger"));
    //logEntry.m_szFileName = _T("KDbgRpt.cpp");
    //logEntry.m_szObjectName = _T("tCrtDbgReport(_CRT_WARN)");
    bResult = (tCrtDbgReport( _CRT_WARN, __TFILE__, __LINE__, _T("TestAssertC()"),
              _T("Test Unicode message with %s\n"), _T("tCrtDbgReport()")) > 0);
    //logEntry.m_bResult = bResult;
    //LogTest(&logEntry);
  #endif
#else //SBCS
  #ifdef _DEBUG
    TsWriteToViewLn(_T("Write a message to the debugger"));
    //logEntry.m_szFileName = _T("crt/src/dbgrpt.c"); //Microsoft CRT
    //logEntry.m_szObjectName = _T("_CrtDbgReport(_CRT_WARN)");
    bResult = (_CrtDbgReport( _CRT_WARN, __TFILE__, __LINE__, _T("TestAssertC()"),
              _T("Test SBCS message with %s\n"), _T("_CrtDbgReport()")) > 0);
    //logEntry.m_bResult = bResult;
    //LogTest(&logEntry);
  #endif
#endif


TsWriteToViewLn(LOG_EOT);

return bResult;
}

/* ////////////////////////////////////////////////////////////////////////// */
/******************************************************************************
 * $Log:
 *  5    Biblioteka1.4         2004-11-09 19:46:06  Darko Kolakovic implemented
 *       TsWriteToViewLn
 *  4    Biblioteka1.3         2004-10-22 12:46:45  Darko Kolakovic CodeWarrior
 *  3    Biblioteka1.2         2004-09-13 15:28:44  Darko           comments
 *  2    Biblioteka1.1         2004-08-31 13:07:52  Darko           Removed
 *       KDbgMacr.h
 *  1    Biblioteka1.0         2004-08-26 13:18:33  Darko
 * $
 *****************************************************************************/
