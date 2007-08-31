/*$Workfile: KUsbHub.cpp$: implementation file
  $Revision: 5$ $Date: 2007-08-24 18:15:43$
  $Author: Darko Kolakovic$

  Universal Serial Bus (USB) Host Controller
  Copyright: 1997-1998 Microsoft Corporation
  2004-03-03 Darko Kolakovic
  1997-25-04: Microsoft Corporation
 */

#ifdef _WIN32

#ifdef _USE_ATL
  //Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)
  //or preprocessor reports unpaired #endif directive

  #include "stdafx.h" //Standard system header files
#endif

#pragma include_alias( "stdint.h", "KType32.h" )
#include "stdint.h" //ISO C99 type definitions


#if defined _ATL_VER
  #ifndef TRACE
    #define TRACE ATLTRACE
    #define TRACE1 ATLTRACE
  #endif
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

#include "KUsb.h"
#include "KWinUsb.h" //USB structures and enumerations

//-----------------------------------------------------------------------------
/*Enumerate Host Controllers
    Host controllers currently have symbolic names (link) of the form HCDx,
    where x starts at 0.  Use CreateFile() to open each host controller
    symbolic link.  Create a node in the TreeView to represent each host
    controller.

    After a host controller has been opened, send the host controller an
    IOCTL_USB_GET_ROOT_HUB_NAME request to get the symbolic link name of
    the root hub that is part of the host controller.

  Note: Microsoft Windows specific (Win32).

  See also: MSDN KB838100: The USBView.exe sample program does not enumerate
  devices on pre-Windows XP SP1-based computers.
 */
uint_fast32_t EnumerateHostControllers()
{
TRACE(_T("EnumerateHostControllers()\n"));
unsigned short wInstance = 0; //HCD module instance number
char szHostControllerName[16]; //Host Controller Driver (HCD) symbolic name
const unsigned short ARBITRARY_NO = 12; //arbitrary maximum of instances
uint_fast32_t nResult = 0;
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

///////////////////////////////////////////////////////////////////////////////
//CUsbHub class implementation

#include <usbiodef.h> //USB specific GUID; Windows DDK
#include <devguid.h> //USB specific GUID; Windows DDK
//See also: MSDN Article ID: 130869 "How to avoid error 'LNK2001 unresolved external'
//by using DEFINE_GUID"
#include "KUsbHub.h"  //CUsbHub class

#ifndef GUID_CLASS_USB_HOST_CONTROLLER
  #include "KSysPnP.h" //USB device system name
#endif

/*Requires setupapi.lib

  Note: If you intend that your device installation application run on
  Windows 9x/Me, or Windows NT 4.0 or earlier, and you use the CM_Xxx functions,
  be sure that cfgmgr32.lib appears before setupapi.lib in the sources file.
  If your application is intended to run only on Windows 2000 or
  a later NT-based operating system, you can omit cfgmgr32.lib.
 */
#pragma comment( lib, "setupapi" )

#ifdef GUID_CLASS_USB_HOST_CONTROLLER

//-----------------------------------------------------------------------------
/*Enumerates USB Host Controllers.

  Return: number of USB host controllers found on the system.

  See also : EnumerateHostControllers()
 */
uint_fast32_t CUsbHub::Enumerate()
{
TRACE(_T("CUsbHub::Enumerate()\n"));
uint_fast32_t nCount = 0;   //number of USB host controllers
//Note: requires <usbiodef.h>
HDEVINFO hDevInfo = SetupDiGetClassDevs((LPGUID)&GUID_CLASS_USB_HOST_CONTROLLER, //a setup class GUID
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
                                    (LPGUID)&GUID_CLASS_USB_HOST_CONTROLLER, //a setup class GUID
                                         //device interface class
                                    iDevCount, //index to the list of interfaces
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
    SetupDiGetDeviceInterfaceDetail(hDevInfo,
                                    &sdiDevinfo,
                                    NULL,
                                    0,
                                    &dwSize,
                                    NULL
                                    );
    psdiDevDetail = (PSP_DEVICE_INTERFACE_DETAIL_DATA)GlobalAlloc(GPTR, dwSize);
    psdiDevDetail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
    SetupDiGetDeviceInterfaceDetail(hDevInfo,
                                    &sdiDevinfo,
                                    psdiDevDetail,
                                    dwSize,
                                    &dwSize,
                                    NULL
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
      nCount++; //Count existing host controllers
      #ifdef _UNICODE
        TRACE2(_T("  %d. %ws\n"), nCount, psdiDevDetail->DevicePath);
      #else
        TRACE2(_T("  %d. %s\n"), nCount, psdiDevDetail->DevicePath);
      #endif
      CloseHandle(hHcd);
      }

    GlobalFree(psdiDevDetail);
    iDevCount++;
    }

  SetupDiDestroyDeviceInfoList(hDevInfo);
  }
return nCount;
}

#else

//-----------------------------------------------------------------------------
/*Enumerates USB Host Controllers.

  Return: number of USB host controllers found on the system.

  See also: EnumerateHostControllers()
 */
