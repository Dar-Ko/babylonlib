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
  #ifndef DBT_DEVTYP_DEVICEINTERFACE
    #define DBT_DEVTYP_DEVICEINTERFACE 5
  #endif
  #ifndef DBT_DEVTYP_HANDLE
    #define DBT_DEVTYP_HANDLE 6
  #endif
#endif

//-----------------------------------------------------------------------------
/*Dumps the PnP Device Type Broadcast Notification Event types.

  The system notifies an application through WM_DEVICECHANGE message parameter
  LPARAM lParam about device type caused a change to its state or the computer
  hardware configuration.

  Note: Microsoft Windows 98 specific (Win9x);
        Microsoft Windows 2000 specific (Win2k).

  Returns: zero-terminated string describing device type.

  See also: DeviceInterfaceRegister(), RegisterDeviceNotification(),
  UnregisterDeviceNotification(), WM_DEVICECHANGE.
 */
LPCTSTR DumpDeviceType(PDEV_BROADCAST_HDR pdwData //[in] device  type
                    //received through WM_DEVICECHANGE message parameter lParam
                      )
{
LPCTSTR szResult = _T("<null>");
if (pdwData != NULL)
  {
  switch (pdwData->dbch_devicetype)
    {
    case DBT_DEVTYP_OEM:             szResult = _T("  DBT_DEVTYP_OEM");             break; // 0 OEM-defined device type
    case DBT_DEVTYP_DEVNODE:         szResult = _T("  DBT_DEVTYP_DEVNODE");         break; // 1 devnode number
    case DBT_DEVTYP_VOLUME:          szResult = _T("  DBT_DEVTYP_VOLUME");          break; // 2 logical volume
    case DBT_DEVTYP_PORT:            szResult = _T("  DBT_DEVTYP_PORT");            break; // 3 serial, parallel
    case DBT_DEVTYP_NET:             szResult = _T("  DBT_DEVTYP_NET");             break; // 4 network resource
    case DBT_DEVTYP_DEVICEINTERFACE: szResult = _T("  DBT_DEVTYP_DEVICEINTERFACE"); break; // 5 device interface class
    case DBT_DEVTYP_HANDLE:          szResult = _T("  DBT_DEVTYP_HANDLE");          break; // 6 file system handle
    case DBT_USERDEFINED:            szResult = _T("  DBT_USERDEFINED");            break; //0xFFFF
    default:
      TRACE(_T("  Device type 0x%.8X",pdwData->dbch_devicetype));
      szResult = _T(("Unknown device type"));
    }
  }
return szResult;
}


///////////////////////////////////////////////////////////////////////////////
#endif //_WIN32
/*****************************************************************************
 * $Log: $
 *****************************************************************************/
