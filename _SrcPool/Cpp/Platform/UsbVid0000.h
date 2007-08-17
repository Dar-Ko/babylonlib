/*$Workfile: $: header file
  $Revision: $ $Date: $
  $Author: ddarko $

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2007-08-17 Darko Kolakovic
 */

/* Group=USB ID                                                              */

#ifndef _USBVID0000_H_
  //$Workfile: UsbVid0000.h$ sentry
  #define _USBVID0000_H_

/*$VID.	USB device vendor identification (VID) number	$VENDOR	$VENDORADR

  See also: usb-if.tsv, USB Implementers Forum, Inc (USB-IF) at http://www.usb.org
 */
#define USBVID_$VENDOR 0x0000

#define USBPID_$PRODUCT $PID //TODO: Append and Sort PID

///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID0000_H_
/*****************************************************************************
 * $Log: $
 *****************************************************************************/
