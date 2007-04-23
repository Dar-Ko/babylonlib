Attribute VB_Name = "KWinIni"
'$Workfile: KWinIni.bas$: implementation file
'$Revision: 2$ $Date: 2007-04-23 09:51:09$
'$Author: Darko Kolakovic$
'
'Configuration file handler (.INI format)
'2003-12-29
Option Explicit

'Retrieves the names of all sections in an initialization file.
'Initialization file have following format:
'   [Section1]
'   Key1=Value1
'   Key2=Value2
'   ...
'   [Section2]
'   Key3=Value3
'   ...
'
' lpszReturnBuffer  [out] A pointer to a buffer that receives the section names
'                   associated with the named file. The buffer is filled with
'                   one or more null-terminated strings; the last string is
'                   followed by a second null character.
' nSize             [in] The size of the buffer pointed to by the lpszReturnBuffer
'                   parameter, in characters.
' lpFileName        [in] The name of the initialization file. If this parameter is
'                   NULL, the function searches the Win.ini file. If this parameter
'                   does not contain a full path to the file, the system searches
'                   for the file in the Windows directory.
'
'Returns the number of characters copied to the specified buffer, not including
'the terminating null character. If the buffer is not large enough to contain
'all the section names associated with the specified initialization file,
'the return value is equal to the size specified by nSize minus two.
Public Declare Function GetPrivateProfileSectionNames Lib "kernel32" Alias _
  "GetPrivateProfileSectionNamesA" (ByVal lpReturnedString As String, _
                                    ByVal nSize As Long, _
                                    ByVal lpFileName As String) As Long

'Retrieves all the keys and values for the specified section of an initialization
'file.
' lpSectionName     [in] The name of the section in the initialization file.
' lpReturnedString  [out] A pointer to a buffer that receives the key name and
'                   value pairs associated with the named section. The buffer is
'                   filled with one or more null-terminated strings; the last string
'                   is followed by a second null character.
' nSize             [in] The size of the buffer pointed to by the lpReturnedString
'                   parameter, in characters. The maximum profile section size is
'                   32,767 characters.
' lpFileName        [in] The name of the initialization file. If this parameter does
'                   not contain a full path to the file, the system searches for
'                   the file in the Windows directory.
'Returns number of characters copied to the buffer, not including the terminating
'null character. If the buffer is not large enough to contain all the key name and
'value pairs associated with the named section, the return value is equal to nSize
'minus two.
Public Declare Function GetPrivateProfileSection Lib "kernel32" Alias _
  "GetPrivateProfileSectionA" (ByVal lpSectionName As String, _
                               ByVal lpReturnedString As String, _
                               ByVal nSize As Long, _
                               ByVal lpFileName As String) As Long

'Retrieves a string from the specified section in an initialization file.
'
'Note:  Avoid specifying a default string with trailing blank characters. The function
'inserts a null character in the lpReturnedString buffer to strip any trailing blanks.
'Windows Me/98/95:  Although lpDefault is declared as a constant parameter, the system
'strips any trailing blanks by inserting a null character into the lpDefault string
'before copying it to the lpReturnedString buffer.
'
' lpSectionName     [in] The name of the section containing the key name. If this parameter is NULL, the GetPrivateProfileString function copies all section names in the file to the supplied buffer.
' lpKeyName         [in] The name of the key whose associated string is to be retrieved. If this parameter is NULL, all key names in the section specified by the lpAppName parameter are copied to the buffer specified by the lpReturnedString parameter.
' lpDefault         [in] A default string. If the lpKeyName key cannot be found in the initialization file, GetPrivateProfileString copies the default string to the lpReturnedString buffer. If this parameter is NULL, the default is an empty string, "".

' lpReturnedString  [out] A pointer to the buffer that receives the retrieved string.
'                   Windows Me/98/95:  The string cannot contain control characters
'                   (character code less than 32). Strings containing control characters may be truncated.
' nSize             [in] The size of the buffer pointed to by the lpReturnedString parameter, in characters.
' lpFileName        [in] The name of the initialization file. If this parameter does not contain a full path to the file, the system searches for the file in the Windows directory.
'
'Returns the number of characters copied to the buffer, not including the terminating
'null character. If neither lpAppName nor lpKeyName is NULL and the supplied destination
'buffer is too small to hold the requested string, the string is truncated and followed
'by a null character, and the return value is equal to nSize minus one.
'If either lpAppName or lpKeyName is NULL and the supplied destination buffer is too
'small to hold all the strings, the last string is truncated and followed by two null
'characters. In this case, the return value is equal to nSize minus two.
Public Declare Function GetPrivateProfileString Lib "kernel32" Alias _
  "GetPrivateProfileStringA" (ByVal lpSectionName As String, _
                              ByVal lpKeyName As Any, _
                              ByVal lpDefault As String, _
                              ByVal lpReturnedString As String, _
                              ByVal nSize As Long, _
                              ByVal lpFileName As String) As Long

