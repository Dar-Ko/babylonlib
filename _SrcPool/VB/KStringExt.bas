Attribute VB_Name = "StringExt"
'$Workfile: StringExt.bas,v $: implementation file
'$Revision: 1.2 $ $Date: 2007/03/29 22:35:11 $
'$Author: dkolakovic $
'
'Text manipulation helpers
'babylonlib@sourceforge.net
'2002-10-14

'Note: JScript does not support ByRef parameters of any type, so if you plan to
'write components that will support JScript, you should not use ByRef parameters
'at all. VBScript does not impose this restriction.
'ByRef procedures cause more overhead during cross-process marshaling, because
'COM must marshal the value both to and from the object.
'ByVal parameters require only one-way marshaling.

'------------------------------------------------------------------------------
'Strip white characters from the end of SBCS string
Public Function TrimRight(strText As String) As String
  Dim strResult As String

  strResult = strText
  nLen = Len(strText)
  Chrr = Asc(Right$(strResult, 1))
  If Len(strText) > 0 Then
    Do While Asc(Right$(strResult, 1)) <= ASCII_SP 'Less or equal to SPACE
      text = Left$(strResult, Len(strResult) - 1)
    Loop
    TrimRight = strResult
  End If
End Function
'------------------------------------------------------------------------------
'Strip white characters from the beginning of SBCS string
Public Function TrimLeft(strText As String) As String
  Dim text As String
  If Len(strText) > 0 Then
    strResult = strText
    Do While Asc(strResult) <= ASCII_SP 'Less or equal to SPACE
      strResult = Mid$(strResult, 2)
    Loop
    TrimLeft = strResult
  End If
End Function
'------------------------------------------------------------------------------
'Strip white characters from the beginning and the end of SBCS string.
Public Function TrimText(strText As String) As String
  TrimBoth = TrimLeft(TrimRight(strText))
End Function
'------------------------------------------------------------------------------
'Returns True if the string is Unicode text with Latin characters
Public Function IsUnicode(strText As String) As Boolean
  Dim i As Long
  Dim lSize As Long 'text lenght
  Dim arrText() As Byte 'text as byte array

  If LenB(strText) Then
    arrText = strText
    lSize = UBound(arrText)
    For i = 1 To lSize Step 2 'Check every 2nd byte
      If (arrText(i) > 0) Then
        IsUnicode = True 'Return OK
        Exit Function
      End If
    Next
  End If
End Function

'//////////////////////////////////////////////////////////////////////////////
'******************************************************************************
'$Log: StringExt.bas,v $
'Revision 1.2  2007/03/29 22:35:11  dkolakovic
'Printer Status
'
'Revision 1.1  2007/03/20 13:22:08  dkolakovic
'Created
'
'******************************************************************************


