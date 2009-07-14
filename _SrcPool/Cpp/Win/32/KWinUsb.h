/*$RCSfile: KWinUsb.h$: header file
  $Revision: 4$ $Date: 2007-08-24 18:15:44$
  $Author: Darko Kolakovic$

  USB types related to Windows platform
  Note: Microsoft Windows specific (Win).
  Copyright: CommonSoft Inc
  2004-03-10 Darko Kolakovic
 */
// Group=Windows

#ifndef _KWINUSB_H_
    //$RCSfile: KWinUsb.h$ sentry
  #define _KWINUSB_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifdef _WIN32 //Windows 32-bit platform

#ifndef _USE_ATL
  #include <windows.h>
#else
  #include "KTraceAtl.h"
#endif

///////////////////////////////////////////////////////////////////////////////
//USB structures and enumerations used on Windows Driver Model (WDM) platforms.
#pragma warning(disable: 4200)
//warning C4200: nonstandard extension used : zero-sized array in struct/union
#include <UsbIoCtl.h> //Windows Platform DDK
#pragma warning(default: 4200)
#include "KSysPnP.h" //SYMBOLICLINK_PREFIX

#ifndef USB_ROOTHUBNAME
  /*
    Note: Microsoft Windows specific (Win32).
   */
  #define USB_ROOTHUBNAME _T("ROOT_HUB")
#endif

//-----------------------------------------------------------------------------
/*Windows registry keys                                                      */

#define WIN_CTRL_USB_VENDOR_VALUE         _T("ProviderName")
#define WIN_CTRL_USB_DESCRIPTION_VALUE    _T("DriverDesc")
#define WIN_CTRL_USB_DRIVERDATE_VALUE     _T("DriverDate")
#define WIN_CTRL_USB_DRIVERVERSION_VALUE  _T("DriverVersion")
#define WIN_CTRL_USB_DEVICEID_VALUE       _T("MatchingDeviceId")
#define WIN_CTRL_USB_CONTROLER_VALUE      _T("Controller")

/*USB controler registry hive name.
  Note: Microsoft Windows9x/Me specific (Win9x).
 */
#define WIN9x_CTRL_USB_KEY  _T("SYSTEM\\CurrentControlSet\\Services\\Class\\USB")
/*USB controler registry hive name.
  Note: Microsoft Windows NT, 2000, XP specific (WinNT), (Win2k), (WinXP).
 */
#define WINNT_CTRL_USB_KEY  _T("SYSTEM\\CurrentControlSet\\Control\\Class\\{36FC9E60-C465-11CF-8056-444553540000}")

///////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" LPTSTR StrIStr(LPCTSTR szSource, LPCTSTR szToken);

//-----------------------------------------------------------------------------
/*Validates if given hardware ID is an USB root hub ID.
  A hardware ID is a vendor-defined identification string that Setup uses 
  to match a device to an INF file. In most cases, a device has associated with
  it a list of hardware IDs.
  A hardware ID has one of the following generic formats:
     <enumerator>\<enumerator-specific-device-ID>
        (i.e. USB\ROOT_HUB&VID8086&PID24D4&REV0002)
     <generic-device-ID> (i.e. PNP0F06)


  Returns true if hardware ID belong to ab USB root hub.
 */
inline bool IsRootHub(const TCHAR* szUsbDriverKeyName //[in] hardware IDs for a device
                     )
{
if ((szUsbDriverKeyName != NULL) && (szUsbDriverKeyName[0] != '\0'))
  {
  return (StrIStr(szUsbDriverKeyName, USB_ROOTHUBNAME) != NULL);
  }
return false;
}

///////////////////////////////////////////////////////////////////////////////
/*Template class used to obtain a symbolic link name of the specified USB device.

  To retrieve a handle to the device, use CreateFile() function with either
  the name of a device or the name of the driver associated with a device.
  Following format is used for the device names:

      \\.\DeviceKeySymbolicName

  Parameters:
    - TUSBKEYNAME the type of output data returned by the operation. The type
      depends on the value of the TUSBIOCTLID parameter.
    - TUSBIOCTLID the control code for the operation. This value identifies
      the specific operation to be performed and the type of device on which
      to perform it.

  See also: <UsbIoCtl.h>, USB_HCD_DRIVERKEY_NAME, IOCTL_GET_HCD_DRIVERKEY_NAME,
  USB_ROOT_HUB_NAME, IOCTL_USB_GET_ROOT_HUB_NAME,
  USB_HUB_NAME, USB_NODE_CONNECTION_DRIVERKEY_NAME, USB_NODE_CONNECTION_NAME,
  USB host controller FDO.
 */
