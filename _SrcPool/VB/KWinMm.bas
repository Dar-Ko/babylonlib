Attribute VB_Name = "KWinMm"
'$Workfile: S:\_SrcPool\VB\KWinMm.bas$: implementation file
'$Revision: 1$ $Date: 2007-05-08 10:12:41$
'$Author: Darko Kolakovic$
'
'MS Windows winmm DLL
'2005-01-04
Option Explicit

Public Declare Function PlaySound Lib "winmm.dll" Alias "PlaySoundA" (ByVal lpszName As String, ByVal hmodule As Long, ByVal dwFlags As Long) As Long
Public Declare Function PlaySoundRgb Lib "winmm.dll" Alias "PlaySoundA" (rgb As Any, ByVal hmodule As Long, ByVal dwFlags As Long) As Long
'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log: 
' 1    Biblioteka1.0         2007-05-08 10:12:41  Darko Kolakovic 
'$
'*******************************************************************************

