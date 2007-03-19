/*$Workfile: S:\_SrcPool\Cpp\Samples\SerialIO\Src\TestSerialIo.cpp$: implementation file
  $Revision: 1$ $Date: 2007-03-18 21:56:25$
  $Author: Darko$

  Test serial port I/O.
  Copyright: CommonSoft Inc.
  2007-02-02 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"

#include "KSerialIo.h" //CSerialIo class

extern CTestLog g_logTest;   //general test logger
extern bool TsWriteToViewLn(LPCTSTR lszText);

bool TestSerialIo(const unsigned int nPortNo = 1);
//-----------------------------------------------------------------------------
/*Validates serial port writing and reading methods.

  Returns true if test is successful; otherwise returns false.
 */
bool TestSerialIo(const unsigned int nPortNo //= 1 [in]
                 )
{
TsWriteToViewLn(_T("TestSerialIo"));

bool bResult = false; //test result

  //Test log  creation
g_logTest.m_szObjectName = _T("CSerialIo()");
g_logTest.m_szFileName   = _T("KSerialIo.cpp");//function or object file name
g_logTest.m_bResult      = false;              //result of the test

try
  {
  CSerialIo clSerialPort;
  bResult = true;
  }
catch(...)
  {
  bResult = false;
  }

g_logTest.LogResult(bResult);
return bResult;
}

#pragma warning (default  : 4786)

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2007-03-18 21:56:25  Darko           
 * $
 *****************************************************************************/
