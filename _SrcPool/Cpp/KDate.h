/*$Workfile: KDate.h$: header file
  $Revision: 3$ $Date: 2005-03-11 17:06:12$
  $Author: Darko Kolakovic$

  date struct encapsulation
  Copyright: CommonSoft Inc
  2003-09-23 Darko Kolakovic
 */
/* Group=Time                                                                */

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
  #pragma once
#endif

#ifndef _KDATE_H_
    //$Workfile: KDate.h$ sentry
  #define _KDATE_H_

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

#include "KTime.h"  //date struct

///////////////////////////////////////////////////////////////////////////////
//CDate encapsulates date structure used to represented calendar date.
//
//Note: da_year represents number of years since epoch beginning. m_iEpoch
//      represents the first year of an epoch. To avoid overflow condition,
//      sum of da_year and m_iEpoch have to be less than INT_LEAST16_MAX.
//
//See also: date
class CDate: public date
{
public:
  CDate(const int_least16_t iEpoch = YEAR_EPOCH_CAL);
  CDate(const CDate& dtValue);
  CDate(const date& dtValue, const int_least16_t iEpoch = YEAR_EPOCH_DOS);
  CDate(const tm& tmtValue);
  CDate(LPCTSTR strValue, const int_least16_t iEpoch = YEAR_EPOCH_CAL);

  virtual ~CDate();

public:
  int_least16_t m_iEpoch; /*first year in an epoch used in year calculation.
                            date.da_year member contains number of years since
                            epoch beginning. If epoch year is 1, date.da_year
                            is a calendar year.

                            Note: calendar years begins with the year 01.

                            See also: date.da_year
                           */
public:
  CDate& operator=(const CDate& dtValue);
  CDate& operator=(const tm& tmValue);
  CDate& operator=(LPCTSTR strValue);
  operator tm();
  int_least8_t  GetDayOfWeek();
  int_least16_t GetDayOfYear();
  void SetDate(tm& tmtValue);
  int_fast16_t GetYear() const;
  int_least16_t SetEpoch(const int_least16_t iNewEpoch);

public:
  virtual LPTSTR toString(LPTSTR szTarget);
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Default constructor initializes date to 0001-01-01.

  See also: date, YEAR_EPOCH_DOS, YEAR_EPOCH_UNIX, YEAR_EPOCH_TM
 */
inline CDate::CDate(const int_least16_t iEpoch //[in]=YEAR_EPOCH_CAL first year
                                               //of an epoch
                   ) :
  m_iEpoch(iEpoch)
{
da_year = 0;
da_day  = 1;
da_mon  = 1;
}

//-----------------------------------------------------------------------------
/*Copy constructor
 */
inline CDate::CDate(const CDate& dtValue //[in] value to copy
      ) :
  m_iEpoch(dtValue.m_iEpoch)
{
da_year = dtValue.da_year;
da_day  = dtValue.da_day ;
da_mon  = dtValue.da_mon ;
}

//-----------------------------------------------------------------------------
/*
  Note: because assignment operator for date is not provided, therefore this
  conversion constructor will be invoked. Default YEAR_EPOCH_DOS epoch will be
  set without converting year from previous epoch. This behavior is by design.

  Example:
      #include "KDate.h"  //Date class
      ...
      CDate dateCal;  //calendar date, YEAR_EPOCH_CAL
      date dateDOS;   //DOS date, YEAR_EPOCH_DOS
        //Set date 2003-06-07
      dateB.da_year = 2003 - YEAR_EPOCH_DOS;
      dateB.da_day = 7;
      dateB.da_mon = 6;

      dateCal = dateDOS; //copy DOS date, YEAR_EPOCH_DOS
      TCHAR szDate[9];
      TRACE(dateA.toString((LPTSTR)szDate)); //output: 20030607

 */
inline CDate::CDate(const date& dtValue,       //[in] value to convert
                    const int_least16_t iEpoch //[in]= YEAR_EPOCH_DOS first year
                                               //of an epoch; default year is 1980
      ) :
  m_iEpoch(iEpoch)
{
da_year = dtValue.da_year;
da_day  = dtValue.da_day ;
da_mon  = dtValue.da_mon ;
}

//-----------------------------------------------------------------------------
/*
 */
inline CDate::CDate(const tm& tmValue //[in] value to copy
      ) :
  m_iEpoch(YEAR_EPOCH_TM)
{
da_year = (int_least16_t)tmValue.tm_year;
da_day  = (int_least8_t)tmValue.tm_mday;
da_mon  = (int_least8_t)tmValue.tm_mon + 1;
}

//-----------------------------------------------------------------------------
/*
 */
inline CDate& CDate::operator=(const CDate& dtValue //[in] value to assign
                            )
{
da_year = dtValue.da_year + dtValue.m_iEpoch - m_iEpoch;
da_day  = dtValue.da_day ;
da_mon  = dtValue.da_mon ;
return *this;
}

//-----------------------------------------------------------------------------
/*
 */
inline CDate& CDate::operator=(const tm& tmValue //[in] value to assign
                            )
{
da_year = (int_least16_t)tmValue.tm_year + YEAR_EPOCH_TM - m_iEpoch;
da_day  = (int_least8_t)tmValue.tm_mday;
da_mon  = (int_least8_t)tmValue.tm_mon + 1;

return *this;
}

//-----------------------------------------------------------------------------
/*Obtains the calendar year. Calendar year is the sum of years since epoch
  beginning and the epoch m_iEpoch.

  Returns: the calendar year. In case of the overflow, the result is undefined.
 */
inline int_fast16_t CDate::GetYear() const
{
return (int_fast16_t)(da_year + m_iEpoch);
}

//-----------------------------------------------------------------------------
/*Sets new epoch. The number of years since epoch beginning will mirror new
  epoch.

  Note: To avoid overflow condition, sum of da_year and m_iEpoch members have
  to be less than INT_LEAST16_MAX.

  Returns: beginning of previous epoch.
 */
inline int_least16_t CDate::SetEpoch(const int_least16_t iNewEpoch)
{
int_least16_t iOldEpoch = m_iEpoch;
da_year += m_iEpoch - iNewEpoch;
m_iEpoch = iNewEpoch;
return iOldEpoch;
}

///////////////////////////////////////////////////////////////////////////////
#endif  //_KDATE_H_
/*****************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2003-09-25 01:29:34  Darko           toString()
 *  1    Biblioteka1.0         2003-09-24 18:41:32  Darko
 * $
 *****************************************************************************/
