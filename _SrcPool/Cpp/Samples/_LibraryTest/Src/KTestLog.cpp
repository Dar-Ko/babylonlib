/*$Workfile: S:\_SrcPool\Cpp\Samples\_LibraryTest\Src\KTestLog.cpp$: implementation file
  $Revision: 1.1 $ $Date: 2003/01/31 03:05:28 $
  $Author: ddarko $

  Outputs test data to file
  Copyright: CommonSoft Inc.
  Darko Kolakovic 2003-01
*/

// Group=Diagnostic

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include <stdio.h>    //fopen()
#include "KStrings.h" //BoolToA()
#include "KTestLog.h" //TESTENTRY struct
#include "KDbgMacr.h"

static bool s_bTestLogInitalized = false; //'Test Log initialization passed' flag
static FILE* s_fileTestLog;  //test log file handler

#ifndef UNICODE
  static LPCTSTR TESTLOGNAME = _T("LibraryTest.log"); //default test 
                                                      //log file name
#else
  static LPCTSTR TESTLOGNAME = _T("LibraryTestUni.log"); //default Unicode test
                                                         //log file name
#endif

//InitLogTest()----------------------------------------------------------------
/*Initalizes test log file and writes data about testing environment.
 */
void InitLogTest()
{
if (!s_bTestLogInitalized) //Initialize only once
  {
  //Open an empty file for reading and writing
  s_fileTestLog = fopen(TESTLOGNAME,"w+");
  if (s_fileTestLog != NULL)
    {
    s_bTestLogInitalized = true;
    LPTSTR szEntry;
      //Write log header: date and time
    fwrite(_T(__DATE__), sizeof(TCHAR), _tcslen(__DATE__), s_fileTestLog);
    fwrite(_T("\t"), sizeof(TCHAR), 1, s_fileTestLog);
    fwrite(_T(__TIME__), sizeof(TCHAR), _tcslen(__TIME__), s_fileTestLog);
    fwrite(_T("\n"), sizeof(TCHAR), 1, s_fileTestLog);
    #ifdef __STDC__
      szEntry = _T("ANSI C compliance\n");
      fwrite(szEntry, sizeof(TCHAR), _tcslen(szEntry), s_fileTestLog);
    #endif
    #ifdef UNICODE
      szEntry = _T("Unicode\n");
      fwrite(szEntry, sizeof(TCHAR), _tcslen(szEntry), s_fileTestLog);
    #endif
    #ifdef _CONSOLE
      szEntry = _T("Console\n");
    #else
      szEntry = _T("GUI\n");
    #endif
    fwrite(szEntry, sizeof(TCHAR), _tcslen(szEntry), s_fileTestLog);

    TESTENTRY logEntry = 
       {_T("Predefined macros"), _T("KDbgMacr.h"), true};
    LogTest(&logEntry);

    logEntry.m_szObjectName = _T("BoolToA()");
    logEntry.m_szFileName = _T("KStrings.h");
    logEntry.m_bResult = true;
    LogTest(&logEntry);

    logEntry.m_szObjectName = _T("InitLogTest()");
    logEntry.m_szFileName = _T("KTestLog.h");
    logEntry.m_bResult = true;
    LogTest(&logEntry);

    logEntry.m_szObjectName = _T("LogTest()");
    logEntry.m_szFileName = _T("KTestLog.h");
    logEntry.m_bResult = true;
    LogTest(&logEntry);

    logEntry.m_szObjectName = _T("CloseLogTest()");
    logEntry.m_szFileName = _T("KTestLog.h");
    logEntry.m_bResult = true;
    LogTest(&logEntry);

    logEntry.m_szObjectName = _T("CTestLog");
    logEntry.m_szFileName = _T("KTestLog.h");
    logEntry.m_bResult = true;
    LogTest(&logEntry);
    }
  }
}

//LogTest()--------------------------------------------------------------------
/*Writes test data to the test log in the following format:

      SourceCodeFileName \t ObjectName \t Result \n

 */
void LogTest(const PTESTENTRY pTestLog)
{
if (!s_bTestLogInitalized)
  InitLogTest();
if ((pTestLog != NULL) && (s_fileTestLog != NULL))
  {
    //Write source code file name
  fwrite(pTestLog->m_szFileName, 
         sizeof(TCHAR), _tcslen(pTestLog->m_szFileName),
         s_fileTestLog);
  fwrite(_T("\t"), sizeof(TCHAR), 1, s_fileTestLog);
    //Write name of the tested object
  fwrite(pTestLog->m_szObjectName, 
         sizeof(TCHAR), _tcslen(pTestLog->m_szObjectName),
         s_fileTestLog);
  fwrite(_T("\t"), sizeof(TCHAR), 1, s_fileTestLog);
    //Write test results
  LPCTSTR szResult = BoolToA(pTestLog->m_bResult);
  fwrite(szResult, sizeof(TCHAR), _tcslen(szResult), s_fileTestLog);
  fwrite(_T("\n"), sizeof(TCHAR), 1, s_fileTestLog);
  }

}

//CloseLogTest()---------------------------------------------------------------
/*Closes the test log.
 */
void CloseLogTest()
{
if (s_fileTestLog != NULL)
  {
  fflush(s_fileTestLog);
  fclose(s_fileTestLog);
  }
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         30/01/2003 9:44:58 PMDarko           
 * $
 *****************************************************************************/
