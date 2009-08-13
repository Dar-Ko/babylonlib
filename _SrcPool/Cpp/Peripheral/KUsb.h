/*$RCSfile: KUsb.h,v $: header file
  $Revision: 1.9 $ $Date: 2009/08/13 21:27:01 $
  $Author: ddarko $

  Universal Serial Bus (USB) device data structures
  Copyright: babylonlib@sourceforge.net CommonSoft Inc.
  2004-03-02 Darko Kolakovic
 */

#ifndef _KUSB_H_
  //$RCSkfile: KUsb.h$ sentry
  #define _KUSB_H_

#ifdef _LINUX
  #define KUSBUNIX 20040301
#endif
#ifdef _UNIX
  #define KUSBUNIX 20040302
#endif

#pragma include_alias( "stdint.h", "KType32.h" )
#include "stdint.h" //ISO C99 type definitions

#include "Usb200.h" //USB 2.0 Specification
//#ifndef LPCTSTR
//  #include "KTChar.h"
//#endif

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifdef KUSBUNIX
  typedef HANDLE int;
#endif

///////////////////////////////////////////////////////////////////////////////
// Macros

//-----------------------------------------------------------------------------
//Class Descriptor Types

//Device Class Definition for Human Interface Devices (HID) v.1.11
//See also: "USB 1.1 specification": Chapters 9.5; 9.6
#define USBCLASSDESCRIPTOR_HID         0x21 //Human Interface Devices (HID) class descriptor
#define USBCLASSDESCRIPTOR_HIDREPORT   0x22
#define USBCLASSDESCRIPTOR_HIDPHYSICAL 0x23

#define USBCLASSDESCRIPTOR_HUB         0x29 //Hub class descriptor

//-----------------------------------------------------------------------------
//HID Class specific requests
#define HID_GET_REPORT      0x01
#define HID_GET_IDLE        0x02
#define HID_GET_PROTOCOL    0x03
#define HID_SET_REPORT      0x09
#define HID_SET_IDLE        0x0A
#define HID_SET_PROTOCOL    0x0B

  /*
#define USB_HID_OK             0
#define USB_HID_OPEN_ERROR     1
#define USB_HID_WRITE_ERROR    2
#define USB_HID_READ_ERROR     3
#define USB_HID_INVALID_VALUE  4
#define USB_HID_ALREADY_OPENED 5
#define USB_HID_NOT_CONFIGURED 6
#define USB_HID_NOT_OPENED     7
#define USB_HID_READ_TIMEOUT   8

#define MAX_USB_HID_SIZE 64
#define DEVICE_LENGTH 255
*/


/*Maximum number of USB devices, including USB hubs, that could be connected to
  a single host controller. Every host controller has at least one build-in hub,
  know as root hub. The host controller assigns a unique 7-bit identification
  number [0, 127] to every device connected.

  Note: practical limit of devices that could be connected depends of the
  communication bandwidth and power consumption of each device and it is
  significantly smaller than number allowed by the standard.
 */
#define USB_MAXCOUNT  127

/*Maximum number of supported languages by a USB device.
  The size is limited with the largest number that could be stored in the
  USB_STRING_DESCRIPTOR::bLength, less two for the size of the structure
  members.

  See also: "Universal Serial Bus Specification Revision 1.1", 
  Chapters 9.5 Descriptors, 9.6.5 String;
  LANGID, MAXIMUM_USB_STRING_LENGTH, USB_STRING_DESCRIPTOR, USB_LANGID_LIST.
 */
#define USB_MAXCOUNT_LANGID  (MAXIMUM_USB_STRING_LENGTH/sizeof(LANGID))


#ifndef USBVID_ANY
  #define USBVID_ANY 0x0000 //undefined or unspecified USB vendor
#endif
#ifndef USBPID_ANY
  #define USBPID_ANY 0x0000 //undefined or unspecified USB product
#endif

#ifndef USBVID_MAX
  #define USBVID_MAX 0xFFFF //largest possible USB vendor ID
#endif
#ifndef USBPID_MAX
  #define USBPID_MAX 0xFFFF //largest possible USB product ID
#endif

#ifndef USBVID_TEST
  #define USBVID_TEST 0x1A0A //6666 USB-IF non-workshop ID used customarily
                             //for prototypes
#endif
#ifndef USBPID_TEST
  #define USBPID_TEST 0xBEEF //prototype USB product ID (not assigned by USB-IF)
#endif

#ifdef _MSC_VER
  #include <pshpack1.h>  //Specifies packing alignment for structure,
                         //union and class members.
#endif

///////////////////////////////////////////////////////////////////////////////
/*USB String Descriptor with supported language codes.
  Device, configuration, and interface descriptors may contain references to
  string descriptors and the device device may support multiple languages. 
  String Descriptor with the special index number of zero
  contains the list of language IDs the device supports.

  Request for the String indexed zero for any language returns a string 
  descriptor that contains an array of two-byte LANGID codes supported by 
  the device.
  USB devices that omit all string descriptors shall not return an array of 
  LANGID codes.
  The array of LANGID codes is not NULL-terminated. The size of the array
  (in bytes) is computed by subtracting two from the value of the first byte of
  the descriptor.

  See also: LANGID, USB_MAXCOUNT_LANGID, USB_STRING_DESCRIPTOR,
  "Universal Serial Bus Specification Revision 1.1", Chapters 9.5 Descriptors, 9.6.5 String;
 */
union tagUSB_LANGID_LIST
  {
  USB_STRING_DESCRIPTOR usbStrDescriptor;
  struct
    {
    uint8_t bLength;         /*[in]/[out] the size in bytes of the entire descriptor*/
    uint8_t bDescriptorType; /*[in] the descriptor type is constant 
                               USB_DESCRIPTOR_TYPE_STRING = 0x03*/
    LANGID  wLangId[1];      /*[out] list of supported language codes; maximum 
                               number of supported languges is 127.*/
    } usbLangIdDescriptor;
  };
