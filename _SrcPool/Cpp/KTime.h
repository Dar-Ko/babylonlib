/*$Workfile: KTime.h$: implementation file
  $Revision: 9$ $Date: 15/01/2003 12:26:13 AM$
  $Author: Darko$

  Date and time manipulation
  Copyright: CommonSoft Inc
  Jan 2003 Darko Kolakovic
 */
/* Group=Time                                                                */

#ifndef __KTIME_H__
    /*KTime.h sentry                                                         */
  #define __KTIME_H__


#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

#include <time.h>     /*tm struct                                            */
#include "KTypedef.h"

/* ///////////////////////////////////////////////////////////////////////// */
/*Structure tm holds date and time and has following members as defined
  in time.h header file:


        struct tm
          {
          int tm_sec;  //seconds after the minute [0, 61]
          int tm_min;  //minutes after the hour   [0, 59]
          int tm_hour; //hours after midnight     [0, 23]
          int tm_mday; //day of the month         [1, 31]
          int tm_mon;  //month of the year        [0, 11] January = 0
          int tm_year; //years since 1900         [INT_MIN, INT_MAX]
          int tm_wday; //day of the week          [0,  6] Sunday = 0
          int tm_yday; //day of the year          [0,365] 1. January = 0
          int tm_isdst;//daylight savings time flag. Positive if daylight
                       //saving time is in effect; 0 if daylight saving time
                       //is not in effect; negative if status of daylight
                       //saving time is unknown.
          }

  Note: ISO C: tm_sec ranges from 0 to 61 to accomodate as many as two leap
        seconds.
        tm_yday ranges from 0 to 365 to accomodate one leap day.

  Example:
    #include <ctime>
    using namespace std;
    void GetLocalTime() //Converts time_t to tm structure
      {
      time_t timeCurr;
      tm     sLocal;
      time(&timeCurr);                 //Get current time_t value
      sLocal=*(localtime(&timeCurr));  //Dereference and assign
      }
    void SetLocalTime() //Converts tm structure to time_t
      {
      time_t timeCurr;
      tm sLocal;
      time(&timeCurr);                //Get current time_t value
      sLocal=*(localtime(&timeCurr)); //Dereference and assign
      time_t timeRes=mktime(&sLocal); //Assign result
      }

  See also: time.h, YEAR_TM_BASE
 */
typedef struct tm* PTM;

#if ((__BORLANDC__ > 0x100) &&(__BORLANDC__ <= 0x500))
  #include <dos.h> /*date, time structure*/
  #define date date
  #define time time
  #pragma message ("   #include <dos.h")
#endif

#ifndef date
  /*Structure date holds calendar date
    History: <dos.h> from DJGPP, Borland C++
  */
  struct date
  {
  int_least16_t da_year;   /*current year or years since 1980 */
  int_least8_t  da_day;    /*day of the month, [1, 31]        */
  int_least8_t  da_mon;    /*month, [1, 12] January = 1       */
  };

  #define date date
#endif

typedef struct date* PDATE; /*Calendar date                   */

#ifndef time
  /*Structure time holds time of the day
    History: <dos.h> from DJGPP, Borland C++
   */
  struct time
  {
  uint_least8_t ti_min;     /*minutes, [0, 59]                */
  uint_least8_t ti_hour;    /*hours, [0, 23]                  */
  uint_least8_t ti_hund;    /*hunrdredths of seconds, [0, 99] */
  uint_least8_t ti_sec;     /*seconds, [0, 59]                */
  };

  #define time time
#endif

typedef struct time* PTIME;  /*Time of the day                */

/* ///////////////////////////////////////////////////////////////////////// */
/*Macros                                                                     */

#define YEAR_TM_BASE    1900 /*staring year for tm structure                 */
#define YEAR_EPOCH_UNIX 1970 /*Unix epoch is the time 1970-1-1T00:00:00.
                               See also: sys/time.h                          */
#define YEAR_EPOCH_DOS  1980 /*DOS epoch is the time 1980-1-1T00:00:00.
                               See also: dos.h DJGPP, Borland C++            */
#define YEAR_EPOCH_WINFILETIME 1601 /*Windows File Time epoch is time
                               1601-1-1T00:00:00Z UTC. The FILETIME structure
                               is a 64-bit value representing the number of
                               100 ns intervals since the epoch.
                               See also: Winbase.h
                               */
#define YEAR_EPOCH_MACLONGTIME 1904 /*MacOS Long Time epoch is time
                               1904-1-1T00:00:00Z UTC. The structure
                               is a 64-bit value representing the number of
                               1 s intervals since the epoch.
                               */
#define YEAR_EPOCH_JAVA 1970 /*Java Time epoch is time 1970-1-1T00:00:00Z UTC.
                               It is a 64-bit value representing the number of
                               1 ms intervals since the epoch.
                               */

