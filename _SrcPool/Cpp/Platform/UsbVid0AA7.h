/*$Workfile: UsbVid0AA7.h$: header file
  $Revision: 1$ $Date: 22/08/2007 10:51:35 AM$
  $Author: Darko Kolakovic$

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2007-08-17 Darko Kolakovic
 */

/* Group=USB ID                                                              */

#ifndef _USBVID0AA7_H_
  //$Workfile: UsbVid0AA7.h$ sentry
  #define _USBVID0AA7_H_

/*2727.	USB device vendor identification (VID) number	Wincor Nixdorf GmbH & Co KG	http://www.wincor-nixdorf.com

  See also: usb-if.tsv, USB Implementers Forum, Inc (USB-IF) at http://www.usb.org
 */
#define USBVID_WINCOR 0x0AA7
#define USBVID_0AA7 _T("Wincor Nixdorf GmbH & Co KG") //VID 2727 Vendor name

#define USBPID_TA58P   0x0100 //Point-of-Sale (POS) Keyboard TA58P-USB
#define USBPID_TA85P   0x0101 //POS Keyboard TA85P-USB
#define USBPID_TA59    0x0102 //POS Keyboard TA59-USB
#define USBPID_TA60    0x0103 //POS Keyboard TA60-USB
#define USBPID_SNIKEY  0x0104 //SNIkey Keyboard SNIKey-KB-USB
#define USBPID_BA63    0x0200 //POS Display BA63
#define USBPID_BA66    0x0201 //POS Display BA66
#define USBPID_XIBA63  0x0202 //Scanner and POS Display XiCheck-BA63
#define USBPID_XIBA66  0x0203 //Scanner and POS Display XiCheck-BA66
#define USBPID_BA63GV  0x0204 //Graphics POS Display BA63GV
#define USBPID_TH210   0x0300 //USB TH210 thermal receipt printer
#define USBPID_TH210N  0x0301 //USB TH210 thermal receipt printer in native mode
#define USBPID_TH220   0x0302 //USB TH220 thermal receipt printer
#define USBPID_TH220N  0x0303 //USB TH220 thermal receipt printer in native mode
#define USBPID_TH230   0x0304 //USB TH230 thermal receipt printer
#define USBPID_XIPRN   0x0305 //Lottery Printer XiPrintPlus
#define USBPID_TH320   0x0306 //USB TH320 thermal receipt printer
#define USBPID_TH320N  0x0307 //USB POS Printer TH320 in native mode
#define USBPID_TH420   0x0308 //USB TH420 thermal receipt printer
#define USBPID_TH420N  0x0309 ////USB POS Printer TH420 in native mode
#define USBPID_TH200B  0x030A //USB POS Printer TH200B
#define USBPID_XISCANS 0x0400 //Lottery Scanner Xiscan S
#define USBPID_XISCAN3 0x0401 //Lottery Scanner Xiscan 3
#define USBPID_TP06    0x4303 //USB Printer Port Monitor for TP06 thermal receipt printer
#define USBPID_TP07    0x4304 //USB Printer Port Monitor for TP07 thermal receipt printer
#define USBPID_TP07C   0x4305 //USB Printer Port Monitor for TP07 compact thermal receipt printer

///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID0AA7_H_
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         22/08/2007 10:51:35 AMDarko Kolakovic
 * $
 *****************************************************************************/

