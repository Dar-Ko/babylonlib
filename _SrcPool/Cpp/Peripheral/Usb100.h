/*$RCSfile: Usb100.h,v $: header file
  $Revision: 1.18 $ $Date: 2011/04/20 15:31:58 $
  $Author: ddarko $

  USB 1.0 definitions
  Copyright: (c) 2004-2008 The Open Watcom Contributors. All Rights Reserved.
  http://www.openwatcom.org/
 */
#ifndef __USB100_H__
  #define __USB100_H__

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

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Request directions */
#define BMREQUEST_HOST_TO_DEVICE  0
#define BMREQUEST_DEVICE_TO_HOST  1

/* Request types */
#define BMREQUEST_STANDARD        0
#define BMREQUEST_CLASS           1
#define BMREQUEST_VENDOR          2

/* Request recipients */
#define BMREQUEST_TO_DEVICE       0
#define BMREQUEST_TO_INTERFACE    1
#define BMREQUEST_TO_ENDPOINT     2
#define BMREQUEST_TO_OTHER        3

/*Maximum USB string length in bytes. The string length includes any optional
  terminating characters. String descriptors use Unicode encodings.

  See also: USB_STRING_DESCRIPTOR::bLength 
 */
#define MAXIMUM_USB_STRING_LENGTH   (((UINT8_MAX - 2) / sizeof(wchar_t)) * sizeof(wchar_t))

/* Get status return values */
#define USB_GETSTATUS_SELF_POWERED          0x01
#define USB_GETSTATUS_REMOTE_WAKEUP_ENABLED 0x02

/*-----------------------------------------------------------------------------
  USB descriptor types.
  See also: USB_DESCRIPTOR_MAKE_TYPE_AND_INDEX
 */

#define USB_DESCRIPTOR_TYPE_DEVICE        0x01 /*USB device descriptor type code       */
#define USB_DESCRIPTOR_TYPE_CONFIGURATION 0x02 /*USB configuration descriptor type code*/
#define USB_DESCRIPTOR_TYPE_STRING        0x03 /*USB string descriptor type code       */
#define USB_DESCRIPTOR_TYPE_INTERFACE     0x04 /*USB interface descriptor type code    */
#define USB_DESCRIPTOR_TYPE_ENDPOINT      0x05 /*USB endpoint descriptor type code     */

  /*Hardware design descriptor types.
    See also: "Usb200.h"
   */
#define USB_DESCRIPTOR_TYPE_INTERFACE_POWER 0x08 /*USB interface power consumption descriptor type code*/

/*Makes USB descriptor request value by combining type of descriptor to retrieve
  in the high byte and the descriptor index in the low byte.

  See also: USB_DESCRIPTOR_REQUEST::wValue, USBDESCRIPTORTYPE_DEVICE, 
  USBDESCRIPTORTYPE_STRING, USB_DESCRIPTOR_MAKE_TYPE_AND_INDEX
 */
#define USB_DESCRIPTOR_REQUEST_VALUE( type, index ) \
    ( (uint16_t)(((uint16_t)(type) << 8) | (index)) )

/****************************************************/
/*USB descriptor types (Microsoft compatible macros)*/

/*USB device descriptor type code*/
#define USB_DEVICE_DESCRIPTOR_TYPE          USB_DESCRIPTOR_TYPE_DEVICE
/*USB configuration descriptor type code*/
#define USB_CONFIGURATION_DESCRIPTOR_TYPE   USB_DESCRIPTOR_TYPE_CONFIGURATION
/*USB string descriptor type code*/
#define USB_STRING_DESCRIPTOR_TYPE          USB_DESCRIPTOR_TYPE_STRING
/*USB interface descriptor type code*/
#define USB_INTERFACE_DESCRIPTOR_TYPE       USB_DESCRIPTOR_TYPE_INTERFACE
/*USB endpoint descriptor type code*/
#define USB_ENDPOINT_DESCRIPTOR_TYPE        USB_DESCRIPTOR_TYPE_ENDPOINT
/*Reserved for USB 2.0 specification
  (deprecated descriptor type code macro, use USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE)*/
#define USB_RESERVED_DESCRIPTOR_TYPE        0x06
/*Specific for USB 1.0 specification
 (USB 2.0 specification uses USB_OTHER_SPEED_CONFIGURATION_DESCRIPTOR_TYPE)*/
