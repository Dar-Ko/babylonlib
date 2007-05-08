Attribute VB_Name = "KFileSys"
'$Workfile: S:\_SrcPool\VB\KFileSys.bas$: implementation file
'$Revision: 1$ $Date: 2007-05-08 10:12:39$
'$Author: Darko Kolakovic$
'
'File System helpers
'CommonSoft Inc.
'2004-08-22

Public Const DRIVE_DELIM  As String = ":" 'Separates drive name and directory
Public Const PATH_END     As String = ";" 'Separates path components
Public Const PATHDELIM    As String = "\" 'Delimits directory and filename
Public Const FILEEXTDELIM As String = "." 'Separates filename base and extension
'-------------------------------------------------------------------------------
'Verifies if the last character in the directory path is a file path delimiter.
'
'Returns: true if the character is one of the recognized delimeters or false
'if it is not.
Public Function IsPathDelim(ByRef strPath As String) As Boolean
  IsPathDelim = False
  Dim ch As String
  ch = Right$(strPath, 1)
  If (ch = PATHDELIM) Or (ch = "/") Then
    IsPathDelim = True
  End If
End Function
'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log: 
' 1    Biblioteka1.0         2007-05-08 10:12:39  Darko Kolakovic 
'$
'*******************************************************************************


