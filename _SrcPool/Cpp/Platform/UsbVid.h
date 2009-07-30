/*$RCSfile: UsbVid.h,v $: header file
  $Revision: 1.3 $ $Date: 2009/07/30 17:08:32 $
  $Author: ddarko $

  Universal Serial Bus (USB) vendor device identification (VID) list
  Copyright: CommonSoft Inc.
  2008-09-29 Darko Kolakovic
 */

/* Group=USB ID                                                              */

#ifndef _USBVID_H_
  //$RCSfile: UsbVid.h,v $ sentry
  #define _USBVID_H_

/*List of known USB device vendor identification (VID) numbers

  See also: usb-if.tsv (usb.if), Company List by USB Implementers Forum, Inc
  (USB-IF) at http://www.usb.org/developers/tools/comp_dump;
  usb.ids, List of USB ID's by Stephen J. Gowdy at http://www.linux-usb.org/usb.ids.
 */

#include "UsbVid0000.h" //USB device vendor identification (VID) template
#include "UsbVid045F.h" //
#include "UsbVid046D.h" //Logitech Inc.
#include "UsbVid04B4.h" //Cypress Semiconductor Corporation
#include "UsbVid04CF.h" //Myson Century, Inc.
#include "UsbVid050D.h" //Belkin Components
#include "UsbVid05E0.h" //Motorola Symbol Technologies
#include "UsbVid078B.h" //Suzo-Happ Group
#include "UsbVid0801.h" //Mag-Tek
#include "UsbVid0839.h" //Samsung Tecwin Co.
#include "UsbVid0AA7.h" //Wincor Nixdorf GmbH
#include "UsbVid0ACD.h" //ID Tech
#include "UsbVid0D85.h" //L-1 Identity Solutions - Identix Incorporated
#include "UsbVid0DD4.h" //Custom Engineering Spa
#include "UsbVid152D.h" //JMicron Technology Corp.
#include "UsbVid413C.h" //Dell Computer Corp.
#include "UsbVid8086.h" //Intel Corporation

///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID_H_
/*****************************************************************************
 * $Log: UsbVid.h,v $
 * Revision 1.3  2009/07/30 17:08:32  ddarko
 * Updated
 *
 * Revision 1.2  2009/05/11 15:21:14  ddarko
 * Added Belkin International, Inc.
 *
 * Revision 1.1  2008/09/29 14:58:15  ddarko
 * Created
 *
 *****************************************************************************/
