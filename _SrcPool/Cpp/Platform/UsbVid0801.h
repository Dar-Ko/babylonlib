/*$Workfile: UsbVid0801.h$: header file
  $Revision: 1.3 $ $Date: 2008/04/08 18:23:05 $
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

#define USBPID_MTKBSWIPEMSR  0x0001 /*MagTek USB KB Swipe/SureSwipe (Dual Head)
                                   Magnetic Strip Readers
                                   emulating a USB Human Interface Device (HID)
                                   keyboard. Part Numbers: 21040107, 21040108,
                                   21040109, 21040110, 21040122, 21040123,
                                   21040145, 21040147.
                                  */
#define USBPID_MTHIDSWIPEMSR 0x0002 /*MagTek Mini HID Swipe/Full Size/ HID SureSwipe
                                   (Dual Head) Magnetic Strip Readers.
                                   Part Numbers: 21040101, 21040102, 21040103,
                                   21040104, 21040113, 21040114, 21040119,
                                   21040139, 21040143, 21040140, 21040146.
                                  */
#define USBPID_MT215MSR      0x0003 //MagTek 215/P-Series Insert Magnetic Strip Reader

///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID0801_H_
/*****************************************************************************
 * $Log: UsbVid0801.h,v $
 * Revision 1.3  2008/04/08 18:23:05  ddarko
 * MagTek KB  Swipe
 *
 *****************************************************************************/
