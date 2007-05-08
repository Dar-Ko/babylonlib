/*$Workfile: KDbgErrorExp.c$: implementation file
  $Revision: 1$ $Date: 2004-11-09 19:42:09$
  $Author: Darko Kolakovic$

  Dumps error code values
  Copyright: CommonSoft Inc.
  2004-11-01 Darko Kolakovic
 */

/* Group=Diagnostic */

#include <PalmOS.h>
#include <ExpansionMgr.h>

#ifndef TRACE1
  #include "KTrace.h"
#endif

void DbgErrorExp(const Err nErrorCode);

/*----------------------------------------------------------------------------*/
/*Dump Expansion Manager and Slot Driver Library error codes.
  Range of error codes is
   (expErrorClass = 0x2900, vfsErrorClass = 0x2a00).

  See also: Palm OS Programmer's API Reference: Appendix D. Palm OS Error Codes

  Note: Palm OS specific (PalmOS).
 */
void DbgErrorExp(const Err nErrorCode //[in] error code
                )
{
    /*Dump most of the Expansion Manager error codes used
      by the Palm OS
     */
switch (nErrorCode)
  {
  case errNone:                     TRACE0(_T("errNone")                    ); break;/*0x0000 No error*/
  case expErrorClass:               TRACE0(_T("expErrorClass (!)")          ); break;/*0x2900 Expansion Manager and Slot Driver Library errors
                                                                                       should not be returned as an eror*/
  case expErrUnsupportedOperation:  TRACE0(_T("expErrUnsupportedOperation") ); break;/*0x2901 The operation is unsupported or undefined.*/
  case expErrNotEnoughPower:        TRACE0(_T("expErrNotEnoughPower")       ); break;/*0x2902 The required power is not available.*/
  case expErrCardNotPresent:        TRACE0(_T("expErrCardNotPresent")       ); break;/*0x2903 There is no card present in the given slot.*/
  case expErrInvalidSlotRefNum:     TRACE0(_T("expErrInvalidSlotRefNum")    ); break;/*0x2904 The slot reference number is not valid.*/
  case expErrSlotDeallocated:       TRACE0(_T("expErrSlotDeallocated")      ); break;/*0x2905 The slot reference number is within the valid range, but the slot has been deallocated.*/
  case expErrCardNoSectorReadWrite: TRACE0(_T("expErrCardNoSectorReadWrite")); break;/*0x2906 The card does not support the slot driver block read/write API.*/
  case expErrCardReadOnly:          TRACE0(_T("expErrCardReadOnly")         ); break;/*0x2907 The card supports the slot driver block read/write API but the card is read only.*/
  case expErrCardBadSector:         TRACE0(_T("expErrCardBadSector")        ); break;/*0x2908 The card supports the slot driver block read/write API but the sector is bad.*/
  case expErrCardProtectedSector:   TRACE0(_T("expErrCardProtectedSector")  ); break;/*0x2909 The card supports the slot driver block read/write API but the sector is protected.*/
  case expErrNotOpen:               TRACE0(_T("expErrNotOpen")              ); break;/*0x290a The slot driver library has not been opened.*/
  case expErrStillOpen:             TRACE0(_T("expErrStillOpen")            ); break;/*0x290b The slot driver library is still open; it may have been opened more than once.*/
  case expErrUnimplemented:         TRACE0(_T("expErrUnimplemented")        ); break;/*0x290c The call is unimplemented.*/
  case expErrEnumerationEmpty:      TRACE0(_T("expErrEnumerationEmpty")     ); break;/*0x290d There are no values remaining to enumerate.*/
  case expErrIncompatibleAPIVer:    TRACE0(_T("expErrIncompatibleAPIVer")   ); break;/*0x290e The API version of the underlying slot driver is not supported by this version of Expansion Manager.*/
  default:                          TRACE0(_T("Unknown error")  );
  }
TRACE1(_T(" (%d).\n"), (UInt32)nErrorCode);
}
/* ////////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2004-11-09 19:42:09  Darko Kolakovic 
 * $
 *****************************************************************************/
