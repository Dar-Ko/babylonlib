/*$Workfile: S:\_SrcPool\Cpp\Platform\UsbVid0801.h$: header file
  $Revision: 1.2 $ $Date: 2007/10/29 19:08:51 $
  $Author: ddarko $

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2007-08-17 Darko Kolakovic
 */

/* Group=USB ID                                                              */

#ifndef _USBVID0801_H_
  //$Workfile: UsbVid0801.h$ sentry
  #define _USBVID0801_H_

/*2049.	USB device vendor identification (VID) number	Mag-Tek	http://www.magtek.com/

  See also: usb-if.tsv, USB Implementers Forum, Inc (USB-IF) at http://www.usb.org
 */
#define USBVID_MAGTEK 0x0801
#define USBVID_0801 _T("Mag-Tek") //VID 2049 Vendor name

#define USBPID_MTSWIPEMSR 0x0002 //MagTek Mini Swipe Magnetic Strip Reader
#define USBPID_MT215MSR   0x0003 //MagTek 215 Insert Magnetic Strip Reader

///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID0801_H_
/*****************************************************************************
 * $Log: UsbVid0801.h,v $
 * Revision 1.2  2007/10/29 19:08:51  ddarko
 * *** empty log message ***
 *
 *****************************************************************************/
