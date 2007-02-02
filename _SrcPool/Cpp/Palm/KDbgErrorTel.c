/*$Workfile: KDbgErrorTel.c$: implementation file
  $Revision: 1$ $Date: 2004-11-09 18:42:23$
  $Author: Darko Kolakovic$

  Dumps error code values
  Copyright: CommonSoft Inc.
  2004-11-01 Darko Kolakovic
 */

/* Group=Diagnostic */

#include <PalmOS.h>
#include <TelephonyMgr.h>

#ifndef TRACE1
  #include "KTrace.h"
#endif

void DbgErrorTel(const Err nErrorCode);

/*----------------------------------------------------------------------------*/
/*Dump Telephony Manager error codes.
  Telephony Manager used as Wireless Telephony Add-on.
  Range of error codes is
   (telErrorClass = 0x8100, 0x8200).

  See also: Palm OS Programmer's API Reference: Appendix D. Palm OS Error Codes

  Note: Palm OS specific (PalmOS).
 */
void DbgErrorTel(const Err nErrorCode //[in] error code
                )
{
    /*Dump most of the Telephony Manager error codes used
      by the Palm OS
     */
switch (nErrorCode)
  {
  case errNone:                   TRACE0(_T("errNone")          ); break;/*0x0000 No error*/
  case telErrorClass:             TRACE0(_T("telErrorClass (!)")           ); break;/*0x8100 Telephony Manager errors
                                                                                      should not be returned as an eror*/
  case telErrMsgAllocation:       TRACE0(_T("telErrMsgAllocation")         ); break;/*0x8101*/
  case telErrUnknown:             TRACE0(_T("telErrUnknown")               ); break;/*0x8102*/
  case telErrMemAllocation:       TRACE0(_T("telErrMemAllocation")         ); break;/*0x8103*/
  case telErrResultTimeOut:       TRACE0(_T("telErrResultTimeOut")         ); break;/*0x8104*/
  case telErrResultUserCancel:    TRACE0(_T("telErrResultUserCancel")      ); break;/*0x8105*/
  case telErrResultBusyResource:  TRACE0(_T("telErrResultBusyResource")    ); break;/*0x8106*/
  case telErrInvalidAppId:        TRACE0(_T("telErrInvalidAppId")          ); break;/*0x8107*/
  case telErrTooManyApps:         TRACE0(_T("telErrTooManyApps")           ); break;/*0x8108*/
  case telErrSecurity:            TRACE0(_T("telErrSecurity")              ); break;/*0x8109*/
  case telErrBufferSize:          TRACE0(_T("telErrBufferSize")            ); break;/*0x810a*/
  case telErrFeatureNotSupported: TRACE0(_T("telErrFeatureNotSupported")   ); break;/*0x810b*/
  case telErrPhoneComm:           TRACE0(_T("telErrPhoneComm")             ); break;/*0x810c*/
  case telErrPhoneReply:          TRACE0(_T("telErrPhoneReply")            ); break;/*0x810d*/
  case telErrCommandFailed:       TRACE0(_T("telErrCommandFailed")         ); break;/*0x810e*/
  case telErrSpcLineIsBusy:       TRACE0(_T("telErrSpcLineIsBusy")         ); break;/*0x810f*/
  case telErrPhoneCodeRequired:   TRACE0(_T("telErrPhoneCodeRequired")     ); break;/*0x8110*/
  case telErrNoSIMInserted:       TRACE0(_T("telErrNoSIMInserted")         ); break;/*0x8111*/
  case telErrPINRequired:         TRACE0(_T("telErrPINRequired")           ); break;/*0x8112*/
  case telErrPUKRequired:         TRACE0(_T("telErrPUKRequired")           ); break;/*0x8113*/
  case telErrSIMFailure:          TRACE0(_T("telErrSIMFailure")            ); break;/*0x8114*/
  case telErrSIMBusy:             TRACE0(_T("telErrSIMBusy")               ); break;/*0x8115*/
  case telErrSIMWrong:            TRACE0(_T("telErrSIMWrong")              ); break;/*0x8116*/
  case telErrPassword:            TRACE0(_T("telErrPassword")              ); break;/*0x8117*/
  case telErrPIN2Required:        TRACE0(_T("telErrPIN2Required")          ); break;/*0x8118*/
  case telErrPUK2Required:        TRACE0(_T("telErrPUK2Required")          ); break;/*0x8119*/
  case telErrPhoneMemAllocation:  TRACE0(_T("telErrPhoneMemAllocation")    ); break;/*0x811a*/
  case telErrInvalidIndex:        TRACE0(_T("telErrInvalidIndex")          ); break;/*0x811b*/
  case telErrEntryNotFound:       TRACE0(_T("telErrEntryNotFound")         ); break;/*0x811c*/
  case telErrPhoneMemFailure:     TRACE0(_T("telErrPhoneMemFailure")       ); break;/*0x811d*/
  case telErrInvalidString:       TRACE0(_T("telErrInvalidString")         ); break;/*0x811e*/
  case telErrInvalidDial:         TRACE0(_T("telErrInvalidDial")           ); break;/*0x811f*/
  case telErrNoNetwork:           TRACE0(_T("telErrNoNetwork")             ); break;/*0x8120*/
  case telErrNetworkTimeOut:      TRACE0(_T("telErrNetworkTimeOut")        ); break;/*0x8121*/
  case telErrInvalidParameter:    TRACE0(_T("telErrInvalidParameter")      ); break;/*0x8122*/
  case telErrValidityPeriod:      TRACE0(_T("telErrValidityPeriod")        ); break;/*0x8123*/
  case telErrCodingScheme:        TRACE0(_T("telErrCodingScheme")          ); break;/*0x8124*/
  case telErrPhoneNumber:         TRACE0(_T("telErrPhoneNumber")           ); break;/*0x8125*/
  case telErrValueStale:          TRACE0(_T("telErrValueStale")            ); break;/*0x8126*/
  case telErrTTaskNotRunning:     TRACE0(_T("telErrTTaskNotRunning")       ); break;/*0x8127*/
  case telErrPhoneToSIMPINRequired:TRACE0(_T("telErrPhoneToSIMPINRequired")); break;/*0x8128*/
  case telErrSpecificDrvNotFound: TRACE0(_T("telErrSpecificDrvNotFound")   ); break;/*0x8129*/
  case telErrGenericDrvNotFound:  TRACE0(_T("telErrGenericDrvNotFound")    ); break;/*0x812a*/
  case telErrNoSpecificDrv:       TRACE0(_T("telErrNoSpecificDrv")         ); break;/*0x812b*/
  case telErrSpcLineIsReleased:   TRACE0(_T("telErrSpcLineIsReleased")     ); break;/*0x812c*/
  case telErrSpcCallError:        TRACE0(_T("telErrSpcCallError")          ); break;/*0x812d*/
  case telErrNotInstalled:        TRACE0(_T("telErrNotInstalled")          ); break;/*0x812e*/
  case telErrVersion:             TRACE0(_T("telErrVersion")               ); break;/*0x812f*/
  case telErrSettings:            TRACE0(_T("telErrSettings")              ); break;/*0x8130*/
  case telErrUnavailableValue:    TRACE0(_T("telErrUnavailableValue")      ); break;/*0x8131*/
  case telErrLimitedCompatibility:TRACE0(_T("telErrLimitedCompatibility")  ); break;/*0x8132*/
  case telErrProfileConflict:     TRACE0(_T("telErrProfileConflict")       ); break;/*0x8133*/
  case telErrLibStillInUse:       TRACE0(_T("telErrLibStillInUse")         ); break;/*0x8134*/
  case telErrTTaskNotFound:       TRACE0(_T("telErrTTaskNotFound")         ); break;/*0x8135*/
  default:                        TRACE0(_T("Unknown error")    );
  }
TRACE1(_T(" (%d).\n"), (UInt32)nErrorCode);
}
/* ////////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2004-11-09 18:42:23  Darko Kolakovic 
 * $
 *****************************************************************************/
