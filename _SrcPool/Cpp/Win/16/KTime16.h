/*$Workfile: KTime16.h$: implementation file
  $Revision: 1$ $Date: 2003-09-30 08:04:46$
  $Author: Darko$

  Date and time manipulation
  Copyright: CommonSoft Inc
  1988 Darko Kolakovic
 */
/* Group=Time                                                                */

#ifndef _KTIME16_H_
    /*$Workfile: KTime16.h$ sentry                                           */
  #define _KTIME16_H_


#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

#include "KTypedef.h"

#if defined (__BORLANDC__)
  /*Borland C/C++ */
  #if ((__BORLANDC__ > 0x100) &&(__BORLANDC__ <= 0x500))
    #include <dos.h> /*_dosdate_t structure*/
    #pragma message ("   #include <dos.h>")
    #define _dosdate_t  _dosdate_t
    #define _dostime_t  _dostime_t
  #endif
#endif


#if defined(__HIGHC__)
  /*MetaWare High C/C++ Compiler*/
  #include <pldos32.h> /*PharLap's DOS Extender */
  #define _dosdate_t  _dosdate_t
  #define _dostime_t  _dostime_t
#endif

#if defined(__DMC__)
  /*Digital Mars C/C++ Compiler*/
  #define _dosdate_t  dos_date_t
  #define _dosdate_t  dos_time_t
#endif


#ifndef _dosdate_t
  /*
    Valid range of MS-DOS dates is:
      [1980-01-01, 2099-12-31]

    Example:
        #include <dos.h>
        #include <stdio.h> 
        #include <stdlib.h>

        void main()
          { 
          struct _dosdate_t dateNew;
          unsigned int iYear; 

          _dos_getdate (& dateNew);
          printf("Date : %02d-%02d-%0d\n", 
                  dateNew.month, dateNew.day, dateNew.year);

          iYear = dateNew.year;
          dateNew.year = 1988; 
          _dos_setdate (&dateNew);
          _dos_getdate (&dateNew); 

          printf("Date : %02d-%02d-%0d\n",
                  dateNew.month,dateNew.day, dateNew.year); 
          dateNew.year = iYear;
          _dos_setdate (&dateNew); 
          _dos_getdate (&dateNew); 
          printf("Date : %02d-%02d-%0d\n",
                  dateNew.month, dateNew.day, dateNew.year); 
          }

    See also: date, FILEDATEDOS, PTM, time_t, tm, KTime.h
   */
  struct _dosdate_t 
    {
    uint8  day;       /*day of the month [1, 31]           */
    uint8  month;     /*month [1,12] January = 1           */
    uint16 year;      /*calendar year [1980,2099]          */
    uint8  dayofweek; /*day of the week [0,6]=, Sunday = 0 */
    };
  #define _dosdate_t _dosdate_t
#endif

typedef struct _dosdate_t   DOSDATE; /*Calendar date                         */
typedef struct _dosdate_t* PDOSDATE; /*Pointer to date structure             */

#ifndef _dostime_t
  /*System time structure

    See also: time, FILETIMEDOS, PTM, time_t, tm, KTime.h

   */
  struct _dostime_t
    {
    uint8 hour;     /*hour of the day [0,23] [h]                   */
    uint8 minute;   /*number of minutes [0,59] [min]               */
    uint8 second;   /*number of seconds [0,59] [s]                 */
    uint8 hsecond;  /*number of hundredths of second [0,99] [s/100]*/
    };
  #define _dostime_t _dostime_t
#endif

typedef struct _dostime_t   DOSTIME; /*System time                           */
typedef struct _dostime_t* PDOSTIME; /*Pointer to time structure             */

#ifndef FILETIMEDOS
    /*MS-DOS records file times as packed 16-bit values in the following format:

          Bits  FEDCBA9876543210
                hhhhhmmmmmmsssss  where
          sssss   is number of two-seconds [0,29] [2s] (bits 0-4)
          mmmmmm  is number of minutes [0,59] [min] (bits 5-10)
          hhhhh   is hour of the day [0,23] [h] (bits 11-15)

    Note: DOS specific (DOS).

    See also: tagFILETIMEDOS
     */
  typedef uint16 FILETIMEDOS;
  #define FILETIMEDOS FILETIMEDOS
#endif

/*File time.

  Note: DOS specific (DOS).

  See also: FILETIMEDOS
 */
struct tagFILETIMEDOS 
  {
  uint16 m_nSecH: 5; /*number of two-seconds [0,29] [2s]*/
  uint16 m_nMin : 6; /*number of minutes [0,59] [min]   */
  uint16 m_nHour: 5; /*number of hours [0,23] [h]       */
 };

typedef tagFILETIMEDOS* PFILETIMEDOS; /*pointer to DOS file time structure*/

#ifndef FILEDATEDOS
  /*DOS records file dates as packed 16-bit values in the following format:

          Bits  FEDCBA9876543210
                YYYYYYYMMMMDDDDD  where
          DDDDD   is day of the month [1, 31] (bits 0-4)
          MMMM    is month [1,12] January = 1 (bits 5-8)
          YYYYYYY is number of years since 1980 (bits 9-15)

    Note: DOS specific (DOS).

    See also: tagFILEDATEDOS
   */
  typedef uint16 FILEDATEDOS;
  #define FILEDATEDOS FILEDATEDOS
#endif

/*File date.
  Valid range of MS-DOS dates is:

    [1980-01-01, 2099-12-31]

  Note: DOS specific (DOS).

  See also: FILEDATEDOS
 */
struct tagFILEDATEDOS
  {
  uint16 m_nDay  : 5; /*day of the month [1, 31]  */
  uint16 m_nMonth: 4; /*month [1,12] January = 1  */
  uint16 n_nYear : 7; /*number of years since 1980*/
  };

typedef tagFILEDATEDOS* PFILEDATEDOS; /*pointer to DOS file date structure*/



/* ///////////////////////////////////////////////////////////////////////// */
/*Macros                                                                     */
#ifndef YEAR_EPOCH_DOS
  #define YEAR_EPOCH_DOS  1980 /*DOS epoch is the time 1980-01-01T00:00:00.
                                See also: dos.h DJGPP, Borland C++           */
#endif
/* ///////////////////////////////////////////////////////////////////////// */
#endif  /*_KTIME16_H_                                                        */

/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2003-09-30 08:04:46  Darko           
 * $
 * 0  1988 Darko Kolakovic
 *****************************************************************************/
