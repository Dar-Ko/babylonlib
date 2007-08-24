/*$Workfile: KGetDevDesc.cpp$: implementation file
  $Revision: 2$ $Date: 2007-08-24 10:53:19$
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

#if defined _ATL_VER 
  #ifndef TRACE
    #define TRACE ATLTRACE
    #define TRACE1 ATLTRACE
  #endif
#else
  #include <windows.h>
  #include <basetyps.h>
  #include <string.h>
#endif

#include <cfgmgr32.h> //PnP Configuration Manager Functions, Windows Platform DDK

#ifndef TRACE
  #ifndef _T
    #include "KTChar.h"
  #endif
  #include "KTrace.h"
#endif

/*Requires cfgmgr32.lib

  Note: If you intend that your device installation application run on 
  Windows 9x/Me, or Windows NT 4.0 or earlier, and you use the CM_Xxx functions, 
  be sure that cfgmgr32.lib appears before SetupAPI.lib in the sources file.
  If your application is intended to run only on Windows 2000 or 
  a later NT-based operating system, you can omit cfgmgr32.lib.
 */
#pragma comment( lib, "cfgmgr32" )

//*****************************************************************************
// G L O B A L S
//*****************************************************************************

TCHAR buf[512];  // XXXXX How big does this have to be? Dynamically size it? Dynamically allocate return buffer?

// The caller should copy the returned string buffer instead of just saving
// the pointer value.  XXXXX 
//*****************************************************************************

//-----------------------------------------------------------------------------
/*Obtains description of the PnP device represented by the driver registry key.

  Returns: Device Description string or NULL if the matching DevNode is not 
  found.
 */
LPCTSTR GetDeviceDesc(const WCHAR* szDriverRegistryName //[in] driver registry 
                                                        //key name 
                     )
{
TRACE1(_T("GetDeviceDesc(%ws)\n"),szDriverRegistryName);

DEVINST     devInst;
DEVINST     devInstNext;
CONFIGRET   cr;
ULONG       walkDone = 0;
ULONG       len;

// Get Root DevNode
//
cr = CM_Locate_DevNode(&devInst,
                        NULL,
                        0);

if (cr != CR_SUCCESS)
{
    return NULL;
}

// Do a depth first search for the DevNode with a matching
// szDriverRegistryName value
//
while (!walkDone)
{
    // Get the szDriverRegistryName value
    //
    len = sizeof(buf);
    cr = CM_Get_DevNode_Registry_Property(devInst,
                                          CM_DRP_DRIVER,
                                          NULL,
                                          buf,
                                          &len,
                                          0);

    // If the szDriverRegistryName value matches, return the DeviceDescription
    //
    if (cr == CR_SUCCESS && _tcsicmp(szDriverRegistryName, buf) == 0)
    {
        len = sizeof(buf);
        cr = CM_Get_DevNode_Registry_Property(devInst,
                                              CM_DRP_DEVICEDESC,
                                              NULL,
                                              buf,
                                              &len,
                                              0);

        if (cr == CR_SUCCESS)
        {
            return buf;
        }
        else
        {
            return NULL;
        }
    }

    // This DevNode didn't match, go down a level to the first child.
    //
    cr = CM_Get_Child(&devInstNext,
                      devInst,
                      0);

    if (cr == CR_SUCCESS)
    {
        devInst = devInstNext;
        continue;
    }

    // Can't go down any further, go across to the next sibling.  If
    // there are no more siblings, go back up until there is a sibling.
    // If we can't go up any further, we're back at the root and we're
    // done.
    //
    for (;;)
    {
        cr = CM_Get_Sibling(&devInstNext,
                            devInst,
                            0);

        if (cr == CR_SUCCESS)
        {
            devInst = devInstNext;
            break;
        }

        cr = CM_Get_Parent(&devInstNext,
                            devInst,
                            0);


        if (cr == CR_SUCCESS)
        {
            devInst = devInstNext;
        }
        else
        {
            walkDone = 1;
            break;
        }
    }
}

return NULL;
}

#endif //_WIN32
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  2    Biblioteka1.1         2007-08-24 10:53:19  Darko Kolakovic Unicode build
 *  1    Biblioteka1.0         2007-08-23 16:57:58  Darko Kolakovic 
 * $
 *****************************************************************************/

/*Note: Used code from Microsoft Windows DDK sample USBView
  Copyright (c) 1998-1998 Microsoft Corporation
  Module Name: DEVNODE.C
 */
