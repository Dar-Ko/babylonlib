/*$Workfile: KTestLog.h$: header file
  $Revision: 8$ $Date: 2007-03-06 18:04:05$
  $Author: Darko Kolakovic$

  Collect some information about code testing
  Copyright: CommonSoft Inc.
  Darko Kolakovic 2003-01
*/
/* Group=Diagnostic                                                          */

#ifndef _KTESTLOG_H_
    /*$Workfile: KTestLog.h$ sentry*/
  #define _KTESTLOG_H_

  #ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files   */
    #pragma message ("   #include " __FILE__ )
  #endif

#include "KTChar.h" /*LPCTSTR */

/*Container holding basic information about tested subject.
 */
struct tagTestEntry
{
LPCTSTR m_szObjectName; /*name of the tested function or object              */
LPCTSTR m_szFileName;   /*function or object file name                       */
bool    m_bResult;      /*result of the test                                 */
};

typedef struct tagTestEntry  TESTENTRY;  /*Basic test data                   */
typedef struct tagTestEntry* PTESTENTRY; /*Pointer to test data container    */
typedef bool (*PFUNC_TEST) (void);       /*Type definition of function used
                                           in testing                        */

/*Default Log entries                                                        */
#ifndef LANG_CURRENT
  #define LANG_CURRENT LANG_NEUTRAL
#endif

#if (LANG_CURRENT == LANG_NEUTRAL) && !defined (LOG_SUCCESS)
    /*Test succeeded log entry       */
  #define LOG_SUCCESS  _T("OK.")
    /*Test failed log entry          */
  #define LOG_FAILURE  _T("NOK!")
    /*End-of-Test tag                */
  #define LOG_EOT      _T("======================")
#endif

#if (LANG_CURRENT == LANG_ENGLISH) && !defined (LOG_SUCCESS)
    /*Test succeeded log entry       */
  #define LOG_SUCCESS  _T("Succeeded.")
    /*Test failed log entry          */
  #define LOG_FAILURE  _T("Failed!")
    /*End-of-Test tag                */
  #define LOG_EOT      _T("===================End")
#endif

#if (LANG_CURRENT == LANG_GERMAN) && !defined (LOG_SUCCESS)
  /*Erfolgreiche Protokollbucheintragung prüfen       */
  #define LOG_SUCCESS  _T("Erfolg.")
  /*Verlassene Protokollbucheintragung prüfen         */
  #define LOG_FAILURE  _T("Ausfall!")
  /*Ende-des-Tests Marke                              */
  #define LOG_EOT      _T("==================Ende")
#endif

/* ///////////////////////////////////////////////////////////////////////// */
/*Declarations                                                               */
#ifdef __cplusplus
extern "C"
  {
#endif

  void InitLogTest();
  void LogTest(const PTESTENTRY pTestLog);
  void CloseLogTest();

#ifdef __cplusplus
  }
#endif

/* ///////////////////////////////////////////////////////////////////////// */
/* C++ encapsulation                                                         */
#ifdef __cplusplus

class CTestLog : public tagTestEntry
    {
    public: 
      CTestLog();
      CTestLog(TESTENTRY& testLog);
      ~CTestLog();
      void LogTest(TESTENTRY& testLog) const;
      void LogResult(const bool bTestResult);

    };

  inline CTestLog::CTestLog()
    {
    ::InitLogTest();
    }

  inline CTestLog::CTestLog(TESTENTRY& testLog)
    {
    ::InitLogTest();
    m_szObjectName = testLog.m_szObjectName; //name of the tested function or object
    m_szFileName   = testLog.m_szFileName  ; //function or object file name
    m_bResult      = testLog.m_bResult     ; //result of the test
    }

  inline CTestLog::~CTestLog()
    {
    ::CloseLogTest();
    }

  //LogTest()------------------------------------------------------------------
  /*Writes an entry to the Test log.
   */
  inline void CTestLog::LogTest(TESTENTRY& testLog //[in] test log entry
                               ) const
    {
    ::LogTest(&testLog);
    }

  //LogResult()----------------------------------------------------------------
  /*Writes test result to the Test log.

    Example:
      #include "KTestLog.h"
      ...
      CTestLog testLog;
      testLog.m_szObjectName = _T("CNewMethod");   //name of the tested object
      testLog.m_szFileName   = _T("NewMethod.cpp");//function or object file name
      testLog.m_bResult      = false;              //result of the test
      ...
      if (bSuccess)
        testLog.LogResult(bSuccess);
      else
        testLog.LogResult(false);

   */
  inline void CTestLog::LogResult(const bool bTestResult //[in] test result
                       )
    {
    m_bResult = bTestResult;
    ::LogTest(this);
    }

#endif

/* ///////////////////////////////////////////////////////////////////////// */
#endif /*_KTESTLOG_H_                                                        */
/******************************************************************************
 * $Log: 
 *  8    Biblioteka1.7         2007-03-06 18:04:05  Darko Kolakovic LANG_GERMAN
 *  7    Biblioteka1.6         2004-10-21 12:18:47  Darko Kolakovic Boolean types
 *  6    Biblioteka1.5         2004-09-30 14:48:59  Darko           LogResult()
 *  5    Biblioteka1.4         2004-06-03 13:33:51  Darko           PFUNC_TEST
 *       typedef
 *  4    Biblioteka1.3         2003-09-22 21:27:03  Darko           formatting
 *  3    Biblioteka1.2         2003-08-29 07:48:38  Darko           localization
 *  2    Biblioteka1.1         2003-02-10 14:48:50  Darko           
 *  1    Biblioteka1.0         2003-01-30 21:45:02  Darko           
 * $
 *****************************************************************************/
