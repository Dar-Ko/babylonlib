/*$Workfile: KTestLog.cpp$: implementation file
  $Revision: 8$ $Date: 2004-08-23 16:59:31$
  $Author: Darko$

  Outputs test data to file
  Copyright: CommonSoft Inc.
  Darko Kolakovic 2003-01
*/

// Group=Diagnostic

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#include <stdio.h>    //fopen()
#include "KStrings.h" //BoolToA()
#include "KTestLog.h" //TESTENTRY struct

static bool s_bTestLogInitalized = false; //'Test Log initialization passed' flag
static FILE* s_fileTestLog;  //test log file handler

#ifndef _UNICODE
  static LPCTSTR TESTLOGNAME = _T("LibraryTest.log"); //default test 
                                                      //log file name
#else
  static LPCTSTR TESTLOGNAME = _T("LibraryTestUni.log"); //default Unicode test
                                                         //log file name
#endif

//InitLogTest()----------------------------------------------------------------
/*Initalizes test log file and writes data about testing environment: date and 
  time of the compilation, ANSI C compliance, text mapping.
 */
void InitLogTest()
{
if (!s_bTestLogInitalized) //Initialize only once
  {
  //Open an empty file for reading and writing
  #ifndef _UNICODE
    LPCTSTR szMode = _T("w+");
  #else
      //binary mode is used to avoid EOL translations (DOS, Win specific)
    LPCTSTR szMode = _T("wb+");
  #endif
  s_fileTestLog = _tfopen(TESTLOGNAME, szMode);

  if (s_fileTestLog != NULL)
    {
    s_bTestLogInitalized = true;
    LPTSTR szEntry;
    LPCTSTR szEOL = _T("\n"); //end-of-line

    #ifndef _UNICODE
      fwrite(__DATE__, sizeof(TCHAR), _tcslen(__DATE__), s_fileTestLog);
      fwrite(_T("\t"), sizeof(TCHAR), 1, s_fileTestLog);
      fwrite(__TIME__, sizeof(TCHAR), _tcslen(__TIME__), s_fileTestLog);
      fwrite(szEOL, sizeof(TCHAR), 1, s_fileTestLog);
    #else
      //Byte order mark indicates a Unicode file
      const TCHAR UCBYTEORDERMARK = 0xFEFF;
      TCHAR szBuffer[32];
      int i = 0;
      unsigned int nLen = 0;
      szBuffer[i++] = UCBYTEORDERMARK;
      //This hack exploits same mapping in SBCS and Unicode tables
      while (nLen < strlen(__DATE__) )
        {
        szBuffer[i++] = __DATE__[nLen++];
        }
      szBuffer[i++] = _T('\t');
      nLen = 0;
      while (nLen < strlen(__TIME__) )
        {
        szBuffer[i++] = __TIME__[nLen++];
        }
      szBuffer[i++] = szEOL[0];
      fwrite(szBuffer, sizeof(TCHAR), i, s_fileTestLog);
    #endif

    #ifdef __STDC__
      szEntry = _T("ANSI C compliance");
      fwrite(szEntry, sizeof(TCHAR), _tcslen(szEntry), s_fileTestLog);
      fwrite(szEOL, sizeof(TCHAR), 1, s_fileTestLog);
    #endif

    #ifdef _AFXDLL
      szEntry = _T("Use MFC in a Shared DLL");
      fwrite(szEntry, sizeof(TCHAR), _tcslen(szEntry), s_fileTestLog);
      fwrite(szEOL, sizeof(TCHAR), 1, s_fileTestLog);
    #endif
    #ifdef _ATL_DLL
      szEntry = _T("Dynamic Link to ATL");
      fwrite(szEntry, sizeof(TCHAR), _tcslen(szEntry), s_fileTestLog);
      fwrite(szEOL, sizeof(TCHAR), 1, s_fileTestLog);
    #endif
    #ifdef _ATL_STATIC_REGISTRY
      szEntry = _T("Static Link to ATL");
      fwrite(szEntry, sizeof(TCHAR), _tcslen(szEntry), s_fileTestLog);
      fwrite(szEOL, sizeof(TCHAR), 1, s_fileTestLog);
    #endif


      /*Write text mapping compiler configuration*/
    #if defined UNICODE || defined _UNICODE
      /*Unicode character (16-bit)
        ISO 10646-1 Universal Multiple Octet Coded Character Set (UCS).
       */
      szEntry = _T("Unicode (wide-character) text mapping");
    #endif
    #if defined _MBCS && !defined _UNICODE
      szEntry = _T("Multibyte-character (MBCS) text mapping");
    #endif
    #if !defined _MBCS && !defined _UNICODE
      /*ASCII character (8-bit)*/
      szEntry = _T("Singlebyte-character (SBCS or ASCII) text mapping");
    #endif
    fwrite(szEntry, sizeof(TCHAR), _tcslen(szEntry), s_fileTestLog);
    fwrite(szEOL, sizeof(TCHAR), 1, s_fileTestLog);

    #ifdef _CONSOLE
      szEntry = _T("Console");
    #else
      szEntry = _T("GUI");
    #endif
    fwrite(szEntry, sizeof(TCHAR), _tcslen(szEntry), s_fileTestLog);
    fwrite(szEOL, sizeof(TCHAR), 1, s_fileTestLog);

    #ifdef _DEBUG
      szEntry = _T("Debug");
    #else
      szEntry = _T("Release");
    #endif
    fwrite(szEntry, sizeof(TCHAR), _tcslen(szEntry), s_fileTestLog);
    fwrite(szEOL, sizeof(TCHAR), 1, s_fileTestLog);

//TODO: move following entries to separate test example D.K.
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
 *  8    Biblioteka1.7         2004-08-23 16:59:31  Darko           Unicode build
 *  7    Biblioteka1.6         2004-06-03 10:25:25  Darko           _AFXDLL,
 *       _ATL_DLL
 *  6    Biblioteka1.5         2004-06-03 08:59:16  Darko           fixed
 *       Unicode-specific prolog
 *  5    Biblioteka1.4         2004-06-01 15:54:43  Darko           StdAfx changed
 *       to stdafx
 *  4    Biblioteka1.3         2003-09-22 21:27:01  Darko           formatting
 *  3    Biblioteka1.2         2003-08-29 07:47:58  Darko           localization
 *  2    Biblioteka1.1         2003-02-10 14:48:40  Darko           
 *  1    Biblioteka1.0         2003-01-30 21:44:58  Darko           
 * $
 *****************************************************************************/
