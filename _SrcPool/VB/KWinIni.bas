Attribute VB_Name = "KWinIni"
'$Workfile: S:\_SrcPool\VB\KWinIni.bas$: implementation file
'$Revision: 1$ $Date: 2007-04-19 17:46:43$
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
' lpSectionName [in] The name of the section to which the string will be copied. If the section does not exist, it is created. The name of the section is case-independent; the string can be any combination of uppercase and lowercase letters.
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
'file.
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
                              szSection As String, _
                              lLength As Long) As String
  Dim szResult As String * lLength
  Dim lCount As Long
  lCount = GetPrivateProfileSection(szSection, szResult, lLength, szFilename)
  GetIniSection = Left(szResult, lCount - 1)
End Function
'-------------------------------------------------------------------------------
'Retrieves a string from the specified section in an initialization file.
'
'Returns value of the specified initialization key
Public Function GetIniValue(szFilename As String, _
                            szSection As String, _
                            szKey As String, _
                            lLength As Long) As String
  Dim szResult As String * lLength
  Dim lCount As Long
  lCount = GetPrivateProfileString(szSection, szKey, "", szResult, lLength, szFilename)
  GetIniValue = Left(szResult, lCount - 1)
End Function
'-------------------------------------------------------------------------------
'Retrieves a string value from the specified key in an initialization file.
'A key in the initialization file must have the following form:
'   Key=Value
'
'Returns value of the specified initialization key
Public Function ReadIniValue(INIpath As String, _
                             KEY As String, _
                             Variable As String) As String
Dim NF As Integer
Dim Temp As String
Dim LcaseTemp As String
Dim ReadyToRead As Boolean
    
AssignVariables:
        NF = FreeFile
        ReadIniValue = ""
        KEY = "[" & LCase$(KEY) & "]"
        Variable = LCase$(Variable)
    
EnsureFileExists:
    Open INIpath For Binary As NF
    Close NF
    SetAttr INIpath, vbArchive
    
LoadFile:
    Open INIpath For Input As NF
    While Not EOF(NF)
    Line Input #NF, Temp
    LcaseTemp = LCase$(Temp)
    If InStr(LcaseTemp, "[") <> 0 Then ReadyToRead = False
    If LcaseTemp = KEY Then ReadyToRead = True
    If InStr(LcaseTemp, "[") = 0 And ReadyToRead = True Then
        If InStr(LcaseTemp, Variable & "=") = 1 Then
            ReadIniValue = Mid$(Temp, 1 + Len(Variable & "="))
            Close NF: Exit Function
            End If
        End If
    Wend
    Close NF
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
Public Function WriteIniValue(INIpath As String, _
                              PutKey As String, _
                              PutVariable As String, _
                              PutValue As String)
Dim Temp As String
Dim LcaseTemp As String
Dim ReadKey As String
Dim ReadVariable As String
Dim LOKEY As Integer
Dim HIKEY As Integer
Dim KEYLEN As Integer
Dim VAR As Integer
Dim VARENDOFLINE As Integer
Dim NF As Integer
Dim X As Integer

AssignVariables:
    NF = FreeFile
    ReadKey = vbCrLf & "[" & LCase$(PutKey) & "]" & Chr$(13)
    KEYLEN = Len(ReadKey)
    ReadVariable = Chr$(10) & LCase$(PutVariable) & "="
        
EnsureFileExists:
    Open INIpath For Binary As NF
    Close NF
    SetAttr INIpath, vbArchive
    
LoadFile:
    Open INIpath For Input As NF
    Temp = Input$(LOF(NF), NF)
    Temp = vbCrLf & Temp & "[]"
    Close NF
    LcaseTemp = LCase$(Temp)
    
LogicMenu:
    LOKEY = InStr(LcaseTemp, ReadKey)
    If LOKEY = 0 Then GoTo AddKey:
    HIKEY = InStr(LOKEY + KEYLEN, LcaseTemp, "[")
    VAR = InStr(LOKEY, LcaseTemp, ReadVariable)
    If VAR > HIKEY Or VAR < LOKEY Then GoTo AddVariable:
    GoTo RenewVariable:
    
AddKey:
        Temp = Left$(Temp, Len(Temp) - 2)
        Temp = Temp & vbCrLf & vbCrLf & "[" & PutKey & "]" & vbCrLf & PutVariable & "=" & PutValue
        GoTo TrimFinalString:
        
AddVariable:
        Temp = Left$(Temp, Len(Temp) - 2)
        Temp = Left$(Temp, LOKEY + KEYLEN) & PutVariable & "=" & PutValue & vbCrLf & Mid$(Temp, LOKEY + KEYLEN + 1)
        GoTo TrimFinalString:
        
RenewVariable:
        Temp = Left$(Temp, Len(Temp) - 2)
        VARENDOFLINE = InStr(VAR, Temp, Chr$(13))
        Temp = Left$(Temp, VAR) & PutVariable & "=" & PutValue & Mid$(Temp, VARENDOFLINE)
        GoTo TrimFinalString:

TrimFinalString:
        Temp = Mid$(Temp, 2)
        Do Until InStr(Temp, vbCrLf & vbCrLf & vbCrLf) = 0
        Temp = Replace(Temp, vbCrLf & vbCrLf & vbCrLf, vbCrLf & vbCrLf)
        Loop
    
        Do Until Right$(Temp, 1) > Chr$(13)
        Temp = Left$(Temp, Len(Temp) - 1)
        Loop
    
        Do Until Left$(Temp, 1) > Chr$(13)
        Temp = Mid$(Temp, 2)
        Loop
    
OutputAmendedINIFile:
        Open INIpath For Output As NF
        Print #NF, Temp
        Close NF
    
End Function

'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log: 
' 1    Biblioteka1.0         2007-04-19 17:46:43  Darko Kolakovic 
'$
'*******************************************************************************

