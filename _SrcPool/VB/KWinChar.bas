Attribute VB_Name = "KWinChar"
'$Workfile: KWinChar.bas$: implementation file
'$Revision: 1.2 $ $Date: 2008/05/23 21:49:10 $
'$Author: ddarko $
'
'Microsoft Windows Data types [Data Structures] WChar.h
'2003-05-29
Option Explicit

'-------------------------------------------------------------------------------
' Microsoft Windows Data types [Data Structures] WChar.h

Public Type WCHAR
  m_Byte0 As Byte
  m_Byte1 As Byte
End Type

'Pointer to string (SBCS)
Public Type LPSTR
  Ptr As Long
End Type
'Pointer to wide-character string
Public Type LPWSTR
  Ptr As Long
End Type

'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log: KWinChar.bas,v $
'Revision 1.2  2008/05/23 21:49:10  ddarko
'new Windows types
'
'*******************************************************************************