template<class TUSBKEYNAME, const DWORD TUSBIOCTLID>
class TUsbSymbolicName
{
public:
  TUsbSymbolicName();
  TUsbSymbolicName(HANDLE hDevice);
  virtual ~TUsbSymbolicName();
public:
  bool IsValid() const;
  LPCWSTR GetName();
  void Create(HANDLE hDevice, TUSBKEYNAME& usbOutput);

private:
  TUSBKEYNAME* m_pData;   //device symbolic name data structure, padded with
                          //device name prefix
  LPWSTR m_pSymbolicName; //formatted device symbolic name
};

//-----------------------------------------------------------------------------
/*Default constructor
 */
template<class TUSBKEYNAME, const DWORD TUSBIOCTLID>
TUsbSymbolicName<TUSBKEYNAME, TUSBIOCTLID>::TUsbSymbolicName() : 
  m_pData(NULL), m_pSymbolicName(NULL)
{
}

/*Sends an I/O control request for the symbolic name directly to the specified
  USB device driver. If the operation fails, symbolic name is NULL. To get
  extended error information, call GetLastError().
 */
template<class TUSBKEYNAME, const DWORD TUSBIOCTLID>
TUsbSymbolicName<TUSBKEYNAME, TUSBIOCTLID>::TUsbSymbolicName(HANDLE hDevice //[in]
                 //handle to the device on which the operation is to be performed.
                 ) : m_pData(NULL), m_pSymbolicName(NULL)
{
TUSBKEYNAME usbTemp;
Create(hDevice, usbTemp);
}

//-----------------------------------------------------------------------------
/*Sends an I/O control request for the symbolic name directly to the specified
  USB device driver. If the operation fails, symbolic name is NULL. To get
  extended error information, call GetLastError().
  Use this method if the I/O control requires certain parameters to be set
  before ther request is made.

  Example:
    ...
    USB_NODE_CONNECTION_NAME usbNodeName;
    usbNodeName.ConnectionIndex = 1;  //Usb port number
    TUsbSymbolicName<USB_NODE_CONNECTION_NAME,
                      IOCTL_USB_GET_NODE_CONNECTION_NAME> usbHubName;
    usbHubName.Create(hHub, usbNodeName);
    if (usbHubName.IsValid())
      TRACE1(_T("Hub: %ws\n"), usbHubName.GetName());
    else
      TRACE1(_T("Failed! Error 0x%0.8X.\n"), GetLastError());

 */
