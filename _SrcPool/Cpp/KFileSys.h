/*$Workfile: KFileSys.h$: header file
  $Revision: 3$ $Date: 2003-08-25 00:27:02$
  $Author: Darko$

  File System helpers
  Copyright: CommonSoft Inc.
  Dec 98 Darko Kolakovic
 */

#ifndef _KFILESYS_H_
  //KFileSys.h sentry
  #define _KFILESYS_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

/* ///////////////////////////////////////////////////////////////////////   */
/* //Constants                                                               */


#ifdef WIN32                          /*Windows 32b , Win9x, WinNT, Win2k    */
  #define DRIVE_DELIM  _T(':')        /*Separates drive name and directory   */
  #define PATH_END     _T(";")        /*Separates path components            */
  #define PATHDELIM    _T('\\')       /*Delimits directory and filename      */
  #define FILEEXTDELIM _T('.')        /*Separates filename base and extension*/
  #define IS_PATH_CASESENSITIVE false
#endif

#ifdef __MSDOS__                      /*MS-DOS                               */
  #define DRIVE_DELIM  _T(':')        /*Separates drive name and directory   */
  #define PATH_END     _T(";")        /*Separates path components            */
  #define PATHDELIM    _T('\\')       /*Delimits directory and filename      */
  #define FILEEXTDELIM _T('.')        /*Separates filename base and extension*/
  #define IS_PATH_CASESENSITIVE false
#endif

#ifdef WIN16                          /*Windows 16b, Win3.1                  */
  #define DRIVE_DELIM  _T(':')        /*Separates drive name and directory   */
  #define PATH_END     _T(";")        /*Separates path components            */
  #define PATHDELIM    _T('\\')       /*Delimits directory and filename      */
  #define FILEEXTDELIM _T('.')        /*Separates filename base and extension*/
  #define IS_PATH_CASESENSITIVE false
#endif

#ifdef __VMS__                           /*Digital OpenVMS                   */
  #define PATH_END     _T(",")           /*Separates path components         */
  #define PATHDELIM    _T('/')           /*Delimits directory and filename   */
  #define IS_PATH_CASESENSITIVE false
#endif

#ifdef __unix__                          /*UNIX                              */
  #define PATH_END     _T(":")           /*Separates path components         */
  #define PATHDELIM    _T('/')           /*Delimits directory and filename   */
  #define IS_PATH_CASESENSITIVE true
#endif

#ifdef __OS2__                        /*OS/2 using EMX/GCC                   */
  #define PATH_END     _T(";")        /*Separates path components            */
  #define PATHDELIM    _T('\\')       /*Delimits directory and filename      */
  #define FILEEXTDELIM _T('.')        /*Separates filename base and extension*/
#endif

#ifndef MAXPATH_FAT32
  /*Maximum length of full path for FAT32 file system.
    
    Note: Microsoft Windows API uses this value as the limit for
    the path size.
    
    See also: _MAX_PATH, MAX_PATH, <stdlib.h>, Path Field Limits
   */
  #define MAXPATH_FAT32 260
#endif

#ifndef MAXPATH_NTFS
  /*Maximum length of full path for NTFS file system.*/
  #define MAXPATH_NTFS 32768
#endif
/* ///////////////////////////////////////////////////////////////////////// */
/* //Macros                                                                  */

/*Test if a character is one of Windows file name delimiters:
  '\', '/' or ':'.

  Returns: true if a character is a file name delimiter; otherwise returns
  false.
 */
#define IS_FILENAME_DELIM_WIN(c)    ( (c) == _T('\\') || (c) == _T('/') || (c) == _T(':') )

/* ///////////////////////////////////////////////////////////////////////// */
/* //Inlines                                                                 */
#ifdef __cplusplus
//-----------------------------------------------------------------------------
/*Verifies if a character is a file path delimiter.

  Returns: true if the character is one of the recognized delimeters or false
  if it is not.
 */
inline bool IsPathDelim(const TCHAR ch //[in] path delimiter
                       )
{
return (ch == _T('\\') || ch == _T('/'));
}
#endif /*__cplusplus*/


/* ///////////////////////////////////////////////////////////////////////// */
#endif //_KFILESYS_H_
/*****************************************************************************
 * $Log:
 *  3    Biblioteka1.2         2003-08-25 00:27:02  Darko           Renamed
 *       IS_FILENAME_DELIM
 *  2    Biblioteka1.1         2002-08-27 22:34:54  Darko
 *       IS_FILENAME_DELIM
 *  1    Biblioteka1.0         2002-07-18 20:57:46  Darko Kolakovic
 * $
 *****************************************************************************/