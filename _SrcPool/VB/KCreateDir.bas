Attribute VB_Name = "KCreateDir"
'$Workfile: KCreateDir.bas$: implementation file
'$Revision: 2$ $Date: 2007-04-24 16:43:17$
'$Author: Darko Kolakovic$
'
'Create directory tree
'2003-12-29

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
'Creates a new directory tree.  If the underlying file system supports security
'on files and directories, the function applies a specified security descriptor
'to the new directory.
'
'Parameter:
' strDirPath  path to folder to be created
'
'Returns number of folders specified directory path has.
Public Function CreateDir(ByVal strDirPath As String) As Integer

  If LenB(strDirPath) <= MAX_PATH Then
    If right$(strDirPath, 1) <> "\" Then
      'Append directory delimiter
      strDirPath = strDirPath & "\"
    End If
    
    Dim iPos As Integer 'current character position in the path string
    iPos = InStr(strDirPath, ":") 'Find drive delimiter
  
    Dim strNewFolder  As String 'directory to be created, if not exist
    'Get the drive name
    If iPos Then
      strNewFolder = StrToken(strDirPath, "\")
    Else
      strNewFolder = ""
    End If
  
    Dim strSubdir As String 'name of the parent folder
    Dim iSubdirCount As Integer
    Dim saDir As SECURITY_ATTRIBUTES
    saDir.nLength = LenB(saDir) 'Initialize structure with required version
    
    Do Until strDirPath = ""
      strSubdir = StrToken(strDirPath, "\") 'Extract one of subfolders
      strNewFolder = strNewFolder & strSubdir 'Form path to parent folder
      Call CreateDirectory(strNewFolder, saDir)
  
      iSubdirCount = iSubdirCount + 1
    Loop
    CreateDir = iSubdirCount + 1
    
  Else
    Err.Raise ERROR_BAD_PATHNAME, App.EXEName, "The specified path is too long."
  End If

End Function

'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log:
' 1  Biblioteka1.0     2007-04-23 13:21:58  Darko Kolakovic
'$
'*******************************************************************************

