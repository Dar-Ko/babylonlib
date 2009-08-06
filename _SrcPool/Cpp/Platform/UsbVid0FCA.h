/*$RCSfile: UsbVid0FCA.h,v $: header file
  $Revision: 1.1 $ $Date: 2009/08/06 19:34:38 $
  $Author: ddarko $

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2008-03-10 Darko Kolakovic
 */

/* Group=USB ID                                                              */

#ifndef _USBVID0FCA_H_
  //$RCSfile: UsbVid0FCA.h,v $ sentry
  #define _USBVID0FCA_H_

/*4042. USB device vendor identification (VID) number Research In Motion, Ltd. (RiM)  http://www.rim.com/

  See also: usb-if.tsv (usb.if), Company List by USB Implementers Forum, Inc
  (USB-IF) at http://www.usb.org/developers/tools/comp_dump;
  usb.ids, List of USB ID's by Stephen J. Gowdy at http://www.linux-usb.org/usb.ids.
 */
#define USBVID_RIM 0x0FCA
#define USBVID_0FCA _T("Research In Motion, Ltd.") //VID 4042 Vendor name

#define USBPID_BLACKBERRY       0x0001  /*BlackBerry Handheld 7100 Smartphone?? maybe others
   Note: Blackberry Handhelds can run in two modes: as a USB storage media only
   or as a mass storage with access to its database.*/
#define USBPID_BLACKBERRY2      0x0004  //BlackBerry ??
#define USBPID_BLACKBERRYPEARL  0x0006  //BlackBerry Pearl Smartphone

///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID0FCA_H_
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         22/08/2007 10:51:35 AMDarko Kolakovic
 * $
 *****************************************************************************/
