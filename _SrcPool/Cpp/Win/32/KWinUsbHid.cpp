/*$Workfile: KUsbHid.cpp$: implementation file
  $Revision: 5$ $Date: 2007-08-24 18:15:43$
  $Author: Darko Kolakovic$

  USB HID handler.
  Requires Microsoft Windows DDK libraries.

  Note: Microsoft Windows specific (Win).
  Copyright: CommonSoft Inc
  2004-11-23 Darko Kolakovic
 */
// Group=Windows

#ifdef _WIN32

#ifdef _USE_ATL
  //Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)
  //or preprocessor reports unpaired #endif directive

  #include "stdafx.h" //Standard system header files
#else
  #include <windows.h>
#endif

#if defined _ATL_VER
  #ifndef TRACE
    #define TRACE ATLTRACE
    #define TRACE1 ATLTRACE
  #endif
#endif

#ifndef TRACE
  #ifndef _T
    #include "KTChar.h"
  #endif
  #include "KTrace.h"
#endif

#include <setupapi.h> //Device Management Structures

//#include <wtypes.h">

//#include <windef.h>
//#include <win32.h>
//#include <basetyps.h>

extern "C"
  {
  #include <hidsdi.h>//USB specific HID class GUID; Windows DDK
  }
#include "KUsbHid.h" //CUsbHid class
#ifndef USBVID_ANY
  #include "KUsb.h"
#endif

/*Requires hid.lib

  Note: Microsoft Windows DDK library.
 */
#pragma comment( lib, "hid" )

///#include <winioctl.h>
///#include <wtypes.h>
//#include <initguid.h>
extern "C"
{
///
///
}

/*
typedef struct StructParamTag
{
  //Application global variables
  HIDP_CAPS   Capabilities;
  int     DeviceDetected;
  HANDLE    DeviceHandle;
  HANDLE    hDevInfo;
  GUID      HidGuid;
  ULONG     Length;
  ULONG     Required;
  HANDLE    WriteHandle;
}StructParam;


void GetDeviceCapabilities();
int FindTheHID();
*/

///////////////////////////////////////////////////////////////////////////////
// CUsbHid Class implementation


//-----------------------------------------------------------------------------
/*Default constructor
 */
CUsbHid::CUsbHid() :
  m_hHid(INVALID_HANDLE_VALUE)
{
//  StructParamPtr = new StructParam;
//  ((StructParam *)StructParamPtr)->DeviceDetected=FALSE;
}

CUsbHid::~CUsbHid()
{
if (m_hHid != INVALID_HANDLE_VALUE)
  {
  CloseHandle(m_hHid);
  m_hHid = INVALID_HANDLE_VALUE;
  }
//  Close();
//  if (StructParamPtr != NULL)
//  {
//    delete StructParamPtr;
//    StructParamPtr = NULL;
//  }
}


//-----------------------------------------------------------------------------
/*Find a HID specified by a vendor (VID) and product identification 
  (PID) number. If the vendor is not specified (VID is USBVID_ANY), the method
  return true when first HID class object is found in the device tree. If PID
  is USBPID_ANY, the method searches for any device from the specified vendor
  and returns true when the first HID is found. If the required device is found,
  handle to the object is preserved as the m_hHid member of the CUsbHid class.

  Returns: true if the requested device of the HID class is found in the 
  USB device tree. Returns false if the device is not present.

  See also: USB Implementers Forum, Inc (USB-IF) at http://www.usb.org; CUsbId
 */
