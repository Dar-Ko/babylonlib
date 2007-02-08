/*$Workfile: KDbgRpt.cpp$: implementation file
  $Revision: 2$ $Date: 2007-02-08 15:49:26$
  $Author: Darko Kolakovic$

  Unicode Debug C Run-time Reporting Functions, required by
  Microsoft Visual Studio .Net 2003 v7.1 or lesser.
  Modified from crt/src/dbgrpt.c (SCBS version)
  Copyright: Microsoft Corporation.
  2005-04-01 Darko Kolakovic
*/

#ifdef _DEBUG
  #ifdef _UNICODE
    #if (_MSC_VER < 1400) //Less than Visual C++ 2005 v8.0

  #ifdef  __cplusplus
    extern "C" {
  #endif  /* __cplusplus */

  #include <crtdbg.h>
  #include <tchar.h>
  #include <stdio.h>
  #include <stdarg.h>
  #include <windows.h>
  #include <signal.h>

  #ifndef LPCTSTR
    typedef const TCHAR * LPCTSTR;
    #define LPCTSTR LPCTSTR
  #endif

  #ifndef _CrtInterlockedIncrement
    //Thread safe increments
    #define _CrtInterlockedIncrement InterlockedIncrement
  #endif
  #ifndef _CrtInterlockedDecrement
    //Thread safe decrements
    #define _CrtInterlockedDecrement InterlockedDecrement
  #endif

  #define MAXLINELEN  64
  #define MAX_MSG     4096 //Maximum debugging message length
  #define tTOOLONGMSG _T("tCrtDbgReport: String too long or IO Error")

  /*CRT MessageBoxA wrapper to avoid static link with user32.dll
    See crt\src\crtmbox.c
   */
  extern int __cdecl __crtMessageBoxA(LPCSTR lpText,
                                      LPCSTR lpCaption,
                                      UINT uType);
  typedef struct ReportHookNode
    {
    struct ReportHookNode* prev;
    struct ReportHookNode* next;
    unsigned               refcount;
    _CRT_REPORT_HOOK       pfnHookFunc;
    } ReportHookNode;

  extern ReportHookNode*  _pReportHookList;
  extern _CRT_REPORT_HOOK _pfnReportHook;
  extern int    _CrtDbgMode[]; //Array of _CRT_ERRCNT = 3debugging modes
  extern _HFILE _CrtDbgFile[]; //Array of _CRT_ERRCNT = 3debugging log files

  extern _CRTIMP long _crtAssertBusy; //Thread synchronisation counter

  /////////////////////////////////////////////////////////////////////////////
  // Unicode Debug Reporting

  int tCrtMessageWindow(int, LPCTSTR, LPCTSTR, LPCTSTR, LPCTSTR);
  int __cdecl tCrtDbgReport(int nRptType,
                            LPCTSTR szFile, int nLine,
                            LPCTSTR szModule, LPCTSTR szFormat, ... );

  //Debugging error message prefixes
  LPCTSTR _tCrtDbgModeMsg[_CRT_ERRCNT] =
    {
    _T("Warning"),
    _T("Error"),
    _T("Assertion Failed")
    };

  #ifdef  __cplusplus
    }
  #endif

/////////////////////////////////////////////////////////////////////////////
// Implementation

