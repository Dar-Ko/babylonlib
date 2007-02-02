/*$Workfile: KTime.h$: implementation file
  $Revision: 18$ $Date: 2005-06-28 12:38:09$
  $Author: Darko Kolakovic$

  OS Service deamon
  Copyright: CommonSoft Inc
  2007-02-02 Darko Kolakovic
 */
/* Group=System                                                              */

#ifndef _KOSSERVICE_H_
    /*$Workfile: $ sentry                                                    */
  #define _KOSSERVICE_H_


#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

#include "KTypedef.h"

#ifdef __cplusplus
/* ///////////////////////////////////////////////////////////////////////// */
/*System service class creates a process running in background and performing
  a service usually without any user's interaction. A service, also known as
  Terminate and Stay Resident (TSR), deamon or extension (see DOS, Unix,
  Windows and MacOS references), most often begins execution immediately
  after operating system start.
 */
class COsService
{
public:
  COsService(LPCTSTR szServiceName, LPCTSTR szDisplayName = NULL);
  virtual ~COsService();

private:
  COsService();
  COsService(const COsService& cService);
  COsService& operator= (const COsService& cService);

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
COsService::COsService()
{}

//-----------------------------------------------------------------------------
/*Creating a copy of other system service object is not allowed.
 */
COsService::COsService(const COsService& cService)
{}

//-----------------------------------------------------------------------------
/*Creating a copy of other system service object is not allowed.
 */
inline COsService& COsService::operator= (const COsService& cService)
{
return( *this );
}

#endif //__cplusplus

/* ///////////////////////////////////////////////////////////////////////// */
#endif  /*_KOSSERVICE_H_                                                     */

/*****************************************************************************
 * $Log: $
 *****************************************************************************/
