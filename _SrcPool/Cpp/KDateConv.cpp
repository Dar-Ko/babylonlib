/*$Workfile: KDateConv.cpp$: implementation file
  $Revision: 5$ $Date: 2004-10-01 14:44:57$
  $Author: Darko$

  Defines the class behavior.
  Copyright: CommonSoft Inc.
  2003-09-21 Darko Kolakovic
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#include "KDateConv.h"  //CDateConv class
#ifndef ASSERT
  #include "KTrace.h"
#endif

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

  //warning C4127: conditional expression is constant
#pragma warning (disable: 4127)
///////////////////////////////////////////////////////////////////////////////
// CDateConv class

//-----------------------------------------------------------------------------
/*Nuber of seconds in one day [s/day].
 */
const double CDateConv::SpDAY = (60.0*60.0*24.0);

//-----------------------------------------------------------------------------
/*Rounding value of one half a second,converted to days (0.5[s/ s/day]).
 */
const double CDateConv::HALF_SECOND = 1.0/(2.0*CDateConv::SpDAY);


//-----------------------------------------------------------------------------
/*Coverts from double or DATA type after validation of negative values, since 
  negative dates are not continuous.

  History: Microsoft COleDateTime::DateFromDouble, ATLComTime.inl
 */
CDateConv::CDateConv(const double dValue //[in] value to convert
                    )
{
if( dValue >= 0 ) //No problem if positive
  m_dateValue = dValue;
else
  {
    //If negative, must convert since negative dates not continuous
    //(examples: -.75 to -1.25, -.50 to -1.50, -.25 to -1.75)
  m_dateValue = floor(dValue); // m_dateValue is now whole part

    //Add day's fractions
  m_dateValue += (m_dateValue-dValue);
  }
}

//-----------------------------------------------------------------------------
/*
 */
CDateConv::CDateConv(int iYear,  //[in] nYear  [100, 9999] MS specific TOOD
                    int iMonth, //[in] nMonth [1, 12] 
                    int iDay,   //[in] nDay   [1, 31] 
                    int iHour,  //[in]= 0 nHour  [0, 23] 
                    int iMinute,//[in]= 0 nMin   [0, 59] 
                    int iSecond //[in]= 0 nSec   [0, 59] 
                    )
{
SetDate(iYear, iMonth, iDay, iHour, iMinute, iSecond);
}

      /*Limits of DATE  */
#ifndef DATE_MIN
    /*Minimum values of DATE is about year 100                               */
  #define DATE_MIN       (DATE)(-657434L) //TODO: Fixme! Microsoft ole time !D.K.
#endif
#ifndef DATE_MAX
    /*Maximum values of DATE is about year 9999                              */
  #define DATE_MAX       (DATE)(2958465L)//TODO: Fixme! Microsoft ole time !D.K.
#endif


//-----------------------------------------------------------------------------
/*Convert a DATE to a tm structure
 */
