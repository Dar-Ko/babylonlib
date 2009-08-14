/*$RCSfile: KGetUsbLangIds.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2009/08/14 18:25:19 $
  $Author: ddarko $

  Obtain list of the languges that a USB device supports.
  Note: Microsoft Windows specific (Win).
  2004-03-16 Darko Kolakovic
 */

// Group=Windows

#ifdef _WIN32 //Windows 32-bit platform

#if defined _ATL_VER
  #ifndef _USE_ATL
    #define _USE_ATL
  #endif
#endif

#ifdef _USE_ATL
  //Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)
  //or preprocessor reports unpaired #endif directive

  #include "stdafx.h" //Standard system header files
  #include "KTraceAtl.h"
  #pragma include_alias( "KString.h", "atlstr.h" )
#else
  #include <windows.h>
#endif

#ifdef _USE_STL
  #include <string>
#endif
#include "KString.h"
#include "KUsb.h"
#include "UsbIoCtl.h" //USB_DESCRIPTOR_REQUEST

//-----------------------------------------------------------------------------
/*Get the list of language codes supported by the USB device.
  The strings in a USB device may support multiple languages. Rquesting 
  the string with index zero for any language returns a string descriptor that
  contains an array of language codes supported by the device. 
  The device is identified by USB hub port on wich is attached.
  USB devices that omit all string descriptors shall not return an array of 
  LANGID codes.
  Note: the array of LANGID codes is not NULL-terminated. The size of the array
  (in bytes) is computed by subtracting two from the value of the first byte of
  the string descriptor.

  Returns number of elements in the language code list. Call GetLastError()
  to verify successful operation.

  See also: "Universal Serial Bus Specification Revision 1.1", 
  Chapters 9.5 Descriptors, 9.6.5 String;
  "Developing International Software for Windows 95 and Windows NT",
  Nadine Kano, Microsoft Press, Redmond, Washington;
  LANGID, MAXIMUM_USB_STRING_LENGTH, USB_STRING_DESCRIPTOR, USB_LANGID_LIST.
 */