'Retrieves an integer associated with a key in the specified section of
'an initialization file.
'
' lpSectionName     [in] The name of the section containing the key name. If this parameter is NULL, the GetPrivateProfileString function copies all section names in the file to the supplied buffer.
' lpKeyName         [in] The name of the key whose associated string is to be retrieved. If this parameter is NULL, all key names in the section specified by the lpAppName parameter are copied to the buffer specified by the lpReturnedString parameter.
' nDefault          [in] The default value to return if the key name cannot be found in the initialization file.
' lpFileName        [in] The name of the initialization file. If this parameter does not contain a full path to the file, the system searches for the file in the Windows directory.
'
'Returns the integer equivalent of the string following the specified key name
'in the specified initialization file. If the key is not found, the return value
'is the specified default value.
Public Declare Function GetPrivateProfileInt Lib "kernel32" Alias _
  "GetPrivateProfileIntA" (ByVal lpSectionName As String, _
                           ByVal lpKeyName As Any, _
                           ByVal nDefault As Long, _
                           ByVal lpFileName As String) As Long
                           
'Retrieves the data associated with a key in the specified section of
'an initialization file. As it retrieves the data, the function calculates
'a checksum and compares it with the checksum calculated by
'the WritePrivateProfileStruct function when the data was added to the file.
'
' lpszSection [in] The name of the section in the initialization file.
' lpszKey     [in] The name of the key whose data is to be retrieved.
' lpStruct    [out] A pointer to the buffer that receives the data associated with the file, section, and key names.
' uSizeStruct [in] The size of the buffer pointed to by the lpStruct parameter, in bytes.
' szFile      [in] The name of the initialization file. If this parameter does not contain a full path to the file, the system searches for the file in the Windows directory.
'
'Returns nonzero if the function succeeds, otherwise returns zero.
Public Declare Function GetPrivateProfileStruct Lib "kernel32" Alias _
  "GetPrivateProfileStructA" (ByVal lpszSection As String, _
                              ByVal lpszKey As Any, _
                              ByVal lpStruct As Long, _
                              ByVal uSizeStruct As Long, _
                              ByVal szFile As String) As Boolean

'Replaces the keys and values for the specified section in an initialization file.
'
' lpSectionName [in] The name of the section in which data is written. This section name is typically the name of the calling application.
' lpString      [in] The new key names and associated values that are to be
'                written to the named section. This string is limited to 65,535 bytes.
' lpFileName    [in] The name of the initialization file. If this parameter does not contain a full path for the file, the function searches the Windows directory for the file. If the file does not exist and lpFileName does not contain a full path, the function creates the file in the Windows directory.
'               If the file exists and was created using Unicode characters, the function writes Unicode characters to the file. Otherwise, the function creates a file using ANSI characters.
'
'Returns nonzero if the function succeeds, otherwise returns zero.
'To get extended error information, call GetLastError().
Public Declare Function WritePrivateProfileSection Lib "kernel32" Alias _
  "WritePrivateProfileSectionA" (ByVal lpSectionName As String, _
                                 ByVal lpString As String, _
                                 ByVal lpFileName As String) As Long
                                 
'Copies a string into the specified section of an initialization file.
' lpSectionName [in] The name of the section to which the string will be copied.
'                If the section does not exist, it is created. The name of the section is case-independent; the string can be any combination of uppercase and lowercase letters.
' lpKeyName     [in] The name of the key to be associated with a string. If the key does not exist in the specified section, it is created. If this parameter is NULL, the entire section, including all entries within the section, is deleted.
' lpString      [in] A null-terminated string to be written to the file. If this parameter is NULL, the key pointed to by the lpKeyName parameter is deleted.
'               Windows Me/98/95:  The system does not support the use of the TAB (\t) character as part of this parameter.
' lpFileName    [in] The name of the initialization file.
'               If the file was created using Unicode characters, the function writes Unicode characters to the file. Otherwise, the function writes ANSI characters.
'
'Returns nonzero if the function succeeds, otherwise returns zero.
'To get extended error information, call GetLastError().
Public Declare Function WritePrivateProfileString Lib "kernel32" Alias _
  "WritePrivateProfileStringA" (ByVal lpSectionName As String, _
                                ByVal lpKeyName As Any, _
                                ByVal lpString As Any, _
                                ByVal lpFileName As String) As Long
