Attribute VB_Name = "KRegKey"
'$Workfile: KRegKey.bas$: implementation file
'$Revision: 3$ $Date: 2007-05-11 17:26:06$
'$Author: Darko Kolakovic$
'
'Windows Registry handler
'Copyright:   CommonSoft Inc
'Darko Kolakovic May 94
 
'Group=Windows
Option Explicit

'------------------------------------------------------------------------------
'Reserved Key Handles [Registry] WinReg.h
'
'The HKEY_CLASSES_ROOT (HKCR) key contains file extension associations and
'COM class registration information such as ProgIDs, CLSIDs, and IIDs.
'It is primarily intended for compatibility with the registry in 16-bit Windows.
Public Const HKEY_CLASSES_ROOT = &H80000000
Public Const HKEY_CURRENT_USER = &H80000001
Public Const HKEY_LOCAL_MACHINE = &H80000002
Public Const HKEY_USERS = &H80000003
Public Const HKEY_PERFORMANCE_DATA = &H80000004
Public Const HKEY_PERFORMANCE_TEXT = &H80000050
Public Const HKEY_PERFORMANCE_NLSTEXT = &H80000060
Public Const HKEY_CURRENT_CONFIG = &H80000005
Public Const HKEY_DYN_DATA = &H80000006

'==============================================================================

'------------------------------------------------------------------------------
'[Registry] WinNt.h (Win32.h)

'Registry Specific Access Rights
Public Const KEY_QUERY_VALUE = &H1
Public Const KEY_SET_VALUE = &H2
Public Const KEY_CREATE_SUB_KEY = &H4
Public Const KEY_ENUMERATE_SUB_KEYS = &H8
Public Const KEY_NOTIFY = &H10
Public Const KEY_CREATE_LINK = &H20
Public Const KEY_READ = ((STANDARD_RIGHTS_READ Or _
                          KEY_QUERY_VALUE Or _
                          KEY_ENUMERATE_SUB_KEYS Or _
                          KEY_NOTIFY) And _
                          (Not SYNCHRONIZE))
Public Const KEY_WRITE = ((STANDARD_RIGHTS_WRITE Or _
                           KEY_SET_VALUE Or _
                           KEY_CREATE_SUB_KEY) And _
                           (Not SYNCHRONIZE))
Public Const KEY_EXECUTE = ((KEY_READ) And (Not SYNCHRONIZE))
Public Const KEY_ALL_ACCESS = ((STANDARD_RIGHTS_ALL Or _
                                KEY_QUERY_VALUE Or _
                                KEY_SET_VALUE Or _
                                KEY_CREATE_SUB_KEY Or _
                                KEY_ENUMERATE_SUB_KEYS Or _
                                KEY_NOTIFY Or _
                                KEY_CREATE_LINK) And _
                                (Not SYNCHRONIZE))

'Open/Create Options
Public Const REG_OPTION_RESERVED = 0       'Parameter is reserved
Public Const REG_OPTION_NON_VOLATILE = 0   'Key is preserved when system is rebooted
Public Const REG_OPTION_VOLATILE = 1       'Key is not preserved when system
                                           'is rebooted
Public Const REG_OPTION_CREATE_LINK = 2    'Created key is a symbolic link
Public Const REG_OPTION_BACKUP_RESTORE = 4 'Open for backup or restore;
                                           'special access rules privilege required
Public Const REG_OPTION_OPEN_LINK = 8      'Open symbolic link
Public Const REG_LEGAL_OPTION = (REG_OPTION_RESERVED Or _
                                 REG_OPTION_NON_VOLATILE Or _
                                 REG_OPTION_VOLATILE Or _
                                 REG_OPTION_CREATE_LINK Or _
                                 REG_OPTION_BACKUP_RESTORE Or _
                                 REG_OPTION_OPEN_LINK)

'Key creation/open disposition
Public Const REG_CREATED_NEW_KEY = &H1     'New Registry Key created
Public Const REG_OPENED_EXISTING_KEY = &H2 'Existing Key opened

'Registry Notify filter values
Public Const REG_NOTIFY_CHANGE_NAME = 1        'Create or delete (child)
Public Const REG_NOTIFY_CHANGE_ATTRIBUTES = 2
Public Const REG_NOTIFY_CHANGE_LAST_SET = 4    'Time stamp
Public Const REG_NOTIFY_CHANGE_SECURITY = 8
Public Const REG_LEGAL_CHANGE_FILTER = (REG_NOTIFY_CHANGE_NAME Or _
                                        REG_NOTIFY_CHANGE_ATTRIBUTES Or _
                                        REG_NOTIFY_CHANGE_LAST_SET Or _
                                        REG_NOTIFY_CHANGE_SECURITY)

