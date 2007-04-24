Attribute VB_Name = "KWinShell32"
'$Workfile: S:\_SrcPool\VB\KWinShell32.bas$: implementation file
'$Revision: 1$ $Date: 2007-04-24 15:24:30$
'$Author: Darko Kolakovic$
'
'MS Windows shell32 DLL
'2004-06-11

Public Declare Function Shell_NotifyIcon Lib "shell32.dll" Alias "Shell_NotifyIconA" (ByVal dwMessage As Long, lpData As NOTIFYICONDATA) As Long
Public Declare Function SHBrowseForFolder Lib "shell32" (lpbi As BROWSEINFO) As Long
Public Declare Function SHGetPathFromIDList Lib "shell32" (ByVal pidList As Long, ByVal lpBuffer As String) As Long

'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log: 
' 1    Biblioteka1.0         2007-04-24 15:24:30  Darko Kolakovic 
'$

