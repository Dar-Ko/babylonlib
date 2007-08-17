/*$Workfile: UsbVid05E0.h $: header file
  $Revision: 1.1 $ $Date: 2007/08/17 21:15:42 $
  $Author: ddarko $

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2007-08-17 Darko Kolakovic
 */

#ifndef _USBVID05E0_H_
  //$Workfile: UsbVid05E0.h$ sentry
  #define _USBVID05E0_H_

/*1504.	USB device vendor identification (VID) number	Motorola Symbol Technologies	http://www.symbol.com/

  See also: usb-if.tsv, USB Implementers Forum, Inc (USB-IF) at http://www.usb.org
 */
#define USBVID_SYMBOL 0x05E0

/*MiniScan MS4404/MS4407 USB scanner product identification (PID) number.
  Microsoft Retail Management System OPOS name is STI_USBSCANNER
 */
#define USBPID_MS4407 0x1200
///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID05E0_H_
/*****************************************************************************
 * $Log: UsbVid05E0.h,v $
 * Revision 1.1  2007/08/17 21:15:42  ddarko
 * Created
 *
 *****************************************************************************/
