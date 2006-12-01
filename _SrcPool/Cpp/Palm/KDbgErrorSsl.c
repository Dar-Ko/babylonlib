/*$Workfile: KDbgErrorSsl.c$: implementation file
  $Revision: 1$ $Date: 2004-11-09 18:42:21$
  $Author: Darko Kolakovic$

  Dumps error code values
  Copyright: CommonSoft Inc.
  2004-11-01 Darko Kolakovic
 */

/* Group=Diagnostic */

#include <PalmOS.h>
#include <SslLib.h>

#ifndef TRACE1
  #include "KTrace.h"
#endif

void DbgErrorSsl(const Err nErrorCode);

/*----------------------------------------------------------------------------*/
/*Dump Secured Sockets Layer (SSL) Library error codes.
  Range of error codes is
    [sslErrorClass = sslErrOk = 0x3900, uilibErrorClass = 0x3a00).

  Secured Sockets Layer is a protocol that transmits your communications over
  the Internet in an encrypted form.

  See also: Palm OS Programmer's API Reference: Appendix D. Palm OS Error Codes

  Note: Palm OS specific (PalmOS).
 */
void DbgErrorSsl(const Err nErrorCode //[in] error code
                )
{
/*These are the possible errors returned from SslLib.
  In addition to these errors, any NetLib errors that occur while SslLib
  is performing network IO will be imediatly returned to the application
 */
switch (nErrorCode)
  {
  case errNone:                              TRACE0(_T("errNone")                          ); break;/*0x0000 No error*/
  case sslErrOk:                             TRACE0(_T("sslErrOk")                             ); break;/*0x3900*/
  //case sslErrorClass:                        TRACE0(_T("sslErrorClass")                        ); break;/*0x3900 SSL errors*/
  case sslErrFailed:                         TRACE0(_T("sslErrFailed")                         ); break;/*0x3901*/
  case sslErrEof:                            TRACE0(_T("sslErrEof")                            ); break;/*0x3902*/
  case sslErrOutOfMemory:                    TRACE0(_T("sslErrOutOfMemory")                    ); break;/*0x3903*/
  case sslErrCbAbort:                        TRACE0(_T("sslErrCbAbort")                        ); break;/*0x3904*/
  case sslErrIo:                             TRACE0(_T("sslErrIo")                             ); break;/*0x3905*/
  case sslErrNotFound:                       TRACE0(_T("sslErrNotFound")                       ); break;/*0x3906*/
  case sslErrDivByZero:                      TRACE0(_T("sslErrDivByZero")                      ); break;/*0x3907*/
  case sslErrNoModInverse:                   TRACE0(_T("sslErrNoModInverse")                   ); break;/*0x3908*/
  case sslErrBadDecode:                      TRACE0(_T("sslErrBadDecode")                      ); break;/*0x3909*/
  case sslErrInitNotCalled:                  TRACE0(_T("sslErrInitNotCalled")                  ); break;/*0x390a*/
  case sslErrBufferTooSmall:                 TRACE0(_T("sslErrBufferTooSmall")                 ); break;/*0x390b*/
  case sslErrNullArg:                        TRACE0(_T("sslErrNullArg")                        ); break;/*0x390c*/
  case sslErrBadLength:                      TRACE0(_T("sslErrBadLength")                      ); break;/*0x390d*/
  case sslErrNoDmem:                         TRACE0(_T("sslErrNoDmem")                         ); break;/*0x390e*/
  case sslErrNoMethodSet:                    TRACE0(_T("sslErrNoMethodSet")                    ); break;/*0x390f*/
  case sslErrNoRandom:                       TRACE0(_T("sslErrNoRandom")                       ); break;/*0x3910*/
  case sslErrBadArgument:                    TRACE0(_T("sslErrBadArgument")                    ); break;/*0x3911*/
  case sslErrBadOption:                      TRACE0(_T("sslErrBadOption")                      ); break;/*0x3912*/
  case sslErrNotImplemented:                 TRACE0(_T("sslErrNotImplemented")                 ); break;/*0x3913*/
  case sslErrReallocStaticData:              TRACE0(_T("sslErrReallocStaticData")              ); break;/*0x3914*/
  case sslErrInternalError:                  TRACE0(_T("sslErrInternalError")                  ); break;/*0x3915*/
  case sslErrRecordError:                    TRACE0(_T("sslErrRecordError")                    ); break;/*0x3925*/
  case sslErrCsp:                            TRACE0(_T("sslErrCsp")                            ); break;/*0x3926*/
  case sslErrCert:                           TRACE0(_T("sslErrCert")                           ); break;/*0x3927*/
  case sslErrHandshakeEncoding:              TRACE0(_T("sslErrHandshakeEncoding")              ); break;/*0x3928*/
  case sslErrMissingProvider:                TRACE0(_T("sslErrMissingProvider")                ); break;/*0x3929*/
  case sslErrHandshakeProtocol:              TRACE0(_T("sslErrHandshakeProtocol")              ); break;/*0x392a*/
  case sslErrExtraHandshakeData:             TRACE0(_T("sslErrExtraHandshakeData")             ); break;/*0x392b*/
  case sslErrWrongMessage:                   TRACE0(_T("sslErrWrongMessage")                   ); break;/*0x392c*/
  case sslErrFatalAlert:                     TRACE0(_T("sslErrFatalAlert")                     ); break;/*0x392d*/
  case sslErrBadPeerFinished:                TRACE0(_T("sslErrBadPeerFinished")                ); break;/*0x392e*/
  case sslErrBadSignature:                   TRACE0(_T("sslErrBadSignature")                   ); break;/*0x392f*/
  case sslErrUnexpectedRecord:               TRACE0(_T("sslErrUnexpectedRecord")               ); break;/*0x3931*/
  case sslErrReadAppData:                    TRACE0(_T("sslErrReadAppData")                    ); break;/*0x3932*/
  case sslErrCertDecodeError:                TRACE0(_T("sslErrCertDecodeError")                ); break;/*0x3933*/
  case sslErrUnsupportedCertType:            TRACE0(_T("sslErrUnsupportedCertType")            ); break;/*0x3934*/
  case sslErrUnsupportedSignatureType:       TRACE0(_T("sslErrUnsupportedSignatureType")       ); break;/*0x3935*/
  case sslErrVerifyBadSignature:             TRACE0(_T("sslErrVerifyBadSignature")             ); break;/*0x3980*/
  case sslErrVerifyNoTrustedRoot:            TRACE0(_T("sslErrVerifyNoTrustedRoot")            ); break;/*0x3981*/
  case sslErrVerifyNotAfter:                 TRACE0(_T("sslErrVerifyNotAfter")                 ); break;/*0x3982*/
  case sslErrVerifyNotBefore:                TRACE0(_T("sslErrVerifyNotBefore")                ); break;/*0x3983*/
  case sslErrVerifyConstraintViolation:      TRACE0(_T("sslErrVerifyConstraintViolation")      ); break;/*0x3984*/
  case sslErrVerifyUnknownCriticalExtension: TRACE0(_T("sslErrVerifyUnknownCriticalExtension") ); break;/*0x3985*/
  case sslErrVerifyCallback:                 TRACE0(_T("sslErrVerifyCallback")                 ); break;/*0x3986*/
  default:                                   TRACE0(_T("Unknown error")                    );
  }
TRACE1(_T(" (%d).\n"), (UInt32)nErrorCode);
}
/* ////////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2004-11-09 18:42:21  Darko Kolakovic 
 * $
 *****************************************************************************/
