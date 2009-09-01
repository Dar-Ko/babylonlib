/*$RCSfile: TestUsb.cpp,v $: implementation file
  $Revision: 1.4 $ $Date: 2009/09/01 15:47:33 $
  $Author: ddarko $

  Test LIBUSB-WIN32, Generic Windows USB Library.
  Copyright (C) 1997-2001 GMD - German National Research Center for Information
               Technology
  Copyright (C) 2002-2004 Fraunhofer Institute for Media Communication
  2009-08-14 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#if !defined _KTESTLOG_H_
 #error wrong stdafx.h header is included!
 //The project options for this module have "..\..\Win\32" in
 //additional include path
#endif

#include <errno.h>
#include <stdio.h>  // printf
#include <string.h> // memset

/*Requires libusb.lib

  Note: LibUsb-Win32 Generic Windows USB Library have different binearies
  to be used with different compilers
 */
#pragma comment( lib, "libusb" )
#include "usb.h"    // usb_*

extern CTestLog g_logTest;   //general test logger
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(const unsigned int& nValue);
extern bool TsWriteToView(const unsigned int& nValue);

void print_string_descriptor (usb_string_descriptor*);
void print_hid_descriptor (usb_hid_descriptor*);
void print_endpoint_descriptor (usb_endpoint_descriptor*);
void print_interface_descriptor (usb_interface_descriptor*);
void print_config_descriptor (usb_config_descriptor*);
void print_device_descriptor (usb_device_descriptor*);
void print_devices (PUSB_DEVICE devices);

//-----------------------------------------------------------------------------
/*Validates a various methods of handling USB devices.

  Returns true if test is successful; otherwise returns false.

  Note: uses Standard Template Library (STL).

  See also: LIBUSB-WIN32, Generic Windows USB Library
 */
bool TestUsbLib(uint16_t nVendorId , //[in] = 0 USB Vendor ID (VID)
                uint16_t nProductId  //[in] = 0 USB Product ID (PID)
               )
{
TsWriteToViewLn(_T("Test USB SDK"));

_UNUSED(nVendorId);
_UNUSED(nProductId);

bool bResult = true;
try
  {
  usb_init();

  usb_set_debug(99);

  usb_find_busses();
  usb_find_devices();

  usb_bus* bus = usb_get_busses();

  while (bus)
    {
    printf("--- bus %s start              ---\n", bus->dirname);
    print_devices(bus->devices);
    printf("--- bus %s end                ---\n", bus->dirname);

    bus = bus->next;
    }

  }
catch(std::out_of_range& eoor)
  {
  #if _MSC_VER == 1200
    //warning C4710: (MSVC6 STL Release build) function not inlined
    #pragma warning (push, 3)
  #endif

  std::_tcout << _T("STL out of range error occured! ") << eoor.what() << std::endl;

  #if _MSC_VER == 1200
    #pragma warning (pop)
  #endif

  bResult = false;
  }
catch(const std::exception& e)
  {
  #if _MSC_VER == 1200
    //warning C4710: (MSVC6 STL Release build) function not inlined
    #pragma warning (disable: 4710)
  #endif

  std::_tcout << _T("STL exception error occured! ") << e.what() << std::endl;
  bResult = false;
  }
catch(...)
  {
  TsWriteToViewLn(_T("An exception error occured!"));
  bResult = false;
  }
TsWriteToViewLn(LOG_EOT);

return bResult;
}

//-----------------------------------------------------------------------------
// from post-0.7.1 cvs tree
int usb_get_string(usb_dev_handle *dev, int index, int langid, char *buf, size_t buflen)
{
return usb_control_msg(dev,
                       USB_ENDPOINT_IN,
                       USB_REQ_GET_DESCRIPTOR,
                       (USB_DT_STRING << 8) + index,
                       langid,
                       buf,
                       buflen,
                       1000);
}

//-----------------------------------------------------------------------------
/*
 */
int usb_get_string_simple(usb_dev_handle *dev, int index, char *buf, size_t buflen)
{
char tbuf[256];
int ret, langid, si, di;

ret = usb_get_string(dev, index, 0, tbuf, sizeof(tbuf));
if (ret < 0)
  return ret;

if (ret < 4)
  return -EIO;

langid = tbuf[2] | (tbuf[3] << 8);

ret = usb_get_string(dev, index, langid, tbuf, sizeof(tbuf));
if (ret < 0)
  return ret;

if (tbuf[1] != USB_DT_STRING)
  return -EIO;

if (tbuf[0] > ret)
  return -EFBIG;

for (di = 0, si = 2; si < tbuf[0]; si += 2)
  {
  if (di >= (int)(buflen - 1))
    break;

  if (tbuf[si + 1]) /* high byte */
    buf[di++] = '?';
  else
    buf[di++] = tbuf[si];
  }

buf[di] = 0;

return di;
}

