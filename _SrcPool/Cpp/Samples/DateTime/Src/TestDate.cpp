/*$Workfile: S:\_SrcPool\Cpp\Samples\DateTime\Src\TestDate.cpp$: implementation file
  $Revision: 5$ $Date: 2004-10-06 23:43:10$
  $Author: Darko$

  Test Date conversions
  Copyright: CommonSoft Inc.
  2003-09-23 Darko Kolakovic
*/

// Group=Examples

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#include "KTChar.h"    //TCHAR typedef
#include "KTypedef.h"  //LPCTSTR typedef
#include "KTrace.h"    //ASSERT macro
#include "KTestLog.h"  //TESTENTRY struct
#include "KDate.h"     //CDate class

extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(LPCTSTR lszText);

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------
/*Function validates date handling.

  Returns: true if successful, otherwise returns false.
 */
bool TestDate()
{
TsWriteToViewLn(_T("TestDate()"));
bool bRes = true;
TESTENTRY logEntry = 
  {_T("CDate()"), _T("KDate.h"), bRes};
LogTest(&logEntry);

const int BUFF_SIZE = 64;
TCHAR szDate[BUFF_SIZE];

  //Test initialization
CDate dateA;  //calendar date
date dateB;   //DOS date
  //Set date 2003-06-07
dateB.da_year = 23;
dateB.da_day = 7;
dateB.da_mon = 6;
dateA = dateB; //copy DOS date
tm dateC = dateA; //Unix date

bRes = ( (dateC.tm_year == dateB.da_year + YEAR_EPOCH_DOS - YEAR_EPOCH_TM) && 
         (dateC.tm_mon  == dateB.da_mon -1) && 
         (dateC.tm_mday == dateB.da_day)    );

logEntry.m_bResult = bRes;
LogTest(&logEntry);

  //Test writing ISO 8601 basic format YYYYMMDD
TsWriteToViewLn(_T("Test output ISO 8601 basic format"));
if(bRes)
  {
  logEntry.m_szObjectName = _T("CDate::toString()");
  dateA.toString((LPTSTR)szDate);
  TsWriteToView(_T("ISO 8601: "));
  TsWriteToViewLn(szDate);
  bRes = (_tcscmp(szDate, _T("20030607")) == 0);
  }

logEntry.m_bResult = bRes;
LogTest(&logEntry);

  //Test reading ISO 8601 basic format YYYYMMDD
TsWriteToViewLn(_T("Test ISO 8601 basic format YYYYMMDD"));
if(bRes)
  {
  logEntry.m_szObjectName = _T("CDate::CDate(LPCTSTR)");
  CDate dateRead(szDate);
  bRes = (( (dateRead.GetYear()) == (dateB.da_year + YEAR_EPOCH_DOS) ) && 
            (dateRead.da_mon == dateB.da_mon) &&
            (dateRead.da_day == dateB.da_day)    );
  }

logEntry.m_bResult = bRes;
LogTest(&logEntry);

  //Test reading ISO 8601 extended format YYYY-MM-DD
TsWriteToViewLn(_T("Test ISO 8601 extended format YYYY-MM-DD"));
if(bRes)
  {
  logEntry.m_szObjectName = _T("CDate::operator=(LPCTSTR)");
  LPCTSTR strDate = _T("1964-11-23T16:30");
  TsWriteToView(_T("extended format: "));
  TsWriteToViewLn(strDate);
    //Set DOS date
  dateA = strDate;

  TsWriteToView(_T("ISO 8601: "));
  TsWriteToViewLn(dateA.toString((LPTSTR)szDate));

  bRes = (  (dateA.GetYear() == 1964 ) && 
            (dateA.da_mon == 11)       &&
            (dateA.da_day == 23)         );
  }

logEntry.m_bResult = bRes;
LogTest(&logEntry);

TsWriteToViewLn(LOG_EOT);

return bRes;
}

/*****************************************************************************
 * $Log: 
 *  5    Biblioteka1.4         2004-10-06 23:43:10  Darko           Unicode fixes
 *  4    Biblioteka1.3         2004-06-01 18:14:16  Darko           StdAfx changed
 *       to stdafx
 *  3    Biblioteka1.2         2003-09-30 09:14:24  Darko           Test reading
 *       ISO 8601
 *  2    Biblioteka1.1         2003-09-25 01:25:19  Darko           ISO 8601
 *  1    Biblioteka1.0         2003-09-24 18:42:12  Darko           
 * $
 *****************************************************************************/
