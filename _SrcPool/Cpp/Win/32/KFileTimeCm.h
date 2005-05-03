/*$Workfile: KFileTimeCm.h$: header file
  $Revision: 3$ $Date: 2004-10-01 22:34:53$
  $Author: Darko$

  FILETIME comparasion operators
  Copyright: CommonSoft Inc.
  Dec 98 Darko Kolakovic
 */
/* Group=Time                                                                */

#ifndef _KFILETIMECM_H_
    //$Workfile: KFileTimeCm.h$ sentry
  #define _KFILETIMECM_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Inlines

//operator <()-----------------------------------------------------------------
/*Note: Microsoft Windows specific (Win).
 */
inline BOOL operator <(const FILETIME& ftTime1, const FILETIME& ftTime2)
{
if (::CompareFileTime(&ftTime1,&ftTime2)  < 0)
  return TRUE;
return FALSE;
}

//operator ==()----------------------------------------------------------------
/*Note: Microsoft Windows specific (Win).
 */
inline BOOL operator ==(const FILETIME& ftTime1, const FILETIME& ftTime2)
{
if (::CompareFileTime(&ftTime1,&ftTime2)  == 0)
  return TRUE;
return FALSE;
}

//operator >()-----------------------------------------------------------------
/*Note: Microsoft Windows specific (Win).
 */
inline BOOL operator >(const FILETIME& ftTime1, const FILETIME& ftTime2)
{
if (::CompareFileTime(&ftTime1,&ftTime2)  > 0)
  return TRUE;
return FALSE;
}
///////////////////////////////////////////////////////////////////////////////
#endif //_KFILETIMECM_H_
/*****************************************************************************
 * $Log: 
 *  3    Biblioteka1.2         2004-10-01 22:34:53  Darko           stdafx.h
 *  2    Biblioteka1.1         2003-09-24 12:27:51  Darko           formatting
 *  1    Biblioteka1.0         2002-03-13 00:40:44  Darko           
 * $
 *****************************************************************************/
