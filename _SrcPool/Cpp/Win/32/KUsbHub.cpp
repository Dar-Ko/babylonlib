/*$Workfile: S:\_SrcPool\Cpp\Win\32\KUsbHub.cpp$: implementation file
  $Revision: 1$ $Date: 22/08/2007 7:29:10 PM$
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
    //Get the system name of the host controller
    USB_HCD_DRIVERKEY_NAME sUnicodeName;
    DWORD dwBytesReturned; 
    bool bRes = DeviceIoControl(hHcd, //handle to the device 
                              IOCTL_GET_HCD_DRIVERKEY_NAME, //control code for the operation
                              &sUnicodeName, //input buffer 
                              sizeof(sUnicodeName), //size of input buffer 
                              &sUnicodeName, //output buffer
                              sizeof(sUnicodeName), //size of output buffer
                              &dwBytesReturned, //size of the data stored in 
                                                //the output buffer
                              NULL //lpOverlapped is ignored
                             );
  if (!bRes)
    {
    CloseHandle(hHcd);
    DWORD dwError = GetLastError();
    
    //TODO: report the error!
    break;
    }
    
  TRACE1(_T("System name is %ws\n"), &UnicodeName.Name[0]);

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
 *  1    Biblioteka1.0         22/08/2007 7:29:10 PMDarko Kolakovic 
 * $
 *****************************************************************************/

/*Note:Used code from Microsoft Windows DDK sample USBView
 */
