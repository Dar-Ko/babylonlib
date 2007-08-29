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
#endif

#ifdef _MSC_VER
  //Microsoft Visual C/C++ compiler
  #pragma include_alias( "stdint.h", "KType32.h" )
  #include "stdint.h" //ISO C99 type definitions
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

  bool Find(const uint16_t wVendorId, const uint16_t wProductId);
  // configuration functions
  ///int SetDevice(char *UsbDevice);
  ///int GetDevice(char *UsbDevice);

  // IO functions
  ///int Open();
  ///int Close();
  ///int Write(void *Buffer, int Size=MAX_USB_HID_SIZE);
  ///int Read(void *Buffer, int Size=MAX_USB_HID_SIZE);
  ///int ReadWrite(void *Buffer, int Size=MAX_USB_HID_SIZE);

  // initialize the function to intercept SIGIO
  //int SetReadSignal(ReadSignalType iRSFunc);

protected:
  HANDLE m_hHid; //handle to requested device of the HID class
  // usb file descriptor;
#ifdef WIN32
  ///void *StructParamPtr;
  ///
  ///void GetDeviceCapabilities();
#else
  ///int fd;
  ///bool IsOpened;
#endif

};
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
#endif  //_KUSBHID_H_
/*****************************************************************************
 * $Log: $
 *****************************************************************************/
