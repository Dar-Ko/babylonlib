/*$Workfile: UsbVid0DD4.h$: header file
  $Revision: 1$ $Date: 22/08/2007 10:51:35 AM$
  $Author: Darko Kolakovic$

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2007-08-17 Darko Kolakovic
 */

/* Group=USB ID                                                              */

#ifndef _USBVID0DD4_H_
  //$Workfile: UsbVid0DD4.h$ sentry
  #define _USBVID0DD4_H_

/*3540.	USB device vendor identification (VID) number	Custom Engineering SPA	http://www.custom.it/

  See also: usb-if.tsv, USB Implementers Forum, Inc (USB-IF) at http://www.usb.org
 */
#define USBVID_CUSTOM 0x0DD4
#define USBVID_0DD4 _T("Custom Engineering SPA") //VID 3540 Vendor name

#define USBPID_KPM216 0x0159 //KPM-210/216H Thermal Printer
#define USBPID_KPMxxx 0x0176 //KPM-300H Thermal Printer TODO: verify model!

///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID0DD4_H_
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         22/08/2007 10:51:35 AMDarko Kolakovic
 * $
 *****************************************************************************/
