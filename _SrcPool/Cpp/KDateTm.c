/*$Workfile: KDateTm.c$: implementation file
  $Revision: 3$ $Date: 2003-09-23 16:12:51$
  $Author: Darko$

  Converts DOS date and time to Unix time
  Copyright: CommonSoft Inc
  Jan 2003 Darko Kolakovic
*/

/* Group=Time                                                                */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#ifdef _DEBUG
  static char THIS_FILE[] = __FILE__;
#endif
#include "KTime.h"  /*date, time struct                                        */

/*DatetoTm()-------------------------------------------------------------------*/

/*Converts date and time to tm structure. Day of the week or year are not
  converted. Daylight savings time (DST) flag is set as unknown.

  Returns: pointer to the tm structure.

  Note: if pointers are not valid, result is not certain.

  See also: time.h, dos.h
  */
PTM DatetoTm(PTM ptmTarget, /*[out] pointer to resulting tm structure          */
             const PDate pdateSource, /*[in] date to convert;  year represents
                                        current year                           */
             const PTime ptimeSource  /*[in] time to convert                   */
             )
{
ptmTarget->tm_sec   = ptimeSource->ti_sec;
ptmTarget->tm_min   = ptimeSource->ti_min;
ptmTarget->tm_hour  = ptimeSource->ti_hour;

ptmTarget->tm_mday  = pdateSource->da_day;
ptmTarget->tm_mon   = pdateSource->da_mon - 1;
ptmTarget->tm_year  = pdateSource->da_year - YEAR_EPOCH_TM;

ptmTarget->tm_wday  = -1; /*day of the week [0,  6] Sunday = 0     */
ptmTarget->tm_yday  = -1; /*day of the year [0,365] 1. January = 0 */
ptmTarget->tm_isdst = -1; /*daylight saving time is unknown;
                            enabled = 1, disabled = 0, unknown = -1*/

return ptmTarget;
}

/* ///////////////////////////////////////////////////////////////////////// */
/*  Structure tm has following members as defined in time.h header file:
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

 */
/*****************************************************************************
 * $Log:
 *  3    Biblioteka1.2         2003-09-23 16:12:51  Darko           AtoI()
 *  2    Biblioteka1.1         2003-09-22 21:25:50  Darko           formatting
 *  1    Biblioteka1.0         2003-01-10 21:53:25  Darko Kolakovic
 * $
 *****************************************************************************/
