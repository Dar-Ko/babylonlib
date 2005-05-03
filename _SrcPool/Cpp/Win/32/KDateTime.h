/*$Workfile: KDateTime.h$: implementation file
  $Revision: 5$ $Date: 2004-10-01 22:52:18$
  $Author: Darko$

  Date and time conversions
  Copyright: CommonSoft Inc
  2003-09-26 Darko Kolakovic
 */
/* Group=Time                                                                */

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
  #pragma once
#endif

#ifndef _KDATETIME_H_
    //$Workfile: KDateTime.h$ sentry
  #define _KDATETIME_H_

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

#ifdef _MSC_VER //Micorsoft C++ compiler
    //DATE is defined in <atlcomtime.h> and <wtypes.h>
  #if defined(__ATLCOMTIME_H__) || defined(__wtypes_h__)
    #define DATE DATE
    #if defined(__ATLCOMTIME_H__)
      #pragma message ("  DATE defined in <atlcomtime.h>")
    #endif
    #if defined(__wtypes_h__)
      #pragma message ("  DATE defined in <wtypes.h>")
    #endif
  #endif

  #if _MSC_VER >= 1300
      //Requires Microsoft Visual C++ .Net
    #ifndef _USE_TIME_64
        //Microsoft specific data type  __time64_t is defined
      #define _USE_TIME_64 64
    #endif
  #endif
#endif
//#if _MSC_VER < 1300
//    /*Microsoft compilers before Visual C++ .Net 2002, 32-bit, version 7.0*/
//  typedef DOUBLE real64;
//#endif

#if _MFC_VER >= 0x0700
  //Requires MFC 7.0+
  #ifndef _USE_TIME_64
      //Microsoft specific data type  __time64_t is defined
    #define _USE_TIME_64 64
  #endif
#endif

#include "KDateConv.h"  //CDateConv class

///////////////////////////////////////////////////////////////////////////////
//CDateTime encapsulates different conversions to and from DATE object used
//represented date and time.
//
//Epoch starts with 1899-12-30T00:00:00 as time zero
//
//Note:  Microsoft Windows specific (Win32).
//
//Note: To avoid the “Year 2038” problem, Microsoft defined a new data type 
//      __time64_t that supports dates up to 3000-12-31. A new set of CRT 
//      routines utilizing __time64_t are found in msvcrt.dll v6.1 or higher.
//      Also is required MFC 7.0  or higher.
//
//See also: COleDateTime, MFC
class CDateTime : public CDateConv
{
public:
  CDateTime(const double dValue = 0.0);
  CDateTime(const CDateTime& dateValue);
  CDateTime(const time_t timeValue);
  CDateTime(const SYSTEMTIME& stValue);
  CDateTime(const FILETIME& ftValue);
  CDateTime(const VARIANT& varValue);
  CDateTime(LPCTSTR strValue);
  virtual ~CDateTime();

public:
  //static const double EPOCH_JD; //TODO: difference to Julian Datte
  static const int DATE_MIN;
  static const int DATE_MAX;
  static const int DATE_ERROR;

public:
  operator tm() const;
  operator FILETIME() const;
  operator SYSTEMTIME() const;
  operator time_t() const;
  operator VARIANT() const;
  CDateTime& operator=(const double& dValue);
  CDateTime& operator=(const tm& tmValue);
  CDateTime& operator=(const SYSTEMTIME& stValue);
  CDateTime& operator=(const FILETIME& ftValue);
  CDateTime& operator=(const time_t& timeValue);
  CDateTime& operator=(const VARIANT& varValue);
  CDateTime& operator=(LPCTSTR strValue);