unsigned int GetUsbLangIds(const HANDLE hHub, //[in] handle of the hub device
                        //containing the port from which the zeroth String 
                        //Descriptor will be requested.
                           const unsigned int nPortNo, //[in] port on
                        //the hub to which a device is attached from the range 
                        //[1, USB_HUB_DESCRIPTOR::bNumberOfPorts].
                           LANGID*  arrLanguageID, //[out] output buffer that is
                        //to receive array with language codes.
                           const unsigned int nSize //[in] number of elements 
                        //of the output buffer.
                              )
{
TRACE1(_T("GetUsbLangIds(nPortNo = %d)\n"), nPortNo);
//Disable warning C4127: conditional expression in ASSERT is constant
#pragma warning (disable: 4127)
  ASSERT((nPortNo > 0) && (nPortNo <= USB_MAXCOUNT));
  ASSERT(hHub != INVALID_HANDLE_VALUE);
  ASSERT(arrLanguageID != NULL);
  ASSERT(nSize > 0);
#pragma warning (default: 4127)

ULONG nResult = 0;

if ((nPortNo > 0) && 
    (nPortNo <= USB_MAXCOUNT) &&
    (arrLanguageID != NULL) &&
    (nSize > 0) &&
    (hHub != INVALID_HANDLE_VALUE))
  {
  const int USB_DESCRIPTOR_LANG_ID = 0;

  uint8_t usbDevResponse[sizeof(USB_LANGID_LIST) + 
                         USB_MAXCOUNT_LANGID * sizeof(LANGID)];

  const int SIZEOF_USB_DESCRIPTOR_REQUEST =  
        sizeof(((PUSB_DESCRIPTOR_REQUEST)usbDevResponse)->ConnectionIndex) +
        sizeof(((PUSB_DESCRIPTOR_REQUEST)usbDevResponse)->SetupPacket);

  #ifdef _DEBUG_VERBOSE
    if (SIZEOF_USB_DESCRIPTOR_REQUEST == sizeof(USB_DESCRIPTOR_REQUEST))
      {
      TRACE(_T("warning C4200:\n  nonstandard Microsoft extension used :\n  zero-sized array in struct USB_DESCRIPTOR_REQUEST.\n"));
      }
  #endif

  #pragma warning (disable: 4127)
    ASSERT((sizeof(usbDevResponse) - SIZEOF_USB_DESCRIPTOR_REQUEST) > 0);
  #pragma warning (default: 4127)

  //Set up request for a string desriptor
  ZeroMemory(usbDevResponse, sizeof(usbDevResponse)); //Zero fill the entire
                                                      //request structure
  //Indicate the port number to which the device of interest is attached
  ((PUSB_DESCRIPTOR_REQUEST)usbDevResponse)->ConnectionIndex = nPortNo;
  //Indicate desired string
  ((PUSB_DESCRIPTOR_REQUEST)usbDevResponse)->SetupPacket.wValue =
    USB_DESCRIPTOR_REQUEST_VALUE(USB_DESCRIPTOR_TYPE_STRING, USB_DESCRIPTOR_LANG_ID);
  //Indicate size of the space allowed for data transfer
  ((PUSB_DESCRIPTOR_REQUEST)usbDevResponse)->SetupPacket.wLength = 
    (USHORT)(sizeof(usbDevResponse) - SIZEOF_USB_DESCRIPTOR_REQUEST);

  //Get the string descriptor
  if(DeviceIoControl( hHub,
                      IOCTL_USB_GET_DESCRIPTOR_FROM_NODE_CONNECTION,
                      (PUSB_DESCRIPTOR_REQUEST)usbDevResponse,
                      sizeof(usbDevResponse),
                      (PUSB_DESCRIPTOR_REQUEST)usbDevResponse,
                      sizeof(usbDevResponse),
                      &nResult,
                      NULL ) == TRUE)
    {
    if (nResult > 1) //Sanity check
      {
      USB_LANGID_LIST& usbDesc = 
        *((USB_LANGID_LIST*)((PUSB_DESCRIPTOR_REQUEST)usbDevResponse)->Data);
      if ((usbDesc.usbLangIdDescriptor.bLength == 
           nResult - SIZEOF_USB_DESCRIPTOR_REQUEST) &&
          (usbDesc.usbLangIdDescriptor.bLength % sizeof(LANGID) == 0) )
        {
        if (usbDesc.usbLangIdDescriptor.bDescriptorType == 
            USB_STRING_DESCRIPTOR_TYPE)
          {
          //Get length of the desription in characters
          nResult = (usbDesc.usbLangIdDescriptor.bLength - 2) / sizeof(LANGID);
          //Copy the list
          unsigned int i = (nResult < nSize) ? nResult : nSize;
          while( i > 0 )
            {
            i--;
            arrLanguageID[i] = usbDesc.usbLangIdDescriptor.wLangId[i]; 
            }
          }
        else
          {
          //IOCTL returned wrong descriptor type
          nResult = 0;
          SetLastError(ERROR_INVALID_CATEGORY);
          }
        }
      else
        {
        //IOCTL returned wrong number of bytes
        nResult = 0;
        SetLastError(ERROR_INVALID_DATA);
        }
      }
    }
  else
    {
    //IOCTL failed.To get extended error information, call GetLastError().
    TRACE1(_T("  DeviceIoControl failed! Error 0x%0.8X.\n"), GetLastError());
    }
  }
else
  {
  SetLastError(ERROR_INVALID_PARAMETER);
  }

return (unsigned int)nResult;
}
///////////////////////////////////////////////////////////////////////////////
#endif //_WIN32

/*****************************************************************************
 * $Log: KGetUsbLangIds.cpp,v $
 * Revision 1.2  2009/08/14 18:25:19  ddarko
 * SetLastError
 *
 * Revision 1.1  2009/08/13 21:24:52  ddarko
 * GetUsbLangIds()
 *
 *****************************************************************************/
