/*$Workfile: UsbVid078B.h$: header file
  $Revision: 1.1 $ $Date: 2008/09/04 15:24:28 $
  $Author: ddarko $

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2008-09-04 Darko Kolakovic
 */

/* Group=USB ID                                                              */

#ifndef _USBVID078B_H_
  //$Workfile: UsbVid078B.h$ sentry
  #define _USBVID078B_H_

/*1931.	USB device vendor identification (VID) number	Suzo-Happ Group, Happ Controls, Inc	http://www.happ.com/

  See also: usb-if.tsv (usb.if), Company List by USB Implementers Forum, Inc
  (USB-IF) at http://www.usb.org/developers/tools/comp_dump;
  usb.ids, List of USB ID's by Stephen J. Gowdy at http://www.linux-usb.org/usb.ids.
 */
#define USBVID_HAPP 0x078B
#define USBVID_078B _T("Suzo-Happ Group") //VID 1931 Vendor name

#define USBPID_DRIVING  0x0010 //Driving USB Game Control Interface (UGCI)
#define USBPID_FLYING   0x0020 //Flying USB Game Control Interface (UGCI)
#define USBPID_FIGHTING 0x0030 //Fighting USB Game Control Interface (UGCI)

///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID078B_H_
/*****************************************************************************
 * $Log: UsbVid078B.h,v $
 * Revision 1.1  2008/09/04 15:24:28  ddarko
 * Created
 *
 *****************************************************************************/
