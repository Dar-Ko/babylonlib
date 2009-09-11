/*$RCSfile: UsbVid05DC.h,v $: header file
  $Revision: 1.2 $ $Date: 2009/09/11 20:03:25 $
  $Author: ddarko $

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2007-08-17 Darko Kolakovic
 */

/* Group=USB ID                                                              */

#ifndef _USBVID05DC_H_
  //$RCSfile: UsbVid05DC.h,v $ sentry
  #define _USBVID05DC_H_

/*1500.	USB device vendor identification (VID) number	Lexar Media, Inc.	http://www.lexar.com/

  See also: usb-if.tsv (usb.if), Company List by USB Implementers Forum, Inc
  (USB-IF) at http://www.usb.org/developers/tools/comp_dump;
  usb.ids, List of USB ID's by Stephen J. Gowdy at http://www.linux-usb.org/usb.ids.
 */
#define USBVID_LEXAR 0x05DC
#define USBVID_05DC _T("Lexar Media, Inc.") //VID 1500 Vendor name

#define USBPID_JUMPSHOT1                   0x0001 //JumpShot Compact Flash Reader
#define USBPID_JUMPSHOT2                   0x0002 //JumpShot
#define USBPID_JUMPSHOT3                   0x0003 //JumpShot
#define USBPID_JD64MB                      0x0080 //Jumpdrive Secure 64MB
#define USBPID_FLASHDRIVERBCCOMPACT        0x0081 //RBC Compact Flash Drive
#define USBPID_JDIMPACT                    0x00A7 //JumpDrive Impact
#define USBPID_JDPRO                       0x0100 //JumpDrive PRO
#define USBPID_JDPRO2                      0x0200 //JumpDrive 2.0 Pro
#define USBPID_JDGEYSR                     0x0300 //Jumpdrive Geysr
#define USBPID_JDCLASSIC                   0x0301 //JumpDrive Classic
#define USBPID_JDMICRO                     0x0302 //JumpDrive Micro
#define USBPID_JDMICROPRO                  0x0303 //JumpDrive Micro Pro
#define USBPID_JDSECUREII                  0x0304 //JumpDrive Secure II
#define USBPID_JD310                       0x0310 //JumpDrive
#define USBPID_JDCLASSIC11                 0x0311 //JumpDrive Classic
#define USBPID_JDMICRO12                   0x0312 //JumpDrive Micro
#define USBPID_JDMICROPRO13                0x0313 //JumpDrive Micro Pro
#define USBPID_JD20                        0x0320 //JumpDrive
#define USBPID_JDMICRO21                   0x0321 //JumpDrive Micro
#define USBPID_JDMICROPRO22                0x0322 //JumpDrive Micro Pro
#define USBPID_UFC                         0x0323 //UFC
#define USBPID_JDEXPRESSION                0x0330 //JumpDrive Expression
#define USBPID_JDTAD                       0x0340 //JumpDrive TAD
#define USBPID_EXPRESS CARD                0x0350 //Express Card
#define USBPID_UFDC400                     0x0400 //USB Flash Drive Card (UFDC)
#define USBPID_UFDC401                     0x0401 //USB Flash Drive Card (UFDC)
#define USBPID_LEXARB                       0x0403 //Locked B Device ??
#define USBPID_LEXARC                       0x0405 //Locked C Device ??
#define USBPID_LEXARD                       0x0407 //Locked D Device
#define USBPID_LEXARE                       0x0409 //Locked E Device
#define USBPID_LEXARF                       0x040B //Locked F Device
#define USBPID_LEXARG                       0x040D //Locked G Device
#define USBPID_LEXARH                       0x040F //Locked H Device
#define USBPID_JD410                       0x0410 //JumpDrive
#define USBPID_JD411                       0x0411 //JumpDrive
#define USBPID_LEXARJ                       0x0413 //Locked J Device
#define USBPID_LEXARK                       0x0415 //Locked K Device
#define USBPID_LEXARL                       0x0417 //Locked L Device
#define USBPID_LEXARM                       0x0419 //Locked M Device
#define USBPID_LEXARN                       0x041B //Locked N Device
#define USBPID_LEXARO                       0x041D //Locked O Device
#define USBPID_LEXARP                       0x041F //Locked P Device
#define USBPID_JD420                       0x0420 //JumpDrive
#define USBPID_JD421                       0x0421 //JumpDrive
#define USBPID_LEXARR                       0x0423 //Locked R Device
#define USBPID_LEXARS                       0x0425 //Locked S Device
#define USBPID_LEXART                       0x0427 //Locked T Device
#define USBPID_LEXARU                       0x0429 //Locked U Device
#define USBPID_LEXARV                       0x042B //Locked V Device
#define USBPID_LEXARW                       0x042D //Locked W Device
#define USBPID_LEXARX                       0x042F //Locked X Device
#define USBPID_LEXARY                       0x0431 //Locked Y Device
#define USBPID_LEXARZ                       0x0433 //Locked Z Device
#define USBPID_MP3PLAYERD02                0x4D02 //MP3 Player
#define USBPID_MP3PLAYERD12                0x4D12 //MP3 Player
#define USBPID_MP3PLAYERD30                0x4D30 //MP3 Player
#define USBPID_JUMPDRIVE2                  0xA300 //JumpDrive2
#define USBPID_JDPRO40_501                 0xA400 //JumpDrive trade; Pro 40-501
#define USBPID_JD128_256MB                 0xA410 //JumpDrive 128MB/256MB
#define USBPID_JDTRAVELER                  0xA411 //JumpDrive Traveler
#define USBPID_JDPRO420                    0xA420 //JumpDrive Pro
#define USBPID_JDPROII421                  0xA421 //JumpDrive Pro II
#define USBPID_JDMICROPRO422               0xA422 //JumpDrive Micro Pro
#define USBPID_JDSECURE430                 0xA430 //JumpDrive Secure
#define USBPID_JDSECUREII431               0xA431 //JumpDrive Secure II
#define USBPID_JDCLASSIC432                0xA432 //JumpDrive Classic
#define USBPID_JDLIGHTNING                 0xA440 //JumpDrive Lightning
#define USBPID_JDTOUCHGUARD                0xA450 //JumpDrive TouchGuard
#define USBPID_JDMERCURY                   0xA460 //JD Mercury
#define USBPID_JDCLASSIC501                0xA501 //JumpDrive Classic
#define USBPID_JDSPORT                     0xA510 //JumpDrive Sport
#define USBPID_JDEXPRESSION530             0xA530 //JumpDrive Expression
#define USBPID_JDSECUREII531               0xA531 //JumpDrive Secure II
#define USBPID_JDFIREFLY550                0xA560 //JumpDrive FireFly
#define USBPID_JDFIREFLY701                0xA701 //JumpDrive FireFly
#define USBPID_FLASH_JD8GB                 0xA793 //JumpDrive 8GB Retrax Hi-Speed Flash Drive
#define USBPID_CARD_LEXARREADER            0xB002 //USB Card Flash Reader
#define USBPID_CARD_LEXARMULTI R           0xB018 //Multi-Card Reader

///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID05DC_H_
/*****************************************************************************
 * $Log: UsbVid05DC.h,v $
 * Revision 1.2  2009/09/11 20:03:25  ddarko
 * *** empty log message ***
 *
 * Revision 1.1  2009/09/09 20:35:51  ddarko
 * Lexar Media
 *
 *****************************************************************************/
