/*$RCSfile: KWmi.cpp,v $: implementation file
  $Revision: 1.5 $ $Date: 2010/02/02 19:19:29 $
  $Author: ddarko $

  Microsoft Windows Management Instrumentation (WMI) client.
  Copyright: Darko Kolakovic
  Darko Kolakovic 2010-01-15
 */
#define _WIN32_DCOM //use DCOM to access COM objects
#include "stdafx.h"
#include <comdef.h> //Native C++ compiler COM support, _bstr_t
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
bool CWmi::Init(LPCTSTR szDeviceUri, //[in] = NULL URI of the correct WMI namespace.
                //If it is NULL the default local namespace will be used.
                LPCTSTR szUserName, //[in] = NULL user name and cannot be an empty string. 
                LPCTSTR szPassword,  //[in] = NULL user password
                LPCTSTR szDomain //[in] = NULL name of the domain of the user to
                //authenticate and can have the following values:
                //    - NULL   NTLM authentication is used and the NTLM domain of 
                //             the current user is used. If the domain is specified
                //             in szUserName, which is the recommended location, then 
                //             it must not be specified here. 
                //             Specifying the domain in both parameters results in
                //             an invalid parameter error.
                //    - Kerberos:<principal name> Kerberos authentication is used and
                //      this parameter should contain a Kerberos (NETBIOS) principal name.
                //    - NTLMDOMAIN:<domain name> NT LAN Manager authentication is used
                //      and this parameter should contain an NTLM (NETBIOS) domain name.
               )
{
#ifdef _UNICODE
  TRACE1(_T("CWmi::Init(%ws)\n"), szDeviceUri);
#else
  TRACE1(_T("CWmi::Init(%s)\n", szDeviceUri);
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
        //4. Obtain a pointer to IWbemServices for the root\cimv2 namespace on
        //   the local or remote computer by calling IWbemLocator::ConnectServer.
        CComBSTR bstrNamespace((szDeviceUri != NULL) ? szDeviceUri : NS_WMICIM);
        CComBSTR bstrUserName(szUserName);
        CComBSTR bstrPassword(szPassword);

        if (m_pIWbemServices != NULL)
            m_pIWbemServices->Release();

        hResult = pIWbemLocator->ConnectServer(bstrNamespace, //URI of WMI
                                      bstrUserName, //current user name
                                      bstrPassword,  //current user password
                                      0,                      //Locale, current _bstr_t(L"MS_409"),
                                      NULL,                   //Security flags
 /*_bstr_t(L"ntlmdomain:DomainOrMachine"),*/ NULL,                      //Authority
                                      0,                      //Context object
                                      &m_pIWbemServices);     //IWbemServices proxy
        pIWbemLocator->Release();
        if(SUCCEEDED(hResult))
          {
          //5. Set IWbemServices proxy security so the WMI service can impersonate
          //    the client by calling CoSetProxyBlanket.
          /*Note: to avoid "0x80070005 - Access Denied" error when executing 
            the ExecQuery() when executing, for example, the ExecQuery(),
            authenticate each WMI interface call properly.
            In general, COM security does not allow one process to access another
            process if you do not set the proper security properties.
           */
          #if defined (AUTHN_LEVEL_NONE) //TODO:
            COAUTHIDENTITY cID;
            cID.User           = (USHORT*)&szUserName;
            cID.UserLength     = lstrlen(pszName); //bstrUsername.length();
            cID.Password       = (USHORT*)&szPassword;
            cID.PasswordLength = lstrlen(pszPwd); //bstrPassword.length();
            cID.Domain         = (USHORT*)&szDomain;
            cID.DomainLength   = lstrlen(pszDom); // bstrDomain.length();
            cID.Flags          = SEC_WINNT_AUTH_IDENTITY_UNICODE;
            RPC_AUTH_IDENTITY_HANDLE pAuthInfo = &cID;
          #endif
          #ifdef AUTHN_LEVEL_DEFAULT
            RPC_AUTH_IDENTITY_HANDLE pAuthInfo = NULL;
          #endif
#ifdef TODO_REMOTEPROXY //TODO:
          //Set security levels on a WMI connection
          hResult = CoSetProxyBlanket(m_pIWbemServices,//Indicates the proxy to set
                       RPC_C_AUTHN_WINNT,           //use NTLMSSP authentication
                                                    //service
                       RPC_C_AUTHZ_NONE,            //authorization service
                       NULL,                        //server principal name
                       RPC_C_AUTHN_LEVEL_CALL,      //authentication level
                       RPC_C_IMP_LEVEL_IMPERSONATE, //impersonation level 
                       pAuthInfo,                   //client identity; not used
                                              //for calls on the same computer
                       EOAC_NONE                    //capabilities of this proxy
                       );
#endif
          if(SUCCEEDED(hResult))
            {
            return true;
            }
          }
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
return true; //false;//m_bConnected;
}

//-----------------------------------------------------------------------------
/*
 */
bool CWmi::Query(LPCTSTR szWqlQuery,  //[in] text of the WQL query. This parameter
                  //cannot be NULL.
                const long nTimeOut //[in] = WBEM_INFINITE the maximum response 
                                    //waiting period [ms]
                 )
{
#ifdef _UNICODE
  TRACE1(_T("CWmi::Query(%ws)\n"), szWqlQuery);
#else
  TRACE1(_T("CWmi::Query(%s)\n", szWqlQuery);
#endif

if ((szWqlQuery != NULL) && (szWqlQuery[0] != _T('\0')))
  {
  if (IsConnected())
    {
    //std::map< std::string, uint64 >& wmiMap;
    CComBSTR bstrQuery(szWqlQuery);
    IEnumWbemClassObject* pEnumerator = NULL; //interface is used to enumerate 
                                              //Common Information Model (CIM)
                                              //objects.
    HRESULT hResult;
    hResult = m_pIWbemServices->ExecQuery(bstr_t("WQL"), //required query language
                              bstrQuery,                 //query text
                              WBEM_FLAG_FORWARD_ONLY | 
                              WBEM_FLAG_RETURN_IMMEDIATELY, 
                              NULL, //no context
                              &pEnumerator //output enumerator
                              );
    if (SUCCEEDED(hResult))
      {
      if(pEnumerator != NULL)
        {
        IWbemClassObject* pCimObject = NULL;
        ULONG             nCount = 0;
        do
          {
          hResult = pEnumerator->Next(nTimeOut, //allowed time period for 
                                              //response [ms]
                                    1, //number of requested objects
                                    &pCimObject, //storage of pointers to 
                                                 //requested CIM objects
                                    &nCount //number of objects returned
                                    );
          if (FAILED(hResult))
            {
              TRACE1(_T("  IEnumWbemClassObject::Next failed (0x%0.8X)!\n"), hResult);;
            break;
            }
          if (hResult == WBEM_S_FALSE)
            {
            //WBEM_S_FALSE is returned when the number of objects returned was
            //less than the number requested, indicating that all elements are
            //obtained.
            ASSERT(nCount == 0);
            break;
            }

          VARIANT vtProp;
          //Get the value of the Name property
          HRESULT hr = pCimObject->Get(L"Name", 0, &vtProp, 0, 0);
          TRACE1(_T("  Name: \"%ws\".\n"), vtProp.bstrVal);
          VariantClear(&vtProp);

          } while(hResult != WBEM_S_FALSE);

        pEnumerator->Release();
        if (hResult == WBEM_S_FALSE)
          return true;
        else
          {
          TRACE1(_T("  IEnumWbemClassObject::Next failed (0x%0.8X)!\n"), hResult);
          }
        }
      }
    else
      {
      TRACE1(_T("  ExecQuery failed (0x%0.8X)!\n"), hResult);
      }
    }
  else
    {
    TRACE(_T("  Query failed because WMI is not initialized!\n"));
    }
  }
return false;
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: KWmi.cpp,v $
 * Revision 1.5  2010/02/02 19:19:29  ddarko
 * WQL constats
 *
 * Revision 1.4  2010/02/01 22:28:07  ddarko
 * ExecQuery
 *
 * Revision 1.3  2010/01/29 22:47:47  ddarko
 * Query (simple)
 *
 * Revision 1.2  2010/01/27 22:41:27  ddarko
 * *** empty log message ***
 *
 * Revision 1.1  2010/01/26 22:47:05  ddarko
 * Initialization of WMI
 *
 *****************************************************************************/
