/*$Workfile: KDbgErrorPwr.c$: implementation file
  $Revision: 1$ $Date: 2004-11-09 18:42:18$
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

void DbgErrorPwr(const Err nErrorCode);

/*----------------------------------------------------------------------------*/
/*Dump Power Manager error codes.
  Range of error codes is
   [pwrErrorClass = pwrErrNone = 0x1e00, cncErrorClass = 0x1f00).

  See also: Palm OS Programmer's API Reference: Appendix D. Palm OS Error Codes

  Note: Palm OS specific (PalmOS).
 */
void DbgErrorPwr(const Err nErrorCode //[in] error code
                )
{
    /*Dump most of the Power Manager error codes used
      by the Palm OS
     */
switch (nErrorCode)
  {
  case errNone:         TRACE0(_T("errNone")        ); break;/*0x0000 No error*/
  case pwrErrNone:      TRACE0(_T("pwrErrNone")     ); break;/*0x1e00*/
  //case pwrErrorClass:   TRACE0(_T("pwrErrorClass")  ); break;/*0x1e00 Power Manager errors*/
  case pwrErrBacklight: TRACE0(_T("pwrErrBacklight")); break;/*0x1e01*/
  case pwrErrRadio:     TRACE0(_T("pwrErrRadio")    ); break;/*0x1e02*/
  case pwrErrBeam:      TRACE0(_T("pwrErrBeam")     ); break;/*0x1e03*/
  case pwrErrGeneric:   TRACE0(_T("pwrErrGeneric")  ); break;/*0x1e04*/
  default:              TRACE0(_T("Unknown error")  );
  }
TRACE1(_T(" (%d).\n"), (UInt32)nErrorCode);
}
/* ////////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2004-11-09 18:42:18  Darko Kolakovic 
 * $
 *****************************************************************************/
