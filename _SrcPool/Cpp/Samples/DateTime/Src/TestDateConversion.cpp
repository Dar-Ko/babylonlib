/*$Workfile: TestDateConversion.cpp$: implementation file
  $Revision: 11$ $Date: 2004-10-08 12:33:23$
  $Author: Darko$

  Test Date conversions
  Copyright: CommonSoft Inc.
  2003-09-20 Darko Kolakovic
*/

// Group=Examples

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#include "KTChar.h"    //TCHAR typedef
#include "KTypedef.h"  //LPCTSTR typedef
#include "KTrace.h"    //ASSERT macro
#include "STL/KOStream.h"    //ostream template
#ifdef _WIN32
  #pragma warning (disable: 4127)
  #include "../../../Win/32/KDateTime.h" //CDateTime class
#endif
#include "STL/KBoolStream.h" //tbool class
#include "KTestLog.h"  //TESTENTRY struct
#ifndef _STL
  //Include STL stream tostream& operator<< (tostream&,tm const&);
  #define _STL
#endif
#include "KTmConv.h"   //CTm class

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToViewLn(const tm& tmDate);
extern bool TsWriteToViewLn(const double& dValue);
extern bool TsWriteToView(const double& dValue);

time_t TestMkTime(struct tm* tm);
extern "C" LPCTSTR g_szMonthAbr[];

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------
/*Function validates date conversions.

  Note: Microsoft Windows specific (Win32).

  Returns: true if successful, otherwise returns false.
 */
