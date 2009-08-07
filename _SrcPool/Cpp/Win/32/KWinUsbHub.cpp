/*$Workfile: KUsbHub.cpp$: implementation file
  $Revision: 1.18 $ $Date: 2009/08/07 21:44:53 $
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
/*Build or refresh the USB device tree.

  Returns number of USB host controllers (root hubs) found.
 */
int CUsbDeviceTree::Enumerate()
{
TRACE(_T("CUsbDeviceTree::Enumerate()\n"));

RemoveAll(); //Erase previous tree

int iCount = 0;
CUsbHostController* pusbHc = new CUsbHostController;
while(pusbHc->GetDeviceInfo(iCount))
  {
  m_usbRootList.Add(pusbHc);
  #ifdef _DEBUG
  int n = (int)(m_usbRootList.GetCount() - 1);
  m_usbRootList[n]->m_usbNodeList.Dump();
  #endif
  pusbHc = new CUsbHostController; //Get next controller
  iCount++;
  }
delete pusbHc; //Delete last non-existing controller
return iCount;
}

//-----------------------------------------------------------------------------
/*Retreives status and addtional description of the USB device specified by
  a vendor (VID) and product identification (PID) number.

  Returns: true if the requested device is found in the
  USB device tree. Returns false if the device is not present.

  See also: USB Implementers Forum, Inc (USB-IF) at http://www.usb.org; CUsbId,
  SP_DEVICE_INTERFACE_DETAIL_DATA, SP_DEVINFO_DATA, <setupapi.h>,
  CUsbDeviceTree::HasDevice(), CUsbHub::Find();
 */
bool CUsbDeviceTree::GetDevice(const uint16_t wVendorId, //[in] USB device
                                  //vendor identification (VID) number.
                               const uint16_t wProductId, //[in] USB product
                                  //identification (PID) number.
                               CUsbDeviceInfo* pDevice //[in]/[out] = NULL
                                  //description of the reqested USB device;
                                  //desription of the device found is returned.
                               )
{
TRACE2(_T("UsbDeviceTree::GetDevice(0x%4.4X, 0x%4.4X)\n"), wVendorId, wProductId);
bool bResult = false;
//Build (or refresh) the USB tree, if it is not done before
if (m_usbRootList.IsEmpty())
  Enumerate();

int i = 0;
while (i < (int)m_usbRootList.GetCount())
  {
  bResult = m_usbRootList[i]->Find(wVendorId, wProductId, pDevice);
  if (bResult)
    break;
  i++;
  }
return bResult;
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
    TRACE1(_T("Number of host controllers: %d.\n"), nCount);
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

  Note: requires <usbiodef.h> from Microsoft DDK or "UsbGuid.h"
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
    if (GetPortCount() > 0)
      bResult = true;
    }
  else
    m_strDevice.Empty();

  }
#ifdef _DEBUG
else
  {
  TRACE(_T("    This host controller is not installed on the system.\n"));
  }
#endif

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

  Note: if driver key names for devices connetect to the hub are required,
  define _USE_USBDRIVERKEYNAME.
 */