//-----------------------------------------------------------------------------

    /***
    *static int tCrtMessageWindow() - report to a message window
    *
    *Purpose:
    *  put report into message window, allow user to choose action to take
    *
    *Entry:
    *  int    nRptType  - report type
    *  const char * szFile  - file name
    *  const char * szLine  - line number
    *  const char * szModule  - module name
    *  const char * szUserMessage - user message
    *
    *Exit:
    *  if (MessageBox)
    *  {
    *   Abort -> aborts
    *   Retry -> return TRUE
    *   Ignore-> return FALSE
    *  }
    *  else
    *   return FALSE
    *
    *Exceptions:
    *
    *******************************************************************************/

    int tCrtMessageWindow(
      int nRptType,
      LPCTSTR szFile,
      LPCTSTR szLine,
      LPCTSTR szModule,
      LPCTSTR szUserMessage
      )
    {
      int nCode;
      LPTSTR szShortProgName;
      LPTSTR szShortModuleName;
      TCHAR szExeName[MAX_PATH + 1];
      TCHAR szOutMessage[MAX_MSG];

      _ASSERTE(szUserMessage != NULL);

      /* Shorten program name */
      szExeName[MAX_PATH] = _T('\0');
      if (!GetModuleFileName(NULL, szExeName, MAX_PATH))
        _tcscpy(szExeName, _T("<program name unknown>"));

      szShortProgName = szExeName;

      if (_tcslen(szShortProgName) > MAXLINELEN)
      {
        szShortProgName += _tcslen(szShortProgName) - MAXLINELEN;
        _tcsncpy(szShortProgName, _T("..."), 3);
      }

      /* Shorten module name */
      szShortModuleName = (TCHAR *) szModule;

      if (szShortModuleName && _tcslen(szShortModuleName) > MAXLINELEN)
      {
        szShortModuleName += _tcslen(szShortModuleName) - MAXLINELEN;
        _tcsncpy(szShortModuleName, _T("..."), 3);
      }

      if (_sntprintf(szOutMessage, MAX_MSG,
        _T("Debug %s!\n\nProgram: %s%s%s%s%s%s%s%s%s%s%s\n\n(Press Retry to debug the application)"),
        _tCrtDbgModeMsg[nRptType],
        szShortProgName,
        szShortModuleName ? _T("\nModule: ") : _T(""),
        szShortModuleName ? szShortModuleName : _T(""),
        szFile ? _T("\nFile: ") : _T(""),
        szFile ? szFile : _T(""),
        szLine ? _T("\nLine: ") : _T(""),
        szLine ? szLine : _T(""),
        szUserMessage[0] ? _T("\n\n") : _T(""),
        szUserMessage[0] && _CRT_ASSERT == nRptType ? _T("Expression: ") : _T(""),
        szUserMessage[0] ? szUserMessage : _T(""),
        _CRT_ASSERT == nRptType ?
        _T("\n\nFor information on how your program can cause an assertion\nfailure, see the Visual C++ documentation on asserts.")
        : _T("")) < 0)
        _tcscpy(szOutMessage, tTOOLONGMSG);

      /* Report the warning/error */ //TODO: convert szOutMessage to SBCS
      nCode = __crtMessageBoxA("szOutMessage",
        ("Unicode Replacement Debug Library"),
        MB_TASKMODAL|MB_ICONHAND|MB_ABORTRETRYIGNORE|MB_SETFOREGROUND);

      /* Abort: abort the program */
      if (IDABORT == nCode)
      {
        /* raise abort signal */
        raise(SIGABRT);

        /* We usually won't get here, but it's possible that
        SIGABRT was ignored. So exit the program anyway. */

        _exit(3);
      }

      /* Retry: return 1 to call the debugger */
      if (IDRETRY == nCode)
        return 1;

      /* Ignore: continue execution */
      return 0;
    }

