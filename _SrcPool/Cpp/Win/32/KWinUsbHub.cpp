/*$Workfile: KUsbHub.cpp$: implementation file
  $Revision: 1.5 $ $Date: 2009/07/10 19:41:07 $
  $Author: ddarko $

  Universal Serial Bus (USB) Host Controller
  Note: Microsoft Windows specific (Win).
  Copyright: 1997-1998 Microsoft Corporation
  2004-03-03 Darko Kolakovic
  1997-25-04: Microsoft Corporation
 */

// Group=Windows

#ifdef _WIN32 //Windows 32-bit platform

#if defined _ATL_VER
  #ifndef _USE_ATL
    #define _USE_ATL
  #endif
#endif

#ifdef _USE_ATL
  //Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)
  //or preprocessor reports unpaired #endif directive

  #include "stdafx.h" //Standard system header files
  #include "KTraceAtl.h"
#else
  #include <windows.h>
 // #include <string.h>
#endif

#ifndef TRACE
  #ifndef _T
    #include "KTChar.h"
  #endif
  #include "KTrace.h"
#endif

#include "KUsbHub.h"  //CUsbHub class
#include "KWinUsb.h"  //TUsbSymbolicName template
#ifdef _USE_MSWINDDK
  //USB specific GUID; Microsoft Windows DDK
  //See also: MSDN Article ID: 130869 "How to avoid error 'LNK2001 unresolved
  //external' by using DEFINE_GUID"
  #pragma include_alias( "UsbGuid.h", "wxp/usbiodef" )
#endif
#include "UsbGuid.h" //USB specific GUID

///////////////////////////////////////////////////////////////////////////////

/*Requires setupapi.lib

  Note: If you intend that your device installation application run on
  Windows 9x/Me, or Windows NT 4.0 or earlier, and you use the CM_Xxx functions,
  be sure that cfgmgr32.lib appears before setupapi.lib in the sources file.
  If your application is intended to run only on Windows 2000 or
  a later NT-based operating system, you can omit cfgmgr32.lib.
 */
#pragma comment( lib, "setupapi" )
#include <setupapi.h> //Device Management Structures

///////////////////////////////////////////////////////////////////////////////
//CUsbHostController class implementation

//-----------------------------------------------------------------------------
/*
 */
unsigned int CUsbHostController::FindFirst()
{
TRACE(_T("  CUsbHostController::FindFirst()\n"));
unsigned int nCount = 0;   //number of USB host controllers
/*The system-supplied port driver for a USB host controller registers instances
  of GUID_DEVINTERFACE_USB_HOST_CONTROLLER to notify the operating system and
  applications of the presence of USB host controllers.

  Note: requires <usbiodef.h> from Microsoft DDK
 */
const GUID& guidUsbHc = GUID_DEVINTERFACE_USB_HOST_CONTROLLER;


CString strDevicePath; //device path
extern bool GetDevicePath(const GUID& guidInterfaceClass,
                          const DWORD nMemberIndex, CString& strDevicePath);

while(GetDevicePath(guidUsbHc, //the device interface
                                //class for the requested interface.
                    nCount,     //index to the list of
                                //interfaces in the device information set.
                    strDevicePath //[out] the device path.
                    ))
  {
  extern bool GetDeviceDescription(const GUID& guidDev, //[in]
                    const DWORD nMemberIndex,//[in] index to the list of
                    //interfaces in the device information set.
                    CString& strDeviceDescription //[out]
                    );

  if(!GetDeviceDescription(guidUsbHc,
                      nCount,
                      m_strDescription))
    {
    m_strDescription.Empty();
    }
  #ifdef _UNICODE
    TRACE2(_T("    %d. %ws\n"), nCount, (LPCTSTR)m_strDescription);
  #else
    TRACE2(_T("    %d. %s\n"), nCount, (LPCTSTR)m_strDescription);
  #endif

  //Open a USB Host Controller.
  HANDLE hHcd = CreateFile((LPCTSTR)strDevicePath,
                            GENERIC_WRITE,
                            FILE_SHARE_WRITE,
                            NULL,//if lpSecurityAttributes is NULL,
                                //the handle cannot be inherited.
                            OPEN_EXISTING,
                            0,
                            NULL);
  if (hHcd != INVALID_HANDLE_VALUE)
    {
    #ifdef _UNICODE
      TRACE2(_T("    %d. %ws\n"), nCount, (LPCTSTR)strDevicePath);
    #else
      TRACE2(_T("    %d. %s\n"), nCount, (LPCTSTR)strDevicePath);
    #endif
    GetRootHub(hHcd, m_strName);

    CloseHandle(hHcd);
    }

  nCount++; //Count existing host controllers
  }
return nCount;
}

//-----------------------------------------------------------------------------
/*Enumerates USB Host Controllers.

  Return: number of USB host controllers found on the system.

  See also : EnumerateHostControllers(), EnumerateRootUsbHub()
 */
LPCTSTR CUsbHostController::FindNext()
{
return 0;
}

//-----------------------------------------------------------------------------
/*
 */
bool CUsbHostController::GetRootHub(HANDLE hHostCotroller, //[in] handle to the device
                      //information set that contains the interface
                                    CString& strName //[out]
                                    )
{
TRACE(_T("    CUsbHostController::GetRootHub()\n"));
//Get the hub name; Check GetLastError() in case of failure.
TUsbSymbolicName<USB_ROOT_HUB_NAME,
                  IOCTL_USB_GET_ROOT_HUB_NAME> usbRootHubName(hHostCotroller);
bool bResult = usbRootHubName.IsValid();
if (bResult)
  {
  strName = usbRootHubName.GetName();
  }
else
  strName.Empty();

return bResult;
}

///////////////////////////////////////////////////////////////////////////////
//CUsbHub class implementation


//-----------------------------------------------------------------------------
unsigned int CUsbHub::Enumerate()
{
return 0;
}

///////////////////////////////////////////////////////////////////////////////
#endif //_WIN32

/*****************************************************************************
 * $Log:
 *  5    Biblioteka1.4         2007-08-24 18:15:43  Darko Kolakovic SBCS build
 *  4    Biblioteka1.3         2007-08-24 17:28:43  Darko Kolakovic Debug
 *       information
 *  3    Biblioteka1.2         2007-08-24 10:53:52  Darko Kolakovic Unicode build
 *  2    Biblioteka1.1         2007-08-23 17:21:17  Darko Kolakovic GetDevDesc()
 *  1    Biblioteka1.0         2007-08-22 19:29:10  Darko Kolakovic
 * $
 *****************************************************************************/

/*Note: Used code from Microsoft Windows DDK sample USBView
 */
