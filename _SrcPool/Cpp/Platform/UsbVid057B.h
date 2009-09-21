/*$RCSfile: UsbVid057B.h,v $: header file
  $Revision: 1.1 $ $Date: 2009/09/21 13:23:56 $
  $Author: ddarko $

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2009-09-22 Darko Kolakovic
 */

/* Group=USB ID                                                              */

#ifndef _USBVID057B_H_
  //$RCSfile: UsbVid057B.h,v $ sentry
  #define _USBVID057B_H_

/*1403.	USB device vendor identification (VID) number	Y-E Data, Inc.	http://www.yedata.com/

  See also: usb-if.tsv (usb.if), Company List by USB Implementers Forum, Inc
  (USB-IF) at http://www.usb.org/developers/tools/comp_dump;
  usb.ids, List of USB ID's by Stephen J. Gowdy at http://www.linux-usb.org/usb.ids.
 */
#define USBVID_Y_E_DATA 0x057B
#define USBVID_057B _T("Y-E Data, Inc.") //VID 1403 Vendor name

#define USBPID_FLOPPYFLASHBUSTER   0x0000 //FlashBuster-U Floppy
#define USBPID_FLOPPYTRIMEDIA      0x0001 //Tri-Media Reader Floppy
#define USBPID_CARD_TRIMEDIAREADER 0x0006 //Tri-Media Card Reader
#define USBPID_STORAGE_YE10        0x0010 //Memory Stick Reader Writer
#define USBPID_CARD_YEHEXA6IN1     0x0020 //HEXA Media Drive 6-in-1 Card Reader Writer (Silicon Media R/W)
#define USBPID_STORAGE_YET         0x0030 //Memory Card Viewer (TV)

///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID057B_H_
/*****************************************************************************
 * $Log: UsbVid057B.h,v $
 * Revision 1.1  2009/09/21 13:23:56  ddarko
 * Created
 *
 *****************************************************************************/
