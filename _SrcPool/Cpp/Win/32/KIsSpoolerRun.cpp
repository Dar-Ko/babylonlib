/*$RCSfile: KIsSpoolerRun.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2012/08/01 18:16:44 $
  $Author: ddarko $

  Verifies Windows spooler service.
  Copyright: CommonSoft Inc.
  2002-10-16 Darko Kolakovic
 */
#include "stdafx.h"
#include <winsvc.h>

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------
/*Verifies if Windows print spoller service is running.

  Returns true id spooler service is running. If service manager could not be
  accessed or if service is not running returns false.
 */
bool IsSpoolerRunning()
{
SC_HANDLE hServiceManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
LPCTSTR szServiceName = _T("Spooler");
if (hServiceManager != NULL) 
  {
  //Connect to the spooler
  SC_HANDLE hService = OpenService(hServiceManager, szServiceName, SERVICE_ALL_ACCESS);
  if (hService != NULL)
    {
    //Get status
    SERVICE_STATUS sServiceStatus;
    if(QueryServiceStatus(hService, &sServiceStatus) == TRUE)
      {
      return (sServiceStatus.dwCurrentState == SERVICE_RUNNING);
      }
    CloseServiceHandle(hService);
    }
  CloseServiceHandle(hServiceManager);
  }
return false;
}
/*****************************************************************************
 * $Log: KIsSpoolerRun.cpp,v $
 * Revision 1.2  2012/08/01 18:16:44  ddarko
 * Service name
 *
 * Revision 1.1  2011/12/22 15:53:06  ddarko
 * Moved from local repository
 *
 *****************************************************************************/
