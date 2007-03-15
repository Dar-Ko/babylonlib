/*$Workfile: TestComAtlNet.cpp$: implementation file
  $Revision: 5$ $Date: 2007-03-15 16:04:42$
  $Author: Darko Kolakovic$

  Implementation file
  Copyright: CommonSoft Inc.
  2006-08-25 Darko Kolakovic
 */

// Group=Examples Windows

#include "stdafx.h"
#include "resource.h"
#include "TestComAtlNet.h" //Note: created by MIDL compiler

///////////////////////////////////////////////////////////////////////////////
/*The class is the main the module for an executable application and contains 
  code that supports creating an .exe, processing the command line, registering 
  class objects, running the message loop, and cleaning up on exit.

  The base class is designed to improve performance when COM objects in 
  the EXE server are continually created and destroyed. 
  After the last COM object is released, the EXE waits for a duration specified 
  by the CAtlExeModuleT::m_dwTimeOut data member. If there is no activity during 
  this period (that is, no COM objects are created), the shutdown process is 
  initiated.
 */
class CTestComAtlNetModule : public CAtlServiceModuleT< CTestComAtlNetModule, IDS_SERVICENAME >
{
public :
  DECLARE_LIBID(LIBID_TestComAtlNetLib)
  DECLARE_REGISTRY_APPID_RESOURCEID(IDR_TESTCOMATLNET, "{931BDB1A-A7AB-41ED-A8F6-15E1C11D65FE}")
  HRESULT InitializeSecurity();
};

//-----------------------------------------------------------------------------
/*Provides the default security settings for the service.

  Returns: S_OK on success, or an error HRESULT on failure.
 */
HRESULT CTestComAtlNetModule::InitializeSecurity() throw()
{
m_bDelayShutdown = false; //flag indicating that there should be a delay 
                          //shutting down the module.

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

CTestComAtlNetModule TestAtlModule; //the main the module for an executable application


//-----------------------------------------------------------------------------
/*The initial entry point for a Windows-based application.

  Returns: if the function succeeds, terminating when it receives a WM_QUIT message, 
  it should return the exit value contained in that message's wParam parameter. 
  If the function terminates before entering the message loop, it should return zero. 
 */
extern "C" int WINAPI _tWinMain(HINSTANCE ,//hInstance [in] Handle to the current
                                 // instance of the application.
                                HINSTANCE ,//hPrevInstance [in] Handle to 
                                //the previous instance of the application. This 
                                //parameter is always NULL.
                                LPTSTR    ,//lpCmdLine [in] Pointer to a null-terminated
                                // string specifying the command line for the application, 
                                //excluding the program name. 
                                int nShowCmd //[in] Specifies how the window is 
                                //to be shown. 
                               )
{
return TestAtlModule.WinMain(nShowCmd);
}

///////////////////////////////////////////////////////////////////////////////
