/*$Workfile: KUsbHub.cpp$: implementation file
  $Revision: 1.2 $ $Date: 2009/07/06 21:35:59 $
  $Author: ddarko $

  Universal Serial Bus (USB) Host Controller
  Copyright: 1997-1998 Microsoft Corporation
  2004-03-03 Darko Kolakovic
  1997-25-04: Microsoft Corporation
 */

// Group=Windows

#ifdef _WIN32

#ifdef _USE_ATL
  //Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)
  //or preprocessor reports unpaired #endif directive

  #include "stdafx.h" //Standard system header files
#endif

#if defined _ATL_VER
  #include "KTraceAtl.h"
#else
  #include <windows.h>
  #include <string.h>
#endif

#ifndef TRACE
  #ifndef _T
    #include "KTChar.h"
  #endif
  #include "KTrace.h"
#endif

#ifdef _DEBUG
  #include "KWinUsb.h" //CUsbDriverKeyName class
#endif
#include "KSysPnP.h" //SYMBOLICLINK_HDC literal

//-----------------------------------------------------------------------------
/*Enumerates USB host controllers using Host Controller Driver (HCD) symbolic
  name. Host controller is also known as the root hub, the root tier or
  simply as the root.
  The host controller controls all traffic on the PCI bus and also functions
  as a hub.

  Host controllers currently have symbolic names (link) of the form HCDx,
  where x starts at 0. Use CreateFile() to open each host controller
  symbolic link. Create a node in the TreeView to represent each host
  controller.

  After a host controller has been opened, send the host controller an
  IOCTL_USB_GET_ROOT_HUB_NAME request to get the symbolic link name of
  the root hub that is part of the host controller.

  Note: Microsoft Windows specific (Win32).

  See also: MSDN KB838100: The USBView.exe sample program does not enumerate
  devices on pre-Windows XP SP1-based computers, EnumerateRootUsbHub().
 */
unsigned int EnumerateHostControllers()
{
TRACE(_T("EnumerateHostControllers()\n"));
unsigned short wInstance = 0; //HCD module instance number
char szHostControllerName[16]; //Host Controller Driver (HCD) symbolic name
const unsigned short ARBITRARY_NO = 12; //arbitrary maximum of instances
unsigned int nResult = 0;
do
  {
  //Create a symbolic link and open communication with HCD
  wsprintfA(szHostControllerName, SYMBOLICLINK_HDC , wInstance);
  HANDLE hHcd = CreateFileA(szHostControllerName,
                            GENERIC_WRITE,
                            FILE_SHARE_WRITE,
                            NULL, //if lpSecurityAttributes is NULL,
                                  //the handle cannot be inherited.
                            OPEN_EXISTING,
                            0,
                            NULL);
  //Note: Windows Me/98/95: The file system restricts CreateFile to creating or
  //opening files streams only.
  if (hHcd != INVALID_HANDLE_VALUE)
    {
    #ifdef _DEBUG
      /*Retrieve the driver key name in the registry for a USB host controller
        driver. The name is in the form: GUID\InstanceNo, where GUID is 'USB device
        setup' class GUID.
        See also: MSDN, Windows Driver Kit: Device Installation, Device Setup
        Classes
       */
      CUsbDriverKeyName usbDriverKeyName(hHcd);
      bool bRes = usbDriverKeyName.LoadKeyName(hHcd);
      if (!bRes)
        {
        CloseHandle(hHcd);
        DWORD dwError = GetLastError();
        TRACE1(_T("  Failed to obtain driber's key name: error 0x%X.\n"), dwError);
        //TODO: report the error!
        break;
        }

      TRACE1(_T("System name is %ws\n"), (const WCHAR*)usbDriverKeyName);
    #endif

    nResult++;
    CloseHandle(hHcd);
    }
  #ifdef _DEBUG
    else
      {
      //TODO: verify if instance numbers are always sequential;
      //in that case break the loop when CreateFile fails. D.K.
      TRACE1(_T("  Failed to open \\\\.\\HCD%d!\n"), wInstance);
      }
  #endif
  wInstance++;
  }
while (wInstance < ARBITRARY_NO);

return nResult;
}

#endif //_WIN32
///////////////////////////////////////////////////////////////////////////////
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
  Module Name:     ENUM.C
  
  Abstract:
    This source file contains the routines which enumerate the USB bus
    and populate the TreeView control.

    The enumeration process goes like this:

    (1) Enumerate Host Controllers and Root Hubs
    Host controllers currently have symbolic link names of the form HCDx,
    where x starts at 0.  Use CreateFile() to open each host controller
    symbolic link.  Create a node in the TreeView to represent each host
    controller.

    After a host controller has been opened, send the host controller an
    IOCTL_USB_GET_ROOT_HUB_NAME request to get the symbolic link name of
    the root hub that is part of the host controller.

    (2) Enumerate Hubs (Root Hubs and External Hubs)
    Given the name of a hub, use CreateFile() to hub the hub.  Send the
    hub an IOCTL_USB_GET_NODE_INFORMATION request to get info about the
    hub, such as the number of downstream ports.  Create a node in the
    TreeView to represent each hub.

    (3) Enumerate Downstream Ports
    Given an handle to an open hub and the number of downstream ports on
    the hub, send the hub an IOCTL_USB_GET_NODE_CONNECTION_INFORMATION
    request for each downstream port of the hub to get info about the
    device (if any) attached to each port.  If there is a device attached
    to a port, send the hub an IOCTL_USB_GET_NODE_CONNECTION_NAME request
    to get the symbolic link name of the hub attached to the downstream
    port.  If there is a hub attached to the downstream port, recurse to
    step (2).  Create a node in the TreeView to represent each hub port
    and attached device.

  Environment:     user mode
  Revision History:     04-25-97 : created

 */