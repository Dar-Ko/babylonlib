/*$Workfile: KDateCst.c$: implementation file
  $Revision: 5$ $Date: 2004-10-06 22:43:03$
  $Author: Darko$

  Date global constants
  Copyright: CommonSoft Inc.
  Darko Kolakovic 2003-09-18
*/

/* Group=Time                                                                */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */
#ifdef _DEBUG
  static char THIS_FILE[] = __FILE__;
#endif
#include "KTChar.h" /*_T() macro                                             */
#include "KTime.h"  /*date, time struct                                      */
  /*Abbreviated weekday names used in some protocols
   */
LPCTSTR g_szDayNameAbr[] = 
  { 
  _T("Sun"), /*0*/
  _T("Mon"), /*1*/
  _T("Tue"), /*2*/
  _T("Wed"), /*3*/
  _T("Thu"), /*4*/
  _T("Fri"), /*5*/
  _T("Sat")  /*6*/
  };

  /*Abbreviated month names used in some protocols
   */
LPCTSTR g_szMonthAbr[] = 
  {
  _T("Jan"), /* 0*/
  _T("Feb"), /* 1*/
  _T("Mar"), /* 2*/
  _T("Apr"), /* 3*/
  _T("May"), /* 4*/
  _T("Jun"), /* 5*/
  _T("Jul"), /* 6*/
  _T("Aug"), /* 7*/
  _T("Sep"), /* 8*/
  _T("Oct"), /* 9*/
  _T("Nov"), /*10*/
  _T("Dec")  /*11*/
  };

  /*Length of months in days
   */
int g_iMonthLen[] = 
  { 
  /* 0   1   2   3   4   5   6   7   8   9  10  11 */ 
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
  };

#if LANG_CURRENT == LANG_ENGLISH
    /*Weekday names
    */
  LPCTSTR g_szDayName[] = 
    { 
    _T("Sunday"   ), /*0*/
    _T("Monday"   ), /*1*/
    _T("Tuesday"  ), /*2*/
    _T("Wednesday"), /*3*/
    _T("Thursday" ), /*4*/
    _T("Friday"   ), /*5*/
    _T("Saturday")   /*6*/
    };

    /*Month names
    */
  LPCTSTR g_szMonth[] = 
    {
    _T("January" ),  /* 0*/
    _T("February" ), /* 1*/
    _T("March"    ), /* 2*/
    _T("April"    ), /* 3*/
    _T("May"      ), /* 4*/
    _T("June"     ), /* 5*/
    _T("July"     ), /* 6*/
    _T("August"   ), /* 7*/
    _T("September"), /* 8*/
    _T("October"  ), /* 9*/
    _T("November" ), /*10*/
    _T("December" )  /*11*/
    };

#endif

#pragma warning(disable: 4127) /*warning C4127: conditional expression is constant*/
#include "KTrace.h" //ASSERT()
/*---------------------------------------------------------------------------*/
/*Range of month index is not validated. In case of overflow returns 
  number of days in February.
 */
uint_fast16_t GetDaysInMonth(uint_fast16_t nYear, /*[in] year */
                             uint_fast16_t nMonth /*[in] index of the 
                                                    month [0,11]*/
                            )
{
ASSERT(nMonth <= 11);
nMonth %= 12; /*Limit the range of the months*/

if (nMonth != 1) 
  return g_iMonthLen[nMonth];
 /*Return number of days in February */
#ifndef __cplusplus
if (nYear >= YEAR_GREGORIAN)
  return (IS_LEAP_YEAR(nYear) ? 29 : 28);
else
  return ((nYear % 4 == 0) ? 29 : 28);
#else
  return (::IsLeapYear (nYear) ? 29 : 28);
#endif
}


int  __cdecl _gx_end_of_month(int m, int y)
{
  switch (m)
  {
  case 4:
  case 6:
  case 9:
  case 11:
    return 30;
  case 2:
    if (IS_LEAP_YEAR(y))
      return 29;
    return 28;
  default:
    return 31;
  }
}

#pragma warning(default: 4127)


uint_fast16_t GetDaysInYear(uint_fast16_t nYear /*[in] year */
                           )
{
uint_fast16_t nResult = 365;
if (nYear == YEAR_GREGORIAN)
  nResult -= 10; /*10 days are cancelled by the Gregorian reform*/
else 
  if (nYear > YEAR_GREGORIAN)
    {
    if (IS_LEAP_YEAR(nYear) != 0)
      nResult++;
    }
  else
    {
    if (nYear % 4 == 0)
      nResult++;
    }
return nResult;
}

struct date IntoYMD (long nDays)
{
    // This algorithm is based on Algorithm 199, CACM, Aug 1963. The
    // algorithm is not valid for dates before Sep 14, 1752.
    unsigned long d;
    unsigned long j = nDays - 1721119L;
    struct date retVal;
    unsigned long mo, da, y;
    y = (((j<<2) - 1) / 146097L);
    j = (j<<2) - 1 - 146097L*y;
    d = (j>>2);
    j = ((d<<2) + 3) / 1461;
    d = (d<<2) + 3 - 1461*j;
    d = (d + 4)>>2;
    mo = (5*d - 3)/153;
    d  = 5*d - 3 - 153*mo;
    da = ((d + 5)/5);
    y  = (100*y + j);
    if (mo < 10)
        mo += 3;
    else {
        mo -= 9;
        y ++;
    }
    retVal.da_year = (short)y;
    retVal.da_day = (char)da;
    retVal.da_mon = /*(eMonth)*/ (char)mo;
    return retVal;
}
#ifdef date
#pragma message("KDateCst.c date defined")
#endif
long IntoDays  (const struct date/*&*/ s)
{
    // This algorithm is based on Algorithm 199, CACM, Aug 1963. The
    // algorithm is not valid for dates before Sep 14, 1752.
unsigned long c ;
unsigned long yy;

    struct date t = s;
    if (t.da_year <= 99)
        t.da_year += 1900;
    if (s.da_day <= 0 || s.da_day > (int)GetDaysInMonth (s.da_year, s.da_mon))
        return -1;
        
    if (t.da_mon > 2)        
        t.da_mon = /*(eMonth)*/ (t.da_mon - 3);
    else {
        t.da_mon = /*(eMonth) */(t.da_mon + 9);
        t.da_year--;
    } 
    c  = t.da_year / 100;
    yy = t.da_year - 100*c;
    return ((146097L * c)>>2) + ((1461*yy)>>2) + (153*t.da_mon + 2)/5 + t.da_day
        + 1721119L;
}

/*
 *  USA      (mm-dd-yy)
 *  American (mm/dd/yy)
 *  British  (dd/mm/yy)
 *  German   (dd.mm.yy)
 *  Italian  (dd-mm-yy)
 *  Japanese (yy/mm/dd)
 *  ANSI     (yy.mm.dd)
 *  xBase    (YYYYMMDD)
 */

time_t shifttime(time_t timer, 
                 int diff //[min]
                 ) 
  {
  /* Surprisingly, there is no ANSI C function to do this */
  struct tm *lt = localtime(&timer);
  lt->tm_min += diff;
  timer = mktime(lt);
  return(timer);
}


#if 0 //TODO:

int
TimeSpan::Age(const zDate &birthday) const
{
      int age = m_year - birthday.m_year - 1;

      if( m_month > birthday.m_month ) age++;
      else if( m_month == birthday.m_month && m_day >= birthday.m_day ) age++;

      return age;
}
#endif

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  5    Biblioteka1.4         2004-10-06 22:43:03  Darko           Unicode fixes
 *  4    Biblioteka1.3         2003-09-27 11:06:41  Darko           draft v2
 *  3    Biblioteka1.2         2003-09-27 11:05:21  Darko           draft v2
 *  2    Biblioteka1.1         2003-09-23 16:09:02  Darko           draft
 *  1    Biblioteka1.0         2003-09-18 16:48:35  Darko           
 * $
 *****************************************************************************/

#if 0  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/* Represents a "Date" header */
class Date : public Base {

  public:
    Date() : Base(), t_ime(0)  {}
    Date(KNMimeContent *p) : Base(p), t_ime(0)  {}
    Date(KNMimeContent *p, time_t t) : Base(p), t_ime(t)  {}
    Date(KNMimeContent *p, const QCString &s) : Base(p)  { from7BitString(s); }
    Date(KNMimeContent *p, const QString &s) : Base(p)  { fromUnicodeString(s, Latin1); }
    ~Date()  {}

    virtual void from7BitString(const QCString &s);
    virtual QCString as7BitString(bool incType=true);
    virtual void fromUnicodeString(const QString &s, const QCString&);
    virtual QString asUnicodeString();
    virtual void clear()            { t_ime=0; }
    virtual bool isEmpty()          { return (t_ime==0); }
    virtual const char* type()      { return "Date"; }

    time_t unixTime()               { return t_ime; }
    void setUnixTime(time_t t)      { t_ime=t; }
    void setUnixTime()              { t_ime=time(0); }
    QDateTime qdt();
    int ageInDays();
    
  protected:
    time_t t_ime;

};

  void Date::from7BitString(const QCString &s)
{
  t_ime=KRFCDate::parseDate(s);
}


QCString Date::as7BitString(bool incType)
{
  if(incType)
    return ( typeIntro()+KRFCDate::rfc2822DateString(t_ime) );
  else
    return QCString(KRFCDate::rfc2822DateString(t_ime));
}


void Date::fromUnicodeString(const QString &s, const QCString&)
{
  from7BitString( QCString(s.latin1()) );
}


QString Date::asUnicodeString()
{
  return QString::fromLatin1(as7BitString(false));
}


QDateTime Date::qdt()
{
  QDateTime dt;
  dt.setTime_t(t_ime);
  return dt;
}


int Date::ageInDays()
{
  QDate today=QDate::currentDate();
  return ( qdt().date().daysTo(today) );
}

//-----</Date>---------------------------------

#endif //0 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#if 0  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//#include <qstring.h>
//#include <time.h>

/**
 * The KDate class contains functions related to the parsing of dates.
 *
 * @author Waldo Bastian <bastian@kde.org>
 */
class KRFCDate
{
public:
   /**
    * This function tries to parse a string containing a date/time in any
    * of the formats specified by RFC822, RFC850, RFC1036, RFC1123 and RFC2822.
    *
    * If the date/time could not be parsed, 0 is returned.  If the
    * parsed date is epoch, then epoch+1 is returned so that a valid
    * date will not be confused with an improper date string.
    *
    * The date/time returned is converted to UTC.
    *
    */
   static time_t parseDate(const QString &);


  /**
   * Returns the local timezone offset to UTC in seconds
   *
   */
   static int localUTCOffset();


  /**
   * Returns a string representation of the given date and time formated
   * in conformance to RFC2822.
   *
   * @param utcTime    a date and time in UTC
   * @param utcOffset  the offset to UTC in seconds
   *
   */

   static QCString rfc2822DateString(time_t utcTime, int utcOffset);


  /**
   * Returns a string representation of the given date and time formated
   * in conformance to RFC2822.
   *
   * Provided for convenience, the function is equivalent to
   * rfc2822DateString(t, localUTCOffset()).
   *
   * @param utcTime    a date and time in UTC
   *
   */

   static QCString rfc2822DateString(time_t utcTime);

};
//#include <config.h>

//#include <sys/param.h>
//#include <ctype.h>
//#include <stdlib.h>

//#include <krfcdate.h>

static unsigned int ymdhms_to_seconds(int year, int mon, int day, int hour, int minute, int second)
{
    unsigned int ret = (day - 32075)       /* days */
            + 1461L * (year + 4800L + (mon - 14) / 12) / 4
            + 367 * (mon - 2 - (mon - 14) / 12 * 12) / 12
            - 3 * ((year + 4900L + (mon - 14) / 12) / 100) / 4
            - 2440588;
    ret = 24*ret + hour;     /* hours   */
    ret = 60*ret + minute;   /* minutes */
    ret = 60*ret + second;   /* seconds */

    return ret;
}

static const char haystack[37]="janfebmaraprmayjunjulaugsepoctnovdec";

// we follow the recommendation of rfc2822 to consider all
// obsolete time zones not listed here equivalent to "-0000"
static const struct {
    const char *tzName;
    int tzOffset;
} known_zones[] = {
    { "UT", 0 },
    { "GMT", 0 },
    { "EST", -300 },
    { "EDT", -240 },
    { "CST", -360 },
    { "CDT", -300 },
    { "MST", -420 },
    { "MDT", -360 },
    { "PST", -480 },
    { "PDT", -420 },
    { 0, 0 }
};

time_t
KRFCDate::parseDate(const QString &_date)
{
     // This parse a date in the form:
     //     Wednesday, 09-Nov-99 23:12:40 GMT
     // or
     //     Sat, 01-Jan-2000 08:00:00 GMT
     // or
     //     Sat, 01 Jan 2000 08:00:00 GMT
     // or
     //     01 Jan 99 22:00 +0100    (exceptions in rfc822/rfc2822)
     //
     // We ignore the weekday
     //
     time_t result = 0;
     int offset = 0;
     char *newPosStr;
     const char *dateString = _date.latin1();
     int day = 0;
     char monthStr[4];
     int month = 0;
     int year = 0;
     int hour = 0;
     int minute = 0;
     int second = 0;

     while(*dateString && !isdigit(*dateString))
      dateString++;

     if (!*dateString)
      return result;  // Invalid date

     // ' 09-Nov-99 23:12:40 GMT'
     day = strtol(dateString, &newPosStr, 10);
     dateString = newPosStr;

     if ((day < 1) || (day > 31))
      return result; // Invalid date;
     if (!*dateString)
      return result;  // Invalid date

     if (*dateString == '-')
      dateString++;

     while(*dateString && isspace(*dateString))
      dateString++;

     for(int i=0; i < 3;i++)
     {
         if (!*dateString || (*dateString == '-') || isspace(*dateString))
              return result;  // Invalid date
         monthStr[i] = tolower(*dateString++);
     }
     monthStr[3] = '\0';

     newPosStr = (char*)strstr(haystack, monthStr);

     if (!newPosStr)
      return result;  // Invalid date

     month = (newPosStr-haystack)/3; // Jan=00, Feb=01, Mar=02, ..

     if ((month < 0) || (month > 11))
      return result;  // Invalid date

     while(*dateString && (*dateString != '-') && !isspace(*dateString))
      dateString++;

     if (!*dateString)
      return result;  // Invalid date

     // '-99 23:12:40 GMT'
     if ((*dateString != '-') && !isspace(*dateString))
      return result;  // Invalid date
     dateString++;

     // '99 23:12:40 GMT'
     year = strtol(dateString, &newPosStr, 10);
     dateString = newPosStr;

     // Y2K: Solve 2 digit years
     if ((year >= 0) && (year < 50))
         year += 2000;

     if ((year >= 50) && (year < 100))
         year += 1900;  // Y2K

     if ((year < 1900) || (year > 2500))
      return result; // Invalid date

     // Don't fail if the time is missing.
     if (*dateString)
     {
        // ' 23:12:40 GMT'
        if (!isspace(*dateString++))
           return result;  // Invalid date

        hour = strtol(dateString, &newPosStr, 10);
        dateString = newPosStr;

        if ((hour < 0) || (hour > 23))
           return result; // Invalid date

        if (!*dateString)
           return result;  // Invalid date

        // ':12:40 GMT'
        if (*dateString++ != ':')
           return result;  // Invalid date

        minute = strtol(dateString, &newPosStr, 10);
        dateString = newPosStr;

        if ((minute < 0) || (minute > 59))
           return result; // Invalid date

        if (!*dateString)
           return result;  // Invalid date

        // ':40 GMT'
        if (*dateString != ':' && !isspace(*dateString))
           return result;  // Invalid date

        // seconds are optional in rfc822 + rfc2822
        if (*dateString ==':') {
           dateString++;

           second = strtol(dateString, &newPosStr, 10);
           dateString = newPosStr;

           if ((second < 0) || (second > 59))
              return result; // Invalid date
        } else {
           dateString++;
        }

        while(*dateString && isspace(*dateString))
           dateString++;
     }

     // don't fail if the time zone is missing, some
     // broken mail-/news-clients omit the time zone
     if (*dateString) {

        if ((*dateString == '+') || (*dateString == '-')) {
           offset = strtol(dateString, &newPosStr, 10);

           if ((offset < -9959) || (offset > 9959))
              return result; // Invalid date

           int sgn = (offset < 0)? -1:1;
           offset = abs(offset);
           offset = ((offset / 100)*60 + (offset % 100))*sgn;
        } else {
           for (int i=0; known_zones[i].tzName != 0; i++) {
              if (0 == strncasecmp(dateString, known_zones[i].tzName, strlen(known_zones[i].tzName))) {
                 offset = known_zones[i].tzOffset;
                 break;
              }
           }
        }
     }
     if (sizeof(time_t) == 4)
     {
         if ((time_t)-1 < 0)
         {
            if (year >= 2038)
            {
               year = 2038;
               month = 0;
               day = 1;
               hour = 0;
               minute = 0;
               second = 0;
            }
         }
         else
         {
            if (year >= 2115)
            {
               year = 2115;
               month = 0;
               day = 1;
               hour = 0;
               minute = 0;
               second = 0;
            }
         }
     }

     result = ymdhms_to_seconds(year, month+1, day, hour, minute, second);

     // avoid negative time values
     if ((offset > 0) && (offset > result))
        offset = 0;

     result -= offset*60;

     // If epoch 0 return epoch +1 which is Thu, 01-Jan-70 00:00:01 GMT
     // This is so that parse error and valid epoch 0 return values won't
     // be the same for sensitive applications...     
     if (result < 1) result = 1;

     return result;
}


int KRFCDate::localUTCOffset()
{
  time_t timeNow = time((time_t*) 0);

  tm *tM = gmtime(&timeNow);
  unsigned int timeUTC = ymdhms_to_seconds(tM->tm_year+1900, tM->tm_mon+1, tM->tm_mday,
                                           tM->tm_hour, tM->tm_min, tM->tm_sec);

  tM = localtime(&timeNow);
  unsigned int timeLocal = ymdhms_to_seconds(tM->tm_year+1900, tM->tm_mon+1, tM->tm_mday,
                                             tM->tm_hour, tM->tm_min, tM->tm_sec);

  return ((int)(timeLocal-timeUTC))/60;
}

/*
static const char *day_names[] = {
    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};

static const char *month_names[] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};
*/

QCString KRFCDate::rfc2822DateString(time_t utcTime, int utcOffset)
{
    utcTime += utcOffset * 60;
    tm *tM = gmtime(&utcTime);
    char sgn = (utcOffset < 0) ? '-' : '+';
    int z = (utcOffset < 0) ? -utcOffset : utcOffset;
    QCString dateStr;

    dateStr.sprintf("%s, %02d %s %04d %02d:%02d:%02d %c%02d%02d",
                    day_names[tM->tm_wday], tM->tm_mday,
                    month_names[tM->tm_mon], tM->tm_year+1900,
                    tM->tm_hour, tM->tm_min, tM->tm_sec,
                    sgn, z/60%24, z%60);

    return dateStr;
}


QCString KRFCDate::rfc2822DateString(time_t utcTime)
{
    return rfc2822DateString(utcTime, localUTCOffset());
}

#endif //0 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#if 0  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//#ifndef _date_h_
//#define _date_h_
/*
 *
 *          Copyright (C) 1995, M. A. Sridhar
 *  
 *
 *     This software is Copyright M. A. Sridhar, 1995. You are free
 *     to copy, modify or distribute this software  as you see fit,
 *     and to use  it  for  any  purpose, provided   this copyright
 *     notice and the following   disclaimer are included  with all
 *     copies.
 *
 *                        DISCLAIMER
 *
 *     The author makes no warranties, either expressed or implied,
 *     with respect  to  this  software, its  quality, performance,
 *     merchantability, or fitness for any particular purpose. This
 *     software is distributed  AS IS.  The  user of this  software
 *     assumes all risks  as to its quality  and performance. In no
 *     event shall the author be liable for any direct, indirect or
 *     consequential damages, even if the  author has been  advised
 *     as to the possibility of such damages.
 *
 */
/*#ifdef __GNUC__
#pragma interface
#endif
*/

//#include "base/defs.h"
//#include "base/string.h"

//[ Global
// This class represents a particular date. Only dates on or after
// Sep 14, 1752 are permitted. The class provides for conversion to and from
// a string representation in one of the following forms, encoded by
// the {\tt DatePrintForm} enumeration, as illustrated below:
// \par\medskip{\tt \begin{tabular}{ll}
//            Date_American   &   October 17, 1992\\
//            Date_Terse      &   17-Oct-1992\\
//            Date_Numbers    &   10/17/92 \\
//            Date_European   &   17 October 1992\\
//            Date_EuroNumbers&   17/10/92\\
// \end{tabular}
// }\par\medskip
// \noindent
// By default, the Date class uses English names of the months and weekdays.
// The Date class supports some rudimentary internationalization. You
// can set the week-day and month names via static methods {\tt
// SetWeekdayNames}, {\tt SetMonthNames} and {\tt SetShortMonthNames}.
//
// As with other YACL classes, the methods that modify the Date object are
// declared virtual. They also provide notification support.
//enum DatePrintForm { Date_American, Date_Terse, Date_Numbers,
//                     Date_European, Date_EuroNumbers };
// {\tt DatePrintForm} is declared in global scope; it defines the different
// date formats.
//] Global
/*
class YACL_BASE  CL_Date: public CL_Object {

public:

    //[ Local
  / *
    enum MonthEnum { InvalidMonth = 0, January, February, March, April,
                     May, June, July, August, September, October,
                     November, December};

    enum WeekdayEnum {InvalidDay = 0, Sunday, Monday, Tuesday, Wednesday,
                      Thursday, Friday, Saturday};
   * /
    //] Local
    
    //
    // ------------- Constructors and destructors ----------------------
    //

    CL_Date ();
    // Construct a Date object containing an invalid date.

    CL_Date (short year, short month, short day);
    // Construct the given date, assuming that the year is given as 1992,
    // not 92, and the month is indexed from 1 (e.g. January is month 1).

    CL_Date (short year, const char* month, short day);
    // Construct the given date, assuming the month specified as a
    // string, e.g., {\tt March}. Assume case-sensitive comparison and
    // completely-specified month names (e.g. {\tt Oct} is not allowed). The
    // month must match one of the month names currently used; the set of
    // month names can be changed by the {\tt SetMonthNames} method.

    CL_Date (const char* s);
    // Construct a date from the given string containing the
    // representation, in one of the forms {\tt Date_American}, {\tt
    // Date_Terse} or {\tt Date_Numbers}.
    

    CL_Date (const CL_Date&);

    ~CL_Date ();

    //
    // ---------------------- Access ----------------------------------
    //

    bool IsLegal () const;
    // Is this a legal date?
    
    short Year() const;
    // Return our year.

    MonthEnum Month () const;
    // Return our month.

    short Day () const;
    // Return our day of month.

    WeekdayEnum DayOfWeek () const;
    // Return our day of week as a {\tt WeekdayEnum}.
    
    CL_String WeekdayName () const {return DayName (DayOfWeek());}
    // Return the name of the weekday of this Date.
    
    short DaysInMonth () const;
    // Return the number of days in our month.
    
    CL_String PrintString (DatePrintForm form = Date_American) const;
    // Return a printable form of this object, according to the
    // parameter.

    bool IsLeapYear () const;
    // Tell if this Date is in a leap year.

    CL_Date NextWeekday (const char* weekday_name) const;
    // Return the date of the next weekday given. For example, since July
    // 11, 1995 was a Tuesday, the expression
    // \par\begin{verbatim}
    //          CL_Date (1995, 7, 11).NextWeekday ("Monday")
    // \end{verbatim}
    // \par\noindent
    // returns a Date object containing July 17, 1995.
    //
    // The method returns an invalid Date if {\tt weekday_name} is not one
    // of the currently-recognized week-day names (as specified by the {\tt
    // SetWeekdayNames} method).
    

    CL_Date PreviousWeekday (const char* weekday_name) const;
    // Return the date of the previous weekday given. For example, since July
    // 11, 1995 was a Tuesday, the expression
    // \par\begin{verbatim}
    //          CL_Date (1995, 7, 11).PreviousWeekday ("Monday")
    // \end{verbatim}
    // \par\noindent
    // returns a Date object containing July 10, 1995.
    
    CL_Date NextWeekday (WeekdayEnum weekday_num) const;
    // Return the date of the next weekday given. For example, since July
    // 11, 1995 was a Tuesday, the expression
    // \par\begin{verbatim}
    //          CL_Date (1995, 7, 11).NextWeekday (CL_Date::Monday)
    // \end{verbatim}
    // \par\noindent
    // returns a Date object containing July 17, 1995.

    CL_Date PreviousWeekday (WeekdayEnum weekday_num) const;
    // Return the date of the previous weekday given.  For example, since July
    // 11, 1995 was a Tuesday, the expression
    // \par\begin{verbatim}
    //          CL_Date (1995, 7, 11).PreviousWeekday (CL_Date::Monday)
    // \end{verbatim}
    // \par\noindent
    // returns a Date object containing July 10, 1995.
    

    //
    // --------------------- Comparison ------------------------------
    //

    bool operator<  (const CL_Date& d) const
        {return _days < d._days ? TRUE : FALSE;};
    // Return TRUE if this Date is earlier than the parameter, and FALSE
    // otherwise.
    
    bool operator<= (const CL_Date& d) const
        {return _days <= d._days ? TRUE : FALSE;};
    // Return TRUE if this Date is earlier than or equal to the parameter,
    // and FALSE otherwise.
    
    bool operator>  (const CL_Date& d) const
        {return _days > d._days ? TRUE : FALSE;};
    // Return TRUE if this Date is later than the parameter, and FALSE
    // otherwise.

    bool operator>= (const CL_Date& d) const
        {return _days >= d._days ? TRUE : FALSE;};
    // Return TRUE if this Date is later than or equal to the parameter, and
    // FALSE otherwise.

    bool operator== (const CL_Date& d) const
        {return _days == d._days ? TRUE : FALSE;};
    // Return TRUE if this Date is equal to the parameter, and FALSE
    // otherwise.

    bool operator!= (const CL_Date& d) const
        {return _days != d._days ? TRUE : FALSE;};
    // Return TRUE if this Date is not equal to the parameter, and FALSE
    // otherwise.

    bool operator<  (const CL_Object& obj) const;
    // Cast down the parameter to a Date and use the Date-specific {\tt
    // operator<}.

    bool operator<= (const CL_Object& obj) const;
    // Cast down the parameter to a Date and use the Date-specific {\tt
    // operator<=}.

    bool operator>  (const CL_Object& obj) const;
    // Cast down the parameter to a Date and use the Date-specific {\tt
    // operator>}.

    bool operator>= (const CL_Object& obj) const;
    // Cast down the parameter to a Date and use the Date-specific {\tt
    // operator>=}.

    bool operator== (const CL_Object& obj) const;
    // Cast down the parameter to a Date and use the Date-specific {\tt
    // operator==}.

    bool operator!= (const CL_Object& obj) const;
    // Cast down the parameter to a Date and use the Date-specific {\tt
    // operator!=}.

    short Compare (const CL_Date&) const;
    // Return $-1$, 0 or $+1$ according to whether this Date is earlier
    // than, equal to or later than the parameter.

    short Compare (const CL_Object&) const;
    // Cast down the parameter to a Date and use the Date-specific {\tt
    // Compare} method. This overrides the inherited virtual method.

    bool IsBetween (const CL_Date& d1, const CL_Date& d2) const;
    // Return TRUE if this date is between the two given dates. The two
    // parameters need not be in ascending order.
    
    //
    // -------------------------- Modification ----------------------
    //

    // Assignment
    
    virtual void operator= (const CL_Date&);
    // Assign the given date to this object.

    virtual void operator= (const char*);
    // Assign our value from a string. The string must be in one of
    // the forms of Date_American, Date_Terse, or Date_Numbers, or
    // else must be six digits (characters) of the form yymmdd or
    // mmddyy. In the former three cases, the year can be either of
    // the form 92 or 1992.

    //
    // -------------------------- Date arithmetic -------------------
    //

    
    CL_Date  operator+  (short num_days) const;
    // Return the result of adding  {\tt num_days} days to this Date.

    virtual CL_Date& operator+= (short num_days);
    // Add  {\tt num_days} days to this Date. Return this Date.

    CL_Date  operator-  (short num_days) const;
    // Subtract {\tt num_days} days and return the result.

    virtual CL_Date& operator-= (short num_days);
    // Subtract {\tt num_days} days from this Date. Return this Date.

    long operator-   (const CL_Date& date) const;
    // Return the number of days between us and the given date (which
    // may be positive or negative).
    
    CL_Date AddMonths (short num_months) const;
    // Return the Date obtained by adding {\tt num_months} to this Date's
    // month. The parameter can be positive or negative.

    CL_Date AddYears (short num_years) const;
    // Return the Date obtained by adding {\tt num_years} to this Date's
    // year. The parameter can be positive or negative.

    //
    // --------------------- Static methods ---------------------------
    //

    static CL_Date Today ();
    // Return a Date with today's date in it.

    static CL_String DayName (WeekdayEnum weekday_num);
    // Return name of given weekday. For example, {\tt CL_Date::DayName
    // (CL_Date::Monday)} returns ``{\tt Monday}'' in the default English
    // setting. Returns the empty string if the parameter is invalid.

    static WeekdayEnum  DayNumber (const char* weekday_name);
    // Return the week-day with name {\tt weekday_name}. 

    static CL_String MonthName (short month_num);
    // Return month name of given month (1 = ``{\tt January},'' etc.).
    // Return the empty String for an invalid month number.

    static CL_String ShortMonthName (short month_num);
    // Return the short (3-character) month name of given month.
    // Return the empty string for an invalid month number. 

    static MonthEnum MonthNumber (const char* month_name);
    // Return the month with name {\tt month_name}. Return $-1$ for an
    // invalid month name.

    static bool IsLeapYear (short year);
    // Return TRUE if {\tt year} is a leap year, and FALSE otherwise.

    static short DaysInMonth  (short month, short year);
    // Return the number of days in the given month and year. For example,
    // {\tt CL_Date::DaysInMonth (2, 1996)} returns 29.
    
    static long ParseAndConvert (const char* date);
    // Validate the given string as representing a date, and return
    // either $-1$ if it's not a valid date, and a positive value otherwise.
    // (This return value can be used to construct a Date object.). The
    // string must be in one of
    // the forms of Date_American, Date_Terse, or Date_Numbers, or
    // else must be six digits (characters) of the form yymmdd or
    // mmddyy. In the former three cases, the year can be either of
    // the form 92 or 1992, and the month names can be mixed case. In the
    // case of six digits of the form yymmdd, the year must be 13 or
    // greater, indicating the year 1913 or later.


    static bool SetMonthNames (char* month_names[12]);
    // Set the names of the months to be used by the Date class. This is for
    // rudimentary support of internationalization. This method need be
    // called only once in an application. If it is not called, the English
    // versions of the month names are used.
    //
    // The method returns TRUE on success, FALSE if the parameter did not
    // have twelve non-null pointers.
    //
    // The implementation simply copies the
    // passed pointers into a local data structure; so the storage for the
    // character strings is still owned by the caller of this method.

    static bool SetShortMonthNames (char* month_names[12]);
    // Set the short (typically 3-character) names of the months to be used
    // by the Date class. This is for rudimentary support of
    // internationalization. This method need be
    // called only once in an application. If it is not called, the English
    // versions of the short month names are used.
    //
    // The method returns TRUE on success, FALSE if the parameter did not
    // have twelve non-null pointers.
    //
    // The implementation simply copies the
    // passed pointers into a local data structure; so the storage for the
    // character strings is still owned by the caller of this method.

    static bool SetWeekdayNames (char* day_names[7]);
    // Set the names of the week days to be used by the Date class. This is for
    // rudimentary support of internationalization. This method need be
    // called only once in an application. If it is not called, the English
    // versions of the week-day names are used.
    //
    // The method returns TRUE on success, FALSE if the parameter did not
    // have seven non-null pointers.
    //
    // The implementation simply copies the
    // passed pointers into a local data structure; so the storage for the
    // character strings is still owned by the caller of this method.

    
    // ----------------------- Storage and restoration ----------------
    
    CL_String AsString () const
        { return PrintString (Date_Numbers);};
    // Return a String that contains this Date's value in {\tt Date_Numbers}
    // form. This method overrides the method inherited from Object.


    void FromStream (istream& strm);
    // Overrides the method inherited from Object. The
    // implementation skips fill characters, and then collects slashes,
    // dashes, and alphabetic and numeric 
    // characters and attempts to parse the result as a date. If successful,
    // this date is modified; otherwise, the collected characters are put
    // back and this date becomes invalid.
    
    long StorableFormWidth () const;
    // Overrides the method inherited from Object.

    bool ReadFrom (const CL_Stream&);
    // Overrides the method inherited from Object.

    bool WriteTo  (CL_Stream&) const;
    // Overrides the method inherited from Object.


    // -------------------------- Assignment ------------------------
    

    virtual void operator= (const CL_Object&);
    // Overrides the method inherited from Object.

    // ------------------------ Basic methods ----------------------
    
    const char* ClassName() const { return "CL_Date";};
    // Overrides the method inherited from Object. Returns the
    // string ``{\tt CL_Date}.''
    
    CL_ClassId ClassId () const {return _CL_Date_CLASSID;};
    // Overrides the method inherited from Object.

    CL_Object* Clone() const {return new CL_Date (*this);};
    // Overrides the method inherited from Object.


    
protected:

    // The representation used is the number of days since Jan 1,
    // 1752??
    long _days;
    
    CL_Date (long num_days);
    
};




inline void CL_Date::operator= (const CL_Object& obj)
{
    if (CheckClassType (obj, "CL_Date::op= (CL_Object&)"))
        *this = (const CL_Date&) obj;
}



inline short CL_Date::Compare (const CL_Object& obj) const
{
    return !IsA(obj) ? (this < (CL_Date*) &obj ? -1 :  1) 
        : Compare ((const CL_Date&) obj);
}


inline bool CL_Date::IsLegal () const
{
    return _days > 0;
}

#endif
*/
/*
#include "base/date.h"
#include "base/error.h"
#include "base/bytstrng.h"
#include "base/stream.h"

#include <iostream.h>
#include <ctype.h>

#include <time.h>
#ifdef MSDOS
#include <dos.h>
#endif


#if defined(__SGI_DELTA_CC__)
#include "base/basicops.h"
#include "base/cmparatr.h"
#pragma instantiate CL_Comparator<CL_Date>
#pragma instantiate CL_Basics<CL_Date>
#endif

*/
// A few static (local) helper functions: IntoDays and IntoYMD
/*
struct DateStruct {
    short y,d;
    CL_Date::MonthEnum m;
};

static DateStruct IntoYMD (long num_days);
static long       IntoDays (const DateStruct&);
*/
/*
static char* months [12] = {
    "January", "February", "March", "April", "May", "June", "July",
    "August", "September", "October", "November", "December"
    };

static char* short_months [12] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul",
    "Aug", "Sep", "Oct", "Nov", "Dec"
    };

static char* week_day [7] = {
    "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday",
    "Saturday"
    };

static short month_days[12] = {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };

*/

/*
bool CL_Date::SetMonthNames (char* month_names[12])
{
    for (short i = 0; i < 12; i++) {
        if (!month_names[i])
            return FALSE;
        months[i] = month_names[i];
    }
    return TRUE;
}
    

bool CL_Date::SetShortMonthNames (char* month_names[12])
{
    for (short i = 0; i < 12; i++) {
        if (!month_names[i])
            return FALSE;
        short_months[i] = month_names[i];
    }
    return TRUE;
}

bool CL_Date::SetWeekdayNames (char* day_names[7])
{
    for (short i = 0; i < 7; i++) {
        if (!day_names[i])
            return FALSE;
        week_day[i] = day_names[i];
    }
    return TRUE;
}

*/
//
// ------------- Constructors and destructors ----------------------
//

// Construct today's date
/*CL_Date::CL_Date ()
{
    _days = 0;
}
*/

/*---------------------------------------------------*/

// Construct the given date, assuming that:
//        the year is given as 1992, not 92
//        the month is indexed from 1 (e.g. January is month 1)
CL_Date::CL_Date (short year, short month, short day)
{
    if (year < 1752) {
        // CL_Error::Warning ("CL_Date constructor: invalid year %d", year);
        _days = 0;
        return;
    }
    if (!(month >= January && month <= December)) {
        // CL_Error::Warning ("CL_Date constructor: invalid month %d", month);
        _days = 0;
        return;
    }
    if (day < 1 || day > DaysInMonth (month, year)) {
        // CL_Error::Warning ("CL_Date constructor: invalid day %d", day);
        _days = 0;
        return;
    }
    
    DateStruct dt;
    dt.y = year;
    dt.m = (MonthEnum) month;
    dt.d = day;
    _days = IntoDays (dt);
}


/*---------------------------------------------------*/
/*

// Construct the given date, assuming the month specified as a
// string, e.g., "March". Assume case-sensitive comparison and
// completely-specified month names (e.g. "Oct" is not allowed).
CL_Date::CL_Date (short year, const char* month, short day)
{
    DateStruct dt;
    dt.y = year;
    dt.m = MonthNumber (month);
    dt.d = day;
    if (year < 1752) {
        // CL_Error::Warning ("CL_Date constructor: invalid year %d", year);
        _days = 0;
        return;
    }
    if (!(dt.m >= January && dt.m <= December)) {
        // CL_Error::Warning ("CL_Date constructor: invalid month %d", dt.m);
        _days = 0;
        return;
    }
    if (day < 1 || day > DaysInMonth (dt.m, year)) {
        // CL_Error::Warning ("CL_Date constructor: invalid day %d", day);
        _days = 0;
        return;
    }
    
    _days = IntoDays (dt);
}

*/
/*---------------------------------------------------*/

// Construct a date from the given string containing the
// representation in one of the allowed forms.
/*
CL_Date::CL_Date (const char* s)
{
    *this = s;
}

void CL_Date::operator= (const char* p)
{
    if (!PrepareToChange())
        return;
    CL_String s(p);
    if (s.Size() == 0) {
        _days = 0;
        Notify ();
        return;
    }
    long d = ParseAndConvert (s);
    if (d < 0) {
        _days = 0;
        Notify ();
        return;
    }
    _days = d;
    Notify ();
}
*/


long CL_Date::ParseAndConvert (const char* strg)
{
    CL_String s (strg);
    CL_String fld[4];
    DateStruct dt;

    if (s.Split (fld, 4, " ,") == 3) { // Date_American
        long l;
        
        fld[0].WordCapitalize ();
        dt.m = MonthNumber (fld[0]);
        short yr = fld[2].ConvertToLong (l) ? (short) l : (short) -1;
        dt.y = (yr >= 1752) ? yr : yr + 1900;
        dt.d = fld[1].ConvertToLong (l) ? (short) l : (short) -1;
    }
    else if (s.Split (fld, 4, "-") == 3) { // Date_Terse
        long l;

        fld[1].WordCapitalize ();
        dt.m = MonthNumber (fld[1]);
        short yr = fld[2].ConvertToLong (l) ? (short) l : (short) -1;
        dt.y = (yr >= 1752) ? yr : yr + 1900;
        dt.d = fld[0].ConvertToLong (l) ? (short) l : (short) -1;
    }
    else if (s.Split (fld, 4, "/") == 3) {// Date_Numbers
        long l;

        dt.m = (MonthEnum) (fld[0].ConvertToLong(l) ? l : -1);
        dt.d = fld[1].ConvertToLong(l) ? (short) l : (short) -1;
        short y = fld[2].ConvertToLong (l) ? (short) l : (short) -1;
        dt.y = y;
        if (dt.y <= 99)
            dt.y += 1900;
    }
    else {
        // Assume that it's six digits, and try to parse it.
        if (s.Size() != 6) {
            return -1;
        }
        for (short i = 0; i < 6; i++) {
            if (s[i] > '9' || s[i] < '0') {
                return -1;
            }
        }
        short f1 = (s[0]-'0')*10 + s[1]-'0';
        short f2 = (s[2]-'0')*10 + s[3]-'0';
        short f3 = (s[4]-'0')*10 + s[5]-'0';
        if (f1 >= 13) { // Assume yymmdd
            dt.m = (MonthEnum) f2;
            dt.y = f1 + 1900;
            dt.d = f3;
        }
        else { // Assume mmddyy
            dt.m = (MonthEnum) f1;
            dt.y = f3 + 1900;
            dt.d = f2;
        }
    }
    if (dt.m <= 0 || dt.m >= 13) {
        return -1;
    }
    if (dt.y <= 1751) {
        return -1;
    }
    if (dt.d <= 0 || dt.d >= 32) {
        return -1;
    }
    
    return IntoDays (dt);
}
/*---------------------------------------------------*
// Copy constructor
CL_Date::CL_Date (const CL_Date& d)
{
    _days = d._days;
}

// Destructor
CL_Date::~CL_Date ()
{
}
*---------------------------------------------------*/

//
// ---------------------- Access ----------------------------------

// Return our year
/*short CL_Date::Year() const
{
    return IntoYMD (_days).y;
}
*---------------------------------------------------*/
/*
// Return our month
CL_Date::MonthEnum CL_Date::Month () const
{
    return IntoYMD (_days).m;
}
*---------------------------------------------------*/
// Return our day of month
/*short CL_Date::Day () const
{
    return IntoYMD (_days).d;
}
*---------------------------------------------------*/
// Return our day of week. Assume that 1 is for Sunday and 7 for
// Saturday.
/*CL_Date::WeekdayEnum CL_Date::DayOfWeek () const
{
    return (WeekdayEnum) (((1 + _days) % 7) + 1);
}
*/

/*---------------------------------------------------*

short CL_Date::DaysInMonth () const
{
    DateStruct dt = IntoYMD (_days);
    return DaysInMonth (dt.m, dt.y);
}

*---------------------------------------------------*/
/*
CL_String CL_Date::PrintString (DatePrintForm form) const
{
    if (_days == 0) // Invalid date
        return "";
    DateStruct dt = IntoYMD (_days);

    CL_String s, t;
    switch (form) {

    case Date_American:
        s =  MonthName (dt.m);
        t.AssignWithFormat ("%s %d, %d", s.AsPtr(), dt.d, dt.y); 
        return t;

    case Date_Terse:
        s =  ShortMonthName (dt.m);
        t.AssignWithFormat ("%02d-%s-%02d", dt.d, s.AsPtr(), dt.y); 
        return t;

    case Date_Numbers:
        t.AssignWithFormat ("%02d/%02d/%02d", dt.m, dt.d,
                            (dt.y >= 0 && dt.y <= 1999) ? (dt.y - 1900)
                            : dt.y); 
        return t;

    case Date_European:
        s = MonthName (dt.m);
        t.AssignWithFormat ("%d %s %d", dt.d, s.AsPtr(), dt.y);
        return t;

    case Date_EuroNumbers:
        t.AssignWithFormat ("%02d/%02d/%02d", dt.d, dt.m,
                            (dt.y >= 0 && dt.y <= 1999) ? (dt.y - 1900)
                            : dt.y); 
        return t;

    default:
        // CL_Error::Warning ("CL_Date::PrintString: Invalid form %d", form);
        return "";
    }
}
*/

/*---------------------------------------------------*/



void CL_Date::FromStream (istream& s)
{
    CL_String rep;
    char c;
    long count = 0;
    
    char fill_char = s.fill ();
    
    while (s.get (c) && c == fill_char);
    if (!s.good() || s.eof()) {
        _days = 0;
        return;
    }
    do {
        if (isalnum (c) || c == '/' || c == '-') {
            rep.Append (c);
            count++;
        }
        else
            break;
    } while (s.get (c));

    long n = ParseAndConvert (rep);
    if (n > 0) {
        if (!s.eof ())
            s.putback (c);
        _days = n;
    }
    else {
        s.seekg (s.tellg() - count, istream::cur);
        _days = 0;
    }
}

/*---------------------------------------------------*
// Tell if ours is a leap year

bool CL_Date::IsLeapYear () const
{
    return IsLeapYear (IntoYMD (_days).y);
}

*---------------------------------------------------*
// Return the date of the next weekday given

CL_Date CL_Date::NextWeekday (const char* weekday_name) const
{
    short incr = DayNumber (weekday_name) - DayOfWeek();
    return CL_Date (_days + ((incr >= 0) ? incr : incr + 7));
}
*---------------------------------------------------*
// Return the date of the previous weekday given
CL_Date CL_Date::PreviousWeekday (const char* weekday_name) const
{
    short incr = DayNumber (weekday_name) - DayOfWeek();
    return CL_Date (_days - ((incr > 0) ? 7 - incr : -incr));
}
CL_Date CL_Date::NextWeekday (WeekdayEnum weekday_num) const
{
    short incr = weekday_num - DayOfWeek();
    return CL_Date (_days + ((incr >= 0) ? incr : incr + 7));
}

*---------------------------------------------------*
// Return the date of the previous weekday given

CL_Date CL_Date::PreviousWeekday (WeekdayEnum weekday_num) const
{
    short incr = weekday_num - DayOfWeek();
    return CL_Date (_days - ((incr > 0) ? 7 - incr : -incr));
}
*/


//
// -------------------------- Modification ----------------------
//

// Assignment
/*
void CL_Date::operator= (const CL_Date& d)
{
    if (this == &d)
        return;
    if (!PrepareToChange())
        return;
    _days = d._days;
    Notify ();   // Notify all our clients
}
// -------------------------- Date arithmetic -------------------
//


// add or subtract the given number of days

CL_Date  CL_Date::operator+  (short num_days) const
{
    return CL_Date (_days + num_days);
}


*---------------------------------------------------*

CL_Date& CL_Date::operator+= (short num_days) 
{
    if (!PrepareToChange())
        return *this;
    _days += num_days;
    Notify();
    return *this;
}


CL_Date  CL_Date::operator-  (short num_days) const
{
    return CL_Date (_days - num_days);
}


CL_Date& CL_Date::operator-= (short num_days)
{
    if (!PrepareToChange())
        return *this;
    _days -= num_days;
    Notify();
    return *this;
}



*---------------------------------------------------*/
/*
// Return the number of days between us and the given date (which
// may be positive or negative)
long CL_Date::operator-   (const CL_Date& date) const
{
    return _days - date._days;
}


CL_Date CL_Date::AddMonths (short num_months) const
{
    DateStruct dt = IntoYMD (_days);
    long new_months = dt.y * 12 + dt.m + num_months - 1;
    short ny = new_months / 12;
    if (ny < 1901) {
        CL_Error::Warning ("CL_Date::AddMonths: parameter %d too large",
                           num_months);
        return *this;
    }
    MonthEnum nm = (MonthEnum) (new_months % 12 + 1);
    return CL_Date (ny, nm, minl (dt.d, CL_Date::DaysInMonth (nm, ny)));
}


        
CL_Date CL_Date::AddYears (short num_years) const
{
    DateStruct dt = IntoYMD (_days);
    return CL_Date (dt.y + num_years, dt.m, dt.d);
}

*/

/*

//
// --------------------- Static methods ---------------------------
//

#if defined (__GNUC__)
extern "C" time_t time (time_t*);
#endif

CL_Date CL_Date::Today ()
{
    time_t timer;
    struct tm *tblock;
    DateStruct dt;

    timer = time ((time_t*) NULL);
    tblock = localtime (&timer);
    dt.y = tblock->tm_year + 1900; 
    dt.m = (MonthEnum) (tblock->tm_mon + 1); // Correct for 0-11
    dt.d = tblock->tm_mday;
    return CL_Date (IntoDays (dt));
}
*/
/*

// Return name of given weekday (1 = "Sunday", ..., 7 = "Saturday")
CL_String CL_Date::DayName (WeekdayEnum weekday_num)
{
    if (Sunday <= weekday_num && weekday_num <= Saturday)
        return CL_String (week_day [weekday_num - Sunday]);
    else return "";
}
*/

/*---------------------------------------------------


// Do the opposite of the above:
CL_Date::WeekdayEnum  CL_Date::DayNumber (const char* weekday)
{
    CL_String weekday_name (weekday);
    for (short i = 0; i < 7; i++) {
        if (weekday_name == week_day[i]) return (WeekdayEnum) (i+1);
    }
//     CL_Error::Warning ("CL_Date::DayNumber: Invalid weekday name '%s'",
//                      (const char*) weekday_name);
    return InvalidDay;
}

// Return month name of given month (1 = "January", etc.)
CL_String CL_Date::MonthName (short month_num)
{
    return (month_num >= 1 && month_num <= 12) ?
        months[month_num-1] : "";
}

CL_String CL_Date::ShortMonthName (short month_num)
{
    return (month_num >= 1 && month_num <= 12) ? 
        (short_months[month_num-1]) : ""; 
}

// And the opposite of the above:
CL_Date::MonthEnum CL_Date::MonthNumber (const char* month)
{
    CL_String month_name (month);
    short i;
    for (i = 0; i < 12; i++) {
        if (month_name == months[i]) return (MonthEnum) (i+1);
    }
    for (i = 0; i < 12; i++) {
        if (month_name == short_months[i]) return (MonthEnum) (i+1);
    }
    return InvalidMonth;
}

*/
/*---------------------------------------------------*/
/*
// Is the given year a leap year?
bool CL_Date::IsLeapYear (short year)
{
    return (year % 4) == 0 && ((year % 100) != 0 || (year % 400) == 0);
}

*/

/*---------------------------------------------------*/
/*

long CL_Date::StorableFormWidth () const
{
    return sizeof (CL_ClassId) + sizeof (long);
}


bool CL_Date::ReadFrom (const CL_Stream& s)
{
    if (!PrepareToChange() || !ReadClassId (s) ||
        !s.Read (_days))
        return FALSE;
    Notify();
    return TRUE;
}



bool CL_Date::WriteTo (CL_Stream& s) const
{
    return s.Write (ClassId())  && s.Write (_days);
}




bool CL_Date::operator<  (const CL_Object& obj) const
{
    if (!IsA (obj))
        return FALSE;
    return operator< ((const CL_Date&) obj);
}


bool CL_Date::operator<= (const CL_Object& obj) const
{
    if (!IsA (obj))
        return FALSE;
    return operator<= ((const CL_Date&) obj);
}


bool CL_Date::operator>  (const CL_Object& obj) const
{
    if (!IsA (obj))
        return FALSE;
    return operator> ((const CL_Date&) obj);
}


bool CL_Date::operator>= (const CL_Object& obj) const
{
    if (!IsA (obj))
        return FALSE;
    return operator>= ((const CL_Date&) obj);
}


bool CL_Date::operator== (const CL_Object& obj) const
{
    if (!IsA (obj))
        return FALSE;
    return operator== ((const CL_Date&) obj);
}


bool CL_Date::operator!= (const CL_Object& obj) const
{
    if (!IsA (obj))
        return FALSE;
    return operator!= ((const CL_Date&) obj);
}



short CL_Date::Compare (const CL_Date& d) const
{
    return _days < d._days ? -1 : (_days == d._days ? 0 : 1);
}



bool CL_Date::IsBetween  (const CL_Date& d1, const CL_Date& d2) const
{
    return _days >= minl (d1._days, d2._days) &&
        _days <= maxl (d1._days, d2._days);
}




// Protected methods

CL_Date::CL_Date (long num_days)
{
    _days = num_days;
}
*/
//
// Helper functions
//

/*
short CL_Date::DaysInMonth (short month, short year)
{
    if (month != February || ! CL_Date::IsLeapYear (year))
        return (month >= January && month <= December)
            ? month_days[month-1] : -1;
    else
        return 29;
}
*/
/*
static DateStruct IntoYMD (long nDays)
{
    // This algorithm is based on Algorithm 199, CACM, Aug 1963. The
    // algorithm is not valid for dates before Sep 14, 1752.
    ulong d;
    ulong j = nDays - 1721119L;
    DateStruct retVal;
    ulong mo, da, y;
    y = (((j<<2) - 1) / 146097L);
    j = (j<<2) - 1 - 146097L*y;
    d = (j>>2);
    j = ((d<<2) + 3) / 1461;
    d = (d<<2) + 3 - 1461*j;
    d = (d + 4)>>2;
    mo = (5*d - 3)/153;
    d  = 5*d - 3 - 153*mo;
    da = ((d + 5)/5);
    y  = (100*y + j);
    if (mo < 10)
        mo += 3;
    else {
        mo -= 9;
        y ++;
    }
    retVal.y = y;
    retVal.d = da;
    retVal.m = (CL_Date::MonthEnum) mo;
    return retVal;
}

static long       IntoDays  (const DateStruct& s)
{
    // This algorithm is based on Algorithm 199, CACM, Aug 1963. The
    // algorithm is not valid for dates before Sep 14, 1752.
    DateStruct t = s;
    if (t.y <= 99)
        t.y += 1900;
    if (s.d <= 0 || s.d > CL_Date::DaysInMonth (s.m, s.y))
        return -1;
        
    if (t.m > 2)        
        t.m = (CL_Date::MonthEnum) (t.m - 3);
    else {
        t.m = (CL_Date::MonthEnum) (t.m + 9);
        t.y--;
    } 
    ulong c  = t.y / 100;
    ulong yy = t.y - 100*c;
    return ((146097L * c)>>2) + ((1461*yy)>>2) + (153*t.m + 2)/5 + t.d
        + 1721119L;
}

*/

// Old code:
// static DateStruct IntoYMD   (long num_days)
// {
//     DateStruct date;
//     long temp_days;
// 
//     temp_days = num_days - (num_days / 1460)   
//                          + (num_days / 36500L)
//                          - (num_days / 146000L);
// 
//     date.y = (short) (temp_days / 365);
//     num_days -= (date.y * 365L) + (date.y / 4) - date.y/100 + date.y /
//         400;
//     date.y += 1901;
//     num_days++; // Correct for: Jan 1, 1901 has days = 0
//     // Set number of days for February
//     short i;
//     for (i = 1; i <= 12; i++) {
//         short ndays = CL_Date::DaysInMonth (i, date.y);
//         if (num_days > ndays)
//             num_days -= ndays;
//         else {
//             date.m = (CL_Date::MonthEnum) i;
//             date.d = (short) num_days;
//             break;
//         }
//     }
//     return date;
// }
// static long       IntoDays  (const DateStruct& s)
// {
//     long n, p;
//     short i;
// 
//     if (s.m < CL_Date::January || s.m > CL_Date::December)
//         return 0;
//     if (s.y < 1901 || s.y > 10000) // Wonder if this library will be around
//                                    // after 10,000 AD? <grin>
//         return 0;
//     if (s.d <= 0 || s.d > CL_Date::DaysInMonth (s.m, s.y))
//         return 0;
//     for (i = 1, p = 0; i <= ((short) s.m) - 1; ((short&) i)++)
//         p += CL_Date::DaysInMonth (i, s.y);
//     n =  (s.y - 1901L) * 365 + p + s.d - 1;
//         // Jan 1, 1901 gives 0 days
//     n += (s.y - 1901L) / 4 + 3 * (s.y - 1901L) / 400;
//         // Add number of leap years between 1901 and s.y
//     return n;
// }


/*
#if defined(__GNUC__) && __GNUC_MINOR__ >= 6
#include "base/binding.h"
#include "base/cmparatr.cxx"

template class CL_Binding0<CL_Date>;
template class CL_Comparator<CL_Date>;
template class CL_Basics<CL_Date>;
#endif
*/
#endif //0 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#if 0  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/*
 * This file is part of PB-Lib C/C++ Library
 *
 * Copyright (c) 1995, 1996 Branislav L. Slantchev
 * A Product of Silicon Creations, Inc.
 *
 * This class is hereby donated to the SNIPPETS collection (maintained
 * by Bob Stout). You are granted the right to use the code contained
 * herein free of charge as long as you keep this copyright notice intact.
 *
 * Contact: 73023.262@compuserve.com
*/
//#ifndef __DATE_INC
//#define __DATE_INC

/*
typedef unsigned long ulong;
typedef enum { False, True } Boolean;
#include <time.h>
*/
class zDate
{
public:
  //    enum month {
  //          jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
  //    };

  //    enum week_day {
    //        mon = 1, tue, wed, thu, fri, sat, sun
    //  };

   //   enum moon_phase {
    //        new_moon, waxing_crescent, first_quater, waxing_gibbous,
    //        full_moon, waning_gibbous, third_quater, waning_crescent
   //   };

      zDate();
      zDate(month month, int day, int year);
      zDate(int dayOfYear, int year);
      zDate(const zDate &aDate);
      zDate(ulong nDayNumber);
      zDate(const struct tm *date);

      zDate             AddMonths(int nMonths) const;
      zDate             AddWeeks(int nWeeks) const;
      zDate             AddYears(int nYears) const;
      int               Age(const zDate &aDate) const;
      zDate             BeginDST() const;
      static zDate      BeginDST(int aYear);
      int               Day() const;
      ulong             DayNumber() const;
      week_day          DayOfWeek() const;
      int               DayOfYear() const;
      int               DaysInMonth() const;
      static int        DaysInMonth(month aMonth, int aYear);
      int               DaysInYear() const;
      static int        DaysInYear(int year);
      zDate             Easter() const;
      static zDate      Easter(int year);
      zDate             EndDST() const;
      static zDate      EndDST(int aYear);
      Boolean           IsDST() const;
      static Boolean    IsDST(const zDate &date);
      Boolean           IsLeapYear() const;
      static Boolean    IsLeapYear(int year);
      Boolean           IsValid() const;
      static Boolean    IsValid(month aMonth, int aDay, int aYear);
      month             Month() const;
      moon_phase        MoonPhase() const;
      static moon_phase MoonPhase(const zDate &date);
                                operator long() const;
      Boolean           operator!=(const zDate &aDate) const;
      zDate             operator+(int nDays) const;
      zDate             operator+(long nDays) const;
      zDate             operator++();
      zDate             operator++(int);
      zDate&            operator+=(int nDays);
      zDate&            operator+=(long nDays);
      long              operator-(const zDate &aDate) const;
      zDate             operator-(int nDays) const;
      zDate             operator-(long nDays) const;
      zDate             operator--();
      zDate             operator--(int);
      zDate&            operator-=(int nDays);
      zDate&            operator-=(long nDays);
      Boolean           operator<(const zDate &aDate) const;
      Boolean           operator<=(const zDate &aDate) const;
      zDate&            operator=(const zDate &aDate);
      Boolean           operator==(const zDate &aDate) const;
      Boolean           operator>(const zDate &aDate) const;
      Boolean           operator>=(const zDate &aDate) const;
      char              operator[](int index) const;
      static void       SetBeginDST(month aMonth, week_day aWeekDay);
      static void       SetEndDST(month aMonth, week_day aWeekDay);
      static zDate      Today();
      int               WeekOfMonth() const;
      int               WeekOfYear() const;
      int               WeeksInYear() const;
      static int        WeeksInYear(int year);
      int               Year() const;

      // Pope Gregor XIII's reform cancelled 10 days:
      // the day after Oct 4 1582 was Oct 15 1582
      static const int      ReformYear;
      static const month    ReformMonth;
      static const ulong    ReformDayNumber;

protected:
      // Daylight Savings Time Month and Day of Week
      static month    BeginDSTMonth;
      static week_day BeginDSTDay;
      static month    EndDSTMonth;
      static week_day EndDSTDay;

protected:
      zDate Set(month aMonth, int aDay, int aYear);
      ulong MakeDayNumber() const;
      void  FromDayNumber(ulong nDayNumber);

private:
      month m_month;
      int   m_day;
      int   m_year;
      ulong m_dayno;
};

/*
 * inline functions that belong to the zDate class
*/
/*
inline int
zDate::Year() const
{
      return m_year;
}

inline int
zDate::Day() const
{
      return m_day;
}

inline zDate::month
zDate::Month() const
{
      return m_month;
}

inline ulong
zDate::DayNumber() const
{
      return m_dayno;
}
*/
//#endif /* __DATE_INC */

// +++Date last modified: 05-Jul-1997

/*
 * This file is part of PB-Lib C/C++ Library
 *
 * Copyright (c) 1995, 1996 Branislav L. Slantchev
 * A Product of Silicon Creations, Inc.
 *
 * This class is hereby donated to the SNIPPETS collection (maintained
 * by Bob Stout). You are granted the right to use the code contained
 * herein free of charge as long as you keep this copyright notice intact.
 *
 * Contact: 73023.262@compuserve.com
*/
//#include "date.hpp"

const int             zDate::ReformYear      = 1582;
const ulong           zDate::ReformDayNumber = 577737L;
const zDate::month    zDate::ReformMonth     = zDate::oct;
        zDate::week_day zDate::BeginDSTDay     = zDate::sun;
        zDate::month    zDate::BeginDSTMonth   = zDate::apr;
        zDate::week_day zDate::EndDSTDay       = zDate::sun;
        zDate::month    zDate::EndDSTMonth     = zDate::oct;

zDate::zDate()
{
      Set(jan, 1, 1);
}

zDate::zDate(month aMonth, int aDay, int aYear)
{
      Set(aMonth, aDay, aYear);
}

zDate::zDate(int dayOfYear, int year)
{
      m_day   = 31;
      m_month = dec;
      m_year  = year - 1;
      m_dayno = MakeDayNumber();
      FromDayNumber(m_dayno + dayOfYear);
}

zDate
zDate::Set(month aMonth, int aDay, int aYear)
{
      m_month = aMonth;
      m_day   = aDay;
      m_year  = aYear;
      m_dayno = MakeDayNumber();

      return *this;
}

zDate::zDate(const zDate &aDate)
{
      m_month = aDate.m_month;
      m_day   = aDate.m_day;
      m_year  = aDate.m_year;
      m_dayno = aDate.m_dayno;
}

zDate::zDate(ulong nJulian)
{
      FromDayNumber(nJulian);
}

zDate::zDate(const struct tm *tmDate)
{
      m_month = (month)(tmDate->tm_mon + 1);
      m_day   = tmDate->tm_mday;
      m_year  = tmDate->tm_year + 1900;
      m_dayno = MakeDayNumber();
}

zDate
zDate::Today()
{
      time_t     secs_now = time(0);
      struct tm *time_now = localtime(&secs_now);
      zDate      today(time_now);

      return today;
}

Boolean
zDate::operator!=(const zDate &aDate) const
{
      return Boolean(m_dayno != aDate.m_dayno);
}

Boolean
zDate::operator==(const zDate &aDate) const
{
      return Boolean(m_dayno == aDate.m_dayno);
}

Boolean
zDate::operator<(const zDate &aDate) const
{
      return Boolean(m_dayno < aDate.m_dayno);
}

Boolean
zDate::operator<=(const zDate &aDate) const
{
      return Boolean(m_dayno <= aDate.m_dayno);
}

Boolean
zDate::operator>(const zDate &aDate) const
{
      return Boolean(m_dayno > aDate.m_dayno);
}

Boolean
zDate::operator>=(const zDate &aDate) const
{
      return Boolean(m_dayno >= aDate.m_dayno);
}

zDate&
zDate::operator=(const zDate &aDate)
{
      m_day   = aDate.m_day;
      m_month = aDate.m_month;
      m_year  = aDate.m_year;
      m_dayno = aDate.m_dayno;

      return *this;
}

int
zDate::DaysInMonth(month aMonth, int aYear)
{
  //    static const int days[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

      if( aYear == ReformYear && aMonth == ReformMonth ) return 21;
      return days[aMonth] + (feb == aMonth && IsLeapYear(aYear));
}

int
zDate::DayOfYear() const
{
      zDate first(jan, 1, m_year);

      return 1 + (int)(m_dayno - first.m_dayno);
}
/*
int
zDate::DaysInYear(int year)
{
      int days = 365 + IsLeapYear(year);
      // 10 days cancelled by the reform of pope Gregor XIII
      if( year == ReformYear ) return days - 10;
      else return days;
}

Boolean
zDate::IsLeapYear(int year)
{
      if( year % 4 ) return False;  // if not divisible by 4, not leap
      if( year < ReformYear ) return True; // before this year, all were leap
      if( year % 100 ) return True; // by 4, but not by 100 is leap
      if( year % 400 ) return False;      // not by 100 and not by 400 not leap
      return True;
}
* /
Boolean
zDate::IsValid(month aMonth, int aDay, int aYear)
{
      return Boolean(
               aYear  > 0
            && aMonth >= jan && aMonth <= dec
            && aDay   >  0   && aDay   <= DaysInMonth(aMonth, aYear)
      );
}

int
zDate::Age(const zDate &birthday) const
{
      int age = m_year - birthday.m_year - 1;

      if( m_month > birthday.m_month ) age++;
      else if( m_month == birthday.m_month && m_day >= birthday.m_day ) age++;

      return age;
}

zDate
zDate::operator+(int nDays) const
{
      return zDate(m_dayno + (long)nDays);
}

zDate
zDate::operator+(long nDays) const
{
      return zDate(m_dayno + nDays);
}

zDate
zDate::operator-(int nDays) const
{
      return zDate(m_dayno - (long)nDays);
}

zDate
zDate::operator-(long nDays) const
{
      return zDate(m_dayno - nDays);
}

long
zDate::operator-(const zDate &aDate) const
{
      return (long)(m_dayno - aDate.m_dayno);
}

zDate&
zDate::operator+=(int nDays)
{
      FromDayNumber(m_dayno + (long)nDays);
      return *this;
}

zDate&
zDate::operator+=(long nDays)
{
      FromDayNumber(m_dayno + nDays);
      return *this;
}

zDate
zDate::operator++()
{
      FromDayNumber(m_dayno + 1L);
      return *this;
}

zDate
zDate::operator++(int)
{
      zDate date(*this);

      FromDayNumber(m_dayno + 1L);
      return date;
}

zDate
zDate::operator--()
{
      FromDayNumber(m_dayno - 1L);
      return *this;
}
*/
/* postfix */
zDate
zDate::operator--(int)
{
      zDate date(*this);

      FromDayNumber(m_dayno - 1L);
      return date;
}

zDate&
zDate::operator-=(int nDays)
{
      FromDayNumber(m_dayno - (long)nDays);
      return *this;
}

zDate&
zDate::operator-=(long nDays)
{
      FromDayNumber(m_dayno - nDays);
      return *this;
}

int
zDate::WeekOfYear() const
{
      zDate first(jan, 1, m_year);

      return 1 + int((m_dayno - first.m_dayno + 1) / 7);
}

int
zDate::WeekOfMonth() const
{
      int abs_mday = m_day + zDate(m_month, 1, m_year).DayOfWeek() - 1;

      return 1 + ((abs_mday - DayOfWeek()) / 7);
}

int
zDate::WeeksInYear(int year)
{
      return zDate(dec, 31, year).WeekOfYear();
}

zDate
zDate::AddWeeks(int nWeeks) const
{
      zDate date(*this);

      date += (long)nWeeks * 7L;
      return date;
}

zDate
zDate::AddYears(int nYears) const
{
      zDate date(*this);
      int   delta = nYears > 0 ? -1 : 1;
      int   year = m_year;
      long  days = 0;

      while( nYears ){
            nYears += delta;
            year   -= delta;
            days   += DaysInYear(year);
      }
      date += (-delta * days);
      return date;
}

zDate::operator long() const
{
      return DayNumber();
}

/*
 * arguably useful routine, you can access the date object as an array,
 * with [0] == day (1..31), [1] == month (1..12), [2] == year - 1900
*/
char
zDate::operator[](int index) const
{
      switch( index ){
            case 0 : return m_day;
            case 1 : return m_month;
            case 2 : return m_year - 1900;
            default: return -1;
      }
}

int
zDate::DaysInMonth() const
{
      return DaysInMonth(m_month, m_year);
}

int
zDate::DaysInYear() const
{
      return DaysInYear(m_year);
}

int
zDate::WeeksInYear() const
{
      return WeeksInYear(m_year);
}

Boolean
zDate::IsValid() const
{
      return IsValid(m_month, m_day, m_year);
}

Boolean
zDate::IsLeapYear() const
{
      return IsLeapYear(m_year);
}

ulong
zDate::MakeDayNumber() const
{
      long days;
      long year  = (long)m_year - 1L;

      // get all days plus all leap years, minus non-leap years
      days = year * 365L + year / 4L - year / 100L + year / 400L;
      // the years before 1582 were all leap if divisible by 4
      if( year > ReformYear ) days += 12;
      else{
            days += year / 100L;
            days -= year / 400L;
      }
      // get the days for the month up to the current one
      for( int i = jan; i < m_month; ++i )
            days += DaysInMonth((month)i, m_year);
      // now add the current days of the month
      days += m_day;
      // now adjust for the 10 missing days (Oct 4 - Oct 15, 1582)
      if( days > ReformDayNumber ) days -= 10L;
      // we have the current day number now
      return days;
}

zDate::week_day
zDate::DayOfWeek() const
{
  //    const week_day wdays[7] = {sun,mon,tue,wed,thu,fri,sat};

      return wdays[(int)(((m_dayno % 7) + 5) % 7)];
}

void
zDate::FromDayNumber(ulong dayno)
{
      m_dayno = dayno;

      if( dayno > ReformDayNumber ) dayno += 10L;

      m_year = (int)(dayno / 365);
      m_day = (int)(dayno % 365L);

      if( m_year < 1700 ) m_day -= (m_year / 4);
      else{
            m_day -= (m_year / 4);
            m_day += (m_year / 100);
            m_day -= (m_year / 400);
            m_day -= 12;
      }

      while( m_day <= 0 ){
            m_day += (365 + IsLeapYear(m_year));
            m_year--;
      }

      // m_year is the number of elapsed years, add 1 to get current
      m_year += 1;

      // figure out the month and current day too
      for( m_month = jan; m_month <= dec; m_month = (month)(m_month + 1) ){
            int days = DaysInMonth(m_month, m_year);

            if( m_day <= days ) break;
            else m_day -= days;
      }
}

Boolean
zDate::IsDST() const
{
      return IsDST(*this);
}

/*
 * DST (Daylight Savings Time) starts at 2:00a on the first Sunday of
 * April and ends at 2:00a on the last Sunday of October (US rules)
*/

zDate
zDate::BeginDST(int year)
{
      zDate date(BeginDSTMonth, 1, year);

      while( BeginDSTDay != date.DayOfWeek() ) date++;
      return date;
}

zDate
zDate::EndDST(int year)
{
      zDate date(EndDSTMonth, 31, year);

      while( EndDSTDay != date.DayOfWeek() ) date--;
      return date;
}

zDate
zDate::BeginDST() const
{
      return BeginDST(m_year);
}

zDate
zDate::EndDST() const
{
      return EndDST(m_year);
}

Boolean
zDate::IsDST(const zDate &date)
{
      return Boolean( date >= date.BeginDST() && date <= date.EndDST() );
}

zDate::moon_phase
zDate::MoonPhase() const
{
      return MoonPhase(*this);
}

zDate::moon_phase
zDate::MoonPhase(const zDate &date)
{
      ulong phase = date.m_dayno;

      phase *= 9693L;
      phase /= 35780L;
      phase -= 4L;
      phase %= 8L;

      return (moon_phase)phase;
}

zDate
zDate::Easter() const
{
      return Easter(m_year);
}

/*
 * i won't pretend i know exactly how this algorithm works.
 * i used the one specified by the US Naval Observatory
*/
zDate
zDate::Easter(int year)
{
      int c, n, k, i, j, l, m, d;

      c = year / 100;
      n = year - 19 * (year / 19);
      k = (c - 17) / 25;
      i = c - c / 4 - (c - k) / 3 + 19 * n + 15;
      i = i - 30 * (i / 30);
      i = i - (i / 28) * (1 - (i / 28) * (29 / (i + 1)) * ((21 - n) / 11));
      j = year + year / 4 + i + 2 - c + c / 4;
      j = j - 7 * (j / 7);
      l = i - j;
      m = 3 + (l + 40) / 44;
      d = l + 28 - 31 * (m / 4);

      return zDate((month)m, d, year);
}

/*
 * this is a peculiar function - when months are added (or subtracted),
 * what really happens is that the month number is modified (with the
 * appropriate year adjustments too). if the resulting month/day combination
 * is invalid (i.e. Apr 31), the days will spill into the next month (in
 * the case with the example, the new date will be May 1). If we are
 * subtracting months and we end up with an invalid date, the difference
 * will be subtracted from the days (the month stays the same): this means
 * that March 31, 1996 (leap year) minus 1 month = Feb 27, 1996
*/
zDate
zDate::AddMonths(int nMonths) const
{
      int mon  = m_month + nMonths;
      int year = m_year;
      int day  = m_day;
      int mdays;

      while( mon < 1 ){
            mon += 12;
            year--;
      }

      while( mon > 12 ){
            mon -= 12;
            year++;
      }

      mdays = DaysInMonth((month)mon, year);

      if( day > mdays ){
            if( nMonths < 0 ) day = mdays - (day - mdays);
            else{
                  day -= mdays;
                  mon++;
                  if( mon > 12 ){
                        year++;
                        mon = 1;
                  }
            }
      }

      return zDate((month)mon, day, year);
}

// +++Date last modified: 05-Jul-1997

/*
 * This file is part of PB-Lib C/C++ Library
 *
 * Copyright (c) 1995, 1996 Branislav L. Slantchev
 * A Product of Silicon Creations, Inc.
 *
 * This class is hereby donated to the SNIPPETS collection (maintained
 * by Bob Stout). You are granted the right to use the code contained
 * herein free of charge as long as you keep this copyright notice intact.
 *
 * Contact: 73023.262@compuserve.com
*/
#include "date.hpp"
#include <iostream.h>

ostream& operator<<(ostream &stream, zDate::moon_phase phase)
{
      switch( phase ){
            case zDate::new_moon: stream << "new"; break;
            case zDate::waxing_crescent: stream << "waxing crescent"; break;
            case zDate::first_quater: stream << "first quater"; break;
            case zDate::waxing_gibbous: stream << "waxing gibbous"; break;
            case zDate::full_moon: stream << "full"; break;
            case zDate::waning_gibbous: stream << "waning gibbous"; break;
            case zDate::third_quater: stream << "third quater"; break;
            case zDate::waning_crescent: stream << "waning crescent"; break;
            default: stream << "--error--"; break;
      }
      return stream;
}

ostream& operator<<(ostream &stream, const zDate &date)
{
      stream << date.Day() << "-" << (int)date.Month() << "-" << date.Year();
      return stream;
}

ostream& operator<<(ostream &stream, zDate::week_day day)
{
      switch( day ){
            case zDate::sun: stream << "Sunday"; break;
            case zDate::mon: stream << "Monday"; break;
            case zDate::tue: stream << "Tuesday"; break;
            case zDate::wed: stream << "Wednesday"; break;
            case zDate::thu: stream << "Thursday"; break;
            case zDate::fri: stream << "Friday"; break;
            case zDate::sat: stream << "Saturday"; break;
            default        : stream << "--error--"; break;
      }
      return stream;
}

void test()
{
      cout << " zDate Class Demo \n\n";

      // default constructor, Jan 1 0000
      zDate a;
      cout << a << endl;
      // Various versions of the constructors
      zDate x(zDate::oct,20,1962);
      cout << x << endl;
      // constructor with a julian
      zDate z( 2450000L );
      cout << z << endl;
      // make a date with system date (tests copy constructor)
      zDate s(zDate::Today());
      cout << s << endl;
      // init with the day of year
      zDate y(33, 1996);
      cout << y << endl;
      // init from current system time
      time_t secs_now = time(NULL);
      zDate n(localtime(&secs_now));
      cout << n << endl;

      // using date addition and subtraction
      zDate adder = x + 10;
      cout << adder << endl;
      adder = adder - 25;
      cout << adder << endl;

      //using subtraction of two date objects
      zDate a1(zDate::Today());
      zDate a2 = a1 + 14;
      cout << (a1 - a2) << endl;
      cout << (a2 += 10) << endl;

      a1++;
      cout << "Tommorrow= " << a1 << endl;

      a1 = zDate(zDate::jul, 14, 1991);
      cout << "a1 (7-14-91) < a2 (" << a2
             << ")? ==> " << ((a1 < a2) ? "TRUE" : "FALSE") << endl;
      cout << "a1 (7-14-91) > a2 ("<< a2
             << ")? ==> " << ((a1 > a2) ? "TRUE" : "FALSE") << endl;
      cout << "a1 (7-14-91) < 8-01-91 ? ==> "
             << ((a1 < zDate(zDate::aug, 1, 1991)) ? "TRUE" : "FALSE") << endl;
      cout << "a1 (7-14-91) > 8-01-91 ? ==> "
             << ((a1 > zDate(zDate::aug, 1, 1991)) ? "TRUE" : "FALSE") << endl;
      cout << "a1 (7-14-91) == 7-14-91 ? ==> "
             << ((a1==zDate(zDate::jul, 14, 1991)) ? "TRUE" : "FALSE") << endl;
      zDate a3 = a1;

      cout << "a1 (" << a1 << ") == a3 (" << a3
             << ") ? ==> " << ((a1==a3) ? "TRUE" : "FALSE") << endl;
      zDate a4 = a1;
      ++a4;
      cout << "a1 ("<< a1 <<") == a4 (" << a4
             << ") ? ==> " << ((a1==a4) ? "TRUE" : "FALSE") << endl;

      zDate a5(zDate::Today());
      cout << "Today is: " << a5 << endl;
      a4 = zDate::Today();
      cout << "Today (a4) is: " << a4 << endl;

      cout << "Today + 4 is: " << (a4 += 4) << endl;
      a4 = zDate::Today();
      cout << "Today - 4 is: " << (a4 -= 4) << endl;
      cout << "=========== Leap Year Test ===========\n";
      a1 = zDate(zDate::jan, 15, 1992);
      cout << a1 << "\t" << ((a1.IsLeapYear()) ? "Leap" : "non-Leap");
      cout << "\t" << "day of year:  " << a1.DayOfYear() << endl;

      a1 = zDate(zDate::feb, 16, 1993);
      cout << a1 << "\t" << ((a1.IsLeapYear()) ? "Leap" : "non-Leap");
      cout << "\t" << "day of year:  " << a1.DayOfYear() << endl;

      zDate v4(zDate::Today());
      cout << "---------- Add Stuff -----------\n";
      cout << "Start => " << v4 << endl;
      cout << "Add  4 Weeks  => " << v4.AddWeeks(4) << endl;
      cout << "Sub 52 Weeks  => " << v4.AddWeeks(-52)  << endl;
      cout << "Add  2 Years  => " << v4.AddYears(2)    << endl;

      cout << flush;

      cout << "---------- Misc Stuff -----------\n";
      cout << "The date aboves' day of the month is => " << v4.Day() << endl;
      cout << "There are " << v4.DaysInMonth() << " days in this month.\n";
      cout << "This day happens to be " << v4.DayOfWeek() << " day of week" << endl;
      cout << "on the " << v4.WeekOfYear() << " week of the year," << endl;
      cout << "on the " << v4.WeekOfMonth() << " week of the month, " << endl;
      cout << "which is the "<< (int)v4.Month() << "nth month in the year.\n";
      cout << "The year alone is " << v4.Year() << endl;
      cout << "And this is the " << v4.DayOfYear() << " day of year" << endl;
      cout << "of a year with " << v4.DaysInYear() << " days in it" << endl;
      cout << "which makes exatcly " << v4.WeeksInYear() << " weeks" << endl;

      zDate birthday(zDate::jul, 16, 1973);
      cout << "The age test: i was born on " << birthday
             << " which makes me " << v4.Age(birthday) << " years old" << endl;

      zDate       D2(zDate::jul, 4, 1776);
      int         I1 = 4;

      cout << "Before: I1 = " << I1 << ",  D2 = " << D2 << endl;
      cout << "---------- Postfix '++' test -----------\n";
      cout << "Test : I1++ = " << I1++ << ",  D2++ = " << D2++ << endl;
      cout << "After: I1   = " << I1 << ",  D2   = " << D2 << endl;

      cout << "---------- Prefix '++' test -----------\n";
      cout << "Test : ++I1 = " << ++I1 << ",  ++D2 = " << ++D2 << endl;
      cout << "After:   I1 = " << I1 << ",    D2 = " << D2 << endl;

      cout << "---------- Postfix '--' test -----------\n";
      cout << "Test : I1-- = " << I1-- << ",  D2-- = " << D2-- << endl;
      cout << "After: I1   = " << I1 << ",  D2   = " << D2 << endl;

      cout << "---------- Prefix '--' test -----------\n";
      cout << "Test : --I1 = " << --I1 << ",  --D2 = " << --D2 << endl;
      cout << "After:   I1 = " << I1 << ",    D2 = " << D2 << endl;

      cout << "Last day of this year is dayno "
             << zDate(zDate::dec, 31, 1996).DayOfYear() << endl;
      cout << "Last day of prev year is dayno "
             << zDate(zDate::dec, 31, 1995).DayOfYear() << endl;

      cout << "Today the moon is " << zDate::Today().MoonPhase() << endl;

      zDate today = zDate::Today();

      cout << "DST for " << today.Year() << " starts on " << today.BeginDST()
             << " and ends on " << today.EndDST() << endl;
      cout << "Today, " << today << ", DST is "
             << (today.IsDST() ? "" : "not") << "in effect" << endl;

      zDate date1(zDate::aug, 31, 1996);
      cout << "Adding 6 months to " << date1 << " results in "
             << date1.AddMonths(6) << endl;

      zDate date2(zDate::mar, 31, 1996);
      cout << "Subtracting 1 month from " << date2 << " results in "
             << date2.AddMonths(-1) << endl;

      zDate date3(zDate::jul, 4, 1776);
      cout << "Adding 2400 months to " << date3 << " results in "
             << date3.AddMonths(2400) << endl;

      cout << "Today's day number is " << zDate::Today().DayNumber() << endl;

      zDate date4(zDate::feb, 29, 1996);
      cout << date4 << " subtract two years = " << date4.AddYears(-2) << endl;

      cout << "In 1996, DST began on " << zDate::BeginDST(1996) << endl;

      zDate date5(zDate::sep, 26, 1996);
      cout << "Moon phase on " << date5 << " was " << date5.MoonPhase() << endl;

      zDate date6(zDate::oct, 3, 1996);
      cout << date6 << " + 55 days is " << (date6 + 55) << endl;

      zDate date7(zDate::oct, 4, 1996);
      cout << date7 << " + 217 days is ";
      date7 += 217;
      cout << date7 << endl;
      date7 = zDate(zDate::oct, 4, 1996);
      cout << "Same date - (-217) days is ";
      date7 -= -217;
      cout << date7 << endl;

      cout << "For 1996, Easter is on " << zDate::Easter(1996) << endl;
}


void
main()
{
      test();
};

#endif //0 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#if 0  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
////////////////////////////////////////////////////////////////////////////
/* +++Date last modified: 05-Jul-1997 */
/* +++Date last modified: 05-Jul-1997 */

/*
** scalar date routines    --    public domain by Ray Gardner
** Numerically, these will work over the range 1/01/01 thru 14699/12/31.
** Practically, these only work from the beginning of the Gregorian
** calendar thru 14699/12/31.  The Gregorian calendar took effect in
** much of Europe in about 1582, some parts of Germany in about 1700, in
** England and the colonies in about 1752ff, and in Russia in 1918.
*/

#ifndef SCALDATE__H
#define SCALDATE__H

#include "sniptype.h"

/*
**  Define ISO_CAL to be 1 for ISO (Mon-Sun) calendars
**
**  ISO defines the first week with 4 or more days in it to be week #1.
*/
/*
#ifndef ISO_CAL
 #define ISO_CAL 0
#endif

#if (ISO_CAL != 0 && ISO_CAL != 1)
 #error ISO_CAL must be set to either 0 or 1
#endif

#if ISO_CAL
 enum DOW_T {DOW_IGNORE = -1,
       MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY};
#else
 enum DOW_T {DOW_IGNORE = -1,
       SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY};
#endif
*/
/*
**  Daylight savings time rules.
**
**  Rules include a month, date, and day. If the day is DOW_IGNORE, DST will
**  start on the month and date specified. If a day is specified (the
**  interpretation of the day parameter is subject to the value of ISO_CAL),
**  DST will start on the first such day following (or equal to) the specified
**  date, or stop on the first such day preceding (or equal to) the specified
**  date.
**
**  The defaults defined for the U.S. mean that DST will begin on the first
**  Sunday after (or on) April 1 and end on the last Sunday preceding (or on)
**  October 31.
*/

extern unsigned   DST_start_mo;
extern unsigned   DST_start_dt;
extern enum DOW_T DST_start_dy;

extern unsigned   DST_stop_mo;
extern unsigned   DST_stop_dt;
extern enum DOW_T DST_stop_dy;

int  isleap (unsigned yr);
long ymd_to_scalar (unsigned yr, unsigned mo, unsigned day);
void scalar_to_ymd (long scalar, unsigned *yr, unsigned *mo, unsigned *day);
int  daynum(int year, int month, int day);
int  weeknum(int year, int month, int day);

Boolean_T valiDate(unsigned yr, unsigned mo, unsigned day);

unsigned dow(unsigned yr, unsigned mo, unsigned day);
unsigned DOW(unsigned y, unsigned m, unsigned d);

long today(void);

extern char *MoonPhaseText[8];

unsigned moonphase(unsigned yr, unsigned mo, unsigned dy);

int getfdate (int handle, long *date);
int getdatef (char *fname, long *date);


#endif /* SCALDATE__H */

/* +++Date last modified: 05-Jul-1997 */

/*
**  Header for SNIPPETS date & time function, excluding scalar dates
*/

//#ifndef DATETIME__H
//#define DATETIME__H

//#include "sniptype.h"

/*
**  Julian day number functions from JDN_L.C
*/

//long ymd_to_jdnl(int y, int m, int d, int julian);
//void jdnl_to_ymd(long jdn, int *yy, int *mm, int *dd, int julian);

/*
**  Add times from ADDTIME.C
*/

//int add_time(unsigned basehrs, unsigned basemins, unsigned basesecs,
//             int spanhrs, int spanmins, int spansecs,
//             unsigned *hrs, unsigned *mins, unsigned *secs, int *days);

/*
**  Determine the date of Easter for any given year
*/

//void easter(int year, int *easter_month, int *easter_day);


/*
**  Moon phase from MOON_AGE.C
*/

//int moon_age(int month, int day, int year);

/*
**  Date parser from PARSDATE.C
*/

//typedef enum {USA, ISO, EUROPE} Syntax_T;

//Boolean_T parse_date(const char *str, unsigned *year, unsigned *month,
//                     unsigned *day, Syntax_T syntax);

/*
**  Time parser from PARSTIME.C
*/

//Boolean_T parse_time(const char *str, unsigned *hours, unsigned *mins,
//                     unsigned *secs);


//#endif /* DATETIME__H */


/*
**  DAYNUM.C - Functions to return statistics about a given date.
**
**  public domain by Bob Stout - uses Ray Gardner's SCALDATE.C
*/

#include "scaldate.h"

static long jan1date;

/*
**  Determine if a given date is valid
*/

Boolean_T valiDate(unsigned yr, unsigned mo, unsigned day)
{
//      unsigned int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

      if (1 > mo || 12 < mo)
            return False_;
      if (1 > day || day > (days[mo - 1] + (2 == mo && isleap(yr))))
            return False_;
      else  return True_;
}

/*
**  Return the day of the week
*/

unsigned dow(unsigned yr, unsigned mo, unsigned day)
{
 
#if (!ISO_CAL)    /* Sunday(0) -> Saturday(6) (i.e. U.S.) calendars  */
      return (unsigned)(ymd_to_scalar(yr, mo, day) % 7L);
#else             /* International Monday(0) -> Sunday(6) calendars  */
      return (unsigned)((ymd_to_scalar(yr, mo, day) - 1L) % 7L);
#endif
}

/*
**  Return the day of the year (1 - 365/6)
*/

int daynum(int year, int month, int day)
{
      jan1date = ymd_to_scalar(year, 1, 1);
      return (int)(ymd_to_scalar(year, month, day) - jan1date + 1L);
}

/*
**  Return the week of the year (1 - 52, 0 - 52 if ISO)
*/

int weeknum(int year, int month, int day)
{
      int wn, j1n, dn = daynum(year, month, day);

      dn += (j1n = (int)((jan1date - (long)ISO_CAL) % 7L)) - 1;
      wn = dn / 7;
      if (ISO_CAL)
            wn += (j1n < 4);
      else  ++wn;
      return wn;
}

/*
**  Return the phase of the moon (0 -> 7, 0 = new, 4 = full)
* /

char *MoonPhaseText[8] = {"new", "waxing crescent", "first quarter",
      "waxing gibbous", "full", "waning gibbous", "third quarter",
      "waning crescent"
      };

unsigned moonphase(unsigned yr, unsigned mo, unsigned dy)
{
      unsigned long date = (unsigned long)ymd_to_scalar(yr, mo, dy);

      date *= 9693L;
      date /= 35780L;
      date -= 4L;
      date %= 8L;
      return (unsigned)date;
}
*/
/*
#ifdef TEST

#include <stdio.h>
#include <stdlib.h>

void do_err(void);

main(int argc, char *argv[])
{
      int day, month, year;
      char *days[] =
#if (!ISO_CAL)
            {"Sunday", "Monday", "Tuesday", "Wednesday",
             "Thursday", "Friday", "Saturday"};
#else
            {"Monday", "Tuesday", "Wednesday", "Thursday",
             "Friday", "Saturday", "Sunday"};
#endif

      if (4 > argc)
      {
            puts("Usage: DAYNUM month day year");
            return EXIT_FAILURE;
      }

      month = atoi(argv[1]);
      day   = atoi(argv[2]);
      year  = atoi(argv[3]);
      if (100 > year)
            year += 1900;

      if (!valiDate(year, month, day))
            printf("%d/%d/%d is invalid!\n", month, day, year);
      else
      {
            printf("%d/%d/%d is a %s, day #%d in week %d\n", month, day, year,
                  days[dow(year, month, day)], daynum(year, month, day),
                  weeknum(year, month, day));
            printf("The phase of the moon is %s\n",
                  MoonPhaseText[moonphase(year, month, day)]);
      }
      return EXIT_SUCCESS;
}

#endif /* TEST */
*/
/* +++Date last modified: 05-Jul-1997 */

/*
** scalar date routines    --    public domain by Ray Gardner
** Numerically, these will work over the range 1/01/01 thru 14699/12/31.
** Practically, these only work from the beginning of the Gregorian 
** calendar thru 14699/12/31.  The Gregorian calendar took effect in
** much of Europe in about 1582, some parts of Germany in about 1700, in
** England and the colonies in about 1752ff, and in Russia in 1918.
*/
/*
#include "scaldate.h"

int isleap (unsigned yr)
{
   return yr % 400 == 0 || (yr % 4 == 0 && yr % 100 != 0);
}
*/
static unsigned months_to_days (unsigned month)
{
   return (month * 3057 - 3007) / 100;
}

static long years_to_days (unsigned yr)
{
   return yr * 365L + yr / 4 - yr / 100 + yr / 400;
}

long ymd_to_scalar (unsigned yr, unsigned mo, unsigned day)
{
   long scalar;
   scalar = day + months_to_days(mo);
   if ( mo > 2 )                         /* adjust if past February */
      scalar -= isleap(yr) ? 1 : 2;
   yr--;
   scalar += years_to_days(yr);
   return scalar;
}

void scalar_to_ymd (long scalar, unsigned *yr, unsigned *mo, unsigned *day)
{
   unsigned n;                /* compute inverse of years_to_days() */

   for ( n = (unsigned)((scalar * 400L) / 146097L); years_to_days(n) < scalar;)
      n++;                          /* 146097 == years_to_days(400) */
   *yr = n;
   n = (unsigned)(scalar - years_to_days(n-1));
   if ( n > 59 ) {                       /* adjust if past February */
      n += 2;
      if ( isleap(*yr) )
         n -= n > 62 ? 1 : 2;
   }
   *mo = (n * 100 + 3007) / 3057;    /* inverse of months_to_days() */
   *day = n - months_to_days(*mo);
}

/* +++Date last modified: 05-Jul-1997 */

/*
**  Header for SNIPPETS date & time function, excluding scalar dates
*/

#ifndef DATETIME__H
#define DATETIME__H

#include "sniptype.h"

/*
**  Julian day number functions from JDN_L.C
*/

long ymd_to_jdnl(int y, int m, int d, int julian);
void jdnl_to_ymd(long jdn, int *yy, int *mm, int *dd, int julian);

/*
**  Add times from ADDTIME.C
*/

int add_time(unsigned basehrs, unsigned basemins, unsigned basesecs,
             int spanhrs, int spanmins, int spansecs,
             unsigned *hrs, unsigned *mins, unsigned *secs, int *days);

/*
**  Determine the date of Easter for any given year
*/

void easter(int year, int *easter_month, int *easter_day);


/*
**  Moon phase from MOON_AGE.C
*/

int moon_age(int month, int day, int year);

/*
**  Date parser from PARSDATE.C
*/

typedef enum {USA, ISO, EUROPE} Syntax_T;

Boolean_T parse_date(const char *str, unsigned *year, unsigned *month,
                     unsigned *day, Syntax_T syntax);

/*
**  Time parser from PARSTIME.C
*/

Boolean_T parse_time(const char *str, unsigned *hours, unsigned *mins,
                     unsigned *secs);


#endif /* DATETIME__H */

/*  ----------------------------------------------------------------<Prolog>-
    Name:       sfldate.h
    Title:      Date and time functions
    Package:    Standard Function Library (SFL)

    Written:    1996/01/05  iMatix SFL project team <sfl@imatix.com>
    Revised:    1998/08/05

    Synopsis:   Includes functions to get the current date/time, calculate
                the day or week, week of year and leap year.  Dates and times
                are each stored in a 32-bit long value of 8 digits: dates are
                CCYYMMDD; times are HHMMSSCC.  You can compare dates and times
                directly - e.g. if (date_wanted >= date_now).

    Copyright:  Copyright (c) 1996-2000 iMatix Corporation
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef SFLDATE_INCLUDED               /*  Allow multiple inclusions        */
#define SFLDATE_INCLUDED

/*  Macros                                                                   */

#define GET_CENTURY(d)      (int) ( (d) / 1000000L)
#define GET_CCYEAR(d)       (int) ( (d) / 10000L)
#define GET_YEAR(d)         (int) (((d) % 1000000L) / 10000L)
#define GET_MONTH(d)        (int) (((d) % 10000L) / 100)
#define GET_DAY(d)          (int) ( (d) % 100)

#define GET_HOUR(t)         (int) ( (t) / 1000000L)
#define GET_MINUTE(t)       (int) (((t) % 1000000L) / 10000L)
#define GET_SECOND(t)       (int) (((t) % 10000L) / 100)
#define GET_CENTI(t)        (int) ( (t) % 100)

#define MAKE_DATE(c,y,m,d)  (long) (c) * 1000000L +                          \
                            (long) (y) * 10000L +                            \
                            (long) (m) * 100 + (d)
#define MAKE_TIME(h,m,s,c)  (long) (h) * 1000000L +                          \
                            (long) (m) * 10000L +                            \
                            (long) (s) * 100 + (c)

#define timeeq(d1,t1,d2,t2)  ((d1) == (d2) && (t1) == (t2))
#define timeneq(d1,t1,d2,t2) ((d1) != (d2) || (t1) != (t2))
#define timelt(d1,t1,d2,t2)  ((d1) < (d2) || ((d1) == (d2) && (t1) <  (t2)))
#define timele(d1,t1,d2,t2)  ((d1) < (d2) || ((d1) == (d2) && (t1) <= (t2)))
#define timegt(d1,t1,d2,t2)  ((d1) > (d2) || ((d1) == (d2) && (t1) >  (t2)))
#define timege(d1,t1,d2,t2)  ((d1) > (d2) || ((d1) == (d2) && (t1) >= (t2)))

/*  Days are numbered from 0=Sunday to 6=Saturday                            * /

#define DAY_SUNDAY      0
#define DAY_MONDAY      1
#define DAY_TUESDAY     2
#define DAY_WEDNESDAY   3
#define DAY_THURSDAY    4
#define DAY_FRIDAY      5
#define DAY_SATURDAY    6
*/

/*  Interval values, specified in centiseconds                               */

#define INTERVAL_CENTI      1
#define INTERVAL_SEC        100
#define INTERVAL_MIN        6000
#define INTERVAL_HOUR       360000L
#define INTERVAL_DAY        8640000L


/*  Function prototypes                                                      */

#ifdef __cplusplus
extern "C" {
#endif

long   date_now           (void);
long   time_now           (void);
Bool   leap_year          (int year);
int    julian_date        (long date);
int    day_of_week        (long date);
int    week_of_year       (long date);
int    year_quarter       (long date);
long   next_weekday       (long date);
long   prev_weekday       (long date);
word   pack_date          (long date);
word   pack_time          (long time);
long   unpack_date        (word packdate);
long   unpack_time        (word packtime);
long   default_century    (long *date);
long   date_to_days       (long date);
long   days_to_date       (long days);
time_t date_to_timer      (long date, long time);
long   timer_to_date      (time_t time_secs);
long   timer_to_time      (time_t time_secs);
long   timer_to_gmdate    (time_t time_secs);
long   timer_to_gmtime    (time_t time_secs);
long   time_to_csecs      (long time);
long   csecs_to_time      (long csecs);
void   future_date        (long *date, long *time, long days, long csecs);
void   past_date          (long *date, long *time, long days, long csecs);
void   date_diff          (long date1, long time1, long date2, long time2,
                           long *days, long *csecs);
Bool   valid_date         (long date);
Bool   valid_time         (long time);
Bool   date_is_future     (long date, long time);
Bool   date_is_past       (long date, long time);
char  *timezone_string    (void);
void   local_to_gmt       (long date, long time, long *gmdate, long *gmtime);
void   gmt_to_local       (long gmdate, long gmtime, long *date, long *time);
struct tm *safe_localtime (const time_t *time_secs);
struct tm *safe_gmtime    (const time_t *time_secs);

#ifdef __cplusplus
}
#endif

#endif

/*  ----------------------------------------------------------------<Prolog>-
    Name:       sfldate.c
    Title:      Date and time functions
    Package:    Standard Function Library (SFL)

    Written:    1996/01/06  iMatix SFL project team <sfl@imatix.com>
    Revised:    2000/01/19

    Copyright:  Copyright (c) 1996-2000 iMatix Corporation
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#include "prelude.h"                    /*  Universal header file            */
#include "sflprint.h"                   /*  snprintf functions               */
#include "sfldate.h"                    /*  Prototypes for functions         */


/*  ---------------------------------------------------------------------[<]-
    Function: date_now

    Synopsis: Returns the current date as a long value (CCYYMMDD).  Since
    most system clocks do not return a century, this function assumes that
    all years 80 and above are in the 20th century, and all years 00 to 79
    are in the 21st century.  For best results, consume before 1 Jan 2080.
    ---------------------------------------------------------------------[>]-*/

long
date_now (void)
{
    return (timer_to_date (time (NULL)));
}


/*  ---------------------------------------------------------------------[<]-
    Function: time_now

    Synopsis: Returns the current time as a long value (HHMMSSCC).  If the
    system clock does not return centiseconds, these are set to zero.
    ---------------------------------------------------------------------[>]-*/

long
time_now (void)
{
#if (defined (__TURBOC__))
    /*  The Turbo-C gettime() function returns just what we want             */
    struct time
        time_struct;

    gettime (&time_struct);
    return (MAKE_TIME (time_struct.ti_hour,
                       time_struct.ti_min,
                       time_struct.ti_sec,
                       time_struct.ti_hund));

#elif (defined (__UTYPE_FREEBSD__))
    return (timer_to_time (time (NULL)));

#elif (defined (__UNIX__) || defined (__VMS_XOPEN))
    /*  The BSD gettimeofday function returns seconds and microseconds       */
    struct timeval
        time_struct;

    gettimeofday (&time_struct, 0);
    return (timer_to_time (time_struct.tv_sec)
                         + time_struct.tv_usec / 10000);

#elif (defined (WIN32))
    /*  The Win32 GetLocalTime function returns just what we want            */
    SYSTEMTIME
        time_struct;

    GetLocalTime (&time_struct);
    return (MAKE_TIME (time_struct.wHour,
                       time_struct.wMinute,
                       time_struct.wSecond,
                       time_struct.wMilliseconds / 10));

#else
    /*  Otherwise, just get the time without milliseconds                    */
    return (timer_to_time (time (NULL)));
#endif
}


/*  ---------------------------------------------------------------------[<]-
    Function: leap_year

    Synopsis: Returns TRUE if the year is a leap year.  You must supply a
    4-digit value for the year: 90 is taken to mean 90 ad.  Handles leap
    centuries correctly.
    ---------------------------------------------------------------------[>]-*/

//Bool
//leap_year (int year)
//{
//    return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
//}


/*  ---------------------------------------------------------------------[<]-
    Function: julian_date

    Synopsis: Returns the number of days since 31 December last year.  The
    Julian date of 1 January is 1.
    ---------------------------------------------------------------------[>]-*/

int
julian_date (long date)
{
    static int
        days [12] = {
        0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
    };
    int
        julian;

    julian = days [GET_MONTH (date) - 1] + GET_DAY (date);
    if (GET_MONTH (date) > 2 && leap_year (GET_YEAR (date)))
        julian++;

    return (julian);
}


/*  ---------------------------------------------------------------------[<]-
    Function: day_of_week

    Synopsis: Returns the day of the week where 0 is Sunday, 1 is Monday,
    ... 6 is Saturday.  Uses Zeller's Congurence algorithm.
    ---------------------------------------------------------------------[>]-*/

int
day_of_week (long date)
{
    int
        year  = GET_CCYEAR (date),
        month = GET_MONTH  (date),
        day   = GET_DAY    (date);

    if (month > 2)
        month -= 2;
    else
      {
        month += 10;
        year--;
      }
    day = ((13 * month - 1) / 5) + day + (year % 100) +
          ((year % 100) / 4) + ((year / 100) / 4) - 2 *
           (year / 100) + 77;

    return (day - 7 * (day / 7));
}


/*  ---------------------------------------------------------------------[<]-
    Function: next_weekday

    Synopsis: Returns the date of the next weekday, skipping from Friday
    to Monday.
    ---------------------------------------------------------------------[>]-*/

long
next_weekday (long date)
{
    long
        days = date_to_days (date);

    if (day_of_week (date) == 5)        /*  Friday                           */
        days += 3;
    else
    if (day_of_week (date) == 6)        /*  Saturday                         */
        days += 2;
    else
        days += 1;                      /*  Sunday to Thursday               */

    return (days_to_date (days));
}


/*  ---------------------------------------------------------------------[<]-
    Function: prev_weekday

    Synopsis: Returns the date of the previous weekday, skipping from Monday
    to Friday.
    ---------------------------------------------------------------------[>]-*/

long
prev_weekday (long date)
{
    long
        days = date_to_days (date);

    if (day_of_week (date) == 1)        /*  Monday                           */
        days -= 3;
    else
    if (day_of_week (date) == 0)        /*  Sunday                           */
        days -= 2;
    else
        days -= 1;                      /*  Tuesday to Saturday              */

    return (days_to_date (days));
}


/*  ---------------------------------------------------------------------[<]-
    Function: week_of_year

    Synopsis: Returns the week of the year, where 1 is the first full week.
    Week 0 may or may not exist in any year.  Uses a Lillian date algorithm
    to calculate the week of the year.
    ---------------------------------------------------------------------[>]-*/

int
week_of_year (long date)
{
    long
        year = GET_CCYEAR (date) - 1501,
        day  = year * 365 + year / 4 - 29872L + 1
             - year / 100 + (year - 300) / 400;

    return ((julian_date (date) + (int) ((day + 4) % 7)) / 7);
}


/*  ---------------------------------------------------------------------[<]-
    Function: year_quarter

    Synopsis: Returns the year quarter, 1 to 4, depending on the month
    specified.
    ---------------------------------------------------------------------[>]-* /

int
year_quarter (long date)
{
    return ((GET_MONTH (date) - 1) / 3 + 1);
}
*/

/*  ---------------------------------------------------------------------[<]-
    Function: default_century

    Synopsis: Supplies a default century for the year if necessary.  If
    the year is 51 to 99, the century is set to 19.  If the year is 0 to
    50, the century is set to 20.  Returns the adjusted date.
    ---------------------------------------------------------------------[>]-*/

long
default_century (long *date)
{
    if (GET_CENTURY (*date) == 0)
        *date += (GET_YEAR (*date) > 50? 19000000L: 20000000L);
    return (*date);
}


/*  ---------------------------------------------------------------------[<]-
    Function: pack_date

    Synopsis: Packs the date into a single unsigned short word.  Use this
    function to store dates when memory space is at a premium.  The packed
    date can be used correctly in comparisons.  Returns the packed date.
    The date must be later than 31 December 1979.
    ---------------------------------------------------------------------[>]-*/

word
pack_date (long date)
{
    return (word) (((GET_CCYEAR (date) - 1980) << 9) +
                    (GET_MONTH  (date) << 5) +
                     GET_DAY    (date));
}


/*  ---------------------------------------------------------------------[<]-
    Function: pack_time

    Synopsis: Packs the time into a single unsigned short word.  Use this
    function to store times when memory space is at a premium.  The packed
    time can be used correctly in comparisons.  Returns the packed time.
    Seconds are stored with 2-second accuracy and centiseconds are lost.
    ---------------------------------------------------------------------[>]-*/

word
pack_time (long time)
{
    return (word) ((GET_HOUR   (time) << 11) +
                   (GET_MINUTE (time) << 5)  +
                   (GET_SECOND (time) >> 1));
}


/*  ---------------------------------------------------------------------[<]-
    Function: unpack_date

    Synopsis: Converts a packed date back into a long value.
    ---------------------------------------------------------------------[>]-*/

long
unpack_date (word packdate)
{
    int year;

    year = ((word) (packdate & 0xfe00) >> 9) + 80;
    return (MAKE_DATE (year > 80? 19: 20,
                       year,
                       (word) (packdate & 0x01e0) >> 5,
                       (word) (packdate & 0x001f)));
}


/*  ---------------------------------------------------------------------[<]-
    Function: unpack_time

    Synopsis: Converts a packed time back into a long value.
    ---------------------------------------------------------------------[>]-*/

long
unpack_time (word packtime)
{
    return (MAKE_TIME ((word) (packtime & 0xf800) >> 11,
                       (word) (packtime & 0x07e0) >> 5,
                       (word) (packtime & 0x001f) << 1, 0));
}


/*  ---------------------------------------------------------------------[<]-
    Function: date_to_days

    Synopsis: Converts the date into a number of days since a distant but
    unspecified epoch.  You can use this function to calculate differences
    between dates, and forward dates.  Use days_to_date() to calculate the
    reverse function.  Author: Robert G. Tantzen, translated from the Algol
    original in Collected Algorithms of the CACM (algorithm 199).  Original
    translation into C by Nat Howard, posted to Usenet 5 Jul 1985.
    ---------------------------------------------------------------------[>]-*/

long
date_to_days (long date)
{
    long
        year    = GET_YEAR    (date),
        century = GET_CENTURY (date),
        month   = GET_MONTH   (date),
        day     = GET_DAY     (date);

    if (month > 2)
        month -= 3;
    else
      {
        month += 9;
        if (year)
            year--;
        else
          {
            year = 99;
            century--;
          }
      }
    return ((146097L * century)    / 4L +
            (1461L   * year)       / 4L +
            (153L    * month + 2L) / 5L +
                       day   + 1721119L);
}


/*  ---------------------------------------------------------------------[<]-
    Function: days_to_date

    Synopsis: Converts a number of days since some distant but unspecified
    epoch into a date.  You can use this function to calculate differences
    between dates, and forward dates.  Use date_to_days() to calculate the
    reverse function.  Author: Robert G. Tantzen, translated from the Algol
    original in Collected Algorithms of the CACM (algorithm 199).  Original
    translation into C by Nat Howard, posted to Usenet 5 Jul 1985.
    ---------------------------------------------------------------------[>]-*/

long
days_to_date (long days)
{
    long
        century,
        year,
        month,
        day;

    days   -= 1721119L;
    century = (4L * days - 1L) / 146097L;
    days    =  4L * days - 1L  - 146097L * century;
    day     =  days / 4L;

    year    = (4L * day + 3L) / 1461L;
    day     =  4L * day + 3L  - 1461L * year;
    day     = (day + 4L) / 4L;

    month   = (5L * day - 3L) / 153L;
    day     =  5L * day - 3   - 153L * month;
    day     = (day + 5L) / 5L;

    if (month < 10)
        month += 3;
    else
      {
        month -= 9;
        if (year++ == 99)
          {
            year = 0;
            century++;
          }
      }
    return (MAKE_DATE (century, year, month, day));
}


/*  ---------------------------------------------------------------------[<]-
    Function: date_to_timer

    Synopsis: Converts the supplied date and time into a time_t timer value.
    This is the number of non-leap seconds since 00:00:00 GMT Jan 1, 1970.
    Function was rewritten by Bruce Walter <walter@fortean.com>.  If the
    input date and time are invalid, returns 0.
    ---------------------------------------------------------------------[>]-*/

time_t
date_to_timer (long date, long time)
{
    struct tm
        time_struct;
    time_t
        timer;

    time_struct.tm_sec   = GET_SECOND (time);
    time_struct.tm_min   = GET_MINUTE (time);
    time_struct.tm_hour  = GET_HOUR   (time);
    time_struct.tm_mday  = GET_DAY    (date);
    time_struct.tm_mon   = GET_MONTH  (date) - 1;
    time_struct.tm_year  = GET_CCYEAR (date) - 1900;
    time_struct.tm_isdst = -1;
    timer = mktime (&time_struct);
    if (timer == -1)
        return (0);
    else
        return (timer);
}


/*  ---------------------------------------------------------------------[<]-
    Function: timer_to_date

    Synopsis: Converts the supplied timer value into a long date value.
    Dates are stored as long values: CCYYMMDD.  If the supplied value is
    zero, returns zero.  The timer value is assumed to be UTC (GMT).
    ---------------------------------------------------------------------[>]-*/

long
timer_to_date (time_t time_secs)
{
    struct tm
        *time_struct;

    if (time_secs == 0)
        return (0);
    else
      {
        /*  Convert into a long value CCYYMMDD                               */
        time_struct = safe_localtime (&time_secs);
        time_struct-> tm_year += 1900;
        return (MAKE_DATE (time_struct-> tm_year / 100,
                           time_struct-> tm_year % 100,
                           time_struct-> tm_mon + 1,
                           time_struct-> tm_mday));
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: timer_to_time

    Synopsis: Converts the supplied timer value into a long time value.
    Times are stored as long values: HHMMSS00.  Since the timer value does
    not hold centiseconds, these are set to zero.  If the supplied value
    was zero, returns zero.  The timer value is assumed to be UTC (GMT).
    ---------------------------------------------------------------------[>]-*/

long
timer_to_time (time_t time_secs)
{
    struct tm
        *time_struct;

    if (time_secs == 0)
        return (0);
    else
      {
        /*  Convert into a long value HHMMSS00                               */
        time_struct = safe_localtime (&time_secs);
        return (MAKE_TIME (time_struct-> tm_hour,
                           time_struct-> tm_min,
                           time_struct-> tm_sec,
                           0));
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: timer_to_gmdate

    Synopsis: Converts the supplied timer value into a long date value in
    Greenwich Mean Time (GMT).  Dates are stored as long values: CCYYMMDD.
    If the supplied value is zero, returns zero.
    ---------------------------------------------------------------------[>]-*/

long
timer_to_gmdate (time_t time_secs)
{
    struct tm
        *time_struct;

    if (time_secs == 0)
        return (0);
    else
      {
        /*  Convert into a long value CCYYMMDD                               */
        time_struct = safe_gmtime (&time_secs);
        if (time_struct == NULL)        /*  If gmtime is not implemented     */
            time_struct = safe_localtime (&time_secs);

        time_struct-> tm_year += 1900;
        return (MAKE_DATE (time_struct-> tm_year / 100,
                           time_struct-> tm_year % 100,
                           time_struct-> tm_mon + 1,
                           time_struct-> tm_mday));
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: timer_to_gmtime

    Synopsis: Converts the supplied timer value into a long time value in
    Greenwich Mean Time (GMT).  Times are stored as long values: HHMMSS00.
    On most systems the clock does not return centiseconds, so these are
    set to zero.  If the supplied value is zero, returns zero.
    ---------------------------------------------------------------------[>]-*/

long
timer_to_gmtime (time_t time_secs)
{
    struct tm
        *time_struct;

    if (time_secs == 0)
        return (0);
    else
      {
        /*  Convert into a long value HHMMSS00                               */
        time_struct = safe_gmtime (&time_secs);
        if (time_struct == NULL)        /*  If gmtime is not implemented     */
            time_struct = safe_localtime (&time_secs);

        return (MAKE_TIME (time_struct-> tm_hour,
                           time_struct-> tm_min,
                           time_struct-> tm_sec,
                           0));
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: time_to_csecs

    Synopsis: Converts a time (HHMMSSCC) into a number of centiseconds.
    ---------------------------------------------------------------------[>]-*/

long
time_to_csecs (long time)
{
    return ((long) (GET_HOUR   (time) * (long) INTERVAL_HOUR)
          + (long) (GET_MINUTE (time) * (long) INTERVAL_MIN)
          + (long) (GET_SECOND (time) * (long) INTERVAL_SEC)
          + (long) (GET_CENTI  (time)));
}


/*  ---------------------------------------------------------------------[<]-
    Function: csecs_to_time

    Synopsis: Converts a number of centiseconds (< INTERVAL_DAY) into a
    time value (HHMMSSCC).
    ---------------------------------------------------------------------[>]-*/

long
csecs_to_time (long csecs)
{
    long
        hour,
        min,
        sec;

    ASSERT (csecs < INTERVAL_DAY);

    hour  = csecs / INTERVAL_HOUR;
    csecs = csecs % INTERVAL_HOUR;
    min   = csecs / INTERVAL_MIN;
    csecs = csecs % INTERVAL_MIN;
    sec   = csecs / INTERVAL_SEC;
    csecs = csecs % INTERVAL_SEC;
    return (MAKE_TIME (hour, min, sec, csecs));
}


/*  ---------------------------------------------------------------------[<]-
    Function: future_date

    Synopsis: Calculates a future date and time from the date and time
    specified, plus an interval specified in days and 1/100th seconds.
    The date can be any date since some distant epoch (around 1600).
    If the date and time arguments are both zero, the current date and
    time are used.  Either date and time arguments may be null.
    ---------------------------------------------------------------------[>]-*/

void
future_date (long *date, long *time, long days, long csecs)
{
    long
        dummy_date = 0,
        dummy_time = 0;

    if (date == NULL)
        date = &dummy_date;
    if (time == NULL)
        time = &dummy_time;

    /*  Set date and time to NOW if necessary                                */
    if (*date == 0 && *time == 0)
      {
        *date = date_now ();
        *time = time_now ();
      }

    /*  Get future date in days and centiseconds                             */
    days  = date_to_days  (*date) + days;
    csecs = time_to_csecs (*time) + csecs;

    /*  Normalise overflow in centiseconds                                   */
    while (csecs >= INTERVAL_DAY)
      {
        days++;
        csecs -= INTERVAL_DAY;
      }

    /*  Convert date and time back into organised values                     */
    *date = days_to_date  (days);
    *time = csecs_to_time (csecs);
}


/*  ---------------------------------------------------------------------[<]-
    Function: past_date

    Synopsis: Calculates a past date and time from the date and time
    specified, minus an interval specified in days and 1/100th seconds.
    The date can be any date since some distant epoch (around 1600).
    If the date and time arguments are both zero, the current date and
    time are used.  Either date and time arguments may be null.
    ---------------------------------------------------------------------[>]-*/

void
past_date (long *date, long *time, long days, long csecs)
{
    long
        dummy_date = 0,
        dummy_time = 0;

    if (date == NULL)
        date = &dummy_date;
    if (time == NULL)
        time = &dummy_time;

    /*  Set date and time to NOW if necessary                                */
    if (*date == 0 && *time == 0)
      {
        *date = date_now ();
        *time = time_now ();
      }
    /*  Get past date in days and centiseconds                               */
    days  = date_to_days  (*date) - days;
    csecs = time_to_csecs (*time) - csecs;

    /*  Normalise underflow in centiseconds                                  */
    while (csecs < 0)
      {
        days--;
        csecs += INTERVAL_DAY;
      }

    /*  Convert date and time back into organised values                     */
    *date = days_to_date  (days);
    *time = csecs_to_time (csecs);
}


/*  ---------------------------------------------------------------------[<]-
    Function: date_diff

    Synopsis: Calculates the difference between two date/time values, and
    returns the difference as a number of days and a number of centiseconds.
    The date can be any date since some distant epoch (around 1600).  The
    calculation is date1:time1 - date2:time2.  The returned values may be
    negative.
    ---------------------------------------------------------------------[>]-*/

void
date_diff (
    long date1, long time1,             /*  Date and time                    */
    long date2, long time2,             /*    minus this date and time       */
    long *days, long *csecs             /*  Gives these values               */
)
{
    *days  = date_to_days  (date1) - date_to_days  (date2);
    *csecs = time_to_csecs (time1) - time_to_csecs (time2);
}


/*  ---------------------------------------------------------------------[<]-
    Function: valid_date

    Synopsis: Returns TRUE if the date is valid or zero; returns FALSE if
    the date is not valid.
    ---------------------------------------------------------------------[>]-*/

Bool
valid_date (long date)
{
    int
        month,
        day;
    Bool
        feedback;
    static byte
        month_days [] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    month = GET_MONTH (date);
    day   = GET_DAY   (date);

    if (date == 0)
        feedback = TRUE;                /*  Zero date is okay                */
    else
    if (month < 1 || month > 12)
        feedback = FALSE;               /*  Month out of range               */
    else
    if ((day < 1 || day > month_days [month - 1])
    ||  (month == 2 && day == 29 && !leap_year (GET_YEAR (date))))
        feedback = FALSE;               /*  Day out of range                 */
    else
        feedback = TRUE;                /*  Zero date is okay                */

    return (feedback);
}


/*  ---------------------------------------------------------------------[<]-
    Function: valid_time

    Synopsis: Returns TRUE if the time is valid or zero; returns FALSE if
    the time is not valid.
    ---------------------------------------------------------------------[>]-*/

Bool
valid_time (long time)
{
    return (GET_SECOND (time) < 60
        &&  GET_MINUTE (time) < 60
        &&  GET_HOUR   (time) < 24);
}


/*  ---------------------------------------------------------------------[<]-
    Function: date_is_future

    Synopsis: Returns TRUE if the specified date and time are in the future.
    Returns FALSE if the date and time are in the past, or the present (which
    will be the past by the time you've read this).  Date is specified as a
    YYYYMMDD value; time as HHMMSSCC.
    ---------------------------------------------------------------------[>]-*/

Bool
date_is_future (long date, long time)
{
    return (date  > date_now ()
        || (date == date_now () && time > time_now ()));
}


/*  ---------------------------------------------------------------------[<]-
    Function: date_is_past

    Synopsis: Returns TRUE if the specified date and time are in the past.
    Returns FALSE if the date and time are in the future or present (which
    despite any assertion to the contrary, is not the past.  Although that
    may change soon).  Date is specified as YYYYMMDD; time as HHMMSSCC.
    ---------------------------------------------------------------------[>]-*/

Bool
date_is_past (long date, long time)
{
    return (date  < date_now ()
        || (date == date_now () && time < time_now ()));
}


/*  ---------------------------------------------------------------------[<]-
    Function: timezone_string

    Synopsis: Returns a static string containing the time zone as a 4-digit
    number, with a leading '+' or '-' character.   GMT is represented as
    "+0000"; Central European Time is "+1000". If the system does not support
    the timezone, returns "+0000".
    ---------------------------------------------------------------------[>]-*/

char *
timezone_string (void)
{
#if (defined (TIMEZONE))
    static char
        formatted_string [10];          /*  -nnnn plus null                  */
    int
        minutes;                        /*  TIMEZONE is in seconds           */

    minutes = 0 - (int) (TIMEZONE / 60);
    snprintf (formatted_string, sizeof (formatted_string), 
              "%03d%02d", minutes / 60, abs (minutes % 60));
    if (*formatted_string == '0')
        *formatted_string = '+';
    return  (formatted_string);
#else
    return ("+0000");
#endif
}


/*  ---------------------------------------------------------------------[<]-
    Function: local_to_gmt

    Synopsis: Converts the specified date and time to GMT.  Returns the GMT
    date and time in two arguments.
    ---------------------------------------------------------------------[>]-*/

void
local_to_gmt (long date, long time, long *gmt_date, long *gmt_time)
{
    time_t
        time_value;

    time_value = date_to_timer   (date, time);
    *gmt_date  = timer_to_gmdate (time_value);
    *gmt_time  = timer_to_gmtime (time_value);
}


/*  ---------------------------------------------------------------------[<]-
    Function: gmt_to_local

    Synopsis: Converts the specified GMT date and time to the local time.
    Returns the local date and time in two arguments.  If the supplied value 
    is out of range, returns 00:00 on 1 January, 1970 (19700101).
    ---------------------------------------------------------------------[>]-*/

void
gmt_to_local (long gmt_date, long gmt_time, long *date, long *time)
{
    time_t
        time_value;
    struct tm
        *time_struct;

    /*  Convert from GMT                                                     */
    time_value  = date_to_timer (gmt_date, gmt_time) - TIMEZONE;
    time_struct = safe_localtime (&time_value);
    if (time_struct-> tm_isdst)
      {
        time_value  += 3600;            /*  Adjust for daylight savings      */
        time_struct = localtime (&time_value);
      }
    time_struct-> tm_year += 1900;
    *date = MAKE_DATE (time_struct-> tm_year / 100,
                       time_struct-> tm_year % 100,
                       time_struct-> tm_mon + 1,
                       time_struct-> tm_mday);
    *time = MAKE_TIME (time_struct-> tm_hour,
                       time_struct-> tm_min,
                       time_struct-> tm_sec,
                       0);
}


/*  ---------------------------------------------------------------------[<]-
    Function: safe_localtime

    Synopsis: Handles time_t values that exceed 2038.  The standard C
    localtime() function fails on most systems when the date passes 2038.
    ---------------------------------------------------------------------[>]-*/

struct tm
*safe_localtime (const time_t *time_secs)
{
    qbyte
        adjusted_time;
    struct tm
        *time_struct;
    int
        adjust_years = 0;

    adjusted_time = (qbyte) *time_secs;
    while (adjusted_time > LONG_MAX)
      {
        adjust_years  += 20;
        adjusted_time -= 631152000;     /*  Number of seconds in 20 years    */
      }
    time_struct = localtime ((const time_t *) &adjusted_time);
    ASSERT (time_struct);               /*  MUST be valid now...             */
    time_struct-> tm_year += adjust_years;

    return (time_struct);
}


/*  ---------------------------------------------------------------------[<]-
    Function: safe_gmtime

    Synopsis: Handles time_t values that exceed 2038.  The standard C
    gmtime() function fails on most systems when the date passes 2038.
    ---------------------------------------------------------------------[>]-*/

struct tm
*safe_gmtime (const time_t *time_secs)
{
    qbyte
        adjusted_time;
    struct tm
        *time_struct;
    int
        adjust_years = 0;

    adjusted_time = (qbyte) *time_secs;
    while (adjusted_time > LONG_MAX)
      {
        adjust_years  += 20;
        adjusted_time -= 631152000;     /*  Nbr seconds in 20 years          */
      }
    time_struct = gmtime ((const time_t *) &adjusted_time);
    if (time_struct)                    /*  gmtime may be unimplemented      */
        time_struct-> tm_year += adjust_years;

    return (time_struct);
}



#endif //0 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#if 0  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//=============================================================================
// File:       datetime.h
// Contents:   Declarations for DwDateTime
// Maintainer: Doug Sauder <dwsauder@fwb.gulf.net>
// WWW:        http://www.fwb.gulf.net/~dwsauder/mimepp.html
// $Revision: 5$
// $Date: 2004-10-06 22:43:03$
//
// Copyright (c) 1996, 1997 Douglas W. Sauder
// All rights reserved.
//
// IN NO EVENT SHALL DOUGLAS W. SAUDER BE LIABLE TO ANY PARTY FOR DIRECT,
// INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT OF
// THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF DOUGLAS W. SAUDER
// HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// DOUGLAS W. SAUDER SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT
// NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
// PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS"
// BASIS, AND DOUGLAS W. SAUDER HAS NO OBLIGATION TO PROVIDE MAINTENANCE,
// SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
//
//=============================================================================

#ifndef DW_DATETIME_H
#define DW_DATETIME_H

#include <time.h>

#ifndef DW_CONFIG_H
#include <mimelib/config.h>
#endif

#ifndef DW_FIELDBDY_H
#include <mimelib/fieldbdy.h>
#endif

//=============================================================================
//+ Name DwDateTime -- Class representing an RFC-822 date-time
//+ Description
//. {\tt DwDatetime} represents a {\it date-time} as described in RFC-822
//. and RFC-1123.  The parse method for {\tt DwDateTime} parses the
//. string representation to extract the year, month, day, hour, minute,
//. second, and time zone.  {\tt DwDateTime} provides member functions
//. to set or get the individual components of the date-time.
//=============================================================================
class DW_EXPORT DwDateTime : public DwFieldBody {

public:

    DwDateTime();
    DwDateTime(const DwDateTime& aDateTime);
    DwDateTime(const DwString& aStr, DwMessageComponent* aParent=0);
    //. The first constructor is the default constructor, which assigns
    //. the current date and time as reported by the operating system.
    //.
    //. The second constructor is the copy constructor.  The parent of
    //. the new {\tt DwDateTime} object is set to {\tt NULL}.
    //.
    //. The third constructor sets {\tt aStr} as the {\tt DwDateTime}
    //. object's string representation and sets {\tt aParent} as its parent.
    //. The virtual member function {\tt Parse()} should be called after
    //. this constructor to extract the date and time information from the
    //. string representation.  Unless it is {\tt NULL}, {\tt aParent} should
    //. point to an object of a class derived from {\tt DwField}.

    virtual ~DwDateTime();

    const DwDateTime& operator = (const DwDateTime& aDateTime);
    //. This is the assignment operator, which sets this {\tt DwDateTime}
    //. object to the same value as {\tt aDateTime}.

    virtual void Parse();
    //. This virtual function, inherited from {\tt DwMessageComponent},
    //. executes the parse method for {\tt DwDateTime} objects. The parse
    //. method creates or updates the broken-down representation from the
    //. string representation.  For {\tt DwDateTime} objects, the parse
    //. method parses the string representation to extract the year,
    //. month, day, hour, minute, second, and time zone.
    //.
    //. This function clears the is-modified flag.

    virtual void Assemble();
    //. This virtual function, inherited from {\tt DwMessageComponent},
    //. executes the assemble method for {\tt DwDateTime} objects.
    //. It should be called whenever one of the object's attributes
    //. is changed in order to assemble the string representation from
    //. its broken-down representation.  It will be called
    //. automatically for this object by the parent object's
    //. {\tt Assemble()} member function if the is-modified flag is set.
    //.
    //. This function clears the is-modified flag.

    virtual DwMessageComponent* Clone() const;
    //. This virtual function, inherited from {\tt DwMessageComponent},
    //. creates a new {\tt DwDateTime} on the free store that has the same
    //. value as this {\tt DwDateTime} object.  The basic idea is that of
    //. a virtual copy constructor.

    DwUint32 AsUnixTime() const;
    //. Returns the date and time as a UNIX (POSIX) time, defined as the
    //. number of seconds elapsed since 1 Jan 1970 00:00:00 UTC.

    void FromUnixTime(DwUint32 aTime);
    //. Sets the date and time from {\tt aTime}, interpreted as the number of
    //. of seconds elapsed since 1 Jan 1970 00:00:00 UTC.

    void FromCalendarTime(time_t aTime);
    //. Sets the date and time from {\tt aTime}, which is assumed to be in a
    //. format compatible with the native {\tt time()} ANSI C function.
    //. For most UNIX systems, this function is the same as the function
    //. {\tt FromUnixTime()}.  (For efficiency, use {\tt FromUnixTime()}
    //. instead of {\tt FromCalendarTime()} if possible).

    DwInt32 DateAsJulianDayNum() const;
    //. Returns the Julian Day Number, defined as the number of days elapsed
    //. since 1 Jan 4713 BC.  The JDN is calculated directly from the values
    //. of the year, month, and day; time zone information is ignored.

    void DateFromJulianDayNum(DwInt32 aJdn);
    //. Sets the year, month, and day from {\tt aJdn}, interpreted as a Julian
    //. Day Number.  By definition, the JDN is the number of days elapsed
    //. since 1 Jan 4713 BC.  This member function ignores time zone
    //. information.

    DwInt32 TimeAsSecsPastMidnight() const;
    //. Returns the number of seconds past midnight.  The value is
    //. calculated directly from the values of the hour, minute, and
    //. second; time zone information is ignored.

    void TimeFromSecsPastMidnight(DwInt32 aSecs);
    //. Sets the hour, minute, and second from {\tt aSecs}, interpreted as the
    //. number of seconds elapsed since midnight.  This member function
    //. ignores time zone information.  The argument {\tt aSecs} should be in
    //. the range 0 to 86399, inclusive.

    int Year() const;
    //. Returns the four digit year, e.g. 1997.

    void SetYear(int aYear);
    //. Sets the year from {\tt aYear}, which should be a four digit year.

    int Month() const;
    //. Returns the month.  Values range from 1 to 12.

    void SetMonth(int aMonth);
    //. Sets the month from {\tt aMonth}, which should be in the range 1
    //. to 12.

    int Day() const;
    //. Returns the day of the month.  Values range from 1 to 31.

    void SetDay(int aDay);
    //. Sets the day of the month from {\tt aDay}.

    int Hour() const;
    //. Returns the hour according to the 24 hour clock.
    //. Values range from 0 to 23.

    void SetHour(int aHour);
    //. Sets the hour from {\tt aHour} based on the 24-hour clock. {\tt aHour}
    //. should be in the range 0 to 23.

    int Minute() const;
    //. Returns the minute.  Values range from 0 to 59.

    void SetMinute(int aMinute);
    //. Sets the minute from {\tt aMinute}, which should be in the range 0
    //. to 59.

    int Second() const;
    //. Returns the second.  Values range from 0 to 59.

    void SetSecond(int aSecond);
    //. Sets the second from {\tt aSecond}, which should be in the range 0
    //. to 59.

    int Zone() const;
    //. Returns the time zone as the diffence in minutes between local time
    //. and Coordinated Universal Time (UTC or GMT).

    void SetZone(int aZone);
    //. Sets the time zone from {\tt aZone}, interpreted as the time difference
    //. in minutes between local time and Coordinated Universal Time
    //. (UTC, or GMT).

    static void SetDefaultZone(int aZone);
    //. Sets the default time zone.  {\tt aZone} should be the time difference
    //. in minutes between local time and Coordinated Universal Time
    //. (UTC, or GMT).  The value is used to set the time zone for any
    //. objects created using the default constructor.

    static DwDateTime* NewDateTime(const DwString&, DwMessageComponent*);
    //. Creates a new {\tt DwDateTime} object on the free store.
    //. If the static data member {\tt sNewDateTime} is {\tt NULL},
    //. this member function will create a new {\tt DwDateTime}
    //. and return it.  Otherwise, {\tt NewDateTime()} will call
    //. the user-supplied function pointed to by {\tt sNewDateTime},
    //. which is assumed to return an object from a class derived from
    //. {\tt DwDateTime}, and return that object.

    //+ Var sNewDateTime
    static DwDateTime* (*sNewDateTime)(const DwString&, DwMessageComponent*);
    //. If {\tt sNewDateTime} is not {\tt NULL}, it is assumed to point to a
    //. user-supplied function that returns an object from a class derived
    //. from {\tt DwDateTime}.

protected:

    void _FromUnixTime(DwUint32 aTime);
    //. Like {\tt FromUnixTime()}, but doesn't set the is-modified flag.

    void _FromCalendarTime(time_t aTime);
    //. Like {\tt FromCalendarTime()}, but doesn't set the is-modified flag.

    int  mYear;
    int  mMonth;
    int  mDay;
    int  mHour;
    int  mMinute;
    int  mSecond;
    int  mZone;

    static int sDefaultZone;
    static int sIsDefaultZoneSet;

private:

    static const char* const sClassName;

    void Init();
    //. Initialization code common to all constructors.

public:

    virtual void PrintDebugInfo(ostream& aStrm, int aDepth=0) const;
    //. This virtual function, inherited from {\tt DwMessageComponent},
    //. prints debugging information about this object to {\tt aStrm}.
    //.
    //. This member function is available only in the debug version of
    //. the library.

    virtual void CheckInvariants() const;
    //. Aborts if one of the invariants of the object fails.  Use this
    //. member function to track down bugs.
    //.
    //. This member function is available only in the debug version of
    //. the library.

protected:

    void _PrintDebugInfo(ostream& aStrm) const;

};


inline int DwDateTime::Year() const
{
    return mYear;
}


inline int DwDateTime::Month() const
{
    return mMonth;
}


inline int DwDateTime::Day() const
{
    return mDay;
}


inline int DwDateTime::Hour() const
{
    return mHour;
}


inline int DwDateTime::Minute() const
{
    return mMinute;
}


inline int DwDateTime::Second() const
{
    return mSecond;
}


inline int DwDateTime::Zone() const
{
    return mZone;
}


inline void DwDateTime::SetYear(int aYear)
{
    mYear = aYear;
    SetModified();
}


inline void DwDateTime::SetMonth(int aMonth)
{
    mMonth = aMonth;
    SetModified();
}


inline void DwDateTime::SetDay(int aDay)
{
    mDay = aDay;
    SetModified();
}


inline void DwDateTime::SetHour(int aHour)
{
    mHour = aHour;
    SetModified();
}


inline void DwDateTime::SetMinute(int aMinute)
{
    mMinute = aMinute;
    SetModified();
}


inline void DwDateTime::SetSecond(int aSecond)
{
    mSecond = aSecond;
    SetModified();
}


inline void DwDateTime::SetZone(int aZone)
{
    mZone = aZone;
    SetModified();
}

#endif

// Last modified 1997-08-23
//+ Noentry ~DwDateTime mYear mMonth mDay mHour mMinute mSecond mZone
//+ Noentry sDefaultZone sIsDefaultZoneSet _PrintDebugInfo

//=============================================================================
// File:       datetime2.cpp
// Contents:   Definitions for DwDateTime
// Maintainer: Doug Sauder <dwsauder@fwb.gulf.net>
// WWW:        http://www.fwb.gulf.net/~dwsauder/mimepp.html
// $Revision: 5$
// $Date: 2004-10-06 22:43:03$
//
// Copyright (c) 1996, 1997 Douglas W. Sauder
// All rights reserved.
//
// IN NO EVENT SHALL DOUGLAS W. SAUDER BE LIABLE TO ANY PARTY FOR DIRECT,
// INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT OF
// THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF DOUGLAS W. SAUDER
// HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// DOUGLAS W. SAUDER SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT
// NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
// PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS"
// BASIS, AND DOUGLAS W. SAUDER HAS NO OBLIGATION TO PROVIDE MAINTENANCE,
// SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
//
//=============================================================================

#define DW_IMPLEMENTATION

#ifdef HAVE_CONFIG_H
#include "../config.h"
#endif

#include <mimelib/config.h>
#include <mimelib/debug.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <mimelib/string.h>
#include <mimelib/datetime.h>
#include <mimelib/token.h>
#include <time.h>

static char lWeekDay[7][4]
    = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
static char lMonth[12][4]
    = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
       "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

extern "C" int ParseRfc822Date(const char *str, struct tm *tms, int *z);
static DwInt32 ymd_to_jdnl(int year, int mon, int day, int julian);
static void jdnl_to_ymd(DwInt32 jdn, int *year, int *mon, int *day, int julian);
static DwUint32 my_inv_gmtime(struct tm* ptms);

const char* const DwDateTime::sClassName = "DwDateTime";


int DwDateTime::sDefaultZone = 0;
int DwDateTime::sIsDefaultZoneSet = 0;
DwDateTime* (*DwDateTime::sNewDateTime)(const DwString&,
    DwMessageComponent*) = 0;


DwDateTime* DwDateTime::NewDateTime(const DwString& aStr,
    DwMessageComponent* aParent)
{
    if (sNewDateTime) {
        return sNewDateTime(aStr, aParent);
    }
    else {
        return new DwDateTime(aStr, aParent);
    }
}


void DwDateTime::SetDefaultZone(int aZone)
{
    sDefaultZone = aZone;
    sIsDefaultZoneSet = 1;
}


DwDateTime::DwDateTime()
{
    Init();
    mIsModified = 1;
}


DwDateTime::DwDateTime(const DwDateTime& aDateTime)
  : DwFieldBody(aDateTime)
{
    mYear   = aDateTime.mYear;
    mMonth  = aDateTime.mMonth;
    mDay    = aDateTime.mDay;
    mHour   = aDateTime.mHour;
    mMinute = aDateTime.mMinute;
    mSecond = aDateTime.mSecond;
    mZone   = aDateTime.mZone;
}


DwDateTime::DwDateTime(const DwString& aStr, DwMessageComponent* aParent)
  : DwFieldBody(aStr, aParent)
{
    Init();
    mIsModified = 0;
}


void DwDateTime::Init()
{
    mClassId = kCidDateTime;
    mClassName = DwDateTime::sClassName;
    // Check if default time zone is set
    if (sIsDefaultZoneSet == 0) {
        // Use calls to gmtime() and localtime() to get the time difference
        // between local time and UTC (GMT) time.
        time_t t_now = time((time_t*) 0);
#if defined(HAVE_GMTIME_R)
        struct tm utc;
        gmtime_r(&t_now, &utc);
        struct tm local;
        localtime_r(&t_now, &local);
#else
        struct tm utc = *gmtime(&t_now);
        struct tm local = *localtime(&t_now);
#endif
        DwUint32 t_local = my_inv_gmtime(&local);
        DwUint32 t_utc = my_inv_gmtime(&utc);
        sDefaultZone = (int) (t_local - t_utc)/60;
        sIsDefaultZoneSet = 1;
    }
    // Set the time zone from the default time zone
    mZone = sDefaultZone;
    // Get the current calendar time
    time_t t_now = time((time_t*) 0);
    // Set year, month, day, hour, minute, and second from calendar time
    _FromCalendarTime(t_now);
}


DwDateTime::~DwDateTime()
{
}


const DwDateTime& DwDateTime::operator = (const DwDateTime& aDateTime)
{
    if (this == &aDateTime) return *this;
    DwFieldBody::operator = (aDateTime);
    mYear   = aDateTime.mYear;
    mMonth  = aDateTime.mMonth;
    mDay    = aDateTime.mDay;
    mHour   = aDateTime.mHour;
    mMinute = aDateTime.mMinute;
    mSecond = aDateTime.mSecond;
    mZone   = aDateTime.mZone;
    return *this;
}


DwUint32 DwDateTime::AsUnixTime() const
{
    struct tm tt;
    tt.tm_year = mYear - 1900;
    tt.tm_mon  = mMonth - 1;
    tt.tm_mday = mDay;
    tt.tm_hour = mHour;
    tt.tm_min  = mMinute;
    tt.tm_sec  = mSecond;
    DwUint32 t = my_inv_gmtime(&tt);
    t = (t == (DwUint32) -1) ? 0 : t;
    t -= mZone*60;
    return t;
}


void DwDateTime::FromUnixTime(DwUint32 aTime)
{
    _FromUnixTime(aTime);
    SetModified();
}


void DwDateTime::_FromUnixTime(DwUint32 aTime)
{
    time_t t = aTime + mZone*60;
#if defined(HAVE_GMTIME_R)
    struct tm tt;
    gmtime_r(&t, &tt);
#else
    struct tm tt = *gmtime(&t);
#endif
    mYear   = tt.tm_year + 1900;
    mMonth  = tt.tm_mon + 1;
    mDay    = tt.tm_mday;
    mHour   = tt.tm_hour;
    mMinute = tt.tm_min;
    mSecond = tt.tm_sec;
}

void DwDateTime::FromCalendarTime(time_t aTime)
{
    _FromCalendarTime(aTime);
    SetModified();
}


void DwDateTime::_FromCalendarTime(time_t aTime)
{
    // Note: the broken-down time is the only portable representation.
    // ANSI does not even require that time_t be an integer type; it could
    // be a double.  And, it doesn't even have to be in seconds.

    // Get the broken-down time.
#if defined(HAVE_GMTIME_R)
    struct tm tms_utc;
    gmtime_r(&aTime, &tms_utc);
#else
    struct tm tms_utc = *gmtime(&aTime);
#endif
    // Convert to UNIX time, using portable routine
    DwUint32 t_unix = my_inv_gmtime(&tms_utc);
    // Set from the UNIX time
    _FromUnixTime(t_unix);
}


DwInt32 DwDateTime::DateAsJulianDayNum() const
{
    DwInt32 jdn = ymd_to_jdnl(mYear, mMonth, mDay, -1);
    return jdn;
}


void DwDateTime::DateFromJulianDayNum(DwInt32 aJdn)
{
    jdnl_to_ymd(aJdn, &mYear, &mMonth, &mDay, -1);
    SetModified();
}


DwInt32 DwDateTime::TimeAsSecsPastMidnight() const
{
    DwInt32 n = mHour;
    n *= 60;
    n += mMinute;
    n *= 60;
    n += mSecond;
    return n;
}


void DwDateTime::TimeFromSecsPastMidnight(DwInt32 aSecs)
{
    mSecond = (int) (aSecs % 60);
    aSecs /= 60;
    mMinute = (int) (aSecs % 60);
    aSecs /= 60;
    mHour = (int) (aSecs % 24);
    SetModified();
}


void DwDateTime::Parse()
{
    mIsModified = 0;
    char buffer[80];
    char *str;
    int mustDelete;
    // Allocate memory from heap only in rare instances where the buffer
    // is too small.
    if (mString.length() >= 80) {
        mustDelete = 1;
        str = new char [mString.length()+1];
    }
    else {
        mustDelete = 0;
        str = buffer;
    }
    strncpy(str, mString.data(), mString.length());
    str[79] = 0;
    struct tm tms;
    int zone;
    int err = ParseRfc822Date(str, &tms, &zone);
    if (!err) {
        mYear   = tms.tm_year + 1900;
        mMonth  = tms.tm_mon+1;
        mDay    = tms.tm_mday;
        mHour   = tms.tm_hour;
        mMinute = tms.tm_min;
        mSecond = tms.tm_sec;
        mZone   = zone;
    }
    else /* if (err) */ {
        mYear   = 1970;
        mMonth  = 1;
        mDay    = 1;
        mHour   = 0;
        mMinute = 0;
        mSecond = 0;
        mZone   = 0;
    }
    if (mustDelete) {
        delete str;
    }
}


void DwDateTime::Assemble()
{
    if (!mIsModified) return;
    // Find the day of the week
    DwInt32 jdn = DateAsJulianDayNum();
    int dow = (int) ((jdn+1)%7);
    char sgn = (mZone < 0) ? '-' : '+';
    int z = (mZone < 0) ? -mZone : mZone;
    char buffer[80];
    sprintf(buffer, "%s, %d %s %4d %02d:%02d:%02d %c%02d%02d",
        lWeekDay[dow], mDay, lMonth[(mMonth-1)%12], mYear,
        mHour, mMinute, mSecond, sgn, z/60%24, z%60);
    mString = buffer;
    mIsModified = 0;
}


DwMessageComponent* DwDateTime::Clone() const
{
    return new DwDateTime(*this);
}


void DwDateTime::PrintDebugInfo(ostream& aStrm, int /*aDepth*/) const
{
#if defined (DW_DEBUG_VERSION)
    aStrm <<
    "---------------- Debug info for DwDateTime class ---------------\n";
    _PrintDebugInfo(aStrm);
#endif // defined (DW_DEBUG_VERSION)
}


void DwDateTime::_PrintDebugInfo(ostream& aStrm) const
{
#if defined (DW_DEBUG_VERSION)
    DwFieldBody::_PrintDebugInfo(aStrm);
    aStrm << "Date:             "
        << mYear << '-' << mMonth << '-' << mDay << ' '
        << mHour << ':' << mMinute << ':' << mSecond << ' '
        << mZone << '\n';
#endif // defined (DW_DEBUG_VERSION)
}


void DwDateTime::CheckInvariants() const
{
#if defined (DW_DEBUG_VERSION)
    DwFieldBody::CheckInvariants();
    assert(mYear >= 0);
    assert(1 <= mMonth && mMonth <= 12);
    assert(1 <= mDay && mDay <= 31);
    assert(0 <= mHour && mHour < 24);
    assert(0 <= mMinute && mMinute < 60);
    assert(0 <= mSecond && mSecond < 60);
    assert(-12*60 <= mZone && mZone <= 12*60);
#endif // defined (DW_DEBUG_VERSION)
}


#ifdef PAPAL                    /* Pope Gregory XIII's decree */
#define LASTJULDATE 15821004L   /* last day to use Julian calendar */
#define LASTJULJDN  2299160L    /* jdn of same */
#else                           /* British-American usage */
#define LASTJULDATE 17520902L   /* last day to use Julian calendar */
#define LASTJULJDN  2361221L    /* jdn of same */
#endif


static DwInt32 ymd_to_jdnl(int year, int mon, int day, int julian)
{
    DwInt32 jdn;

    if (julian < 0)         /* set Julian flag if auto set */
        julian = (((year * 100L) + mon) * 100 + day  <=  LASTJULDATE);

    if (year < 0)              /* adjust BC year */
        year++;

    if (julian)
        jdn = 367L * year - 7 * (year + 5001L + (mon - 9) / 7) / 4
        + 275 * mon / 9 + day + 1729777L;
    else
        jdn = (DwInt32)(day - 32075)
            + 1461L * (year + 4800L + (mon - 14) / 12) / 4
            + 367 * (mon - 2 - (mon - 14) / 12 * 12) / 12
            - 3 * ((year + 4900L + (mon - 14) / 12) / 100) / 4;

    return jdn;
}


static void jdnl_to_ymd(DwInt32 jdn, int *year, int *mon, int *day, int julian)
{
    DwInt32 x, z, m, d, y;
    DwInt32 daysPer400Years = 146097L;
    DwInt32 fudgedDaysPer4000Years = 1460970L + 31;

    if (julian < 0)                 /* set Julian flag if auto set */
        julian = (jdn <= LASTJULJDN);

    x = jdn + 68569L;
    if (julian) {
        x += 38;
        daysPer400Years = 146100L;
        fudgedDaysPer4000Years = 1461000L + 1;
    }
    z = 4 * x / daysPer400Years;
    x = x - (daysPer400Years * z + 3) / 4;
    y = 4000 * (x + 1) / fudgedDaysPer4000Years;
    x = x - 1461 * y / 4 + 31;
    m = 80 * x / 2447;
    d = x - 2447 * m / 80;
    x = m / 11;
    m = m + 2 - 12 * x;
    y = 100 * (z - 49) + y + x;

    *year = (int)y;
    *mon = (int)m;
    *day = (int)d;

    if (*year <= 0)                   /* adjust BC years */
        (*year)--;
}

#define JDN_JAN_1_1970  2440588L

/*
 * Converts broken-down time to time in seconds since 1 Jan 1970 00:00.
 * Pays no attention to time zone or daylight savings time.  Another way
 * to think about this function is that it is the inverse of gmtime().
 * One word of caution: the values in the broken down time must be
 * correct.
 *
 * This function is different from mktime() in three ways:
 * 1. mktime() accepts a broken-down local time and converts it to a scalar
 *    UTC time.  Thus, mktime() takes time zone and daylight savings time
 *    information into account when computing the scalar time.  (This makes
 *    mktime() highly non-portable).
 * 2. mktime() will adjust for non-standard values, such as a tm_mday member
 *    that is out of range.  This function does no such conversion.
 * 3. mktime() sets the struct fields tm_yday, tm_wday, and tm_isdst to
 *    their correct values on output.  This function does not.
 */
static DwUint32 my_inv_gmtime(struct tm* ptms)
{
    DwInt32 jdn;
    DwUint32 t;

    jdn = ymd_to_jdnl(ptms->tm_year+1900, ptms->tm_mon+1,
        ptms->tm_mday, -1);
    t = jdn - JDN_JAN_1_1970;  /* days    */
    t = 24*t + ptms->tm_hour;  /* hours   */
    t = 60*t + ptms->tm_min;   /* minutes */
    t = 60*t + ptms->tm_sec;   /* seconds */
    return t;
}
#endif //0 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#if 0  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/////////////////////////////////////////////////////////////////////////////
// GDateTime.hpp - GDateTime and GDateTimeSpan class declarations.

#ifndef GDATETIME_HPP
//#define GDATETIME_HPP

//class GDateTime;
//class GDateTimeSpan;

/*
Note:
 These functions are valid for dates between the years 1753 and 9999.
 Zero is recognised as a 'null date'.
*/

class GDateTime
{
public:
  //GDateTime();
  //GDateTime(int nYear, int nMonth, int nDay, int nHour, int nMinute, int nSecond);
  //GDateTime(const GDateTime& dt);
//  GDateTime(double dt); // Lotus Serial dates no longer supported

  /*
// Support for the MFC CTime class:
#ifdef __AFX_H__
  GDateTime(CTime ctime);
  operator CTime();
  void operator=(CTime ctime);
#endif  // __AFX_H__

// Support for SQL date/time types:
#ifdef __SQLTYPES
  GDateTime(const DATE_STRUCT& ds);
  GDateTime(const TIME_STRUCT& ts);
  GDateTime(const TIMESTAMP_STRUCT& ts);
  void operator=(const DATE_STRUCT& ds);
  void operator=(const TIME_STRUCT& ts);
  void operator=(const TIMESTAMP_STRUCT& ts);
#endif  // __SQLTYPES
*/
// Attributes:
public:
  // In the following functions:
  //    If bKeepTime == 0 then time part is set to zero (= midnight), else time part is kept as it is.
  //    If bKeepDate == 0 then date part is set to zero (= null date), else date part is kept as it is.

  void SetDate(int nYear, int nMonth, int nDay, int bKeepTime = 1);
  void SetDate(long date, int bKeepTime = 1);
  BOOL SetDate(const char* strDate, int* pnNextCharIndex = NULL);
      // Returns FALSE if not a valid date.
  void SetTime(int nHour, int nMinute, int nSecond, int bKeepDate = 1);
  void SetTime(long time, int bKeepDate = 1);
  BOOL SetTime(const char* strTime, int* pnNextCharIndex = NULL);
      // Returns FALSE if not a valid time.
  void SetDateTime(int nYear, int nMonth, int nDay, int nHour, int nMinute, int nSecond);
//  void SetDateTime(double LotusSerial); // Lotus Serial dates no longer supported
  BOOL SetDateTime(const char* strDateTime, int* pnNextCharIndex = NULL);
      // If time field not present, time set to zero. Returns FALSE if not a valid date or time.
  void SetYear(int nYear);
  void SetMonth(int nMonth);
  void SetDay(int nDay);
  void SetHour(int nHour);
  void SetMinute(int nMinute);
  void SetSecond(int nSecond);

  void GetDate(int* pnYear, int* pnMonth, int* pnDay) const;
  long GetDate() const { return m_date; }   // The date's serial number.
  void GetTime(int* pnHour, int* pnMinute, int* pnSecond) const;
  long GetTime() const { return m_time; }   // Number of seconds since midnight.
  int GetYear() const;
  int GetMonth() const;
  int GetDay() const;
  int GetHour() const;
  int GetMinute() const;
  int GetSecond() const;
//  double GetLotusSerial() const;  // Lotus Serial dates no longer supported

  long GetTimeTo(long time2) const;
  long GetDaysTo(const GDateTime& dt2) const { return dt2.m_date - m_date; }
  long GetDaysTo(const GDateTime& dt2, BOOL bIncludeWeekends) const;
  //GDateTimeSpan GetDateTimeSpanTo(GDateTime dt2) const;   // Not yet implemented.

  void SetNull() { m_date = 0; m_time = 0; }
  void SetNullDate() { m_date = 0; }
  void SetNullTime() { m_time = 0; }      // Note: null time is equivalent to midnight.
  void SetNullDateTime() { m_date = 0; m_time = 0; }

  int IsNullDate() const { return m_date == 0; }
  int IsNullTime() const { return m_time == 0; }  // Note: null time is equivalent to midnight.
  int IsNullDateTime() const { return m_date == 0 && m_time == 0; }
  int NotNullDate() const { return !IsNullDate(); }

  //int IsLeapYear() const { return IsLeapYear(GetYear()); }
  //int GetDaysInMonth() const { int y, m, d; GetDate(&y, &m, &d); return DaysInMonth(m, y); }
  int GetDayOfWeek() const;
  int IsWeekend() const { return GetDayOfWeek() > Friday; }
  int IsWeekday() const { return GetDayOfWeek() <= Friday; }

// Operations:
public:
  void Now();

  void AddTime(long nSeconds);
  void AddDateSpan(const GDateTimeSpan& span);
  void AddTimeSpan(const GDateTimeSpan& span);
  void AddDateTimeSpan(const GDateTimeSpan& span);
  void AddYears(long nYears);
  void AddMonths(long nMonths);
  void AddDays(long nDays);
  void AddDays(long nDays, BOOL bIncludeWeekends);
  void AddWeekDays(long nDays) { AddDays(nDays, FALSE); }
  void AddHours(long nHours);
  void AddMinutes(long nMinutes);
  void AddSeconds(long nSeconds);

  void SubTime(long nSeconds);
  void SubDateSpan(const GDateTimeSpan& span);
  void SubTimeSpan(const GDateTimeSpan& span);
  void SubDateTimeSpan(const GDateTimeSpan& span);
  void SubYears(long nYears);
  void SubMonths(long nMonths);
  void SubDays(long nDays);
  void SubDays(long nDays, BOOL bIncludeWeekends);
  void SubWeekDays(long nDays) { SubDays(nDays, FALSE); }
  void SubHours(long nHours);
  void SubMinutes(long nMinutes);
  void SubSeconds(long nSeconds);

  const GDateTime& operator=(const GDateTime& dt) { m_date = dt.m_date; m_time = dt.m_time; return *this; }
//  const GDateTime& operator=(double LotusSerial) { SetDateTime(LotusSerial); return *this; }
  const GDateTime& operator=(const char* strDateTime) { SetDateTime(strDateTime); return *this; }

  GDateTime operator+(const GDateTimeSpan& span) const { GDateTime dt(*this); dt.AddDateTimeSpan(span); return dt; }
  GDateTime operator-(const GDateTimeSpan& span) const { GDateTime dt(*this); dt.SubDateTimeSpan(span); return dt; }
  GDateTime& operator+=(const GDateTimeSpan& span) { AddDateTimeSpan(span); return *this; }
  GDateTime& operator-=(const GDateTimeSpan& span) { SubDateTimeSpan(span); return *this; }

  int operator==(const GDateTime& dt) const;
  int operator!=(const GDateTime& dt) const;
  int operator>(const GDateTime& dt) const;
  int operator<(const GDateTime& dt) const;
  int operator>=(const GDateTime& dt) const;
  int operator<=(const GDateTime& dt) const;

  operator const char*() const { return StrDateTime(); }

  const char* StrDate() const;
  const char* StrTime() const;
  const char* StrDateTime() const;
  const char* StrDayOfWeek() const;
  const char* StrMonth() const;

  // For use with sorting functions:
  const char* StrDateForSorting() const;    // Returns date in "yyyymmdd" format.
  const char* StrTimeForSorting() const;    // Returns time in "hhmmss" format.
  const char* StrDateTimeForSorting() const;  // Returns date and time in "yyyymmdd hhmmss" format.

  // For use with ODBC:
  const char* StrDateODBC() const;
  const char* StrTimeODBC() const;
  const char* StrDateTimeODBC() const;

  // For use with SQL Server only:
  const char* StrDateSQLServer() const;
  const char* StrTimeSQLServer() const;
  const char* StrDateTimeSQLServer() const;

  // Public helper functions:
  static int  IsLeapYear(int nYear);
  static int  DaysInMonth(int nMonth, int nYear);
  static long YMDToSerial(int nYear, int nMonth, int nDay);   // Returns Lotus Serial date.
  static long HMSToSerial(int nHour, int nMinute, int nSecond); // Returns Lotus Serial time.
  static int  IsValidDate(int nYear, int nMonth, int nDay);   // True if a valid date between 1900 and 2099, or all zeroes (a NULL date).
  static int  IsValidDate(const char* pszDateString);       // True if a valid date between 1900 and 2099 (NULL dates not allowed).
  static int  IsValidTime(int nHour, int nMinute, int nSecond); // True if a valid time between 00:00:00 and 23:59:59.
  static void AddCenturyToYear(int& nYear);


// Constants:
public:
  static const int  FirstValidYear; // 1753: The year following Britain's adoption of the Gregorian calendar (on 14 Sep 1752).
  static const int  LastValidYear;  // 9999: Chosen only because it's the last four-digit year. (Roll on the Y10K project!)
  static const int  FirstDOW;     // First day of week of First Valid Year.

  static const long SecondsPerMinute; // =    60; // = 60 (seconds)
  static const long SecondsPerHour; // =  3600; // = 60 (minutes) * 60 (seconds)
  static const long SecondsPerDay;  // = 86400; // = 24 (hours) * 60 (minutes) * 60 (seconds)
  static const long HoursPerDay;    // =    24; // = 24 (hours)
  static const long MinutesPerDay;  // =  1440; // = 24 (hours) * 60 (minutes)
  static const int  DaysPerWeek;    // =     7;
  static const int  MonthsPerYear;  // =    12;
  static const int  YearsPerCentury;  // =   100;

  static const char* DayNames[7];   // 0 to 6.
  static const char* MonthNames[13];  // 1 to 12.

  //enum enumDayOfWeek { Monday = 0, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };
  //enum enumMonthOfYear { January = 1, February, March, April, May, June, July, August,
  //        September, October, November, December };

// Helper functions:
protected:
  void    ToYMD(int* pnYear, int* pnMonth, int* pnDay) const;     // Returns all zeros if null date.
  void    ToHMS(int* pnHour, int* pnMinute, int* pnSecond) const;
  void    FromYMD(int nYear, int nMonth, int nDay);
  void    FromHMS(int nHour, int nMinute, int nSecond);

protected:
  long m_date;  // The Lotus serial date number.
  long m_time;  // Number of seconds since midnight.

private:
  // Julian/Gregorian calendar functions:
  static long ymd_to_jdnl(int y, int m, int d, int julian = 0);
  static void jdnl_to_ymd(long jdn, int *yy, int *mm, int *dd, int julian = 0);
  static int  jdnl_to_dow(long jdn);
  static int  jdnl_is_leap_year(long jdn);
};


/////////////////////////////////////////////////////////////////////////////

class GDateTimeSpan
{
public:
  GDateTimeSpan();
  GDateTimeSpan(long nYears, long nMonths, long nDays, long nHours, long nMinutes, long nSeconds);
  GDateTimeSpan(long nDays, long nSeconds); // nDays is currently ignored.
  GDateTimeSpan(const GDateTimeSpan& span);

  GDateTimeSpan(const GDateTime& dt1, const GDateTime& dt2);
    // dt1 must be less than (or equal to) dt2.
    // Assumes 365 days-per-year.

// Attributes:
public:
  void SetDateSpan(long nYears, long nMonths, long nDays, int bKeepTimeSpan = 1);
  BOOL SetDateSpan(const char* strDateSpan, int* pnNextCharIndex = NULL);
  void SetTimeSpan(long nHours, long nMinutes, long nSeconds, int bKeepDateSpan = 1);
  void SetTimeSpan(long nSeconds, int bKeepDateSpan = 1); // Hours may be set to larger than 23.
  BOOL SetTimeSpan(const char* strTimeSpan, int* pnNextCharIndex = NULL);
  void SetDateTimeSpan(long nYears, long nMonths, long nDays, long nHours, long nMinutes, long nSeconds);
  BOOL SetDateTimeSpan(const char* strDateTimeSpan, int* pnNextCharIndex = NULL);
  void SetDateTimeSpan(const GDateTimeSpan& span);
  void SetYears(int nYears) { m_years = nYears; }
  void SetMonths(int nMonths) { m_months = nMonths; }
  void SetDays(int nDays) { m_days = nDays; }
  void SetHours(int nHours) { m_hours = nHours; }
  void SetMinutes(int nMinutes) { m_minutes = nMinutes; }
  void SetSeconds(int nSeconds) { m_seconds = nSeconds; }

  void GetDateSpan(long* pnYears, long* pnMonths, long* pnDays) const;
  void GetTimeSpan(long* pnHours, long* pnMinutes, long* pnSeconds) const;
  long GetYears() const { return m_years; }
  long GetMonths() const { return m_months; }
  long GetDays() const { return m_days; }
  long GetHours() const { return m_hours; }
  long GetMinutes() const { return m_minutes; }
  long GetSeconds() const { return m_seconds; }

  long GetTime() const; // Returns hours + minutes + seconds (all in terms of seconds, of course).

  void SetZero();
  void SetZeroDateSpan();
  void SetZeroTimeSpan();

  int IsZero() const;
  int IsZeroDateSpan() const;
  int IsZeroTimeSpan() const;
  int NotZero() const { return !IsZero(); }
  int NotZeroDateSpan() const { return !IsZeroDateSpan(); }
  int NotZeroTimeSpan() const { return !IsZeroTimeSpan(); }

// Operations:
public:


  const GDateTimeSpan& operator=(const GDateTimeSpan& span) { SetDateTimeSpan(span); return *this; }
  const GDateTimeSpan& operator=(const char* strDateTimeSpan) { SetDateTimeSpan(strDateTimeSpan); return *this; }

  operator const char*() const { return StrDateTimeSpan(); }

  const char* StrDateSpan() const;
  const char* StrTimeSpan() const;
  const char* StrDateTimeSpan() const;


protected:
  long m_years;
  long m_months;
  long m_days;
  long m_hours;
  long m_minutes;
  long m_seconds;
};


#endif  // GDATETIME_HPP

/////////////////////////////////////////////////////////////////////////////
// GDateTime.cpp

#include "StdAfx.h"
#include <datetime.hpp>
#include <common.hpp>
#include <math.h>
#include <time.h>
#include <ctype.h>


#define LOTUS 0
#define GREGORIAN 1

//#define SERIAL_FORMAT LOTUS
//#define SERIAL_FORMAT GREGORIAN


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// GDateTime

#if SERIAL_FORMAT == GREGORIAN
const int  GDateTime::FirstValidYear  =  1753;  // 1753: The year following Britain's adoption of the Gregorian calendar (on 14 Sep 1752).
const int  GDateTime::LastValidYear   =  9999;  // 9999: Chosen only because it's the last four-digit year. (Roll on the Y10K project!)
const int  GDateTime::FirstDOW      =  0;   // First day of week of First Valid Year.
#else // LOTUS
const int  GDateTime::FirstValidYear  =  1970;
const int  GDateTime::LastValidYear   =  2039;
const int  GDateTime::FirstDOW      =  3;
#endif

const long GDateTime::SecondsPerMinute  =    60;  // = 60 (seconds)
const long GDateTime::SecondsPerHour  =  3600;  // = 60 (minutes) * 60 (seconds)
const long GDateTime::SecondsPerDay   = 86400;  // = 24 (hours) * 60 (minutes) * 60 (seconds)
const long GDateTime::HoursPerDay   =    24;  // = 24 (hours)
const long GDateTime::MinutesPerDay   =  1440;  // = 24 (hours) * 60 (minutes)
const int  GDateTime::DaysPerWeek   =     7;
const int  GDateTime::MonthsPerYear   =    12;
const int  GDateTime::YearsPerCentury =   100;

/*
const char* GDateTime::DayNames[7] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
const char* GDateTime::MonthNames[13] = { NULL, "January", "February", "March", "April", "May",
  "June", "July", "August", "September", "October", "November", "December" };
 */

#ifdef _DEBUG

#define ASSERT_YMD(y, m, d) \
  if (!(y == 0 && m == 0 && d == 0) && \
    ((y) < FirstValidYear || (y) > LastValidYear || (y) == 0 || (m) < 1 || (m) > 12 || (d) < 1 || (d) > 31)) \
    { \
    TRACE3("Invalid GDateTime date: %ld/%ld/%ld\n", long(d), long(m), long(y)); \
    ASSERT(0); \
    }

#define ASSERT_HMS(h, m, s) \
  if ((h) < 0 || (h) > 23 || (m) < 0 || (m) > 59 || (s) < 0 || (s) > 59) \
    { \
    TRACE3("Invalid GDateTime time: %ld/%ld/%ld\n", long(h), long(m), long(s)); \
    ASSERT(0); \
    }
#else
#define ASSERT_YMD(y, m, d)   ((void)0)
#define ASSERT_HMS(h, m, s)   ((void)0)
#endif


/////////////////////////////////////////////////////////////////////////////
// Constructors:

GDateTime::GDateTime()
{
  m_date = 0;
  m_time = 0;
}


GDateTime::GDateTime(int nYear, int nMonth, int nDay, int nHour, int nMinute, int nSecond)
  : m_date(0), m_time(0)
{
  SetDate(nYear, nMonth, nDay);
  SetTime(nHour, nMinute, nSecond);
}

GDateTime::GDateTime(const GDateTime& dt)
  : m_date(dt.m_date), m_time(dt.m_time)
{
}

/* Lotus Serial dates no longer supported

GDateTime::GDateTime(double dt)
  : m_date(0), m_time(0)
{
  SetDateTime(dt);
}
*/


/////////////////////////////////////////////////////////////////////////////
// Support for the MFC CTime class:

#ifdef __AFX_H__

GDateTime::GDateTime(CTime ctime)
{
  SetDate(ctime.GetYear(), ctime.GetMonth(), ctime.GetDay());
  SetTime(ctime.GetHour(), ctime.GetMinute(), ctime.GetSecond());
}

GDateTime::operator CTime()
{
  int nYear, nMonth, nDay;

  if (m_date == 0L)
    {
    GDateTime dtNow;
    dtNow.Now();

    nYear = dtNow.GetYear();
    nMonth = dtNow.GetMonth();
    nDay = dtNow.GetDay();
    }
  else
    {
    nYear = GetYear();
    nMonth = GetMonth();
    nDay = GetDay();
    }

  CTime ctime(nYear, nMonth, nDay, GetHour(), GetMinute(), GetSecond());
  return ctime;
}

void GDateTime::operator=(CTime ctime)
{
  SetDate(ctime.GetYear(), ctime.GetMonth(), ctime.GetDay());
  SetTime(ctime.GetHour(), ctime.GetMinute(), ctime.GetSecond());
}

#endif  // __AFX_H__


/////////////////////////////////////////////////////////////////////////////
// Support for SQL date/time types:
#ifdef __SQLTYPES

GDateTime::GDateTime(const DATE_STRUCT& ds)
  : m_date(0), m_time(0)
{
  SetDate(ds.year, ds.month, ds.day);
}

GDateTime::GDateTime(const TIME_STRUCT& ts)
  : m_date(0), m_time(0)
{
  SetTime(ts.hour, ts.minute, ts.second);
}

GDateTime::GDateTime(const TIMESTAMP_STRUCT& ts)
  : m_date(0), m_time(0)
{
  SetDate(ts.year, ts.month, ts.day);
  SetTime(ts.hour, ts.minute, ts.second);
}

void GDateTime::operator=(const DATE_STRUCT& ds)
{
  SetDate(ds.year, ds.month, ds.day, FALSE);
}

void GDateTime::operator=(const TIME_STRUCT& ts)
{
  SetTime(ts.hour, ts.minute, ts.second, FALSE);
}

void GDateTime::operator=(const TIMESTAMP_STRUCT& ts)
{
  SetDate(ts.year, ts.month, ts.day);
  SetTime(ts.hour, ts.minute, ts.second);
}

#endif  // __SQLTYPES


/////////////////////////////////////////////////////////////////////////////
// Attributes:

void GDateTime::SetDate(int nYear, int nMonth, int nDay, int bKeepTime /* = 1 */)
{
  ASSERT_YMD(nYear, nMonth, nDay);

  long date;
  if (nYear == 0 && nMonth == 0 && nDay == 0)
    date = 0L;
  else
    date = YMDToSerial(nYear, nMonth, nDay);
  if (!bKeepTime)
    m_time = 0;
  m_date = date;
}

void GDateTime::SetDate(long date, int bKeepTime /* = 1 */)
{
  if (!bKeepTime)
    m_time = 0;
  m_date = date;
}

BOOL GDateTime::SetDate(const char* strDate, int* pnNextCharIndex /* = NULL */)
{
  ASSERT(strDate != NULL);

  int val, year = 0, month = 0, day = 0;
  const char* p = strDate;
  const char* tmp;

  if (NotNullDate())
    ToYMD(&year, &month, &day);

  if (pnNextCharIndex)
    {
    ASSERT(*pnNextCharIndex <= (int) strlen(strDate));
    p += *pnNextCharIndex;
    }

// Skip any spaces and quotes:
  while (*p && strchr(" \"", *p))
    p++;

// Get day:
  if ((val = atoi(p)) == 0)
    goto end;
  day = val;
  if ((tmp = strchr(p, '/')) == NULL)
    goto end;
  p = tmp;

// Get month:
  if ((val = atoi(++p)) == 0)
    goto end;
  month = val;
  if ((tmp = strchr(p, '/')) == NULL)
    goto end;
  p = tmp;

// Get year:
  if ((val = atoi(++p)) == 0)
    {
    // If the year was not explicity set to zero,
    // keep whatever year the date object already has:
    if (p[0] != '0')
      goto end;
    }
  year = val;

  AddCenturyToYear(year);

  if (year < FirstValidYear || year > LastValidYear)
    return FALSE;

end:
// Skip rest of date and any quotes:
  while (*p && strchr("0123456789/\"", *p))
    p++;

  if (!IsValidDate(year, month, day))
    return FALSE;

  FromYMD(year, month, day);

  if (pnNextCharIndex)
    *pnNextCharIndex = p - strDate;

  return TRUE;
}

void GDateTime::SetTime(int nHour, int nMinute, int nSecond, int bKeepDate /* = 1 */)
{
  ASSERT_HMS(nHour, nMinute, nSecond);

  long time = HMSToSerial(nHour, nMinute, nSecond);
  if (!bKeepDate)
    m_date = 0;
  m_time = time;
}

void GDateTime::SetTime(long time, int bKeepDate /* = 1 */)
{
  if (!bKeepDate)
    m_date = 0;
  m_time = time;
}

BOOL GDateTime::SetTime(const char* strTime, int* pnNextCharIndex /* = NULL */)
{
  ASSERT(strTime != NULL);

  int hour = 0, minute = 0, second = 0;
  const char* p = strTime;
  const char* tmp;

  if (pnNextCharIndex)
    {
    ASSERT(*pnNextCharIndex <= (int) strlen(strTime));
    p += *pnNextCharIndex;
    }

// Skip any spaces and quotes:
  while (*p && strchr(" \"", *p))
    p++;

// Get hours:
  if (!isdigit(*p))
    goto end;
  hour = atoi(p);
  if ((tmp = strchr(p, ':')) == NULL)
    goto end;
  p = tmp;

// Get minutes:
  minute = atoi(++p);
  if ((tmp = strchr(p, ':')) == NULL)
    goto end;
  p = tmp;

// Get seconds:
  second = atoi(++p);

end:
// Skip rest of time and any quotes:
  while (*p && strchr("0123456789:\"", *p))
    p++;

  if (!IsValidTime(hour, minute, second))
    return FALSE;

  FromHMS(hour, minute, second);

  if (pnNextCharIndex)
    *pnNextCharIndex = p - strTime;

  return TRUE;
}

void GDateTime::SetDateTime(int nYear, int nMonth, int nDay, int nHour, int nMinute, int nSecond)
{
  m_date = YMDToSerial(nYear, nMonth, nDay);
  m_time = HMSToSerial(nHour, nMinute, nSecond);
}

/* Lotus Serial dates no longer supported
void GDateTime::SetDateTime(double LotusSerial)
{
  const double OneSecond = 1.0 / 86400.0;
  const double HalfSecond = OneSecond / 2.0;

  double date;
  double time = modf(LotusSerial, &date);   // 'date' gets the integer part of LotusSerial, 'time' the fractional part.
  m_date = (long) date;
  m_time = (long) ((time + HalfSecond) * 86400.0);
}
*/

BOOL GDateTime::SetDateTime(const char* strDateTime, int* pnNextCharIndex /* = NULL */)
{
  ASSERT(strDateTime != NULL);

  int index = (pnNextCharIndex ? *pnNextCharIndex : 0);

  if (!SetDate(strDateTime, &index))
    return FALSE;

  if (strchr(strDateTime + index, ':') != NULL)
    {
    if (!SetTime(strDateTime, &index))
      return FALSE;
    }
  else
    SetNullTime();

  if (pnNextCharIndex)
    *pnNextCharIndex = index;

  return TRUE;
}

void GDateTime::SetYear(int nYear)
{
  int year, month, day;
  ToYMD(&year, &month, &day);
  SetDate(nYear, month, day);
}

void GDateTime::SetMonth(int nMonth)
{
  int year, month, day;
  ToYMD(&year, &month, &day);
  SetDate(year, nMonth, day);
}

void GDateTime::SetDay(int nDay)
{
  int year, month, day;
  ToYMD(&year, &month, &day);
  SetDate(year, month, nDay);
}

void GDateTime::SetHour(int nHour)
{
  int hour, minute, second;
  ToHMS(&hour, &minute, &second);
  SetTime(nHour, minute, second);
}

void GDateTime::SetMinute(int nMinute)
{
  int hour, minute, second;
  ToHMS(&hour, &minute, &second);
  SetTime(hour, nMinute, second);
}

void GDateTime::SetSecond(int nSecond)
{
  int hour, minute, second;
  ToHMS(&hour, &minute, &second);
  SetTime(hour, minute, nSecond);
}

void GDateTime::GetDate(int* pnYear, int* pnMonth, int* pnDay) const
{
  ToYMD(pnYear, pnMonth, pnDay);
}

void GDateTime::GetTime(int* pnHour, int* pnMinute, int* pnSecond) const
{
  ToHMS(pnHour, pnMinute, pnSecond);
}

int GDateTime::GetYear() const
{
  int year, month, day;
  ToYMD(&year, &month, &day);
  return year;
}

int GDateTime::GetMonth() const
{
  int year, month, day;
  ToYMD(&year, &month, &day);
  return month;
}

int GDateTime::GetDay() const
{
  int year, month, day;
  ToYMD(&year, &month, &day);
  return day;
}

int GDateTime::GetHour() const
{
  int hour, minute, second;
  ToHMS(&hour, &minute, &second);
  return hour;
}

int GDateTime::GetMinute() const
{
  int hour, minute, second;
  ToHMS(&hour, &minute, &second);
  return minute;
}

int GDateTime::GetSecond() const
{
  int hour, minute, second;
  ToHMS(&hour, &minute, &second);
  return second;
}

/* Lotus Serial dates no longer supported
double GDateTime::GetLotusSerial() const
{
  double serial = double(m_date) + (double(m_time) / 86400.0);
  return serial;
}
*/

long GDateTime::GetTimeTo(long time2) const
{
  ASSERT(time2 >= m_time);

  return time2 - m_time;
}

long GDateTime::GetDaysTo(const GDateTime& dt2, BOOL bIncludeWeekends) const
{
  ASSERT(dt2 >= *this);

  long nDays;

  if (bIncludeWeekends)
    {
    // The easy one:
    nDays = dt2.m_date - m_date;
    }
  else
    {
    // The not-so-easy one:
    long nWeekendDays = ( (dt2.m_date - dt2.GetDayOfWeek()) - (m_date - GetDayOfWeek()) ) / 7L * 2L;
    long nDaysBetween = dt2.m_date - m_date;
    nDays = nDaysBetween - nWeekendDays;
    }

  return nDays;
}

/* I started but didn't finish...

GDateTimeSpan GDateTime::GetDateTimeSpanTo(GDateTime dt2) const
{
  ASSERT(dt2 >= *this);

  long time;
  int day, month, year;
  int days, months, years;

  time = m_time - dt2.m_time;
  if (time < 0)
    {
    dt2.SubDays(1);
    time += SecondsPerDay;
    }

  GetDate(&year, &month, &day);

  if (dt2.GetDay() >= day)
    {
    days = dt2.GetDay() - day;
    }
  else
    {
    
    }


  return GDateTimeSpan(years, months, days, hours, minutes, seconds);
}
*/

/////////////////////////////////////////////////////////////////////////////
// Operations:

void GDateTime::Now()
{
#ifdef WIN32

  SYSTEMTIME st;
  memset(&st, 0, sizeof(st));
  GetLocalTime(&st);
  SetDateTime(st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

#else

  struct tm *t;
  long ltime;
  time( &ltime );
  t = localtime( &ltime );
  SetDateTime(1900 + t->tm_year, 1 + t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

#endif  // WIN32
}

void GDateTime::AddTime(long nSeconds)
{
  AddSeconds(nSeconds);
}

void GDateTime::AddDateSpan(const GDateTimeSpan& span)
{
  AddDays(span.GetDays());
  AddMonths(span.GetMonths());
  AddYears(span.GetYears());
}


void GDateTime::AddTimeSpan(const GDateTimeSpan& span)
{
  AddSeconds(span.GetSeconds());
  AddMinutes(span.GetMinutes());
  AddHours(span.GetHours());
}

void GDateTime::AddDateTimeSpan(const GDateTimeSpan& span)
{
  AddSeconds(span.GetSeconds());
  AddMinutes(span.GetMinutes());
  AddHours(span.GetHours());
  AddDays(span.GetDays());
  AddMonths(span.GetMonths());
  AddYears(span.GetYears());
}

void GDateTime::AddYears(long nYears)
{
  int year, month, day;
  ToYMD(&year, &month, &day);
  FromYMD(year + int(nYears), month, day);
}

void GDateTime::AddMonths(long nMonths)
{
  int year, month, day;
  ToYMD(&year, &month, &day);
  month += int(nMonths);
  year += (month - 1) / MonthsPerYear;
  month = ((month - 1) % MonthsPerYear) + 1;

  int nDaysInMonth = DaysInMonth(month, year);
  if (day > nDaysInMonth)
    day = nDaysInMonth;

  FromYMD(year, month, day);
}

void GDateTime::AddDays(long nDays)
{
  m_date += nDays;
}

void GDateTime::AddDays(long nDays, BOOL bIncludeWeekends)
{
  ASSERT(nDays >= 0);

  if (bIncludeWeekends)
    {
    m_date += nDays;
    }
  else
    {
    long numWholeWeeks = nDays / 5L;  // Calc number of 5-day weeks...

    m_date += (numWholeWeeks * 7L);   // ...and add that number of *7-day* weeks to the date.
    nDays -= (numWholeWeeks * 5L);    // Reduce by number of days in those 5-day weeks.

    ASSERT(nDays >= 0L);

    while (nDays--)
      {
      m_date++;
      if (IsWeekend())
        {
        m_date++;
        m_date++;
        }
      }
    }
}

void GDateTime::AddHours(long nHours)
{
  AddSeconds(nHours * SecondsPerHour);
}

void GDateTime::AddMinutes(long nMinutes)
{
  AddSeconds(nMinutes * SecondsPerMinute);
}

void GDateTime::AddSeconds(long nSeconds)
{
    nSeconds += m_time;
    long days = nSeconds / SecondsPerDay;
    long seconds = nSeconds % SecondsPerDay;

    m_date += days;
    m_time = seconds;
}

void GDateTime::SubTime(long nSeconds)
{
  SubSeconds(nSeconds);
}

void GDateTime::SubDateSpan(const GDateTimeSpan& span)
{
  SubDays(span.GetDays());
  SubMonths(span.GetMonths());
  SubYears(span.GetYears());
}

void GDateTime::SubTimeSpan(const GDateTimeSpan& span)
{
  SubSeconds(span.GetSeconds());
  SubMinutes(span.GetMinutes());
  SubHours(span.GetHours());
}

void GDateTime::SubDateTimeSpan(const GDateTimeSpan& span)
{
  SubSeconds(span.GetSeconds());
  SubMinutes(span.GetMinutes());
  SubHours(span.GetHours());
  SubDays(span.GetDays());
  SubMonths(span.GetMonths());
  SubYears(span.GetYears());
}

void GDateTime::SubYears(long nYears)
{
  int year, month, day;
  ToYMD(&year, &month, &day);
  FromYMD(int(year - nYears), month, day);
}

void GDateTime::SubMonths(long nMonths)
{
  int year, month, day;
  ToYMD(&year, &month, &day);
  long MonthIndex = (year * MonthsPerYear) + month - 1;
  MonthIndex -= nMonths;
  year = int(MonthIndex / MonthsPerYear);
  month = int(MonthIndex % MonthsPerYear) + 1;

  int nDaysInMonth = DaysInMonth(month, year);
  if (day > nDaysInMonth)
    day = nDaysInMonth;

  FromYMD(year, month, day);
}

void GDateTime::SubDays(long nDays)
{
  ASSERT(nDays >= 0);

  m_date -= nDays;
}

void GDateTime::SubDays(long nDays, BOOL bIncludeWeekends)
{
  ASSERT(nDays >= 0);

  if (bIncludeWeekends)
    {
    m_date -= nDays;
    }
  else
    {
    long numWholeWeeks = nDays / 5L;  // Calc number of 5-day weeks...

    m_date -= (numWholeWeeks * 7L);   // ...and subtract that number of *7-day* weeks from the date.
    nDays -= (numWholeWeeks * 5L);    // Reduce by number of days in those 5-day weeks.

    ASSERT(nDays >= 0L);

    while (nDays--)
      {
      m_date--;
      if (IsWeekend())
        {
        m_date--;
        m_date--;
        }
      }
    }
}

void GDateTime::SubHours(long nHours)
{
  SubSeconds(nHours * SecondsPerHour);
}

void GDateTime::SubMinutes(long nMinutes)
{
  SubSeconds(nMinutes * SecondsPerMinute);
}

void GDateTime::SubSeconds(long nSeconds)
{
    nSeconds = m_time - nSeconds;

    if (nSeconds >= 0)
        {
        m_time = nSeconds;
        }
    else
        {
        long days = labs(nSeconds / SecondsPerDay) + 1;
        long seconds = SecondsPerDay - labs(nSeconds % SecondsPerDay);

        m_date -= days;
        m_time = seconds;
        }
}

/////////////////////////////////////////////////////////////////////////////

int GDateTime::operator==(const GDateTime& dt) const
{
  int result = (m_date == dt.m_date) && (m_time == dt.m_time);
  return result;
}

int GDateTime::operator!=(const GDateTime& dt) const
{
  int result = (m_date != dt.m_date) || (m_time != dt.m_time);
  return result;
}

int GDateTime::operator>(const GDateTime& dt) const
{
  int result =
    (m_date > dt.m_date) ||
    ((m_date == dt.m_date) && (m_time > dt.m_time));
  return result;
}

int GDateTime::operator<(const GDateTime& dt) const
{
  int result =
    (m_date < dt.m_date) ||
    ((m_date == dt.m_date) && (m_time < dt.m_time));
  return result;
}

int GDateTime::operator>=(const GDateTime& dt) const
{
  int result =
    (m_date > dt.m_date) ||
    ((m_date == dt.m_date) && (m_time >= dt.m_time));
  return result;
}

int GDateTime::operator<=(const GDateTime& dt) const
{
  int result =
    (m_date < dt.m_date) ||
    ((m_date == dt.m_date) && (m_time <= dt.m_time));
  return result;
}

/////////////////////////////////////////////////////////////////////////////

const char* GDateTime::StrDate() const
{
  int year, month, day;
  GetDate(&year, &month, &day);
  return form("%02d/%02d/%04d", day, month, year);
}

const char* GDateTime::StrTime() const
{
  int hour, minute, second;
  GetTime(&hour, &minute, &second);
  return form("%02d:%02d:%02d", hour, minute, second);
}

const char* GDateTime::StrDateTime() const
{
  int year, month, day, hour, minute, second;
  GetDate(&year, &month, &day);
  GetTime(&hour, &minute, &second);
  return form("%02d/%02d/%04d %02d:%02d:%02d", day, month, year, hour, minute, second);
}

const char* GDateTime::StrDayOfWeek() const
{
  return DayNames[GetDayOfWeek()];
}

const char* GDateTime::StrMonth() const
{
  return MonthNames[GetMonth()];
}


// For use with sorting functions:

const char* GDateTime::StrDateForSorting() const
{
  int year, month, day;
  GetDate(&year, &month, &day);
  return form("%04d%02d%02d", year, month, day);
}

const char* GDateTime::StrTimeForSorting() const
{
  int hour, minute, second;
  GetTime(&hour, &minute, &second);
  return form("%02d%02d%02d", hour, minute, second);
}

const char* GDateTime::StrDateTimeForSorting() const
{
  int year, month, day, hour, minute, second;
  GetDate(&year, &month, &day);
  GetTime(&hour, &minute, &second);
  return form("%04d%02d%02d %02d%02d%02d", year, month, day, hour, minute, second);
}


// For use with ODBC:

const char* GDateTime::StrDateODBC() const
{
  int year, month, day;
  GetDate(&year, &month, &day);
  return form("{d '%04d-%02d-%02d'}", year, month, day);
}

const char* GDateTime::StrTimeODBC() const
{
  int hour, minute, second;
  GetTime(&hour, &minute, &second);
  return form("{t '%02d:%02d:%02d'}", hour, minute, second);
}

const char* GDateTime::StrDateTimeODBC() const
{
  int year, month, day, hour, minute, second;
  GetDate(&year, &month, &day);
  GetTime(&hour, &minute, &second);
  return form("{ts '%04d-%02d-%02d %02d:%02d:%02d'}", year, month, day, hour, minute, second);
}


// For use with SQL Server only:

const char* GDateTime::StrDateSQLServer() const
{
  int year, month, day;
  GetDate(&year, &month, &day);
//  const char* p = form("'%02d %3.3s %04d'", day, MonthNames[month], year);
  const char* p = form("\"%02d %3.3s %04d\"", day, MonthNames[month], year);
  return p;
}

const char* GDateTime::StrTimeSQLServer() const
{
  int hour, minute, second;
  GetTime(&hour, &minute, &second);
  const char* p = form("'%02d:%02d:%02d'", hour, minute, second);
  return p;
}

const char* GDateTime::StrDateTimeSQLServer() const
{
  int year, month, day, hour, minute, second;
  GetDate(&year, &month, &day);
  GetTime(&hour, &minute, &second);
  const char* p = form("'%02d %3.3s %04d %02d:%02d:%02d'",
      day, MonthNames[month], year,
      hour, minute, second);
  return p;
}


/////////////////////////////////////////////////////////////////////////////
// Public helper functions:
/*
int GDateTime::IsLeapYear(int nYear)
{
  return ((nYear % 400 == 0) || ((nYear % 4 == 0) && (nYear % 100 != 0)));
}

int GDateTime::DaysInMonth(int nMonth, int nYear)
{
  static char _monthDays[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  if (nMonth == 2)
    return (IsLeapYear(nYear) ? 29 : 28);

  return _monthDays[nMonth];
}
*/
long GDateTime::YMDToSerial(int nYear, int nMonth, int nDay)
{
  long nSerial = 0L;

#if SERIAL_FORMAT == GREGORIAN

  nSerial = ymd_to_jdnl(nYear, nMonth, nDay);

#else // LOTUS

  ASSERT_YMD(nYear, nMonth, nDay);

  AddCenturyToYear(nYear);

  int year = nYear;

  year--;
  int leapYears = (year / 4) - (year / 100) + (year / 400);
  long totalDays = (year * 365L) + leapYears;
  year++;

  for (int i = 1; i < nMonth; ++i)
    totalDays += (long) DaysInMonth(i, year);

  totalDays += nDay;
    // This is the number of days since zero AD (assuming our Gregorian calendar extends back to then).

  nSerial = (totalDays - 693594L);    // Convert to Lotus Serial date.

#endif


  return nSerial;
}

long GDateTime::HMSToSerial(int nHour, int nMinute, int nSecond)
{
  ASSERT_HMS(nHour, nMinute, nSecond);

  long time = (nHour * SecondsPerHour) + (nMinute * SecondsPerMinute) + nSecond;
  return time;
}

int GDateTime::IsValidDate(int nYear, int nMonth, int nDay)
{
  if (nYear == 0 && nMonth == 0 && nDay == 0)
    return TRUE;

  AddCenturyToYear(nYear);

  if (nYear < FirstValidYear || nYear > LastValidYear)
    return FALSE;
  if (nMonth < 1 || nMonth > 12)
    return FALSE;
  if (nDay < 1 || nDay > DaysInMonth(nMonth, nYear))
    return FALSE;
  return TRUE;
}

int GDateTime::IsValidDate(const char* pszDateString)
{
  // Make sure we've been passed something:
  if (pszDateString == NULL)
    {
    ASSERT(0);
    return FALSE;
    }

  if (strlen(pszDateString) == 0)
    return FALSE;

  // Make sure the string contains only digits and slashes:
  const char* p = pszDateString;
  while (*p)
    {
    if (strchr("0123456789/", *p) == NULL)
      return FALSE;
    p++;
    }

  // Make sure the date is between FirstValidYear and LastValidYear (inclusive):
  GDateTime dtTest;
  if (!dtTest.SetDate(pszDateString))
    return FALSE;

  if (dtTest.IsNullDate())
    return FALSE; 

  // All okay:

  return TRUE;
}

int GDateTime::IsValidTime(int nHour, int nMinute, int nSecond)
{
  if (nHour < 0 || nHour > 23)
    return FALSE;
  if (nMinute < 0 || nMinute > 59)
    return FALSE;
  if (nSecond < 0 || nSecond > 59)
    return FALSE;
  return TRUE;
}


void GDateTime::AddCenturyToYear(int& nYear)
{
  // Ensure that the year is within scope:
  if ((nYear >= 0 && nYear <= 99) || (nYear >= FirstValidYear && nYear <= LastValidYear))
    ; // Year okay.
  else
    return;

  // If year already has a century, then do nothing to it:
  if (nYear > 99)
    return;

// Important: We assume that the two-digit year refers to a year within 50 years of the current year.

  // Get info on current date:
  GDateTime dtNow;
  dtNow.Now();
  int nCurrentFourDigitYear = dtNow.GetYear();
  int nCurrentTwoDigitYear = (nCurrentFourDigitYear % 100);
  int nCurrentCentury = int(nCurrentFourDigitYear / 100) * 100;

  // A little check to make sure the logic so far is correct:
  ASSERT(nCurrentFourDigitYear == (nCurrentCentury + nCurrentTwoDigitYear));  // i.e. 1997 == (1900 + 97)

  // First, assume that nYear refers to current century:
  nYear = (nCurrentCentury + nYear);

  // Next, if the resulting year is more than 50 years previous, assume year refers to the following century:
  if (nYear < (nCurrentFourDigitYear - 50))
    nYear += YearsPerCentury;
  // Otherwise, if the resulting year is more than 49 years hence, assume year refers to the previous century:
  else if (nYear > (nCurrentFourDigitYear + 49))
    nYear -= YearsPerCentury;


  // Finished.

/* Examples:

Current Year  Date Window
------------  -----------
1997      1947 - 2046
1998      1948 - 2047
1999      1949 - 2048
2000      1950 - 2049
2001      1951 - 2050

*/
}


/////////////////////////////////////////////////////////////////////////////
// Helper functions:

void GDateTime::ToYMD(int* pnYear, int* pnMonth, int* pnDay) const
{
  if (IsNullDate())
    {
    *pnYear = *pnMonth = *pnDay = 0;
    return;
    }


#if SERIAL_FORMAT == GREGORIAN

  jdnl_to_ymd(m_date, pnYear, pnMonth, pnDay);

#else // LOTUS

/*
  Minimum Lotus serial number:  6211 = 01/01/1917
  Maximum Lotus serial number: 73050 = 31/12/2099
*/
  long lotusSerial = m_date;

  if (lotusSerial < 6211L || lotusSerial > 73050L)
    {
    *pnYear = *pnMonth = *pnDay = 0;
    //ASSERT(0);
    TRACE("Invalid date in GDateTime::ToYMD (Lotus Serial = %ld)\n", lotusSerial);
    return;
    }

  const int BASEYEAR = 1917;
  static int M0[13] = { 0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };
  static int M1[13] = { 0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 };

  lotusSerial -= 6210L;

  int dd = int(lotusSerial % 1461L);
  int _year, _month, _day;

  if (dd == 0)
    {
    _year = BASEYEAR + int(lotusSerial / 1461L) * 4 - 1;
    _month = 12;
    _day = 31;
    }
  else
    {
    _year = BASEYEAR + int(lotusSerial / 1461L) * 4 + (dd - 1) / 365;

    dd = ((dd - 1) % 365) + 1;
    _month = 12;

    if ((_year % 4) == 0)
      {
      while (dd <= M1[_month])
        _month--;
      _day = dd - M1[_month];
      }
    else
      {
      while (dd <= M0[_month])
        _month--;
      _day = dd - M0[_month];
      }
    }

  *pnYear = _year;
  *pnMonth = _month;
  *pnDay = _day;

#endif
}


int GDateTime::GetDayOfWeek() const
{
  int dow = 0;  // Monday == 0, Tuesday == 1, etc.

#if SERIAL_FORMAT == GREGORIAN

  dow = jdnl_to_dow(m_date);

#else // LOTUS

  dow = int((m_date - 2L) % DaysPerWeek);

#endif

  return dow;
}


void GDateTime::ToHMS(int* pnHour, int* pnMinute, int* pnSecond) const
{
  long time = m_time;
  int hour, minute, second;

  hour = int(time / SecondsPerHour);
  time -= (hour * SecondsPerHour);

  minute = int(time / SecondsPerMinute);
  time -= (minute * SecondsPerMinute);

  second = int(time);

  *pnHour = hour;
  *pnMinute = minute;
  *pnSecond = second;
}

void GDateTime::FromYMD(int nYear, int nMonth, int nDay)
{
  if (nYear == 0 && nMonth == 0 && nDay == 0)
    m_date = 0;
  else
    m_date = YMDToSerial(nYear, nMonth, nDay);
}

void GDateTime::FromHMS(int nHour, int nMinute, int nSecond)
{
  m_time = HMSToSerial(nHour, nMinute, nSecond);
}


/////////////////////////////////////////////////////////////////////////////
/* public domain Julian Day Number functions
**
** Based on formulae originally posted by
**    Tom Van Flandern / Washington, DC / metares@well.sf.ca.us
**       in the UseNet newsgroup sci.astro.
**    Reposted 14 May 1991 in FidoNet C Echo conference by
**       Paul Schlyter (Stockholm)
** Minor corrections, added JDN to julian, and recast into C by
**    Raymond Gardner  Englewood, Colorado
**
** Synopsis:
**      long ymd_to_jdnl(int year, int month, int day, int julian_flag)
**      void jdnl_to_ymd(long jdnl, int *year, int *month, int *day,
**                                                      int julian_flag)
**      year is negative if BC
**      if julian_flag is >  0, use Julian calendar
**      if julian_flag is == 0, use Gregorian calendar
**      if julian_flag is <  0, routines decide based on date
**
** These routines convert Gregorian and Julian calendar dates to and
** from Julian Day Numbers.  Julian Day Numbers (JDN) are used by
** astronomers as a date/time measure independent of calendars and
** convenient for computing the elapsed time between dates.  The JDN
** for any date/time is the number of days (including fractional
** days) elapsed since noon, 1 Jan 4713 BC.  Julian Day Numbers were
** originated by Joseph Scaliger in 1582 and named after his father
** Julius, not after Julius Caesar.  They are not related to the
** Julian calendar.
**
** For dates from 1 Jan 4713 BC thru 12 Dec Feb 32766 AD, ymd_to_jdnl()
** will give the JDN for noon on that date.  jdnl_to_ymd() will compute
** the year, month, and day from the JDN.  Years BC are given (and
** returned) as negative numbers.  Note that there is no year 0 BC;
** the day before 1 Jan 1 AD is 31 Dec 1 BC.  Note also that 1 BC,
** 5 BC, etc. are leap years.
**
** Pope Gregory XIII decreed that the Julian calendar would end on
** 4 Oct 1582 AD and that the next day would be 15 Oct 1582 in the
** Gregorian Calendar.  The only other change is that centesimal
** years (years ending in 00) would no longer be leap years
** unless divisible by 400.  Britain and its possessions and
** colonies continued to use the Julian calendar up until 2 Sep
** 1752, when the next day became 14 Sep 1752 in the Gregorian
** Calendar.  These routines can be compiled to use either
** convention.  By default, the British convention will be used.
** Simply #define PAPAL to use Pope Gregory's convention.
**
** Each routine takes, as its last argument, a flag to indicate
** whether to use the Julian or Gregorian calendar convention.  If
** this flag is negative, the routines decide based on the date
** itself, using the changeover date described in the preceding
** paragraph.  If the flag is zero, Gregorian conventions will be used,
** and if the flag is positive, Julian conventions will be used.
**
** Proper JDN's are always floating point values so as to include the
** time as well as the date. These functions avoid the overhead of
** floating point math by computing only the integral value of the JDN.
*/

//#include "datetime.h"

//#ifdef PAPAL                    /* Pope Gregory XIII's decree */
//#define LASTJULDATE 15821004L   /* last day to use Julian calendar */
//#define LASTJULJDN  2299160L    /* jdn of same */
//#else                           /* British-American usage */

#define LASTJULDATE 17520902L   /* last day to use Julian calendar */
#define LASTJULJDN  2361221L    /* jdn of same */

//#endif


long GDateTime::ymd_to_jdnl(int y, int m, int d, int julian /* = 0 */)
{
        long jdn;

        if (julian < 0)         /* set Julian flag if auto set */
                julian = (((y * 100L) + m) * 100 + d  <=  LASTJULDATE);

        if (y < 0)              /* adjust BC year */
                y++;

        if (julian)
                jdn = 367L * y - 7 * (y + 5001L + (m - 9) / 7) / 4
                + 275 * m / 9 + d + 1729777L;
        else
                jdn = (long)(d - 32076)
                + 1461L * (y + 4800L + (m - 14) / 12) / 4
                + 367 * (m - 2 - (m - 14) / 12 * 12) / 12
                - 3 * ((y + 4900L + (m - 14) / 12) / 100) / 4
                + 1;            /* correction by rdg */

        return jdn;
}


void GDateTime::jdnl_to_ymd(long jdn, int *yy, int *mm, int *dd, int julian /* = 0 */)
{
        long x, z, m, d, y;
        long daysPer400Years = 146097L;
        long fudgedDaysPer4000Years = 1460970L + 31;

        if (julian < 0)                 /* set Julian flag if auto set */
                julian = (jdn <= LASTJULJDN);

        x = jdn + 68569L;
        if ( julian )
        {
                x += 38;
                daysPer400Years = 146100L;
                fudgedDaysPer4000Years = 1461000L + 1;
        }
        z = 4 * x / daysPer400Years;
        x = x - (daysPer400Years * z + 3) / 4;
        y = 4000 * (x + 1) / fudgedDaysPer4000Years;
        x = x - 1461 * y / 4 + 31;
        m = 80 * x / 2447;
        d = x - 2447 * m / 80;
        x = m / 11;
        m = m + 2 - 12 * x;
        y = 100 * (z - 49) + y + x;

        *yy = (int)y;
        *mm = (int)m;
        *dd = (int)d;

        if (*yy <= 0)                   /* adjust BC years */
                (*yy)--;
}

// And these are Carl's functions:

int GDateTime::jdnl_to_dow(long jdn)
{
  int dow = 0;

  if (jdn == 0)
    dow = 0;
  else if (jdn <= LASTJULJDN)
    dow = int(jdn % DaysPerWeek);
  else
    dow = int(jdn % DaysPerWeek);

  return dow;
}

int GDateTime::jdnl_is_leap_year(long jdn)
{
  int is_leap = 0;

  if (jdn == 0)
    is_leap = 0;
  else if (jdn <= LASTJULJDN)
    is_leap = int(jdn % DaysPerWeek);
  else
    is_leap = int(jdn % DaysPerWeek);

  return is_leap;
}



/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// GDateTimeSpan


/////////////////////////////////////////////////////////////////////////////
// Constructors:

GDateTimeSpan::GDateTimeSpan()
{
  m_years = 0;
  m_months = 0;
  m_days = 0;
  m_hours = 0;
  m_minutes = 0;
  m_seconds = 0;
}

GDateTimeSpan::GDateTimeSpan(long nYears, long nMonths, long nDays, long nHours, long nMinutes, long nSeconds)
{
  SetDateSpan(nYears, nMonths, nDays);
  SetTimeSpan(nHours, nMinutes, nSeconds);
}

GDateTimeSpan::GDateTimeSpan(long /* nDays */, long nSeconds)
{
  SetTimeSpan(nSeconds, 0);
}

GDateTimeSpan::GDateTimeSpan(const GDateTimeSpan& span)
{
  m_years = span.m_years;
  m_months = span.m_months;
  m_days = span.m_days;
  m_hours = span.m_hours;
  m_minutes = span.m_minutes;
  m_seconds = span.m_seconds;
}

GDateTimeSpan::GDateTimeSpan(const GDateTime& dt1, const GDateTime& dt2)
{
  ASSERT(dt1 <= dt2);

// The following is a subtraction: dt2 - dt1.

  int nCarry = 0;

  m_seconds = dt2.GetSecond() - dt1.GetSecond();
  if (m_seconds < 0)
    {
    m_seconds += 60;
    nCarry = 1;   // Carry over a minute.
    }
  else
    nCarry = 0;

  m_minutes = dt2.GetMinute() - (dt1.GetMinute() + nCarry);
  if (m_minutes < 0)
    {
    m_minutes += 60;
    nCarry = 1;   // Carry over a hour.
    }
  else
    nCarry = 0;

  m_hours = dt2.GetHour() - (dt1.GetHour() + nCarry);
  if (m_hours < 0)
    {
    m_hours += 24;
    nCarry = 1;   // Carry over a day.
    }
  else
    nCarry = 0;

  GDateTime dtTmp(dt2);

  if (nCarry)
    dtTmp.SubDays(nCarry);

  m_days = 0;
  while (dtTmp.GetDay() < dt1.GetDay() && dtTmp.GetDate() > dt1.GetDate())
    {
    m_days++;
    dtTmp.SubDays(1);
    }

  m_days += (dtTmp.GetDay() - dt1.GetDay());

  m_months = dtTmp.GetMonth() - dt1.GetMonth();
  if (m_months < 0)
    {
    m_months += 12;
    nCarry = 1;   // Carry over a year.
    }
  else
    nCarry = 0;

  m_years = dtTmp.GetYear() - (dt1.GetYear() + nCarry);
}


/////////////////////////////////////////////////////////////////////////////
// Attributes:

void GDateTimeSpan::SetDateSpan(long nYears, long nMonths, long nDays, int bKeepTimeSpan /* = 1 */)
{
  m_years = nYears;
  m_months = nMonths;
  m_days = nDays;

  if (!bKeepTimeSpan)
    {
    m_hours = 0;
    m_minutes = 0;
    m_seconds = 0;
    }
}

BOOL GDateTimeSpan::SetDateSpan(const char* strDateSpan, int* pnNextCharIndex /* = NULL */)
{
  ASSERT(strDateSpan != NULL);

  long val;
  const char* p = strDateSpan;
  const char* tmp;

  m_years = m_months = m_days = 0;

  if (pnNextCharIndex)
    p += *pnNextCharIndex;

// Skip any spaces and quotes:
  while (strchr(" \"", *p))
    p++;

// Get days:
  if ((val = atol(p)) == 0)
    goto end;
  m_days = val;
  if ((tmp = strchr(p, '/')) == NULL)
    goto end;
  p = tmp;

// Get months:
  if ((val = atoi(++p)) == 0)
    goto end;
  m_months = val;
  if ((tmp = strchr(p, '/')) == NULL)
    goto end;
  p = tmp;

// Get years:
  if ((val = atoi(++p)) == 0)
    goto end;
  m_years = val;

end:
// Skip rest of datespan and any quotes:
  while (*p && strchr("0123456789/\"", *p))
    p++;

  if (pnNextCharIndex)
    *pnNextCharIndex = p - strDateSpan;

  return TRUE;
}

void GDateTimeSpan::SetTimeSpan(long nHours, long nMinutes, long nSeconds, int bKeepDateSpan /* = 1 */)
{
  m_hours = nHours;
  m_minutes = nMinutes;
  m_seconds = nSeconds;

  if (!bKeepDateSpan)
    {
    m_years = 0;
    m_months = 0;
    m_days = 0;
    }
}

void GDateTimeSpan::SetTimeSpan(long nSeconds, int bKeepDateSpan /* = 1 */)
{
  m_hours = nSeconds / GDateTime::SecondsPerHour;
  nSeconds -= (m_hours * GDateTime::SecondsPerHour);
  m_minutes = nSeconds / GDateTime::SecondsPerMinute;
  nSeconds -= (m_minutes * GDateTime::SecondsPerMinute);
  m_seconds = nSeconds;

  if (!bKeepDateSpan)
    SetZeroDateSpan();
}

BOOL GDateTimeSpan::SetTimeSpan(const char* strTimeSpan, int* pnNextCharIndex /* = NULL */)
{
  ASSERT(strTimeSpan != NULL);

  int hours, minutes, seconds;
  GDateTime dt;

  dt.SetTime(strTimeSpan, pnNextCharIndex);
  dt.GetTime(&hours, &minutes, &seconds);
  m_hours = hours;
  m_minutes = minutes;
  m_seconds = seconds;

  return TRUE;
}

void GDateTimeSpan::SetDateTimeSpan(long nYears, long nMonths, long nDays, long nHours, long nMinutes, long nSeconds)
{
  SetDateSpan(nYears, nMonths, nDays);
  SetTimeSpan(nHours, nMinutes, nSeconds);
}

BOOL GDateTimeSpan::SetDateTimeSpan(const char* strDateTimeSpan, int* pnNextCharIndex /* = NULL */)
{
  ASSERT(strDateTimeSpan != NULL);

  int index = (pnNextCharIndex ? *pnNextCharIndex : 0);

  if (!SetDateSpan(strDateTimeSpan, &index))
    return FALSE;

  if (strchr(strDateTimeSpan + index, ':') != NULL)
    if (!SetTimeSpan(strDateTimeSpan, &index))
      return FALSE;

  if (pnNextCharIndex)
    *pnNextCharIndex = index;

  return TRUE;
}

void GDateTimeSpan::SetDateTimeSpan(const GDateTimeSpan& span)
{
  m_years = span.m_years;
  m_months = span.m_months;
  m_days = span.m_days;
  m_hours = span.m_hours;
  m_minutes = span.m_minutes;
  m_seconds = span.m_seconds;
}

void GDateTimeSpan::GetDateSpan(long* pnYears, long* pnMonths, long* pnDays) const
{
  *pnYears = m_years;
  *pnMonths = m_months;
  *pnDays = m_days;
}

void GDateTimeSpan::GetTimeSpan(long* pnHours, long* pnMinutes, long* pnSeconds) const
{
  *pnHours = m_hours;
  *pnMinutes = m_minutes;
  *pnSeconds = m_seconds;
}

long GDateTimeSpan::GetTime() const
{
  long time =
    (m_hours * GDateTime::SecondsPerHour) +
    (m_minutes * GDateTime::SecondsPerMinute) +
    (m_seconds);
  return time;
}

void GDateTimeSpan::SetZero()
{
  SetZeroDateSpan();
  SetZeroTimeSpan();
}

void GDateTimeSpan::SetZeroDateSpan()
{
  m_years = m_months = m_days = 0;
}

void GDateTimeSpan::SetZeroTimeSpan()
{
  m_hours = m_minutes = m_seconds = 0;
}

int GDateTimeSpan::IsZero() const
{
  return IsZeroDateSpan() && IsZeroTimeSpan();
}

int GDateTimeSpan::IsZeroDateSpan() const
{
  return m_years == 0 && m_months == 0 && m_days == 0;
}

int GDateTimeSpan::IsZeroTimeSpan() const
{
  return m_hours == 0 && m_minutes == 0 && m_seconds == 0;
}


/////////////////////////////////////////////////////////////////////////////
// Operations:

const char* GDateTimeSpan::StrDateSpan() const
{
  return form("%ld/%ld/%ld", m_days, m_months, m_years);
}

const char* GDateTimeSpan::StrTimeSpan() const
{
  return form("%ld:%ld:%ld", m_hours, m_minutes, m_seconds);
}

const char* GDateTimeSpan::StrDateTimeSpan() const
{
  return form("%s %s", StrDateSpan(), StrTimeSpan());
}
#endif //0 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#if 0  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/* Copyright (C) 2000, 2001  SWsoft, Singapore
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*  $Id: datetime.cpp,v 1.11 2001/08/20 12:23:38 kir Exp $
 *  Author: Kir Kolyshkin
 */

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "defines.h"
#include "datetime.h"

/* Function to convert date returned by web-server to time_t
 *
 * Earlier we used strptime, but it seems to be completely broken
 * on Solaris 2.6. Thanks to Maciek Uhlig <muhlig@us.edu.pl> for pointing
 * out this and bugfix proposal (to use Apache's ap_parseHTTPdate).
 *
 * 10 July 2000 kir.
 */


/*****
 *  BEGIN: Below is taken from Apache's util_date.c
 */

/* ====================================================================
 * Copyright (c) 1996-1999 The Apache Group.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the Apache Group
 *    for use in the Apache HTTP server project (http://www.apache.org/)."
 *
 * 4. The names "Apache Server" and "Apache Group" must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission. For written permission, please contact
 *    apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache"
 *    nor may "Apache" appear in their names without prior written
 *    permission of the Apache Group.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the Apache Group
 *    for use in the Apache HTTP server project (http://www.apache.org/)."
 *
 * THIS SOFTWARE IS PROVIDED BY THE APACHE GROUP ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE APACHE GROUP OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Group and was originally based
 * on public domain software written at the National Center for
 * Supercomputing Applications, University of Illinois, Urbana-Champaign.
 * For more information on the Apache Group and the Apache HTTP server
 * project, please see <http://www.apache.org/>.
 *
 */

/********
 * BEGIN
 * This is taken from ap_ctype.h
 * --kir.
 */

#include <ctype.h>

#ifdef __cplusplus
extern "C" {
#endif

/* These macros allow correct support of 8-bit characters on systems which
 * support 8-bit characters.  Pretty dumb how the cast is required, but
 * that's legacy libc for ya.  These new macros do not support EOF like
 * the standard macros do.  Tough.
 */
#define ap_isalnum(c) (isalnum(((unsigned char)(c))))
#define ap_isalpha(c) (isalpha(((unsigned char)(c))))
#define ap_iscntrl(c) (iscntrl(((unsigned char)(c))))
#define ap_isdigit(c) (isdigit(((unsigned char)(c))))
#define ap_isgraph(c) (isgraph(((unsigned char)(c))))
#define ap_islower(c) (islower(((unsigned char)(c))))
#define ap_isprint(c) (isprint(((unsigned char)(c))))
#define ap_ispunct(c) (ispunct(((unsigned char)(c))))
#define ap_isspace(c) (isspace(((unsigned char)(c))))
#define ap_isupper(c) (isupper(((unsigned char)(c))))
#define ap_isxdigit(c) (isxdigit(((unsigned char)(c))))
#define ap_tolower(c) (tolower(((unsigned char)(c))))
#define ap_toupper(c) (toupper(((unsigned char)(c))))

#ifdef __cplusplus
}
#endif

/*******
 * END of taken from ap_ctype.h
 */

/*
 * Compare a string to a mask
 * Mask characters (arbitrary maximum is 256 characters, just in case):
 *   @ - uppercase letter
 *   $ - lowercase letter
 *   & - hex digit
 *   # - digit
 *   ~ - digit or space
 *   * - swallow remaining characters
 *  <x> - exact match for any other character
 */
int ap_checkmask(const char *data, const char *mask)
{
    int i;
    char d;

    for (i = 0; i < 256; i++) {
        d = data[i];
        switch (mask[i]) {
        case '\0':
            return (d == '\0');

        case '*':
            return 1;

        case '@':
            if (!ap_isupper(d))
                return 0;
            break;
        case '$':
            if (!ap_islower(d))
                return 0;
            break;
        case '#':
            if (!ap_isdigit(d))
                return 0;
            break;
        case '&':
            if (!ap_isxdigit(d))
                return 0;
            break;
        case '~':
            if ((d != ' ') && !ap_isdigit(d))
                return 0;
            break;
        default:
            if (mask[i] != d)
                return 0;
            break;
        }
    }
    return 0;                   /* We only get here if mask is corrupted (exceeds 256) */
}

/*
 * tm2sec converts a GMT tm structure into the number of seconds since
 * 1st January 1970 UT.  Note that we ignore tm_wday, tm_yday, and tm_dst.
 *
 * The return value is always a valid time_t value -- (time_t)0 is returned
 * if the input date is outside that capable of being represented by time(),
 * i.e., before Thu, 01 Jan 1970 00:00:00 for all systems and
 * beyond 2038 for 32bit systems.
 *
 * This routine is intended to be very fast, much faster than mktime().
 */
time_t ap_tm2sec(const struct tm * t)
{
    int year;
    time_t days;
    static const int dayoffset[12] =
    {306, 337, 0, 31, 61, 92, 122, 153, 184, 214, 245, 275};

    year = t->tm_year;

    if (year < 70 || ((sizeof(time_t) <= 4) && (year >= 138)))
        return BAD_DATE;

    /* shift new year to 1st March in order to make leap year calc easy */

    if (t->tm_mon < 2)
        year--;

    /* Find number of days since 1st March 1900 (in the Gregorian calendar). */

    days = year * 365 + year / 4 - year / 100 + (year / 100 + 3) / 4;
    days += dayoffset[t->tm_mon] + t->tm_mday - 1;
    days -= 25508;              /* 1 jan 1970 is 25508 days since 1 mar 1900 */

    days = ((days * 24 + t->tm_hour) * 60 + t->tm_min) * 60 + t->tm_sec;

    if (days < 0)
        return BAD_DATE;        /* must have overflowed */
    else
        return days;                /* must be a valid time */
}

/*
 * Parses an HTTP date in one of three standard forms:
 *
 *     Sun, 06 Nov 1994 08:49:37 GMT  ; RFC 822, updated by RFC 1123
 *     Sunday, 06-Nov-94 08:49:37 GMT ; RFC 850, obsoleted by RFC 1036
 *     Sun Nov  6 08:49:37 1994       ; ANSI C's asctime() format
 *
 * and returns the time_t number of seconds since 1 Jan 1970 GMT, or
 * 0 if this would be out of range or if the date is invalid.
 *
 * The restricted HTTP syntax is
 *
 *     HTTP-date    = rfc1123-date | rfc850-date | asctime-date
 *
 *     rfc1123-date = wkday "," SP date1 SP time SP "GMT"
 *     rfc850-date  = weekday "," SP date2 SP time SP "GMT"
 *     asctime-date = wkday SP date3 SP time SP 4DIGIT
 *
 *     date1        = 2DIGIT SP month SP 4DIGIT
 *                    ; day month year (e.g., 02 Jun 1982)
 *     date2        = 2DIGIT "-" month "-" 2DIGIT
 *                    ; day-month-year (e.g., 02-Jun-82)
 *     date3        = month SP ( 2DIGIT | ( SP 1DIGIT ))
 *                    ; month day (e.g., Jun  2)
 *
 *     time         = 2DIGIT ":" 2DIGIT ":" 2DIGIT
 *                    ; 00:00:00 - 23:59:59
 *
 *     wkday        = "Mon" | "Tue" | "Wed"
 *                  | "Thu" | "Fri" | "Sat" | "Sun"
 *
 *     weekday      = "Monday" | "Tuesday" | "Wednesday"
 *                  | "Thursday" | "Friday" | "Saturday" | "Sunday"
 *
 *     month        = "Jan" | "Feb" | "Mar" | "Apr"
 *                  | "May" | "Jun" | "Jul" | "Aug"
 *                  | "Sep" | "Oct" | "Nov" | "Dec"
 *
 * However, for the sake of robustness (and Netscapeness), we ignore the
 * weekday and anything after the time field (including the timezone).
 *
 * This routine is intended to be very fast; 10x faster than using sscanf.
 *
 * Originally from Andrew Daviel <andrew@vancouver-webpages.com>, 29 Jul 96
 * but many changes since then.
 *
 */
time_t httpDate2time_t(const char *date){
    struct tm ds;
    int mint, mon;
    const char *monstr, *timstr;
    static const int months[12] =
    {
        ('J' << 16) | ('a' << 8) | 'n', ('F' << 16) | ('e' << 8) | 'b',
        ('M' << 16) | ('a' << 8) | 'r', ('A' << 16) | ('p' << 8) | 'r',
        ('M' << 16) | ('a' << 8) | 'y', ('J' << 16) | ('u' << 8) | 'n',
        ('J' << 16) | ('u' << 8) | 'l', ('A' << 16) | ('u' << 8) | 'g',
        ('S' << 16) | ('e' << 8) | 'p', ('O' << 16) | ('c' << 8) | 't',
        ('N' << 16) | ('o' << 8) | 'v', ('D' << 16) | ('e' << 8) | 'c'};

    if (!date)
        return BAD_DATE;

    while (*date && ap_isspace(*date))  /* Find first non-whitespace char */
        ++date;

    if (*date == '\0')
        return BAD_DATE;

    if ((date = strchr(date, ' ')) == NULL)     /* Find space after weekday */
        return BAD_DATE;

    ++date;                     /* Now pointing to first char after space, which should be */
    /* start of the actual date information for all 3 formats. */

    if (ap_checkmask(date, "## @$$ #### ##:##:## *")) { /* RFC 1123 format */
        ds.tm_year = ((date[7] - '0') * 10 + (date[8] - '0') - 19) * 100;
        if (ds.tm_year < 0)
            return BAD_DATE;

        ds.tm_year += ((date[9] - '0') * 10) + (date[10] - '0');

        ds.tm_mday = ((date[0] - '0') * 10) + (date[1] - '0');

        monstr = date + 3;
        timstr = date + 12;
    }
    else if (ap_checkmask(date, "##-@$$-## ##:##:## *")) {              /* RFC 850 format  */
        ds.tm_year = ((date[7] - '0') * 10) + (date[8] - '0');
        if (ds.tm_year < 70)
            ds.tm_year += 100;

        ds.tm_mday = ((date[0] - '0') * 10) + (date[1] - '0');

        monstr = date + 3;
        timstr = date + 10;
    }
    else if (ap_checkmask(date, "@$$ ~# ##:##:## ####*")) {     /* asctime format  */
        ds.tm_year = ((date[16] - '0') * 10 + (date[17] - '0') - 19) * 100;
        if (ds.tm_year < 0)
            return BAD_DATE;

        ds.tm_year += ((date[18] - '0') * 10) + (date[19] - '0');

        if (date[4] == ' ')
            ds.tm_mday = 0;
        else
            ds.tm_mday = (date[4] - '0') * 10;

        ds.tm_mday += (date[5] - '0');

        monstr = date;
        timstr = date + 7;
    }
    else
        return BAD_DATE;

    if (ds.tm_mday <= 0 || ds.tm_mday > 31)
        return BAD_DATE;

    ds.tm_hour = ((timstr[0] - '0') * 10) + (timstr[1] - '0');
    ds.tm_min = ((timstr[3] - '0') * 10) + (timstr[4] - '0');
    ds.tm_sec = ((timstr[6] - '0') * 10) + (timstr[7] - '0');

    if ((ds.tm_hour > 23) || (ds.tm_min > 59) || (ds.tm_sec > 61))
        return BAD_DATE;

    mint = (monstr[0] << 16) | (monstr[1] << 8) | monstr[2];
    for (mon = 0; mon < 12; mon++)
        if (mint == months[mon])
            break;
    if (mon == 12)
        return BAD_DATE;

    if ((ds.tm_mday == 31) && (mon == 3 || mon == 5 || mon == 8 || mon == 10))
        return BAD_DATE;

    /* February gets special check for leapyear */

    if ((mon == 1) &&
        ((ds.tm_mday > 29)
         || ((ds.tm_mday == 29)
             && ((ds.tm_year & 3)
                 || (((ds.tm_year % 100) == 0)
                     && (((ds.tm_year % 400) != 100)))))))
        return BAD_DATE;

    ds.tm_mon = mon;

    /* printf("parseHTTPdate: %s is %lu\n", date, ap_tm2sec(&ds)); */

    return ap_tm2sec(&ds);
}

/********
 * END: Above is taken from Apache's util_date.c
 */

time_t ftpDate2time_t(char *date){
        struct tm ds;

        if (!(ap_checkmask(date+4, "##############*")))
                return BAD_DATE;

/*        strptime(date+6, "%y%m%d%H%M%S", &tm_s); */

        ds.tm_year = (((date[4] - '0') * 10) + (date[5] - '0') - 19)*100;
        ds.tm_year += ((date[6] - '0') * 10) + (date[7] - '0');

        ds.tm_mon = ((date[8] - '0') * 10) + (date[9] - '0') - 1;
        ds.tm_mday = ((date[10] - '0') * 10) + (date[11] - '0');

        ds.tm_hour = ((date[12] - '0') * 10) + (date[13] - '0');
        ds.tm_min = ((date[14] - '0') * 10) + (date[15] - '0');
        ds.tm_sec = ((date[16] - '0') * 10) + (date[17] - '0');

        /* printf("parseFTPdate: %s is %lu\n", date, ap_tm2sec(&ds)); */

        return ap_tm2sec(&ds);
}

time_t tstr2time_t(char * time_str){
        time_t t=0;
        long i;
        char *s, *ts;

        /* flag telling us that time_str is exactly <num> without any char
         * so we think it's seconds
         * flag==0 means not defined yet
         * flag==1 means ordinary format (XXXmYYYs)
         * flag==2 means seconds only
         */
        int flag=0;

        ts=time_str;
        do{
                i=strtol(ts, &s, 10);
                if (s==ts){ /* failed to find a number */
                        return BAD_DATE;
                }

                /* ignore spaces */
                while (isspace(*s))
                        s++;

                switch(*s){
                        case 's': /* seconds */
                                t+=i; flag=1; break;
                        case 'M': /* minutes */
                                t+=i*60; flag=1; break;
                        case 'h': /* hours */
                                t+=i*60*60; flag=1; break;
                        case 'd': /* days */
                                t+=i*60*60*24; flag=1; break;
                        case 'm': /* months */
                                /* I assume month is 30 days */
                                t+=i*60*60*24*30; flag=1; break;
                        case 'y': /* years */
                                t+=i*60*60*24*365; flag=1; break;
                        case 0: /* end of string */
                                if (flag==1)
                                        return BAD_DATE;
                                else{
                                        t=i;
                                        flag=2;
                                        return t;
                                }
                        default:
                                return BAD_DATE;
                }
                /* go to next char */
                ts=++s;
        /* is it end? */
        } while (*s);

        return t;
}

time_t dmy2time_t(int d, int m, int y){
        struct tm t;

        memset((void *)&t, 0, sizeof(t));
        t.tm_mday=d;
        t.tm_mon=m;
        t.tm_year=y-1900;
        return ap_tm2sec(&t);
}

time_t dmyStr2time_t(char *str){
        struct tm t;
        char *cp, *cp2;

        memset((void *)&t, 0, sizeof(t));
        // str is dd/mm/yyyy
        t.tm_mday=(int)strtol(str, &cp, 10);
        if ((cp == str) || (*cp != '/') || (t.tm_mday<31) )        // some weirdness
                return BAD_DATE;
        t.tm_mon=(int)strtol(++cp, &cp2, 10) - 1; // months are from 0
        if ((cp2 == cp) || (*cp2 != '/') || (t.tm_mon<11) )        // some weirdness
                return BAD_DATE;
        t.tm_year=(int)strtol(++cp2, &cp, 10) - 1900; // years are from 1900
        if (cp == cp2)
                return BAD_DATE;

        return ap_tm2sec(&t);
}

/*******************************************************
Name:  Date.h
Authors:  David Barber
          Marcelo Labardini
Discussion Section:  M 4-5pm

*/

#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <iomanip> //needed to manipulate the output fields
#include <cassert>
#include <cmath> //needed for the power function.
using namespace std;

/*Description:  This is the header file where the class Date is defined.
It is primarily composed of its constructor and four member functions:
==,=,< and notleapyear.. The operator << is inlined and is declared as a friend.
This is where the operator finally ends the cascade started in Quicken's class
definition.  The exception IllegalException is also defined here.
*/
class Date {

  friend ostream& operator << (ostream& lhs, const Date& rhs)
    {
    lhs <<setfill('0')<< setw(2)<< rhs.month<<"/" <<setw(2)<<rhs.day<<"/"
    <<setw(4)<<rhs.year<<" "<<setfill(' ');

    return lhs;
    }

     public:
         class IllegalException {//handles day,month,year errors.

     public:
       IllegalException(const char* errormessage):
         message(errormessage){}

         const char* what() const {return message;}

     private:
       const char *message;};

     public:
     Date();
         Date (const int, const int , const int ) throw (IllegalException);
     bool notleapyear(const int);

         bool operator == (const Date&) const;
         bool operator <  (const Date&) const;
     Date& operator = (const Date&);

     private:

         int month,day,year,monthday;
    };
#endif

/*******************************************************
Name:  Date.cpp
Authors:  David Barber
          Marcelo Labardini
Discussion Section:  M 4-5pm

Description:  This is the source file where the class Date is implemented.
Its constructor and four member functions are defined.
*/

/*
#include "Date.h"

bool Date::notleapyear(const int yy) //function to determine if year is not leapyear
{
  if (( yy % 400 == 0) || ((yy%100 !=0) && (yy%4 == 0)))
    return false;
  else return true;
}
*/
//Date::Date():month(0),day(0),year(0),monthday(0){}

Date::Date(const int mn,const int dy, const int yr) throw (IllegalException)

{ //month,day,and year are assigned and their corresponding exceptions are
 //throw.  This also take into consider leapyear
  const int daysmonth[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};  
  if (mn >=1 && mn<=12)
  month = mn; else throw IllegalException("Invalid Month\n\n");
  if (yr >=1900 && yr <=2100)
  year = yr;
  else throw IllegalException("Invalid Year\n\n");
  if ((month == 2) && (dy==29) && notleapyear(year))
     throw IllegalException("Invalid Day: Not a leapyear \n\n");
  if (dy >=1 && dy <= daysmonth[month])
      day = dy;else throw IllegalException("Invalid Day\n\n");  
  monthday = month * pow(10,2) + day;}//convert month and day into one field.
                                        //easier to compare combined fields than to each one separately.
bool Date::operator <  (const Date& rhs) const
{
  if (this->year < rhs.year) //compares year
    return true;
  else if ((this->year == rhs.year) && (this->monthday < rhs.monthday)) //if year is equal then compare monthday field.
  return true;
  else return false;

}

Date& Date::operator = (const Date& rhs) //assignment operator
{
this->day=rhs.day;
this->month=rhs.month;
this->year=rhs.year;
this->monthday=rhs.monthday;
return *this;
}
#endif //0 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#if 0  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/********************************************************************\
 * date.h -- utility functions to handle the date (adjusting, get   * 
 *           current date, etc.) for xacc (X-Accountant)            *
 * Copyright (C) 1997 Robin D. Clark (rclark@cs.hmc.edu)            *
 * Copyright (C) 1998, 1999 Linas Vepstas                           *
 *                                                                  *
 * This program is free software; you can redistribute it and/or    *
 * modify it under the terms of the GNU General Public License as   *
 * published by the Free Software Foundation; either version 2 of   *
 * the License, or (at your option) any later version.              *
 *                                                                  *
 * This program is distributed in the hope that it will be useful,  *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of   *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the    *
 * GNU General Public License for more details.                     *
 *                                                                  *
 * You should have received a copy of the GNU General Public License*
 * along with this program; if not, write to the Free Software      *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.        *
\********************************************************************/

/* 
 * hack alert -- the scan and print routines should probably be moved 
 * to somewhere else ... the engine really isn't involved with things 
 * like printing formats.  This is needed mostl;y by the GUI and so on.
 * If a file-io thing needs date handling, it should do it itself, instead
 * of depending on the routines here ...
 */


/**
 * printDate
 *    Convert a date as day / month / year integers into a localized string
 *    representation
 *
 * Args:   buff - pointer to previously allocated character array; its size
 *                must be at lease MAX_DATE_LENTH bytes.
 *         day - day of the month as 1 ... 31
 *         month - month of the year as 1 ... 12
 *         year - year (4-digit)
 *
 * Return: nothing
 *
 * Globals: global dateFormat value
 */

/**
 * scanDate
 *    Convert a string into  day / month / year integers according to
 *    the current dateFormat value.
 *
 * Args:   buff - pointer to date string
 *         day -  will store day of the month as 1 ... 31
 *         month - will store month of the year as 1 ... 12
 *         year - will store the year (4-digit)
 *
 * Return: 0 if conversion was successful, 1 otherwise
 *
 * Globals: global dateFormat value
 */
/**
 * dateSeparator
 *    Return the field separator for the current date format
 *
 * Args:   none
 *
 * Return: date character
 *
 * Globals: global dateFormat value
 */


#ifndef __XACC_DATE_H__
#define __XACC_DATE_H__

#include "config.h"
#include "Transaction.h"

typedef enum
{
  DATE_FORMAT_US,       /* United states: mm/dd/yyyy */
  DATE_FORMAT_UK,       /* Britain: dd/mm/yyyy */
  DATE_FORMAT_CE,       /* Continental Europe: dd.mm.yyyy */
  DATE_FORMAT_ISO       /* ISO: yyyy-mm-dd */
} DateFormat;

/* the maximum length of a string created by sprtDate() */
#define MAX_DATE_LENGTH 11

/** PROTOTYPES ******************************************************/
void printDate (char * buff, int day, int month, int year);
void printDateSecs (char * buff, time_t secs);

char * xaccPrintDateSecs (time_t secs);

void scanDate (const char *buff, int *day, int *monty, int *year);
char dateSeparator(void);

char * xaccTransGetDateStr (Transaction *trans);
void   xaccTransSetDateStr (Transaction *trans, char *str);

time_t xaccDMYToSec (int day, int month, int year);
time_t xaccScanDateS (const char *buff);

/** GLOBALS *********************************************************/

extern DateFormat dateFormat;

#endif /* __XACC_DATE_H__ */

/********************************************************************\
 * date.c -- utility functions to handle the date (adjusting, get   * 
 *           current date, etc.) for xacc (X-Accountant)            *
 * Copyright (C) 1997 Robin D. Clark                                *
 * Copyright (C) 1998 Linas Vepstas                                 *
 *                                                                  *
 * This program is free software; you can redistribute it and/or    *
 * modify it under the terms of the GNU General Public License as   *
 * published by the Free Software Foundation; either version 2 of   *
 * the License, or (at your option) any later version.              *
 *                                                                  *
 * This program is distributed in the hope that it will be useful,  *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of   *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the    *
 * GNU General Public License for more details.                     *
 *                                                                  *
 * You should have received a copy of the GNU General Public License*
 * along with this program; if not, write to the Free Software      *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.        *
 *                                                                  *
 *   Author: Rob Clark                                              *
 * Internet: rclark@cs.hmc.edu                                      *
 *  Address: 609 8th Street                                         *
 *           Huntington Beach, CA 92648-4632                        *
 *                                                                  *
 *                                                                  * 
 * TODO: - for now, every year is leap year                         * 
 *                                                                  * 
\********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "config.h"
#include "date.h"

/* hack alert -- this should be turned into user-configurable parameter .. */
DateFormat dateFormat = DATE_FORMAT_US;

/********************************************************************\
\********************************************************************/

/**
 * printDate
 *    Convert a date as day / month / year integers into a localized string
 *    representation
 *
 * Args:   buff - pointer to previously allocated character array; its size
 *                must be at lease MAX_DATE_LENTH bytes.
 *         day - day of the month as 1 ... 31
 *         month - month of the year as 1 ... 12
 *         year - year (4-digit)
 *
 * Return: nothing
 *
 * Globals: global dateFormat value
 */
void 
printDate (char * buff, int day, int month, int year)
{
  if (!buff) return;

  /* Note that when printing year, we use %-4d in format string;
   * this causes a one, two or three-digit year to be left-adjusted
   * when printed (i.e. padded with blanks on the right).  This is 
   * important while the user is editing the year, since erasing a 
   * digit can temporarily cause a three-digit year, and having the 
   * blank on the left is a real pain for the user.  So pad on the 
   * right.
   */
  switch(dateFormat)
    {
    case DATE_FORMAT_UK:
      sprintf (buff, "%2d/%2d/%-4d", day, month, year);
      break;
    case DATE_FORMAT_CE:
      sprintf (buff, "%2d.%2d.%-4d", day, month, year);
      break;
    case DATE_FORMAT_ISO:
      sprintf (buff, "%04d-%02d-%02d", year, month, day);
      break;
    case DATE_FORMAT_US:
    default:
      sprintf (buff, "%2d/%2d/%-4d", month, day, year);
      break;
    }
}

void 
printDateSecs (char * buff, time_t t)
{
  struct tm *theTime;
  if (!buff) return;
  
  theTime = localtime(&t);
  
  printDate (buff, theTime->tm_mday, 
                   theTime->tm_mon + 1,
                   theTime->tm_year + 1900);
}


char * 
xaccPrintDateSecs (time_t t)
{
   char buff[100];
   printDateSecs (buff, t);
   return strdup (buff);
}

/**
 * scanDate
 *    Convert a string into  day / month / year integers according to
 *    the current dateFormat value.
 *
 * Args:   buff - pointer to date string
 *         day -  will store day of the month as 1 ... 31
 *         month - will store month of the year as 1 ... 12
 *         year - will store the year (4-digit)
 *
 * Return: 0 if conversion was successful, 1 otherwise
 *
 * Globals: global dateFormat value
 */
void 
scanDate(const char *buff, int *day, int *month, int *year)
{
   char *dupe, *tmp, *first_field, *second_field, *third_field;
   int iday, imonth, iyear;
   time_t secs;
   struct tm *now;

   if (!buff) return;
   dupe = strdup (buff);
   tmp = dupe;
   first_field = 0x0;
   second_field = 0x0;
   third_field = 0x0;

   /* use strtok to find delimiters */
   if (tmp) {
      first_field = strtok (tmp, ".,-+/\\()");
      if (first_field) {
         second_field = strtok (NULL, ".,-+/\\()");
         if (second_field) {
            third_field = strtok (NULL, ".,-+/\\()");
         }
      }
   }
   
   /* if any fields appear blank, use today's date */
   time (&secs);
   now = localtime (&secs);
   iday = now->tm_mday; 
   imonth = now->tm_mon+1;
   iyear = now->tm_year+1900;

   /* get numeric values */
   switch(dateFormat)
   {
     case DATE_FORMAT_UK:
     case DATE_FORMAT_CE:
       if (first_field) iday = atoi (first_field);
       if (second_field) imonth = atoi (second_field);
       if (third_field) iyear = atoi (third_field);
       break;
     case DATE_FORMAT_ISO:
       if (first_field) iyear = atoi (first_field);
       if (second_field) imonth = atoi (second_field);
       if (third_field) iday = atoi (third_field);
       break;
     case DATE_FORMAT_US:
     default:
       if (first_field) imonth = atoi (first_field);
       if (second_field) iday = atoi (second_field);
       if (third_field) iyear = atoi (third_field);
       break;
   }

   free (dupe);

   /* if the year entered is smaller than 100, assume we mean the current
      century (and are not revising some roman emperor's books) */
   if(iyear<100) {
     iyear += ((int) ((now->tm_year+1900)/100)) * 100;
   }

   if (year) *year=iyear;
   if (month) *month=imonth;
   if (day) *day=iday;
}

/**
 * dateSeparator
 *    Return the field separator for the current date format
 *
 * Args:   none
 *
 * Return: date character
 *
 * Globals: global dateFormat value
 */
char dateSeparator()
{
  char separator;
  switch(dateFormat)
  {
    case DATE_FORMAT_CE:
      separator='.';
      break;
    case DATE_FORMAT_ISO:
      separator='-';
      break;
    case DATE_FORMAT_US:
    case DATE_FORMAT_UK:
    default:
      separator='/';
      break;
  }
  return separator;
}

/********************************************************************\
\********************************************************************/

char *
xaccTransGetDateStr (Transaction *trans)
{
   char buf [MAX_DATE_LENGTH];
   time_t secs;
   struct tm *date;

   secs = xaccTransGetDate (trans);

   date = localtime (&secs);

   printDate(buf, date->tm_mday, date->tm_mon+1, date->tm_year +1900);
   return strdup (buf);
}

void
xaccTransSetDateStr (Transaction *trans, char *str)
{
   int day, month, year;

   /* hack alert -- the date string should be parsed for time values */
   /* cvs has some cool date parsing/guessing code .. maybe steal 
    * that code from there ...  */
   scanDate(str, &day, &month, &year);
   xaccTransSetDate (trans, day, month, year);
}

time_t 
xaccDMYToSec (int day, int month, int year)
{
   struct tm stm;
   time_t secs;

   stm.tm_year = year - 1900;
   stm.tm_mon = month - 1;
   stm.tm_mday = day;
   stm.tm_hour = 11;
   stm.tm_min = 0;
   stm.tm_sec = 0;

   /* compute number of seconds */
   secs = mktime (&stm);

   return (secs);
}

time_t
xaccScanDateS (const char *str)
{
   int month,day,year;
   scanDate (str, &day, &month, &year);
   return (xaccDMYToSec (day,month,year));
}

/********************** END OF FILE *********************************\
\********************************************************************/

      
/*
  Local Variables:
  tab-width: 2
  indent-tabs-mode: nil
  mode: c-mode
  c-indentation-style: gnu
  eval: (c-set-offset 'block-open '-)
  End:
*/
      
#endif //0 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#if 0  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/*********************************************************
                     APMISC.C  1.01

            Based on the  unit APMISC.PAS
    Pascal version Copyright (c) 1991 TurboPower Software.

           C/C++ version Copyright (c) 1993 TechMate, Inc.
                    All rights reserved.

              Licensed to TurboPower Software.
**********************************************************/
#define __APMISC_C     // don't tag routines as external in C file

#if !defined(__APMISC_H)
#include <apmisc.h>
#endif

#if !defined(__APSCRN_H)
#include <apscrn.h>
#endif

#if !defined(__APEXIT_H)
#include <apexit.h>
#endif

#if !defined(__APROOT_H)
#include <aproot.h>
#endif

#if !defined(__APINLINE_H)
#include <apinline.h>
#endif

#if defined(__BORLANDC__)
#if !defined(__ALLOC_H)
#include <alloc.h>
#endif

#if !defined(__MEM_H)
#include <mem.h>
#endif
#endif

#if !defined(__STDLIB_H)
#include <stdlib.h>
#endif

#if !defined(__STRING_H)
#include <string.h>
#endif

#if defined(HeapDebug)
#if !defined(__FCNTL_H)
#include <fcntl.h>
#endif

#if !defined(__STAT_H)
#include <sys\stat.h>
#endif

#if !defined(__IO_H)
#include <io.h>
#endif
#endif

#if defined(HeapDebug)
  int HDebug;
  ExitFuncPtr apmiSaveExit;
#endif

#if !defined(UseOPRO)

char DosDelimSet[4] = {'\\', ':', '\0'};
char Digits[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
                   '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
/*
  boolean IsLeapYear(int Year)
    //-Return True if Year is a leap year
  {
    return (Year % 4 == 0) && (Year % 4000 != 0) &&
                  ((Year % 100 != 0) || (Year % 400 == 0));
  }

  int DaysInMonth(int Month, int Year)
    //-Return the number of days in the specified month of a given year
  {
    if (Year < 100)
      Year += 1900;

    switch (Month) {
      case 1 :
      case 3 :
      case 5 :
      case 7 :
      case 8 :
      case 10 :
      case 12 :
        return 31;
      case 4 :
      case 6 :
      case 9 :
      case 11 :
        return 30;
      case 2 :
        return 28+IsLeapYear(Year);
      default :
        return 0;
    }
  }
*/
  boolean ValidDate(int Day, int Month, int Year)
    //-Verify that day, month, year is a valid date
  {
    if (Year < 100) {
      Year += 1900;
      if (Year < Threshold2000)
        Year += 100;
    }

    if ((Day < 1) || (Year < MinYear) || (Year > MaxYear))
      return FALSE;
    else if ((Month >= 1) && (Month <= 12))
      return (Day <= DaysInMonth(Month, Year));
    else
      return FALSE;
  }

  Date DMYtoDate(int Day, int Month, int Year)
    //-Convert from day, month, year to a julian date
  {
    Date RetVal;

    if (Year < 100) {
      Year += 1900;
      if (Year < Threshold2000)
        Year += 100;
    }

    if (! ValidDate(Day, Month, Year))
      RetVal = BadDate;
    else if ((Year == MinYear) && (Month < 3))
      if (Month == 1)
        RetVal = Day-1;
      else
        RetVal = Day+30;
    else {
      if (Month > 2)
        Month -= 3;
      else {
        Month += 9;
        Year--;
      }
      Year -= MinYear;
      RetVal = (Date)((((long)Year*1461) / 4)+
          (((153*Month)+2) / 5)+Day+First2Months);
    }
    return RetVal;
  }

  void DateToDMY(Date Julian, int *Day, int *Month, int *Year)
    //-Convert from a julian date to month, day, year
  {
    long I;

    if (Julian == BadDate) {
      *Day = 0;
      *Month = 0;
      *Year = 0;
    }
    else if (Julian <= First2Months) {
      *Year = MinYear;
      if (Julian <= 30) {
        *Month = 1;
        *Day = (Julian+1);
      }
      else {
        *Month = 2;
        *Day = Julian-30;
      }
    }
    else {
      I = (long)((4*(long)(Julian-First2Months))-1);
      *Year = (int)(I / 1461);
      I = (long)((5*((I % 1461) / 4)) + 2);
      *Month = (int)(I / 153);
      *Day = (int)(((I % 153)+5) / 5);
      if (*Month < 10)
        *Month += 3;
      else {
        *Month -= 9;
        (*Year)++;
      }
      *Year += MinYear;
    }
  }

  void DateTimeDiff(DateTimeRec DT1, DateTimeRec DT2, word *Days, long *Secs)
    //-Return the difference in days and seconds between two points in time
  {
    DateTimeRec DTTemp;

    //swap if DT1 later than DT2
    if ((DT1.D > DT2.D) || ((DT1.D == DT2.D) && (DT1.T > DT2.T))) {
      DTTemp = DT1;
      DT1 = DT2;
      DT2 = DTTemp;
    }

    //the difference in days is easy
    *Days = DT2.D - DT1.D;

    //difference in seconds
    if (DT2.T < DT1.T) {
      //subtract one day, add 24 hours
      Days--;
      DT2.T += SecondsInDay;
    }
    *Secs = DT2.T-DT1.T;
  }

  void TimeToHMS(Time T, byte *Hours, byte *Minutes, byte *Seconds)
    //-Convert a Time variable to Hours, Minutes, Seconds
  {
    if (T == BadTime) {
      Hours = 0;
      Minutes = 0;
      Seconds = 0;
    }
    else {
      *Hours = (byte)(T / SecondsInHour);                       //!!.01
      T -= (long)((long)(*Hours) * SecondsInHour);
      *Minutes = (byte)(T / SecondsInMinute);                   //!!.01
      T -= (long)((long)(*Minutes) * SecondsInMinute);
      *Seconds = (byte)T;                                       //!!.01
    }
  }

  Time HMStoTime(byte Hours, byte Minutes, byte Seconds)
    //-Convert Hours, Minutes, Seconds to a Time variable
  {
    Time T;

    Hours %= HoursInDay;
    T = ((long)Hours*SecondsInHour)+((long)Minutes*SecondsInMinute)+Seconds;
    return T % SecondsInDay;
  }

  void IncDateTime(DateTimeRec *DT1, DateTimeRec *DT2, int Days, long Secs)
    //-Increment (or decrement) DT1 by the specified number of days and seconds
    // and put the result in DT2
  {
    *DT2 = *DT1;

    //date first
    DT2->D += (Date)Days;

    if (Secs < 0) {
      //change the sign
      Secs = -Secs;

      //adjust the date
      DT2->D -= (Date)(Secs / SecondsInDay);
      Secs = Secs % SecondsInDay;

      if (Secs > DT2->T) {
        //subtract a day from DT2.D and add a day's worth of seconds to DT2.T
        DT2->D--;
        DT2->T += SecondsInDay;
      }

      //now subtract the seconds
      DT2->T -= Secs;
    }
    else {
      //increment the seconds
      DT2->T += Secs;

      //adjust date if necessary
      DT2->D += (Date)(DT2->T / SecondsInDay);

      //force time to 0..SecondsInDay-1 range
      DT2->T = DT2->T % SecondsInDay;
    }
  }

  byte Pos(char C, const char *S)
    //return the position of C in S or 0xFF if not found
  {
    #if defined(_MSC_VER)
    word A;
    #endif
    byte SLen = strlen(S);

    if (SLen == 0)
      return 0xFF;

    asm {
      push ds
      mov ah,C           //get the character we want to compare
      mov cl,SLen        //get the length of S
      xor ch,ch          //0 the high byte
      cld                //clear the direction flag
    }
    #if defined (OPDataIsFar)
    asm {
      lds si,S           //DS:SI => address of the start of S
    }
    #else
    asm {
      mov si,S           //DS:SI => address of the start of S
    }
    #endif
    Next:
    asm {
      lodsb              //get the first byte of S
      cmp ah,al          //is this the character we are looking for?
      jz  Done
      dec cx
      jnz Next           //get next character if not to end of S
    }
    asm { pop ds }
    return 0xFF;
    Done:
    asm { pop ds }
    #if defined(__BORLANDC__)
    return SLen - _CX;
    #else
    asm mov A,cx
    return SLen - A;
    #endif
  }

  char *PadCh(const char *S, char Ch, byte Len, char *SRet)
    //Return a string right-padded to length len with ch
  {
    byte SLen;

    SLen = strlen(S);

    if (SLen >= Len) {
      strcpy(SRet, S);
    }
    else {
      MoveFast(S, SRet, SLen);
      if (SLen < 255)
        setmem(&SRet[SLen], Len-SLen, Ch);
      SRet[Len] = '\0';
    }
    return SRet;
  }

  char *HexW(word W, char *SRet)
    //-Return hex string for word
  {
    SRet[0] = Digits[W >> 12];
    SRet[1] = Digits[(W >> 8) & 0x000F];
    SRet[2] = Digits[(W & 0x00F0) >> 4];
    SRet[3] = Digits[W & 0x000F];
    SRet[4] = '\0';
    return SRet;
  }

  char *HexL(long L, char *SRet)
    //-Return hex string for LongInt
  {
    HexW((*(LH *)&L).H, &SRet[0]);
    HexW((*(LH *)&L).L, &SRet[4]);
    return SRet;
  }

  char *AddBackSlash(const char *DirName, char *SRet)
    // -Add a default backslash to a directory name
  {
    byte length;
    char T[65];

    strcpy(T, DirName);
    length = strlen(T);

    if ((length == 0) || ((T[length-1] == '\\') || (T[length-1] == ':'))) {
      strcpy(SRet, T);
    }
    else {
      strcpy(SRet, T);
      strcat(SRet, "\\");
    }
    return SRet;
  }

  char *DefaultExtension(const char *Name, const char *Ext, char *SRet)
    //-Return a file name with a default extension attached
  {
    word DotPos;

    if (HasExtension(Name, &DotPos)) {
      strcpy(SRet, Name);
    } else if (Name[0] == '\0') {
      SRet[0] = '\0';
    }
    else {
      strcpy(SRet, Name);
      strcat(SRet, ".");
      strcat(SRet, Ext);
    }
    return SRet;
  }


  word Search(const void far *Buffer, word BufLength,
              const void far *Match, word MatLength)
   //-Search through Buffer for Match. BufLength is length of range to search.
   // MatLength is length of string to match. Returns number of bytes searched
   // to find Match, $FFFF if not found.}
  {
    #if defined(_MSC_VER)
    word RetVal;
    #endif
    asm {
      PUSH DS                 //Save DS
      CLD                     //Go forward
      LES  DI,Buffer          //ES:DI ==> Buffer
      MOV  BX,DI              //BX == Ofs(Buffer)
      MOV  CX,BufLength       //CX == Length of range to scan
      MOV  DX,MatLength       //DX == Length of match char*
      TEST DX,DX              //strlen(Match) == 0?
      JZ   Error              //If so, we're done
      LDS  SI,Match           //DS:SI ==> Match buffer
      LODSB                   //AL == Match[1]; DS:SI ==> Match[2]
      DEC  DX                 //DX == MatLength-1
      SUB  CX,DX              //CX == BufLength-(MatLength-1)
      JBE  Error              //Error if BufLength is less
    }                         //Search for first character in Match
    Next:
    asm {
      REPNE SCASB             //Search forward for Match[1]
      JNE  Error              //Done if (not found
      TEST DX,DX              //If Length == 1 (DX == 0) ...
      JZ   Found              // the "char*" was found
                              //Search for remainder of Match
      PUSH CX                 //Save CX
      PUSH DI                 //Save DI
      PUSH SI                 //Save SI
      MOV  CX,DX              //CX == strlen(Match) - 1
      REPE CMPSB              //Does rest of char* match?
      POP  SI                 //Restore SI
      POP  DI                 //Restore DI
      POP  CX                 //Restore CX
      JNE  Next               //Try again if (no match
    }                        //Calculate number of bytes searched and return
    Found:
    asm {
      DEC  DI                 //DX == Offset where found
      MOV  AX,DI              //AX == Offset where found
      SUB  AX,BX              //Subtract starting offset
      JMP  SHORT SDone        //Done
    }                        //Match was not found
    Error:
    asm {
      XOR  AX,AX              //Return $FFFF
      DEC  AX
    }
    SDone:
    asm {
      POP  DS                 //Restore DS
    }
    #if defined(__BORLANDC__)
    return _AX;               //Set func result
    #else
    asm { mov RetVal,ax };
    return RetVal;
    #endif
  }

  char *StUpcase(const char *S, char *SRet)
    //-Convert lower case letters in string to uppercase
  {
    int I;

    for (I = 0; I <= (int)strlen(S);I++)                        //!!.01
      SRet[I] = Upcase(S[I]);
    return SRet;
  }

  void HexPtr(void far *P, char *SRet)
    //-Return hex string for pointer
  {
    HexW(FP_SEG(P), &SRet[0]);
    SRet[4] = ':';
    HexW(FP_OFF(P), &SRet[5]);
  }

#if defined(HeapDebug)

#define     ExtraSize  10
#define     MarkValue  0xAA

typedef byte ByteArray[65521L];

  void DebugExit(void)
    //-Exit procedure to close the debug file
  {
    long MemAvail = coreleft();
    char T[255];

    ExitFunc = apmiSaveExit;
    write(HDebug, "\r\n", 2);
    write(HDebug, "Ending MemAvail: \r\n", 19);
    ltoa(MemAvail, T, 10);
    write(HDebug, T, strlen(T));
    write(HDebug, "Ending MaxAvail: \r\n", 19);
    ltoa(MaxAvail, T, 10);
    write(HDebug, T, strlen(T));
    close(HDebug);
  }

  void LogError(void *P, long Size, word Bound)
    //-Log memory overwrite errors
  {
    int F;
    int Result;
    char T[255];

    F = open("HEAPERR.RPT", O_RDONLY | O_BINARY | O_CREAT, S_IREAD, S_IWRITE);

    if (ExistFile("HEAPERR.RPT"))
      lseek(F, 0L, SEEK_END);

    Result = IOResult();
    if ((Result == 0) || (Result == 2)) {
      if (Size == -1) {
        write(F, "  also at ", 10);
        ltoa(Bound, T, 10);
        strcat(T, "\r\n");
        write(F, T, strlen(T));
      } else {
        HexPtr(P, T);
        write(F, "Out of bounds occurred on ", 26);
        strcat(T, " (");
        write(F, T, strlen(T));
        ltoa(Size, T, 10);
        write(F, T, strlen(T));
        write(F, ") variable at ", 14);
        ltoa(Bound, T, 10);
        strcat(T, "\r\n");
        write(F, T, strlen(T));
      }
      IOResult();
      close(F);
      IOResult();
    }
  }
#endif

  boolean pascal GetMemCheckPrim(void **P, word Bytes)
    //-Allocate heap space, returning true if successful
  {
    void *Pt = *P;

   #if defined(HeapDebug)
    char T[255];
    boolean RetVal;
    void far *X;
   #endif

   #if defined(HeapDebug)
    Bytes += ExtraSize;
    *P = malloc(Bytes);
    if ((Pt != NULL)) {
      setmem(Pt, Bytes, MarkValue);
      RetVal = TRUE;
    } else
      RetVal = FALSE;

    //Log the allocation
    X = (void *)(*((void *)(long)(&Bytes)-4)));

    Seg(X) -= _psp + 0x10;

    write(HDebug, "from ", 5);
    HexPtr(X, T);
    write(HDebug, T, strlen(T));
    write(HDebug, "  allocate: ", 12);
    HexPtr(P, T);
    strcat(T, " ");
    write(HDebug, T, strlen(T));
    ltoa(Bytes-ExtraSize, T, 10);
    strcat(T, "\r\n");
    write(HDebug, T, strlen(T));
    return RetVal;
   #else
    *P = malloc(Bytes);
   return (*P != NULL);
   #endif
  }

  void pascal FreeMemCheckPrim(void **P)
    //-Deallocate heap space
  {
    void *Pt = *P;
   #if defined(HeapDebug)
    void *X;
    boolean Found;
    word I;
    char S[255];
   #endif

   #if defined(HeapDebug)
    X = (&Bytes - 4);

    Seg(X) -= _psp + 0x10;

    HexPtr(X, S);
    write(HDebug, "from ", 5);
    write(HDebug, S, strlen(S));
    write(HDebug, "  free:     ", 12);
    HexPtr(P, S);
    write(HDebug, S, strlen(S));
    write(HDebug, " ", 1);
    write(HDebug, &Bytes, sizeof(Bytes));

    if ((Pt != NULL)) {
      I = Bytes + 1;
      Found = FALSE;
      while ((I <= Bytes + ExtraSize)) {
        if (*((ByteArray *)Pt)[I] != MarkValue) {
          if (! Found) {
            Found = TRUE;
            LogError(*P, Bytes, I);
          } else
            LogError(*P, -1, I);
        }
        I++;
      }

      Bytes += ExtraSize;
      free(*P);
      *P = NULL;
    }
   #else
    if (*P != NULL) {
      free(*P);
      *P = NULL;
    }
   #endif
  }

  char *JustFileName(const char *PathName, char *SRet)
    // -Return just the filename and extension of a pathname
  {
    int I;

    I = strlen(PathName);
    for (--I; ((PathName[I] != '\\') && (PathName[I] != ':') && (I != -1)); I--);
    if ((strlen(PathName) - I) > 12)
      Copy(PathName, (byte)++I, 12, SRet);
    else
      strcpy(SRet, &PathName[++I]);
    return SRet;
  }

  #define dVolumeId      8
  #define dDirectory  0x10

  boolean ExistFile(const char *FName)
    //-Return true if file is found
  {
    union REGS regs;
    struct SREGS sregs;

    //check for empty string
    if (FName[0] == '\0')
      return FALSE;

    regs.h.ah = 0x43;      //get file attribute
    regs.h.al = 0x00;      //get file attr
    sregs.ds = FP_SEG(FName);
    regs.x.dx = FP_OFF(FName);
    intdosx(&regs, &regs, &sregs);

    _doserrno = 0;

    return  (! (regs.x.cflag) & 1) &&
                  ((regs.x.cx & (dVolumeId+dDirectory)) == 0);
  }

  char *StringToHeap(const char *S)
  {
    word L;
    char *P = NULL;

    L = strlen(S)+1;
    if (GetMemCheck(&P, strlen(S)+1))
      MoveFast(S, P, L);
    return P;
  }

  void DisposeString(char **P)
  {
    if (P != NULL)
      FreeMemCheck(P);
  }

  void WhereXYAbs(word *XY)
    //-Return the absolute (not window relative) coordinates of cursor
  {
    union REGS Regs;

    Regs.h.ah = 3;
    Regs.h.bh = 0;
    int86(0x10, &Regs, &Regs);
    Regs.h.dl++;
    Regs.h.dh++;
    *XY = Regs.x.dx;
    _doserrno = 0;
  }

  void GotoXYAbs(byte X, byte Y)
    //-Position cursor at absolute coordinates X, Y
  {
    union REGS Regs;
    Regs.h.ah = 2;
    Regs.h.bh = 0;
    Regs.h.dh = Y-1;
    Regs.h.dl = X-1;
    int86(0x10, &Regs, &Regs);
    _doserrno = 0;
  }

  #endif

boolean APMiscInited = FALSE;

void APMiscInit(void)
{
  if (APMiscInited)
    return;

  #if !defined(UseOPRO)
  APRootInit();
  OPCrtInit();
  #endif
  #if defined(HeapDebug)
  word MemAvail;
  word MaxAvail;
  char T[255];
  #endif

  #if defined(HeapDebug)
  //Delete old heap error report
  HDebug = open("HEAPERR.RPT", O_RDWR | O_BINARY | O_CREAT | O_TRUNC,
              S_IREAD | S_IWRITE);

  if (IOResult() != 0)
    ;

  //Open new heap allocation report file
  HDebug = open("HEAP.RPT", O_RDWR | O_BINARY | O_CREAT | O_TRUNC,
              S_IREAD | S_IWRITE);

  MemAvail = coreleft();
  write(HDebug, "Initial MemAvail: \r\n", 20);
  ltoa(MemAvail, T, 10);
  write(HDebug, T, strlen(T));
  write(HDebug, "Initial MaxAvail: \r\n", 20);
  ltoa(MaxAvail, T, 10);
  write(HDebug, T, strlen(T));
  write(HDebug, "\r\n", 2);
  if (IOResult() != 0)
    ;

  apmiSaveExit = ExitFunc;
  ExitFunc = DebugExit;
  #endif
  APMiscInited = TRUE;
}

  //This acknowledgment is for the table/code used in the UpdateCRC routine
  //*
  //* updCRC derived from article Copyright (c) 1986 Stephen Satchell.
  //*  NOTE: First argument must be in range 0 to 255.
  //*        Second argument is referenced twice.
  //*
  //* Programmers may incorporate any or all code into their programs,
  //* giving proper credit within the source. Publication of the
  //* source routines is permitted so long as proper credit is given
  //* to Stephen Satchell, Satchell Evaluations and Chuck Forsberg,
  //* Omen Technology.
  //*

uint32  DateToDays (uint32  year, uint32  month, uint32  day)
{
    static const int    month2days[] =
    {
          0,     31,     59,     90,    120,    151,
        181,    212,    243,    273,    304,    334
    };


    // Normalize the values.
//
    year -= 1904;
    month -= 1;
    day -= 1;

    // Not counting any possible leap-day in the current year, figure out
    // the number of days between now and 1/1/1904.
//
    const uint32     kNumDaysInLeapCycle = 4 * 365 + 1;

    uint32  days =   day + month2days[month] +
                    (year * kNumDaysInLeapCycle + 3) / 4;

    // Now add in this year's leap-day, if there is one.
//
    if ((month >= 2) && ((year & 3) == 0))
        days++;

    return days;
} 


/*
 * Translated from Andrew Tuman's Pascal sources.
 */

//#ifndef __DATE_H
//#define __DATE_H

/*
typedef unsigned DayTy;
typedef unsigned MonthTy;
typedef unsigned YearTy;
typedef unsigned long JulTy;

typedef struct {
  unsigned short year;
  unsigned char month;
  unsigned char day;
} BDateTy;

#define DATE_BUFFER_LEN 11
*/
/*
extern "C" {
  extern const YearTy century;
  extern const DayTy daysInMonth[];

  YearTy get_full_year(YearTy year);

  int LeapYear(YearTy);

  DayTy DaysToDate(YearTy, MonthTy, DayTy);
  JulTy DaysToYear(YearTy);
    
  void Encode(YearTy, MonthTy, DayTy, JulTy&);
  void Decode(YearTy&, MonthTy&, DayTy&, const JulTy);

  int DayOfWeek(YearTy, MonthTy, DayTy);    

  char* d2xbase(YearTy year, MonthTy month, DayTy day, char* buffer);

  char* d2h(const char* value, char* buffer);
  char* h2d(const char* value, char* buffer);
}
*/
//class DateTy {
//public:
/*
 *  USA      (mm-dd-yy)
 *  American (mm/dd/yy)
 *  British  (dd/mm/yy)
 *  German   (dd.mm.yy)
 *  Italian  (dd-mm-yy)
 *  Japanese (yy/mm/dd)
 *  ANSI     (yy.mm.dd)
 *  xBase    (YYYYMMDD)
 */
  /*
  enum Formats {
    AMERICAN = 0, USA = 1, ANSI = 2, JAPANESE = 3, BRITISH = 4,
    GERMAN = 5, ITALIAN = 6, XBASE = 7, PACKED = 8, DEFAULT = 9,
    SWIFT32A = 10
  };
*/
/*
  DateTy(bool use_global = true);
  DateTy(YearTy, MonthTy, DayTy);
  DateTy(JulTy);
  DateTy(const char *, DateTy::Formats = DEFAULT);

  const char* c_str(DateTy::Formats = DEFAULT, bool century = true) const;

  int IsLeap() const;
  int WeekDay() const;
  DayTy Day() const;
  MonthTy Month() const;
  YearTy Year(bool century = true) const;
  DayTy DaysInMonth() const;
  DayTy LastWorkDay() const;   

  DateTy& FirstMonthDay();
  DateTy& LastMonthDay();
  DateTy& DecMonth(unsigned = 1);
  DateTy& IncMonth(unsigned = 1);

  operator JulTy() const {
    return JulNum;
  }
  bool operator<(const DateTy& rhs) const {
    return JulNum < rhs.JulNum;
  }
  bool operator==(const DateTy& rhs) const {
    return JulNum == rhs.JulNum;
  }
  DateTy& operator++() {
    JulNum += 1;
    return *this;
  }
  DateTy& operator--() {
    JulNum -= 1;
    return *this;
  }
  DateTy& operator+=(int delta) {
    JulNum += delta;
    return *this;
  }
  DateTy& operator-=(int delta) {
    JulNum -= delta;
    return *this;
  }
  JulTy operator-(const DateTy& rhs) const {
    return JulNum - rhs.JulNum;
  }
  JulTy operator+(int rhs) const {
    return JulNum + rhs;
  }

  const char* ShortDayName(DayTy weekDayNumber);
  const char* MonthName(MonthTy monthNumber);

  static void PrintMode(Formats = DateTy::BRITISH);

protected:
  static char GetDelimiter();

  void IncOneMonth();
  void DecOneMonth();

  void d2h(const char* value) const;
  void h2d(const char* value) const;

private:
  JulTy JulNum;
  static Formats PrintOption;
  mutable char buffer[16];
  */
//};
/*
class DateMY {
private:
  MonthTy month;
  YearTy year;
   
public:
  DateMY(JulTy date) : month(DateTy(date).Month()), year(DateTy(date).Year()) {}
  DateMY(const DateTy& date) : month(date.Month()), year(date.Year()) {}

  bool operator<(const DateMY& rhs) const {
    if(year < rhs.year) return true;
    if(year > rhs.year) return false;
    return month < rhs.month;
  }
  bool operator==(const DateMY& rhs) const {
    return month == rhs.month && year == rhs.year;
  }

  MonthTy Month() const { return month; }
  YearTy Year() const { return year; }
};
*/
//extern DateTy global_date_value;

//#endif // __DATE_H

/*
 * Translated from Andrew Tuman's Pascal sources.
 */
/*
#include <stdio.h>
#include <string.h>
#include <mem.h>
#include <time.h>

#include "datety.hpp"

DateTy global_date_value(false);

static const char formatStrRead[]  = "%d%c%d%c%d";
static const char formatDbfRead[]  = "%04d%02d%02d";
static const char formatSwift23ARead[]  = "%02d%02d%02d";
static const char formatStrWrite[] = "%02d%c%02d%c%d";
static const char formatDbfWrite[] = "%04d%02d%02d";

DateTy::Formats DateTy::PrintOption = DateTy::BRITISH;
*/
/*
static const char* MonthNames[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov",
  "Dec" };
*/
//static const char* WeekDayNames[7] = {
//  "Su", "Mn", "Tu", "We", "Th", "Fr", "St" };
/*
DateTy::DateTy(bool use_global) 
  {
  if(!use_global) {
    long clk = ::time(0);
    struct tm *now = ::localtime(&clk);
    Encode(century + now->tm_year, now->tm_mon + 1, now->tm_mday, JulNum);
  }
  else JulNum = global_date_value.JulNum;
}

DateTy::DateTy(YearTy year, MonthTy month, DayTy day) {
  Encode(::get_full_year(year), month, day, JulNum);
}

DateTy::DateTy(JulTy JulDate) {
  JulNum = JulDate;
}

DateTy::DateTy(const char* date, DateTy::Formats _mode) 
  {
  DayTy day; MonthTy month; YearTy year;
  char c1 = '\0', c2 = '\0';
  int scaned, must_be;
  switch(_mode == DEFAULT ? PrintOption : _mode) {
  case AMERICAN:
  case USA:
    must_be = 5;
    scaned = ::sscanf(date, formatStrRead, &month, &c1, &day, &c2, &year);
    break;
  case ANSI:
  case JAPANESE:
    must_be = 5;
    scaned = ::sscanf(date, formatStrRead, &year, &c1, &month, &c2, &day);
    break;
  case BRITISH:
  case GERMAN:
  case ITALIAN:
    must_be = 5;
    scaned = ::sscanf(date, formatStrRead, &day, &c1, &month, &c2, &year);
    break;
  case PACKED:
    h2d(date);
    must_be = 3;
    scaned = ::sscanf(buffer, formatDbfRead, &year, &month, &day);
    break;
  case XBASE:
    must_be = 3;
    scaned = ::sscanf(date, formatDbfRead, &year, &month, &day);
    break;
  case SWIFT32A:
    must_be = 3;
    scaned = ::sscanf(date, formatSwift23ARead, &year, &month, &day);
    break;
  }
  if(scaned != must_be) {
    JulNum = (JulTy)0l;
    return;
  }
  Encode(::get_full_year(year), month, day, JulNum);
}
*/
/*
int DateTy::IsLeap() const {
  DayTy day; MonthTy month; YearTy year;
  Decode(year, month, day, JulNum);
  return LeapYear(year);
}


int DateTy::WeekDay() const {
  DayTy day; MonthTy month; YearTy year;
  Decode(year, month, day, JulNum);
  return DayOfWeek(year, month, day);
}

DayTy DateTy::Day() const {
  DayTy day; MonthTy month; YearTy year;
  Decode(year, month, day, JulNum);
  return day;
}

MonthTy DateTy::Month() const {
  DayTy day; MonthTy month; YearTy year;
  Decode(year, month, day, JulNum);
  return month;
}

YearTy DateTy::Year(bool century) const {
  DayTy day; MonthTy month; YearTy year;
  Decode(year, month, day, JulNum);
  return century ? year : year % 100;
}

void DateTy::PrintMode(Formats newMode) {
  if(newMode != DEFAULT && newMode != XBASE && newMode != PACKED)
    PrintOption = newMode;
}

DayTy DateTy::DaysInMonth() const {
  DayTy day; MonthTy month; YearTy year;
  if(JulNum) {
    Decode(year, month, day, JulNum);
    return ((month == 2) && LeapYear(year)) ?
      (daysInMonth[month] + 1) : (daysInMonth[month]);
  }
  return 0;
}
*/
/*
DayTy DateTy::LastWorkDay() const {
  DayTy day; MonthTy month; YearTy year; JulTy tmp;
  if(JulNum) {
    Decode(year, month, day, JulNum);
    day = DaysInMonth();
    Encode(year, month, day, tmp);
    int wd = DayOfWeek(year, month, day);
    switch(wd) {
    case 1: // Sunday.
      tmp -= 2;
      break;
    case 7: // Saturday.
      tmp -= 1;
      break;
    }
    Decode(year, month, day, tmp);
    return day;
  }
  return 0;
}

DateTy& DateTy::FirstMonthDay() {
  DayTy day; MonthTy month; YearTy year;
  if(JulNum) {
    Decode(year, month, day, JulNum);
    day = 1;
    Encode(year, month, day, JulNum);
  }
  return *this;
}

DateTy& DateTy::LastMonthDay() {
  DayTy day; MonthTy month; YearTy year;
  if(JulNum) {
    Decode(year, month, day, JulNum);
    day = ((month == 2) && LeapYear(year)) ?
      (daysInMonth[month]+1) : (daysInMonth[month]);
    Encode(year, month, day, JulNum);
  }
  return *this;
}

void DateTy::IncOneMonth() {
  DayTy day, limit; MonthTy month; YearTy year;
  if(JulNum) {
    Decode(year, month, day, JulNum);
    month = (month % 12) + 1;
    if(month == 1) year++;
    limit = ((month == 2) && LeapYear(year)) ?
      (daysInMonth[month] + 1) : (daysInMonth[month]);
    Encode(year, month, ((day <= limit ) ? day : limit ), JulNum);
  }
}

void DateTy::DecOneMonth() {
  DayTy day, limit; MonthTy month; YearTy year;
  if(JulNum) {
    Decode(year, month, day, JulNum);
    month = ((month + 10) % 12) + 1;
    if(month == 12 ) year--;
    limit = ((month == 2) && LeapYear(year)) ?
      (daysInMonth[month] + 1) : (daysInMonth[month]);
    Encode(year, month, ((day <= limit ) ? day : limit), JulNum);
  }
}

DateTy& DateTy::DecMonth(unsigned count) {
  if(JulNum && count) {
    for(register unsigned i = 1; i <= count; i++)
      DecOneMonth();
  }
  return *this;
}

DateTy& DateTy::IncMonth(unsigned count) {
  if(JulNum && count) {
    for(register unsigned i = 1; i <= count; i++)
      IncOneMonth();
  }
  return *this;
}
*/
/*
char DateTy::GetDelimiter() {
  switch(PrintOption) {
  case USA:
  case ITALIAN:
    return '-';
  case GERMAN:
  case ANSI:
    return '.';
  case AMERICAN:
  case JAPANESE:
  case BRITISH:
    return '/';
  }
  return '/';
}

const char* DateTy::c_str(DateTy::Formats _mode, bool century) const {
  DayTy day; MonthTy month; YearTy year;
  char delimiter = GetDelimiter();
  ::memset(buffer, 0, sizeof(buffer));
  Decode(year, month, day, JulNum);
  if(!century) year = year % 100;
  switch(_mode == DEFAULT ? PrintOption : _mode) {
  case AMERICAN:
  case USA:
    ::sprintf(buffer, formatStrWrite, month, delimiter, day, delimiter, year);
    break;
  case ANSI:
  case JAPANESE:
    ::sprintf(buffer, formatStrWrite, year, delimiter, month, delimiter, day);
    break;
  case BRITISH:
  case GERMAN:
  case ITALIAN:
    ::sprintf(buffer, formatStrWrite, day, delimiter, month, delimiter, year);
    break;
  case XBASE:
    ::sprintf(buffer, formatDbfWrite, year, month, day);
    break;
  case PACKED:
    char tmp[9];
    ::sprintf(tmp, formatDbfWrite, year, month, day);
    d2h(tmp);
    break;
  }
  return buffer;
}

const char* DateTy::ShortDayName(DayTy weekDayNumber) {
  if(weekDayNumber >=1 && weekDayNumber <= 7)
    ::strcpy(buffer, WeekDayNames[weekDayNumber - 1]);
  else ::memset(buffer, 0, sizeof(buffer));
  return buffer;
}

const char* DateTy::MonthName(MonthTy monthNumber) {
  if(monthNumber >=1 && monthNumber <= 12)
    ::strcpy(buffer, MonthNames[monthNumber - 1]);
  else ::memset(buffer, 0, sizeof(buffer));
  return buffer;
}

void DateTy::d2h(const char* value) const {
  ::d2h(value, buffer);
}

void DateTy::h2d(const char* value) const {
  ::h2d(value, buffer);
}
*/
/* +++Date last modified: 05-Jul-1997 */

/*
**  PARSDATE.C - A simple parser to extract dates from strings.
**
**  Original Copyright 1995 by Robert B. Stout as part of
**  the MicroFirm Function Library (MFL)
**
**  The user is granted a free limited license to use this source file
**  to create royalty-free programs, subject to the terms of the
**  license restrictions specified in the LICENSE.MFL file.
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "datetime.h"

static unsigned  year_norml(unsigned year);
static Boolean_T get_fields(char *str);
static Boolean_T validate(unsigned year, unsigned month, unsigned day);
static Boolean_T isleap (unsigned yr);
static unsigned  get_month(char *month);

/*
static char *fields[3];
static char *month[2][12] = {
      {"January", "February", "March", "April", "May", "June",
       "July", "August", "September", "October", "November", "December"},
      {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
       "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"}
};
*/

/*
**  parse_date() - Parse a date string into its components
**
**  Arguments: 1 - String to parse
**             2 - Address of year storage
**             3 - Address of month storage
**             4 - Address of day storage
**             5 - Syntax to use
**
**  Returns: 0 For success, non-zero for range errors
**
**  Notes: The following syntaxes are supported:
**
**    Date ordering: USA (month, day, year),
**                   ISO (year, month, day)
**                   EUROPE (day, month, year)
**    Delimiters:    Spaces, commas, dashes, periods, slashes. (" ,-./")
**    Years:         2-digit years assumed to be between 1970 and 2069
**                   4-digit years required otherwise
*/

Boolean_T parse_date(const char *str,
                     unsigned   *year,
                     unsigned   *month,
                     unsigned   *day,
                     Syntax_T   syntax)
{
      unsigned yy, mm, dd;                /* Local data                 */
      char str_copy[512];                 /* Nice and roomy             */

      strcpy(str_copy, str);
      if (Error_ == get_fields(str_copy))
            return Error_;

      switch (syntax)
      {
      case USA:
            yy = atoi(fields[2]);
            dd = atoi(fields[1]);
            if (isalpha(*fields[0]))
            {
                  mm = get_month(fields[0]);
                  if (0 == mm)
                  {
                        return Error_;
                  }
            }
            else  mm = atoi(fields[0]);
            break;

      case ISO:
            yy = atoi(fields[0]);
            dd = atoi(fields[2]);
            if (isalpha(*fields[1]))
            {
                  mm = get_month(fields[1]);
                  if (0 == mm)
                        return Error_;
            }
            else  mm = atoi(fields[1]);
            break;

      case EUROPE:
            yy = atoi(fields[2]);
            dd = atoi(fields[0]);
            if (isalpha(*fields[1]))
            {
                  mm = get_month(fields[1]);
                  if (0 == mm)
                        return Error_;
            }
            else  mm = atoi(fields[1]);
            break;

      default:
            return Error_;
      }
      yy = year_norml(yy);
      if (Error_ == validate(yy, mm, dd))
            return Error_;
      *year  = yy;
      *day   = dd;
      *month = mm;
      return Success_;
}

/*
**  Utility function to split string fields
*/

static Boolean_T get_fields(char *str)
{
      if (NULL == (fields[0] = strtok(str, " ,-./")))
            return Error_;
      if (NULL == (fields[1] = strtok(NULL, " ,-./")))
            return Error_;
      if (NULL == (fields[2] = strtok(NULL, " ,-./")))
            return Error_;
      if (NULL != strtok(NULL, " ,-./"))
            return Error_;
      return Success_;
}

/*
**  Utility function to validate dates
*/

static Boolean_T validate(unsigned year, unsigned month, unsigned day)
{
      unsigned int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

      if (1 > month || 12 < month)
            return Error_;
      if (1 > day || day > (days[month - 1] + (2 == month && isleap(year))))
            return Error_;
      else  return Success_;
}

/*
**  Utility function to detect leap years
* /

static Boolean_T isleap (unsigned yr)
{
   return yr % 400 == 0 || (yr % 4 == 0 && yr % 100 != 0);
}
*/
/*
**  Utility function to normalize years
*/

static unsigned year_norml(unsigned year)
{
      if (99 < year)
            return year;
      if (69 < year)
            return year + 1900;
      else  return year + 2000;
}

/*
**  Utility function to determine month from string
**
**  (Note: Uses non-standard stricmp(), common to all DOS compilers
*/

static unsigned get_month(char *str)
{
      int ix, iy;                         /* Indexes                    */

      for (ix = 0; ix < 2; ++ix)
      {
            for (iy = 0; iy < 12; ++iy)
            {
                  if (Success_ == stricmp(str, month[ix][iy]))
                        return iy + 1;
            }
      }
      return 0;
}

#ifdef TEST

#include <stdio.h>

main(int argc, char *argv[])
{
      if (2 > argc)
      {
            puts("Usage: PARSDATE syntax date_string");
            puts("       syntax = 0, 1, or 2");
            return EXIT_FAILURE;
      }
      while (--argc)
      {
            Syntax_T syntax;
            char *str;
            unsigned yy, mm, dd;
            Boolean_T retval;

            if (4 > argc)
                  break;
            syntax = atoi(*++argv);
            str = *++argv;
            printf("str = \"%s\"\n", str);
            retval = parse_date(str, &yy, &mm, &dd, syntax);
            printf("parse_date(%d, \"%s\") returned %d\n"
                  "  date = %u-%u-%u\n\n",
                  syntax, str, retval, mm, dd, yy);
      }
      return EXIT_SUCCESS;
}

#endif /* TEST */
#endif //0 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#if 0  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/***             analog 4.90beta1             http://www.analog.cx/             ***/
/*** This program is copyright (c) Stephen R. E. Turner 1995 - 2001 except as
 *** stated otherwise. Distribution, usage and modification of this program is
 *** subject to the conditions of the Licence which you should have received
 *** with it. This program comes with no warranty, expressed or implied.   ***/

/*** dates.c; anything to do with dates. ***/

//#include "anlghea3.h"

/* Analog stores times internally in minutes since midnight 30-31/12/1969.
   (Not in "Unix time" because it works better if all valid times are > 0).
   Note also that months are numbered Jan = 0 to Dec = 11 internally. */

unsigned int daysbefore[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273,
             304, 334};  /* in non-leap year */
//unsigned int monthlength[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30,
//        31};

/* 
void code2date(datecode_t code, unsigned int *date, unsigned int *month,
         unsigned int *year) {
  / * not most efficient possible, but only used in output so doesn't need to
     be super-fast. NB DATE2CODE() is in anlghea3.h. * /
  code += 364;    / * so 0 -> 1/1/69 * /
  *year = 1969 + 4 * (code / 1461);
  code %= 1461;
  *year += MIN(code / 365, 3); / * no leap days for a while after 1/1/69! * /
  if (code == 1460) {
    *month = DEC;
    *date = 31;
  }
  else {
    code %= 365;    / * so 0 -> 1/Jan, any year * /
    for (*month = DEC;
   daysbefore[*month] + (IS_LEAPYEAR(*year) && *month > FEB) > code;
   (*month)--)
      ;   / * run to right month * /
    *date = code - daysbefore[*month] + 1 -
      (IS_LEAPYEAR(*year) && *month > FEB);
  }
}
*/
/*
time_t shifttime(time_t timer, int diff) {
  / * Surprisingly, there is no ANSI C function to do this * /
  struct tm *lt = localtime(&timer);
  lt->tm_min += diff;
  timer = mktime(lt);
  return(timer);
}
*/

choice parsedate(time_t starttime, char *s, timecode_t *date, logical from,
     logical unixtime) 
  {
  struct tm *st;
  int y, m, d, h, n;
  char *p;

#ifndef NOGMTIME
  if (unixtime)
    st = gmtime(&starttime);
  else
#endif
    st = localtime(&starttime);
  if (ISDIGIT(*s) && ISDIGIT(*(s + 1))) 
    {
    y = 10 * (*s - '0') + (*(s + 1) - '0');
    s += 2;
    y += 1900;
    if (y < 1970)
      y += 100;
   }
  else if (*s == '+' && ISDIGIT(*(s + 1)) && ISDIGIT(*(s + 2))) {
    y = st->tm_year + 1900 + 10 * (*(s + 1) - '0') + (*(s + 2) - '0');
    s += 3;
  }
  else if (*s == '-' && ISDIGIT(*(s + 1)) && ISDIGIT(*(s + 2))) {
    y = st->tm_year + 1900 - 10 * (*(s + 1) - '0') - (*(s + 2) - '0');
    s += 3;
  }
  else
    return(ERR);

  if (ISDIGIT(*s) && ISDIGIT(*(s + 1))) {
    m = 10 * (*s - '0') + (*(s + 1) - '0') - 1;
    if (m > 11 || m < 0)
      return(ERR);
    s += 2;
  }
  else if (*s == '+' && ISDIGIT(*(s + 1)) && ISDIGIT(*(s + 2))) {
    m = st->tm_mon + 10 * (*(s + 1) - '0') + (*(s + 2) - '0');
    s += 3;
  }
  else if (*s == '-' && ISDIGIT(*(s + 1)) && ISDIGIT(*(s + 2))) {
    m = st->tm_mon - 10 * (*(s + 1) - '0') - (*(s + 2) - '0');
    s += 3;
  }
  else
    return(ERR);
  while (m < 0) {   /* need to do this now because about to use monthlength */
    m += 12;
    y--;
  }
  while (m > 11) {
    m -= 12;
    y++;
  }

  if (ISDIGIT(*s) && ISDIGIT(*(s + 1))) {
    d = (int)strtol(s, &p, 10);
    if (d > 31 || d <= 0)
      return(ERR);
    else if (d > (int)(monthlength[m]) + (m == FEB && IS_LEAPYEAR(y)))
      d = monthlength[m] + (m == FEB && IS_LEAPYEAR(y));
  }                   /* relative dates must be >= 2 digits but can be more */
  else if (*s == '+' && ISDIGIT(*(s + 1)) && ISDIGIT(*(s + 2)))
    d = st->tm_mday + (int)strtol(s + 1, &p, 10);
  else if (*s == '-' && ISDIGIT(*(s + 1)) && ISDIGIT(*(s + 2)))
    d = st->tm_mday - (int)strtol(s + 1, &p, 10);
  else
    return(ERR);

  if (*p == ':') {  /* parse hr & min */
    s = p + 1;
    if (ISDIGIT(*s) && ISDIGIT(*(s + 1))) {
      h = 10 * (*s - '0') + (*(s + 1) - '0');
      if (h > 23)
  return(ERR);
      s += 2;
    }
    else if (*s == '+' && ISDIGIT(*(s + 1)) && ISDIGIT(*(s + 2))) {
      h = st->tm_hour + 10 * (*(s + 1) - '0') + (*(s + 2) - '0');
      s += 3;
    }
    else if (*s == '-' && ISDIGIT(*(s + 1)) && ISDIGIT(*(s + 2))) {
      h = st->tm_hour - 10 * (*(s + 1) - '0') - (*(s + 2) - '0');
      s += 3;
    }
    else
      return(ERR);

    if (ISDIGIT(*s) && ISDIGIT(*(s + 1))) {
      n = 10 * (*s - '0') + (*(s + 1) - '0');
      if (n > 59)
  return(ERR);
      s += 2;
    }
    else if (*s == '+' && ISDIGIT(*(s + 1)) && ISDIGIT(*(s + 2))) {
      n = st->tm_min + 10 * (*(s + 1) - '0') + (*(s + 2) - '0');
      s += 3;
    }
    else if (*s == '-' && ISDIGIT(*(s + 1)) && ISDIGIT(*(s + 2))) {
      n = st->tm_min - 10 * (*(s + 1) - '0') - (*(s + 2) - '0');
      s += 3;
    }
    else
      return(ERR);
  }                 /* end *p == ':' */
  else if (*p == '\0' || *p == 'd' || *p == 'D' || *p == 'e' || *p == 'E') {
    /* d, e can come from FLOOR */
    if (from) {
      h = 0;
      n = 0;
    }
    else {
      h = 23;
      n = 59;
    }
  }
  else
    return(ERR);

  while (n < 0) {
    n += 60;
    h--;
  }
  while (n > 59) {
    n -= 60;
    h++;
  }
  while (h < 0) {
    h += 24;
    d--;
  }
  while (h > 23) {
    h -= 24;
    d++;
  }
  while (d < 0) {
    m--;
    if (m < 0) {   /* NB already adjusted m once above */
      m += 12;
      y--;
    }
    d += monthlength[m] + (m == FEB && IS_LEAPYEAR(y));
  }
  while (d > (int)(monthlength[m]) + (m == FEB && IS_LEAPYEAR(y))) {
    d -= monthlength[m] + (m == FEB && IS_LEAPYEAR(y));
    m++;
    if (m > 11) {
      m -= 12;
      y++;
    }
  }

  *date = TIMECODE(DATE2CODE(y, m, d), h, n);
#ifndef NOGMTIME
  if (unixtime)
    *date -= 1440;   /* Unix time is one day different from analog time */
#endif
  return(OK);
}

choice wantdate(timecode_t *timecode, Dateman *dman, unsigned int hr,
    unsigned int min, unsigned int date, unsigned int month,
    unsigned int year, int tz) {
  static unsigned int oldy = 0, oldm = 0, oldd = 0, oldh = 25;
  static timecode_t oldtime = 0;

  /* first check integrity of date */
  if (month > 11 || hr > 23 || min > 59 || date == 0 ||
      date > monthlength[month] + (month == FEB && IS_LEAPYEAR(year)) ||
      year < 1970 || year > 2069)
    return(ERR);

  if (hr != oldh || date != oldd || month != oldm || year != oldy) {
    oldtime = TIMECODE(DATE2CODE(year, month, date), hr, 0);
    oldh = hr;                        /* only calculate once an hour */
    oldd = date;
    oldm = month;
    oldy = year;
  }

  *timecode =  oldtime + min + tz;
  if (*timecode < dman->from || *timecode > dman->to)
    return(FALSE);
  return(TRUE);
}

choice wantunixtime(timecode_t *timecode, Dateman *dman,
        unsigned long unixtime, int tz) {
  /* no need to check range because parseulong() catches it */
  *timecode = UXTIME2CODE(unixtime) + tz;
  if (*timecode < dman->from || *timecode > dman->to)
    return(FALSE);
  return(TRUE);
}
/*
Daysdata *newday(unsigned int granularity) {
  extern Memman *xmemman;

  Daysdata *dp;
  unsigned int i;

  dp = (Daysdata *)submalloc(xmemman, sizeof(Daysdata));
  dp->reqs = (unsigned long *)submalloc(xmemman,
          granularity * sizeof(unsigned long));
  dp->pages = (unsigned long *)submalloc(xmemman,
           granularity * sizeof(unsigned long));
  dp->bytes = (double *)submalloc(xmemman, granularity * sizeof(double));

  for (i = 0; i < granularity; i++) {
    dp->reqs[i] = 0;
    dp->pages[i] = 0;
    dp->bytes[i] = 0.0;
  }

  dp->prev = NULL;
  dp->next = NULL;

  return(dp);
}
*/
      /*
void dmaninit(Dateman *dman, datecode_t datecode, unsigned int granularity) {
  dman->firstdate = datecode;
  dman->lastdate = datecode;
  dman->currdate = datecode;
  dman->firstdp = newday(granularity);
  dman->lastdp = dman->firstdp;
  dman->currdp = dman->firstdp;
}
*/
/*
void datehash(timecode_t timecode, Dateman *dman, unsigned long reqs,
        unsigned long pages, double bytes, unsigned int granularity) {
  int i;
  Daysdata *dp;

  datecode_t datecode = (datecode_t)(timecode/1440);

  if (dman->currdp == NULL)
    dmaninit(dman, datecode, granularity);
  if (datecode >= dman->lastdate) {
    for (i = datecode - dman->lastdate; i > 0; i--) {
      dp = newday(granularity);
      dman->lastdp->next = dp;
      dp->prev = dman->lastdp;
      dman->lastdp = dp;
      dman->lastdate = datecode;
    }
    dman->currdp = dman->lastdp;
  }
  else if (datecode >= dman->currdate) {
    for (i = datecode - dman->currdate; i > 0; i--)
      dman->currdp = dman->currdp->next;
  }
  else if (datecode <= dman->firstdate) {
    for (i = dman->firstdate - datecode; i > 0; i--) {
      dp = newday(granularity);
      dman->firstdp->prev = dp;
      dp->next = dman->firstdp;
      dman->firstdp = dp;
      dman->firstdate = datecode;
    }
    dman->currdp = dman->firstdp;
  }
  else {
    dman->currdp = dman->firstdp;
    for (i = datecode - dman->firstdate; i > 0; i--) {
      dman->currdp = dman->currdp->next;
    }
  }

  dman->currdate = datecode;

  i = ((timecode % 1440) * granularity) / 1440;
  dman->currdp->reqs[i] += reqs;
  dman->currdp->pages[i] += pages;
  dman->currdp->bytes[i] += bytes;
}
*/
      /* +++Date last modified: 05-Jul-1997 */

//
// loctm.h
// Time functions class (a C++ wrapper for ANSI struct tm)
//
// written by David Nugent
//
// This code is public domain. Use for any purpose is unrestricted.
//

//# if !defined( _loctm_h )
//# define _loctm_h 1

/*
# include <time.h>
# if defined( __MSDOS__ ) || defined( MSDOS )
#  define STRSTREAM_H "strstrea.h"  // 8.3 (sigh)
# else
#  define STRSTREAM_H "strstream.h"
# endif

    // Forward declare for streams interface

class ostream;
class istream;

    // class loc_tm
    // C++ class (mainly I/O) wrapper for ANSI-C struct tm

class loc_tm : public tm
{

  public:

    loc_tm (void) {}                  // Do nothing constructor
    loc_tm (time_t t);     // Set to time, 0 is magic for 'now'
    loc_tm (tm const & t); // Copy constructor

    loc_tm & operator= (tm const & t);            // Assignment
    operator time_t (void) const;        // Conversion operator

    int is_valid (void) const;             // Test for validity

    int compare (loc_tm const & t) const;      // Compare times
    int compare (time_t const tt) const;       // Compare times

    enum f_date     // Date format flags
    {
        d_Year          = (int)0x0001,            // Print year
        d_YearShort     = (int)0x0002, // Print last two digits
        d_PadYear       = (int)0x0004,    // Pad year to 2 or 4
        d_ZeroYear      = (int)0x0008,        // Zero fill year
        d_Month         = (int)0x0010,           // Print month
        d_MonText       = (int)0x0020,   // Print month in text
        d_PadMon        = (int)0x0040, // Pad to 2 (trunc to 3)
        d_ZeroMon       = (int)0x0080,       // Zero fill month
        d_Day           = (int)0x0100,            // Print date
        d_DayOfWeek     = (int)0x0200,     // Print day of week
        d_PadDay        = (int)0x0400,         // Pad date to 2
        d_ZeroDay       = (int)0x0800,         // Zero fill day
        d_DMY           = (int)0x0111, // Print date, mth, year
        d_PadDMY        = (int)0x0444,         // Pad all three
        d_ZeroDMY       = (int)0x0888,   // Zero fill all three
        d_YearFirst     = (int)0x1000,      // Print year first
        d_MonFirst      = (int)0x2000,     // Print month first
        d_SepChar       = (int)0x4000,// Separate fields datech
        d_SepSpace      = (int)0x8000  // Separate fields space
    };
    enum date_f                         // Composite date flags
    {
        d_International = (int)(d_DMY|d_MonText|d_PadMon|
                                d_SepSpace),
        d_IntlShort     = (int)(d_DMY|d_MonText|d_PadMon|
                                d_SepSpace|d_YearShort),
        d_Usa           = (int)(d_DMY|d_MonFirst|d_PadDMY|
                                d_ZeroDMY|d_YearShort|d_SepChar),
        d_English       = (int)(d_DMY|d_YearShort|d_PadDMY|
                                d_ZeroDMY|d_SepChar),
        d_Japanese      = (int)(d_DMY|d_YearFirst|d_PadDMY|
                                d_ZeroDMY|d_YearShort|d_MonFirst|
                                d_SepChar),
        d_Full          = (int)(d_DMY|d_DayOfWeek|d_MonText|
                                d_SepSpace)
    };

    enum f_time  // Time format (nb: time zones not implemented)
    {
        t_Secs          = (int)0x0001,         // Print seconds
        t_ZeroSecs      = (int)0x0002,     // Zero fill seconds
        t_PadSecs       = (int)0x0004,      // Pad seconds to 2
        t_SecsAll       = (int)0x0007,
        t_TimeZone      = (int)0x0008,        // Print timezone
        t_Mins          = (int)0x0010,         // Print minutes
        t_ZeroMins      = (int)0x0020,     // Zero fill minutes
        t_PadMins       = (int)0x0040,      // Pad minutes to 2
        t_MinsAll       = (int)0x0070,
        t_TZNumeric     = (int)0x0080,      // Print numeric TZ
        t_Hour          = (int)0x0100,            // Print hour
        t_ZeroHour      = (int)0x0200,        // Zero fill hour
        t_PadHour       = (int)0x0400,  // Pad hour to 2 digits
        t_HourAll       = (int)0x0700,
        t_24hour        = (int)0x0800,          // 24hour clock
        t_SepChar       = (int)0x1000, // Separate field timech
        t_SepSpace      = (int)0x2000, // Separate fields space
        t_SepAbbrev     = (int)0x4000,     // Add abbreviations
        t_AmPm          = (int)0x8000       // Add 'am' or 'pm'
    };
    enum time_f  // Composite time flags
    {
        t_International = (int)(t_HourAll|t_MinsAll|t_SecsAll|
                                t_24hour|t_SepChar),
        t_ShortTime     = (int)(t_HourAll|t_MinsAll|t_24hour|
                                t_SepChar),
        t_ClockTime     = (int)(t_Hour|t_PadHour|t_MinsAll|
                                t_AmPm|t_SepChar),
        t_LongTime      = (int)(t_Hour|t_PadHour|t_MinsAll|
                                t_SecsAll|t_SepAbbrev|t_SepSpace),
        t_Millitary     = (int)(t_HourAll|t_MinsAll|t_24hour)
    };


    static char timech;    // Character used for time separator
    static char datech;    // Character used for date separator
    static int datefmt;                  // Default date format
    static int timefmt;                  // Default time format

                                              // Output methods
    ostream & print (ostream & os, int df =datefmt,
                                   int tf =timefmt) const;
    ostream & printTime (ostream & os, int f =timefmt) const;
    ostream & printDate (ostream & os, int f =datefmt) const;

                                       // Input/parsing methods
  //  istream & parseTime (istream & is);        // Unimplemented
  //  istream & parseDate (istream & is);        // Unimplemented
  //  istream & parse (istream & is);            // Unimplemented

  private:
                                                 // Time suffix
    void tSfx (ostream & os, int fmt, char ch) const;
                                       // Time field formatters
    void pHour (ostream & os, int fmt) const;
    void pMins (ostream & os, int fmt) const;
    void pSecs (ostream & os, int fmt) const;
                                                 // Date suffix
    void dSfx (ostream & os, int fmt) const;
                                       // Date field formatters
    void pDate (ostream & os, int fmt) const;
    void pMonth (ostream & os, int fmt) const;
    void pYear (ostream & os, int fmt) const;

};

inline ostream &                        // Stream output method
operator<< (ostream & os, loc_tm const & t)
{   return t.print(os);     }

inline int                                          // Equality
operator== (loc_tm const & t1, loc_tm const & t2)
{   return int(t1.compare(t2) == 0);    }

inline int                                        // Inequality
operator!= (loc_tm const & t1, loc_tm const & t2)
{   return int(t1.compare(t2) != 0);    }

inline int                                         // Less then
operator<  (loc_tm const & t1, loc_tm const & t2)
{   return int(t1.compare(t2) < 0);     }

inline int                                   // Less than/equal
operator<= (loc_tm const & t1, loc_tm const & t2)
{   return int(t1.compare(t2) <= 0);    }

inline int                                      // Greater than
operator>  (loc_tm const & t1, loc_tm const & t2)
{   return int(t1.compare(t2) > 0);     }

inline int                                // Greater than/equal
operator>=  (loc_tm const & t1, loc_tm const & t2)
{   return int(t1.compare(t2) >= 0);    }


    // class loc_date
    // Date formatter

class loc_date : public loc_tm
{

  public:

    loc_date (loc_tm const & t, int dtfmt =loc_tm::datefmt)
        : loc_tm (t), _fmt(dtfmt)   {}
    loc_date (time_t t, int dtfmt =loc_tm::datefmt)
        : loc_tm (t), _fmt(dtfmt)   {}
    int fmt (int f)                 {   return _fmt = f;    }
    int fmt (void) const            {   return _fmt;        }

    ostream & print (ostream & os) const
        {   return printDate (os, _fmt);    }

  private:

    int _fmt;

};

inline ostream &                // Stream output method - date
operator<< (ostream & os, loc_date const & d)
{   return d.print(os);     }


    // class loc_time
    // Time formatter

class loc_time : public loc_tm
{

  public:

    loc_time (loc_tm const & t, int tmfmt =loc_tm::timefmt)
        : loc_tm (t), _fmt(tmfmt)   {}
    loc_time (time_t t, int tmfmt =loc_tm::timefmt)
        : loc_tm (t), _fmt(tmfmt)   {}
    int fmt (int f)                 {   return _fmt = f;    }
    int fmt (void) const            {   return _fmt;        }

    ostream & print (ostream & os) const
        {   return printTime (os, _fmt);    }

  private:

    int _fmt;

};

inline ostream &                // Stream output method - time
operator<< (ostream & os, loc_time const & t)
{   return t.print(os);     }

*/

//# endif     // _loctm_h

// +++Date last modified: 05-Jul-1997

//
// loctm.cpp
// C++ class wrapper for ANSI-C struct tm
//
// written by David Nugent
//
// This code is public domain. Use for any purpose is unrestricted.
//

//# include "loctm.h"

//char loc_tm::timech = ':';
//char loc_tm::datech = '/';

//int loc_tm::datefmt = loc_tm::d_IntlShort;
//int loc_tm::timefmt = loc_tm::t_International;

/*

loc_tm::loc_tm (time_t t)
{
    if (t == 0)
        t = time(0); //_time64 coordinated universal time (UTC)
    //Convert a time value and correct for the local time zone
    //ANSI C range [1970-01-01 00:00:00, 2038-01-18 19:14:07]
    *(tm *)this = *localtime(&t);
    //Win32 range [1970-01-01 00:00:00, 3000-12-31 23:59:59]
//_localtime64
}
*/
/*
loc_tm::loc_tm (tm const & t)
{
    *((tm *)this) = t;
}

loc_tm &
loc_tm::operator= (tm const & t)
{
    *((tm *)this) = t;
    return *this;
}
*/
/*
int
loc_tm::compare (loc_tm const & t) const
{
    return compare ((time_t)t);
}

int
loc_tm::compare (time_t const tt) const
{
    time_t tx = (time_t)*this;
    return (tx == tt) ? 0 : (tx > tt) ? 1 : -1;
}

loc_tm::operator time_t (void) const
{
    return mktime ((tm *)this);
}
*/
/*
int
loc_tm::is_valid (void) const
{
  //  static int maxd[] =
  //  {
  //      31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
  //  };

    return (tm_year > 0 &&
            tm_mon >= 0 && tm_mon < 12 &&
            tm_mday > 0 && tm_mday <= maxd[tm_mon] &&
            tm_wday < 7 && tm_yday < 367 &&
            tm_sec < 60 && tm_min < 60 && tm_hour < 24);
}
*/
/*
  File: PARSDATE.H
  Description:
    Header file for PARSDATE.CPP.
  History:
    1/1/95 -- Created, Dave Roberts
  Copyright 1995, David G. Roberts
*/

#ifndef _PARSDATE_H

/* PROTOTYPES */
int ConvertTimeZone(char FAR * lpszTZ);
int ConvertDay(char FAR * lpszDay);
int ConvertMonth(char FAR * lpszMonth);
char FAR * GetDateToken(char FAR * lpszDate, char FAR * lpszBuffer,
  unsigned uMaxLen);
time_t ParseDateString(char FAR * lpszDate);

#define _PARSDATE_H

#endif


/*
  File: PARSDATE.CPP
  Description:
    Functions used for parsing an RFC822 or ctime style date
    string.
  History:
    1/1/95 -- Created, Dave Roberts
  Copyright 1995, David G. Roberts
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "parsdate.h"

/* CONSTANTS */
//static char *szDayName[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri",
//  "Sat" };
//static char *szLongDayName[7] = { "Sunday", "Monday", "Tuesday",
//  "Wednesday", "Thursday", "Friday", "Saturday" };
//static char *szMonthName[12] = {"Jan", "Feb", "Mar", "Apr", "May",
//  "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
//static char *szLongMonthName[12] = {"January", "February", "March",
//  "April", "May", "June", "July", "August", "September",
//  "October", "November", "December" };
//static int iDaysPerMonth[12] = { 31, 29, 31, 30, 31, 30, 31, 31,
//  30, 31, 30, 31 };

// Timezone info.  Much of the TZ info here (including the comments) came
// from the date_util.c file of the source to the Elm mail system,
// Copyright (c) 1993 USENET Community Trust.
typedef struct {
  char  *szName;  // Name of timezone
  int   iOffset;  // Offset east of GMT in military format
} TZ_INFO;

static TZ_INFO tzInfo[] = {
  // From RFC822
  { "UT", 0 }, { "UCT", 0 }, { "GMT", 0 },
  { "EST", -500 }, { "EDT", -400 },
  { "CST", -600 }, { "CDT", -500 },
  { "MST", -700 }, { "MDT", -600 },
  { "PST", -800 }, { "PDT", -700 },
  { "HST", -1000 },         // hawaii
  { "Z", 0}, // Military time ("Zulu" = GMT), rest of militaries not used

  // popular European timezones
  { "WET", 0 },   // western european
  { "MET", 100 },   // middle european
  { "EET", 200 },   // eastern european
  { "BST", 100 },   // ??? british summer time

  // Canadian timezones
  { "AST", -400 }, { "ADT", -300 }, // atlantic
  { "NST", -330 }, { "NDT", -230 }, // newfoundland
  { "YST", -900 }, { "YDT", -800 }, // yukon

  // Asian timezones
  { "JST", 900 },   // japan
  { "SST", 800 },   // singapore

  // South-Pacific timezones
  { "NZST", 1200 }, { "NZDT", 1300 }, // new zealand  { "WST", 800 }, { "WDT", 900 }    // western australia
};

// Date format codes.
#define DF_RFC822 (1)
#define DF_CTIME  (2)

// ParseDate state numbers.
#define ST_WDAY   (0)
#define ST_COMMA  (1)
#define ST_MDAY   (2)
#define ST_DASH1  (3)
#define ST_MONTH  (4)
#define ST_DASH2  (5)
#define ST_YEAR   (6)
#define ST_HOUR   (7)
#define ST_COLON1 (8)
#define ST_CORRECT4 (9)
#define ST_MIN    (10)
#define ST_COLON2 (11)
#define ST_SEC    (12)
#define ST_ZONE   (13)

/* MACROS */
#define IsALPHA(c)  ((65 <= c && c <= 90) || (97 <= c && c <= 122))
#define IsDIGIT(c)  (48 <= c && c <= 57)
#define IsLWSP(c) (c == 32 || c == 9)
#define DIM(x)    (sizeof(x)/sizeof(x[0]))

/*
  Function: ConvertTimeZone
  Description:
    Converts a timezone string into a numeric offset in minutes
    for the zone.
    Strings can specify a number of different named timezones
    (e.g., EST, PDT, etc.) or a numeric offset in string format
    (e.g., +100, -800, +1).
*/
int ConvertTimeZone(char * szTZ)
{
  int iResult;
  int i;
  int iLen;

  if (szTZ == NULL || szTZ[0] == '\0')
    return 0; // Null strings = GMT.

  if (((szTZ[0] == '+' || szTZ[0] == '-') && IsDIGIT(szTZ[1])) ||
    IsDIGIT(szTZ[0])) {
    // This one looks to be numeric.
    iResult = atoi(szTZ);
    iLen = lstrlen(szTZ);
    if (iLen == 2 || iLen == 3) // If we got a 2-digit offset
      iResult *= 100;     // then convert it to 4-digit offset.
  }
  else {
    // Search for a named timezone.
    if (szTZ[0] == '-') // Elm mentions that some bad mailers put
      szTZ++;     // '-' in front of a zone name, so skip it.

    iResult = 0;    // Default.
    // Search the zone name list.
    for (i = 0; i < DIM(tzInfo); i++) {
      if (lstrcmpi(szTZ, tzInfo[i].szName) == 0) {
        iResult = tzInfo[i].iOffset;
        break;
      }
    } // end for (i...
  } // end else...

  // Now convert timezone from military format offset to offset in
  // minutes.
  iResult = (iResult / 100) * 60 + (iResult % 100);
  return iResult;
}

/*
  Function: ConvertDay
  Description:
    Returns number of month corresponding to string argument.
    January = 0.
*/
int ConvertDay(char * szDay)
{
  int i;

  // Compare against short names.
  for (i = 0; i < DIM(szDayName); i++) {
    // Use windows case insensitive string comparison function.
    if (lstrcmpi(szDay, szDayName[i]) == 0)
      return i;
  }
  // Compare against long names.
  for (i = 0; i < DIM(szLongDayName); i++) {
    // Use windows case insensitive string comparison function.
    if (lstrcmpi(szDay, szLongDayName[i]) == 0)
      return i;
  }
  return -1;
}

/*
  Function: ConvertMonth
  Description:
    Returns number of month corresponding to string argument.
    January = 0.
*/
int ConvertMonth(char * szMonth)
{
  int i;

  // Compare against short names.
  for (i = 0; i < DIM(szMonthName); i++)
    {
    // Use windows case insensitive string comparison function.
    if (lstrcmpi(szMonth, szMonthName[i]) == 0)
      return i;
    }
  // Compare against long names.
  for (i = 0; i < DIM(szLongMonthName); i++) {
    // Use windows case insensitive string comparison function.
    if (lstrcmpi(szMonth, szLongMonthName[i]) == 0)
      return i;
  }
  return -1;
}

/*
  Function: GetDateToken
  Description:
    Gets the next token from a date string.  A date token is
    defined to be a sequence of letters or numbers, but not both, or
    a punctuation or control character by itself.  The function
    returns a pointer to the next character that was not consumed.
    The scanned token is returned in szBuffer and is up to uMaxLen
    in length.
*/
char FAR * GetDateToken(char FAR * lpszDate, char * szBuffer,
  unsigned uMaxLen)
{
  int i;
  int c;
  BOOL bAlphaMode;

  // Skip any leading white space
  while (IsLWSP(*lpszDate))
    lpszDate++;

  // See if we've found the end of the string.
  if (*lpszDate == '\0') {
      // If so, then return null token and don't advance.
    szBuffer[0] = '\0';
    return lpszDate;
  }

  // See if we got a punctuation, control, or space character.
  if (!IsALPHA(*lpszDate) && !IsDIGIT(*lpszDate)) {
    // If so, return just that single character.
    szBuffer[0] = *lpszDate;
    szBuffer[1] = '\0';
    return lpszDate + 1;
  }
  else if (IsALPHA(*lpszDate))  // Scanning alphas or digits?
    bAlphaMode = TRUE;
  else
    bAlphaMode = FALSE;

  // Loop until we encounter a character that is not alpha or digit,
  // or we run out of room in the token buffer.
  i = 0;
  while (1) {
    c = *lpszDate;
    if ((unsigned)i == (uMaxLen - 1) || 
      bAlphaMode && !IsALPHA(c) ||
      !bAlphaMode && !IsDIGIT(c))
      break;
    szBuffer[i] = (char)c;
    i++;
    lpszDate++;
  }
  // Null terminate token buffer string.
  szBuffer[i] = '\0';

  return lpszDate;
}

time_t ParseDateString(char FAR * lpszDate)
{
  char  szToken[21];  // Input token (20 + terminator)
  int   iState;     // Parser state
  int   iFormat;    // Major date format
  BOOL  bAdvance;   // Should machine advance to next token?
  BOOL  bDone;      // Have we parsed a complete date yet?
  int   iDOW, iDay,   // Variables to hold results of parse.
      iMonth, iYear,
      iHour, iMin,
      iSec, iZoneOffset;
  struct tm tmTime;   // Temp structure needed for mktime conversion.
  time_t  tLocalCorrection; // Needed because mktime assumes time is
                // specified in local time.
  time_t  tResult;    // The result of our hard work.

  iState    = ST_WDAY;    // Start off looking for a weekday name.
  bAdvance  = TRUE;     // Need to get initial token.
  bDone   = FALSE;    // We're just getting started.

  // Loop until we've found all the parts.  Premature end of the date
  // string causes a direct return with a value of -1.
  while (!bDone) {
    if (bAdvance) {
      // Get next token from the input.
      lpszDate = GetDateToken(lpszDate, szToken, sizeof(szToken));
    }
    switch (iState) {
      case ST_WDAY: // Parse weekday name.
        if (szToken[0] == '\0') // Check for premature end.
          return -1;
        if (IsDIGIT(szToken[0])) {
          // If the day name starts with a digit, we know we've
          // got an RFC822-style date, so move on to day of month.
          iFormat   = DF_RFC822;
          iState    = ST_MDAY;
          bAdvance  = FALSE;  // Don't advance.
        }
        else {
          // Convert day of week.
          iDOW = ConvertDay(szToken);
          if (0 <= iDOW && iDOW <= 11) {
            // If it's a valid day name, continue.
            iState    = ST_COMMA;
            bAdvance  = TRUE;
          }
          else {
            // If it's not a valid day name, then perhaps
            // we have a ctime-style date with a missing
            // day name.  Assume it's a month name instead.(??)
            iFormat   = DF_CTIME;
            iState    = ST_MONTH;
            bAdvance  = FALSE;  // Don't advance.
          }
        }
        break;  // Go to next state.
      case ST_COMMA:  // Check for a comma following weekday name.
        if (szToken[0] == '\0') // Check for premature end.
          return -1;
        if (szToken[0] == ',' && szToken[1] == '\0') {
          // If we have a comma, then it's an RFC822-style date.
          iFormat   = DF_RFC822;
          iState    = ST_MDAY;
          bAdvance  = TRUE;
        }
        else {
          // Otherwise it's a ctime-style date.
          iFormat   = DF_CTIME;
          iState    = ST_MONTH;
          bAdvance  = FALSE;  // Don't advance.
        }
        break;  // Go to next state.
      case ST_MDAY: // Parse day of month.
        if (szToken[0] == '\0') // Check for premature end.
          return -1;
        iDay = atoi(szToken);
        if (iDay < 1 || iDay > 31)  // Sanity check.
          return -1;
        if (iFormat == DF_RFC822) {
          iState    = ST_DASH1;
          bAdvance  = TRUE;
        }
        else if (iFormat == DF_CTIME) {
          // This is a ctime-style date so we have already
          // parsed the month.  Do a bit more sanity checking.
          // Note that a compiler may flag this line with a
          // "Possible use before definition" warning which
                    // can be ignored.
          if (iDay > iDaysPerMonth[iMonth])
            return -1;
          iState    = ST_HOUR;
          bAdvance  = TRUE;
        }
        else
          return -1;  // Problem: invalid date format!!
        break;  // Go to next state.
      case ST_DASH1:  // Skip optional dash between day and month.
        if (szToken[0] == '\0') // Check for premature end.
          return -1;
        if (szToken[0] == '-' && szToken[1] == '\0')
          bAdvance = TRUE;
        else
          bAdvance = FALSE;
        iState = ST_MONTH;
        break;  // Go to next state.
      case ST_MONTH:  // Parse month name.
        if (szToken[0] == '\0') // Check for premature end.
          return -1;
        iMonth = ConvertMonth(szToken);
        if (iMonth < 0 || iMonth > 11) // Sanity check.
          return -1;
        if (iFormat == DF_RFC822) {
          // We now have both date and month info.  Do a bit
          // more sanity checking on day.
          if (iDay > iDaysPerMonth[iMonth])
            return -1;
          iState    = ST_DASH2;
          bAdvance  = TRUE;
        }
        else if (iFormat == DF_CTIME) {
          iState    = ST_MDAY;
          bAdvance  = TRUE;
        }
        else
          return -1;  // Problem: invalid date format!!
        break;  // Go to next state.
      case ST_DASH2:  // Skip optional dash between month and year.
        if (szToken[0] == '\0') // Check for premature end.
          return -1;
        if (szToken[0] == '-' && szToken[1] == '\0')
          bAdvance = TRUE;
        else
          bAdvance = FALSE;
        iState = ST_YEAR;
        break;  // Go to next state.
      case ST_YEAR: // Parse year.
        if (szToken[0] == '\0') // Check for premature end.
          return -1;
        iYear = atoi(szToken);
        if (iYear > 100)  // Just use the last two digits
          iYear %= 100;
        if (iFormat == DF_RFC822) {
          iState    = ST_HOUR;
          bAdvance  = TRUE;
        }
        else if (iFormat == DF_CTIME) {
                  bDone   = TRUE; // We're done!
        }
        else
          return -1;  // Problem: invalid date format!!
        break;  // Go to next state.
      case ST_HOUR: // Parse hour.
        if (szToken[0] == '\0') // Check for premature end.
          return -1;
        iHour = atoi(szToken);
        if (iHour < 0)  // Sanity check.
          return -1;
        if (iHour <= 23) {
          // Hour appears to be in range.
          iState    = ST_COLON1;
          bAdvance  = TRUE;
        }
        else {
          // Hour is out of range, so we have a military
          // style 4-digit hours-minutes (HHMM).
          iState    = ST_CORRECT4;
          bAdvance  = TRUE;
        }
        break;  // Go to next state.
      case ST_COLON1: // Check for colon between hour and minutes.
        if (szToken[0] == '\0') // Check for premature end.
          return -1;
        if (szToken[0] == ':' && szToken[1] == '\0') {
          iState    = ST_MIN;
          bAdvance  = TRUE;
        }
        else {
          iState    = ST_CORRECT4;
          bAdvance  = FALSE;  // Don't advance.
        }
        break;  // Go to next state.
      case ST_CORRECT4: // Correct for 4-digit hours/mins (HHMM)
        iMin  = iHour % 100;
        iHour = iHour / 100;
        if (iMin > 59 || iHour > 23)  // Sanity check.
          return -1;
        iSec    = 0;  // No seconds.
        iState    = ST_ZONE;
        bAdvance  = FALSE;
        break;
      case ST_MIN:  // Parse minutes.
        if (szToken[0] == '\0') // Check for premature end.
          return -1;
        iMin = atoi(szToken);
        if (iMin < 0 || iMin > 59)  // Sanity check.
          return -1;
        iState    = ST_COLON2;
        bAdvance  = TRUE;
        break;
      case ST_COLON2: // Check for colon between minutes and seconds.
        if (szToken[0] == '\0') // Check for premature end.
          return -1;
        if (szToken[0] == ':' && szToken[1] == '\0') {
          iState    = ST_SEC;
          bAdvance  = TRUE;
        }
        else {
          iSec    = 0;  // No seconds.
          iState    = ST_ZONE;
          bAdvance  = FALSE;
        }
        break;  // Go to next state.
      case ST_SEC:  // Parse seconds.
        if (szToken[0] == '\0') // Check for premature end.
          return -1;
        iSec = atoi(szToken);
        if (iSec < 0 || iSec > 59)  // Sanity check
          return -1;
        iState    = ST_ZONE;
        bAdvance  = TRUE;
        break;
      case ST_ZONE: // Parse timezone.
        if (szToken[0] == '\0') // Check for premature end.
          return -1;
        // Ctime-style dates have the year following the
        // optional timezone string.  If the timezone starts
        // with a digit rather than '+' or '-' and we're parsing
        // a ctime-style date, then assume the timezone isn't
        // present and we have a year.
        if (IsDIGIT(szToken[0]) && iFormat == DF_CTIME) {
          iZoneOffset = 0; // Assume GMT if no other info.
          iState    = ST_YEAR;
          bAdvance  = FALSE;
        }
        else {
          // See if character parsed was a '+' or a '-'.
          if ((szToken[0] == '+' || szToken[0] == '-') &&
            szToken[1] == '\0') {
            // If so, grab the rest of the timezone following
            // and append it to the current token.
            lpszDate = GetDateToken(lpszDate, szToken + 1,
              sizeof(szToken) - 1);
          }
          iZoneOffset = ConvertTimeZone(szToken);
          if (iFormat == DF_RFC822) {
            bDone = TRUE; // We're done!
          }
          else if (iFormat == DF_CTIME) {
            iState    = ST_YEAR;
            bAdvance  = TRUE;
          }
          else
            return -1;  // Problem: invalid date format!!
        }
        break;    // Go to next state.
      default:
        return -1;  // The state machine is off in the weeds!!!
    }
  }

  // Now convert all the parsed information into a time_t value.

  // First convert 01 Jan 70 00:00:00 to a time_t value.  It would be
  // nice if the tm structure contained a timezone field that mktime
  // could use to interpret the rest of the time specified.  There is,
  // no such field, however, and so mktime interprets the tm structure
  // fields as a local time and adds in an offset to get a GMT time_t
  // value.  The following code figures out what this offset is so that
  // we can subtract it out later and add in our own offset based on the
  // timezone value we just parsed in the date.
  tmTime.tm_sec = 0;
  tmTime.tm_min = 0;
  tmTime.tm_hour  = 0;
  tmTime.tm_mday  = 1;
  tmTime.tm_mon = 0;
  tmTime.tm_year  = 70;
  tmTime.tm_wday  = 0;  // Don't need this.
  tmTime.tm_yday  = 0;  // Don't need this.
  tmTime.tm_isdst = 0;  // Don't need this.
  tLocalCorrection = mktime(&tmTime);

  tmTime.tm_sec = iSec;
  tmTime.tm_min = iMin;
  tmTime.tm_hour  = iHour;
  tmTime.tm_mday  = iDay;
  tmTime.tm_mon = iMonth;
  tmTime.tm_year  = iYear;
  tmTime.tm_wday  = 0;  // Don't need this.
  tmTime.tm_yday  = 0;  // Don't need this.
  tmTime.tm_isdst = 0;  // Don't need this.

  // Convert time to seconds since the epoch.
  tResult = mktime(&tmTime);

  // Now adjust time to GMT, taking into account the local bias
  // introduced by mktime and the parsed timezone value.
  tResult -= (tLocalCorrection + (iZoneOffset * 60));

  return tResult;
}
#endif //0 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#if 0  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// This is a part of the Objective Grid C++ Library.
// Copyright (C) 1995-1998 Stingray Software, Inc.
// All rights reserved.
//
// This source code is only intended as a supplement to
// the Objective Grid Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// the Objective Grid product.
//
// Author: Stefan Hoenig
//
// Portions Copyright (C) 1995-1998 X Engineering Software Systems Corp
//

// gxsdate.cpp: date utilities

//#include "stdafx.h"
//#include "gxsinc.h"


//#ifdef _DEBUG
//#undef THIS_FILE
//static char BASED_CODE THIS_FILE[] = __FILE__;
//#endif

//#define new DEBUG_NEW

#define ADJUST_1904 1462

/*
static struct
{
  short noDays;
}      _gx_months[12] =
{
  31,
  28,
  31,
  30,
  31,
  30,
  31,
  31,
  30,
  31,
  30,
  31
};
*/
long __cdecl _gx_encode_date(int si, int year, int month, int day)
{
  // Unused:
  si;

  long gdate,
    i,
    leap_year;

  leap_year = !(year % 4);    /* 1 if leap year */
  _gx_months[1].noDays = (short) (28 + leap_year);

  if (year >= 1900)
    year -= 1900;
  if (year < 0 || year > 199)
    return 0;
  if (month < 1 || month > 12)
    return 0;
  if (day < 1 || day > _gx_months[month - 1].noDays)
    return 0;
  gdate = (long) year * 365 + (year == 0 ? 0 : (year - 1) / 4 + 1);
  for (i = 0; i < month - 1; i++) /* days in prior _gx_months */
    gdate += _gx_months[i].noDays;
  gdate += day;   /* days in current month */
//  if (get_1904_mode(si))
//    gdate -= ADJUST_1904;
  return gdate;
}

long _gx_encode_date_360(int si, int year, int month, int day)
{
  // Unused:
  si;

  long gdate,
    i,
    leap_year;

  leap_year = !(year % 4);    /* 1 if leap year */
  _gx_months[1].noDays = (short) (28 + leap_year);
//Range [1900, 2199]
  if (year >= 1900)
    year -= 1900;
  if (year < 0 || year > 199)
    return 0;
  if (month < 1 || month > 12)
    return 0;
  if (day < 1 || day > _gx_months[month - 1].noDays)
    return 0;
  gdate = (long) year * 365 + (year == 0 ? 0 : (year - 1) / 4 + 1);
  for (i = 0; i < month - 1; i++) /* days in prior _gx_months */
    gdate += 30;
  gdate += day;   /* days in current month */
//  if (get_1904_mode(si))
//    gdate -= ADJUST_1904;
  return gdate;
}


int  __cdecl _gx_decode_date(int si, long gdate, int *year, int *month, int *day)
{
  // Unused:
  si;

  int m;
  long day_of_quad;
  long quads;

  if (gdate <= 0 || gdate > 73050)
    return 0;
//  if (get_1904_mode(si))
//    gdate += ADJUST_1904;
  quads = (gdate - 1) / 1461;
  day_of_quad = (gdate - 1) % 1461 + 1;
  if (day_of_quad <= 366)
  {
    _gx_months[1].noDays = 29;
    *day = day_of_quad;
    *year = 4 * quads;
  }
  else
  {
    _gx_months[1].noDays = 28;
    *day = (day_of_quad - 366 - 1) % 365 + 1;
    *year = 4 * quads + (day_of_quad - 366 - 1) / 365 + 1;
  }
  m = 0;
  while (*day > _gx_months[m].noDays)
  {
    *day -= _gx_months[m].noDays;
    m++;
  }
  *month = m + 1;
  return 1;
}
/*
int  __cdecl _gx_end_of_month(int m, int y)
{
  switch (m)
  {
  case 4:
  case 6:
  case 9:
  case 11:
    return 30;
  case 2:
    if (GX_LEAPYEAR(y))
      return 29;
    return 28;
  default:
    return 31;
  }
}
*/

/* this version of _gx_edate follows the "end-of-month" rule.  It's called
 * mostly by functions in finance_fns2.c.
 */
long  __cdecl _gx_edate(int si, long start_date, int mos)
{
  // Unused:
  si;

  int month,
    day,
    year,
    yrs,
    femflag = 0;
  long edate;

  _gx_decode_date(si, start_date, &year, &month, &day);
  if ((month == 2) && (day == _gx_end_of_month(month, year)))
    femflag = 1;
  yrs = mos / 12;
  mos = mos % 12;
  year += yrs;
  if ((month += mos) <= 0)
  {
    year--;
    month += 12;
  }
  else if (month > 12)
  {
    year++;
    month -= 12;
  }
  if ((day > _gx_end_of_month(month, year)) || femflag)
    day = _gx_end_of_month(month, year);
  edate = _gx_encode_date(si, year, month, day);
  return edate;
}


/* this function will be called by _gx_fn_yearfrac() and some financial functions. */
void  __cdecl _gx_find_yearfrac1(int si, long start_date, long end_date, int basis, gxNumber * year_frac)
{
  int year1,
    year2,
    month,
    day;
  gxNumber year_basis = 360.0,
       days;

  _gx_decode_date(si, start_date, &year1, &month, &day);
  _gx_decode_date(si, end_date, &year2, &month, &day);
  if (basis == 0)
    days = _gx_days360(si, start_date, end_date) + 1;
  else
    days = end_date - start_date + 1;

  if (basis == 3)
    year_basis = 365.0;
  else if (basis == 1)
    year_basis = ((!(year1 % 4)) ? 366.0 : 365.0);
  *year_frac = fabs(days / year_basis);
  return;
}


/* this function is slightly different than fin_yearfrac, it is
 * provide for being consistant with many financial functions
 * with Excel and Quatro Pro
 */
void  __cdecl _gx_find_yearfrac(int si, long start_date, long end_date, int basis, gxNumber * year_frac)
{
  int year1,
    year2,
    month,
    day;
  gxNumber year_basis = 360.0,
       days;

  _gx_decode_date(si, start_date, &year1, &month, &day);
  _gx_decode_date(si, end_date, &year2, &month, &day);
  if (basis == 0)
    days = _gx_days360(si, start_date, end_date);
  else
    days = end_date - start_date;

  if (basis == 3)
    year_basis = 365.0;
  else if (basis == 1)
    year_basis = ((!(year1 % 4)) ? 366.0 : 365.0);
  *year_frac = fabs(days / year_basis);
  return;
}


long  __cdecl _gx_days360(int si, long date1, long date2)
{
  int y1,
    y2,
    m1,
    m2,
    d1,
    d2;

  _gx_decode_date(si, date1, &y1, &m1, &d1);
  _gx_decode_date(si, date2, &y2, &m2, &d2);

  /* convention concerning Feb - "end-of-month rule" */
  if (d1 == _gx_end_of_month(m1, y1))
  {
    d1 = 30;
    if (d2 == _gx_end_of_month(m2, y2))
      d2 = 30;
  }
  /* convention concerning last day of the month */
  if (d1 == 31)
    d1--;
  if ((d2 == 31) && (d1 > 29))
    d2--;
  return (y2 - y1) * 360 + (m2 - m1) * 30 + (d2 - d1);
}

void  __cdecl _gx_current_time(int *yr, int *mo, int *da, int *hr, int *min, int *sec)
{
  time_t timeval;
  struct tm *t;

  timeval = time(NULL);
  t = localtime(&timeval);
  *yr = t->tm_year;
  *mo = t->tm_mon + 1;
  *da = t->tm_mday;
  *hr = t->tm_hour;
  *min = t->tm_min;
  *sec = t->tm_sec;
}

int  __cdecl _gx_get_date(int si, LPCTSTR date_str, int *mp, int *dp, int *yp, int *fmtp)
{
  // Unused:
  si;

#if _MFC_VER >= 0x0300
  COleDateTime dt;
  if (dt.ParseDateTime(date_str))
  {
    *mp = dt.GetMonth();
    *dp = dt.GetDay();
    *yp = dt.GetYear();

    *fmtp = GX_FMT_DATE;

    return 1;
  }                 
#else                                     
  TIMESTAMP_STRUCT tm;  
  if (GXParseDateTime(&tm, date_str))
  {
    *mp = tm.month;
    *dp = tm.day;
    *yp = tm.year;

    *fmtp = GX_FMT_DATE;

    return 1;
  }                 
#endif
  return 0;
}

int  __cdecl _gx_get_time(LPCTSTR time_str, int *hp, int *mp, int *sp)
{
#if _MFC_VER >= 0x0300
  COleDateTime dt;
  if (dt.ParseDateTime(time_str))
  {
    *hp = dt.GetHour();
    *mp = dt.GetMinute();
    *sp = dt.GetSecond();

    return 1;
  }
#else
  TIMESTAMP_STRUCT tm;  
  if (GXParseDateTime(&tm, time_str))
  {
    *hp = tm.hour;
    *mp = tm.minute;
    *sp = tm.second;

    return 1;
  }                 
#endif
  return 0;
}

int  __cdecl _gx_encode_time(double *timeval, int hr, int min, int sec)
{
  if (hr < 0 || hr > 23 || min < 0 || min > 59 || sec < 0 || sec > 59)
    return 0;
  *timeval = ((sec / 60.0 + min) / 60.0 + hr) / 24.0;
  return 1;
}

int  __cdecl _gx_decode_time(double timeval, int *hr, int *min, int *sec)
{
  register int total;

  timeval -= floor(timeval);  /* throw away the integer part */
  total = (int) (timeval * 24 * 60 * 60 + 0.5);
  *sec = total % 60;
  total /= 60;
  *min = total % 60;
  total /= 60;
  *hr = total;
  return 1;
}

/////////////////////////////////////////////////////////////////////////////
// GXBGetTmFromOleDate
//
// Function to convert a DATE (base for COleDateTime) to a tm structure.
//
/*
BOOL AFXAPI GXBGetTmFromOleDate(DATE dtSrc, struct tm& tmDest)
{
  // Half a second, expressed in days
  static const DATE HALF_SECOND = (1.0/172800.0);

  // One-based array of days in year at month start
  static int rgMonthDays[13] =
    {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

  // The legal range does not actually span year 0 to 9999.
  if (dtSrc > maxDateTime || dtSrc < minDateTime) // about year 100 to about 9999
    return FALSE;

  long nDays;             // Number of days since Dec. 30, 1899
  long nDaysAbsolute;     // Number of days since 1/1/0
  long nSecsInDay;        // Time in seconds since midnight
  long nMinutesInDay;     // Minutes in day

  long n400Years;         // Number of 400 year increments since 1/1/0
  long n400Century;       // Century within 400 year block (0,1,2 or 3)
  long n4Years;           // Number of 4 year increments since 1/1/0
  long n4Day;             // Day within 4 year block
              //  (0 is 1/1/yr1, 1460 is 12/31/yr4)
  long n4Yr;              // Year within 4 year block (0,1,2 or 3)
  BOOL bLeap4 = TRUE;     // TRUE if 4 year block includes leap year

  double dblDate = dtSrc; // tempory serial date

  // If a valid date, then this conversion should not overflow
  nDays = (long)dblDate;

  // Round to the second
  dblDate += ((dtSrc > 0.0) ? HALF_SECOND : -HALF_SECOND);

  nDaysAbsolute = (long)dblDate + 693959L; // Add days from 1/1/0 to 12/30/1899

  dblDate = fabs(dblDate);
  nSecsInDay = (long)((dblDate - floor(dblDate)) * 86400.);

  // Calculate the day of week (sun=1, mon=2...)
  //   -1 because 1/1/0 is Sat.  +1 because we want 1-based
  tmDest.tm_wday = (int)((nDaysAbsolute - 1) % 7L) + 1;

  // Leap years every 4 yrs except centuries not multiples of 400.
  n400Years = (long)(nDaysAbsolute / 146097L);

  // Set nDaysAbsolute to day within 400-year block
  nDaysAbsolute %= 146097L;

  // -1 because first century has extra day
  n400Century = (long)((nDaysAbsolute - 1) / 36524L);

  // Non-leap century
  if (n400Century != 0)
  {
    // Set nDaysAbsolute to day within century
    nDaysAbsolute = (nDaysAbsolute - 1) % 36524L;

    // +1 because 1st 4 year increment has 1460 days
    n4Years = (long)((nDaysAbsolute + 1) / 1461L);

    if (n4Years != 0)
      n4Day = (long)((nDaysAbsolute + 1) % 1461L);
    else
    {
      bLeap4 = FALSE;
      n4Day = (long)nDaysAbsolute;
    }
  }
  else
  {
    // Leap century - not special case!
    n4Years = (long)(nDaysAbsolute / 1461L);
    n4Day = (long)(nDaysAbsolute % 1461L);
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
      / * Feb. 29 * /
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

  // Month number always >= n/32, so save some loop time * /
  for (tmDest.tm_mon = (n4Day >> 5) + 1;
    n4Day > rgMonthDays[tmDest.tm_mon]; tmDest.tm_mon++);

  tmDest.tm_mday = (int)(n4Day - rgMonthDays[tmDest.tm_mon-1]);

DoTime:
  if (nSecsInDay == 0)
    tmDest.tm_hour = tmDest.tm_min = tmDest.tm_sec = 0;
  else
  {
    tmDest.tm_sec = (int)nSecsInDay % 60L;
    nMinutesInDay = nSecsInDay / 60L;
    tmDest.tm_min = (int)nMinutesInDay % 60;
    tmDest.tm_hour = (int)nMinutesInDay / 60;
  }

  return TRUE;
}
*/

// Useful macro for determining the number of elements in an array
//#define dimensionof(a) (sizeof(a)/sizeof(a[0]))

// Date/Time format characters
static const TCHAR cHours12 = _T('h');        // Hours (12 hour clock)
static const TCHAR cHours24 = _T('H');        // Hours (24 hour clock)
static const TCHAR cMinutes = _T('m');        // Minutes
static const TCHAR cSeconds = _T('s');        // Seconds
static const TCHAR cAmPm    = _T('t');        // AM/PM designator
static const TCHAR cDay     = _T('d');        // Day of week/month
static const TCHAR cMonth   = _T('M');        // Month
static const TCHAR cYear    = _T('y');        // Year
static const TCHAR cEra     = _T('g');        // Era

// List of type codes for Am/Pm strings
static const LCTYPE AmPmIds[2] = 
{
  LOCALE_S1159,                  // Am 
  LOCALE_S2359                  // Pm
};

//-----------------------------------------------------------------------------
//  ParseDateTimeFormat
//
//  Parses the date/time format string returned by GetFormat and builds the
//  gadget array (m_gadgets) for each of the date/time component fields
//
void CGXBDateTimeCtrl::ParseDateTimeFormat()
{
  // Table mapping date/time format characters onto correct function for
  // parsing that format.
  struct 
  {
    TCHAR c;
    void (CGXBDateTimeCtrl::*fn)(LPCTSTR&, LPCTSTR&, UINT);
    UINT  u;
    BOOL bDate;
  }
    static const DTFormatTable[] =
       {
          { cHours12,  &CGXBDateTimeCtrl::ParseHours,      FALSE , 0 },
          { cHours24,  &CGXBDateTimeCtrl::ParseHours,      TRUE  , 0 },
          { cMinutes,  &CGXBDateTimeCtrl::ParseMinutes,    0     , 0 },
          { cSeconds,  &CGXBDateTimeCtrl::ParseSeconds,    0     , 0 },
          { cAmPm,     &CGXBDateTimeCtrl::ParseAmPm,       0     , 0 },
          { cDay,      &CGXBDateTimeCtrl::ParseDay,        0     , TRUE },
          { cMonth,    &CGXBDateTimeCtrl::ParseMonth,      0     , TRUE },
          { cYear,     &CGXBDateTimeCtrl::ParseYear,       0     , TRUE },
          { cEra,      &CGXBDateTimeCtrl::ParseEra,        0     , TRUE },
          { _T('\''),  &CGXBDateTimeCtrl::ParseQuotedText, 0     , 0 },
          { _T('"'),   &CGXBDateTimeCtrl::ParseQuotedText, 0     , 0 }
       };

  // Get the current date/time format string
  CString temp;
  GetFormat(temp);

  m_bDateTokens = FALSE;

  // We loop down the date/time format string. For each character we 
  // recognise, we call a function for parsing that format string. This
  // function will add any text not recognised since the last recognised
  // character as a static gadget, before adding a gadget to handle the
  // recognised date/time component.
  LPCTSTR lpsz = temp;
  LPCTSTR lpszStart = lpsz;
  while(*lpsz)
  {
    // Lookup to see if we know about this character
    for(int i=0; i<dimensionof(DTFormatTable); i++)
    {
      if(DTFormatTable[i].c == *lpsz)
      {
        // We know about it, so call it's parsing function.
        (this->*DTFormatTable[i].fn)(lpszStart, lpsz, 
                       DTFormatTable[i].u);

        m_bDateTokens |= DTFormatTable[i].bDate;

        break;
      }
    }

    lpsz = _tcsinc(lpsz);        // Move forward to next character
  }
  
  // Flush any text not since the last handled sequence.
  FlushStatic(lpszStart, lpsz);

  // Update all new gadgets with the current date/time values
  UpdateGadgets();
}

//-----------------------------------------------------------------------------
//  ParseHours
//
//  Parses the hour fields 'h' and 'H'.
//
//    Formats:   h  hours (12 hour clock) with no lead zero
//              hh  hours (12 hour clock) with lead zero
//               H  hours (24 hour clock) with no lead zero
//              HH  hours (24 hour clock) with lead zero
//
void CGXBDateTimeCtrl::ParseHours(LPCTSTR& lpszStart, LPCTSTR& lpsz, 
                 UINT uParam)
{
  // Add any unrecognised text as static gadget
  FlushStatic(lpszStart, lpsz);

  // Create numeric gadget for handling hours
  CGXBDTNumericGadget* pGadget = new CGXBDTNumericGadget;

  if(uParam)
  {
    // 24 hour clock
    BOOL bLeadZero = CheckLeadZero(lpsz, cHours24);
    pGadget->Initialise(this, 0, 23, 0, bLeadZero, GXDT_DTID_24HOUR);
  }
  else
  {
    // 12 hour clock
    BOOL bLeadZero = CheckLeadZero(lpsz, cHours12);
    pGadget->Initialise(this, 1, 12, 0, bLeadZero, GXDT_DTID_12HOUR);
  }
  
  if(m_nNoEdit & FixedHour)
  {
    // The user is not allowed to change the hour, so ensure this field
    // can't receive focus
    pGadget->SetStyle(pGadget->GetStyle() & (~CGXBDTGadget::WantFocus));
  }

  m_gadgets.Add(pGadget);

  // Skip past this field
  lpszStart = _tcsinc(lpsz);
}

//-----------------------------------------------------------------------------
//  ParseMinutes
//
//  Parses the minutes field 'm'.
//
//    Formats:   m  minutes with no lead zero
//              mm  minutes with lead zero
//
void CGXBDateTimeCtrl::ParseMinutes(LPCTSTR& lpszStart, LPCTSTR& lpsz, 
                   UINT / * uParam * /)
{
  // Add any unrecognised text as static gadget
  FlushStatic(lpszStart, lpsz);

  // Create numeric gadget for handling minutes
  BOOL bLeadZero = CheckLeadZero(lpsz, cMinutes);
  CGXBDTNumericGadget* pGadget = new CGXBDTNumericGadget;
  pGadget->Initialise(this, 0, 59, 0, bLeadZero, GXDT_DTID_MINUTE);

  if(m_nNoEdit & FixedMinute)
  {
    // The user is not allowed to change the minutes, so ensure this field
    // can't receive focus
    pGadget->SetStyle(pGadget->GetStyle() & (~CGXBDTGadget::WantFocus));
  }

  m_gadgets.Add(pGadget);

  // Skip past this field
  lpszStart = _tcsinc(lpsz);
}

//-----------------------------------------------------------------------------
//  ParseSeconds
//
//  Parses the seconds field 's'.
//
//    Formats:   s  seconds with no lead zero
//              ss  seconds with lead zero
//
void CGXBDateTimeCtrl::ParseSeconds(LPCTSTR& lpszStart, LPCTSTR& lpsz, 
                   UINT / * uParam * /)
{
  // Add any unrecognised text as static gadget
  FlushStatic(lpszStart, lpsz);

  // Create numeric gadget for seconds minutes
  BOOL bLeadZero = CheckLeadZero(lpsz, cSeconds);
  CGXBDTNumericGadget* pGadget = new CGXBDTNumericGadget;
  pGadget->Initialise(this, 0, 59, 0, bLeadZero, GXDT_DTID_SECOND);

  if(m_nNoEdit & FixedSecond)
  {
    // The user is not allowed to change the seconds, so ensure this field
    // can't receive focus
    pGadget->SetStyle(pGadget->GetStyle() & (~CGXBDTGadget::WantFocus));
  }

  m_gadgets.Add(pGadget);

  // Skip past this field
  lpszStart = _tcsinc(lpsz);
}

//-----------------------------------------------------------------------------
//  ParseAmPm
//
//  Parses the am/pm field 't'.
//
//    Formats:   t  One digit Am/Pm designator
//              tt  Complete Am/Pm designator
//
void CGXBDateTimeCtrl::ParseAmPm(LPCTSTR& lpszStart, LPCTSTR& lpsz, 
                UINT / * uParam * /)
{
  // Add any unrecognised text as static gadget
  FlushStatic(lpszStart, lpsz);

  // TRUE if we are dealing with abbreviated form
  BOOL bAbbreviated = !CheckLeadZero(lpsz, cAmPm);

  // Build a list of the Am/Pm designators (all 2 of them!)
  TCHAR buf[256];
  LCID lcid = GetUserDefaultLCID();

  CStringArray list;
  for(int i=0; i<dimensionof(AmPmIds); i++)
  {
    GetLocaleInfo(lcid, AmPmIds[i], buf, sizeof(buf));
    if(bAbbreviated)
    {
      LPTSTR ptr = _tcsinc(buf);
      if(ptr)
        *ptr = TCHAR(NULL);
    }

    list.Add(buf);
  }

  // Now create and initialise a list gadget for this field
  CGXBDTListGadget* pGadget = new CGXBDTListGadget;
  pGadget->Initialise(this, list, 0, GXDT_DTID_AMPM);

  if(m_nNoEdit & FixedHour)
  {
    // The user is not allowed to change the hours, so ensure this field
    // can't receive focus.
    pGadget->SetStyle(pGadget->GetStyle() & (~CGXBDTGadget::WantFocus));
  }

  m_gadgets.Add(pGadget);

  // Skip past this field
  lpszStart = _tcsinc(lpsz);
}

//-----------------------------------------------------------------------------
//  ParseDay
//
//  Parses the day and day of week fields 'd'.
//
//    Formats:   d  day of month with no leading zero
//              dd  day of month with leading zero
//             ddd  abbreviated day of week
//            dddd  full day of week
//
void CGXBDateTimeCtrl::ParseDay(LPCTSTR& lpszStart, LPCTSTR& lpsz, 
                 UINT / * uParam * /)
{
  // Add any unrecognised text as static gadget
  FlushStatic(lpszStart, lpsz);

  // Determine format required
  BOOL bNumeric = TRUE;
  BOOL bLong    = TRUE;
  if(!CheckLeadZero(lpsz, cDay))
    bLong = FALSE;
  else if(CheckLeadZero(lpsz, cDay))
  {
    bNumeric = FALSE;
    if(!CheckLeadZero(lpsz, cDay))
      bLong = FALSE;
  }

  // We now have:  bLong  bNumeric
  //               FALSE   TRUE        d (day of month with no leading zero)
  //               TRUE    TRUE       dd (day of month with leading zero)
  //               FALSE   FALSE     ddd (abbreviated day of week)
  //               TRUE    FALSE    dddd (full day of week)

  if(bNumeric)
  {
    // Create and initialise numeric gadget for day of month
    CGXBDTNumericGadget* pGadget = new CGXBDTNumericGadget;
    pGadget->Initialise(this, 1, 31, 0, bLong, GXDT_DTID_DAYNO);

    if(m_nNoEdit & FixedDay)
    {
      // The user is not allowed to change the day, so ensure this field
      // can't receive focus
      pGadget->SetStyle(pGadget->GetStyle() & (~CGXBDTGadget::WantFocus));
    }

    m_gadgets.Add(pGadget);
  }
  else
  {
    // We need to build a list of the locale day's of week names
    CStringArray list;
    CString strDay;

    for(int i=1; i<=7; i++)
    {
      VERIFY(CGXBLocale::GetDayName(strDay, i, bLong));
      list.Add(strDay);    
    }

    // Create and initialise a list gadget (with these day names)
    CGXBDTListGadget* pGadget = new CGXBDTListGadget;
    pGadget->Initialise(this, list, 0, GXDT_DTID_DAYNAME);

    if(m_nNoEdit & FixedDay)
    {
      // The user is not allowed to change the day, so ensure this field
      // can't receive focus
      pGadget->SetStyle(pGadget->GetStyle() & (~CGXBDTGadget::WantFocus));
    }

    m_gadgets.Add(pGadget);
  }

  // Skip past this field
  lpszStart = _tcsinc(lpsz);
}

//-----------------------------------------------------------------------------
//  ParseMonth
//
//  Parses the month field 'M'.
//
//    Formats:   M  Month as digit with no leading zero
//              MM  Month as digit with leading zero
//             MMM  Abbreviated month name
//            MMMM  Full month name
//
void CGXBDateTimeCtrl::ParseMonth(LPCTSTR& lpszStart, LPCTSTR& lpsz, 
                 UINT / * uParam * /)
{
  // Add any unrecognised text as static gadget
  FlushStatic(lpszStart, lpsz);

  // Determine format required
  BOOL bNumeric = TRUE;
  BOOL bLong    = TRUE;
  if(!CheckLeadZero(lpsz, cMonth))
    bLong = FALSE;
  else if(CheckLeadZero(lpsz, cMonth))
  {
    bNumeric = FALSE;
    if(!CheckLeadZero(lpsz, cMonth))
      bLong = FALSE;
  }

  // We now have:  bLong  bNumeric
  //               FALSE   TRUE       M (Month as digit with no leading zero)
  //               TRUE    TRUE      MM (Month as digit with leading zero)
  //               FALSE   FALSE    MMM (abbreviated month name)
  //               TRUE    FALSE   MMMM (full month name)

  if(bNumeric)
  {
    // Create and initialise numeric gadget for month digit
    CGXBDTNumericGadget* pGadget = new CGXBDTNumericGadget;
    pGadget->Initialise(this, 1, 12, 0, bLong, GXDT_DTID_MONTHNO);

    if(m_nNoEdit & FixedMonth)
    {
      // The user is not allowed to change the month, so ensure this 
      // field can't receive focus
      pGadget->SetStyle(pGadget->GetStyle() & (~CGXBDTGadget::WantFocus));
    }

    m_gadgets.Add(pGadget);
  }
  else
  {
    // We need to build a list of the locale month names
    CStringArray list;
    CString strMonth;

    for(int i=1; i<=12; i++)
    {
      VERIFY(CGXBLocale::GetMonthName(strMonth, i, bLong));
      list.Add(strMonth);    
    }

    // Create and initialise a list gadget (with these month names)
    CGXBDTListGadget* pGadget = new CGXBDTListGadget;
    pGadget->Initialise(this, list, 0, GXDT_DTID_MONTHNAME);

    if(m_nNoEdit & FixedMonth)
    {
      // The user is not allowed to change the month, so ensure this 
      // field can't receive focus
      pGadget->SetStyle(pGadget->GetStyle() & (~CGXBDTGadget::WantFocus));
    }

    m_gadgets.Add(pGadget);
  }

  // Skip past this field
  lpszStart = _tcsinc(lpsz);
}

//-----------------------------------------------------------------------------
//  ParseYear
//
//  Parses the year field 'y'.
//
//    Formats:   y  Year as 2 digits with no lead zero for year less than 10
//              yy  Year as 2 digits with lead zero for year less than 10
//             yyy  Year as 4 digits
//            yyyy  Year as 4 digits (same as yyy)
//
void CGXBDateTimeCtrl::ParseYear(LPCTSTR& lpszStart, LPCTSTR& lpsz, 
                UINT / * uParam * /)
{
  // Add any unrecognised text as static gadget
  FlushStatic(lpszStart, lpsz);

  BOOL b2Digit   = TRUE;
  BOOL bLeadZero = TRUE;
  if(!CheckLeadZero(lpsz, cYear))
    // 2 digit, no lead zero
    bLeadZero = FALSE;
  else if(CheckLeadZero(lpsz, cYear))
  {
    // 4 digit
    b2Digit   = FALSE;

    // Case of yyy and yyyy are same
    CheckLeadZero(lpsz, cYear);
  }
  // else  2 digit lead zero

  // We now have:  b2Digit  bLeadZero
  //                TRUE     FALSE       y (2 digit with no lead zero)
  //                TRUE     TRUE       yy (2 digit with lead zero)
  //                FALSE    ?        yyyy (4 digit)

  // Create and initialise numeric gadget for year field
  CGXBDTNumericGadget* pGadget = new CGXBDTNumericGadget;
  if(b2Digit)
    pGadget->Initialise(this, 0, 99, 0, bLeadZero, GXDT_DTID_YEAR2);
  else
    pGadget->Initialise(this, 0, 9999, 0, FALSE, GXDT_DTID_YEAR4);

  if(m_nNoEdit & FixedYear)
  {
    // The user is not allowed to change the year, so ensure this 
    // field can't receive focus
    pGadget->SetStyle(pGadget->GetStyle() & (~CGXBDTGadget::WantFocus));
  }

  m_gadgets.Add(pGadget);

  // Skip past this field
  lpszStart = _tcsinc(lpsz);
}

//-----------------------------------------------------------------------------
//  ParseEra
//
//  Parses the era field 'g' (note we don't currently support era's).
//
//    Formats:  gg  Period/era string
//
void CGXBDateTimeCtrl::ParseEra(LPCTSTR& lpszStart, LPCTSTR& lpsz, UINT / * uParam  * /)
{
  // We currently don't handle era's ... so just ignore

  // Add any unrecognised text as static gadget
  FlushStatic(lpszStart, lpsz);

  // Call CheckLeadZero to handle the case of 'gg' as well as 'g'.
  CheckLeadZero(lpsz, cEra);

  // Skip past this field
  lpszStart = _tcsinc(lpsz);
}

//-----------------------------------------------------------------------------
//  ParseQuotedText
/
//  Parses quoted text and emits it through transparently to the gadget list.
//
void CGXBDateTimeCtrl::ParseQuotedText(LPCTSTR& lpszStart, LPCTSTR& lpsz, UINT / * uParam * /)
{
  // Add any unrecognised text as static gadget
  FlushStatic(lpszStart, lpsz);

  // Find the end of the quoted text
  TCHAR cQuote = *lpsz;

  lpszStart = lpsz = _tcsinc(lpsz);
  
  while(*lpsz && *lpsz != cQuote)
    lpsz = _tcsinc(lpsz);

  // and add this string as a static string
  FlushStatic(lpszStart, lpsz);

  // Move past the last quote
  lpszStart = _tcsinc(lpsz);
}


// This is a part of the Objective Grid C++ Library.
// Copyright (C) 1995-1998 Stingray Software, Inc.
// All rights reserved.
//
// This source code is only intended as a supplement to
// the Objective Grid Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// the Objective Grid product.
//
// Author: Stefan Hoenig
//

// gxext.h : common extensions
/////////////////////////////////////////////////////////////////////////////
#endif //if 0 >>>>>>>>>>>>>>>>>>>>

#if 0
#ifndef _GXEXT_H_
#define _GXEXT_H_

#ifndef _GXSTATE_H_
#include "gxstate.h"
#endif

#ifndef _GXRESRC_H_
#include "gxresrc.h"
#endif

//
// GridMFC Extension DLL
// initialize declaration context
//

#ifdef _GXDLL
  #undef AFXAPP_DATA
  #define AFXAPP_DATA AFXAPI_DATA
  #undef AFX_DATA
  #define AFX_DATA    GX_DATAEXT
#endif

// header file

/////////////////////////////////////////////////////////////////////////////
// Time and date formatting

#include <time.h>

#if !defined(_AFX_NO_DB_SUPPORT)

#include <sqlext.h> // TIMESTAMP_STRUCT

#else

// needed for GXFormatTimeStamp

typedef short int               SWORD;
typedef unsigned short int      UWORD;
typedef unsigned long int       UDWORD;

typedef SWORD                   SQLSMALLINT;
typedef UDWORD                  SQLUINTEGER;
typedef UWORD                   SQLUSMALLINT;

typedef struct tagTIMESTAMP_STRUCT
{
    SQLSMALLINT    year;
    SQLUSMALLINT   month;
    SQLUSMALLINT   day;
    SQLUSMALLINT   hour;
    SQLUSMALLINT   minute;
    SQLUSMALLINT   second;
    SQLUINTEGER    fraction;
} TIMESTAMP_STRUCT;

#endif

size_t AFXAPI GXIntlStrFtime(
  HINSTANCE nResourceHandle,
  UINT nStrFTimeResourceID,
  LPTSTR s,
  size_t maxs,
  LPCTSTR f,
  const struct tm *t);

void AFXAPI GXFormatTimeStamp(CString& strRet, const CTime* pTime);
void AFXAPI GXFormatTimeStamp(CString& strRet, const TIMESTAMP_STRUCT* pTime);

// Parsing date/time values

// NOTE: This methods are provided because parsing
// date/time values was not possible with VC 1.5x
// and VC 2.x projects.
//
// If you are using VC 4.x or greater, we recommend
// using the COleDateTime::ParseDateTime for this
// purpose.

void AFXAPI GXImplementOleDateTime();
void AFXAPI GXImplementNoOleDateTime();
void AFXAPI GXUpdateDateTimeSettings();
GXDateFormat AFXAPI GXGetDateFormatFromWinIni(BOOL bReload, BOOL& bCentury, TCHAR& chDateSep);
TCHAR AFXAPI GXGetTimeSeparatorFromWinIni(BOOL bReload = FALSE);

// CTime
BOOL AFXAPI GXParseDateTime(struct tm* ptm, LPCTSTR szValue, GXDateFormat DateFormat = gxDEFAULT);

// TIMESTAMP_STRUCT
BOOL AFXAPI GXParseDateTime(TIMESTAMP_STRUCT* ptm, LPCTSTR szValue, GXDateFormat DateFormat = gxDEFAULT);


#ifndef _GXDLL_H_
#include "gxdll.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXTIME")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#if _MFC_VER >= 0x0300

// GXIntlStrFtime is obsolete for newer MFC versions
// because strftime already provides the necessary
// fucntionality.
//
// You should call _tsetlocale() in the initialization
// code of your application if you want to support
// locale date/time representatons.
//

size_t AFXAPI GXIntlStrFtime(HINSTANCE, UINT, LPTSTR s, size_t maxs, LPCTSTR f, const struct tm *t)
{
#if defined(_UNICODE) && _MFC_VER < 0x0400
  char astring[64];

  WideCharToMultiByte (CP_ACP, 0, f, -1,
            astring, 64, NULL, NULL);

  return _tcsftime(s, maxs, astring, t);
#else
  return _tcsftime(s, maxs, f, t);
#endif
}

#else

static void AFX_CDECL strfmt(LPTSTR str, LPCTSTR fmt, ...);

#define ADAY_OFFSET     0
#define DAY_OFFSET      7
#define AMONTH_OFFSET   14
#define MONTH_OFFSET    26
#define STD_DATETIME    38
#define STD_DATE        39
#define STD_TIME        40

/**
 *
 * size_t GXIntlStrFtime(HINSTANCE nResourceHandle,
 *                      UINT nStrFTimeResourceID,
 *          LPTSTR str,
 *                      size_t maxs,
 *          LPCTSTR fmt,
 *                      const struct tm *t)
 *
 *      this functions acts much like a sprintf for time/date output.
 *      given a pointer to an output buffer, a format string and a
 *      time, it copies the time to the output buffer formatted in
 *      accordance with the format string.  the parameters are used
 *      as follows:
 *
 *
 *          nResourceHandle should be assigned with AfxGetResourceHandle()
 *          in MFC
 *
 *          nStrFTimeResourceID is the resource ID in your .RC file
 *          where the day abbreviations start. First there must be
 *          seven day abbreviations, then seven full day names, then
 *          month abbreviations and at last full month. It is important
 *          that you have continous resource ids for these names.
 *
 *          str is a pointer to the output buffer, there should
 *          be at least maxs characters available at the address
 *          pointed to by str.
 *
 *          maxs is the maximum number of characters to be copied
 *          into the output buffer, included the '\0' terminator
 *
 *          fmt is the format string.  a percent sign (%) is used
 *          to indicate that the following character is a special
 *          format character.  the following are valid format
 *          characters:
 *
 *              %A      full weekday name (Monday)
 *              %a      abbreviated weekday name (Mon)
 *              %B      full month name (January)
 *              %b      abbreviated month name (Jan)
 *              %c      standard date and time representation
 *              %d      day-of-month (01-31)
 *              %H      hour (24 hour clock) (00-23)
 *              %I      hour (12 hour clock) (01-12)
 *              %j      day-of-year (001-366)
 *              %M      minute (00-59)
 *              %m      month (01-12)
 *              %p      local equivalent of AM or PM
 *              %S      second (00-59)
 *              %U      week-of-year, first day sunday (00-53)
 *              %W      week-of-year, first day monday (00-53)
 *              %w      weekday (0-6, sunday is 0)
 *              %X      standard time representation
 *              %x      standard date representation
 *              %Y      year with century
 *              %y      year without century (00-99)
 *              %Z      timezone name
 *              %%      percent sign
 *
 *      the standard date string is equivalent to:
 *
 *          %a %b %d %Y
 *
 *      the standard time string is equivalent to:
 *
 *          %H:%M:%S
 *
 *      the standard date and time string is equivalent to:
 *
 *          %a %b %d %H:%M:%S %Y
 *
 *      GXIntlStrFtime returns the number of characters placed in the
 *      buffer, not including the terminating \0, or zero if more
 *      than maxs characters were produced.
 *
**/

size_t AFXAPI GXIntlStrFtime(HINSTANCE nResourceHandle, UINT nStrFTimeResourceID, LPTSTR s, size_t maxs, LPCTSTR f, const struct tm *t)
{
    int w;
    LPTSTR p;
    LPTSTR q;
    LPTSTR r;

    UINT aday   = nStrFTimeResourceID+ADAY_OFFSET;
    UINT day    = nStrFTimeResourceID+DAY_OFFSET;
    UINT amonth = nStrFTimeResourceID+AMONTH_OFFSET;
    UINT month  = nStrFTimeResourceID+MONTH_OFFSET;
    UINT ddt    = nStrFTimeResourceID+STD_DATETIME;
    UINT ddate  = nStrFTimeResourceID+STD_DATE;
    UINT dtime  = nStrFTimeResourceID+STD_TIME;

    char buf[128], buf1[128];

    p = s;
    q = s + maxs - 1;
    while ((*f != '\0'))
    {
      if (*f++ == '%')
      {
          r = buf;
          switch (*f++)
          {
          case '%' :
            r = "%";
            break;

          case 'a' :
            LoadString(nResourceHandle, aday+t->tm_wday, buf, sizeof(buf));
            break;

          case 'A' :
            LoadString(nResourceHandle, day+t->tm_wday, buf, sizeof(buf));
            break;

          case 'b' :
            LoadString(nResourceHandle, amonth+t->tm_mon, buf, sizeof(buf));
            break;

          case 'B' :
            LoadString(nResourceHandle, month+t->tm_mon, buf, sizeof(buf));
            break;

          case 'c' :
            LoadString(nResourceHandle, ddt, buf1, sizeof(buf1));
            GXIntlStrFtime(nResourceHandle, nStrFTimeResourceID, buf, sizeof(buf), buf1, t);
            break;

          case 'd' :
            strfmt(r,"%2",t->tm_mday);
            break;

          case 'H' :
            strfmt(r,"%2",t->tm_hour);
            break;

          case 'I' :
            strfmt(r,"%2",(t->tm_hour%12)?t->tm_hour%12:12);
            break;

          case 'j' :
            strfmt(r,"%3",t->tm_yday+1);
            break;

          case 'm' :
            strfmt(r,"%2",t->tm_mon+1);
            break;

          case 'M' :
            strfmt(r,"%2",t->tm_min);
            break;

          case 'p' :
            r = (t->tm_hour>11)?"PM":"AM";
            break;

          case 'S' :
            strfmt(r,"%2",t->tm_sec);
            break;

          case 'U' :
            w = t->tm_yday/7;
            if (t->tm_yday%7 > t->tm_wday)
                w++;
            strfmt(r, "%2", w);
            break;

          case 'W' :
            w = t->tm_yday/7;
            if (t->tm_yday%7 > (t->tm_wday+6)%7)
                w++;
            strfmt(r, "%2", w);
            break;

          case 'w' :
            strfmt(r,"%1",t->tm_wday);
            break;

          case 'x' :
            {
              BOOL bCentury;
              TCHAR chDateSep;
              GXDateFormat DateFormat = GXGetDateFormatFromWinIni(FALSE, bCentury, chDateSep);
              if (bCentury)
              {
                if (DateFormat == gxDDMMYY)
                  wsprintf(buf1, _T("%%d%c%%m%c%%Y"), chDateSep, chDateSep);
                else if (DateFormat == gxMMDDYY)
                  wsprintf(buf1, _T("%%m%c%%d%c%%Y"), chDateSep, chDateSep);
                else if (DateFormat == gxYYMMDD)
                  wsprintf(buf1, _T("%%Y%c%%m%c%%d"), chDateSep, chDateSep);
              }
              else
              {
                if (DateFormat == gxDDMMYY)
                  wsprintf(buf1, _T("%%d%c%%m%c%%y"), chDateSep, chDateSep);
                else if (DateFormat == gxMMDDYY)
                  wsprintf(buf1, _T("%%m%c%%d%c%%y"), chDateSep, chDateSep);
                else if (DateFormat == gxYYMMDD)
                  wsprintf(buf1, _T("%%y%c%%m%c%%d"), chDateSep, chDateSep);
              }

              GXIntlStrFtime(nResourceHandle, nStrFTimeResourceID, buf, sizeof(buf), buf1, t);
            }
            break;

          case 'X' :
            LoadString(nResourceHandle, dtime, buf1, sizeof(buf1));
            GXIntlStrFtime(nResourceHandle, nStrFTimeResourceID, buf, sizeof(buf), buf1, t);
            break;

          case 'y' :
            strfmt(r,"%2",t->tm_year%100);
            break;

          case 'Y' :
            strfmt(r,"%4",t->tm_year+1900);
            break;

          case 'Z' :
#if _MFC_VER >= 0x0300
            {
              TIME_ZONE_INFORMATION tzi;

// Wind/U - GetTimeZoneInformation not supported on Solaris and on MAC

#if defined(_UNIX_) || defined(_MAC)
              DWORD dwRet = TIME_ZONE_ID_UNKNOWN;
#else
              DWORD dwRet = GetTimeZoneInformation(&tzi);
#endif
              switch (dwRet)
              {
              case TIME_ZONE_ID_UNKNOWN:
                break;
              case TIME_ZONE_ID_STANDARD:
                WideCharToMultiByte(CP_ACP, 0, tzi.StandardName, -1,
                  r, sizeof(buf), NULL, NULL);
                break;
              case TIME_ZONE_ID_DAYLIGHT:
                WideCharToMultiByte(CP_ACP, 0, tzi.DaylightName, -1,
                  r, sizeof(buf), NULL, NULL);
                break;
              }
            }

#else
            r = (t->tm_isdst && tzname[1][0])?tzname[1]:tzname[0];
#endif
            break;

          default:
            buf[0] = '%';     /* reconstruct the format */
            buf[1] = f[-1];
            buf[2] = '\0';
              if (buf[1] == 0)
                f--;        /* back up if at end of string */
          }
          while (*r)
          {
            if (p == q)
            {
                *q = '\0';
                return 0;
            }
            *p++ = *r++;
          }
      }
      else
      {
          if (p == q)
          {
            *q = '\0';
            return 0;
          }
          *p++ = f[-1];
      }
    }
    *p = '\0';
    return p - s;
}

static int BASED_CODE npow[5] = { 1, 10, 100, 1000, 10000 };

/**
 * static void strfmt(LPTSTR str, LPTSTR fmt);
 *
 * simple sprintf for strftime
 *
 * each format descriptor is of the form %n
 * where n goes from zero to four
 *
 * 0    -- string %s
 * 1..4 -- int %?.?d
 *
**/

static void AFX_CDECL strfmt(LPTSTR str, LPCTSTR fmt, ...)
{
    int ival, ilen;
    LPTSTR sval;
    va_list vp;

    va_start(vp, fmt);
    while (*fmt)
    {
      if (*fmt++ == '%')
      {
          ilen = *fmt++ - '0';
          if (ilen == 0)                /* zero means string arg */
          {
            sval = va_arg(vp, char*);
            while (*sval)
                *str++ = *sval++;
          }
          else                          /* always leading zeros */
          {
            ival = va_arg(vp, int);
            while (ilen)
            {
                ival %= npow[ilen--];
                *str++ = (char) ('0' + ival / npow[ilen]);
            }
          }
      }
      else  *str++ = fmt[-1];
    }
    *str = '\0';
    va_end(vp);
}

#endif // _MFC_VER >= 0x0300

//////////////////////////////////////////////////////////////////////
// Parsing date/time values

void AFXAPI GXUpdateDateTimeSettings()
{
  if (GXGetAppData()->m_pDateTimeImp)
    GXGetAppData()->m_pDateTimeImp->UpdateDateTimeSettings();
}

// public methods
GXDateFormat AFXAPI GXGetDateFormatFromWinIni(BOOL bReload, BOOL& bCentury, TCHAR& chDateSep)
{
  if (GXGetAppData()->m_pDateTimeImp)
    return GXGetAppData()->m_pDateTimeImp->GetDateFormatFromWinIni(bReload, bCentury, chDateSep);

  return gxDEFAULT;
}

TCHAR AFXAPI GXGetTimeSeparatorFromWinIni(BOOL bReload)
{
  if (GXGetAppData()->m_pDateTimeImp)
    return GXGetAppData()->m_pDateTimeImp->GetTimeSeparatorFromWinIni(bReload);

  return _T(':');
}

BOOL AFXAPI GXParseDateTime(struct tm* ptm, LPCTSTR szValue, GXDateFormat DateFormat)
{
  GX_CHECKIMP(GXGetAppData()->m_pDateTimeImp, "GXParseDateTime");

  if (GXGetAppData()->m_pDateTimeImp)
    return GXGetAppData()->m_pDateTimeImp->ParseDateTime(ptm, szValue, DateFormat);

  return FALSE;
}

BOOL AFXAPI GXParseDateTime(TIMESTAMP_STRUCT* ptm, LPCTSTR szValue, GXDateFormat DateFormat)
{
  GX_CHECKIMP(GXGetAppData()->m_pDateTimeImp, "GXParseDateTime");

  if (GXGetAppData()->m_pDateTimeImp)
    return GXGetAppData()->m_pDateTimeImp->ParseDateTime(ptm, szValue, DateFormat);

  return FALSE;
}

void AFXAPI GXFormatTimeStamp(CString& strRet, const CTime* pTime)
{
  GX_CHECKIMP(GXGetAppData()->m_pDateTimeImp, "GXFormatTimeStamp");

  if (GXGetAppData()->m_pDateTimeImp)
    GXGetAppData()->m_pDateTimeImp->FormatTimeStamp(strRet, pTime);
}

void AFXAPI GXFormatTimeStamp(CString& strRet, const TIMESTAMP_STRUCT* pTime)
{
  GX_CHECKIMP(GXGetAppData()->m_pDateTimeImp, "GXFormatTimeStamp");

  if (GXGetAppData()->m_pDateTimeImp)
    GXGetAppData()->m_pDateTimeImp->FormatTimeStamp(strRet, pTime);
}

/////////////////////////////////////////////////////////////////////////////
// Date/Time parsing and formatting (OG offers concrete classes for OleDateTime
// and NoOleDateTime)

enum GXDateFormat { gxDDMMYY, gxMMDDYY, gxYYMMDD, gxDEFAULT };
typedef struct tagTIMESTAMP_STRUCT TIMESTAMP_STRUCT;

class CGXAbstractDateTimeImp
{
public:
  virtual void UpdateDateTimeSettings() = 0;
  virtual GXDateFormat GetDateFormatFromWinIni(BOOL bReload, BOOL& bCentury, TCHAR& chDateSep) = 0;
  virtual TCHAR GetTimeSeparatorFromWinIni(BOOL bReload) = 0;
  virtual BOOL ParseDateTime(struct tm* ptm, LPCTSTR szValue, GXDateFormat DateFormat) = 0;
  virtual BOOL ParseDateTime(TIMESTAMP_STRUCT* ptm, LPCTSTR szValue, GXDateFormat DateFormat) = 0;
  virtual void FormatTimeStamp(CString& strRet, const CTime* pTime) = 0;
  virtual void FormatTimeStamp(CString& strRet, const TIMESTAMP_STRUCT* pTime) = 0;
};
// This is a part of the Objective Grid C++ Library.
// Copyright (C) 1995-1998 Stingray Software, Inc.
// All rights reserved.
//
// This source code is only intended as a supplement to
// the Objective Grid Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// the Objective Grid product.
//
// Author: Stefan Hoenig
//

// gxtime.cpp : date and time parsing and formatting 
//              (without using COleDateTime class)

#include "stdafx.h"

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

// Headers

#include <stddef.h>     /* for size_t */
#include <stdarg.h>     /* for va_arg */
#include <time.h>       /* for struct tm */
#include <ctype.h>

#ifndef _GXEXT_H_
#include "gxext.h"
#endif

#ifndef _GXDLL_H_
#include "gxdll.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXTIME")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


class CGXNoOleDateTimeImp: public CGXAbstractDateTimeImp
{
public:
  virtual void UpdateDateTimeSettings();
  virtual GXDateFormat GetDateFormatFromWinIni(BOOL bReload, BOOL& bCentury, TCHAR& chDateSep);
  virtual TCHAR GetTimeSeparatorFromWinIni(BOOL bReload);
  virtual BOOL ParseDateTime(struct tm* ptm, LPCTSTR szValue, GXDateFormat DateFormat);
  virtual BOOL ParseDateTime(TIMESTAMP_STRUCT* ptm, LPCTSTR szValue, GXDateFormat DateFormat);
  virtual void FormatTimeStamp(CString& strRet, const CTime* pTime);
  virtual void FormatTimeStamp(CString& strRet, const TIMESTAMP_STRUCT* pTime);
};

void AFXAPI GXImplementNoOleDateTime()
{
  if (GXGetAppData()->m_pDateTimeImp == NULL)
    GXGetAppData()->AutoDeletePtr(GXGetAppData()->m_pDateTimeImp = new CGXNoOleDateTimeImp);
}


// NOTE: This methods are provided because parsing
// date/time values was not possible with VC 1.5x
// and VC 2.x projects.
//
// If you are using VC 4.x or greater, we recommend
// using the COleDateTime::ParseDateTime for this
// purpose.

// helper methods:

static void AFXAPI StripLeadingBlanks(CString& sEdit);
static BOOL AFXAPI IsLeapYear(int Year);
static int AFXAPI GetEndMonth (int Month, int Year);
static int AFXAPI GetDD (CString& strDate);
static int AFXAPI GetYY (CString& strDate);
static int AFXAPI GetMM (CString& strDate);

// static data

//static int nMonthMax[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
static GXDateFormat s_dateFormat = gxDEFAULT;
static TCHAR s_chTimeSep = 0;
static BOOL s_bCentury = FALSE;
static TCHAR s_chDateSep = '/';

void CGXNoOleDateTimeImp::UpdateDateTimeSettings()
{
  BOOL bCentury;
  TCHAR chDateSep;
  GXGetDateFormatFromWinIni(TRUE, bCentury, chDateSep);
  GXGetTimeSeparatorFromWinIni(TRUE);
}

// public methods
GXDateFormat CGXNoOleDateTimeImp::GetDateFormatFromWinIni(BOOL bReload, BOOL& bCentury, TCHAR& chDateSep)
{
  // Note: In your application, you should process
  // the WM_WININICHANGE message and call
  // GXGetDateFormatFromWinIni(TRUE).

  if (s_dateFormat == gxDEFAULT  || bReload)
  {
    CString sDefault = _T("MM.dd.yy");
    CString sShortDate;
    LPTSTR pszBuffer = sShortDate.GetBuffer(128);
    bCentury = FALSE;
#if _MFC_VER >= 0x0300
    GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SSHORTDATE, pszBuffer, 128);
#else
    GetProfileString(_T("intl"), _T("sShortDate"), sDefault, pszBuffer, 128);
#endif
    sShortDate.ReleaseBuffer();


    s_dateFormat = gxMMDDYY;
    if (!sShortDate.IsEmpty())
    {
      sShortDate.MakeUpper();
      if (sShortDate[0] == _T('M'))
        s_dateFormat = gxMMDDYY;
      else if (sShortDate[0] == _T('D'))
        s_dateFormat = gxDDMMYY;
      else if (sShortDate[0] == _T('Y'))
        s_dateFormat = gxYYMMDD;

      // display century only when YYYY is found in sShortDate
      s_bCentury = sShortDate.Find(_T("YYYY")) != -1;

      for (LPCTSTR p = sShortDate; *p && _istalpha(*p) && *p != _T(' '); p++)
        NULL;

      s_chDateSep = *p;
    }
  }

  bCentury = s_bCentury;
  chDateSep = s_chDateSep;

  return s_dateFormat;
}

TCHAR CGXNoOleDateTimeImp::GetTimeSeparatorFromWinIni(BOOL bReload)
{
  // Note: In your application, you should process
  // the WM_WININICHANGE message and call
  // GXGetDateFormatFromWinIni(TRUE).

  if (s_chTimeSep == 0 || bReload)
  {
    CString sDefault = _T(":");
    CString sTime;
    LPTSTR pszBuffer = sTime.GetBuffer(128);
#if _MFC_VER >= 0x0300
    GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_STIME, pszBuffer, 128);
#else
    GetProfileString(_T("intl"), _T("sTime"), sDefault, pszBuffer, 128);
#endif
    sTime.ReleaseBuffer();

    if (sTime.IsEmpty())
      s_chTimeSep = _T(':');
    else
      s_chTimeSep = sTime[0];
  }

  return s_chTimeSep;
}

BOOL CGXNoOleDateTimeImp::ParseDateTime(struct tm* ptm, LPCTSTR szValue, GXDateFormat DateFormat)
{
  ASSERT(ptm);

  BOOL bValid = TRUE;

  // Split into time/date
  CString sSrc = szValue;
  CString sDate, sTime;

  // clear tm struct
  memset(ptm, 0, sizeof(struct tm));

  // find separators
  TCHAR chTimeSep = GXGetTimeSeparatorFromWinIni(FALSE);
  int nBlank = sSrc.Find(_T(' '));
  int nColon = sSrc.Find(chTimeSep);

  if (nBlank != -1 && nColon > nBlank)
  {
    // Parse date and time
    // Input format: "date hh:mm[:ss]"
    sTime = sSrc.Mid(nBlank+1);
    sDate = sSrc.Left(nBlank);
  }
  else if (nColon != -1)
  {
    // Parse only time
    // Input format: "hh:mm[:ss]"
    sTime = sSrc;
  }
  else
  {
    // Parse only date
    // Input format: "date"
    sDate = sSrc;
  }

  StripLeadingBlanks(sTime);
  StripLeadingBlanks(sDate);

  // Parse time string
  if (!sTime.IsEmpty())
  {
    ptm->tm_year = 70;
    ptm->tm_mon = 0;
    ptm->tm_mday = 1;

    int nColon1 = sTime.Find(chTimeSep);

    // hour
    if (bValid)
    {
      // must use "PM" to make the code to work with both military or AM/PM format
      if ((sTime.Right(2)).CompareNoCase(_T("PM")) == 0 || (sTime.Right(1)).CompareNoCase(_T("P")) == 0)
      {
        ptm->tm_hour = _ttoi(sTime.Left(nColon1)) + 12;
        if (ptm->tm_hour == 24)  // 12:mm PM 
          ptm->tm_hour = 12;
      }
      else
      {
        ptm->tm_hour = _ttoi(sTime.Left(nColon1));
        if ((sTime.Right(2)).CompareNoCase(_T("AM")) == 0 || (sTime.Right(1)).CompareNoCase(_T("A")) == 0)
        {
          bValid &= ptm->tm_hour <= 12;
          if (ptm->tm_hour == 12)  // 12:mm AM
            ptm->tm_hour = 0;
        }
      }

      bValid &= ptm->tm_hour >= 0 && ptm->tm_hour <= 24;
    }

    // minute
    if (bValid && !sTime.IsEmpty())
    {
      sTime = sTime.Mid(nColon1 + 1);
      ptm->tm_min = _ttoi(sTime.Left(2));
      bValid &= ptm->tm_min >= 0 && ptm->tm_min < 60;
    }

    // second
    if (bValid && !sTime.IsEmpty())
    {
      sTime = sTime.Mid(3);
      ptm->tm_sec = _ttoi(sTime.Left(2));
      bValid &= ptm->tm_sec >= 0 && ptm->tm_sec < 60;
    }
  }

  // Parse date string
  if (!sDate.IsEmpty())
  {
    if (sDate != sDate.SpanIncluding(_T("0123456789/-. ")))
    {
      // TRACE0("Invalid character in date\n");
      bValid = FALSE;
    }

    if ( sDate.GetLength() == 6 )
    {
      if (isdigit(sDate[0]) && isdigit(sDate[1]) && isdigit(sDate[2])
        && isdigit(sDate[3]) && isdigit(sDate[4]) && isdigit(sDate[5]))
        sDate = sDate.Left(2)+_T('/')+sDate.Mid(2,2)+_T('/')+sDate.Right(2);
    }

    BOOL bCentury;

    TCHAR chDateSep;
    if (DateFormat == gxDEFAULT)
      DateFormat = GXGetDateFormatFromWinIni(FALSE, bCentury, chDateSep);

    if (DateFormat == gxDDMMYY)
    {
      bValid = bValid && (ptm->tm_mday = GetDD(sDate)) != -1;
      bValid = bValid && (ptm->tm_mon  = GetMM(sDate)) != -1;
      bValid = bValid && (ptm->tm_year = GetYY(sDate)) != -1;
      bValid = bValid && (ptm->tm_mday <= GetEndMonth(ptm->tm_mon, ptm->tm_year));
    }
    else if (DateFormat == gxMMDDYY)
    {
      bValid = bValid && (ptm->tm_mon  = GetMM(sDate)) != -1;
      bValid = bValid && (ptm->tm_mday = GetDD(sDate)) != -1;
      bValid = bValid && (ptm->tm_year = GetYY(sDate)) != -1;
      bValid = bValid && (ptm->tm_mday <= GetEndMonth(ptm->tm_mon, ptm->tm_year));
    }
    else if (DateFormat == gxYYMMDD)
    {
      bValid = bValid && (ptm->tm_year = GetYY(sDate)) != -1;
      bValid = bValid && (ptm->tm_mon  = GetMM(sDate)) != -1;
      bValid = bValid && (ptm->tm_mday = GetDD(sDate)) != -1;
      bValid = bValid && (ptm->tm_mday <= GetEndMonth(ptm->tm_mon, ptm->tm_year));
    }
    else
    {
      bValid = FALSE;
      ASSERT(0);
      // ASSERTION-> DateFormat is invalid ->END
    }

    if (bValid)
    {
      // make month zero-based
      ptm->tm_mon--;

      // adjust year (time_t only allows from 1970 to 2037)
      if (ptm->tm_year >= 1900)
        ptm->tm_year -= 1900;
      else if (ptm->tm_year <= 37) // year 2000-2037
        ptm->tm_year += 100;
    }
  }

  return bValid;
}

BOOL CGXNoOleDateTimeImp::ParseDateTime(TIMESTAMP_STRUCT* ptm, LPCTSTR szValue, GXDateFormat DateFormat)
{
  ASSERT(ptm);

  BOOL bValid = TRUE;

  // Split into time/date
  CString sSrc = szValue;
  CString sDate, sTime;

  // clear tm struct
  memset(ptm, 0, sizeof(TIMESTAMP_STRUCT));

  // find separators
  TCHAR chTimeSep = GXGetTimeSeparatorFromWinIni(FALSE);
  int nBlank = sSrc.Find(_T(' '));
  int nColon = sSrc.Find(chTimeSep);

  if (nBlank != -1 && nColon > nBlank)
  {
    // Parse date and time
    // Input format: "date hh:mm[:ss]"
    sTime = sSrc.Mid(nBlank+1);
    sDate = sSrc.Left(nBlank);
  }
  else if (nColon != -1)
  {
    // Parse only time
    // Input format: "hh:mm[:ss]"
    sTime = sSrc;
  }
  else
  {
    // Parse only date
    // Input format: "date"
    sDate = sSrc;
  }

  StripLeadingBlanks(sTime);
  StripLeadingBlanks(sDate);

  // Parse time string
  if (!sTime.IsEmpty())
  {
    ptm->year = 70;
    ptm->month = 0;
    ptm->day = 1;

    int nColon1 = sTime.Find(chTimeSep);

    // hour
    if (bValid)
    {
      // must use "PM" to make the code to work with both military or AM/PM format
      if ((sTime.Right(2)).CompareNoCase(_T("PM")) == 0 || (sTime.Right(1)).CompareNoCase(_T("P")) == 0)
      {
        ptm->hour = (UWORD) (_ttoi(sTime.Left(nColon1)) + 12);
        if (ptm->hour == 24)  // 12:mm PM 
          ptm->hour = 12;
      }
      else
      {
        ptm->hour = (UWORD) _ttoi(sTime.Left(nColon1));
        if ((sTime.Right(2)).CompareNoCase(_T("AM")) == 0 || (sTime.Right(1)).CompareNoCase(_T("A")) == 0)
        {
          bValid &= ptm->hour <= 12;
          if (ptm->hour == 12)  // 12:mm AM
            ptm->hour = 0;
        }
      }

      bValid &= ptm->hour >= 0 && ptm->hour <= 24;
    }

    // minute
    if (bValid && !sTime.IsEmpty())
    {
      sTime = sTime.Mid(nColon1 + 1);
      ptm->minute = (UWORD) _ttoi(sTime.Left(2));
      bValid &= ptm->minute >= 0 && ptm->minute < 60;
    }

    // secondond
    if (bValid && !sTime.IsEmpty())
    {
      sTime = sTime.Mid(3);
      ptm->second = (UWORD) _ttoi(sTime.Left(2));
      bValid &= ptm->second >= 0 && ptm->second < 60;
    }
  }

  // Parse date string
  if (!sDate.IsEmpty())
  {
    if (sDate != sDate.SpanIncluding(_T("0123456789/-. ")))
    {
      // TRACE0("Invalid character in date\n");
      bValid = FALSE;
    }

    if( sDate.GetLength() == 6 )
      if (isdigit(sDate[0]) && isdigit(sDate[1]) && isdigit(sDate[2])
        && isdigit(sDate[3]) && isdigit(sDate[4]) && isdigit(sDate[5]))
        sDate = sDate.Left(2)+_T('/')+sDate.Mid(2,2)+_T('/')+sDate.Right(2);

    BOOL bCentury;

    TCHAR chDateSep;
    if (DateFormat == gxDEFAULT)
      DateFormat = GXGetDateFormatFromWinIni(FALSE, bCentury, chDateSep);

    if (DateFormat == gxDDMMYY)
    {
      bValid = bValid && (ptm->day = (UWORD) GetDD(sDate)) != (UWORD) -1;
      bValid = bValid && (ptm->month  = (UWORD) GetMM(sDate)) != (UWORD) -1;
      bValid = bValid && (ptm->year = (SWORD) GetYY(sDate)) != (SWORD) -1;
      bValid = bValid && (ptm->day <= (UWORD) GetEndMonth(ptm->month, ptm->year));
    }
    else if (DateFormat == gxMMDDYY)
    {
      bValid = bValid && (ptm->month  = (UWORD) GetMM(sDate)) != (UWORD) -1;
      bValid = bValid && (ptm->day = (UWORD) GetDD(sDate)) != (UWORD) -1;
      bValid = bValid && (ptm->year = (SWORD) GetYY(sDate)) != (SWORD) -1;
      bValid = bValid && (ptm->day <= (UWORD) GetEndMonth(ptm->month, ptm->year));
    }
    else if (DateFormat == gxYYMMDD)
    {
      bValid = bValid && (ptm->year = (SWORD) GetYY(sDate)) != (SWORD) -1;
      bValid = bValid && (ptm->month  = (UWORD) GetMM(sDate)) != (UWORD) -1;
      bValid = bValid && (ptm->day = (UWORD) GetDD(sDate)) != (UWORD) -1;
      bValid = bValid && (ptm->day <= (UWORD) GetEndMonth(ptm->month, ptm->year));
    }
    else
    {
      bValid = FALSE;
      ASSERT(0);
      // ASSERTION-> DateFormat is invalid ->END
    }
  }

  return bValid;
}

void CGXNoOleDateTimeImp::FormatTimeStamp(CString& strRet, const CTime* pTime)
{
  BOOL bTime =
    pTime->GetHour()
    || pTime->GetMinute()
    || pTime->GetSecond();
  BOOL bDate =
    pTime->GetMonth() > 0;

#if _MFC_VER >= 0x0300
  // can use CTime::Format member
  if (bTime && bDate)
    strRet = pTime->Format(_T("%c"));
  else if (bTime)
    strRet = pTime->Format(_T("%X"));
  else
    strRet = pTime->Format(_T("%x"));
#else
  // need to use my own Format method
  TCHAR szBuffer[64];
  struct tm* ptmTemp = pTime->GetLocalTm( NULL );
  ASSERT(ptmTemp != NULL); // make sure the time has been initialized!

  LPTSTR pFormat;

  if (bTime && bDate)
    pFormat = _T("%c");
  else if (bTime)
    pFormat = _T("%X");
  else
    pFormat = _T("%x");

  if (!GXIntlStrFtime(GXGetResourceHandle( ), GX_IDS_TIME_ADAY1,
    szBuffer, sizeof(szBuffer), pFormat, ptmTemp))
  szBuffer[0] = '\0';

  strRet = szBuffer;
#endif
}

void CGXNoOleDateTimeImp::FormatTimeStamp(CString& strRet, const TIMESTAMP_STRUCT* pTime)
{
  BOOL bTime =
    pTime->hour
    || pTime->minute
    || pTime->second;
  BOOL bDate =
    pTime->month > 0;

  // need to use my own Format method

  BOOL bCentury;
  TCHAR chDateSep;
  GXDateFormat DateFormat = GXGetDateFormatFromWinIni(FALSE, bCentury, chDateSep);
  TCHAR chSep = GXGetTimeSeparatorFromWinIni();

  CString sDate;
  CString sTime;

  if (bDate)
  {
    LPTSTR pszBuf = sDate.GetBuffer(128);

    if (bCentury)
    {
      // display 4-digit year
      if (DateFormat == gxDDMMYY)
        wsprintf(pszBuf, _T("%02d%c%02d%c%04d"),
          pTime->day, chDateSep, pTime->month, chDateSep, pTime->year);
      else if (DateFormat == gxMMDDYY)
        wsprintf(pszBuf, _T("%02d%c%02d%c%04d"),
          pTime->month, chDateSep, pTime->day, chDateSep, pTime->year);
      else if (DateFormat == gxYYMMDD)
        wsprintf(pszBuf, _T("%04d%c%02d%c%02d"),
          pTime->year, chDateSep, pTime->month, chDateSep, pTime->day);
    }
    else
    {
      // display 2-digit year
      if (DateFormat == gxDDMMYY)
        wsprintf(pszBuf, _T("%02d%c%02d%c%02d"),
          pTime->day, chDateSep, pTime->month, chDateSep, pTime->year%100);
      else if (DateFormat == gxMMDDYY)
        wsprintf(pszBuf, _T("%02d%c%02d%c%02d"),
          pTime->month, chDateSep, pTime->day, chDateSep, pTime->year%100);
      else if (DateFormat == gxYYMMDD)
        wsprintf(pszBuf, _T("%02d%c%02d%c%02d"),
          pTime->year%100, chDateSep, pTime->month, chDateSep, pTime->day);
    }
    sDate.ReleaseBuffer();
  }

  if (bTime)
  {
    LPTSTR pszBuf = sTime.GetBuffer(128);

    wsprintf(pszBuf, _T("%02d%c%02d%c%02d"),
      pTime->hour, chSep, pTime->minute, chSep, pTime->second);

    sTime.ReleaseBuffer();
  }

  strRet = sDate;
  if (bDate && bTime)
    strRet += _T(" ");
  if (bTime)
    strRet +=sTime;
}

////////////////////////////////////////////////////////////////////////
// Implemenation

static void AFXAPI StripLeadingBlanks(CString& sEdit)
{
  // find first non-space character
  LPCTSTR lpsz = sEdit;
  int n = 0;
  while (*lpsz == _T(' '))
  {
    lpsz = _tcsinc(lpsz);
    n++;
  }

  // fix up data
  if (n > 0)
    sEdit = sEdit.Mid(n);
}

static BOOL AFXAPI IsLeapYear(int nYear)
{
  return (((nYear % 4 == 0) && (nYear % 100 != 0)) || (nYear % 400 == 0));
}

// GetEndMonth
//
// Determines the number of days in the month

static int AFXAPI GetEndMonth (int nMonth, int nYear)
{
  ASSERT (nMonth >= 1);
  ASSERT (nMonth <= 12);

  int nLastDay = nMonthMax [nMonth-1];

  if (nMonth == 2)         // check for leap year
    if (IsLeapYear (nYear))
      nLastDay++;

  return nLastDay;
}

// GetDD
//
// Strips the leading two numbers from the string passed as
// an argument and returns them.  Also returns the string
// that was passed minus the two numbers.

static int AFXAPI GetDD (CString& strDate)
{
  // Get DD nDay Value
  if (strDate.GetLength())
  {
    StripLeadingBlanks(strDate);

    if(!isdigit(strDate[0]))
      strDate = strDate.Mid(1);

    for (int nChars = 0; nChars < strDate.GetLength() && isdigit(strDate[nChars]); nChars++)
      NULL;

    if (nChars == 0 || nChars > 2)          // string is bad
      return -1;

    int nDay = _ttoi(strDate);

    if (nDay > 31  || nDay < 1)
    {
      TRACE0("nDay must be between 1 and 31");
      return -1;
    }

    strDate = strDate.Mid(nChars);      // strip off the DD value

    return nDay;
  }
  else
    return -1;
}

// GetYY
//
// Strips the first two numbers from a string passed
// as an argument and returns them as the year.  Also
// returns the string minus the two numbers.

static int AFXAPI GetYY (CString& strDate)
{
  // Get YY Value
  if (strDate.GetLength())
  {
    StripLeadingBlanks(strDate);

    if(!isdigit(strDate[0]))
      strDate = strDate.Mid(1);

    for (int nChars = 0; nChars < strDate.GetLength() && isdigit(strDate[nChars]); nChars++)
      NULL;

    if (nChars == 0 || nChars > 4)          // string is bad
      return -1;

    int nYear = _ttoi(strDate);

    if (nChars <= 2)
    {
      // if only 2 digits, make it the current century
      // (when this tool were written).
      if (nYear > 0 && nYear < 100)
        nYear += 1900;

      // User can input years from 0 to 100 by typing in
      // a "0" before the year, e.g. 01.01.0060 or 01.01.060
      // but if he enters 01.01.60, the year will become
      // 01.01.1960.
    }

    strDate = strDate.Mid(nChars);      // strip off the YY value

    return nYear;
  }
  else
    return -1;
}

// GetMM
//
// Strips the leading two numbers from the string passed as
// an argument and returns the month.  Also returns the string
// that was passed minus the two numbers.

static int AFXAPI GetMM (CString& strDate)
{
  // Get MM Value
  if (strDate.GetLength())
  {
    StripLeadingBlanks(strDate);

    if(!isdigit(strDate[0]))
      strDate = strDate.Mid(1);

    for (int nChars = 0; nChars < strDate.GetLength() && isdigit(strDate[nChars]); nChars++)
      NULL;

    if (nChars == 0 || nChars > 2)          // string is bad
      return -1;

    int nMonth = _ttoi(strDate);

    if ((nMonth == 0) || (nMonth > 12))
    {
      TRACE0("Month must be between 1 and 12");
      return -1;
    }

    strDate = strDate.Mid(nChars);      // strip off the MM value

    return nMonth;
  }
  else
    return -1;
}

// This is a part of the Objective Grid C++ Library.
// Copyright (C) 1995-1998 Stingray Software, Inc.
// All rights reserved.
//
// This source code is only intended as a supplement to
// the Objective Grid Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// the Objective Grid product.
//
// Author: Stefan Hoenig
//

// gxtime2.cpp : Date and Time parsing using the COleDateTime class
//

#include "stdafx.h"

#if _MFC_VER >= 0x0400 

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

// Headers

#include <stddef.h>     /* for size_t */
#include <stdarg.h>     /* for va_arg */
#include <time.h>       /* for struct tm */
#include <ctype.h>

#ifndef _GXEXT_H_
#include "gxext.h"
#endif

#ifndef _GXDLL_H_
#include "gxdll.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXTIME")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

class CGXOleDateTimeImp: public CGXAbstractDateTimeImp
{
public:
  virtual void UpdateDateTimeSettings();
  virtual GXDateFormat GetDateFormatFromWinIni(BOOL bReload, BOOL& bCentury, TCHAR& chDateSep);
  virtual TCHAR GetTimeSeparatorFromWinIni(BOOL bReload);
  virtual BOOL ParseDateTime(struct tm* ptm, LPCTSTR szValue, GXDateFormat DateFormat);
  virtual BOOL ParseDateTime(TIMESTAMP_STRUCT* ptm, LPCTSTR szValue, GXDateFormat DateFormat);
  virtual void FormatTimeStamp(CString& strRet, const CTime* pTime);
  virtual void FormatTimeStamp(CString& strRet, const TIMESTAMP_STRUCT* pTime);
};

void AFXAPI GXImplementOleDateTime()
{
  if (GXGetAppData()->m_pDateTimeImp == NULL)
    GXGetAppData()->AutoDeletePtr(GXGetAppData()->m_pDateTimeImp = new CGXOleDateTimeImp);
}

// public methods
void CGXOleDateTimeImp::UpdateDateTimeSettings()
{
}

GXDateFormat CGXOleDateTimeImp::GetDateFormatFromWinIni(BOOL bReload, BOOL& bCentury, TCHAR& chDateSep)
{
  GX_UNUSED_ALWAYS(bReload);
  GX_UNUSED_ALWAYS(bCentury);
  GX_UNUSED_ALWAYS(chDateSep);

  return gxDEFAULT;
}

TCHAR CGXOleDateTimeImp::GetTimeSeparatorFromWinIni(BOOL bReload)
{
  GX_UNUSED_ALWAYS(bReload);

  return 0;
}

BOOL CGXOleDateTimeImp::ParseDateTime(struct tm* ptm, LPCTSTR szValue, GXDateFormat DateFormat)
{
  GX_UNUSED_ALWAYS(DateFormat);

  // can use COleDateTime for parsing
  COleDateTime date;

  memset(ptm, 0, sizeof(struct tm));

  if (date.ParseDateTime(szValue))
  {
    ptm->tm_year = date.GetYear()-1900; // tm_year is 1900 based
    ptm->tm_mon = date.GetMonth()-1;    // month is zero-based
    ptm->tm_mday = date.GetDay();
    ptm->tm_hour = date.GetHour();
    ptm->tm_min = date.GetMinute();
    ptm->tm_sec = date.GetSecond();

    return TRUE;
  }

  return FALSE;
}

BOOL CGXOleDateTimeImp::ParseDateTime(TIMESTAMP_STRUCT* ptm, LPCTSTR szValue, GXDateFormat DateFormat)
{
  GX_UNUSED_ALWAYS(DateFormat);

  // can use COleDateTime for parsing
  COleDateTime date;

  memset(ptm, 0, sizeof(TIMESTAMP_STRUCT));

  if (date.ParseDateTime(szValue))
  {
    ptm->year = (SWORD) date.GetYear();
    ptm->month = (UWORD) date.GetMonth();
    ptm->day = (UWORD) date.GetDay();
    ptm->hour = (UWORD) date.GetHour();
    ptm->minute = (UWORD) date.GetMinute();
    ptm->second = (UWORD) date.GetSecond();

    return TRUE;
  }

  return FALSE;
}

void CGXOleDateTimeImp::FormatTimeStamp(CString& strRet, const CTime* pTime)
{
  COleDateTime date;

  BOOL bTime =
    pTime->GetHour()
    || pTime->GetMinute()
    || pTime->GetSecond();
  BOOL bDate =
    pTime->GetMonth() > 0;

#if _MFC_VER >= 0x0300
  // can use CTime::Format member
  if (bTime && bDate)
    strRet = pTime->Format(_T("%c"));
  else if (bTime)
    strRet = pTime->Format(_T("%X"));
  else
    strRet = pTime->Format(_T("%x"));
#else
  // need to use my own Format method
  TCHAR szBuffer[64];
  struct tm* ptmTemp = pTime->GetLocalTm( NULL );
  ASSERT(ptmTemp != NULL); // make sure the time has been initialized!

  LPTSTR pFormat;

  if (bTime && bDate)
    pFormat = _T("%c");
  else if (bTime)
    pFormat = _T("%X");
  else
    pFormat = _T("%x");

  if (!GXIntlStrFtime(GXGetResourceHandle( ), GX_IDS_TIME_ADAY1,
    szBuffer, sizeof(szBuffer), pFormat, ptmTemp))
  szBuffer[0] = '\0';

  strRet = szBuffer;
#endif
}

void CGXOleDateTimeImp::FormatTimeStamp(CString& strRet, const TIMESTAMP_STRUCT* pTime)
{
  BOOL bTime =
    pTime->hour
    || pTime->minute
    || pTime->second;
  BOOL bDate =
    pTime->month > 0;

  // can use COleDateTime formatting

  LPTSTR pFormat;

  if (bTime && bDate)
    pFormat = _T("%c");
  else if (bTime)
    pFormat = _T("%X");
  else
    pFormat = _T("%x");

  // Can use COleDateTime formatting
  COleDateTime date(
    pTime->year, pTime->month, pTime->day,
    pTime->hour, pTime->minute, pTime->second);

  strRet = date.Format(pFormat);
}


#endif // _MFC_VER 
#endif
#endif //0 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#if 0  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ----------------------------------------------------------- //
// C++ Header File Name: cdate.h 
// C++ Compiler Used: Microsoft visual C/C++ version 4.0 
// Produced By: Doug Gaer   
// File Creation Date: 09/21/1997 
// Date Last Modified: 03/15/1999
// ----------------------------------------------------------- // 
// ---------- Include File Description and Details  ---------- // 
// ----------------------------------------------------------- // 
/*
The CDate class is used turn a date string into into concrete
data type.
*/
// ----------------------------------------------------------- //   
/*#ifndef __CDATE_HPP
#define __CDATE_HPP

// Define this macro to use the CPP iostream
// #ifndef __USE_CPP_IOSTREAM__
// #define __USE_CPP_IOSTREAM__
// #endif

#include <iostream.h>
#include "dtypes.h"
#include "uint16.h"

// (C)oncrete (D)ate class
class CDate
{
public:
  CDate() { }
  CDate(__UBYTE__ month, __UBYTE__ day, UINT16 year) {
    Month = month, Day = day, Year = year;
  }
  CDate(const CDate& ob);
  CDate& operator=(const CDate& ob);
  
public:
  void SetDay(__UBYTE__ byte) { Day = byte; }
  void SetMonth(__UBYTE__ byte) { Month = byte; }
  void SetYear(UINT16 uint16) { Year = uint16; }
  void SetDate(__UBYTE__ month, __UBYTE__ day, UINT16 year) {
    Month = month, Day = day, Year = year;
  
  __UBYTE__ GetDay() { return Day; }
  __UBYTE__ GetMonth() { return Month; }
  UINT16 GetYear() { return Year; }
  char *c_str();
  const char *c_str() const;
  char *month_c_str();
  const char *month_c_str() const;
  char *day_c_str();
  const char *day_c_str() const;
  char *year_c_str();
  const char *year_c_str() const;
  unsigned SizeOf() { return sizeof(Month)+sizeof(Day)+sizeof(Year); }
  
public: // Overloaded operators
  friend int operator==(const CDate &a, const CDate &b);
  friend int operator!=(const CDate &a, const CDate &b);
  friend int operator<(const CDate &a, const CDate &b);
  
public:
#ifdef __USE_CPP_IOSTREAM__
  friend ostream &operator<<(ostream &os, const CDate &ob);
  friend void operator>>(istream &is, CDate &ob);
#endif
  
private:
  __UBYTE__ Month;
  __UBYTE__ Day;
  UINT16 Year;
};

#endif  // __CDATE_HPP
*/
  // ----------------------------------------------------------- // 
// C++ Source Code File Name: cdate.cpp 
// C++ Compiler Used: Microsoft visual C/C++ version 4.0 
// Produced By: Doug Gaer   
// File Creation Date: 09/21/1997 
// Date Last Modified: 03/15/1999
// ----------------------------------------------------------- // 
// ------------- Program Description and Details ------------- // 
// ----------------------------------------------------------- // 
/*
The CDate class is used turn a date string into into concrete
data type.
*/
// ----------------------------------------------------------- // 
/*#include "string.h"
#include "stdio.h"
#include "cdate.h"

// String lenght for date strings
const int MaxStrLen = 25;

CDate::CDate(const CDate& ob)
{
  Month = ob.Month;
  Day = ob.Day;
  Year = ob.Year;
}

CDate& CDate::operator=(const CDate& ob)
{
  Month = ob.Month;
  Day = ob.Day;
  Year = ob.Year;
  return *this;
}

char *CDate::c_str()
// Returns null terminated date string
{
  const int MaxStrLen = 25;
  char date_str[MaxStrLen];
  sprintf(date_str, "%u/%u/%u", (unsigned)Month,(unsigned)Day,(unsigned)Year);
  int len = strlen(date_str);
  char *buf = new char[len];
  buf[len] = '\0';
  memmove(buf, date_str, len);
  return buf;
}

const char *CDate::c_str() const
// Returns null terminated date string
{
  const int MaxStrLen = 25;
  char date_str[MaxStrLen];
  sprintf(date_str, "%u/%u/%u", (unsigned)Month,(unsigned)Day,(unsigned)Year);
  int len = strlen(date_str);
  char *buf = new char[len];
  buf[len] = '\0';
  memmove(buf, date_str, len);
  return buf;
}

char *CDate::month_c_str()
// Returns null terminated date string
{
  char date_str[MaxStrLen];
  sprintf(date_str, "%u", (unsigned)Month);
  int len = strlen(date_str);
  char *buf = new char[len];
  buf[len] = '\0';
  memmove(buf, date_str, len);
  return buf;
}

const char *CDate::month_c_str() const
// Returns null terminated date string
{
  char date_str[MaxStrLen];
  sprintf(date_str, "%u", (unsigned)Month);
  int len = strlen(date_str);
  char *buf = new char[len];
  buf[len] = '\0';
  memmove(buf, date_str, len);
  return buf;
}

char *CDate::day_c_str()
// Returns null terminated date string
{
  char date_str[MaxStrLen];
  sprintf(date_str, "%u", (unsigned)Day);
  int len = strlen(date_str);
  char *buf = new char[len];
  buf[len] = '\0';
  memmove(buf, date_str, len);
  return buf;
}

const char *CDate::day_c_str() const
// Returns null terminated date string
{
  char date_str[MaxStrLen];
  sprintf(date_str, "%u", (unsigned)Day);
  int len = strlen(date_str);
  char *buf = new char[len];
  buf[len] = '\0';
  memmove(buf, date_str, len);
  return buf;
}

char *CDate::year_c_str()
// Returns null terminated date string
{
  char date_str[MaxStrLen];
  sprintf(date_str, "%u", (unsigned)Year);
  int len = strlen(date_str);
  char *buf = new char[len];
  buf[len] = '\0';
  memmove(buf, date_str, len);
  return buf;
}

const char *CDate::year_c_str() const
// Returns null terminated date string
{
  char date_str[MaxStrLen];
  sprintf(date_str, "%u", (unsigned)Year);
  int len = strlen(date_str);
  char *buf = new char[len];
  buf[len] = '\0';
  memmove(buf, date_str, len);
  return buf;
}

#ifdef __USE_CPP_IOSTREAM__
ostream &operator<<(ostream &os, const CDate &ob)
{
  os << (unsigned)ob.Month << "/"
     << (unsigned)ob.Day << "/"
     << ob.Year;
  return os;
}

void operator>>(istream &is, CDate &ob)
{
  unsigned  buf;

  cout << "Month (XX):  ";
  is >> buf;
  ob.SetMonth((__UBYTE__)buf);

  cout << "Day (XX):    ";
  is >> buf;
  ob.SetDay((__UBYTE__)buf);

  cout << "Year (XXXX): ";
  is >> buf;
  ob.SetYear(buf);
}
#endif // __USE_CPP_IOSTREAM__

int operator==(const CDate &a, const CDate &b)
{
  if(a.Year == b.Year) return 1;
  if(a.Year == b.Year && a.Month == b.Month) return 1;
  if(a.Year == b.Year && a.Month == b.Month && a.Day == b.Day) return 1;
  if(a.Month == b.Month) return 1;
  if(a.Month == b.Month && a.Day == b.Day) return 1;
  if(a.Day == b.Day) return 1;
  return 0;
}

int operator!=(const CDate &a, const CDate &b)
{
  if(a.Year != b.Year) return 1;
  if(a.Year != b.Year && a.Month != b.Month) return 1;
  if(a.Year != b.Year && a.Month != b.Month && a.Day != b.Day) return 1;
  if(a.Month != b.Month) return 1;
  if(a.Month != b.Month && a.Day != b.Day) return 1;
  if(a.Day != b.Day) return 1;
  return 0;
}

int operator<(const CDate &a, const CDate &b)
{
  if(a.Year < b.Year) return 1;
  if(a.Year == b.Year) {
    if(a.Month < b.Month) {
      return 1;
    }
    if(a.Month == b.Month) {
      if(a.Day < b.Day) return 1;
    }
  }
  
  return 0;
}
*/
// ----------------------------------------------------------- //
// ------------------------------- //
// --------- End of File --------- //
// ------------------------------- //

#endif //0 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//------------------------------------------------------------------------------
