/*$Workfile: KDbgErrorHost.c$: implementation file
  $Revision: 1$ $Date: 2004-11-09 18:42:10$
  $Author: Darko Kolakovic$

  Dumps error code values
  Copyright: CommonSoft Inc.
  2004-11-01 Darko Kolakovic
 */

/* Group=Diagnostic */

#include <PalmOS.h>
#include <HostControl.h>

#ifndef TRACE1
  #include "KTrace.h"
#endif

void DbgErrorHost(const Err nErrorCode);

/*----------------------------------------------------------------------------*/
/*Dump Emulator/Host Control Manager error codes.
  Range of error codes is
    (emuErrorClass = hostErrorClass = 0x1c00, flshErrorClass = 0x1d00).

  See also: Palm OS Programmer's API Reference: Appendix D. Palm OS Error Codes

  Note: Palm OS specific (PalmOS).
 */
void DbgErrorHost(const Err nErrorCode //[in] error code
                 )
{
    /*Dump most of the Emulator/Host Control Manager error codes used by the Palm OS*/
switch (nErrorCode)
  {
  case errNone:                       TRACE0(_T("errNone")                      ); break;/*0x0000 No error*/
  //case emuErrorClass:                 TRACE0(_T("emuErrorClass")                ); break;/*0x1c00 Emulator Control Manager errors*/
  case hostErrorClass:                TRACE0(_T("hostErrorClass (!)")               ); break;/*0x1c00 Host Control Manager errors;
                                                                                    should not be returned as an eror*/
  case hostErrUnknownGestaltSelector: TRACE0(_T("hostErrUnknownGestaltSelector")); break;/*0x1c01*/
  case hostErrDiskError:              TRACE0(_T("hostErrDiskError")             ); break;/*0x1c02*/
  case hostErrOutOfMemory:            TRACE0(_T("hostErrOutOfMemory")           ); break;/*0x1c03*/
  case hostErrMemReadOutOfRange:      TRACE0(_T("hostErrMemReadOutOfRange")     ); break;/*0x1c04*/
  case hostErrMemWriteOutOfRange:     TRACE0(_T("hostErrMemWriteOutOfRange")    ); break;/*0x1c05*/
  case hostErrMemInvalidPtr:          TRACE0(_T("hostErrMemInvalidPtr")         ); break;/*0x1c06*/
  case hostErrInvalidParameter:       TRACE0(_T("hostErrInvalidParameter")      ); break;/*0x1c07*/
  case hostErrTimeout:                TRACE0(_T("hostErrTimeout")               ); break;/*0x1c08*/
  case hostErrInvalidDeviceType:      TRACE0(_T("hostErrInvalidDeviceType")     ); break;/*0x1c09*/
  case hostErrInvalidRAMSize:         TRACE0(_T("hostErrInvalidRAMSize")        ); break;/*0x1c0a*/
  case hostErrFileNotFound:           TRACE0(_T("hostErrFileNotFound")          ); break;/*0x1c0b*/
  case hostErrRPCCall:                TRACE0(_T("hostErrRPCCall")               ); break;/*0x1c0c*/
  case hostErrSessionRunning:         TRACE0(_T("hostErrSessionRunning")        ); break;/*0x1c0d*/
  case hostErrSessionNotRunning:      TRACE0(_T("hostErrSessionNotRunning")     ); break;/*0x1c0e*/
  case hostErrNoSignalWaiters:        TRACE0(_T("hostErrNoSignalWaiters")       ); break;/*0x1c0f*/
  case hostErrSessionNotPaused:       TRACE0(_T("hostErrSessionNotPaused")      ); break;/*0x1c10*/
  case hostErrPermissions:            TRACE0(_T("hostErrPermissions")           ); break;/*0x1c11*/
  case hostErrFileNameTooLong:        TRACE0(_T("hostErrFileNameTooLong")       ); break;/*0x1c12*/
  case hostErrNotADirectory:          TRACE0(_T("hostErrNotADirectory")         ); break;/*0x1c13*/
  case hostErrTooManyFiles:           TRACE0(_T("hostErrTooManyFiles")          ); break;/*0x1c14*/
  case hostErrFileTooBig:             TRACE0(_T("hostErrFileTooBig")            ); break;/*0x1c15*/
  case hostErrReadOnlyFS:             TRACE0(_T("hostErrReadOnlyFS")            ); break;/*0x1c16*/
  case hostErrIsDirectory:            TRACE0(_T("hostErrIsDirectory")           ); break;/*0x1c17*/
  case hostErrExists:                 TRACE0(_T("hostErrExists")                ); break;/*0x1c18*/
  case hostErrOpNotAvailable:         TRACE0(_T("hostErrOpNotAvailable")        ); break;/*0x1c19*/
  case hostErrDirNotEmpty:            TRACE0(_T("hostErrDirNotEmpty")           ); break;/*0x1c1a*/
  case hostErrDiskFull:               TRACE0(_T("hostErrDiskFull")              ); break;/*0x1c1b*/
  case hostErrUnknownError:           TRACE0(_T("hostErrUnknownError")          ); break;/*0x1c1c*/
  case hostErrProfilingNotReady:      TRACE0(_T("hostErrProfilingNotReady")     ); break;/*0x1c1d*/
  default:                            TRACE0(_T("Unknown error")                );
  }
TRACE1(_T(" (%d).\n"), (UInt32)nErrorCode);
}
/* ////////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2004-11-09 18:42:10  Darko Kolakovic 
 * $
 *****************************************************************************/
