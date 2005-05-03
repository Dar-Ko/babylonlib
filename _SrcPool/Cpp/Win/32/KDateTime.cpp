/*$Workfile: KDateTime.cpp$: implementation file
  $Revision: 7$ $Date: 2004-10-08 12:35:47$
  $Author: Darko$

  Defines the class behavior.
  Copyright: CommonSoft Inc.
  2003-09-26 Darko Kolakovic
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

/*Replaces library header file names with the compiler's aliases*/
#ifdef _USE_STD_HEADERS
  #ifdef _WIN32
    #ifdef _MSC_VER //Micorsoft Visual Studio C++ compiler
      #ifdef _UNICODE
        #ifndef UNICODE
          //To enable Unicode for some Microsoft Visual C/C++ header files,
          //the UNICODE definition is required
          #define UNICODE
        #endif
      #endif
      #include <wtypes.h> //LPCTSTR struct
      #pragma include_alias("KTChar.h", "tchar.h")
      //#pragma include_alias("KTypedef.h", "stdint.h")
      //#pragma include_alias("KTrace.h",   "trace.h")
    #endif  //_MSC_VER
  #endif  //_WIN32
#endif  //_USE_STD_HEADERS

#include "KTChar.h"
#ifndef __wtypes_h__
  #include <wtypes.h> //SYSTEMTIME struct
#endif
  //Disable warning C4127: conditional expression in ASSERT is constant
#pragma warning (disable: 4127)
#ifndef ASSERT
  #include "KTrace.h"
#endif

//#include "KTime16.h"  //FILETIMEDOS typedef
#include "KDateTime.h"  //CDateTime class


  //Include OLE library containing SystemTimeToVariantTime()
#pragma comment( lib, "Oleaut32" )

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#else
    //Used in <atlconv.h>, MSVC 6.0
  #ifndef _ASSERTE
    #define _ASSERTE(expr)
  #endif
#endif

///////////////////////////////////////////////////////////////////////////////
// CDateTime class
/*Minimum values of DATE is 0100-01-01T00:00:00
  */
const int CDateTime::DATE_MIN = -657434L;
/*Maximum values of DATE is 9999-12-31T23:59:59
  */
const int CDateTime::DATE_MAX = 2958465L;
/*Maximum values of DATE is 9999-12-31T23:59:59
  */
const int CDateTime::DATE_ERROR = INT_MAX;//CDateTime::DATE_MAX;

//-----------------------------------------------------------------------------
/*converts date and time to a system time.

        typedef struct _SYSTEMTIME 
          {
          WORD wYear;     //year (1601, 30827] WinXP
          WORD wMonth;    //month [1, 12] January = 1
          WORD wDayOfWeek;//day of the week [0, 6] Sunday = 0
          WORD wDay;      //day of the month [1. 31]
          WORD wHour;     //hours after 00:00:00     [h][0, 23]
          WORD wMinute;   //minutes after the hour   [min][0, 59]
          WORD wSecond;   //seconds after the minute [s][0, 61]
          WORD wMilliseconds; //milliseconds after the second [ms][0, 999]
          } SYSTEMTIME, *PSYSTEMTIME;

 */
CDateTime::operator SYSTEMTIME() const
{
SYSTEMTIME  stResult;
::VariantTimeToSystemTime((real64)m_dateValue, &stResult);
return stResult;
}

//-----------------------------------------------------------------------------
/*Converts date and time to a calendar value. time_t represents number of 
  seconds elapsed since 1970-01-01T00:00:00Z (UTC).

  Valid range is [1970-01-01T00:00:00Z, 2038-01-18T19:14:07Z] (UTC).

  Returns: the specified calendar time encoded as a value of type time_t or -1
  if time is out of range.
 */
