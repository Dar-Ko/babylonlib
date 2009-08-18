/*$RCSfile: Usb200.h,v $: header file
  $Revision: 1.8 $ $Date: 2009/08/18 21:36:54 $
  $Author: ddarko $

  USB 2.0 definitions
  Copyright: (c) 2004-2008 The Open Watcom Contributors. All Rights Reserved.
  http://www.openwatcom.org/
 */
#ifndef __USB200_H__
  #define __USB200_H__

#ifndef _ENABLE_AUTODEPEND
  #ifdef __WATCOMC__
    /*Watcom 32b Compiler*/
    #pragma read_only_file;
  #endif
#endif

#if __GNUC__ >= 3
  #pragma GCC system_header
#endif

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#include "Usb100.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* USB hub port status flags */
#define USB_PORT_STATUS_CONNECT                       0x0001
#define USB_PORT_STATUS_ENABLE                        0x0002
#define USB_PORT_STATUS_SUSPEND                       0x0004
#define USB_PORT_STATUS_OVER_CURRENT                  0x0008
#define USB_PORT_STATUS_RESET                         0x0010
#define USB_PORT_STATUS_POWER                         0x0100
#define USB_PORT_STATUS_LOW_SPEED                     0x0200
#define USB_PORT_STATUS_HIGH_SPEED                    0x0400

  /*USB descriptor types
    See also: "Usb100.h"
   */

#define USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER 0x06 /*Indicates a USB 2.0 "device qualifier" */
#define USB_DESCRIPTOR_TYPE_OTHER_SPEED      0x07 /*Indicates a USB 2.0 "other speed configuration" */
#define USB_DESCRIPTOR_TYPE_INTERFACE_ASSOCIATION  0x0B

/*USB descriptor types (Microsoft compatible macros)*/

#define USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE          USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER
#define USB_OTHER_SPEED_CONFIGURATION_DESCRIPTOR_TYPE USB_DESCRIPTOR_TYPE_OTHER_SPEED
#define USB_INTERFACE_ASSOCIATION_DESCRIPTOR_TYPE     USB_DESCRIPTOR_TYPE_INTERFACE_ASSOCIATION

/*---------------------------------------------------------------------------*/
/* All structures in this file get one-byte packing.                         */
/* All multibyte data fields are in little-endian form.                      */
#include <pshpack1.h>

/* USB device speeds */
typedef enum _USB_DEVICE_SPEED {
    UsbLowSpeed     = 0,
    UsbFullSpeed    = 1,
    UsbHighSpeed    = 2
} USB_DEVICE_SPEED;

/* USB device types */
typedef enum _USB_DEVICE_TYPE {
    Usb11Device = 0,
    Usb20Device = 1
} USB_DEVICE_TYPE;

/* Request type */
typedef union _BM_REQUEST_TYPE {
    struct _BM {
        UCHAR   Recipient   : 2;
        UCHAR   Reserved    : 3;
        UCHAR   Type        : 2;
        UCHAR   Dir         : 1;
    };
    UCHAR   B;
} BM_REQUEST_TYPE;
typedef BM_REQUEST_TYPE *PBM_REQUEST_TYPE;

#ifdef _MSC_VER
  //Microsoft Visual C/C++
  //warning C4201: nonstandard extension used : nameless struct/union
  #pragma warning(disable: 4201)
#endif
/* USB default pipe setup packet */
typedef struct _USB_DEFAULT_PIPE_SETUP_PACKET
  {
  BM_REQUEST_TYPE bmRequestType;
  UCHAR           bRequest;
  union _wValue
    {
    struct
      {
      UCHAR   LowByte;
      UCHAR   HiByte;
      };
    USHORT  W;
    } wValue;
  union _wIndex
    {
    struct
      {
      UCHAR   LowByte;
      UCHAR   HiByte;
      };
    USHORT  W;
    } wIndex;
  USHORT          wLength;
  } USB_DEFAULT_PIPE_SETUP_PACKET;