'Predefined registry data types
Public Const REG_NONE = 0       'No value type
Public Const REG_SZ = 1         'Unicode nul terminated string
Public Const REG_EXPAND_SZ = 2  'Unicode nul terminated string
                                '(with environment variable references)
Public Const REG_BINARY = 3     'Free form binary
Public Const REG_DWORD = 4      '32-bit number
Public Const REG_DWORD_LITTLE_ENDIAN = 4 '32-bit number (same as REG_DWORD)
Public Const REG_DWORD_BIG_ENDIAN = 5 '32-bit number
Public Const REG_LINK = 6       'Symbolic Link(Unicode)
Public Const REG_MULTI_SZ = 7   'Multiple Unicode strings
Public Const REG_RESOURCE_LIST = 8 'Resource list in the resource map
Public Const REG_FULL_RESOURCE_DESCRIPTOR = 9 'Resource list in the hardware
                                              'description
Public Const REG_RESOURCE_REQUIREMENTS_LIST = 10

Private Const RESERVED_FOR_FUTURE_USE = 0
'------------------------------------------------------------------------------
'AdvApi
Private Declare Function RegOpenKeyEx Lib "advapi32.dll" Alias "RegOpenKeyExA" (ByVal hKey As Long, ByVal lpSubKey As String, ByVal ulOptions As Long, ByVal samDesired As Long, phkResult As Long) As Long
Private Declare Function RegCreateKeyEx Lib "advapi32.dll" Alias "RegCreateKeyExA" (ByVal hKey As Long, ByVal lpSubKey As String, ByVal Reserved As Long, ByVal lpClass As String, ByVal dwOptions As Long, ByVal samDesired As Long, lpSecurityAttributes As Any, phkResult As Long, lpdwDisposition As Long) As Long
Private Declare Function RegQueryValueEx Lib "advapi32.dll" Alias "RegQueryValueExA" (ByVal hKey As Long, ByVal lpValueName As String, ByVal lpReserved As Long, lpType As Long, lpData As Any, lpcbData As Long) As Long         ' Note that if you declare the lpData parameter as String, you must pass it By Value.
Private Declare Function RegQueryInfoKey Lib "advapi32.dll" Alias "RegQueryInfoKeyA" (ByVal hKey As Long, ByVal lpClass As String, lpcbClass As Long, lpReserved As Long, lpcSubKeys As Long, lpcbMaxSubKeyLen As Long, lpcbMaxClassLen As Long, lpcValues As Long, lpcbMaxValueNameLen As Long, lpcbMaxValueLen As Long, lpcbSecurityDescriptor As Long, lpftLastWriteTime As Any) As Long
Private Declare Function RegEnumKeyEx Lib "advapi32.dll" Alias "RegEnumKeyExA" (ByVal hKey As Long, ByVal dwIndex As Long, ByVal lpName As String, lpcbName As Long, lpReserved As Long, ByVal lpClass As String, lpcbClass As Long, lpftLastWriteTime As Any) As Long
Private Declare Function RegEnumValue Lib "advapi32.dll" Alias "RegEnumValueA" (ByVal hKey As Long, ByVal dwIndex As Long, ByVal lpValueName As String, lpcbValueName As Long, lpReserved As Long, lpType As Long, lpData As Any, lpcbData As Long) As Long
Private Declare Function RegSetValueEx Lib "advapi32.dll" Alias "RegSetValueExA" (ByVal hKey As Long, ByVal lpValueName As String, ByVal Reserved As Long, ByVal dwType As Long, lpData As Any, ByVal cbData As Long) As Long         ' Note that if you declare the lpData parameter as String, you must pass it By Value.
Private Declare Function RegDeleteKey Lib "advapi32.dll" Alias "RegDeleteKeyA" (ByVal hKey As Long, ByVal lpSubKey As String) As Long
Private Declare Function RegDeleteValue Lib "advapi32.dll" Alias "RegDeleteValueA" (ByVal hKey As Long, ByVal lpValueName As String) As Long
Private Declare Function RegCloseKey Lib "advapi32.dll" (ByVal hKey As Long) As Long