//-----------------------------------------------------------------------------
/*
 */
const char* get_class_types (size_t class_type)
{
switch (class_type)
  {
  case USB_CLASS_PER_INTERFACE: return "PER I/F";
  case USB_CLASS_AUDIO:         return "AUDIO";
  case USB_CLASS_COMM:          return "COMM";
  case USB_CLASS_HID:           return "HID";
  case USB_CLASS_PRINTER:       return "PRINTER";
  case USB_CLASS_MASS_STORAGE:  return "MASS STORAGE";
  case USB_CLASS_HUB:           return "HUB";
  case USB_CLASS_DATA:          return "DATA";
  case USB_CLASS_VENDOR_SPEC:   return "VENDOR SPEC.";
  default:                      return "UNKNOWN";
  }
}

//-----------------------------------------------------------------------------
/*
 */
const char* get_descriptor_type (size_t descr_type)
{
switch (descr_type)
  {
  case USB_DT_DEVICE:    return "DEVICE";
  case USB_DT_CONFIG:    return "CONFIG";
  case USB_DT_STRING:    return "STRING";
  case USB_DT_INTERFACE: return "INTERFACE";
  case USB_DT_ENDPOINT:  return "ENDPOINT";
  case USB_DT_HID:       return "HID";
  case USB_DT_REPORT:    return "REPORT";
  case USB_DT_PHYSICAL:  return "PHYSICAL";
  case USB_DT_HUB:       return "HUB";
  default:               return "UNKNOWN";
  }
}

//-----------------------------------------------------------------------------
/*
 */
void print_string_descriptor (usb_string_descriptor* string)
{
if (string)
  {
  printf("--- string descriptor start    ---\n");
  printf("\tdescriptor:       %s (%02X, len: %d)\n",
         get_descriptor_type (string->bDescriptorType), string->bDescriptorType, string->bLength);
  printf("\twData:            %d\n", string->wData[0]);
  printf("--- string descriptor stop     ---\n");
  }
}

//-----------------------------------------------------------------------------
/*
 */
void print_hid_descriptor (usb_hid_descriptor* hid)
{
if (hid)
  {
  printf("--- hid descriptor start       ---\n");
  printf("\tdescriptor:       %s (%02X, len: %d)\n",
         get_descriptor_type (hid->bDescriptorType), hid->bDescriptorType, hid->bLength);
  printf("\tHID ver.:         %04X\n", hid->bcdHID);
  printf("\tcountry code:     %d\n", hid->bCountryCode);
  printf("\t# of descr:       %d\n", hid->bNumDescriptors);
  printf("--- hid descriptor stop        ---\n");
  }
}

//-----------------------------------------------------------------------------
/*
 */
void print_endpoint_descriptor (usb_endpoint_descriptor* endpoint)
{
if (endpoint)
  {
  printf("--- endpoint descriptor start  ---\n");
  printf("\tdescriptor:       %s (%02X, len: %d)\n",
         get_descriptor_type (endpoint->bDescriptorType), endpoint->bDescriptorType, endpoint->bLength);

  printf("\tep address:       %02X:%02X (0x%02X)\n",
         USB_ENDPOINT_DIR_MASK & endpoint->bEndpointAddress,
         USB_ENDPOINT_ADDRESS_MASK & endpoint->bEndpointAddress,
         endpoint->bEndpointAddress);

  printf("\tattributes:       ");
  switch (endpoint->bmAttributes & USB_ENDPOINT_TYPE_MASK)
    {
    case USB_ENDPOINT_TYPE_CONTROL:     printf("CONTROL "); break;
    case USB_ENDPOINT_TYPE_ISOCHRONOUS: printf("ISOCHRONOUS "); break;
    case USB_ENDPOINT_TYPE_BULK:        printf("BULK "); break;
    case USB_ENDPOINT_TYPE_INTERRUPT:   printf("INTERRUPT "); break;
    default:                            printf("UNKNOWN "); break;
    }
  printf("(%d)\n", endpoint->bmAttributes);

  printf("\tmax. packet size: %d\n", endpoint->wMaxPacketSize);
  printf("\tinterval:         %d\n", endpoint->bInterval);
  printf("\trefresh:          %d\n", endpoint->bRefresh);
  printf("\tsynch address:    %d\n", endpoint->bSynchAddress);

  if (endpoint->extra)
    {
    printf("\textra descr.:     @0x%x+%d\n", endpoint->extra, endpoint->extralen);

    if (endpoint->extralen >= sizeof(usb_descriptor_header))
      {
      usb_descriptor_header* tmp = (usb_descriptor_header*) endpoint->extra;

      switch (tmp->bDescriptorType)
        {
        case USB_DT_DEVICE:    print_device_descriptor ((usb_device_descriptor*) tmp); break;
        case USB_DT_CONFIG:    print_config_descriptor ((usb_config_descriptor*) tmp); break;
        case USB_DT_STRING:    print_string_descriptor ((usb_string_descriptor*) tmp); break;
        case USB_DT_INTERFACE: print_interface_descriptor ((usb_interface_descriptor*) tmp); break;
        case USB_DT_ENDPOINT:  print_endpoint_descriptor ((usb_endpoint_descriptor*) tmp); break;
        case USB_DT_HID:       print_hid_descriptor ((usb_hid_descriptor*) tmp); break;
        default:               printf("\tunexpected %s descr. (%02X)\n",
                                      get_descriptor_type(tmp->bDescriptorType), tmp->bDescriptorType); break;
        }
      }
    }

  printf("--- endpoint descriptor end    ---\n");
  }
}

