/*$RCSfile: KWinSerialEnum.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2011/08/04 15:40:29 $
  $Author: ddarko $

  Module : ENUMSER.H
  Purpose: Defines the interface for a single function to 
           enumerate the serial ports installed on a PC
  Created: PJN / 02-11-1998
  History: PJN / 23-02-1999 Now uses QueryDosDevice when running on NT.

  Copyright (c) 1998 - 1999 by PJ Naughter.  
  All rights reserved.
*/
/* Group=Windows                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#include "stdafx.h"
#include "KWinSerial.h" //Litterals

#ifndef __AFXTEMPL_H__
#pragma message("EnumerateSerialPorts function requires afxtempl.h in your PCH")                                                                                
#endif



///////////////////////////// Statics / Locals ////////////////////////////////

#ifdef _DEBUG
#undef THIS_FILE
#define new DEBUG_NEW
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

void EnumerateSerialPorts(CUIntArray& ports);


/*
  Note: Microsoft Windows specific (Win32).

  See also: 
 */


///////////////////////////// Implementation //////////////////////////////////

void EnumerateSerialPorts(CUIntArray& ports)
{
  //Make sure we clear out any elements which may already be in the array
  ports.RemoveAll();

  //Determine what OS we are running on
  OSVERSIONINFO osvi;
  osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
  BOOL bGetVer = GetVersionEx(&osvi);

  //On NT use the QueryDosDevice API
  if (bGetVer && (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT))
  {
    //Use QueryDosDevice to look for all devices of the form COMx. This is a better
    //solution as it means that no ports have to be opened at all.
    TCHAR szDevices[65535];
    DWORD dwChars = QueryDosDevice(NULL, szDevices, 65535);
    if (dwChars)
    {
      int i=0;

      for (;;)
      {
        //Get the current device name
        TCHAR* pszCurrentDevice = &szDevices[i];

        //If it looks like "COMX" then
        //add it to the array which will be returned
        int nLen = _tcslen(pszCurrentDevice);
        if (nLen > 3 && _tcsnicmp(pszCurrentDevice, _T("COM"), 3) == 0)
        {
          //Work out the port number
          int nPort = _ttoi(&pszCurrentDevice[3]);
          ports.Add(nPort);
        }

        // Go to next NULL character
        while(szDevices[i] != _T('\0'))
          i++;

        // Bump pointer to the next string
        i++;

        // The list is double-NULL terminated, so if the character is
        // now NULL, we're at the end
        if (szDevices[i] == _T('\0'))
          break;
      }
    }
    else
      TRACE(_T("Failed in call to QueryDosDevice, GetLastError:%d\n"), GetLastError());
  }
  else
  {
    //On 95/98 open up each port to determine their existence

    //Up to 255 COM ports are supported so we iterate through all of them seeing
    //if we can open them or if we fail to open them, get an access denied or general error error.
    //Both of these cases indicate that there is a COM port at that number. 
    for (UINT i=1; i<256; i++)
    {
      //Form the Raw device name
      CString sPort;
      sPort.Format(_T("\\\\.\\COM%d"), i);

      //Try to open the port
      BOOL bSuccess = FALSE;
      HANDLE hPort = ::CreateFile(sPort, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
      if (hPort == INVALID_HANDLE_VALUE)
      {
        DWORD dwError = GetLastError();

        //Check to see if the error was because some other app had the port open or a general failure
        if (dwError == ERROR_ACCESS_DENIED || dwError == ERROR_GEN_FAILURE)
          bSuccess = TRUE;
      }
      else
      {
        //The port was opened successfully
        bSuccess = TRUE;

        //Don't forget to close the port, since we are going to do nothing with it anyway
        CloseHandle(hPort);
      }

      //Add the port number to the array which will be returned
      if (bSuccess)
        ports.Add(i);
    }
  }
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: KWinSerialEnum.cpp,v $
 * Revision 1.1  2011/08/04 15:40:29  ddarko
 * PJ Naughter V1.02 (12 December 1999) http://www.codeproject.com/KB/system/enumports.aspx
 *
 *****************************************************************************/

/*
 EnumSerialPorts v1.02

Welcome to EnumSerialPorts v1.01, A simple MFC function to enumerate the serial ports installed on your machine.

 
Features
Usage
History
API Reference
Contacting the Author

Features

    Simple C style function interface.
    The code works on both Windows 95/98 and NT. The whole problem is that there is no standard Win32 API call which allows serial port enumeration. The approach that this code uses is if on NT it uses the QueryDosDevice otherwise it calls CreateFile directly. If the port cannot be opened, the code examines the error code to see if it was accessed denied error in which case it knows that the port exists even though it could not open the port.
    The code is fully Unicode compliant and include Unicode built options in the workspace file.

Usage

    To use the function in your code simply include enumser.cpp in your project and #include enumser.h in which ever of your modules needs to make calls to the function.
    Your code will need to include MFC either statically or dynamically.
    To see the class in action, have a look at the main function in the module "main.cpp".

History

V1.0 (3 November 1998)

    Initial public release.

V1.01 (23 February 1999)

    Code now uses QueryDosDevice if running on NT to determine which serial ports are available. This avoids having to open the ports at all. It should operate a lot faster in addition.

V1.02 (12 December 1999)

    Fixed a problem in the Win9x code path when trying to detect deactivated IRDA-ports. When trying to open those, you will get the error-code ERROR_GEN_FAILURE. 

API Reference

EnumerateSerialPorts

void ::EnumerateSerialPorts(CUIntArray&  ports);

Parameters

ports Upon return this array will contain the port numbers of all the serial ports installed on the computer

CONTACTING THE AUTHOR

PJ Naughter
Email: pjn@indigo.ie
Web: http://indigo.ie/~pjn
12 December 1999

License
This article has no explicit license attached to it but may contain usage terms in the article text or the download files themselves. If in doubt please contact the author via the discussion board below.

The Licenses
http://www.codeproject.com/info/Licenses.aspx

The following is a rough guide to the current licenses supported on The Code Project. Please read them carefully by following the links to the license pages themselves because some categorisations (such as whether code can be used commercially, or whether extensions must be release to the public) depends on the situtation. This is merely a guide: it's up to you to read the actual license carefully before using code licensed by each license or assigned a license to code you submit.
The Code Project Open License (CPOL)

The main points subject to the terms of the License are:

    Source Code and Executable Files can be used in commercial applications;
    Source Code and Executable Files can be redistributed; and
    Source Code can be modified to create derivative works.
    No claim of suitability, guarantee, or any warranty whatsoever is provided. The software is provided "as-is".

    Provides copyright protection: True
    Can be used in commercial applications: True
    Bug fixes / extensions must be released to the public domain: False
    Provides an explicit patent license: True
    Can be used in proprietary (closed source) applications: True
    Is a viral licence: False
    
*/