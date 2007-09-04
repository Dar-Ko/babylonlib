/*$Workfile: KUsbHid.cpp$: implementation file
  $Revision: 5$ $Date: 2007-08-24 18:15:43$
  $Author: Darko Kolakovic$

  USB HID handler.
  Requires Microsoft Windows DDK libraries.

  Note: Microsoft Windows specific (Win).
  Copyright: CommonSoft Inc
  2004-11-23 Darko Kolakovic
 */
// Group=Windows

#ifdef _WIN32

#ifdef _USE_ATL
  //Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)
  //or preprocessor reports unpaired #endif directive

  #include "stdafx.h" //Standard system header files
#else
  #include <windows.h>
#endif

#if defined _ATL_VER
  #ifndef TRACE
    #define TRACE ATLTRACE
    #define TRACE1 ATLTRACE
  #endif
#endif

#ifndef TRACE
  #ifndef _T
    #include "KTChar.h"
  #endif
  #include "KTrace.h"
#endif

#include "KUsbHid.h" //CUsbHid class
#ifndef USBVID_ANY
  #include "KUsb.h"
#endif

/*Requires setupapi.lib

  Note: If you intend that your device installation application run on
  Windows 9x/Me, or Windows NT 4.0 or earlier, and you use the CM_Xxx functions,
  be sure that cfgmgr32.lib appears before setupapi.lib in the sources file.
  If your application is intended to run only on Windows 2000 or
  a later NT-based operating system, you can omit cfgmgr32.lib.
 */
#pragma comment( lib, "setupapi" )

/*Requires hid.lib

  Note: Microsoft Windows DDK library.
 */
#pragma comment( lib, "hid" )

///////////////////////////////////////////////////////////////////////////////
// CUsbHid Class implementation

//-----------------------------------------------------------------------------
/*Default constructor
 */
CUsbHid::CUsbHid() :
  m_hHid(INVALID_HANDLE_VALUE),
  m_szDevicePath(NULL),
  m_phidCapabilities(NULL),
  m_psdiDevinfo(NULL)
{
}

CUsbHid::~CUsbHid()
{
if (m_hHid != INVALID_HANDLE_VALUE)
  {
  CloseHandle(m_hHid);
  m_hHid = INVALID_HANDLE_VALUE;
  }
if (m_szDevicePath != NULL)
  delete[] m_szDevicePath;
if (m_phidCapabilities != NULL)
  delete m_phidCapabilities;
if (m_psdiDevinfo != NULL)
  delete m_psdiDevinfo;
}

//-----------------------------------------------------------------------------
/*Find a HID specified by a vendor (VID) and product identification
  (PID) number. If the vendor is not specified (VID is USBVID_ANY), the method
  return true when first HID class object is found in the device tree. If PID
  is USBPID_ANY, the method searches for any device from the specified vendor
  and returns true when the first HID is found. If the required device is found,
  handle to the object is preserved as the m_hHid member of the CUsbHid class.

  Returns: true if the requested device of the HID class is found in the
  USB device tree. Returns false if the device is not present.

  See also: USB Implementers Forum, Inc (USB-IF) at http://www.usb.org; CUsbId
 */
