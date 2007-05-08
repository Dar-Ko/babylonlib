Attribute VB_Name = "KFileUnique"
'$Workfile: S:\_SrcPool\VB\KFileUnique.bas$: implementation file
'$Revision: 1$ $Date: 2007-05-08 10:12:40$
'$Author: Darko Kolakovic$
'
'Creates unique file name
'CommonSoft Inc.
'2004-08-22
Option Explicit
'-------------------------------------------------------------------------------
'Creates unique name for a file in the given folder. Filename is generated
'from the current time and has minimum length of 8 characters.
'File name is limited to MAX_PATH. Lengths of directory path and file name
'extension are also included in the limit, if they are not empty strings.
'
'Parameters:
' strFilePath   directory path or empty string
' strPrefix,    filename prefix  or empty string
' strExtension  filename extension or empty string
'
'Note: some other process could create a file with the same name as the name
'returned by the function, in the period before the caller actually creates the
'file.
'
'Note: Path length limit for FAT32 file systems is MAX_PATH and for NTFS is 32768
'characters (see also: Path Field Limits (CRT)).
'
'Returns: string with unique file name or NULL in case of a failure.
 Public Function CreateUniqueFileName(Optional ByVal strFilePath As String, _
                                      Optional ByRef strPrefix As String, _
                                      Optional ByVal strExtension As String _
                                     ) As String
  If strFilePath <> "" Then
    If Not IsPathDelim(strFilePath) Then
      strFilePath = strFilePath & PATHDELIM 'Append directory delimiter
    End If
  End If
  strFilePath = strFilePath & strPrefix 'Append filename prefix to the directory
  
  If strExtension <> "" Then
    If Left(strExtension, 1) <> FILEEXTDELIM Then
      'Insert filename extension separator
      strExtension = FILEEXTDELIM & strExtension
    End If
  End If
  
  Dim ftTime As FILETIME 'system time
  Call GetSystemTimeAsFileTime(ftTime)
  ftTime.dwHighDateTime = ftTime.dwLowDateTime 'Save value for later
                                                'sanity check
  Dim strName As String
  strName = Hex(ftTime.dwLowDateTime)
  Do While IsFileExisting(strFilePath & strName & strExtension)
    If (ftTime.dwHighDateTime - ftTime.dwLowDateTime) > &H1000 Then
      'Break theoretical endless loop
      CreateUniqueFileName = ""
      Exit Function
    End If
    
    ftTime.dwLowDateTime = ftTime.dwLowDateTime + 1
    strName = Hex(ftTime.dwLowDateTime)
  Loop
  
CreateUniqueFileName = strFilePath & strName & strExtension
End Function
'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log: 
' 1    Biblioteka1.0         2007-05-08 10:12:40  Darko Kolakovic 
'$
'*******************************************************************************

