/*$Workfile: TestBasicTypes.js$: script file
  $Revision: 1$ $Date: 2006-11-09 17:58:29$
  $Author: Darko Kolakovic$

  Test basic types validation
  Copyright: CommonSoft Inc.
  2006-11-09 Darko Kolakovic
*/

// Group=Examples
//-----------------------------------------------------------------------------
/*Function validates basic types

  Returns: true if successful, otherwise returns false.
 */

function TestBasicTypes()
{
TsWriteToView("TestBasicTypes()");
//TESTENTRY logEntry =
//  {_T("IsLeapYear()"), _T("KTime.h"), false};

var bRes = true;

  //Write test log
//logEntry.m_bResult = bRes;
//LogTest(&logEntry);
//logEntry.m_szObjectName = _T("IS_LEAP_YEAR()");
//LogTest(&logEntry);
TsWriteToView("LOG_EOT");
return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2006-11-09 17:58:29  Darko Kolakovic 
 * $
 *****************************************************************************/
