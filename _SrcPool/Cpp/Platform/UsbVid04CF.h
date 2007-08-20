/*$Workfile: $: header file
  $Revision: 1.1 $ $Date: 2007/08/20 18:55:32 $
  $Author: ddarko $

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2005-12-11 Darko Kolakovic
 */

/* Group=USB ID                                                              */

#ifndef _USBVID04CF_H_
  //$Workfile: UsbVid04CF.h$ sentry
  #define _USBVID04CF_H_

/*1231.	USB device vendor identification (VID) number	Myson Century, Inc.	http://www.myson.com.tw/

  See also: usb-if.tsv, USB Implementers Forum, Inc (USB-IF) at http://www.usb.org
 */
#define USBVID_MYSON 0x04CF

#define USBPID_MTM808 0x0808 //MTM808 USB Mass Storage Device
#define USBPID_MTM809 0x0809 //MTM809 USB Mass Storage Device
#define USBPID_CS8810 0x8810 //CS8810 USB Mass Storage Device
#define USBPID_CS8811 0x8811 /*CS8811/CS8812 USB 2.0 mass storage class peripheral
                               controller for standard ATA and ATAPI devices.*/
#define USBPID_CS8813 0x8813 //CS8813 USB Mass Storage Device
#define USBPID_CS8815 0x8816 //CS8816 USB Mass Storage Device
#define USBPID_CS8818 0x8818 /*CS8818 USB 2.0 Mass storage class peripheral
                               controller for standard 2.5" ATAPI devices
                               (USB2.0 to ATAPI Bridge Controller).*/

///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID04CF_H_
/*****************************************************************************
 * $Log: UsbVid04CF.h,v $
 * Revision 1.1  2007/08/20 18:55:32  ddarko
 * Created
 *
 *****************************************************************************/
