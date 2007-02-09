/*$Workfile: KWinService.cpp$: implementation file
  $Revision: 3$ $Date: 2007-02-09 18:47:30$
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

  void WINAPI ServiceStart(DWORD argc, LPTSTR* argv);

//-----------------------------------------------------------------------------
/*This constructor creates a Windows Service and register it to the Service
  Control Manager (SCM).

  {html:
    <img src="../Images/diagWinService.gif" title="Service Components"
      alt="WinNT service components" border="0"> <br />
  }

  When SCM method StartServiceCtrlDispatcher successfully set service or
  services entry points, the calling thread does not return until all running
  services in the process have entered the SERVICE_STOPPED state.
  The SCM sends control requests to this thread through a named pipe.

  Note: Microsoft Windows specific (Win32)
 */
CWinService::CWinService() :
  m_pfServiceMain(ServiceStart)
{
TRACE(_T("CWinService::CWinService()\n"));

/*Service type (not including device drivers) could be
   SERVICE_WIN32_OWN_PROCESS   service runs in its own process.
   SERVICE_WIN32_SHARE_PROCESS service shares a process with other services.
   SERVICE_INTERACTIVE_PROCESS service can interact with the desktop if it is
                               running on the context of the LocalSystem account.
   Note: Windows Vista does not support displaying a user interface.

  Service state could be
    SERVICE_CONTINUE_PENDING  service continue is pending.
    SERVICE_PAUSE_PENDING     service pause is pending.
    SERVICE_PAUSED            service is paused.
    SERVICE_RUNNING           service is running.
    SERVICE_START_PENDING     service is starting.
    SERVICE_STOP_PENDING      service is stopping.
    SERVICE_STOPPED           service is not running.

  Error code the service uses to report an error that occurs when it is starting
  or stopping. To return an error code specific to the service, the service
  must set this value to ERROR_SERVICE_SPECIFIC_ERROR to indicate that the
  dwServiceSpecificExitCode member contains the error code.
  The service should set this value to NO_ERROR when it is running and
  on normal termination.
 */

//Default values for SERVICE_STATUS structure.
m_sStatus.dwServiceType        = SERVICE_WIN32_OWN_PROCESS; //type of service.
m_sStatus.dwCurrentState       = SERVICE_STOPPED; //current state of the service
m_sStatus.dwControlsAccepted   = 0; //control codes the service accepts
                                    //and processes in its handler function
m_sStatus.dwWin32ExitCode      = NO_ERROR; //Error code when service is running.
m_sStatus.dwServiceSpecificExitCode = 0;
m_sStatus.dwCheckPoint         = 0; //progress increments during a lengthy operation
m_sStatus.dwWaitHint           = 3000; //[ms] estimated time for a lengthy operation

  //Only WinNT and later are compatibile with SCM. (check Win98)
  //Win95 requires different service handling.
m_bHasScm = IsWinNT();
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
/*A service could be standalone or shared type, depending of the Share Process
  flag:
     SERVICE_WIN32_OWN_PROCESS contains the code for one service.
     SERVICE_WIN32_SHARE_PROCESS code is shared between more than one service.

  A service can be configured to execute in the context of a user account or
  a special service user account from either the local, primary or trusted domain.

  The Service Control Manager database could hold service name szServiceName up to
  256 characters of length, preserving the case of the characters. Service name
  comparisons should be always case insensitive. Forward-slash (/) and
  back-slash (\) are invalid service name characters.

  The main thread of a service process should make this call as soon as possible
  after it starts up. Any the initialization before calling StartServiceCtrlDispatcher,
  should take less than 30s, otherwise use another thread to do the
  common initialization, allowing main thread to call StartServiceCtrlDispatcher.

  Returns: true if successful, false in case of a failure.
 */
bool CWinService::Create(LPTSTR szServiceName, //[in] name of the service to
                         //install. The maximum string length is 256 characters.
                         LPCTSTR szDisplayName // = NULL [in] descriptive service
                         //name used by user interface programs to identify the
                         //service. The maximum length is 256 characters. The
                         //name is case-preserved in the service control manager.
                         //Display name comparisons are always case-insensitive.
                        )
{
TRACE1(_T("CWinService::Create(%s)\n"), szServiceName);
if ((szServiceName == NULL) || szServiceName[0] == TCHAR('\0'))
  szServiceName = _T("KOsService");

if ((szDisplayName == NULL) || szDisplayName[0] == TCHAR('\0'))
  szDisplayName = szServiceName;

/*Array of SERVICE_TABLE_ENTRY structures containing one entry for each service
  that can execute in the calling process.
  The members of the last entry in the table must have NULL values to designate
  the end of the table.
  The SERVICE_TABLE_ENTRY structure is used by the StartServiceCtrlDispatcher()
  function to specify the ServiceMain function for a service that can run in
  the calling process.
 */
SERVICE_TABLE_ENTRY arrDispatchTable[] =
  {
  //1st and only service, suitable for SERVICE_WIN32_OWN_PROCESS.
  //More then one service sharing some resources requires
  //SERVICE_WIN32_SHARE_PROCESS service type
    {
    //specifies the name of a service to be run; ignored if the service
    //is of SERVICE_WIN32_OWN_PROCESS service type.
    szServiceName,
    //pointer to a callback function used as service starting (entry) point
    m_pfServiceMain
    },
  {NULL, NULL} //End of List tag
 };

// connect to  the service control manager
if(StartServiceCtrlDispatcher(arrDispatchTable) == 0)
  {
  TRACE2(_T("  Service '%s'\n  returned (%d):"),
         szServiceName,
         GetLastError());
  //TODO: LogEvent(GetLastError())
  switch(GetLastError())
    {
    case ERROR_FAILED_SERVICE_CONTROLLER_CONNECT:
      //Typically, this error indicates that the program is being run as
      //a console application rather than as a service.
      TRACE(_T("  ERROR_FAILED_SERVICE_CONTROLLER_CONNECT\n"));
      return true;
      break;
    case ERROR_INVALID_DATA:
    //The specified dispatch table contains entries that are not in
    //the proper format.
      TRACE(_T("  ERROR_INVALID_DATA\n"));
      return false;
      break;
    case ERROR_SERVICE_ALREADY_RUNNING:
      //The process called StartServiceCtrlDispatcher more than once (WinXP)
      TRACE(_T("  ERROR_SERVICE_ALREADY_RUNNING\n"));
      return false;
      break;
    default:
      //Unspecified error
      TRACE(_T("  USPECIFIED ERROR\n"));
      return false;
    }
  }

return true;
}

//-----------------------------------------------------------------------------
/*
 */
void WINAPI ServiceStart(DWORD argc,      //[in] specifies how many arguments are
                          //passed to the service.
                          // The value of argc is at least one: the service name.
                     LPTSTR* argv //[in] arguments passed to the service by the
                          //process that called the StartService() to start
                          //the service. The first string (argv[0]) is the
                          //service name. The end of the array
                          //(argv[argc]) is indicated by a NULL pointer.
                   )
{
TRACE2(_T("CWinService::Start(argc = %d)\n"), argc);
SERVICE_STATUS          m_sServiceStatus;
SERVICE_STATUS_HANDLE   MyServiceStatusHandle;
DWORD MyServiceInitialization (DWORD, LPTSTR*, DWORD*);


    DWORD status;
    DWORD specificError;

    m_sServiceStatus.dwServiceType        = SERVICE_WIN32;
    m_sServiceStatus.dwCurrentState       = SERVICE_START_PENDING;
    m_sServiceStatus.dwControlsAccepted   = 0;
    m_sServiceStatus.dwWin32ExitCode      = 0;
    m_sServiceStatus.dwServiceSpecificExitCode = 0;
    m_sServiceStatus.dwCheckPoint         = 0;
    m_sServiceStatus.dwWaitHint           = 10000;

    MyServiceStatusHandle = RegisterServiceCtrlHandler(
        _T("MyService"),
        NULL);//MyServiceCtrlHandler);

    if (MyServiceStatusHandle == (SERVICE_STATUS_HANDLE)0)
    {
        TRACE1(_T(" [MY_SERVICE] RegisterServiceCtrlHandler \
            failed %d\n"), GetLastError());
        return;
    }

    SetServiceStatus(MyServiceStatusHandle, &m_sServiceStatus);

    // Initialization code goes here.
    status = MyServiceInitialization(argc,argv, &specificError);

    // Handle error condition
    if (status != NO_ERROR)
    {
        m_sServiceStatus.dwCurrentState       = SERVICE_STOPPED;
        m_sServiceStatus.dwCheckPoint         = 0;
        m_sServiceStatus.dwWaitHint           = 0;
        m_sServiceStatus.dwWin32ExitCode      = status;
        m_sServiceStatus.dwServiceSpecificExitCode = specificError;

        SetServiceStatus (MyServiceStatusHandle, &m_sServiceStatus);
        return;
    }

    // Initialization complete - report running status.
    m_sServiceStatus.dwCurrentState       = SERVICE_RUNNING;
    m_sServiceStatus.dwCheckPoint         = 0;
    m_sServiceStatus.dwWaitHint           = 0;
    m_sServiceStatus.dwControlsAccepted   = SERVICE_ACCEPT_STOP |
        SERVICE_ACCEPT_PAUSE_CONTINUE;

    if (!SetServiceStatus (MyServiceStatusHandle, &m_sServiceStatus))
    {
        status = GetLastError();
        TRACE1(_T(" [MY_SERVICE] SetServiceStatus error \
            %ld\n"),status);
    }

    // This is where the service does its work.
    TRACE1(_T(" [MY_SERVICE] Returning the Main Thread \n"),0);

    return;
}

// Stub initialization function.
DWORD MyServiceInitialization(DWORD argc, LPTSTR *argv, DWORD *specificError)
{
    argv;
    argc;
    specificError;
    return(0);
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2007-02-06 11:00:42  Darko Kolakovic
 * $
 *****************************************************************************/