#define USB_CONFIG_POWER_DESCRIPTOR_TYPE    0x07
/*USB interface power consumption descriptor type code*/
#define USB_INTERFACE_POWER_DESCRIPTOR_TYPE USB_DESCRIPTOR_TYPE_INTERFACE_POWER
/*Macro to make USB descriptors*/
#define USB_DESCRIPTOR_MAKE_TYPE_AND_INDEX  USB_DESCRIPTOR_REQUEST_VALUE

/* USB endpoint types */
#define USB_ENDPOINT_TYPE_MASK              0x03
#define USB_ENDPOINT_TYPE_CONTROL           0x00
#define USB_ENDPOINT_TYPE_ISOCHRONOUS       0x01
#define USB_ENDPOINT_TYPE_BULK              0x02
#define USB_ENDPOINT_TYPE_INTERRUPT         0x03

//-----------------------------------------------------------------------------
/*USB configuration descriptor attributes.

  See also: USB_CONFIGURATION_DESCRIPTOR::bmAttributes
 */

#define USB_CONFIGURATION_ATTRIB_REMOTEWAKEUP 0x20  //USB configuration flag 'remote wakeup supported'
#define USB_CONFIGURATION_ATTRIB_SELFPOWERED  0x40  //USB configuration flag 'device is self-powered'
#define USB_CONFIGURATION_ATTRIB_BUSPOWERED   0x80  //USB configuration flag 'powered by the bus'
//Bit mask to power source attributes of USB configuration descriptor
#define USB_CONFIGURATION_ATTRIB_POWERED_MASK \
  (USB_CONFIGURATION_ATTRIB_SELFPOWERED | USB_CONFIGURATION_ATTRIB_BUSPOWERED)

/*USB configuration descriptor attributes (Microsoft compatible macros)*/
#define USB_CONFIG_POWERED_MASK  USB_CONFIGURATION_ATTRIB_POWERED_MASK //Bit mask to power source attributes
#define USB_CONFIG_BUS_POWERED   USB_CONFIGURATION_ATTRIB_BUSPOWERED   //USB configuration flag 'powered by the bus'
#define USB_CONFIG_SELF_POWERED  USB_CONFIGURATION_ATTRIB_SELFPOWERED  //USB configuration flag 'device is self-powered'
#define USB_CONFIG_REMOTE_WAKEUP USB_CONFIGURATION_ATTRIB_REMOTEWAKEUP //USB configuration flag 'remote wakeup supported'

/* USB endpoint direction mask */
#define USB_ENDPOINT_DIRECTION_MASK         0x80

/* USB endpoint direction macros */
#define USB_ENDPOINT_DIRECTION_OUT( x ) (!((x) & USB_ENDPOINT_DIRECTION_MASK))
#define USB_ENDPOINT_DIRECTION_IN( x )    ((x) & USB_ENDPOINT_DIRECTION_MASK)

/* Standard Request Codes USB 2.0 Specification Table 9-4 */
#define USB_REQUEST_GET_STATUS              0x00
#define USB_REQUEST_CLEAR_FEATURE           0x01
#define USB_REQUEST_RESERVED_02             0x02
#define USB_REQUEST_SET_FEATURE             0x03
#define USB_REQUEST_RESERVED_04             0x04
#define USB_REQUEST_SET_ADDRESS             0x05
#define USB_REQUEST_GET_DESCRIPTOR          0x06
#define USB_REQUEST_SET_DESCRIPTOR          0x07
#define USB_REQUEST_GET_CONFIGURATION       0x08
#define USB_REQUEST_SET_CONFIGURATION       0x09
#define USB_REQUEST_GET_INTERFACE           0x0A
#define USB_REQUEST_SET_INTERFACE           0x0B
#define USB_REQUEST_SYNC_FRAME              0x0C

