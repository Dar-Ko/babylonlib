/*$Workfile: KGetDevDesc.cpp$: implementation file
  $Revision: 5$ $Date: 2007-08-24 18:15:42$
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
    #define TRACE2 ATLTRACE
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
// MS Code sample
TCHAR buf[512];  //  How big does this have to be? Dynamically size it? 
// TODO: Dynamically allocate return buffer
// The caller should copy the returned string buffer instead of just saving
// the pointer value.   
//*****************************************************************************

class CCmMachine
  {
  public:
    CCmMachine(LPCTSTR szUncServerName = NULL//[in] Caller-supplied pointer to a text 
      //string representing the UNC name, including the \\ prefix, of the 
      //system for which a connection will be made. 
      //If the pointer is NULL, the local system is used. 
       )
      {
      //Note: use machine handles obtained with this function only with 
      //the PnP configuration manager functions.
      CONFIGRET crRes = CM_Connect_Machine(szUncServerName, &m_hMachine);
      if (crRes != CR_SUCCESS)
        m_hMachine = INVALID_HANDLE_VALUE;
      };
    ~CCmMachine()
      {
      CONFIGRET crRes;
      if (m_hMachine != INVALID_HANDLE_VALUE)
        crRes = CM_Disconnect_Machine(m_hMachine);
      };
    operator HMACHINE()
      {
      return m_hMachine;
      };
    HMACHINE m_hMachine; //machine handle required by the PnP configuration 
                         //manager functions
  };

//-----------------------------------------------------------------------------
/*Obtains description of a node on the PnP device tree. The function allocates 
  memory space required to hold the description by using new[] operator.
  Caller is responsible for deleting allocated memory.
  
  Returns: true and Device Description string or false in case of a failure.
  found.
 */
bool GetDeviceDesc(const DEVNODE* pDevNode, //[in]
                   TCHAR* szBuff //[out]
                   )
{
if ((pDevNode == NULL) || (szBuff == NULL))
  return false;

const int BUFFERSIZE = MAX_PATH + MAX_DEVICE_ID_LEN;
szBuff = new TCHAR[BUFFERSIZE];
DWORD dwLen = BUFFERSIZE * sizeof(TCHAR);
if (szBuff != NULL)
  {
  CCmMachine hLocalMachine;
  /*TODO: Do not use CM_Get_DevNode_Registry_Property_Ex function. 
    Use SetupDiGetDeviceRegistryProperty function instead (Windows Driver Kit note).
    */
  if (CM_Get_DevNode_Registry_Property_Ex(*pDevNode,
                                          CM_DRP_FRIENDLYNAME, 
                                          NULL,
                                          szBuff, 
                                          &dwLen, 
                                          0, 
                                          hLocalMachine) == CR_SUCCESS)
    {
    return true;
    }
  
  dwLen = BUFFERSIZE * sizeof(TCHAR);
  if (CM_Get_DevNode_Registry_Property_Ex(*pDevNode,
                                          CM_DRP_DEVICEDESC, 
                                          NULL,
                                          szBuff, 
                                          &dwLen, 
                                          0, 
                                          hLocalMachine) == CR_SUCCESS)
    {
    return true;
    }
  }

szBuff[0] = 0; //Return empty string
return false;
}

//-----------------------------------------------------------------------------
/*Obtains description of the PnP device on the local machine represented by 
  the driver registry key.

  Returns: Device Description string or NULL if the matching device is not 
  found.
 */
