/*$Workfile: S:\_SrcPool\Cpp\Platform\UsbVid04CF.h$: header file
  $Revision: 1.2 $ $Date: 2007/09/06 01:20:34 $
  $Author: ddarko $

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2005-12-11 Darko Kolakovic
 */

/* Group=USB ID                                                              */

#ifndef _USBVID04CF_H_
  //$Workfile: S:\_SrcPool\Cpp\Platform\UsbVid04CF.h$ sentry
  #define _USBVID04CF_H_

/*1231.	USB device vendor identification (VID) number	Myson Century, Inc.	http://www.myson.com.tw/

  See also: usb-if.tsv, USB Implementers Forum, Inc (USB-IF) at http://www.usb.org
 */
#define USBVID_MYSON 0x04CF
#define USBVID_04CF _T("Myson Century, Inc.") //VID 1231 Vendor name

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
 * $Log:
 *  1    Biblioteka1.0         22/08/2007 10:51:36 AMDarko Kolakovic
 * $
 * Revision 1.1  2007/08/20 18:55:32  ddarko
 * Created
 *
 *****************************************************************************/
