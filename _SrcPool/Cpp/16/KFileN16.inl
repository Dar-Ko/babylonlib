/*$Workfile: KFileN16.inl$: header file
  $Revision: 1$ $Date: 8/27/02 5:04:41 PM$
  $Author: Darko Kolakovic$

  File Name handler (Win16)
  Copyright: CommonSoft Inc.
  Jan 93 Darko Kolakovic
  May 98 Created Win32 version D.K.
 */

#ifndef _KFILENAME16_INL_
    //KFileN16.inl sentry
  #define _KFILENAME16_INL_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#include <dir.h>  //ffblk struct
/////////////////////////////////////////////////////////////////////////////
// CFileName Inlines

//::CreateDirectory()----------------------------------------------------------
/*The CreateDirectory function creates a new directory. 
  If the function succeeds, the return value is TRUE. If the function fails, 
  the return value is FALSE. To get extended error information, call GetLastError. 
 */
inline BOOL CFileName::CreateDirectory() const
{
return (mkdir(Canonical()) == 0);
}

//::ChangeDirectory()----------------------------------------------------------
/*The SetCurrentDirectory function changes the current directory for the 
  current process.
  If the function succeeds, the return value is TRUE. If the function fails, 
  the return value is FALSE. To get extended error information, call GetLastError. 
 */
inline BOOL CFileName::ChangeDirectory() const
{
return (chdir(Canonical()) == 0);
}

//::Remove()-----------------------------------------------------------------
/*The Remove() function deletes an existing file or directory.
 */
inline void CFileName::Remove() const
{
if (remove(Canonical()) != 0)
  rmdir(Canonical());
}

///////////////////////////////////////////////////////////////////////////////
#endif  //_KUFILENAME16_INL_
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         8/27/02 5:04:41 PM   Darko Kolakovic 
 * $
 * May 98 Created Win32 version D.K.
 * Jan 93 Darko Kolakovic
 *****************************************************************************/