LPCTSTR GetDeviceDesc(LPCTSTR szDriverRegistryName //[in] driver registry 
                                                   //key name 
                     )
{
#ifdef _UNICODE
  TRACE1(_T("GetDeviceDesc(%ws)\n"),szDriverRegistryName);
#else
  TRACE1(_T("GetDeviceDesc(%s)\n"),szDriverRegistryName);
#endif

LPTSTR    szResult = NULL; //device description
DEVINST   diRoot;          //root device instance handle
CONFIGRET crResult;        //result of Configuration Manager function

#ifdef _DEBUG
  extern LPCTSTR DumpConfigRet(const CONFIGRET crCode);
  short dbgInsane = 0; //Sanity checking
#endif
/*Obtain a device instance handle to the device node that is associated with
  a specified device instance identifier, on the local machine.
 */
if((crResult = CM_Locate_DevNode(&diRoot, //[out] device instance handle
                                //on local machine
                       NULL,    //if NULL, get the device 
                                //at the root of the device tree.
                       CM_LOCATE_DEVNODE_NORMAL //get the device that is 
                                //currently configured in the device tree
                       )) == CR_SUCCESS)
  {
  //Browse through the device tree until matched device registry key is not found
  //See also: http://msdn2.microsoft.com/en-us/library/aa489660.aspx 
  //"Windows Driver Kit: Kernel-Mode Driver Architecture", "Device Tree"
  bool bCompleted = false;
  do
    {
    #ifdef _DEBUG
    if (++dbgInsane < 0) //Break endless loop
      {
      bCompleted = true;
      crResult = CR_INVALID_DATA;
      TRACE(_T("  Failure: browsing the device tree have too many iterations!\n"));
      break;
      }
    #endif
    ULONG nSize = sizeof(buf); //size of output buffer in bytes

    //Get the device driver property from the registry
    /*TODO: Do not use CM_Get_DevNode_Registry_Property function. 
      Use SetupDiGetDeviceRegistryProperty function instead (Windows Driver Kit note).
     */
    crResult = CM_Get_DevNode_Registry_Property(diRoot, //device instance handle
                                               //of a node from the device tree
                                          CM_DRP_DRIVER, //device driver property
                                          NULL, //registry data type
                                          buf,
                                          &nSize, //[IN, OUT] size of 
                                        //the requested device property in bytes
                                          0    //not used
                                          );
    if (crResult == CR_SUCCESS)
      {
      //Get the required device description
      if(_tcsicmp(szDriverRegistryName, buf) == 0)
        {
        nSize = sizeof(buf);
        if((crResult = CM_Get_DevNode_Registry_Property(diRoot,
                                              CM_DRP_DEVICEDESC,
                                              NULL,
                                              buf,
                                              &nSize,
                                              0
                                              )) == CR_SUCCESS)
          {
          szResult = buf; //Return success
          }
        break; //Registry key found with or without the description
        }
      }
 
    //Failed to match device node, try with a child node
    #ifdef _DEBUG_GDD
      #ifdef _UNICODE
        #define DBG_FORMAT_A _T("  %d. Failed to match device node (%ws)!\n")
      #else
        #define DBG_FORMAT_A _T("  %d. Failed to match device node (%s)!\n")
      #endif

      TRACE2(DBG_FORMAT_A, 
             dbgInsane, 
             DumpConfigRet(crResult));
      if (crResult == CR_SUCCESS)
        TRACE(buf);
    #endif
      
    DEVINST diNode;
    if ((crResult = CM_Get_Child(&diNode,
                      diRoot,
                      0 //not used
                      )) == CR_SUCCESS)
      {
      #ifdef _DEBUG_GDD
        TRACE1(_T("  %d. Get child node\n"), dbgInsane);
      #endif

      diRoot = diNode; //Set new search starting point
      }
    else //Failed to find a child node, try with a sibling node
      {
      do
        {
        if ((crResult = CM_Get_Sibling(&diNode,
                            diRoot,
                            0
                            )) != CR_SUCCESS)
          {
          //No more sibling nodes, try with the parent's sibling
          if((crResult = CM_Get_Parent(&diNode,
                            diRoot,
                            0
                            )) == CR_SUCCESS)
            {
            crResult = CR_DEFAULT; //Do one more loop to get parent's sibling
            #ifdef _DEBUG_GDD
              TRACE1(_T("  %d. Get parent node\n"), dbgInsane);
            #endif
            }
          else
            {
            //No more parents, requested device node is not found
            bCompleted = true;
            break;
            }

          }
        #ifdef _DEBUG_GDD
        else
          TRACE1(_T("  %d. Get sibling node\n"), dbgInsane);
        #endif

        diRoot = diNode; //Set new search starting point
        } while(crResult != CR_SUCCESS);
      }
    } while (!bCompleted);
  }

#ifdef _DEBUG
if (crResult != CR_SUCCESS)
  {
  //A PnP Configuration Manager function returned one of the CR_Xxx error codes
  //that are defined in cfgmgr32.h.
  #ifdef _UNICODE
    TRACE1(_T("  Failed (%ws)!\n"), DumpConfigRet(crResult));
  #else
    TRACE1(_T("  Failed (%s)!\n"), DumpConfigRet(crResult));
  #endif
  }
#endif

return szResult;
}

#endif //_WIN32
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  5    Biblioteka1.4         2007-08-24 18:15:42  Darko Kolakovic SBCS build
 *  4    Biblioteka1.3         2007-08-24 17:29:55  Darko Kolakovic Redesigned
 *  3    Biblioteka1.2         2007-08-24 16:10:11  Darko Kolakovic Debug commands
 *  2    Biblioteka1.1         2007-08-24 10:53:19  Darko Kolakovic Unicode build
 *  1    Biblioteka1.0         2007-08-23 16:57:58  Darko Kolakovic 
 * $
 *****************************************************************************/

/*Note: Used code from Microsoft Windows DDK sample USBView
  Copyright (c) 1998-1998 Microsoft Corporation
  Module Name: DEVNODE.C
 */
