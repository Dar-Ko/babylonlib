/*$RCSfile: KErrnoFromLastError.cpp,v $: implementation file
  $Revision: 1.4 $ $Date: 2012/02/22 15:08:20 $
  $Author: ddarko $

  Mapping between errno and Windows error codes
  Note: Microsoft Windows specific (Win).
  Copyright: CommonSoft Inc
  2002-11-21 Darko Kolakovic
 */

// Group=Windows

#ifdef _WIN32

#ifdef _USE_ATL
  //Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)
  //or preprocessor reports unpaired #endif directive

  #include "stdafx.h" //Standard system header files
#else
  #include <windows.h>
#endif

#include <errno.h>

#if defined _ATL_VER
  #include "KTraceAtl.h"
#endif

#ifndef TRACE
  #ifndef _T
    #include "KTChar.h"
  #endif
  #include "KTrace.h"
#endif

#if MSVC_VER < 1400 //Older version than Microsoft Visual C/C++ 2005, version 8.0
  #ifndef errno_t   //See also: "KProgCstMsvc.h", <errno.h>
    typedef int errno_t; //global error type
  #endif
#endif
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
/*Translates Windows API error codes to POSIX error codes.
  Mapping of error codes is done as close as possible to intentioned meaning.

  Returns: POSIX error code.

  Note:  Microsoft Windows specific (Win32).

  See also: <winerror.h>, <errno.h>, GetLastError(), errno_t
 */
errno_t ErrnoFromLastError(const DWORD dwError //[in] Windows API error code
                          )
{
errno_t nErrno = -1; //POSIX error code

switch(dwError)
  {
  case NO_ERROR:
    nErrno = 0;      //No error
    break;

  // EPERM =  1

  case ERROR_FILE_NOT_FOUND:      //Cannot find the file specified.
  case ERROR_PATH_NOT_FOUND:      //Cannot find the path specified.
  case ERROR_INVALID_DRIVE:       //Cannot find the drive specified.
  case ERROR_NO_MORE_FILES:       //There are no more files.
  case ERROR_BAD_PATHNAME:        //The specified path is invalid.
  case ERROR_BAD_NETPATH:         //The network path was not found.
  case ERROR_FILENAME_EXCED_RANGE://The filename or extension is too long.
    nErrno = ENOENT;              // =  2
    break;

  // ESRCH =  3
  // EINTR =  4
  // EIO   =  5
  // ENXIO =  6

  case ERROR_BAD_ENVIRONMENT:     //The environment is incorrect.
    nErrno = E2BIG;               // = 7
    break;

  // ENOEXEC = 8

  case ERROR_BAD_FORMAT:
  case ERROR_INVALID_HANDLE:        //The handle is invalid.
  case ERROR_INVALID_TARGET_HANDLE: //The target internal file identifier is incorrect.
  case ERROR_DIRECT_ACCESS_HANDLE:  //Operation other than raw disk I/O not permitted.
    nErrno = EBADF;                 // =  9
    break;

  // ECHILD = 10
  // EAGAIN = 11

  case ERROR_ARENA_TRASHED:       //The storage control blocks were destroyed.
  case ERROR_NOT_ENOUGH_MEMORY:   //Not enough storage is available.
  case ERROR_INVALID_BLOCK:       //The storage control block address is invalid.
  case ERROR_NOT_ENOUGH_QUOTA:    //Not enough quota is available to process this command.
    nErrno = ENOMEM;              // = 12
    break;

  case ERROR_ACCESS_DENIED:       //Access denied.
  case ERROR_CURRENT_DIRECTORY:   //The directory cannot be removed.
  case ERROR_WRITE_PROTECT:       //The media is write protected.
  case ERROR_LOCK_VIOLATION:      //Another process has locked a portion of the file.
  case ERROR_WRONG_DISK:          //The wrong diskette is in the drive.
  case ERROR_SHARING_BUFFER_EXCEEDED: //Too many files opened for sharing.
  case ERROR_DRIVE_LOCKED:        //The disk is in use or locked by another process.
  case ERROR_LOCK_FAILED:         //Unable to lock a region of a file.
  case ERROR_SEEK_ON_DEVICE:      //The file pointer cannot be set on the specified device or file.
    nErrno = EACCES;              // = 13
    break;

  // EFAULT = 14
  // EBUSY  = 16

  case ERROR_FILE_EXISTS:         //The file exists.
  case ERROR_ALREADY_EXISTS:      //Cannot create a file when that file already exists.
    nErrno = EEXIST;              // = 17
    break;

  case ERROR_NOT_SAME_DEVICE:     //The system cannot move the file to a different disk drive.
    nErrno = EXDEV;               // = 18
    break;
  // ENODEV  = 19
  // ENOTDIR = 20
  // EISDIR  = 21

  case ERROR_INVALID_ACCESS:      //The access code is invalid.
  case ERROR_INVALID_DATA:        //The data is invalid.
    nErrno = EINVAL;              // = 22
    break;

  // ENFILE = 23

  case ERROR_HANDLE_EOF:          //Reached the end of the file.
  case ERROR_TOO_MANY_OPEN_FILES: //The system cannot open the file.
    nErrno = EMFILE;              // = 24
    break;

  // ENOTTY = 25
  // EFBIG  = 27

  case ERROR_DISK_FULL:           //There is not enough space on the disk.
    nErrno = ENOSPC;              // = 28
    break;

  // ESPIPE        = 29
  // EROFS         = 30
  // EMLINK        = 31
  // EPIPE         = 32
  // EDOM          = 33
  // ERANGE        = 34
  // EDEADLK       = 36
  // ENAMETOOLONG  = 38
  // ENOLCK        = 39
  // ENOSYS        = 40

  case ERROR_DIR_NOT_EMPTY:       //The directory is not empty.
    nErrno = ENOTEMPTY;           // = 41
    break;

  // EILSEQ        = 42
  // STRUNCATE     = 80
  default:
    nErrno = 0xFFFF;  //Unknown or unhandled or not mapped error code
  }

return nErrno;
}
#endif //_WIN32
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: KErrnoFromLastError.cpp,v $
 * Revision 1.4  2012/02/22 15:08:20  ddarko
 * Fixed return value
 *
 * Revision 1.3  2009/07/02 19:38:39  ddarko
 * Replaced TRACE with ATL header
 *
 * Revision 1.2  2009/03/09 20:06:39  ddarko
 * fixed typo
 *
 * Revision 1.1  2009/03/09 19:55:27  ddarko
 * Moved from old repository
 *
 ******************************************************************************/