uint_fast32_t CUsbHub::Enumerate()
{
TRACE(_T("CUsbHub::Enumerate()\n"));
uint_fast32_t nCount = 0;   //number of USB host controllers
HDEVINFO hDevInfo = SetupDiGetClassDevs(NULL, //a setup class GUID
                                        SYSTEMENUM_USB, //PnP name of the device
                                        NULL, //user interface window
                                        DIGCF_ALLCLASSES | //list of installed
                                                      //devices for all classes
                                        DIGCF_PRESENT      //currently present
                                                      //devices
                                        );

if (hDevInfo != INVALID_HANDLE_VALUE)
  {
  //Get a context structure for a device information element of
  //the specified device information set.
  SP_DEVINFO_DATA sdiDevinfo; //device instance that is a member of
                              //a device information set.
  sdiDevinfo.cbSize = sizeof(SP_DEVINFO_DATA);
  int iDevCount = 0;
  while(SetupDiEnumDeviceInfo(hDevInfo, //handle to the device information set
                              iDevCount, //index to the list of interfaces
                              &sdiDevinfo //[out] device information
                              ))
    {
    TCHAR szBuff[MAX_PATH];
    DWORD dwLen = sizeof(szBuff);
    //Get a REG_MULTI_SZ string containing the list of hardware IDs for
    //a USB device
    if(GetDeviceProperty(hDevInfo, //handle to the device information
                          &sdiDevinfo, //device instance
                          SPDRP_HARDWAREID, //property to be retrieved
                          szBuff,//requested device property
                          dwLen //required buffer size, in bytes
                        ))
      {
      if(IsRootHub(szBuff))
        {
        nCount++;
        TRACE2(_T("  %d. %s\n"),nCount, szBuff);
        }
      }
    else
      {
      TRACE1(_T("  SetupDiGetDeviceRegistryProperty() Failed #%0.8d!\n"),
              GetLastError());
      }
      
    iDevCount++;
    }

  SetupDiDestroyDeviceInfoList(hDevInfo);
  }
return nCount;
}
#endif

//-----------------------------------------------------------------------------
/*
 */
bool CUsbHub::GetDeviceProperty(HDEVINFO hDevInfo, //[in]
                                SP_DEVINFO_DATA* psdiDevinfo, //[in]
                                const DWORD dwProperty, //[in]
                                TCHAR* szBuff, //[out]
                                DWORD& dwLen //[in, out]
                                )
{
if (IsWinNt())
  {
  //Get a REG_MULTI_SZ string containing the list of hardware IDs for
  //a USB device
  DWORD dwSize  = dwLen;
  if(SetupDiGetDeviceRegistryProperty(hDevInfo, //handle to the device
                                            //information
                                      psdiDevinfo, //device instance
                                      dwProperty, //property to
                                          //be retrieved
                                      NULL, //registry data type
                                      (BYTE*)szBuff,//requested device
                                        //property
                                      dwSize, //size of
                                      //the buffer, in bytes
                                      &dwLen //required buffer
                                      //size, in bytes
                                     ))
  return true;
  }
else //Win98 TODO: test on old Win9x!
  {
  HKEY hDevKey = SetupDiOpenDevRegKey(hDevInfo,
                                      psdiDevinfo,
                                      DICS_FLAG_GLOBAL,
                                      0,
                                      DIREG_DEV,
                                      KEY_ALL_ACCESS
                                      );
  if( hDevKey != INVALID_HANDLE_VALUE )
    {
    TCHAR* szPropertyKey = NULL;
    switch(dwProperty)
      {
      case SPDRP_LOWERFILTERS: szPropertyKey = _T("LowerFilters"); break;
      case SPDRP_UPPERFILTERS: szPropertyKey = _T("UpperFilters"); break;
      case SPDRP_SERVICE:      szPropertyKey = _T("NTMPDriver")  ; break;
      case SPDRP_CLASS:        szPropertyKey = _T("Class")       ; break;
      case SPDRP_HARDWAREID:   szPropertyKey = _T("HardwareID")  ; break;
      case SPDRP_DEVICEDESC:   szPropertyKey = _T("DeviceDesc")  ; break;
      case SPDRP_MFG:          szPropertyKey = _T("Mfg")         ; break;
      default: return false;
      }
    DWORD dwType;
    if( RegQueryValueEx(hDevKey,
                        szPropertyKey,
                        NULL,
                        &dwType,
                        (BYTE*)szBuff,
                        &dwLen) == ERROR_SUCCESS)
      {
      if(dwType == REG_MULTI_SZ)
        {
        //Truncate resulting string
        DWORD i = 0;
        while((szBuff[i] != 0) && (i < dwLen))
          {
          if(szBuff[i] == _T(','))
            {
            szBuff[i] = 0;
            break;
            }
          i++;
          }
        }
      return true;
      }
    RegCloseKey(hDevKey);
    }
  }
return false;
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
 */
