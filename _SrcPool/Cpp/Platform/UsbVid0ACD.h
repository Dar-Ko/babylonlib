/*$Workfile: UsbVid0ACD.h$: header file
  $Revision: 1$ $Date: 22/08/2007 10:51:35 AM$
  $Author: Darko Kolakovic$

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2007-09-01 Darko Kolakovic
 */

/* Group=USB ID                                                              */

#ifndef _USBVID0ACD_H_
  //$Workfile: UsbVid0ACD.h$ sentry
  #define _USBVID0ACD_H_

/*2765.	USB device vendor identification (VID) number	ID Tech	http://www.idt-net.com/

  See also: usb-if.tsv, USB Implementers Forum, Inc (USB-IF) at http://www.usb.org
 */
#define USBVID_IDTECH 0x0ACD
#define USBVID_0ACD _T("ID Tech") //VID 2765 Vendor name

#define USBPID_MOIRSPECTRUM3SMART 0x0401 //Spectrum III Hybrid Smartcard Reader
#define USBPID_MOIRSPECTRUM3      0x0630 /*Spectrum III USB Magstripe Only Insert
                                Reader (MOIR) with CDC USB to COM port driver*/

///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID0ACD_H_
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         22/08/2007 10:51:35 AMDarko Kolakovic
 * $
 *****************************************************************************/