bool CUsbHid::Find(const uint16_t wVendorId, //[in] USB device vendor
                                             //identification (VID) number
                   const uint16_t wProductId //[in] USB product identification
                                             //(PID) number
                  )
{
TRACE2(_T("CUsbHid::Find(0x%4.4X, 0x%4.4X)\n"), wVendorId, wProductId);
bool bResult = false;

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
                                    &guidHid, //a HID class GUID
                                    //device interface class
                                    iDevCount, //index to the list of interfaces
                                    &sdiDevinfo //[out] device information
                                   ))
    {
    //Obtain information from HID Object.
    PSP_DEVICE_INTERFACE_DETAIL_DATA psdiDevDetail = NULL;
    DWORD dwSize = 0; //size of the holding buffer
    //Get required buffer size
    SetupDiGetDeviceInterfaceDetail(hDevInfo,
                                    &sdiDevinfo,
                                    NULL,
                                    0,
                                    &dwSize, //required size for the buffer
                                    NULL
                                    );
    //Allocate space for the string that specifies the device path
    psdiDevDetail = (PSP_DEVICE_INTERFACE_DETAIL_DATA) new char[dwSize];
    psdiDevDetail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
    SetupDiGetDeviceInterfaceDetail(hDevInfo,
                                    &sdiDevinfo,
                                    psdiDevDetail,
                                    dwSize,
                                    &dwSize,
                                    NULL
                                    );
    //Open a HID
    //Note: generic keyboard or pointing device driver does not allow
    //read nor write access to the device.
    HANDLE hHid = CreateFile(psdiDevDetail->DevicePath,
                             0, //query device existence without
                                //accessing the device.
                            FILE_SHARE_READ | FILE_SHARE_WRITE,
                            NULL,//if lpSecurityAttributes is NULL,
                            //the handle cannot be inherited.
                            OPEN_EXISTING,
                            0,
                            NULL);
    if (hHid != INVALID_HANDLE_VALUE)
      {
      #ifdef _UNICODE
        TRACE2(_T("  %d. %ws\n"), iDevCount, psdiDevDetail->DevicePath);
      #else
        TRACE2(_T("  %d. %s\n"), iDevCount, psdiDevDetail->DevicePath);
      #endif

      if ( wVendorId != USBVID_ANY )
        {
        //Get the attributes of a specified top-level collection.
        HIDD_ATTRIBUTES hiddAttributes; //attributes of the top-level collection
        hiddAttributes.Size = sizeof(hiddAttributes);
        if ( HidD_GetAttributes(hHid, &hiddAttributes) )
          {
          if (hiddAttributes.VendorID == wVendorId)
            if (( wProductId != USBPID_ANY ) &&
                ( hiddAttributes.ProductID != wProductId ))
              {
              CloseHandle(hHid);
              }
            else
            bResult = true;
          }
        }
      else
        bResult = true;
      }
    #ifdef _DEBUG
      else
        {
        TRACE1(_T("  Failed to open HID: #%0.8d!\n"), GetLastError());
        }
    #endif

    if(bResult) //Desired device is found
      {
      if (m_hHid != INVALID_HANDLE_VALUE)
        CloseHandle(m_hHid);
      m_hHid = hHid; //Preserve the device handle
      if(m_szDevicePath != NULL)
        delete[] m_szDevicePath;
      size_t nLen = _tcsclen(psdiDevDetail->DevicePath) + 1;
      m_szDevicePath = new TCHAR[nLen];
      if(m_szDevicePath != NULL)
        _tcsncpy(m_szDevicePath, psdiDevDetail->DevicePath, nLen);
      delete[] psdiDevDetail;

      if (m_psdiDevinfo == NULL)
        m_psdiDevinfo = new SP_DEVINFO_DATA();
      if (m_psdiDevinfo != NULL)
        {
        m_psdiDevinfo->cbSize = sizeof(SP_DEVINFO_DATA);
        //Get context structure for a device information element of
        //the specified device information set.
        if (!SetupDiEnumDeviceInfo(hDevInfo, iDevCount, m_psdiDevinfo))
          {
          TRACE1(_T("  Failed to get SP_DEVINFO_DATA: #%0.8d!"),
                 GetLastError());
          delete m_psdiDevinfo;
          m_psdiDevinfo = NULL;
          }
        }
      break; //Return the result

      }

     delete[] psdiDevDetail;
    iDevCount++;
    }

  SetupDiDestroyDeviceInfoList(hDevInfo);
  }
return bResult;
}

//-----------------------------------------------------------------------------
/*Obtains device's capabilites.
  Search for the device before querying device's capabilites.

  Returns: pointer to device's HIDP_CAPS structure or NULL in case of a failure.
 */
const PHIDP_CAPS CUsbHid::GetDeviceCapabilities()
{
TRACE(_T("CUsbHid::GetDeviceCapabilities()\n"));

  //Get top-level collection's preparsed data.
PHIDP_PREPARSED_DATA  phidPreparsedData;

if((m_hHid != INVALID_HANDLE_VALUE) &&  //handle to a top-level collection
   HidD_GetPreparsedData (m_hHid, &phidPreparsedData))
  {
  //Obtain generic HID class device capability information
  if (m_phidCapabilities == NULL)
    m_phidCapabilities = new HIDP_CAPS();

  if ( (m_phidCapabilities != NULL) &&
       HidP_GetCaps (phidPreparsedData, m_phidCapabilities) == HIDP_STATUS_SUCCESS)
    {
    return m_phidCapabilities;
    }
  HidD_FreePreparsedData(phidPreparsedData);
  }
return NULL;
}

//-----------------------------------------------------------------------------
/*Configures installation parameters for a particular device information
  element.

  Device state can be one of the following values:

    DICS_ENABLE      The device is being enabled.
                     For this state change, Setup enables the device if the
                     DICS_FLAG_GLOBAL flag is specified. If the D
                     ICS_FLAG_CONFIGSPECIFIC flag is specified and the current
                     hardware profile is specified then Setup enables the device.
                     If the DICS_FLAG_CONFIGSPECIFIC is specified and not the
                     current hardware profile then Setup sets some flags in
                     the registry and does not change the device's state.
                     Setup will change the device state when the specified
                     profile becomes the current profile.
    DICS_DISABLE     The device is being disabled.
                     For this state change, Setup disables the device if
                     the DICS_FLAG_GLOBAL flag is specified. If the
                     DICS_FLAG_CONFIGSPECIFIC flag is specified and the current
                     hardware profile is specified then Setup disables the device.
                     If the DICS_FLAG_CONFIGSPECIFIC is specified and not the
                     current hardware profile then Setup sets some flags in the
                     registry and does not change the device's state.
    DICS_PROPCHANGE  The properties of the device have changed.
                     For this state change, Setup ignores the Scope information
                     and stops and restarts the device.
    DICS_START       The device is being started (if the request is for the
                     currently active hardware profile). Make the change in
                     the specified profile only; you cannot perform this
                     change globally. Setup only starts the device if the current
                     hardware profile is specified, otherwise Setup sets a
                     registry flag and does not change the state of the device.
    DICS_STOP        The device is being stopped. The driver stack will be
                     unloaded and the CSCONFIGFLAG_DO_NOT_START flag will be set
                     for the device. Make the change in the specified profile
                     only; you cannot perform this change globally. Setup only
                     stops the device if the current hardware profile is
                     specified, otherwise Setup sets a registry flag and does
                     not change the state of the device.

  Note: installation parameters for generic keyboard or pointing device driver
  could not be changed.

  Returns: true if successful or false in case of a failure. To get extended
  error information, call GetLastError().
 */
