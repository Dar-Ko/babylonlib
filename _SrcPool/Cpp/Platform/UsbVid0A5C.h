/*$RCSfile: UsbVid0A5C.h,v $: header file
  $Revision: 1.1 $ $Date: 2009/09/11 20:35:49 $
  $Author: ddarko $

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2007-08-17 Darko Kolakovic
 */

/* Group=USB ID                                                              */

#ifndef _USBVID0A5C_H_
  //$RCSfile: UsbVid0A5C.h,v $ sentry
  #define _USBVID0A5C_H_

/*2652.	USB device vendor identification (VID) number	Broadcom Corporation	http://www.broadcom.com

  See also: usb-if.tsv (usb.if), Company List by USB Implementers Forum, Inc
  (USB-IF) at http://www.usb.org/developers/tools/comp_dump;
  usb.ids, List of USB ID's by Stephen J. Gowdy at http://www.linux-usb.org/usb.ids.
 */
#define USBVID_BROADCOM 0x0A5C
#define USBVID_0A5C _T("Broadcom Corporation") //VID 2652 Vendor name

#define USBPID_BCILINE10          0x0201 //iLine10 Network Adapter
#define USBPID_BCD2000            0x2000 //Bluetooth Device
#define USBPID_BCD2001            0x2001 //Bluetooth Device
#define USBPID_BCM2009            0x2009 //Bluetooth Controller
#define USBPID_BCD200A            0x200A //Bluetooth dongle
#define USBPID_BCM200F            0x200F //Bluetooth Controller
#define USBPID_BCD201D            0x201D //Bluetooth Device
#define USBPID_BCIBMINTEGRATED4   0x201E //IBM Integrated Bluetooth IV
#define USBPID_BCD2020            0x2020 //Bluetooth dongle
#define USBPID_BCM2033            0x2033 //BCM-2033 Bluetooth
#define USBPID_BCM2035            0x2035 //BCM-2035 Bluetooth
#define USBPID_BLUTONIUM          0x2038 //Blutonium Device
#define USBPID_BCD2039            0x2039 //Bluetooth Device
#define USBPID_BCM2045A           0x2045 //BCM-2045A Bluetooth Controller
#define USBPID_BCD2046            0x2046 //Bluetooth Device
#define USBPID_BCD2047            0x2047 //Bluetooth Device
#define USBPID_BCD205E            0x205E //Bluetooth Device
#define USBPID_BCD2EDRDONGLE      0x2100 //Bluetooth 2.0+eDR dongle
#define USBPID_BCALINKBLUEUSBA2   0x2101 //A-Link BlueUsb A2 Bluetooth
#define USBPID_BCANYCOM200250     0x2102 //ANYCOM Blue USB-200/250
#define USBPID_BCM2110            0x2110 //Bluetooth Controller
#define USBPID_BCANYCOMUHE200250  0x2111 //ANYCOM Blue USB-UHE 200/250
#define USBPID_BC2045UHE          0x2120 //2045 Bluetooth 2.0 USB-UHE Device with trace filter
#define USBPID_BCM2210            0x2121 //BCM-2210 Bluetooth
#define USBPID_BCD2EDR            0x2122 //Bluetooth 2.0+EDR dongle
#define USBPID_BCD2123            0x2123 //Bluetooth dongle
#define USBPID_BCM2045UHE2        0x2130 //2045 Bluetooth 2.0 USB-UHE Device with trace filter
#define USBPID_BCM2045BT2         0x2131 //2045 Bluetooth 2.0 Device with trace filter
#define USBPID_BCM2046B1          0x4500 //BCM-2046B1 USB 2.0 Hub (part of BCM2046 Bluetooth)
#define USBPID_BCM5880            0x5800 //BCM-5880 Secure Applications Processor
#define USBPID_BCPIRELLI          0x6300 //Pirelli Remote NDIS Device

///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID0A5C_H_
/*****************************************************************************
 * $Log: UsbVid0A5C.h,v $
 * Revision 1.1  2009/09/11 20:35:49  ddarko
 * Broadcom
 *
 *****************************************************************************/
