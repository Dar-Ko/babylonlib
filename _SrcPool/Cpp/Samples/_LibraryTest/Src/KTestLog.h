/*$Workfile: S:\_SrcPool\Cpp\Samples\_LibraryTest\Src\KTestLog.h$: header file
  $Revision: 1.1 $ $Date: 2003/01/31 03:05:28 $
  $Author: ddarko $

  Collect some information about code testing
  Copyright: CommonSoft Inc.
  Darko Kolakovic 2003-01
*/
/* Group=Diagnostic                                                          */

#ifndef __KTESTLOG_H__
    /*KTestLog.h sentry                                                      */
  #define __KTESTLOG_H__

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
      ~CTestLog();
      void LogTest(TESTENTRY& testLog) const;
    };

  inline CTestLog::CTestLog()
    {
    ::InitLogTest();
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
#endif

/* ///////////////////////////////////////////////////////////////////////// */
#endif /*__KTESTLOG_H__                                                      */
/******************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         30/01/2003 9:45:02 PMDarko           
 * $
 *****************************************************************************/
