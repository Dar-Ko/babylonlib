/*$Workfile: KDateConv.h$: header file
  $Revision: 5$ $Date: 2005-03-11 18:06:26$
  $Author: Darko Kolakovic$

  DATE conversions
  Copyright: CommonSoft Inc
  2003-09-21 Darko Kolakovic
 */
/* Group=Time                                                                */

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
  #pragma once
#endif

#ifndef _KDATECONV_H_
    //$Workfile: KDateConv.h$ sentry
  #define _KDATECONV_H_

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
#endif

#include "KTime.h"  //DATE typedef

///////////////////////////////////////////////////////////////////////////////
//Abstract class that encapsulates different conversions to and from DATE object used
//represented date and time.
//
//See also: COleDateTime, MFC
class CDateConv
{
public:
  CDateConv();
  CDateConv(int iYear, int iMonth, int iDay,
            int iHour = 0, int iMinute = 0, int iSecond = 0);
  CDateConv(const CDateConv& dateValue);
  CDateConv(const double dValue);
  CDateConv(LPCTSTR strValue);

  virtual ~CDateConv();

public:
  static const double SpDAY;
  static const double HALF_SECOND;
  DATE m_dateValue;         //date and time since epoch beginning

public:
  operator double() const;
  CDateConv& operator=(const double& dValue);
  virtual operator tm() const = 0;

public:
  virtual bool SetDate(int iYear, int iMonth, int iDay,
                       int iHour = 0, int iMinute = 0, int iSecond = 0) = 0;
  virtual bool SetDate(LPCTSTR strValue) =0;
  virtual bool IsValid() const = 0;
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*
 */
inline CDateConv::CDateConv()
{
}

//-----------------------------------------------------------------------------
/*Copy constructor
 */
inline CDateConv::CDateConv(const CDateConv& dateValue //[in] value to copy
                    ) :
m_dateValue(dateValue.m_dateValue)
{
}

//-----------------------------------------------------------------------------
/*
 */
inline CDateConv::~CDateConv()
{
}

//-----------------------------------------------------------------------------
/*
 */
inline CDateConv::operator double() const
{
return DateToD(m_dateValue);
}

//-----------------------------------------------------------------------------
/*Assigns double or DATA type after validation of negative values, since
  negative dates are not continuous.

  History: Microsoft COleDateTime::DateFromDouble, ATLComTime.inl
 */
inline CDateConv& CDateConv::operator=(const double& dValue //[in] value to assign
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
return *this;
}

///////////////////////////////////////////////////////////////////////////////
#endif  //_KDATECONV_H_
/*****************************************************************************
 * $Log:
 *  4    Biblioteka1.3         2003-09-28 01:39:22  Darko           operator=()
 *  3    Biblioteka1.2         2003-09-27 12:13:16  Darko           SetDate()
 *  2    Biblioteka1.1         2003-09-22 22:25:47  Darko           formatting
 *  1    Biblioteka1.0         2003-09-22 22:23:17  Darko
 * $
 *****************************************************************************/