//-----------------------------------------------------------------------------
/*
 */
void print_interface_descriptor (usb_interface_descriptor* interface)
{
if (interface)
  {
  printf("--- interface descriptor start ---\n");
  printf("\tdescriptor:       %s (%02X, len: %d)\n",
         get_descriptor_type (interface->bDescriptorType), interface->bDescriptorType, interface->bLength);
  printf("\ti/f #:            %d\n", interface->bInterfaceNumber);
  printf("\talt. setting:     %d\n", interface->bAlternateSetting);
  printf("\ti/f class:        %s (%d)\n",
         get_class_types(interface->bInterfaceClass), interface->bInterfaceClass);
  printf("\ti/f subclass:     %d\n", interface->bInterfaceSubClass);
  printf("\ti/f protocol:     %d\n", interface->bInterfaceProtocol);
  printf("\tinterface   :     %d\n", interface->iInterface);

  int i;

  for (i = 0; i < interface->bNumEndpoints; i++)
    print_endpoint_descriptor(&interface->endpoint[i]);

  if (interface->extra)
    {
    printf("\textra descr.:     @0x%x+%d\n", interface->extra, interface->extralen);

    if (interface->extralen >= sizeof(usb_descriptor_header))
      {
      usb_descriptor_header* tmp = (usb_descriptor_header*) interface->extra;

      switch (tmp->bDescriptorType)
        {
        case USB_DT_DEVICE:    print_device_descriptor ((usb_device_descriptor*) tmp); break;
        case USB_DT_CONFIG:    print_config_descriptor ((usb_config_descriptor*) tmp); break;
        case USB_DT_STRING:    print_string_descriptor ((usb_string_descriptor*) tmp); break;
        case USB_DT_INTERFACE: print_interface_descriptor ((usb_interface_descriptor*) tmp); break;
        case USB_DT_ENDPOINT:  print_endpoint_descriptor ((usb_endpoint_descriptor*) tmp); break;
        case USB_DT_HID:       print_hid_descriptor ((usb_hid_descriptor*) tmp); break;
        default:               printf("\tunexpected %s descr. (%02X)\n",
                                      get_descriptor_type(tmp->bDescriptorType), tmp->bDescriptorType); break;
        }
      }
    }

  printf("--- interface descriptor end   ---\n");
  }
}

//-----------------------------------------------------------------------------
/*
 */
void print_config_descriptor (usb_config_descriptor* config)
{
  if (config) {
    printf("--- config descriptor start    ---\n");
    printf("\tdescriptor:       %s (%02X, len: %d)\n",
           get_descriptor_type (config->bDescriptorType), config->bDescriptorType, config->bLength);
    printf("\ttotal length:     %d\n", config->wTotalLength);
    printf("\tconfig value:     %d\n", config->bConfigurationValue);
    printf("\tconfiguration:    %d\n", config->iConfiguration);

    // 0..4 reserved
    // 5    rem. wakeup
    // 6    self powered
    // 7    reserved
    printf("\tattributes:       0x%02X\n", config->bmAttributes);
    printf("\tmax. power:       %dmA\n", config->MaxPower*2);

    int i,j;

    for (i = 0; i < config->bNumInterfaces; i++)
      for (j = 0; j < config->interface[i].num_altsetting; j++)
        print_interface_descriptor(&(config->interface[i].altsetting[j]));

    if (config->extra) {
      printf("\textra descr.:     @0x%x+%d\n", config->extra, config->extralen);

      if (config->extralen >= sizeof(usb_descriptor_header)) {
        usb_descriptor_header* tmp = (usb_descriptor_header*) config->extra;

        switch (tmp->bDescriptorType) {
        case USB_DT_DEVICE:    print_device_descriptor ((usb_device_descriptor*) tmp); break;
        case USB_DT_CONFIG:    print_config_descriptor ((usb_config_descriptor*) tmp); break;
        case USB_DT_STRING:    print_string_descriptor ((usb_string_descriptor*) tmp); break;
        case USB_DT_INTERFACE: print_interface_descriptor ((usb_interface_descriptor*) tmp); break;
        case USB_DT_ENDPOINT:  print_endpoint_descriptor ((usb_endpoint_descriptor*) tmp); break;
        case USB_DT_HID:       print_hid_descriptor ((usb_hid_descriptor*) tmp); break;
        default:               printf("\tunexpected %s descr. (%02X)\n",
                                      get_descriptor_type(tmp->bDescriptorType), tmp->bDescriptorType); break;
        }
      }
    }

    printf("--- config descriptor end      ---\n");
  }
}

