/*$Workfile: KFileHnd.inl$: header file
  $Revision: 1.3 $ $Date: 2003/01/28 05:38:05 $
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
 *  6    Biblioteka1.5         29/01/2002 10:21:00 PMDarko           Used lbraries
 *       notes 
 *  5    Biblioteka1.4         29/01/2002 2:39:51 PMDarko           Tag update
 *  4    Biblioteka1.3         19/08/2001 10:53:52 PMDarko           Butyfier
 *  3    Biblioteka1.2         11/07/2001 9:51:31 PMDarko           
 *  2    Biblioteka1.1         08/06/2001 10:50:44 PMDarko           VSS
 *  1    Biblioteka1.0         13/08/2000 2:56:31 PMDarko           
 * $
 *****************************************************************************/
