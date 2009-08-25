/*$Workfile: KUsbHub.h$: header file
  $Revision: 1.20 $ $Date: 2009/08/25 21:27:15 $
  $Author: ddarko $

  Universal Serial Bus (USB) Host Controller
  Copyright: CommonSoft Inc
  2004-03-09 Darko Kolakovic
 */

#ifndef _KUSBHUB_H_
    //$Workfile: KUsbHub.h$ sentry
  #define _KUSBHUB_H_

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
#include "UsbIoCtl.h"//USB_CONNECTION_STATUS enum
#include "KUsb.h"    //CUsbId class

LPCTSTR GetUsbStatus(const USB_CONNECTION_STATUS& eStatus);

///////////////////////////////////////////////////////////////////////////////
/*USB Device Information container.
  A USB device is attached to the hub a port.
  A USB device can be any kind of peripheral device, such as a keyboard, mouse,
  game controller, printer, USB hub and so forth.
 */
class CUsbDevice : public CUsbId
{
public:
  CUsbDevice();
  ~CUsbDevice();
public:
  bool GetStringDescriptor(HANDLE hUsbHub,
                           const unsigned int nPortId,
                           const unsigned int nStringId,
                           LANGID nLangId,
                           CString& strResult);
  bool CUsbDevice::HasStringDescriptor(
        const PUSB_DEVICE_DESCRIPTOR pusbDevDescriptor,
        const PUSB_CONFIGURATION_DESCRIPTOR pusbConfigDescriptor = NULL
        );

  CString Bcd2Str(const uint16_t nBcd);
  void Empty();

public:
  bool m_bHub;               //device is a hub
  USB_CONNECTION_STATUS m_eStatus; //device status
  CString m_strDevice;       //USB device path
  CString m_strDescription;  //description of the device
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Default constructor
 */
inline CUsbDevice::CUsbDevice() :
    m_eStatus(NoDeviceConnected),
    m_bHub(false)
{
}

inline CUsbDevice::~CUsbDevice()
{
}


//-----------------------------------------------------------------------------
/*Converts four digit binary-coded decimal (BCD) number to a text, formatted as

      nn.nn

  Each decimal digit is stored in a four-bit 8421 coded nibble. Leading and
  trailing zeroes will be truncated.

  Returns text representation of a BCD number.
 */
inline CString CUsbDevice::Bcd2Str(const uint16_t nBcd //[in] binary 8421 coded 
                                                       //decimal number
                                   )
{
TCHAR szResult[6]; //decimal number
//TODO: redo HIBYTE & LOBYTE for bigendian CPU; MSVC macros are for littleendians
szResult[0] = _T('0') + ((0xF0 & HIBYTE(nBcd)) >> 4);
szResult[1] = _T('0') + ( 0x0F & HIBYTE(nBcd));
szResult[2] = _T('.');
szResult[3] = _T('0') + ((0xF0 & LOBYTE(nBcd)) >> 4);
szResult[4] = _T('0') + ( 0x0F & LOBYTE(nBcd));
//Cut-off trailing zero character
if (szResult[4] == _T('0'))
  szResult[4] =  _T('\0');
else
  szResult[5] = _T('\0'); //terminating zero

CString strResult = (szResult[0] == _T('0')) ?
    (LPCTSTR)(&szResult[1]) : szResult;
return strResult;
}

//-----------------------------------------------------------------------------
/*Intilizes all fields to the default state.
  All string members are emptied and device status is set to NoDeviceConnected.
 */
inline void CUsbDevice::Empty()
{
m_wVid = USBVID_ANY;           //unspecified USB vendor
m_wPid = USBPID_ANY;           //unspecified USB product
m_strDevice.Empty();           //USB device path
m_strDescription.Empty();      //description of the device
m_bHub = false;                //device is not a hub
m_eStatus = NoDeviceConnected; //device status
}

///////////////////////////////////////////////////////////////////////////////
/*Data set describing a USB device. Data respresent onaly a subset of possible
  information abut the USB device.
 */
class CUsbDeviceInfo : public CUsbId
{
public:
  CUsbDeviceInfo();
  ~CUsbDeviceInfo();
public:
  int GetPortNo() const;
  void SetPortNo(const int iPortId);
  void ZeroPortNo();
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

