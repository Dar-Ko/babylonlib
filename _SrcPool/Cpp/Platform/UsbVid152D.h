/*$Workfile: S:\_SrcPool\Cpp\Platform\UsbVid152D.h$: header file
  $Revision: 1$ $Date: 22/08/2007 10:51:35 AM$
  $Author: Darko Kolakovic$

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2007-08-17 Darko Kolakovic
 */

/* Group=USB ID                                                              */

#ifndef _USBVID152D_H_
  //$Workfile: UsbVid152D.h$ sentry
  #define _USBVID152D_H_

/*5421.	USB device vendor identification (VID) number	JMicron Technology Corp.	http://www.jmicron.com

  See also: usb-if.tsv, USB Implementers Forum, Inc (USB-IF) at http://www.usb.org
 */
#define USBVID_JMICRON 0x152D
#define USBVID_152D _T("JMicron Technology Corp.") //VID 5421 Vendor name

#define USBPID_JM20335 0x2335 //JM20335 Hi-speed USB to PATA Bridge
#define USBPID_JM20336 0x2336 //JM20336 Hi-Speed USB and SATA II 3.0G Combo to SATA II 3.0G Bridge
#define USBPID_JM20337 0x2337 //JM20337 Hi-Speed USB to SATA and PATA Combo Bridge
#define USBPID_JM20338 0x2338 //JM20338 Hi-Speed USB to SATA Combo (SATA/ATA/ATAPI) and PATA Bridge
#define USBPID_JM20339 0x2339 //JM20339 Hi-Speed USB to SATA Bridge

///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID152D_H_
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         22/08/2007 10:51:35 AMDarko Kolakovic
 * $
 *****************************************************************************/
