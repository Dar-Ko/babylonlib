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
 
 //----------------------------------------------------------------------------
 BOOL WaitForServiceToReachState(SC_HANDLE hService, DWORD dwDesiredState,
                                 SERVICE_STATUS* pss, DWORD dwMilliseconds) {
 
    DWORD dwLastState, dwLastCheckPoint;
    BOOL  fFirstTime = TRUE; // Don't compare state & checkpoint the first time through
    BOOL  fServiceOk = TRUE;
    DWORD dwTimeout = GetTickCount() + dwMilliseconds;
 
    // Loop until the service reaches the desired state,
    // an error occurs, or we timeout
    while  (TRUE) {
       // Get current state of service
       fServiceOk = ::QueryServiceStatus(hService, pss);
 
       // If we can't query the service, we're done
       if (!fServiceOk) break;
 
       // If the service reaches the desired state, we're done
       if (pss->dwCurrentState == dwDesiredState) break;
 
       // If we timed-out, we're done
       if ((dwMilliseconds != INFINITE) && (dwTimeout > GetTickCount())) {
          SetLastError(ERROR_TIMEOUT); 
          break;
       }
 
       // If this is our first time, save the service's state & checkpoint
       if (fFirstTime) {
          dwLastState = pss->dwCurrentState;
          dwLastCheckPoint = pss->dwCheckPoint;
          fFirstTime = FALSE;
       } else {
          // If not first time & state has changed, save state & checkpoint
          if (dwLastState != pss->dwCurrentState) {
             dwLastState = pss->dwCurrentState;
             dwLastCheckPoint = pss->dwCheckPoint;
          } else {
             // State hasn't change, check that checkpoint is increasing
             if (pss->dwCheckPoint > dwLastCheckPoint) {
                // Checkpoint has increased, save checkpoint
                dwLastCheckPoint = pss->dwCheckPoint;
             } else {
                // Checkpoint hasn't increased, service failed, we're done!
                fServiceOk = FALSE; 
                break;
             }
          }
       }
       // We're not done, wait the specified period of time
       Sleep(pss->dwWaitHint);
    }
 
    // Note: The last SERVICE_STATUS is returned to the caller so
    // that the caller can check the service state and error codes.
    return(fServiceOk);
 }

//---------------------------------------------------------------------------
DWORD StopService(LPCTSTR pszInternalName)
{
	DWORD dwResult      = S_OK;

	SC_HANDLE hSCM      = NULL; 
	SC_HANDLE hService  = NULL;


	do
	{
		// Connect to the SCM 

		hSCM = ::OpenSCManager( NULL, NULL, SC_MANAGER_CONNECT );

		if( hSCM == NULL ) 
		{
			dwResult = GetLastError();
			break;
		}


		// Open the service 
		hService = ::OpenService( hSCM, pszInternalName, SERVICE_STOP);// | SERVICE_QUERY_STATUS );
		if( hService == NULL )
		{
			dwResult = GetLastError(); 
			break;
		}


		// Ask the service to stop 
		SERVICE_STATUS ss;

		if( !::ControlService( hService, SERVICE_CONTROL_STOP, &ss ) )
		{
			DWORD dwErrCode = GetLastError(); 

			if( dwErrCode != ERROR_SERVICE_NOT_ACTIVE )
			{
				dwResult = dwErrCode; 
				break;
			}
		}


		// Wait until it stopped (or timeout expired)
		if( !WaitForServiceToReachState( hService, SERVICE_STOPPED, &ss, INFINITE ) )
		{
			dwResult = GetLastError();
			break;
		}

	} 
	while(0);


	// Cleanup 
	if( hService != NULL )
		::CloseServiceHandle( hService );

	if( hSCM != NULL )
		::CloseServiceHandle( hSCM );

	return dwResult; 
}

