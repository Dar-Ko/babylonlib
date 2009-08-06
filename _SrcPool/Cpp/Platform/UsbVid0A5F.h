/*$RCSfile: UsbVid0A5F.h,v $: header file
  $Revision: 1.2 $ $Date: 2009/08/06 19:34:38 $
  $Author: ddarko $

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2009-07-30 Darko Kolakovic
 */

/* Group=USB ID                                                              */

#ifndef _USBVID0A5F_H_
  //$RCSile: UsbVid0A5F.h$ sentry
  #define _USBVID0A5F_H_

/*2655.	USB device vendor identification (VID) number	Zebra Technologies (Eltron Card Printer Products)	http://www.zebra.com

  See also: usb-if.tsv (usb.if), Company List by USB Implementers Forum, Inc
  (USB-IF) at http://www.usb.org/developers/tools/comp_dump;
  usb.ids, List of USB ID's by Stephen J. Gowdy at http://www.linux-usb.org/usb.ids.
 */
#define USBVID_ZEBRATECHNOLOGIES 0x0A5F
#define USBVID_0A5F              _T("Zebra Technologies") //VID 2655 Vendor name

#define USBPID_PRNLP2844   0x0009 //Eltron thermal LP 2844 bar code label printer
#define USBPID_PRNTLP2844  0x000A //Eltron thermal transfer TLP 2844 bar code label printer
#define USBPID_PRNZEBRA    0x930A //Printer ??

///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID0A5F_H_
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         22/08/2007 10:51:35 AMDarko Kolakovic
 * $
 *****************************************************************************/