typedef USB_DEFAULT_PIPE_SETUP_PACKET   *PUSB_DEFAULT_PIPE_SETUP_PACKET;
#ifdef _MSC_VER
  //warning C4201: nonstandard extension used : nameless struct/union
  #pragma warning(default: 4201)
#endif

/* USB device qualifier descriptor */
typedef struct _USB_DEVICE_QUALIFIER_DESCRIPTOR {
    UCHAR   bLength;
    UCHAR   bDescriptorType; /*[in] the descriptor type is constant
                               USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER = 0x06*/
    USHORT  bcdUSB;
    UCHAR   bDeviceClass;
    UCHAR   bDeviceSubClass;
    UCHAR   bDeviceProtocol;
    UCHAR   bMaxPacketSize0;
    UCHAR   bNumConfigurations;
    UCHAR   bReserved;
} USB_DEVICE_QUALIFIER_DESCRIPTOR;
typedef USB_DEVICE_QUALIFIER_DESCRIPTOR *PUSB_DEVICE_QUALIFIER_DESCRIPTOR;
/*USB Device Qualifier Descriptor.
  See also: "USB Specification 2.0", http://www.usb.org.
 */
typedef USB_DEVICE_QUALIFIER_DESCRIPTOR IOUSBDeviceQualifierDescriptor;


/* USB high speed maximum packet */
typedef union _USB_HIGH_SPEED_MAXPACKET {
    struct _MP {
        USHORT  MaxPacket   : 11;
        USHORT  HSmux       : 2;
        USHORT  Reserved    : 3;
    };
    USHORT  us;
} USB_HIGH_SPEED_MAXPACKET;
typedef USB_HIGH_SPEED_MAXPACKET    *PUSB_HIGH_SPEED_MAXPACKET;

/* USB interface association descriptor */
typedef struct _USB_INTERFACE_ASSOCIATION_DESCRIPTOR {
    UCHAR   bLength;
    UCHAR   bDescriptorType; /*[in] the descriptor type is constant
                               USB_DESCRIPTOR_TYPE_INTERFACE_ASSOCIATION = 0x0B*/
    UCHAR   bFirstInterface;
    UCHAR   bInterfaceCount;
    UCHAR   bFunctionClass;
    UCHAR   bFunctionSubClass;
    UCHAR   bFunctionProtocol;
    UCHAR   iFunction;
} USB_INTERFACE_ASSOCIATION_DESCRIPTOR;
typedef USB_INTERFACE_ASSOCIATION_DESCRIPTOR    *PUSB_INTERFACE_ASSOCIATION_DESCRIPTOR;
/*USB Inerface Association Descriptor.
  See also: "ECN to the USB Specification 2.0", http://www.usb.org.
 */
typedef USB_INTERFACE_ASSOCIATION_DESCRIPTOR    IOUSBInterfaceAssociationDescriptor;

/*---------------------------------------------------------------------------*/
/* Revert to default packing.                                                */
#include <poppack.h>

#ifdef __cplusplus
} /* End of extern "C" */
#endif
///////////////////////////////////////////////////////////////////////////////
#endif /* __USB200_H__ */

/*****************************************************************************
 * $Log: Usb200.h,v $
 * Revision 1.8  2009/08/18 21:36:54  ddarko
 * MacOs
 *
 * Revision 1.7  2009/08/10 20:55:41  ddarko
 * Desceiptor types
 *
 * Revision 1.6  2009/06/30 17:41:15  ddarko
 * Updated version
 *
 * Revision 1.5  2009/05/22 18:41:03  ddarko
 * Consolidated items across the header files
 *
 * Revision 1.4  2009/05/20 21:14:15  ddarko
 * disabled MSVC warning
 *
 * Revision 1.3  2009/05/20 20:58:27  ddarko
 * Comment
 *
 *****************************************************************************/

/*Open Watcom is a project of the open source community to maintain and enhance
  the Watcom C, C++, and Fortran cross compilers and tools.
  An Open Source license from Sybase allows free commercial and non-commercial
  use of Open Watcom.
  http://www.openwatcom.org/index.php/Open_Watcom_Public_License
 */