#define YEAR_GREGORIAN  1582 /*Year of introduction of the Gregorian calendar
                               by Council of Trent. It was decreed by Pope
                               Gregory XIII in a papal bull of 1582-02 that 10
                               days should be dropped so that 1582-10-15
                               should follow immediately after 1582-10-04.
                               The calendar corrects for errors in the older
                               Julian Calendar by having 97 leap years every
                               400 years.
                               See also: YEAR_GREGORIAN2, YEAR_GREGORIAN3,
                               YEAR_GREGORIAN4, IsLeapYear()*/
#define YEAR_GREGORIAN2 1700 /*Assumes the Gregorian Calendar reformation have
                               occurred 1700-02-28.
                               See also: YEAR_GREGORIAN*/
#define YEAR_GREGORIAN3 1752 /*Assumes the Gregorian Calendar reformation have
                               occurred 1752-09-13.
                               See also: YEAR_GREGORIAN*/
#define YEAR_GREGORIAN4 1753 /*Assumes the Gregorian Calendar reformation have
                               occurred 1753-02-28.
                               See also: YEAR_GREGORIAN*/

#ifndef TIME_T_MIN
  #include <limits.h> /*CHAR_BIT constant*/
  /*Minimum time_t value                                                     */
  #define TIME_T_MIN (0 < (time_t)(-1) ? \
          (time_t)0  : ~ (time_t)0 << (sizeof(time_t) * CHAR_BIT - 1))
#endif
#ifndef TIME_T_MAX
  /*Maximum time_t value                                                     */
  #define TIME_T_MAX (~(time_t)0 - TIME_T_MIN)
#endif

  /*The international standard date notation in extended form is YYYY-MM-DD
    where YYYY is the year in the usual Gregorian calendar,
    MM is the month of the year [01,12] (January is 01), and
    DD is the day of the month [01,31].

    See also: International Standard
    {HTML: <A HREF ="Res/ISO8601.htm"> ISO 8601:2000 </A>}
    Data elements and interchange formats,
    {HTML: <A HREF ="Res/RFC3339.htm"> RFC 3339 </A>}
    Date and Time on the Internet: Timestamps
  */
#define _STD_DATE_FORMAT  "%4d-%2d-%2d"

  /*The extended form of the international standard notation for the time of 
    day is hh:mm:ss
    where hh is the number of complete hours that have passed since midnight [00,24],
    mm is the number of complete minutes that have passed since the start of
    the hour [00,59], and
    ss is the number of complete seconds since the start of the minute [00-60].
    If the hour value is 24, then the minute and second values must be zero.
    The value 60 for ss is allowed for the occasional leap second.

    See also: International Standard
    {HTML: <A HREF ="Res/ISO8601.htm"> ISO 8601:2000 </A>}
    Data elements and interchange formats,
    {HTML: <A HREF ="Res/RFC3339.htm"> RFC 3339 </A>}
    Date and Time on the Internet: Timestamps
   */
#define _STD_TIME_FORMAT  "%2d:%2d:%2d"

#ifndef IS_LEAP_YEAR
  /*Returns nonzero if a year is a leap year. Leap year is every forth year,
    except every 100th is not, and every 400th is.
    Leap years are years with an additional day YYYY-02-29, where the year
    number is a multiple of four with the following exception: if a year is
    a multiple of 100 is not a leap year, exept if it is also a multiple of 400.
    For example, 1900 was not a leap year, but 2000 is one.

    Note: macro uses the proleptic Gregorian calendar e.g. leap years are
    defined by the same rule into the indefinite past and future, even
    before the calendar was adopted.

    Example:
      bool bLeap = false;
      if (IS_LEAP_YEAR(tmTime.tm_year+YEAR_TM_BASE))
        bLeap = true;

    See also: International Standard
    {HTML: <A HREF ="Res/ISO8601.htm"> ISO 8601:2000 </A>}
    Data elements and interchange formats,
    {HTML: <A HREF ="Res/RFC3339.htm"> RFC 3339 </A>}
    Date and Time on the Internet: Timestamps
   */
  #define	IS_LEAP_YEAR(year)	\
    ((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0))
#endif


/* ///////////////////////////////////////////////////////////////////////// */
/*Declarations                                                               */
#ifdef __cplusplus
extern "C"
  {
#endif

  int TmCmp(const PTM ptmTime1,const PTM ptmTime2);
  PTM DatetoTm(PTM ptmTarget, const PDATE pdateSource, const PTIME ptimeSource);

#ifdef __cplusplus
  }
#endif

/* ///////////////////////////////////////////////////////////////////////// */
/* C++ declarations                                                          */
#ifdef __cplusplus

///////////////////////////////////////////////////////////////////////////////
// Inlines

//operator==()-----------------------------------------------------------------
/*Operator compares two date/time values.

  Return: true if the condition is true; otherwise, it is false.
 */
