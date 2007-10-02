/*$Workfile: S:\_SrcPool\Cpp\Platform\UsbVid0AA7.h$: header file
  $Revision: 1$ $Date: 22/08/2007 10:51:35 AM$
  $Author: Darko Kolakovic$

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2007-08-17 Darko Kolakovic
 */

/* Group=USB ID                                                              */

#ifndef _USBVID0AA7_H_
  //$Workfile: UsbVid0AA7.h$ sentry
  #define _USBVID0AA7_H_

/*2727.	USB device vendor identification (VID) number	Wincor Nixdorf GmbH & Co KG	http://www.wincor-nixdorf.com

  See also: usb-if.tsv, USB Implementers Forum, Inc (USB-IF) at http://www.usb.org
 */
#define USBVID_WINCOR 0x0AA7
#define USBVID_0AA7 _T("Wincor Nixdorf GmbH & Co KG") //VID 2727 Vendor name

#define USBPID_TP06  0x4303 //USB Printer Port Monitor for TP06 thermal receipt printer
#define USBPID_TP07  0x4304 //USB Printer Port Monitor for TP07 thermal receipt printer
#define USBPID_TP07C 0x4305 //USB Printer Port Monitor for TP07 compact thermal receipt printer

///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID0AA7_H_
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         22/08/2007 10:51:35 AMDarko Kolakovic
 * $
 *****************************************************************************/
