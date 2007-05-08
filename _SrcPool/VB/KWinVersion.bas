Attribute VB_Name = "KWinVersion"
'$Workfile: S:\_SrcPool\VB\KWinVersion.bas$: implementation file
'$Revision: 1$ $Date: 2007-05-08 10:12:41$
'$Author: Darko Kolakovic$
'
'MS Windows version DLL
'2005-01-04
Option Explicit

Public Declare Function GetFileVersionInfo Lib "version.dll" Alias "GetFileVersionInfoA"     (ByVal lptstrFilename As String, ByVal dwHandle As Long, ByVal dwLen As Long,     lpData As Any) As Long
Public Declare Function GetFileVersionInfoSize Lib "version.dll" Alias "GetFileVersionInfoSizeA"     (ByVal lptstrFilename As String, lpdwHandle As Long) As Long
Public Declare Function VerQueryValue Lib "version.dll" Alias "VerQueryValueA"     (pBlock As Any, ByVal lpSubBlock As String, lplpBuffer As Long,     puLen As Long) As Long

'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log: 
' 1    Biblioteka1.0         2007-05-08 10:12:41  Darko Kolakovic 
'$
'*******************************************************************************

