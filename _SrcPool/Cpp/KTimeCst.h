/*$Workfile:  KTimeCst.h$: header file
  $Revision: 1.1 $ $Date: 2009/03/02 17:19:22 $
  $Author: ddarko $

  Time and Date - Constants
  Copyright: CommonSoft Inc
  2007-10-11 Darko Kolakovic
  Jan. 96  D. Kolakovic
 */

#ifndef _KTIMECST_H_
    //$Workfile: KTimeCst.h$ sentry
  #define _KTIMECST_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

//-----------------------------------------------------------------------------
// Group=Constants

  //Time

#ifdef __cplusplus

  const unsigned CST_SpMIN    = 60; //second per minute
  const unsigned CST_MINpH    = 60; //minute per hour
  const unsigned CST_HpDAY    = 24; //hours per day
  const unsigned CST_SpH = (CST_MINpH*CST_nSpMIN) //seconds per hour [s/h]
  const unsigned CST_SpDAY = 60*60*24;     //seconds per day [s/day]
  const unsigned CST_DAYpWEEK  =   7; //number of days in a week
  const unsigned CST_DAYpYEAR  = 365; //number of days in a year
  const unsigned CST_DAYpLYEAR = 366; //number of days in a leap year
  const unsigned CST_WEEKpYEAR =  52; //number of weeks in a year
  const unsigned CST_MpYEAR    =  12; //number of months in a year
#else  //!__cplusplus

  #define CST_SpMIN        60    //second per minute
  #define CST_MINpH        60    //minute per hour
  #define CST_HpDAY        24    //hours per day
  #define CST_SpH        (60*60) //seconds per hour [s/h]
  #define CST_SpDAY (CST_SpH*24) //seconds per day [s/day]
  #define CST_DAYpWEEK      7    //number of days in a week
  #define CST_DAYpYEAR    365    //number of days in a year
  #define CST_DAYpLYEAR   366    //number of days in a leap year
  #define CST_WEEKpYEAR    52    //number of weeks in a year
  #define CST_MpYEAR       12    //number of months in a year

#endif  //__cplusplus

///////////////////////////////////////////////////////////////////////////////
#endif  //_KTIMECST_H_
/*****************************************************************************
 * $Log: KTimeCst.h,v $
 * Revision 1.1  2009/03/02 17:19:22  ddarko
 * Moved from local repository
 *
 *****************************************************************************/
