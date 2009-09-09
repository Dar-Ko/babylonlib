/*$Workfile: UsbVid04B4.h$: header file
  $Revision: 1.5 $ $Date: 2009/09/09 21:07:32 $
  $Author: ddarko $

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2008-09-24 Darko Kolakovic
 */

/* Group=USB ID                                                              */

#ifndef _USBVID04B4_H_
  //$Workfile: UsbVid04B4.h$ sentry
  #define _USBVID04B4_H_

/*1204.	USB device vendor identification (VID) number	Cypress Semiconductor Corporation	http://www.cypress.com/

  See also: usb-if.tsv (usb.if), Company List by USB Implementers Forum, Inc
  (USB-IF) at http://www.usb.org/developers/tools/comp_dump;
  usb.ids, List of USB ID's by Stephen J. Gowdy at http://www.linux-usb.org/usb.ids.
 */
#define USBVID_CYPRESSSEMICONDUCTOR 0x04B4
#define USBVID_04B4 _T("Cypress Semiconductor Corporation") //VID 1204 Vendor name

#define USBPID_DACALDC101    0x0000 //Dacal DC-101 CD Library
#define USBPID_MOUSECY       0x0001 //Cypress Mouse
#define USBPID_CY7C63X0X     0x0002 //CY7C63x0x Thermometer
#define USBPID_KBDHUBCY      0x0101 //Cypress Keyboard/Hub
#define USBPID_KBDAPM        0x0102 //Cypress Keyboard with APM
#define USBPID_MYIRC         0x0130 //MyIRC Remote Receiver
#define USBPID_PHONERECEIVER 0x0306 //Telephone Receiver
#define USBPID_METAGEEK      0x0BAD //MetaGeek Wi-Spy
#define USBPID_CY7C63001     0x1002 //CY7C63001 R100 FM Radio
#define USBPID_HIDCY         0x1006 //Cypress Human Interface Device
#define USBPID_SCAPSUSC1     0x4381 //SCAPS USC-1 Scanner Controller
#define USBPID_USBFX2CY      0x4611 //Cypress Storage Adapter FX2
#define USBPID_USBFLASHCY    0x4616 //Flash Disk (TPP)
#define USBPID_HIDRS232      0x5500 //Cypress USB HID to COM RS232 Adapter
#define USBPID_MOUSECC2201   0x6370 //ViewMate Desktop Mouse CC2201
#define USBPID_CY7C65640     0x6560 //CY7C65640 USB-2.0 4-port TetraHub
#define USBPID_CY7C68300A    0x6830 //CY7C68300A EZ-USB AT2 USB 2.0 to ATA/ATAPI
#define USBPID_ISD300LPCY    0x6831 //Cypress Storage Adapter ISD-300LP
#define USBPID_CYPCLOCK      0x7417 //Cypress Wireless PC Lock
#define USBPID_CY7C68013     0x8613 //CY7C68013 EZ-USB FX2 USB 2.0 Development Kit
#define USBPID_UDST7020BDA   0x8614 //DTV-DVB UDST7020BDA DVB-S Box(DVBS for MCE2005)
#define USBPID_CENTOR        0xCC04 //Centor USB RACIA-ALVAR USB PORT
#define USBPID_CENTORP       0xCC06 //Centor-P RACIA-ALVAR USB PORT
#define USBPID_ZBOXER        0xD5D5 //CY7C63x0x (?? D.K.) Zoltrix Z-Boxer GamePad ??
#define USBPID_CY30700       0xF000 //CY30700 Licorice evaluation board


///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID04B4_H_
/*****************************************************************************
 * $Log: UsbVid04B4.h,v $
 * Revision 1.5  2009/09/09 21:07:32  ddarko
 * *** empty log message ***
 *
 * Revision 1.4  2009/07/30 17:08:32  ddarko
 * Updated
 *
 * Revision 1.3  2008/09/29 15:27:15  ddarko
 * Corrected duplicated definitions
 *
 * Revision 1.2  2008/09/29 14:58:39  ddarko
 * Comments
 *
 * Revision 1.1  2008/09/24 18:06:24  ddarko
 * Created
 *
 *****************************************************************************/