unsigned int CUsbHub::Enumerate(LPCTSTR szDevicePath //[in] the USB hub
                                    //device path
                                )
{
TRACE(_T("    CUsbHub::Enumerate()\n"));
unsigned int dwPortCount = 0;
Erase(); //Prepare the object for new enumeration

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
        nBytes = sizeof(USB_NODE_CONNECTION_INFORMATION_EX);
      #else
        USB_NODE_CONNECTION_INFORMATION usbPortInfo;
        nBytes = sizeof(USB_NODE_CONNECTION_INFORMATION);
      #endif

      unsigned long& nPortId = usbPortInfo.ConnectionIndex;
      nPortId = 1; //USB port indexing begins with 1
      while (nPortId <= dwPortCount)
        {
        CUsbDevice* pusbDevice = NULL;
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
          #ifdef _UNICODE
              TRACE2(_T("      Port %d connection status: %ws.\n"),
                        usbPortInfo.ConnectionIndex, //port Id
                        GetUsbStatus(usbPortInfo.ConnectionStatus));
          #else
            TRACE2(_T("      Port %d connection status: %s.\n"),
                      usbPortInfo.ConnectionIndex, //port Id
                      GetUsbStatus(usbPortInfo.ConnectionStatus));
          #endif
          if (usbPortInfo.ConnectionStatus != NoDeviceConnected)
            {
            pusbDevice = new CUsbDevice;
            if (pusbDevice != NULL)
              {
              #ifdef _USE_USBDRIVERKEYNAME
                extern bool GetUsbDriverKeyName(HANDLE hUsbHub,
                          const unsigned int nPortId,
                          CString& strDriverKeyName);
                GetUsbDriverKeyName(hHub, nPortId, pusbDevice->m_strDevice);
              #endif
              TRACE1(_T("        product Id: 0x%0.4X.\n"),
                    usbPortInfo.DeviceDescriptor.idProduct);
              TRACE1(_T("        vendor  Id: 0x%0.4X.\n"),
                    usbPortInfo.DeviceDescriptor.idVendor);
              TRACE1(_T("        supported USB %s.\n"), 
                (LPCTSTR) pusbDevice->Bcd2Str(usbPortInfo.DeviceDescriptor.bcdUSB));
              TRACE1(_T("        device version: %s.\n"), 
                (LPCTSTR) pusbDevice->Bcd2Str(usbPortInfo.DeviceDescriptor.bcdDevice));
              TRACE1(_T("        hub attached: %d\n"), usbPortInfo.DeviceIsHub);

              pusbDevice->m_eStatus = usbPortInfo.ConnectionStatus;
              pusbDevice->m_wPid    = usbPortInfo.DeviceDescriptor.idProduct;
              pusbDevice->m_wVid    = usbPortInfo.DeviceDescriptor.idVendor;

              pusbDevice->m_bHub = (usbPortInfo.DeviceIsHub == TRUE);

              //If the device connected to the port is an external hub, get the
              //name of the external hub and recursively enumerate it.
              if(pusbDevice->m_bHub)
                {
                 //Replace USB device data with the hub data
                CUsbHub* pusbHubDevice = (CUsbHub*) new CUsbHub(*pusbDevice);
                if (pusbHubDevice != NULL)
                  {
                  delete pusbDevice;
                  pusbDevice = (CUsbDevice*)pusbHubDevice;

                  //Get the hub name; Check GetLastError() in case of failure.
                  USB_NODE_CONNECTION_NAME usbNodeName;
                  usbNodeName.ConnectionIndex = nPortId;

                  TUsbSymbolicName<USB_NODE_CONNECTION_NAME,
                                  IOCTL_USB_GET_NODE_CONNECTION_NAME> usbHubName;
                  usbHubName.Create(hHub, usbNodeName);

                  if (usbHubName.IsValid())
                    {
                    //Get the name of the external hub attached
                    //to the specified port
                    pusbHubDevice->m_strDevice = usbHubName.GetName();
                    TRACE1(_T("        %ws\n"),
                           (LPCTSTR)pusbDevice->m_strDevice);
                    pusbHubDevice->m_nPortCount =
                        pusbHubDevice->Enumerate(pusbHubDevice->m_strDevice);
                    TRACE(_T("        ------End of enumeration------\n"));
                    }
                  else
                    {
                    TRACE1(_T("        Failed! Error 0x%0.8X.\n"),
                           GetLastError());
                    }
                  }

                }

              }
            }
          }
        //Add pointer to the device or NULL if port is not used;
        //number of elements in the list have to match number of ports.
        m_usbNodeList.Add(pusbDevice);
        nPortId++;
        }
      }
    CloseHandle(hHub);
    }
  }

#ifdef _DEBUG
  m_usbNodeList.Dump();
#endif
return dwPortCount;
}

//-----------------------------------------------------------------------------
/*Retreives status and addtional description of the USB device specified by
  a vendor (VID) and product identification (PID) number.

  Returns: true if the requested device is found in the
  USB device tree. Returns false if the device is not present.

  See also: USB Implementers Forum, Inc (USB-IF) at http://www.usb.org; CUsbId,
  SP_DEVICE_INTERFACE_DETAIL_DATA, SP_DEVINFO_DATA, <setupapi.h>,
  CUsbDeviceTree::HasDevice();
 */
