/*$Workfile: TestLeapYear.cpp$: implementation file
  $Revision: 10$ $Date: 2004-10-06 23:43:13$
  $Author: Darko$

  Test leap year validation
  Copyright: CommonSoft Inc.
  Jan. 2k2 Darko Kolakovic
*/

// Group=Examples

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#include "KTChar.h"    //TCHAR typedef
#include "KTypedef.h"  //LPCTSTR typedef
#include "KTrace.h"    //ASSERT macro
#include "KTime.h"     //IsLeapYear()
#include "KTestLog.h"  //TESTENTRY struct

extern bool TsWriteToView(LPCTSTR lszText);

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//TestLeapYear()------------------------------------------------------------
/*Function validates leap years.

  Returns: true if successful, otherwise returns false.
 */
bool TestLeapYear()
{
TsWriteToView(_T("TestLeapYear()\r\n"));
TESTENTRY logEntry = 
  {_T("IsLeapYear()"), _T("KTime.h"), false};

bool bRes = true;
const int TESTCOUNT = 19;
const int ID_HYSTORIC  = 0; //Id of Gregorian Calendar results
const int ID_PROLEPTIC = 1; //Id of Proleptic Gregorian Calendar results
int iYear[TESTCOUNT] = 
  {
  1996, //00
  1609, //01
  1500, //02
  4000, //03
  1800, //04
  9250, //05
  1900, //06
  2000, //07
  1388, //08
  1582, //09
  2002, //10
  2004, //11
   104, //12
    96, //13
     4, //14
    12, //15
  7866, //16
  -120, //17
     0  //18
  };
bool bLeapYear[TESTCOUNT][2] = 
  {
//Hist,  Proleptic
  true,  true, //00 1996,
  false, false,//01 1609,
  true,  false,//02 1500, < YEAR_GREGORIAN
  true,  true, //03 4000,
  false, false,//04 1800,
  false, false,//05 9250,
  false, false,//06 1900,
  true,  true, //07 2000,
  true,  true, //08 1388, < YEAR_GREGORIAN
  false, false,//09 1582, = YEAR_GREGORIAN
  false, false,//10 2002,
  true,  true, //11 2004,
  true,  true, //12  104,  < YEAR_GREGORIAN
  true,  true, //13   96,  < YEAR_GREGORIAN
  true,  true, //14    4,  < YEAR_GREGORIAN
  true,  true, //15   12,  < YEAR_GREGORIAN
  false, false,//16 7866, 
  true,  true, //17 -120,  < YEAR_GREGORIAN
  true,  true  //18    0   < YEAR_GREGORIAN
  };

TsWriteToView(_T("Proleptic Gregorian Calendar:\r\n"));
int i = 0;
while ((i < TESTCOUNT) && bRes)
  {
    
  bRes = (IsLeapYear((int_least16_t)iYear[i]) == bLeapYear[i][ID_HYSTORIC]); //Test inline
  if (bRes)
    {
      //Test proleptic macro
    bRes = (IS_LEAP_YEAR(iYear[i]) == bLeapYear[i][ID_PROLEPTIC]);
    }

  if (bRes)
    {
    //Proleptic Gregorian Calendar
    TCHAR szYear[8];
    TsWriteToView(_itot(iYear[i],szYear,10));
    TsWriteToView(_T(". is "));
    if (iYear[i] > 0 )
      {
    //Note: (year&3) is faster than (year%4), but vaild only for years > 0
      if(!((iYear[i] & 3) == 0 && iYear[i] % 100 != 0 || iYear[i] % 400 == 0))
        TsWriteToView(_T("not"));
      }
    else
      {
      if(!((iYear[i] % 4) == 0 && iYear[i] % 100 != 0 || iYear[i] % 400 == 0))
        TsWriteToView(_T("not"));
      }
    TsWriteToView(_T(" leap year.\r\n"));
    }
  i++;
  }

  //Write test log
logEntry.m_bResult = bRes;
LogTest(&logEntry);
logEntry.m_szObjectName = _T("IS_LEAP_YEAR()");
LogTest(&logEntry);
TsWriteToView(LOG_EOT);
TsWriteToView(_T("\r\n"));
return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  10   Biblioteka1.9         2004-10-06 23:43:13  Darko           Unicode fixes
 *  9    Biblioteka1.8         2004-10-01 15:49:07  Darko           fixed MSVC6
 *       SBCS build
 *  8    Biblioteka1.7         2004-06-03 10:02:30  Darko           comment
 *  7    Biblioteka1.6         2004-06-01 18:14:20  Darko           StdAfx changed
 *       to stdafx
 *  6    Biblioteka1.5         2003-09-22 22:06:06  Darko           
 *  5    Biblioteka1.4         2003-09-22 21:57:59  Darko           Unicode
 *  4    Biblioteka1.3         2003-01-30 22:47:38  Darko           Write results
 *       to the test log
 *  3    Biblioteka1.2         2003-01-22 23:23:23  Darko           Unicode
 *  2    Biblioteka1.1         2003-01-20 04:15:36  Darko           Replaced BOOL
 *       with bool
 *  1    Biblioteka1.0         2003-01-15 01:29:45  Darko           
 * $
 *****************************************************************************/
