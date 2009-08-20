#ifndef __USB_H__
#define __USB_H__

#include <stdlib.h>
#include <windows.h>
#include "KUsb.h"

/*
 * 'interface' is defined somewhere in the Windows header files. This macro
 * is deleted here to avoid conflicts and compile errors.
 */

#ifdef interface
#undef interface
#endif

/*
 * PATH_MAX from limits.h can't be used on Windows if the dll and
 * import libraries are build/used by different compilers
 */

#define LIBUSB_PATH_MAX 512

/*
 * USB spec information
 *
 * This is all stuff grabbed from various USB specs and is pretty much
 * not subject to change
 */

/*
 * Device and/or Interface Class codes
 */
#define USB_CLASS_PER_INTERFACE       0   /* for DeviceClass */

#define USB_ENDPOINT_ADDRESS_MASK    0x0f    /* in bEndpointAddress */

/*
 * Descriptor sizes in bytes per descriptor type
 */
#define USB_DT_DEVICE_SIZE          18
#define USB_DT_CONFIG_SIZE           9
#define USB_DT_INTERFACE_SIZE        9
#define USB_DT_ENDPOINT_SIZE         7
#define USB_DT_ENDPOINT_AUDIO_SIZE   9   /* Audio extension */
#define USB_DT_HUB_NONVAR_SIZE       7

/*USB Device Classes (LibUsb Generic USB Library compatible macros) See: Usb100.h*/
#define USB_CLASS_AUDIO        USB_DEVICE_CLASS_AUDIO           /*  1*/
#define USB_CLASS_COMM         USB_DEVICE_CLASS_COMMUNICATIONS  /*  2*/
#define USB_CLASS_HID          USB_DEVICE_CLASS_HUMAN_INTERFACE /*  3*/
#define USB_CLASS_PRINTER      USB_DEVICE_CLASS_PRINTER         /*  7*/
#define USB_CLASS_MASS_STORAGE USB_DEVICE_CLASS_STORAGE         /*  8*/
#define USB_CLASS_HUB          USB_DEVICE_CLASS_HUB             /*  9*/
#define USB_CLASS_DATA         USB_DEVICE_CLASS_DATA            /* 10*/
#define USB_CLASS_VENDOR_SPEC  USB_DEVICE_CLASS_VENDOR_SPECIFIC /*255*/

/*Descriptor types (LibUsb Generic USB Library compatible macros) See: Usb100.h  */
#define USB_DT_DEVICE    USB_DESCRIPTOR_TYPE_DEVICE        /*0x01 USB device descriptor type code*/
#define USB_DT_CONFIG    USB_DESCRIPTOR_TYPE_CONFIGURATION /*0x02 USB configuration descriptor type code*/
#define USB_DT_STRING    USB_DESCRIPTOR_TYPE_STRING        /*0x03 USB string descriptor type code*/
#define USB_DT_INTERFACE USB_DESCRIPTOR_TYPE_INTERFACE     /*0x04 USB interface descriptor type code*/
#define USB_DT_ENDPOINT  USB_DESCRIPTOR_TYPE_ENDPOINT      /*0x05 USB endpoint descriptor type code*/
/*Class Descriptor Types (LibUsb Generic USB Library compatible macros) See: KUsb.h  */ 
#define USB_DT_HID       USBCLASSDESCRIPTOR_HID         /*0x21 Human Interface Devices (HID) class descriptor*/
#define USB_DT_REPORT    USBCLASSDESCRIPTOR_HIDREPORT   /*0x22 */
#define USB_DT_PHYSICAL  USBCLASSDESCRIPTOR_HIDPHYSICAL /*0x23 */
#define USB_DT_HUB       USBCLASSDESCRIPTOR_HUB         /*0x29 Hub class descriptor*/
/* USB endpoint types (LibUsb Generic USB Library compatible macros) See: Usb100.h  */
#define USB_ENDPOINT_DIR_MASK         USB_ENDPOINT_DIRECTION_MASK /*0x80*/
#ifndef USB_ENDPOINT_TYPE_MASK
  #define USB_ENDPOINT_TYPE_MASK      0x03        /* in bmAttributes */
  #define USB_ENDPOINT_TYPE_CONTROL      0
  #define USB_ENDPOINT_TYPE_ISOCHRONOUS  1
  #define USB_ENDPOINT_TYPE_BULK         2
  #define USB_ENDPOINT_TYPE_INTERRUPT    3
