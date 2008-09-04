/*$Workfile: UsbVid413C.h$: header file
  $Revision: 1$ $Date: 22/08/2007 10:51:35 AM$
  $Author: Darko Kolakovic$

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2007-08-17 Darko Kolakovic
 */

/* Group=USB ID                                                              */

#ifndef _USBVID413C_H_
  //$Workfile: UsbVid413C.h$ sentry
  #define _USBVID413C_H_

/*16700.	USB device vendor identification (VID) number	Dell Computer Corp.	http://www.dell.com

  See also: usb-if.tsv, USB Implementers Forum, Inc (USB-IF) at http://www.usb.org
 */
#define USBVID_DELL 0x413C
#define USBVID_413C _T("Dell Inc") //VID 16700 Vendor name

#define USBPID_PORTREPLICATOR                        0x0058 //Port Replicator
#define USBPID_KBDHUBDELL1                           0x1001 //Keyboard Hub
#define USBPID_KBDHUBDELL2                           0x1002 //Keyboard Hub
#define USBPID_KBDHIDSUPPORT                         0x2001 //Keyboard HID Support
#define USBPID_SK8125                                0x2002 //SK-8125 Keyboard
#define USBPID_KBDDELL                               0x2003 //Keyboard
#define USBPID_RT7D50KBD                             0x2005 //RT7D50 Keyboard
#define USBPID_SK3106                                0x2100 //SK-3106 Keyboard
#define USBPID_DELLSCRD                              0x2101 //SmartCard Reader Keyboard
#define USBPID_DRAC4RAC                              0x2500 //DRAC4 Remote Access Card
#define USBPID_DELLMOUSEOW                           0x3010 //Optical Wheel Mouse
#define USBPID_MOUSEDELL                             0x3200 //Dell Mouse
#define USBPID_AXIMX5                                0x4001 //Axim X5
#define USBPID_AXIMX3                                0x4002 //Axim X3
#define USBPID_AXIMX30                               0x4003 //Axim X30
#define USBPID_AXIMSYNC4                             0x4004 //Axim Sync
#define USBPID_AXIMSYNC5                             0x4005 //Axim Sync
#define USBPID_AXIMSYNC6                             0x4006 //Axim Sync
#define USBPID_AXIMSYNC7                             0x4007 //Axim Sync
#define USBPID_AXIMSYNC8                             0x4008 //Axim Sync
#define USBPID_AXIMSYNC9                             0x4009 //Axim Sync
#define USBPID_PRTAIOA940                            0x5103 //AIO Printer A940
#define USBPID_PRTAIOA920                            0x5105 //AIO Printer A920
#define USBPID_PRTAIOA960                            0x5107 //AIO Printer A960
#define USBPID_PRTPHOTOAIO922                        0x5109 //Photo AIO Printer 922
#define USBPID_PRTPHOTOAIO962                        0x5110 //Photo AIO Printer 962
#define USBPID_PRTPHOTOAIO942                        0x5111 //Photo AIO Printer 942
#define USBPID_PRTPHOTOAIO924                        0x5112 //Photo AIO Printer 924
#define USBPID_PRTPHOTOAIO944                        0x5113 //Photo AIO Printer 944
#define USBPID_PRTPHOTOAIO964                        0x5114 //Photo AIO Printer 964
#define USBPID_PRTPHOTOAIO926                        0x5115 //Photo AIO Printer 926
#define USBPID_PRTAIO946                             0x5116 //AIO Printer 946
#define USBPID_PRTPHOTOAIO966                        0x5117 //Photo AIO Printer 966
#define USBPID_AIO810                                0x5118 //AIO 810
#define USBPID_LASERMFP1815                          0x5124 //Laser MFP 1815
#define USBPID_PHOTOAIO928                           0x5128 //Photo AIO 928
#define USBPID_PRTLASERDELL1                         0x5200 //Laser Printer
#define USBPID_PRINTINGSUPPORT1                      0x5202 //Printing Support
#define USBPID_PRINTINGSUPPORT2                      0x5203 //Printing Support
#define USBPID_PRINTINGSUPPORT3                      0x5210 //Printing Support
#define USBPID_PRINTINGSUPPORT4                      0x5211 //Printing Support
#define USBPID_LASERMFP1600N                         0x5220 //Laser MFP 1600n
#define USBPID_PRINTINGSUPPORT                       0x5225 //Printing Support
#define USBPID_PRINTINGSUPPORT                       0x5226 //Printing Support
#define USBPID_PRTLASERDELL2                         0x5300 //Laser Printer
#define USBPID_PRTLASERDELL3                         0x5400 //Laser Printer
#define USBPID_PRTLASERDELL4                         0x5401 //Laser Printer
#define USBPID_PRTLASER3100CN                        0x5601 //Laser Printer 3100cn
#define USBPID_PRTLASER3000CN                        0x5602 //Laser Printer 3000cn
#define USBPID_PRTLASER5100CN                        0x5631 //Laser Printer 5100cn
#define USBPID_PRINTINGSUPPORT5                      0x5905 //Printing Support
#define USBPID_BTBC02USBADAPTER                      0x8000 //BC02 Bluetooth USB Adapter
#define USBPID_BTTRUEMOBILEMODULEIN                  0x8010 //TrueMobile Bluetooth Module in
#define USBPID_TRUEMOBILE1300WLANCARD                0x8102 //TrueMobile 1300 USB2.0 WLAN Card
#define USBPID_1450DUAL_BAND                         0x8104 //Wireless 1450 Dual-band (802.11a/b/g) USB2.0 Adapter
#define USBPID_U2HID                                 0x8105 //U2 in HID - Driver
#define USBPID_WIRELESS350BTIN                       0x8106 //Wireless 350 Bluetooth Internal Card in
#define USBPID_WIRELESS3XXBT                         0x8110 //Wireless 3xx Bluetooth Internal Card
#define USBPID_WIRELESS3XXBTIN                       0x8111 //Wireless 3xx Bluetooth Internal Card in
#define USBPID_WIRELESS5700MODEM                     0x8114 //Wireless 5700 Mobile Broadband (CDMA EV-DO) Minicard Modem
#define USBPID_WIRELESS5500MODEM                     0x8115 //Wireless 5500 Mobile Broadband (3G HSDPA) Minicard Modem
#define USBPID_WIRELESS5505MODEM                     0x8116 //Wireless 5505 Mobile Broadband (3G HSDPA) Minicard Modem
#define USBPID_WIRELESS5700MODEM                     0x8117 //Wireless 5700 Mobile Broadband (CDMA EV-DO) Expresscard Modem
#define USBPID_WIRELESS5510STATUSPORT                0x8118 //Wireless 5510 Mobile Broadband (3G HSDPA) Expresscard Status Port
#define USBPID_BTADAPTERDELL                         0x8120 //Bluetooth adapter
#define USBPID_EASTFOLDHID                           0x8121 //Eastfold in HID
#define USBPID_EASTFOLDDFU                           0x8122 //Eastfold in DFU
#define USBPID_EHOMEINFRAREDRECEIVER1                0x8123 //eHome Infrared Receiver
#define USBPID_EHOMEINFRAREDRECEIVER2                0x8124 //eHome Infrared Receiver
#define USBPID_WIRELESS355BT                         0x8126 //Wireless 355 Bluetooth
#define USBPID_WIRELESS355BT_EDR                     0x8127 //Wireless 355 Module with Bluetooth 2.0 + EDR Technology.
#define USBPID_WIRELESS5700_SPRINTSTATUSPORT         0x8128 //Wireless 5700-Sprint Mobile Broadband (CDMA EV-DO) Mini-Card Status Port
#define USBPID_WIRELESS5700_TELUSSTATUSPORT          0x8129 //Wireless 5700-Telus Mobile Broadband (CDMA EV-DO) Mini-Card Status Port
#define USBPID_WIRELESS360BT_EDR                     0x8131 //Wireless 360 Bluetooth 2.0 + EDR module.
#define USBPID_WIRELESS5720_VZWGPSPORT               0x8133 //Wireless 5720 VZW Mobile Broadband (EVDO Rev-A) Minicard GPS Port
#define USBPID_WIRELESS5720_SPRINTSTATUSPORT         0x8134 //Wireless 5720 Sprint Mobile Broadband (EVDO Rev-A) Minicard Status Port
#define USBPID_WIRELESS5720_TELUSDIAGNOSTICSPORT     0x8135 //Wireless 5720 TELUS Mobile Broadband (EVDO Rev-A) Minicard Diagnostics Port
#define USBPID_WIRELESS5520_CINGULARDIAGNOSTICSPORT  0x8136 //Wireless 5520 Cingular Mobile Broadband (3G HSDPA) Minicard Diagnostics Port
#define USBPID_WIRELESS5520_VODALSTATUSPORT          0x8137 //Wireless 5520 Voda L Mobile Broadband (3G HSDPA) Minicard Status Port
#define USBPID_WIRELESS5520_VODAIEAPPORT             0x8138 //Wireless 5520 Voda I Mobile Broadband (3G HSDPA) Minicard EAP-SIM Port
#define USBPID_WIRELESS360BT                         0x8140 //Wireless 360 Bluetooth
#define USBPID_MOBILE360DFU                          0x8142 //Mobile 360 in DFU
#define USBPID_TRUMOB1180                            0x8100 //TrueMobile 1180 802.11b Adapter
#define USBPID_WIRE350BT                             0x8103 //Wireless 350 Bluetooth
#define USBPID_BTADAPTERDELL                         0x8501 //Bluetooth Adapter
#define USBPID_DELLHUB                               0xA001 //Hub
#define USBPID_HUBINTERNAL2DELL                      0xA005 //Internal 2.0 Hub
#define USBPID_DELLHUB1905                           0xA700 //Hub (in 1905FP LCD Monitor)

///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID413C_H_
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         22/08/2007 10:51:35 AMDarko Kolakovic
 * $
 *****************************************************************************/
