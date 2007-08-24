/*$Workfile: KUsbHub.cpp$: implementation file
  $Revision: 5$ $Date: 2007-08-24 18:15:43$
  $Author: Darko Kolakovic$

  Universal Serial Bus (USB) Host Controller
  Copyright: 1997-1998 Microsoft Corporation
  2004-03-03 Darko Kolakovic
  1997-25-04: Microsoft Corporation
 */

#ifdef _WIN32

#ifdef _USE_ATL
  //Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option) 
  //or preprocessor reports unpaired #endif directive

  #include "stdafx.h" //Standard system header files
#endif
  
#pragma include_alias( "stdint.h", "KType32.h" )
#include "stdint.h" //ISO C99 type definitions


#if defined _ATL_VER 
  #ifndef TRACE
    #define TRACE ATLTRACE
    #define TRACE1 ATLTRACE
  #endif
#else
  #include <windows.h>
  #include <string.h>
#endif

#ifndef TRACE
  #ifndef _T
    #include "KTChar.h"
  #endif
  #include "KTrace.h"
#endif

#include "KUsb.h"
#include "KWinUsb.h" //USB structures and enumerations

//-----------------------------------------------------------------------------
/*Enumerate Host Controllers
    Host controllers currently have symbolic names (link) of the form HCDx,
    where x starts at 0.  Use CreateFile() to open each host controller
    symbolic link.  Create a node in the TreeView to represent each host
    controller.

    After a host controller has been opened, send the host controller an
    IOCTL_USB_GET_ROOT_HUB_NAME request to get the symbolic link name of
    the root hub that is part of the host controller.

  Note: Microsoft Windows specific (Win32).

  See also: MSDN KB838100: The USBView.exe sample program does not enumerate 
  devices on pre-Windows XP SP1-based computers.
 */
uint_fast32_t EnumerateHostControllers()
{
TRACE(_T("EnumerateHostControllers()\n"));
unsigned short wInstance = 0; //HCD module instance number
char szHostControllerName[16]; //Host Controller Driver (HCD) symbolic name
const unsigned short ARBITRARY_NO = 12; //arbitrary maximum of instances
uint_fast32_t nResult = 0;
do 
  {
  //Create a symbolic link and open communication with HCD
  wsprintfA(szHostControllerName, SYMBOLICLINK_HDC , wInstance);
  HANDLE hHcd = CreateFileA(szHostControllerName,
                            GENERIC_WRITE,
                            FILE_SHARE_WRITE,
                            NULL, //if lpSecurityAttributes is NULL, 
                                  //the handle cannot be inherited.
                            OPEN_EXISTING,
                            0,
                            NULL);
  //Note: Windows Me/98/95: The file system restricts CreateFile to creating or
  //opening files streams only.
  if (hHcd != INVALID_HANDLE_VALUE)
    {
    //Retrieve the driver key name in the registry for a USB host controller driver.
    CUsbDriverKeyName usbDriverKeyName(hHcd);
    bool bRes = usbDriverKeyName.LoadKeyName(hHcd);
    if (!bRes)
      {
      CloseHandle(hHcd);
      DWORD dwError = GetLastError();
      
      //TODO: report the error!
      break;
      }
      
    TRACE1(_T("System name is %ws\n"), (const WCHAR*)usbDriverKeyName);
    TRACE(GetDeviceDesc(usbDriverKeyName));
    nResult++;
    CloseHandle(hHcd);
    }
  #ifdef _DEBUG
    else
      {
      //TODO: verify if instance numbers are always sequential; 
      //in that case break the loop when CreateFile fails. D.K.
      TRACE1(_T("  Failed to open \\\\.\\HCD%d!\n"), wInstance);
      }
  #endif
  wInstance++;
  }
while (wInstance < ARBITRARY_NO);

return nResult;
}
#endif
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  5    Biblioteka1.4         2007-08-24 18:15:43  Darko Kolakovic SBCS build
 *  4    Biblioteka1.3         2007-08-24 17:28:43  Darko Kolakovic Debug
 *       information
 *  3    Biblioteka1.2         2007-08-24 10:53:52  Darko Kolakovic Unicode build
 *  2    Biblioteka1.1         2007-08-23 17:21:17  Darko Kolakovic GetDevDesc()
 *  1    Biblioteka1.0         2007-08-22 19:29:10  Darko Kolakovic 
 * $
 *****************************************************************************/

/*Note: Used code from Microsoft Windows DDK sample USBView
 */
