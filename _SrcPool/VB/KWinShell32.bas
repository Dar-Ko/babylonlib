Attribute VB_Name = "KWinShell32"
'$Workfile: KWinShell32.bas$: implementation file
'$Revision: 2$ $Date: 2007-05-08 10:14:48$
'$Author: Darko Kolakovic$
'
'MS Windows shell32 DLL
'2004-06-11

'-------------------------------------------------------------------------------
'ShellAPI.h

Public Const NIM_ADD = &H0     'add icon to system tray
Public Const NIM_MODIFY = &H1  'modify icon in system tray
Public Const NIM_DELETE = &H2  'delete icon in system tray

Public Const NIF_MESSAGE = &H1 'windows message about event is sent
Public Const NIF_ICON = &H2    'icon is displayed
Public Const NIF_TIP = &H4     'tooltip availibility

Public Type NOTIFYICONDATA
  cbSize           As Long 'size of the structure
  hwnd             As Long 'handle of the window
  uId              As Long 'unique ID for the icon
  uFlags           As Long 'flags
  uCallBackMessage As Long '
  hicon            As Long 'memory location of the icon
  szTip     As String * 64 'tooltip of 64 characters maximum
End Type

Public Declare Function SHBrowseForFolder Lib "shell32" (lpbi As BROWSEINFO) As Long
Public Declare Function Shell_NotifyIcon Lib "shell32.dll" Alias "Shell_NotifyIconA" (ByVal dwMessage As Long, lpData As NOTIFYICONDATA) As Long
Public Declare Function ShellExecute Lib "shell32.dll" Alias "ShellExecuteA"   (ByVal hwnd As Long, ByVal lpOperation As String, ByVal lpFile As String,    ByVal lpParameters As String, ByVal lpDirectory As String,    ByVal nShowCmd As Long) As Long
Public Declare Function SHGetPathFromIDList Lib "shell32" (ByVal pidList As Long, ByVal lpBuffer As String) As Long


'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log:
' 1    Biblioteka1.0         2007-04-24 15:24:30  Darko Kolakovic
'$

