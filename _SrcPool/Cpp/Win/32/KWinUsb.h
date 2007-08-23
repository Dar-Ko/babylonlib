/*$Workfile: S:\_SrcPool\Cpp\Win\32\KWinUsb.h$: header file
  $Revision: 1$ $Date: 23/08/2007 11:43:36 AM$
  $Author: Darko Kolakovic$

  Constants related to Windows platform version
  Note: Microsoft Windows specific (Win). 
  Copyright: CommonSoft Inc
  2004-03-10 Darko Kolakovic
 */
// Group=Windows

#ifndef _KWINUSB_H_
    //$Workfile: S:\_SrcPool\Cpp\Win\32\KWinUsb.h$ sentry
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
#include <usbioctl.h> //Windows Platform DDK
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
    enumerate devices on pre-Windows XP SP1-based computers".
  */
  #define SYMBOLICLINK_HDC "\\\\.\\HCD%d"
#endif

///////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus

///////////////////////////////////////////////////////////////////////////////
/*Handles driver registry key name used for the USB host controller driver.
 */
class CUsbDriverKeyName: public USB_HCD_DRIVERKEY_NAME
{
public:
  CUsbDriverKeyName();
  CUsbDriverKeyName(ULONG lSize);
  ~CUsbDriverKeyName();
  void SetSize(ULONG lSize);
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Default constructor
 */
inline CUsbDriverKeyName::CUsbDriverKeyName()
{
ActualLength = sizeof(DriverKeyName); //length, in bytes, of the string holding 
                                      //driver registry key name
if (ActualLength <= sizeof(WCHAR))
  DriverKeyName[0] = (WCHAR)0; //zero-terminated Unicode driver registry key name
}

#endif //__cplusplus

#endif //_WIN32
///////////////////////////////////////////////////////////////////////////////
#endif  //_KWINUSB_H_
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         23/08/2007 11:43:36 AMDarko Kolakovic 
 * $
 *****************************************************************************/
