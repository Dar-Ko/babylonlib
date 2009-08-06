/*$RCSfile: UsbVid0000.h$: header file
  $Revision: 1$ $Date: 22/08/2007 10:51:35 AM$
  $Author: Darko Kolakovic$

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2007-08-17 Darko Kolakovic
 */

/* Group=USB ID                                                              */

#ifndef _USBVID0000_H_
  //$RCSfile: UsbVid0000.h$ sentry
  #define _USBVID0000_H_

/*$VID.	USB device vendor identification (VID) number	$VENDOR	$VENDORADR

  See also: usb-if.tsv (usb.if), Company List by USB Implementers Forum, Inc
  (USB-IF) at http://www.usb.org/developers/tools/comp_dump;
  usb.ids, List of USB ID's by Stephen J. Gowdy at http://www.linux-usb.org/usb.ids.
 */
#define USBVID_$VENDOR 0x0000
#define USBVID_0000 _T("$VENDOR") //VID $VID Vendor name

#define USBPID_$PRODUCT $PID //TODO: Append and Sort PID

///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID0000_H_
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         22/08/2007 10:51:35 AMDarko Kolakovic
 * $
 *****************************************************************************/
