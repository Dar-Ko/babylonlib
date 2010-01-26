/*$RCSfile: TestWmi.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2010/01/26 22:47:05 $
  $Author: ddarko $

  Test WMI routines.
  2010-01-05 Darko Kolakovic
 */

// Group=Examples Windows

#include "stdafx.h"
#include "KWmi.h" //CWmi class

//-----------------------------------------------------------------------------
/*
 */
bool TestWmi()
{
TRACE(_T("TestWmi()\n"));
bool bResult = false;
CWmi wmiTest;
bResult = wmiTest.Init(NULL);
if(bResult)
  {
  bResult = wmiTest.Disconnect();
  }
return bResult;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: TestWmi.cpp,v $
 * Revision 1.2  2010/01/26 22:47:05  ddarko
 * Initialization of WMI
 *
 * Revision 1.1  2010/01/21 22:18:19  ddarko
 * Created
 *
 ******************************************************************************/
