/*$Workfile: KUsbHub.cpp$: implementation file
  $Revision: 1.8 $ $Date: 2009/07/13 09:29:43 $
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
//CUsbDeviceTree class implementation

//-----------------------------------------------------------------------------
/*
 */
int CUsbDeviceTree::Enumerate()
{
TRACE(_T("CUsbDeviceTree::Enumerate()\n"));

int iCount = 0;
CUsbHostController usbHc;
while(usbHc.GetDeviceInfo(iCount))
  {
  m_usbRootList.Add(usbHc);
  iCount++;
  }
return iCount;
}

///////////////////////////////////////////////////////////////////////////////
//CUsbHostController class implementation

//-----------------------------------------------------------------------------
/*Retrieves information about USB host controller.
  Returns true if device is found in the list of available devices.

  Example:

    unsigned int nCount = 0;
    CUsbHostController usbRootHub;
    while(usbRootHub.GetDeviceInfo(nCount))
      {
      TRACE1(_T("%d. %s\n"), nCount, (LPCSTR)usbRootHub.m_strDescription);
      nCount++;
      }
    TRACE1(_T("Number of host controllers: %d."), nCount);
 */
bool CUsbHostController::GetDeviceInfo(const unsigned int nMemberIndex //[in] = 0
                                       //index to the list of interfaces in
                                       //the device information set.
                                       )
{
TRACE1(_T("  CUsbHostController::GetDeviceInfo(device index = %d)\n"), nMemberIndex);
bool bResult = false;
/*The system-supplied port driver for a USB host controller registers instances
  of GUID_DEVINTERFACE_USB_HOST_CONTROLLER to notify the operating system and
  applications of the presence of USB host controllers.

  Note: requires <usbiodef.h> from Microsoft DDK
 */
const GUID& guidUsbHc = GUID_DEVINTERFACE_USB_HOST_CONTROLLER;


CString strDevicePath; //device path
extern bool GetDevicePath(const GUID& guidInterfaceClass,
                          const DWORD nMemberIndex, CString& strDevicePath);

if(GetDevicePath(guidUsbHc,    //the device interface
                               //class for the requested interface.
                 nMemberIndex, //index to the list of
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
                      nMemberIndex,
                      m_strDescription))
    {
    m_strDescription.Empty();
    }
  #ifdef _UNICODE
    TRACE2(_T("    %d. %ws\n"), nMemberIndex, (LPCTSTR)m_strDescription);
  #else
    TRACE2(_T("    %d. %s\n"), nMemberIndex, (LPCTSTR)m_strDescription);
  #endif

  if (GetRootHub((LPCTSTR)strDevicePath, m_strDevice))
    {
    #ifdef _UNICODE
      TRACE2(_T("    %d. %ws\n"), nMemberIndex, (LPCTSTR)m_strDevice);
    #else
      TRACE2(_T("    %d. %s\n"), nMemberIndex, (LPCTSTR)m_strDevice);
    #endif
    m_nPortCount = Enumerate((LPCTSTR)m_strDevice); //Enumerate USB ports 
    if (m_nPortCount > 0)
      bResult = true;
    }
  else
    m_strDevice.Empty();

  }
return bResult;
}

//-----------------------------------------------------------------------------
/*Retreive device path of the hub embedded into host controller.
  
  Returns true if successful and the USB root hub device path, otherwise
  returns false.
 */
bool CUsbHostController::GetRootHub(LPCTSTR szDevicePath, //[in] the USB host 
                                    //controller device path.
                                    CString& strRootHubPath //[out] the USB root hub 
                                    //device path
                                    )
{
TRACE(_T("    CUsbHostController::GetRootHub()\n"));
bool bResult = false;
//Open a USB Host Controller.
HANDLE hHostController = CreateFile(szDevicePath,
                          GENERIC_WRITE,
                          FILE_SHARE_WRITE,
                          NULL,//if lpSecurityAttributes is NULL,
                              //the handle cannot be inherited.
                          OPEN_EXISTING,
                          0,
                          NULL);
if (hHostController != INVALID_HANDLE_VALUE)
  {
  //Get the hub name; Check GetLastError() in case of failure.
  TUsbSymbolicName<USB_ROOT_HUB_NAME,
                    IOCTL_USB_GET_ROOT_HUB_NAME> usbRootHubName(hHostController);
  if (usbRootHubName.IsValid())
    {
    strRootHubPath = usbRootHubName.GetName();
    bResult = true;
    }
  else
    {
    TRACE1(_T("      Failed! Error 0x%0.8X.\n"), GetLastError());
    }
  CloseHandle(hHostController);
  }

return bResult;
}


///////////////////////////////////////////////////////////////////////////////
//CUsbHub class implementation
#include "UsbIoCtl.h"//USB_NODE_CONNECTION_INFORMATION_EX