inline CDateTime::operator time_t () const
{
tm tmResult;
SYSTEMTIME  stTemp;
if(::VariantTimeToSystemTime((real64)m_dateValue, &stTemp) != 0)
  {
  tmResult.tm_sec   = stTemp.wSecond;     //seconds after the minute [0, 61]
  tmResult.tm_min   = stTemp.wMinute;     //minutes after the hour   [0, 59]
  tmResult.tm_hour  = stTemp.wHour;       //hours after 00:00:00     [0, 23]
  tmResult.tm_mday  = stTemp.wDay;        //day of the month         [1, 31]
  tmResult.tm_mon   = stTemp.wMonth - 1;  //month of the year        [0, 11] 
  tmResult.tm_year  = stTemp.wYear - YEAR_EPOCH_TM;//years since 1900 
  tmResult.tm_wday  = stTemp.wDayOfWeek;  //day of the week          [0,  6] 
                                          //Sunday = 0
  tmResult.tm_isdst = -1; //Daylight saving time is unknown
  return mktime(&tmResult); //Convert the incomplete time to a normalized
                           //calendar value.
  }
return -1;
}

#ifdef _USE_TIME_64
/*Converts date and time to a calendar value.__time64_t represents number of 
  seconds elapsed since 1970-01-01T00:00:00Z (UTC).

  Valid range is [1970-01-01T00:00:00Z, 3000-12-31T23:59:59Z] (UTC).

  Returns: the specified calendar time encoded as a value of type time_t or -1
  if time is out of range.
 */
inline CDateTime::operator __time64_t () const
{
tm tmResult;
SYSTEMTIME  stTemp;
if(::VariantTimeToSystemTime((real64)m_dateValue, &stTemp) != 0)
  {
  tmResult.tm_sec   = stTemp.wSecond;     //seconds after the minute [0, 61]
  tmResult.tm_min   = stTemp.wMinute;     //minutes after the hour   [0, 59]
  tmResult.tm_hour  = stTemp.wHour;       //hours after 00:00:00     [0, 23]
  tmResult.tm_mday  = stTemp.wDay;        //day of the month         [1, 31]
  tmResult.tm_mon   = stTemp.wMonth - 1;  //month of the year        [0, 11] 
  tmResult.tm_year  = stTemp.wYear - YEAR_EPOCH_TM;//years since 1900 
  tmResult.tm_wday  = stTemp.wDayOfWeek;  //day of the week          [0,  6] 
                                          //Sunday = 0
  tmResult.tm_isdst = -1; //Daylight saving time is unknown
  return _mktime64(&tmResult); //Convert the incomplete time to a normalized
                           //calendar value.
  }
return -1;
}
#endif //_USE_TIME_64

//-----------------------------------------------------------------------------
#ifdef _USE_TIME_64
/*
 */
CDateTime& CDateTime::operator=(const __time64_t& timeValue //[in] date to assign
                                )
{
tm* ptmTemp = _localtime64(&timeValue);
return (*this = *ptmTemp);
}
#endif //_USE_TIME_64

//-----------------------------------------------------------------------------
/*Convert a DATE to a tm structure. Valid range for date is:

      [0100-01-01T00:00:00, 9999-12-31T23:59:59].

  In case of a failure, tm structure members are filled with -1;
 */
CDateTime::operator tm() const
{
tm tmResult;
SYSTEMTIME  stTemp;
if(::VariantTimeToSystemTime((real64)m_dateValue, &stTemp) != 0)
  {
  tmResult.tm_sec   = stTemp.wSecond;     //seconds after the minute [0, 61]
  tmResult.tm_min   = stTemp.wMinute;     //minutes after the hour   [0, 59]
  tmResult.tm_hour  = stTemp.wHour;       //hours after 00:00:00     [0, 23]
  tmResult.tm_mday  = stTemp.wDay;        //day of the month         [1, 31]
  tmResult.tm_mon   = stTemp.wMonth - 1;  //month of the year        [0, 11] 
  tmResult.tm_year  = stTemp.wYear - YEAR_EPOCH_TM;//years since 1900 
  tmResult.tm_wday  = stTemp.wDayOfWeek;  //day of the week          [0,  6] 
                                          //Sunday = 0
  tmResult.tm_isdst = -1; //Daylight saving time is unknown
  #ifdef _USE_TIME_64
    _mktime64(&tmResult); //Convert the incomplete time to a normalized
                          //calendar value.
  #else
    mktime(&tmResult);
  #endif //_USE_TIME_64
  }
else
  {
  ::FillMemory(&tmResult, sizeof(tmResult), 0xFF);
  }
return tmResult;
}

