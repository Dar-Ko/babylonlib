Attribute VB_Name = "KStringExt"
'$Workfile: KStringExt.bas$: implementation file
'$Revision: 4$ $Date: 2007-04-24 15:25:37$
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

Private Declare Sub CopyMem Lib "kernel32" Alias _
  "RtlMoveMemory" (pTo As Any, uFrom As Any, ByVal lSize As Long)
Private Declare Function lstrlenW Lib "kernel32" (ByVal lpString As Long) As Long
Private Declare Function lstrlenA Lib "kernel32" (ByVal lpString As Long) As Long
Private Declare Function lstrcpyW Lib "kernel32" (lpString1 As Byte, _
                                                  ByVal lpString2 As Long) As Long

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
'-------------------------------------------------------------------------------
'Find the next token in a string. The set of characters in strDelimiter specifies
'possible delimiters of the token to be found in strSource on the current call.
'
'Parameters
' strSource      [in/out] String containing token or tokens.
' strDelimiter   [in] Set of delimiter characters.
'
'Returns a token if found and remaining part of the strSource after the token.
Function strToken(ByRef strSource As String, _
                  ByVal strDelimiter As String) As String

  Dim iPos As Integer
  Dim sToken As String
  iPos = 1

  Do
    If Mid$(strSource, iPos, 1) = strDelimiter Then
      sToken = Mid$(strSource, 1, iPos)
      strSource = Mid$(strSource, iPos + 1, Len(strSource))
      strToken = sToken
      Exit Function
    End If
    iPos = iPos + 1
  Loop

End Function
'------------------------------------------------------------------------------
'Replaces all occurrences of strSearch in the source string.
'Parameters:
'   strSource       string to search
'   strSearch       string to search for
'   strReplacement  replacment string
'
'Returns string with replaced text
Public Function StrReplace(ByVal strSource, _
                           ByVal strSearch, _
                           ByVal strReplacement)
  Do Until InStr(1, strSource, strSearch) = 0
    strSource = Left(strSource, InStr(1, strSource, strSearch) - 1) + _
                strReplacement + _
                Mid(strSource, InStr(1, strSource, strSearch) + Len(strSearch))
  Loop
  StrReplace = strSource
End Function
'------------------------------------------------------------------------------
'Converts C-style pointer to SBSC character string to String
Public Function PointerToStringA(ByVal pStringA As Long) As String
   Dim Buffer() As Byte
   Dim nLen As Long

   If pStringA Then
      nLen = lstrlenA(ByVal pStringA)
      If nLen Then
         ReDim Buffer(0 To (nLen - 1)) As Byte
         CopyMem Buffer(0), ByVal pStringA, nLen
         PointerToStringA = StrConv(Buffer, vbUnicode)
      End If
   End If
End Function
'------------------------------------------------------------------------------
'Converts C-style pointer to wide character string to String
Public Function PointerToStringW(ByVal pStringW As Long) As String
   Dim Buffer() As Byte
   Dim nLen As Long

   If pStringW Then
      nLen = lstrlenW(pStringW) * 2
      If nLen Then
         ReDim Buffer(0 To (nLen - 1)) As Byte
         CopyMem Buffer(0), ByVal pStringW, nLen
         PointerToStringW = Buffer
      End If
   End If
End Function
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
'-------------------------------------------------------------------------------
'Returns string without trailing spaces and directory delimiter ('\') characters.
Public Function StrTrimSlash(ByVal strPath As String) As String

  'Trim and remove any trailing slash
  strPath = Trim$(strPath)

  If Right$(strPath, 1) = "\" Then
    StrTrimSlash = Left$(strPath, Len(strPath) - 1)
  Else
    StrTrimSlash = strPath
  End If

End Function
'//////////////////////////////////////////////////////////////////////////////
'******************************************************************************
'$Log:
' 2    Biblioteka1.1         2007-04-18 16:05:20  Darko Kolakovic Constant
' 1    Biblioteka1.0         2007-04-13 09:23:58  Darko Kolakovic
'$
'******************************************************************************

