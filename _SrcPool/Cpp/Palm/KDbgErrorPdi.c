/*$Workfile: KDbgErrorPdi.c$: implementation file
  $Revision: 1$ $Date: 2004-11-09 18:42:16$
  $Author: Darko Kolakovic$

  Dumps error code values
  Copyright: CommonSoft Inc.
  2004-11-01 Darko Kolakovic
 */

/* Group=Diagnostic */

#include <PalmOS.h>
#include <PdiLib.h>

#ifndef TRACE1
  #include "KTrace.h"
#endif

void DbgErrorPdi(const Err nErrorCode);

/*----------------------------------------------------------------------------*/
/*Dump PDI versit Library error codes.
  Range of error codes is
   (pdiErrorClass = 0x2d00, attnErrorClass = 0x2e00).

  See also: Palm OS Programmer's API Reference: Appendix D. Palm OS Error Codes

  Note: Palm OS specific (PalmOS).
 */
void DbgErrorPdi(const Err nErrorCode //[in] error code
                )
{
    /*Dump most of the PDI Library error codes used
      by the Palm OS
     */
switch (nErrorCode)
  {
  case errNone:               TRACE0(_T("errNone")              ); break;/*0x0000 No error*/
  case pdiErrorClass:         TRACE0(_T("pdiErrorClass (!)")    ); break;/*0x2d00 PDI Library errors
                                                                             should not be returned as an eror*/
  case pdiErrRead:            TRACE0(_T("pdiErrRead")           ); break;/*0x2d01*/
  case pdiErrWrite:           TRACE0(_T("pdiErrWrite")          ); break;/*0x2d02*/
  case pdiErrNoPropertyName:  TRACE0(_T("pdiErrNoPropertyName") ); break;/*0x2d03*/
  case pdiErrNoPropertyValue: TRACE0(_T("pdiErrNoPropertyValue")); break;/*0x2d04*/
  case pdiErrMoreChars:       TRACE0(_T("pdiErrMoreChars")      ); break;/*0x2d05*/
  case pdiErrNoMoreFields:    TRACE0(_T("pdiErrNoMoreFields")   ); break;/*0x2d06*/
  case pdiErrOpenFailed:      TRACE0(_T("pdiErrOpenFailed")     ); break;/*0x2d07*/
  case pdiErrCloseFailed:     TRACE0(_T("pdiErrCloseFailed")    ); break;/*0x2d08*/
  default:                    TRACE0(_T("Unknown error")  );
  }
TRACE1(_T(" (%d).\n"), (UInt32)nErrorCode);
}
/* ////////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2004-11-09 18:42:16  Darko Kolakovic 
 * $
 *****************************************************************************/
