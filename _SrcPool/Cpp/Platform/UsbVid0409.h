/*$RCSfile: UsbVid0409.h,v $: header file
  $Revision: 1.1 $ $Date: 2009/10/08 15:32:01 $
  $Author: ddarko $

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2007-08-17 Darko Kolakovic
 */

/* Group=USB ID                                                              */

#ifndef _USBVID0409_H_
  //$RCSfile: UsbVid0409.h,v $ sentry
  #define _USBVID0409_H_

/*1033.	USB device vendor identification (VID) number	NEC Corporation	http://www.nec.com/

  See also: usb-if.tsv (usb.if), Company List by USB Implementers Forum, Inc
  (USB-IF) at http://www.usb.org/developers/tools/comp_dump;
  usb.ids, List of USB ID's by Stephen J. Gowdy at http://www.linux-usb.org/usb.ids.
 */
#define USBVID_NEC 0x0409
#define USBVID_0409 _T("$VENDOR") //VID 1033 Vendor name

#define USBPID_MOUSENECPC98           0x0011 //PC98 Series Layout Keyboard Mouse
#define USBPID_ATERMIT75DSU           0x0012 //ATerm IT75DSU ISDN TA
#define USBPID_KBDNECJ14              0x0014 //NEC Japanese Keyboard
#define USBPID_KBDNEC109JHUB          0x0019 //109 Japanese Keyboard with Bus-Powered Hub
#define USBPID_KBDNECPC98HUB          0x001A //PC98 Series Layout Keyboard with Bus-Powered Hub
#define USBPID_NECBARCODE             0x001F //Generic bar code scanner
#define USBPID_KBDNECMINIHUB          0x0025 //Mini Keyboard with Bus-Powered Hub
#define USBPID_MONITORNECMULTISYNC    0x0027 //MultiSync Monitor
#define USBPID_STORAGENECCLIK         0x002C //Clik!-USB Drive
#define USBPID_KBDNEC109JONETOUCH     0x0034 //109 Japanese Keyboard with One-touch start buttons
#define USBPID_KBDNECWIRELESSONETOUCH 0x003F //Wireless Keyboard with One-touch start buttons
#define USBPID_FLOPPYNEC              0x0040 //Floppy
#define USBPID_SUPERSCRIPT1400        0x004E //SuperScript 1400 Series
#define USBPID_KBDNECWIRELESS4F       0x004F //Wireless Keyboard with One-touch start buttons
#define USBPID_HUBNECHIGHSPEED58      0x0058 //HighSpeed Hub
#define USBPID_HUBNECHIGHSPEED59      0x0059 //HighSpeed Hub
#define USBPID_HUBNECHIGHSPEED5A      0x005A //HighSpeed Hub
#define USBPID_STORAGECONCEPTRONIC    0x006A //Conceptronic USB Harddisk Box
#define USBPID_SUPERSCRIPT140081      0x0081 //SuperScript 1400 Series
#define USBPID_SUPERSCRIPT140082      0x0082 //SuperScript 1400 Series
#define USBPID_KBDNEC109JONETOUCH94   0x0094 //Japanese Keyboard with One-touch start buttons
#define USBPID_KBDNECJ95              0x0095 //Japanese Keyboard
#define USBPID_ATERMIT21L128K         0x00A9 //AtermIT21L 128K Support Standard
#define USBPID_ATERMITX72128K         0x00AA //AtermITX72 128K Support Standard
#define USBPID_ATERMITX62128K         0x00AB //AtermITX62 128K Support Standard
#define USBPID_ATERMIT42128K          0x00AC //AtermIT42 128K Support Standard
#define USBPID_INSMATEV70GMAX         0x00AE //INSMATEV70G-MAX Standard
#define USBPID_ATERMITX70128K         0x00AF //AtermITX70 128K Support Standard
#define USBPID_ATERMITX80128K         0x00B0 //AtermITX80 128K Support Standard
#define USBPID_ATERMITX80D128K        0x00B2 //AtermITX80D 128K Support Standard
#define USBPID_WIRELESSREMOCON        0x00C0 //Wireless Remocon Remote controll
#define USBPID_MOINTORSMARTPKSD10     0x00F7 //Smart Display PK-SD10
#define USBPID_PHONENECE228MOBILE     0x011D //e228 Mobile Phone
#define USBPID_NECHIDAUDIOCONTROLS    0x0203 //HID Audio Controls
#define USBPID_HUBNEC55AA             0x55AA //Hub
#define USBPID_KBDHUBIMACITOUCH       0x55AB //Hub [iMac/iTouch kbd]
#define USBPID_HUBINTELLIBASE10       0x8010 //Intellibase Hub
#define USBPID_HUBINTELLIBASE11       0x8011 //Intellibase Hub
#define USBPID_PICTY900               0xEFBE //P!cty 900 [HP DJ]
#define USBPID_PICTY920               0xF0BE //P!cty 920 [HP DJ 812c]
///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID0409_H_
/*****************************************************************************
 * $Log: UsbVid0409.h,v $
 * Revision 1.1  2009/10/08 15:32:01  ddarko
 * Added new devices
 *
 *****************************************************************************/
