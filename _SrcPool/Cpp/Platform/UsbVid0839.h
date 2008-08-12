/*$RCSfile: UsbVid0839.h,v $: header file
  $Revision: 1.2 $ $Date: 2008/08/12 18:55:45 $
  $Author: ddarko $

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2008-08-12 Darko Kolakovic
 */

/* Group=USB ID                                                              */

#ifndef _USBVID0839_H_
  //$Workfile: UsbVid0839.h$ sentry
  #define _USBVID0839_H_

/*2105.	USB device vendor identification (VID) number	Samsung Tecwin Co., Ltd	http://www.samsungtechwin.com/

  See also: usb-if.tsv (usb.if), Company List by USB Implementers Forum, Inc
  (USB-IF) at http://www.usb.org/developers/tools/comp_dump;
  usb.ids, List of USB ID's by Stephen J. Gowdy at http://www.linux-usb.org/usb.ids.
 */
#define USBVID_SAMSUNGTECWIN 0x0839
#define USBVID_0839 _T("Samsung Tecwin Co., Ltd") //VID 2105 Vendor name

#define USBPID_DIGIMAX    0x0005 //Samsung Digimax Digital Camera
#define USBPID_DIGIMAX230 0x0008 //Samsung Digimax 230 Digital Camera
#define USBPID_DIGIMAX340 0x0009 //Samsung Digimax 340 Digital Camera
#define USBPID_DIGIMAX410 0x000A //Samsung Digimax 410 Digital Camera
#define USBPID_DIGIMAX360 0x000E //Samsung Digimax 360 Digital Camera
#define USBPID_DIGIMAX300 0x0010 //Samsung Digimax 300 Digital Camera
#define USBPID_DIGIMAX55  0x004A /*Samsung Digimax L55W Digital Camera
                                   Model Number STP1-55 USB Mass Storage Device*/
#define USBPID_DIGIMAX210 0x1003 //Samsung Digimax 210SE Digital Camera
#define USBPID_DIGIMAX220 0x1005 //Samsung Digimax 220 Digital Camera
#define USBPID_DIGIMAX_V4 0x1009 //Samsung Digimax V4 Digital Camera
#define USBPID_TECWIN6500 0x1012 //6500 Document Camera
#define USBPID_TECWINS730 0x1058 //S730 Digital Camera
#define USBPID_DIGIMAX50  0x1542 //Samsung Digimax 50 Duo Digital Camera
#define USBPID_DIGIMAX35  0x3000 //Samsung Digimax 35 MP3 Digital Camera

///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID0839_H_
/*****************************************************************************
 * $Log: UsbVid0839.h,v $
 * Revision 1.2  2008/08/12 18:55:45  ddarko
 * *** empty log message ***
 *
 * Revision 1.1  2008/08/12 18:54:17  ddarko
 * Created
 *
 *****************************************************************************/