//-----------------------------------------------------------------------------
/*USB Device Classes.
  USB defines device types codes used to identify a device�s functionality.

  Class 	Usage   	Description 	                  	Examples
  00h 	Device    	Unspecified                     	Device class is unspecified. Interface descriptors are used for determining the required drivers.
  01h 	Interface 	Audio                           	Speaker, microphone, sound card
  02h 	Both      	Communications and CDC Control  	Ethernet adapter, modem, serial port adapter
  03h 	Interface 	Human Interface Device (HID)    	Keyboard, mouse, joystick
  05h 	Interface 	Physical Interface Device (PID) 	Force feedback joystick
  06h 	Interface 	Image                           	Webcam, scanner
  07h 	Interface 	Printer                         	Laser printer, inkjet printer, CNC machine
  08h 	Interface 	Mass Storage                    	USB flash drive, memory card reader, digital audio player, digital camera, external drive
  09h 	Device    	USB hub                         	Full speed hub, hi-speed hub
  0Ah 	Interface 	CDC-Data                        	(This class is used together with class 02h - Communications and CDC Control.)
  0Bh 	Interface 	Smart Card                      	USB smart card reader
  0Dh 	Interface 	Content Security                	-
  0Eh 	Interface 	Video                           	Webcam
  0Fh 	Interface 	Personal Healthcare             	-
  DCh 	Both      	Diagnostic Device               	USB compliance testing device
  E0h 	Interface 	Wireless Controller             	Wi-Fi adapter, Bluetooth adapter
  EFh 	Both      	Miscellaneous                   	ActiveSync device
  FEh 	Interface 	Application Specific            	IrDA Bridge, Test & Measurement Class (USBTMC)[4]
  FFh 	Both      	Vendor Specific                 	This class code indicates that the device needs vendor specific drivers.

  See also: {html: <a href="http://www.usb.org/developers/defined_class/">USB Class Codes</a>}
 */
#define USB_DEVICE_CLASS_AUDIO              0x01 /*Identifier for audio class interfaces. */
#define USB_DEVICE_CLASS_COMMUNICATIONS     0x02 /*Identifier for communications control class interfaces. */
#define USB_DEVICE_CLASS_HUMAN_INTERFACE    0x03 /*Identifier for Human Interaction Device (HID) class interfaces. */
#define USB_DEVICE_CLASS_MONITOR            0x04
#define USB_DEVICE_CLASS_PHYSICAL_INTERFACE 0x05 /*Identifier for Physical Interface Device (PID) class interfaces. */
#define USB_DEVICE_CLASS_POWER              0x06 /* Image ?? */
#define USB_DEVICE_CLASS_PRINTER            0x07 /*Identifier for printer class interfaces. */
#define USB_DEVICE_CLASS_STORAGE            0x08 /*Identifier for mass storage class interfaces. */
#define USB_DEVICE_CLASS_HUB                0x09 /*Identifier for hub class interfaces. */
#define USB_DEVICE_CLASS_DATA               0x0A /*Identifier for communications data class interfaces. */
#define USB_DEVICE_CLASS_APP_SPECIFIC       0xFE /*Identifier for application-specific interfaces.
                                                   Subclass codes are used to indicate facilities such as
                                                   firmware update or an IrDA/USB bridge. */
#define USB_DEVICE_CLASS_VENDOR_SPECIFIC    0xFF /*Identifier for vendor-specific interfaces. */

/*Standard USB Feature Selectors*/
#define USB_FEATURE_ENDPOINT_STALL          0x00  //USB endpoint halt
#define USB_FEATURE_REMOTE_WAKEUP           0x01
#define USB_FEATURE_INTERFACE_POWER_D0      0x02
#define USB_FEATURE_INTERFACE_POWER_D1      0x03
#define USB_FEATURE_INTERFACE_POWER_D2      0x04
#define USB_FEATURE_INTERFACE_POWER_D3      0x05

/* USB support flags */
#define USB_SUPPORT_D0_COMMAND              0x01
#define USB_SUPPORT_D1_COMMAND              0x02
#define USB_SUPPORT_D2_COMMAND              0x04
#define USB_SUPPORT_D3_COMMAND              0x08
#define USB_SUPPORT_D0_WAKEUP               0x10
#define USB_SUPPORT_D1_WAKEUP               0x20

/* ------------------------------------------------------------------------- */
/* All structures in this file get one-byte packing.                         */
/* All multibyte data fields are in little-endian form.                      */
#include <pshpack1.h>

/*USB_DEVICE_DESCRIPTOR structure is used to retrieve information about
  USB device.

  Note: all multibyte data fields are in little-endian form.
 */
