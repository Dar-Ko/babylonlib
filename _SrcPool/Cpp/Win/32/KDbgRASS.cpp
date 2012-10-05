/*$Workfile: KDbgRASS.cpp$: implementation file
  $Revision: 5$ $Date: 2004-10-01 22:34:31$
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

#ifndef KCONSTCASE
  #ifdef _UNICODE
    #define KCONSTCASE(idVal) \
      case idVal: szResult = L#idVal; break;
  #else
    #define KCONSTCASE(idVal) \
      case idVal: szResult = #idVal; break;
  #endif
#endif

//DumpRASConnState()--------------------------------------------------------
/*Dump RAS connection state as a plain text.

  Note: Microsoft Windows specific (Win).
 */
LPTSTR DumpRASConnState(const RASCONNSTATE& rasState)
{
LPTSTR szResult = NULL;
switch (rasState)
  {
  KCONSTCASE(RASCS_OpenPort           );
  KCONSTCASE(RASCS_PortOpened         );
  KCONSTCASE(RASCS_ConnectDevice      );
  KCONSTCASE(RASCS_DeviceConnected    );
  KCONSTCASE(RASCS_AllDevicesConnected);
  KCONSTCASE(RASCS_Authenticate       );
  KCONSTCASE(RASCS_AuthNotify         );
  KCONSTCASE(RASCS_AuthRetry          );
  KCONSTCASE(RASCS_AuthCallback       );
  KCONSTCASE(RASCS_AuthChangePassword );
  KCONSTCASE(RASCS_AuthProject        );
  KCONSTCASE(RASCS_AuthLinkSpeed      );
  KCONSTCASE(RASCS_AuthAck            );
  KCONSTCASE(RASCS_ReAuthenticate     );
  KCONSTCASE(RASCS_Authenticated      );
  KCONSTCASE(RASCS_PrepareForCallback );
  KCONSTCASE(RASCS_WaitForModemReset  );
  KCONSTCASE(RASCS_WaitForCallback    );
  KCONSTCASE(RASCS_Interactive        );
  KCONSTCASE(RASCS_RetryAuthentication);
  KCONSTCASE(RASCS_CallbackSetByCaller);
  KCONSTCASE(RASCS_PasswordExpired    );
  KCONSTCASE(RASCS_Connected          );
  KCONSTCASE(RASCS_Disconnected       );
  default: return _T("Unknown RAS Status");
  }
return szResult;
}

///////////////////////////////////////////////////////////////////////////////
#endif //_DEBUG
