Attribute VB_Name = "KWinUser32"
'$Workfile: KWinUser32.bas$: implementation file
'$Revision: 4$ $Date: 2007-05-08 10:14:49$
'$Author: Darko Kolakovic$
'
'MS Windows user32 DLL
'2004-06-11
Option Explicit

Public Declare Function CallWindowProc Lib "user32" Alias "CallWindowProcA"   (ByVal lpPrevWndFunc As Long,    ByVal hwnd As Long, ByVal msg As Long,    ByVal wparam As Long, ByVal lparam As Long) As Long
Public Declare Function ClientToScreen Lib "user32"   (ByVal hwnd As Long, lpPoint As POINTAPI) As Long
Public Declare Function DrawIcon Lib "user32"   (ByVal hdc As Long, ByVal X As Long, ByVal Y As Long,    ByVal hicon As Long) As Long
Public Declare Function EnumChildWindows Lib "user32"   (ByVal hWndParent As Long, ByVal lpEnumFunc As Long, ByVal lparam As Long) As Long
Public Declare Function EnumThreadWindows Lib "user32"   (ByVal dwThreadId As Long, ByVal lpfn As Long, ByVal lparam As Long) As Long
Public Declare Function EnumWindows Lib "user32" (ByVal lpEnumFunc As Long, ByVal lparam As Long) As Long
Public Declare Function ExitWindowsEx Lib "user32" (ByVal dwOptions As Long, ByVal dwReserved As Long) As Long
Public Declare Function FindWindow Lib "user32" Alias "FindWindowA" (ByVal lpClassName As String, ByVal lpWindowName As String) As Long
Public Declare Function FindWindowEx Lib "user32" Alias "FindWindowExA" (ByVal hWnd1 As Long, ByVal hWnd2 As Long, ByVal lpsz1 As String, ByVal lpsz2 As String) As Long
Public Declare Function GetClassName Lib "user32" Alias "GetClassNameA" (ByVal hwnd As Long, ByVal lpClassName As String, ByVal nMaxCount As Long) As Long
Public Declare Function GetClientRect Lib "user32"   (ByVal hwnd As Long, lpRect As RECT) As Long
Public Declare Function GetCursorPos Lib "user32"   (lpPoint As POINTAPI) As Long
Public Declare Function GetDC Lib "user32"   (ByVal hwnd As Long) As Long
Public Declare Function GetForegroundWindow Lib "user32" () As Long
Public Declare Function GetKeyboardState Lib "user32" (ByRef lpKeyState As Byte) As Long
Public Declare Function GetKeyState Lib "user32" (ByVal nVirtKey As Long) As Integer
Public Declare Function GetMenu Lib "user32"   (ByVal hwnd As Long) As Long
Public Declare Function GetMenuItemCount Lib "user32"   (ByVal hmenu As Long) As Long
Public Declare Function GetMenuItemID Lib "user32"   (ByVal hmenu As Long, ByVal nPos As Long) As Long
Public Declare Function GetParent Lib "user32"   (ByVal hwnd As Long) As Long
Public Declare Function GetSubMenu Lib "user32"   (ByVal hmenu As Long, ByVal nPos As Long) As Long
Public Declare Function GetSystemMetrics Lib "user32" (ByVal nIndex As Long) As Long
Public Declare Function GetWindow Lib "user32"   (ByVal hwnd As Long, ByVal wCmd As Long) As Long
Public Declare Function GetWindowLong Lib "user32" Alias "GetWindowLongA"   (ByVal hwnd As Long, ByVal nIndex As Long) As Long
Public Declare Function GetWindowPlacement Lib "user32"   (ByVal hwnd As Long, lpwndpl As WINDOWPLACEMENT) As Long
Public Declare Function GetWindowRect Lib "user32"   (ByVal hwnd As Long, lpRect As RECT) As Long
Public Declare Function GetWindowText Lib "user32" Alias "GetWindowTextA" (ByVal hwnd As Long, ByVal lpString As String, ByVal cch As Long) As Long
Public Declare Function GetWindowTextLength Lib "user32" Alias "GetWindowTextLengthA"   (ByVal hwnd As Long) As Long
Public Declare Function GetWindowThreadProcessId Lib "user32" (ByVal hwnd As Long, lpdwProcessId As Long) As Long
Public Declare Function IsIconic Lib "user32" (ByVal hwnd As Long) As Long
Public Declare Function IsWindow Lib "user32" (ByVal hwnd As Long) As Long
Public Declare Function IsZoomed Lib "user32" (ByVal hwnd As Long) As Long
Public Declare Function KillTimer Lib "user32"   (ByVal hwnd As Long, ByVal id As Long) As Long
Public Declare Function LoadIcon Lib "user32" Alias "LoadIconA"   (ByVal hInstance As Long, ByVal lpIconName As String) As Long
Public Declare Function LoadStdIcon Lib "user32" Alias "LoadIconA"   (ByVal hInstance As Long, ByVal idIcon As Long) As Long
Public Declare Function MapVirtualKey Lib "user32" Alias "MapVirtualKeyA"   (ByVal wCode As Long, ByVal wMapType As Long) As Long
Public Declare Function MoveWindow Lib "user32"   (ByVal hwnd As Long, ByVal X As Long, ByVal Y As Long, ByVal nWidth As Long, ByVal nHeight As Long, ByVal bRepaint As Long) As Long
Public Declare Function PostMessage Lib "user32" Alias "PostMessageA"   (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wparam As Long, ByVal lparam As Long) As Long
Public Declare Function ReleaseDC Lib "user32"   (ByVal hwnd As Long, ByVal hdc As Long) As Long
Public Declare Function ScreenToClient Lib "user32"   (ByVal hwnd As Long, lpPoint As POINTAPI) As Long
Public Declare Function SendInput Lib "user32"   (ByVal cinput As Long, rginput() As InputType, ByVal cbInput As Long) As Long
Public Declare Function SendMessage Lib "user32" Alias "SendMessageA" (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wparam As Long, lparam As Any) As Long
Public Declare Function SendMessageCallback Lib "user32" Alias "SendMessageCallbackA"   (ByVal hwnd As Long, ByVal msg As Long, ByVal wparam As Long, ByVal lparam As Long,    ByVal lpResultCallBack As Long, ByRef dwData As Any) As Long
Public Declare Function SendMessageTimeout Lib "user32" Alias "SendMessageTimeoutA" (ByVal hwnd As Long, ByVal msg As Long, ByVal wparam As Long, ByVal lparam As Long, ByVal fuFlags As Long, ByVal uTimeout As Long, pdwResult As Long) As Long
Public Declare Function SetCursorPos Lib "user32"   (ByVal X As Long, ByVal Y As Long) As Long
Public Declare Function SetForegroundWindow Lib "user32"   (ByVal hwnd As Long) As Long
Public Declare Function SetTimer Lib "user32"   (ByVal hwnd As Long, ByVal id As Long, ByVal cmsec As Long, ByVal lpTimerFunc As Long) As Long
Public Declare Function SetWindowLong Lib "user32" Alias "SetWindowLongA"   (ByVal hwnd As Long, ByVal nIndex As Long, ByVal dwNewLong As Long) As Long
Public Declare Function SetWindowPlacement Lib "user32"   (ByVal hwnd As Long, lpwndpl As WINDOWPLACEMENT) As Long
Public Declare Function SetWindowPos Lib "user32" (ByVal hwnd As Long, ByVal hWndInsertAfter As Long, ByVal X As Long, ByVal Y As Long, ByVal cx As Long, ByVal cy As Long, ByVal wFlags As Long) As Long
Public Declare Function ShowWindow Lib "user32"   (ByVal hwnd As Long, ByVal nCmdShow As Long) As Long
Public Declare Function ToAscii Lib "user32"   (ByVal uVirtKey As Long, ByVal uScanCode As Long, ByRef lpKeyState As Byte,    ByRef lpChar As Integer, ByVal uFlags As Long) As Long
Public Declare Function TrackMouseEvent Lib "user32"   (tme As TrackMouseEventType) As Long
Public Declare Function VkKeyScan Lib "user32" Alias "VkKeyScanA"   (ByVal cchar As Byte) As Integer

'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log:
' 1    Biblioteka1.0         2007-04-20 14:03:01  Darko Kolakovic
'$
'*******************************************************************************