'-------------------------------------------------------------------------------
'Retrieves all the keys and values for the specified section of an initialization
'file. The string is limited to the 256 characters.
'Initialization file have following format:
'   [Section1]
'   Key1=Value1
'   Key2=Value2
'   ...
'   [Section2]
'   Key3=Value3
'   ...
'
'Returns section paragraph.
Public Function GetIniSection(szFilename As String, _
                              szSection As String) As String
  Const VAL_SIZE = 256
  Dim szResult As String * VAL_SIZE
  Dim lCount As Long
  lCount = GetPrivateProfileSection(szSection, szResult, VAL_SIZE, szFilename)
  GetIniSection = Left(szResult, lCount - 1)
  If (lCount > 0) Then
    GetIniValue = Left(szResult, lCount - 1)
  Else
    GetIniValue = ""
  End If
End Function
'-------------------------------------------------------------------------------
'Retrieves a string from the specified section in an initialization file.
'The string is limited to the 256 characters.
'
'Returns value of the specified initialization key
Public Function GetIniValue(szFilename As String, _
                            szSection As String, _
                            szKey As String) As String
  Const VAL_SIZE = 256
  Dim szResult As String * VAL_SIZE
  Dim lCount As Long
  lCount = GetPrivateProfileString(szSection, szKey, "", szResult, VAL_SIZE, szFilename)
  If (lCount > 0) Then
    GetIniValue = Left(szResult, lCount - 1)
  Else
    GetIniValue = ""
  End If
End Function
'-------------------------------------------------------------------------------
'Retrieves a string value from the specified key in an initialization file.
'The search for the key is case insensitive.
'A section with keys must have the following form:
'   [Section]
'A key in the initialization file must have the following form:
'   Key=Value
'
'Parameters:
' szFilename  initialization file name
' strSection  name of the section in the initialization file or an empty string.
'             If the section is not specified, the function will search for the
'             first occurrence of the key.
' strKey      name of the key to be associated with a string.
'
'Returns value of the specified initialization key or the empty string if the file
'or the key could not be found.
Public Function ReadIniValue(ByVal szFilename As String, _
                             ByVal strSection As String, _
                             ByVal strKey As String) As String
  ReadIniValue = ""
  If szFilename <> "" Then 'File is not specified
    If ((strKey = "") And (strSection = "")) Then Exit Function 'Nothing to do
    
    Dim bBrowseSections As Boolean
    'Normalize search strings to lower case
    strKey = LCase$(strKey)
    If (strSection <> "") Then
      'Find the section
      strSection = "[" & LCase$(strSection) & "]"
      bBrowseSections = True
    Else
      'Find the fist occurrence of the key
      bBrowseSections = False
    End If
    
    Dim strLine As String 'line of text
    Dim strNormalizedLine As String 'line of text in lower case
    Dim bFoundSection As Boolean 'line contains a section name
    bFoundSection = False
    
    Dim hFile As Integer 'file handle
    hFile = FreeFile
    SetAttr szFilename, vbArchive
    Open szFilename For Input As hFile
    'Read the file lines until the end of file
    While Not EOF(hFile)
      Line Input #hFile, strLine
      strNormalizedLine = LCase$(strLine)
      'Find the section name
      
      If bBrowseSections Then 'Find the section
        If Not bFoundSection And (InStr(strNormalizedLine, strSection) <> 0) Then
          bFoundSection = True 'Found a section
          GoTo GET_NEXT 'Break and read next line
        End If
        If bFoundSection Then
          If InStr(strNormalizedLine, "[") <> 0 Then
            'Found next section
            Close hFile
            Exit Function 'Stop searching
          Else
            If InStr(strNormalizedLine, strKey) <> 0 Then
              'Found the key
              If InStr(strNormalizedLine, strKey & "=") = 1 Then
                'Get the key value
                ReadIniValue = Mid$(strLine, 1 + Len(strKey & "="))
                Close hFile
                Exit Function
              End If
            End If
          End If
        End If
      Else 'Find first occurrence of the key, regardless of section
        If InStr(strNormalizedLine, strKey) <> 0 Then
          'Found the key
          If InStr(strNormalizedLine, strKey & "=") = 1 Then
            'Get the key value
            ReadIniValue = Mid$(strLine, 1 + Len(strKey & "="))
            Close hFile
            Exit Function
          End If
        End If
      End If
GET_NEXT:
    Wend
    Close hFile
  End If