template<class TUSBKEYNAME, const DWORD TUSBIOCTLID>
void TUsbSymbolicName<TUSBKEYNAME, TUSBIOCTLID>::Create(HANDLE hDevice, //[in]
                //handle to the device on which the operation is to be performed.
                                       TUSBKEYNAME& usbInput //[in] data 
                //returned by the operation. The input type depends on the value of 
                //the TUSBIOCTLID parameter.
                 )
{
//Disable warning C4127: conditional expression in ASSERT is constant
#pragma warning (disable: 4127)
  ASSERT(hDevice != INVALID_HANDLE_VALUE);
#pragma warning (default: 4127)

if (m_pData != NULL)
  {
  //Clean the buffer from any residual values thus allowing multiple calls
  //and error validation
  delete [] m_pData;
  m_pData = NULL;
  }

if (hDevice != INVALID_HANDLE_VALUE)
  {
  DWORD nBytesReturned;
  /*Send a control code directly to a specified device driver, causing
    the corresponding device to perform the corresponding operation.
    If the operation fails or is pending, the return value is FALSE.
   */
  if (DeviceIoControl(hDevice, //handle to the device
                      TUSBIOCTLID, //control code for the operation
                      &usbInput, //data required to perform the operation
                      sizeof(usbInput),//size of the input data, in bytes
                      &usbInput, //data returned by the operation
                      sizeof(usbInput), //size of the buffer reserved 
                                         //for output data, in bytes
                      &nBytesReturned, //number of bytes actually returned
                      NULL) == TRUE)
    {
    /*Returned data length is sum of the length of the wide character symbolic
      link name and the length of unknown data preceding the name. When the
      preceding data are not required, it could be overwritten with symbolic
      name prefix in order to obtain proper device name. Because it is not
      known beforehand how much padding is required, total length is increased
      for the size of prefix, allowing a couple bytes to be wasted.
      */
    m_pData = (TUSBKEYNAME*) new BYTE[usbInput.ActualLength + 
                                      SYMBOLICLINK_PREFIX_LEN];
    if (m_pData != NULL)
      {
      if (DeviceIoControl(hDevice, //handle to the device
                          TUSBIOCTLID, //control code for the operation
                          &usbInput, //data
                            //required to perform the operation
                          usbInput.ActualLength,//size of the input data in bytes
                          (LPBYTE)m_pData + SYMBOLICLINK_PREFIX_LEN, //data
                           //returned by the operation, offset for the padding
                          usbInput.ActualLength,
                          &nBytesReturned,
                          NULL) != TRUE)
        {
        //Disable warning C4127: conditional expression in ASSERT is constant
        #pragma warning (disable: 4127)
          ASSERT(false); //Failed to obtain symolic link name;
        #pragma warning (default: 4127)
        //To get extended error information, call GetLastError().
        TRACE2(_T("      Failed device I/O request #%d! Error# 0x%0.8X.\n"),
                TUSBIOCTLID, GetLastError());
        delete [] m_pData;
        m_pData = NULL;
        }
      }
    }
  #ifdef _DEBUG
  else
    {
    TRACE2(_T("      IOCTL %d failed to get required data size! Error# 0x%0.8X.\n"), 
            TUSBIOCTLID, GetLastError());
    }
  #endif

  }
}

#if 0
/*Obtains Unicode symbolic link for the downstream USB hub that is attached to
  the port specified by usbOutput.ConnectionIndex.  or
  If there is no attached device, the attached device does not have a symbolic
  link or if the device is not a hub, the resulting device data will contain
  empty string.

  Note: USB_NODE_CONNECTION_NAME partial specialization.

  Example:
    ...
    USB_NODE_CONNECTION_NAME usbNodeName;
    usbNodeName.ConnectionIndex = 1;  //Usb port number
    TUsbSymbolicName<USB_NODE_CONNECTION_NAME,
                      IOCTL_USB_GET_NODE_CONNECTION_NAME> usbHubName;
    usbHubName.Create(hHub, usbNodeName);
    if (usbHubName.IsValid())
      TRACE1(_T("Hub: %ws\n"), usbHubName.GetName());
    else
      TRACE1(_T("Failed! Error 0x%0.8X.\n"), GetLastError());

  See also: USB_NODE_CONNECTION_NAME, IOCTL_USB_GET_NODE_CONNECTION_NAME 
 */