typedef struct _USB_DEVICE_DESCRIPTOR 
  {
  uint8_t  bLength;  /*size of the entire data structure [bytes] */
  uint8_t  bDescriptorType; /*the descriptor type is constant 
                              USB_DESCRIPTOR_TYPE_DEVICE = 0x01*/
  uint16_t bcdUSB;          /*USB specification version supported by device
                              as binary-coded decimal number*/
  uint8_t  bDeviceClass;    /*the class code of the device as assigned by 
                              the USB specification group.*/
  uint8_t  bDeviceSubClass; /*the subclass code of the device as assigned by 
                              the USB specification group.*/
  uint8_t  bDeviceProtocol; /*protocol code of the device as assigned by
                              the USB specification group.*/
  uint8_t  bMaxPacketSize0; /*the maximum packet size, in bytes, for endpoint
                              zero of the device. The value must be set to 
                              8, 16, 32, or 64.*/
  uint16_t idVendor;        /*vendor identifier for the device as assigned by
                              the USB specification committee.*/
  uint16_t idProduct;       /*the product identifier as assigned by
                              the manufacturer.*/
  uint16_t bcdDevice;       /*the version of the device as binary-coded decimal
                              number*/
  uint8_t  iManufacturer;   /*index of the string with manufacturer name*/ 
  uint8_t  iProduct;        /*index of the string with device description*/ 
  uint8_t  iSerialNumber;   /*index of the string with serial number
                              for the device*/
  uint8_t  bNumConfigurations; /*the total number of possible configurations
                                 for the device.*/
  } USB_DEVICE_DESCRIPTOR;
/*USB device descriptor*/
typedef USB_DEVICE_DESCRIPTOR   *PUSB_DEVICE_DESCRIPTOR;
/*Descriptor for a USB Device.
  See also: "USB Specification 1.1", http://www.usb.org.
 */
typedef USB_DEVICE_DESCRIPTOR   IOUSBDeviceDescriptor;

/*USB endpoint descriptor */
typedef struct _USB_ENDPOINT_DESCRIPTOR 
  {
  uint8_t   bLength;        /*size of the entire data structure [bytes] */
  uint8_t   bDescriptorType;/*the descriptor type is constant 
                              USB_DESCRIPTOR_TYPE_ENDPOINT = 0x05*/
  uint8_t   bEndpointAddress;
  uint8_t   bmAttributes;
  uint16_t  wMaxPacketSize;
  uint8_t   bInterval;
  } USB_ENDPOINT_DESCRIPTOR;
/*USB endpoint descriptor */
typedef USB_ENDPOINT_DESCRIPTOR *PUSB_ENDPOINT_DESCRIPTOR;
/*Descriptor for a USB Endpoint.
  See also: "USB Specification 1.1", http://www.usb.org.
 */
typedef USB_ENDPOINT_DESCRIPTOR IOUSBEndpointDescriptor;

/*USB configuration descriptor contains information about a specific USB device
  configuration. USB devices can support several different configurations in
  which different interfaces on the device might behave in different ways.

  Note: all multibyte data fields are in little-endian form.

  See also: USB_CONFIGURATION_ATTRIB_REMOTEWAKEUP, USB_CONFIGURATION_ATTRIB_SELFPOWERED,
  USB_CONFIGURATION_ATTRIB_BUSPOWERED
 */
typedef struct _USB_CONFIGURATION_DESCRIPTOR
  {
  uint8_t   bLength; /*size of the entire data structure [bytes] */
  uint8_t   bDescriptorType; /*the descriptor type is constant 
                             USB_DESCRIPTOR_TYPE_CONFIGURATION = 0x02*/
  uint16_t  wTotalLength;  /*[out] total length of data returned for this
                           configuration. This includes the combined length of
                           all structures: USB_CONFIGURATION_DESCRIPTOR,
                           USB_INTERFACE, USB_ENDPOINT_DESCRIPTOR and any class
                           or vendor-specific structures*/
  uint8_t   bNumInterfaces; /*number of interfaces supported as part of this
                            configuration*/
  uint8_t   bConfigurationValue; /*value used when this configuration descriptor is
                                 requested*/
  uint8_t   iConfiguration; /*index of a string descriptor describing this
                            configuration*/
  uint8_t   bmAttributes;  /*configuration flags

                           7|6|5|4|3|2|1|0
                           | | | +-------+- bits [0, 4] are reserved and should
                           | | |            be zero (0)
                           | | +-- remote wakeup supported (0/1)
                           | +---- self-powered (1/0)
                           +------ powered by the bus in this configuration (0/1)
                          */
  uint8_t   MaxPower;     /*maximum consumption in 2mA units; used if 
                          the bmAttributes member indicates that the device
                          requires bus power*/ 
  } USB_CONFIGURATION_DESCRIPTOR;
/*USB configuration descriptor */
typedef USB_CONFIGURATION_DESCRIPTOR    *PUSB_CONFIGURATION_DESCRIPTOR;
/*Standard USB Configuration Descriptor. 
  It is variable length, so this only specifies the known fields.
  See also: "USB Specification 1.1", http://www.usb.org.
 */
typedef USB_CONFIGURATION_DESCRIPTOR    IOUSBConfigurationDescriptor;

