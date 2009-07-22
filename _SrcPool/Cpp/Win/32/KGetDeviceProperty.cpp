/*$RCSfile: KGetDeviceProperty.cpp,v $: implementation file
  $Revision: 1.6 $ $Date: 2009/07/22 19:20:32 $
  $Author: ddarko $

  Device Property method.
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
#endif

/*Requires setupapi.lib

  Note: If you intend that your device installation application run on
  Windows 9x/Me, or Windows NT 4.0 or earlier, and you use the CM_Xxx functions,
  be sure that cfgmgr32.lib appears before setupapi.lib in the sources file.
  If your application is intended to run only on Windows 2000 or
  a later NT-based operating system, you can omit cfgmgr32.lib.
 */
#pragma comment( lib, "setupapi" )
#include <setupapi.h> //Device Management Structures

#ifndef TRACE
  #ifndef _T
    #include "KTChar.h"
  #endif
  #include "KTrace.h"
#endif

//-----------------------------------------------------------------------------
/*Retrieves the specified device property value stored by the device on the
  computer.

  Returns: true if successful and requested device property or false in
  case of a failure. To get extended error information, call GetLastError().
 */
bool GetDeviceProperty(HDEVINFO hDevInfo, //[in] handle to the device
                      //information set that contains the interface
                      SP_DEVINFO_DATA* psdiDevinfo, //[in] structure
                      //that defines the device instance
                      const DWORD dwProperty, //[in] property
                      //to be retrieved
                      TCHAR* szBuff, //[out] requested device property
                      DWORD& dwLen //[in, out] availabile and required
                      //buffer size in bytes
                      )
{
#ifdef _DEBUG
  extern LPCTSTR DumpDevicePropertyCode(const DWORD dwProperty);
  #ifdef _UNICODE
    TRACE1(_T("  GetDeviceProperty(%ws)\n"), DumpDevicePropertyCode(dwProperty));
  #else
    TRACE1(_T("  GetDeviceProperty(%s)\n"), DumpDevicePropertyCode(dwProperty));
  #endif
#endif
if (GetVersion() < 0x80000000)
  {
  DWORD dwSize  = dwLen;
  //Note: Requires Windows XP, Windows 2000 Professional,
  //Windows Me or Windows 98
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
    {
    return true;
    }
  else
    {
     /*Bug: SetupDiGetDeviceRegistryProperty function returns an incorrect
       RequiredSize value on DBCS characters in Windows 2000.

       This problem occurs in single-byte character (SBCS) projects because
       the size-conversion logic does not calculate correctly the required
       capacity in bytes of wide character buffer.

       Note: Microsoft Windows 2000 specific.
       See also: MSDN Article ID 888609 (KB888609).
     */
    TRACE1(_T("    SetupDiGetDeviceRegistryProperty() Failed #%0.8d!\n"),
            GetLastError());
    #ifndef _UNICODE
      if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
        {
        //Double required size as workaround to the bug described in
        //MSDN Article ID 888609
        dwLen *= 2;
        }
    #endif
    }
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

TRACE1(_T("    Failed to obtain the property: #%0.8d!\n"), GetLastError());
return false;
}

#ifdef _USE_STL
  #include <string>
#endif
#ifdef _USE_ATL
  #pragma include_alias( "KString.h", "atlstr.h" )
#endif
#include "KString.h"

//-----------------------------------------------------------------------------
/*Retrieves the device path from the specified device interface.

  Returns true and the device path if successful or false if device could
  not be found.
 */
bool GetDevicePath(const GUID& guidInterfaceClass, //[in] the device interface
                   //class for the requested interface.
                   const DWORD nMemberIndex,//[in] index to the list of
                   //interfaces in the device information set.
                   CString& strDevicePath //[out] string that specifies
                   //the device path.
                   )
{
bool bResult = false;
//Get handle to the device information set
HDEVINFO hDevInfo =
    SetupDiGetClassDevs(&guidInterfaceClass,    //a setup class GUID
                        NULL,                   //PnP name of the device
                        NULL,                   //user interface window
                        DIGCF_DEVICEINTERFACE | //list of installed interface class devices
                        DIGCF_PRESENT           //currently present devices
                        );

//Disable warning C4127: conditional expression in ASSERT is constant
#pragma warning (disable: 4127)
  ASSERT(INVALID_HANDLE_VALUE != hDevInfo);
#pragma warning (default: 4127)

if(hDevInfo != INVALID_HANDLE_VALUE)
  {
  //Get a context structure for a device information element of
  //the specified device information set.
  SP_DEVICE_INTERFACE_DATA sdiDevinfo; //device instance that is a member of
                            //a device information set.
  sdiDevinfo.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

  if(SetupDiEnumDeviceInterfaces(hDevInfo,//handle to the device information set
                                 NULL,    //search for specific interface
                                 &guidInterfaceClass, //a setup
                                      //class GUID device interface class
                                 nMemberIndex, //index to the list of interfaces
                                 &sdiDevinfo   //[out] device information
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
    strDevicePath = psdiDevDetail->DevicePath;

    delete[] psdiDevDetail;
    bResult = true;
    }
  else
    {
    if(GetLastError() != NO_ERROR &&
       GetLastError() != ERROR_NO_MORE_ITEMS)
      {
      //ToDO: Insert error handling here.

      }
    }

  SetupDiDestroyDeviceInfoList(hDevInfo);
  }
return bResult;
}

//-----------------------------------------------------------------------------
/*Retrieves a registry string containing the description of a device.

  Returns true and the device description if successful or false. If device could
  not be found, GetLastError() could returns ERROR_NO_MORE_ITEMS and fuction fails.

  Example:

      #include "UsbGuid.h" //USB specific GUID
      ...
      unsigned int nCount = 0; //1st USB host controller
      CString strResult;
      bool bResult =
              GetDeviceDescription(GUID_DEVINTERFACE_USB_HOST_CONTROLLER,
                                   nCount,
                                   strResult);
      if(!bResult)
        {
        if((GetLastError() == ERROR_NO_MORE_ITEMS) ||
           (GetLastError() == NO_ERROR))
          {
          strResult = _T("The system is without USB controllers");
          bResult = true;
          }
        }
 */
bool GetDeviceDescription(const GUID& guidDev, //[in] handle to the device
                          //information set that contains the interface
                          const DWORD nMemberIndex,//[in] index to the list of
                          //interfaces in the device information set.
                          CString& strDeviceDescription //[out] the description
                          //of a device.
                          )
{
bool bResult = false;
//Get handle to the device information set
HDEVINFO hDevInfo =
    SetupDiGetClassDevs(&guidDev,             //a setup class GUID
                        NULL,                   //PnP name of the device
                        NULL,                   //user interface window
                        DIGCF_DEVICEINTERFACE | //list of installed interface class devices
                        DIGCF_PRESENT           //currently present devices
                        );
if (hDevInfo != INVALID_HANDLE_VALUE)
  {
  SP_DEVINFO_DATA sddDevInfo;
  sddDevInfo.cbSize = sizeof(SP_DEVINFO_DATA);

  //Get the device information structure of the specified device.
  if (SetupDiEnumDeviceInfo (hDevInfo, nMemberIndex, &sddDevInfo))
    {
    TCHAR szBuff[MAX_PATH];
    DWORD dwSize = sizeof(szBuff);
    extern bool GetDeviceProperty(HDEVINFO hDevInfo, SP_DEVINFO_DATA* psdiDevinfo,
                        const DWORD dwProperty, TCHAR* szBuff, DWORD& dwLen);

    if(GetDeviceProperty(hDevInfo, //[in] handle to the device
                        //information set that contains the interface
                      &sddDevInfo,  //[in] structure
                        //that defines the device instance
                      SPDRP_DEVICEDESC,//[in] property
                        //to be retrieved
                      szBuff, //[out] requested device property
                      dwSize //[in, out] availabile and required
                        //buffer size in bytes
                      ))
      {
      strDeviceDescription = (LPTSTR)szBuff;
      bResult = true;
      }
    else
      {
      if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
        {
        LPTSTR szDescription = (LPTSTR)new char[dwSize];
        if (szDescription != NULL)
          {
          if(GetDeviceProperty(hDevInfo,
                            &sddDevInfo,
                            SPDRP_DEVICEDESC,
                            szBuff,
                            dwSize
                            ))
            {
            strDeviceDescription = szDescription;
            bResult = true;
            }
          delete[] szDescription;
          }
        }

      //Failed 1st or 2nd try to obtain device property
      if(GetLastError() != NO_ERROR &&
        GetLastError() != ERROR_NO_MORE_ITEMS)
        {
        //ToDO: Insert error handling here.

        }

      }
    }

  SetupDiDestroyDeviceInfoList(hDevInfo);
  }
return bResult;
}

///////////////////////////////////////////////////////////////////////////////
#endif //_WIN32

/*****************************************************************************
 * $Log: KGetDeviceProperty.cpp,v $
 * Revision 1.6  2009/07/22 19:20:32  ddarko
 * Use Atl CString
 *
 * Revision 1.5  2009/07/20 13:59:13  ddarko
 * ATLTRACE macro
 *
 * Revision 1.1  2009/07/06 16:09:07  ddarko
 * Extracted from KWinUsb Hub.cpp
 *
 *****************************************************************************/
