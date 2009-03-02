/*$RCSfile: KTimeUtc.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2009/03/02 17:19:22 $
  $Author: ddarko $

  Date and time manipulators
  2004-08-19
 */

// Group=Windows

#include "stdafx.h" // MFC core and standard components

#ifndef _T
  #include "KTChar.h" //LPCTSTR typedef
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
      *  hh  is the number of complete hours that have passed since midnight;
             represented by two digits in the range [00, 24].
             The Hour 00 is the beginning of any given day and the Hour 24 is the
             end of the day. Midnight will normally be represented as 0000 or 2400.
             Hour 24  have the minute and second values zero 24:00:00.
      * mm   is the number of complete minutes that have passed since the start
             of the hour; represented by two digits in the range [00, 59].
      * ss   is the number of complete seconds since the start of the minute;
             represented by two digits in the range [00, 60].
             Value 60 allows to add a leap second to
             the Coordinated Universal Time (UTC).
      * ffff is the decimal fraction of the preceding time unit (hour, minute or
             second); it is represented by any previously agreed number of digits
             bigger or equal to one. Decimal sign is comma (,)  or dot (.),
             but comma is preferred.
      * Inserting time designator T is preferred way to store date and time
        in a single field.

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
if (bBasicFormat)
  {
  LPCTSTR szTimeFormat = _T("%0.4d%0.2d%0.2dT%0.2d%0.2d%0.2d,%0.3d");
  strResult.Format(szTimeFormat,
                  uSystTime.wYear,
                  uSystTime.wMonth,
                  uSystTime.wDay,
                  uSystTime.wHour,
                  uSystTime.wMinute,
                  uSystTime.wSecond,
                  uSystTime.wMilliseconds);
  }
else //Extended format
  {
  LPCTSTR szTimeFormat = _T("%0.4d-%0.2d-%0.2dT%0.2d:%0.2d:%0.2d,%0.3d");
  strResult.Format(szTimeFormat,
                  uSystTime.wYear,
                  uSystTime.wMonth,
                  uSystTime.wDay,
                  uSystTime.wHour,
                  uSystTime.wMinute,
                  uSystTime.wSecond,
                  uSystTime.wMilliseconds);
  }
return strResult;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
* $Log: KTimeUtc.cpp,v $
* Revision 1.1  2009/03/02 17:19:22  ddarko
* Moved from local repository
*
*****************************************************************************/