inline bool operator==(const tm& tmTime1,//[in]object corresponding to
                                         //the left side of the operator.
                       const tm& tmTime2 //[in] object corresponding to
                                         //the right side of the operator.
                      )
{
if (tmTime1.tm_year == tmTime2.tm_year)
 if (tmTime1.tm_mon == tmTime2.tm_mon)
  if (tmTime1.tm_mday == tmTime2.tm_mday)
   if (tmTime1.tm_hour == tmTime2.tm_hour)
    if (tmTime1.tm_min == tmTime2.tm_min)
     if (tmTime1.tm_sec == tmTime2.tm_sec)
       return true;
return false;
}

//operator>()------------------------------------------------------------------
/*Operator compares two date/time values.

  Return: true if the condition is true; otherwise, it is false.
 */
inline bool operator>(const tm& tmTime1,//[in]object corresponding to
                                        //the left side of the operator.
                      const tm& tmTime2 //[in] object corresponding to
                                        //the right side of the operator.
                      )
{
if (tmTime1.tm_year > tmTime2.tm_year)
  return true;
if ((tmTime1.tm_year == tmTime2.tm_year) && (tmTime1.tm_mon > tmTime2.tm_mon))
  return true;
else
  {
  if ((tmTime1.tm_mon == tmTime2.tm_mon) && (tmTime1.tm_mday >tmTime2.tm_mday))
      return true;
  else
    {
    if((tmTime1.tm_mday ==tmTime2.tm_mday)&&(tmTime1.tm_hour >tmTime2.tm_hour))
      return true;
    else
      {
      if((tmTime1.tm_hour ==tmTime2.tm_hour)&&(tmTime1.tm_min >tmTime2.tm_min))
        return true;
      else
        if((tmTime1.tm_min ==tmTime2.tm_min)&&(tmTime1.tm_sec >tmTime2.tm_sec))
           return true;
      }
    }
  }
return false;
}

//IsLeapYear()-----------------------------------------------------------------
/*Returns nonzero if a year is a leap year. Leap year is every forth year,
  except every 100th is not, and every 400th is.
  Leap years are years with an additional day YYYY-02-29, where the year
  number is a multiple of four with the following exception: if a year is
  a multiple of 100 is not a leap year, exept if it is also a multiple of 400.
  For example, 1900 was not a leap year, but 2000 is one.

  The leap years are introduced by adoption of the Gregorian Calendar proposed
  by Aloysius Lilius from Naples to Council of Trent (1545-1563). It was
  decreed by Pope Gregory XIII in a papal bull of 1582-02 that 10 days
  should be dropped so that 1582-10-15 should follow immediately after
  1582-10-04.

  The actual length of a sidereal year (the time required for the Earth to
  revolve once about the Sun) is 365.25635 days.
  In the Gregorian Calendar, the year is approximated as
  365+97/400 days = 365.2425 days. Therefore  it takes approximately 3300 years
  for the tropical year to shift one day with respect to the Gregorian calendar.
  The approximation 365+97/400 is achieved by having 97 leap years every 400
  years.

  The calendar replaces the older Julian Calendar. In the Julian Calendar
  a year is a leap year if it is divisible by 4.

  Note: calendar used is not proleptic; calucaltion for leap years before
  1582 is based on Julian Calendar.

  Return: true if a year is a leap year; otherwise returns false.

  See also: International Standard
  {HTML: <A HREF ="Res/ISO8601.htm"> ISO 8601:2000 </A>}
  Data elements and interchange formats,
  {HTML: <A HREF ="Res/RFC3339.htm"> RFC 3339 </A>}
  Date and Time on the Internet: Timestamps, YEAR_GREGORIAN, YEAR_GREGORIAN4
 */
inline bool IsLeapYear(const int_least16_t iYear //[in] current year
                      )
{
//TODO: verify efficienci of
//(iYear&3) == 0 && iYear%100 != 0 || iYear % 400 == 0;
return  ( (iYear >= YEAR_GREGORIAN) ?
          (iYear % 4 == 0  &&  iYear % 100 != 0  ||  iYear % 400 == 0 ):
          (iYear % 4 == 0) ); //In the Julian Calendar a year is a leap
                              //year if it is divisible by 4.
}

#endif //__cplusplus

/* ///////////////////////////////////////////////////////////////////////// */
#endif  /*__KTIME_H__                                                        */

/*****************************************************************************
 * $Log:
 *  3    Biblioteka1.2         1/13/03 1:50:24 AM   Darko           IsLeapYear
 *  2    Biblioteka1.1         1/10/03 9:52:09 PM   Darko Kolakovic ISO8061 time
 *       format
 *  1    Biblioteka1.0         1/8/03 3:26:02 PM    Darko Kolakovic
 * $
 *****************************************************************************/