#endif
/* Standard Request Codes (LibUsb Generic USB Library compatible macros) See: Usb100.h  */
#define USB_REQ_GET_STATUS        USB_REQUEST_GET_STATUS        /*0x00 */
#define USB_REQ_CLEAR_FEATURE     USB_REQUEST_CLEAR_FEATURE     /*0x01 */
#define USB_REQ_SET_FEATURE       USB_REQUEST_SET_FEATURE       /*0x03 */
#define USB_REQ_SET_ADDRESS       USB_REQUEST_SET_ADDRESS       /*0x05 */
#define USB_REQ_GET_DESCRIPTOR    USB_REQUEST_GET_DESCRIPTOR    /*0x06 */
#define USB_REQ_SET_DESCRIPTOR    USB_REQUEST_SET_DESCRIPTOR    /*0x07 */
#define USB_REQ_GET_CONFIGURATION USB_REQUEST_GET_CONFIGURATION /*0x08 */
#define USB_REQ_SET_CONFIGURATION USB_REQUEST_SET_CONFIGURATION /*0x09 */
#define USB_REQ_GET_INTERFACE     USB_REQUEST_GET_INTERFACE     /*0x0A */
#define USB_REQ_SET_INTERFACE     USB_REQUEST_SET_INTERFACE     /*0x0B */
#define USB_REQ_SYNCH_FRAME       USB_REQUEST_SYNC_FRAME        /*0x0C */
/* Request recipients (LibUsb Generic USB Library compatible macros) See: Usb100.h  */
#define USB_RECIP_DEVICE      BMREQUEST_TO_DEVICE   /*0x00*/
#define USB_RECIP_INTERFACE   BMREQUEST_TO_INTERFACE/*0x01*/
#define USB_RECIP_ENDPOINT    BMREQUEST_TO_ENDPOINT /*0x02*/
#define USB_RECIP_OTHER       BMREQUEST_TO_OTHER    /*0x03*/
/*Descriptors data structures (LibUsb Generic USB Library compatible types) See: Usb100.h  */
#define wData bString      /*variable length output buffer is named differently*/
typedef USB_COMMON_DESCRIPTOR usb_descriptor_header; /* All standard descriptors have these 2 fields in common */
typedef USB_STRING_DESCRIPTOR usb_string_descriptor; /* String descriptor */
typedef USB_DEVICE_DESCRIPTOR usb_device_descriptor; /* Device descriptor */


/* ensure byte-packed structures */
#include <pshpack1.h>

/* HID descriptor */
struct usb_hid_descriptor {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint16_t bcdHID;
  uint8_t  bCountryCode;
  uint8_t  bNumDescriptors;
};

/* Endpoint descriptor */
#define USB_MAXENDPOINTS   32
struct usb_endpoint_descriptor {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint8_t  bEndpointAddress;
  uint8_t  bmAttributes;
  uint16_t wMaxPacketSize;
  uint8_t  bInterval;

  uint8_t  bRefresh;
  uint8_t  bSynchAddress;

  uint8_t *extra;   /* Extra descriptors */
  int extralen;
};


/* Interface descriptor */
#define USB_MAXINTERFACES   32
struct usb_interface_descriptor {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint8_t  bInterfaceNumber;
  uint8_t  bAlternateSetting;
  uint8_t  bNumEndpoints;
  uint8_t  bInterfaceClass;
  uint8_t  bInterfaceSubClass;
  uint8_t  bInterfaceProtocol;
  uint8_t  iInterface;

  struct usb_endpoint_descriptor *endpoint;

  uint8_t *extra;   /* Extra descriptors */
  int extralen;
};

#define USB_MAXALTSETTING   128   /* Hard limit */

struct usb_interface {
  struct usb_interface_descriptor *altsetting;

  int num_altsetting;
};

/* Configuration descriptor information.. */
#define USB_MAXCONFIG      8
struct usb_config_descriptor {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint16_t wTotalLength;
  uint8_t  bNumInterfaces;
  uint8_t  bConfigurationValue;
  uint8_t  iConfiguration;
  uint8_t  bmAttributes;
  uint8_t  MaxPower;

  struct usb_interface *interface;

  uint8_t *extra;   /* Extra descriptors */
  int extralen;
};

/*describes a descriptor request. See USB_DESCRIPTOR_REQUEST*/
struct usb_ctrl_setup {
  uint8_t  bRequestType;
  uint8_t  bRequest;
  uint16_t wValue;
  uint16_t wIndex;
  uint16_t wLength;
};

/*
 * Standard requests
 */

#define USB_TYPE_STANDARD      (BMREQUEST_STANDARD << 5)
#define USB_TYPE_CLASS         (BMREQUEST_CLASS    << 5)
#define USB_TYPE_VENDOR        (BMREQUEST_VENDOR   << 5)
#define USB_TYPE_RESERVED      (0x03 << 5)

/*
 * Various libusb API related stuff
 */

#define USB_ENDPOINT_IN       0x80 /*See USB_ENDPOINT_DIRECTION_IN*/
#define USB_ENDPOINT_OUT      0x00 /*See USB_ENDPOINT_DIRECTION_OUT*/

/* Error codes */
#define USB_ERROR_BEGIN         500000

/*
 * This is supposed to look weird. This file is generated from autoconf
 * and I didn't want to make this too complicated.
 */
#define USB_LE16_TO_CPU(x)

/* Data types */
/* struct usb_device; */
/* struct usb_bus; */

struct usb_device {
  usb_device *next, *prev;

  char filename[LIBUSB_PATH_MAX];

  struct usb_bus *bus;

  usb_device_descriptor descriptor;
  usb_config_descriptor *config;

