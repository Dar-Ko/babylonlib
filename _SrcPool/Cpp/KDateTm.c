/*$Workfile: KDateTm.c$: implementation file
  $Revision: 1$ $Date: 10/01/2003 9:53:25 PM$
  $Author: Darko Kolakovic$
 
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
             const PDATE pdateSource, /*[in] date to convert;  year represents
                                        current year                           */
             const PTIME ptimeSource  /*[in] time to convert                   */
             )
{
ptmTarget->tm_sec   = ptimeSource->ti_sec;
ptmTarget->tm_min   = ptimeSource->ti_min;
ptmTarget->tm_hour  = ptimeSource->ti_hour;

ptmTarget->tm_mday  = pdateSource->da_day;
ptmTarget->tm_mon   = pdateSource->da_mon - 1;
ptmTarget->tm_year  = pdateSource->da_year - YEAR_TM_BASE;

ptmTarget->tm_wday  = -1; /*day of the week [0,  6] Sunday = 0     */
ptmTarget->tm_yday  = -1; /*day of the year [0,365] 1. January = 0 */
ptmTarget->tm_isdst = -1; /*daylight saving time is unknown; 
                            enabled = 1, disabled = 0, unknown = -1*/

return ptmTarget;
}

/* ///////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         10/01/2003 9:53:25 PMDarko Kolakovic 
 * $
 *****************************************************************************/
