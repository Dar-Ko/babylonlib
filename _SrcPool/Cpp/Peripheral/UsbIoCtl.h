/*$RCSfile: UsbIoCtl.h,v $: header file
  $Revision: 1.12 $ $Date: 2009/08/07 21:45:13 $
  $Author: ddarko $

  USB device I/O control codes for Microsoft Windows OS.
  Note: Microsoft Windows specific (Win).
  Copyright: (c) 2004-2008 The Open Watcom Contributors. All Rights Reserved.
  http://www.openwatcom.org/
 */
// Group=Windows

#ifndef __USBIOCTL_H__
  #define __USBIOCTL_H__

#ifndef _ENABLE_AUTODEPEND
  #ifdef __WATCOMC__
    /*Watcom 32b Compiler*/
    #pragma read_only_file;
  #endif
#endif

#if __GNUC__ >=3
  #pragma GCC system_header
#endif

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#include "Usb200.h"
#include "UsbIoDef.h"

#ifdef __cplusplus
  extern "C" {
#endif

#ifdef WIN32 //Microsoft Windows I/O Control codes
////////////////////////////////////////////////////////////////////////////////

/* USB device I/O control codes */
#define IOCTL_INTERNAL_USB_SUBMIT_URB \
    CTL_CODE( FILE_DEVICE_USB, USB_SUBMIT_URB, METHOD_NEITHER, FILE_ANY_ACCESS )
#define IOCTL_INTERNAL_USB_RESET_PORT \
    CTL_CODE( FILE_DEVICE_USB, USB_RESET_PORT, METHOD_NEITHER, FILE_ANY_ACCESS )
#define IOCTL_INTERNAL_USB_GET_ROOTHUB_PDO \
    CTL_CODE( FILE_DEVICE_USB, USB_GET_ROOTHUB_PDO, METHOD_NEITHER, FILE_ANY_ACCESS )
#define IOCTL_INTERNAL_USB_GET_PORT_STATUS \
    CTL_CODE( FILE_DEVICE_USB, USB_GET_PORT_STATUS, METHOD_NEITHER, FILE_ANY_ACCESS )
#define IOCTL_INTERNAL_USB_ENABLE_PORT \
    CTL_CODE( FILE_DEVICE_USB, USB_ENABLE_PORT, METHOD_NEITHER, FILE_ANY_ACCESS )
#define IOCTL_INTERNAL_USB_GET_HUB_COUNT \
    CTL_CODE( FILE_DEVICE_USB, USB_GET_HUB_COUNT, METHOD_NEITHER, FILE_ANY_ACCESS )
#define IOCTL_INTERNAL_USB_CYCLE_PORT \
    CTL_CODE( FILE_DEVICE_USB, USB_CYCLE_PORT, METHOD_NEITHER, FILE_ANY_ACCESS )
#define IOCTL_INTERNAL_USB_GET_HUB_NAME \
    CTL_CODE( FILE_DEVICE_USB, USB_GET_HUB_NAME, METHOD_BUFFERED, FILE_ANY_ACCESS )
#define IOCTL_INTERNAL_USB_GET_BUS_INFO \
    CTL_CODE( FILE_DEVICE_USB, USB_GET_BUS_INFO, METHOD_BUFFERED, FILE_ANY_ACCESS )
#define IOCTL_INTERNAL_USB_GET_CONTROLLER_NAME \
    CTL_CODE( FILE_DEVICE_USB, USB_GET_CONTROLLER_NAME, METHOD_BUFFERED, \
    FILE_ANY_ACCESS )
#define IOCTL_INTERNAL_USB_GET_BUSGUID_INFO \
    CTL_CODE( FILE_DEVICE_USB, USB_GET_BUSGUID_INFO, METHOD_BUFFERED, FILE_ANY_ACCESS )
#define IOCTL_INTERNAL_USB_GET_PARENT_HUB_INFO \
    CTL_CODE( FILE_DEVICE_USB, USB_GET_PARENT_HUB_INFO, METHOD_BUFFERED, \
    FILE_ANY_ACCESS )
#if (_WIN32_WINNT >= 0x0501)
    #define IOCTL_INTERNAL_USB_SUBMIT_IDLE_NOTIFICATION \
        CTL_CODE( FILE_DEVICE_USB, USB_IDLE_NOTIFICATION, METHOD_NEITHER, \
        FILE_ANY_ACCESS )
    #define IOCTL_INTERNAL_USB_GET_DEVICE_HANDLE \
        CTL_CODE( FILE_DEVICE_USB, USB_GET_DEVICE_HANDLE, METHOD_NEITHER, \
        FILE_ANY_ACCESS )
#endif
#if (_WIN32_WINNT >= 0x0600)
    #define IOCTL_INTERNAL_USB_NOTIFY_IDLE_READY \
        CTL_CODE( FILE_DEVICE_USB, USB_IDLE_NOTIFICATION_EX, METHOD_NEITHER, \
        FILE_ANY_ACCESS )
    #define IOCTL_INTERNAL_USB_REQ_GLOBAL_SUSPEND \
        CTL_CODE( FILE_DEVICE_USB, USB_REQ_GLOBAL_SUSPEND, METHOD_NEITHER, \
        FILE_ANY_ACCESS )
    #define IOCTL_INTERNAL_USB_REQ_GLOBAL_RESUME \
        CTL_CODE( FILE_DEVICE_USB, USB_REQ_GLOBAL_RESUME, METHOD_NEITHER, \
        FILE_ANY_ACCESS )
    #define IOCTL_INTERNAL_USB_RECORD_FAILURE \
        CTL_CODE( FILE_DEVICE_USB, USB_RECORD_FAILURE, METHOD_NEITHER, \
        FILE_ANY_ACCESS )
    #define IOCTL_INTERNAL_USB_GET_DEVICE_HANDLE_EX \
        CTL_CODE( FILE_DEVICE_USB, USB_GET_DEVICE_HANDLE_EX, METHOD_NEITHER, \
        FILE_ANY_ACCESS )
    #define IOCTL_INTERNAL_USB_GET_TT_DEVICE_HANDLE \
        CTL_CODE( FILE_DEVICE_USB, USB_GET_TT_DEVICE_HANDLE, METHOD_NEITHER, \
        FILE_ANY_ACCESS )
    #define IOCTL_INTERNAL_USB_GET_TOPOLOGY_ADDRESS \
        CTL_CODE( FILE_DEVICE_USB, USB_GET_TOPOLOGY_ADDRESS, METHOD_NEITHER, \
        FILE_ANY_ACCESS )
    #define IOCTL_INTERNAL_USB_GET_DEVICE_CONFIG_INFO \
        CTL_CODE( FILE_DEVICE_USB, USB_GET_HUB_CONFIG_INFO, METHOD_NEITHER, \
        FILE_ANY_ACCESS )
#endif
#ifndef USB_KERNEL_IOCTL
    #define IOCTL_USB_HCD_GET_STATS_1 \
        CTL_CODE( FILE_DEVICE_USB, HCD_GET_STATS_1, METHOD_BUFFERED, FILE_ANY_ACCESS )
    #define IOCTL_USB_HCD_GET_STATS_2 \
        CTL_CODE( FILE_DEVICE_USB, HCD_GET_STATS_2, METHOD_BUFFERED, FILE_ANY_ACCESS )
    #define IOCTL_USB_HCD_DISABLE_PORT \
        CTL_CODE( FILE_DEVICE_USB, HCD_DISABLE_PORT, METHOD_BUFFERED, FILE_ANY_ACCESS )
    #define IOCTL_USB_HCD_ENABLE_PORT \
        CTL_CODE( FILE_DEVICE_USB, HCD_ENABLE_PORT, METHOD_BUFFERED, FILE_ANY_ACCESS )
    #ifndef IOCTL_USB_DIAGNOSTIC_MODE_ON
        #define IOCTL_USB_DIAGNOSTIC_MODE_ON \
            CTL_CODE( FILE_DEVICE_USB, HCD_DIAGNOSTIC_MODE_ON, METHOD_BUFFERED, \
            FILE_ANY_ACCESS )
    #endif
    #ifndef IOCTL_USB_DIAGNOSTIC_MODE_OFF
        #define IOCTL_USB_DIAGNOSTIC_MODE_OFF \
            CTL_CODE( FILE_DEVICE_USB, HCD_DIAGNOSTIC_MODE_OFF, METHOD_BUFFERED, \
            FILE_ANY_ACCESS )
    #endif
    #ifndef IOCTL_USB_GET_ROOT_HUB_NAME
      //Request to retrieve the symbolic link name of the root hub (0x220408).
        #define IOCTL_USB_GET_ROOT_HUB_NAME \
            CTL_CODE( FILE_DEVICE_USB, HCD_GET_ROOT_HUB_NAME, METHOD_BUFFERED, \
            FILE_ANY_ACCESS )
    #endif
    #ifndef IOCTL_GET_HCD_DRIVERKEY_NAME
        #define IOCTL_GET_HCD_DRIVERKEY_NAME \
            CTL_CODE( FILE_DEVICE_USB, HCD_GET_DRIVERKEY_NAME, METHOD_BUFFERED, \
            FILE_ANY_ACCESS )
    #endif

    //Request to retrieve information about a parent device (0x220408).
    #define IOCTL_USB_GET_NODE_INFORMATION \
        CTL_CODE( FILE_DEVICE_USB, USB_GET_NODE_INFORMATION, METHOD_BUFFERED, \
        FILE_ANY_ACCESS )
    #define IOCTL_USB_GET_NODE_CONNECTION_INFORMATION \
        CTL_CODE( FILE_DEVICE_USB, USB_GET_NODE_CONNECTION_INFORMATION, \
        METHOD_BUFFERED, FILE_ANY_ACCESS )

    //Request for the device descriptors associated with the USB port (0x220410).
    #define IOCTL_USB_GET_DESCRIPTOR_FROM_NODE_CONNECTION \
        CTL_CODE( FILE_DEVICE_USB, USB_GET_DESCRIPTOR_FROM_NODE_CONNECTION, \
        METHOD_BUFFERED, FILE_ANY_ACCESS )

    //Request to retrieve the symbolic link name of the hub that is attached to
    //the downstream port (0x220414).
    #define IOCTL_USB_GET_NODE_CONNECTION_NAME \
        CTL_CODE( FILE_DEVICE_USB, USB_GET_NODE_CONNECTION_NAME, METHOD_BUFFERED, \
        FILE_ANY_ACCESS )
    #define IOCTL_USB_DIAG_IGNORE_HUBS_ON \
        CTL_CODE( FILE_DEVICE_USB, USB_DIAG_IGNORE_HUBS_ON, METHOD_BUFFERED, \
        FILE_ANY_ACCESS )
    #define IOCTL_USB_DIAG_IGNORE_HUBS_OFF \
        CTL_CODE( FILE_DEVICE_USB, USB_DIAG_IGNORE_HUBS_OFF, METHOD_BUFFERED, \
        FILE_ANY_ACCESS )

    //(0x220420).
    #define IOCTL_USB_GET_NODE_CONNECTION_DRIVERKEY_NAME \
        CTL_CODE( FILE_DEVICE_USB, USB_GET_NODE_CONNECTION_DRIVERKEY_NAME, \
        METHOD_BUFFERED, FILE_ANY_ACCESS )
    #if (_WIN32_WINNT >= 0x0501)
        #define IOCTL_USB_GET_HUB_CAPABILITIES \
            CTL_CODE( FILE_DEVICE_USB, USB_GET_HUB_CAPABILITIES, METHOD_BUFFERED, \
            FILE_ANY_ACCESS )
        #define IOCTL_USB_HUB_CYCLE_PORT \
            CTL_CODE( FILE_DEVICE_USB, USB_HUB_CYCLE_PORT, METHOD_BUFFERED, \
            FILE_ANY_ACCESS )
        #define IOCTL_USB_GET_NODE_CONNECTION_ATTRIBUTES \
            CTL_CODE( FILE_DEVICE_USB, USB_GET_NODE_CONNECTION_ATTRIBUTES, \
            METHOD_BUFFERED, FILE_ANY_ACCESS )

        //Request for a USB port information and the attached device (0x220448).
        //Note: Specific to Microsoft Windows XP SP1 platforms and later
        #define IOCTL_USB_GET_NODE_CONNECTION_INFORMATION_EX \
            CTL_CODE( FILE_DEVICE_USB, USB_GET_NODE_CONNECTION_INFORMATION_EX, \
            METHOD_BUFFERED, FILE_ANY_ACCESS )
    #endif
    #if (_WIN32_WINNT >= 0x0600)
        #define IOCTL_USB_RESET_HUB \
            CTL_CODE( FILE_DEVICE_USB, USB_RESET_HUB, METHOD_BUFFERED, FILE_ANY_ACCESS )
        #define IOCTL_USB_GET_HUB_CAPABILITIES_EX \
            CTL_CODE( FILE_DEVICE_USB, USB_GET_HUB_CAPABILITIES_EX, METHOD_BUFFERED, \
            FILE_ANY_ACCESS )
    #endif
#endif

/* USBD port status flags */
#define USBD_PORT_ENABLED   0x00000001L
#define USBD_PORT_CONNECTED 0x00000002L

/*WMI USB GUID indices.
  Note: Microsoft Windows Specific.
 */
#ifndef USB_KERNEL_IOCTL
    #define WMI_USB_DRIVER_INFORMATION      0
    #define WMI_USB_DRIVER_NOTIFICATION     1
    #define WMI_USB_POWER_DEVICE_ENABLE     2
    #define WMI_USB_HUB_NODE_INFORMATION    4
    #define WMI_USB_PERFORMANCE_INFORMATION 1
    #define WMI_USB_DEVICE_NODE_INFORMATION 2
#endif

/* USB node information signature */
#ifndef USB_KERNEL_IOCTL
    #if (_WIN32_WINNT >= 0x0600)
        #define USB_NODE_INFO_SIG   'USBN'
    #endif
#endif

/* USB start fail data */
#if (_WIN32_WINNT >= 0x0600)
#ifdef USB20_API
typedef struct _USB_START_FAILDATA {
    ULONG       LengthInBytes;
    NTSTATUS    NtStatus;
    USBD_STATUS UsbdStatus;
    ULONG       ConnectStatus;
    UCHAR       DriverData[4];
} USB_START_FAILDATA;
typedef USB_START_FAILDATA  *PUSB_START_FAILDATA;
#endif
#endif

/* USB topology address */
#if (_WIN32_WINNT >= 0x0600)
typedef struct _USB_TOPOLOGY_ADDRESS {
    ULONG   PciBusNumber;
    ULONG   PciDeviceNumber;
    ULONG   PciFunctionNumber;
    ULONG   Reserved;
    USHORT  RootHubPortNumber;
    USHORT  HubPortNumber[5];
    USHORT  Reserved2;
} USB_TOPOLOGY_ADDRESS;
typedef USB_TOPOLOGY_ADDRESS    *PUSB_TOPOLOGY_ADDRESS;
#endif

/*----------------------------------------------------------------------------*/
/* The following structures get one-byte packing.                             */
#include <pshpack1.h>

/* USB hub nodes */
#ifndef USB_KERNEL_IOCTL
typedef enum _USB_HUB_NODE {
    UsbHub      = 0,
    UsbMIParent = 1
} USB_HUB_NODE;
#endif

#ifndef USB_KERNEL_IOCTL
  /*USB_HUB_INFORMATION structure contains information about an USB hub.*/
  typedef struct _USB_HUB_INFORMATION 
    {
    USB_HUB_DESCRIPTOR HubDescriptor;  /*selected hub information*/
    BOOLEAN            HubIsBusPowered;/*indicates whether the hub is powered*/
    } USB_HUB_INFORMATION;
  /*USB hub information*/
  typedef USB_HUB_INFORMATION *PUSB_HUB_INFORMATION;
#endif

/* USB MI parent information */
#ifndef USB_KERNEL_IOCTL
typedef struct _USB_MI_PARENT_INFORMATION {
    ULONG   NumberOfInterfaces;
} USB_MI_PARENT_INFORMATION;
typedef USB_MI_PARENT_INFORMATION   *PUSB_MI_PARENT_INFORMATION;
#endif

#ifndef USB_KERNEL_IOCTL
  /*USB_NODE_INFORMATION structure is used with the IOCTL_USB_GET_NODE_INFORMATION
    I/O control request the information about a parent device.
   */
  typedef struct _USB_NODE_INFORMATION
    {
    USB_HUB_NODE    NodeType; /*indicates whether the parent device is a hub or
                                a non-hub composite device:

                                - UsbHub indicates that the device is a hub.
                                - UsbMIParent the device is a composite device 
                                  with multiple interfaces.
                               */
    union
      {
      /*information about a parent hub device.*/
      USB_HUB_INFORMATION       HubInformation;
       /*information about a parent composite device.
         Composite devices are devices that have multiple interfaces.
         Windows loads the USB generic parent driver for composite devices,
         instead of the hub driver, but the generic parent driver performs
         many of the functions of the hub driver.*/
      USB_MI_PARENT_INFORMATION MiParentInformation;
      } u;
    } USB_NODE_INFORMATION;
  /*USB parent node information*/
  typedef USB_NODE_INFORMATION    *PUSB_NODE_INFORMATION;
#endif

/* USB pipe information */
#ifndef USB_KERNEL_IOCTL
typedef struct _USB_PIPE_INFO {
    USB_ENDPOINT_DESCRIPTOR EndpointDescriptor;
    ULONG                   ScheduleOffset;
} USB_PIPE_INFO;
typedef USB_PIPE_INFO   *PUSB_PIPE_INFO;
#endif

/* USB connection status values */
#ifndef USB_KERNEL_IOCTL
typedef enum _USB_CONNECTION_STATUS {
    NoDeviceConnected           = 0,
    DeviceConnected             = 1,
    DeviceFailedEnumeration     = 2,
    DeviceGeneralFailure        = 3,
    DeviceCausedOvercurrent     = 4,
    DeviceNotEnoughPower        = 5,
    #if (_WIN32_WINNT >= 0x0501)
      DeviceNotEnoughBandwidth  = 6,
      DeviceHubNestedTooDeeply  = 7,
      #if (_WIN32_WINNT >= 0x0600)
        DeviceInLegacyHub       = 8,
        DeviceEnumerating       = 9,
        DeviceReset             = 10
      #else
        DeviceInLegacyHub       = 8
      #endif
    #else
      DeviceNotEnoughBandwidth  = 6
  #endif
} USB_CONNECTION_STATUS;
typedef USB_CONNECTION_STATUS   *PUSB_CONNECTION_STATUS;
#endif

#ifndef USB_KERNEL_IOCTL
  /*USB_NODE_CONNECTION_INFORMATION structure is used with
    the IOCTL_USB_GET_NODE_CONNECTION_INFORMATION to obtain information about
    the connection associated with the indicated USB port.

    If there is no device connected, result of the request is the information
    about the port. If a device is connected to the port, the structure
    contains information about both the port and the connected device.

    The USB_NODE_CONNECTION_INFORMATION_EX structure is an extended version of
    USB_NODE_CONNECTION_INFORMATION. The two structures are identical, except
    for LowSpeed member.

    See also: "Universal Serial Bus Specification", USB_NODE_CONNECTION_INFORMATION_EX
   */
  typedef struct _USB_NODE_CONNECTION_INFORMATION
    {
    ULONG                 ConnectionIndex; /*specifies the number of 
                the port in the range [1, USB_HUB_DESCRIPTOR::bNumberOfPorts]*/
    USB_DEVICE_DESCRIPTOR DeviceDescriptor; /*attached USB device description*/
    UCHAR                 CurrentConfigurationValue; /*ID of attached USB 
                                           device description configuration*/
    BOOLEAN               LowSpeed;   /*data transfer speed*/
    BOOLEAN               DeviceIsHub;/*indicates if attached device is a hub*/
    USHORT                DeviceAddress;/*bus-relative address of the 
                                          attached device*/
    ULONG                 NumberOfOpenPipes;/*number of open USB pipes
                                              associated with the port*/
    USB_CONNECTION_STATUS ConnectionStatus; /*connection status of the port*/
    USB_PIPE_INFO         PipeList[1]; /*list of theopen pipes associated
                 with the port, including the associated endpoint descriptor*/
    } USB_NODE_CONNECTION_INFORMATION;
  /*USB node connection information*/
  typedef USB_NODE_CONNECTION_INFORMATION *PUSB_NODE_CONNECTION_INFORMATION;
#endif

#ifndef USB_KERNEL_IOCTL
  /*USB_NODE_CONNECTION_DRIVERKEY_NAME structure is used with
    the IOCTL_USB_GET_NODE_CONNECTION_DRIVERKEY_NAME I/O control request to
    retrieve the driver key name for the device that is connected to
    the indicated port.
   */
  typedef struct _USB_NODE_CONNECTION_DRIVERKEY_NAME
    {
    ULONG   ConnectionIndex;/*[in] the port number to which the hub is attached
                         in the range [1, USB_HUB_DESCRIPTOR::bNumberOfPorts]*/
    ULONG   ActualLength;  /*[out] the driver's key name length in bytes*/
    WCHAR   DriverKeyName[1]; /*[out] Unicode driver key name for the device
                               that is attached to the hub port*/
    } USB_NODE_CONNECTION_DRIVERKEY_NAME;
  /*USB node connection driver key name*/
  typedef USB_NODE_CONNECTION_DRIVERKEY_NAME  *PUSB_NODE_CONNECTION_DRIVERKEY_NAME;
#endif

#ifndef USB_KERNEL_IOCTL
  /*USB_NODE_CONNECTION_NAME structure is used with
    the IOCTL_USB_GET_NODE_CONNECTION_NAME I/O control request to retrieve
    the symbolic link of the downstream hub that is attached to the port.
   */
  typedef struct _USB_NODE_CONNECTION_NAME
    {
    ULONG   ConnectionIndex; /*[in] the port number to which the hub is attached
                         in the range [1, USB_HUB_DESCRIPTOR::bNumberOfPorts]*/
    ULONG   ActualLength; /*[out] the attached hub's symbolic link length
                            in bytes*/
    WCHAR   NodeName[1];  /*[out] Unicode symbolic link for the downstream hub
             that is attached to the port specified by ConnectionIndex or
             empty string if there is no attached device, the attached device
             does not have a symbolic link or if the device is not a hub*/
    } USB_NODE_CONNECTION_NAME;
  /*USB node connection name*/
  typedef USB_NODE_CONNECTION_NAME *PUSB_NODE_CONNECTION_NAME;
#endif

#ifndef USB_KERNEL_IOCTL
  /*USB_HUB_NAME structure stores the hub's symbolic device name.*/
  typedef struct _USB_HUB_NAME
    {
    ULONG   ActualLength;  /*size of the entire data structure [bytes]*/
    WCHAR   HubName[1];    /*hub's symbolic device name in Unicode    */
    } USB_HUB_NAME;
  typedef USB_HUB_NAME    *PUSB_HUB_NAME; /*USB hub name*/
#endif

#ifndef USB_KERNEL_IOCTL
  /*USB_ROOT_HUB_NAME structure stores the root hub's symbolic device name.*/
  typedef struct _USB_ROOT_HUB_NAME
    {
    ULONG   ActualLength;   /*size of the entire data structure [bytes] */
    WCHAR   RootHubName[1]; /*root hub's symbolic device name in Unicode*/
    } USB_ROOT_HUB_NAME;
  typedef USB_ROOT_HUB_NAME   *PUSB_ROOT_HUB_NAME; /*USB root hub name*/
#endif


#ifndef USB_KERNEL_IOCTL
  /*USB_HCD_DRIVERKEY_NAME structure is used with the IOCTL_GET_HCD_DRIVERKEY_NAME
    I/O control request to retrieve the driver key in the registry for
    the USB host controller driver. */
  typedef struct _USB_HCD_DRIVERKEY_NAME
    {
    ULONG   ActualLength;     /*size of the entire data structure [bytes]  */
    WCHAR   DriverKeyName[1]; /*driver key name for the USB host controller
                                in Unicode*/
    } USB_HCD_DRIVERKEY_NAME;
  /*USB HCD driver key name*/
  typedef USB_HCD_DRIVERKEY_NAME  *PUSB_HCD_DRIVERKEY_NAME;
#endif

#ifndef USB_KERNEL_IOCTL
  /*USB_DESCRIPTOR_REQUEST structure is used with the 
   IOCTL_USB_GET_DESCRIPTOR_FROM_NODE_CONNECTION I/O control request to retrieve
   one or more descriptors for the device that is associated with the indicated
   connection index.
   bmRequest is set to a value of 0x80, indicating a standard USB device request
   and a device-to-host data transfer.
   bRequest is set to the value GET_DESCRIPTOR = 0x06.

   Note: If the caller specifies a value of USB_CONFIGURATION_DESCRIPTOR_TYPE
   in the wValue member, the output buffer must be large enough to hold all
   of the descriptors that are associated with the current configuration.

   See also: "Universal Serial Bus Specification"
   */
  typedef struct _USB_DESCRIPTOR_REQUEST
    {
    ULONG   ConnectionIndex; /*[in] specifies the number of 
                the port in the range [1, USB_HUB_DESCRIPTOR::bNumberOfPorts]*/
    struct
      {
      UCHAR  bmRequest;/*[out] type of USB device request (standard, class or 
                         vendor), the direction of the data transfer, and the
                         type of data recipient (device, interface, or endpoint).*/
      UCHAR  bRequest;/*[out] request number*/
      USHORT wValue;  /*type of descriptor to retrieve in the high byte and
                        the descriptor index in the low byte.*/
      USHORT wIndex;  /*[in] device-specific index of the descriptor that is
                        to be retrieved; 0 or language ID for string Descriptors.*/
      USHORT wLength; /*[in/out] length of the data that is transferred in bytes.*/
      } SetupPacket;   /*describes a descriptor request*/
    UCHAR   Data[1];   /*[out] the retrieved descriptors.*/
    } USB_DESCRIPTOR_REQUEST;
  /*USB descriptor request*/
  typedef USB_DESCRIPTOR_REQUEST  *PUSB_DESCRIPTOR_REQUEST;
#endif

/* USB hub capabilities */
#ifndef USB_KERNEL_IOCTL
#if (_WIN32_WINNT >= 0x0501)
typedef struct _USB_HUB_CAPABILITIES {
    ULONG   HubIs2xCapable  : 1;
} USB_HUB_CAPABILITIES;
typedef USB_HUB_CAPABILITIES    *PUSB_HUB_CAPABILITIES;
#endif
#endif

/* USB node connection attributes */
#ifndef USB_KERNEL_IOCTL
#if (_WIN32_WINNT >= 0x0501)
typedef struct _USB_NODE_CONNECTION_ATTRIBUTES {
    ULONG                   ConnectionIndex; /*specifies the number of 
                the port in the range [1, USB_HUB_DESCRIPTOR::bNumberOfPorts]*/
    USB_CONNECTION_STATUS   ConnectionStatus;
    ULONG                   PortAttributes;
} USB_NODE_CONNECTION_ATTRIBUTES;
typedef USB_NODE_CONNECTION_ATTRIBUTES  *PUSB_NODE_CONNECTION_ATTRIBUTES;
#endif
#endif

#ifndef USB_KERNEL_IOCTL
  #if (_WIN32_WINNT >= 0x0501)
    /*USB_NODE_CONNECTION_INFORMATION_EX structure is used with the I/O control
      request IOCTL_USB_GET_NODE_CONNECTION_INFORMATION_EX to obtain
      information about the connection associated with the indicated USB port.

      If there is no device connected, result of the request is the information
      about the port. If a device is connected to the port, the structure
      contains information about both the port and the connected device.

      Note: Microsoft Windows XP and Windows .NET Server or newer specific.

      See also: "Universal Serial Bus Specification"
     */
    typedef struct _USB_NODE_CONNECTION_INFORMATION_EX
      {
      ULONG                   ConnectionIndex; /*specifies the number of 
                the port in the range [1, USB_HUB_DESCRIPTOR::bNumberOfPorts]*/
      USB_DEVICE_DESCRIPTOR   DeviceDescriptor; /*attached USB device description*/
      UCHAR                   CurrentConfigurationValue; /*ID of attached USB 
                                             device description configuration*/
      UCHAR                   Speed;  /*data transfer speed of  
                                        the attached USB device*/
      BOOLEAN                 DeviceIsHub; /*indicates if attached device is a hub*/
      USHORT                  DeviceAddress;/*bus-relative address of the 
                                              attached device*/
      ULONG                   NumberOfOpenPipes; /*number of open USB pipes
                                                   associated with the port*/
      USB_CONNECTION_STATUS   ConnectionStatus; /*connection status of the port*/
      USB_PIPE_INFO           PipeList[1]; /*list of the open pipes associated
                 with the port, including the associated endpoint descriptor*/
      } USB_NODE_CONNECTION_INFORMATION_EX;
    /*Extended USB node connection information*/
    typedef USB_NODE_CONNECTION_INFORMATION_EX  *PUSB_NODE_CONNECTION_INFORMATION_EX;
  #endif
#endif

/* USB hub capability flags */
#ifndef USB_KERNEL_IOCTL
#if (_WIN32_WINNT >= 0x0600)
typedef union _USB_HUB_CAP_FLAGS {
    ULONG   ul;
    struct {
        ULONG   HubIsHighSpeedCapable   : 1;
        ULONG   HubIsHighSpeed          : 1;
        ULONG   HubIsMultiTtCapable     : 1;
        ULONG   HubIsMultiTt            : 1;
        ULONG   HubIsRoot               : 1;
        ULONG   HubIsArmedWakeOnConnect : 1;
        ULONG   HubIsBusPowered         : 1;
        ULONG   ReservedMBZ             : 25;
    };
} USB_HUB_CAP_FLAGS;
typedef USB_HUB_CAP_FLAGS   *PUSB_HUB_CAP_FLAGS;
#endif
#endif

/* USB hub capabilities (extended version) */
#ifndef USB_KERNEL_IOCTL
#if (_WIN32_WINNT >= 0x0600)
typedef struct _USB_HUB_CAPABILITIES_EX {
    USB_HUB_CAP_FLAGS   CapabilityFlags;
} USB_HUB_CAPABILITIES_EX;
typedef USB_HUB_CAPABILITIES_EX *PUSB_HUB_CAPABILITIES_EX;
#endif
#endif

/* USB cycle port parameters */
#ifndef USB_KERNEL_IOCTL
#if (_WIN32_WINNT >= 0x0600)
typedef struct _USB_CYCLE_PORT_PARAMS {
    ULONG   ConnectionIndex; /*specifies the number of 
                the port in the range [1, USB_HUB_DESCRIPTOR::bNumberOfPorts]*/
    ULONG   StatusReturned;
} USB_CYCLE_PORT_PARAMS;
typedef USB_CYCLE_PORT_PARAMS   *PUSB_CYCLE_PORT_PARAMS;
#endif
#endif

/* USB identifier string */
#ifndef USB_KERNEL_IOCTL
#if (_WIN32_WINNT >= 0x0600)
typedef struct _USB_ID_STRING {
    USHORT  LanguageId;
    USHORT  Pad;
    ULONG   LengthInBytes;
    PWCHAR  Buffer;
} USB_ID_STRING;
typedef USB_ID_STRING   *PUSB_ID_STRING;
#endif
#endif

/* Hub device configuration information (version 1) */
#ifndef USB_KERNEL_IOCTL
#if (_WIN32_WINNT >= 0x0600)
typedef struct _HUB_DEVICE_CONFIG_INFO_V1 {
    ULONG               Version;
    ULONG               Length;
    USB_HUB_CAP_FLAGS   HubFlags;
    USB_ID_STRING       HardwareIds;
    USB_ID_STRING       CompatibleIds;
    USB_ID_STRING       DeviceDescription;
    ULONG               Reserved[36];
} HUB_DEVICE_CONFIG_INFO;
typedef HUB_DEVICE_CONFIG_INFO  *PHUB_DEVICE_CONFIG_INFO;
#endif
#endif

/* HCD statistics counters */
#ifndef USB_KERNEL_IOCTL
typedef struct _HCD_STAT_COUNTERS {
    ULONG   BytesTransferred;
    USHORT  IsoMissedCount;
    USHORT  DataOverrunErrorCount;
    USHORT  CrcErrorCount;
    USHORT  ScheduleOverrunCount;
    USHORT  TimeoutErrorCount;
    USHORT  InternalHcErrorCount;
    USHORT  BufferOverrunErrorCount;
    USHORT  SWErrorCount;
    USHORT  StallPidCount;
    USHORT  PortDisableCount;
} HCD_STAT_COUNTERS;
typedef HCD_STAT_COUNTERS   *PHCD_STAT_COUNTERS;
#endif

/* HCD ISO statistics counters */
#ifndef USB_KERNEL_IOCTL
typedef struct _HCD_ISO_STAT_COUNTERS {
    USHORT  LateUrbs;
    USHORT  DoubleBufferedPackets;
    USHORT  TransfersCF_5ms;
    USHORT  TransfersCF_2ms;
    USHORT  TransfersCF_1ms;
    USHORT  MaxInterruptLatency;
    USHORT  BadStartFrame;
    USHORT  StaleUrbs;
    USHORT  IsoPacketNotAccessed;
    USHORT  IsoPacketHWError;
    USHORT  SmallestUrbPacketCount;
    USHORT  LargestUrbPacketCount;
    USHORT  IsoCRC_Error;
    USHORT  IsoOVERRUN_Error;
    USHORT  IsoINTERNAL_Error;
    USHORT  IsoUNKNOWN_Error;
    ULONG   IsoBytesTransferred;
    USHORT  LateMissedCount;
    USHORT  HWIsoMissedCount;
    ULONG   Reserved7[8];
} HCD_ISO_STAT_COUNTERS;
typedef HCD_ISO_STAT_COUNTERS   *PHCD_ISO_STAT_COUNTERS;
#endif

/* HCD statistics information (version 1) */
#ifndef USB_KERNEL_IOCTL
typedef struct _HCD_STAT_INFORMATION_1 {
    ULONG               Reserved1;
    ULONG               Reserved2;
    ULONG               ResetCounters;
    LARGE_INTEGER       TimeRead;
    HCD_STAT_COUNTERS   Counters;
} HCD_STAT_INFORMATION_1;
typedef HCD_STAT_INFORMATION_1  *PHCD_STAT_INFORMATION_1;
#endif

/* HCD statistics information (version 2) */
#ifndef USB_KERNEL_IOCTL
typedef struct _HCD_STAT_INFORMATION_2 {
    ULONG                   Reserved1;
    ULONG                   Reserved2;
    ULONG                   ResetCounters;
    LARGE_INTEGER           TimeRead;
    LONG                    LockedMemoryUsed;
    HCD_STAT_COUNTERS       Counters;
    HCD_ISO_STAT_COUNTERS   IsoCounters;
} HCD_STAT_INFORMATION_2;
typedef HCD_STAT_INFORMATION_2  *PHCD_STAT_INFORMATION_2;
#endif

/* USB notification types */
#ifndef USB_KERNEL_IOCTL
typedef enum _USB_NOTIFICATION_TYPE {
    EnumerationFailure      = 0,
    InsufficientBandwidth   = 1,
    InsufficientPower       = 2,
    OverCurrent             = 3,
    ResetOvercurrent        = 4,
    AcquireBusInfo          = 5,
    AcquireHubName          = 6,
    AcquireControllerName   = 7,
    HubOvercurrent          = 8,
#if (_WIN32_WINNT >= 0x0501)
    HubPowerChange          = 9,
    HubNestedTooDeeply      = 10,
    ModernDeviceInLegacyHub = 11
#else
    HubPowerChange          = 9
#endif
} USB_NOTIFICATION_TYPE;
#endif

/* USB notification */
#ifndef USB_KERNEL_IOCTL
typedef struct _USB_NOTIFICATION {
    USB_NOTIFICATION_TYPE   NotificationType;
} USB_NOTIFICATION;
typedef USB_NOTIFICATION    *PUSB_NOTIFICATION;
#endif

/* USB connection notification */
#ifndef USB_KERNEL_IOCTL
typedef struct _USB_CONNECTION_INFORMATION {
    USB_NOTIFICATION_TYPE   NotificationType;
    ULONG                   ConnectionNumber;
    ULONG                   RequestedBandwidth;
    ULONG                   EnumerationFailReason;
    ULONG                   PowerRequested;
    ULONG                   HubNameLength;
} USB_CONNECTION_INFORMATION;
typedef USB_CONNECTION_INFORMATION  *PUSB_CONNECTION_INFORMATION;
#endif

/* USB bus notification */
#ifndef USB_KERNEL_IOCTL
typedef struct _USB_BUS_NOTIFICATION {
    USB_NOTIFICATION_TYPE   NotificationType;
    ULONG                   TotalBandwidth;
    ULONG                   ConsumedBandwidth;
    ULONG                   ControllerNameLength;
} USB_BUS_NOTIFICATION;
typedef USB_BUS_NOTIFICATION    *PUSB_BUS_NOTIFICATION;
#endif

/* USB acquire information */
#ifndef USB_KERNEL_IOCTL
typedef struct _USB_ACQUIRE_INFO {
    USB_NOTIFICATION_TYPE   NotificationType;
    ULONG                   TotalSize;
    WCHAR                   Buffer[1];
} USB_ACQUIRE_INFO;
typedef USB_ACQUIRE_INFO    *PUSB_ACQUIRE_INFO;
#endif

/* USB WMI device node types */
#ifndef USB_KERNEL_IOCTL
#if (_WIN32_WINNT >= 0x0600)
typedef enum _USB_WMI_DEVICE_NODE_TYPE {
    UsbDevice       = 0,
    HubDevice       = 1,
    CompositeDevice = 2,
    UsbController   = 3
} USB_WMI_DEVICE_NODE_TYPE;
typedef USB_WMI_DEVICE_NODE_TYPE    *PUSB_WMI_DEVICE_NODE_TYPE;
#endif
#endif

/* USB device state */
#ifndef USB_KERNEL_IOCTL
#if (_WIN32_WINNT >= 0x0600)
typedef struct _USB_DEVICE_STATE {
    ULONG   DeviceConnected : 1;
    ULONG   DeviceStarted   : 1;
} USB_DEVICE_STATE;
typedef USB_DEVICE_STATE    *PUSB_DEVICE_STATE;
#endif
#endif

/* USB hub port information */
#ifndef USB_KERNEL_IOCTL
#if (_WIN32_WINNT >= 0x0600)
typedef struct _USB_HUB_PORT_INFORMATION {
    USB_DEVICE_STATE        DeviceState;
    USHORT                  PortNumber;
    USHORT                  DeviceAddress;
    ULONG                   ConnectionIndex;  /*specifies the number of 
                the port in the range [1, USB_HUB_DESCRIPTOR::bNumberOfPorts]*/
    USB_CONNECTION_STATUS   ConnectionStatus;
} USB_HUB_PORT_INFORMATION;
typedef USB_HUB_PORT_INFORMATION    *PUSB_HUB_PORT_INFORMATION;
#endif
#endif

/* USB hub device information */
#ifndef USB_KERNEL_IOCTL
#if (_WIN32_WINNT >= 0x0600)
typedef struct _USB_HUB_DEVICE_INFO {
    USB_HUB_DESCRIPTOR          HubDescriptor;
    ULONG                       HubNumber;
    USHORT                      DeviceAddress;
    BOOLEAN                     HubIsSelfPowered;
    BOOLEAN                     HubIsRootHub;
    USB_HUB_CAPABILITIES        HubCapabilities;
    ULONG                       NumberOfHubPorts;
    USB_HUB_PORT_INFORMATION    PortInfo[1];
} USB_HUB_DEVICE_INFO;
typedef USB_HUB_DEVICE_INFO *PUSB_HUB_DEVICE_INFO;
#endif
#endif

/* USB composite function information */
#ifndef USB_KERNEL_IOCTL
#if (_WIN32_WINNT >= 0x0600)
typedef struct _USB_COMPOSITE_FUNCTION_INFO {
    UCHAR   FunctionNumber;
    UCHAR   BaseInterfaceNumber;
    UCHAR   NumberOfInterfaces;
    BOOLEAN FunctionIsIdle;
} USB_COMPOSITE_FUNCTION_INFO;
typedef USB_COMPOSITE_FUNCTION_INFO *PUSB_COMPOSITE_FUNCTION_INFO;
#endif
#endif

/* USB composite device information */
#ifndef USB_KERNEL_IOCTL
#if (_WIN32_WINNT >= 0x0600)
typedef struct _USB_COMPOSITE_DEVICE_INFO {
    USB_DEVICE_DESCRIPTOR           DeviceDescriptor;
    USB_CONFIGURATION_DESCRIPTOR    CurrentConfigDescriptor;
    UCHAR                           CurrentConfigurationValue;
    UCHAR                           NumberOfFunctions;
    USB_COMPOSITE_FUNCTION_INFO     FunctionInfo[1];
} USB_COMPOSITE_DEVICE_INFO;
typedef USB_COMPOSITE_DEVICE_INFO   *PUSB_COMPOSITE_DEVICE_INFO;
#endif
#endif

/* USB controller device information */
#ifndef USB_KERNEL_IOCTL
#if (_WIN32_WINNT >= 0x0600)
typedef struct _USB_CONTROLLER_DEVICE_INFO {
    ULONG   PciVendorId;
    ULONG   PciDeviceId;
    ULONG   PciRevision;
    ULONG   NumberOfRootPorts;
    ULONG   HcFeatureFlags;
} USB_CONTROLLER_DEVICE_INFO;
typedef USB_CONTROLLER_DEVICE_INFO  *PUSB_CONTROLLER_DEVICE_INFO;
#endif
#endif

/* USB device information */
#ifndef USB_KERNEL_IOCTL
#if (_WIN32_WINNT >= 0x0600)
typedef struct _USB_DEVICE_INFO {
    USB_DEVICE_STATE        DeviceState;
    USHORT                  PortNumber;
    USB_DEVICE_DESCRIPTOR   DeviceDescriptor;
    UCHAR                   CurrentConfigurationValue;
    USB_DEVICE_SPEED        Speed;
    USHORT                  DeviceAddress;
    ULONG                   ConnectionIndex; /*specifies the number of 
                the port in the range [1, USB_HUB_DESCRIPTOR::bNumberOfPorts]*/
    USB_CONNECTION_STATUS   ConnectionStatus;
    WCHAR                   PnpHardwareId[128];
    WCHAR                   PnpCompatibleId[128];
    WCHAR                   SerialNumberId[128];
    WCHAR                   PnpDeviceDescription[128];
    ULONG                   NumberOfOpenPipes;
    USB_PIPE_INFO           PipeList[1];
} USB_DEVICE_INFO;
typedef USB_DEVICE_INFO *PUSB_DEVICE_INFO;
#endif
#endif

/* USB device node information */
#ifndef USB_KERNEL_IOCTL
#if (_WIN32_WINNT >= 0x0600)
typedef struct _USB_DEVICE_NODE_INFO {
    ULONG                       Sig;
    ULONG                       LengthInBytes;
    WCHAR                       DeviceDescription[40];
    USB_WMI_DEVICE_NODE_TYPE    NodeType;
    USB_TOPOLOGY_ADDRESS        BusAddress;
    union {
        USB_DEVICE_INFO             UsbDeviceInfo;
        USB_HUB_DEVICE_INFO         HubDeviceInfo;
        USB_COMPOSITE_DEVICE_INFO   CompositeDeviceInfo;
        USB_CONTROLLER_DEVICE_INFO  ControllerDeviceInfo;
        UCHAR                       DeviceInformation[4];
    };
} USB_DEVICE_NODE_INFO;
typedef USB_DEVICE_NODE_INFO    *PUSB_DEVICE_NODE_INFO;
#endif
#endif

/* USB device performance information */
#ifndef USB_KERNEL_IOCTL
#if (_WIN32_WINNT >= 0x0600)
typedef struct _USB_DEVICE_PERFORMANCE_INFO {
    ULONG               BulkBytes;
    ULONG               ControlDataBytes;
    ULONG               IsoBytes;
    ULONG               InterruptBytes;
    ULONG               BulkUrbCount;
    ULONG               ControlUrbCount;
    ULONG               IsoUrbCount;
    ULONG               InterruptUrbCount;
    ULONG               AllocedInterrupt[6];
    ULONG               AllocedIso;
    ULONG               Total32secBandwidth;
    ULONG               TotalTtBandwidth;
    WCHAR               DeviceDescription[60];
    USB_DEVICE_SPEED    DeviceSpeed;
    ULONG               TotalIsoLatency;
    ULONG               DroppedIsoPackets;
    ULONG               TransferErrors;
    ULONG               PciInterruptCount;
    ULONG               HcIdleState;
    ULONG               HcAsyncIdleState;
    ULONG               HcAsyncCacheFlushCount;
    ULONG               HcPeriodicIdleState;
    ULONG               HcPeriodicCacheFlushCount;
} USB_DEVICE_PERFORMANCE_INFO;
typedef USB_DEVICE_PERFORMANCE_INFO *PUSB_DEVICE_PERFORMANCE_INFO;
#endif
#endif

/*----------------------------------------------------------------------------*/
/* Revert to default packing.                                                 */
#include <poppack.h>

#endif //WIN32

#ifdef __cplusplus
  } /* extern "C" */
