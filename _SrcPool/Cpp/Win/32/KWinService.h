/*$Workfile: KWinService.h$: implementation file
  $Revision: 4$ $Date: 2007-02-21 09:08:59$
  $Author: Darko Kolakovic$

  OS Service deamon
  Copyright: CommonSoft Inc
  2007-02-02 Darko Kolakovic
 */
/* Group=System                                                              */

#ifndef _KWINSERVICE_H_
    /*$Workfile: KWinService.h$ sentry                                       */
  #define _KWINSERVICE_H_


#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

#include "KTypedef.h"

#ifdef __cplusplus
/* ///////////////////////////////////////////////////////////////////////// */
/*System service class creates a process running in background and performing
  a service usually without any user's interaction. A service most often begins
  execution immediately after operating system start.
  Configuration and control of services on Windows NT or later systems is
  handled by Service Control Manager (SCM).
  The Service Control Manager, started at system boot, provides a database
  of installed services and driver services and methods for service configuration
  or handling. Becouse it is remote procedure call (RPC) server, it could be
  also accessed from remote machines.
  A service created with the type SERVICE_WIN32_OWN_PROCESS only contains the
  code for one service. A service created with the type
  SERVICE_WIN32_SHARE_PROCESS contains code for more than one service,
  enabling them to share code. A service can be configured to execute in
  the context of a user account from either the built-in (local), primary or
  trusted domain. It can also be configured to run in a special service user
  account.

  Example:
      #include "KWinService.h"  //CWinService class
      int _tmain(int argc, TCHAR* argv[])
        {
        CWinService myService;
        //Allow SCM to create the service entry and initialize
        //service specific data
        if (myService.Create(_T("MyService")))
          {
          ...
          }
        ...
        }

  See also: CAtlServiceModuleT (ATL)
 */
class CWinService
{
// Construction
public:
  CWinService();
  virtual ~CWinService();

private:
  CWinService(const CWinService& cService);
  CWinService& operator= (const CWinService& cService);

// Attributes
private:
  bool m_bHasScm; //OS has support for Service Control Manager (SCM) used
                  //to load and control a service.

  LPSERVICE_MAIN_FUNCTION m_pfServiceMain; //pointer to the callback function
                  //to be used by SCM to start and initialize the service and
                  //update service status.
  SERVICE_STATUS          m_sStatus; //current state of the service
  SERVICE_STATUS_HANDLE   MyServiceStatusHandle;

// Operations
public:
  virtual bool Create(LPTSTR szServiceName, LPCTSTR szDisplayName = NULL);
//  virtual void Run();
//  virtual void Stop();

//    virtual void Pause();
//    virtual void Continue();
//    virtual void Shutdown();

    //virtual bool StartDispatcher();
    //virtual bool InstallService();
    //virtual bool UninstallService();
    //virtual bool StartService();
    //virtual bool StopService();
    //virtual bool ExecuteService();

public:
  //bool IsInstalled() const;
  //virtual LPTSTR toString(LPTSTR szTarget);

};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Creating a copy of other system service object is not allowed.
 */
inline CWinService::CWinService(const CWinService& cService) :
  m_pfServiceMain(NULL)
{}

//-----------------------------------------------------------------------------
/*Creating a copy of other system service object is not allowed.
 */
inline CWinService& CWinService::operator= (const CWinService& cService)
{
return( *this );
}

#endif //__cplusplus

/* ///////////////////////////////////////////////////////////////////////// */
#endif  /*_KWINSERVICE_H_                                                     */

/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2007-02-06 11:00:43  Darko Kolakovic
 * $
 *****************************************************************************/
