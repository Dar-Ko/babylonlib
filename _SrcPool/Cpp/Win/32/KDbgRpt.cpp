/*$Workfile: KDbgRpt.cpp$: implementation file
  $Revision: 5$ $Date: 22/08/2007 7:29:01 PM$
  $Author: Darko Kolakovic$

  Unicode Debug C Run-time Reporting Functions, required by
  Microsoft Visual Studio .Net 2003 v7.1 or lesser.
  Modified from crt/src/dbgrpt.c (SCBS version)
  Copyright: Microsoft Corporation.
  2005-04-01 Darko Kolakovic
*/

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#ifdef _DEBUG
  #ifdef _UNICODE
    #if (_MSC_VER < 1400) //Less than Visual C++ 2005 v8.0

  #ifndef UNICODE //Fix Microsoft macro mixed definitions
    #define UNICODE 20070822
  #endif

  #include <crtdbg.h>
  #include <tchar.h>
  #include <stdio.h>
  #include <stdarg.h>
  #define _WIN32_WINNT 0x0400 /* for MB_SERVICE_NOTIFICATION, defined in <winuser.h>*/
  #include <windows.h>
  #include <signal.h>

  #ifdef _MT
    /*Multithreaded build
      See also: crt\src\mtdll.h (MSVC++ v7.1 2003)
     */
    extern "C" void __cdecl _lock (int locknum);
    extern "C" void __cdecl _unlock (int locknum);
    #define _DEBUG_LOCK     15      /*lock for debug global structs*/
    #define _mlock(l)     _lock(l)
    #define _munlock(l)   _unlock(l)
  #endif

  #ifndef LPCTSTR
    #ifndef _WINNT_ //not included <winnt.h>
      typedef const TCHAR * LPCTSTR;
    #endif
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


  #ifdef  __cplusplus
    extern "C" {
  #endif  /* __cplusplus */

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

  extern _CRT_REPORT_HOOK _pfnReportHook;
  extern int    _CrtDbgMode[]; //Array of _CRT_ERRCNT = 3debugging modes
  extern _HFILE _CrtDbgFile[]; //Array of _CRT_ERRCNT = 3debugging log files

  extern _CRTIMP long _crtAssertBusy; //Thread synchronisation counter

  #if (_MSC_VER < 1300) //Less than Visual C++ .Net 2002, 32-bit, version 7.0
    _CRTIMP unsigned int _osplatform = 0;
    ReportHookNode*  _pReportHookList = NULL;
  #else
    extern ReportHookNode*  _pReportHookList;
  #endif

  /////////////////////////////////////////////////////////////////////////////
  // Unicode Debug Reporting

  int __cdecl tMessageBox(LPCTSTR lpText, LPCTSTR lpCaption, UINT uType);
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

//#ifndef MB_SERVICE_NOTIFICATION
  //#define _WIN32_WINNT 0x0400
  //#include <windows.h>
  //
//#endif
//-----------------------------------------------------------------------------
/*Creates a MessageBox dialog when actually needed, not linking user32.dll
  statically.

  Returns: 0 in case of failure and error to be obtained by GetLastError().
  If the function succeeds, the return value is one of the following menu-item values:
  - IDABORT Abort button was selected.
  - IDCANCEL Cancel button was selected.
  - IDCONTINUE Continue button was selected.
  - IDIGNORE Ignore button was selected.
  - IDNO No button was selected.
  - IDOK OK button was selected.
  - IDRETRY Retry button was selected.
  - IDTRYAGAIN Try Again button was selected.
  - IDYES Yes button was selected.

  See also: crt/src/crtmbox.c
 */
  int __cdecl tMessageBox(LPCTSTR lpText,    //[in] message to be displayed
                          LPCTSTR lpCaption, //[in] dialog box title. If it is
                          //NULL, the default title Error is used.
                          UINT uType         //[in] Specifies the contents and
                          //behavior of the dialog box. See also MessageBox().
                         )
  {
  typedef int     (APIENTRY *FMESSAGEBOX)(HWND, LPCTSTR, LPCTSTR, UINT);
  typedef HWND    (APIENTRY *FGETACTIVEWIN)(void);
  typedef HWND    (APIENTRY *FGETLASTACTIVEPOPUP)(HWND);
  typedef HWINSTA (APIENTRY *FGETPROCWINSTATION)(void);
  typedef bool    (APIENTRY *FGETUSROBJINFO)(HANDLE, int, PVOID, DWORD, LPDWORD);

  static FMESSAGEBOX          pfnMessageBox               = NULL;
  static FGETACTIVEWIN        pfnGetActiveWindow          = NULL;
  static FGETLASTACTIVEPOPUP  pfnGetLastActivePopup       = NULL;
  static FGETPROCWINSTATION   pfnGetProcessWindowStation  = NULL;
  static FGETUSROBJINFO       pfnGetUserObjectInformation = NULL;
  #ifdef _UNICODE
    #define FN_MESSAGEBOX "MessageBoxW"
    #define FN_GETUSROBJINFO "GetUserObjectInformationW"
  #else  //SBCS
    #define FN_MESSAGEBOX "MessageBoxA"
    #define FN_GETUSROBJINFO "GetUserObjectInformationA"
  #endif

  HWND    hWndParent = NULL;
  bool    bNonInteractive = false;
  HWINSTA hwinsta;
  USEROBJECTFLAGS uof;
  DWORD nDummy;

  if (NULL == pfnMessageBox)
    {
    HMODULE hlib = LoadLibrary(_T("user32.dll"));

    if (NULL == hlib ||
        NULL == (pfnMessageBox = (FMESSAGEBOX) GetProcAddress(hlib, FN_MESSAGEBOX)))
      return 0; //Could not find the required function

    pfnGetActiveWindow = (FGETACTIVEWIN)
      GetProcAddress(hlib, "GetActiveWindow");

    pfnGetLastActivePopup = (FGETLASTACTIVEPOPUP)
      GetProcAddress(hlib, "GetLastActivePopup");

    #if (_MSC_VER < 1300) //Less than Visual C++ .Net 2002, 32-bit, version 7.0
      if (_osplatform == 0) //Initialize OS version Id
        {
        OSVERSIONINFOA osvi;
        osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);
        (void)GetVersionExA(&osvi);
        _osplatform = osvi.dwPlatformId;
        }
    #endif

    if (_osplatform == VER_PLATFORM_WIN32_NT)
      {
      pfnGetUserObjectInformation = (FGETUSROBJINFO)
        GetProcAddress(hlib, FN_GETUSROBJINFO);

      if (pfnGetUserObjectInformation)
        pfnGetProcessWindowStation = (FGETPROCWINSTATION)
        GetProcAddress(hlib, "GetProcessWindowStation");
      }
    }

  if (pfnGetProcessWindowStation)
    {
    /*If the current process isn't attached to a visible WindowStation, (e.g.
      non-interactive service), then we need to set the MB_SERVICE_NOTIFICATION
      flag, else the message box will be invisible, hanging the program.
      This check only applies to Windows NT-based systems (for which we retrieved
      the address of GetProcessWindowStation above).
    */
    if( NULL == (hwinsta = (*pfnGetProcessWindowStation)()) ||
            !(*pfnGetUserObjectInformation)(hwinsta,
                                             UOI_FLAGS,
                                             &uof,
                                             sizeof(uof),
                                             &nDummy)       ||
            (uof.dwFlags & WSF_VISIBLE) == 0)
      {
      bNonInteractive = true;
      }
    }

  if (bNonInteractive)
    {
    if (_winmajor >= 4)
      uType |= MB_SERVICE_NOTIFICATION;
    else
      uType |= MB_SERVICE_NOTIFICATION_NT3X;
    }
  else
    {
    if (pfnGetActiveWindow)
      hWndParent = (*pfnGetActiveWindow)();

    if (hWndParent != NULL && pfnGetLastActivePopup)
      hWndParent = (*pfnGetLastActivePopup)(hWndParent);
    }

  return (*pfnMessageBox)(hWndParent, lpText, lpCaption, uType);
  }

