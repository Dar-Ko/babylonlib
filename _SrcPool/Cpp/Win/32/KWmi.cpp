/*$RCSfile: KWmi.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2010/01/27 22:41:27 $
  $Author: ddarko $

  Microsoft Windows Management Instrumentation (WMI) client.
  Copyright: Darko Kolakovic
  Darko Kolakovic 2010-01-15
 */
#define _WIN32_DCOM //use DCOM to access COM objects
#include "stdafx.h"
//#include <comdef.h> //Native C++ compiler COM support
//#include "wbemcli.h"        //WMI interface declarations (wbemcli.idl)
#include "KWmi.h" //CWmi class
#pragma comment(lib, "wbemuuid.lib")

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
//
// Web-Based Enterprise Management (WBEM) is a set of systems management
// technologies developed to unify the management of distributed computing
// environments. WBEM is based on Internet standards and DMTF open standards: CIM
// infrastructure and schema, CIM-XML, CIM operations over HTTP, WS-Management.

//-----------------------------------------------------------------------------
/*Deafult constructor.
 */
CWmi::CWmi() :
  m_hInitializeRes(RPC_E_CHANGED_MODE),
  m_pIWbemServices(NULL)
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
if(IsCoInitialized())
  {
  /*To close the COM library gracefully on a thread, each successful call to
    CoInitialize or CoInitializeEx, including any call that returns S_FALSE,
    must be balanced by a corresponding call to CoUninitialize, as the last
    step in the process.
   */
  CoUninitialize();
  }
}

//-----------------------------------------------------------------------------
/*Initializes necessary resources required to query local or remote WMI objects.

  Returns: true if successful, otherwise returns false.
 */
bool CWmi::Init(LPCTSTR lpstrDeviceUri //[in] = NULL URI of the correct WMI namespace.
                //If it is NULL the default local namespace will be used.
               )
{
#ifdef _UNICODE
  TRACE1(_T("CWmi::Init(%ws)\n"), lpstrDeviceUri);
#else
  TRACE1(_T("CWmi::Init(%s)\n", lpstrDeviceUri);
#endif

try
  {
  //1. Initialize COM parameters with a call to CoInitializeEx.
  /*Initialize the thread for multi-threaded object concurrency.
    Note: OLE clients require apartment-threading (COINIT_APARTMENTTHREADED).
    Minimum supported client is Windows 2000 Professional.
   */
  m_hInitializeRes = CoInitializeEx(NULL,
                                 COINIT_MULTITHREADED
                                 );
  if(IsCoInitialized())
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
    #elif defined (AUTHN_LEVEL_NONE)
      //the authentication level for the process to be used for remote asynchronous
      //WMI calls to non-Kerberos targets, where the "Local System" account has no
      //network identity. This will make application less secure, so it is recommeded
      //replacing asynchronous WMI calls with semi-synchronous.
      const DWORD dwAuthnLevel = RPC_C_AUTHN_LEVEL_NONE;
      //additional capabilities of the client or server have to be EOAC_NONE if
      //authentication level is set to RPC_C_AUTHN_LEVEL_NONE
      const DWORD dwCapabilities = EOAC_NONE;
    #else
      //the credentials authentication and encryption
      const DWORD dwAuthnLevel = RPC_C_AUTHN_LEVEL_PKT_PRIVACY;
      //additional capabilities of the client or server
      const DWORD dwCapabilities = EOAC_SECURE_REFS;
    #endif
    HRESULT hResult;
    hResult = CoInitializeSecurity(NULL,              //Security descriptor
                          -1,                         //COM authentication
                          NULL,                       //Authentication services
                          NULL,                       //Reserved
                          dwAuthnLevel,               //Default authentication
                          RPC_C_IMP_LEVEL_IMPERSONATE,//Default Impersonation
                          NULL,                       //Authentication info
                          dwCapabilities,             //Additional capabilities
                          NULL);                      //Reserved
    if(SUCCEEDED(hResult))
      {
      //3. Obtain the initial locator to WMI by calling CoCreateInstance.
      IWbemLocator* pIWbemLocator = NULL; //interface to the WbemLocator service
      hResult = CoCreateInstance(CLSID_WbemLocator,      //locator class ID
                                 NULL,                   //not aggregate object
                                 CLSCTX_INPROC_SERVER,   //indicates a dll running
                                                         //in same process as caller
                                 IID_IWbemLocator,       //WBEM interface reference
                                 (LPVOID *) &pIWbemLocator //instance of
                                                         //the the WbemLocator
                                 );
      if(SUCCEEDED(hResult))
        {
        //4. Obtain a pointer to IWbemServices for the root\cimv2 namespace on the local
        //   or remote computer by calling IWbemLocator::ConnectServer.
        CComBSTR bstrNamespace = (lpstrDeviceUri != NULL) ? 
            CComBSTR(lpstrDeviceUri):
            CComBSTR(NS_WMICIM);
        if (m_pIWbemServices != NULL)
            m_pIWbemServices->Release();

        hResult = pIWbemLocator->ConnectServer(bstrNamespace, //URI of WMI
                                      NULL,                         //current user name
                                      NULL,                         //current user password
                                      0,                            //Locale, current
                                      NULL,                         //Security flags
                                      0,                            //Authority
                                      0,                            //Context object
                                      &m_pIWbemServices);           //IWbemServices proxy
        pIWbemLocator->Release();
        //5. Set IWbemServices proxy security so the WMI service can impersonate the client
        //   by calling CoSetProxyBlanket.

        return true;
        }
      else
        {
        TRACE1(_T( "  CoCreateInstance() failed (0x%08X).\n"), hResult);
        }
      }
    else
      {
      TRACE1(_T( "  CoInitializeSecurity() failed (0x%08X).\n"), hResult);
      }
    }

  }
catch (...)
  {
  TRACE(_T( "  WMI connection failed.\n"));
  }

return false;
}

//-----------------------------------------------------------------------------
/*
 */
bool CWmi::Disconnect()
{
TRACE(_T("CWmi::Disconnect()\n"));
try
  {
  if (IsConnected())
    {
    }

  //m_bConnected = false;
  if (m_pIWbemServices != NULL)
    {
    #ifdef _DEBUG
      unsigned long nRef = m_pIWbemServices->Release();
      if (nRef == 0)
        m_pIWbemServices = NULL;
      else
        {
        TRACE1(_T("  IWbemServices reference counter = %d.\n"), nRef);
        }
    #else
      if (m_pIWbemServices->Release() == 0)
        m_pIWbemServices = NULL;
    #endif
    }
  return true;
  }
catch(...)
  {
  TRACE(_T("  Failed to release resources!\n"));
  }
return false;
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
 * Revision 1.2  2010/01/27 22:41:27  ddarko
 * *** empty log message ***
 *
 * Revision 1.1  2010/01/26 22:47:05  ddarko
 * Initialization of WMI
 *
 *****************************************************************************/
