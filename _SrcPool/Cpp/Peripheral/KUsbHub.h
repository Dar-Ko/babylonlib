/*$Workfile: KUsbHub.h$: header file
  $Revision: 1.9 $ $Date: 2009/07/20 21:51:12 $
  $Author: ddarko $

  Universal Serial Bus (USB) Host Controller
  Copyright: CommonSoft Inc
  2004-03-09 Darko Kolakovic
 */

#ifndef _KUSBHUB_H_
    //$Workfile: KUsbHub.h$ sentry
  #define _KUSBHUB_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
#ifdef _USE_STL
  #include <string>  //CString base class
#endif
#include "KString.h" //CString class replacement
#include "UsbIoCtl.h"//USB_CONNECTION_STATUS enum
#include "KUsb.h"    //CUsbId class

LPCTSTR GetUsbStatus(const USB_CONNECTION_STATUS& eStatus);

///////////////////////////////////////////////////////////////////////////////
/*USB Device Information container.
  A USB device is attached to the hub a port. 
  A USB device can be any kind of peripheral device, such as a keyboard, mouse,
  game controller, printer, USB hub and so forth. 
 */
class CUsbDevice : public CUsbId
{
public:
  CUsbDevice();
  ~CUsbDevice();
public:
  bool GetStringDescriptor(HANDLE hUsbHub,
                           const unsigned int nPortId,
                           const unsigned int nStringId,
                           LANGID nLangId,
                           CString& strResult);
  bool CUsbDevice::HasStringDescriptor( 
        const PUSB_DEVICE_DESCRIPTOR pusbDevDescriptor,
        const PUSB_CONFIGURATION_DESCRIPTOR pusbConfigDescriptor
        );


public:
  CString m_strDevice;       //USB device path
  CString m_strDescription;  //description of the device
  bool m_bHub;  //device is a hub (TODO: check if class descriptor is sufficient)
  USB_CONNECTION_STATUS m_eStatus; //device status
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Default constructor
 */
inline CUsbDevice::CUsbDevice() :
    m_eStatus(NoDeviceConnected)
{
}

inline CUsbDevice::~CUsbDevice()
{
}

#include "KArrayPtr.h" //CArrayPtr template
///////////////////////////////////////////////////////////////////////////////
/*
 */
class CUsbDeviceArray : public  CArrayPtr<CUsbDevice>
{
public:
  CUsbDeviceArray();
  ~CUsbDeviceArray();
};
///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*
 */
inline CUsbDeviceArray::CUsbDeviceArray()
{
}

inline CUsbDeviceArray::~CUsbDeviceArray()
{
}

///////////////////////////////////////////////////////////////////////////////
/*Handles the USB hub.
  A USB hub is a device that allows many USB devices to be connected to a
  single USB port on the host computer or another hub.

  Hub Provides multiple ports, for attaching devices to the USB bus.
  Hubs are also responsible for detecting devices that are plugged in or 
  unplugged and for providing power for attached devices. 
  Hubs are either bus-powered, drawing power directly from the USB bus or 
  self-powered, drawing power from an external power supply. 
  Bus-powered hubs are capable of providing 100 mA
  per port for attached devices and they can provide a maximum of four ports
  for devices to be plugged into.
  Self-powered hubs, on the other hand, typically provide 500 mA per port
  and they can provide more than four ports.
  Hubs can be stand-alone devices or they can be integrated into other devices
  such as keyboards and monitors.

  See also: CUsbDeviceTree, CUsbHostController, CUsbDevice
 */
class CUsbHub : public CUsbDevice
{
public:
  CUsbHub();
  CUsbHub(const CUsbDevice& usbSrc);
  ~CUsbHub();
  unsigned int Enumerate(LPCTSTR szDevicePath);

public:
  unsigned int m_nPortCount;     //number of ports on the hub

protected:
  CUsbDeviceArray m_usbNodeList; //hub node connections (ports)
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Default constructor
 */
inline CUsbHub::CUsbHub() :
  m_nPortCount(0)
{
m_bHub = true;
}

inline CUsbHub::CUsbHub(const CUsbDevice& usbSrc) :
  CUsbDevice(usbSrc),
  m_nPortCount(0)
{
m_bHub = true;
}

inline CUsbHub::~CUsbHub()
{
}

///////////////////////////////////////////////////////////////////////////////
/*Universal Serial Bus (USB) host controller (also known as the root, root tier
  or the root hub) controls all traffic on the data bus and also functions as
  a hub. One host controller can control several USB ports.
 */
class CUsbHostController : public CUsbHub
{
public:
  bool GetDeviceInfo(const unsigned int nMemberIndex = 0);

protected:
  bool GetRootHub(LPCTSTR szDevicePath, CString& strRootHubPath);
};

#include "STL/KArrayStl.h" //CArray template
///////////////////////////////////////////////////////////////////////////////
/*This class browses all USB host controllers USB hubs and USB devices
  attached on the system.

  USB uses a tiered topology so that you can simultaneously attach up to 127 
  devices to the bus. 
  There always exists one hub known as the root hub, which is built into 
  the host controller.
  USB supports up to seven tier levels, including the root tier and five common
  hubs. The lowest tier supports only a single nonhub device.

      Tier level:    1                  2         3      ...       7
            +-USB Host Controller -+- Device
            |   (root hub)         |          +- Device
            |                      +-- Hub ---+- Device
       PCI -+                                 +-- Hub -- ... --- Device
            |
            +-USB Host Controller --- Device
            |   (root hub)
            |         
            .
            .
            .

  There are three types of USB components: host controller, hub and device.
  
  See also: CUsbHostController, CUsbHub, CUsbDevice
 */
class CUsbDeviceTree
{
public:
  int Enumerate();
//protected:

  CArray<CUsbHostController> m_usbRootList;
};

///////////////////////////////////////////////////////////////////////////////
#endif //__cplusplus

///////////////////////////////////////////////////////////////////////////////
#endif  //_KUSBHUB_H_
/*****************************************************************************
 * $Log: KUsbHub.h,v $
 * Revision 1.9  2009/07/20 21:51:12  ddarko
 * *** empty log message ***
 *
 * Revision 1.8  2009/07/16 21:50:23  ddarko
 * CUsbDeviceArray
 *
 * Revision 1.7  2009/07/14 21:36:24  ddarko
 * Code cleanup
 *
 * Revision 1.6  2009/07/12 21:10:26  ddarko
 * Comments
 *
 * Revision 1.5  2009/07/10 21:34:31  ddarko
 * Renamed methods
 *
 * Revision 1.4  2009/07/08 21:51:07  ddarko
 * CUsbHostController
 *
 * Revision 1.3  2009/07/06 21:38:26  ddarko
 * Comment
 *
 * Revision 1.2  2009/07/02 21:44:13  ddarko
 * Excluded some Windows specifics
 *
 * Revision 1.1  2009/07/02 20:31:15  ddarko
 * Moved from platform specific directory
 *
 *****************************************************************************/
