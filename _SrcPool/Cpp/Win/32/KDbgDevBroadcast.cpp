/*$Workfile: KLogoOut.cpp$: implementation file
  $Revision: 6$ $Date: 2002-01-29 23:21:26$
  $Author: Darko$

  Dumps the PnP Device Broadcast Notification Event types.

  Note: Microsoft Windows specific (Win32).

  Copyright: babylonlib.sourceforge.net
  2007-10-02 Darko Kolakovic
 */

// Group=Diagnostic
#ifdef _WIN32

#if defined _USE_ATL || defined _USE_MFC
  //Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)
  //or preprocessor reports unpaired #endif directive

  #include "stdafx.h" //Standard system header files

#else
  #include <windows.h>
#endif
#include <dbt.h>

#if defined _ATL_VER
  #ifndef TRACE
    #define TRACE ATLTRACE
    #define TRACE1 ATLTRACE
    #define TRACE2 ATLTRACE
  #endif
#endif

#ifndef TRACE
  #ifndef _T
    #include "KTChar.h"
  #endif
  #include "KTrace.h"
#endif

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

#if(WINVER < 0x040A)
  #ifndef DBT_CUSTOMEVENT
    #define DBT_CUSTOMEVENT 0x8006
  #endif
#endif

//-----------------------------------------------------------------------------
/*Dumps the PnP Device Broadcast Notification Event types.

  The system notifies an application through WM_DEVICECHANGE message parameter
  WPARAM wParam about changes to the hardware configuration of a device or
  the computer.

  Note: Microsoft Windows 98 specific (Win9x);
        Microsoft Windows 2000 specific (Win2k).

  Returns: zero-terminated string describing notification event.

  See also: DeviceInterfaceRegister(), RegisterDeviceNotification(),
  UnregisterDeviceNotification(), WM_DEVICECHANGE.
 */
LPCTSTR DumpDeviceBroadcastEvent(UINT nEventType, //[in] event type received
                                 //through message parameter wParam
                                )
{
LPCTSTR szResult;
switch(nEventType)
  {
  case DBT_APPYBEGIN:               szResult = _T("  DBT_APPYBEGIN");               break; // 0
  case DBT_APPYEND:                 szResult = _T("  DBT_APPYEND");                 break; // 1
  case DBT_DEVNODES_CHANGED:        szResult = _T("  DBT_DEVNODES_CHANGED");        break; // 7
  case DBT_QUERYCHANGECONFIG:       szResult = _T("  DBT_QUERYCHANGECONFIG");       break; //23
  case DBT_CONFIGCHANGED:           szResult = _T("  DBT_CONFIGCHANGED");           break; //24
  case DBT_CONFIGCHANGECANCELED:    szResult = _T("  DBT_CONFIGCHANGECANCELED");    break; //25
  case DBT_MONITORCHANGE:           szResult = _T("  DBT_MONITORCHANGE");           break; //27
  case DBT_SHELLLOGGEDON:           szResult = _T("  DBT_SHELLLOGGEDON");           break; //32
  case DBT_CONFIGMGAPI32:           szResult = _T("  DBT_CONFIGMGAPI32");           break; //34
  case DBT_VXDINITCOMPLETE:         szResult = _T("  DBT_VXDINITCOMPLETE");         break; //35
  case DBT_CUSTOMEVENT:             szResult = _T("  DBT_CUSTOMEVENT");             break; //0x8006
  case DBT_DEVICEARRIVAL:           szResult = _T("  DBT_DEVICEARRIVAL");           break; //0x8000
  case DBT_DEVICEQUERYREMOVE:       szResult = _T("  DBT_DEVICEQUERYREMOVE");       break; //0x8001
  case DBT_DEVICEQUERYREMOVEFAILED: szResult = _T("  DBT_DEVICEQUERYREMOVEFAILED"); break; //0x8002
  case DBT_DEVICEREMOVECOMPLETE:    szResult = _T("  DBT_DEVICEREMOVECOMPLETE");    break; //0x8004
  case DBT_DEVICEREMOVEPENDING:     szResult = _T("  DBT_DEVICEREMOVEPENDING");     break; //0x8003
  case DBT_DEVICETYPESPECIFIC:      szResult = _T("  DBT_DEVICETYPESPECIFIC");      break; //0x8005
  case DBT_VOLLOCKQUERYLOCK:        szResult = _T("  DBT_VOLLOCKQUERYLOCK");        break; //0x8041
  case DBT_VOLLOCKLOCKTAKEN:        szResult = _T("  DBT_VOLLOCKLOCKTAKEN");        break; //0x8042
  case DBT_VOLLOCKLOCKFAILED:       szResult = _T("  DBT_VOLLOCKLOCKFAILED");       break; //0x8043
  case DBT_VOLLOCKQUERYUNLOCK:      szResult = _T("  DBT_VOLLOCKQUERYUNLOCK");      break; //0x8044
  case DBT_VOLLOCKLOCKRELEASED:     szResult = _T("  DBT_VOLLOCKLOCKRELEASED");     break; //0x8045
  case DBT_VOLLOCKUNLOCKFAILED:     szResult = _T("  DBT_VOLLOCKUNLOCKFAILED");     break; //0x8046
  case DBT_USERDEFINED:             szResult = _T("  DBT_USERDEFINED");             break; //0xFFFF

  default:
    {
    TRACE(_T("  Device change event 0x%.8X "), nEventType);
    szResult = _T("  Unknown event");
    }
  }
return szResult;
}


///////////////////////////////////////////////////////////////////////////////
#endif //_WIN32
/*****************************************************************************
 * $Log: $
 *****************************************************************************/
