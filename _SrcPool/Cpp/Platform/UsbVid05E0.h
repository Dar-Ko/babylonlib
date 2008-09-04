/*$Workfile: UsbVid05E0.h$: header file
  $Revision: 1.6 $ $Date: 2008/09/04 21:14:48 $
  $Author: ddarko $

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2007-08-17 Darko Kolakovic
 */

#ifndef _USBVID05E0_H_
  //$Workfile: UsbVid05E0.h$ sentry
  #define _USBVID05E0_H_

#define USBVID_05E0 _T("Motorola Symbol Technologies") //VID 1504 Vendor name

/*1504.	USB device vendor identification (VID) number	Motorola Symbol Technologies	http://www.symbol.com/; http://www.motorola.com/

  See also: usb-if.tsv, USB Implementers Forum, Inc (USB-IF) at http://www.usb.org
 */
#define USBVID_SYMBOL 0x05E0

/*MiniScan MS4404/MS4407 USB scanner product identification (PID) number.
  Device is configured for Simple COM Port Emulation (Rev:NBRPVAAK5).
  See also: MS4404/MS4407 Integration Guide, 9-3 MS4407 - USB Interface.
 */
#define USBPID_MS4407COM 0x0600

#define USBPID_CS1504     0x0700  //Bar Code Scanner (CS1504)
#define USBPID_SPECTRUM24 0x0800  //Symbol Spectrum24 Wireless LAN Adapter

/*MiniScan MS4404/MS4407 USB scanner product identification (PID) number.
  Device is configured for HID Keyboard Emulation (Rev:NBRPVAAK3).
  See also: MS4404/MS4407 Integration Guide, 9-3 MS4407 - USB Interface.
 */
#define USBPID_MS4407KBD 0x1200

/*MiniScan MS4404/MS4407 USB scanner product identification (PID) number.
  Device is configured as USB OPOS or IBM Hand-held Scanner (Rev:NBRPVAAK1).
  See also: MS4404/MS4407 Integration Guide, 9-3 MS4407 - USB Interface.
  Microsoft Retail Management System OPOS name is STI_USBSCANNER
 */
#define USBPID_MS4407HHS 0x1300

/*MiniScan MS4404/MS4407 USB scanner product identification (PID) number.
  Device is configured as IBM Table Top Scanner (Rev:NBRPVAAK2).
  See also: MS4404/MS4407 Integration Guide, 9-3 MS4407 - USB Interface.
 */
#define USBPID_MS4407TTS 0x1400

/*MiniScan MS4404/MS4407 USB scanner product identification (PID) number.
  Device is configured for Symbol Native API (SNAPI) with Imaging Interface
  (Rev:NBRPVAAK9) or without Imaging Interface (Rev:NBRPVAAKA).
  See also: MS4404/MS4407 Integration Guide, 9-3 MS4407 - USB Interface.
 */
#define USBPID_MS4407SNAPI 0x1900
#define USBPID_MC3090      0x2000  //MC3090 Rugged Mobile Computer
#define USBPID_MC70        0x200D  //MC70 Handheld Mobile Computer

///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID05E0_H_
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         22/08/2007 10:51:37 AMDarko Kolakovic
 * $
 *****************************************************************************/
