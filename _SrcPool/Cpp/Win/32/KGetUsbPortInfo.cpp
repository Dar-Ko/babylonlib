/*$RCSfile: KGetUsbPortInfo.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2009/08/18 14:21:55 $
  $Author: ddarko $

  Obtain USB string descriptor.
  Note: Microsoft Windows specific (Win).
  Copyright: 1997-1998 Microsoft Corporation
  2004-03-15 Darko Kolakovic
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
#endif

#ifndef TRACE
  #ifndef _T
    #include "KTChar.h"
  #endif
  #include "KTrace.h"
#endif

#ifdef _USE_MSWINDDK
  #pragma include_alias( "UsbIoCtl.h", "wxp/usbioctl.h" )
#endif

#include "KUsb.h" //USB_MAXCOUNT
#include "UsbIoCtl.h" //IOCTL_USB_GET_NODE_CONNECTION_INFORMATION

//-----------------------------------------------------------------------------
/*Obtains information about the specified USB port. If there is a device connected
  to the port, the result contains also information about the attached USB device.

  Returns true and requested information, or false in case of the failure.
  Call GetLastError() to verify successful operation.

  See also: "Universal Serial Bus Specification Revision 1.1";
  USB_NODE_CONNECTION_INFORMATION_EX, IOCTL_USB_GET_NODE_CONNECTION_INFORMATION_EX,
  IOCTL_USB_GET_NODE_CONNECTION_INFORMATION
 */
bool GetUsbPortInfo(const HANDLE hHub, //[in] handle of the hub device
                        //containing the port from which the String Descriptor
                        //will be requested.
                               const unsigned int nPortNo, //[in] port on
                        //the hub to which a device is attached from the range
                        //[1, USB_HUB_DESCRIPTOR::bNumberOfPorts].
                               PUSB_NODE_CONNECTION_INFORMATION pusbPortInfo //[out]
                        //requested USB port information.
                              )
{
TRACE1(_T("GetUsbPortInfo(nPortNo = %d)\n"), nPortNo);
//Disable warning C4127: conditional expression in ASSERT is constant
#pragma warning (disable: 4127)
  ASSERT((nPortNo > 0) && (nPortNo <= USB_MAXCOUNT));
  ASSERT(pusbPortInfo != NULL); //String Descriptor 0 contains the array of
                            //supported Language IDs
  ASSERT(hHub != INVALID_HANDLE_VALUE);
#pragma warning (default: 4127)

bool bResult = false;

if ((nPortNo > 0) &&
    (nPortNo <= USB_MAXCOUNT) &&
    (pusbPortInfo != NULL) &&
    (hHub != INVALID_HANDLE_VALUE))
  {
  pusbPortInfo->ConnectionIndex = nPortNo;
  ULONG nBytesReturned; //actual size of the response

  if (DeviceIoControl(hHub,
                      IOCTL_USB_GET_NODE_CONNECTION_INFORMATION,
                      pusbPortInfo,
                      sizeof(USB_NODE_CONNECTION_INFORMATION),
                      pusbPortInfo,
                      sizeof(USB_NODE_CONNECTION_INFORMATION),
                      &nBytesReturned,  //unused
                      NULL))
    {
    if (nBytesReturned > 1) //Sanity check
      {
      bResult = true;
      }
    else
      {
      //IOCTL returned wrong number of bytes
      SetLastError(ERROR_INVALID_DATA);
      }
    }
  else
    {
    //IOCTL failed.To get extended error information, call GetLastError().
    TRACE1(_T("  DeviceIoControl failed! Error 0x%0.8X.\n"), GetLastError());
    }
  }
else
  {
  SetLastError(ERROR_INVALID_PARAMETER);
  }

return bResult;
}

#if (_WIN32_WINNT >= 0x0501)
//-----------------------------------------------------------------------------
/*Obtains extended information about the specified USB port. If there is
  a device connected to the port, the result contains also information about
  the attached USB device.
  The resulting USB_NODE_CONNECTION_INFORMATION_EX structure is an extended
  version of USB_NODE_CONNECTION_INFORMATION that differs only in Speed member.

  Returns true and requested information, or false in case of the failure.
  Call GetLastError() to verify successful operation.

  Note: Microsoft Windows XP and Windows .NET Server or newer specific.

  See also: "Universal Serial Bus Specification Revision 1.1";
  USB_NODE_CONNECTION_INFORMATION, IOCTL_USB_GET_NODE_CONNECTION_INFORMATION,
  IOCTL_USB_GET_NODE_CONNECTION_INFORMATION_EX
 */
bool GetUsbPortInfo(const HANDLE hHub, //[in] handle of the hub device
                        //containing the port from which the String Descriptor
                        //will be requested.
                               const unsigned int nPortNo, //[in] port on
                        //the hub to which a device is attached from the range
                        //[1, USB_HUB_DESCRIPTOR::bNumberOfPorts].
                               PUSB_NODE_CONNECTION_INFORMATION_EX pusbPortInfo //[out]
                        //requested USB port information.
                              )
{
TRACE1(_T("GetUsbPortInfo(nPortNo = %d, extended)\n"), nPortNo);
//Disable warning C4127: conditional expression in ASSERT is constant
#pragma warning (disable: 4127)
  ASSERT((nPortNo > 0) && (nPortNo <= USB_MAXCOUNT));
  ASSERT(pusbPortInfo != NULL 0); //String Descriptor 0 contains the array of
                            //supported Language IDs
  ASSERT(hHub != INVALID_HANDLE_VALUE);
#pragma warning (default: 4127)

bool bResult = false;

if ((nPortNo > 0) &&
    (nPortNo <= USB_MAXCOUNT) &&
    (pusbPortInfo != NULL) &&
    (hHub != INVALID_HANDLE_VALUE))
  {
  pusbPortInfo->ConnectionIndex = nPortNo;
  ULONG nBytesReturned; //actual size of the response

  if (DeviceIoControl(hHub,
                      IOCTL_USB_GET_NODE_CONNECTION_INFORMATION_EX,
                      pusbPortInfo,
                      sizeof(USB_NODE_CONNECTION_INFORMATION_EX),
                      &usbPortInfo,
                      sizeof(USB_NODE_CONNECTION_INFORMATION_EX),
                      pusbPortInfo,  //unused
                      NULL))
    {
    if (nBytesReturned > 1) //Sanity check
      {
      bResult = true;
      }
    else
      {
      //IOCTL returned wrong number of bytes
      SetLastError(ERROR_INVALID_DATA);
      }
    }
  else
    {
    //IOCTL failed.To get extended error information, call GetLastError().
    TRACE1(_T("  DeviceIoControl failed! Error 0x%0.8X.\n"), GetLastError());
    }
  }
else
  {
  SetLastError(ERROR_INVALID_PARAMETER);
  }

return bResult;
}
#endif
///////////////////////////////////////////////////////////////////////////////
#endif //_WIN32

/*****************************************************************************
 * $Log: KGetUsbPortInfo.cpp,v $
 * Revision 1.2  2009/08/18 14:21:55  ddarko
 * *** empty log message ***
 *
 * Revision 1.1  2009/08/18 14:20:09  ddarko
 * Created
 *
 *****************************************************************************/
