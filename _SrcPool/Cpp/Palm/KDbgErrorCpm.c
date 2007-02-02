/*$Workfile: KDbgErrorCpm.c$: implementation file
  $Revision: 1$ $Date: 2004-11-09 18:42:05$
  $Author: Darko Kolakovic$

  Dumps error code values
  Copyright: CommonSoft Inc.
  2004-11-01 Darko Kolakovic
 */

/* Group=Diagnostic */

#include <PalmOS.h>
#include <CPMLibCommon.h>

#ifndef TRACE1
  #include "KTrace.h"
#endif

void DbgErrorCpm(const Err nErrorCode);

/*----------------------------------------------------------------------------*/
/*Dump Cryptographic Provider Manager error codes.
  Range of error codes is
   (cpmErrorClass = 0x3800, sslErrorClass = 0x3900).

  See also: Palm OS Programmer's API Reference: Appendix D. Palm OS Error Codes

  Note: Palm OS specific (PalmOS).
 */
void DbgErrorCpm(const Err nErrorCode //[in] error code
                )
{
    /*Dump most of the Cryptographic Provider Manager error codes used
      by the Palm OS
     */
switch (nErrorCode)
  {
  case errNone:                TRACE0(_T("errNone")               ); break;/*0x0000 No error*/
  case cpmErrorClass:          TRACE0(_T("cpmErrorClass (!)")     ); break;/*0x3800 Cryptographic Provider Manager errors
                                                                             should not be returned as an eror*/
  case cpmErrAlreadyOpen:      TRACE0(_T("cpmErrAlreadyOpen")     ); break;/*0x3801*/
  case cpmErrNotOpen:          TRACE0(_T("cpmErrNotOpen")         ); break;/*0x3802*/
  case cpmErrStillOpen:        TRACE0(_T("cpmErrStillOpen")       ); break;/*0x3803*/
  case cpmErrNoProviders:      TRACE0(_T("cpmErrNoProviders")     ); break;/*0x3804*/
  case cpmErrNoBaseProvider:   TRACE0(_T("cpmErrNoBaseProvider")  ); break;/*0x3805*/
  case cpmErrProviderNotFound: TRACE0(_T("cpmErrProviderNotFound")); break;/*0x3806*/
  case cpmErrParamErr:         TRACE0(_T("cpmErrParamErr")        ); break;/*0x380a*/
  case cpmErrOutOfResources:   TRACE0(_T("cpmErrOutOfResources")  ); break;/*0x380b*/
  case cpmErrOutOfMemory:      TRACE0(_T("cpmErrOutOfMemory")     ); break;/*0x380c*/
  case cpmErrBufTooSmall:      TRACE0(_T("cpmErrBufTooSmall")     ); break;/*0x380d*/
  case cpmErrBadData:          TRACE0(_T("cpmErrBadData")         ); break;/*0x380e*/
  case cpmErrUnimplemented:    TRACE0(_T("cpmErrUnimplemented")   ); break;/*0x380f*/
  case cpmErrUnsupported:      TRACE0(_T("cpmErrUnsupported")     ); break;/*0x3810*/
  case cpmErrNoGlobals:        TRACE0(_T("cpmErrNoGlobals")       ); break;/*0x3811*/
  case cpmErrKeyExists:        TRACE0(_T("cpmErrKeyExists")       ); break;/*0x3812*/
  case cpmErrKeyNotFound:      TRACE0(_T("cpmErrKeyNotFound")     ); break;/*0x3813*/
  default:                     TRACE0(_T("Unknown error")         );
  }
TRACE1(_T(" (%d).\n"), (UInt32)nErrorCode);
}
/* ////////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2004-11-09 18:42:05  Darko Kolakovic 
 * $
 *****************************************************************************/
