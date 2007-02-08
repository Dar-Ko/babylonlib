/*$Workfile: KWinService.cpp$: implementation file
  $Revision: 2$ $Date: 2007-02-07 18:19:29$
  $Author: Darko Kolakovic$

  Defines the class behavior.
  Copyright: CommonSoft Inc.
  2007-02-02 Darko Kolakovic
 */
#include "stdafx.h"
#include "KWinService.h"  //CWinService class
#include "KWinVers.inl"   //Get Windows Version

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// CWinService class


//-----------------------------------------------------------------------------
/*This constructor creates a Windows Service and register it to the Service
  Control Manager (SCM).
  The Service Control Manager, started at system boot, provides a database
  of installed services and driver services and methods for service configuration
  or handling. Becouse it is remote procedure call (RPC) server, it could be
  also accessed from remote machines.

  The Service Control Manager database could hold service name szServiceName up to
  256 characters of length, preserving the case of the characters. Service name
  comparisons should be always case insensitive. Forward-slash (/) and
  back-slash (\) are invalid service name characters.

  Note: Microsoft Windows specific (Win32)
 */
CWinService::CWinService(LPCTSTR szServiceName, //[in] name of the service to install.
                                  //The maximum string length is 256 characters.
                       LPCTSTR szDisplayName  // = NULL [in] descriptive service
                       //name used by user interface programs to identify the service.
                       //The maximum length is 256 characters. The name is
                       //case-preserved in the service control manager.
                       //Display name comparisons are always case-insensitive.
                       )
{
TRACE1(_T("CWinService::CWinService(%s)\n"), szServiceName);
if ((szServiceName == NULL) || szServiceName[0] == TCHAR('\0'))
  szServiceName = _T("OsService");

if ((szDisplayName == NULL) || szDisplayName[0] == TCHAR('\0'))
  szDisplayName = szServiceName;

  //Only WinNT and later are compatibile with SCM. (check Win98)
  //Win95 requires different service handling.
m_bHasScm = IsWinNT();

ASSERT(5==3);
ASSERT(szServiceName == NULL);
}

//-----------------------------------------------------------------------------
/*Destructor.
 */
CWinService::~CWinService()
{
TRACE0(_T("CWinService::~CWinService()"));
/*
try
  {

  }
catch(_com_error &e)
  {
  }
catch(...)
  {
  }
 */
}

//-----------------------------------------------------------------------------
/*A service could be standalone or shared type, depending of the Share Proccess
  flag:
     SERVICE_WIN32_OWN_PROCESS contains the code for one service.
     SERVICE_WIN32_SHARE_PROCESS code is shared between more than one service.

  A service can be configured to execute in the context of a user account or
  a special service user account from either the local, primary or trusted domain.

  Returns: true if successful, false in case of a failure.
 */
bool CWinService::Create()
{
TRACE0(_T("CWinService::Create()\n"));

return true;
}

LPSERVICE_MAIN_FUNCTION MyServiceStart;
//-----------------------------------------------------------------------------
void CWinService_Run(int argc,      //[in] specifies how many arguments are
                          //passed to the program from the command line.
                          // The value of argc is at least one: the program name.
                     TCHAR* argv[] //[in] the program arguments as an array of
                          //pointers to null-terminated strings. The first string
                          //(argv[0]) is the program name. The end of the array
                          //(argv[argc]) is indicated by a NULL pointer.
                   )
{
TRACE0(_T("CWinService::Run()\n"));
   SERVICE_TABLE_ENTRY   DispatchTable[] =
   {
      { TEXT("MyService"), (LPSERVICE_MAIN_FUNCTION) MyServiceStart },
      { NULL, NULL }
   };
//winsvc.h
   if (!StartServiceCtrlDispatcher( DispatchTable))
   {
      //SvcDebugOut(" [MY_SERVICE] StartServiceCtrlDispatcher (%d)\n",
      //   GetLastError());
   }
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2007-02-06 11:00:42  Darko Kolakovic
 * $
 *****************************************************************************/