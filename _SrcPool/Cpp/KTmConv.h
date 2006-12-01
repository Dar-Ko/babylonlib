/*$Workfile: KTmConv.h$: implementation file
  $Revision: 8$ $Date: 2005-06-28 13:38:13$
  $Author: Darko Kolakovic$

  struct tm conversions
  Copyright: CommonSoft Inc
  2003-09-21 Darko Kolakovic
 */
/* Group=Time                                                                */

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
  #pragma once
#endif

#ifndef _KTMCONV_H_
    //$Workfile: KTmConv.h$ sentry
  #define _KTMCONV_H_

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

#if _MSC_VER >= 1300
    //Requires Microsoft Visual C++ .Net
  #ifndef _USE_TIME_64
      //Microsoft specific data type  __time64_t is defined
    #define _USE_TIME_64 64
  #endif
#endif
#if _MFC_VER >= 0x0700
  //Requires MFC 7.0+
  #ifndef _USE_TIME_64
      //Microsoft specific data type  __time64_t is defined
    #define _USE_TIME_64 64
  #endif
#endif

#include <time.h>     /*tm struct                                            */

#ifndef _KTIME_H_ //#include "KTime.h"
  #ifndef YEAR_EPOCH_TM
    #define YEAR_EPOCH_TM   1900 /*staring year for tm structure             */
  #endif
#endif
///////////////////////////////////////////////////////////////////////////////
//CTm encapsulates tm structure used in various date and time functions.
//Structure tm holds date and time and has following members as defined
//in time.h header file:
//
//      struct tm
//        {
//        int tm_sec;  //seconds after the minute [0, 61]
//        int tm_min;  //minutes after the hour   [0, 59]
//        int tm_hour; //hours after 00:00:00     [0, 23]
//        int tm_mday; //day of the month         [1, 31]
//        int tm_mon;  //month of the year        [0, 11] January = 0
//        int tm_year; //years since 1900         [INT_MIN, INT_MAX]
//        int tm_wday; //day of the week          [0,  6] Sunday = 0
//        int tm_yday; //day of the year          [0,365] 1. January = 0
//        int tm_isdst;//daylight savings time flag. Positive if daylight
//                     //saving time is in effect; 0 if daylight saving time
//                     //is not in effect; negative if status of daylight
//                     //saving time is unknown.
//        }
//
//Note: ISO C: tm_sec ranges from 0 to 61 to accomodate as many as two leap
//      seconds.
//      tm_yday ranges from 0 to 365 to accomodate one leap day.
//
//See also: time.h, asctime(), strftime(), PTM
class CTm : public tm
{
public:
  CTm (tm& tmValue);
  CTm (time_t timeValue);
  #ifdef _USE_TIME_64
    CTm (__time64_t timeValue);
    operator __time64_t() const;
  #endif

