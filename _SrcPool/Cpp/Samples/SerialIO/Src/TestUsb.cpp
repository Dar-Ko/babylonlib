/*$Workfile: TestSerialIo.cpp$: implementation file
  $Revision: 1$ $Date: 2007-03-18 21:56:25$
  $Author: Darko$

  Test USB port helpers.
  Copyright: CommonSoft Inc.
  2007-08-02 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"

#include "KUsb.h" //USBID struct

extern CTestLog g_logTest;   //general test logger
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(const unsigned int& nValue);

extern uint_fast32_t EnumerateHostControllers();

//-----------------------------------------------------------------------------
/*Validates Universal Serial Bus (USB) port enumeration methods.

  Returns true if test is successful; otherwise returns false.
 */
bool TestUsbEnumeration()
{
TsWriteToViewLn(_T("TestUsbEnumeration"));

bool bResult = false; //test result

  //Test log  creation
g_logTest.m_szObjectName = _T("EnumerateHostControllers()");
g_logTest.m_szFileName   = _T("KUsbHub.cpp");//function or object file name
g_logTest.m_bResult      = false;              //result of the test

try
  {
  unsigned nUsbHostControllerCount = EnumerateHostControllers();
  TsWriteToView(_T("USB Host Controllers: "));
  TsWriteToViewLn(nUsbHostControllerCount);
  bResult = true;
  }
catch(...)
  {
  bResult = false;
  }

g_logTest.LogResult(bResult);
return bResult;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: $
 *****************************************************************************/
