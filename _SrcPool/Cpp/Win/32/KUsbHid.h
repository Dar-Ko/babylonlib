/*$Workfile: KUsbHid.h$: header file
  $Revision: 4$ $Date: 2007-08-24 18:15:44$
  $Author: Darko Kolakovic$

  USB HID handler.
  Note: Microsoft Windows specific (Win).
  Copyright: CommonSoft Inc
  2004-11-23 Darko Kolakovic
 */
// Group=Windows

#ifndef _KUSBHID_H_
    //$Workfile: KUsbHid.h$ sentry
  #define _KUSBHID_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifdef WIN32
  #ifndef _USE_ATL
    #include <windows.h>
  #endif
  #include <setupapi.h> //Device Management Structures
  extern "C"
  {
  #include <hidsdi.h>//USB specific HID class GUID; Windows DDK
                     //to use in the user space
  //Note: include <hidpddi.h> to use in the kernel space
  LPTSTR StrIStr(LPCTSTR szSource, LPCTSTR szToken);
  }
  #include <hidpi.h> //HIDP_CAPS struct; Windows DDK
#endif

#ifdef _MSC_VER
  //Microsoft Visual C/C++ compiler
  #pragma include_alias( "stdint.h", "KType32.h" )
  #include "stdint.h" //ISO C99 type definitions
#endif
#ifndef SYSTEMENUM_HID
  #include "KSysPnP.h"
#endif

///////////////////////////////////////////////////////////////////////////////
/*Handles the Universal Serial Bus Human Interface Devices (USB HID).
  The HID class consists primarily of devices that are used by humans to control
  the operation of computer systems. The devices included in the HID class are
  keyboards, pointing devices, bar-code readers, indicators or specialized
  displays and other equipment.

  Note: Microsoft Windows specific (Win32).

  See also: www.usb.org HID Information, "Device Class Definition for Human
  Interface Devices (HID)": Firmware Specification, v1.11
 */
class CUsbHid
  {
public:
  CUsbHid();
  virtual ~CUsbHid();

public:
  bool Find(const uint16_t wVendorId, const uint16_t wProductId);
  const TCHAR* GetDevicePath() const;
  const PHIDP_CAPS GetDeviceCapabilities();
  bool Enable(bool bStart = true);
  bool Start(bool bStart = true);
  bool Restart();
  bool IsHid(const TCHAR* szHardwareId) const;
  operator HDEVINFO() const;
  const PSP_DEVINFO_DATA GetDevInfo() const;
protected:
  bool SetDeviceState(const DWORD dwState,
                      const PSP_DEVINFO_DATA psdiDevInfo);
protected:
  HANDLE m_hHid; //handle to requested device of the HID class
  TCHAR* m_szDevicePath; //zero-terminated string specifying the HID path
  PHIDP_CAPS m_phidCapabilities;  //device capability information
  PSP_DEVINFO_DATA m_psdiDevinfo; //device instance information
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*
  Returns: zero-terminated string or NULL if device is not discovered with
  CUsbHid::Find() method.
 */
inline const TCHAR* CUsbHid::GetDevicePath() const
{
return m_szDevicePath;
}

//-----------------------------------------------------------------------------
/*Verifies if hardware is of HID class.
  Hardware ID have following format:
    HID\Vid_mmmm&Pid_nnnn&...
 */
inline bool CUsbHid::IsHid(const TCHAR* szHardwareId //[in]
              ) const
{
if ((szHardwareId != NULL) && (szHardwareId[0] != '\0'))
  {
  return (StrIStr(szHardwareId, SYSTEMENUM_HID) == szHardwareId);
  }
return false;
}

//-----------------------------------------------------------------------------
/*Get handle to the HID class device information set for the installed and
  present devices.

  Returns: a handle to a device information set containing all installed
  and present devices. In case of a failure, the return value is
  INVALID_HANDLE_VALUE. To get extended error information, call GetLastError().
 */
inline CUsbHid::operator HDEVINFO() const
{
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
#ifdef _DEBUG
  #if defined _ATL_VER
    #ifndef TRACE1
      #define TRACE1 ATLTRACE
    #endif
  #endif

  if (hDevInfo == INVALID_HANDLE_VALUE)
    TRACE1(_T("  hDevInfo = INVALID_HANDLE_VALUE (Error #%0.8d)!\n"),
           GetLastError());
#endif
return hDevInfo;
}

//-----------------------------------------------------------------------------
/*
  Returns: structure that defines the previously discovered device instance or
  NULL.
 */
inline const PSP_DEVINFO_DATA CUsbHid::GetDevInfo() const
{
return m_psdiDevinfo;
}

///////////////////////////////////////////////////////////////////////////////
#endif  //_KUSBHID_H_
/*****************************************************************************
 * $Log: $
 *****************************************************************************/
