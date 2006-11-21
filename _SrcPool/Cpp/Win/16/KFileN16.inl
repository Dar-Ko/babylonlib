/*$Workfile: KFileN16.inl$: header file
  $Revision: 2$ $Date: 2005-05-24 12:22:03$
  $Author: Darko Kolakovic$

  File Name handler (Win16)
  Copyright: CommonSoft Inc.
  Jan 93 Darko Kolakovic
  May 98 Created Win32 version D.K.
 */

#ifndef _KFILENAME16_INL_
    //$Workfile: KFileN16.inl$ sentry
  #define _KFILENAME16_INL_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#include <dir.h>  //mkdir()
/////////////////////////////////////////////////////////////////////////////
// CFileName Inlines

//::CreateDirectory()----------------------------------------------------------
/*The CreateDirectory() function creates a new directory.

  Returns: true if the function succeeds. If the function fails, the return
  value is false. To get extended error information, call GetLastError().

  Note: Microsoft Windows specific (Win16),
        Microsoft DOS specific (DOS).
 */
inline bool CFileName::CreateDirectory() const
{
return (mkdir(Canonical()) == 0);
}

//::ChangeDirectory()----------------------------------------------------------
/*This function changes the current directory for the current process.

  Returns: true if the function succeeds. If the function fails, the return
  value is false. To get extended error information, call GetLastError().
 */
inline bool CFileName::ChangeDirectory() const
{
return (chdir(Canonical()) == 0);
}

//::Remove()-----------------------------------------------------------------
/*The Remove() function deletes an existing file or directory.

  Note: Microsoft Windows specific (Win16),
        Microsoft DOS specific (DOS).
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
 *  1    Biblioteka1.0         2002-08-27 17:04:41  Darko Kolakovic
 * $
 * May 98 Created Win32 version D.K.
 * Jan 93 Darko Kolakovic
 *****************************************************************************/