'-------------------------------------------------------------------------------
'The function opens the specified registry key. If lpszKeyName parameter is NULL or a
'pointer to an empty string, the function initializes m_hKey member to the same
'handle that was passed in.
'A single registry key can be opened only 65534 times; after that function fails.
'
'Parameters:
' hKey    [in] handle to an open registry key or a predefined key. The calling process
'         must have KEY_CREATE_SUB_KEY access to the key.
'         Predefined reserved key handle values are:
'
'         HKEY_CLASSES_ROOT
'         HKEY_CURRENT_USER
'         HKEY_LOCAL_MACHINE
'         HKEY_USERS
'         HKEY_PERFORMANCE_DATA
'         HKEY_PERFORMANCE_TEXT
'         HKEY_PERFORMANCE_NLSTEXT
'         HKEY_CURRENT_CONFIG
'         HKEY_DYN_DATA
'
' strKeyName  [in] name of subkey to open or an empty string. If this parameter is
'             an empty string, the function will open a new handle to the key
'             identified by the hKey parameter.
' lSamDesired [in] desired security access
' hResultKey  [out] handle of the newly opened or created key
' bCreate     [in] = False open existing or create new registry key if required subkey
'             does not exist.
'
' Registry Specific Access Rights         Description (REGSAM WinNT.h)
'    KEY_ALL_ACCESS                     Combination of KEY_QUERY_VALUE,
'                                       KEY_ENUMERATE_SUB_KEYS,
'                                       KEY_NOTIFY, KEY_CREATE_SUB_KEY,
'                                       KEY_CREATE_LINK,
'                                       and KEY_SET_VALUE access.
'    KEY_CREATE_LINK                32  Permission to create a symbolic link.
'    KEY_CREATE_SUB_KEY              4  Permission to create subkeys.
'    KEY_ENUMERATE_SUB_KEYS          8  Permission to enumerate subkeys.
'    KEY_EXECUTE                        Permission for read access.
'    KEY_NOTIFY                     16  Permission for change notification.
'    KEY_QUERY_VALUE                 1  Permission to query subkey data.
'    KEY_READ                           Combination of KEY_QUERY_VALUE,
'                                       KEY_ENUMERATE_SUB_KEYS,
'                                       and KEY_NOTIFY access.
'    KEY_SET_VALUE                   2  Permission to set subkey data.
'    KEY_WRITE                          Combination of KEY_SET_VALUE and
'                                       KEY_CREATE_SUB_KEY access.
'
'Returns: True if the function succeeds or False if fails. Also returns
'the handle of the newly opened or created key.
'
'Example:
'    If (Not RegKeyOpen(HKEY_LOCAL_MACHINE, -
'                   "SYSTEM\CurrentControlSet\Services\EventLog\Application", -
'                    KEY_WRITE, hKey)  Then
'      MsgBox("Failure")
'    End If
Public Function RegKeyOpen(ByVal hKey As Long, _
                           ByRef strKeyName As String, _
                           ByVal lSamDesired As Long, _
                           ByRef hResultKey As Long, _
                           Optional bCreate As Boolean = False) As Boolean
  If strKeyName = "" Then
    'If subkey is not given, open a new handle to the key identified by
    'the hKey parameter.
    bCreate = False
  End If
  
  Do While Left(strKeyName, 1) = "\"
    'Trim leading key separators
    strKeyName = Right(strKeyName, Len(strKeyName) - 1)
  Loop
  
  Dim lDisposition As Long 'receives one of the following disposition values:
                           '  REG_CREATED_NEW_KEY  The key did not exist and
                           '              was created.
                           '  REG_OPENED_EXISTING_KEY The key existed and was
                           '              simply opened without being changed.
  
  If bCreate Then 'Create new registry key
    Dim Dummy As SECURITY_ATTRIBUTES
    Dummy.nLength = LenB(Dummy)
    RegKeyOpen = (RegCreateKeyEx(hKey, _
                                strKeyName, _
                                RESERVED_FOR_FUTURE_USE, _
                                REG_NONE, _
                                REG_OPTION_NON_VOLATILE, _
                                lSamDesired, _
                                Dummy, _
                                hResultKey, _
                                lDisposition) = ERROR_SUCCESS)
  Else 'Open existing registry key
    RegKeyOpen = (RegOpenKeyEx(hKey, _
                              strKeyName, _
                              RESERVED_FOR_FUTURE_USE, _
                              lSamDesired, _
                              hResultKey) = ERROR_SUCCESS)
  End If