bool CUsbHid::Find(const uint16_t wVendorId, //[in] USB device vendor 
                                             //identification (VID) number
                   const uint16_t wProductId //[in] USB product identification 
                                             //(PID) number
                  )
{
TRACE2(_T("CUsbHid::Find(0x%4.4X, 0x%4.4X)\n"), wVendorId, wProductId);
bool bResult = false;

//Get the top HIDClass device interface GUID
GUID guidHid;  //device interface GUID for HIDClass devices
HidD_GetHidGuid(&guidHid);

//Get handle to the device information set
HDEVINFO hDevInfo = SetupDiGetClassDevs(&guidHid, //a interface class GUID
                                        NULL, //PnP name of the device
                                        NULL, //user interface window
                                        DIGCF_DEVICEINTERFACE | //list of installed
                                        //interface class devices
                                        DIGCF_PRESENT      //currently present
                                        //devices
                                        );

if (hDevInfo != INVALID_HANDLE_VALUE)
  {
  //Get a context structure for a device information element of
  //the specified device information set.
  int iDevCount = 0;
  SP_DEVICE_INTERFACE_DATA sdiDevinfo; //device instance that is a member of
  //a device information set.
  sdiDevinfo.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
  while(SetupDiEnumDeviceInterfaces(hDevInfo,//handle to the device information set
                                    NULL, //search for specific interface
                                    &guidHid, //a HID class GUID
                                    //device interface class
                                    iDevCount, //index to the list of interfaces
                                    &sdiDevinfo //[out] device information
                                   ))
    {
    //Obtain information from HID Object.
    PSP_DEVICE_INTERFACE_DETAIL_DATA psdiDevDetail = NULL;
    DWORD dwSize = 0; //size of the holding buffer
    //Get required buffer size
    SetupDiGetDeviceInterfaceDetail(hDevInfo,
                                    &sdiDevinfo,
                                    NULL,
                                    0,
                                    &dwSize, //required size for the buffer
                                    NULL
                                    );
    psdiDevDetail = (PSP_DEVICE_INTERFACE_DETAIL_DATA) new char[dwSize];
    psdiDevDetail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
    SetupDiGetDeviceInterfaceDetail(hDevInfo,
                                    &sdiDevinfo,
                                    psdiDevDetail,
                                    dwSize,
                                    &dwSize,
                                    NULL
                                    );
    //Open a HID
    //Note: generic keyborad or pointing device driver does not allow 
    //read nor write access to the device.
    HANDLE hHid = CreateFile(psdiDevDetail->DevicePath,
                             0, //query device existence without 
                                //accessing the device.
                            FILE_SHARE_READ | FILE_SHARE_WRITE,
                            NULL,//if lpSecurityAttributes is NULL,
                            //the handle cannot be inherited.
                            OPEN_EXISTING,
                            0,
                            NULL);
    if (hHid != INVALID_HANDLE_VALUE)
      {
      #ifdef _UNICODE
        TRACE2(_T("  %d. %ws\n"), iDevCount, psdiDevDetail->DevicePath);
      #else
        TRACE2(_T("  %d. %s\n"), iDevCount, psdiDevDetail->DevicePath);
      #endif
      
      if ( wVendorId != USBVID_ANY )
        {
        //Get the attributes of a specified top-level collection.
        HIDD_ATTRIBUTES hiddAttributes; //attributes of the top-level collection
        hiddAttributes.Size = sizeof(hiddAttributes);
        if ( HidD_GetAttributes(hHid, &hiddAttributes) )
          {
          if (hiddAttributes.VendorID == wVendorId)
            if (( wProductId != USBPID_ANY ) && 
                ( hiddAttributes.ProductID != wProductId ))
              {
              CloseHandle(hHid);
              }
            else
            bResult = true;
          }
        }
      else
        bResult = true;
      }
    #ifdef _DEBUG
      else
        {
        TRACE1(_T("  Failed to open HID: #%0.8d!\n"), GetLastError());
        }
    #endif

    delete[] psdiDevDetail;
    
    if(bResult) //Desired device is found
      {
      if (m_hHid != INVALID_HANDLE_VALUE)
        CloseHandle(m_hHid);
      m_hHid = hHid; //Preserve the device handle
      break; //Return the result
      }
      
    iDevCount++;
    }
    
  SetupDiDestroyDeviceInfoList(hDevInfo);
  }
return bResult;
}

// configuration functions
/*
int CUsbHid::SetDevice(char *UsbDevice)
{
  return USB_HID_OK;
}

int CUsbHid::GetDevice(char *UsbDevice)
{
  return USB_HID_OK;
}
*/
// IO functions
/*int CUsbHid::Open()
{
  if (((StructParam *)StructParamPtr)->DeviceDetected == TRUE) return USB_HID_OK;
  ((StructParam *)StructParamPtr)->DeviceDetected=FALSE;

  // Open the driver
  ((StructParam *)StructParamPtr)->DeviceDetected = FindTheHID();
  if (((StructParam *)StructParamPtr)->DeviceDetected == TRUE)
  {
    // let's now try to set the report buffer queue to 2 reports.
    HidD_SetNumInputBuffers(hHid, 2);
    return USB_HID_OK;
  }
  else
  {
    return USB_HID_NOT_OPENED;
  }
/ *  DeviceDetected=FALSE;

  // Open the driver
  DeviceDetected = FindTheHID();
  if (DeviceDetected == TRUE)
  {
    return USB_HID_OK;
  }
  else
  {
    return USB_HID_NOT_OPENED;
  }* /
}*/

/*int CUsbHid::Close()
{
  if (((StructParam *)StructParamPtr)->DeviceDetected == TRUE)
  {
    //Close open handles.
    CloseHandle(hHid);
    ((StructParam *)StructParamPtr)->DeviceDetected = FALSE;
  }

  return USB_HID_OK;
}*/

/*int CUsbHid::Write(void *Buffer, int Size)
{
  UCHAR *OutputReport = (UCHAR *)Buffer;
  DWORD BytesWritten = 0;
  ULONG Result = 0;

  //If the device hasn't been detected already, look for it.
  if (((StructParam *)StructParamPtr)->DeviceDetected==FALSE)
  {
    ((StructParam *)StructParamPtr)->DeviceDetected=FindTheHID();
  }

  if (((StructParam *)StructParamPtr)->DeviceDetected==TRUE)
  {
    // Write a report to the device.
    Result = WriteFile(hHid, OutputReport, ((StructParam *)StructParamPtr)->Capabilities.OutputReportByteLength, &BytesWritten, NULL);

    // Test the result
    if (Result == 0)
    {
      //The WriteFile failed, so close the handle, display a message,
      //and set DeviceDetected to FALSE so the next attempt will look for the device.
      CloseHandle(hHid);
      ((StructParam *)StructParamPtr)->DeviceDetected = FALSE;
      return USB_HID_NOT_OPENED;
    }
  }
  else
  {
    return USB_HID_NOT_OPENED;
  }

  return USB_HID_OK;
}*/