bool CUsbHub::Find(const uint16_t wVendorId, //[in] USB device
                    //vendor identification (VID) number.
                   const uint16_t wProductId, //[in] USB product
                    //identification (PID) number.
                   CUsbDeviceInfo* pDevice //[in]/[out] = NULL
                    //description of the reqested USB device;
                    //desription of the device found is returned.
                  )
{
TRACE2(_T("  CUsbHub::Find(0x%4.4X, 0x%4.4X)\n"), wVendorId, wProductId);
#ifdef _UNICODE
  TRACE1(_T("    @ %ws\n"), (LPCTSTR)m_strDevice);
#else
  TRACE1(_T("    @ %s\n"), (LPCTSTR)m_strDevice);
#endif

#ifdef _DEBUG
  m_usbNodeList.Dump();
#endif

bool bResult = false;
//TODO: check for USBVID_ANY
if (IsVendor(wVendorId) && IsProduct(wProductId))
  {
  if (pDevice != NULL)
    {

    //TODO check port no, serno
#pragma todo copy CUsbDevice to pDevice
    }
  bResult = true;
  }
else
  {
    //Disable warning C4127: conditional expression in ASSERT is constant
  #pragma warning (disable: 4127)
    ASSERT(USB_MAXCOUNT >= GetPortCount()); //Check sanity
  #pragma warning (default: 4127)

  //Search through all hub's ports for the required unit
  int i = 0;
  while(i < (int)m_usbNodeList.GetCount())
    {
    CUsbDevice* pUsbNode = m_usbNodeList[i];
    if (pUsbNode != NULL)
      {
      //TODO: check for USBVID_ANY
      if (pUsbNode->IsVendor(wVendorId) &&
          pUsbNode->IsProduct(wProductId) )
        {
        if(pDevice != NULL)
          {
          //Validate port number
          if (pDevice->m_nPortNo > 0)
            bResult = (pDevice->m_nPortNo == (uint16_t)(i + 1));
          else //Ignore port number
            {
            bResult = true;
            }

           //TODO Get sdevice strings.
//TODO: check multiple conditions
          if (pDevice->m_strSerialNo.IsEmpty())
            {
            pDevice->m_strSerialNo = _T("N/A"); //TODO: get ser no
            bResult = true;
            }
          else //Compare serial numbers
            {
            bResult = (pDevice->m_strSerialNo.CompareNoCase(_T("get ser no")) == 0);
            }

          if (bResult)
            {
            pDevice->m_wVid = wVendorId;
            pDevice->m_wPid = wProductId;
            pDevice->m_eStatus = pUsbNode->m_eStatus;
            pDevice->m_nPortNo = (uint16_t)(i + 1); //Set one-based port Id

            }
          }
        else //No additional validation is required
          {
          bResult = true;
          }

        if (bResult)
          break;
        }
      if (pUsbNode->m_bHub)
        {
        //Search through attached hub
        if ( ((CUsbHub*)pUsbNode)->Find(wVendorId, wProductId, pDevice) )
          {
          bResult = true;
          break;
          }
        }
      }
    i++;
    }

  }
return bResult;
}

///////////////////////////////////////////////////////////////////////////////
//CUsbDevice class implementation

//-----------------------------------------------------------------------------
/*
 Device, configuration, and interface descriptors may contain references to string descriptors. String descriptors are referenced by their one-based index number. A string descriptor contains one or more Unicode strings; each string is a translation of the others into another language.
 Drivers can request the special index number of zero to determine which language IDs the device supports. For this special value, the device returns an array of language IDs rather than a Unicode string.

  String descriptors are referenced by their one-based index
  number. A string descriptor contains one or more Unicode strings; each string
  is a translation of the others into another language.
  Drivers can request the special index number of zero to determine which
  language IDs the device supports.

 See also: USB_STRING_DESCRIPTOR, LANGID
 */