  operator time_t() const;
  CTm& operator= (tm const & tmValue);
  bool IsValid() const;
  //LPTSTR GetDate(LPTSTR szTarget, bool bBasic = true); TODO: _DATE_FORMAT_STD_BASIC
  //LPTSTR GetTime(LPTSTR szTarget, bool bBasic = true); TODO: _TIME_FORMAT_STD_BASIC
  void GetLocalTime();
  time_t CTm::GmTime() const;
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Copy constructor
 */
inline CTm::CTm(tm& tmValue //[in] date and time to copy
                )
{
*((tm *)this) = tmValue;
}

//-----------------------------------------------------------------------------
/*Converts a time value and corrects for the local time zone in conformance
  with the ANSI C standard.
  time_t represents number of seconds elapsed since 1970-01-01T00:00:00Z (UTC).
  Valid range is [1970-01-01 00:00:00, 2038-01-18 19:14:07].
 */
inline CTm::CTm(time_t timeValue //[in] system time
               )
{
//Convert a time value and correct for the local time zone
*(tm *)this = *localtime(&timeValue);
}

#if _USE_TIME_64
/*Converts a time value and corrects for the local time zone.
  __time64_t represents number of seconds elapsed since 1970-01-01T00:00:00Z (UTC).
  Valid range is [1970-01-01 00:00:00, 3000-12-31 23:59:59].
 */
inline CTm::CTm(__time64_t timeValue //[in] system time
               )
{
  //Convert a time value and correct for the local time zone
*(tm*)this = *_localtime64(&timeValue);
}
#endif

//-----------------------------------------------------------------------------
/*Assign operator
 */
inline CTm& CTm::operator=(tm const& tmValue //[in] date and time to assign
                )
{
*((tm *)this) = tmValue;
return *this;
}

//-----------------------------------------------------------------------------
/*Converts the local time to a calendar value. time_t represents number of
  seconds elapsed since 1970-01-01T00:00:00Z (UTC).
  Valid range is [1970-01-01 00:00:00, 2038-01-18 19:14:07] (UTC).

  Returns: the specified calendar time encoded as a value of type time_t or -1
  if time is out of range.
 */
inline CTm::operator time_t () const
{
return mktime((tm *)this);
}

#ifdef _USE_TIME_64
/*Converts the local time to a calendar value. __time64_t represents number of
  seconds elapsed since 1970-01-01T00:00:00Z (UTC).
  Valid range is [1970-01-01 00:00:00, 3000-12-31 23:59:59] (UTC).

  Returns: the specified calendar time encoded as a value of type time_t or -1
  if time is out of range.
 */
inline CTm::operator __time64_t () const
{
return _mktime64((tm *)this);
}
#endif

//-----------------------------------------------------------------------------
/*Convert date and time to coordinated universal time (UTC).

  Returns: The time is represented as seconds elapsed since 1970-01-01 00:00:00,
  coordinated universal time (UTC).

  See also: Unix time, Greenwich Mean Time (GMT), Coordinated Universal Time (UTC)
 */
time_t CTm::GmTime() const
{
const int_least32_t SpDAY = 60*60*24;     //[s/day]
const int_least32_t DAY19700101 = 719469; //number of days on 1970-01-01
                                          //according to Julian Day counting [day]
const int ID_FEBRUARY = 1;
const int EPOCH_TM = YEAR_EPOCH_TM;
//Note: The Julian Day (JD) or Julian Day Number or Astronomical Julian Day (AJD)
//is the time that has elapsed since 4713-01-01 12:00 BC (according to
//the proleptic Julian calendar; or 4714-11-24 BC according to the proleptic
//Gregorian calendar), expressed in days and fractions of a day.
int iYear = tm_year + EPOCH_TM; //tm_year = years since 1900

  //D.K. 2003-09-21 month fix; see F. Bellard mktimegm()
int iMonth; //month count
if (tm_mon > ID_FEBRUARY)
  iMonth = tm_mon + 1;
else
  {
  iMonth = tm_mon + 1 + 12; //add one year in the month count
  iYear--; //decrease year count for one
  }
  //Get number of days since 1970-01-01, including leap days
iYear = 365 * iYear + iYear / 4 - iYear / 100 + iYear / 400 - DAY19700101; //[day]
  //Get number of seconds in whole days since 1970-01-01 00:00:00
time_t timeResult =
        SpDAY * (tm_mday + (153 * iMonth - 457) / 5 + iYear);//[s]
  //Add remaining part of the day
timeResult += 3600 * tm_hour + 60 * tm_min + tm_sec;
return timeResult;
}

//-----------------------------------------------------------------------------
extern "C" int g_iMonthLen[];
/*Validates date and time range.

  Note: the day of the month is valid if it is in [1, 31] range. Leap years or
  number of days for the particular month are not accounted into validation.

  Returns: true if date and time are in valid range, othervise returns false.
 */
inline bool CTm::IsValid() const
{
if ((tm_sec >= 0) && (tm_sec <= 61))        //seconds after the minute [0, 61]
  if ((tm_min >= 0) && (tm_min < 60))       //minutes after the hour   [0, 59]
    if ((tm_hour >= 0) && (tm_hour < 24))   //hours after 00:00:00     [0, 23]
      if ((tm_mday > 0) && (tm_mday <= 31)) //day of the month         [1, 31]
        if ((tm_wday >= 0) && (tm_wday < 7))     //day of the week     [0,  6]
          if ((tm_yday >= 0) && (tm_yday < 366)) //day of the year     [0,365]
            return true;
return false;
}

//-----------------------------------------------------------------------------
/*Obtains current local date and time. The time is corrected for the local
  time zone.
 */
inline void CTm::GetLocalTime()
{
#ifdef _USE_TIME_64
  __time64_t timeCurr;
  _time64(&timeCurr);                       //Get current _time64 value
  *(tm*)this = *(_localtime64(&timeCurr));  //Dereference and assign
#else //ANSI C
  time_t timeCurr;
  time(&timeCurr);                 //Get current time_t value
  *(tm*)this = *(localtime(&timeCurr));  //Dereference and assign
#endif
}

//-----------------------------------------------------------------------------
/*TODO: _DATE_FORMAT_STD_BASIC
LPTSTR CTm::GetDate(LPTSTR szTarget, bool bBasic = true)
{

printDate(szTarget, tm_mday, tm_mon+1, tm_year +1900);
}

*/

///////////////////////////////////////////////////////////////////////////////
// Inline functions

#if defined(_STL) || defined (_USE_STL) //Use Standard Template Library (STL)
#pragma message ("  Standard Template Library (STL) used " __FILE__ )

#include "STL/KOstream.h" //tostream typedef
  //---------------------------------------------------------------------------
  /*Writes date and time in standard exended format YYYY-MM-DDThh:mm:ss to
    output stream.

    See also: _TIME_FORMAT_STD, International Standard
    {html: <a href="Documentation/ISO8601.htm">ISO 8601:2000</a>}
    Data elements and interchange formats,
    {html: <a href="Documentation/RFC3339.htm">RFC 3339</a>}
    Date and Time on the Internet: Timestamps
  */
  inline tostream& operator<< (tostream& outStream,//[out] output stream
                               tm const& tmValue   //[in] value to write
              )
  {
  outStream.fill(_T('0'));
  outStream << std::setw(4) << tmValue.tm_year + YEAR_EPOCH_TM
            << _T('-') << std::setw(2) << tmValue.tm_mon + 1
            << _T('-') << std::setw(2) << tmValue.tm_mday
            << _T('T') << std::setw(2) << tmValue.tm_hour
            << _T(':') << std::setw(2) << tmValue.tm_min
            << _T(':') << std::setw(2) << tmValue.tm_sec;
  outStream.fill();

  return outStream;
  }
#endif

///////////////////////////////////////////////////////////////////////////////
#endif  //_KTMCONV_H_
/*****************************************************************************
 * $Log:
 *  6    Biblioteka1.5         2004-10-01 15:48:13  Darko           excluded
 *       __time64_t for MSVC6
 *  5    Biblioteka1.4         2003-09-30 09:13:52  Darko           YEAR_EPOCH_TM
 *  4    Biblioteka1.3         2003-09-28 01:42:40  Darko           comment
 *  3    Biblioteka1.2         2003-09-27 12:17:00  Darko           Constructor
 *       does not set local time
 *  2    Biblioteka1.1         2003-09-23 17:12:00  Darko           _DATE_EPOCH_TM
 *  1    Biblioteka1.0         2003-09-22 22:21:20  Darko
 * $
 *****************************************************************************/