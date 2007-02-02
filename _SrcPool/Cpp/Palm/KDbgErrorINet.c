/*$Workfile: KDbgErrorINet.c$: implementation file
  $Revision: 1$ $Date: 2004-11-09 18:42:12$
  $Author: Darko Kolakovic$

  Dumps error code values
  Copyright: CommonSoft Inc.
  2004-11-01 Darko Kolakovic
 */

/* Group=Diagnostic */

#include <PalmOS.h>
#include <INetMgr.h>

#ifndef TRACE1
  #include "KTrace.h"
#endif

void DbgErrorINet(const Err nErrorCode);

/*----------------------------------------------------------------------------*/
/*Dump Internet Library error codes.
  Range of error codes is (inetErrorClass = 0x1400, exgErrorClass = 0x1500).

  See also: Palm OS Programmer's API Reference: Appendix D. Palm OS Error Codes

  Note: Palm OS specific (PalmOS).
 */
void DbgErrorINet(const Err nErrorCode //[in] error code
                 )
{
    /*Dump most of the Internet Library error codes used by the Palm OS*/
switch (nErrorCode)
  {
  case inetErrNone:                          TRACE0(_T("inetErrNone")                          ); break;/*0x0000 No error*/
  case inetErrorClass:                       TRACE0(_T("inetErrorClass(!)")                    ); break;/*0x1400 Internet Manager class;
                                                                                                          should not be returned as an eror*/
  case inetErrTooManyClients:                TRACE0(_T("inetErrTooManyClients")                ); break;/*0x1401*/
  case inetErrHandleInvalid:                 TRACE0(_T("inetErrHandleInvalid")                 ); break;/*0x1402*/
  case inetErrParamsInvalid:                 TRACE0(_T("inetErrParamsInvalid")                 ); break;/*0x1403*/
  case inetErrURLVersionInvalid:             TRACE0(_T("inetErrURLVersionInvalid")             ); break;/*0x1404*/
  case inetErrURLBufTooSmall:                TRACE0(_T("inetErrURLBufTooSmall")                ); break;/*0x1405*/
  case inetErrURLInvalid:                    TRACE0(_T("inetErrURLInvalid")                    ); break;/*0x1406*/
  case inetErrTooManySockets:                TRACE0(_T("inetErrTooManySockets")                ); break;/*0x1407*/
  case inetErrNoRequestCreated:              TRACE0(_T("inetErrNoRequestCreated")              ); break;/*0x1408*/
  case inetErrNotConnected:                  TRACE0(_T("inetErrNotConnected")                  ); break;/*0x1409*/
  case inetErrInvalidRequest:                TRACE0(_T("inetErrInvalidRequest")                ); break;/*0x140a*/
  case inetErrNeedTime:                      TRACE0(_T("inetErrNeedTime")                      ); break;/*0x140b*/
  case inetErrHostnameInvalid:               TRACE0(_T("inetErrHostnameInvalid")               ); break;/*0x140c*/
  case inetErrInvalidPort:                   TRACE0(_T("inetErrInvalidPort")                   ); break;/*0x140d*/
  case inetErrInvalidHostAddr:               TRACE0(_T("inetErrInvalidHostAddr")               ); break;/*0x140e*/
  case inetErrNilBuffer:                     TRACE0(_T("inetErrNilBuffer")                     ); break;/*0x140f*/
  case inetErrConnectTimeout:                TRACE0(_T("inetErrConnectTimeout")                ); break;/*0x1410*/
  case inetErrResolveTimeout:                TRACE0(_T("inetErrResolveTimeout")                ); break;/*0x1411*/
  case inetErrSendReqTimeout:                TRACE0(_T("inetErrSendReqTimeout")                ); break;/*0x1412*/
  case inetErrReadTimeout:                   TRACE0(_T("inetErrReadTimeout")                   ); break;/*0x1413*/
  case inetErrBufTooSmall:                   TRACE0(_T("inetErrBufTooSmall")                   ); break;/*0x1414*/
  case inetErrSchemeNotSupported:            TRACE0(_T("inetErrSchemeNotSupported")            ); break;/*0x1415*/
  case inetErrInvalidResponse:               TRACE0(_T("inetErrInvalidResponse")               ); break;/*0x1416*/
  case inetErrSettingTooLarge:               TRACE0(_T("inetErrSettingTooLarge")               ); break;/*0x1419*/
  case inetErrSettingSizeInvalid:            TRACE0(_T("inetErrSettingSizeInvalid")            ); break;/*0x141a*/
  case inetErrRequestTooLong:                TRACE0(_T("inetErrRequestTooLong")                ); break;/*0x141b*/
  case inetErrSettingNotImplemented:         TRACE0(_T("inetErrSettingNotImplemented")         ); break;/*0x141c*/
  case inetErrConfigNotFound:                TRACE0(_T("inetErrConfigNotFound")                ); break;/*0x141d*/
  case inetErrConfigCantDelete:              TRACE0(_T("inetErrConfigCantDelete")              ); break;/*0x141e*/
  case inetErrConfigTooMany:                 TRACE0(_T("inetErrConfigTooMany")                 ); break;/*0x141f*/
  case inetErrConfigBadName:                 TRACE0(_T("inetErrConfigBadName")                 ); break;/*0x1420*/
  case inetErrConfigNotAlias:                TRACE0(_T("inetErrConfigNotAlias")                ); break;/*0x1421*/
  case inetErrConfigCantPointToAlias:        TRACE0(_T("inetErrConfigCantPointToAlias")        ); break;/*0x1422*/
  case inetErrConfigEmpty:                   TRACE0(_T("inetErrConfigEmpty")                   ); break;/*0x1423*/
  case inetErrConfigAliasErr:                TRACE0(_T("inetErrConfigAliasErr")                ); break;/*0x1425*/
  case inetErrNoWirelessInterface:           TRACE0(_T("inetErrNoWirelessInterface")           ); break;/*0x1426*/
  case inetErrEncryptionNotAvail:            TRACE0(_T("inetErrEncryptionNotAvail")            ); break;/*0x1427*/
  case inetErrNeedRetryEncSeqNum:            TRACE0(_T("inetErrNeedRetryEncSeqNum")            ); break;/*0x1428*/
  case inetErrNeedRetryEncPublicKey:         TRACE0(_T("inetErrNeedRetryEncPublicKey")         ); break;/*0x1429*/
  case inetErrResponseTooShort:              TRACE0(_T("inetErrResponseTooShort")              ); break;/*0x142a*/
  case inetErrMobitexIllegalOKHost:          TRACE0(_T("inetErrMobitexIllegalOKHost")          ); break;/*0x142b*/
  case inetErrMobitexIllegalBadHost:         TRACE0(_T("inetErrMobitexIllegalBadHost")         ); break;/*0x142c*/
  case inetErrHTTPBadRequest:                TRACE0(_T("inetErrHTTPBadRequest")                ); break;/*0x142d*/
  case inetErrHTTPUnauthorized:              TRACE0(_T("inetErrHTTPUnauthorized")              ); break;/*0x142e*/
  case inetErrHTTPForbidden:                 TRACE0(_T("inetErrHTTPForbidden")                 ); break;/*0x142f*/
  case inetErrHTTPNotFound:                  TRACE0(_T("inetErrHTTPNotFound")                  ); break;/*0x1430*/
  case inetErrHTTPMethodNotAllowed:          TRACE0(_T("inetErrHTTPMethodNotAllowed")          ); break;/*0x1431*/
  case inetErrHTTPNotAcceptable:             TRACE0(_T("inetErrHTTPNotAcceptable")             ); break;/*0x1432*/
  case inetErrHTTPProxyAuthRequired:         TRACE0(_T("inetErrHTTPProxyAuthRequired")         ); break;/*0x1433*/
  case inetErrHTTPRequestTimeout:            TRACE0(_T("inetErrHTTPRequestTimeout")            ); break;/*0x1434*/
  case inetErrHTTPConflict:                  TRACE0(_T("inetErrHTTPConflict")                  ); break;/*0x1435*/
  case inetErrHTTPGone:                      TRACE0(_T("inetErrHTTPGone")                      ); break;/*0x1436*/
  case inetErrHTTPLengthRequired:            TRACE0(_T("inetErrHTTPLengthRequired")            ); break;/*0x1437*/
  case inetErrHTTPPreconditionFailed:        TRACE0(_T("inetErrHTTPPreconditionFailed")        ); break;/*0x1438*/
  case inetErrHTTPRequestTooLarge:           TRACE0(_T("inetErrHTTPRequestTooLarge")           ); break;/*0x1439*/
  case inetErrHTTPRequestURITooLong:         TRACE0(_T("inetErrHTTPRequestURITooLong")         ); break;/*0x143a*/
  case inetErrHTTPUnsupportedType:           TRACE0(_T("inetErrHTTPUnsupportedType")           ); break;/*0x143b*/
  case inetErrHTTPServerError:               TRACE0(_T("inetErrHTTPServerError")               ); break;/*0x143c*/
  case inetErrCTPServerError:                TRACE0(_T("inetErrCTPServerError")                ); break;/*0x143d*/
  case inetErrTypeNotCached:                 TRACE0(_T("inetErrTypeNotCached")                 ); break;/*0x143e*/
  case inetErrCacheInvalid:                  TRACE0(_T("inetErrCacheInvalid")                  ); break;/*0x143f*/
  case inetErrURLDispatched:                 TRACE0(_T("inetErrURLDispatched")                 ); break;/*0x1440*/
  case inetErrDatabaseNotFound:              TRACE0(_T("inetErrDatabaseNotFound")              ); break;/*0x1441*/
  case inetErrCTPMalformedRequest:           TRACE0(_T("inetErrCTPMalformedRequest")           ); break;/*0x1442*/
  case inetErrCTPUnknownCommand:             TRACE0(_T("inetErrCTPUnknownCommand")             ); break;/*0x1443*/
  case inetErrCTPTruncated:                  TRACE0(_T("inetErrCTPTruncated")                  ); break;/*0x1444*/
  case inetErrCTPUnknownError:               TRACE0(_T("inetErrCTPUnknownError")               ); break;/*0x1445*/
  case inetErrCTPProxyError:                 TRACE0(_T("inetErrCTPProxyError")                 ); break;/*0x1446*/
  case inetErrCTPSocketErr:                  TRACE0(_T("inetErrCTPSocketErr")                  ); break;/*0x1447*/
  case inetErrCTPInvalidURL:                 TRACE0(_T("inetErrCTPInvalidURL")                 ); break;/*0x1448*/
  case inetErrCTPReferringPageOutOfDate:     TRACE0(_T("inetErrCTPReferringPageOutOfDate")     ); break;/*0x1449*/
  case inetErrCTPBadRequest:                 TRACE0(_T("inetErrCTPBadRequest")                 ); break;/*0x144a*/
  case inetErrUNUSED:                        TRACE0(_T("inetErrUNUSED")                        ); break;/*0x144b*/
  case inetErrCTPMailServerDown:             TRACE0(_T("inetErrCTPMailServerDown")             ); break;/*0x144c*/
  case inetErrCTPHostNotFound:               TRACE0(_T("inetErrCTPHostNotFound")               ); break;/*0x144d*/
  case inetErrCTPContentInvalidTag:          TRACE0(_T("inetErrCTPContentInvalidTag")          ); break;/*0x144e*/
  case inetErrCTPContentInternal:            TRACE0(_T("inetErrCTPContentInternal")            ); break;/*0x144f*/
  case inetErrCTPContentDataEnd:             TRACE0(_T("inetErrCTPContentDataEnd")             ); break;/*0x1450*/
  case inetErrCTPContentResourceTooBig:      TRACE0(_T("inetErrCTPContentResourceTooBig")      ); break;/*0x1451*/
  case inetErrCTPContentNoNoFrames:          TRACE0(_T("inetErrCTPContentNoNoFrames")          ); break;/*0x1452*/
  case inetErrCTPContentUnsupportedContent:  TRACE0(_T("inetErrCTPContentUnsupportedContent")  ); break;/*0x1453*/
  case inetErrCTPContentUnsupportedEncoding: TRACE0(_T("inetErrCTPContentUnsupportedEncoding") ); break;/*0x1454*/
  case inetErrCTPContentBadForm:             TRACE0(_T("inetErrCTPContentBadForm")             ); break;/*0x1455*/
  case inetErrCTPContentBadFormMissingAction:TRACE0(_T("inetErrCTPContentBadFormMissingAction")); break;/*0x1456*/
  case inetErrCTPContentBadFormMissingMethod:TRACE0(_T("inetErrCTPContentBadFormMissingMethod")); break;/*0x1457*/
  case inetErrCTPContentNoSourceData:        TRACE0(_T("inetErrCTPContentNoSourceData")        ); break;/*0x1458*/
  case inetErrCTPContentBadImage:            TRACE0(_T("inetErrCTPContentBadImage")            ); break;/*0x1459*/
  case inetErrCTPContentImageTooLarge:       TRACE0(_T("inetErrCTPContentImageTooLarge")       ); break;/*0x145a*/
  case inetErrMobitexErrorHandled:           TRACE0(_T("inetErrMobitexErrorHandled")           ); break;/*0x145b  Mobitex illegal handled error code.
                                             This error is sent after
                                             INetLib handles inetErrMobitexIllegalOKHost or inetErrMobitexIllegalBadHost
                                             errors.  The application needs to know that something went wrong and it needs
                                             to change state.  This error does not need to be displayed to the user.
                                              */
  case inetErrProxyDownBadHost:              TRACE0(_T("inetErrProxyDownBadHost")              ); break;/*0x145c*/
  case inetErrHostConnectionLost:            TRACE0(_T("inetErrHostConnectionLost")            ); break;/*0x145d*/
  case inetErrLinkNotFound:                  TRACE0(_T("inetErrLinkNotFound")                  ); break;/*0x145e*/
  case inetErrCacheInvalidSort:              TRACE0(_T("inetErrCacheInvalidSort")              ); break;/*0x145f*/
  default:                                   TRACE0(_T("Unknown error")                        );
  }
TRACE1(_T(" (%d).\n"), (UInt32)nErrorCode);
}
/* ////////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2004-11-09 18:42:12  Darko Kolakovic 
 * $
 *****************************************************************************/