bool CUsbHid::SetDeviceState(const DWORD dwState, //[IN] new device state
                             const PSP_DEVINFO_DATA psdiDevInfo //[in]
                            )
{
TRACE1(_T("CUsbHid::SetDeviceState(dwState = %d)\n"), dwState);

if (psdiDevInfo == NULL)
  {
  SetLastError(E_POINTER);
  return false;
  }

/*The scope of a device property change:
  DICS_FLAG_GLOBAL         0x00000001  make change in all hardware profiles
  DICS_FLAG_CONFIGSPECIFIC 0x00000002  make change in specified profile only
  DICS_FLAG_CONFIGGENERAL  0x00000004  one or more hardware profile-specific
                                       changes to follow.
 */
HDEVINFO hDevinfo = *this; //Get handle to the device information set
SP_PROPCHANGE_PARAMS spPropChangeParams;
memset(&spPropChangeParams, 0, sizeof(spPropChangeParams));
spPropChangeParams.ClassInstallHeader.cbSize = sizeof(SP_CLASSINSTALL_HEADER);
spPropChangeParams.ClassInstallHeader.InstallFunction = DIF_PROPERTYCHANGE;
spPropChangeParams.Scope = ((dwState == DICS_START) ||
                            (dwState == DICS_STOP)) ?
                            DICS_FLAG_CONFIGSPECIFIC : DICS_FLAG_GLOBAL;
spPropChangeParams.StateChange = dwState;
spPropChangeParams.HwProfile = 0; //Zero specifies the current hardware profile

if(SetupDiSetClassInstallParams(hDevinfo, //handle to the device information set
                               psdiDevInfo, //device install class to set
                               (SP_CLASSINSTALL_HEADER*) &spPropChangeParams,
                                 //new class install parameters
                               sizeof(spPropChangeParams)) )
  {
  //Call the appropriate class installer and any registered co-installers
  if(SetupDiCallClassInstaller(DIF_PROPERTYCHANGE,
                               hDevinfo,
                               psdiDevInfo))
    {
    return true;
    }
  }

TRACE1(_T("  Failed: #%0.8d!\n"), GetLastError());
return false;
}

//-----------------------------------------------------------------------------
/*Start or stop previously discovered device driver.

  Returns: true if successful or false in case of a failure. To get extended
  error information, call GetLastError().
 */
bool CUsbHid::Enable(bool bEnable //[in] = true enable or disable device
                     //driver
                    )
{
TRACE1(_T("CUsbHid::Enable(%d)\n"),(bEnable ? DICS_ENABLE : DICS_DISABLE));
if(m_psdiDevinfo != NULL)
  {
  return SetDeviceState( (bEnable ? DICS_ENABLE : DICS_DISABLE),
                         m_psdiDevinfo );
  }
return false;
}

//-----------------------------------------------------------------------------
/*Start or stop previously discovered device driver.

  Returns: true if successful or false in case of a failure. To get extended
  error information, call GetLastError().
 */
bool CUsbHid::Start(bool bStart //[in] = true start or stop discovered device
                    //driver
                     )
{
TRACE1(_T("CUsbHid::Enable(%d)\n"),(bStart ? DICS_START : DICS_STOP));
if(m_psdiDevinfo != NULL)
  {
  return SetDeviceState( (bStart ? DICS_START : DICS_STOP),
                         m_psdiDevinfo );
  }
return false;
}

//-----------------------------------------------------------------------------
/*Restart driver of the previously discovered device.

  Returns: true if successful or false in case of a failure. To get extended
  error information, call GetLastError().
 */
bool CUsbHid::Restart()
{
TRACE(_T("CUsbHid::Restart()\n"));
if(m_psdiDevinfo != NULL)
  {
  return SetDeviceState( DICS_PROPCHANGE, m_psdiDevinfo );
  }
return false;
}

#endif //_WIN32
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: $
 *****************************************************************************/
