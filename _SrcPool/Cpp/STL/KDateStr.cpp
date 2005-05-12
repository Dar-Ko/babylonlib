/*$Workfile: KDateStr.cpp$: implementation file
  $Revision: 8$ $Date: 2005-05-11 22:33:33$
  $Author: Darko$

  Format a date and time string
  Copyright: CommonSoft Inc.
  Jan 2000 Darko Kolakovic
 */

/* Group=Time                                                                */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#ifdef _DEBUG
  #ifndef _STLP_DEBUG
    #define _STLP_DEBUG 1    //Debug STLPort library
  #endif
#else
  #ifdef _STLP_DEBUG
    #undef _STLP_DEBUG
  #endif
#endif

#ifndef _STRING_
  #include <string> //std::string
  #include "KTString.h" //tstring typedef
#endif
#include <time.h> //time()

  //Declaration
tstring LocalDateToStr(TCHAR* szFormat = _T("%a %b %d %Y, %X %z"));

//LocalDateToStr()-------------------------------------------------------------
/*The function formats a date and time string.
  The formatting codes for szFormat are listed below:

    %a  Abbreviated weekday name
    %A  Full weekday name
    %b  Abbreviated month name
    %B  Full month name
    %c  Date and time representation appropriate for locale
    %d  Day of month as decimal number (01 – 31)
    %H  Hour in 24-hour format (00 – 23)
    %I  Hour in 12-hour format (01 – 12)
    %j  Day of year as decimal number (001 – 366)
    %m  Month as decimal number (01 – 12)
    %M  Minute as decimal number (00 – 59)
    %p  Current locale’s A.M./P.M. indicator for 12-hour clock
    %S  Second as decimal number (00 – 59)
    %U  Week of year as decimal number, with Sunday as first day of week (00 – 53)
    %w  Weekday as decimal number (0 – 6; Sunday is 0)
    %W  Week of year as decimal number, with Monday as first day of week (00 – 53)
    %x  Date representation for current locale
    %X  Time representation for current locale
    %y  Year without century, as decimal number (00 – 99)
    %Y  Year with century, as decimal number
    %Z, %z  Time-zone name or abbreviation; no characters if time zone is unknown
    %%  Percent sign

  Returns: STL string with date and time. String length is limited to 128 characters.

  See also: strftime()

  Note: uses Standard Template Library (STL).

  Example:

    #include <iostream>
    #include <string>
    #include "KStrings.h"
    int main(int argc, char* argv[])
      {
      extern std::string LocalDateToStr();
      std::string Date = LocalDateToStr();
      std::cout << Date << std::endl;
      return 0;
      }
 */
tstring LocalDateToStr(TCHAR* szFormat //[in]= "%a %b %d %Y, %X %z"
                                          //format-control string
                           )
{
using namespace std;
const int MAXSTRLEN = 128; //Maximum length of string
TCHAR szBuf[MAXSTRLEN];
time_t timeCurrent = time(NULL);
/*Note:
  TCHAR.H Routine | _UNICODE & _MBCS Not Defined | _MBCS Defined  | _UNICODE Defined
      _tcsftime   |        strftime              |   strftime     |     wcsftime
 */
_tcsftime(szBuf, MAXSTRLEN, szFormat, localtime(&timeCurrent));
return szBuf;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  6    Biblioteka1.5         2003-09-22 18:37:20  Darko           formatting
 *  5    Biblioteka1.4         2003-09-18 14:28:45  Darko           Unicode
 *  4    Biblioteka1.3         2003-08-07 17:18:17  Darko           replaced
 *       include names for case-sensitive compilers
 *  3    Biblioteka1.2         2002-01-29 23:20:04  Darko           Used lbraries
 *       notes
 *  2    Biblioteka1.1         2002-01-29 15:38:28  Darko           Tag update
 *  1    Biblioteka1.0         2001-07-18 23:32:08  Darko
 * $
 *****************************************************************************/
