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

#define USBPID_CAMEASYPC    0x0110  //Easy PC Camera
#define USBPID_CAMPROVIDEO  0x0431  //Intel Pro Video PC Camera
#define USBPID_DIGIMOVIE    0x0510  //Digital Movie Creator
#define USBPID_CAMPOCKETPC  0x0630  //Pocket PC Camera
#define USBPID_BLOBBOOT     0x07D3  //BLOB boot loader firmware TODO: what is this? D.K.
#define USBPID_802_11_2011B 0x1111  //PRO/Wireless 2011B 802.11b Adapter
#define USBPID_USBHDC1      0x24D2  //82801EB 1st USB Universal Host Controller on the board
#define USBPID_USBHDC2      0x24D4  //82801EB 2nd USB Universal Host Controller on the board
#define USBPID_USBHDC3      0x24DE  //82801EB 3rd USB Universal Host Controller on the board
#define USBPID_USBHDC4      0x24DD  //82801EB 4th USB Universal Host Controller on the board
#define USBPID_82930        0x9890  //82930 Test Board
#define USBPID_HIDSTATION   0xC013  //Wireless HID Station
///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID8086_H_
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         22/08/2007 10:51:35 AMDarko Kolakovic
 * $
 *****************************************************************************/
