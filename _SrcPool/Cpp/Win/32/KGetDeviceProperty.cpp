/*$RCSfile: KGetDeviceProperty.cpp,v $: implementation file
  $Revision: 1.3 $ $Date: 2009/07/09 22:15:44 $
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

#include <string>
#include "KString.h"
//-----------------------------------------------------------------------------
/*Retrieves the device path from the specified device interface.

  Retruns true and the device path if successful or false if device could
  not be found.
 */
bool GetDevicePath(const HDEVINFO hDevInfo, //[in] handle to a device information set.
                   const LPGUID pguidInterfaceClass, //[in] the device interface
                   //class for the requested interface.
                   const DWORD nMemberIndex,//[in] index to the list of
                   //interfaces in the device information set.
                   CString& strDevicePath //[out] string that specifies
                   //the device path.
                   )
{
ASSERT(hDevInfo != INVALID_HANDLE_VALUE);
bool bResult = false;
if ((hDevInfo != INVALID_HANDLE_VALUE) && (pguidInterfaceClass != NULL) )
  {
  //Get a context structure for a device information element of
  //the specified device information set.
  SP_DEVICE_INTERFACE_DATA sdiDevinfo; //device instance that is a member of
                            //a device information set.
  sdiDevinfo.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

  if(SetupDiEnumDeviceInterfaces(hDevInfo,//handle to the device information set
                                 NULL,    //search for specific interface
                                 pguidInterfaceClass, //a setup
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
       if ( GetLastError()!=NO_ERROR &&
            GetLastError()!=ERROR_NO_MORE_ITEMS )
       {
           // Insert error handling here.
           
       }
    }
  }
return bResult;
}

//-----------------------------------------------------------------------------
/*
 */
void GetDeviceDescription(const GUID& guidDev, //[in]
                   const DWORD nMemberIndex,//[in] index to the list of
                   //interfaces in the device information set.
                   CString& strDeviceDescription //[out]
                   )
{
  HDEVINFO   hDevInfo;
  SP_DEVINFO_DATA DevInfoData;
  DWORD dwSize = 0;
  char szBuff [1024];



  hDevInfo = SetupDiGetClassDevs ((LPGUID) &guidDev, NULL, NULL,
                                   DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

  DevInfoData.cbSize = sizeof (SP_DEVINFO_DATA);

  if (SetupDiEnumDeviceInfo (hDevInfo, nMemberIndex, &DevInfoData))
  {
    dwSize = 1024;

  extern bool GetDeviceProperty(HDEVINFO hDevInfo, //[in] handle to the device
                      //information set that contains the interface
                      SP_DEVINFO_DATA* psdiDevinfo, //[in] structure
                      //that defines the device instance
                      const DWORD dwProperty, //[in] property
                      //to be retrieved
                      TCHAR* szBuff, //[out] requested device property
                      DWORD& dwLen //[in, out] availabile and required
                      //buffer size in bytes
                      );

  GetDeviceProperty(hDevInfo,
                    &DevInfoData,
                    SPDRP_DEVICEDESC,
                    (TCHAR*) szBuff,
                    dwSize
                    );

   strDeviceDescription = (LPTSTR)szBuff;

  }

  SetupDiDestroyDeviceInfoList (hDevInfo);
}

///////////////////////////////////////////////////////////////////////////////
#endif //_WIN32

/*****************************************************************************
 * $Log: KGetDeviceProperty.cpp,v $
 * Revision 1.3  2009/07/09 22:15:44  ddarko
 * GetDeviceDescription()
 *
 * Revision 1.1  2009/07/06 16:09:07  ddarko
 * Extracted from KWinUsb Hub.cpp
 *
 *****************************************************************************/