  #if (defined _WIN32) && (defined _USE_TIME_64)
    CDateTime (const __time64_t timeValue);
    operator __time64_t() const;
    CDateTime& operator=(const __time64_t& timeValue);
  #endif
  #ifdef __AFX_H__
    CDateTime(CTime ctTime);
    operator CTime() const;
    CDateTime& operator=(const CTime& ctTime);
  #endif  // __AFX_H__
  #ifdef __oledb_h__
    operator DBTIMESTAMP() const;
    CDateTime& operator=(const DBTIMESTAMP& dbtsValue);
  #endif  // __oledb_h__
  #ifdef __SQLTYPES //<sqltypes.h>
    CDateTime(const DATE_STRUCT& ds) const;
    CDateTime(const TIME_STRUCT& ts) const;
    CDateTime(const TIMESTAMP_STRUCT& ts) const;
    CDateTime& operator=(const DATE_STRUCT& ds);
    CDateTime& operator=(const TIME_STRUCT& ts);
    CDateTime& operator=(const TIMESTAMP_STRUCT& ts);
  #endif  // __SQLTYPES

public:
  void GetLocalTime();
  //#ifdef _USE_ATL TODO: do we need this guard?
    bool SetDate(LPCTSTR szDate, LCID lcid, DWORD dwFlags = LOCALE_NOUSEROVERRIDE);
  //#endif //_USE_ATL
  #ifdef _KTIME16_H_
    bool SetDate(const FILEDATEDOS& dosDate, const FILETIMEDOS& dosTime = 0);
  #endif
  virtual bool SetDate(int iYear, int iMonth, int iDay, 
                       int iHour = 0, int iMinute = 0, int iSecond = 0);
  virtual bool SetDate(LPCTSTR strValue);
  virtual bool IsValid() const;
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Copy constructor
 */
inline CDateTime::CDateTime(const CDateTime& dateValue //[in] value to copy
                           )
{
m_dateValue = dateValue.m_dateValue;
} 

//-----------------------------------------------------------------------------
/*Coverts from double or DATA type after validation of negative values, since 
  negative dates are not continuous.
 */
inline CDateTime::CDateTime(const double dValue //[in]= 0.0 value to convert
                            ) :
  CDateConv(dValue)
{
}

//-----------------------------------------------------------------------------
/*Converts a time value.
  Valid range is [1970-01-01 00:00:00, 2038-01-18 19:14:07].
 */
inline CDateTime::CDateTime(const time_t timeValue //[in] system time
               )
{
//Convert a time value and correct for the local time zone
tm* pTemp = localtime(&timeValue);
if(!(SetDate(pTemp->tm_year + YEAR_EPOCH_TM,
        pTemp->tm_mon + 1,
        pTemp->tm_mday,
        pTemp->tm_hour,
        pTemp->tm_min,
        pTemp->tm_sec)) )
  {
  TRACE0("  Failed to set date.\n");
  m_dateValue = CDateTime::DATE_ERROR;
  }

}

//-----------------------------------------------------------------------------
#if _USE_TIME_64
  /*Converts a time value.
  Valid range is [1970-01-01 00:00:00, 3000-12-31 23:59:59].
 */
  inline CDateTime::CDateTime(const __time64_t timeValue //[in] system time
                            )
  {
  tm * pTemp = _localtime64(&timeValue);
  if(!(SetDate(pTemp->tm_year + YEAR_EPOCH_TM,
        pTemp->tm_mon + 1,
        pTemp->tm_mday,
        pTemp->tm_hour,
        pTemp->tm_min,
        pTemp->tm_sec)) )
  ASSERT(FALSE);
  }
#endif //_USE_TIME_64

//-----------------------------------------------------------------------------
/*
 */
inline CDateTime::CDateTime(const SYSTEMTIME& stValue //[in] date and time
                            )
{ 
*this = stValue;
}

/*
 */
inline CDateTime::CDateTime(const FILETIME& ftValue //[in] date and time
                            )
{ 
*this = ftValue;
}

/*
 */
inline CDateTime::CDateTime(const VARIANT& varValue //[in] date and time
                            )
{ 
*this = varValue; 
}

//-----------------------------------------------------------------------------
/*Initializes this object with date from the formatted string. Date could be in
  ISO 8601 basic, extended date, or similar format:

      YYYYMMDD or YYYYcMMcDD
      where
        YYYY is year [0, 9999]. Meaning of the numbers depends of
             the implemtation and current epoch m_iEpoch
        MM   is month [1, 12]
        DD   is day of the month [1, 31]
        c    number separator.

  If the string could not be parsed, date is set to CDateTime::DATE_MAX;

  See also: _DATE_FORMAT_STD_BASIC, CDateTime:: SetDate(), CDate::opertor=(), 
  International Standard
  {HTML: <A HREF ="Res/ISO8601.htm"> ISO 8601:2000 </A>}
  Data elements and interchange formats,
  {HTML: <A HREF ="Res/RFC3339.htm"> RFC 3339 </A>}
  Date and Time on the Internet: Timestamps
 */
inline CDateTime::CDateTime(LPCTSTR strValue //[in] string to parse
                           )
{
if(!SetDate(strValue))
  {
  TRACE1("  Failed to parse %s.\n", strValue);
  m_dateValue = CDateTime::DATE_ERROR;
  }
}

//-----------------------------------------------------------------------------
/*
 */
inline CDateTime::~CDateTime()
{
}

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

