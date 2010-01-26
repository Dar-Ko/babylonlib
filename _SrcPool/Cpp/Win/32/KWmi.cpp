/*$RCSfile: KWmi.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2010/01/26 22:47:05 $
  $Author: ddarko $

  Microsoft Windows Management Instrumentation (WMI) client.
  Copyright: Darko Kolakovic
  Darko Kolakovic 2010-01-15
 */
#include "stdafx.h"
#include "KWmi.h" //CWmi class

///////////////////////////////////////////////////////////////////////////////
// CWmi class implementation
// To create an application for WMI you must initialize COM, access and set WMI
// protocols and perform a manual cleanup. Follow next steps:
//   1. Initialize COM.
//      Because WMI is based on COM technology, you must perform calls to the 
//      CoInitializeEx and CoInitializeSecurity functions to access WMI.
//   2. Create a connection to a WMI namespace.
//      By definition, WMI runs in a different process than your application. 
//      Therefore, you must create a connection between your application and WMI.
//   3. Set the security levels on the WMI connection.
//      To use the connection you create to WMI, you must set the impersonation 
//      and authentication levels for your application.
//   4. Implement the purpose of your application.
//      WMI exposes a variety of COM interfaces use to access and manipulate data 
//      across your enterprise. For more information, see Manipulating Class and 
//      Instance Information, Receiving a WMI Event, and COM API for WMI.
//      This is where the bulk of your WMI client application should exist, such 
//      as accessing WMI objects or manipulating data.
//   5. Cleanup and shut down your application.
//      After you complete your queries to WMI, you should destroy all COM pointers
//      and shut down your application correctly.
// Reference: MSDN: Creating a WMI Application Using C++, 
// http://msdn.microsoft.com/en-us/library/aa389762%28VS.85%29.aspx


//-----------------------------------------------------------------------------
/*Deafult constructor.
 */
CWmi::CWmi()
{
TRACE0("CWmi::CWmi()\n");
}

//-----------------------------------------------------------------------------
/*
 */
CWmi::~CWmi()
{
TRACE0("CWmi::~CWmi()\n");
Disconnect();
}

//-----------------------------------------------------------------------------
/*
 */
bool CWmi::Init(LPCTSTR lpstrDevice //[in] = NULL
                   )
{
#ifdef _UNICODE
  TRACE1(_T("CWmi::Connect(%ws)\n"), lpstrDevice);
#else
  TRACE1(_T("CWmi::Connect(%s)\n", lpstrDevice);
#endif
HRESULT hInitializeRes = S_FALSE;
try
  {
  //1. Initialize COM parameters with a call to CoInitializeEx.
  /*Initialize the thread for multi-threaded object concurrency.
    Note: OLE clients require apartment-threading (COINIT_APARTMENTTHREADED).
    Minimum supported client is Windows 2000 Professional.
   */
  hInitializeRes = CoInitializeEx(NULL, 
                                 COINIT_MULTITHREADED
                                 );
  if(hInitializeRes != RPC_E_CHANGED_MODE)
    {
    //2. Initialize COM process security by calling CoInitializeSecurity.
    //   Windows 2000:  Specify the default authentication credentials for
    //   a user by using a SOLE_AUTHENTICATION_LIST structure in the pAuthList
    //   parameter of CoInitializeSecurity.

    #ifdef AUTHN_LEVEL_DEFAULT
      //the default authentication level for the process
      const DWORD dwAuthnLevel = RPC_C_AUTHN_LEVEL_DEFAULT;
      //additional capabilities of the client or server
      const DWORD dwCapabilities = EOAC_NONE;
    #endif
    #ifdef AUTHN_LEVEL_NONE
      //the authentication level for the process to be used for remote asynchronous
      //WMI calls to non-Kerberos targets, where the "Local System" account has no 
      //network identity. This will make application less secure, so it is recommeded
      //replacing asynchronous WMI calls with semi-synchronous.
      const DWORD dwAuthnLevel = RPC_C_AUTHN_LEVEL_NONE;
      //additional capabilities of the client or server have to be EOAC_NONE if
      //authentication level is set to RPC_C_AUTHN_LEVEL_NONE
      const DWORD dwCapabilities = EOAC_NONE;
    #endif

    //the credentials authentication and encryption
    const DWORD dwAuthnLevel = RPC_C_AUTHN_LEVEL_PKT_PRIVACY;
    //additional capabilities of the client or server
    const DWORD dwCapabilities = EOAC_SECURE_REFS;
    HRESULT hResult;
    hResult = CoInitializeSecurity(NULL,                         //Security descriptor
                                  -1,                            //COM authentication
                                  NULL,                          //Authentication services
                                  NULL,                          //Reserved
                                  dwAuthnLevel,                  //Default authentication 
                                  RPC_C_IMP_LEVEL_IMPERSONATE,   //Default Impersonation  
                                  NULL,                          //Authentication info
                                  dwCapabilities,                //Additional capabilities 
                                  NULL);                         //Reserved
    if(SUCCEEDED(hResult))
      {
      //3. Obtain the initial locator to WMI by calling CoCreateInstance.

      //4. Obtain a pointer to IWbemServices for the root\cimv2 namespace on the local
      //   computer by calling IWbemLocator::ConnectServer.

      //5. Set IWbemServices proxy security so the WMI service can impersonate the client
      //   by calling CoSetProxyBlanket.

      return true;
      }
    else
      {
      TRACE(_T( "  CoInitializeSecurity() failed.\n"));
      }
    }

  }
catch (...)
  {
  TRACE(_T( "  WMI connection failed.\n"));
  }

if(hInitializeRes != RPC_E_CHANGED_MODE) //Failed after step 1.
  {
  /*To close the COM library gracefully on a thread, each successful call to CoInitialize 
    or CoInitializeEx, including any call that returns S_FALSE, must be balanced by 
    a corresponding call to CoUninitialize.
   */
  CoUninitialize();
  }
return false;
}

//-----------------------------------------------------------------------------
/*
 */
bool CWmi::Disconnect()
{
TRACE(_T("CWmi::Disconnect()\n"));
if (IsConnected())
  {
  }
//m_bConnected = false;
return true;
}

//-----------------------------------------------------------------------------
/*
 */
bool CWmi::IsConnected()
{
return false;//m_bConnected;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: KWmi.cpp,v $
 * Revision 1.1  2010/01/26 22:47:05  ddarko
 * Initialization of WMI
 *
 *****************************************************************************/
