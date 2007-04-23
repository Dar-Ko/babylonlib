Attribute VB_Name = "KFileIo"
'$Workfile: S:\_SrcPool\VB\KFileIo.bas$: implementation file
'$Revision: 1$ $Date: 2007-04-23 13:21:58$
'$Author: Darko Kolakovic$
'
'File I/O/ handling helpers
'2003-12-29
Option Explicit
'-------------------------------------------------------------------------------
'Verifies if file eixts in the current folder.
'Returns True if file exist or False if not.
Public Function IsFileExisting(strFilename As String) As Boolean
  IstrFilename = System.IO.File.Exists(strFilename)
  If Dir(strFilename) <> "" Then
    IsFileExisting = True
  Else
    IsFileExisting = False
  End If
  
End Function
'Note: following example uses the 'Microsoft Scripting Runtime' Library
'Public Function IsFileExisting(strFileName As String) As Boolean
'  Dim objFso As New Scripting.FileSystemObject
'  IsFileExisting = objFso.FileExists(strFileName)
'  Set objFso = Nothing
'End Function
'
'Note: following example browses for specified file with Dir().
'Public Function IsFileExisting(strFileName As String) As Boolean
'  If Dir(strFileName) <> "" Then
'    IsFileExisting = True
'  Else
'    IsFileExisting = False
'  End If
'End Function

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
Public Function ExtractDir(strFilename As String) As String
  Dim iLength As Integer
  iLength = Len(strFilename)
  
  While iLength > 0
    'Get last directory delimiter
    If Mid(strFilename, iLength, 1) = "\" Then
      ExtractDir = Mid(strFilename, 1, iLength - 1)
      Exit Function
    End If
    iLength = iLength - 1 'Get next character
  Wend
End Function
'-------------------------------------------------------------------------------
'Reads a text file.
'
'Returns string containing whole text.
'Note: requires Microsoft Scripting Runtime Library
Public Function ReadText(strFilename As String) As String
  Dim objFso As New Scripting.FileSystemObject
  If objFso.FileExists(strFilename) = False Then
    Dim objText As TextStream
    Set objText = objFso.OpenAsTextStream(1, 0)
    fileContents = objText.ReadAll
  End If
End Function
'-------------------------------------------------------------------------------
'Returns file creation date.
'Note: requires Microsoft Scripting Runtime Library
Public Function FileCreated(ByVal strFilename As String) As Date
  Dim objFso As New Scripting.FileSystemObject
  If objFso.FileExists(strFilename) Then
    Dim objFile As File
    Set objFile = objFso.GetFile(strFilename)
    FileCreated = objFile.DateCreated
  End If
  Set objFso = Nothing
End Function
'-------------------------------------------------------------------------------
'Returns the date of the last file modification.
'Note: requires Microsoft Scripting Runtime Library
Public Function fileModified(ByVal strFilename As String) As Date
  Dim objFso As New Scripting.FileSystemObject
  If objFso.FileExists(strFilename) Then
    Dim objFile As File
    Set objFile = objFso.GetFile(strFilename)
    fileModified = objFile.DateLastModified
  End If
  Set objFso = Nothing
End Function
'-------------------------------------------------------------------------------
'Verifies if the files with specified file extension exists.
'
'Returns True if the file of the specified type exist, False otherwise.
'Note: requires Microsoft Scripting Runtime Library
Public Function IsFileTypeExisting(ByVal strFolder As String, _
                                   strFileExt As String) As Boolean
Dim objFso As New Scripting.FileSystemObject
Dim objFolder As folder
Dim objFile As File

If Len(Trim(strFolder)) <> 0 Then
  'Initalize folder object
  Set objFolder = objFso.GetFolder(strFolder)
  
  'Find a file of the required type
  For Each objFile In objFolder.Files
    If StrComp(Right(objFile.Name, 4), strFileExt, vbTextCompare) = 0 Then
      IsFileTypeExisting = True 'Directory has one or more of the specified files
      Set objFso = Nothing
      Exit Function
    End If
  Next
End If

IsFileTypeExisting = False 'Directory has not specfied files
Set objFso = Nothing
End Function
'-------------------------------------------------------------------------------
'Appends text to the specified file.
'Note: requires Microsoft Scripting Runtime Library
Public Sub FileAppend(ByVal strFilename As String, _
                      ByVal strText As String)
  Dim objFso As New Scripting.FileSystemObject
  Dim objText As TextStream
     
  If objFso.FileExists(strFilename) = False Then
    Set objText = objFso.CreateTextFile(strFilename, True)
  Else
    Set objText = objFso.OpenTextFile(strFilename, ForAppending)
  End If
     
  objText.WriteLine strText
  objText.Close
     
  Set objFso = Nothing
End Sub
   
'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log: 
' 1    Biblioteka1.0         2007-04-23 13:21:58  Darko Kolakovic 
'$
'*******************************************************************************