/*USB interface descriptor */
typedef struct _USB_INTERFACE_DESCRIPTOR 
  {
  uint8_t bLength;        /*size of the entire data structure [bytes] */
  uint8_t bDescriptorType;/*the descriptor type is constant 
                            USB_DESCRIPTOR_TYPE_INTERFACE = 0x04*/
  uint8_t bInterfaceNumber;
  uint8_t bAlternateSetting;
  uint8_t bNumEndpoints;
  uint8_t bInterfaceClass;
  uint8_t bInterfaceSubClass;
  uint8_t bInterfaceProtocol;
  uint8_t iInterface;
  } USB_INTERFACE_DESCRIPTOR;
/*USB interface descriptor */
typedef USB_INTERFACE_DESCRIPTOR    *PUSB_INTERFACE_DESCRIPTOR;
/*Descriptor for a USB Interface.
  See also: "USB Specification 1.1", http://www.usb.org.
 */
typedef USB_INTERFACE_DESCRIPTOR    IOUSBInterfaceDescriptor;

/*USB String Descriptor.
  Device, configuration, and interface descriptors may contain references to
  string descriptors. String descriptors are referenced by their one-based index
  number. A string descriptor contains one or more Unicode strings; each string
  is a translation of the others into another language.
  Drivers can request the special index number of zero to determine which
  language IDs the device supports. For this special value, the device returns
  an array of language IDs rather than a Unicode string.

  See also: LANGID, MAXIMUM_USB_STRING_LENGTH;
  "Universal Serial Bus Specification Revision 1.1", Chapters 9.5 Descriptors, 
  9.6.5 String;
 */
typedef struct _USB_STRING_DESCRIPTOR
  {
  uint8_t bLength;         /*[in]/[out] the size in bytes of the entire descriptor*/
  uint8_t bDescriptorType; /*[in] the descriptor type is constant 
                           USB_DESCRIPTOR_TYPE_STRING = 0x03*/
  WCHAR bString[1];      /*[out] requested Unicode string or array of language
                           IDs*/
  } USB_STRING_DESCRIPTOR;
/*USB string descriptor*/
typedef USB_STRING_DESCRIPTOR   *PUSB_STRING_DESCRIPTOR;

/*USB common descriptor */
typedef struct _USB_COMMON_DESCRIPTOR 
  {
  uint8_t   bLength;
  uint8_t   bDescriptorType;
  } USB_COMMON_DESCRIPTOR;
/*USB common descriptor */
typedef USB_COMMON_DESCRIPTOR   *PUSB_COMMON_DESCRIPTOR;
/*Standard header used for all USB descriptors.
  Used to read the length of a descriptor so that we can allocate storage for
  the whole descriptor later on.
 */
typedef USB_COMMON_DESCRIPTOR   IOUSBDescriptorHeader;

/*USB hub descriptor.
  See also: USB Specification: Chapter 11
 */
typedef struct _USB_HUB_DESCRIPTOR 
  {
  uint8_t  bDescriptorLength;   //length of this descriptor in bytes
  uint8_t  bDescriptorType;     //descriptor type; default value for hub
                              //is constant USBCLASSDESCRIPTOR_HUB = 0x29
  uint8_t  bNumberOfPorts;      //number of ports on the hub
  uint16_t wHubCharacteristics; //hub characteristics
  uint8_t  bPowerOnToPowerGood; //time, in 2 ms increments, that it
                              //takes the device to turn on completely
  uint8_t  bHubControlCurrent;  //maximum current consumption [mA]
  uint8_t  bRemoveAndPowerMask[64];//power control and removable bitmasks
                               //for up to 255 (256 ?) ports (?! max devices on host controller is 127 D.K. (verify))
  } USB_HUB_DESCRIPTOR;
/*USB hub descriptor.*/
typedef USB_HUB_DESCRIPTOR  *PUSB_HUB_DESCRIPTOR;

/*USB power configuration descriptor 
  Note: specific for USB 1.0 specification
 */
typedef struct _USB_CONFIGURATION_POWER_DESCRIPTOR 
  {
  uint8_t   bLength;
  uint8_t   bDescriptorType;  /*[in] the descriptor type is constant
                                USB_CONFIG_POWER_DESCRIPTOR_TYPE = 0x07*/
  uint8_t   SelfPowerConsumedD0[3];
  uint8_t   bPowerSummaryId;
  uint8_t   bBusPowerSavingD1;
  uint8_t   bSelfPowerSavingD1;
  uint8_t   bBusPowerSavingD2;
  uint8_t   bSelfPowerSavingD2;
  uint8_t   bBusPowerSavingD3;
  uint8_t   bSelfPowerSavindD3;
  uint16_t  TransitionTimeFromD1;
  uint16_t  TransitionTimeFromD2;
  uint16_t  TransitionTimeFromD3;
  } USB_CONFIGURATION_POWER_DESCRIPTOR;
