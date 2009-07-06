/*$Workfile: KUsbHub.h$: header file
  $Revision: 1.3 $ $Date: 2009/07/06 21:38:26 $
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

///////////////////////////////////////////////////////////////////////////////
/*
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
  PCI -+                                 +-- Hub    ... --- Device
       |
       +-USB Host Controller --- Device
       |   (root hub)
       |         
       .
       .
       .


 There are three types of USB components:

    *       Host controller Also known as the root, the root tier, or the root hub, the host controller can be built into the motherboard of the computer or installed as an add-in CardBus or PCI card in the computer to gain additional ports and bandwidth. The host controller controls all traffic on the bus and also functions as a hub.
    *       Hub Provides multiple ports, for attaching devices to the USB bus. Hubs are also responsible for detecting devices that are plugged in or unplugged, and for providing power for attached devices. Hubs are either bus-powered, drawing power directly from the USB bus, or self-powered, drawing power from an external AC adapter. Bus-powered hubs are capable of providing 100 milliamperes (mA) of power per port for attached devices, and they can provide a maximum of four ports for devices to be plugged into. Self-powered hubs, on the other hand, typically provide 500 mA of power per port, and they can provide more than four ports. Hubs can be stand-alone devices, or they can be integrated into other devices such as keyboards and monitors.
    *       Device A USB device, which is attached to the bus through a port. A USB device can be any kind of peripheral device, such as a keyboard, mouse, game controller, printer, and so forth. Certain USB input devices such as keyboards and mice require only 100 mA of power to function. Thus, they can be plugged into both bus-powered and self-powered hubs, in addition to being plugged directly into a root port. Other devices such as printers, scanners, storage devices, and video-conferencing cameras might require 500 mA of power to function. These kinds of devices can only be plugged into root ports or self-powered hubs. If the device requires more than 500 mA of power, it includes a wall plug provided by the vendor for power.

  See also:
 */
class CUsbDeviceTree
{
public:
  void GetHdc();
};

///////////////////////////////////////////////////////////////////////////////
/*Handles the USB hub.
  A USB hub is a device that allows many USB devices to be connected to a
  single USB port on the host computer or another hub.

  See also:
 */
class CUsbHub
{
public:
  CUsbHub();

  ~CUsbHub();
  uint_fast32_t Enumerate();

};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Default constructor
 */
inline CUsbHub::CUsbHub()
{
}

inline CUsbHub::~CUsbHub()
{
}

///////////////////////////////////////////////////////////////////////////////
#endif //__cplusplus

///////////////////////////////////////////////////////////////////////////////
#endif  //_KUSBHUB_H_
/*****************************************************************************
 * $Log: KUsbHub.h,v $
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
