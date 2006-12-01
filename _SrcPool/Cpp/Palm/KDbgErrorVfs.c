/*$Workfile: KDbgErrorVfs.c$: implementation file
  $Revision: 1$ $Date: 2004-11-09 18:42:27$
  $Author: Darko Kolakovic$

  Dumps error code values
  Copyright: CommonSoft Inc.
  2004-11-01 Darko Kolakovic
 */

/* Group=Diagnostic */

#include <PalmOS.h>
#include <VFSMgr.h>

#ifndef TRACE1
  #include "KTrace.h"
#endif

void DbgErrorVfs(const Err nErrorCode);

/*----------------------------------------------------------------------------*/
/*Dump Virtual Filesystem Manager and Filesystem Library error codes.
  Range of error codes is
   (vfsErrorClass = 0x2a00, lmErrorClass = 0x2b00).

  See also: Palm OS Programmer's API Reference: Appendix D. Palm OS Error Codes

  Note: Palm OS specific (PalmOS).
 */
void DbgErrorVfs(const Err nErrorCode //[in] error code
                )
{
    /*Dump most of the Virtual Filesystem Manager error codes used
      by the Palm OS
     */
switch (nErrorCode)
  {
  case errNone:                    TRACE0(_T("errNone")                   ); break;/*0x0000 No error*/
  case vfsErrorClass:              TRACE0(_T("vfsErrorClass (!)")         ); break;/*0x2a00 Virtual Filesystem Manager and Filesystem Library errors
                                                                                     should not be returned as an eror*/
  case vfsErrBufferOverflow:       TRACE0(_T("vfsErrBufferOverflow")      ); break;/*0x2a01 The supplied buffer is too small.*/
  case vfsErrFileGeneric:          TRACE0(_T("vfsErrFileGeneric")         ); break;/*0x2a02 Generic file error.*/
  case vfsErrFileBadRef:           TRACE0(_T("vfsErrFileBadRef")          ); break;/*0x2a03 The file reference is invalid: it has been closed or was not obtained from VFSFileOpen().*/
  case vfsErrFileStillOpen:        TRACE0(_T("vfsErrFileStillOpen")       ); break;/*0x2a04 Returned from the underlying file system's delete function if the file is still open.*/
  case vfsErrFilePermissionDenied: TRACE0(_T("vfsErrFilePermissionDenied")); break;/*0x2a05 The requested permissions could not be granted.*/
  case vfsErrFileAlreadyExists:    TRACE0(_T("vfsErrFileAlreadyExists")   ); break;/*0x2a06 A file with this name exists already in this location.*/
  case vfsErrFileEOF:              TRACE0(_T("vfsErrFileEOF")             ); break;/*0x2a07 The file pointer is at the end of the file.*/
  case vfsErrFileNotFound:         TRACE0(_T("vfsErrFileNotFound")        ); break;/*0x2a08 The file was not found at the specified location.*/
  case vfsErrVolumeBadRef:         TRACE0(_T("vfsErrVolumeBadRef")        ); break;/*0x2a09 The volume reference number is invalid.*/
  case vfsErrVolumeStillMounted:   TRACE0(_T("vfsErrVolumeStillMounted")  ); break;/*0x2a0a Returned from the underlying file system's format function if the volume is still mounted.*/
  case vfsErrNoFileSystem:         TRACE0(_T("vfsErrNoFileSystem")        ); break;/*0x2a0b None of the installed file systems support this operation.*/
  case vfsErrBadData:              TRACE0(_T("vfsErrBadData")             ); break;/*0x2a0c The operation could not be completed because of invalid data.*/
  case vfsErrDirNotEmpty:          TRACE0(_T("vfsErrDirNotEmpty")         ); break;/*0x2a0d The directory is not empty and therefore cannot be deleted.*/
  case vfsErrBadName:              TRACE0(_T("vfsErrBadName")             ); break;/*0x2a0e Invalid filename, path, or volume label.*/
  case vfsErrVolumeFull:           TRACE0(_T("vfsErrVolumeFull")          ); break;/*0x2a0f There is insufficient space left on the volume.*/
  case vfsErrUnimplemented:        TRACE0(_T("vfsErrUnimplemented")       ); break;/*0x2a10*/
  case vfsErrNotADirectory:        TRACE0(_T("vfsErrNotADirectory")       ); break;/*0x2a11 This operation can only performed on a directory.*/
  case vfsErrIsADirectory:         TRACE0(_T("vfsErrIsADirectory")        ); break;/*0x2a12 This operation can only be performed on a regular file, not a directory.*/
  case vfsErrDirectoryNotFound:    TRACE0(_T("vfsErrDirectoryNotFound")   ); break;/*0x2a13 Returned when the path leading up to the file does not exist.*/
  case vfsErrNameShortened:        TRACE0(_T("vfsErrNameShortened")       ); break;/*0x2a14 A volume name or filename was automatically shortened to conform to the file system specification.*/
  default:                         TRACE0(_T("Unknown error")  );
  }
TRACE1(_T(" (%d).\n"), (UInt32)nErrorCode);
}
/* ////////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2004-11-09 18:42:27  Darko Kolakovic 
 * $
 *****************************************************************************/
