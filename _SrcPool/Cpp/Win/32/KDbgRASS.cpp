/*$Workfile: KDbgRASS.cpp$: implementation file
  $Revision: 5$ $Date: 2004-10-01 21:34:31$
  $Author: Darko$

  Dumps RAS connection state
  Copyright: CommonSoft Inc.
  D. Kolakovic May 98
 */

// Group=Diagnostic

#ifdef _DEBUG
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

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

#ifndef _T
  #if !defined _MBCS && !defined _UNICODE
      /*ASCII character (8-bit)*/
    #define _T(x)      x
  #else
    #define _T(x)      L ## x
  #endif
#endif

//DumpRASConnState()--------------------------------------------------------
/*Dump RAS connection state as a plain text.

  Note: Microsoft Windows specific (Win).
 */
LPTSTR DumpRASConnState(const RASCONNSTATE& rasState)
{
switch (rasState)
  {
  case RASCS_OpenPort           : return _T("RASCS_OpenPort");
  case RASCS_PortOpened         : return _T("RASCS_PortOpened");
  case RASCS_ConnectDevice      : return _T("RASCS_ConnectDevice");
  case RASCS_DeviceConnected    : return _T("RASCS_DeviceConnected");
  case RASCS_AllDevicesConnected: return _T("RASCS_AllDevicesConnected");
  case RASCS_Authenticate       : return _T("RASCS_Authenticate");
  case RASCS_AuthNotify         : return _T("RASCS_AuthNotify");
  case RASCS_AuthRetry          : return _T("RASCS_AuthRetry");
  case RASCS_AuthCallback       : return _T("RASCS_AuthCallback");
  case RASCS_AuthChangePassword : return _T("RASCS_AuthChangePassword");
  case RASCS_AuthProject        : return _T("RASCS_AuthProject");
  case RASCS_AuthLinkSpeed      : return _T("RASCS_AuthLinkSpeed");
  case RASCS_AuthAck            : return _T("RASCS_AuthAck");
  case RASCS_ReAuthenticate     : return _T("RASCS_ReAuthenticate");
  case RASCS_Authenticated      : return _T("RASCS_Authenticated");
  case RASCS_PrepareForCallback : return _T("RASCS_PrepareForCallback");
  case RASCS_WaitForModemReset  : return _T("RASCS_WaitForModemReset");
  case RASCS_WaitForCallback    : return _T("RASCS_WaitForCallback");
  case RASCS_Interactive        : return _T("RASCS_Interactive");
  case RASCS_RetryAuthentication: return _T("RASCS_RetryAuthentication");
  case RASCS_CallbackSetByCaller: return _T("RASCS_CallbackSetByCaller");
  case RASCS_PasswordExpired    : return _T("RASCS_PasswordExpired");
  case RASCS_Connected          : return _T("RASCS_Connected");
  case RASCS_Disconnected       : return _T("RASCS_Disconnected");
  default: return _T("Unknown RAS Status");
  }
}

///////////////////////////////////////////////////////////////////////////////
#endif //_DEBUG
