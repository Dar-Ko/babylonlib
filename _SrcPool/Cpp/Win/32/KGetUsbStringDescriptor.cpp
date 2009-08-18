/*$RCSfile: KGetUsbStringDescriptor.cpp,v $: implementation file
  $Revision: 1.6 $ $Date: 2009/08/18 14:18:04 $
  $Author: ddarko $

  Obtain USB string descriptor.
  Note: Microsoft Windows specific (Win).
  Copyright: 1997-1998 Microsoft Corporation
  2004-03-15 Darko Kolakovic
  1997-25-04: Microsoft Corporation
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
/*Obtains a string descriptor of the device attached to the specified USB hub 
  node.

  String descriptors provides displayable information describing a descriptor
  in human-readable form. The inclusion of string descriptors is optional. However,
  the reference fields like String Descriptor index in Standard Device Descriptor
  are mandatory.
  If a device does not support string descriptors, String Descriptor index must
  be zero to indicate no string descriptor is available.
  String descriptors use Unicode encodings and may support multiple
  languages.

  Note: the Unicode string descriptor is not zero-terminated. The string length
  in bytes is computed by subtracting two from the value of the descriptor
  length (first byte of the descriptor).

  Returns requested information, if the device contains one or the empty string.
  Call GetLastError() to verify successful operation.

  See also: "Universal Serial Bus Specification Revision 1.1", 
  Chapters 9.5 Descriptors, 9.6.5 String;
  "The Unicode Standard, Worldwide Character Encoding, Version 1.0", Volumes 1 and 2, 
  The Unicode Consortium; LANGID, USB_MAXCOUNT_LANGID, USB_STRING_DESCRIPTOR.
 */
CString GetUsbStringDescriptor(const HANDLE hHub, //[in] handle of the hub device
                        //containing the port from which the String Descriptor 
                        //will be requested.
                               const unsigned int nPortNo, //[in] port on
                        //the hub to which a device is attached from the range 
                        //[1, USB_HUB_DESCRIPTOR::bNumberOfPorts].
                               const UCHAR  cDescriptorId, //[in] String 
                        //Descriptor index [1, 255].
                               LANGID  nLanguageID //[in] = 0 language code
                                //in which the string should be requested
                              )
{
TRACE1(_T("GetUsbStringDescriptor(id = %d)\n"), cDescriptorId);
//Disable warning C4127: conditional expression in ASSERT is constant
#pragma warning (disable: 4127)
  ASSERT((nPortNo > 0) && (nPortNo <= USB_MAXCOUNT));
  ASSERT(cDescriptorId > 0); //String Descriptor 0 contains the array of
                            //supported Language IDs
  ASSERT(hHub != INVALID_HANDLE_VALUE);
#pragma warning (default: 4127)

CString strResult;

if ((nPortNo > 0) && 
    (nPortNo <= USB_MAXCOUNT) &&
    (cDescriptorId > 0) &&
    (hHub != INVALID_HANDLE_VALUE))
  {
  const LANGID LANGID_EN_US = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US); //0x0409 English (U.S.)
  if (nLanguageID == 0)
    nLanguageID = LANGID_EN_US;
  //TODO: obatin 1st language from the list

  uint8_t usbDevResponse[sizeof(USB_DESCRIPTOR_REQUEST) + 
                         MAXIMUM_USB_STRING_LENGTH];

  ULONG   nBytesReturned; //actual size of the response

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
    USB_DESCRIPTOR_REQUEST_VALUE(USB_DESCRIPTOR_TYPE_STRING, cDescriptorId);
  ((PUSB_DESCRIPTOR_REQUEST)usbDevResponse)->SetupPacket.wIndex = nLanguageID;
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
                      &nBytesReturned,
                      NULL ) == TRUE)
    {
    if (nBytesReturned > 1) //Sanity check
      {
      USB_STRING_DESCRIPTOR& usbStrDescriptor = 
        *((PUSB_STRING_DESCRIPTOR)((PUSB_DESCRIPTOR_REQUEST)usbDevResponse)->Data);
      if ((usbStrDescriptor.bLength == nBytesReturned - SIZEOF_USB_DESCRIPTOR_REQUEST) &&
          (usbStrDescriptor.bLength % sizeof(wchar_t) == 0) )
        {
        if (usbStrDescriptor.bDescriptorType == USB_STRING_DESCRIPTOR_TYPE)
          {
          //Get length of the desription in characters
          nBytesReturned = (usbStrDescriptor.bLength - 2) / sizeof(wchar_t);
          //Copy the string
          #ifdef _UNICODE
            memcpy(strResult.GetBuffer(nBytesReturned),
                  usbStrDescriptor.bString,
                  (usbStrDescriptor.bLength - 2));
            strResult.ReleaseBuffer(nBytesReturned);
          #else
            LPWSTR strwTemp = new wchar_t[nBytesReturned + 1];
            if (strwTemp != NULL)
              {
              memcpy(strwTemp,
                    usbStrDescriptor.bString,
                    (usbStrDescriptor.bLength - 2));
              strwTemp[nBytesReturned] = (wchar_t) 0;
              strResult = strwTemp;
              delete[] strwTemp;
              }
          #endif
          }
        else
          {
          //IOCTL returned wrong descriptor type
          SetLastError(ERROR_INVALID_CATEGORY);
          }
        }
      else
        {
        //IOCTL returned wrong number of bytes
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

return strResult;
}
///////////////////////////////////////////////////////////////////////////////
#endif //_WIN32

/*****************************************************************************
 * $Log: KGetUsbStringDescriptor.cpp,v $
 * Revision 1.6  2009/08/18 14:18:04  ddarko
 * fixed nBytesReturned
 *
 * Revision 1.5  2009/08/14 18:25:19  ddarko
 * SetLastError
 *
 * Revision 1.4  2009/08/13 21:24:52  ddarko
 * GetUsbLangIds()
 *
 * Revision 1.3  2009/08/12 17:21:22  ddarko
 * GetUsbStringDescriptor()
 *
 * Revision 1.2  2009/08/11 21:20:58  ddarko
 * USB string descriptor
 *
 * Revision 1.1  2009/08/11 13:43:31  ddarko
 * Windows DDK, UsbView
 *
 *****************************************************************************/

/*Copyright (c) 1997-1998 Microsoft Corporation
  Reference:            Windows DDK, USBView example, enum.c
  Environment:          user mode
  Revision History:     04-25-97 : created
 */
