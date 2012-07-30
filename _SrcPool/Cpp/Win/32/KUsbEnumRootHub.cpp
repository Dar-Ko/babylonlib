/*$RCSfile: KUsbEnumRootHub.cpp,v $: implementation file
  $Revision: 1.6 $ $Date: 2012/07/30 15:50:23 $
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
#include "KStrArray.h" //CStringArray class

//-----------------------------------------------------------------------------
/*Enumerates USB host controllers using its hardware ID.
  Host controller is also known as the root hub, the root tier or
  simply as the root.
  The host controller controls all traffic on the PCI bus and also functions
  as a hub.

  One or more host controllers can be built into the motherboard of the computer
  or installed as an add-in CardBus or PCI card in the computer to gain additional
  ports and bandwidth.

  Return: number of root USB hubs found on the system.

  Browses through hardware IDs for an USB device of, enumerating every ROOT_HUB.
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
unsigned int EnumerateRootUsbHub(CStringArray* pUsbHardwareIds //[out] = NULL
                                 //list of USB host controller IDs
                                )
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
    //Get a REG_MULTI_SZ string containing the hardware IDs for an USB device.
    //HardwareIds are supplied by device's INF file in Models section.
    //List have following format: "hw-id1\0hw-id2\0…hw-idn\0\0"
    //for example:
    //  "USB\ROOT_HUB&VID8086&PID24D2&REV0002\0USB\ROOT_HUB&VID8086&PID24D2\0USB\ROOT_HUB\0\0"
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
        if (pUsbHardwareIds != NULL)
          pUsbHardwareIds->Add(szBuff);
        }
      }
    else
      {
      TRACE1(_T("  SetupDiGetDeviceRegistryProperty() Failed #%0.8d!\n"),
              GetLastError());
      if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
        {
        TRACE1(_T("  Increase buffer size to %d bytes!\n"), dwLen);
        }
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
 * Revision 1.6  2012/07/30 15:50:23  ddarko
 * Build note
 *
 * Revision 1.5  2009/08/28 21:06:53  ddarko
 * *** empty log message ***
 *
 * Revision 1.4  2009/07/09 22:15:44  ddarko
 * GetDeviceDescription()
 *
 * Revision 1.3  2009/07/07 20:46:05  ddarko
 * Return list of device names
 *
 * Revision 1.2  2009/07/06 21:35:59  ddarko
 * Comment
 *
 * Revision 1.1  2009/07/06 18:30:59  ddarko
 * Extracted from KWinUsbHub.cpp
 *
 *****************************************************************************/