bool CUsbDevice::GetStringDescriptor(const HANDLE hUsbHub, //[in]
                                     const unsigned int nPortId, //[in] USB hub
           //port number to which a device is attached
                                     const unsigned int nStringId, //[in] index
           //of required string from an array of descriptions [1, N]
                                     LANGID nLangId, //[in] Microsoft language ID
                                     CString& strResult    //[out] result
                                     )
{
TRACE2(_T("    CUsbDevice::GetStringDescriptor(port = %d, string Id = %d)\n"),
       nPortId, nStringId);
bool bResult = false;
if (hUsbHub != INVALID_HANDLE_VALUE)
  {
    //Disable warning C4127: conditional expression in ASSERT is constant
  #pragma warning (disable: 4127)
    ASSERT((nPortId > 0) && (nPortId <= (USB_MAXCOUNT+1)));
  #pragma warning (default: 4127)
  if (nStringId > 0)
    {
    if (nLangId == 0) //Set default language
      nLangId = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US); //0x409 English (U.S.)

    /*Because the string descriptor consists of variable-length data,
      the desriptor must be obtained it in two steps:
        1. get required buffer size by issuing the request, passing a data
           buffer large enough to hold the header for a string
           descriptor - a USB_STRING_DESCRIPTOR structure. The bLength member
           of USB_STRING_DESCRIPTOR specifies the size in bytes of the entire
           descriptor.
        2. get the desired string. Make the same request with a data buffer
           of size bLength.
     */
    USB_DESCRIPTOR_REQUEST usbDescriptor;
    usbDescriptor.SetupPacket.wLength = sizeof(usbDescriptor);
#pragma TODO GetStringDescriptor

    PUSB_DESCRIPTOR_REQUEST pusbDescriptor;
    }
  }
return bResult;
}

//-----------------------------------------------------------------------------
/*Verifies if the device descriptor or configuration descriptor has device 
  description.
  Device, configuration and interface descriptors may contain references to
  string descriptors. String descriptors are referenced by their one-based
  index number.
  Method examines the device descriptor first and if that fails, check for
  strings in configuration or interface descriptors.

  Returns true if a string descriptor is found.

  See also: USB_DEVICE_DESCRIPTOR, USB_CONFIGURATION_DESCRIPTOR
 */
bool CUsbDevice::HasStringDescriptor(
        const PUSB_DEVICE_DESCRIPTOR pusbDevDescriptor, //[in] USB device descriptor
        const PUSB_CONFIGURATION_DESCRIPTOR pusbConfigDescriptor //[in] USB
        //configuration descriptor
        )
{
if((pusbDevDescriptor->iManufacturer > 0) ||
   (pusbDevDescriptor->iProduct > 0)      ||
   (pusbDevDescriptor->iSerialNumber > 0))
  return true;

PUCHAR pEnd = (PUCHAR)pusbConfigDescriptor + pusbConfigDescriptor->wTotalLength;
PUSB_COMMON_DESCRIPTOR pusbCommonDescriptor = (PUSB_COMMON_DESCRIPTOR)pusbConfigDescriptor;

while( ((PUCHAR)pusbCommonDescriptor + sizeof(USB_COMMON_DESCRIPTOR) < pEnd) &&
       ((PUCHAR)pusbCommonDescriptor + pusbCommonDescriptor->bLength <= pEnd) )
  {
  switch(pusbCommonDescriptor->bDescriptorType)
    {
    case USB_CONFIGURATION_DESCRIPTOR_TYPE:
      if(pusbCommonDescriptor->bLength != sizeof(USB_CONFIGURATION_DESCRIPTOR))
        return false;
      if(((USB_CONFIGURATION_DESCRIPTOR*)pusbCommonDescriptor)->iConfiguration)
        return true;
      break;

    case USB_INTERFACE_DESCRIPTOR_TYPE:
      if(pusbCommonDescriptor->bLength != sizeof(USB_INTERFACE_DESCRIPTOR))
        return false;
      if(((USB_INTERFACE_DESCRIPTOR*)pusbCommonDescriptor)->iInterface)
        return true;
      break;

    default:
      break;
    }
  pusbCommonDescriptor = (PUSB_COMMON_DESCRIPTOR)
    ((PUCHAR)(pusbCommonDescriptor) + pusbCommonDescriptor->bLength);
  }

return false;
}

///////////////////////////////////////////////////////////////////////////////
//

