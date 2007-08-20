/*$Workfile: UsbVid05E0.h,v $: header file
  $Revision: 1.2 $ $Date: 2007/08/20 19:38:21 $
  $Author: ddarko $

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2007-08-17 Darko Kolakovic
 */

#ifndef _USBVID05E0_H_
  //$Workfile: UsbVid05E0.h$ sentry
  #define _USBVID05E0_H_

/*1504.USB device vendor identification (VID) number	Motorola Symbol Technologies	http://www.symbol.com/

  See also: usb-if.tsv, USB Implementers Forum, Inc (USB-IF) at http://www.usb.org
 */
#define USBVID_SYMBOL 0x5E0

/*MiniScan MS4404/MS4407 USB scanner product identification (PID) number.
  Device is configured for Simple COM Port Emulation (Rev:NBRPVAAK5).
  See also: MS4404/MS4407 Integration Guide, 9-3 MS4407 - USB Interface.
 */
#define USBPID_MS4407COM 0x0600

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

///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID05E0_H_
/*****************************************************************************
 * $Log: UsbVid05E0.h,v $
 * Revision 1.2  2007/08/20 19:38:21  ddarko
 * PID for different revisions
 *
 *****************************************************************************/