template<> inline
void TUsbSymbolicName<USB_NODE_CONNECTION_NAME, 
                      IOCTL_USB_GET_NODE_CONNECTION_NAME>::Create(HANDLE hDevice, //[in]
                //handle to the device on which the operation is to be performed.
                                       USB_NODE_CONNECTION_NAME& usbInput //[in] data 
                //required by the operation.
                 )
{
//Disable warning C4127: conditional expression in ASSERT is constant
#pragma warning (disable: 4127)
  ASSERT(hDevice != INVALID_HANDLE_VALUE);
#pragma warning (default: 4127)

if (m_pData != NULL)
  {
  //Clean the buffer from any residual values thus allowing multiple calls
  //and error validation
  delete [] m_pData;
  m_pData = NULL;
  }

if (hDevice != INVALID_HANDLE_VALUE)
  {
  DWORD nBytesReturned;
  /*Send a control code directly to a specified device driver, causing
    the corresponding device to perform the corresponding operation.
    If the operation fails or is pending, the return value is FALSE.
   */
  if (DeviceIoControl(hDevice,           //handle to the device
                      IOCTL_USB_GET_NODE_CONNECTION_NAME, //control code for
                                                          //the operation
                      &usbInput,        //data required to perform the operation
                      sizeof(usbInput), //size of the input data, in bytes
                      &usbInput,        //data returned by the operation
                      sizeof(usbInput), //size of the buffer reserved for
                                        //output data, in bytes
                      &nBytesReturned,  //number of bytes actually returned
                      NULL) == TRUE)
    {
    /*Returned data length is sum of the length of the wide character symbolic
      link name and the length of unknown data preceding the name. When the
      preceding data are not required, it could be overwritten with symbolic
      name prefix in order to obtain proper device name. Because it is not
      known beforehand how much padding is required, total length is increased
      for the size of prefix, allowing a couple bytes to be wasted.
      */
    m_pData = (USB_NODE_CONNECTION_NAME*) new BYTE[usbInput.ActualLength +
                                                   SYMBOLICLINK_PREFIX_LEN];
    if (m_pData != NULL)
      {
      USB_NODE_CONNECTION_NAME& usbHubName = 
         *(USB_NODE_CONNECTION_NAME*)((LPBYTE)m_pData + SYMBOLICLINK_PREFIX_LEN);
      //usbHubName.ConnectionIndex = usbOutput.ConnectionIndex; //Set USB port index  

      if (DeviceIoControl(hDevice, //handle to the device
                          IOCTL_USB_GET_NODE_CONNECTION_NAME, //control code for
                                                              //the operation
                          &usbInput, //data required to perform the operation
                          usbInput.ActualLength,//size of the input data, in bytes
                          &usbHubName, //data
                           //returned by the operation, offset for the padding
                          usbInput.ActualLength,
                          &nBytesReturned,
                          NULL) != TRUE)
        {
        //Disable warning C4127: conditional expression in ASSERT is constant
        #pragma warning (disable: 4127)
          ASSERT(false); //Failed to obtain symolic link name;
        #pragma warning (default: 4127)
        //To get extended error information, call GetLastError().
        TRACE1(_T("      Failed IOCTL_USB_GET_NODE_CONNECTION_NAME request! Error# 0x%0.8X.\n"), 
                GetLastError());
        delete [] m_pData;
        m_pData = NULL;
        }
      }
    }
  #ifdef _DEBUG
  else
    {
    TRACE1(_T("      IOCTL_USB_GET_NODE_CONNECTION_NAME failed to get required data size! Error# 0x%0.8X.\n"), 
            GetLastError());
    }
  #endif
  }
}
#endif
//-----------------------------------------------------------------------------
/*
 */
template<class TUSBKEYNAME, const DWORD TUSBIOCTLID>
TUsbSymbolicName<TUSBKEYNAME, TUSBIOCTLID>::~TUsbSymbolicName()
{
if (IsValid())
  delete[] m_pData;
}

//-----------------------------------------------------------------------------
/*Verifies if the symbolic name of the USB device is valid.
  To get extended error information, call GetLastError().

  Returns true if the symbolic name is obtained successfuly, otherwise returns
  false.
 */
template<class TUSBKEYNAME, const DWORD TUSBIOCTLID>
bool TUsbSymbolicName<TUSBKEYNAME, TUSBIOCTLID>::IsValid() const
{
return (m_pData != NULL);
}

//-----------------------------------------------------------------------------
/*Creates a device name from previously obtained device symbolic link.
  Following format is used for the device names:

      \\.\DeviceKeySymbolicName

  Returns pointer formatted device name or NULL in case of failure.

  Example:
      ...
      LPWSTR szDeviceDriverPath = 
      L"\\?\pci#ven_8086&dev_2658&subsys_01811028&rev_03#3&172e68dd&0&e8#{3abf6f2d-71c4-462a-8a92-1e6861e6af27}";
      HANDLE hUsbDevice = CreateFile(szDeviceDriverPath, 
                                     GENERIC_WRITE, 
                                     FILE_SHARE_WRITE, 
                                     NULL, 
                                     OPEN_EXISTING, 
                                     0, 
                                     NULL);
      if (hUsbDevice != INVALID_HANDLE_VALUE)
        {
        TUsbSymbolicName<USB_ROOT_HUB_NAME, 
                         IOCTL_USB_GET_ROOT_HUB_NAME> usbDeviceName(hUsbDevice);
        if (usbDeviceName.IsValid()) //Check GetLastError() in case of failure.
          {
          LPCWSTR usbDevicePath = usbRootHubName.GetName();
          ...
          }
        }
 */
