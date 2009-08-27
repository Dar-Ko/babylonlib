/*$RCSfile: UsbVid058F.h,v $: header file
  $Revision: 1.1 $ $Date: 2009/08/27 14:18:45 $
  $Author: ddarko $

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2007-08-17 Darko Kolakovic
 */

/* Group=USB ID                                                              */

#ifndef _USBVID058F_H_
  //$RCSfile: UsbVid058F.h,v $ sentry
  #define _USBVID058F_H_

/*1423. USB device vendor identification (VID) number Alcor Micro, Corp.  http://www.alcormicro.com

  See also: usb-if.tsv (usb.if), Company List by USB Implementers Forum, Inc
  (USB-IF) at http://www.usb.org/developers/tools/comp_dump;
  usb.ids, List of USB ID's by Stephen J. Gowdy at http://www.linux-usb.org/usb.ids.
 */
#define USBVID_ALCORMICRO 0x058F
#define USBVID_058F _T("Alcor Micro, Corp.") //VID 1423 Vendor name

#define USBPID_STORAGE_AMFLASHDRIVE34    0x1234 //Flash Drive
#define USBPID_SCARDRW_CSR145            0x2412 //SCard R/W CSR-145
#define USBPID_KBD_MONTEREY              0x2802 //Monterey Keyboard
#define USBPID_HUBAM92                   0x5492 //Hub
#define USBPID_CARD_AMHI16IN1            0x6232 //Hi-Speed 16-in-1 Flash Card Reader/Writer
#define USBPID_HUBAM54                   0x6254 //USB Hub
#define USBPID_CARD_AMSD_MMC             0x6335 //SD/MMC Card Reader
#define USBPID_CARD_AMMULTIMEDIA60       0x6360 //Multimedia Card Reader
#define USBPID_CARD_AMMULTIMEDIA61       0x6361 //Multimedia Card Reader
#define USBPID_CARD_AMHI21IN1            0x6362 //Hi-Speed 21-in-1 Flash Card Reader/Writer (Internal/External)
#define USBPID_CARD_AMMULTIMEDIA77       0x6377 //Multimedia Card Reader
#define USBPID_STORAGE_AM86              0x6386 //Memory Card
#define USBPID_STORAGE_TRANSCENDJETFLASH 0x6387 //Transcend JetFlash Flash Drive
#define USBPID_AM_IDEBRIDGE              0x6390 //USB 2.0-IDE bridge
#define USBPID_KBD_MACALLYHUB            0x9213 //MacAlly Kbd Hub
#define USBPID_HUBAU9814                 0x9215 //AU9814 Hub
#define USBPID_HUBAMGENERIC4PORT         0x9254 //Generic Hub 4 Port
#define USBPID_STORAGE_UID457A           0x9310 //Mass Storage (UID4/5A & UID7A)
#define USBPID_STORAGE_AMMICRO20WIN98    0x9320 //Micro Storage Driver for Win98
#define USBPID_STORAGE_AMMICRO21WIN98    0x9321 //Micro Storage Driver for Win98
#define USBPID_CARD_AMSDREADER           0x9330 //SD Reader
#define USBPID_STORAGE_AMMICRO31WIN98    0x9331 //Micro Storage Driver for Win98
#define USBPID_DELKINEFILMREADER32_40    0x9340 //Delkin eFilm Reader-32
#define USBPID_DELKINEFILMREADER32_50    0x9350 //Delkin eFilm Reader-32
#define USBPID_CARD_AM8IN1MEDIAREADER    0x9360 //8-in-1 Media Card Reader
#define USBPID_CARD_AMMULTIMEDIA361      0x9361 //Multimedia Card Reader
#define USBPID_CARD_AMMULTIMEDIA368      0x9368 //Multimedia Card Reader
#define USBPID_STORAGE_AMFLASHDRIVE80    0x9380 //Flash Drive
#define USBPID_STORAGE_ACERSWEEX         0x9382 //Acer/Sweex Flash drive
#define USBPID_KBD_AM410                 0x9410 //Keyboard
#define USBPID_KBD_AMHUB472              0x9472 //Keyboard Hub
#define USBPID_CARD_CHUNGHWATLUSB02      0x9510 //ChunghwaTL USB02 Smartcard Reader
#define USBPID_CARD_EMVCERT              0x9520 //EMV Certified Smart Card Reader
#define USBPID_AMSERIALADAPTER           0x9720 //USB-Serial Adapter
///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID058F_H_
/*****************************************************************************
 * $Log: UsbVid058F.h,v $
 * Revision 1.1  2009/08/27 14:18:45  ddarko
 * Alcor Micro, Corp.
 *
 *****************************************************************************/
