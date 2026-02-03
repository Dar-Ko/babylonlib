/*$Workfile: KDate.cpp$: implementation file
  $Revision: 8$ $Date: 2005-06-28 13:37:53$
  $Author: Darko Kolakovic$

  Defines the class behavior.
  Copyright: CommonSoft Inc.
  2003-09-23 Darko Kolakovic
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#ifdef _MSC_VER //Microsoft Visual Studio C++ compiler
  #ifdef _UNICODE
    #ifndef UNICODE
      //To enable Unicode for some Microsoft Visual C/C++ header files,
      //the UNICODE definition is required
      #define UNICODE
    #endif
  #endif
#endif  //_MSC_VER

#include "KDate.h"  //CDate class
#ifndef ASSERT
  #include "KTrace.h"
#endif
#include "KTChar.h"    //TCHAR typedef

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

  //warning C4127: conditional expression is constant
#pragma warning (disable: 4127)
///////////////////////////////////////////////////////////////////////////////
// CDate class

//-----------------------------------------------------------------------------
/*Initializes this object with date from the formatted string. Date could be in
  ISO 8601 basic, extended date, or similar format:

      YYYYMMDD or YYYYcMMcDD
      where
        YYYY is year [0, 9999]. Meaning of the numbers depends of
             the implementation and current epoch m_iEpoch
        MM   is month [1, 12]
        DD   is day of the month [1, 31]
        c    number separator.

  See also: _DATE_FORMAT_STD_BASIC, CDate::operator=(), International Standard
  {html: <a href="Documentation/ISO8601.htm">ISO 8601:2000</a>}
  Data elements and interchange formats,
  {html: <a href="Documentation/RFC3339.htm">RFC 3339</a>}
  Date and Time on the Internet: Timestamps
 */
CDate::CDate(LPCTSTR strValue,  //[in] string with date
             const int_least16_t iEpoch //[in]= YEAR_EPOCH_CAL
             ) :
  m_iEpoch(iEpoch)
{
*this = strValue;
}

CDate::~CDate()
{
}

//-----------------------------------------------------------------------------
/*Converts a CDate to a tm structure. Time will be set to 00:00:00
 */
CDate::operator tm()
{
tm tmResult;
tmResult.tm_sec  = 0;
tmResult.tm_min  = 0;
tmResult.tm_hour = 0;
tmResult.tm_mday = da_day;
tmResult.tm_mon  = da_mon -1;
tmResult.tm_year = da_year + m_iEpoch - YEAR_EPOCH_TM;
tmResult.tm_wday = GetDayOfWeek();
tmResult.tm_yday = GetDayOfYear();
tmResult.tm_isdst = -1; //Daylight saving time is unknown
return tmResult;
}

//-----------------------------------------------------------------------------
/*TODO: GetDayOfWeek()
 */
int_least8_t CDate::GetDayOfWeek()
{
return 0;
}

//-----------------------------------------------------------------------------
/*TODO: GetDayOfYear()
 */
int_least16_t CDate::GetDayOfYear()
{
return 0;
}

//-----------------------------------------------------------------------------
/*Set date portion of the tm object. The time would not be changed.
 */
void CDate::SetDate(tm& tmtValue //[out] date in tm structure
                    )
{
tmtValue.tm_mday = da_day;
tmtValue.tm_mon  = da_mon -1;
tmtValue.tm_year = da_year + m_iEpoch - YEAR_EPOCH_TM;
tmtValue.tm_wday = GetDayOfWeek();
tmtValue.tm_yday = GetDayOfYear();
}

//-----------------------------------------------------------------------------
/*Converts date to zero-terminated string in ISO 8601 basic date format:
      YYYYMMDD where
        YYYY is year [0000, 9999]. Meaning of the numbers depends of
             the implementation and current epoch m_iEpoch
        MM   is month [01, 12]
        DD   is day of the month [01, 31]

  Method requires a szTarget to store 9 characters. Method does not check szTarget
  overflow condition.
  Override this method if different date format is desired.

  Returns: pointer to szTarget containing date in basic format.

  See also: _DATE_FORMAT_STD_BASIC, International Standard
  {html: <a href="Documentation/ISO8601.htm">ISO 8601:2000</a>}
  Data elements and interchange formats,
  {html: <a href="Documentation/RFC3339.htm">RFC 3339</a>}
  Date and Time on the Internet: Timestamps
 */
