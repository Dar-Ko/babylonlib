/*$Workfile: KDbgErrorBlth.c$: implementation file
  $Revision: 1$ $Date: 2004-11-09 18:42:01$
  $Author: Darko Kolakovic$

  Dumps error code values
  Copyright: CommonSoft Inc.
  2004-11-01 Darko Kolakovic
 */

/* Group=Diagnostic */

#include <PalmOS.h>
#include <BtLibTypes.h>

#ifndef TRACE1
  #include "KTrace.h"
#endif

void DbgErrorBlth(const Err nErrorCode);

/*----------------------------------------------------------------------------*/
/*Dump Bluetooth Library error codes.
  Range of error codes is (blthErrorClass = 0x3100, udaErrorClass = 0x3200).

  See also: Palm OS Programmer's API Reference: Appendix D. Palm OS Error Codes

  Note: Palm OS specific (PalmOS).
 */
void DbgErrorBlth(const Err nErrorCode //[in] error code
                 )
{
    /*Dump most of the Bluetooth  Library error codes used by the Palm OS*/
switch (nErrorCode)
  {
  case errNone:                           TRACE0(_T("errNone")                          ); break;/*0x0000 No error*/
  case blthErrorClass:                    TRACE0(_T("blthErrorClass (!)")                   ); break;/*0x3100 Bluetooth Library errors
                                                                                                          should not be returned as an eror*/
  case btLibErrNotOpen:                   TRACE0(_T("btLibErrNotOpen")                  ); break;/*0x3101*/
  case btLibErrBluetoothOff:              TRACE0(_T("btLibErrBluetoothOff")             ); break;/*0x3102*/
  case btLibErrNoPrefs:                   TRACE0(_T("btLibErrNoPrefs")                  ); break;/*0x3103*/
  case btLibErrAlreadyOpen:               TRACE0(_T("btLibErrAlreadyOpen")              ); break;/*0x3104*/
  case btLibErrOutOfMemory:               TRACE0(_T("btLibErrOutOfMemory")              ); break;/*0x3105*/
  case btLibErrFailed:                    TRACE0(_T("btLibErrFailed")                   ); break;/*0x3106*/
  case btLibErrInProgress:                TRACE0(_T("btLibErrInProgress")               ); break;/*0x3107*/
  case btLibErrParamError:                TRACE0(_T("btLibErrParamError")               ); break;/*0x3108*/
  case btLibErrTooMany:                   TRACE0(_T("btLibErrTooMany")                  ); break;/*0x3109*/
  case btLibErrPending:                   TRACE0(_T("btLibErrPending")                  ); break;/*0x310a*/
  case btLibErrNotInProgress:             TRACE0(_T("btLibErrNotInProgress")            ); break;/*0x310b*/
  case btLibErrRadioInitFailed:           TRACE0(_T("btLibErrRadioInitFailed")          ); break;/*0x310c*/
  case btLibErrRadioFatal:                TRACE0(_T("btLibErrRadioFatal")               ); break;/*0x310d*/
  case btLibErrRadioInitialized:          TRACE0(_T("btLibErrRadioInitialized")         ); break;/*0x310e*/
  case btLibErrRadioSleepWake:            TRACE0(_T("btLibErrRadioSleepWake")           ); break;/*0x310f*/
  case btLibErrNoConnection:              TRACE0(_T("btLibErrNoConnection")             ); break;/*0x3110*/
  case btLibErrAlreadyRegistered:         TRACE0(_T("btLibErrAlreadyRegistered")        ); break;/*0x3111*/
  case btLibErrNoAclLink:                 TRACE0(_T("btLibErrNoAclLink")                ); break;/*0x3112*/
  case btLibErrSdpRemoteRecord:           TRACE0(_T("btLibErrSdpRemoteRecord")          ); break;/*0x3113*/
  case btLibErrSdpAdvertised:             TRACE0(_T("btLibErrSdpAdvertised")            ); break;/*0x3114*/
  case btLibErrSdpFormat:                 TRACE0(_T("btLibErrSdpFormat")                ); break;/*0x3115*/
  case btLibErrSdpNotAdvertised:          TRACE0(_T("btLibErrSdpNotAdvertised")         ); break;/*0x3116*/
  case btLibErrSdpQueryVersion:           TRACE0(_T("btLibErrSdpQueryVersion")          ); break;/*0x3117*/
  case btLibErrSdpQueryHandle:            TRACE0(_T("btLibErrSdpQueryHandle")           ); break;/*0x3118*/
  case btLibErrSdpQuerySyntax:            TRACE0(_T("btLibErrSdpQuerySyntax")           ); break;/*0x3119*/
  case btLibErrSdpQueryPduSize:           TRACE0(_T("btLibErrSdpQueryPduSize")          ); break;/*0x311a*/
  case btLibErrSdpQueryContinuation:      TRACE0(_T("btLibErrSdpQueryContinuation")     ); break;/*0x311b*/
  case btLibErrSdpQueryResources:         TRACE0(_T("btLibErrSdpQueryResources")        ); break;/*0x311c*/
  case btLibErrSdpQueryDisconnect:        TRACE0(_T("btLibErrSdpQueryDisconnect")       ); break;/*0x311d*/
  case btLibErrSdpInvalidResponse:        TRACE0(_T("btLibErrSdpInvalidResponse")       ); break;/*0x311e*/
  case btLibErrSdpAttributeNotSet:        TRACE0(_T("btLibErrSdpAttributeNotSet")       ); break;/*0x311f*/
  case btLibErrSdpMapped:                 TRACE0(_T("btLibErrSdpMapped")                ); break;/*0x3120*/
  case btLibErrSocket:                    TRACE0(_T("btLibErrSocket")                   ); break;/*0x3121*/
  case btLibErrSocketProtocol:            TRACE0(_T("btLibErrSocketProtocol")           ); break;/*0x3122*/
  case btLibErrSocketRole:                TRACE0(_T("btLibErrSocketRole")               ); break;/*0x3123*/
  case btLibErrSocketPsmUnavailable:      TRACE0(_T("btLibErrSocketPsmUnavailable")     ); break;/*0x3124*/
  case btLibErrSocketChannelUnavailable:  TRACE0(_T("btLibErrSocketChannelUnavailable") ); break;/*0x3125*/
  case btLibErrSocketUserDisconnect:      TRACE0(_T("btLibErrSocketUserDisconnect")     ); break;/*0x3126*/
  case btLibErrCanceled:                  TRACE0(_T("btLibErrCanceled")                 ); break;/*0x3127*/
  case btLibErrBusy:                      TRACE0(_T("btLibErrBusy")                     ); break;/*0x3128*/
  case btLibMeStatusUnknownHciCommand:    TRACE0(_T("btLibMeStatusUnknownHciCommand")   ); break;/*0x3129*/
  case btLibMeStatusNoConnection:         TRACE0(_T("btLibMeStatusNoConnection")        ); break;/*0x312a*/
  case btLibMeStatusHardwareFailure:      TRACE0(_T("btLibMeStatusHardwareFailure")     ); break;/*0x312b*/
  case btLibMeStatusPageTimeout:          TRACE0(_T("btLibMeStatusPageTimeout")         ); break;/*0x312c*/
  case btLibMeStatusAuthenticateFailure:  TRACE0(_T("btLibMeStatusAuthenticateFailure") ); break;/*0x312d*/
  case btLibMeStatusMissingKey:           TRACE0(_T("btLibMeStatusMissingKey")          ); break;/*0x312e*/
  case btLibMeStatusMemoryFull:           TRACE0(_T("btLibMeStatusMemoryFull")          ); break;/*0x312f*/
  case btLibMeStatusConnnectionTimeout:   TRACE0(_T("btLibMeStatusConnnectionTimeout")  ); break;/*0x3130*/
  case btLibMeStatusMaxConnections:       TRACE0(_T("btLibMeStatusMaxConnections")      ); break;/*0x3131*/
  case btLibMeStatusMaxScoConnections:    TRACE0(_T("btLibMeStatusMaxScoConnections")   ); break;/*0x3132*/
  case btLibMeStatusMaxAclConnections:    TRACE0(_T("btLibMeStatusMaxAclConnections")   ); break;/*0x3133*/
  case btLibMeStatusCommandDisallowed:    TRACE0(_T("btLibMeStatusCommandDisallowed")   ); break;/*0x3134*/
  case btLibMeStatusLimitedResources:     TRACE0(_T("btLibMeStatusLimitedResources")    ); break;/*0x3135*/
  case btLibMeStatusSecurityError:        TRACE0(_T("btLibMeStatusSecurityError")       ); break;/*0x3136*/
  case btLibMeStatusPersonalDevice:       TRACE0(_T("btLibMeStatusPersonalDevice")      ); break;/*0x3137*/
  case btLibMeStatusHostTimeout:          TRACE0(_T("btLibMeStatusHostTimeout")         ); break;/*0x3138*/
  case btLibMeStatusUnsupportedFeature:   TRACE0(_T("btLibMeStatusUnsupportedFeature")  ); break;/*0x3139*/
  case btLibMeStatusInvalidHciParam:      TRACE0(_T("btLibMeStatusInvalidHciParam")     ); break;/*0x313a*/
  case btLibMeStatusUserTerminated:       TRACE0(_T("btLibMeStatusUserTerminated")      ); break;/*0x313b*/
  case btLibMeStatusLowResources:         TRACE0(_T("btLibMeStatusLowResources")        ); break;/*0x313c*/
  case btLibMeStatusPowerOff:             TRACE0(_T("btLibMeStatusPowerOff")            ); break;/*0x313d*/
  case btLibMeStatusLocalTerminated:      TRACE0(_T("btLibMeStatusLocalTerminated")     ); break;/*0x313e*/
  case btLibMeStatusRepeatedAttempts:     TRACE0(_T("btLibMeStatusRepeatedAttempts")    ); break;/*0x313f*/
  case btLibMeStatusPairingNotAllowed:    TRACE0(_T("btLibMeStatusPairingNotAllowed")   ); break;/*0x3140*/
  case btLibMeStatusUnknownLmpPDU:        TRACE0(_T("btLibMeStatusUnknownLmpPDU")       ); break;/*0x3141*/
  case btLibMeStatusUnsupportedRemote:    TRACE0(_T("btLibMeStatusUnsupportedRemote")   ); break;/*0x3142*/
  case btLibMeStatusScoOffsetRejected:    TRACE0(_T("btLibMeStatusScoOffsetRejected")   ); break;/*0x3143*/
  case btLibMeStatusScoIntervalRejected:  TRACE0(_T("btLibMeStatusScoIntervalRejected") ); break;/*0x3144*/
  case btLibMeStatusScoAirModeRejected:   TRACE0(_T("btLibMeStatusScoAirModeRejected")  ); break;/*0x3145*/
  case btLibMeStatusInvalidLmpParam:      TRACE0(_T("btLibMeStatusInvalidLmpParam")     ); break;/*0x3146*/
  case btLibMeStatusUnspecifiedError:     TRACE0(_T("btLibMeStatusUnspecifiedError")    ); break;/*0x3147*/
  case btLibMeStatusUnsupportedLmpParam:  TRACE0(_T("btLibMeStatusUnsupportedLmpParam") ); break;/*0x3148*/
  case btLibMeStatusRoleChangeNotAllowed: TRACE0(_T("btLibMeStatusRoleChangeNotAllowed")); break;/*0x3149*/
  case btLibMeStatusLmpResponseTimeout:   TRACE0(_T("btLibMeStatusLmpResponseTimeout")  ); break;/*0x314a*/
  case btLibMeStatusLmpTransdCollision:   TRACE0(_T("btLibMeStatusLmpTransdCollision")  ); break;/*0x314b*/
  case btLibMeStatusLmpPduNotAllowed:     TRACE0(_T("btLibMeStatusLmpPduNotAllowed")    ); break;/*0x314c*/
  case btLibL2DiscReasonUnknown:          TRACE0(_T("btLibL2DiscReasonUnknown")         ); break;/*0x314d*/
  case btLibL2DiscUserRequest:            TRACE0(_T("btLibL2DiscUserRequest")           ); break;/*0x314e*/
  case btLibL2DiscRequestTimeout:         TRACE0(_T("btLibL2DiscRequestTimeout")        ); break;/*0x314f*/
  case btLibL2DiscLinkDisc:               TRACE0(_T("btLibL2DiscLinkDisc")              ); break;/*0x3150*/
  case btLibL2DiscQosViolation:           TRACE0(_T("btLibL2DiscQosViolation")          ); break;/*0x3151*/
  case btLibL2DiscSecurityBlock:          TRACE0(_T("btLibL2DiscSecurityBlock")         ); break;/*0x3152*/
  case btLibL2DiscConnPsmUnsupported:     TRACE0(_T("btLibL2DiscConnPsmUnsupported")    ); break;/*0x3153*/
  case btLibL2DiscConnSecurityBlock:      TRACE0(_T("btLibL2DiscConnSecurityBlock")     ); break;/*0x3154*/
  case btLibL2DiscConnNoResources:        TRACE0(_T("btLibL2DiscConnNoResources")       ); break;/*0x3155*/
  case btLibL2DiscConfigUnacceptable:     TRACE0(_T("btLibL2DiscConfigUnacceptable")    ); break;/*0x3156*/
  case btLibL2DiscConfigReject:           TRACE0(_T("btLibL2DiscConfigReject")          ); break;/*0x3157*/
  case btLibL2DiscConfigOptions:          TRACE0(_T("btLibL2DiscConfigOptions")         ); break;/*0x3158*/
  case btLibServiceShutdownAppUse:        TRACE0(_T("btLibServiceShutdownAppUse")       ); break;/*0x3159*/
  case btLibServiceShutdownPowerCycled:   TRACE0(_T("btLibServiceShutdownPowerCycled")  ); break;/*0x315a*/
  case btLibServiceShutdownAclDrop:       TRACE0(_T("btLibServiceShutdownAclDrop")      ); break;/*0x315b*/
  case btLibServiceShutdownTimeout:       TRACE0(_T("btLibServiceShutdownTimeout")      ); break;/*0x315c*/
  case btLibServiceShutdownDetached:      TRACE0(_T("btLibServiceShutdownDetached")     ); break;/*0x315d*/
  case btLibErrInUseByService:            TRACE0(_T("btLibErrInUseByService")           ); break;/*0x315e*/
  case btLibErrNoPiconet:                 TRACE0(_T("btLibErrNoPiconet")                ); break;/*0x315f*/
  case btLibErrRoleChange:                TRACE0(_T("btLibErrRoleChange")               ); break;/*0x3160*/
  case btLibErrSdpNotMapped:              TRACE0(_T("btLibErrSdpNotMapped")             ); break;/*0x3161*/
  case btLibErrAlreadyConnected:          TRACE0(_T("btLibErrAlreadyConnected")         ); break;/*0x3162*/
  case btLibErrStackNotOpen:              TRACE0(_T("btLibErrStackNotOpen")             ); break;/*0x3163*/
  case btLibErrBatteryTooLow:             TRACE0(_T("btLibErrBatteryTooLow")            ); break;/*0x3164*/
  case btLibErrNotFound:                  TRACE0(_T("btLibErrNotFound")                 ); break;/*0x3165*/
  case btLibNotYetSupported:              TRACE0(_T("btLibNotYetSupported")             ); break;/*0x31ef*/
  case btLibErrError:                     TRACE0(_T("btLibErrError")                    ); break;/*0x31ff*/
  default:                                TRACE0(_T("Unknown error")                    );
  }
TRACE1(_T(" (%d).\n"), (UInt32)nErrorCode);
}
/* ////////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2004-11-09 18:42:01  Darko Kolakovic 
 * $
 *****************************************************************************/