CDateConv::operator tm() const
{
tm tmResult;
  //Valid year range is [100, 9999]
ASSERT((m_dateValue >= DATE_MIN) && (m_dateValue <= DATE_MAX));
if ((m_dateValue >= DATE_MIN) && (m_dateValue <= DATE_MAX))
  {
  const long DAYS_IN_EPCOH = 693959L; //number of days in period
                                      //[0000-01-01, 1989-12-30]
  const long DAYSpWEEK = 7L;
  long lDays;    //number of days
  long lSeconds; //number of seconds since 00:00:00
  double  dTemp = m_dateValue;
    //Round to the second
  dTemp += ((m_dateValue > 0.0) ? HALF_SECOND : -HALF_SECOND);
#pragma KMESSAGE(warning TODO: convert seconds)

    //Integer part is number of days since 1899-12-30
  lDays = (long)m_dateValue + DAYS_IN_EPCOH; //Get number of days
    //Get the day of week [Sunday=0, Saturday=6]
  tmResult.tm_wday = (int)((lDays - 1) % DAYSpWEEK);
    //Get number of seconds since midnight
  dTemp = fabs(dTemp);
  lSeconds = (long)((dTemp - floor(dTemp)) * CDateConv::SpDAY);
  if (lSeconds > 0)
    {
    tmResult.tm_sec = (int)lSeconds % 60L;
    tmResult.tm_min = (int)(lSeconds / 60L) % 60;
    tmResult.tm_hour = (int)lSeconds / (60L * 60L);
    }
  else //Midnight 00:00:00
    tmResult.tm_hour = tmResult.tm_min = tmResult.tm_sec = 0;

  }
else
  {
  memset(&tmResult,0, sizeof(tm));
  }

tmResult.tm_isdst = -1; //Daylight saving time is unknown
return tmResult;
////////////////////////////////////////////////////////////////
#if 0
// Half a second, expressed in days
//static const DATE HALF_SECOND = (1.0/172800.0);

// One-based array of days in year at month start
static rgMonthDays[13] =
  {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

// The legal range does not actually span year 0 to 9999.
//if (m_dateValue > maxDateTime || m_dateValue < minDateTime) // about year 100 to about 9999
//  return FALSE;

//long lNDays;             // Number of days since Dec. 30, 1899
//long lDays;     // Number of days since 1/1/0
//long lSeconds;        // Time in seconds since midnight
//long nMinutesInDay;     // Minutes in day

long n400Years;         // Number of 400 year increments since 1/1/0
long n400Century;       // Century within 400 year block (0,1,2 or 3)
long n4Years;           // Number of 4 year increments since 1/1/0
long n4Day;             // Day within 4 year block
            //  (0 is 1/1/yr1, 1460 is 12/31/yr4)
long n4Yr;              // Year within 4 year block (0,1,2 or 3)
BOOL bLeap4 = TRUE;     // TRUE if 4 year block includes leap year

//double dTemp = m_dateValue; // tempory serial date

// If a valid date, then this conversion should not overflow
//lNDays = (long)dTemp;

// Round to the second
//dTemp += ((m_dateValue > 0.0) ? HALF_SECOND : -HALF_SECOND);

//lDays = (long)dTemp + 693959L; // Add days from 1/1/0 to 12/30/1899

//dTemp = fabs(dTemp);
//lSeconds = (long)((dTemp - floor(dTemp)) * 86400.);

// Calculate the day of week (sun=1, mon=2...)
//   -1 because 1/1/0 is Sat.  +1 because we want 1-based
//tmDest.tm_wday = (int)((lDays - 1) % 7L) + 1;

// Leap years every 4 yrs except centuries not multiples of 400.
n400Years = (long)(lDays / 146097L);

// Set lDays to day within 400-year block
lDays %= 146097L;

// -1 because first century has extra day
n400Century = (long)((lDays - 1) / 36524L);

// Non-leap century
if (n400Century != 0)
{
  // Set lDays to day within century
  lDays = (lDays - 1) % 36524L;

  // +1 because 1st 4 year increment has 1460 days
  n4Years = (long)((lDays + 1) / 1461L);

  if (n4Years != 0)
    n4Day = (long)((lDays + 1) % 1461L);
  else
  {
    bLeap4 = FALSE;
    n4Day = (long)lDays;
  }
}
else
{
  // Leap century - not special case!
  n4Years = (long)(lDays / 1461L);
  n4Day = (long)(lDays % 1461L);
}

if (bLeap4)
{
  // -1 because first year has 366 days
  n4Yr = (n4Day - 1) / 365;

  if (n4Yr != 0)
    n4Day = (n4Day - 1) % 365;
}
else
{
  n4Yr = n4Day / 365;
  n4Day %= 365;
}

// n4Day is now 0-based day of year. Save 1-based day of year, year number
tmDest.tm_yday = (int)n4Day + 1;
tmDest.tm_year = n400Years * 400 + n400Century * 100 + n4Years * 4 + n4Yr;

// Handle leap year: before, on, and after Feb. 29.
if (n4Yr == 0 && bLeap4)
{
  // Leap Year
  if (n4Day == 59)
  {
    /* Feb. 29 */
    tmDest.tm_mon = 2;
    tmDest.tm_mday = 29;
    goto DoTime;
  }

  // Pretend it's not a leap year for month/day comp.
  if (n4Day >= 60)
    --n4Day;
}

// Make n4DaY a 1-based day of non-leap year and compute
//  month/day for everything but Feb. 29.
++n4Day;

// Month number always >= n/32, so save some loop time */
for (tmDest.tm_mon = (n4Day >> 5) + 1;
  n4Day > rgMonthDays[tmDest.tm_mon]; tmDest.tm_mon++);

tmDest.tm_mday = (int)(n4Day - rgMonthDays[tmDest.tm_mon-1]);

DoTime:
/*
  if (lSeconds == 0)
    tmDest.tm_hour = tmDest.tm_min = tmDest.tm_sec = 0;
  else
  {
    tmDest.tm_sec = (int)lSeconds % 60L;
    nMinutesInDay = lSeconds / 60L;
    tmDest.tm_min = (int)nMinutesInDay % 60;
    tmDest.tm_hour = (int)nMinutesInDay / 60;
  }
*/
//return TRUE;
#endif
}

//-----------------------------------------------------------------------------
/*
 */
bool CDateConv::SetDate(int iYear,  //[in] nYear  [100, 9999] MS specific TOOD
                        int iMonth, //[in] nMonth [1, 12] 
                        int iDay,   //[in] nDay   [1, 31] 
                        int iHour,  //[in]= 0 nHour  [0, 23] 
                        int iMinute,//[in]= 0 nMin   [0, 59] 
                        int iSecond //[in]= 0 nSec   [0, 59] 
                        )
{
ASSERT(FALSE);
return false; //TODO: SetDate convert to JD
}

///////////////////////////////////////////////////////////////////////////////
#pragma warning (default: 4127)
/*****************************************************************************
 * $Log: 
 *  5    Biblioteka1.4         2004-10-01 14:44:57  Darko           fixed KMESSAGE
 *       format
 *  4    Biblioteka1.3         2004-06-01 16:50:18  Darko           time sync
 *  3    Biblioteka1.2         2003-09-28 00:38:35  Darko           CDateConv(const
 *       double dValue)
 *  2    Biblioteka1.1         2003-09-27 11:13:06  Darko           SetDate()
 *  1    Biblioteka1.0         2003-09-23 16:08:12  Darko           
 * $
 *****************************************************************************/
