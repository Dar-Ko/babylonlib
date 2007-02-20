/*$Workfile: TestDumpButtonStyle.cpp$: implementation file
  $Revision: 5$ $Date: 2005-04-26 12:00:57$
  $Author: Darko Kolakovic$

  Implementation file
  Copyright: CommonSoft Inc.
  2007-01-25 Darko Kolakovic
 */

// Group=Examples Windows

#include "stdafx.h"
#include "Resource.h"
#include "KTestLog.h"
#include "KHresult.h" //CHresult class

#ifdef _DEBUG
  #define new DEBUG_NEW
#endif

bool TestCHresult();

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
/*Testing exceptions based on HRESULT.

  Returns: true if successful, otherwise returns false.

  Note: Microsoft Windows specific (Win32).

  See also: AtlThrow()
 */
bool TestCHresult()
{
TRACE(_T("TestCHresult()\n"));
TsWriteToViewLn(_T("TestCHresult()"));
bool bRes = true;
TESTENTRY logEntry =
  {_T("CHresult::CHresult()"), _T("KHresult.h"), false};
TCHAR szReport[255]; //error message

try
  {
  CHresult hrLasterror; //Get the last Win32 error. Expected success code.
  _stprintf(szReport,_T("GetLasteError returned HRESULT = %i"),(HRESULT)hrLasterror);
  TsWriteToViewLn(szReport);
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  //Test bool conversion
  logEntry.m_szObjectName = _T("CHresult::&operator= (const bool)");
  hrLasterror = bRes;
  _stprintf(szReport,_T("%s returned HRESULT = %i"),
                     (bRes ? _T("true"):_T("false")),(HRESULT)hrLasterror);
  TsWriteToViewLn(szReport);
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  //Test HRESULT conversion
  logEntry.m_szObjectName = _T("CHresult::&operator= (const HRESULT=S_OK)");
  hrLasterror = S_OK;
  _stprintf(szReport,_T("S_OK = %i"),(HRESULT)hrLasterror);
  TsWriteToViewLn(szReport);
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);


  //Test error results
  if(bRes)
    {
    try
      {
      logEntry.m_szObjectName = _T("CHresult::CHresult(HRESULT = E_UNEXPECTED)");
      CHresult hrError(E_UNEXPECTED); //Throw exception
      //Write test log
      logEntry.m_bResult = bRes = false;
      }
    catch(...)
      {
      logEntry.m_bResult = bRes; //Correct action
      _stprintf(szReport,_T("E_UNEXPECTED = %i"),(HRESULT)hrLasterror);
      TsWriteToViewLn(szReport);
      }
    LogTest(&logEntry);
    }
  }
catch(...)
  {
  bRes = false;
  //Write test log
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);
  }
TsWriteToView(LOG_EOT);
TsWriteToView(_T("\r\n"));
return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: $
 *****************************************************************************/
