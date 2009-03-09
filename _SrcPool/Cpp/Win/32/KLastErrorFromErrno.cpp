/*$RCSfile: KLastErrorFromErrno.cpp,v $: implementation file
  $Revision: 1.3 $ $Date: 2009/03/09 20:06:39 $
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
  #ifndef TRACE
    #define TRACE ATLTRACE
    #define TRACE1 ATLTRACE
  #endif
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
/*Translates POSIX error codes to Windows API error codes.
  Mapping of error codes is done as close as possible to intentioned meaning.

  Returns: errno value.

  Note:  Microsoft Windows specific (Win32).

  See also: <winerror.h>, <errno.h>, GetLastError(), HRESULT_FROM_WIN32
 */
DWORD LastErrorFromErrno(const errno_t nErrno //[in]
                        )
{
DWORD dwError = ERROR_GEN_FAILURE;

switch(nErrno)
  {
  case 0            :
    dwError = NO_ERROR;
    break;
  case EPERM        : // = 1
    dwError = ERROR_ACCESS_DENIED;
    break;
  case ENOENT       : // = 2
    dwError = ERROR_FILE_NOT_FOUND;
    break;
  case ESRCH        : // = 3
  case EINTR        : // = 4
  case EIO          : // = 5
  case ENXIO        : // = 6
  case E2BIG        : // = 7
    dwError = ERROR_BAD_ENVIRONMENT;
    break;
  case ENOEXEC      : // = 8
    dwError = ERROR_GEN_FAILURE; //FixMe!
    break;
  case EBADF        : // = 9
    dwError = ERROR_BAD_FORMAT;
    break;
  case ECHILD       : // = 10
    dwError = ERROR_GEN_FAILURE; //FixMe!
    break;
  case EAGAIN       : // = 11
    dwError = ERROR_SHARING_VIOLATION;
    break;
  case ENOMEM       : // = 12
    dwError = ERROR_NOT_ENOUGH_MEMORY;
    break;
  case EACCES       : // = 13
    dwError = ERROR_ACCESS_DENIED;
    break;
  case EFAULT       : // = 14
    dwError = ERROR_GEN_FAILURE; //FixMe!
    break;
  case EBUSY        : // = 16
    dwError = ERROR_LOCK_VIOLATION;
    break;
  case EEXIST       : // = 17
    dwError = ERROR_FILE_EXISTS;
    break;
  case EXDEV        : // = 18
    dwError = ERROR_NOT_SAME_DEVICE;
    break;
  case ENODEV       : // = 19
  case ENOTDIR      : // = 20
    dwError = ERROR_GEN_FAILURE; //FixMe!
    break;
  case EISDIR       : // = 21
    dwError = ERROR_CANNOT_MAKE;
    break;
  case EINVAL       : // = 22
    dwError = ERROR_INVALID_DATA;
    break;
  case ENFILE       : // = 23
    dwError = ERROR_NO_MORE_FILES;
    break;
  case EMFILE       : // = 24
    dwError = ERROR_TOO_MANY_OPEN_FILES;
    break;
  case ENOTTY       : // = 25
  case EFBIG        : // = 27
    dwError = ERROR_GEN_FAILURE; //FixMe!
    break;
  case ENOSPC       : // = 28
    dwError = ERROR_DISK_FULL;
    break;
  case ESPIPE       : // = 29
  case EROFS        : // = 30
    dwError = ERROR_ACCESS_DENIED;
    break;
  case EMLINK       : // = 31
  case EPIPE        : // = 32
    dwError = ERROR_SEEK;
    break;
  case EDOM         : // = 33
  case ERANGE       : // = 34
  case EDEADLK      : // = 36
  case ENAMETOOLONG : // = 38
  case ENOLCK       : // = 39
  case ENOSYS       : // = 40
    dwError = ERROR_GEN_FAILURE; //FixMe!
    break;
  case ENOTEMPTY    : // = 41
    dwError = ERROR_DIR_NOT_EMPTY;
    break;
  case EILSEQ       : // = 42
  case STRUNCATE    : // = 80
    dwError = ERROR_GEN_FAILURE; //FixMe!
    break;
  default:
    dwError = ERROR_GEN_FAILURE;
    break;
  }

return dwError;
}
#endif //_WIN32
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: KLastErrorFromErrno.cpp,v $
 * Revision 1.3  2009/03/09 20:06:39  ddarko
 * fixed typo
 *
 * Revision 1.2  2009/03/09 19:57:07  ddarko
 * comment
 *
 * Revision 1.1  2009/03/09 19:55:27  ddarko
 * Moved from old repository
 *
 *****************************************************************************/
