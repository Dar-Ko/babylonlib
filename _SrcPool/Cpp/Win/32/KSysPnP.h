/*$RCSfile: KSysPnP.h$: header file
  $Revision: 4$ $Date: 2007-08-24 18:15:44$
  $Author: Darko Kolakovic$

  Names of the system-supplied PnP enumerators
  Note: Microsoft Windows specific (Win).
  Copyright: CommonSoft Inc
  2004-05-12 Darko Kolakovic
 */
// Group=Windows

#ifndef _KSYSPNP_H_
    //$RCSfile: KSysPnP.h$ sentry
  #define _KSYSPNP_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifdef _WIN32 //Windows 32-bit platform

////////////////////////////////////////////////////////////////////////////////
//Symbolic names of names of the system-supplied PnP enumerators used for
//Device Identification.
//The Plug and Play (PnP) manager and Setup use device identification strings
//to identify devices that are installed in a system.
//Most, but not all, identifier strings are bus-specific.
//
//See also: MSDN: Windows Driver Kit: Device Installation

/*System-supplied PnP enumerator name for Peripheral Component Interconnect (PCI)
  devices.

  The following is a list of the device identification string formats that the
  PCI bus driver uses to report hardware IDs:

    PCI\VEN_v(4)&DEV_d(4)&SUBSYS_s(4)n(4)&REV_r(2)
    PCI\VEN_v(4)&DEV_d(4)&SUBSYS_s(4)n(4)
    PCI\VEN_v(4)&DEV_d(4)&REV_r(2)
    PCI\VEN_v(4)&DEV_d(4)
    PCI\VEN_v(4)&DEV_d(4)&CC_c(2)s(2)p(2)
    PCI\VEN_v(4)&DEV_d(4)&CC_c(2)s(2)

  See also: MSDN: Windows Driver Kit: Device Installation
 */
#define SYSTEMENUM_PCI _T("PCI")

/*System-supplied PnP enumerator name for for a Small Computer System Interface
  (SCSI) devices.

  The device ID format for a SCSI device is:

    SCSI\t*v(8)p(16)r(4)

  See also: MSDN: Windows Driver Kit: Device Installation
 */
#define SYSTEMENUM_SCSI _T("SCSI")

/*System-supplied PnP enumerator name for Integrated Device Electronics (IDE)
  devices.

  The device ID format for an IDE device is:

    IDE\t*v(40)r(8)

  See also: MSDN: Windows Driver Kit: Device Installation
 */
#define SYSTEMENUM_IDE _T("IDE")

/*System-supplied PnP enumerator name for Personal Computer Memory Card
  International Association (PCMCIA) devices.

  The device ID format for a one-functional PCMCIA device is:

    PCMCIA\Manufacturer-Product-Crc(4)

  Multifunctional devices have different format for the device ID.

  See also: MSDN: Windows Driver Kit: Device Installation
 */
#define SYSTEMENUM_PCMCIA _T("PCMCIA")

/*System-supplied PnP enumerator name for Industry Standard Architecture (ISA)
  devices.

  The device ID format created by ISA PnP enumerator for an ISA device is:

    ISAPNP\m(3)d(4)

  See also: MSDN: Windows Driver Kit: Device Installation
 */
#define SYSTEMENUM_ISA _T("ISAPNP")


/*System-supplied PnP enumerator name for Apple Computer's FireWire devices
  as described by IEEE 1394 standard.

  The device ID formats created by the 1394 bus driver for a FireWire device are:

    1394\VendorName&ModelName
    1394\UnitSpecId&UnitSwVersion

  See also: MSDN: Windows Driver Kit: Device Installation; IEEE 1394, FireWire
 */
#define SYSTEMENUM_1394 _T("1394")
/*System-supplied PnP enumerator name for Apple Computer's FireWire devices
  as described by IEEE 1394 standard.

  See also: SYSTEMENUM_1394; MSDN: Windows Driver Kit: Device Installation;
  IEEE 1394, FireWire
 */
#define SYSTEMENUM_FIREWIRE SYSTEMENUM_1394

/*System-supplied PnP enumerator name for Secure Digital (SD) devices.

  The device ID format for an SD memory device is:

    SD\VID_v(2)&OID_o(4)&PID_p(0-5)&REV_n(1).m(1)

  The device ID format of an SD I/O device is:

    SD\VID_v(4)&PID_p(4)

  See also: MSDN: Windows Driver Kit: Device Installation
 */
#define SYSTEMENUM_SD _T("SD")

/*System-supplied PnP enumerator name for Universal Serial Bus (USB)
  devices.

  The device ID format created by Microsoft Windows USB Hub driver for a USB
  device is:

    USB\VID_v(4)&PID_d(4)&REV_r(4)

  Multiple-Interface USB Devices have ID in the format:

    USB\VID_v(4)&PID_d(4)&MI_z(2)

  See also: MSDN: Windows Driver Kit: Device Installation
 */
#define SYSTEMENUM_USB _T("USB")

/*System-supplied PnP enumerator name for priners using Universal Serial Bus
  (USB).

  The device ID format for a USB printers is:

    USBPRINT\NameModel(20)Checksum(4)

  See also: MSDN: Windows Driver Kit: Device Installation
 */
#define SYSTEMENUM_USBPRINT _T("USBPRINT")

/*System-supplied PnP enumerator name for mass storage devices using Universal
  Serial Bus (USB).

  The device ID format for a USB mass storage devices is:

    USBSTOR\v(8)p(16)r(4)

  See also: MSDN: Windows Driver Kit: Device Installation
 */
#define SYSTEMENUM_USBSTOR _T("USBSTOR")

/*Human Interface Device (HID) class.
  The device ID format is:

    HID\Vid_v(4)&Pid_d(4)&REV_r(4)
 */
#define SYSTEMENUM_HID _T("HID")

/*Advanced Configuration and Power Interface (ACPI) device class
 */
#define SYSTEMENUM_ACPI _T("ACPI")

#define SYSTEMENUM_LPT _T("LPTENUM")

//------------------------------------------------------------------------------
//Device I/O control

#ifndef SYMBOLICLINK_PREFIX
  /*Device name prefix used to create complete device name.
    Following format is used for the device names:

      \\.\DeviceName

    where DeviceName could be a specific device or logical drive name, for
    example "\\.\c:" or "\\.\PhysicalDrive1", "\\.\HDC0"

    Note: Microsoft Windows specific (Win32).

    See also: DeviceIoControl(), CreateSymbolicLink(), CreateFile().
  */
  #define SYMBOLICLINK_PREFIX  L"\\\\.\\"
  //Length of device name prefix in bytes
  #define SYMBOLICLINK_PREFIX_LEN (4 * sizeof(wchar_t))
#endif

#ifndef SYMBOLICLINK_HCD
  /*Symbolic name for USB Host Controller Driver (HCD) modules have following
    form:

        \\.\HCDn
        where n (0,...,k) is module instance number in the driver's stack.

    Host controller is also known as the root hub, the root tier or
    simply as the root.
    Note: USB driver uses two different stacks for USB 1.1 and USB 2.0 host
    controllers.
    Note: Microsoft Windows specific (Win32).

    See also: MSDN KB838100,  "The USBView.exe sample program does not
    enumerate devices on pre-Windows XP SP1-based computers";
    CreateSymbolicLink().
  */
  #define SYMBOLICLINK_HCD "\\\\.\\HCD%d"
#endif

#endif //_WIN32
///////////////////////////////////////////////////////////////////////////////
#endif  //_KSYSPNP_H_
/*****************************************************************************
 * $Log: $
 *****************************************************************************/
