/*$RCSfile: KGetUsbStringDescriptor.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2009/08/11 13:43:31 $
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

//-----------------------------------------------------------------------------
//
//
// hHubDevice - Handle of the hub device containing the port from which the
// String Descriptor will be requested.
//
// ConnectionIndex - Identifies the port on the hub to which a device is
// attached from which the String Descriptor will be requested.
//
// DescriptorIndex - String Descriptor index.
//
// LanguageID - Language in which the string should be requested.
//
//*****************************************************************************

CString GetUsbStringDescriptor(const HANDLE hHubDevice,
                                const ULONG   ConnectionIndex,
                                const UCHAR   DescriptorIndex,
                                const LANGID  LanguageID
                                )
{
    BOOL    success;
    ULONG   nBytes;
    ULONG   nBytesReturned;

    UCHAR   stringDescReqBuf[sizeof(USB_DESCRIPTOR_REQUEST) +
                             MAXIMUM_USB_STRING_LENGTH];

    PUSB_DESCRIPTOR_REQUEST pusbDescReq = (PUSB_DESCRIPTOR_REQUEST)stringDescReqBuf;

    nBytes = sizeof(stringDescReqBuf);

 
    // Zero fill the entire request structure
    //
    memset(pusbDescReq, 0, nBytes);

    // Indicate the port from which the descriptor will be requested
    //
    pusbDescReq->ConnectionIndex = ConnectionIndex;

    //
    // USBHUB uses URB_FUNCTION_GET_DESCRIPTOR_FROM_DEVICE to process this
    // IOCTL_USB_GET_DESCRIPTOR_FROM_NODE_CONNECTION request.
    //
    // USBD will automatically initialize these fields:
    //     bmRequest = 0x80
    //     bRequest  = 0x06
    //
    // We must inititialize these fields:
    //     wValue    = Descriptor Type (high) and Descriptor Index (low byte)
    //     wIndex    = Zero (or Language ID for String Descriptors)
    //     wLength   = Length of descriptor buffer
    //
    pusbDescReq->SetupPacket.wValue = (USB_STRING_DESCRIPTOR_TYPE << 8)
                                        | DescriptorIndex;

    pusbDescReq->SetupPacket.wIndex = LanguageID;

    pusbDescReq->SetupPacket.wLength = (USHORT)(nBytes - sizeof(USB_DESCRIPTOR_REQUEST));

    // Now issue the get descriptor request.
    //
    success = DeviceIoControl(hHubDevice,
                              IOCTL_USB_GET_DESCRIPTOR_FROM_NODE_CONNECTION,
                              pusbDescReq,
                              nBytes,
                              pusbDescReq,
                              nBytes,
                              &nBytesReturned,
                              NULL);

    //
    // Do some sanity checks on the return from the get descriptor request.
    //

    if (!success)
    {
        OOPS();
        return NULL;
    }

    if (nBytesReturned < 2)
    {
        OOPS();
        return NULL;
    }

    PUSB_STRING_DESCRIPTOR  pusbStrDescriptor= (PUSB_STRING_DESCRIPTOR)(pusbDescReq+1);
    PSTRING_DESCRIPTOR_NODE pusbStrDescriptorNode;

    if (pusbStrDescriptor->bDescriptorType != USB_STRING_DESCRIPTOR_TYPE)
    {
        OOPS();
        return NULL;
    }

    if (pusbStrDescriptor->bLength != nBytesReturned - sizeof(USB_DESCRIPTOR_REQUEST))
    {
        OOPS();
        return NULL;
    }

    if (pusbStrDescriptor->bLength % 2 != 0)
    {
        OOPS();
        return NULL;
    }

    //
    // Looks good, allocate some (zero filled) space for the string descriptor
    // node and copy the string descriptor to it.
    //

    pusbStrDescriptorNode = (PSTRING_DESCRIPTOR_NODE)ALLOC(sizeof(STRING_DESCRIPTOR_NODE) +
                                                    pusbStrDescriptor->bLength);

    if (pusbStrDescriptorNode == NULL)
    {
        OOPS();
        return NULL;
    }

    pusbStrDescriptorNode->DescriptorIndex = DescriptorIndex;
    pusbStrDescriptorNode->LanguageID = LanguageID;

    memcpy(pusbStrDescriptorNode->StringDescriptor,
           pusbStrDescriptor,
           pusbStrDescriptor->bLength);

    return pusbStrDescriptorNode;
}


///////////////////////////////////////////////////////////////////////////////
#endif //_WIN32

/*****************************************************************************
 * $Log: KGetUsbStringDescriptor.cpp,v $
 * Revision 1.1  2009/08/11 13:43:31  ddarko
 * Windows DDK, UsbView
 *
 *****************************************************************************/

/*Copyright (c) 1997-1998 Microsoft Corporation
  Reference:            Windows DDK, USBView example, enum.c
  Environment:          user mode
  Revision History:     04-25-97 : created
 */