//-----------------------------------------------------------------------------
/*Create debugging report in a message box, allowing user to choose between
  aborting the procedure, retrying the action or ignoring the message.

  Requires debug versions of C run-time libraries and Microsoft visual Studio
  .Net 2003 v7.1, or Microsoft Visual C/C++ v6.0. It is not required for
  Microsoft Visual C/C++ 2005 v8.0 or greater.

  Returns: 0 or 1 if the user selects Retry or exits with 3 if user selects
  Abort.

  Note: Microsoft Windows specific (Win32).
 */
  int tCrtMessageWindow(int nRptType,         //[in] report type
                        LPCTSTR szFile,       //[in] file name
                        LPCTSTR szLine,       //[in] line number
                        LPCTSTR szModule,     //[in] module name
                        LPCTSTR szUserMessage //[in] user message
                       )
  {
  int     nCode;
  LPTSTR  szShortProgName;
  LPTSTR  szShortModuleName;
  TCHAR   szExeName[MAX_PATH + 1];
  TCHAR   szOutMessage[MAX_MSG];

  #pragma warning(disable : 4127) //warning C4127: conditional expression is constant
    _ASSERTE(szUserMessage != NULL);
  #pragma warning(default : 4127)
  /*Shorten program name */
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

  if(_sntprintf(szOutMessage,
                MAX_MSG,
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
                _CRT_ASSERT != nRptType ? _T("") :
                  _T("\n\nFor information on how your program can cause an assertion\nfailure, see the Visual C++ documentation on asserts.")
               ) < 0 )
    _tcscpy(szOutMessage, tTOOLONGMSG);

  /* Report the warning/error */
  nCode = tMessageBox(szOutMessage,
                           _T("Unicode Replacement Debug Library"),
                            MB_TASKMODAL       |
                            MB_ICONHAND        |
                            MB_ABORTRETRYIGNORE|
                            MB_SETFOREGROUND);

  /*Abort: abort the program */
  if (IDABORT == nCode)
    {
    raise(SIGABRT); /* raise abort signal */
    /*We usually won't get here, but it's possible that SIGABRT was ignored.
      So exit the program anyway. */
    _exit(3);
    }

  /*Retry: return 1 to call the debugger */
  if (IDRETRY == nCode)
    return 1;

  /*Ignore: continue execution */
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
      tCrtDbgReport(_CRT_WARN, NULL, 0, NULL,
                    _T("Another example with %s\n"), szUnicode);
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
    /*use only 'safe' functions -- must not assert in here! */
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
        //#include "KStrConvert.h" TODO: Convert szOutMessage to SBCS
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
    return retval; //If 0, user selected to ignore assertion; 1 is retry
    }

  if (_CRT_ASSERT == nRptType)
    _CrtInterlockedDecrement(&_crtAssertBusy);

  return 0; /*no other errors found */
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
