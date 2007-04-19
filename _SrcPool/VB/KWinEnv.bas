Attribute VB_Name = "KWinEnv"
'$Workfile: KWinEnv.bas$: implementation file
'$Revision: 2$ $Date: 2007-04-19 13:23:46$
'$Author: Darko Kolakovic$
'
'MS Windows Environment Variable Handler
'2004-06-11
Option Explicit

'Retrieves the contents of the specified variable from the environment block
'of the calling process.
' pName       [in] The name of the environment variable.
' lpBuffer    [out] A pointer to a buffer that receives the contents of
'             the specified environment variable as a null-terminated string.
'             An environment variable has a maximum size limit of 32,767
'             characters, including the null-terminating character.
' nSize       [in] The size of the buffer pointed to by the lpBuffer parameter,
'            in characters.
'
'Returns zero if fails or if the specified environment variable was not found
'in the environment block and GetLastError returns ERROR_ENVVAR_NOT_FOUND.
'If the function succeeds, return length of the environment string, including
'the null-terminating character.
Public Declare Function GetEnvironmentVariable Lib "kernel32.dll" Alias _
  "GetEnvironmentVariableA" (ByVal lpName As String, _
                             ByVal lpBuffer As String, _
                             ByVal nSize As Long) As Long
'Sets the contents of the specified environment variable for the current process.
' pName     [in] The name of the environment variable. The operating system
'           creates the environment variable if it does not exist and lpValue
'           is not NULL.
' lpValue   [in] The contents of the environment variable. The total size of
'           the environment block for a process may not exceed 32,767 characters.
'           Empty string will delete the variable from the environment block.
'
'Returns nonzero if the function succeeds.If the function fails, the return
'value is zero. To get extended error information, call GetLastError.
'
'Example
'     Private Sub Form_Load()
'       Dim lResult As Long
'       lResult = SetEnvironmentVariable("TEMP", "C:\windows\temp")
'       End
'     End Sub
Public Declare Function SetEnvironmentVariable Lib "kernel32.dll" Alias _
  "SetEnvironmentVariableA" (ByVal lpName As String, _
                             ByVal lpValue As String) As Long
'-------------------------------------------------------------------------------
'Returns the value of required Windows environment variable or the empty string.
Public Function GetEnvVariable(ByVal szName As String) As String
  Dim lpBuffer As String 'buffer that receives required environment variable
  Dim nSize As Long 'size of the buffer

  lpBuffer = String(256, " ")
  nSize = GetEnvironmentVariable(szName, lpBuffer, Len(lpBuffer))
  If nSize = 0 Then
    GetEnvVariable = "" 'Variable not exist
  Else
    'Trim the result
    lpBuffer = Left(lpBuffer, InStr(lpBuffer, Chr(0)) - 1)
    GetEnvVariable = lpBuffer
  End If
End Function
'-------------------------------------------------------------------------------
'Returns the list with Windows environment variables.
Public Function GetEnvList() As String
  Dim i As Integer
  Dim szList As String
  szList = ""
  i = 1
  'Environ$() returns the text assigned to the specified environment variable;
  'the text following the equal sign (=) in the environment-string table for
  'that environment variable or zero-length string (""), if the variable name
  'is specified. If variable sequential number is given, Environ$() returns
  'pairs "name=value".
  While Environ$(i) <> ""
    szList = szList + _
             Mid(Environ$(i), 1, InStr(1, Environ(i), "=") - 1) + _
             vbNewLine
    i = i + 1
  Wend
  GetEnvList = szList
End Function
'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log:
' 1    Biblioteka1.0         2007-04-18 15:59:40  Darko Kolakovic
'$
'*******************************************************************************
