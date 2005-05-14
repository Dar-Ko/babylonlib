/*$Workfile: KDbgErrorDlk.c$: implementation file
  $Revision: 1$ $Date: 2004-11-09 19:42:07$
  $Author: Darko Kolakovic$

  Dumps error code values
  Copyright: CommonSoft Inc.
  2004-11-01 Darko Kolakovic
 */

/* Group=Diagnostic */

#include <PalmOS.h>
#include <DLServer.h>

#ifndef TRACE1
  #include "KTrace.h"
#endif

void DbgErrorDlk(const Err nErrorCode);


/*----------------------------------------------------------------------------*/
/*Dump Desktop Link Protocol (DLP) Server error codes.
  Range of error codes is (dlkErrorClass = 0x0e00, padErrorClass = 0x0f00).

  Note: dlkErrorClass is defined in SystemMgr.h

  See also: Palm OS Programmer's API Reference: Appendix D. Palm OS Error Codes

  Note: Palm OS specific (PalmOS).
 */
void DbgErrorDlk(const Err nErrorCode //[in] error code
                )
{
    /*Dump most of the Desktop Link Protocol (DLP) Server error codes used
      by the Palm OS
     */
switch (nErrorCode)
  {
  case errNone:                    TRACE0(_T("errNone")                   ); break;/*0x0000 No error*/
  case dlkErrorClass:              TRACE0(_T("dlkErrorClass (!)")         ); break;/*0x0e00 Desktop Link Manager error class;
                                                                           should not be returned as an eror*/
  case dlkErrParam:                TRACE0(_T("dlkErrParam")               ); break;/*0x0e01*/
  case dlkErrMemory:               TRACE0(_T("dlkErrMemory")              ); break;/*0x0e02*/
  case dlkErrNoSession:            TRACE0(_T("dlkErrNoSession")           ); break;/*0x0e03*/
  case dlkErrSizeErr:              TRACE0(_T("dlkErrSizeErr")             ); break;/*0x0e04*/
  case dlkErrLostConnection:       TRACE0(_T("dlkErrLostConnection")      ); break;/*0x0e05*/
  case dlkErrInterrupted:          TRACE0(_T("dlkErrInterrupted")         ); break;/*0x0e06*/
  case dlkErrUserCan:              TRACE0(_T("dlkErrUserCan")             ); break;/*0x0e07*/
  case dlkErrIncompatibleProducts: TRACE0(_T("dlkErrIncompatibleProducts")); break;/*0x0e08*/
  case dlkErrNPOD:                 TRACE0(_T("dlkErrNPOD")                ); break;/*0x0e09*/
  default:                         TRACE0(_T("Unknown error")             );
  }
TRACE1(_T(" (%d).\n"), (UInt32)nErrorCode);
}
/* ////////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2004-11-09 19:42:07  Darko Kolakovic 
 * $
 *****************************************************************************/