End Function
'-------------------------------------------------------------------------------
'Saves a string under a specified registry key.
'
'Parameters:
' hKey    [in] handle to an open registry key or a predefined key. The calling process
'         must have KEY_CREATE_SUB_KEY access to the key.
'         Predefined reserved key handle values are:
'
'         HKEY_CLASSES_ROOT
'         HKEY_CURRENT_USER
'         HKEY_LOCAL_MACHINE
'         HKEY_USERS
'         HKEY_PERFORMANCE_DATA
'         HKEY_PERFORMANCE_TEXT
'         HKEY_PERFORMANCE_NLSTEXT
'         HKEY_CURRENT_CONFIG
'         HKEY_DYN_DATA
'
' strKeyName  [in] name of subkey to open or an empty string.
' strValueName  [in] name of the value to be set. If a value with this name is
'               not already present in the key, the function adds it to the key.
'               If strValueName is an empty string, the function sets the type
'               and data for the key's unnamed or default value.
' szValue       [in] null-terminated string to be stored
'
'Returns: True if the function succeeds or False if fails.
'
'Example:
'   Call RegKeyOpen(HKEY_LOCAL_MACHINE, -
'                   "Software\CommonSoftInc\", -
'                   KEY_WRITE, -
'                   hKey, -
'                   True)
'   Call RegKeySetStringValue(hKey, "NewKey\Key2", "aString", "Some text")
'
Public Function RegKeySetStringValue(ByVal hKey As Long, _
                                     ByVal strKeyName, _
                                     ByVal strValueName As String, _
                                     ByVal szValue As String) As Boolean
  'Create or open the subkey
  Dim hSubKey As Long
  Dim lDisposition As Long
  If (RegCreateKeyEx(hKey, _
                     strKeyName, _
                     RESERVED_FOR_FUTURE_USE, _
                     REG_NONE, _
                     REG_OPTION_NON_VOLATILE, _
                     KEY_ALL_ACCESS, _
                     ByVal 0&, _
                     hSubKey, _
                     lDisposition) = ERROR_SUCCESS) Then
    
    szValue = szValue & vbNullChar 'Append string terminator, just in case
    'Write new value to the  registry
    RegKeySetStringValue = (RegSetValueEx(hSubKey, _
                         strValueName, _
                         RESERVED_FOR_FUTURE_USE, _
                         REG_SZ, _
                         ByVal szValue, _
                         Len(szValue)) = ERROR_SUCCESS)
    Call RegCloseKey(hSubKey)
  Else
    RegKeySetStringValue = False
  End If
End Function
'-------------------------------------------------------------------------------
'Retrieves the string for the specified value name associated with a registry key.
'
'Parameters:
' hKey    [in] handle to an open registry key or a predefined key.
' strKeyName  [in] name of subkey to open or an empty string.
' strValueName  [in] The name of the registry value. If it is an empty string,
'               the function retrieves the type and data for the key's unnamed or
'               default value, if any.
' strDefaultValue   [in] default value to return if no value is set in the strKeyName
'
'Returns: required string or default value in case of a failure.
Public Function RegKeyGetString(ByVal hKey As Long, _
                               ByVal strKeyName As String, _
                               ByVal strValueName As String, _
                               Optional ByVal strDefaultValue As String = "") As String
  RegKeyGetString = strDefaultValue 'Set default return value
  
  
  'Open the subkey
  Dim hSubKey As Long
  If RegOpenKeyEx(hKey, strKeyName, RESERVED_FOR_FUTURE_USE, _
                  KEY_READ, hSubKey) = ERROR_SUCCESS Then
    'Get the length and the type of the registry value
    Dim nType As Long
    Dim lSize As Long 'size of the buffer pointed to by the szData parameter, in bytes.
    Dim szData As String
    
    If RegQueryValueEx(hSubKey, strValueName, RESERVED_FOR_FUTURE_USE, _
                       nType, ByVal szData, lSize) = ERROR_SUCCESS Then
      
      If lSize > 0 Then 'Allocate required space and read the string
        Select Case nType
          Case REG_SZ
            szData = String(lSize, " ")
            If RegQueryValueEx(hSubKey, strValueName, RESERVED_FOR_FUTURE_USE, _
                               nType, ByVal szData, Len(szData)) = ERROR_SUCCESS Then
              RegKeyGetString = Left(szData, lSize - 1) 'Trim terminating zero
            End If
            
          Case REG_DWORD
            Dim lData As Long
            lSize = 4
            If RegQueryValueEx(hSubKey, strValueName, RESERVED_FOR_FUTURE_USE, _
                               nType, lData, lSize) = ERROR_SUCCESS Then
              RegKeyGetString = lData
            End If
        End Select
      End If
    End If
    Call RegCloseKey(hSubKey)
  End If