bool TestDateConversion()
{
TsWriteToView(_T("TestDateConversion()\r\n"));
bool bRes= true;
TESTENTRY logEntry =
  {_T("CDateTime()"), _T("KDateTime.h"), bRes};
  //Class uses Win32 system calls
#ifdef _WIN32
    //Test conversion from and to double
  TsWriteToViewLn(_T("Test conversion from and to double"));
  CDateTime dateA((double)-0.25);
  double dValue = dateA;
  bRes = ((dValue - 1.5) == dateA.m_dateValue); //Normalized negative value
  CDateTime dateC;
  if(bRes)
    {
      //Test invalid range
    dValue = 20031215.88;
    dateC = dValue;
    bRes = (dValue == (double)dateC.m_dateValue);
    }

    //Test converision from and to DATE (sinonim for double!)
  if(bRes)
    {
    DATE dtValue = -1500.78;
    CDateTime dateTest(dtValue); //Normalizing from -1500.78 to -1501.22
    dtValue = dateTest;
    bRes = (dtValue == -1500.78);
    TsWriteToView(_T("converision from and to DATE "));
    TsWriteToViewLn(dtValue);
    }

  //Test conversion from and to tm
  TsWriteToViewLn(_T("Test conversion from and to tm"));
  if (bRes)
    {
      //Test invalid range
    tm tmTime = dateC;
    TsWriteToView(_T("invalid date "));
    TsWriteToViewLn(tmTime);
    bRes  = ((tmTime.tm_hour == -1) && (tmTime.tm_mon == -1));

    if (bRes)
      {
        //-205121.66 = 1338-05-24T08:03:42
      dateA = -205120.6641;
      tmTime = dateA;
      bRes  = ((tmTime.tm_year == 1338 - YEAR_EPOCH_TM) &&
              (tmTime.tm_mon  == 5 -1)  &&
              (tmTime.tm_mday == 24)    &&
              (tmTime.tm_hour == 8)     &&
              (tmTime.tm_min  == 3)         );
      TsWriteToView(dateA);
      TsWriteToView(_T(" = "));
      TsWriteToViewLn(tmTime);
      }
    }
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

    //Test date boundaries
  TsWriteToViewLn(_T("Test date boundaries"));
  logEntry.m_szObjectName = _T("CDateTime::IsValid()");
  if(bRes)
    {
    dateA.m_dateValue = CDateTime::DATE_MIN;
    bRes = dateA.IsValid();
    tm tmTemp = dateA;
    std::_tcout << tmTemp << _T(": ")
                << dateA.m_dateValue  << _T(" -> ")
                << (tbool)bRes << std::endl;
    if(bRes)
      {
      dateA.m_dateValue = CDateTime::DATE_MAX;
      bRes = dateA.IsValid();
      tmTemp = dateA;
      std::_tcout << tmTemp << _T(": ")
                  << dateA.m_dateValue  << _T(" -> ")
                  << (tbool)bRes << std::endl;
      }
    if(bRes)
      {
      dateA.m_dateValue = CDateTime::DATE_ERROR;
      bRes = !dateA.IsValid();
      tmTemp = dateA;
      std::_tcout << tmTemp << _T(": ")
                  << dateA.m_dateValue  << _T(" -> ")
                  << !(tbool)bRes << std::endl;
      }
    }
logEntry.m_bResult = bRes;
LogTest(&logEntry);

    //Test ISO 8601:2000 string parsing
  TsWriteToViewLn(_T("Test ISO 8601:2000 string parsing"));
  logEntry.m_szObjectName = _T("CDateTime::SetDate(LPTCTSTR)");
  if(bRes)
    {
    const int TESTCOUNT = 8;
    struct tagTestSetDate
    {
      LPCTSTR m_szSource; //string to parse
      DATE    m_dResult;  //expected result
    } Test[TESTCOUNT] =
      {
        //YYYYMMDDThhmmss     <-  expected formats
        //YYYY_MM_DD_hh_mm_ss
      _T("  Garbage"),               CDateTime::DATE_ERROR,  // 0
      _T("\t  +100"),                -20.0,  // 1 YYYY = "\t  +";
                                             //after delimiter skip:
                                             //MM= "  " DD= "10"
      _T("-100"),                    CDateTime::DATE_ERROR, // 2
      _T("+0  "),                                   -30.0,  // 3
      _T("-214013083648"),           CDateTime::DATE_ERROR, //4 out of range
      _T("2147483647"),              CDateTime::DATE_ERROR, //5 not valid month
      _T("19641123 145055"),                        23704.0,// 6
      _T("2003-09-25T13:30:45Z300"),                37889.0 // 7
      };

    //TODO: Fix CDateTime::SetDate(LPCTSR) to parse time (hhmmss) D.K.
    //TODO: Add test cases for  time (hhmmss) D.K.

    /*Expected output:
        0.   Garbage   -> 2147483647.0: 1899-00--1T-1:-1:-1
        1.        +100 -> -20.0: 1899-12-10T00:00:00
        2. -100        -> -20.0: 1899-12-10T00:00:00
        3. +0          -> -30.0: 1899-11-30T00:00:00
        4. -2147483648 -> 2147483647.0: 1899-00--1T-1:-1:-1
        5. 2147483647  -> 2147483647.0: 1899-00--1T-1:-1:-1
        6. 19641123 145055         -> 23704.0: 1964-11-23T00:00:00
        7. 2003-09-25T13:30:45Z300 -> 37889.0: 2003-09-25T00:00:00
     */
    int i = 0;
    tm tmTemp;
    while((i < TESTCOUNT) && bRes)
      {
      std::_tcout << i << _T(". ") << Test[i].m_szSource;
      dateA  = Test[i].m_szSource;
      std::_tcout << _T(" -> ") << dateA.m_dateValue;
      tmTemp = dateA;
      std::_tcout << _T(": ") << tmTemp << std::endl;
      bRes = (dateA.m_dateValue == Test[i].m_dResult);
      i++;
      }
    }

#endif //_WIN32

logEntry.m_bResult = bRes;
LogTest(&logEntry);

TsWriteToView(LOG_EOT);
TsWriteToView(_T("\r\n"));

return bRes;
}

//-----------------------------------------------------------------------------
/*Function validates tm structure conversions.

  Returns: true if successful, otherwise returns false.
 */
