/*$Workfile: KDbgWsaError.c$: implementation file
  $Revision: 1$ $Date: 01/10/2004 10:17:55 PM$
  $Author: Darko$

  Dumps Windows Sockets (WSA) errors
  Copyright: CommonSoft Inc.
  2003-02-01 Darko Kolakovic
 */

/* Group=Diagnostic                                                           */

#include <winsock2.h>
#include "KTrace.h"
    /*Link with required Ws2_32.lib winsocket library */
#pragma comment (lib, "ws2_32")

/*---------------------------------------------------------------------------*/
/*Dumps errors returned by Windows Sockets (WSA)functions .

  Requires Ws2_32.lib.

  Note: Error return codes from gethostbyname() and gethostbyaddr() (when 
  using the resolver). Note that these errors are   retrieved via
  WSAGetLastError() and must therefore follow the rules for avoiding clashes
  with error numbers from specific implementations or language run-time
  systems.
  For this reason the codes are based at WSABASEERR+1001. Note also that
  [WSA]NO_ADDRESS is defined only for compatibility purposes.

  Note: Microsoft Windows specific (Win).
  See also: <winsock.h>, <winsock2.h>
 */
void DumpWsaError()
{
int iWsaError;
switch(iWsaError = WSAGetLastError())
  {
  case 0: /*No errors*/
      break;
    /*Windows Sockets definitions of regular Microsoft C error constants*/
  case WSAEINTR:
    TRACE1("  WSAEINTR (%d) A blocking Windows Socket 1.1 call was canceled through\
 WSACancelBlockingCall.\n", iWsaError);
    break;
  case WSAEBADF              : TRACE1("  WSAEBADF (%d)\n",iWsaError); break;
  case WSAEACCES             : TRACE1("  WSAEACCES (%d)\n",iWsaError); break;
  case WSAEFAULT:
    TRACE1("  WSAEFAULT (%d) The name parameter is not a valid part of the user\
 address space.\n", iWsaError);
    break;
  case WSAEINVAL             : TRACE1("  WSAEINVAL (%d)\n",iWsaError); break;
  case WSAEMFILE             : TRACE1("  WSAEMFILE (%d)\n",iWsaError); break;
/*
 * Windows Sockets definitions of regular Berkeley error constants
 */
  case WSAEWOULDBLOCK        : TRACE1("  WSAEWOULDBLOCK     (%d)\n",iWsaError); break;
  case WSAEINPROGRESS:
    TRACE1("  WSAEINPROGRESS (%d) A blocking Windows Sockets 1.1 call is in progress,\
 or the service provider is still processing a callback function.\n", iWsaError);
    break;
  case WSAEALREADY           : TRACE1("  WSAEALREADY (%d)\n",iWsaError); break;
  case WSAENOTSOCK           : TRACE1("  WSAENOTSOCK (%d)\n",iWsaError); break;
  case WSAEDESTADDRREQ       : TRACE1("  WSAEDESTADDRREQ (%d)\n",iWsaError); break;
  case WSAEMSGSIZE           : TRACE1("  WSAEMSGSIZE (%d)\n",iWsaError); break;
  case WSAEPROTOTYPE         : TRACE1("  WSAEPROTOTYPE (%d)\n",iWsaError); break;
  case WSAENOPROTOOPT        : TRACE1("  WSAENOPROTOOPT (%d)\n",iWsaError); break;
  case WSAEPROTONOSUPPORT    : TRACE1("  WSAEPROTONOSUPPORT (%d)\n",iWsaError); break;
  case WSAESOCKTNOSUPPORT    : TRACE1("  WSAESOCKTNOSUPPORT (%d)\n",iWsaError); break;
  case WSAEOPNOTSUPP         : TRACE1("  WSAEOPNOTSUPP (%d)\n",iWsaError); break;
  case WSAEPFNOSUPPORT       : TRACE1("  WSAEPFNOSUPPORT (%d)\n",iWsaError); break;
  case WSAEAFNOSUPPORT       : TRACE1("  WSAEAFNOSUPPORT (%d)\n",iWsaError); break;
  case WSAEADDRINUSE         : TRACE1("  WSAEADDRINUSE (%d)\n",iWsaError); break;
  case WSAEADDRNOTAVAIL      : TRACE1("  WSAEADDRNOTAVAIL (%d)\n",iWsaError); break;
  case WSAENETDOWN:
    TRACE1("  WSAENETDOWN (%d) The network subsystem has failed.\n", iWsaError);
    break;
  case WSAENETUNREACH        : TRACE1("  WSAENETUNREACH (%d)\n",iWsaError); break;
  case WSAENETRESET          : TRACE1("  WSAENETRESET (%d)\n",iWsaError); break;
  case WSAECONNABORTED       : TRACE1("  WSAECONNABORTED (%d)\n",iWsaError); break;
  case WSAECONNRESET         : TRACE1("  WSAECONNRESET (%d)\n",iWsaError); break;
  case WSAENOBUFS            : TRACE1("  WSAENOBUFS (%d)\n",iWsaError); break;
  case WSAEISCONN            : TRACE1("  WSAEISCONN (%d)\n",iWsaError); break;
  case WSAENOTCONN           : TRACE1("  WSAENOTCONN (%d)\n",iWsaError); break;
  case WSAESHUTDOWN          : TRACE1("  WSAESHUTDOWN (%d)\n",iWsaError); break;
  case WSAETOOMANYREFS       : TRACE1("  WSAETOOMANYREFS (%d)\n",iWsaError); break;
  case WSAETIMEDOUT          : TRACE1("  WSAETIMEDOUT (%d)\n",iWsaError); break;
  case WSAECONNREFUSED       : TRACE1("  WSAECONNREFUSED (%d)\n",iWsaError); break;
  case WSAELOOP              : TRACE1("  WSAELOOP (%d)\n",iWsaError); break;
  case WSAENAMETOOLONG       : TRACE1("  WSAENAMETOOLONG (%d)\n",iWsaError); break;
  case WSAEHOSTDOWN          : TRACE1("  WSAEHOSTDOWN (%d)\n",iWsaError); break;
  case WSAEHOSTUNREACH       : TRACE1("  WSAEHOSTUNREACH (%d)\n",iWsaError); break;
  case WSAENOTEMPTY          : TRACE1("  WSAENOTEMPTY (%d)\n",iWsaError); break;
  case WSAEPROCLIM           : TRACE1("  WSAEPROCLIM (%d)\n",iWsaError); break;
  case WSAEUSERS             : TRACE1("  WSAEUSERS (%d)\n",iWsaError); break;
  case WSAEDQUOT             : TRACE1("  WSAEDQUOT (%d)\n",iWsaError); break;
  case WSAESTALE             : TRACE1("  WSAESTALE (%d)\n",iWsaError); break;
  case WSAEREMOTE            : TRACE1("  WSAEREMOTE (%d)\n",iWsaError); break;

    /*Extended Windows Sockets error constant definitions */
  case WSASYSNOTREADY        : TRACE1("  WSASYSNOTREADY (%d)\n",iWsaError); break;
  case WSAVERNOTSUPPORTED    : TRACE1("  WSAVERNOTSUPPORTED (%d)\n",iWsaError); break;
  case WSANOTINITIALISED:
    TRACE1("  WSANOTINITIALISED (%d) A successful WSAStartup call must occur before \
 using this function.\n", iWsaError);
    break;
  case WSAEDISCON            : TRACE1("  WSAEDISCON (%d)\n",iWsaError); break;
  case WSAENOMORE            : TRACE1("  WSAENOMORE (%d)\n",iWsaError); break;
  case WSAECANCELLED         : TRACE1("  WSAECANCELLED (%d)\n",iWsaError); break;
  case WSAEINVALIDPROCTABLE  : TRACE1("  WSAEINVALIDPROCTABLE (%d)\n",iWsaError); break;
  case WSAEINVALIDPROVIDER   : TRACE1("  WSAEINVALIDPROVIDER (%d)\n",iWsaError); break;
  case WSAEPROVIDERFAILEDINIT: TRACE1("  WSAEPROVIDERFAILEDINIT(%d)\n",iWsaError); break;
  case WSASYSCALLFAILURE     : TRACE1("  WSASYSCALLFAILURE (%d)\n",iWsaError); break;
  case WSASERVICE_NOT_FOUND  : TRACE1("  WSASERVICE_NOT_FOUND (%d)\n",iWsaError); break;
  case WSATYPE_NOT_FOUND     : TRACE1("  WSATYPE_NOT_FOUND (%d)\n",iWsaError); break;
  case WSA_E_NO_MORE         : TRACE1("  WSA_E_NO_MORE (%d)\n",iWsaError); break;
  case WSA_E_CANCELLED       : TRACE1("  WSA_E_CANCELLED (%d)\n",iWsaError); break;
  case WSAEREFUSED           : TRACE1("  WSAEREFUSED (%d)\n",iWsaError); break;
    /*HOST_NOT_FOUND Authoritative Answer: Host not found */
  case WSAHOST_NOT_FOUND:
    TRACE1("  WSAHOST_NOT_FOUND (%d) Authoritative answer host not found.\n", iWsaError);
    break;
    /*TRY_AGAIN Non-Authoritative: Host not found, or SERVERFAIL */
  case WSATRY_AGAIN:
    TRACE1("  WSATRY_AGAIN (%d) Nonauthoritative host not found, or server\
 failure.\n", iWsaError);
    break;
    /*NO_RECOVERY Non-recoverable errors, FORMERR, REFUSED, NOTIMP */
  case WSANO_RECOVERY:
    TRACE1("  WSANO_RECOVERY (%d) A nonrecoverable error occurred.\n", iWsaError);
    break;
    /*NO_DATA Valid name, no data record of requested type */
  case WSANO_DATA:
    TRACE1("  WSANO_DATA (%d) Valid name, no data record of requested type.\n",
           iWsaError);
    /*WSANO_ADDRESS = WSANO_DATA; drop down */
    /*NO_ADDRESS No address, look for MX record */
    TRACE1("  WSANO_ADDRESS (%d)\n",iWsaError); break;

    /*Define QOS related error return codes */
         /*At least one Reserve has arrived */
  case  WSA_QOS_RECEIVERS               : TRACE1("  WSA_QOS_RECEIVERS (%d)\n",iWsaError); break;
         /*At least one Path has arrived */
  case  WSA_QOS_SENDERS                 : TRACE1("  WSA_QOS_SENDERS (%d)\n",iWsaError); break;
         /*There are no senders */
  case  WSA_QOS_NO_SENDERS              : TRACE1("  WSA_QOS_NO_SENDERS (%d)\n",iWsaError); break; 
         /*There are no receivers */
  case  WSA_QOS_NO_RECEIVERS            : TRACE1("  WSA_QOS_NO_RECEIVERS (%d)\n",iWsaError); break;
         /*Reserve has been confirmed */
  case  WSA_QOS_REQUEST_CONFIRMED       : TRACE1("  WSA_QOS_REQUEST_CONFIRMED (%d)\n",iWsaError); break;
         /*Error due to lack of resources */
  case  WSA_QOS_ADMISSION_FAILURE       : TRACE1("  WSA_QOS_ADMISSION_FAILURE (%d)\n",iWsaError); break;
         /*Rejected for administrative reasons - bad credentials */
  case  WSA_QOS_POLICY_FAILURE          : TRACE1("  WSA_QOS_POLICY_FAILURE (%d)\n",iWsaError); break;
         /*Unknown or conflicting style */
  case  WSA_QOS_BAD_STYLE               : TRACE1("  WSA_QOS_BAD_STYLE (%d)\n",iWsaError); break;
         /*Problem with some part of the filterspec or providerspecific
           buffer in general */
  case  WSA_QOS_BAD_OBJECT              : TRACE1("  WSA_QOS_BAD_OBJECT (%d)\n",iWsaError); break;
         /*Problem with some part of the flowspec */
  case  WSA_QOS_TRAFFIC_CTRL_ERROR      : TRACE1("  WSA_QOS_TRAFFIC_CTRL_ERROR (%d)\n",iWsaError); break;
         /*General error */
  case  WSA_QOS_GENERIC_ERROR           : TRACE1("  WSA_QOS_GENERIC_ERROR (%d)\n",iWsaError); break;

    default:
      TRACE1("  (%d) unknown Windows Sockets error.\n", iWsaError);
  }
}
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         01/10/2004 10:17:55 PMDarko           
 * $
 * Revision 1.1  2004/08/01 14:59:19  dkolakovic
 * added DumpWsaError()
 *
 *****************************************************************************/