template<class TUSBKEYNAME, const DWORD TUSBIOCTLID>
LPCWSTR TUsbSymbolicName<TUSBKEYNAME, TUSBIOCTLID>::GetName()
{
if (IsValid())
  {
  if (m_pSymbolicName == NULL)
    {
    /*Note: this magic requires that of ActualLength member of USB I/O data
      immediately precedes string with device name.
      Adddres of the buffer with result would be: address of the ActualLength
      member + sizeof(ActualLength) - prefix length.

          +---- padding (SYMBOLICLINK_PREFIX_LEN)
          |      +--------- other data members
      |01234567|...|0123| device name |
                      |       +-  device name (wide characters)
                      +---- ActualLength (uint32) and 
     */
    m_pSymbolicName = (LPWSTR)((LPBYTE)( &( (TUSBKEYNAME*)
      ((LPBYTE)m_pData + SYMBOLICLINK_PREFIX_LEN) )->ActualLength) +
                       sizeof(m_pData->ActualLength) - SYMBOLICLINK_PREFIX_LEN);

    //Disable warning C4127: conditional expression in ASSERT is constant
    #pragma warning (disable: 4127)
      ASSERT(m_pSymbolicName != NULL);
      ASSERT((LPBYTE)m_pSymbolicName > (LPBYTE)m_pData);
    #pragma warning (default: 4127)
    m_pSymbolicName[0] = SYMBOLICLINK_PREFIX[0];
    m_pSymbolicName[1] = SYMBOLICLINK_PREFIX[1];
    m_pSymbolicName[2] = SYMBOLICLINK_PREFIX[2];
    m_pSymbolicName[3] = SYMBOLICLINK_PREFIX[3];
    }
  return m_pSymbolicName;
  }
return NULL;
}

///////////////////////////////////////////////////////////////////////////////
LPCTSTR GetDeviceDesc(LPCTSTR szDriverRegistryName);

///////////////////////////////////////////////////////////////////////////////
/*Handles driver registry key name used for the USB host controller driver.

  Note: Microsoft Windows specific (Win32).

  See also: IOCTL_GET_HCD_DRIVERKEY_NAME, USB_HCD_DRIVERKEY_NAME
 */
class CUsbDriverKeyName
{
public:
  CUsbDriverKeyName();
  CUsbDriverKeyName(const ULONG lSize);
  CUsbDriverKeyName(const HANDLE hHDC);