  void *dev;      /* Darwin support */

  uint8_t devnum;

  uint8_t num_children;
  usb_device **children;
};
typedef usb_device* PUSB_DEVICE;

struct usb_bus {
  usb_bus *next, *prev;

  char dirname[LIBUSB_PATH_MAX];

  usb_device *devices;
  unsigned long location;

  usb_device *root_dev;
};

/* Version information, Windows specific */
struct usb_version {
  struct {
    int major;
    int minor;
    int micro;
    int nano;
  } dll;
  struct {
    int major;
    int minor;
    int micro;
    int nano;
  } driver;
};


struct usb_dev_handle;
typedef struct usb_dev_handle usb_dev_handle;

/* Variables */
#ifndef __USB_C__
#define usb_busses usb_get_busses()
#endif



#include <poppack.h>


#ifdef __cplusplus
extern "C" {
#endif

  /* Function prototypes */

  /* usb.c */
  usb_dev_handle *usb_open(struct usb_device *dev);
  int usb_close(usb_dev_handle *dev);
  int usb_get_string(usb_dev_handle *dev, int index, int langid, char *buf,
                     size_t buflen);
  int usb_get_string_simple(usb_dev_handle *dev, int index, char *buf,
                            size_t buflen);

  /* descriptors.c */
  int usb_get_descriptor_by_endpoint(usb_dev_handle *udev, int ep,
                                     uint8_t type, uint8_t index,
                                     void *buf, int size);
  int usb_get_descriptor(usb_dev_handle *udev, uint8_t type,
                         uint8_t index, void *buf, int size);

  /* <arch>.c */
  int usb_bulk_write(usb_dev_handle *dev, int ep, char *bytes, int size,
                     int timeout);
  int usb_bulk_read(usb_dev_handle *dev, int ep, char *bytes, int size,
                    int timeout);
  int usb_interrupt_write(usb_dev_handle *dev, int ep, char *bytes, int size,
                          int timeout);
  int usb_interrupt_read(usb_dev_handle *dev, int ep, char *bytes, int size,
                         int timeout);
  int usb_control_msg(usb_dev_handle *dev, int requesttype, int request,
                      int value, int index, char *bytes, int size,
                      int timeout);
  int usb_set_configuration(usb_dev_handle *dev, int configuration);
  int usb_claim_interface(usb_dev_handle *dev, int interface);
  int usb_release_interface(usb_dev_handle *dev, int interface);
  int usb_set_altinterface(usb_dev_handle *dev, int alternate);
  int usb_resetep(usb_dev_handle *dev, unsigned int ep);
  int usb_clear_halt(usb_dev_handle *dev, unsigned int ep);
  int usb_reset(usb_dev_handle *dev);

  char *usb_strerror(void);

  void usb_init(void);
  void usb_set_debug(int level);
  int usb_find_busses(void);
  int usb_find_devices(void);
  struct usb_device *usb_device(usb_dev_handle *dev);
  struct usb_bus *usb_get_busses(void);


  /* Windows specific functions */

  #define LIBUSB_HAS_INSTALL_SERVICE_NP 1
  int usb_install_service_np(void);
  void CALLBACK usb_install_service_np_rundll(HWND wnd, HINSTANCE instance,
                                              LPSTR cmd_line, int cmd_show);

  #define LIBUSB_HAS_UNINSTALL_SERVICE_NP 1
  int usb_uninstall_service_np(void);
  void CALLBACK usb_uninstall_service_np_rundll(HWND wnd, HINSTANCE instance,
                                                LPSTR cmd_line, int cmd_show);

  #define LIBUSB_HAS_INSTALL_DRIVER_NP 1
  int usb_install_driver_np(const char *inf_file);
  void CALLBACK usb_install_driver_np_rundll(HWND wnd, HINSTANCE instance,
                                             LPSTR cmd_line, int cmd_show);

  #define LIBUSB_HAS_TOUCH_INF_FILE_NP 1
  int usb_touch_inf_file_np(const char *inf_file);
  void CALLBACK usb_touch_inf_file_np_rundll(HWND wnd, HINSTANCE instance,
                                             LPSTR cmd_line, int cmd_show);

  #define LIBUSB_HAS_INSTALL_NEEDS_RESTART_NP 1
  int usb_install_needs_restart_np(void);

  const struct usb_version *usb_get_version(void);

  int usb_isochronous_setup_async(usb_dev_handle *dev, void **context,
                                  uint8_t ep, int pktsize);
  int usb_bulk_setup_async(usb_dev_handle *dev, void **context,
                           uint8_t ep);
  int usb_interrupt_setup_async(usb_dev_handle *dev, void **context,
                                uint8_t ep);

  int usb_submit_async(void *context, char *bytes, int size);
  int usb_reap_async(void *context, int timeout);
  int usb_reap_async_nocancel(void *context, int timeout);
  int usb_cancel_async(void *context);
  int usb_free_async(void **context);


#ifdef __cplusplus
}
#endif

#endif /* __USB_H__ */

