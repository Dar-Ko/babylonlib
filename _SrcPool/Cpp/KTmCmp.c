/*$Workfile: KTmCmp.c$: implementation file
  $Revision: 2$ $Date: 10/01/2003 9:53:03 PM$
  $Author: Darko Kolakovic$
 
  Compares two date/time values
  Copyright: CommonSoft Inc
  Jan 2003 Darko Kolakovic
*/

/* Group=Time                                                                */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#ifdef _DEBUG
  static char THIS_FILE[] = __FILE__;
#endif

#include "KTime.h" /*tm struct                                               */

/*TmCmp()--------------------------------------------------------------------*/

/*Compares two dates to determine if they are the same.
  Result is one of following
    - < 0 *ptmTime1 less than *ptmTime2 
      = 0 *ptmTime1 identical to *ptmTime2 
      > 0 *ptmTime1 greater than *ptmTime2 

  Structure tm has following members as defined in time.h header file:
      struct tm 
        {
        int tm_sec;  //seconds after the minute [0, 61]
        int tm_min;  //minutes after the hour   [0, 59]
        int tm_hour; //hours after midnight     [0, 23]
        int tm_mday; //day of the month         [1, 31]
        int tm_mon;  //month of the year        [0, 11] January = 0
        int tm_year; //years since 1900         [INT_MIN, INT_MAX]
        int tm_wday; //day of the week          [0,  6] Sunday = 0
        int tm_yday; //day of the year          [0,365] 1. January = 0
        int tm_isdst;//daylight savings time flag. Positive if daylight 
                     //saving time is in effect; 0 if daylight saving time 
                     //is not in effect; negative if status of daylight 
                     //saving time is unknown. 
        }

  Note: ISO C: tm_sec ranges from 0 to 61 to accomodate as many as two leap
        seconds.
        tm_yday ranges from 0 to 365 to accomodate one leap day.

  Returns: zero if the strings are identical. Returns a positive value if 
  the first date is greater than that pointed to by ptmTime2. Returns 
  a negative value if the date pointed to by ptmTime1 is less than that 
  pointed to by ptmTime2.

  Note: if pointers are not valid, result is not certain.

  See also: time.h
  */
int TmCmp(const PTM ptmTime1,/*[in] pointer tm the first date to be compared*/
          const PTM ptmTime2 /*[in] pointer tm the second date to be compared*/
         )
{
if (ptmTime1->tm_year != ptmTime2->tm_year)
  return ptmTime1->tm_year - ptmTime2->tm_year;

if (ptmTime1->tm_mon != ptmTime2->tm_mon)
	return ptmTime1->tm_mon - ptmTime2->tm_mon;

if (ptmTime1->tm_mday != ptmTime2->tm_mday)
  return ptmTime1->tm_mday - ptmTime2->tm_mday;

if (ptmTime1->tm_hour != ptmTime2->tm_hour)
  return ptmTime1->tm_hour - ptmTime2->tm_hour;

if (ptmTime1->tm_min != ptmTime2->tm_min)
  return ptmTime1->tm_min - ptmTime2->tm_min;

if (ptmTime1->tm_sec != ptmTime2->tm_sec)
  return ptmTime1->tm_sec - ptmTime2->tm_sec;

return 0;
}

/* ///////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log: 
 *  2    Biblioteka1.1         10/01/2003 9:53:03 PMDarko Kolakovic replaced tm*
 *       with PTM
 *  1    Biblioteka1.0         08/01/2003 3:26:22 PMDarko Kolakovic 
 * $
 *****************************************************************************/
