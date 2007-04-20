Attribute VB_Name = "KTerminateProcess"
'$Workfile: S:\_SrcPool\VB\KTerminateProcess.bas$: implementation file
'$Revision: 1$ $Date: 2007-04-20 14:02:58$
'$Author: Darko Kolakovic$
'
'Kill MS Windows process
'2004-06-11
Option Explicit
'-------------------------------------------------------------------------------
'Terminate running Windows process
Public Function TerminateProcess(ByVal hActiveWnd As Long, _
                                 ByVal lpdwActiveProcessId As Long) As Boolean
  Dim dwThreadId   As Long
  Dim lpdwProcessId  As Long
  TerminateProcess = False
  'Get the identifier of the thread that created the specified window
  'and, optionally, the identifier of the process that created the window.
  dwThreadId = GetWindowThreadProcessId(ByVal hActiveWnd, lpdwProcessId)
  
  'Cose the window owning the process
  If lpdwProcessId = lpdwActiveProcessId Then
    'Closing open Windows
    Call SendMessage(hWnd, WM_CLOSE, ByVal 0, ByVal 0)
    TerminateProcess = True
  End If
End Function
'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log: 
' 1    Biblioteka1.0         2007-04-20 14:02:58  Darko Kolakovic 
'$
'*******************************************************************************