//-----------------------------------------------------------------------------
/*Return compact description of the device status. For longer description or
  different locale, this method have to be customized.

    - NoDeviceConnected         Indicates that there is no device connected to
                                the port.
    - DeviceConnected           Indicates that a device was successfully
                                connected to the port.
    - DeviceFailedEnumeration   Indicates that an attempt was made to connect
                                a device to the port, but the enumeration of
                                the device failed.
    - DeviceGeneralFailure      Indicates that an attempt was made to connect
                                a device to the port, but the connection failed
                                for unspecified reasons.
    - DeviceCausedOvercurrent   Indicates that an attempt was made to connect
                                a device to the port, but the attempt failed
                                because of an overcurrent condition.
    - DeviceNotEnoughPower      Indicates that an attempt was made to connect
                                a device to the port, but there was not enough
                                power to drive the device, and the connection
                                failed.
    - DeviceNotEnoughBandwidth  Indicates that an attempt was made to connect
                                a device to the port, but there was not enough
                                bandwidth available for the device to function
                                properly, and the connection failed.
    - DeviceHubNestedTooDeeply  Indicates that an attempt was made to connect
                                a device to the port, but the nesting of USB
                                hubs was too deep, so the connection failed.
    - DeviceInLegacyHub         Indicates that an attempt was made to connect
                                a device to the port of an unsupported legacy
                                hub, and the connection failed.

  See also: USB_CONNECTION_STATUS
 */
LPCTSTR GetUsbStatus(const USB_CONNECTION_STATUS& eStatus //[in] status
                    //of the connection to a device on a USB hub port.
                    )
{
LPCTSTR szResult;

#if (_WIN32_WINNT < 0x0600)
  const int DeviceEnumerating =  9;
  const int DeviceReset       = 10;
#endif

#if (_WIN32_WINNT < 0x0501)
  const int DeviceHubNestedTooDeeply = 7;
  const int DeviceInLegacyHub        = 8;
#endif

switch((int)eStatus)
  {
  case NoDeviceConnected:        szResult = _T("NoDeviceConnected");        break;
  case DeviceConnected:          szResult = _T("DeviceConnected");          break;
  case DeviceFailedEnumeration:  szResult = _T("DeviceFailedEnumeration");  break;
  case DeviceGeneralFailure:     szResult = _T("DeviceGeneralFailure");     break;
  case DeviceCausedOvercurrent:  szResult = _T("DeviceCausedOvercurrent");  break;
  case DeviceNotEnoughPower:     szResult = _T("DeviceNotEnoughPower");     break;
  case DeviceNotEnoughBandwidth: szResult = _T("DeviceNotEnoughBandwidth"); break;

  case DeviceHubNestedTooDeeply: szResult = _T("DeviceHubNestedTooDeeply"); break;
  case DeviceInLegacyHub:        szResult = _T("DeviceInLegacyHub");        break;
  case DeviceEnumerating:        szResult = _T("DeviceEnumerating");        break;
  case DeviceReset:              szResult = _T("DeviceReset");              break;

  default: szResult = _T("UnknownDeviceStatus");
  }
return szResult;
}

//-----------------------------------------------------------------------------
//#include "UsbIoCtl.h"
//Obtain string desriptors
bool GetDeviceString( const uint16_t wVendorId,
                const uint16_t wProductId,
                LPCWSTR HubDevicePath,
                PUSB_NODE_CONNECTION_INFORMATION pusbNodeInfo,
                CString& sProductName,
                CString& sManufacturerName,
                CString& sSerialNumber,
                int& PortNum //[out]
              )
{
TRACE2(_T("    GetDeviceString(0x%0.4X, 0x%0.4X)\n"), wVendorId, wProductId);

bool bResult = false;
HANDLE h;
const DWORD LANGID_EN_US = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US); //0x409 English (U.S.)

PortNum = pusbNodeInfo->ConnectionIndex;

bResult = (pusbNodeInfo->DeviceDescriptor.idVendor==wVendorId) || (wVendorId==USBVID_ANY);
bResult = bResult && ((pusbNodeInfo->DeviceDescriptor.idProduct==wProductId) ||
                      (wProductId==USBPID_ANY));

if ((!bResult) && (pusbNodeInfo->DeviceIsHub != (BOOLEAN)TRUE))
    return false; //If the device is not required one and it is not a hub, break away

