/*$RCSfile: UsbVid04B0.h,v $: header file
  $Revision: 1.1 $ $Date: 2009/08/24 17:47:43 $
  $Author: ddarko $

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2009-08-24 Darko Kolakovic
 */

/* Group=USB ID                                                              */

#ifndef _USBVID04B0_H_
  //$RCSfile: UsbVid04B0.h,v $ sentry
  #define _USBVID04B0_H_

/*1200.	USB device vendor identification (VID) number	Nikon Corporation	http://www.nikon.com/

  See also: usb-if.tsv (usb.if), Company List by USB Implementers Forum, Inc
  (USB-IF) at http://www.usb.org/developers/tools/comp_dump;
  usb.ids, List of USB ID's by Stephen J. Gowdy at http://www.linux-usb.org/usb.ids.
 */
#define USBVID_NIKON 0x04B0
#define USBVID_04B0 _T("Nikon Corporation") //VID 1200 Vendor name

#define USBPID_COOLPIX990       0x0102 //Coolpix 990
#define USBPID_COOLPIX880       0x0103 //Coolpix 880
#define USBPID_COOLPIX995       0x0104 //Coolpix 995
#define USBPID_COOLPIX775       0x0106 //Coolpix 775
#define USBPID_COOLPIX5000      0x0107 //Coolpix 5000
#define USBPID_COOLPIX2500      0x0108 //Coolpix 2500
#define USBPID_COOLPIX2500_PTP  0x0109 //Coolpix 2500 picture transfer protocol mode
#define USBPID_COOLPIX4500      0x010A //Coolpix 4500
#define USBPID_COOLPIX4500_PTP  0x010B //Coolpix 4500 picture transfer protocol mode
#define USBPID_COOLPIX5700_PTP  0x010D //Coolpix 5700 picture transfer protocol mode
#define USBPID_COOLPIX4300      0x010E //Coolpix 4300 mass storage mode
#define USBPID_COOLPIX4300_PTP  0x010F //Coolpix 4300 picture transfer protocol mode
#define USBPID_COOLPIX3500      0x0110 //Coolpix 3500 (Sierra Mode)
#define USBPID_COOLPIX3500_PTP  0x0111 //Coolpix 3500 picture transfer protocol mode
#define USBPID_COOLPIX885_PTP   0x0112 //Coolpix 885 picture transfer protocol mode
#define USBPID_COOLPIX5000_PTP  0x0113 //Coolpix 5000 picture transfer protocol mode
#define USBPID_COOLPIX3100      0x0114 //Coolpix 3100 mass storage mode
#define USBPID_COOLPIX3100_PTP  0x0115 //Coolpix 3100 picture transfer protocol mode
#define USBPID_COOLPIX2100_PTP  0x0117 //Coolpix 2100 picture transfer protocol mode
#define USBPID_COOLPIX5400_PTP  0x0119 //Coolpix 5400 picture transfer protocol mode
#define USBPID_COOLPIX3700_PTP  0x011D //Coolpix 3700 picture transfer protocol mode
#define USBPID_COOLPIX3200_PTP  0x0121 //Coolpix 3200 picture transfer protocol mode
#define USBPID_COOLPIX2200_PTP  0x0122 //Coolpix 2200 picture transfer protocol mode
#define USBPID_COOLPIX8400      0x0124 //Coolpix 8400 mass storage mode
#define USBPID_COOLPIX8400_PTP  0x0125 //Coolpix 8400 picture transfer protocol mode
#define USBPID_COOLPIX8800      0x0126 //Coolpix 8800
#define USBPID_COOLPIX4800_PTP  0x0129 //Coolpix 4800 picture transfer protocol mode
#define USBPID_COOLPIX4100      0x012C //Coolpix 4100 mass storage mode
#define USBPID_COOLPIX4100_PTP  0x012D //Coolpix 4100 picture transfer protocol mode
#define USBPID_COOLPIX5600_PTP  0x012E //Coolpix 5600 picture transfer protocol mode
#define USBPID_COOLPIX4600_PTP  0x0130 //Coolpix 4600 picture transfer protocol mode
#define USBPID_COOLPIX5900_PTP  0x0135 //Coolpix 5900 picture transfer protocol mode
#define USBPID_COOLPIX7900      0x0136 //Coolpix 7900 mass storage mode
#define USBPID_COOLPIX7900_PTP  0x0137 //Coolpix 7900 picture transfer protocol mode
#define USBPID_COOLPIX100       0x013A //Coolpix 100 mass storage mode
#define USBPID_COOLPIX100_PTP   0x013B //Coolpix 100 picture transfer protocol mode
#define USBPID_COOLPIXP2        0x0141 //Coolpix P2 mass storage mode
#define USBPID_COOLPIXP2_PTP    0x0142 //Coolpix P2 picture transfer protocol mode
#define USBPID_COOLPIXP5100_PTP 0x0163 //Coolpix P5100 picture transfer protocol mode
#define USBPID_COOLPIXP50_PTP   0x0169 //Coolpix P50 picture transfer protocol mode
#define USBPID_COOLPIXS210      0x016E //Coolpix S210 picture transfer protocol mode
#define USBPID_COOLPIXSQ_PTP    0x0202 //Coolpix SQ picture transfer protocol mode
#define USBPID_COOLPIX4200      0x0203 //Coolpix 4200 mass storage mode
#define USBPID_COOLPIX4200_PTP  0x0204 //Coolpix 4200 picture transfer protocol mode
#define USBPID_COOLPIX5200      0x0205 //Coolpix 5200 mass storage mode
#define USBPID_COOLPIX5200_PTP  0x0206 //Coolpix 5200 picture transfer protocol mode
#define USBPID_COOLPIX2000      0x0301 //Coolpix 2000 mass storage mode
#define USBPID_COOLPIX2000_PTP  0x0302 //Coolpix 2000 picture transfer protocol mode
#define USBPID_DSCD100_PTP      0x0402 //DSC D100 picture transfer protocol mode
#define USBPID_D2H              0x0403 //D2H mass storage mode
#define USBPID_D2HSLR_PTP       0x0404 //D2H SLR picture transfer protocol mode
#define USBPID_DSCD70           0x0405 //D70 mass storage mode
#define USBPID_DSCD70_PTP       0x0406 //DSC D70 picture transfer protocol mode
#define USBPID_D2XSLR_PTP       0x0408 //D2X SLR picture transfer protocol mode
#define USBPID_D50              0x0409 //D50 digital camera
#define USBPID_D50_PTP          0x040A //D50 picture transfer protocol mode
#define USBPID_D2HS             0x040C //D2Hs digital camera
#define USBPID_DSCD70S_PTP      0x040E //DSC D70s picture transfer protocol mode
#define USBPID_D200             0x040F //D200 mass storage mode
#define USBPID_D200_PTP         0x0410 //D200 picture transfer protocol mode
#define USBPID_D40              0x0413 //D40 mass storage mode
#define USBPID_D700_PTP         0x0422 //D700 picture transfer protocol mode
#define USBPID_COOLSCANLS40ED   0x4000 //Coolscan LS 40 ED
#define USBPID_COOLSCANLS50ED   0x4001 //Coolscan V LS 50 ED
#define USBPID_LS5000ED         0x4002 //Super Coolscan LS-5000 ED

///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID04B0_H_
/*****************************************************************************
 * $Log: UsbVid04B0.h,v $
 * Revision 1.1  2009/08/24 17:47:43  ddarko
 * Created
 *
 *****************************************************************************/
