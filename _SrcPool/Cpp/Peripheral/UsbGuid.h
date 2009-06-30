/*$RCSfile: UsbGuid.h,v $: header file
  $Revision: 1.2 $ $Date: 2009/06/30 17:41:15 $
  $Author: ddarko $

  USB specific GUIDs.
 */
#ifndef __USBGUID_H__
  #define __USBGUID_H__

#ifndef _ENABLE_AUTODEPEND
  #ifdef __WATCOMC__
    /*Watcom 32b Compiler*/
    #pragma read_only_file;
  #endif
#endif

#if __GNUC__ >= 3
  #pragma GCC system_header
#endif

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef WIN32
  /*Note: For Microsoft Visual C++ 6.0 and older, a GUID must be initialized
    exactly once. For more information refer the article:
    "How to avoid error "LNK2001 unresolved external" by using DEFINE_GUID"
    http://support.microsoft.com/kb/130869
    If the version of the compiler is newer than version 6.0, when you are
    using precompiled headers, you can include the INITGUID.H header file
    in a single header file that includes other header files.

    See also <PlatformSDK/include/guiddef.h>, <initguid.h>, DEFINE_GUID, INITGUID
   */
  #ifdef DEFINE_GUID
    /* GUID_DEVINTERFACE_USB_HUB = F18A0E88-C30C-11D0-8815-00A0C906BED8 */
    DEFINE_GUID(GUID_DEVINTERFACE_USB_HUB, \
      0xF18A0E88, 0xC30C, 0x11D0, 0x88, 0x15, 0x00, 0xA0, 0xC9, 0x06, 0xBE, 0xD8);

    /* GUID_DEVINTERFACE_USB_DEVICE = A5DCBF10-6530-11D2-901F-00C04FB951ED */
    DEFINE_GUID(GUID_DEVINTERFACE_USB_DEVICE, \
      0xA5DCBF10L, 0x6530, 0x11D2, 0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED);

    /*Class identifier for new instances of USB host controllers.
      GUID_DEVINTERFACE_USB_HOST_CONTROLLER = 3ABF6F2D-71C4-462a-8A92-1E6861E6AF27
      Note: Microsoft Windows 2000 and newer
     */
    DEFINE_GUID(GUID_DEVINTERFACE_USB_HOST_CONTROLLER, \
      0x3abf6f2d, 0x71c4, 0x462a, 0x8a, 0x92, 0x1e, 0x68, 0x61, 0xe6, 0xaf, 0x27);

    /* GUID_USB_WMI_STD_DATA = 4E623B20-CB14-11D1-B331-00A0C959BBD2 */
    DEFINE_GUID(GUID_USB_WMI_STD_DATA, \
      0x4E623B20L, 0xCB14, 0x11D1, 0xB3, 0x31, 0x00, 0xA0, 0xC9, 0x59, 0xBB, 0xD2);

    /* GUID_USB_WMI_STD_NOTIFICATION = 4E623B20-CB14-11D1-B331-00A0C959BBD2 */
    DEFINE_GUID(GUID_USB_WMI_STD_NOTIFICATION, \
      0x4E623B20L, 0xCB14, 0x11D1, 0xB3, 0x31, 0x00, 0xA0, 0xC9, 0x59, 0xBB, 0xD2);


    /*Obsolete device interface class GUID names kept for code compatibility.
     */

    #define GUID_CLASS_USBHUB               GUID_DEVINTERFACE_USB_HUB
    #define GUID_CLASS_USB_DEVICE           GUID_DEVINTERFACE_USB_DEVICE
    /*Class identifier for new instances of USB host controllers.
      GUID_CLASS_USB_HOST_CONTROLLER = 3ABF6F2D-71C4-462a-8A92-1E6861E6AF27

      Note: Microsoft Windows NT and older. Use GUID_DEVINTERFACE_USB_HOST_CONTROLLER
      instead.

      Intel 82801FB/FBM USB Universal Host Controller (UHC) Device CreateFile Name:
      \\?\pci#ven_8086&dev_2658&subsys_01811028&rev_03#3&172e68dd&0&e8#{3abf6f2d-71c4-462a-8a92-1e6861e6af27}
     */
    #define GUID_CLASS_USB_HOST_CONTROLLER  GUID_DEVINTERFACE_USB_HOST_CONTROLLER

  #endif /* DEFINE_GUID */
#endif //WIN32

#ifdef __cplusplus
} /* End of extern "C" */
#endif
///////////////////////////////////////////////////////////////////////////////
#endif /* __USBGUID_H__ */

/*****************************************************************************
 * $Log: UsbGuid.h,v $
 * Revision 1.2  2009/06/30 17:41:15  ddarko
 * Updated version
 *
 * Revision 1.1  2009/06/26 21:29:14  ddarko
 * Created
 *
 *****************************************************************************/

/*Copyright (c) Microsoft Corporation. All rights reserved.
  Common header file for all USB IOCTLs defined for the core stack.
  We divide the IOCTLS supported by the stack as follows:
   - kernel IOCTLS:
   - user IOCTLS:
      * IOCTLS Handled by HCD (PORT) FDO
      * IOCTLS Handled by HUB FDO
      * IOCTLS Handled by USB (DEVICE) PDO
  See also: ddk/inc/wxp/usbiodef.h
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