//-----------------------------------------------------------------------------
/*Generates a report with a debugging message and sends the report to three
  possible destinations (Unicode debug version only).
  Displays a message window with the following format:

      ================= Microsoft Visual C++ Debug Library ================

      {Warning! | Error! | Assertion Failed!}

      Program: c:\test\mytest\foo.exe
      [Module: c:\test\mytest\bar.dll]
      [File: c:\test\mytest\bar.c]
      [Line: 69]

      {<warning or error message> | Expression: <expression>}

      [For information on how your program can cause an assertion
      failure, see the Visual C++ documentation on asserts]

      (Press Retry to debug the application)

      ===================================================================

  Requires debug versions of C run-time libraries and Microsoft visual Studio
  .Net 2003 v7.1, or Microsoft Visual C/C++ v6.0. It is not required for
  Microsoft Visual C/C++ 2005 v8.0 or greater.

  Returns: –1 if an error occurs for all report destinations or 0 if no errors
  are encountered. However, when the report destination is a debug message
  window and the user clicks the Retry button, returns 1.
  If the user clicks the Abort button in the Debug Message window,
  function immediately aborts and does not return a value.

  Example:
      #include "KTrace.h"
      #define _UNICODE
      {
      ...
      LPCTSTR szUnicode = _T("Wide-characters");
        //Example using TRACE macro
      TRACE1(_T("My Unicode message: %s.\n"), szUnicode);
      ...
      tCrtDbgReport( _CRT_WARN, NULL, 0, NULL, _T("Another example with %s\n"), szUnicode);
      }
 */
  _CRTIMP int __cdecl tCrtDbgReport(int nRptType,    //[in] report type:
                                     //_CRT_WARN, _CRT_ERROR, _CRT_ASSERT.
                                    LPCTSTR szFile,   //[in] name of source
                                     //file where assert/report occurred or NULL.
                                    int nLine,        //[in] line number in
                                     //source file where assert/report occurred
                                     //or NULL.
                                    LPCTSTR szModule, //[in] name of module
                                     //(.exe or .dll) where assert/report occurred.
                                    LPCTSTR szFormat, //[in] format-control
                                     //string used to create the user message.
                                    ...               //[in] optional
                                     //substitution arguments used by szFormat.
                                    )
  {
  int retval;
  va_list arglist;
  TCHAR szLineMessage[MAX_MSG] = {0};
  TCHAR szOutMessage[MAX_MSG]  = {0};
  TCHAR szUserMessage[MAX_MSG] = {0};
  #define ASSERTINTRO1 _T("Assertion failed: ")
  #define ASSERTINTRO2 _T("Assertion failed!")

  va_start(arglist, szFormat);

  if (nRptType < 0 || nRptType >= _CRT_ERRCNT)
    return -1;

  /*Handle the (hopefully rare) case of ASSERT while already dealing with
    other ASSERT or two threads asserting at the same time
   */
  if (_CRT_ASSERT == nRptType && _CrtInterlockedIncrement(&_crtAssertBusy) > 0)
    {
    /* use only 'safe' functions -- must not assert in here! */
    /*wsprintfW function */
    static int (APIENTRY *pfntsprintf)(LPTSTR, LPCTSTR, ...) = NULL;

    if (NULL == pfntsprintf)
      {
      //Load dynamically
      HANDLE hlib = LoadLibrary(_T("user32.dll"));
      if (NULL == hlib ||
          NULL == (pfntsprintf = (int (APIENTRY *)(LPTSTR, LPCTSTR, ...))
        GetProcAddress((HMODULE)hlib, "wsprintfW")))
      return -1;
      }

    (*pfntsprintf)( szOutMessage,
                    _T("Second Chance Assertion Failed: File %s, Line %d\n"),
                    szFile,
                    nLine);

    OutputDebugString(szOutMessage);
    _CrtInterlockedDecrement(&_crtAssertBusy);

    _CrtDbgBreak(); //Open a debugger window
    return -1;
    }

  //Leave space for ASSERTINTRO1 and "\r\n"
  if( szFormat &&
      _vsntprintf(szUserMessage,
      MAX_MSG-(max(sizeof(ASSERTINTRO1),sizeof(ASSERTINTRO2))/sizeof(TCHAR))-2,
      szFormat,
      arglist) < 0
    )
    _tcscpy(szUserMessage, tTOOLONGMSG);

  if (_CRT_ASSERT == nRptType) //Assert requires output
    _tcscpy(szLineMessage, szFormat ? ASSERTINTRO1 : ASSERTINTRO2);
  _tcscat(szLineMessage, szUserMessage);

  if (_CRT_ASSERT == nRptType) //Output to the file
    {
    if (_CrtDbgMode[nRptType] & _CRTDBG_MODE_FILE)
      _tcscat(szLineMessage, _T("\r"));
    _tcscat(szLineMessage, _T("\n"));
    }

  if (szFile) //Prepare output message
    {
    if (_sntprintf(szOutMessage, MAX_MSG, _T("%s(%d) : %s"),
                   szFile,
                   nLine,
                   szLineMessage) < 0)
      _tcscpy(szOutMessage, tTOOLONGMSG);
    }
  else
    _tcscpy(szOutMessage, szLineMessage);

  /* User hook may handle report. Check Hook2 list first */
  if (_pReportHookList)
    {
    ReportHookNode *pnode;

    #ifdef _MT
      _mlock(_DEBUG_LOCK);
      __try
      {
    #endif /* _MT */

      for (pnode = _pReportHookList; pnode; pnode = pnode->next)
        {
        //TODO: Convert szOutMessage to SBCS
        if ((*pnode->pfnHookFunc)(nRptType, "szOutMessage", &retval))
          {
          if (_CRT_ASSERT == nRptType)
            _CrtInterlockedDecrement(&_crtAssertBusy);
          return retval;
          }
        }

    #ifdef _MT
      }
      __finally {
        _munlock(_DEBUG_LOCK);
      }
    #endif /* _MT */
    }

  if (_pfnReportHook)
    {
    //TODO: Convert szOutMessage to SBCS
    if ((*_pfnReportHook)(nRptType, "szOutMessage", &retval))
      {
      if (_CRT_ASSERT == nRptType)
        _CrtInterlockedDecrement(&_crtAssertBusy);
      return retval;
      }
    }

  if (_CrtDbgMode[nRptType] & _CRTDBG_MODE_FILE) //Dump to the log file
    {
    if (_CrtDbgFile[nRptType] != _CRTDBG_INVALID_HFILE)
      {
      DWORD written;
      WriteFile(_CrtDbgFile[nRptType],
                szOutMessage,
                (unsigned long)_tcslen(szOutMessage)*sizeof(TCHAR),
                &written,
                NULL);
      }
    }

  if (_CrtDbgMode[nRptType] & _CRTDBG_MODE_DEBUG) //Output to debugger window
    {
    OutputDebugString(szOutMessage);
    }

  if (_CrtDbgMode[nRptType] & _CRTDBG_MODE_WNDW) //Open Message Box
    {
    TCHAR szLine[20];
    retval = tCrtMessageWindow(nRptType,
                                szFile,
                                nLine ? _itot(nLine, szLine, 10) : NULL,
                                szModule,
                                szUserMessage);
    if (_CRT_ASSERT == nRptType)
      _CrtInterlockedDecrement(&_crtAssertBusy);
    return retval;
    }

  if (_CRT_ASSERT == nRptType)
    _CrtInterlockedDecrement(&_crtAssertBusy);

  return FALSE; /* ignore */
  }
    //=========================================================================
    #else //(_MSC_VER == 1400) Visual C++ 2005 v8.0
      #ifndef tCrtDbgReport
        //Debug reporting DBCS version
        #define tCrtDbgReport _CrtDbgReportW
      #endif
    #endif //(_MSC_VER < 1400)
  /////////////////////////////////////////////////////////////////////////////
  #else //!(_UNIOCODE)
    #ifndef tCrtDbgReport
      //Debug reporting SBCS version
     #define tCrtDbgReport _CrtDbgReport
    #endif
  #endif //(_UNIOCODE)
#endif /* _DEBUG */
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  2    Biblioteka1.1         2007-02-08 15:49:26  Darko Kolakovic tCrtDbgReport()
 *  1    Biblioteka1.0         2007-02-07 18:19:47  Darko Kolakovic 
 * $
 *****************************************************************************/
