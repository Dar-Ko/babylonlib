/*$RCSfile: KGetDeviceProperty.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2009/07/06 16:09:07 $
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

//-----------------------------------------------------------------------------
/*Retrieves the specified device property value stored by the device on the
  computer.

  Returns: true if successful and requested device property or false in
  case of a failure. To get extended error information, call GetLastError().
 */
bool CUsbHub::GetDeviceProperty(HDEVINFO hDevInfo, //[in] handle to the device
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
TRACE1(_T("CUsbHub::GetDeviceProperty(dwProperty = %d)\n"), dwProperty);
if ((GetVersion() < 0x80000000)
  {
  //Get a REG_MULTI_SZ string containing the list of hardware IDs for
  //a USB device
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

TRACE1(_T("  Failed to obtain the property: #%0.8d!\n"), GetLastError());
return false;
}

///////////////////////////////////////////////////////////////////////////////
#endif //_WIN32

/*****************************************************************************
 * $Log: KGetDeviceProperty.cpp,v $
 * Revision 1.1  2009/07/06 16:09:07  ddarko
 * Extracted from KWinUsb Hub.cpp
 *
 *****************************************************************************/
