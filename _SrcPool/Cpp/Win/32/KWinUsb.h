/*$Workfile: KWinUsb.h$: header file
  $Revision: 4$ $Date: 2007-08-24 18:15:44$
  $Author: Darko Kolakovic$

  Constants related to Windows platform version
  Note: Microsoft Windows specific (Win).
  Copyright: CommonSoft Inc
  2004-03-10 Darko Kolakovic
 */
// Group=Windows

#ifndef _KWINUSB_H_
    //$Workfile: KWinUsb.h$ sentry
  #define _KWINUSB_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifdef _WIN32 //Windows 32-bit platform

#ifndef _USE_ATL
  #include <windows.h>
#endif

///////////////////////////////////////////////////////////////////////////////
//USB structures and enumerations used on Windows Driver Model (WDM) platforms.
#pragma warning(disable: 4200)
//warning C4200: nonstandard extension used : zero-sized array in struct/union
#include <usbioctl.h> //Windows Platform DDK, using pre-Win2k functions
#pragma warning(default: 4200)

#ifndef SYMBOLICLINK_HDC
  /*Symbolic name for Host Controller Driver (HCD) modules have following
    form:
        \\.\HCDn
        where n (0,...,k) is module instance number in the driver's stack.

    Note: USB driver uses two different stacks for USB 1.1 and USB 2.0 host
    controllers.
    Note: Microsoft Windows specific (Win32).

    See also: MSDN KB838100,  "The USBView.exe sample program does not
    enumerate devices on pre-Windows XP SP1-based computers";
    CreateSymbolicLink().
  */
  #define SYMBOLICLINK_HDC "\\\\.\\HCD%d"
#endif

#ifndef USB_ROOTHUBNAME
  /*
    Note: Microsoft Windows specific (Win32).
   */
  #define USB_ROOTHUBNAME _T("ROOT_HUB")
#endif
///////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus

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
ASSERT(hHcd != NULL);
if (hHcd != NULL)
  {
  //Get required buffer size
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
ASSERT(hHcd != NULL);
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
