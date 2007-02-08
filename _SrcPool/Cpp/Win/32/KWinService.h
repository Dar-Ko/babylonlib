/*$Workfile: KWinService.h$: implementation file
  $Revision: 2$ $Date: 2007-02-07 18:19:30$
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

  {html:
    <img src="../Images/diagWinService.gif" title="Service Components"
      alt="WinNT service components" border="0"> <br />
  }
 */
class CWinService
{
// Construction
public:
  CWinService(LPCTSTR szServiceName, LPCTSTR szDisplayName = NULL);
  virtual ~CWinService();

private:
  CWinService();
  CWinService(const CWinService& cService);
  CWinService& operator= (const CWinService& cService);

// Attributes
private:
  bool m_bHasScm; //OS has support for Service Control Manager (SCM) used
                  //to load and control a service.
  LPSERVICE_MAIN_FUNCTION m_pfService;
// Operations
public:
  virtual bool Create();
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
/*Default system service is not allowed.
 */
inline CWinService::CWinService()
{}

//-----------------------------------------------------------------------------
/*Creating a copy of other system service object is not allowed.
 */
inline CWinService::CWinService(const CWinService& cService)
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
