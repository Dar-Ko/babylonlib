/*$Workfile: KGetDevDesc.cpp$: implementation file
  $Revision: 1.2 $ $Date: 2009/07/20 21:50:20 $
  $Author: ddarko $

  Universal Serial Bus (USB) Driver Key Name
  Copyright: 1997-1998 Microsoft Corporation
  1997-25-04: Microsoft Corporation
  2009-07-10: Darko Kolakovic
 */
// Group=Windows

#ifdef _WIN32

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
#endif

#ifndef TRACE
  #ifndef _T
    #include "KTChar.h"
  #endif
  #include "KTrace.h"
#endif

#ifdef __cplusplus
#ifdef _USE_STL
  #include <string>  //CString base class
#endif
#include "KString.h" //CString class replacement
#include "KWinUsb.h" //TUsbSymbolicName template

//-----------------------------------------------------------------------------
/*Retrieves the driver key name of USB device attached to the USB hub.

  Returns: true if successful and requested driver key name or false in
  case of a failure. To get extended error information, call GetLastError().
 */
bool GetUsbDriverKeyName(HANDLE hUsbHub, //[in] handle to the USB hub device
                         const unsigned int nPortId, //[in] the hub port number
                         //where device of interest is attached
                         //[1, USB_HUB_DESCRIPTOR::bNumberOfPorts]
                         CString& strDriverKeyName //[out] driver key name of
                         //the device attached to the specified port.
                        )
{
TRACE1(_T("      GetUsbDriverKeyName(nPortNo = %d)\n"), nPortId);

//Disable warning C4127: conditional expression in ASSERT is constant
#pragma warning (disable: 4127)
  ASSERT((nPortId > 0) && (nPortId < 255));
#pragma warning (default: 4127)

//Get driver key name; Check GetLastError() in case of failure.
USB_NODE_CONNECTION_DRIVERKEY_NAME usbNodeName;
usbNodeName.ConnectionIndex = nPortId;

TUsbSymbolicName<USB_NODE_CONNECTION_DRIVERKEY_NAME,
                 IOCTL_USB_GET_NODE_CONNECTION_DRIVERKEY_NAME> usbDrvKeyName;
usbDrvKeyName.Create(hUsbHub, usbNodeName);

if (usbDrvKeyName.GetName() != NULL)
  {
  //Get the driver key name of the device attached to the specified port
  strDriverKeyName = usbDrvKeyName.GetName();
  TRACE1(_T("        %ws\n"), usbDrvKeyName.GetName());
  return true;
  }

TRACE1(_T("        Failed to obtain the driver key name: #%0.8d!\n"),
       GetLastError());
return false;
}

#endif //__cplusplus
///////////////////////////////////////////////////////////////////////////////
#endif //_WIN32
/*****************************************************************************
 * $Log: KUsbDrvKeyName.cpp,v $
 * Revision 1.2  2009/07/20 21:50:20  ddarko
 * HasStringDescriptor()
 *
 * Revision 1.1  2009/07/20 16:19:14  ddarko
 * Created
 *
 *****************************************************************************/

/*Note: Used code from Microsoft Windows DDK sample USBView
  Copyright (c) 1998-1998 Microsoft Corporation
  Module Name: ENUM.C
 */
