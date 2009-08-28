/*$RCSfile: KUsbDeviceInfo.h,v $: header file
  $Revision: 1.1 $ $Date: 2009/08/28 13:57:26 $
  $Author: ddarko $

  USB (Universal Serial Bus) device information container
  Copyright: CommonSoft Inc
  2004-03-09 Darko Kolakovic
 */

#ifndef _KUSBDEVICEINFO_H_
    //$RCSfile: KUsbDeviceInfo.h,v $ sentry
  #define _KUSBDEVICEINFO_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
#ifdef _USE_STL
  #include <string>  //CString base class
#endif
#ifdef _USE_ATL
  #pragma include_alias( "KString.h", "atlstr.h" )
#endif
#include "KString.h" //CString class replacement
#include "KUsb.h"    //CUsbId class

///////////////////////////////////////////////////////////////////////////////
/*Data set describing a USB device. Data represent only a subset of possible
  information abut the USB device.
 */
class CUsbDeviceInfo : public CUsbId
{
public:
  CUsbDeviceInfo();
  ~CUsbDeviceInfo();
public:
  int GetPortNo() const;
  LPCTSTR GetPortNo(CString& strPortId) const;
  void SetPortNo(const int iPortId);
  void SetPortNo(const unsigned int nTier, const int iPortId);
  void ZeroPortNo();
  int  SearchTier() const;
  void Empty();

public:
  bool m_bHub;           //[out] device is a hub
  USB_CONNECTION_STATUS m_eStatus; //[out] device status
  int m_nTierLevel;      //[out] the topmost USB tier level whith described device
                         //[USB_ROOTLEVEL, USB_TOPLEVEL - 1]
  CString m_strVendor;   //[out] manufacturer of the device
  CString m_strProduct;  //[out} description of the device
  CString m_strSerialNo; //[in/out] serial number of the device

private:
  int m_nPortNo[USB_TOPLEVEL - 1];  //[in/out] number of the hub port number
                                    //where the device is connected to [1, n]

};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*
 */
inline CUsbDeviceInfo::CUsbDeviceInfo() :
  m_bHub(false),
  m_eStatus(NoDeviceConnected),
  m_nTierLevel(USB_ROOTLEVEL)
{
ZeroMemory(m_nPortNo, sizeof(m_nPortNo));
}

inline CUsbDeviceInfo::~CUsbDeviceInfo()
{
}

//-----------------------------------------------------------------------------
/*Set a tiered, one-based port (hub node) index for the current tier level.
  Because USB uses a tiered topology, identifying a device requires the port
  number and tier level. The tier level is maintained by m_nTierLevel field.

  Note: if tier level is out of proper range, the port index is not set.

  See also: USB_MAXCOUNT, USB_TOPLEVEL
 */
inline void CUsbDeviceInfo::SetPortNo(const int iPortId //[in] hub port number
                                      //in the range [1, n]
                                     )
{
#pragma warning (disable: 4127)
  ASSERT((m_nTierLevel >= USB_ROOTLEVEL) && (m_nTierLevel <= (USB_TOPLEVEL - 1)));
#pragma warning (default: 4127)
if ((m_nTierLevel >= USB_ROOTLEVEL) && (m_nTierLevel <= (USB_TOPLEVEL - 1)))
  m_nPortNo[m_nTierLevel - 1] = iPortId;
}

/*Set a tiered, one-based port (hub node) index for the given tier level.
  If tier level is out of proper range, the port index is not set.
 */
inline void CUsbDeviceInfo::SetPortNo(const unsigned int nTier, //[in] USB tier
                                      //level [USB_ROOTLEVEL, USB_TOPLEVEL - 1]
                                      const int iPortId //[in] hub port number
                                      //in the range [1, n]
                                     )
{
#pragma warning (disable: 4127)
  ASSERT((nTier >= USB_ROOTLEVEL) && (nTier <= (USB_TOPLEVEL - 1)));
#pragma warning (default: 4127)
if ((nTier >= USB_ROOTLEVEL) && (nTier <= (USB_TOPLEVEL - 1)))
  m_nPortNo[nTier - 1] = iPortId;
}

//-----------------------------------------------------------------------------
/*Returns USB hub port (node) index for the current tier level.
 */
inline int CUsbDeviceInfo::GetPortNo() const
{
#pragma warning (disable: 4127)
  ASSERT((m_nTierLevel >= USB_ROOTLEVEL) && (m_nTierLevel <= (USB_TOPLEVEL - 1)));
#pragma warning (default: 4127)
return m_nPortNo[m_nTierLevel - 1];
}

//-----------------------------------------------------------------------------
/*Annulling the port indexes and the current tier level.

  See also: USB_MAXCOUNT, USB_TOPLEVEL
 */
inline void CUsbDeviceInfo::ZeroPortNo()
{
ZeroMemory(m_nPortNo, sizeof(m_nPortNo));
m_nTierLevel = USB_ROOTLEVEL;
}

//-----------------------------------------------------------------------------
/*Port ID Search state table
      1 2 3 4 5 6  tier
      0:x:x:x:x:x  search all possible ports
      i:0:x:x:x:x  search only root hub node i
      i:j:0:x:x:x  search only extern hub node i:j
      i:j:k:0:x:x  search only extern hub node i:j:k
      ...

  Note: current tier level is maintained by m_nTierLevel member.

  Returns positive number (1) if required device could be connected to any port;
  zero (0) if required device have to be connected on specified port at
  the current tier level or negative number (-1) if the search should include
  the tier above the current one.
*/
inline int CUsbDeviceInfo::SearchTier() const
{
if (m_nPortNo[USB_ROOTLEVEL - 1] == 0)
  return 1; //Look for the device anywhere
else
  {
  //Note: port numbers should be in the range [1, USB_MAXCOUNT]; value 0 have
  //      special meaning for root tier and different for other levels.
  //Note: tier levels have one-based indexes.
  if (m_nPortNo[m_nTierLevel] == 0)
    return 0; //Stop search on this tier level
  else
    return -1; //Search in the next tier level
  }
}

//-----------------------------------------------------------------------------
/*Initializes all fields to the default state.
  All string members are emptied.
 */
inline void CUsbDeviceInfo::Empty()
{
m_wVid = USBVID_ANY;           //unspecified USB vendor
m_wPid = USBPID_ANY;           //unspecified USB product
m_bHub = false;                //device is not a hub
m_eStatus = NoDeviceConnected; //device status
m_strVendor.Empty();           //manufacturer of the device
m_strProduct.Empty();          //description of the device
m_strSerialNo.Empty();         //serial number of the device
ZeroPortNo();                  //hub node index
}

///////////////////////////////////////////////////////////////////////////////
#endif //__cplusplus

///////////////////////////////////////////////////////////////////////////////
#endif  //_KUSBDEVICEINFO_H_
/*****************************************************************************
 * $Log: KUsbDeviceInfo.h,v $
 * Revision 1.1  2009/08/28 13:57:26  ddarko
 * Extracted from KUsbHub
 *
 *****************************************************************************/
