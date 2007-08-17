/*$RCSfile: KUsb.h,v $: header file
  $Revision: 1.1 $ $Date: 2007/08/17 17:55:39 $
  $Author: dkolakovic $

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

#ifndef LPCTSTR
  #include "KTChar.h"
#endif

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifdef KUSBUNIX
  typedef HANDLE int;
#endif

///////////////////////////////////////////////////////////////////////////////
// Macros

#ifndef USBVID_ANY
  #define USBVID_ANY 0x0000 //undefined or unspecified USB vendor
#endif
#ifndef USBPID_ANY
  #define USBPID_ANY 0x0000 //undefined or unspecified USB product
#endif

#ifndef USBVID_TEST
  #define USBVID_TEST 0xFEED //USB vendor ID used for prototypes (not assigned by USB-IF)
#endif
#ifndef USBPID_TEST
  #define USBPID_TEST 0xBEEF //prototype USB product ID (not assigned by USB-IF)
#endif

#ifdef _MSC_VER
  #pragma pack(push, 1)  //Specifies packing alignment for structure,
                         //union and class members.
#endif

///////////////////////////////////////////////////////////////////////////////
/*Universal Serial Bus (USB) device type identification consists of
    16 bit wide Vendor ID assigned by the USB-IF and
    16 bit wide Product ID assigned by the manufacturer.

  USB ID numbers is the part of Standard Device Descriptor data structure.

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
  #pragma pack(pop)
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

#ifdef _cplusplus
///////////////////////////////////////////////////////////////////////////////
/*
 */
class CUsbId: public USBID
{
public:
  CUsbId();
  CUsbId(const USBID& usbId);
  CUsbId(const CUsbId& usbId);
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
CUsbId::CUsbId() :
  m_wVid(USBVID_ANY),
  m_wPid(USBPID_ANY)
{
}

CUsbId::CUsbId(const USBID& usbId) :
m_wVid(usbId.m_wVid),
m_wPid(usbId.m_wPid)
{
}

CUsbId::CUsbId(const CUsbId& usbId) :
m_wVid(usbId.m_wVid),
m_wPid(usbId.m_wPid)
{
}

CUsbId::~CUsbId()
{
}

//-----------------------------------------------------------------------------
/*Assignment operator
 */
CUsbId& CUsbId::operator =(const USBID& usbId //[in] value to assign
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
bool CUsbId::operator==(const CUsbId& usbId) const
{
return ((m_wVid == usbId.m_wVid) && (m_wPid == usbId.m_wPid));
}

/*Not-Equals operator.

  Returns: true if two objects are not the same.
 */
bool CUsbId::operator!=(const CUsbId& usbId) const
{
return ((m_wVid != usbId.m_wVid) || (m_wPid != usbId.m_wPid));
}

//-----------------------------------------------------------------------------
/*Validates USB device vendor identification (VID) number.

  Returns true if USB vendor have appropriate ID.
 */
bool CUsbId::IsVendor(const uint16_t wVendorId //[in] USB device vendor
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
bool CUsbId::IsProduct(const uint16_t wProductId //[in] USB product
                      //identification number assigned by the manufacturer
                      )
{
return (m_wPid == wProductId);
}

#endif //_cplusplus

///////////////////////////////////////////////////////////////////////////////
#endif //_KUSB_H_
/*****************************************************************************
 * $Log: KUsb.h,v $
 * Revision 1.1  2004/02/17 17:55:39  dkolakovic
 * Created
 *
 *****************************************************************************/
