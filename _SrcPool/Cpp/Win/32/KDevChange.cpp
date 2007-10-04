/*$Workfile: KLogoOut.cpp$: implementation file
  $Revision: 6$ $Date: 2002-01-29 23:21:26$
  $Author: Darko$

  Handler of PnP Device Notifications.

  Note: Microsoft Windows specific (Win32).

  Copyright: babylonlib.sourceforge.net
  2007-10-02 Darko Kolakovic
 */

// Group=Windows
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

//-----------------------------------------------------------------------------
/*Call this function as part of the WM_DEVICECHANGE message processing.
  The WM_DEVICECHANGE device message notifies an application of a change to
  the hardware configuration of a device or the computer.

  The system notifies through message parameter WPARAM wParam about following
  events:

    - DBT_CONFIGCHANGECANCELED    25. A request to change the current configuration
                                  (dock or undock) has been canceled.
                                  lParam is set to zero.
    - DBT_CONFIGCHANGED           24. The current configuration has changed,
                                  due to a dock or undock.
                                  lParam is set to zero.
    - DBT_CUSTOMEVENT             32774. A custom event has occurred.
                                  lParam is pointer to DEV_BROADCAST_HDR with
                                  dbch_devicetype member describing the device
                                  type.
                                  Windows 95, NT 4.0: This event is not supported.
    - DBT_DEVICEARRIVAL           32768. A device or piece of media has been inserted
                                  and is now available.
                                  lParam is pointer to DEV_BROADCAST_HDR with
                                  dbch_devicetype member describing the device
                                  type.
    - DBT_DEVICEQUERYREMOVE       32769. Permission is requested to remove a device or
                                  piece of media. Any application can deny this
                                  request and cancel the removal. If the system
                                  forcibly removes a device, it may not send the
                                  query before doing so.
                                  lParam is pointer to DEV_BROADCAST_HDR with
                                  dbch_devicetype member describing the device
                                  type.
    - DBT_DEVICEQUERYREMOVEFAILED 32770. A request to remove a device or piece of media
                                  has been canceled.
                                  lParam is pointer to DEV_BROADCAST_HDR with
                                  dbch_devicetype member describing the device
                                  type.
    - DBT_DEVICEREMOVECOMPLETE    32772. A device or piece of media has been removed.
                                  lParam is pointer to DEV_BROADCAST_HDR with
                                  dbch_devicetype member describing the device
                                  type. Windows 2003: If the device type is
                                  DBT_DEVTYP_HANDLE, the dbch_data member is a
                                  pointer to a CLASS_MEDIA_CHANGE_CONTEXT.
    - DBT_DEVICEREMOVEPENDING     32771. A device or piece of media is about to be
                                  removed. Cannot be denied. The system typically
                                  sends this notification for devices with
                                  software-controllable features, such as
                                  ejection and locking.
                                  lParam is pointer to DEV_BROADCAST_HDR with
                                  dbch_devicetype member describing the device
                                  type.
    - DBT_DEVICETYPESPECIFIC      32773. A device-specific event has occurred.
                                  lParam is pointer to DEV_BROADCAST_HDR with
                                  dbch_devicetype member describing the device
                                  type.
    - DBT_DEVNODES_CHANGED        7. A device has been added to or removed from the
                                  system.
                                  lParam is set to zero.
                                  Windows 95, 98, Me, NT 4.0: This event is not supported.
    - DBT_QUERYCHANGECONFIG       23. Permission is requested to change the current
                                  configuration (dock or undock).
                                  lParam is set to zero.
    - DBT_USERDEFINED             65535. The meaning of this message is user-defined.
                                  lParam is pointer to _DEV_BROADCAST_USERDEFINED
                                  with dbud_szName member describing the
                                  user-defined message.

  The responses on the message are TRUE to acknowledge the notification or
  BROADCAST_QUERY_DENY to deny a request.

  Note: Microsoft Windows 98 specific (Win9x);
        Microsoft Windows 2000 specific (Win2k).

  Returns: true

  See also: DeviceInterfaceRegister(), RegisterDeviceNotification(),
  UnregisterDeviceNotification(), WM_DEVICECHANGE.
 */
  bool DeviceChange(UINT nEventType, //[in] event type received
                    //through message parameter wParam
                     PDEV_BROADCAST_HDR pdwData  //[in] event-specific data
                    // received through message parameter lParam
                    )
{
TRACE(_T("DeviceChange() on WM_DEVICECHANGE\n"));
switch(nEventType)
  {
  case DBT_APPYBEGIN: 
    TRACE(_T("  DBT_APPYBEGIN\n"));
    break; // 0
  case DBT_APPYEND:
    TRACE(_T("  DBT_APPYEND\n"));
    break; // 1
  case DBT_DEVNODES_CHANGED:
    TRACE(_T("  DBT_DEVNODES_CHANGED\n"));
    break; // 7
  case DBT_QUERYCHANGECONFIG:
    TRACE(_T("  DBT_QUERYCHANGECONFIG\n"));
    break; //23
  case DBT_CONFIGCHANGED:
    TRACE(_T("  DBT_CONFIGCHANGED\n"));
    break; //24 
  case DBT_CONFIGCHANGECANCELED:
    TRACE(_T("  DBT_CONFIGCHANGECANCELED\n"));
    break; //25
  case DBT_MONITORCHANGE:
    TRACE(_T("  DBT_MONITORCHANGE\n"));
    break; //27 
  case DBT_SHELLLOGGEDON:
    TRACE(_T("  DBT_SHELLLOGGEDON\n"));
    break; //32 
  case DBT_CONFIGMGAPI32:
    TRACE(_T("  DBT_CONFIGMGAPI32\n"));
    break; //34 
  case DBT_VXDINITCOMPLETE:
    TRACE(_T("  DBT_VXDINITCOMPLETE\n"));
    break; //35 
  #if(WINVER >= 0x040A)  
  case DBT_CUSTOMEVENT:
    TRACE(_T("  DBT_CUSTOMEVENT\n"));
    break; //0x8006
  #endif
  case DBT_DEVICEARRIVAL:
    TRACE(_T("  DBT_DEVICEARRIVAL\n"));
    break; //0x8000
  case DBT_DEVICEQUERYREMOVE:
    TRACE(_T("  DBT_DEVICEQUERYREMOVE\n"));
    break; //0x8001
  case DBT_DEVICEQUERYREMOVEFAILED:
    TRACE(_T("  DBT_DEVICEQUERYREMOVEFAILED\n"));
    break; //0x8002
  case DBT_DEVICEREMOVECOMPLETE:
    TRACE(_T("  DBT_DEVICEREMOVECOMPLETE\n"));
    break;//0x8004
  case DBT_DEVICEREMOVEPENDING:
    TRACE(_T("  DBT_DEVICEREMOVEPENDING\n"));
    break; //0x8003
  case DBT_DEVICETYPESPECIFIC:
    TRACE(_T("  DBT_DEVICETYPESPECIFIC\n"));
    break; //0x8005
  case DBT_USERDEFINED:
    TRACE(_T("  DBT_USERDEFINED\n"));
    break; //0xFFFF
    /*
DBT_VOLLOCKQUERYLOCK    0x8041
DBT_VOLLOCKLOCKTAKEN    0x8042
DBT_VOLLOCKLOCKFAILED   0x8043
DBT_VOLLOCKQUERYUNLOCK  0x8044
DBT_VOLLOCKLOCKRELEASED 0x8045
DBT_VOLLOCKUNLOCKFAILED 0x8046
*/    
  default:
    TRACE(_T("  Device change event 0x%.8X\n"), nEventType);
  }
return true;
}


///////////////////////////////////////////////////////////////////////////////
#endif //_WIN32
/*****************************************************************************
 * $Log: $
 *****************************************************************************/
