/*$Workfile: H:\_SrcPool\Cpp\KFileSys.h$: header file
  $Revision: 2$ $Date: 8/27/02 11:34:54 PM$
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


#ifdef WIN32                             /*Windows 32b , Win9x, WinNT, Win2k */
  #define DRIVE_DELIM  _T(':')           /*Separates drive name and directory*/
  #define PATH_END     _T(";")           /*Separates path components         */
  #define PATHDELIM    _T('\\')          /*Delimits directory and filename   */
  #define IS_PATH_CASESENSITIVE false
#endif

#ifdef __MSDOS__                         /*MS-DOS                            */
  #define DRIVE_DELIM  _T(':')           /*Separates drive name and directory*/
  #define PATH_END     _T(";")           /*Separates path components         */
  #define PATHDELIM    _T('\\')          /*Delimits directory and filename   */
  #define IS_PATH_CASESENSITIVE false
#endif

#ifdef WIN16                             /*Windows 16b, Win3.1               */
  #define DRIVE_DELIM  _T(':')           /*Separates drive name and directory*/
  #define PATH_END     _T(";")           /*Separates path components         */
  #define PATHDELIM    _T('\\')          /*Delimits directory and filename   */
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

#ifdef __OS2__                           /*OS/2 using EMX/GCC                */
  #define PATH_END     _T(";")           /*Separates path components         */
  #define PATHDELIM    _T('\\')          /*Delimits directory and filename   */
#endif

/* ///////////////////////////////////////////////////////////////////////// */
/* //Macros                                                                  */

/*Test if a character is one of Windows file name delimiters: 
  '\', '/' or ':'.

  Returns: true if a character is a file name delimiter; otherwise reurns false
 */
#define IS_FILENAME_DELIM(c)    ( (c) == _T('\\') || (c) == _T('/') || (c) == _T(':') )

/* ///////////////////////////////////////////////////////////////////////// */
#endif //_KFILESYS_H_
/*****************************************************************************
 * $Log: 
 *  2    Biblioteka1.1         8/27/02 11:34:54 PM  Darko          
 *       IS_FILENAME_DELIM
 *  1    Biblioteka1.0         7/18/02 9:57:46 PM   Darko Kolakovic 
 * $
 *****************************************************************************/