bool TestTmConversion()
{
TsWriteToView(_T("TestTmConversion()\r\n"));
TESTENTRY logEntry;
bool& bRes = logEntry.m_bResult;
bRes = true;
logEntry.m_szFileName   = _T("KTmConv.h");
logEntry.m_szObjectName = _T("CTm()");

CTm dateA((time_t)-0.25); //Takes only integer part (0)
tm tmDate = dateA;
LogTest(&logEntry);
std::_tcout << tmDate << std::endl;
bRes = (!true); //Fixme!

  //Test getting local time
logEntry.m_szObjectName = _T("GetLocalTime()");
CTm dateB((time_t)0);
time_t timetDate;
if(bRes)
  {
    //Get current system time
  time_t secs_now = time(NULL);
  CTm n(*localtime(&secs_now));
  std::_tcout << (tm)n << std::endl;

  dateB.GetLocalTime();
  dateB.IsValid();
  timetDate = dateB;
  #ifdef _USE_TIME_64
    __time64_t time64tDate = dateB;
  #endif
  bRes = (!true); //Fixme!
  }

  //Test output to the stream
logEntry.m_szObjectName = _T("operator<<()");
if(bRes)
  {
  std::_tcout << (tm)dateB << std::endl;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CTm::GmTime()");
  std::_tcout << _T("UTC ") << dateB.GmTime() << _T(" [s]") << std::endl;
  timetDate = TestMkTime(&dateB);
  std::_tcout << _T("UTC ") << timetDate << _T(" [s]") << std::endl;

  dateB.tm_mon = eFebruary;
  std::_tcout << g_szMonthAbr[dateB.tm_mon] << _T(' ')
              << dateB.GmTime() << _T(" [s]") << std::endl;
  timetDate = TestMkTime(&dateB);
  std::_tcout << g_szMonthAbr[dateB.tm_mon] << _T(' ')
              << timetDate << _T(" [s]") << std::endl;
  bRes = (!true); //Fixme!
  }

LogTest(&logEntry);
TsWriteToViewLn(LOG_EOT);
return bRes;
}

//-----------------------------------------------------------------------------
/*This test helper function converts date and time to UTC time.

  Returns: UTC time is represented as seconds elapsed since 1970-01-01 00:00:00.

  History:  2000 Fabrice Bellard <1>
 */
time_t TestMkTime(struct tm* ptmDate //[in] date and time to convert
                  )
{
time_t timeRes;
int iYear = ptmDate->tm_year + 1900; //calendar year
int iMonth = ptmDate->tm_mon + 1;    //calendar month [1, 12]
int iDay = ptmDate->tm_mday;
if (iMonth < 3)
  {
  iMonth += 12;
  iYear--;
  }
timeRes = 86400 *
    (iDay + (153 * iMonth - 457) / 5 +
     365 * iYear + iYear / 4 - iYear / 100 + iYear / 400 - 719469);
timeRes += 3600 * ptmDate->tm_hour + 60 * ptmDate->tm_min + ptmDate->tm_sec;
return timeRes;
}

///////////////////////////////////////////////////////////////////////////////
/*<1>
  Various simple utilities for ffmpeg system
  Copyright (c) 2000, 2001, 2002 Fabrice Bellard

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*****************************************************************************
 * $Log:
 *  6    Biblioteka1.5         2004-06-01 18:14:18  Darko           StdAfx changed
 *       to stdafx
 *  5    Biblioteka1.4         2003-09-30 09:14:27  Darko           Test reading
 *       ISO 8601
 *  4    Biblioteka1.3         2003-09-28 01:43:24  Darko           warning C4127
 *  3    Biblioteka1.2         2003-09-27 12:18:23  Darko           Test CDateTime
 *       instead CDateConv
 *  2    Biblioteka1.1         2003-09-23 17:12:53  Darko           AtoI()
 *  1    Biblioteka1.0         2003-09-22 21:58:13  Darko
 * $
 *****************************************************************************/