  If the string could not be parsed, date is set to CDateTime::DATE_MAX;

  Note: number values for years, months or days of the month are not validated.

  See also: _DATE_FORMAT_STD_BASIC, CDateTime:: SetDate(), CDate,
  International Standard
  {HTML: <A HREF ="Res/ISO8601.htm"> ISO 8601:2000 </A>}
  Data elements and interchange formats,
  {HTML: <A HREF ="Res/RFC3339.htm"> RFC 3339 </A>}
  Date and Time on the Internet: Timestamps
 */
inline CDateTime& CDateTime::operator=(LPCTSTR strValue //[in] string with date
                                                        // to assign
                            )
{
if(!SetDate(strValue))
  {
  TRACE1("  Failed to parse %s.\n", strValue);
  m_dateValue = CDateTime::DATE_ERROR;
  }
return *this;
}

//-----------------------------------------------------------------------------
/*Assigns double or DATA type after validation of negative values, since 
  negative dates are not continuous.
 */
inline CDateTime& CDateTime::operator=(const double& dValue //[in] value to assign
                     )
{
*(CDateConv*)this = dValue;
return *this;
}

//-----------------------------------------------------------------------------
#ifdef _KTIME16_H_
  /*Set new date and time. Method will accept ceratin invalid dates and try to
    fix them. A day less than 31 but greater than the maximum day in that month
    has the day promoted to the appropriate day of the next month. A day equal
    to zero resolves as the last day of the previous month.

    Valid range for dates is [1980-01-01T00:00:00, 2099-12-31T23:59:59].

    Note: include "KTime16.h" before "KDateTime.h"

    Returns: true if successful, false if days are negative, months are out of
    valid range

    See also: KTime16.h, tagFILETIMEDOS, tagFILEDATEDOS
  */
  inline bool CDateTime::SetDate(const FILEDATEDOS& dosDate,//[in] new date
                          const FILETIMEDOS& dosTime //[in]= 0 new time
                          )
  {
  if( !::DosDateTimeToVariantTime(dosDate, dosTime, &m_dateValue) ) 
    return false;
  return true;
  }
#endif

//-----------------------------------------------------------------------------
/*Validates date and time range. Valid range for date is:

      [0100-01-01T00:00:00, 9999-12-31T23:59:59].

  Returns: true if date and time are in valid range, othervise returns false.
 */
inline bool CDateTime::IsValid() const
{
return ((m_dateValue >= DATE_MIN) &&
        (m_dateValue <= DATE_MAX)   );
}

///////////////////////////////////////////////////////////////////////////////
#endif  //_KDATETIME_H_
/*****************************************************************************
 * $Log: 
 *  5    Biblioteka1.4         2004-10-01 22:52:18  Darko           Added _USE_ATL
 *       guard
 *  4    Biblioteka1.3         2004-10-01 15:46:28  Darko           excluded
 *       __time64_t for MSVC6
 *  3    Biblioteka1.2         2003-09-30 09:06:23  Darko           DATE_ERROR
 *  2    Biblioteka1.1         2003-09-28 01:40:57  Darko           SetDate()
 *  1    Biblioteka1.0         2003-09-27 11:53:10  Darko           
 * $
 *****************************************************************************/