/*int CUsbHid::Read(void *Buffer, int Size)
{
  UCHAR *OutputReport = (UCHAR *)Buffer;
  DWORD BytesWritten = 0;
  ULONG Result = 0;

  //If the device hasn't been detected already, look for it.
  if (((StructParam *)StructParamPtr)->DeviceDetected==FALSE)
  {
    ((StructParam *)StructParamPtr)->DeviceDetected=FindTheHID();
  }

  if (((StructParam *)StructParamPtr)->DeviceDetected==TRUE)
  {
    // Write a report to the device.
    Result = ReadFile(hHid, OutputReport, ((StructParam *)StructParamPtr)->Capabilities.OutputReportByteLength, &BytesWritten, NULL);

    // Test the result
    if (Result == 0)
    {
      //The WriteFile failed, so close the handle, display a message,
      //and set DeviceDetected to FALSE so the next attempt will look for the device.
      CloseHandle(hHid);
      //wxMessageBox("Cannot write to device");
      ((StructParam *)StructParamPtr)->DeviceDetected = FALSE;
      return USB_HID_NOT_OPENED;
    }
  }
  else
  {
    return USB_HID_NOT_OPENED;
  }

  return USB_HID_OK;
}*/

/*CUsbHid::ReadWrite(void *Buffer, int Size)
{
  UCHAR *OutputReport = (UCHAR *)Buffer;
  DWORD BytesWritten = 0;
  ULONG Result = 0;

  //If the device hasn't been detected already, look for it.
  if (((StructParam *)StructParamPtr)->DeviceDetected==FALSE)
  {
    ((StructParam *)StructParamPtr)->DeviceDetected=FindTheHID();
  }

  if (((StructParam *)StructParamPtr)->DeviceDetected==TRUE)
  {
    // Write a report to the device.
    Result = WriteFile(hHid, OutputReport, ((StructParam *)StructParamPtr)->Capabilities.OutputReportByteLength, &BytesWritten, NULL);

    // Test the result
    if (Result == 0)
    {
      //The WriteFile failed, so close the handle, display a message,
      //and set DeviceDetected to FALSE so the next attempt will look for the device.
      CloseHandle(hHid);
      //wxMessageBox("Cannot write to device");
      ((StructParam *)StructParamPtr)->DeviceDetected = FALSE;
      return USB_HID_NOT_OPENED;
    }

    // Write a report to the device.
    Result = ReadFile(hHid, OutputReport, ((StructParam *)StructParamPtr)->Capabilities.OutputReportByteLength, &BytesWritten, NULL);

    // Test the result
    if (Result == 0)
    {
      //The WriteFile failed, so close the handle, display a message,
      //and set DeviceDetected to FALSE so the next attempt will look for the device.
      CloseHandle(hHid);
      ((StructParam *)StructParamPtr)->DeviceDetected = FALSE;
      return USB_HID_NOT_OPENED;
    }
  }
  else
  {
    return USB_HID_NOT_OPENED;
  }

  return USB_HID_OK;
}*/

// initialize the function to intercept SIGIO
//int SetReadSignal(ReadSignalType iRSFunc){
  // reading not implemented so this is not !
  //return USB_HID_READ_ERROR;;
//}

/*void CUsbHid::GetDeviceCapabilities()
{
  //Get the Capabilities structure for the device.
  PHIDP_PREPARSED_DATA  PreparsedData;

  / *
  API function: HidD_GetPreparsedData
  Returns: a pointer to a buffer containing the information about the device's capabilities.
  Requires: A handle returned by CreateFile.
  There's no need to access the buffer directly,
  but HidP_GetCaps and other API functions require a pointer to the buffer.
  * /

  HidD_GetPreparsedData \
    (hHid, \
    &PreparsedData);
//  DisplayLastError("HidD_GetPreparsedData: ");

  / *
  API function: HidP_GetCaps
  Learn the device's capabilities.
  For standard devices such as joysticks, you can find out the specific
  capabilities of the device.
  For a custom device, the software will probably know what the device is capable of,
  and the call only verifies the information.
  Requires: the pointer to the buffer returned by HidD_GetPreparsedData.
  Returns: a Capabilities structure containing the information.
  * /

  HidP_GetCaps \
    (PreparsedData, \
    &(((StructParam *)StructParamPtr)->Capabilities));

  //No need for PreparsedData any more, so free the memory it's using.
  HidD_FreePreparsedData(PreparsedData);
}*/
#endif //_WIN32
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: $
 *****************************************************************************/

