/*$RCSfile: KUsbEnumRootHub.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2009/07/06 18:30:59 $
  $Author: ddarko $

  Enumerates root USB hubs.
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
  #include <string.h>
#endif

#ifndef TRACE
  #ifndef _T
    #include "KTChar.h"
  #endif
  #include "KTrace.h"
#endif

#include <setupapi.h> //Device Management Structures

#include "KWinUsb.h" //USB structures and enumerations

//-----------------------------------------------------------------------------
/*Enumerates root USB hubs.

  Return: number of root USB hubs found on the system.

  Browses through hardware IDs for an USB device of, enumerationg every ROOT_HUB.
  Example of USB hardware IDs:

    1. USB\ROOT_HUB&VID8086&PID24D2&REV0002
    2. USB\ROOT_HUB&VID8086&PID24D4&REV0002
    3. USB\ROOT_HUB&VID8086&PID24DE&REV0002
    4. USB\ROOT_HUB20&VID8086&PID24DD&REV0002

  A hardware ID is a vendor-defined identification string that Setup uses 
  to match a device to an INF file. In most cases, a device has associated with
  it a list of hardware IDs.

  See also: EnumerateHostControllers(), SPDRP_HARDWAREID
 */
unsigned int EnumerateRootUsbHub()
{
TRACE(_T("EnumerateRootUsbHub() using SYSTEMENUM_USB\n"));
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
    extern bool GetDeviceProperty(HDEVINFO hDevInfo,
                      SP_DEVINFO_DATA* psdiDevinfo,
                      const DWORD dwProperty,
                      TCHAR* szBuff,
                      DWORD& dwLen);
    //Get a REG_MULTI_SZ string containing the list of hardware IDs for
    //an USB device
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

///////////////////////////////////////////////////////////////////////////////
#endif //_WIN32

/*****************************************************************************
 * $Log: KUsbEnumRootHub.cpp,v $
 * Revision 1.1  2009/07/06 18:30:59  ddarko
 * Extracted from KWinUsbHub.cpp
 *
 *****************************************************************************/

/*Note: Used code from Microsoft Windows DDK sample USBView
 */