/*Note: Used code from Microsoft Windows DDK sample USBView.

  WDK Build Environment Refactoring:
  =================================
  ref: http://www.tech-archive.net/Archive/Development/microsoft.public.development.device.drivers/2005-08/msg00980.html
       http://download.microsoft.com/download/f/0/5/f05a42ce-575b-4c60-82d6-208d3754b2d6/WDK_BE-Refactoring.ppt


  Header File Changes in the Windows Driver Kit:
  http://download.microsoft.com/download/5/D/6/5D6EAF2B-7DDF-476B-93DC-7CF0072878E6/headers.doc


  These describe the changes between the old DDK and the WDK, including the header file reorganisation that has taken place and led to my build problems.


  In the release notes for version 5112 WDK, there’s the following brief mention of the changes:

  Header Versioning Activated
  This release of the WDK implements a versioned header system. The overall effect of this new system is that the WDK no longer contains operating system-specific include directories under \inc. The WDK build environments are configured for this change, but customized build environments that have hard-coded include paths might break.

  Workaround: Use the WDK build environments, or update customized build environments appropriately.

  >From the above 2 URLs, I found the following essential information:

  ----

  1) The WDK build environment defines the constant NTDDI_VERSION to match the driver’s build environment.
  - Since various projects in Tony’s updated Application Manager solution use the DDK, and I’m building them in Microsoft Visual Studio .NET, this is the crux of the problem. If I was to build all the projects using the WDK build environment, in theory, this build problem shouldn’t exist.


  2) In order to still be able to build in Visual Studio, the solution is to define NTDDI_VERSION with a target operating system value

  Table 1: Windows Operating System Version Constants

  Constant Version of operating system

  NTDDI_WIN2K Windows 2000
  NTDDI_WINXP Windows XP
  NTDDI_WS03 Windows Server 2003
  NTDDI_LONGHORN Windows Longhorn

  (declared in the new sdkddkver.h header file)

  · DO be sure that you build your drivers within the build environment provided by the DDK, or that you define the necessary environment variables to ensure that NTDDI_VERSION is correctly defined.

  ----
  Taking into account this information, as a test, I added this line at the
  top of RulesInfo.cpp

  #define NTDDI_VERSION NTDDI_WINXP

  The resulting RulesInfo.i file then contained:

  (OSVER(NTDDI_WINXP) == NTDDI_WIN2K && SPVER(NTDDI_WINXP) >=5) ||
  (OSVER(NTDDI_WINXP) == NTDDI_WINXP && SPVER(NTDDI_WINXP) >=2) ||
  (OSVER(NTDDI_WINXP) == NTDDI_WS03 && SPVER(NTDDI_WINXP) >=1) ||
  (OSVER(NTDDI_WINXP) >= NTDDI_WINLH)


  Indicating that OSVER and SPVER were still undefined.

  I found that these are defined in the new “sdkddkver.h” header file, and that is #included in the DDK version of “windows.h”, found at:
  C:\WINDDK\5112\inc\api

  So, after all that, the main thing I needed to do was to ensure that this include file directory is listed at the top of the Include Directories in Visual Studio’s Tools -> Options… -> Projects -> VC++ Directories settings.
  It then turned out that NTDDI_VERSION gets #defined in “sdkddkver.h” too, so #define'ing it wasn’t necessary in my source file.

  After this primary reason for my build problem, I then had another 3 -
  here's how I resolved them:

  1) Even though everything in the project compiled, no .obj files were being created, and it couldn’t link.

  - It turns out that that having the “C/C++ -> Preprocessor -> Generate
  Processed File“ project setting set to “With Line Numbers (/P)” caused no ..obj files to be created!?! Turning it off fixed the problem.


  2) There was then a problem with another project in the solution against the WDK:


  c:\WINDDK\5112\inc\api\usb200.h(85) : error C2332: 'struct' : missing tag name
  c:\WINDDK\5112\inc\api\usb200.h(85) : error C2011: '__unnamed' : 'enum' type redefinition
  C:\WINDDK\5112\inc\api\shlwapi.h(1482) : see declaration of '__unnamed'
  c:\WINDDK\5112\inc\api\usb200.h(85) : error C2059: syntax error : 'constant'
  c:\WINDDK\5112\inc\api\usb200.h(85) : error C2334: unexpected token(s) preceding '{'; skipping apparent function body

  In usb200.h, the following was defined:

  typedef union _USB_HIGH_SPEED_MAXPACKET {
  struct _MP {
  USHORT MaxPacket:11; // 0..10 
  USHORT HSmux:2; // 11..12 
  USHORT Reserved:3; // 13..15 
  };

  USHORT us;

  } USB_HIGH_SPEED_MAXPACKET, *PUSB_HIGH_SPEED_MAXPACKET;

  But this caused a problem because _MP is already a #defined constant in
  mbctype.h:
  // bit masks for MBCS character types

  #define _MS 0x01 // MBCS single-byte symbol 
  #define _MP 0x02 // MBCS punct 

  ….

  So my inelegant fix for this to put #undef _MP above the #include
  <afxtempl.h> line in the project's stdafx.h file.

  3) A simple one – the PUSB_NODE_CONNECTION_INFORMATION_EX used in this
  project is defined within “#if (_WIN32_WINNT >= 0x0501)” in
  C:\WINDDK\5112\inc\api\usbioctl.h
  It wasn't inside a #ifdef in the previous DDK version.

  So I simply updated the _WIN32_WINNT #define in the project's stdafx.h file
  as follows:

  #define _WIN32_WINNT 0x0501 // Change this to the appropriate value to
  target Windows 2000 or later.
 */