//-----------------------------------------------------------------------------
/*Converts date to VARIANT VT_DATE data type used in OLE automation.
  VARIANT dates are represented as 64-bit real numbers where 
  1900-01-01T00:00:00 is 2.0.

  Note: 1899-12-30T00:00:00 is DATE with valie 0.0

  See also: oaidl.h
 */
CDateTime::operator VARIANT() const
{
VARIANT varResult;
varResult.vt = VT_DATE;
varResult.date = m_dateValue;
return varResult;
}

//-----------------------------------------------------------------------------
/*
 */
CDateTime& CDateTime::operator=(const tm& tmValue //[in] date to assign
                                )
{
if(!(SetDate(tmValue.tm_year + YEAR_EPOCH_TM,
        tmValue.tm_mon + 1,
        tmValue.tm_mday,
        tmValue.tm_hour,
        tmValue.tm_min,
        tmValue.tm_sec)) )
  ASSERT (FALSE);
return *this;
}

//-----------------------------------------------------------------------------
/*
 */
CDateTime& CDateTime::operator=(const SYSTEMTIME& stValue //[in] date to assign
                                )
{
if(!::SystemTimeToVariantTime(const_cast<LPSYSTEMTIME>(&stValue), 
                              (real64*)&m_dateValue))
  ASSERT(FALSE);
return *this;
}

//-----------------------------------------------------------------------------
/*Assigns date and time to this object.
  To convert to local time call first FileTimeToLocalFileTime().

  See also: FileTimeToLocalFileTime()
 */
CDateTime& CDateTime::operator=(const FILETIME& ftValue //[in] date to assign
                                )
{
SYSTEMTIME stTemp;
if(!::FileTimeToSystemTime(&ftValue, &stTemp))
  ASSERT(FALSE);
*this = stTemp;
return *this;
}

//-----------------------------------------------------------------------------
/*
 */
CDateTime& CDateTime::operator=(const time_t& timeValue //[in] date to assign
                                )
{
tm* ptmTemp = localtime(&timeValue);
return (*this = *ptmTemp);
}

//-----------------------------------------------------------------------------
/*
 */
CDateTime& CDateTime::operator=(const VARIANT& varValue //[in] date to assign
                                )
{
if( varValue.vt == VT_DATE ) //Assign the value
  {
  m_dateValue = varValue.date;
  }
else //Convert the value
  {
  VARIANT varTemp;
  if( SUCCEEDED(VariantChangeType(&varTemp, 
                const_cast<VARIANT*>(&varValue), 0, VT_DATE)) )
    {
      m_dateValue = varTemp.date;
      VariantClear(&varTemp);
    }
  #ifdef _DEBUG
    else
      TRACE0("  Failed to convert VARIANT to VT_DATE type.\n");
  #endif
  }

return *this;
}

//-----------------------------------------------------------------------------
/*Set new date and time. Method will accept ceratin invalid dates and try to
  fix them. A day less than 31 but greater than the maximum day in that month
  has the day promoted to the appropriate day of the next month. A day equal
  to zero resolves as the last day of the previous month.
  Valid range for dates is [0100-01-01T00:00:00, 9999-12-31T23:59:59].

  Returns: true if successful, false if days are negative, months are out of
  valid range
 */