/*USB String Descriptor with supported language codes.*/
typedef tagUSB_LANGID_LIST USB_LANGID_LIST;

///////////////////////////////////////////////////////////////////////////////
/*Universal Serial Bus (USB) device type identification consists of:
    16 bit wide Vendor ID (VID) assigned by the USB-IF and
    16 bit wide Product ID (PID) assigned by the manufacturer.

  A VID/PID unique to a particular USB device must be contained within
  the device hardware to comply with the USB specification.
  USB ID numbers are the part of Standard Device Descriptor data structure.

  See also: USB Implementers Forum, Inc (USB-IF) at http://www.usb.org;
  Universal Serial Bus Specification Revision 2.0, 9.6 Standard USB Descriptor
  Definitions.
 */
struct tagUsbId
{
uint16_t  m_wVid; //USB device vendor identification (VID) number
uint16_t  m_wPid; //USB product identification (PID) number
};

#ifdef _MSC_VER
  #include <poppack.h> //Revert to default packing
#endif

#if !defined(USBID)

  //Globally Unique Identifier (USBID). See also: tagUUID, tagUsbId
  typedef tagUsbId  USBID;

  //Pointer to Globally Unique Identifier (USBID). See also: tagUsbId
  typedef tagUsbId* LPUSBID;

  //Constant pointer to Globally Unique Identifier (USBID). See also: tagUsbId
  typedef const tagUsbId* LPCUSBID;

  #define tagUsbId tagUsbId
  #define USBID USBID
#endif /*tagUsbId*/

#ifdef __cplusplus
///////////////////////////////////////////////////////////////////////////////
/*Encapsulates common operations with USB device identification numbers
  (VID, PID).

  See also: tagUsbId struct, LPUSBID, Standard USB Descriptor Definitions,
  USB Implementers Forum, Inc (USB-IF) at http://www.usb.org;
 */
class CUsbId: public USBID
{
public:
  CUsbId();
  CUsbId(const USBID& usbId);
  CUsbId(const CUsbId& usbId);
  CUsbId(const uint16_t wVendorId, const uint16_t wProductId);
  virtual ~CUsbId();
  CUsbId& operator =(const USBID& usbId);
  bool operator==(const CUsbId& usbId) const;
  bool operator!=(const CUsbId& usbId) const;
  bool IsVendor(const uint16_t wVendorId);
  bool IsProduct(const uint16_t wProductId);

};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Default constructor
 */
inline CUsbId::CUsbId()
{
m_wVid = USBVID_ANY;
m_wPid = USBPID_ANY;
}

inline CUsbId::CUsbId(const USBID& usbId)
{
m_wVid = usbId.m_wVid;
m_wPid = usbId.m_wPid;
}

inline CUsbId::CUsbId(const CUsbId& usbId)
{
m_wVid = usbId.m_wVid;
m_wPid = usbId.m_wPid;
}

inline
CUsbId::CUsbId(const uint16_t wVendorId, //[in] USB device vendor identification
                                         //(VID) number
               const uint16_t wProductId //[in] USB product identification (PID)
                                         //number
               )
{
m_wVid = wVendorId;
m_wPid = wProductId;
}

inline CUsbId::~CUsbId()
{
}

//-----------------------------------------------------------------------------
/*Assignment operator
 */
inline CUsbId& CUsbId::operator =(const USBID& usbId //[in] value to assign
                                 )
{
m_wVid = usbId.m_wVid;
m_wPid = usbId.m_wPid;
return (*this);
}

//-----------------------------------------------------------------------------
/*Equality operator.

  Returns: true if two objects are the same.
 */
inline bool CUsbId::operator==(const CUsbId& usbId) const
{
return ((m_wVid == usbId.m_wVid) && (m_wPid == usbId.m_wPid));
}

/*Not-Equals operator.

  Returns: true if two objects are not the same.
 */
inline bool CUsbId::operator!=(const CUsbId& usbId) const
{
return ((m_wVid != usbId.m_wVid) || (m_wPid != usbId.m_wPid));
}

//-----------------------------------------------------------------------------
/*Validates USB device vendor identification (VID) number.

  Returns true if USB vendor have appropriate ID.
 */
inline bool CUsbId::IsVendor(const uint16_t wVendorId //[in] USB device vendor
                      //identification number assigned by the
                      //USB Implementers Forum (USB-IF)
                     )
{
return (m_wVid == wVendorId);
}

//-----------------------------------------------------------------------------
/*Validates USB product identification (PID) number.

  Returns true if USB product have appropriate ID.
*/
inline bool CUsbId::IsProduct(const uint16_t wProductId //[in] USB product
                      //identification number assigned by the manufacturer
                      )
{
return (m_wPid == wProductId);
}

#endif //_cplusplus

///////////////////////////////////////////////////////////////////////////////
#endif //_KUSB_H_
/*****************************************************************************
 * $Log:
 *  3    Biblioteka1.2         2007-08-24 18:17:11  Darko Kolakovic Extracted
 *       Windows specifics
 *  2    Biblioteka1.1         2007-08-22 19:28:02  Darko Kolakovic USB
 *  1    Biblioteka1.0         2007-08-22 10:50:52  Darko Kolakovic
 * $
 * Revision 1.2  2007/08/21 14:46:24  dkolakovic
 * IsConnected()
 *
 * Revision 1.1  2007/08/17 17:55:39  dkolakovic
 * Copied from BabylonLib
 *
 *****************************************************************************/
