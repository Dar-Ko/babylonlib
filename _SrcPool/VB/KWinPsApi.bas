Attribute VB_Name = "KWinPsApi"
'$Workfile: S:\_SrcPool\VB\KWinPsApi.bas$: implementation file
'$Revision: 1$ $Date: 2007-04-20 14:03:00$
'$Author: Darko Kolakovic$
'
'MS Windows psapi DLL
'2004-06-11
Option Explicit

Public Declare Function GetProcessMemoryInfo Lib "psapi.dll" (ByVal hProcess As Long, ppsmemCounters As PROCESS_MEMORY_COUNTERS, ByVal cb As Long) As Long

'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log: 
' 1    Biblioteka1.0         2007-04-20 14:03:00  Darko Kolakovic 
'$
'*******************************************************************************

