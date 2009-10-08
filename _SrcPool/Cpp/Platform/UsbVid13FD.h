/*$RCSfile: UsbVid13FD.h,v $: header file
  $Revision: 1.1 $ $Date: 2009/10/08 15:32:01 $
  $Author: ddarko $

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2007-08-17 Darko Kolakovic
 */

/* Group=USB ID                                                              */

#ifndef _USBVID13FD_H_
  //$RCSfile: UsbVid13FD.h,v $ sentry
  #define _USBVID13FD_H_

/*5117.	USB device vendor identification (VID) number	Initio Corporation	http://www.initio.com/

  See also: usb-if.tsv (usb.if), Company List by USB Implementers Forum, Inc
  (USB-IF) at http://www.usb.org/developers/tools/comp_dump;
  usb.ids, List of USB ID's by Stephen J. Gowdy at http://www.linux-usb.org/usb.ids.
 */
#define USBVID_INITIO 0x13FD
#define USBVID_13FD _T("Initio Corporation") //VID 5117 Vendor name

#define USBPID_STORAGEINITIOTGEN 0x1840 //Generic External 2.5" Storage Adapter

///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID13FD_H_
/*****************************************************************************
 * $Log: UsbVid13FD.h,v $
 * Revision 1.1  2009/10/08 15:32:01  ddarko
 * Added new devices
 *
 *****************************************************************************/
