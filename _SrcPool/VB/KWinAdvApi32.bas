Attribute VB_Name = "KWinAdvApi32"
'$Workfile: KWinAdvApi32.bas$: implementation file
'$Revision: 3$ $Date: 2007-05-08 10:14:46$
'$Author: Darko Kolakovic$
'
'MS Windows advapi32 DLL
'2004-06-11
Option Explicit

Public Declare Function AdjustTokenPrivileges Lib "advapi32" (ByVal TokenHandle As Long, ByVal DisableAllPrivileges As Long, NewState As TOKEN_PRIVILEGES, ByVal BufferLength As Long, PreviousState As TOKEN_PRIVILEGES, ReturnLength As Long) As Long
Public Declare Function DeregisterEventSource Lib "advapi32.dll" (ByVal hEventLog As Long) As Long
Public Declare Function GetUserName Lib "advapi32.dll" Alias "GetUserNameA"   (ByVal lpBuffer As String, nSize As Long) As Long
Public Declare Function LookupPrivilegeValue Lib "advapi32" Alias "LookupPrivilegeValueA" (ByVal lpSystemName As String, ByVal lpName As String, lpLuid As LUID) As Long
Public Declare Function OpenProcessToken Lib "advapi32" (ByVal ProcessHandle As Long, ByVal DesiredAccess As Long, TokenHandle As Long) As Long
Public Declare Function RegisterEventSource Lib "advapi32.dll" Alias "RegisterEventSourceA" (ByVal lpUNCServerName As String, ByVal lpSourceName As String) As Long
Public Declare Function ReportEvent Lib "advapi32.dll" Alias "ReportEventA" (ByVal hEventLog As Long, ByVal wType As Integer, ByVal wCategory As Integer, ByVal dwEventID As Long, ByVal lpUserSid As Any, ByVal wNumStrings As Integer, ByVal dwDataSize As Long, plpStrings As Long, lpRawData As Any) As Boolean


'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log:
' 1  Biblioteka1.0  2007-04-20 14:02:59 Darko Kolakovic
'$
'*******************************************************************************