#endif
///////////////////////////////////////////////////////////////////////////////
#endif /* __USBIOCTL_H__ */
/*****************************************************************************
 * $Log: UsbIoCtl.h,v $
 * Revision 1.12  2009/08/07 21:45:13  ddarko
 * Comments
 *
 * Revision 1.11  2009/07/20 21:51:12  ddarko
 * *** empty log message ***
 *
 * Revision 1.10  2009/07/14 21:36:24  ddarko
 * Code cleanup
 *
 * Revision 1.9  2009/07/13 22:04:01  ddarko
 * Description
 *
 * Revision 1.8  2009/07/12 21:10:26  ddarko
 * Comments
 *
 * Revision 1.7  2009/06/30 18:35:05  ddarko
 * Windows tag
 *
 * Revision 1.6  2009/06/30 17:41:15  ddarko
 * Updated version
 *
 * Revision 1.5  2009/05/22 18:41:03  ddarko
 * Consolidated items across the header files
 *
 * Revision 1.4  2009/05/20 21:43:47  ddarko
 * IOCTL comments
 *
 * Revision 1.3  2009/05/20 20:51:38  ddarko
 * Clean version of USB stack
 *
 *****************************************************************************/

/*Copyright (c) Microsoft Corporation. All rights reserved.
   This file defines both kernel and user mode IOCTL codes supported by
   the USB core stack.
 */

/*Contributors:
 *   Created by Casper S. Hornstrup <chorns@users.sourceforge.net>
 *
 * THIS SOFTWARE IS NOT COPYRIGHTED
 *
 * This source code is offered for use in the public domain. You may
 * use, modify or distribute it freely.
 *
 * This code is distributed in the hope that it will be useful but
 * WITHOUT ANY WARRANTY. ALL WARRANTIES, EXPRESS OR IMPLIED ARE HEREBY
 * DISCLAIMED. This includes but is not limited to warranties of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/*Open Watcom is a project of the open source community to maintain and enhance
  the Watcom C, C++, and Fortran cross compilers and tools.
  An Open Source license from Sybase allows free commercial and non-commercial
  use of Open Watcom.
  http://www.openwatcom.org/index.php/Open_Watcom_Public_License
 */