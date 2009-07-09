/*$Workfile: KUsbHub.cpp$: implementation file
  $Revision: 1.4 $ $Date: 2009/07/09 22:15:44 $
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

#ifdef GUID_CLASS_USB_HOST_CONTROLLER
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
//Note: requires <usbiodef.h>
HDEVINFO hDevInfo = 
    SetupDiGetClassDevs((LPGUID)&GUID_CLASS_USB_HOST_CONTROLLER, //a setup class GUID
                        NULL,                   //PnP name of the device
                        NULL,                   //user interface window
                        DIGCF_DEVICEINTERFACE | //list of installed interface class devices
                        DIGCF_PRESENT           //currently present devices
                        );

if (hDevInfo != INVALID_HANDLE_VALUE)
  {
  //Get a context structure for a device information element of
  //the specified device information set.
  SP_DEVICE_INTERFACE_DATA sdiDevinfo; //device instance that is a member of
                            //a device information set.
  sdiDevinfo.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

  while(SetupDiEnumDeviceInterfaces(hDevInfo,//handle to the device information set
                                    NULL, //search for specific interface
                                    (LPGUID)&GUID_CLASS_USB_HOST_CONTROLLER, //a setup
                                         //class GUID device interface class
                                    nCount, //index to the list of interfaces
                                    &sdiDevinfo //[out] device information
                                    ))
    {
    /*Obtain information from Windows Driver Model (WDM) Device Object.
      The WDM stack for a USB device have following layers:

         4. USB Device stack
         3. USB Hub Device stack
         2. USB Host Controller Device stack
         1. PCI Bus Device Stack
     */
    PSP_DEVICE_INTERFACE_DETAIL_DATA psdiDevDetail = NULL;
    DWORD dwSize = 0;
    //Obtain required size of the result buffer
    SetupDiGetDeviceInterfaceDetail(hDevInfo,
                                    &sdiDevinfo,
                                    NULL,
                                    0,
                                    &dwSize,
                                    NULL
                                    );
    psdiDevDetail = (PSP_DEVICE_INTERFACE_DETAIL_DATA) new char[dwSize];
    psdiDevDetail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

    SetupDiGetDeviceInterfaceDetail(hDevInfo,
                                    &sdiDevinfo,
                                    psdiDevDetail,
                                    dwSize,
                                    &dwSize,
                                    NULL  //SP_DEVINFO_DATA structure
                                    );
    //Open a USB Host Controller.
    HANDLE hHcd = CreateFile(psdiDevDetail->DevicePath,
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
        TRACE2(_T("    %d. %ws\n"), nCount, psdiDevDetail->DevicePath);
      #else
        TRACE2(_T("    %d. %s\n"), nCount, psdiDevDetail->DevicePath);
      #endif
      GetRootHub(hHcd, m_strName);

extern void GetDeviceDescription(const GUID& guidDev, //[in]
                   const DWORD nMemberIndex,//[in] index to the list of
                   //interfaces in the device information set.
                   CString& strDeviceDescription //[out]
                   );

GetDeviceDescription(GUID_CLASS_USB_HOST_CONTROLLER,
                     nCount,
                       m_strDescription);

  /*
      TCHAR szBuff[MAX_PATH];
      DWORD dwLen = sizeof(szBuff);
      extern bool GetDeviceProperty(HDEVINFO hDevInfo,
                        SP_DEVINFO_DATA* psdiDevinfo,
                        const DWORD dwProperty,
                        TCHAR* szBuff,
                        DWORD& dwLen);
      //Get a REG_SZ string containing the description of a device. 
      if(GetDeviceProperty(hHcd, //handle to the device information
                            &sdiDevinfo, //device instance
                            SPDRP_DEVICEDESC, //property to be retrieved
                            szBuff,//requested device property
                            dwLen //required buffer size, in bytes
                          ))
        {
        m_strDescription = szBuff;
        }
  */
      CloseHandle(hHcd);
      }

    delete[] psdiDevDetail;
    nCount++; //Count existing host controllers
    }

  SetupDiDestroyDeviceInfoList(hDevInfo);
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
#else
  #error GUID_CLASS_USB_HOST_CONTROLLER is not defined!
#endif //GUID_CLASS_USB_HOST_CONTROLLER

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
