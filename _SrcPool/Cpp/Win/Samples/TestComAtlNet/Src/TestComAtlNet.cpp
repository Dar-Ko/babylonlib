/*$Workfile: TestComAtlNet.cpp$: implementation file
  $Revision: 3$ $Date: 2007-02-16 14:22:32$
  $Author: Darko Kolakovic$

  Implementation file
  Copyright: CommonSoft Inc.
  2006-08-25 Darko Kolakovic
 */

#include "stdafx.h"
#include "resource.h"
#include "TestComAtlNet.h" //Note: created by MIDL compiler

class CTestComAtlNetModule : public CAtlServiceModuleT< CTestComAtlNetModule, IDS_SERVICENAME >
{
public :
  DECLARE_LIBID(LIBID_TestComAtlNetLib)
  DECLARE_REGISTRY_APPID_RESOURCEID(IDR_TESTCOMATLNET, "{931BDB1A-A7AB-41ED-A8F6-15E1C11D65FE}")
  HRESULT InitializeSecurity();
};

//-----------------------------------------------------------------------------
/*
 */
HRESULT CTestComAtlNetModule::InitializeSecurity() throw()
{
//Allow service access to everyone
HRESULT hResult =
  CoInitializeSecurity(NULL, //points to the access permissions that
                             //a server will use to receive calls
                      -1,   //count of entries in asAuthSvc
                      NULL, //array of authentication services
                      NULL, //reserved for future use
                      RPC_C_AUTHN_LEVEL_NONE, //default authentication level
                      RPC_C_IMP_LEVEL_IMPERSONATE, //default impersonation
                                                   //level for proxies
                      NULL, //information for each authentication service
                            //that a client can use to call a server
                      EOAC_NONE, //capabilities of the client or server
                      NULL //reserved for future use
                      );

return hResult;
}

CTestComAtlNetModule _AtlModule;


//-----------------------------------------------------------------------------
/*
 */
extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/,
                                HINSTANCE /*hPrevInstance*/,
                                LPTSTR /*lpCmdLine*/,
                                int nShowCmd
                               )
{
return _AtlModule.WinMain(nShowCmd);
}