h = CreateFile(HubDevicePath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
if ( h == INVALID_HANDLE_VALUE)
  return false;

DWORD nBytesReturned;
const int BUFFER_SIZE = 2048;
WCHAR buffer[BUFFER_SIZE];
int nBytes = BUFFER_SIZE;

//Get The Manufacturer
TRACE(_T("      get the manufacturer,\n"));
if (pusbNodeInfo->DeviceDescriptor.iManufacturer > 0) 
   {
    PUSB_DESCRIPTOR_REQUEST Request = (PUSB_DESCRIPTOR_REQUEST)buffer;
    memset(buffer, 0, sizeof(buffer));
    Request->ConnectionIndex = pusbNodeInfo->ConnectionIndex;
    Request->SetupPacket.wValue = (short)((USBDESCRIPTORTYPE_STRING << 8) + pusbNodeInfo->DeviceDescriptor.iManufacturer);
    Request->SetupPacket.wLength = (short)(nBytes - sizeof(USB_DESCRIPTOR_REQUEST));
    Request->SetupPacket.wIndex = LANGID_EN_US; // Language Code
    if (DeviceIoControl(h, IOCTL_USB_GET_DESCRIPTOR_FROM_NODE_CONNECTION,
                        Request, nBytes, Request, nBytes, &nBytesReturned, NULL))
    {
      PUSB_STRING_DESCRIPTOR StringDesc = (PUSB_STRING_DESCRIPTOR)(Request->Data);
      sProductName = StringDesc->bString;
    }
}

//Get The Product Name
TRACE(_T("      get the product name,\n"));

if (pusbNodeInfo->DeviceDescriptor.iProduct > 0)
{
    PUSB_DESCRIPTOR_REQUEST Request = (PUSB_DESCRIPTOR_REQUEST)buffer;
    memset(buffer, 0, sizeof(buffer));
    Request->ConnectionIndex = pusbNodeInfo->ConnectionIndex;
    Request->SetupPacket.wValue = (short)((USBDESCRIPTORTYPE_STRING << 8) + pusbNodeInfo->DeviceDescriptor.iProduct);
    Request->SetupPacket.wLength = (short)(nBytes - sizeof(USB_DESCRIPTOR_REQUEST));
    Request->SetupPacket.wIndex = LANGID_EN_US; // Language Code
    if (DeviceIoControl(h, IOCTL_USB_GET_DESCRIPTOR_FROM_NODE_CONNECTION,
      Request, nBytes, Request, nBytes, &nBytesReturned, NULL))
    {
      PUSB_STRING_DESCRIPTOR StringDesc = (PUSB_STRING_DESCRIPTOR)(Request->Data);
      sManufacturerName = StringDesc->bString;
    }
}

//Get the Serial Number
/*A USB device may be programmed with a serial number, allowing the host to keep track of different instances of products with the same vendor ID, product ID, and device release number. The serial number is stored as a string descriptor, and the index of that string descriptor is stored in the iSerialNumber field of the device descriptor. If a serial number is not assigned to the device, iSerialNumber is zero.

Microsoft requires that if a serial number is set it must be unique, and each byte in the serial number must be in the range 0x20 <= N <= 0x7F, excluding 0x2C. Windows operating systems always use LANGID 0x0409 to retrieve serial numbers.
*/
if (pusbNodeInfo->DeviceDescriptor.iSerialNumber > 0)
{
    PUSB_DESCRIPTOR_REQUEST Request = (PUSB_DESCRIPTOR_REQUEST)buffer;
    memset(buffer, 0, sizeof(buffer));
    Request->ConnectionIndex = pusbNodeInfo->ConnectionIndex;
    Request->SetupPacket.wValue = (short)((USBDESCRIPTORTYPE_STRING << 8) + pusbNodeInfo->DeviceDescriptor.iSerialNumber);
    Request->SetupPacket.wLength = (short)(nBytes - sizeof(USB_DESCRIPTOR_REQUEST));
    Request->SetupPacket.wIndex = LANGID_EN_US; // Language Code
    if (DeviceIoControl(h, IOCTL_USB_GET_DESCRIPTOR_FROM_NODE_CONNECTION,
      Request, nBytes, Request, nBytes, &nBytesReturned, NULL))
    {
      PUSB_STRING_DESCRIPTOR StringDesc = (PUSB_STRING_DESCRIPTOR)(Request->Data);
      sSerialNumber = StringDesc->bString;
    }
}

CloseHandle(h);

return true;
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
