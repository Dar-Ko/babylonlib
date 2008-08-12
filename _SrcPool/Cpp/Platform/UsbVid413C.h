/*$Workfile: UsbVid413C.h$: header file
  $Revision: 1$ $Date: 22/08/2007 10:51:35 AM$
  $Author: Darko Kolakovic$

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2007-08-17 Darko Kolakovic
 */

/* Group=USB ID                                                              */

#ifndef _USBVID413C_H_
  //$Workfile: UsbVid413C.h$ sentry
  #define _USBVID413C_H_

/*16700.	USB device vendor identification (VID) number	Dell Computer Corp.	http://www.dell.com

  See also: usb-if.tsv, USB Implementers Forum, Inc (USB-IF) at http://www.usb.org
 */
#define USBVID_DELL 0x413C
#define USBVID_413C _T("Dell Inc") //VID 16700 Vendor name

#define USBPID_DELLKBDH    0x1002  //Keyboard Hub
#define USBPID_SK8125      0x2002  //SK-8125 Keyboard
#define USBPID_SK3106      0x2100  //SK-3106 Keyboard
#define USBPID_DELLSCRD    0x2101  //SmartCard Reader Keyboard
#define USBPID_DRAC4RAC    0x2500  //DRAC4 Remote Access Card
#define USBPID_DELLMOUSEOW 0x3010  //Optical Wheel Mouse
#define USBPID_AXIMX5      0x4001  //Axim X5
#define USBPID_AXIMX3      0x4002  //Axim X3
#define USBPID_AXIMX30     0x4003  //Axim X30
#define USBPID_TRUMOB1180  0x8100  //TrueMobile 1180 802.11b Adapter
#define USBPID_WIRE350BT   0x8103  //Wireless 350 Bluetooth
#define USBPID_DELLHUB     0xA001  //Hub
#define USBPID_DELLHUB1905 0xA700  //Hub (in 1905FP LCD Monitor)

///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID413C_H_
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         22/08/2007 10:51:35 AMDarko Kolakovic
 * $
 *****************************************************************************/
