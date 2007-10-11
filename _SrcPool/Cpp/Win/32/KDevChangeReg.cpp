/*$Workfile: KLogoOut.cpp$: implementation file
  $Revision: 6$ $Date: 2002-01-29 23:21:26$
  $Author: Darko$

  Registering for PnP Device Notification.

  Note: Microsoft Windows specific (Win32).

  Copyright: babylonlib.sourceforge.net
  2007-10-01 Darko Kolakovic
  1999-11-23 Microsoft DDK 2600.1106
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
#include <dbt.h> //DEV_BROADCAST_DEVICEINTERFACE struct

#if(WINVER < 0x0500)
  #pragma message(__FILE__ "(31) : warning: Requires Windows Vista, Windows XP, Windows 2000 Professional, Windows Me or Windows 98.")
  #define RegisterDeviceNotification(h,n,f) (NULL) //not supported function
  typedef  PVOID           HDEVNOTIFY;
#else
  #if(_WIN32_WINNT < 0x0501)
    #pragma message(__FILE__ "(34) : warning: DEVICE_NOTIFY_ALL_INTERFACE_CLASSES requires Windows Vista or Windows XP.")
    #define DEVICE_NOTIFY_ALL_INTERFACE_CLASSES  0x00000004 //Unused flag
  #endif
#endif

#if _MSC_VER >= 700
  #define _USE_DEVICE_NOTIFY 20071001
#endif

#ifndef _USE_DEVICE_NOTIFY
  //Substitute missing definitions from MSVC 6.0 winuser.h header file
  //See also: <winuser.h>
  #define _USE_DEVICE_NOTIFY 20071003

  #define DEVICE_NOTIFY_WINDOW_HANDLE          0x00000000
  #ifndef DEVICE_NOTIFY_ALL_INTERFACE_CLASSES
    #define DEVICE_NOTIFY_ALL_INTERFACE_CLASSES  0x00000004
  #endif
  typedef  PVOID        HDEVNOTIFY;
  typedef  HDEVNOTIFY *PHDEVNOTIFY;

  WINUSERAPI HDEVNOTIFY WINAPI RegisterDeviceNotificationA(IN HANDLE hRecipient,
                                                   IN LPVOID NotificationFilter,
                                                   IN DWORD Flags);
  WINUSERAPI HDEVNOTIFY WINAPI RegisterDeviceNotificationW(IN HANDLE hRecipient,
                                                   IN LPVOID NotificationFilter,
                                                   IN DWORD Flags);
  #ifndef RegisterDeviceNotification
    #if defined UNICODE || defined _UNICODE
      #define RegisterDeviceNotification  RegisterDeviceNotificationW
    #else
      #define RegisterDeviceNotification  RegisterDeviceNotificationA
    #endif // !UNICODE
  #endif

#endif

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

//-----------------------------------------------------------------------------
/*Call this function to register a recipient window object for notification of
  changes in the Plug-and-Play (PnP) device interfaces for the given
  interface class GUID.
  Device notification handles returned by the function must be closed by
  calling the UnregisterDeviceNotification() function when they are
  no longer needed.

  Any application with a top-level window can receive basic notifications by
  processing the WM_DEVICECHANGE message. Event DBT_DEVTYP_VOLUME for sound
  notifucation and DBT_DEVICEARRIVAL, DBT_DEVICEREMOVECOMPLETE events for
  devices using ports are also automatically  broadcast to all top-level windows.
  Other types of application, like services, have to be registered to PnP
  manager for device notifications.

  Note: Be sure to handle Plug and Play device events as quickly as possible,
  even in another thread. Otherwise, the system may become unresponsive.

  Note: For Microsoft Windows XP, 2003, Vista and later, recipient will be notified
  of device interface events for all device interface classes and guidInterfaceClass
  parameter is ignored. This parameter have to be specified for Microsoft
  Windows 98 and 2000.

  Returns: the device notification handle or NULL in case of a failure.
  To get extended error information, call GetLastError().

  Note: Microsoft Windows 98 specific (Win9x);
        Microsoft Windows 2000 specific (Win2k).

  See also: RegisterDeviceNotification(), UnregisterDeviceNotification(),
  WM_DEVICECHANGE, OnDeviceChange(), <winioctl.h> for GUID
 */
HDEVNOTIFY DeviceInterfaceRegister(HWND hRecipient, //[in] window handle to send
                              //notifications to. If hRecipient is a service
                              //status handle, SERVICE_CONTROL_DEVICEEVENT
                              //notifications are sent to the service control
                              //handler
                                GUID* pguidInterfaceClass //[in] interface class
                              //GUID for the device interfaces or NULL to receive
                              //notifications for all device interface classes.
                              )
{
TRACE(_T("DeviceInterfaceRegister()\n"));
#if(WINVER >= 0x040A) //Requires Windows Millenium or later
  DEV_BROADCAST_DEVICEINTERFACE NotificationFilter;
  ZeroMemory( &NotificationFilter, sizeof(NotificationFilter) );
  DWORD dwFlags = DEVICE_NOTIFY_WINDOW_HANDLE;  //the hRecipient parameter is 
                 //a window. For a service use DEVICE_NOTIFY_SERVICE_HANDLE.
                 
  //Configure event filter
  NotificationFilter.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
  /*Fails if the dbch_devicetype member is DBT_DEVTYP_PORT, DBT_DEVTYP_VOLUME
    or DBT_DEVTYP_OEM. This types are handled differently by the system.
   */
  NotificationFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
  if (pguidInterfaceClass != NULL)
    NotificationFilter.dbcc_classguid = *pguidInterfaceClass;
  else
    {
    GUID guidDummy = { 0x0, 0x0, 0x0, 0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08 };
    NotificationFilter.dbcc_classguid = guidDummy;
    dwFlags = dwFlags | DEVICE_NOTIFY_ALL_INTERFACE_CLASSES; //Notifies 
                                     //the recipient of device interface events about
                                     //all device interface classes. 
                                     //The dbcc_classguid member is ignored 
                                     //(WinXP and above only).
    } 
#else
  #pragma message(__FILE__ "(153) : warning: Requires Windows 2000 Professional, Windows 98 4.10 or later.")
  SetLastError(ERROR_NOT_SUPPORTED); //The function is replaced with NULL; see the prolog.
#endif

HDEVNOTIFY hDevNotify =
               RegisterDeviceNotification( hRecipient, //Handle to the window or service that
                            //will receive device events for the devices specified
                            //in the NotificationFilter parameter.
                            //The same window handle can be used in multiple calls
                            //to RegisterDeviceNotification.
                            //Services can specify either a window handle
                            //or service status handle.

                                        &NotificationFilter, //type of device for
                            //which notifications should be sent
                                        dwFlags //type recipient handle.
                                      );
#ifdef _DEBUG
  if (hDevNotify == NULL)
    TRACE(_T("  Failed to register: 0x%0.8X!\n"), GetLastError());
#endif

return hDevNotify;
}
///////////////////////////////////////////////////////////////////////////////
#endif //_WIN32
/*****************************************************************************
 * $Log: $
 * 2007-10-01 Darko Kolakovic Added Windows version validation
 *****************************************************************************/

/*Copyright (c) Microsoft Corporation.  All rights reserved.

    THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
    KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
    PURPOSE.
 */
