/*$Workfile: KDbgErrorCnc.c$: implementation file
  $Revision: 1$ $Date: 2004-11-09 18:42:03$
  $Author: Darko Kolakovic$

  Dumps error code values
  Copyright: CommonSoft Inc.
  2004-11-01 Darko Kolakovic
 */

/* Group=Diagnostic */

#include <PalmOS.h>

#ifndef TRACE1
  #include "KTrace.h"
#endif

void DbgErrorCnc(const Err nErrorCode);

/*----------------------------------------------------------------------------*/
/*Dump Connection Manager (serial communication) error codes.
  Range of error codes is
   (cncErrorClass = 0x1f00, flshErrorClass = 0x1d00).

  See also: Palm OS Programmer's API Reference: Appendix D. Palm OS Error Codes

  Note: Palm OS specific (PalmOS).
 */
void DbgErrorCnc(const Err nErrorCode //[in] error code
                )
{
    /*Dump most of the Connection Manager error codes used
      by the Palm OS
     */
switch (nErrorCode)
  {
  case errNone:                           TRACE0(_T("errNone")        ); break;/*0x0000 No error*/
  case cncErrorClass:                     TRACE0(_T("cncErrorClass (!)")                    ); break;/*0x1f00 Connection Manager (serial communication) errors
                                                                                                       should not be returned as an eror*/
  case cncErrAddProfileFailed:            TRACE0(_T("cncErrAddProfileFailed")           ); break;/*0x1f01*/
  //case kCncErrAddProfileFailed:           TRACE0(_T("kCncErrAddProfileFailed")          ); break;/*0x1f01*/
  case cncErrProfileListFull:             TRACE0(_T("cncErrProfileListFull")            ); break;/*0x1f02*/
  //case kCncErrProfileListFull:            TRACE0(_T("kCncErrProfileListFull")           ); break;/*0x1f02*/
  case cncErrGetProfileFailed:            TRACE0(_T("cncErrGetProfileFailed")           ); break;/*0x1f03*/
  //case kCncErrGetProfileFailed:           TRACE0(_T("kCncErrGetProfileFailed")          ); break;/*0x1f03*/
  case cncErrConDBNotFound:               TRACE0(_T("cncErrConDBNotFound")              ); break;/*0x1f04*/
  //case kCncErrDBAccessFailed:             TRACE0(_T("kCncErrDBAccessFailed")            ); break;/*0x1f04*/
  case cncErrGetProfileListFailed:        TRACE0(_T("cncErrGetProfileListFailed")       ); break;/*0x1f05*/
  //case kCncErrGetProfileListFailed:       TRACE0(_T("kCncErrGetProfileListFailed")      ); break;/*0x1f05*/
  case cncErrProfileReadOnly:             TRACE0(_T("cncErrProfileReadOnly")            ); break;/*0x1f06*/
  //case kCncErrProfileReadOnly:            TRACE0(_T("kCncErrProfileReadOnly")           ); break;/*0x1f06*/
  case cncErrProfileNotFound:             TRACE0(_T("cncErrProfileNotFound")            ); break;/*0x1f07*/
  //case kCncErrProfileNotFound:            TRACE0(_T("kCncErrProfileNotFound")           ); break;/*0x1f07*/
  case kCncErrProfileParamNotFound:       TRACE0(_T("kCncErrProfileParamNotFound")      ); break;/*0x1f08*/
  case kCncErrProfileParamReadOnly:       TRACE0(_T("kCncErrProfileParamReadOnly")      ); break;/*0x1f09*/
  case kCncErrProfileParamNameHasChange:  TRACE0(_T("kCncErrProfileParamNameHasChange") ); break;/*0x1f0a*/
  case kCncErrProfileGetParamFailed:      TRACE0(_T("kCncErrProfileGetParamFailed")     ); break;/*0x1f0b*/
  case kCncErrProfileSetParamFailed:      TRACE0(_T("kCncErrProfileSetParamFailed")     ); break;/*0x1f0c*/
  case kCncErrProfileBadParamSize:        TRACE0(_T("kCncErrProfileBadParamSize")       ); break;/*0x1f0d*/
  case kCncErrProfileBadSystemFlagBitnum: TRACE0(_T("kCncErrProfileBadSystemFlagBitnum")); break;/*0x1f0e*/
  default:                                TRACE0(_T("Unknown error")  );
  }
TRACE1(_T(" (%d).\n"), (UInt32)nErrorCode);
}
/* ////////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2004-11-09 18:42:03  Darko Kolakovic 
 * $
 *****************************************************************************/
