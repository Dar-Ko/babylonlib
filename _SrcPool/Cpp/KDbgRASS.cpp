/*$Workfile: KDbgRASS.cpp$: implementation file
  $Revision: 1.3 $ $Date: 2003/01/28 05:35:50 $
  $Author: ddarko $

  Dumps RAS connection state
  Copyright: CommonSoft Inc.
  D. Kolakovic May 98
 */

// Group=Diagnostic

#ifdef _DEBUG
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include <Windows.h>
#ifdef WIN16
  #include <win16ext.h> //Required only for win16 applications
#endif
#ifndef _RAS_H_
    #include <RAS.h>    //Remote Access external API
#endif

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//DumpRASConnState()--------------------------------------------------------
/*Dump RAS connection state as a plain text.

  Note: Microsoft Windows specific (Win).
 */
LPTSTR DumpRASConnState(const RASCONNSTATE& rasState)
{
switch (rasState)
  {
  case RASCS_OpenPort           : return "RASCS_OpenPort";
  case RASCS_PortOpened         : return "RASCS_PortOpened";
  case RASCS_ConnectDevice      : return "RASCS_ConnectDevice";
  case RASCS_DeviceConnected    : return "RASCS_DeviceConnected";
  case RASCS_AllDevicesConnected: return "RASCS_AllDevicesConnected";
  case RASCS_Authenticate       : return "RASCS_Authenticate";
  case RASCS_AuthNotify         : return "RASCS_AuthNotify";
  case RASCS_AuthRetry          : return "RASCS_AuthRetry";
  case RASCS_AuthCallback       : return "RASCS_AuthCallback";
  case RASCS_AuthChangePassword : return "RASCS_AuthChangePassword";
  case RASCS_AuthProject        : return "RASCS_AuthProject";
  case RASCS_AuthLinkSpeed      : return "RASCS_AuthLinkSpeed";
  case RASCS_AuthAck            : return "RASCS_AuthAck";
  case RASCS_ReAuthenticate     : return "RASCS_ReAuthenticate";
  case RASCS_Authenticated      : return "RASCS_Authenticated";
  case RASCS_PrepareForCallback : return "RASCS_PrepareForCallback";
  case RASCS_WaitForModemReset  : return "RASCS_WaitForModemReset";
  case RASCS_WaitForCallback    : return "RASCS_WaitForCallback";
  case RASCS_Interactive        : return "RASCS_Interactive";
  case RASCS_RetryAuthentication: return "RASCS_RetryAuthentication";
  case RASCS_CallbackSetByCaller: return "RASCS_CallbackSetByCaller";
  case RASCS_PasswordExpired    : return "RASCS_PasswordExpired";
  case RASCS_Connected          : return "RASCS_Connected";
  case RASCS_Disconnected       : return "RASCS_Disconnected";
  default: return "Unknown RAS Status";
  }
}

///////////////////////////////////////////////////////////////////////////////
#endif //_DEBUG