End Function
'-------------------------------------------------------------------------------
'Replaces the keys and values for the specified section in an initialization file.
Public Sub SetIniSection(szFilename As String, _
                           szSection As String, _
                           szList As String)
  Call WritePrivateProfileSection(szSection, szList, szFilename)
End Sub
'-------------------------------------------------------------------------------
'Copies a string into the specified section of an initialization file.
Public Sub SetIniValue(szFilename As String, _
                       szSection As String, _
                       szKey As String, _
                       szValue As String)
  Call WritePrivateProfileString(szSection, szKey, szValue, szFilename)
End Sub
'-------------------------------------------------------------------------------
'Copies a string into the specified section of an initialization file.
'Requires 2 times file size of free memory. If file does not exist, creates
'new one.
'
'Author Bernie Madigan <bernie@ testrun.cjb.net>
Public Function WriteIniValue(szFilename As String, _
                              strSection As String, _
                              strKey As String, _
                              strValue As String)
  Dim hFile As Integer 'file handle
  Dim strSectionName As String 'normalized section name
  Dim iSectionNameLen As Integer
  Dim strKeyName As String 'normalized key name
  
  hFile = FreeFile
  strSectionName = vbCrLf & "[" & LCase$(strSection) & "]" & Chr$(13)
  iSectionNameLen = Len(strSectionName)
  strKeyName = Chr$(10) & LCase$(strKey) & "="
        
  'Create file if not exist
  Open szFilename For Binary As hFile
  Close hFile
  SetAttr szFilename, vbArchive
    
  'Read the file
  Dim strFileContent As String
  Dim strNormalizedContent As String
  Open szFilename For Input As hFile
  strFileContent = Input$(LOF(hFile), hFile)
  strFileContent = vbCrLf & strFileContent & "[]"
  Close hFile
  strNormalizedContent = LCase$(strFileContent)
    
  'Get position of the elements
  Dim iSectionStart As Integer 'section start position
  iSectionStart = InStr(strNormalizedContent, strSectionName)
  If iSectionStart = 0 Then GoTo INSERT_KEY:
  
  Dim iSectionEnd As Integer 'section end position
  iSectionEnd = InStr(iSectionStart + iSectionNameLen, strNormalizedContent, "[")
  
  Dim iKeyEnd As Integer 'key name end position
  iKeyEnd = InStr(iSectionStart, strNormalizedContent, strKeyName)
  If iKeyEnd > iSectionEnd Or iKeyEnd < iSectionStart Then GoTo INSERT_VALUE:
  
  GoTo CHANGE_VALUE:
    
INSERT_KEY:
  strFileContent = Left$(strFileContent, Len(strFileContent) - 2)
  strFileContent = strFileContent & vbCrLf & vbCrLf & _
                   "[" & strSection & "]" & vbCrLf & _
                   strKey & "=" & strValue
  GoTo FORMAT_OUTPUT:
        
INSERT_VALUE:
  strFileContent = Left$(strFileContent, Len(strFileContent) - 2)
  strFileContent = Left$(strFileContent, iSectionStart + iSectionNameLen) & _
                   strKey & "=" & strValue & vbCrLf & _
                   Mid$(strFileContent, iSectionStart + iSectionNameLen + 1)
  GoTo FORMAT_OUTPUT:
        
CHANGE_VALUE:
  Dim iValueEnd As Integer 'text value end position
  strFileContent = Left$(strFileContent, Len(strFileContent) - 2)
  iValueEnd = InStr(iKeyEnd, strFileContent, Chr$(13))
  strFileContent = Left$(strFileContent, iKeyEnd) & _
                   strKey & "=" & strValue & _
                   Mid$(strFileContent, iValueEnd)
  GoTo FORMAT_OUTPUT:

FORMAT_OUTPUT:
  strFileContent = Mid$(strFileContent, 2)
  Do Until InStr(strFileContent, vbCrLf & vbCrLf & vbCrLf) = 0
    strFileContent = Replace(strFileContent, vbCrLf & vbCrLf & vbCrLf, vbCrLf & vbCrLf)
  Loop
  
  Do Until Right$(strFileContent, 1) > Chr$(13)
    strFileContent = Left$(strFileContent, Len(strFileContent) - 1)
  Loop
  
  Do Until Left$(strFileContent, 1) > Chr$(13)
    strFileContent = Mid$(strFileContent, 2)
  Loop
    
  'Save the result
  Open szFilename For Output As hFile
  Print #hFile, strFileContent
  Close hFile
    
End Function
'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log:
' 1    Biblioteka1.0         2007-04-19 17:46:43  Darko Kolakovic
'$
'*******************************************************************************

