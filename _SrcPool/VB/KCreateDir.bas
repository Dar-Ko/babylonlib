Attribute VB_Name = "KCreateDir"
'$Workfile: S:\_SrcPool\VB\KCreateDir.bas$: implementation file
'$Revision: 1$ $Date: 2007-04-24 15:24:29$
'$Author: Darko Kolakovic$
'
'File I/O/ handling helpers
'2003-12-29

Private Const INVALID_HANDLE_VALUE As Long = -1
Private Const MAX_PATH As Long = 260

Private Type SECURITY_ATTRIBUTES
  nLength As Long
  lpSecurityDescriptor As Long
  bInheritHandle As Long
End Type

Private Declare Function CreateDirectory Lib "kernel32" Alias _
  "CreateDirectoryA" (ByVal lpPathName As String, _
                      lpSecurityAttributes As SECURITY_ATTRIBUTES) As Long
'-------------------------------------------------------------------------------
'Creates a new directory. If the underlying file system supports security on
'files and directories, the function applies a specified security descriptor to
' the new directory.
Public Function CreateDir(ByVal strDirPath As String) As Integer
  Dim r As Long
  Dim SA As SECURITY_ATTRIBUTES
  Dim drivePart As String
  Dim newDirectory  As String
  Dim item As String
  Dim sfolders() As String
  Dim pos As Integer
  Dim iSubdirCount As Integer

  If Right$(strDirPath, 1) <> "\" Then
    strDirPath = strDirPath & "\"
  End If

  pos = InStr(strDirPath, ":")

  If pos Then
    drivePart = StrToken(strDirPath, "\")
  Else
    drivePart = ""
  End If

  Do Until strDirPath = ""
    'strip off one item (i.e. "Files\")
    item = StrToken(strDirPath, "\")

    'add it to an array for later use, and
    'if this is the first item (iSubdirCount=0),
    'append the drivepart
    ReDim Preserve sfolders(0 To iSubdirCount) As String

    If iSubdirCount = 0 Then item = drivePart & item
    sfolders(iSubdirCount) = item

    'debug only
    '   List1.AddItem item

    'increment the array counter
    iSubdirCount = iSubdirCount + 1
  Loop

  'Now create the directories.
  'Because the first directory is
  '0 in the array, reinitialize iSubdirCount to -1
  iSubdirCount = -1

  Do
    iSubdirCount = iSubdirCount + 1
    'just keep appending the folders in the
    'array to newDirectory.  When iSubdirCount=0 ,
    'newDirectory is "", so the
    'newDirectory gets assigned drive:\firstfolder.

    'Subsequent loops adds the next member of the
    'array to the path, forming a fully qualified
    'path to the new directory.
     newDirectory = newDirectory & sfolders(iSubdirCount)

    'the only member of the SA type needed (on
    'a win95/98 system at least)
    SA.nLength = LenB(SA)

    Call CreateDirectory(newDirectory, SA)

    'debug only
    '    List2.AddItem newDirectory

  Loop Until iSubdirCount = UBound(sfolders)

  'done. Return iSubdirCount, but add 1 for the 0-based array.
  CreateDir = iSubdirCount + 1

End Function

'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log:
' 1  Biblioteka1.0     2007-04-23 13:21:58  Darko Kolakovic
'$
'*******************************************************************************