//-----------------------------------------------------------------------------
/*Enumerate USB hub ports.

  Returns number of availabile USB ports or 0 in case of a failure. Use
  GetLasteError() to obtain error code.
 */
unsigned int CUsbHub::Enumerate(LPCTSTR szDevicePath //[out] the USB hub 
                                    //device path
                                )
{
TRACE(_T("    CUsbHub::Enumerate()\n"));
unsigned int dwPortCount = 0;

if ((szDevicePath != NULL) && (szDevicePath[0] != _T('\0')) )
  {
  //Open the connection with the hub
  HANDLE hHub = CreateFile(szDevicePath,
                            GENERIC_WRITE,
                            FILE_SHARE_WRITE,
                            NULL,//if lpSecurityAttributes is NULL,
                                //the handle cannot be inherited.
                            OPEN_EXISTING,
                            0,
                            NULL);
  if (hHub != INVALID_HANDLE_VALUE)
    {
    //Obtain the hub information
    DWORD nBytesReturned; //number of bytes stored in the result buffer
    USB_NODE_INFORMATION usbHubNodeInfo;
    usbHubNodeInfo.NodeType = UsbHub; //parent hub device
    unsigned int nBytes = sizeof(USB_NODE_INFORMATION);
    if (DeviceIoControl(hHub, 
                        IOCTL_USB_GET_NODE_INFORMATION, 
                        &usbHubNodeInfo, 
                        nBytes, 
                        &usbHubNodeInfo, 
                        nBytes, 
                        &nBytesReturned, //unused
                        NULL))
      {
      #ifdef _DEBUG
        USB_HUB_DESCRIPTOR& usbDbgHubInfo = usbHubNodeInfo.u.HubInformation.HubDescriptor;
        TRACE1(_T("      number of ports = %d.\n"), usbDbgHubInfo.bNumberOfPorts);
        TRACE1(_T("      descriptor type = 0x%X.\n"), usbDbgHubInfo.bDescriptorType);
        TRACE1(_T("      startup time    = %d ms.\n"), (usbDbgHubInfo.bPowerOnToPowerGood * 2));
        (usbHubNodeInfo.u.HubInformation.HubIsBusPowered == FALSE) ? 
            TRACE(_T("      self-powered\n")) : 
            TRACE(_T("      bus-powered\n"));
        TRACE1(_T("      controller consumption = %d mA.\n"), usbDbgHubInfo.bHubControlCurrent);
      #endif
      dwPortCount = usbHubNodeInfo.u.HubInformation.HubDescriptor.bNumberOfPorts;

      //Obtain information about every device attached to the hub
      #if (_WIN32_WINNT >= 0x0501)
        USB_NODE_CONNECTION_INFORMATION_EX usbPortInfo;
      #else
        USB_NODE_CONNECTION_INFORMATION usbPortInfo;
      #endif

      unsigned long& nPortId = usbPortInfo.ConnectionIndex;
      nPortId = 1; //USB port indexing begins with 1
      while (nPortId <= dwPortCount)
        {
        CUsbDevice usbDevice;
        if (DeviceIoControl(hHub,
                            
                            #if (_WIN32_WINNT >= 0x0501)
                              IOCTL_USB_GET_NODE_CONNECTION_INFORMATION_EX,
                            #else
                              IOCTL_USB_GET_NODE_CONNECTION_INFORMATION,
                            #endif

                            &usbPortInfo,
                            nBytes,
                            &usbPortInfo,
                            nBytes,
                            &nBytesReturned,  //unused
                            NULL))
          {
          TRACE2(_T("      Port %d connection status: %d.\n"),
                    usbPortInfo.ConnectionIndex, //port Id
                    usbPortInfo.ConnectionStatus);
          TRACE1(_T("      hub attached: %d\n"), usbPortInfo.DeviceIsHub);
          usbDevice.m_eStatus = usbPortInfo.ConnectionStatus;

          if (usbPortInfo.ConnectionStatus != NoDeviceConnected)
            {
            usbDevice.m_bHub = (usbPortInfo.DeviceIsHub == TRUE);
           //If the device connected to the port is an external hub, get the
           //name of the external hub and recursively enumerate it.

            //if(usbDevice.m_bHub)
              {

              //Get the hub name; Check GetLastError() in case of failure.
              USB_NODE_CONNECTION_NAME usbNodeName;
              usbNodeName.ConnectionIndex = nPortId;
              TUsbSymbolicName<USB_NODE_CONNECTION_NAME,
                               IOCTL_USB_GET_NODE_CONNECTION_NAME> usbHubName(hHub);
              if (usbHubName.IsValid())
                {
                CString strHubPath = usbHubName.GetName();
                
                }
              else
                {
                TRACE1(_T("      Failed! Error 0x%0.8X.\n"), GetLastError());
                }
              }

            }
          }
        m_usbNodeList.Add(usbDevice);
        nPortId++;
        }
      }
    CloseHandle(hHub);
    }
  }
return dwPortCount;
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
