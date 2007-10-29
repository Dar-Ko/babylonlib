/*$Workfile: S:\_SrcPool\Cpp\Platform\UsbVid0801.h$: header file
  $Revision: 1.1 $ $Date: 2007/10/29 19:05:25 $
  $Author: ddarko $

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2007-08-17 Darko Kolakovic
 */

/* Group=USB ID                                                              */

#ifndef _USBVID0801_H_
  //$Workfile: UsbVid0801.h$ sentry
  #define _USBVID0801_H_

/*2049.	USB device vendor identification (VID) number	Mag-Tek	http://www.magtek.com/

  See also: usb-if.tsv, USB Implementers Forum, Inc (USB-IF) at http://www.usb.org
 */
#define USBVID_MAGTEK 0x0801
#define USBVID_0801 _T("Mag-Tek") //VID 2049 Vendor name

#define USBPID_MTSWIPEMSR 0x0002 //MagTek Mini Swipe Magnetic Strip Reader
#define USBPID_MT215MSR   0x0003 //MagTek 215 Insert Magnetic Strip Reader

///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID0801_H_
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         22/08/2007 10:51:35 AMDarko Kolakovic
 * $
 *****************************************************************************/
