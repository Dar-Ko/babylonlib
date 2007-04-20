Attribute VB_Name = "KStringExt"
'$Workfile: KStringExt.bas$: implementation file
'$Revision: 3$ $Date: 2007-04-20 14:03:23$
'$Author: Darko Kolakovic$
'
'Text manipulation helpers
'2002-10-14

Option Explicit
                   
'Note: JScript does not support ByRef parameters of any type, so if you plan to
'write components that will support JScript, you should not use ByRef parameters
'at all. VBScript does not impose this restriction.
'ByRef procedures cause more overhead during cross-process marshaling, because
'COM must marshal the value both to and from the object.
'ByVal parameters require only one-way marshaling.

Public Const ASCII_SP As Integer = 32
'------------------------------------------------------------------------------
'Strip white characters from the end of SBCS string
Public Function TrimRight(strText As String) As String
  Dim strResult As String
  If Len(strText) > 0 Then
    strResult = strText
    Do While Asc(Right$(strResult, 1)) <= ASCII_SP 'Less or equal to SPACE
      strResult = Left$(strResult, Len(strResult) - 1)
    Loop
    TrimRight = strResult
  End If
End Function
'------------------------------------------------------------------------------
'Strip white characters from the beginning of SBCS string
Public Function TrimLeft(strText As String) As String
  Dim strResult As String
  If Len(strText) > 0 Then
    strResult = strText
    Do While Asc(strResult) <= ASCII_SP 'Less or equal to SPACE
      strResult = Mid$(strResult, 2)
    Loop
    TrimLeft = strResult
  End If
End Function
'------------------------------------------------------------------------------
'Strip white characters from the beginning and the end of SBCS string
Public Function TrimBoth(strText As String) As String
    TrimBoth = TrimLeft(TrimRight(strText))
End Function
'------------------------------------------------------------------------------
'Converts number of bytes to a string
Public Function BytesToString(pByteArray As Byte, _
                              lByteArraySize As Long) As String
  Dim strTemp As String
  Dim lLength As Long

  'Create a storage
  strTemp = String(lByteArraySize + 1, 0)
  'Copy byte array to the storage
  CopyMemory ByVal strTemp, pByteArray, lByteArraySize

  lLength = InStr(strTemp, Chr$(0)) - 1
  BytesToString = Left$(strTemp, lLength) 'Return the string
End Function
'------------------------------------------------------------------------------
'Public Function PointerToStringA(ByVal lpStringA As Long) As String
'   Dim Buffer() As Byte
'   Dim nLen As Long

   'If lpStringA Then
   '   nLen = lstrlenA(ByVal lpStringA)
   '   If nLen Then
   '      ReDim Buffer(0 To (nLen - 1)) As Byte
   '      CopyMemory Buffer(0), ByVal lpStringA, nLen
   '      PointerToStringA = StrConv(Buffer, vbUnicode)
   '   End If
   'End If
'End Function
'------------------------------------------------------------------------------
'Public Function PointerToStringW(ByVal lpStringW As Long) As String
'   Dim Buffer() As Byte
'   Dim nLen As Long

'   If lpStringW Then
'      nLen = lstrlenW(lpStringW) * 2
'      If nLen Then
'         ReDim Buffer(0 To (nLen - 1)) As Byte
'         CopyMemory Buffer(0), ByVal lpStringW, nLen
'         PointerToStringW = Buffer
'      End If
'   End If
'End Function
'------------------------------------------------------------------------------
'Returns True if the string is Unicode
Public Function IsUnicode(strText As String) As Boolean
   Dim i As Long
   Dim lLen As Long
   Dim Map() As Byte

   If LenB(strText) Then
      Map = strText
      lLen = UBound(Map)
      For i = 1 To lLen Step 2
         If (Map(i) > 0) Then
            IsUnicode = True 'Return OK
            Exit Function
         End If
      Next
   End If
End Function

'//////////////////////////////////////////////////////////////////////////////
'******************************************************************************
'$Log:
' 2    Biblioteka1.1         2007-04-18 16:05:20  Darko Kolakovic Constant
' 1    Biblioteka1.0         2007-04-13 09:23:58  Darko Kolakovic
'$
'******************************************************************************

