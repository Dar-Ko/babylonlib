/*$Workfile: KFileTimeCm.h$: header file
  $Revision: 1.2 $ $Date: 2002/09/10 15:22:21 $
  $Author: ddarko $

  FILETIME comparasion operators
  Copyright: CommonSoft Inc.
  Dec 98 Darko Kolakovic
 */

#ifndef _KFILETIMECM_H_
    //KFileTimeCm.h sentry
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
