/*$RCSfile: UsbVid05E3.h,v $: header file
  $Revision: 1.2 $ $Date: 2012/02/22 14:53:06 $
  $Author: ddarko $

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2009-08-24 Darko Kolakovic
 */

/* Group=USB ID                                                              */

#ifndef _USBVID05E3_H_
  //$RCSfile: UsbVid05E3.h,v $ sentry
  #define _USBVID05E3_H_

/*1507.	USB device vendor identification (VID) number	Genesys Logic, Inc.	http://www.genesyslogic.com

  See also: usb-if.tsv (usb.if), Company List by USB Implementers Forum, Inc
  (USB-IF) at http://www.usb.org/developers/tools/comp_dump;
  usb.ids, List of USB ID's by Stephen J. Gowdy at http://www.linux-usb.org/usb.ids.
 */
#define USBVID_GENESYSLOGIC 0x05E3
#define USBVID_05E3 _T("Genesys Logic, Inc.") //VID 1507 Vendor name

#define USBPID_KBD_GLPS2                 0x000A //Keyboard with PS/2 Port
#define USBPID_MOUSE_GLB                 0x000B //Mouse
#define USBPID_NINTENDOGAMEBOYADVANCESP  0x0100 //Nintendo Game Boy Advance SP
#define USBPID_SCANPACIFICIMAGE1800U     0x0120 //Pacific Image Electronics PrimeFilm 1800u slide/negative scanner
#define USBPID_CARD_CFSM_RW              0x0131 //CF/SM Reader/Writer
#define USBPID_SCANMULTIPLESLIDES3600    0x0142 //Multiple Slides Scanner-3600
#define USBPID_SCANMULTIPLEFRAMESFILM36X 0x0143 //Multiple Frames Film Scanner-36 series
#define USBPID_SCANPLUSTEK               0x0180 //Plustek Scanner
#define USBPID_WIZEMEDIA1000             0x0182 //Wize Media 1000
#define USBPID_SCANJET4600X              0x0189 //ScanJet 4600 series
#define USBPID_XEROX6400                 0x018A //Xerox 6400
#define USBPID_GLUSB98PT_LPT             0x0300 //GLUSB98PT Parallel Port
#define USBPID_USB2LPT_REL2              0x0301 //USB2LPT Cable Release2
#define USBPID_HUB_GL6                   0x0406 //Hub
#define USBPID_GL620H2H                  0x0501 //GL620USB Host-Host interface
#define USBPID_GL620GENELINK             0x0502 //GL620USB-A GeneLink USB-USB Bridge
#define USBPID_KBDHIDFILTER              0x0504 //HID Keyboard Filter
#define USBPID_HUB_GLUSB11B              0x0604 //USB 1.1 Hub
#define USBPID_HUB_GLUSB20EDNET          0x0605 //USB 2.0 Hub [ednet]
#define USBPID_HUB_HUBDLINKDUBH4         0x0606 //USB 2.0 Hub / D-Link DUB-H4 USB 2.0 Hub
#define USBPID_HUB_GLUSB20_4PORT         0x0608 //USB-2.0 4-Port Laptop hub
#define USBPID_HUB_GLUSB20               0x0660 //USB 2.0 Hub
#define USBPID_CARD_CFSIIG_US2256        0x0700 //SIIG US2256 CompactFlash Card Reader
#define USBPID_HUB_GLUSB20IDE            0x0701 //USB 2.0 IDE Adapter
#define USBPID_HUB_GLUSB20IDE2           0x0702 //USB 2.0 IDE Adapter
#define USBPID_CARD_GLREADER3            0x0703 //Card Reader
#define USBPID_CARD_GLREADER4            0x0704 //Card Reader
#define USBPID_CARD_GLREADER5            0x0705 //Card Reader
#define USBPID_CARD_GLREADER6            0x0706 //Card Reader
#define USBPID_CARD_GLREADER7            0x0707 //Card Reader
#define USBPID_CARD_GLREADER8            0x0708 //Card Reader
#define USBPID_CARD_GLREADER9            0x0709 //Card Reader
#define USBPID_GLPENFLASHA               0x070A //Pen Flash storage
#define USBPID_DMHS1B_DFU                0x070B //DMHS1B Rev 3 DFU Adapter
#define USBPID_CARD_XPROCR20XA           0x070E //X-PRO CR20xA USB 2.0 Internal Card Reader
#define USBPID_GLPENFLASHF               0x070F //Pen Flash
#define USBPID_CARD_GL33IN1              0x0710 //USB 2.0 33-in-1 Card Reader
#define USBPID_CARD_GLREADER11           0x0711 //Card Reader
#define USBPID_STORAGEDELKIN             0x0712 //Delkin Mass Storage Device
#define USBPID_MICROSDREADER             0x0715 //USB 2.0 microSD Reader
#define USBPID_CARD_GLRW60               0x0760 //USB 2.0 Card Reader/Writer
#define USBPID_STORAGEGENESYS            0x0761 //Genesys Mass Storage Device
#define USBPID_USBFSDFU                  0x0780 //USBFS DFU Adapter
#define USBPID_GLPENFLASHA0              0x07A0 //Pen Flash ?? (is this same as 070A?)
#define USBPID_CARD_GLREADER27           0x0927 //Card Reader
#define USBPID_MOUSEAFILIASH3003         0x1205 //Afilias Optical Mouse H3003
#define USBPID_GLPENFLASH00              0xA700 //Pen Flash
#define USBPID_VX7012TV2                 0xF102 //VX7012 TV Box
#define USBPID_VX7012TV3                 0xF103 //VX7012 TV Box (??)
#define USBPID_VX7012TV4                 0xF104 //VX7012 TV Box
#define USBPID_3MTL20TEMPLOGGER          0xFD21 //3M TL20 Temperature Logger
#define USBPID_MOUSERAZER                0xFE00 //Razer Mouse

///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID05E3_H_
/*****************************************************************************
 * $Log: UsbVid05E3.h,v $
 * Revision 1.2  2012/02/22 14:53:06  ddarko
 * Update
 *
 * Revision 1.1  2009/08/25 21:26:34  ddarko
 * *** empty log message ***
 *
 *****************************************************************************/