  ~CUsbDriverKeyName();
  void SetSize(const ULONG lSize);
  void SetSize(const HANDLE hHDC);
  ULONG GetSize() const;
  bool LoadKeyName(const HANDLE hHDC);
  operator const char*();
  operator const WCHAR*();

public:
  PUSB_HCD_DRIVERKEY_NAME m_pKeyName; //dynamically allocated string
                                      //holding registry key name
protected:
  char* m_szDriverKeyNameA;           //SBCS driver registry key name. The string
                                      //is created after first usage of
                                      //operator const char*()
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Default constructor
 */
inline CUsbDriverKeyName::CUsbDriverKeyName() :
  m_pKeyName(NULL),
  m_szDriverKeyNameA(NULL)
{
}

/*Allocates the space required for the USB driver registry key name.

  See also: IOCTL_GET_HCD_DRIVERKEY_NAME
 */
inline CUsbDriverKeyName::CUsbDriverKeyName(const ULONG lSize //[in] buffer size
                                            //in bytes
                                            ) :
  m_szDriverKeyNameA(NULL)
{
m_pKeyName = (PUSB_HCD_DRIVERKEY_NAME)new char[lSize];
if (m_pKeyName != NULL)
  {
  //Length, in bytes, of the string holding driver registry key name
  m_pKeyName->ActualLength = lSize - sizeof(ULONG);
  if (m_pKeyName->ActualLength >= sizeof(WCHAR))
    m_pKeyName->DriverKeyName[0] = (WCHAR)0; //zero-terminated Unicode
                                             //driver registry key name
  }
}

/*Retrieves the registry driver key name from the USB host controller driver.
  In case of an error, obtain error code by calling GetLastError().

  See also: IOCTL_GET_HCD_DRIVERKEY_NAME
 */
inline CUsbDriverKeyName::CUsbDriverKeyName(const HANDLE hHcd //[in] handle
                                          //to USB Host Controller Driver (HCD)
                                            ) :
  m_pKeyName(NULL),
  m_szDriverKeyNameA(NULL)
{
SetSize(hHcd);
}

inline CUsbDriverKeyName::~CUsbDriverKeyName()
{
if (m_pKeyName != NULL)
  delete[] m_pKeyName;
if (m_szDriverKeyNameA != NULL)
  delete[] m_szDriverKeyNameA;
}

//-----------------------------------------------------------------------------
/*Gets the size of the buffer holding registry key name.

  Returns: the size in bytes of the holding buffer.
 */
inline ULONG CUsbDriverKeyName::GetSize() const
{
if (m_pKeyName == NULL)
  return 0;

/*The size of the whole buffer, which is specified in
  the Parameters.DeviceIoControl.InputBufferLength member,
  must be >= sizeof(USB_HCD_DRIVERKEY_NAME).
 */

//Return length, in bytes, of the string holding driver registry key name
//and size of the length container.
return (m_pKeyName->ActualLength + sizeof(ULONG));
}

//-----------------------------------------------------------------------------
/*Sets the new size of the buffer holding registry key name. The method
  does not preserve the data previously contained by the old buffer.
  The allocated space is reused if the new size is smaller that old value.
 */
inline void CUsbDriverKeyName::SetSize(const ULONG lSize //[in] buffer size
                                            //in bytes
                                      )
{
if (m_pKeyName != NULL)
  {
  if (lSize > GetSize())
    {
    delete[] m_pKeyName;
    m_pKeyName = NULL;
    }
  }

if (m_pKeyName == NULL)
  m_pKeyName = (PUSB_HCD_DRIVERKEY_NAME)new char[lSize];

if (m_pKeyName != NULL)
  {
  //Length, in bytes, of the string holding driver registry key name
  m_pKeyName->ActualLength = lSize - sizeof(ULONG);
  if (m_pKeyName->ActualLength >= sizeof(WCHAR))
    m_pKeyName->DriverKeyName[0] = (WCHAR)0; //zero-terminated Unicode
                                             //driver registry key name
  }
}

//-----------------------------------------------------------------------------
/*Sets the size of the buffer holding registry key name. The required size is
  obtained from the USB Host Controller Driver.
  The method does not preserve the data previously contained by the old buffer.
  The allocated space is reused if the new size is smaller that old value.

  See also: IOCTL_GET_HCD_DRIVERKEY_NAME
 */
inline void CUsbDriverKeyName::SetSize(const HANDLE hHcd //[in] handle
                                          //to USB Host Controller Driver (HCD)
                                      )
{
//Disable warning C4127: conditional expression in ASSERT is constant
#pragma warning (disable: 4127)
  ASSERT(hHcd != INVALID_HANDLE_VALUE);
#pragma warning (default: 4127)

if (hHcd != INVALID_HANDLE_VALUE)
  {
  //Get required buffer size
#ifdef TODO_TEMPLATE
  TUsbSymbolicName<USB_HCD_DRIVERKEY_NAME,
                   IOCTL_GET_HCD_DRIVERKEY_NAME> usbHcdDriverKeyName(hHcd);
#else

  USB_HCD_DRIVERKEY_NAME sUnicodeName; //Unicode driver registry key
  DWORD dwBytesReturned;
  bool bRes = (DeviceIoControl(hHcd, //handle to the device
                            IOCTL_GET_HCD_DRIVERKEY_NAME, //control code for
                                                          //the operation
                            &sUnicodeName, //input buffer; NULL is not allowed
                            sizeof(sUnicodeName), //size of input buffer
                            &sUnicodeName, //output buffer; NULL is not allowed
                            sizeof(sUnicodeName), //size of output buffer
                            &dwBytesReturned, //size of the data stored in
                                              //the output buffer
                            NULL //lpOverlapped is ignored
                            ) == TRUE);
  if (bRes)
    SetSize(sUnicodeName.ActualLength);
  else
    {
    DWORD dwError = GetLastError();
    TRACE1(_T("DeviceIoControl(IOCTL_GET_HCD_DRIVERKEY_NAME) failed #0x%X\n"),
           dwError);
    if (dwError == ERROR_INSUFFICIENT_BUFFER) //error code 122
      //The data area passed to a system call is too small.
      TRACE(_T("The data area passed to a system call is too small."));
    //TODO: report the error! (throw exception) D.K.
    }
#endif //TODO
  }
}

//-----------------------------------------------------------------------------
/*Retrieves the registry driver key name from the USB host controller driver.

  Returns: true if successful. In case of an error, obtain error code by calling
  GetLastError().

  Example:
      HANDLE hHcd = CreateFileA("\\\\.\\HCD0",
                                GENERIC_WRITE,
                                FILE_SHARE_WRITE,
                                NULL,
                                OPEN_EXISTING,
                                0,
                                NULL);
      if (hHcd != INVALID_HANDLE_VALUE)
        {
        //Retrieve the driver key name in the registry
        //for a USB host controller driver.
        CUsbDriverKeyName usbDriverKeyName(hHcd);
        bool bRes = usbDriverKeyName.LoadKeyName(hHcd);
        CloseHandle(hHcd);
        if (!bRes)
          {
          DWORD dwError = GetLastError();
          //report the error!
          return;
          }
        TRACE1(_T("System name is %ws\n"), (const WCHAR*)usbDriverKeyName);
        }

  See also: IOCTL_GET_HCD_DRIVERKEY_NAME
 */
inline bool CUsbDriverKeyName::LoadKeyName(const HANDLE hHcd //[in] handle
                                          //to USB Host Controller Driver (HCD)
                                          )
{
//Disable warning C4127: conditional expression in ASSERT is constant
#pragma warning (disable: 4127)
  ASSERT(hHcd != NULL);
#pragma warning (default: 4127)

if (hHcd != NULL)
  {
  if ((m_pKeyName == NULL) || (m_pKeyName->ActualLength == 0))
    {
    SetLastError(ERROR_INSUFFICIENT_BUFFER);
    return false;
    }

  DWORD dwBytesReturned = GetSize();
  return (DeviceIoControl(hHcd, //handle to the device
                          IOCTL_GET_HCD_DRIVERKEY_NAME, //control code for
                                                        //the operation
                          m_pKeyName, //input buffer; NULL is not allowed
                          dwBytesReturned, //size of input buffer
                          m_pKeyName, //output buffer; NULL is not allowed
                          dwBytesReturned, //size of output buffer
                          &dwBytesReturned, //size of the data stored in
                                            //the output buffer
                          NULL //lpOverlapped is ignored
                          ) == TRUE);
  }
SetLastError(ERROR_INVALID_TARGET_HANDLE);
return false;
}

//-----------------------------------------------------------------------------
/*Get USB host controller driver registry key name or NULL pointer.
 */
inline CUsbDriverKeyName::operator const char*()
{
if (m_pKeyName != NULL)
  {
  extern LPSTR WtoA(LPWSTR szWideCharStr);
  if (m_szDriverKeyNameA != NULL)
    delete[] m_szDriverKeyNameA;
  m_szDriverKeyNameA = WtoA(m_pKeyName->DriverKeyName);
  return m_szDriverKeyNameA;
  }
return NULL;
}

/*Get USB host controller driver registry key name or NULL pointer.
 */
inline CUsbDriverKeyName::operator const WCHAR*()
{
if (m_pKeyName != NULL)
  {
  return (m_pKeyName->DriverKeyName);
  }
return (WCHAR*)NULL;
}

///////////////////////////////////////////////////////////////////////////////
#endif //__cplusplus

#endif //_WIN32
///////////////////////////////////////////////////////////////////////////////
#endif  //_KWINUSB_H_
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         23/08/2007 11:43:36 AMDarko Kolakovic
 * $
 *****************************************************************************/
