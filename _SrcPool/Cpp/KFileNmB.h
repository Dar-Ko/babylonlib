/*$Workfile: KFileNmB.h$: header file
  $Revision: 1.1 $ $Date: 2002/09/06 22:14:10 $
  $Author: ddarko $

  File Name Browser
  Copyright: CommonSoft Inc.
  May 94 Darko Kolakovic
 */

#ifndef _KFILENMB_H_
    //KFileNmB.h sentry
  #define _KFILENMB_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifndef WIN32    //Windows 32b application
  #pragma error ("Requred Windows 32b")
#endif

///////////////////////////////////////////////////////////////////////////////
//CFileNameBrowser class encapsualtes WIN32_FIND_DATA structure. Class searches
//a directory for a file. The file name string specifies a valid directory
//or path and filename, which can contain wildcard characters (* and ?).
//This string must not exceed MAX_PATH characters.
//
//Note: Microsoft Windows specific (Win).
class CFileNameBrowser
{
  // Construction
public:
  CFileNameBrowser(LPCTSTR szFileName);
 ~CFileNameBrowser();

// Attributes
private:
  WIN32_FIND_DATA m_FindData; //The WIN32_FIND_DATA structure describes a file found
                              //by the FindFirstFile or FindNextFile function.

  HANDLE m_Handle;  //a search handle used in a subsequent call
                    //to FindNextFile or FindClose.
  BOOL  m_bDone;    //signals that iteration is done

// Operations
public:
  operator LPCTSTR() const;
  BOOL IsFileFound() const;
  BOOL IsLastFileFound() const;
  LPCTSTR operator ++();
  const WIN32_FIND_DATA& FindData() const;
  DWORD GetFileAttributes() const;
  BOOL  IsDirectory() const;

};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//::operator const LPTSTR()----------------------------------------------------
/*Returns a null-terminated string that is the file name found.
 */
inline CFileNameBrowser::operator LPCTSTR() const
{
return FindData().cFileName;
}

//::IsFileFound()-------------------------------------------------------------
/*Returns TRUE if file has been found
 */
inline BOOL CFileNameBrowser::IsFileFound() const
{
return (m_Handle != INVALID_HANDLE_VALUE);
}

//::IsLastFileFound()----------------------------------------------------------
/*Returns TRUE if the last file in the directory has been found
 */
inline BOOL CFileNameBrowser::IsLastFileFound() const
{
return m_bDone;
}

//::FindData()-----------------------------------------------------------------
/*Returns information about file found
 */
inline const WIN32_FIND_DATA& CFileNameBrowser::FindData() const
{
return m_FindData;
}

//::GetFileAttributes()--------------------------------------------------------
/*Returns the file attributes of the file found.
  The attributes can be one or more of the following values:

    FILE_ATTRIBUTE_ARCHIVE       file or directory is an archive file or
                                 directory. Applications use this attribute to
                                 mark files for backup or removal.
    FILE_ATTRIBUTE_COMPRESSED    file or directory is compressed.
    FILE_ATTRIBUTE_DIRECTORY     handle identifies a directory.
    FILE_ATTRIBUTE_ENCRYPTED     file or directory is encrypted.
    FILE_ATTRIBUTE_HIDDEN        file or directory is hidden.
    FILE_ATTRIBUTE_NORMAL        file or directory has no other attributes set.
    FILE_ATTRIBUTE_OFFLINE       file data is not immediately available. This
                                 attribute indicates that the file data has been
                                 physically moved to offline storage.
                                 This attribute is used by the hierarchical
                                 storage management software in Windows 2000.
    FILE_ATTRIBUTE_READONLY      file or directory is read-only.
    FILE_ATTRIBUTE_REPARSE_POINT file has an associated reparse point.
    FILE_ATTRIBUTE_SPARSE_FILE   file is a sparse file.
    FILE_ATTRIBUTE_SYSTEM        file or directory is part of the operating system
                                 or is used exclusively by the operating system.
    FILE_ATTRIBUTE_TEMPORARY     file is being used for temporary storage.
 */
inline DWORD CFileNameBrowser::GetFileAttributes() const
{
return FindData().dwFileAttributes;
}

//::IsDirectory()--------------------------------------------------------------
/*Returns TRUE if file found is a directory.
 */
inline BOOL CFileNameBrowser::IsDirectory() const
{
return ((GetFileAttributes() & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY);
}

///////////////////////////////////////////////////////////////////////////////
#endif  //_KFILENMB_H_
