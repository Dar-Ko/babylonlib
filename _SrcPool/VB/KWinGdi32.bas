Attribute VB_Name = "KWinGdi32"
'$Workfile: S:\_SrcPool\VB\KWinGdi32.bas$: implementation file
'$Revision: 1$ $Date: 2007-05-08 10:12:40$
'$Author: Darko Kolakovic$
'
'MS Windows gdi32 DLL
'2005-01-04
Option Explicit

Public Declare Function CreatePen Lib "gdi32" (ByVal nPenStyle As Long, ByVal nWidth As Long, ByVal crColor As Long) As Long
Public Declare Function CreateSolidBrush Lib "gdi32" (ByVal crColor As Long) As Long
Public Declare Function GetPixel Lib "gdi32"   (ByVal hdc As Long, ByVal X As Long, ByVal Y As Long) As Long
Public Declare Function Polygon Lib "gdi32" (ByVal hdc As Long, lpPoint As POINTAPI, ByVal nCount As Long) As Long
Public Declare Function SelectObject Lib "gdi32" (ByVal hdc As Long, ByVal hObject As Long) As Long

'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log: 
' 1    Biblioteka1.0         2007-05-08 10:12:40  Darko Kolakovic 
'$
'*******************************************************************************

