/*$Workfile: H:\_SrcPool\Cpp\KFileHnd.inl$: header file
  $Revision: 1.1 $ $Date: 2002/09/06 22:14:10 $
  $Author: ddarko $

  File I/O helper functions
  Copyright: CommonSoft Inc.
  May 95 Darko Kolakovic
 */ 

#ifndef __KFILEHND_INL_
    //KFileHnd.inl sentry
  #define __KFILEHND_INL_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif


#ifndef __AFXWIN_H__
  #include <Windows.h>
#endif
#ifdef _DEBUG
  #ifdef _WIN32
    #include <Assert.h>
  #endif
#endif
///////////////////////////////////////////////////////////////////////////////
//Inline functions

//IsFileInPath()---------------------------------------------------------------
#ifndef UNICODE
/*Checks if file is accessible. The lpszName parameter cannot contain wildcard
  characters. Function searches for a matching file in the following directories,
  in the order shown:

    1.	the directory from which the application loaded.
    2.	the current directory.
    3.	Windows 95: The Windows system directory.
        Windows NT: The 32-bit and 16-bit Windows system directory.
    4.	the Windows directory.
    5.	the directories that are listed in the PATH environment variable.

  Returns: TRUE if the function succeeds, or FALSE if the function fails.
  To get extended error information, call GetLastError.

  Note: Microsoft Windows specific (Win32 and Win16).
 */
inline BOOL IsFileInPath(LPCSTR lpszName)
{
/*Note:
  OpenFile() is provided for compatibility with 16-bit versions of Windows.
  In particular, the OpenFile function cannot open a named pipe.
  Win32-based applications should use the CreateFile function.
  The OpenFile() function does not support Unicode filenames.
  A pathname string is limited to OFS_MAXPATHNAME characters (128 characters).
 */
#ifdef _DEBUG
  #ifdef _WIN32
    assert(lpszName != NULL);
  #endif
#endif

OFSTRUCT ofs;
return (OpenFile(lpszName, &ofs, OF_EXIST) != HFILE_ERROR);
}

#else
  #pragma message("error: Unicode filenames are not supported in IsFileInPath()" __FILE__)
#endif //UNICODE

//////////////////////////////////////////////////////////////////////////////
#endif  //__KFILEHND_INL_
/*****************************************************************************
 * $Log: 
 *  6    Biblioteka1.5         1/29/02 10:21:00 PM  Darko           Used lbraries
 *       notes 
 *  5    Biblioteka1.4         1/29/02 2:39:51 PM   Darko           Tag update
 *  4    Biblioteka1.3         8/19/01 10:53:52 PM  Darko           Butyfier
 *  3    Biblioteka1.2         7/11/01 9:51:31 PM   Darko           
 *  2    Biblioteka1.1         6/8/01 10:50:44 PM   Darko           VSS
 *  1    Biblioteka1.0         8/13/00 2:56:31 PM   Darko           
 * $
 *****************************************************************************/
