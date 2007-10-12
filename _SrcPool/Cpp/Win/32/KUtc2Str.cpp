/*$Workfile: KTimeUtc.cpp$: implementation file
  $Revision: 1.2 $ $Date: 2007/10/12 15:29:17 $
  $Author: ddarko $

  Date and time manipulators
  2004-08-19
 */

// Group=Time

#include "stdafx.h" // MFC core and standard components

#ifndef _T
  #include "KTChar.h" //LPCTSTR typedef
#endif
#ifndef _DATETIME_FORMAT_STD
  #include "KTime.h" //_DATETIME_FORMAT_STD
#endif

#ifdef _DEBUG
  #ifdef _USE_MFC
    #define new DEBUG_NEW
  #endif
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

CString GetUtcTime(bool bBasicFormat = true);

//-----------------------------------------------------------------------------
/*Returns current Universal Coordinated Time (UTC) in the ISO 8601 date format:
     Basic format      YYYYMMDDThhmmss,fff
     Extended format   YYYY-MM-DDThh:mm:ss,fff
     where:
      - YYYY is the year in the usual Gregorian calendar,
      - MM   is the month of the year [01,12] (January is 01)
      - DD   is the day of the month [01,31].
      - T    is time designator
      - hh   is the number of complete hours that have passed since midnight;
             represented by two digits in the range [00, 24].
             The Hour 00 is the beginning of any given day and the Hour 24 is the
             end of the day. Midnight will normally be represented as 0000 or 2400.
             Hour 24  have the minute and second values zero 24:00:00.
      - mm   is the number of complete minutes that have passed since the start
             of the hour; represented by two digits in the range [00, 59].
      - ss   is the number of complete seconds since the start of the minute;
             represented by two digits in the range [00, 60].
             Value 60 allows to add a leap second to
             the Coordinated Universal Time (UTC).
      - fff  is the decimal fraction of the preceding time unit (second in this
             case); it is represented by any previously agreed number of digits
             bigger or equal to one. Decimal sign is comma (,) or dot (.),
             but comma is preferred.

  Note: uses Microsoft Foundation Library (MFC) or
        uses Microsoft Active Template Library (ATL);
        Microsoft Windows specific (Win32).
*/
CString GetUtcTime(bool bBasicFormat //[in] = true
                  )
{
SYSTEMTIME uSystTime;
CString strResult;

GetSystemTime(&uSystTime);

LPCTSTR szTimeFormat = (bBasicFormat) ?
                             _DATETIME_FORMAT_STD_BASIC :
                             _DATETIME_FORMAT_STD ; //Extended format
strResult.Format(szTimeFormat,
                uSystTime.wYear,
                uSystTime.wMonth,
                uSystTime.wDay,
                uSystTime.wHour,
                uSystTime.wMinute,
                uSystTime.wSecond,
                uSystTime.wMilliseconds);

return strResult;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
* $Log: KUtc2Str.cpp,v $
* Revision 1.2  2007/10/12 15:29:17  ddarko
* DateTime ISO format
*
* Revision 1.1  2007/09/15 00:56:42  ddarko
* Created
*
*****************************************************************************/