bool CDateTime::SetDate(int iYear,  //[in] nYear  [100, 9999]
                        int iMonth, //[in] nMonth [1, 12] 
                        int iDay,   //[in] nDay   [1, 31] 
                        int iHour,  //[in]= 0 nHour  [0, 23] 
                        int iMinute,//[in]= 0 nMin   [0, 59] 
                        int iSecond //[in]= 0 nSec   [0, 59] 
                        )
{
SYSTEMTIME stTemp;
stTemp.wYear   = (WORD)iYear;   //current year
stTemp.wMonth  = (WORD)iMonth;  //current month; January is 1
stTemp.wDay    = (WORD)iDay;    //current day of the month
stTemp.wHour   = (WORD)iHour;   //current hour
stTemp.wMinute = (WORD)iMinute; //current minute
stTemp.wSecond = (WORD)iSecond; //current second
stTemp.wMilliseconds = 0;  //current millisecond

  //Note: variant time is stored as an 8-byte real value (double), representing 
  //a date between 0100-01-01 and 9999-12-31, inclusive, Negative numbers
  //represent dates prior to 1899-12-30.

  //Note: The SystemTimeToVariantTime function will accept invalid dates and
  //try to fix them when resolving to a VARIANT time. For example, an invalid
  //date such as 2001-02-29 will resolve to 2001-03-01. Only days are fixed,
  //so invalid month values result in an error being returned. Days are checked
  //to be between 1 and 31.
  //Negative days and days greater than 31 results in an error.
  //A day less than 31 but greater than the maximum day in that month has
  //the day promoted to the appropriate day of the next month. A day equal to
  //zero resolves as the last day of the previous month. For example,
  //an invalid dates such as 2001-02-00 will resolve to 2001-01-31.

return (::SystemTimeToVariantTime(&stTemp, (real64*)&m_dateValue) != 0);
}

//-----------------------------------------------------------------------------
//#ifdef _USE_ATL
  #ifndef __ATLCONV_H__
    #if (_MSC_VER <= 1200) //Microsoft Visual Studio 6.0 or less
      #include <stddef.h> //offsetof() definitions
    #endif
    #include <atlconv.h>
  #endif
/*Parses a string to read a date and time value.

  The szDate parameter can take a variety of formats. For example, the following 
  strings contain acceptable date/time formats:

      "25 January 1996"
      "8:30:00"
      "20:30:00"
      "January 25, 1996 8:30:00"
      "8:30:00 Jan. 25, 1996"
      "1/25/1996 8:30:00"  // always specify the full year,
                          // even in a 'short date' format

  Requires Active Template Library.(ATL). To enable define macro _USE_ATL
  Returns: true if successful; otherwise returns false.

  See also: VarDateFromStr()
 */
bool CDateTime::SetDate(LPCTSTR szDate, //[in] zero-terminated date and time
                                        //string which is to be parsed.
                        LCID lcid,      //[in] locale ID to use for the conversion
                        DWORD dwFlags //[in]= LOCALE_NOUSEROVERRIDE  one or more
                        //of the following flags:
                        //
                        //    Flag                    Description 
                        //    LOCALE_NOUSEROVERRIDE   system default locale settings,
                        //    VAR_CALENDAR_HJRI       Hijri calendar is used,
                        //    VAR_DATEVALUEONLY       parses only the date,
                        //    VAR_TIMEVALUEONLY       parses only the time.

                        )
{
LPCTSTR pszDate = ( szDate == NULL ) ? _T("") : szDate;
#if (_ATL_VER >= 0x700) //ATL 7.0 <atlconv.h>
  USES_CONVERSION_EX;
  LPOLESTR poleDate = T2OLE_EX((LPTSTR)pszDate, _ATL_SAFE_ALLOCA_DEF_THRESHOLD);
  if (SUCCEEDED(::VarDateFromStr(poleDate, lcid, dwFlags, &m_dateValue )))
    return true;

#else  //ATL 3.0
  USES_CONVERSION;
  if( SUCCEEDED(VarDateFromStr(T2OLE(const_cast<LPTSTR>(pszDate)), 
                              lcid, 
                              dwFlags, 
                              &m_dateValue)) )
    return true;
#endif
return false;
}
//#endif //_USE_ATL

