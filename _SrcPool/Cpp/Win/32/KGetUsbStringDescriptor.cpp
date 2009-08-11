/*$RCSfile: KGetUsbStringDescriptor.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2009/08/11 21:20:58 $
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
#else
  #include <windows.h>
#endif

    //
    // Get the array of supported Language IDs, which is returned
    // in String Descriptor 0
    //
    supportedLanguagesString = GetStringDescriptor(hHubDevice,
                                                   ConnectionIndex,
                                                   0,
                                                   0);
    numLanguageIDs = (StringDescriptor->bLength - 2) / 2;
    languageIDs = &StringDescriptor->bString[0];
//-----------------------------------------------------------------------------
/*Obtains a string descriptor of the device attached to the specified USB hub 
  node.

  String descriptors provides displayable information describing a descriptor
  in human-readable form. The inclusion of string descriptors is optional. However,
  the reference fields like String Descriptor index in Standard Device Descriptor
  are mandatory.
  If a device does not support string descriptors, String Descriptor index must
  be zero to indicate no string descriptor is available.
  String descriptors use Unicode encodings and may support multiple languages.

  Note: the Unicode string descriptor is not zero-terminated. The string length
  in bytes is computed by subtracting two from the value of the descriptor
  length (first byte of the descriptor).

  See also: "Universal Serial Bus Specification Revision 1.1", 
  Chapters 9.5 Descriptors, 9.6.5 String;
  "The Unicode Standard, Worldwide Character Encoding, Version 1.0", Volumes 1 and 2, 
  The Unicode Consortium; LANGID, MAXIMUM_USB_STRING_LENGTH.
 */
CString GetUsbStringDescriptor(const HANDLE hHub, //[in] handle of the hub device
                        //containing the port from which the String Descriptor 
                        //will be requested.
                               const unsigned int nPortNo, //[in] port on
                        //the hub to which a device is attached from the range 
                        //[1, USB_HUB_DESCRIPTOR::bNumberOfPorts].
                               const UCHAR   cDescriptorId, //[in] String 
                        //Descriptor index [1, 255].
                               LANGID  nLanguageID //[in] = 0 language code
                                //in which the string should be requested
                              )
{
TRACE1(_T("GetUsbStringDescriptor(id=%d)\n"), cDescriptorId);

CString strResult;
ASSERT((nPortNo > 0) && (nPortNo <= USB_MAXCOUNT));
ASSERT(cDescriptorId > 0); //String Descriptor 0 contains the array of
                           //supported Language IDs
ASSERT(hHub != INVALID_HANDLE_VALUE);

if ((nPortNo > 0) && 
    (nPortNo <= USB_MAXCOUNT) &&
    (cDescriptorId > 0) &&
    (hHub != INVALID_HANDLE_VALUE))
  {
  const LANGID LANGID_EN_US = MAKELANGID(LANG_ENGLISH. SUBLANG_US); //0x0409 English (U.S.)
  if (nLanguageID == 0)
    nLanguageID = LANGID_EN_US;
  //TODO: obatin 1st language from the list

  uint8_t usbDevResponse[sizeof(USB_DESCRIPTOR_REQUEST) + 
                         MAXIMUM_USB_STRING_LENGTH];

  ULONG   nBytesReturned; //actual size of the response

  //Set up request for a string desriptor

  ZeroMemory(usbDevResponse, sizeof(usbDevResponse)); //Zero fill the entire
                                                      //request structure
  //Indicate the port number to which the device of interest is attached
  ((PUSB_DESCRIPTOR_REQUEST)usbDevResponse)->ConnectionIndex = nPortNo;
  //Indicate desired string
  ((PUSB_DESCRIPTOR_REQUEST)usbDevResponse)->SetupPacket.wValue = 
    USB_DESCRIPTOR_REQUEST_VALUE(USB_STRING_DESCRIPTOR_TYPE, cDescriptorId);
  ((PUSB_DESCRIPTOR_REQUEST)usbDevResponse)->SetupPacket.wIndex = LanguageID;
  //Indicate size of the space allowed for data transfer
  ((PUSB_DESCRIPTOR_REQUEST)usbDevResponse)->SetupPacket.wLength = 
    (USHORT)(sizeof(usbDevResponse) - sizeof(USB_DESCRIPTOR_REQUEST));

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
        (*PUSB_STRING_DESCRIPTOR)((PUSB_DESCRIPTOR_REQUEST)usbDevResponse)->Data;
      if ((usbStrDescriptor.bLength == nBytesReturned - sizeof(USB_DESCRIPTOR_REQUEST)) &&
          (usbStrDescriptor.bLength % sizeof(wchar_t) == 0) )
        {
        if (usbStrDescriptor.bDescriptorType == USB_STRING_DESCRIPTOR_TYPE)
          {
          strResult.Copy(usbStrDescriptor.bString, (usbStrDescriptor.bLength - 2) % sizeof(wchar_t))
          }

        }
      }
    }
  else
    {
      //todo error
    }

  }

return strResult;
}
///////////////////////////////////////////////////////////////////////////////
#endif //_WIN32

/*****************************************************************************
 * $Log: KGetUsbStringDescriptor.cpp,v $
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

/*Universal Serial Bus Specification Revision 1.1", 9.6.5 String;
  The strings in a USB device may support multiple languages. When requesting a
  string descriptor, the requester specifies the desired language using
  a sixteen-bit language ID (LANGID) defined by Microsoft for Windows as 
  described in Developing International Software for Windows 95 and Windows NT,
  Nadine Kano, Microsoft Press, Redmond, Washington. 
  String index zero for all languages returns a string descriptor that contains
  an array of two-byte LANGID codes supported by the device.
  Table 9-11 shows the LANGID code array. A USB device may omit all string
  descriptors.
  USB devices that omit all string descriptors shall not return an array of 
  LANGID codes.
  The array of LANGID codes is not NULL-terminated. The size of the array
  (in bytes) is computed by subtracting two from the value of the first byte of
  the descriptor.
*/