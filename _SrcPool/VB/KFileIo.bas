Attribute VB_Name = "KFileIo"
'$Workfile: KFileIo.bas$: implementation file
'$Revision: 5$ $Date: 2007-05-08 10:13:40$
'$Author: Darko Kolakovic$
'
'File I/O/ handling helpers
'2003-12-29
Option Explicit
'-------------------------------------------------------------------------------
'Verifies if file eixts in the current folder.
'Returns True if file exist or False if not.
Public Function IsFileExisting(strFileName As String) As Boolean
  If Dir(strFileName) <> "" Then
    IsFileExisting = True
  Else
    IsFileExisting = False
  End If
End Function
'-------------------------------------------------------------------------------
'Verifies if the specified directory exists.
'
'Returns True if the directory exists, False otherwise
Public Function IsDirExisting(strPath As String) As Boolean
  If Dir(strPath, vbDirectory) <> "" Then
    IsDirExisting = True
  Else
    IsDirExisting = False
  End If
End Function
'-------------------------------------------------------------------------------
'Returns the directory portion of the fully qualified file path name. If file
'name is a directory, returns parent folder. If file name ends with directory
' delimiter '\', returns strFilename.
Public Function ExtractDir(strFileName As String) As String
  Dim iLength As Integer
  iLength = Len(strFileName)
  
  While iLength > 0
    'Get last directory delimiter
    If Mid(strFileName, iLength, 1) = "\" Then
      ExtractDir = Mid(strFileName, 1, iLength - 1)
      Exit Function
    End If
    iLength = iLength - 1 'Get next character
  Wend
End Function
'-------------------------------------------------------------------------------
'Returns the file name portion of the fully qualified file path name.
Public Function ExtractFilename(ByVal strFileName As String) As String
  If Len(strFileName) = 0 Then Exit Function 'Nothing to do
  Dim i As Integer
  Do
    i = InStr(strFileName, "\")
    If i = 0 Then Exit Do 'Break
    strFileName = Right(strFileName, Len(strFileName) - i%)
  Loop
  ExtractFilename = strFileName
End Function
'-------------------------------------------------------------------------------
'Creates an empty temporary file with unique name in the following form:
'   X:\TempDir\XXX12345.tmp
'in the directory designated as temporary directory by the TMP or TEMP
'environment variable.
Public Function CreateTmpFile(Optional strPrefix As String) As String
  Dim strPath As String
  Dim strResult As String
  strResult = Space$(MAX_PATH) 'Create a buffer
  
  strPath = Environ$("temp")
  If GetTempFileName(strPath, strPrefix, 0, strResult) <> 0 Then
    CreateTmpFile = Left(strResult, InStr(1, strResult, Chr(0)) - 1)
  Else
    CreateTmpFile = ""
  End If
End Function
'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log:
' 1    Biblioteka1.0         2007-04-23 13:21:58  Darko Kolakovic
'$
'*******************************************************************************