//-----------------------------------------------------------------------------
/*Assigns date from the string to this object. The date could be in ISO 8601 
  basic, extended, or similar format:

      YYYYMMDD or YYYYcMMcDD
      where
        YYYY is year [0, 9999]. Meaning of the numbers depends of
             the implemtation and current epoch m_iEpoch
        MM   is month [1, 12]
        DD   is day of the month [1, 31]
        c    number separator.

  This implematation will accept any non-digit character as number separator.
  Also, signed numbers are allowed and the leading zeros are not neccessary,
  allowing conversion from following format:

      +YY/MMDD

  The method also accepts invalid dates and tries to fix them. For example, an 
  invalid date such as 2001-02-29 will resolve to 2001-03-01. Only days are
  fixed, so invalid month values result in an error being returned. Days are
  checked to be between 1 and 31. Negative days and days greater than 31
  results in an error. 
  A day less than 31 but greater than the maximum day in that month has the day
  promoted to the appropriate day of the next month. A day equal to zero
  resolves as the last day of the previous month. For example, an invalid dates
  such as 2001-02-00 will resolve to 2001-01-31.

  Note: number values for years, months or days of the month are not validated.
  Two digit years represent number of years since 1900.

  See also: _DATE_FORMAT_STD_BASIC, CDate, International Standard
  {HTML: <A HREF ="Res/ISO8601.htm"> ISO 8601:2000 </A>}
  Data elements and interchange formats,
  {HTML: <A HREF ="Res/RFC3339.htm"> RFC 3339 </A>}
  Date and Time on the Internet: Timestamps
 */
bool CDateTime::SetDate(LPCTSTR strValue //[in] string with date to set
                        )
{
extern int AtoI(LPCTSTR strSource, uint_fast16_t& nLen);
SYSTEMTIME stTemp;

uint_fast16_t nDigitCount; //number of digits parsed
uint_fast16_t nLen1 = 4;
stTemp.wYear = (WORD)AtoI(strValue, nLen1);
nDigitCount = nLen1;

if (stTemp.wYear < 100)
  stTemp.wYear += YEAR_EPOCH_TM;

if (!_istdigit (strValue[nLen1]))
  ++nLen1; //The character is probably a date delimiter

uint_fast16_t nLen2 = 2;
stTemp.wMonth  = (WORD)AtoI(&strValue[nLen1], nLen2);
nDigitCount += nLen2;

if (!_istdigit (strValue[nLen2 += nLen1]))
  ++nLen2; //The character is probably a date delimiter

nLen1 = 2;
stTemp.wDay  = (WORD)AtoI(&strValue[nLen2], nLen1);
nDigitCount += nLen1;

  //Note: Properly formatted date has 8 digits, but we will
  //try to fix date even with less digits.

if (nDigitCount == 0) //Not a single digit found
  return false;

stTemp.wHour   = 0; //TODO: parse time as well
stTemp.wMinute = 0;
stTemp.wSecond = 0;
stTemp.wMilliseconds = 0; 
stTemp.wDayOfWeek = (WORD)(-1);
return (::SystemTimeToVariantTime(&stTemp, (real64*)&m_dateValue) != 0);
}

//-----------------------------------------------------------------------------
#ifdef __oledb_h__
/*Convert date and time to DBTIMESTAMP structure. The data structure initialized
  by this operator will have its fraction member set to zero.

      typedef struct tagDBTIMESTAMP
        {
        SHORT year;
        USHORT month;
        USHORT day;
        USHORT hour;
        USHORT minute;
        USHORT second;
        ULONG fraction;
        }   DBTIMESTAMP;

  Note: This method is only available when oledb.h is included.

  See also: oledb.h
*/
CDateTime::operator DBTIMESTAMP() const
{
DBTIMESTAMP dbtsResult;
tm tmTemp = *this;
if( (tmTemp.tm_hour >= 0 ) && (tmTemp.tm_mon >= 0) )
  {
  dbtsResult.day    = tmTemp.tm_mday;
  dbtsResult.month  = tmTemp.tm_mon + 1;
  dbtsResult.year   = tmTemp.tm_year + YEAR_EPOCH_TM;
  dbtsResult.hour   = tmTemp.tm_hour;
  dbtsResult.minute = tmTemp.tm_min;
  dbtsResult.second = tmTemp.tm_sec;
  dbtsResult.fraction = 0;
  }
else
  ZeroMemory(&dbtsResult,sizeof(dbtsResult));
return dbtsResult;
}
#endif