//---------------------------------------------------------------------------
DWORD StartService(LPCTSTR pszInternalName)
{
DWORD dwStatus      = S_OK;
char szCode[16] = {0};  //error code
extern void log(const std::string& strMsg);
std::string strLogEntry;

SERVICE_STATUS_PROCESS ssStatus;
DWORD dwOldCheckPoint = 0;
DWORD dwStartTickCount;

SC_HANDLE schSCManager = OpenSCManager(NULL,                    // local machine 
                            NULL,                    // ServicesActive database 
                            SC_MANAGER_ALL_ACCESS);  // full access rights 
 
if (schSCManager != NULL) 
  {
  SC_HANDLE schService = OpenService(schSCManager,          // SCM database 
                                     pszInternalName,          // service name
                                     SERVICE_ALL_ACCESS);    //TODO: see that the service is in not running currently. 

  if (schService != NULL)
    {
    /*- When a driver service is started, the StartService function does not
        return until the device driver has finished initializing.
      - When a service is started, the Service Control Manager (SCM) spawns
        the service process, if necessary. StartService returns when the SCM
        receives notification from the service control dispatcher that 
        the ServiceMain thread for this service was created successfully.
        Current state of the service is set to SERVICE_START_PENDING.
     */
    if (StartService(schService,  // handle to service 
                     0,           // number of arguments 
                     NULL) != FALSE)
      {
      DWORD dwBytesNeeded = 0;
      dwStartTickCount = GetTickCount();

      //Check the status until the service is no longer start pending

      //TODO: replace loop with WaitForServiceToReachState D.K.
      while (QueryServiceStatusEx(schService,             // handle to service 
                                  SC_STATUS_PROCESS_INFO, // info level
                                  (LPBYTE)&ssStatus,              // address of structure
                                  sizeof(SERVICE_STATUS_PROCESS), // size of structure
                                  &dwBytesNeeded ) != FALSE)
        {
        if( ssStatus.dwCurrentState == SERVICE_RUNNING )
          {
          dwStatus = S_OK;
          break;  //Service is running
          }

        if( ssStatus.dwCurrentState == SERVICE_START_PENDING )
          {
          if ( ssStatus.dwCheckPoint > dwOldCheckPoint ) //Check if any progress is made
            {
            dwStartTickCount = GetTickCount();
            dwOldCheckPoint = ssStatus.dwCheckPoint;
            }
          else //Check if we are waiting more then hinted period
            {
            if((GetTickCount() - dwStartTickCount) > ssStatus.dwWaitHint)
              {
              break; //Bail out
              }
            }
          Sleep(1500); //Give time or more
          }
        }

      if (ssStatus.dwCurrentState != SERVICE_RUNNING)
        {
        //Failed to start the service
        dwStatus = GetLastError();
        strLogEntry = "StartService() time expired: system error 0x";
        _itoa_s(dwStatus, szCode, 16, 16);
        strLogEntry += szCode;
        log(strLogEntry);
        }

      }
    else
      {
      dwStatus = GetLastError();
      if(dwStatus != ERROR_SERVICE_ALREADY_RUNNING)
        {
        strLogEntry = "StartService() failed: system error 0x";
        }
      else
        {
        strLogEntry = pszInternalName;
        strLogEntry += " is running: 0x";
        }
      _itoa_s(dwStatus, szCode, 16, 16);
      strLogEntry += szCode;
      log(strLogEntry);
      }

    CloseServiceHandle(schService);
    }
  else
    { 
    dwStatus = GetLastError();
    strLogEntry = "OpenService() failed: system error 0x";
    _itoa_s(dwStatus, szCode, 16, 16);
    strLogEntry += szCode;
    log(strLogEntry);
    }
  }
else
  {
  dwStatus = GetLastError();
  strLogEntry = "OpenSCManager() failed: system error 0x";
  _itoa_s(dwStatus, szCode, 16, 16);
  strLogEntry += szCode;
  log(strLogEntry);
  }

return dwStatus;
}
