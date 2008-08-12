/*$Workfile: UsbVid0D85.h$: header file
  $Revision: 1.2 $ $Date: 2008/08/12 18:52:55 $
  $Author: ddarko $

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2007-08-17 Darko Kolakovic
 */

/* Group=USB ID                                                              */

#ifndef _USBVID0D85_H_
  //$Workfile: UsbVid0D85.h$ sentry
  #define _USBVID0D85_H_

/*3461.	USB device vendor identification (VID) number	Identix Incorporated of L-1 Identity Solutions	http://www.l1id.com/

  See also: usb-if.tsv, USB Implementers Forum, Inc (USB-IF) at http://www.usb.org
 */
#define USBVID_IDENTIX 0x0D85
#define USBVID_0D85 _T("Identix Incorporated") //VID 3461 Vendor name

#define USBPID_DFR2100 0x0004 //DFR-2100 USB Fingerprint Reader

///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID0D85_H_
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         22/08/2007 10:51:35 AMDarko Kolakovic
 * $
 *****************************************************************************/