//-----------------------------------------------------------------------------
/*
 */
void print_device_descriptor (usb_device_descriptor* device)
{
  printf("--- device descriptor start    ---\n");
  printf("\tdescriptor:       %s (%02X, len: %d)\n",
         get_descriptor_type (device->bDescriptorType), device->bDescriptorType, device->bLength);
  printf("\tUSB ver.:         %d.%02d\n", device->bcdUSB >> 8, device->bcdUSB & 0xff);
  printf("\tdev. class:       %s (%d)\n", get_class_types (device->bDeviceClass), device->bDeviceClass);
  printf("\tdev. subclass:    %d\n", device->bDeviceSubClass);
  printf("\tdev. protocol:    %d\n", device->bDeviceProtocol);
  printf("\tmax. packet size: %d\n", device->bMaxPacketSize0);
  printf("\tvendor id:        %04X\n", device->idVendor);
  printf("\tproduct id:       %04X\n", device->idProduct);
  printf("\tdev. ver.:        %d.%02d\n", device->bcdDevice >> 8 , device->bcdDevice & 0xff);
  printf("--- device descriptor end      ---\n");
}

//-----------------------------------------------------------------------------
/*
 */
void print_devices (PUSB_DEVICE devices)
{
  while (devices) {
    printf("--- device %s:%s start       ---\n", devices->bus->dirname, devices->filename);
    print_device_descriptor(&devices->descriptor);

    usb_dev_handle* handle = usb_open(devices);

    if (0 != handle) {
      char* buffer = new char[256];

      if (devices->descriptor.iManufacturer) {
        memset(buffer, 0, sizeof(buffer));

        if (0 < usb_get_string_simple(handle, devices->descriptor.iManufacturer, buffer, sizeof(buffer)))
          printf("\tmanufacturer:     %s\n", buffer);
      }

      if (devices->descriptor.iProduct) {
        memset(buffer, 0, sizeof(buffer));

        if (0 < usb_get_string_simple(handle, devices->descriptor.iProduct, buffer, sizeof(buffer)))
          printf("\tproduct:          %s\n", buffer);
      }

      if (devices->descriptor.iSerialNumber) {
        memset(buffer, 0, sizeof(buffer));

        if (0 < usb_get_string_simple(handle, devices->descriptor.iSerialNumber, buffer, sizeof(buffer)))
          printf("\tserialnumber:     %s\n", buffer);
      }

      delete [] buffer;
    }

    usb_close(handle);

    int i;

    for (i = 0; i < devices->descriptor.bNumConfigurations; i++)
      print_config_descriptor(&devices->config[i]);
    printf("--- device %s:%s end         ---\n", devices->bus->dirname, devices->filename);

    devices = devices->next;
  }
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: TestUsb.cpp,v $
 *Revision 1.4  2009/09/01 15:47:33  ddarko
 *Reformatted
 *
 *Revision 1.3  2009/08/20 18:59:37  ddarko
 *Merged with DDK headers
 *
 *Revision 1.2  2009/08/19 21:09:37  ddarko
 *Test LIBUSB-WIN32
 *
 *****************************************************************************/
/*****************************************************************************/
/*                                       License                             */
/*                                                                           */
/* This library is free software; you can redistribute it and/or modify it   */
/* under the terms of the GNU Library General Public License as published    */
/* by the Free Software Foundation,  version 2.                              */
/* This library is distributed in the hope that it will be useful, but       */
/* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY*/
/* or FITNESS FOR A PARTICULAR PURPOSE.                                      */
/* See the GNU Library General Public License for more details.              */
/*                                                                           */
/* You should have received a copy of the GNU Library General Public License */
/* along with this library; if not, write to the Free Software Foundation,   */
/* Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                             */
/*****************************************************************************/