//-----------------------------------------------------------------------------
#ifdef __oledb_h__
/*
  Note: This method is only available when oledb.h is included.

  See also: oledb.h
 */
CComDATE& CComDATE::operator=(const DBTIMESTAMP& dbtsValue //[in] value to assign
                              )
{ 
SYSTEMTIME stTemp;
stTemp.wYear   = dbtsValue.year;   //current year
stTemp.wMonth  = dbtsValue.month;  //current month; January is 1
stTemp.wDay    = dbtsValue.day;    //current day of the month
stTemp.wHour   = dbtsValue.hour;   //current hour
stTemp.wMinute = dbtsValue.minute; //current minute
stTemp.wSecond = dbtsValue.second; //current second
stTemp.wMilliseconds = 0;  //current millisecond
//TODO: Convert dbtsValue.fraction D.K.

  //Note: variant time is stored as an 8-byte real value (double), representing 
  //a date between 0100-01-01 and 9999-12-31, inclusive, Negative numbers
  //represent dates prior to 1899-12-30.

  //Note: The SystemTimeToVariantTime function will accept invalid dates and
  //try to fix them when resolving to a VARIANT time. For example, an invalid
  //date such  as 2001-02-29 will resolve to 2001-03-01. Only days are fixed,
  // so invalid month values result in an error being returned. Days are
  //checked to be between 1 and 31.
  //Negative days and days greater than 31 results in an error.
  //A day less than 31 but greater than the maximum day in that month has
  //the day promoted to the appropriate day of the next month. A day equal to
  // zero resolves as the last day of the previous month. For example,
  //an invalid dates such as 2001-02-00 will resolve to 2001-01-31.

::SystemTimeToVariantTime(&stTemp, (real64*)&m_dateValue);

return *this;
}
#endif  // __oledb_h__

//-----------------------------------------------------------------------------
/*Converts date and time to a file time. The FILETIME structure is a 
  64-bit value representing the number of 100-nanosecond intervals since 
  1601-01-01T00:00:00Z (UTC).

      typedef struct _FILETIME 
        {
        DWORD dwLowDateTime; //low-order part of the file time.
        DWORD dwHighDateTime;//high-order part of the file time. 

        } FILETIME, *PFILETIME;
 */
CDateTime::operator FILETIME() const
{
FILETIME ftResult;

SYSTEMTIME stTemp = *this;
::SystemTimeToFileTime(&stTemp, &ftResult);

return ftResult;
}

//-----------------------------------------------------------------------------
/*Obtains current local date and time. The time is corrected for the local
  time zone.
 */
void CDateTime::GetLocalTime()
{
SYSTEMTIME stCurrentTime;
::GetLocalTime(&stCurrentTime);
*this = stCurrentTime;
}

///////////////////////////////////////////////////////////////////////////////
#pragma warning (default: 4127)
/*****************************************************************************
 * $Log: 
 *  7    Biblioteka1.6         2004-10-08 12:35:47  Darko           fixed MSVC
 *       UNICODE and header aliases
 *  6    Biblioteka1.5         2004-10-06 23:14:24  Darko           Unicode
 *  5    Biblioteka1.4         2004-10-01 22:52:16  Darko           Added _USE_ATL
 *       guard
 *  4    Biblioteka1.3         2004-10-01 15:45:43  Darko           fixed VARIANT
 *       support in MSVC6
 *  3    Biblioteka1.2         2003-09-30 09:06:20  Darko           DATE_ERROR
 *  2    Biblioteka1.1         2003-09-28 01:40:55  Darko           SetDate()
 *  1    Biblioteka1.0         2003-09-27 11:53:07  Darko           
 * $
 *****************************************************************************/
