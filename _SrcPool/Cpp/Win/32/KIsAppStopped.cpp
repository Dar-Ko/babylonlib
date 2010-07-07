/*$RCSfile: KIsAppStopped.cpp,v $: implementation file
  $Revision: 1.3 $ $Date: 2010/07/07 19:58:09 $
  $Author: ddarko $

  Checks if application is responsive.
  Copyright: (c)1999 Ashot Oganesyan K, SmartLine, Inc
  mailto:ashot@aha.ru,
 */

#include "stdafx.h"
#include <winuser.h> //IsHungAppWindow() Windows XP (SP1) header

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------
/*Validates if a specified application is responsive.
  An application is considered to be not responding if it is not waiting for input,
  is not in startup processing and has not called PeekMessage within the internal
  timeout period of 5 seconds.

  Returns: true if application is stopped, otherwise returns false. If specified
  handle is not a handle of a window, error is set to ERROR_INVALID_PARAMETER and
  true is returned. To obtain error code, call GetLastError().

  Note: Microsoft Windows specific (Win).

  See also: IsHungAppWindow(),
  {html: <a ref="http://support.microsoft.com/kb/q231844/">
  MSDN; Q231844 HOWTO: Detect If an Application Has Stopped Responding</a>},
  How the Windows Task Manager determines when the application is not responding?
  by Ashot Oganesyan.

*/
bool IsAppStopped(HWND hWnd //[in] handle to the window to be tested.
                  )
{
TRACE1(_T("IsAppStopped(hWnd = %08X)\n"), hWnd);
if (!IsWindow(hWnd))
  return SetLastError(ERROR_INVALID_PARAMETER), true; //Abtop: Alekcahdp Fedopob

/*Microsoft doesn't provide the required exports symbols in the User32.lib for
  systemes before Windows XP Service Pack 1, so we loading methods
  dynamically.
 */
HMODULE hUser32 = GetModuleHandle(_T("user32.dll"));
_ASSERTE(hUser32 != NULL);
if (hUser32 != NULL)
  {
  //User32!IsHungAppWindow (WinNT specific)
  BOOL (WINAPI* pfIsHungAppWindow)(HWND);
  *(FARPROC *)& pfIsHungAppWindow = GetProcAddress(hUser32,
                                                  "IsHungAppWindow");
  if(pfIsHungAppWindow != NULL)
    {
    return (pfIsHungAppWindow(hWnd) == TRUE);
    }
  else
    {
    //User32!IsHungThread (Win95/98 specific)
    BOOL (WINAPI* pfIsHungThread)(DWORD);
    *(FARPROC *)& pfIsHungThread = GetProcAddress(hUser32,
                                                  "IsHungThread");
    if (pfIsHungThread != NULL)
      {
      return (pfIsHungThread(GetWindowThreadProcessId(hWnd, NULL)) == TRUE);
      }
    else
      {
      //None of requested functions is supported, so try the method described in
      //MSDN; Q231844

      /*If SendMessageTimeout function fails or times out, it returns value of zero.
        To get extended error information, call GetLastError.
        If GetLastError returns zero, then the function timed out.
        SendMessageTimeout does not provide information about individual windows
        timing out if HWND_BROADCAST is used.

        If the timeout period elapses, that indicates that either the application in
        question is too busy to check messages or it's hung. Testing showed that
        with timeout period of 5s or more, results are more or less reliable, but
        then the caller application is not responsive until the time period expires.
        The period of 5000ms is chosen per Microsoft's recomendation. Responsiveness
        depends of the overall load of the system.
       */
      DWORD_PTR dwResult;
      return (SendMessageTimeout(hWnd,
                                 WM_NULL,
                                 0, 0,
                                 SMTO_ABORTIFHUNG |
                                 SMTO_BLOCK,
                                 5000,  //time-out period [ms]
                                  &dwResult) == 0);
      }
    }
  }
return true; //Default result
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: KIsAppStopped.cpp,v $
 * Revision 1.3  2010/07/07 19:58:09  ddarko
 * TRACE improvment
 *
 * Revision 1.2  2010/07/07 18:24:26  ddarko
 * *** empty log message ***
 *
 * Revision 1.1  2010/07/07 18:20:41  ddarko
 * Created
 *
 *****************************************************************************/

/*
http://msdn.microsoft.com/en-us/library/ms633526%28VS.85%29.aspx

IsHungAppWindow Function

[This function is not intended for general use. It may be altered or unavailable
 in subsequent versions of Windows.]

Determines whether the system considers that a specified application is not
responding.
An application is considered to be not responding if it is not waiting for input,
is not in startup processing, and has not called PeekMessage within the internal
timeout period of 5 seconds.

Syntax
    BOOL WINAPI IsHungAppWindow(__in  HWND hWnd);

Parameters
    hWnd [in]    HWND    A handle to the window to be tested.

Return Value
    BOOL  The return value is TRUE if the window stops responding; otherwise,
          it is FALSE. Ghost windows always return TRUE.

Remarks
The Windows timeout criteria of 5 seconds is subject to change.

This function was not included in the SDK headers and libraries until Windows XP
Service Pack 1 (SP1) and Windows Server 2003. If you do not have a header file
and import library for this function, you can call the function using LoadLibrary
and GetProcAddress.

Requirements

Minimum supported client  Windows 2000 Professional
Minimum supported server  Windows 2000 Server

Header
  Winuser.h (include Windows.h)

Library
  User32.lib

DLL
  User32.dll

See Also
  Undocumented conversions between a window handle HWND and the ghost window HWND:
  HWND WINAPI GhostWindowFromHungWindow(HWND hwnd);
  HWND WINAPI HungWindowFromGhostWindow(HWND hwnd);
 */

//-----------------------------------------------------------------------------
/*Trick 2: How the Windows Task Manager determines when the application is
  not responding?

A couple of weeks ago I've been writing some functions for Remote Task Manager
and when I've compared RTM with the Windows NT Task Manager I saw that the standard
task manager displays the status of the applications (running or not responding).
I've thought the standard task manager sends (through the SendMessageTimeout
function) a message to the main application window and if the function fails or
time out – the application has the status not responding otherwise running status.
But in a few minutes I found a much better solution.

The trick here is that we need to call an undocumented function from the User32.dll.
This function presents in the Windows 95/98 as well as in the Windows NT/2000 but
with different names, IsHungAppWindow in NT systems and IsHungThread in 9x systems.
I'll try to describe the prototypes for them:
BOOL IsHungAppWindow (
HWND hWnd, // handle to main app's window
);

and:
BOOL IsHungThread (
DWORD dwThreadId, // The thread's identifier of the main app's window
);

Unfortunately, Microsoft doesn't provide us with the exports symbols in the
User32.lib for these functions, so we should load them dynamically using
the GetProcAddress and GetModuleHandle functions:
typedef BOOL (WINAPI *PROCISHUNGAPPWINDOW) (HWND);
typedef BOOL (WINAPI *PROCISHUNGTHREAD) (DWORD);

PROCISHUNGAPPWINDOW IsHungAppWindow;
PROCISHUNGTHREAD IsHungThread;

HMODULE hUser32 = GetModuleHandle("user32");

IsHungAppWindow =   (PROCISHUNGAPPWINDOW)
GetProcAddress(hUser32,"IsHungAppWindow");

IsHungThread =  (PROCISHUNGTHREAD)
GetProcAddress(hUser32,"IsHungThread");

Sincerely yours, Ashot Oganesyan.

// ishung.cpp (Windows 95/98/NT/2000)
// This example will show you how you can obtain the current status
// of the application.
//
// (c)1999 Ashot Oganesyan K, SmartLine, Inc
// mailto:ashot@aha.ru, http://www.protect-me.com, http://www.codepile.com

#include <windows.h>
#include <stdio.h>


// User32!IsHungAppWindow (NT specific!)
//
// The function retrieves the status (running or not responding) of the
// specified application
//
// BOOL IsHungAppWindow(
//   HWND hWnd,        // handle to main app's window
// );
typedef BOOL    (WINAPI *PROCISHUNGAPPWINDOW)(HWND);


// User32!IsHungThread (95/98 specific!)
//
// The function retrieves the status (running or not responding) of the
// specified thread
//
// BOOL IsHungThread(
//   DWORD dwThreadId, // The identifier of the main app's window thread
// );
typedef BOOL    (WINAPI *PROCISHUNGTHREAD)(DWORD);

PROCISHUNGAPPWINDOW         IsHungAppWindow;
PROCISHUNGTHREAD            IsHungThread;

void main(int argc, char* argv[])
{
if (argc<2)
  {
  printf("Usage:\n\nishung.exe hWnd\n");
  return;
  }

HWND hWnd;
sscanf(argv[1],"%lx",&hWnd);

if (!IsWindow(hWnd))
  {
  printf("Incorrect window handle\n");
  return;
  }

HMODULE hUser32 = GetModuleHandle("user32");
if (!hUser32)
  return;

IsHungAppWindow = (PROCISHUNGAPPWINDOW)
                   GetProcAddress( hUser32,
                                   "IsHungAppWindow" );

IsHungThread = (PROCISHUNGTHREAD) GetProcAddress( hUser32,
                                                 "IsHungThread" );

if (!IsHungAppWindow && !IsHungThread)
  return;

OSVERSIONINFO osver;
osver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
if (!GetVersionEx(&osver))
  return;

BOOL IsHung;
if (osver.dwPlatformId&VER_PLATFORM_WIN32_NT)
  IsHung = IsHungAppWindow(hWnd);
else
  IsHung = IsHungThread(GetWindowThreadProcessId(hWnd,NULL));

if (IsHung)
  printf("Not Responding\n");
else
  printf("Running\n");
}

*/
