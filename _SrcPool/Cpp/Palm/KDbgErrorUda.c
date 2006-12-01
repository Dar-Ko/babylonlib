/*$Workfile: KDbgErrorUda.c$: implementation file
  $Revision: 1$ $Date: 2004-11-09 18:42:25$
  $Author: Darko Kolakovic$

  Dumps error code values
  Copyright: CommonSoft Inc.
  2004-11-01 Darko Kolakovic
 */

/* Group=Diagnostic */

#include <PalmOS.h>
#include <UDAMgr.h>

#ifndef TRACE1
  #include "KTrace.h"
#endif

void DbgErrorUda(const Err nErrorCode);

/*----------------------------------------------------------------------------*/
/*Dump Unified Data Manager (UDA) error codes.
  Range of error codes is
   (udaErrorClass = 0x3200, 0x3300).

  See also: Palm OS Programmer's API Reference: Appendix D. Palm OS Error Codes

  Note: Palm OS specific (PalmOS).
 */
void DbgErrorUda(const Err nErrorCode //[in] error code
                )
{
    /*Dump most of the UDA Manager error codes used
      by the Palm OS
     */
switch (nErrorCode)
  {
  case errNone:       TRACE0(_T("errNone")          ); break;/*0x0000 No error*/
  case udaErrorClass: TRACE0(_T("udaErrorClass (!)")); break;/*0x3200 UDA Manager errors
                                                               should not be returned as an eror*/
  case udaErrControl: TRACE0(_T("udaErrControl")); break;/*0x3201*/
  default:            TRACE0(_T("Unknown error")    );
  }
TRACE1(_T(" (%d).\n"), (UInt32)nErrorCode);
}
/* ////////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2004-11-09 18:42:25  Darko Kolakovic 
 * $
 *****************************************************************************/
