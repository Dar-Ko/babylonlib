/*$RCSfile: UsbVid050D.h,v $: header file
  $Revision: 1.2 $ $Date: 2009/07/30 17:08:32 $
  $Author: ddarko $

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2009-05-05 Darko Kolakovic
 */

/* Group=USB ID                                                              */

#ifndef _USBVID050D_H_
  //$RCSfile: UsbVid050D.h,v $ sentry
  #define _USBVID050D_H_

/*1293.	USB device vendor identification (VID) number	Belkin International, Inc.	http://www.belkin.com/

  See also: usb-if.tsv (usb.if), Company List by USB Implementers Forum, Inc
  (USB-IF) at http://www.usb.org/developers/tools/comp_dump;
  usb.ids, List of USB ID's by Stephen J. Gowdy at http://www.linux-usb.org/usb.ids.
 */
#define USBVID_BELKIN 0x050D
#define USBVID_050D _T("Belkin Components") //VID 1293 Vendor name

#define USBPID_DIRECTCONNECT                      0x0004  //Direct Connect
#define USBPID_BLUETOOTHF8T012                    0x0012  //F8T012 Bluetooth Adapter
#define USBPID_BLUETOOTHF8T013                    0x0013  //F8T013 Bluetooth Adapter
#define USBPID_WIRELESSF5D6050                    0x0050  //F5D6050 802.11b Wireless Adapter
#define USBPID_BLUETOOTHF8T001V2                  0x0081  //F8T001v2 Bluetooth
#define USBPID_BLUETOOTHDEVICE                    0x0083  //Bluetooth Device
#define USBPID_BLUETOOTHF8T003V2                  0x0084  //F8T003v2 Bluetooth
#define USBPID_KVMFLIP                            0x0102  //Flip KVM
#define USBPID_SERIALF5U103ETEK                   0x0103  //F5U103 Serial Adapter [etek]
#define USBPID_VIDEOBUSII                         0x0106  //VideoBus II Adapter, Video
#define USBPID_KVMF1DE108B                        0x0108  //F1DE108B KVM
#define USBPID_PDAF5U109                          0x0109  //F5U109/F5U409 PDA Adapter
#define USBPID_SCSIADAPTER                        0x0115  //SCSI Adapter
#define USBPID_SERIALF5U120PCDUALPS2              0x0119  //F5U120-PC Dual PS/2 Ports
#define USBPID_ETHERNETF5D5050                    0x0121  //F5D5050 100Mbps Ethernet
#define USBPID_ETHERNETADAPTER                    0x0122  //Ethernet Adapter
#define USBPID_BLUETOOTHTRACEFILTER               0x0131  //Bluetooth Device with trace filter
#define USBPID_BLUETOOTHMINIDONGLE                0x016A //Bluetooth Mini Dongle
#define USBPID_PERIPHERALSWITCH                   0x0201  //Peripheral Switch
#define USBPID_USBVIEWIINT1004                    0x0208  //USBView II Video Adapter [nt1004]
#define USBPID_DVDF5U228HISPEED                   0x0210  //F5U228 Hi-Speed USB 2.0 DVD Creator
#define USBPID_READERF5U211                       0x0211  //F5U211 USB 2.0 15-in-1 Media Reader & Writer
#define USBPID_USBHUBF5U224                       0x0224  //F5U224 USB 2.0 4-Port Hub
#define USBPID_USBHUBF5U234                       0x0234  //F5U234 USB 2.0 4-Port Hub
#define USBPID_USBHUBF5U237                       0x0237  //F5U237 USB 2.0 7-Port Hub
#define USBPID_CARDREADER_F5U240                  0x0240  //F5U240 USB 2.0 CF Card Reader
#define USBPID_FLASHMEDIAUSB2                     0x0249 //USB 2 Flash Media Device
#define USBPID_SERIALF5U257                       0x0257  //F5U257 Serial
#define USBPID_SERIALF5U409                       0x0409  //F5U409 Serial
#define USBPID_USBHUB7PORT                        0x0416  //External powered USB 2.0 7 port Hub
#define USBPID_UPSF6C550AVR                       0x0551  //F6C550-AVR UPS
#define USBPID_GAMEPADNOSTROMON40                 0x0802  //Nostromo n40 Gamepad
#define USBPID_GAMEPADNOSTROMO1745                0x0803  //Nostromo 1745 GamePad
#define USBPID_GAMEPADNOSTROMON50                 0x0805  //Nostromo N50 GamePad
#define USBPID_MOUSENOSTROMON52HIDSPEEDPADWHEEL   0x0815  //Nostromo n52 HID SpeedPad Mouse Wheel
#define USBPID_MOUSEERGOFITWIRELESSOPTICALHID     0x0826  //ErgoFit Wireless Optical Mouse (HID)
#define USBPID_UPSHIDBATTERY                      0x0980  //HID UPS Battery
#define USBPID_PARALLELF5U120PCT                  0x1202  //F5U120-PC Parallel Printer Port
#define USBPID_SERIALF5U120PC                     0x1203  //F5U120-PC Serial Port
#define USBPID_F5U258HOSTTOHOSTCABLE              0x258A  //F5U258 Host to Host cable
#define USBPID_HUBF1DFG102UFLIP                   0x3101  //F1DF102U/F1DG102U Flip Hub
#define USBPID_KVMF1DFG102UFLIP                   0x3201  //F1DF102U/F1DG102U Flip KVM
#define USBPID_ZD1211B                            0x4050  //ZD1211B
#define USBPID_F5D5055                            0x5055  //F5D5055
#define USBPID_NETWORK11MBPSWIRELESS              0x6051  //11Mbps Wireless Network Adapter
#define USBPID_F5D7050VER1000WIFI                 0x7050  //F5D7050 ver 1000 WiFi
#define USBPID_NETWORKF5D705154GUSB               0x7051  //F5D7051 54g USB Network Adapter
#define USBPID_WIRELESSF5D7050A                   0x705A  //F5D7050A Wireless Adapter
#define USBPID_WIRELESSG                          0x705B  //Wireless G Adapter
#define USBPID_WIRELESSF5D7050V4000               0x705C  //F5D7050 v4000 Wireless Adapter
#define USBPID_WIRELESSF5D9050VER3                0x905B  //F5D9050 ver 3 Wireless Adapter
#define USBPID_WIRELESSGPLUSMIMO                  0x905C  //Wireless G Plus MIMO Network Adapter

///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID050D_H_
/*****************************************************************************
 * $Log: UsbVid050D.h,v $
 * Revision 1.2  2009/07/30 17:08:32  ddarko
 * Updated
 *
 * Revision 1.1  2009/05/11 15:21:15  ddarko
 * Added Belkin International, Inc.
 *
 *****************************************************************************/

