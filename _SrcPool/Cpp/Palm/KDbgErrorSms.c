/*$Workfile: KDbgErrorSms.c$: implementation file
  $Revision: 1$ $Date: 2004-11-09 18:42:19$
  $Author: Darko Kolakovic$

  Dumps error code values
  Copyright: CommonSoft Inc.
  2004-11-01 Darko Kolakovic
 */

/* Group=Diagnostic */

#include <PalmOS.h>
#include <SmsLib.h>

#ifndef TRACE1
  #include "KTrace.h"
#endif

void DbgErrorSms(const Err nErrorCode);

/*----------------------------------------------------------------------------*/
/*Dump SMS Library error codes.
  Range of error codes is
   (smsErrorClass = 0x2800, expErrorClass = 0x2900).

  Note: The SMS library is used as an Exchange library. <ExgLib.h> defines all
  the primary entrypoints into the library.

  See also: Palm OS Programmer's API Reference: Appendix D. Palm OS Error Codes

  Note: Palm OS specific (PalmOS).
 */
void DbgErrorSms(const Err nErrorCode //[in] error code
                )
{
    /*Dump most of the SMS Library error codes used
      by the Palm OS
     */
switch (nErrorCode)
  {
  case errNone:                TRACE0(_T("errNone")               ); break;/*0x0000 No error*/
  case smsErrorClass:          TRACE0(_T("smsErrorClass (!)")     ); break;/*0x2800 SMS Library errors
                                                                             should not be returned as an eror*/
  case kSmsErrMaxSizeExceeded: TRACE0(_T("kSmsErrMaxSizeExceeded")); break;/*0x2801*/
  default:                     TRACE0(_T("Unknown error")  );
  }
TRACE1(_T(" (%d).\n"), (UInt32)nErrorCode);
}
/* ////////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2004-11-09 18:42:19  Darko Kolakovic 
 * $
 *****************************************************************************/