End Function
'-------------------------------------------------------------------------------
'Delete a registry key value
'
'Returns: True if the function succeeds or False if fails.
Public Function RegKeyDeleteValue(ByVal hKey As Long, _
                                  ByRef strKeyName As String, _
                                  ByRef strValueName As String) As Boolean
  Dim hSubKey As Long
  
  If (RegOpenKeyEx(hKey, _
                   strKeyName, _
                   RESERVED_FOR_FUTURE_USE, _
                   KEY_ALL_ACCESS, hSubKey) = ERROR_SUCCESS) Then
    RegKeyDeleteValue = (RegDeleteValue(hSubKey, strValueName) = ERROR_SUCCESS)
    Call RegCloseKey(hSubKey)
  Else
    RegKeyDeleteValue = False
  End If
  
End Function
'-------------------------------------------------------------------------------
'Delete a registry key
'
'Returns: True if the function succeeds or False if fails.
Public Function RegKeyDelete(ByVal hKey As Long, _
                        ByRef strKeyName As String) As Boolean
  Dim hSubKey As Long
  If (RegOpenKeyEx(hKey, _
                   vbNullChar, _
                   RESERVED_FOR_FUTURE_USE, _
                   KEY_ALL_ACCESS, hSubKey) = ERROR_SUCCESS) Then
                   
    RegKeyDelete = (RegDeleteValue(hSubKey, strKeyName) = ERROR_SUCCESS)
    Call RegCloseKey(hSubKey)
  Else
    RegKeyDelete = False
  End If
End Function
'-------------------------------------------------------------------------------
'
Public Function RegKeySaveBinValue(ByVal hKey As Long, _
                              ByVal strKeyName As String, _
                              ByVal strValueName As String, _
                              ByRef arrData() As Byte) As Boolean
                              
  'Create or open the subkey
  Dim hSubKey As Long
  Dim lDisposition As Long
  If (RegCreateKeyEx(hKey, _
                     strKeyName, _
                     RESERVED_FOR_FUTURE_USE, _
                     REG_NONE, _
                     REG_OPTION_NON_VOLATILE, _
                     KEY_ALL_ACCESS, _
                     ByVal 0&, _
                     hSubKey, _
                     lDisposition) = ERROR_SUCCESS) Then
    'Write new value to the  registry
    RegKeySaveBinValue = (RegSetValueEx(hSubKey, _
                         strValueName, _
                         RESERVED_FOR_FUTURE_USE, _
                         REG_BINARY, _
                         arrData(0), _
                         UBound(arrData()) + 1) = ERROR_SUCCESS)
    Call RegCloseKey(hSubKey)
  Else
    RegKeySaveBinValue = False
  End If
End Function
'-------------------------------------------------------------------------------
'Converts predefined registry key names to one of the following reserved
'handles:
'         HKEY_CLASSES_ROOT
'         HKEY_CURRENT_USER
'         HKEY_LOCAL_MACHINE
'         HKEY_USERS
'         HKEY_PERFORMANCE_DATA
'         HKEY_PERFORMANCE_TEXT
'         HKEY_PERFORMANCE_NLSTEXT
'         HKEY_CURRENT_CONFIG
'         HKEY_DYN_DATA
'Returns: one of resreved registry key handles or HKEY_CURRENT_USER if
'key name is not one from the list of predefined handles.
Public Function StrToHkey(ByVal strHkey As String) As Long
  StrToHkey = HKEY_CURRENT_USER 'Return default value
  
  Select Case strHkey
    Case "HKEY_CLASSES_ROOT"
      StrToHkey = HKEY_CLASSES_ROOT
    Case "HKEY_LOCAL_MACHINE"
      StrToHkey = HKEY_LOCAL_MACHINE
    Case "HKEY_USERS"
      StrToHkey = HKEY_USERS
    Case "HKEY_PERFORMANCE_DATA"
      StrToHkey = HKEY_PERFORMANCE_DATA
    Case "HKEY_PERFORMANCE_TEXT"
      StrToHkey = HKEY_PERFORMANCE_TEXT
    Case "HKEY_PERFORMANCE_NLSTEXT"
      StrToHkey = HKEY_PERFORMANCE_NLSTEXT
    Case "HKEY_CURRENT_CONFIG"
      StrToHkey = HKEY_CURRENT_CONFIG
    Case "HKEY_DYN_DATA"
      StrToHkey = HKEY_DYN_DATA
  End Select
End Function

'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log:
' 1    Biblioteka1.0         2007-05-10 11:11:22  Darko Kolakovic
'$
'*******************************************************************************


