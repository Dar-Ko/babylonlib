/*$Workfile: TestWinService.cpp$: implementation file
  $Revision: 3$ $Date: 2007-02-09 18:49:07$
  $Author: Darko Kolakovic$

  Test creating a Windows Service
  Copyright: CommonSoft Inc.
  2007-02-06 Darko Kolakovic
*/
// Group=Examples

#include "stdafx.h"
//#include "KTrace.h"        //ASSERT macro
//#include "KTypedef.h"      //DWORD typedef
#include "KWinService.h"   //CWinService class

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(const int& iValue);
extern bool TsWriteToViewLn(const int& iValue);

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif


//-----------------------------------------------------------------------------
/*Test creating a Windows Service.

  Returns: true if successful, otherwise returns false.

  Note: Microsoft Windows specific (Win32).
 */
bool TestWinService()
{
TsWriteToViewLn(_T("TestWinService()"));
bool bRes = true;
TESTENTRY logEntry = 
  {_T("CWinService::CWinService()"), _T("KWinService.cpp"), false};

try
  {

  CWinService testService;
    //Write test log
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CWinService::Create(LPCTSTR)");
  bRes = testService.Create(_T("A Service with the name more than 256 characters long requires a lot of typing and editing. Such names are not very useful in the practice, because of limited space the user have on the screen and therefore should be avoided and replaced with more concise names."));
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  //Test reversing double
  if(bRes)
    {
    logEntry.m_szObjectName = _T("CWinService::Run()");

      //Write test log
    logEntry.m_bResult = bRes;
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
/******************************************************************************
 * $Log: 
 *  3    Biblioteka1.2         2007-02-09 18:49:07  Darko Kolakovic Create()
 *  2    Biblioteka1.1         2007-02-08 15:50:12  Darko Kolakovic tCrtDbgReport()
 *  1    Biblioteka1.0         2007-02-06 18:06:37  Darko Kolakovic 
 * $
 *****************************************************************************/
