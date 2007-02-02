/*$Workfile: KXmlProcessorSax.cpp$: implementation file
  $Revision: 14$ $Date: 2005-04-29 01:13:07$
  $Author: Darko$

  Defines the class behavior.
  Copyright: CommonSoft Inc.
  2007-02-02 Darko Kolakovic
 */
#include "stdafx.h"
#include "KOsService.h"  //COsService class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// COsService class


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
COsService::COsService(LPCTSTR szServiceName, //[in] name of the service to install.
                                  //The maximum string length is 256 characters.
                       LPCTSTR szDisplayName  // = NULL [in] descriptive service
                       //name used by user interface programs to identify the service.
                       //The maximum length is 256 characters. The name is
                       //case-preserved in the service control manager.
                       //Display name comparisons are always case-insensitive.
                       )
{
if ((szServiceName == NULL) || szServiceName[0] == TCHAR('\0'))
  szServiceName = _T("OsService");

if ((szDisplayName == NULL) || szDisplayName[0] == TCHAR('\0'))
  szDisplayName = szServiceName;
}

//-----------------------------------------------------------------------------
/*Destructor.
 */
COsService::~COsService()
{
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
/*
  Returns: true if successful, false in case of a failure.
 */
bool COsService::Create()
{
return true;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: $
 *****************************************************************************/