LPTSTR CDate::toString(LPTSTR szTarget //[out] zero-terminated date string
                       )
{
ASSERT(szTarget != NULL);
if (szTarget != NULL)
  {
  int_least16_t iYear = da_year + m_iEpoch;

  if (iYear < 0)
    iYear = 0;
  if (iYear > 9999)
    iYear = 9999;

  szTarget[0] = (TCHAR)(iYear / 1000 + _T('0'));
  szTarget[1] = (TCHAR)((iYear % 1000) / 100 + _T('0'));
  szTarget[2] = (TCHAR)((iYear % 100) / 10 + _T('0'));
  szTarget[3] = (TCHAR)(iYear % 10 + _T('0'));
  szTarget[4] = (TCHAR)(da_mon / 10 + _T('0'));
  szTarget[5] = (TCHAR)(da_mon % 10 + _T('0'));
  szTarget[6] = (TCHAR)(da_day / 10 + _T('0'));
  szTarget[7] = (TCHAR)(da_day % 10 + _T('0'));
  szTarget[8] = _T('\0');
  }
return szTarget;
}

//-----------------------------------------------------------------------------
/*Assigns date from the string to this object. The date could be in ISO 8601
  basic, extended, or similar format:

      YYYYMMDD or YYYYcMMcDD
      where
        YYYY is year [0, 9999]. Meaning of the numbers depends of
             the implementation and current epoch m_iEpoch
        MM   is month [1, 12]
        DD   is day of the month [1, 31]
        c    number separator.

  This implementation will accept any non-digit character as number separator. Also,
  signed numbers are allowed and the leading zeros are not necessary, allowing
  conversion from following format:

      +YY/MMDD

  Note: number values for years, months or days of the month are not validated.
  Two digit years represent number of years since current epoch m_iEpoch.

  Example:
      #include"KDate.h" //CDate class
      ...
      char* strDate = "1964-11-23T16:30";
      char szBuffer[9];
      CDate dateA;
      dateA = strDate; //Set calendar date
      std::cout << "ISO 8601: " << dateA.toString((LPTSTR)szBuffer) << std::endl;


  See also: _DATE_FORMAT_STD_BASIC, International Standard
  {html: <a href="Documentation/ISO8601.htm">ISO 8601:2000</a>}
  Data elements and interchange formats,
  {html: <a href="Documentation/RFC3339.htm">RFC 3339</a>}
  Date and Time on the Internet: Timestamps
 */
CDate& CDate::operator=(LPCTSTR strValue //[in] string with date to assign
                       )
{
extern int AtoI(LPCTSTR strSource, uint_fast16_t& nLen);

uint_fast16_t nLen1 = 4;
da_year = (uint_least16_t)AtoI(strValue,nLen1) - m_iEpoch;

if (!_istdigit (strValue[nLen1]))
  ++nLen1; //The character is probably a date delimiter

uint_fast16_t nLen2 = 2;
da_mon  = (uint_least8_t)AtoI(&strValue[nLen1], nLen2);

if (!_istdigit (strValue[nLen2 += nLen1]))
  ++nLen2; //The character is probably a date delimiter

nLen1 = 2;
da_day  = (uint_least8_t)AtoI(&strValue[nLen2], nLen1);

return *this;
}

///////////////////////////////////////////////////////////////////////////////
#pragma warning (default: 4127)
/*****************************************************************************
 * $Log:
 *  4    Biblioteka1.3         2004-06-01 17:50:16  Darko           time sync
 *  3    Biblioteka1.2         2003-11-03 13:08:50  Darko           Unicode fix
 *  2    Biblioteka1.1         2003-09-25 01:29:33  Darko           toString()
 *  1    Biblioteka1.0         2003-09-24 18:41:31  Darko
 * $
 *****************************************************************************/