  See also: USB_MAXCOUNT, USB_TOPLEVEL
 */
inline void CUsbDeviceInfo::SetPortNo(const int iPortId //[in] hub port number
                                      //in the range [1, n]
                                     )
{
#pragma warning (disable: 4127)
  ASSERT((m_nTierLevel >= USB_ROOTLEVEL) && (m_nTierLevel <= (USB_TOPLEVEL - 1)));
#pragma warning (default: 4127)
m_nPortNo[m_nTierLevel - 1] = iPortId;
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
/*Intilizes all fields to the default state.
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

//#include "KArrayPtr.h" //CArrayPtr template
#ifdef _USE_ATL
  #include <atlsimpcoll.h>
  #define CArray CAtlArray
#endif
#ifdef _USE_STL
  #include "STL/KArrayStl.h" //CArray template
#endif
///////////////////////////////////////////////////////////////////////////////
/*
 */
class CUsbDeviceArray : public CArray<CUsbDevice*>
{
public:
  CUsbDeviceArray();
  ~CUsbDeviceArray();
private:
  //Usage of the copy constructor is prohibited
  CUsbDeviceArray(const CUsbDeviceArray&){};
public:
  void  RemoveAll();

  #ifdef _DEBUG
    void Dump();
  #endif
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*
 */
inline CUsbDeviceArray::CUsbDeviceArray()
{
}

inline CUsbDeviceArray::~CUsbDeviceArray()
{
}

//-----------------------------------------------------------------------------
/*Deletes all elements of the array and frees allocated resources.
 */
inline void CUsbDeviceArray::RemoveAll()
{
TRACE1(_T("CUsbDeviceArray::RemoveAll() @ 0x%0.8X\n"), this);
int i = 0;
while (i < (int)GetCount())
  {
  CUsbDevice* pElement = GetAt(i);
  if (pElement != NULL)
    {
    delete pElement;
    }
  i++;
  }
CArray<CUsbDevice*>::RemoveAll();
}

#ifdef _DEBUG
  //---------------------------------------------------------------------------
  /*Dumps all elements of the array.
   */
  inline void CUsbDeviceArray::Dump()
  {
  TRACE1(_T("CUsbDeviceArray::Dump(this = 0x%0.8X)\n"), this);
  int i = 0;
  TRACE1(_T("  number of elements = %d\n"),GetCount());
  while (i < (int)GetCount())
    {
    TRACE2(_T("   %0.2d. 0x%0.8X\n"), i, GetAt(i) );
    i++;
    }
  }
#endif

///////////////////////////////////////////////////////////////////////////////
/*Handles the USB hub.
  A USB hub is a device that allows many USB devices to be connected to a
  single USB port on the host computer or another hub.

  Hub provides multiple ports, for attaching devices to the USB bus.
  Hubs are also responsible for detecting devices that are plugged in or
  unplugged and for providing power for attached devices.
  Hubs are either bus-powered, drawing power directly from the USB bus or
  self-powered, drawing power from an external power supply.
  Bus-powered hubs are capable of providing 100 mA
  per port for attached devices and they can provide a maximum of four ports
  for devices to be plugged into.
  Self-powered hubs, on the other hand, typically provide 500 mA per port
  and they can provide more than four ports.
  Hubs can be stand-alone devices or they can be integrated into other devices
  such as keyboards and monitors.

  See also: CUsbDeviceTree, CUsbHostController, CUsbDevice
 */
class CUsbHub : public CUsbDevice
{
public:
  CUsbHub();
  CUsbHub(const CUsbHub& usbSrc);
  CUsbHub(const CUsbDevice& usbSrc);
  ~CUsbHub();
  unsigned int Enumerate(LPCTSTR szDevicePath);
  bool Find(const uint16_t wVendorId,
            const uint16_t wProductId,
            CUsbDeviceInfo* pDeviceInfo = NULL);
  bool FindNext(const uint16_t wVendorId,
                const uint16_t wProductId,
                CUsbDeviceInfo* pDeviceInfo = NULL);
  uint16_t GetPortCount() const;
  USB_CONNECTION_STATUS GetStatus(const uint16_t nPortNo) const;

protected:
  void Erase();

protected:
  CUsbDeviceArray m_usbNodeList; //hub node connections (ports)
  int m_iLastNodeAccessed; //one-based index of the hub node (port) accessed while
                           //searching for a device [1, m_usbNodeList.GetSize] 
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Default constructor
 */
inline CUsbHub::CUsbHub() :
  m_iLastNodeAccessed(-1)
{
m_bHub = true;
}

inline CUsbHub::CUsbHub(const CUsbDevice& usbSrc) :
  CUsbDevice(usbSrc),
  m_iLastNodeAccessed(-1)
{
m_bHub = true;
}

inline CUsbHub::CUsbHub(const CUsbHub& usbSrc) :
  CUsbDevice((CUsbDevice)usbSrc),
  m_iLastNodeAccessed(usbSrc.m_iLastNodeAccessed)
{
m_usbNodeList.Copy(usbSrc.m_usbNodeList);
}

inline CUsbHub::~CUsbHub()
{
Erase();
}

//-----------------------------------------------------------------------------
/*
 */
inline uint16_t CUsbHub::GetPortCount() const
{
return (uint16_t)m_usbNodeList.GetCount();
}

//-----------------------------------------------------------------------------
/*Obtains the status of the USB connection node.
  
  Returns the current status of the device attached to the hub port or
  NoDeviceConnected if the port is not available or not used.

  See also: USB_CONNECTION_STATUS
 */
inline USB_CONNECTION_STATUS CUsbHub::GetStatus(const uint16_t nPortNo //[in]
                        //hub port number that the device is connected to [1, n]
                                               ) const
{
if ( (nPortNo == 0) || (nPortNo > GetPortCount()) )
  return NoDeviceConnected;
CUsbDevice* pDev = m_usbNodeList[nPortNo - 1];
if (pDev == NULL)
  return NoDeviceConnected;
return (pDev->m_eStatus);
}

//-----------------------------------------------------------------------------
/*Cleanup residual data structures and statuses
 */
inline void CUsbHub::Erase()
{
m_usbNodeList.RemoveAll();
m_iLastNodeAccessed = -1;
}

///////////////////////////////////////////////////////////////////////////////
/*Universal Serial Bus (USB) host controller (also known as the root, root tier
  or the root hub) controls all traffic on the data bus and also functions as
  a hub. One host controller can control several USB ports.
 */
class CUsbHostController : public CUsbHub
{
public:

  CUsbHostController(const CUsbHostController& src) :
      CUsbHub((CUsbHub)src)
  {
  };

  CUsbHostController()
  {
  };
  bool GetDeviceInfo(const unsigned int nMemberIndex = 0);

protected:
  bool GetRootHub(LPCTSTR szDevicePath, CString& strRootHubPath);
};

#ifdef _USE_ATL
  #include <atlsimpcoll.h>
  #define CArray CAtlArray
#endif
#ifdef _USE_STL
  #include "STL/KArrayStl.h" //CArray template
#endif
///////////////////////////////////////////////////////////////////////////////
/*This class browses all USB host controllers USB hubs and USB devices
  attached on the system.

  USB uses a tiered topology so that you can simultaneously attach up to 127
  devices to the bus.
  There always exists one hub known as the root hub, which is built into
  the host controller.
  USB supports up to seven tier levels, including the root tier and five common
  hubs. The topmost tier supports only a single nonhub device.

      Tier level:    1                  2         3      ...       7
            +-USB Host Controller -+- Device
            |   (root hub)         |          +- Device
            |                      +-- Hub ---+- Device
       PCI -+                                 +-- Hub -- ... --- Device
            |
            +-USB Host Controller --- Device
            |   (root hub)
            |
            .
            .
            .

  There are three types of USB components: host controller, hub and device.

  See also: CUsbHostController, CUsbHub, CUsbDevice, USB_TOPLEVEL
 */
class CUsbDeviceTree
{
public:
  CUsbDeviceTree();
  ~CUsbDeviceTree();
  int Enumerate();
  bool GetDevice(const uint16_t wVendorId,
                 const uint16_t wProductId,
                 CUsbDeviceInfo* pDeviceInfo = NULL);
  bool GetNextDevice(const uint16_t wVendorId,
                     const uint16_t wProductId,
                     CUsbDeviceInfo* pDeviceInfo = NULL);
  bool HasDevice(const uint16_t wVendorId,
                 const uint16_t wProductId);
  void RemoveAll();
public:
  CArray<CUsbHostController*> m_usbRootList; //list of available USB host
                                             //controllers (root hubs)
protected:
  int m_iLastNodeAccessed; //one-based index of the root hub node accessed while
                           //searching for a device [1, m_usbRootList.GetSize] 
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*
 */
inline CUsbDeviceTree::CUsbDeviceTree() :
  m_iLastNodeAccessed(-1)
{
}

inline CUsbDeviceTree::~CUsbDeviceTree()
{
RemoveAll();
}

//-----------------------------------------------------------------------------
/*Find the USB device specified by a vendor (VID) and product identification
  (PID) number in the USB device tree.

  Returns: true if the requested device is found in the
  USB device tree. Returns false if the device is not present.

  See also: USB Implementers Forum, Inc (USB-IF) at http://www.usb.org; CUsbId,
  SP_DEVICE_INTERFACE_DETAIL_DATA, SP_DEVINFO_DATA, <setupapi.h>,
  CUsbDeviceTree::GetDevice();
 */
inline bool CUsbDeviceTree::HasDevice(const uint16_t wVendorId, //[in] USB device
                                             //vendor identification (VID) number
                                      const uint16_t wProductId //[in] USB product
                                             //identification (PID) number
                                      )
{
return GetDevice(wVendorId, wProductId);
}

//-----------------------------------------------------------------------------
/*Deletes all elements from the host controller list.
 */
inline void CUsbDeviceTree::RemoveAll()
{
TRACE(_T("CUsbDeviceTree::RemoveAll()\n"));
int i = 0;
while(i < (int)m_usbRootList.GetCount())
  {
  CUsbHostController* pElement = m_usbRootList.GetAt(i);
  if (pElement != NULL)
    delete pElement;
  i++;
  }
m_usbRootList.RemoveAll();
m_iLastNodeAccessed = -1;
}

///////////////////////////////////////////////////////////////////////////////
#endif //__cplusplus

///////////////////////////////////////////////////////////////////////////////
#endif  //_KUSBHUB_H_
/*****************************************************************************
 * $Log: KUsbHub.h,v $
 * Revision 1.20  2009/08/25 21:27:15  ddarko
 * *** empty log message ***
 *
 * Revision 1.19  2009/08/24 22:02:52  ddarko
 * USB tier level
 *
 * Revision 1.18  2009/08/21 21:24:03  ddarko
 * CUsbDevice::GetStringDescriptor()
 *
 * Revision 1.17  2009/08/20 21:23:41  ddarko
 * Added search index member
 *
 * Revision 1.16  2009/08/19 21:14:31  ddarko
 * CUsbDevice::Empty
 *
 * Revision 1.15  2009/08/14 18:27:14  ddarko
 * CUsbHub::GetStatus()
 *
 * Revision 1.14  2009/08/11 21:20:31  ddarko
 * USB string descriptor
 *
 * Revision 1.13  2009/08/07 21:45:26  ddarko
 * Bcd2Str
 *
 * Revision 1.12  2009/07/22 19:12:03  ddarko
 * Use CAtlArray
 *
 * Revision 1.11  2009/07/22 16:46:15  ddarko
 * Replaced arrays with arrays od references
 *
 * Revision 1.10  2009/07/21 22:19:27  ddarko
 * Find(vid, pid)
 *
 * Revision 1.9  2009/07/20 21:51:12  ddarko
 * *** empty log message ***
 *
 * Revision 1.8  2009/07/16 21:50:23  ddarko
 * CUsbDeviceArray
 *
 * Revision 1.7  2009/07/14 21:36:24  ddarko
 * Code cleanup
 *
 * Revision 1.6  2009/07/12 21:10:26  ddarko
 * Comments
 *
 * Revision 1.5  2009/07/10 21:34:31  ddarko
 * Renamed methods
 *
 * Revision 1.4  2009/07/08 21:51:07  ddarko
 * CUsbHostController
 *
 * Revision 1.3  2009/07/06 21:38:26  ddarko
 * Comment
 *
 * Revision 1.2  2009/07/02 21:44:13  ddarko
 * Excluded some Windows specifics
 *
 * Revision 1.1  2009/07/02 20:31:15  ddarko
 * Moved from platform specific directory
 *
 *****************************************************************************/
