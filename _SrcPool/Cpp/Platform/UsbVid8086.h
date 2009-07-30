/*$Workfile: UsbVid8086.h$: header file
  $Revision: 1$ $Date: 22/08/2007 10:51:35 AM$
  $Author: Darko Kolakovic$

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2007-08-17 Darko Kolakovic
 */

/* Group=USB ID                                                              */

#ifndef _USBVID8086_H_
  //$Workfile: UsbVid8086.h$ sentry
  #define _USBVID8086_H_

/*32902.	USB device vendor identification (VID) number	Intel Corporation	http://www.intel.com/

  See also: usb-if.tsv, USB Implementers Forum, Inc (USB-IF) at http://www.usb.org
 */
#define USBVID_INTEL 0x8086
#define USBVID_8086 _T("Intel Corporation") //VID 32902 Vendor name

#define USBPID_ANYPOINTWIRELESS16  0x0001 //AnyPoint Home Network 1.6 Mbps Wireless Adapter
#define USBPID_PAP3000             0x0100 //Personal Audio Player 3000
#define USBPID_PAP3001             0x0101 //Personal Audio Player 3000 (FixMe!)
#define USBPID_CAMEASYPC           0x0110 //Easy PC Camera
#define USBPID_CS120               0x0120 //PC Camera CS120
#define USBPID_ANYPOINTWIRELESS11  0x0200 //AnyPoint Wireless II Network 11Mbps Adapter
#define USBPID_CAMPROVIDEO         0x0431 //Intel Pro Video PC Camera
#define USBPID_DIGIMOVIE           0x0510 //Digital Movie Creator
#define USBPID_CAMPOCKETPC         0x0630 //Pocket PC Camera
#define USBPID_CS780               0x0780 //CS780 Microphone Input
#define USBPID_BLOBBOOT            0x07D3 //BLOB boot loader firmware TODO: what is this? D.K.
#define USBPID_KBDCHERRYMIN        0x0DAD //Cherry MiniatureCard Keyboard
#define USBPID_ANYPOINTPHONELINE10 0x1010 //AnyPoint Home Network 10 Mbps Phoneline Adapter
#define USBPID_BTERICSSONP4A       0x110A //Bluetooth Controller Ericsson P4A
#define USBPID_BTINTELCSR          0x110B //Bluetooth Controller Intel/CSR
#define USBPID_LANWIRELESSPRO      0x1110 //PRO/Wireless LAN Module
#define USBPID_802_11_2011B        0x1111 //PRO/Wireless 2011B 802.11b Adapter
#define USBPID_HOLLISTERMOB        0x1134 //Hollister Mobile Monitor
#define USBPID_RWPROTOTYPE         0x1234 //Prototype Reader/Writer
#define USBPID_USBHDC1             0x24D2 //82801EB 1st USB Universal Host Controller on the board
#define USBPID_USBHDC2             0x24D4 //82801EB 2nd USB Universal Host Controller on the board
#define USBPID_USBHDC3             0x24DE //82801EB 3rd USB Universal Host Controller on the board
#define USBPID_USBHDC4             0x24DD //82801EB 4th Enhanced USB2 Universal Host Controller on the board
#define USBPID_DSL3220WAN          0x3100 //PRO/DSL 3220 Modem WAN
#define USBPID_DSL3220             0x3101 //PRO/DSL 3220 Modem
#define USBPID_ANYPOINT3240WAN     0x3240 //AnyPoint 3240 Modem WAN
#define USBPID_ANYPOINT3240        0x3241 //AnyPoint 3240 Modem
#define USBPID_MINCARDSLOT         0x8602 //Miniature Card Slot
#define USBPID_HUB8x930H           0x9303 //Intel 8x930Hx Hub
#define USBPID_82930               0x9890 //82930 Test Board
#define USBPID_SCMCARDRW           0xBEEF //SCM Miniature Card Reader/Writer
#define USBPID_HIDSTATION          0xC013 //Wireless HID Station
#define USBPID_XSCALEPXA27X        0xF001 //XScale PXA27x Bulverde flash
///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID8086_H_
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         22/08/2007 10:51:35 AMDarko Kolakovic
 * $
 *****************************************************************************/
