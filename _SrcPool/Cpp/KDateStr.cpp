/*$Workfile: H:\_SrcPool\Cpp\KDateStr.cpp$: implementation file
  $Revision: 1.1 $ $Date: 2002/09/06 22:09:08 $
  $Author: ddarko $

  Format a date and time string
  Copyright: CommonSoft Inc.
  Jan 2000 Darko Kolakovic
 */

/* Group=Strings                                                             */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#ifndef _STRING_
  #include <string> //std::string
#endif
#include <Time.h> //time()

  //Declaration
std::string LocalDateToStr(char* szFormat = "%a %b %d %Y, %X %z");

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

  Returns: STL string with date and time.

  See also: strftime()

  Note: uses Standard Template Library (STL).

  Example:

    #include <IOStream>
    #include <String>
    #include "KStrings.h"
    int main(int argc, char* argv[])
      {
      extern std::string LocalDateToStr();
      std::string Date = LocalDateToStr();
      std::cout << Date << std::endl;
 	  return 0;
      }
 */
std::string LocalDateToStr(char* szFormat //[in]= "%a %b %d %Y, %X %z" 
                                          //format-control string
                           )
{
using namespace std;
char szBuf[128];
time_t timeCurrent = time(NULL);
/*Note:
  TCHAR.H Routine | _UNICODE & _MBCS Not Defined | _MBCS Defined  | _UNICODE Defined 
      _tcsftime   |        strftime              |   strftime     |     wcsftime 
 */
_tcsftime(szBuf, sizeof(szBuf), szFormat, localtime(&timeCurrent));
return szBuf;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  3    Biblioteka1.2         1/29/02 10:20:04 PM  Darko           Used lbraries
 *       notes 
 *  2    Biblioteka1.1         1/29/02 2:38:28 PM   Darko           Tag update
 *  1    Biblioteka1.0         7/18/01 10:32:08 PM  Darko           
 * $
 *****************************************************************************/