/*USB power configuration descriptor */
typedef USB_CONFIGURATION_POWER_DESCRIPTOR  *PUSB_CONFIGURATION_POWER_DESCRIPTOR;

/*USB interface power descriptor */
typedef struct _USB_INTERFACE_POWER_DESCRIPTOR 
  {
  uint8_t   bLength;
  uint8_t   bDescriptorType; /*[in] the descriptor type is constant
                               USB_DESCRIPTOR_TYPE_INTERFACE_POWER = 0x08*/
  uint8_t   bmCapabilitiesFlags;
  uint8_t   bBusPowerSavingD1;
  uint8_t   bSelfPowerSavingD1;
  uint8_t   bBusPowerSavingD2;
  uint8_t   bSelfPowerSavingD2;
  uint8_t   bBusPowerSavingD3;
  uint8_t   bSelfPowerSavingD3;
  uint16_t  TransitionTimeFromD1;
  uint16_t  TransitionTimeFromD2;
  uint16_t  TransitionTimeFromD3;
  } USB_INTERFACE_POWER_DESCRIPTOR;
/*USB interface power descriptor */
typedef USB_INTERFACE_POWER_DESCRIPTOR  *PUSB_INTERFACE_POWER_DESCRIPTOR;

/* ------------------------------------------------------------------------- */
/* Revert to default packing.                                                */
#include <poppack.h>

#ifdef __cplusplus
} /* End of extern "C" */
#endif
///////////////////////////////////////////////////////////////////////////////
#endif /* __USB100_H__ */

/*****************************************************************************
 * $Log: Usb100.h,v $
 * Revision 1.18  2011/04/20 15:31:58  ddarko
 * formatting
 *
 * Revision 1.17  2009/08/20 21:25:36  ddarko
 * ISO C99 types
 *
 * Revision 1.16  2009/08/18 21:36:54  ddarko
 * MacOs
 *
 * Revision 1.15  2009/08/14 18:26:05  ddarko
 * Correct value for MAXIMUM_USB_STRING_LENGTH
 *
 * Revision 1.14  2009/08/13 21:27:09  ddarko
 * *** empty log message ***
 *
 * Revision 1.13  2009/08/12 17:21:02  ddarko
 * USB_DESCRIPTOR_REQUEST_VALUE
 *
 * Revision 1.12  2009/08/11 21:20:31  ddarko
 * USB string descriptor
 *
 * Revision 1.11  2009/08/10 20:55:41  ddarko
 * Descriptor types
 *
 * Revision 1.10  2009/08/07 21:45:13  ddarko
 * Comments
 *
 * Revision 1.9  2009/07/21 22:18:34  ddarko
 * USBCLASSDESCRIPTOR_HUB
 *
 * Revision 1.8  2009/07/20 21:51:12  ddarko
 * *** empty log message ***
 *
 * Revision 1.7  2009/07/13 22:04:01  ddarko
 * Description
 *
 * Revision 1.6  2009/07/12 21:10:26  ddarko
 * Comments
 *
 * Revision 1.5  2009/05/22 18:41:03  ddarko
 * Consolidated items across the header files
 *
 * Revision 1.4  2009/05/20 20:58:27  ddarko
 * Comment
 *
 *****************************************************************************/

/*Contributors:
 *   Created by Casper S. Hornstrup <chorns@users.sourceforge.net>
 *
 * THIS SOFTWARE IS NOT COPYRIGHTED
 *
 * This source code is offered for use in the public domain. You may
 * use, modify or distribute it freely.
 *
 * This code is distributed in the hope that it will be useful but
 * WITHOUT ANY WARRANTY. ALL WARRANTIES, EXPRESS OR IMPLIED ARE HEREBY
 * DISCLAIMED. This includes but is not limited to warranties of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/*Open Watcom is a project of the open source community to maintain and enhance
  the Watcom C, C++, and Fortran cross compilers and tools.
  An Open Source license from Sybase allows free commercial and non-commercial
  use of Open Watcom.
  http://www.openwatcom.org/index.php/Open_Watcom_Public_License
 */
