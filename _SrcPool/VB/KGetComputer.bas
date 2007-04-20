Attribute VB_Name = "KGetComputer"
'$Workfile: S:\_SrcPool\VB\KGetComputer.bas$: implementation file
'$Revision: 1$ $Date: 2007-04-20 14:02:56$
'$Author: Darko Kolakovic$
'
'MS Windows computer name
'2004-06-11
Option Explicit
'-------------------------------------------------------------------------------
'Returns the computer name
Public Function ComputerName() As String
  Dim lLength As Long
  Dim lSize As Long
  Dim szTemp As String
  lLength = MAX_COMPUTERNAME_LENGTH + 1 'Allowed size and terminating null
  szTemp = String(lLength, 0)
  
  lSize = GetComputerName(szTemp, lLength) 'Get the computer Name
  If lSize <> 0 Then
    ComputerName = Mid(szTemp, 1, lLength)
  Else
    ComputerName = szTemp 'Return empty string
  End If
End Function
'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log: 
' 1    Biblioteka1.0         2007-04-20 14:02:56  Darko Kolakovic 
'$
'*******************************************************************************

