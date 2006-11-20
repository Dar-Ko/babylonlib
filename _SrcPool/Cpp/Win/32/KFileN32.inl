/*$Workfile: KFileN32.inl$: header file
  $Revision: 1.1 $ $Date: 2006/11/20 19:34:24 $
  $Author: ddarko $

  File Name handler (Win32)
  Copyright: CommonSoft Inc.
  Jan 93 Win3.1 Darko Kolakovic
  May 98 Win32 version D.K.
 */

#ifndef _KFILEN32_INL_
    //$Workfile: KFileN32.inl$ sentry
  #define _KFILEN32_INL_

#ifndef WIN32    //Windows 32b application
  #pragma error ("Requred Windows 32b")
#endif

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileName Inlines

//::CreateDirectory()----------------------------------------------------------
/*The CreateDirectory function creates a new directory.

  Returns: true if the function succeeds. If the function fails, the return
  value is false. To get extended error information, call GetLastError().

  Note: Microsoft Windows specific (Win32).
 */
inline bool CFileName::CreateDirectory() const
{
return ::CreateDirectory(Canonical(),   // pointer to a directory path string
                          NULL          // pointer to a security descriptor
                          );
}

//::ChangeDirectory()----------------------------------------------------------
/*The SetCurrentDirectory function changes the current directory for the
  current process.

  Returns: true if the function succeeds. If the function fails, the return
  value is false. To get extended error information, call GetLastError().
 */
inline bool CFileName::ChangeDirectory() const
{
return ::SetCurrentDirectory(Canonical());
}

//::IsFileFound()--------------------------------------------------------------
/*Checks if file is accesibile.

  Returns: true if the function succeeds, or  false if the function fails.
  To get extended error information, call GetLastError().

  Note:
  OpenFile() is provided for compatibility with 16-bit versions of Windows.
  In particular, the OpenFile function cannot open a named pipe.
  Win32-based applications should use the CreateFile function.
 */
inline bool CFileName::IsFileFound() const
{
#pragma TODO(CreateFile() instead OpenFile)
OFSTRUCT ofs;
ofs.cBytes = sizeof ofs;
return ::OpenFile(Canonical(), &ofs, OF_EXIST) != HFILE_ERROR;
}

//::IsShortcut()--------------------------------------------------------------
/*Verifies if a file is a shortcut file.

  Returns: true if file name have extension same as Window's shortcut file (.Lnk).
  To obtain shorcut's target call ::GetShortcutTarget().

  Note: Microsoft Windows specific (Win32).
 */
inline bool CFileName::IsShortcut() const
{
if (!m_strExt.IsEmpty())
  {
    //Validate extension
  if (m_strExt == &g_szExtLnk[1])
    return true;
  }
return false;
}

//::CopyFile()-----------------------------------------------------------------
/*The CopyFile function copies an existing file to a new file. If bFailIfExists
  parameter is true and the new file already exists, the function fails.
  If this parameter is false and the new file already exists, the function
  overwrites the existing file and succeeds.
 */
inline void CFileName::CopyFile(LPCTSTR lpNewFileName, //pointer to filename to copy to
                         bool    bFailIfExists  //flag for operation if file exists
                         ) const
{
::CopyFile(Canonical(),CFileName::Canonical(lpNewFileName,false), bFailIfExists);
}

//::Remove()-----------------------------------------------------------------
/*The Remove() function deletes an existing file or directory.

 Note: Windows 95: The DeleteFile function deletes a file even if it is open
 for normal I/O or as a memory-mapped file. To prevent loss of data, close
 files before attempting to delete them.
 Windows NT: The DeleteFile function fails if an application attempts to
 delete a file that is open for normal I/O or as a memory-mapped file.
 To close an open file, use the CloseHandle function.
 */
inline void CFileName::Remove() const
{
if (!::DeleteFile(Canonical()))
  ::RemoveDirectory(Canonical());
}

///////////////////////////////////////////////////////////////////////////////
#endif  //_KFILEN32_INL_
/*****************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2002-08-27 23:35:32  Darko           Deleted
 *       IS_FILENAME_DELIM
 *  1    Biblioteka1.0         2002-08-27 17:04:45  Darko Kolakovic
 * $
 * May 98 Win32 version D.K.
 * Jan 93 Win3.1 D.K.
 *****************************************************************************/
