Attribute VB_Name = "KWinPsApi"
'$Workfile: KWinPsApi.bas$: implementation file
'$Revision: 2$ $Date: 2007-05-08 10:14:48$
'$Author: Darko Kolakovic$
'
'MS Windows psapi DLL
'2004-06-11
Option Explicit

Public Type MODULEINFO
  lpBaseOfDll As Long
  SizeOfImage As Long
  EntryPoint As Long
End Type


Public Declare Function EnumProcessModules Lib "psapi"   (ByVal hprocess As Long, ByRef rghmodule As Long,    ByVal cb As Long, ByRef cbNeeded As Long) As Long
Public Declare Function GetModuleFileNameEx Lib "psapi" Alias "GetModuleFileNameExA"   (ByVal hprocess As Long, ByVal hmodule As Long,    ByVal lpFileName As String, ByVal nSize As Long) As Long
Public Declare Function GetModuleInformation Lib "psapi"   (ByVal hprocess As Long, ByVal hmodule As Long,    lpModinfo As MODULEINFO, ByVal cb As Long) As Long
Public Declare Function GetProcessMemoryInfo Lib "psapi.dll" (ByVal hprocess As Long, ppsmemCounters As PROCESS_MEMORY_COUNTERS, ByVal cb As Long) As Long

'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log:
' 1    Biblioteka1.0         2007-04-20 14:03:00  Darko Kolakovic
'$
'*******************************************************************************

